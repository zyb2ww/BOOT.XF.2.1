/** @file
  This module produce main entry for BDS phase - BdsEntry.
  When this module was dispatched by DxeCore, gEfiBdsArchProtocolGuid will be installed
  which contains interface of BdsEntry.
  After DxeCore finish DXE phase, gEfiBdsArchProtocolGuid->BdsEntry will be invoked
  to enter BDS phase.

  Copyright (c) 2011 - 2014, Qualcomm Technologies, Inc. All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  Portions Copyright (c) 2004 - 2012, Intel Corporation. All rights reserved.<BR>

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "Bds.h"
#include "Language.h"
//#include "FrontPage.h"
#include "Hotkey.h"
//#include "HwErrRecSupport.h"

// Qcom BdsPlatformLib
VOID
EFIAPI
PlatformBdsLoadShellForNonProdMode ( IN  BDS_COMMON_OPTION *Option);

extern EFI_STATUS EFIAPI BdsLibConnectUsb( VOID );

extern EFI_STATUS EFIAPI BdsLibEnumerateAllForUsb (IN OUT LIST_ENTRY *BdsBootOptionList);

extern EFI_STATUS EFIAPI PlatformBdsAddUSBClass( VOID );

///
/// BDS arch protocol instance initial value.
///
/// Note: Current BDS not directly get the BootMode, DefaultBoot,
/// TimeoutDefault, MemoryTestLevel value from the BDS arch protocol.
/// Please refer to the library useage of BdsLibGetBootMode, BdsLibGetTimeout
/// and PlatformBdsDiagnostics in BdsPlatform.c
///
EFI_HANDLE  gBdsHandle = NULL;

EFI_BDS_ARCH_PROTOCOL  gBds = {
  BdsEntry
};

UINT16                          *mBootNext = NULL;

/**

  Install Boot Device Selection Protocol

  @param ImageHandle     The image handle.
  @param SystemTable     The system table.

  @retval  EFI_SUCEESS  BDS has finished initializing.
                        Return the dispatcher and recall BDS.Entry
  @retval  Other        Return status from AllocatePool() or gBS->InstallProtocolInterface

**/
EFI_STATUS
EFIAPI
BdsInitialize (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_STATUS  Status;

  //
  // Install protocol interface
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &gBdsHandle,
                  &gEfiBdsArchProtocolGuid, &gBds,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

extern UINT32 NumIoHandles;

/**

  This function attempts to boot from a USB device, if present

**/
EFI_STATUS
BdsBootUsbSelect (
  VOID
  )
{
  EFI_STATUS        Status;
  LIST_ENTRY        *Link;
  BDS_COMMON_OPTION *BootOption;
  UINTN             ExitDataSize;
  CHAR16            *ExitData;
  LIST_ENTRY        BootLists;
  CHAR16            Buffer[20];
  UINTN             FoundButCouldNotBoot;
#if 0 //For FrontPage Support
  UINT16            Timeout;
  LIST_ENTRY        *LinkBootNext = NULL;
#endif

  DEBUG ((EFI_D_WARN, "Attempting to boot from USB device\r\n"));

  InitializeListHead (&BootLists);

  ZeroMem (Buffer, sizeof (Buffer));

  if (mBootNext != NULL) {
    //
    // Clear the this variable so it's only exist in this time boot
    //
    gRT->SetVariable (
          L"BootNext",
          &gEfiGlobalVariableGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
          0,
          mBootNext
          );

    //
    // Add the boot next boot option
    //
    UnicodeSPrint (Buffer, sizeof (Buffer), L"Boot%04x", *mBootNext);
    BootOption = BdsLibVariableToOption (&BootLists, Buffer);

    //
    // If fail to get boot option from variable, just return and do nothing.
    //
    if (BootOption == NULL) {
      return EFI_INVALID_PARAMETER;
    }

    BootOption->BootCurrent = *mBootNext;
  }

  //
  // Parse the boot order to get boot option
  //
  BdsLibBuildOptionFromVar (&BootLists, L"BootOrder");
  Link = BootLists.ForwardLink;

  //
  // Parameter check, make sure the loop will be valid
  //
  if (Link == NULL)
    return EFI_INVALID_PARAMETER;

  FoundButCouldNotBoot = 0;

  //
  // Here we make the boot in a loop, until we find a USB device
  // or else we will exit out
  //
  for (;;) {
    //
    // Check the boot option list first
    //
    if (Link == &BootLists)
    {
      //
      // If the list is empty, or we have processed the entire list and
      // there is no enumerated USB device, then exit out
      //
      goto ExitOut;
    }

    //
    // Get the boot option from the link list
    //
    BootOption = CR (Link, BDS_COMMON_OPTION, Link, BDS_LOAD_OPTION_SIGNATURE);

    //
    // According to EFI Specification, if a load option is not marked
    // as LOAD_OPTION_ACTIVE, the boot manager will not automatically
    // load the option.
    //
    if (!IS_LOAD_OPTION_TYPE (BootOption->Attribute, LOAD_OPTION_ACTIVE)) {
      //
      // skip the header of the link list, because it has no boot option
      //
      Link = Link->ForwardLink;
      continue;
    }

    //
    // If we reach here it means we've found a bootable USB entry, so load and execute
    //
    Status = BdsLibBootViaBootOption (BootOption, BootOption->DevicePath, &ExitDataSize, &ExitData);
    if (EFI_ERROR (Status)) {
      //
      // Call platform action to indicate the boot fail
      //
      BootOption->StatusString = GetStringById (STRING_TOKEN (STR_BOOT_FAILED));
      PlatformBdsBootFail (BootOption, Status, ExitData, ExitDataSize);
      FoundButCouldNotBoot++;

      //
      // Check the next boot option
      //
      Link = Link->ForwardLink;

    } else {
      //
      // Call platform action to indicate the boot success
      //
      BootOption->StatusString = GetStringById (STRING_TOKEN (STR_BOOT_SUCCEEDED));
      PlatformBdsBootSuccess (BootOption);

      // If failure occurs then wait for key input and then reset
      gST->ConOut->ClearScreen(gST->ConOut);
      gST->ConOut->OutputString (
                    gST->ConOut,
                    L"Successfully executed boot option. Press any key to reset.\r\n"
                    );
      {
        EFI_INPUT_KEY Key;
        Key.ScanCode = SCAN_NULL;
        Key.UnicodeChar = 0;

        while ((Key.ScanCode == SCAN_NULL) &&
               (Key.UnicodeChar == 0))
        {
          gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
        }
      }
      gST->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);

/* QCOM: Do not support FrontPage */
#if 0
      //
      // Boot success, then stop process the boot order, and
      // present the boot manager menu, front page
      //
      Timeout = 0xffff;
      PlatformBdsEnterFrontPage (Timeout, FALSE);

      //
      // Rescan the boot option list, avoid potential risk of the boot
      // option change in front page
      //
      if (BootNextExist) {
        LinkBootNext = BootLists.ForwardLink;
      }

      InitializeListHead (&BootLists);
      if (LinkBootNext != NULL) {
        //
        // Reserve the boot next option
        //
        InsertTailList (&BootLists, LinkBootNext);
      }

      BdsLibBuildOptionFromVar (&BootLists, L"BootOrder");
      Link = BootLists.ForwardLink;
#endif
    }

  }

ExitOut:
  if (FoundButCouldNotBoot)
    return EFI_LOAD_ERROR;
  else
    return EFI_NO_MEDIA;
}

extern EFI_STATUS BdsWaitForSingleEvent (IN UINT64 Timeout);
extern BOOLEAN USBAlreadyConnected;

/**

  This function attempts to boot for the boot order specified
  by platform policy.

**/
VOID
BdsBootDeviceSelect (
  VOID
  )
{
  EFI_STATUS        Status;
  LIST_ENTRY        *Link;
  BDS_COMMON_OPTION *BootOption;
  UINTN             ExitDataSize;
  CHAR16            *ExitData;
  LIST_ENTRY        BootLists;
  CHAR16            Buffer[20];
  STATIC UINT16     IsSecondTry = 0;

#if 0 //QCOM: If FrontPage support
  BOOLEAN           BootNextExist;
  UINT16            Timeout;
  LIST_ENTRY        *LinkBootNext;
  LinkBootNext  = NULL;
  BootNextExist = FALSE;
#endif
  InitializeListHead (&BootLists);

  //
  // First check the boot next option
  //
  ZeroMem (Buffer, sizeof (Buffer));

  if (mBootNext != NULL) {
#if 0
    //
    // Indicate we have the boot next variable, so this time
    // boot will always have this boot option
    //
    BootNextExist = TRUE;
#endif

    //
    // Clear the this variable so it's only exist in this time boot
    //
    gRT->SetVariable (
          L"BootNext",
          &gEfiGlobalVariableGuid,
          EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
          0,
          mBootNext
          );

    //
    // Add the boot next boot option
    //
    UnicodeSPrint (Buffer, sizeof (Buffer), L"Boot%04x", *mBootNext);
    BootOption = BdsLibVariableToOption (&BootLists, Buffer);

    //
    // If fail to get boot option from variable, try the next boot option
    //
    if (BootOption != NULL) {  
       BootOption->BootCurrent = *mBootNext;
	}
  }
  //
  // Parse the boot order to get boot option
  //
  BdsLibBuildOptionFromVar (&BootLists, L"BootOrder");

/* TODO: QCOM removed this for now - need to evaluate whether this needs to be skipped */
#if 0
  //
  // When we didn't have chance to build boot option variables in the first
  // full configuration boot (e.g.: Reset in the first page or in Device Manager),
  // we have no boot options in the following mini configuration boot.
  // Give the last chance to enumerate the boot options.
  //
  if (IsListEmpty (&BootLists)) {
    BdsLibEnumerateAllBootOption (&BootLists);
  }
#endif

  Link = BootLists.ForwardLink;

  //
  // Parameter check, make sure the loop will be valid
  //
  if (Link == NULL)
    return ;

  //
  // Here we make the boot in a loop, every boot success will
  // return to the front page
  //
  for (;;) {
    //
    // Check the boot option list first
    //
    if (Link == &BootLists) {
      //
      // There are two ways to enter here:
      // 1. There is no active boot option, attempt to enumerate all
      //    bootable devices, in case a new device has been added since last
      //    enumerating
      // 2. All the active boot option processed, and there is no
      //    one is success to boot, then we back here to allow user
      //    add new active boot option
      //

      if (IsSecondTry == 0) {
        IsSecondTry = 1;
        BdsLibEnumerateAllBootOption (&BootLists);
        BdsBootDeviceSelect();
      }

      // Enter shell if enabled
      PlatformBdsLoadShellForNonProdMode(NULL);

      // If failure occurs then wait for key input and then reset
      gST->ConOut->ClearScreen(gST->ConOut);
      gST->ConOut->OutputString (
                    gST->ConOut,
                    L"ERROR: Unable to find a bootable option. Press any key to shut down.\r\n"
                    );
      {
        EFI_INPUT_KEY Key;
        Key.ScanCode = SCAN_NULL;
        Key.UnicodeChar = 0;

        while ((Key.ScanCode == SCAN_NULL) &&
               (Key.UnicodeChar == 0))
        {
          gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
        }
      }
      // TODO: remove line below and uncomment shutdown
      gST->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
      //gST->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);

/* QCOM: Do not support FrontPage */
#if 0
      Timeout = 0xffff;
      PlatformBdsEnterFrontPage (Timeout, FALSE);
      InitializeListHead (&BootLists);
      BdsLibBuildOptionFromVar (&BootLists, L"BootOrder");
      Link = BootLists.ForwardLink;
#endif
      continue;
    }
    //
    // Get the boot option from the link list
    //
    BootOption = CR (Link, BDS_COMMON_OPTION, Link, BDS_LOAD_OPTION_SIGNATURE);

    //
    // According to EFI Specification, if a load option is not marked
    // as LOAD_OPTION_ACTIVE, the boot manager will not automatically
    // load the option.
    //
    if (!IS_LOAD_OPTION_TYPE (BootOption->Attribute, LOAD_OPTION_ACTIVE)) {
      //
      // skip the header of the link list, because it has no boot option
      //
      Link = Link->ForwardLink;
      continue;
    }

    if (DevicePathType (BootOption->DevicePath) != BBS_DEVICE_PATH)
    {
      //
      // Make sure the boot option device path connected,
      // but ignore the BBS device path
      //
      //
      // Notes: the internal shell can not been connected with device path
      // so we do not check the status here
      //
      BdsLibConnectDevicePath (BootOption->DevicePath);
    }

/* QCOM: Do not support FrontPage */
#if 0
    //
    // Restore to original mode before launching boot option.
    //
    BdsSetConsoleMode (FALSE);
#endif

    PlatformBdsAddUSBClass();
	
    //
    // All the driver options should have been processed since
    // now boot will be performed.
    //
    Status = BdsLibBootViaBootOption (BootOption, BootOption->DevicePath, &ExitDataSize, &ExitData);
    if (Status != EFI_SUCCESS) {
      //
      // Call platform action to indicate the boot fail
      //
      BootOption->StatusString = GetStringById (STRING_TOKEN (STR_BOOT_FAILED));
      PlatformBdsBootFail (BootOption, Status, ExitData, ExitDataSize);

      //
      // Check the next boot option
      //
      Link = Link->ForwardLink;
      continue;

    } else {
      //
      // Call platform action to indicate the boot success
      //
      BootOption->StatusString = GetStringById (STRING_TOKEN (STR_BOOT_SUCCEEDED));
      PlatformBdsBootSuccess (BootOption);

      // If failure occurs then wait for key input and then reset
      gST->ConOut->ClearScreen(gST->ConOut);
      gST->ConOut->OutputString (
                    gST->ConOut,
                    L"Successfully executed boot option. Press any key to reset.\r\n"
                    );
      {
        EFI_INPUT_KEY Key;
        Key.ScanCode = SCAN_NULL;
        Key.UnicodeChar = 0;

        while ((Key.ScanCode == SCAN_NULL) &&
               (Key.UnicodeChar == 0))
        {
          gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
        }
      }
      gST->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);

/* QCOM: Do not support FrontPage */
#if 0
      //
      // Boot success, then stop process the boot order, and
      // present the boot manager menu, front page
      //
      Timeout = 0xffff;
      PlatformBdsEnterFrontPage (Timeout, FALSE);

      //
      // Rescan the boot option list, avoid potential risk of the boot
      // option change in front page
      //
      if (BootNextExist) {
        LinkBootNext = BootLists.ForwardLink;
      }

      InitializeListHead (&BootLists);
      if (LinkBootNext != NULL) {
        //
        // Reserve the boot next option
        //
        InsertTailList (&BootLists, LinkBootNext);
      }

      BdsLibBuildOptionFromVar (&BootLists, L"BootOrder");
      Link = BootLists.ForwardLink;
#endif
    }
  }

}

/**
  Validate the device path instance.

  Only base on the length filed in the device path node to validate the device path.

  @param  DevicePath         A pointer to a device path data structure.
  @param  MaxSize            Max valid device path size. If big than this size,
                             return error.

  @retval TRUE               An valid device path.
  @retval FALSE              An invalid device path.

**/
BOOLEAN
IsValidDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  IN UINTN                     MaxSize
  )
{
  UINTN  Size;
  UINTN  NodeSize;

  if (DevicePath == NULL) {
    return TRUE;
  }

  Size = 0;

  while (!IsDevicePathEnd (DevicePath)) {
    NodeSize = DevicePathNodeLength (DevicePath);
    if (NodeSize < END_DEVICE_PATH_LENGTH) {
      return FALSE;
    }

    Size += NodeSize;
    if (Size > MaxSize) {
      return FALSE;
    }

    DevicePath = NextDevicePathNode (DevicePath);
  }

  Size += DevicePathNodeLength (DevicePath);
  if (Size > MaxSize) {
    return FALSE;
  }

  return TRUE;
}

/**

  Validate input console variable data.

  If found the device path is not a valid device path, remove the variable.

  @param VariableName             Input console variable name.

**/
VOID
BdsFormalizeConsoleVariable (
  IN  CHAR16          *VariableName
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  UINTN                     VariableSize;
  EFI_STATUS                Status;

  DevicePath = BdsLibGetVariableAndSize (
                      VariableName,
                      &gEfiGlobalVariableGuid,
                      &VariableSize
                      );
  if (!IsValidDevicePath (DevicePath, VariableSize)) {
    Status = gRT->SetVariable (
                    VariableName,
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    0,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  }
}

/**

  Formalize Bds global variables.

 1. For ConIn/ConOut/ConErr, if found the device path is not a valid device path, remove the variable.
 2. For OsIndicationsSupported, Create a BS/RT/UINT64 variable to report caps
 3. Delete OsIndications variable if it is not NV/BS/RT UINT64
 Item 3 is used to solve case when OS corrupts OsIndications. Here simply delete this NV variable.

**/
VOID
BdsFormalizeEfiGlobalVariable (
  VOID
  )
{
  EFI_STATUS Status;
  UINT64     OsIndicationSupport;
  UINT64     OsIndication;
  UINTN      DataSize;
  UINT32     Attributes;

  //
  // Validate Console variable.
  //
  BdsFormalizeConsoleVariable (L"ConIn");
  BdsFormalizeConsoleVariable (L"ConOut");
  BdsFormalizeConsoleVariable (L"ErrOut");

  //
  // OS indicater support variable
  //
  OsIndicationSupport = EFI_OS_INDICATIONS_BOOT_TO_FW_UI;
  Status = gRT->SetVariable (
                  L"OsIndicationsSupported",
                  &gEfiGlobalVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof(UINT64),
                  &OsIndicationSupport
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // If OsIndications is invalid, remove it.
  // Invalid case
  //   1. Data size != UINT64
  //   2. OsIndication value inconsistence
  //   3. OsIndication attribute inconsistence
  //
  OsIndication = 0;
  Attributes = 0;
  DataSize = sizeof(UINT64);
  Status = gRT->GetVariable (
                  L"OsIndications",
                  &gEfiGlobalVariableGuid,
                  &Attributes,
                  &DataSize,
                  &OsIndication
                  );

  if (!EFI_ERROR(Status)) {
    if (DataSize != sizeof(UINT64) ||
        (OsIndication & ~OsIndicationSupport) != 0 ||
        Attributes != (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE)){

      DEBUG ((EFI_D_ERROR, "Unformalized OsIndications variable exists. Delete it\n"));
      Status = gRT->SetVariable (
                      L"OsIndications",
                      &gEfiGlobalVariableGuid,
                      Attributes,
                      0,
                      &OsIndication
                      );
      ASSERT_EFI_ERROR (Status);
    }
  }

}

/**

  Service routine for BdsInstance->Entry(). Devices are connected, the
  consoles are initialized, and the boot options are tried.

  @param This             Protocol Instance structure.

**/
VOID
EFIAPI
BdsEntry (
  IN EFI_BDS_ARCH_PROTOCOL  *This
  )
{
  LIST_ENTRY                      DriverOptionList;
  LIST_ENTRY                      BootOptionList;
  UINTN                           BootNextSize;
  CHAR16                          *FirmwareVendor;

  //
  // Insert the performance probe
  //
  PERF_END (NULL, "DXE", NULL, 0);
  PERF_START (NULL, "BDS", NULL, 0);

  //
  // Initialize the global system boot option and driver option
  //
  InitializeListHead (&DriverOptionList);
  InitializeListHead (&BootOptionList);

  //
  // Initialize hotkey service
  //
  InitializeHotkeyService ();

  //
  // Fill in FirmwareVendor and FirmwareRevision from PCDs
  //
  FirmwareVendor = (CHAR16 *)PcdGetPtr (PcdFirmwareVendor);
  gST->FirmwareVendor = AllocateRuntimeCopyPool (StrSize (FirmwareVendor), FirmwareVendor);
  ASSERT (gST->FirmwareVendor != NULL);
  gST->FirmwareRevision = PcdGet32 (PcdFirmwareRevision);

  //
  // Fixup Tasble CRC after we updated Firmware Vendor and Revision
  //
  gBS->CalculateCrc32 ((VOID *)gST, sizeof(EFI_SYSTEM_TABLE), &gST->Hdr.CRC32);

  //
  // Validate Variable.
  //
  BdsFormalizeEfiGlobalVariable();

  //
  // Do the platform init, can be customized by OEM/IBV
  //
  PERF_START (NULL, "PlatformBds", "BDS", 0);
  PlatformBdsInit ();

  //InitializeHwErrRecSupport();

  //
  // bugbug: platform specific code
  // Initialize the platform specific string and language
  //
  InitializeStringSupport ();
  InitializeLanguage (TRUE);
/* QCOM: Do not support FrontPage */
#if 0
  InitializeFrontPage (TRUE);
#endif

  //
  // Set up the device list based on EFI 1.1 variables
  // process Driver#### and Load the driver's in the
  // driver option list
  //
  BdsLibBuildOptionFromVar (&DriverOptionList, L"DriverOrder");
  if (!IsListEmpty (&DriverOptionList)) {
    BdsLibLoadDrivers (&DriverOptionList);
  }
  //
  // Check if we have the boot next option
  //
  mBootNext = BdsLibGetVariableAndSize (
                L"BootNext",
                &gEfiGlobalVariableGuid,
                &BootNextSize
                );

  //
  // Setup some platform policy here
  //
  PlatformBdsPolicyBehavior (&DriverOptionList, &BootOptionList, BdsProcessCapsules, BdsMemoryTest);
  PERF_END (NULL, "PlatformBds", "BDS", 0);

  //
  // BDS select the boot device to load OS
  //
  BdsBootDeviceSelect ();

  //
  // Only assert here since this is the right behavior, we should never
  // return back to DxeCore.
  //
  ASSERT (FALSE);

  return ;
}

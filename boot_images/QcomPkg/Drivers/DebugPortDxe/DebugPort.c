/** @file DebugPort.c
  Top level C file for debugport driver.  Contains initialization function.
  This driver layers on top of SerialIo.
  ALL CODE IN THE SERIALIO STACK MUST BE RE-ENTRANT AND CALLABLE FROM
  INTERRUPT CONTEXT
 
  Copyright (c) 2012 Qualcomm Technologies, Inc.  All Rights
  Reserved. Qualcomm Technologies Proprietary and Confidential. 
  Copyright (c) 2006 - 2009, Intel Corporation. All rights
  reserved.<BR> This program and the accompanying materials are
  licensed and made available under the terms and conditions of
  the BSD License which accompanies this distribution.  The full
  text of the license may be found at
  http://opensource.org/licenses/bsd-license.php 

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS"
  BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND,
  EITHER EXPRESS OR IMPLIED. 

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 11/01/12   plc     New File from Joel Winarske for WinDbg support

=============================================================================*/

#include "DebugPort.h"

//
// Globals
//
EFI_DRIVER_BINDING_PROTOCOL gDebugPortDriverBinding = {
  DebugPortSupported,
  DebugPortStart,
  DebugPortStop,
  DEBUGPORT_DRIVER_VERSION,
  NULL,
  NULL
};

DEBUGPORT_DEVICE mDebugPortDevice = {
  DEBUGPORT_DEVICE_SIGNATURE,
  (EFI_HANDLE) 0,
  (EFI_HANDLE) 0,
  (VOID *) NULL,
  (EFI_DEVICE_PATH_PROTOCOL *) NULL,
  {
    DebugPortReset,
    DebugPortWrite,
    DebugPortRead,
    DebugPortPoll
  },
  (EFI_HANDLE) 0,
  (EFI_SERIAL_IO_PROTOCOL *) NULL,
  DEBUGPORT_UART_DEFAULT_BAUDRATE,
  DEBUGPORT_UART_DEFAULT_FIFO_DEPTH,
  DEBUGPORT_UART_DEFAULT_TIMEOUT,
  (EFI_PARITY_TYPE) DEBUGPORT_UART_DEFAULT_PARITY,
  DEBUGPORT_UART_DEFAULT_DATA_BITS,
  (EFI_STOP_BITS_TYPE) DEBUGPORT_UART_DEFAULT_STOP_BITS
};

static UINTN write_stats[128];
static UINTN actual_write_stats[128];
static UINTN read_stats[128];
static UINTN read_stalls[128];
static UINTN actual_read_stats[128];

/**
  Local worker function to obtain device path information from DebugPort variable.

  Records requested settings in DebugPort device structure.

**/
VOID
GetDebugPortVariable (
  VOID
  )
{
  UINTN                     DataSize;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_STATUS                Status;

  DataSize = 0;

  Status = gRT->GetVariable (
                  (CHAR16 *) EFI_DEBUGPORT_VARIABLE_NAME,
                  &gEfiDebugPortVariableGuid,
                  NULL,
                  &DataSize,
                  mDebugPortDevice.DebugPortVariable
                  );

  if (Status == EFI_BUFFER_TOO_SMALL) {
    if (mDebugPortDevice.DebugPortVariable != NULL) {
      FreePool (mDebugPortDevice.DebugPortVariable);
    }

    mDebugPortDevice.DebugPortVariable = AllocatePool (DataSize);
    if (mDebugPortDevice.DebugPortVariable != NULL) {
      gRT->GetVariable (
            (CHAR16 *) EFI_DEBUGPORT_VARIABLE_NAME,
            &gEfiDebugPortVariableGuid,
            NULL,
            &DataSize,
            mDebugPortDevice.DebugPortVariable
            );
      DevicePath = (EFI_DEVICE_PATH_PROTOCOL *) mDebugPortDevice.DebugPortVariable;
      while (!IsDevicePathEnd (DevicePath) && !IS_UART_DEVICEPATH (DevicePath)) {
        DevicePath = NextDevicePathNode (DevicePath);
      }

      if (IsDevicePathEnd (DevicePath)) {
        FreePool (mDebugPortDevice.DebugPortVariable);
        mDebugPortDevice.DebugPortVariable = NULL;
      } else {
        CopyMem (
          &mDebugPortDevice.BaudRate,
          &((UART_DEVICE_PATH *) DevicePath)->BaudRate,
          sizeof (((UART_DEVICE_PATH *) DevicePath)->BaudRate)
          );
        mDebugPortDevice.ReceiveFifoDepth = DEBUGPORT_UART_DEFAULT_FIFO_DEPTH;
        mDebugPortDevice.Timeout          = DEBUGPORT_UART_DEFAULT_TIMEOUT;
        CopyMem (
          &mDebugPortDevice.Parity,
          &((UART_DEVICE_PATH *) DevicePath)->Parity,
          sizeof (((UART_DEVICE_PATH *) DevicePath)->Parity)
          );
        CopyMem (
          &mDebugPortDevice.DataBits,
          &((UART_DEVICE_PATH *) DevicePath)->DataBits,
          sizeof (((UART_DEVICE_PATH *) DevicePath)->DataBits)
          );
        CopyMem (
          &mDebugPortDevice.StopBits,
          &((UART_DEVICE_PATH *) DevicePath)->StopBits,
          sizeof (((UART_DEVICE_PATH *) DevicePath)->StopBits)
          );
      }
    }
  }
}

/**
  Debug Port Driver entry point.

  Reads DebugPort variable to determine what device and settings to use as the
  debug port.  Binds exclusively to SerialIo. Reverts to defaults if no variable
  is found.

  @param[in] ImageHandle       The firmware allocated handle for the EFI image.
  @param[in] SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS          The entry point is executed successfully.
  @retval EFI_OUT_OF_RESOURCES Fails to allocate memory for device.
  @retval other                Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
InitializeDebugPortDriver (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
{
  EFI_STATUS    Status;

  //
  // Install driver model protocol(s).
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gDebugPortDriverBinding,
             ImageHandle,
             &gDebugPortComponentName,
             &gDebugPortComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Checks to see if there's not already a DebugPort interface somewhere.

  If there's a DEBUGPORT variable, the device path must match exactly.  If there's
  no DEBUGPORT variable, then device path is not checked and does not matter.
  Checks to see that there's a serial io interface on the controller handle
  that can be bound BY_DRIVER | EXCLUSIVE.
  If all these tests succeed, then we return EFI_SUCCESS, else, EFI_UNSUPPORTED
  or other error returned by OpenProtocol.

  @param  This                 Protocol instance pointer.
  @param  ControllerHandle     Handle of device to test.
  @param  RemainingDevicePath  Optional parameter use to pick a specific child
                               device to start.

  @retval EFI_SUCCESS          This driver supports this device.
  @retval EFI_UNSUPPORTED      Debug Port device is not supported.
  @retval EFI_OUT_OF_RESOURCES Fails to allocate memory for device.
  @retval others               Some error occurs.

**/
EFI_STATUS
EFIAPI
DebugPortSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EFI_DEVICE_PATH_PROTOCOL  *Dp1;
  EFI_DEVICE_PATH_PROTOCOL  *Dp2;
  EFI_SERIAL_IO_PROTOCOL    *SerialIo;
  EFI_DEBUGPORT_PROTOCOL    *DebugPortInterface;
  EFI_HANDLE                TempHandle;

  //
  // Check to see that there's not a debugport protocol already published,
  // since only one standard UART serial port could be supported by this driver.
  //
  if (gBS->LocateProtocol (&gEfiDebugPortProtocolGuid, NULL, (VOID **) &DebugPortInterface) != EFI_NOT_FOUND) {
    return EFI_UNSUPPORTED;
  }
  //
  // Read DebugPort variable to determine debug port selection and parameters
  //
  GetDebugPortVariable ();

  if (mDebugPortDevice.DebugPortVariable != NULL) {
    //
    // There's a DEBUGPORT variable, so do LocateDevicePath and check to see if
    // the closest matching handle matches the controller handle, and if it does,
    // check to see that the remaining device path has the DebugPort GUIDed messaging
    // device path only.  Otherwise, it's a mismatch and EFI_UNSUPPORTED is returned.
    //
    Dp1 = DuplicateDevicePath ((EFI_DEVICE_PATH_PROTOCOL *) mDebugPortDevice.DebugPortVariable);
    if (Dp1 == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    Dp2 = Dp1;

    Status = gBS->LocateDevicePath (
                    &gEfiSerialIoProtocolGuid,
                    &Dp2,
                    &TempHandle
                    );

    if (Status == EFI_SUCCESS && TempHandle != ControllerHandle) {
      Status = EFI_UNSUPPORTED;
    }

    if (Status == EFI_SUCCESS &&
        (Dp2->Type != MESSAGING_DEVICE_PATH ||
         Dp2->SubType != MSG_VENDOR_DP ||
         *((UINT16 *) Dp2->Length) != sizeof (DEBUGPORT_DEVICE_PATH))) {

      Status = EFI_UNSUPPORTED;
    }

    if (Status == EFI_SUCCESS && !CompareGuid (&gEfiDebugPortDevicePathGuid, (GUID *) (Dp2 + 1))) {
      Status = EFI_UNSUPPORTED;
    }

    FreePool (Dp1);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiSerialIoProtocolGuid,
                  (VOID **) &SerialIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBS->CloseProtocol (
        ControllerHandle,
        &gEfiSerialIoProtocolGuid,
        This->DriverBindingHandle,
        ControllerHandle
        );

  return EFI_SUCCESS;
}

/**
  Binds exclusively to serial io on the controller handle, Produces DebugPort
  protocol and DevicePath on new handle.

  @param  This                 Protocol instance pointer.
  @param  ControllerHandle     Handle of device to bind driver to.
  @param  RemainingDevicePath  Optional parameter use to pick a specific child
                               device to start.

  @retval EFI_SUCCESS          This driver is added to ControllerHandle.
  @retval EFI_OUT_OF_RESOURCES Fails to allocate memory for device.
  @retval others               Some error occurs.

**/
EFI_STATUS
EFIAPI
DebugPortStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  DEBUGPORT_DEVICE_PATH     DebugPortDP;
  EFI_DEVICE_PATH_PROTOCOL  EndDP;
  EFI_DEVICE_PATH_PROTOCOL  *Dp1;
  UINTN i;

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiSerialIoProtocolGuid,
                  (VOID **) &mDebugPortDevice.SerialIoBinding,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mDebugPortDevice.SerialIoDeviceHandle = ControllerHandle;

  //
  // Initialize the Serial Io interface...
  //
  mDebugPortDevice.BaudRate          = 0;
  mDebugPortDevice.ReceiveFifoDepth  = 0;
  mDebugPortDevice.Timeout           = 0;
  mDebugPortDevice.Parity            = DefaultParity;
  mDebugPortDevice.DataBits          = 0;
  mDebugPortDevice.StopBits          = DefaultStopBits;

  //
  // Reset
  //
  mDebugPortDevice.SerialIoBinding->Reset (mDebugPortDevice.SerialIoBinding);

  //
  // Create device path instance for DebugPort
  //
  DebugPortDP.Header.Type     = MESSAGING_DEVICE_PATH;
  DebugPortDP.Header.SubType  = MSG_VENDOR_DP;
  SetDevicePathNodeLength (&(DebugPortDP.Header), sizeof (DebugPortDP));
  CopyGuid (&DebugPortDP.Guid, &gEfiDebugPortDevicePathGuid);

  Dp1 = DevicePathFromHandle (ControllerHandle);
  if (Dp1 == NULL) {
    Dp1 = &EndDP;
    SetDevicePathEndNode (Dp1);
  }

  mDebugPortDevice.DebugPortDevicePath = AppendDevicePathNode (Dp1, (EFI_DEVICE_PATH_PROTOCOL *) &DebugPortDP);
  if (mDebugPortDevice.DebugPortDevicePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  // Publish DebugPort and Device Path protocols
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &mDebugPortDevice.DebugPortDeviceHandle,
                  &gEfiDevicePathProtocolGuid,
                  mDebugPortDevice.DebugPortDevicePath,
                  &gEfiDebugPortProtocolGuid,
                  &mDebugPortDevice.DebugPortInterface,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
          ControllerHandle,
          &gEfiSerialIoProtocolGuid,
          This->DriverBindingHandle,
          ControllerHandle
          );
    return Status;
  }
  //
  // Connect debugport child to serial io
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiSerialIoProtocolGuid,
                  (VOID **) &mDebugPortDevice.SerialIoBinding,
                  This->DriverBindingHandle,
                  mDebugPortDevice.DebugPortDeviceHandle,
                  EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
                  );

  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
          ControllerHandle,
          &gEfiSerialIoProtocolGuid,
          This->DriverBindingHandle,
          ControllerHandle
          );
    return Status;
  }

  for(i=0; i<128; i++) {
    read_stats[i] = 0;
    actual_read_stats[i] = 0;
    write_stats[i] = 0;
    actual_write_stats[i] = 0;
  }

  return EFI_SUCCESS;
}

/**
  Stop this driver on ControllerHandle by removing Serial IO protocol on
  the ControllerHandle.

  @param  This              Protocol instance pointer.
  @param  ControllerHandle  Handle of device to stop driver on
  @param  NumberOfChildren  Number of Handles in ChildHandleBuffer. If number of
                            children is zero stop the entire bus driver.
  @param  ChildHandleBuffer List of Child Handles to Stop.

  @retval EFI_SUCCESS       This driver is removed ControllerHandle.
  @retval other             This driver was not removed from this device.

**/
EFI_STATUS
EFIAPI
DebugPortStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     ControllerHandle,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  EFI_STATUS  Status;

  if (NumberOfChildren == 0) {
    //
    // Close the bus driver
    //
    gBS->CloseProtocol (
          ControllerHandle,
          &gEfiSerialIoProtocolGuid,
          This->DriverBindingHandle,
          ControllerHandle
          );

    mDebugPortDevice.SerialIoBinding = NULL;

    gBS->CloseProtocol (
          ControllerHandle,
          &gEfiDevicePathProtocolGuid,
          This->DriverBindingHandle,
          ControllerHandle
          );

    FreePool (mDebugPortDevice.DebugPortDevicePath);

    return EFI_SUCCESS;
  } else {
    //
    // Disconnect SerialIo child handle
    //
    Status = gBS->CloseProtocol (
                    mDebugPortDevice.SerialIoDeviceHandle,
                    &gEfiSerialIoProtocolGuid,
                    This->DriverBindingHandle,
                    mDebugPortDevice.DebugPortDeviceHandle
                    );

    if (EFI_ERROR (Status)) {
      return Status;
    }
    //
    // Unpublish our protocols (DevicePath, DebugPort)
    //
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    mDebugPortDevice.DebugPortDeviceHandle,
                    &gEfiDevicePathProtocolGuid,
                    mDebugPortDevice.DebugPortDevicePath,
                    &gEfiDebugPortProtocolGuid,
                    &mDebugPortDevice.DebugPortInterface,
                    NULL
                    );

    if (EFI_ERROR (Status)) {
      gBS->OpenProtocol (
            ControllerHandle,
            &gEfiSerialIoProtocolGuid,
            (VOID **) &mDebugPortDevice.SerialIoBinding,
            This->DriverBindingHandle,
            mDebugPortDevice.DebugPortDeviceHandle,
            EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER
            );
    } else {
      mDebugPortDevice.DebugPortDeviceHandle = NULL;
    }
  }

  return Status;
}

/**
  DebugPort protocol member function.  Calls SerialIo:GetControl to flush buffer.
  We cannot call SerialIo:SetAttributes because it uses pool services, which use
  locks, which affect TPL, so it's not interrupt context safe or re-entrant.
  SerialIo:Reset() calls SetAttributes, so it can't be used either.

  The port itself should be fine since it was set up during initialization.

  @param  This              Protocol instance pointer.

  @return EFI_SUCCESS       Always.

**/
EFI_STATUS
EFIAPI
DebugPortReset (
  IN EFI_DEBUGPORT_PROTOCOL   *This
  )
{
  UINTN             BufferSize;
  UINT32            BitBucket[1024];

  BufferSize = 1024;
  This->Read (This, 0, &BufferSize, BitBucket);
  return EFI_SUCCESS;
}

/**
  DebugPort protocol member function.  Calls SerialIo:Read() after setting
  if it's different than the last SerialIo access.

  @param  This                Pointer to DebugPort protocol.
  @param  Timeout             Timeout value.
  @param  BufferSize          On input, the size of Buffer.
                              On output, the amount of data actually written.
  @param  Buffer              Pointer to buffer to read.

  @retval EFI_SUCCESS
  @retval others

**/
EFI_STATUS
EFIAPI
DebugPortRead (
  IN EFI_DEBUGPORT_PROTOCOL   *This,
  IN UINT32                   Timeout,
  IN OUT UINTN                *BufferSize,
  OUT VOID                    *Buffer
  )
{
  DEBUGPORT_DEVICE  *DebugPortDevice;
  UINTN             LocalBufferSize;
  EFI_STATUS        Status;
  UINT8             *BufferPtr;
  UINTN             LocalTimeout = 450000;  // 3000 attempts

  DebugPortDevice = DEBUGPORT_DEVICE_FROM_THIS (This);
  BufferPtr       = Buffer;

  /* MSFT workaround - required until they fix their boot code! */
  *BufferSize     = 1;


  LocalBufferSize = *BufferSize;

  if (*BufferSize < 128)  
    read_stats[*BufferSize] += 1;

  do {
    Status = DebugPortDevice->SerialIoBinding->Read (
                                                DebugPortDevice->SerialIoBinding,
                                                &LocalBufferSize,
                                                BufferPtr
                                                );
    if (Status == EFI_TIMEOUT) {
      if (LocalTimeout > DEBUGPORT_UART_DEFAULT_TIMEOUT) {

        if (*BufferSize < 128)  
          read_stalls[*BufferSize] += 1;

        gBS->Stall (DEBUGPORT_UART_DEFAULT_TIMEOUT);
        LocalTimeout -= DEBUGPORT_UART_DEFAULT_TIMEOUT;
      } else {
        LocalTimeout = 0;
      }
    } else if (EFI_ERROR (Status)) {
      break;
    }

    
    BufferPtr += LocalBufferSize;
    LocalBufferSize = *BufferSize - (BufferPtr - (UINT8 *) Buffer);
  } while (LocalBufferSize != 0 && LocalTimeout > 0);

  *BufferSize = (UINTN) (BufferPtr - (UINT8 *) Buffer);

  if (*BufferSize < 128)  
    actual_read_stats[*BufferSize] += 1;

  return Status;
}

/**
  DebugPort protocol member function.  Calls SerialIo:Write()

  @param  This                Pointer to DebugPort protocol.
  @param  Timeout             Timeout value.
  @param  BufferSize          On input, the size of Buffer.
                              On output, the amount of data actually written.
  @param  Buffer              Pointer to buffer to read.

  @retval EFI_SUCCESS         The data was written.
  @retval others              Fails when writing data to debug port device.

**/
EFI_STATUS
EFIAPI
DebugPortWrite (
  IN EFI_DEBUGPORT_PROTOCOL   *This,
  IN UINT32                   Timeout,
  IN OUT UINTN                *BufferSize,
  IN VOID                     *Buffer
  )
{
  EFI_STATUS        Status = EFI_SUCCESS;
  DEBUGPORT_DEVICE  *DebugPortDevice;

  DebugPortDevice = DEBUGPORT_DEVICE_FROM_THIS (This);

  if (*BufferSize < 128)
    write_stats[*BufferSize] += 1;

  Status = DebugPortDevice->SerialIoBinding->Write (
    DebugPortDevice->SerialIoBinding,
    BufferSize,
    (UINT8 *) Buffer
  );

  if (*BufferSize < 128)
    actual_write_stats[*BufferSize] += 1;

  return Status;
}

/**
  DebugPort protocol member function.  Calls 
  SerialIo:GetControl().

  @param  This                Pointer to DebugPort protocol.

  @retval EFI_SUCCESS         At least 1 character is ready to be read from
                              the DebugPort interface.
  @retval EFI_NOT_READY       There are no characters ready to read from the
                              DebugPort interface
  @retval EFI_DEVICE_ERROR    A hardware failure occurred... (from SerialIo)

**/
EFI_STATUS
EFIAPI
DebugPortPoll (
  IN EFI_DEBUGPORT_PROTOCOL   *This
  )
{
  EFI_STATUS        Status;
  UINT32            SerialControl;
  DEBUGPORT_DEVICE  *DebugPortDevice;

  DebugPortDevice = DEBUGPORT_DEVICE_FROM_THIS (This);

  Status = DebugPortDevice->SerialIoBinding->GetControl (
                                              DebugPortDevice->SerialIoBinding,
                                              &SerialControl
                                              );

  if (!EFI_ERROR (Status)) {
    if ((SerialControl & EFI_SERIAL_INPUT_BUFFER_EMPTY) != 0) {
      Status = EFI_NOT_READY;
    } else {
      Status = EFI_SUCCESS;
    }
  }

  return Status;
}

/**
  Unload function that is registered in the LoadImage protocol.  It un-installs
  protocols produced and deallocates pool used by the driver.  Called by the core
  when unloading the driver.

  @param  ImageHandle

  @retval EFI_SUCCESS     Unload Debug Port driver successfully.
  @retval EFI_ABORTED     Serial IO is still binding.

**/
EFI_STATUS
EFIAPI
ImageUnloadHandler (
  EFI_HANDLE ImageHandle
  )
{
  if (mDebugPortDevice.SerialIoBinding != NULL) {
    return EFI_ABORTED;
  }

  //
  // Clean up allocations
  //
  if (mDebugPortDevice.DebugPortVariable != NULL) {
    FreePool (mDebugPortDevice.DebugPortVariable);
  }

  return EFI_SUCCESS;
}

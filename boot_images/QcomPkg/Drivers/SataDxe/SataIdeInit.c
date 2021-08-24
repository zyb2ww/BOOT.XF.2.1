/** @file
  This driver module produces IDE_CONTROLLER_INIT protocol for Sata Controllers.
  
  Copyright (c) 2014 Qualcomm Technologies, Inc.	All Rights Reserved.
  
  Portions Copyright (c) 2011, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   -----   ----------------------------------------------------------- 
2014/11/10   rm      Initial Verison

=============================================================================*/

#include "SataIdeInit.h"

//
// Interface functions of IDE_CONTROLLER_INIT protocol
//
/**
  Returns the information about the specified IDE channel.
  
  This function can be used to obtain information about a particular IDE channel.
  The driver entity uses this information during the enumeration process. 
  
  If Enabled is set to FALSE, the driver entity will not scan the channel. Note 
  that it will not prevent an operating system driver from scanning the channel.
  
  For most of today's controllers, MaxDevices will either be 1 or 2. For SATA 
  controllers, this value will always be 1. SATA configurations can contain SATA 
  port multipliers. SATA port multipliers behave like SATA bridges and can support
  up to 16 devices on the other side. If a SATA port out of the IDE controller 
  is connected to a port multiplier, MaxDevices will be set to the number of SATA 
  devices that the port multiplier supports. Because today's port multipliers 
  support up to fifteen SATA devices, this number can be as large as fifteen. The IDE  
  bus driver is required to scan for the presence of port multipliers behind an SATA 
  controller and enumerate up to MaxDevices number of devices behind the port 
  multiplier.    
  
  In this context, the devices behind a port multiplier constitute a channel.  
  
  @param[in]  This         The pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in]  Channel      Zero-based channel number.
  @param[out] Enabled      TRUE if this channel is enabled.  Disabled channels 
                           are not scanned to see if any devices are present.
  @param[out] MaxDevices   The maximum number of IDE devices that the bus driver
                           can expect on this channel.  For the ATA/ATAPI 
                           specification, version 6, this number will either be 
                           one or two. For Serial ATA (SATA) configurations with a 
                           port multiplier, this number can be as large as fifteen.

  @retval EFI_SUCCESS             Information was returned without any errors.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).

**/
EFI_STATUS
EFIAPI
IdeInitGetChannelInfo (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN UINT8                              Channel,
  OUT BOOLEAN                           *Enabled,
  OUT UINT8                             *MaxDevices
  )
{
  return EFI_SUCCESS;
}

/**
  The notifications from the driver entity that it is about to enter a certain
  phase of the IDE channel enumeration process.
  
  This function can be used to notify the IDE controller driver to perform 
  specific actions, including any chipset-specific initialization, so that the 
  chipset is ready to enter the next phase. Seven notification points are defined 
  at this time. 
  
  More synchronization points may be added as required in the future.  

  @param[in] This      The pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Phase     The phase during enumeration.
  @param[in] Channel   Zero-based channel number.

  @retval EFI_SUCCESS             The notification was accepted without any errors.
  @retval EFI_UNSUPPORTED         Phase is not supported.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).
  @retval EFI_NOT_READY           This phase cannot be entered at this time; for 
                                  example, an attempt was made to enter a Phase 
                                  without having entered one or more previous 
                                  Phase.

**/
EFI_STATUS
EFIAPI
IdeInitNotifyPhase (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN EFI_IDE_CONTROLLER_ENUM_PHASE      Phase,
  IN UINT8                              Channel
  )
{
  return EFI_SUCCESS;
}

/**
  Submits the device information to the IDE controller driver.

  This function is used by the driver entity to pass detailed information about 
  a particular device to the IDE controller driver. The driver entity obtains 
  this information by issuing an ATA or ATAPI IDENTIFY_DEVICE command. IdentifyData
  is the pointer to the response data buffer. The IdentifyData buffer is owned 
  by the driver entity, and the IDE controller driver must make a local copy 
  of the entire buffer or parts of the buffer as needed. The original IdentifyData 
  buffer pointer may not be valid when
  
    - EFI_IDE_CONTROLLER_INIT_PROTOCOL.CalculateMode() or
    - EFI_IDE_CONTROLLER_INIT_PROTOCOL.DisqualifyMode() is called at a later point.
    
  The IDE controller driver may consult various fields of EFI_IDENTIFY_DATA to 
  compute the optimum mode for the device. These fields are not limited to the 
  timing information. For example, an implementation of the IDE controller driver 
  may examine the vendor and type/mode field to match known bad drives.  
  
  The driver entity may submit drive information in any order, as long as it 
  submits information for all the devices belonging to the enumeration group 
  before EFI_IDE_CONTROLLER_INIT_PROTOCOL.CalculateMode() is called for any device
  in that enumeration group. If a device is absent, EFI_IDE_CONTROLLER_INIT_PROTOCOL.SubmitData()
  should be called with IdentifyData set to NULL.  The IDE controller driver may 
  not have any other mechanism to know whether a device is present or not. Therefore, 
  setting IdentifyData to NULL does not constitute an error condition. 
  EFI_IDE_CONTROLLER_INIT_PROTOCOL.SubmitData() can be called only once for a 
  given (Channel, Device) pair.  
    
  @param[in] This           A pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel        Zero-based channel number.
  @param[in] Device         Zero-based device number on the Channel.
  @param[in] IdentifyData   The device's response to the ATA IDENTIFY_DEVICE command.

  @retval EFI_SUCCESS             The information was accepted without any errors.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).
  @retval EFI_INVALID_PARAMETER   Device is invalid.

**/
EFI_STATUS
EFIAPI
IdeInitSubmitData (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN UINT8                              Channel,
  IN UINT8                              Device,
  IN EFI_IDENTIFY_DATA                  *IdentifyData
  )
{
  return EFI_SUCCESS;
}

/**
  Disqualifies specific modes for an IDE device.

  This function allows the driver entity or other drivers (such as platform 
  drivers) to reject certain timing modes and request the IDE controller driver
  to recalculate modes. This function allows the driver entity and the IDE 
  controller driver to negotiate the timings on a per-device basis. This function 
  is useful in the case of drives that lie about their capabilities. An example 
  is when the IDE device fails to accept the timing modes that are calculated 
  by the IDE controller driver based on the response to the Identify Drive command.

  If the driver entity does not want to limit the ATA timing modes and leave that 
  decision to the IDE controller driver, it can either not call this function for 
  the given device or call this function and set the Valid flag to FALSE for all 
  modes that are listed in EFI_ATA_COLLECTIVE_MODE.
  
  The driver entity may disqualify modes for a device in any order and any number 
  of times.
  
  This function can be called multiple times to invalidate multiple modes of the 
  same type (e.g., Programmed Input/Output [PIO] modes 3 and 4). See the ATA/ATAPI 
  specification for more information on PIO modes.  
  
  For Serial ATA (SATA) controllers, this member function can be used to disqualify
  a higher transfer rate mode on a given channel. For example, a platform driver
  may inform the IDE controller driver to not use second-generation (Gen2) speeds 
  for a certain SATA drive.
  
  @param[in] This       The pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel    The zero-based channel number.
  @param[in] Device     The zero-based device number on the Channel.
  @param[in] BadModes   The modes that the device does not support and that
                        should be disqualified.

  @retval EFI_SUCCESS             The modes were accepted without any errors.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).
  @retval EFI_INVALID_PARAMETER   Device is invalid.
  @retval EFI_INVALID_PARAMETER   IdentifyData is NULL.
                                
**/
EFI_STATUS
EFIAPI
IdeInitDisqualifyMode (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN UINT8                              Channel,
  IN UINT8                              Device,
  IN EFI_ATA_COLLECTIVE_MODE            *BadModes
  )
{
  return EFI_SUCCESS;
}

/**
  Returns the information about the optimum modes for the specified IDE device.

  This function is used by the driver entity to obtain the optimum ATA modes for
  a specific device.  The IDE controller driver takes into account the following 
  while calculating the mode:
    - The IdentifyData inputs to EFI_IDE_CONTROLLER_INIT_PROTOCOL.SubmitData()
    - The BadModes inputs to EFI_IDE_CONTROLLER_INIT_PROTOCOL.DisqualifyMode()

  The driver entity is required to call EFI_IDE_CONTROLLER_INIT_PROTOCOL.SubmitData() 
  for all the devices that belong to an enumeration group before calling 
  EFI_IDE_CONTROLLER_INIT_PROTOCOL.CalculateMode() for any device in the same group.  
  
  The IDE controller driver will use controller- and possibly platform-specific 
  algorithms to arrive at SupportedModes.  The IDE controller may base its 
  decision on user preferences and other considerations as well. This function 
  may be called multiple times because the driver entity may renegotiate the mode 
  with the IDE controller driver using EFI_IDE_CONTROLLER_INIT_PROTOCOL.DisqualifyMode().
    
  The driver entity may collect timing information for various devices in any 
  order. The driver entity is responsible for making sure that all the dependencies
  are satisfied. For example, the SupportedModes information for device A that 
  was previously returned may become stale after a call to 
  EFI_IDE_CONTROLLER_INIT_PROTOCOL.DisqualifyMode() for device B.
  
  The buffer SupportedModes is allocated by the callee because the caller does 
  not necessarily know the size of the buffer. The type EFI_ATA_COLLECTIVE_MODE 
  is defined in a way that allows for future extensibility and can be of variable 
  length. This memory pool should be deallocated by the caller when it is no 
  longer necessary.  
  
  The IDE controller driver for a Serial ATA (SATA) controller can use this 
  member function to force a lower speed (first-generation [Gen1] speeds on a 
  second-generation [Gen2]-capable hardware).  The IDE controller driver can 
  also allow the driver entity to stay with the speed that has been negotiated 
  by the physical layer.
  
  @param[in]  This             The pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in]  Channel          A zero-based channel number.
  @param[in]  Device           A zero-based device number on the Channel.
  @param[out] SupportedModes   The optimum modes for the device.

  @retval EFI_SUCCESS             SupportedModes was returned.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).
  @retval EFI_INVALID_PARAMETER   Device is invalid. 
  @retval EFI_INVALID_PARAMETER   SupportedModes is NULL.
  @retval EFI_NOT_READY           Modes cannot be calculated due to a lack of 
                                  data.  This error may happen if 
                                  EFI_IDE_CONTROLLER_INIT_PROTOCOL.SubmitData() 
                                  and EFI_IDE_CONTROLLER_INIT_PROTOCOL.DisqualifyData() 
                                  were not called for at least one drive in the 
                                  same enumeration group.

**/
EFI_STATUS
EFIAPI
IdeInitCalculateMode (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN UINT8                              Channel,
  IN UINT8                              Device,
  OUT EFI_ATA_COLLECTIVE_MODE           **SupportedModes
  )
{
  /* As per ACS - 3 set Transfer mode is mandatory */ 
  /* Use default Transfer mode for now. Will add this later */
  *SupportedModes = AllocateZeroPool (sizeof (EFI_ATA_COLLECTIVE_MODE));
  if (*SupportedModes == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  return EFI_SUCCESS;
}

/**
  Commands the IDE controller driver to program the IDE controller hardware
  so that the specified device can operate at the specified mode.

  This function is used by the driver entity to instruct the IDE controller 
  driver to program the IDE controller hardware to the specified modes. This 
  function can be called only once for a particular device. For a Serial ATA 
  (SATA) Advanced Host Controller Interface (AHCI) controller, no controller-
  specific programming may be required.

  @param[in] This      Pointer to the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
  @param[in] Channel   Zero-based channel number.
  @param[in] Device    Zero-based device number on the Channel.
  @param[in] Modes     The modes to set.

  @retval EFI_SUCCESS             The command was accepted without any errors.
  @retval EFI_INVALID_PARAMETER   Channel is invalid (Channel >= ChannelCount).
  @retval EFI_INVALID_PARAMETER   Device is invalid.
  @retval EFI_NOT_READY           Modes cannot be set at this time due to lack of data.
  @retval EFI_DEVICE_ERROR        Modes cannot be set due to hardware failure.
                                  The driver entity should not use this device.

**/
EFI_STATUS
EFIAPI
IdeInitSetTiming (
  IN EFI_IDE_CONTROLLER_INIT_PROTOCOL   *This,
  IN UINT8                              Channel,
  IN UINT8                              Device,
  IN EFI_ATA_COLLECTIVE_MODE            *Modes
  )
{
  return EFI_SUCCESS;
}

#==============================================================================
# @file JtagProgrammer.dsc
# SDM670 JtagProgrammer
#
# Copyright (c) 2017 Qualcomm Technologies, Inc. All rights reserved.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = SDM670Pkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = Build/SDM670LA_Loader

!include QcomPkg/SDM670Pkg/LA/Common.dsc.inc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/Library/JtagProgrammerLib/JtagProgrammer.inf {
      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x4
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|0
   }


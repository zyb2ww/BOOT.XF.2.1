#ifndef __PMICARBCOREHWIO_H__
#define __PMICARBCOREHWIO_H__
/*
===========================================================================
*/
/**
  @file PmicArbCoreHwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    SDM670 (Warlock) [napaliq_v1.0_p3q2r100_v3_BTO]
 
  This file contains HWIO register definitions for the following modules:
    PMIC_ARB_CORE
    PMIC_ARB_CORE_REGISTERS
    PMIC_ARB_CORE_REGISTERS_OBS


  Generation parameters: 
  { u'explicit-addressing': True,
    u'filename': u'PmicArbCoreHwio.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [ u'PMIC_ARB_CORE',
                  u'PMIC_ARB_CORE_REGISTERS',
                  u'PMIC_ARB_CORE_REGISTERS_OBS'],
    u'output-offsets': True}
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/rel/boot.xf/2.1/QcomPkg/Library/SPMILib/src/platform/config/hoya/670/PmicArbCoreHwio.h#1 $
  $DateTime: 2017/09/18 09:26:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REG_BASE                                           (AOSS_BASE      + 0x01440000)
#define PMIC_ARB_CORE_REG_BASE_OFFS                                      0x01440000

#define HWIO_PMIC_ARB_HW_VERSION_ADDR(x)                                 ((x) + 0x00000000)
#define HWIO_PMIC_ARB_HW_VERSION_OFFS                                    (0x00000000)
#define HWIO_PMIC_ARB_HW_VERSION_RMSK                                    0xffffffff
#define HWIO_PMIC_ARB_HW_VERSION_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_HW_VERSION_ADDR(x), HWIO_PMIC_ARB_HW_VERSION_RMSK)
#define HWIO_PMIC_ARB_HW_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_HW_VERSION_ADDR(x), m)
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_BMSK                              0xf0000000
#define HWIO_PMIC_ARB_HW_VERSION_MAJOR_SHFT                                    0x1c
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_BMSK                               0xfff0000
#define HWIO_PMIC_ARB_HW_VERSION_MINOR_SHFT                                    0x10
#define HWIO_PMIC_ARB_HW_VERSION_STEP_BMSK                                   0xffff
#define HWIO_PMIC_ARB_HW_VERSION_STEP_SHFT                                      0x0

#define HWIO_PMIC_ARB_FEATURES_ADDR(x)                                   ((x) + 0x00000004)
#define HWIO_PMIC_ARB_FEATURES_OFFS                                      (0x00000004)
#define HWIO_PMIC_ARB_FEATURES_RMSK                                      0xffff03ff
#define HWIO_PMIC_ARB_FEATURES_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_FEATURES_ADDR(x), HWIO_PMIC_ARB_FEATURES_RMSK)
#define HWIO_PMIC_ARB_FEATURES_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_FEATURES_ADDR(x), m)
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PIC_ACC_ENABLES_BMSK            0xffc00000
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PIC_ACC_ENABLES_SHFT                  0x16
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PVC_PORTS_BMSK                    0x3f0000
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PVC_PORTS_SHFT                        0x10
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PMIC_PERIPHERALS_BMSK                0x3ff
#define HWIO_PMIC_ARB_FEATURES_NUMBER_OF_PMIC_PERIPHERALS_SHFT                  0x0

#define HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x)                                ((x) + 0x00000010)
#define HWIO_PMIC_ARB_MISC_CONFIG_OFFS                                   (0x00000010)
#define HWIO_PMIC_ARB_MISC_CONFIG_RMSK                                          0x7
#define HWIO_PMIC_ARB_MISC_CONFIG_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x), HWIO_PMIC_ARB_MISC_CONFIG_RMSK)
#define HWIO_PMIC_ARB_MISC_CONFIG_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x), m)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),v)
#define HWIO_PMIC_ARB_MISC_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_MISC_CONFIG_ADDR(x),m,v,HWIO_PMIC_ARB_MISC_CONFIG_IN(x))
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_BMSK                              0x4
#define HWIO_PMIC_ARB_MISC_CONFIG_TEST_BUS_EN_SHFT                              0x2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_BMSK                              0x2
#define HWIO_PMIC_ARB_MISC_CONFIG_CLK_GATE_EN_SHFT                              0x1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_BMSK                              0x1
#define HWIO_PMIC_ARB_MISC_CONFIG_DONE_IRQ_EN_SHFT                              0x0

#define HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n)                           ((base) + 0x00000100 + 0x4 * (n))
#define HWIO_PMIC_ARB_PRIORITIESn_OFFS(base,n)                           (0x00000100 + 0x4 * (n))
#define HWIO_PMIC_ARB_PRIORITIESn_RMSK                                          0xf
#define HWIO_PMIC_ARB_PRIORITIESn_MAXn                                            9
#define HWIO_PMIC_ARB_PRIORITIESn_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n), HWIO_PMIC_ARB_PRIORITIESn_RMSK)
#define HWIO_PMIC_ARB_PRIORITIESn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PRIORITIESn_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n),val)
#define HWIO_PMIC_ARB_PRIORITIESn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PRIORITIESn_ADDR(base,n),mask,val,HWIO_PMIC_ARB_PRIORITIESn_INI(base,n))
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_PRIORITY_BMSK                            0xf
#define HWIO_PMIC_ARB_PRIORITIESn_PORT_PRIORITY_SHFT                            0x0

#define HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x)                               ((x) + 0x00000200)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OFFS                                  (0x00000200)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_RMSK                                         0x1
#define HWIO_PMIC_ARB_PVC_INTF_CTL_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x), HWIO_PMIC_ARB_PVC_INTF_CTL_RMSK)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x), m)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x),v)
#define HWIO_PMIC_ARB_PVC_INTF_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVC_INTF_CTL_ADDR(x),m,v,HWIO_PMIC_ARB_PVC_INTF_CTL_IN(x))
#define HWIO_PMIC_ARB_PVC_INTF_CTL_PVC_INTF_EN_BMSK                             0x1
#define HWIO_PMIC_ARB_PVC_INTF_CTL_PVC_INTF_EN_SHFT                             0x0

#define HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x)                            ((x) + 0x00000204)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_OFFS                               (0x00000204)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_RMSK                                      0x1
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x), HWIO_PMIC_ARB_PVC_INTF_STATUS_RMSK)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_PVC_INTF_STATUS_ADDR(x), m)
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_PVC_INTF_BUSY_BMSK                        0x1
#define HWIO_PMIC_ARB_PVC_INTF_STATUS_PVC_INTF_BUSY_SHFT                        0x0

#define HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n)                         ((base) + 0x00000208 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OFFS(base,n)                         (0x00000208 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_RMSK                                        0x3
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_MAXn                                          6
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n), HWIO_PMIC_ARB_PVC_PORTn_CTL_RMSK)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n),val)
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVC_PORTn_CTL_ADDR(base,n),mask,val,HWIO_PMIC_ARB_PVC_PORTn_CTL_INI(base,n))
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_SPMI_PRIORITY_BMSK                          0x2
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_SPMI_PRIORITY_SHFT                          0x1
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_PVC_PORT_EN_BMSK                            0x1
#define HWIO_PMIC_ARB_PVC_PORTn_CTL_PVC_PORT_EN_SHFT                            0x0

#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n)                      ((base) + 0x00000288 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_OFFS(base,n)                      (0x00000288 + 0x4 * (n))
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_RMSK                                     0x3
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_MAXn                                       6
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n), HWIO_PMIC_ARB_PVC_PORTn_STATUS_RMSK)
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVC_PORTn_STATUS_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_FAILURE_BMSK                    0x2
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_FAILURE_SHFT                    0x1
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_BUSY_BMSK                       0x1
#define HWIO_PMIC_ARB_PVC_PORTn_STATUS_PVC_PORT_BUSY_SHFT                       0x0

#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m)                          ((base) + 0x00000400 + 0x20 * (n) + 0x4 * (m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_OFFS(base,n,m)                          (0x00000400 + 0x20 * (n) + 0x4 * (m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_RMSK                                       0xfffff
#define HWIO_PMIC_ARB_PVCn_ADDRm_MAXn                                             6
#define HWIO_PMIC_ARB_PVCn_ADDRm_MAXm                                             3
#define HWIO_PMIC_ARB_PVCn_ADDRm_INI2(base,n,m)        \
        in_dword_masked(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m), HWIO_PMIC_ARB_PVCn_ADDRm_RMSK)
#define HWIO_PMIC_ARB_PVCn_ADDRm_INMI2(base,n,m,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m), mask)
#define HWIO_PMIC_ARB_PVCn_ADDRm_OUTI2(base,n,m,val)    \
        out_dword(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m),val)
#define HWIO_PMIC_ARB_PVCn_ADDRm_OUTMI2(base,n,m,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_PVCn_ADDRm_ADDR(base,n,m),mask,val,HWIO_PMIC_ARB_PVCn_ADDRm_INI2(base,n,m))
#define HWIO_PMIC_ARB_PVCn_ADDRm_SID_BMSK                                   0xf0000
#define HWIO_PMIC_ARB_PVCn_ADDRm_SID_SHFT                                      0x10
#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDRESS_BMSK                                0xffff
#define HWIO_PMIC_ARB_PVCn_ADDRm_ADDRESS_SHFT                                   0x0

#define HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p)                             ((base) + 0x00000900 + 0x4 * (p))
#define HWIO_PMIC_ARB_REG_ADDRp_OFFS(base,p)                             (0x00000900 + 0x4 * (p))
#define HWIO_PMIC_ARB_REG_ADDRp_RMSK                                      0x10fff00
#define HWIO_PMIC_ARB_REG_ADDRp_MAXp                                            511
#define HWIO_PMIC_ARB_REG_ADDRp_INI(base,p)        \
        in_dword_masked(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p), HWIO_PMIC_ARB_REG_ADDRp_RMSK)
#define HWIO_PMIC_ARB_REG_ADDRp_INMI(base,p,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p), mask)
#define HWIO_PMIC_ARB_REG_ADDRp_OUTI(base,p,val)    \
        out_dword(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p),val)
#define HWIO_PMIC_ARB_REG_ADDRp_OUTMI(base,p,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_REG_ADDRp_ADDR(base,p),mask,val,HWIO_PMIC_ARB_REG_ADDRp_INI(base,p))
#define HWIO_PMIC_ARB_REG_ADDRp_IRQ_OWN_BMSK                              0x1000000
#define HWIO_PMIC_ARB_REG_ADDRp_IRQ_OWN_SHFT                                   0x18
#define HWIO_PMIC_ARB_REG_ADDRp_SID_BMSK                                    0xf0000
#define HWIO_PMIC_ARB_REG_ADDRp_SID_SHFT                                       0x10
#define HWIO_PMIC_ARB_REG_ADDRp_ADDRESS_BMSK                                 0xff00
#define HWIO_PMIC_ARB_REG_ADDRp_ADDRESS_SHFT                                    0x8

#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x)                             ((x) + 0x00002200)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OFFS                                (0x00002200)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_RMSK                                       0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x), HWIO_PMIC_ARB_VRM_S_INTF_CTL_RMSK)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x), m)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x),v)
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_VRM_S_INTF_CTL_ADDR(x),m,v,HWIO_PMIC_ARB_VRM_S_INTF_CTL_IN(x))
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_VRM_S_INTF_EN_BMSK                         0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_CTL_VRM_S_INTF_EN_SHFT                         0x0

#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_ADDR(x)                          ((x) + 0x00002204)
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_OFFS                             (0x00002204)
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_RMSK                                    0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_INTF_STATUS_ADDR(x), HWIO_PMIC_ARB_VRM_S_INTF_STATUS_RMSK)
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_INTF_STATUS_ADDR(x), m)
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_VRM_S_INTF_BUSY_BMSK                    0x1
#define HWIO_PMIC_ARB_VRM_S_INTF_STATUS_VRM_S_INTF_BUSY_SHFT                    0x0

#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_ADDR(x)                             ((x) + 0x00002208)
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_OFFS                                (0x00002208)
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_RMSK                                       0x3
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_PORT_CTL_ADDR(x), HWIO_PMIC_ARB_VRM_S_PORT_CTL_RMSK)
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_PORT_CTL_ADDR(x), m)
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_OUT(x, v)      \
        out_dword(HWIO_PMIC_ARB_VRM_S_PORT_CTL_ADDR(x),v)
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMIC_ARB_VRM_S_PORT_CTL_ADDR(x),m,v,HWIO_PMIC_ARB_VRM_S_PORT_CTL_IN(x))
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_SPMI_PRIORITY_BMSK                         0x2
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_SPMI_PRIORITY_SHFT                         0x1
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_VRM_S_PORT_EN_BMSK                         0x1
#define HWIO_PMIC_ARB_VRM_S_PORT_CTL_VRM_S_PORT_EN_SHFT                         0x0

#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_ADDR(x)                          ((x) + 0x0000220c)
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_OFFS                             (0x0000220c)
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_RMSK                                    0x3
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_IN(x)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_PORT_STATUS_ADDR(x), HWIO_PMIC_ARB_VRM_S_PORT_STATUS_RMSK)
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_PORT_STATUS_ADDR(x), m)
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_VRM_S_PORT_FAILURE_BMSK                 0x2
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_VRM_S_PORT_FAILURE_SHFT                 0x1
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_VRM_S_PORT_BUSY_BMSK                    0x1
#define HWIO_PMIC_ARB_VRM_S_PORT_STATUS_VRM_S_PORT_BUSY_SHFT                    0x0

#define HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w)                           ((base) + 0x00002300 + 0x4 * (w))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OFFS(base,w)                           (0x00002300 + 0x4 * (w))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_RMSK                                      0xfff00
#define HWIO_PMIC_ARB_VRM_S_ADDRw_MAXw                                          255
#define HWIO_PMIC_ARB_VRM_S_ADDRw_INI(base,w)        \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w), HWIO_PMIC_ARB_VRM_S_ADDRw_RMSK)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_INMI(base,w,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w), mask)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OUTI(base,w,val)    \
        out_dword(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w),val)
#define HWIO_PMIC_ARB_VRM_S_ADDRw_OUTMI(base,w,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_VRM_S_ADDRw_ADDR(base,w),mask,val,HWIO_PMIC_ARB_VRM_S_ADDRw_INI(base,w))
#define HWIO_PMIC_ARB_VRM_S_ADDRw_SID_BMSK                                  0xf0000
#define HWIO_PMIC_ARB_VRM_S_ADDRw_SID_SHFT                                     0x10
#define HWIO_PMIC_ARB_VRM_S_ADDRw_PPID_BMSK                                  0xff00
#define HWIO_PMIC_ARB_VRM_S_ADDRw_PPID_SHFT                                     0x8

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_REG_BASE                                               (AOSS_BASE      + 0x01600000)
#define PMIC_ARB_CORE_REGISTERS_REG_BASE_OFFS                                          0x01600000

#define HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n)                                           ((base) + 0x00000000 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_CMD_OFFS(base,n)                                           (0x00000000 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_CMD_RMSK                                                   0xfc000ff7
#define HWIO_PMIC_ARB_CHNLn_CMD_MAXn                                                          511
#define HWIO_PMIC_ARB_CHNLn_CMD_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARB_CHNLn_CMD_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_CMD_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_CMD_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_CMD_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_CMD_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_CMD_OPCODE_BMSK                                            0xf8000000
#define HWIO_PMIC_ARB_CHNLn_CMD_OPCODE_SHFT                                                  0x1b
#define HWIO_PMIC_ARB_CHNLn_CMD_PRIORITY_BMSK                                           0x4000000
#define HWIO_PMIC_ARB_CHNLn_CMD_PRIORITY_SHFT                                                0x1a
#define HWIO_PMIC_ARB_CHNLn_CMD_ADDRESS_OFFSET_BMSK                                         0xff0
#define HWIO_PMIC_ARB_CHNLn_CMD_ADDRESS_OFFSET_SHFT                                           0x4
#define HWIO_PMIC_ARB_CHNLn_CMD_BYTE_CNT_BMSK                                                 0x7
#define HWIO_PMIC_ARB_CHNLn_CMD_BYTE_CNT_SHFT                                                 0x0

#define HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n)                                        ((base) + 0x00000004 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OFFS(base,n)                                        (0x00000004 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_RMSK                                                       0x1
#define HWIO_PMIC_ARB_CHNLn_CONFIG_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_CONFIG_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_CONFIG_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_CONFIG_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_CONFIG_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_CONFIG_IRQ_EN_BMSK                                                0x1
#define HWIO_PMIC_ARB_CHNLn_CONFIG_IRQ_EN_SHFT                                                0x0

#define HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n)                                        ((base) + 0x00000008 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_STATUS_OFFS(base,n)                                        (0x00000008 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_STATUS_RMSK                                                       0xf
#define HWIO_PMIC_ARB_CHNLn_STATUS_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_STATUS_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARB_CHNLn_STATUS_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_STATUS_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_STATUS_DROPPED_BMSK                                               0x8
#define HWIO_PMIC_ARB_CHNLn_STATUS_DROPPED_SHFT                                               0x3
#define HWIO_PMIC_ARB_CHNLn_STATUS_DENIED_BMSK                                                0x4
#define HWIO_PMIC_ARB_CHNLn_STATUS_DENIED_SHFT                                                0x2
#define HWIO_PMIC_ARB_CHNLn_STATUS_FAILURE_BMSK                                               0x2
#define HWIO_PMIC_ARB_CHNLn_STATUS_FAILURE_SHFT                                               0x1
#define HWIO_PMIC_ARB_CHNLn_STATUS_DONE_BMSK                                                  0x1
#define HWIO_PMIC_ARB_CHNLn_STATUS_DONE_SHFT                                                  0x0

#define HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n)                                        ((base) + 0x00000010 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OFFS(base,n)                                        (0x00000010 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA0_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_WDATA0_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_WDATA0_RMSK)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_WDATA0_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_WDATA0_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_WDATA0_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA0_DATA_SHFT                                                  0x0

#define HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n)                                        ((base) + 0x00000014 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OFFS(base,n)                                        (0x00000014 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA1_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_WDATA1_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_WDATA1_RMSK)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OUTI(base,n,val)    \
        out_dword(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n),val)
#define HWIO_PMIC_ARB_CHNLn_WDATA1_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR(base,n),mask,val,HWIO_PMIC_ARB_CHNLn_WDATA1_INI(base,n))
#define HWIO_PMIC_ARB_CHNLn_WDATA1_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_WDATA1_DATA_SHFT                                                  0x0

#define HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n)                                        ((base) + 0x00000018 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA0_OFFS(base,n)                                        (0x00000018 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA0_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA0_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_RDATA0_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA0_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA0_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA0_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA0_DATA_SHFT                                                  0x0

#define HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n)                                        ((base) + 0x0000001c + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA1_OFFS(base,n)                                        (0x0000001c + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA1_RMSK                                                0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA1_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_RDATA1_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA1_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA1_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA1_DATA_BMSK                                           0xffffffff
#define HWIO_PMIC_ARB_CHNLn_RDATA1_DATA_SHFT                                                  0x0

#define HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n)                                        ((base) + 0x00000020 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA2_OFFS(base,n)                                        (0x00000020 + 0x10000 * (n))
#define HWIO_PMIC_ARB_CHNLn_RDATA2_RMSK                                                    0xffff
#define HWIO_PMIC_ARB_CHNLn_RDATA2_MAXn                                                       511
#define HWIO_PMIC_ARB_CHNLn_RDATA2_INI(base,n)        \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n), HWIO_PMIC_ARB_CHNLn_RDATA2_RMSK)
#define HWIO_PMIC_ARB_CHNLn_RDATA2_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_CHNLn_RDATA2_ADDR(base,n), mask)
#define HWIO_PMIC_ARB_CHNLn_RDATA2_DATA_BMSK                                               0xffff
#define HWIO_PMIC_ARB_CHNLn_RDATA2_DATA_SHFT                                                  0x0

#define HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n)                                         ((base) + 0x00000100 + 0x10000 * (n))
#define HWIO_SPMI_PIC_ACC_ENABLEn_OFFS(base,n)                                         (0x00000100 + 0x10000 * (n))
#define HWIO_SPMI_PIC_ACC_ENABLEn_RMSK                                                        0x1
#define HWIO_SPMI_PIC_ACC_ENABLEn_MAXn                                                        511
#define HWIO_SPMI_PIC_ACC_ENABLEn_INI(base,n)        \
        in_dword_masked(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n), HWIO_SPMI_PIC_ACC_ENABLEn_RMSK)
#define HWIO_SPMI_PIC_ACC_ENABLEn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n), mask)
#define HWIO_SPMI_PIC_ACC_ENABLEn_OUTI(base,n,val)    \
        out_dword(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n),val)
#define HWIO_SPMI_PIC_ACC_ENABLEn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_SPMI_PIC_ACC_ENABLEn_ADDR(base,n),mask,val,HWIO_SPMI_PIC_ACC_ENABLEn_INI(base,n))
#define HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE_BMSK                                         0x1
#define HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE_SHFT                                         0x0

#define HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n)                                         ((base) + 0x00000104 + 0x10000 * (n))
#define HWIO_SPMI_PIC_IRQ_STATUSn_OFFS(base,n)                                         (0x00000104 + 0x10000 * (n))
#define HWIO_SPMI_PIC_IRQ_STATUSn_RMSK                                                       0xff
#define HWIO_SPMI_PIC_IRQ_STATUSn_MAXn                                                        511
#define HWIO_SPMI_PIC_IRQ_STATUSn_INI(base,n)        \
        in_dword_masked(HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n), HWIO_SPMI_PIC_IRQ_STATUSn_RMSK)
#define HWIO_SPMI_PIC_IRQ_STATUSn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SPMI_PIC_IRQ_STATUSn_ADDR(base,n), mask)
#define HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS_BMSK                                            0xff
#define HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS_SHFT                                             0x0

#define HWIO_SPMI_PIC_IRQ_CLEARn_ADDR(base,n)                                          ((base) + 0x00000108 + 0x10000 * (n))
#define HWIO_SPMI_PIC_IRQ_CLEARn_OFFS(base,n)                                          (0x00000108 + 0x10000 * (n))
#define HWIO_SPMI_PIC_IRQ_CLEARn_RMSK                                                        0xff
#define HWIO_SPMI_PIC_IRQ_CLEARn_MAXn                                                         511
#define HWIO_SPMI_PIC_IRQ_CLEARn_OUTI(base,n,val)    \
        out_dword(HWIO_SPMI_PIC_IRQ_CLEARn_ADDR(base,n),val)
#define HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR_BMSK                                              0xff
#define HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR_SHFT                                               0x0

#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n)                                  ((base) + 0x0000010c + 0x10000 * (n))
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_OFFS(base,n)                                  (0x0000010c + 0x10000 * (n))
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_RMSK                                               0xfff
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_MAXn                                                 511
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_INI(base,n)        \
        in_dword_masked(HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n), HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_RMSK)
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ADDR(base,n), mask)
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_SHFT                            0xb
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_SHFT                               0xa
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_BMSK                               0x200
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_SHFT                                 0x9
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_SHFT                                  0x8
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                 0x7
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                  0x6
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_SHFT                    0x5
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_BMSK                                  0x10
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_SHFT                                   0x4
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_SHFT                             0x3
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                    0x2
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                    0x1
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_SWCHAN_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                   0x0

/*----------------------------------------------------------------------------
 * MODULE: PMIC_ARB_CORE_REGISTERS_OBS
 *--------------------------------------------------------------------------*/

#define PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE                                             (AOSS_BASE      + 0x03600000)
#define PMIC_ARB_CORE_REGISTERS_OBS_REG_BASE_OFFS                                        0x03600000

#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n)                                      ((base) + 0x00000000 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OFFS(base,q,n)                                      (0x00000000 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK                                                0xfc000ff7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_MAXq                                                         6
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_MAXn                                                       511
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CMD_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CMD_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_BMSK                                         0xf8000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT                                               0x1b
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_BMSK                                        0x4000000
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT                                             0x1a
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_BMSK                                             0xff0
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT                                               0x4
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_BMSK                                              0x7
#define HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT                                              0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n)                                   ((base) + 0x00000004 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OFFS(base,q,n)                                   (0x00000004 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK                                                    0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_MAXq                                                      6
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_MAXn                                                    511
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTI2(base,q,n,val)    \
        out_dword(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),val)
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_OUTMI2(base,q,n,mask,val) \
        out_dword_masked_ns(HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_ADDR(base,q,n),mask,val,HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_INI2(base,q,n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_BMSK                                             0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_CONFIG_IRQ_EN_SHFT                                             0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n)                                   ((base) + 0x00000008 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_OFFS(base,q,n)                                   (0x00000008 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK                                                    0xf
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_MAXq                                                      6
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_MAXn                                                    511
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_BMSK                                            0x8
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DROPPED_SHFT                                            0x3
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_BMSK                                             0x4
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DENIED_SHFT                                             0x2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_BMSK                                            0x2
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_FAILURE_SHFT                                            0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_BMSK                                               0x1
#define HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE_SHFT                                               0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n)                                   ((base) + 0x00000018 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_OFFS(base,q,n)                                   (0x00000018 + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_MAXq                                                      6
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_MAXn                                                    511
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_DATA_SHFT                                               0x0

#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n)                                   ((base) + 0x0000001c + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_OFFS(base,q,n)                                   (0x0000001c + 0x10000 * (q) + 0x80 * (n))
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK                                             0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_MAXq                                                      6
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_MAXn                                                    511
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INI2(base,q,n)        \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_RMSK)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR(base,q,n), mask)
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_BMSK                                        0xffffffff
#define HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_DATA_SHFT                                               0x0

#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n)                                ((base) + 0x0000000c + 0x10000 * (q) + 0x80 * (n))
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_OFFS(base,q,n)                                (0x0000000c + 0x10000 * (q) + 0x80 * (n))
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_RMSK                                               0xfff
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MAXq                                                   6
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MAXn                                                 511
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_INI2(base,q,n)        \
        in_dword_masked(HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n), HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_RMSK)
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_INMI2(base,q,n,mask)    \
        in_dword_masked(HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ADDR(base,q,n), mask)
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_BMSK                          0x800
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_DISCONNECTED_SHFT                            0xb
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_BMSK                             0x400
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_ARBITER_CONNECTED_SHFT                               0xa
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_BMSK                               0x200
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_PERIPH_IRQ_LOST_SHFT                                 0x9
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_BMSK                                0x100
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNEXPECTED_SSC_SHFT                                  0x8
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_BMSK                0x80
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_DATA_FRAME_DETECTED_SHFT                 0x7
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_BMSK                 0x40
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_NO_RESPONSE_CMD_FRAME_DETECTED_SHFT                  0x6
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_BMSK                   0x20
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_MASTER_ARBITRATION_WIN_SHFT                    0x5
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_BMSK                                  0x10
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_FALSE_BUS_REQ_SHFT                                   0x4
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_BMSK                             0x8
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_UNSUPPORTED_COMMAND_SHFT                             0x3
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_BMSK                    0x4
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_DATA_ADDR_FRAME_PARITY_ERROR_SHFT                    0x2
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_BMSK                    0x2
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_SLAVE_CMD_FRAME_PARITY_ERROR_SHFT                    0x1
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_BMSK                   0x1
#define HWIO_OBSCHANq_PROTOCOL_IRQ_STATUSn_MASTER_CMD_FRAME_PARITY_ERROR_SHFT                   0x0


#endif /* __PMICARBCOREHWIO_H__ */

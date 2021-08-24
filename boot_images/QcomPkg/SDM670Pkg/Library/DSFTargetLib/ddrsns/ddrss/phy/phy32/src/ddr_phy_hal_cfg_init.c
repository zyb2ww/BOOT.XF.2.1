//===========================================================================
//  Copyright (c) 2017, Qualcomm Technologies Incorporated. All rights reserved.
//  QUALCOMM Proprietary and Confidential. 
//===========================================================================
////////////////////////////////////////////////////////////////////////////////////////////////

#include "ddrss.h"
#include "ddr_phy.h"

void DDR_PHY_hal_cfg_sw_handshake_complete( uint32 _inst_ )
{
    uint8 FPM_BYPASS_EN_0 = 0;
    ///  FPM bypass only handshake signals generated by FPM
    uint8 FPM_SW_HDSHAKE_EN_0 = 0;
    ///  FPM SW handshake mode
    uint8 BYPASS_COMPLETE_1 = 1;
    
    uint32 tmp;
    
    ///  COMPLETE signal in BYPASS mode for debug purposes
    ///  Enable the PHY FPM HW mode
    tmp = (0x600003 & 0xFF9F00F9)    | 
          (0x0 << 8)                 | 
          (FPM_SW_HDSHAKE_EN_0 << 2) | 
          (BYPASS_COMPLETE_1 << 21)  | 
          (FPM_BYPASS_EN_0 << 1)     | 
          (FPM_BYPASS_EN_0 << 22);
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, tmp);
    
    tmp = (0x600003 & 0xFF1F00F9)    | 
          (0x0 << 23)                | 
          (0x0 << 8)                 | 
          (FPM_SW_HDSHAKE_EN_0 << 2) | 
          (BYPASS_COMPLETE_1 << 21)  | 
          (FPM_BYPASS_EN_0 << 1)     | 
          (FPM_BYPASS_EN_0 << 22);
    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, tmp);
}


void DDR_PHY_hal_cfg_sw_handshake_stop(BOOT_DDR_STRUCT *ddr, uint32 _inst_ )
{
    uint32 fpm_period  = 0;
    uint8 fpm_period_1 = 0;
    uint8 fpm_period_2 = 0;
    uint8 fpm_period_3 = 0;
    ///  FPM Period derived from clk_freq_khz
    uint8 FPM_SW_HDSHAKE_EN_1 = 1;
    ///  Enable FPM SW handshake mode
    uint8 FPM_BYPASS_EN_0 = 0;
    ///  disable FPM bypass only handshake signals generated by FPM
    uint8 FPM_INIT_START_0 = 0;  
    uint32 tmp;
	uint32 clk_freq_khz;
    
	clk_freq_khz = ddr->shrm_ddr_ptr->misc.new_clk_in_kHz;
    ///  set FPM_INIT_START to 0
    ///  Calculate the fpm period
    fpm_period = (CONVERT_CYC_TO_PS / clk_freq_khz);	
    fpm_period_1 = fpm_period & 0xFF;
    fpm_period_2 = fpm_period >>8 & 0xF;
    fpm_period_3 = fpm_period >>12 & 0x1F;

    ///  de-assert init_start
    tmp = (0x600003 & 0xFF3F00F1) | 
          (FPM_INIT_START_0 << 3) | 
          (0x1 << 23)             | 
          (fpm_period_1 << 8)     | 
          (fpm_period_2 << 4)     |
          (fpm_period_3 << 25)    | 
          (FPM_BYPASS_EN_0 << 1)  | 
          (FPM_BYPASS_EN_0 << 22) | 
          (FPM_SW_HDSHAKE_EN_1 << 2);

    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, tmp);
    ///  1 = selects period from CSR source, 0 = select from primary input
}


void DDR_PHY_hal_cfg_sw_handshake_start(BOOT_DDR_STRUCT *ddr, uint32 _inst_ )
{
    uint32 fpm_period  = 0;
    uint8 fpm_period_1 = 0;
    uint8 fpm_period_2 = 0;
    uint8 fpm_period_3 = 0;
    ///  Enable FPM. Set 0 to disable/clock gate FPM. If set frequency switch can be done only through SW
    uint8 FPM_SW_HDSHAKE_EN_1 = 1;
    ///  Enable FPM SW handshake mode
    uint8 FPM_INIT_START_1 = 1;
    ///  set FPM_INIT_START to 1
    uint8 FPM_BYPASS_EN_0 = 0;
    ///  disable FPM bypass only handshake signals generated by FPM      
    uint32 tmp;
	uint32 clk_freq_khz;
	
    clk_freq_khz = ddr->shrm_ddr_ptr->misc.new_clk_in_kHz;
	///  FPM Period derived from clk_freq_khz
//    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_UPDATE_INTF_CFG, 0x3200);
//    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_UPDATE_INTF_CFG, 0x3000);
    ///  Do a SW frequency switch to load the FPM period into the PHY
    ///  Calculate the fpm period 
    fpm_period = (CONVERT_CYC_TO_PS / clk_freq_khz);
    fpm_period_1 = fpm_period & 0xFF;
    fpm_period_2 = fpm_period >>8 & 0xF;
    fpm_period_3 = fpm_period >>12 & 0x1F;	    

    ///  Assert init_start
    tmp = (0x600003 & 0xFF3F00F9) | 
          (0x1 << 23)             | 
          (fpm_period_1 << 8)     | 
          (fpm_period_2 << 4)     |
          (fpm_period_3 << 25)    | 
          (FPM_BYPASS_EN_0 << 1)  | 
          (FPM_BYPASS_EN_0 << 22) | 
          (FPM_SW_HDSHAKE_EN_1 << 2);    

    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, tmp);
    
    ///  1 = selects period from CSR source, 0 = select from primary input
    tmp = (0x600003 & 0xFF3F00F1) | 
          (FPM_INIT_START_1 << 3) | 
          (0x1 << 23)             | 
          (fpm_period_1 << 8)     | 
          (fpm_period_2 << 4)     |
          (fpm_period_3 << 25)    |	
          (FPM_BYPASS_EN_0 << 1)  | 
          (FPM_BYPASS_EN_0 << 22) | 
          (FPM_SW_HDSHAKE_EN_1 << 2);    

    HWIO_OUTX (_inst_, DDR_PHY_DDRPHY_FPM_CNTRL_CFG, tmp);
    ///  1 = selects period from CSR source, 0 = select from primary input
}


void DDR_PHY_hal_cfg_sw_iocal(uint32 _inst_)
{
    HWIO_OUTXF(_inst_, DDR_PHY_DDRPHY_IOCTLR_CTRL_CFG, CAL_NOW, 1);
    HWIO_OUTXF(_inst_, DDR_PHY_DDRPHY_IOCTLR_CTRL_CFG, CAL_NOW, 0);
    while(HWIO_INXF (_inst_, DDR_PHY_DDRPHY_IOCTLR_TOP_1_STA, IOCAL_DONE) == 0);
}

void DDR_PHY_hal_hpcdc_enable( BOOT_DDR_STRUCT *ddr, uint8 enable)
{
    uint8  ch = 0;
    uint8  dq = 0;
    uint8  ca = 0;
    uint32 dq0_ddr_phy_base;
    uint32 ca0_ddr_phy_base;
    uint8 num_ch           = ddr->shrm_ddr_ptr->misc.num_channel;

    // // Read the PRFS status from the first phy.
    // tmp = HWIO_INX (DDR_PHY_SS_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG); // read from the first PHY
    // tmp &= ~(0x1F << (45-32)); // mask bits 49 through 45
    
    // if(enable) 
    // {
        // // If we are enabling the HPCDC, set the PRFS appropriately 
        // tmp |= 0x16 << (45-32); // set slave_cdc_hp_en, slave_cdc_mode[0]=1, set master_cdc_hp_en
    // }
    // else 
    // {
        // // If we are disabling the HPCDC, set the registers required for that.
        // tmp |= 0x09 << (45-32); // set slave_cdc_lp_en, slave_cdc_mode[0]=0, set master_cdc_lp_en
    // }
    
   // // Enable broadcast mode for all DQ and CA PHYs on both channels
    // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),	
             // AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x1FBF);  //write to both CA and DQ
    // //HWIO_OUTXF2 (BROADCAST_BASE, DDR_PHY_DDRPHY_CMCDCMSTR_TOP_CFG, HP_EN, LP_EN, enable, ~enable);
    // //HWIO_OUTXF (BROADCAST_BASE, DDR_PHY_DDRPHY_CMCDCMSTR_TOP_CFG, HP_EN, enable);
    // HWIO_OUTX (BROADCAST_BASE, DDR_PHY_DDRPHY_FPM_PRFS_0_PWRS_1_HI_CFG, tmp);
   // // Disable broadcast mode for all DQ and CA PHYs on both channels
    // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), 
             // AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);
     // while ( HWIO_INX ((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),    
             // AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER) != 0x0);
   // Enable broadcast mode for all DQ and CA PHYs on both channels
   // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),	
   //          AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x1FBF);  //write to both CA and DQ

  for (ch=0;ch<num_ch;ch++) 
  {
    dq0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + DQ0_DDR_PHY_OFFSET;
    ca0_ddr_phy_base  = REG_OFFSET_DDR_PHY_CH(ch) + CA0_DDR_PHY_OFFSET;

    // Enable HP and LPDDR for the DQ PHYs
    for (dq=0;dq<NUM_DQ_PCH;dq++)
    {
      HWIO_OUTXF2(dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_TOP_CFG, HP_EN, LP_EN, enable, ~enable);
    //  HWIO_OUTXF (dq0_ddr_phy_base + (dq * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_PAD_CNTL_0_CFG, LPDDR, enable);
    }
   
    // HP enable for the CA PHYs
    for (ca=0;ca<NUM_CA_PCH;ca++)
    {
      HWIO_OUTXF2 (ca0_ddr_phy_base + (ca * DDR_PHY_OFFSET), DDR_PHY_DDRPHY_CMCDCMSTR_TOP_CFG, HP_EN, LP_EN, enable, ~enable);
    }
  }

   // Disable broadcast mode for all DQ and CA PHYs on both channels
   // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), 
   //         AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);
   // while ( HWIO_INX ((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),    
   //         AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER) != 0x0);
             
             
   // Enable broadcast mode for all DQ PHYs on both channels
   // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),
   //         AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x1E3C); // write to only DQs
   // HWIO_OUTXF (BROADCAST_BASE, DDR_PHY_DDRPHY_PAD_CNTL_0_CFG, LPDDR, enable);

   // Disable broadcast mode for all DQ PHYs on both channels
   // HWIO_OUTX((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET), 
   //         AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER, 0x0);
   // while ( HWIO_INX ((DDR_PHY_SS_BASE + SEQ_DDR_SS_DDRSS_AHB2PHY_SWMAN_OFFSET),    
   //         AHB2PHY_SWMAN_AHB2PHY_BROADCAST_EN_CFG_LOWER) != 0x0);			 
}

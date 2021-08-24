#ifndef __UFS_PHY__
#define __UFS_PHY__

#define HWIO_QSERDES_COM_SYS_CLK_CTRL_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007000)
#define HWIO_QSERDES_COM_PLL_VCOTAIL_EN_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007004)
#define HWIO_QSERDES_COM_PLL_CNTRL_ADDR                (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007014)
#define HWIO_QSERDES_COM_PLL_IP_SETI_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007018)
#define HWIO_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_ADDR      (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007020)
#define HWIO_QSERDES_COM_PLL_CP_SETI_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007024)
#define HWIO_QSERDES_COM_PLL_IP_SETP_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007028)
#define HWIO_QSERDES_COM_PLL_CP_SETP_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000702c)
#define HWIO_QSERDES_COM_SYSCLK_EN_SEL_ADDR            (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007038)
#define HWIO_QSERDES_COM_RES_CODE_TXBAND_ADDR          (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000703c)
#define HWIO_QSERDES_COM_RESETSM_CNTRL_ADDR            (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007040)
#define HWIO_QSERDES_COM_PLLLOCK_CMP1_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007044)
#define HWIO_QSERDES_COM_PLLLOCK_CMP2_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007048)
#define HWIO_QSERDES_COM_PLLLOCK_CMP3_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000704c)
#define HWIO_QSERDES_COM_PLLLOCK_CMP_EN_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007050)
#define HWIO_QSERDES_COM_DEC_START1_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007064)
#define HWIO_QSERDES_COM_DIV_FRAC_START1_ADDR          (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007098)
#define HWIO_QSERDES_COM_DIV_FRAC_START2_ADDR          (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000709c)
#define HWIO_QSERDES_COM_DIV_FRAC_START3_ADDR          (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070a0)
#define HWIO_QSERDES_COM_DEC_START2_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070a4)
#define HWIO_QSERDES_COM_PLL_RXTXEPCLK_EN_ADDR         (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070a8)
#define HWIO_QSERDES_COM_PLL_CRCTRL_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070ac)
#define HWIO_QSERDES_COM_PLL_CLKEPDIV_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070b0)
#define HWIO_QSERDES_COM_RESET_SM_ADDR                 (UFS_MEM_UFS_1LANE_REGS_BASE + 0x000070bc)

#define HWIO_QSERDES_RX0_CDR_CONTROL_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007600)
#define HWIO_QSERDES_RX0_RX_IQ_RXDET_EN_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007628)
#define HWIO_QSERDES_RX0_SIGDET_CNTRL_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007634)
#define HWIO_QSERDES_RX0_RX_BAND_ADDR                  (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007638)
#define HWIO_QSERDES_RX0_PWM_CNTRL1_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007680)
#define HWIO_QSERDES_RX0_PWM_CNTRL2_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007684)
#define HWIO_QSERDES_RX0_PWM_NDIV_ADDR                 (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007688)
#define HWIO_QSERDES_RX0_SIGDET_CNTRL2_ADDR            (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000768c)
#define HWIO_QSERDES_RX0_UFS_CNTRL_ADDR                (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007690)
#define HWIO_QSERDES_RX0_CDR_CONTROL_HALF_ADDR         (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007698)
#define HWIO_QSERDES_RX0_CDR_CONTROL_QUARTER_ADDR      (UFS_MEM_UFS_1LANE_REGS_BASE + 0x0000769c)

#define HWIO_QSERDES_RX1_CDR_CONTROL_ADDR              (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a00)
#define HWIO_QSERDES_RX1_RX_IQ_RXDET_EN_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a28)
#define HWIO_QSERDES_RX1_SIGDET_CNTRL_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a34)
#define HWIO_QSERDES_RX1_RX_BAND_ADDR                  (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a38)
#define HWIO_QSERDES_RX1_PWM_CNTRL1_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a80)
#define HWIO_QSERDES_RX1_PWM_CNTRL2_ADDR               (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a84)
#define HWIO_QSERDES_RX1_PWM_NDIV_ADDR                 (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a88)
#define HWIO_QSERDES_RX1_SIGDET_CNTRL2_ADDR            (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a8c) 
#define HWIO_QSERDES_RX1_UFS_CNTRL_ADDR                (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a90)
#define HWIO_QSERDES_RX1_CDR_CONTROL_HALF_ADDR         (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a98)
#define HWIO_QSERDES_RX1_CDR_CONTROL_QUARTER_ADDR      (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007a9c)

#define HWIO_UFS_PHY_PHY_START_ADDR                    (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007c00)
#define HWIO_UFS_PHY_POWER_DOWN_CONTROL_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007c04)
#define HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_MSB_ADDR (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007c08)
#define HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_LSB_ADDR (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007c0c)
#define HWIO_UFS_PHY_RX_SYM_RESYNC_CTRL_ADDR           (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007d34)
#define HWIO_UFS_PHY_MULTI_LANE_CTRL1_ADDR             (UFS_MEM_UFS_1LANE_REGS_BASE + 0x00007dc4)

#define HWIO_GE_DUT_USER_REGS_REG_BASE                 (UFS_MEM_UFS_1LANE_REGS_BASE + 0x4000 + 0x14000)         
#define HWIO_GE_DUT_RESET_REG_ADDR                     (HWIO_GE_DUT_USER_REGS_REG_BASE + 0x00000004)
#define HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR            (HWIO_GE_DUT_USER_REGS_REG_BASE + 0x00000014)
#define HWIO_GE_DUT_UFS_ICE_CTRL_REG_ADDR              (HWIO_GE_DUT_USER_REGS_REG_BASE + 0x00000028)

#endif /*__UFS_PHY__*/

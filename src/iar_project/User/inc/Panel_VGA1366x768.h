#ifndef __Panel_VGA1366x768_H
#define __Panel_VGA1366x768_H

#ifdef __cplusplus
 extern "C" {
#endif

#define Panel_HS_Width		56
#define Panel_VS_Height		6

#define Panel_HBP			64
#define Panel_Active_Width	1366	
#define Panel_HFP			14

#define Panel_VBP			28
#define Panel_Active_Height	768
#define Panel_VFP			1

#define Panel_HTotal			Panel_HS_Width+Panel_HBP+Panel_Active_Width+Panel_HFP-1
#define Panel_Vtotal			Panel_VS_Height+Panel_VBP+Panel_Active_Height+Panel_VFP-1

/* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
/* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 288 Mhz */
/* PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 288/2 = 144 Mhz */
/* LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 142/2 = 72 Mhz */

#define Panel_PLLSAI_N		288	// 192~432
#define Panel_PLLSAI_R		2	// 2~7
#define Panel_PLLSAI_DivR	2	// 2¡B4¡B8¡B16

#define Panel_HS_ActivePolarity	1	// 0:low 1:high
#define Panel_VS_ActivePolarity	1	// 0:low 1:high
#define Panel_DE_ActivePolarity	1	// 0:low 1:high
#define Panel_DotClock_Invert	1	// 0:normal 1:intert

#define DotClcok				Panel_PLLSAI_N*1000000/Panel_PLLSAI_R/Panel_PLLSAI_DivR	//Hz
#define FrameRate			DotClcok/Panel_HTotal/Panel_Vtotal	//Hz

#define Layer1_Active_Width	1366
#define Layer1_Active_Height	768

#define Layer2_Active_Width	1366
#define Layer2_Active_Height	768

#define Layer1FrameS			((uint32_t)0xC0000000)

#define Layer1FrameE			Layer1FrameS+((uint32_t)Layer1_Active_Width * Layer1_Active_Height * 4) - 1
#define Layer1BFrameS			Layer1FrameE + 1
#define Layer1BFrameE			Layer1BFrameS+((uint32_t)Layer1_Active_Width * Layer1_Active_Height * 4) - 1

#define Layer2FrameS			Layer1BFrameE + 1
#define Layer2FrameE			Layer2FrameS+((uint32_t)Layer2_Active_Width * Layer2_Active_Height * 4) -1
#define Layer2BFrameS			Layer2FrameE + 1
#define Layer2BFrameE			Layer2BFrameS+((uint32_t)Layer2_Active_Width * Layer2_Active_Height * 4) -1



#ifdef __cplusplus
}
#endif

#endif /*__Panel_VGA1366x768_H */


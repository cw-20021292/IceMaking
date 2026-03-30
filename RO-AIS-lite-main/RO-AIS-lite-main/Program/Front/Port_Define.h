/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/

#ifndef _Port_Define_H
#define _Port_Define_H

/***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#define pLED_SETTING_ICE_LOCK                P0.0
#define pLED_SETTING_ICE_FIRST               P0.1
#define pLED_AMOUNT                          P0.2
#define pLED_COLD                            P0.3
#define pLED_AMBIENT                         P0.4
#define pFND_SEG_1_1_E                       P0.5
#define pFND_SEG_1_1_D                       P0.6

#define pLED_HOT_TEMP_2                      P1.0
#define pLED_HOT_TEMP_3                      P1.1
//#define pLED_ICON_ALL_LOCK                   P1.2
#define pMAIN_TX                             P1.3
#define pMAIN_RX                             P1.4
#define pLED_ICON_SAVE                       P1.5
#define pLED_UV_STERILIZATION                P1.6
#define pFND_SEG_2_1_C                       P1.7


//#define unused                             P2.0
//#define unused                             P2.1
//#define unused                             P2.2
//#define unused                             P2.3
//#define unused                             P2.4
#define pKEY_SETTING_ECO_MODE                P2.5
#define pKEY_AMBIENT                         P2.6
#define pKEY_SETTING_COLD_TEMP               P2.7



#define pFND_SEG_1_2_G                       P3.0
#define pLED_ICON_ICE_LOCK                   P3.1

#define pKEY_WATER_EXTRACT                   P2.3
#define pKEY_ICE_EXTRACT                     P2.4
#define pLED_COLD_TEMP_1                     P4.3
#define pLED_PM	              			     P4.4
//#define pLED_WATER_EXTRACT_2                 P2.0
/*.. [24-12-23] 하드웨어 포트꼬임으로 인한 LED Port Swap ..*/
#define pLED_WATER_EXTRACT_1                 P4.7
//#define pLED_ICE_EXTRACT_2                   P2.1
#define pLED_ICE_EXTRACT_1                   P4.5

#define pFND_SEG_1_3_A                       P5.0
#define pFND_SEG_1_3_B                       P5.1
#define pFND_SEG_1_3_C                       P5.2
#define pFND_SEG_1_3_D                       P5.3
#define pFND_SEG_1_3_E                       P5.4
#define pFND_SEG_1_3_F                       P5.5
#define pFND_SEG_1_3_G                       P5.6
#define pFND_SEG_2_1_B                       P5.7

// EEPROM, RTC
//#define unused                               P6.0
//#define unused                               P6.1
#define pLED_ICON_ICE_FIRST                  P6.2
#define pLED_ICE                             P6.3
//#define unused                               P6.4
#define pLED_CONT                            P6.5
#define pLED_POT                             P6.6
#define pLED_2_CUP                           P6.7

#define pFND_SEG_1_1_C                       P7.0
#define pFND_SEG_1_1_B                       P7.1
#define pFND_SEG_1_1_A                       P7.2
#define pLED_mL                              P7.3
#define pLED_PERCENT                         P7.4
#define pLED_AUTO_DRAIN_OPERATION            P7.5
#define pLED_LOW_WATER                       P7.6
#define pLED_1_CUP                           P7.7

#define pFND_SEG_1_1_F                       P8.0
#define pFND_SEG_1_1_G                       P8.1
#define pFND_SEG_1_2_A                       P8.2
#define pFND_SEG_1_2_B                       P8.3
#define pFND_SEG_1_2_C                       P8.4
#define pFND_SEG_1_2_D                       P8.5
#define pFND_SEG_1_2_E                       P8.6
#define pFND_SEG_1_2_F                       P8.7

#define pKEY_SETTING_HOT_LOCK                P10.0
#define pLED_HOT_TEMP_1                      P10.1
#define pLED_ICON_HOT_LOCK                   P10.2

#define pLED_FAUCET_STERILIZION              P11.0
#define pLED_ICE_TANK_STERILIZION            P11.1

#define pLED_COLD_TEMP_2                     P12.0

#define pLED_HOT                             P13.0
//#define unused                             P13.7

#define pLED_COLD_TEMP_3                     P14.0
#define pLED_ICE_FULL                        P14.1
#define pLED_SETTING_MY_CUP                  P14.2
#define pLED_SETTING_COLD_OFF				 P14.3
#define pLED_SETTING_ECO_MODE                P14.4
#define pLED_SETTING_HOT_LOCK                P14.5
#define pLED_SETTING_START                   P14.6
#define pKEY_HOT                             P14.7


#define pKEY_COLD                            P15.0
#define pKEY_SETTING_MY_CUP                  P15.1
#define pKEY_AMOUNT                          P15.2
#define pKEY_SETTING_ICE_FIRST               P15.3
#define pKEY_SETTING_START                   P15.4
#define pKEY_SETTING_ICE_LOCK                P15.5
#define pKEY_ICE                             P15.6

//add
#define pLED_AM								 P4.6
#define pLED_HALF_CUP						 P4.2
#define pLED_COLON							 P4.1
#define pLED_WiFi_Blue						 P6.4
#define pLED_WiFi_White						 P1.2
#define pLED_UV_ICE_FAUCET					 P6.0
#define pUV_ON_OFF							 P7.5


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif

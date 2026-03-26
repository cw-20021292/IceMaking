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
#define UI2C_SCL                               P6.0    //(O)// EEPROM (SCL)
#define UI2C_SDA                               P6.1    //(IO)// EEPROM(SDA)

/*#define pUV_LED_ICE_TRAY_2                     P0.0*/
//#define unused                               P0.0
#define pWifi_RESET                            P0.1
#define pWIFI_TX                               P0.2
#define pWIFI_RX                               P0.3
#define pWifi_ON                               P0.4
#define pSTEP_MOTOR_RO_DRAIN_1                 P0.5
#define pVALVE_OVERHEATING_NOS                 P0.6
#define pUV_LED_WATER_TANK_1_2                 P0.7


#define pSWING_BAR                             P1.0
#define pFRONT_RX                              P1.1
#define pFRONT_TX                              P1.2
#define pBLDC_TX                               P1.3
#define pBLDC_RX                               P1.4
#define pIR_POWER                              P1.5
#define pSTEP_MOTOR_ICE_DOOR_1                 P1.6
#define pSTEP_MOTOR_ICE_DOOR_2                 P1.7

#define pAD_TEST_24V_CURRENT                   P2.0    //ANI 0
#define pAD_TEST_12V_CURRENT                   P2.1    //ANI 1
#define pAD_Drain_Pump_IAD                     P2.2    //ANI 2
#define pAD_Hot_Temp_Out                       P2.3    //ANI 3
#define pAD_Hot_Pump_IAD                       P2.4    //ANI 4
#define pAD_UV_WATER_TANK_LED_IAD              P2.5    //ANI 5
#define pAD_UV_ICE_TANK_BACK_1_2_IAD           P2.6    //ANI 6
#define pAD_UV_ICE_TRAY_1_IAD                  P2.7    //ANI 7

#define pLEVEL_ICE_DRAIN_HIGH                  P3.0
/*#define pTDS_IN_DATA                           P3.1    //intp4*/
#define pREED_ACID                             P3.2
#define pUV_LED_ICE_TANK_3_FRONT               P3.3
#define pDC_FAN                                P3.4
/*#define pAD_TDS_IN_TH                          P3.5    //ANI 23*/

#define pAD_UV_ICE_TANK_FRONT_IAD              P3.6    //ANI 22
/*#define unused                                 P3.7*/

#define p12V_POWER                             P4.1
#define pHEATER_HOT                            P4.2
#define pCOMP                                  P4.3
/*#define pMOTOR_ICE_OUT_CW                      P4.4*/
/*#define pMOTOR_ICE_OUT_CCW                     P4.5*/
#define pMOTOR_ICE_OUT_CCW                     P4.4
#define pMOTOR_ICE_OUT_CW                      P4.5

#define pMOTOR_ICE_TRAY_CCW                    P4.6
#define pMOTOR_ICE_TRAY_CW                     P4.7

#define pLEAKAGE_ON                            P5.0
#define pREED_TANK_COVER                       P5.1
#define pREED_INO_3_FILTER                     P5.2
#define pLEVEL_PURIFY_HIGH                     P5.3
#define pVALVE_ICE_TANK_STER_FEED_RIGHT        P5.4
#define pVALVE_24V_POWER                       P5.5
#define pSTEP_MOTOR_ICE_DOOR_4                 P5.6
#define pSTEP_MOTOR_ICE_DOOR_3                 P5.7

// EEPROM, RTC
#define P_I2C_SCL                              P6.0
#define P_I2C_SDA                              P6.1
/*#define pCOLD_TH_POWER                         P6.2*/
/*#define pROOM_TH_POWER                         P6.3*/
#define pROOM_TH_POWER                         P6.2
#define pCOLD_TH_POWER                         P6.3
/*#define pTDS_IN_Power                          P6.4*/
#define pPUMP_DRAIN_PWM                        P6.5
#define pPUMP_TRAY_PWM                         P6.6
//#define unused                                 P6.7

#define pVALVE_HOT_IN_FEED                     P7.0
#define pVALVE_ICE_TRAY_IN_FEED                P7.1
#define pVALVE_COLD_DRAIN                      P7.2
#define pVALVE_FEED                            P7.3
#define pVALVE_NOS                             P7.4
/*#define pVALVE_FLUSHING_FEED                   P7.5*/
#define pVALVE_FLUSHING_NOS                    P7.5
#define pVALVE_ICE_TANK_STER_FEED_LEFT         P7.6
#define pINT_TRAY_FLOW                         P7.7

#define pSTEP_MOTOR_RO_DRAIN_2                 P8.0
#define pSTEP_MOTOR_RO_DRAIN_3                 P8.1
#define pSTEP_MOTOR_RO_DRAIN_4                 P8.2
//#define unused                               P8.3
/*#define	pTDS_OUT_Power2					   P8.4*/
/*#define	pTDS_OUT_Power1					   P8.5*/
#define pICE_MICRO_SW_HIGH                     P8.6
#define pLEVEL_ICE_DRAIN_LOW                   P8.7

#define Port_VOICE_RESET                       P9.0
#define Port_VOICE_CSB                         P9.1
#define pREED_NEO_1_FILTER                     P9.2
#define pREED_RO_2_FILTER                      P9.3

/*#define pVALVE_FLUSHING_NOS                    P9.4*/
#define pVALVE_FLUSHING_FEED                   P9.4
#define Port_VOICE_clk                         P9.5
#define Port_VOICE_data                        P9.6
#define pSTEP_MOTOR_GAS_SW_1                   P9.7


//#define unused                               P10.0
//#define unused                               P10.1
#define pVALVE_HOT_OUT                         P10.2
//#define unused                               P10.3
#define pVALVE_COLD_OUT                        P10.4
#define pVALVE_ROOM_OUT                        P10.5
/*#define pPower_Drain_Level                     P10.6*/

#define pLEVEL_PURIFY_LOW                      P11.0
#define pREED_FILTER_COVER                     P11.1
#define pSTEP_MOTOR_GAS_SW_2                   P11.2
#define pSTEP_MOTOR_GAS_SW_3                   P11.3
#define pSTEP_MOTOR_GAS_SW_4                   P11.4
///#define unused                              P11.5
/*#define pAD_TDS_OUT_DATA                       P11.6   // ANI 25*/
/*#define pAD_TDS_OUT_TEMP                       P11.7   // ANI 24*/

#define pAD_AMB_SIDE_TEMP                      P12.0
//#define unused                               P12.1
//#define unused                               P12.2
//#define unused                               P12.3
//#define unused                               P12.4
//#define unused                               P12.5
//#define unused                               P12.6
//#define unused                               P12.7

#define pVALVE_AIR_VENT                        P13.0
//#define unused                               P13.7

#define pUV_LED_ICE_TANK_1_2_BACK              P14.0
#define pINT_FILTER_FLOW                       P14.1    //INTP7
#define pOPTION                                P14.2
#define pFACTORY_TEST_RX                       P14.3
#define pFACTORY_TEST_TX                       P14.4
#define pUV_LED_ICE_TRAY_1_2                   P14.5
#define pICE_MICRO_SW_LOW                      P14.6
#define pAD_FAN_IAD                            P14.7    //ANI 18

#define pAD_IR_Receive                         P15.0    //ANI 8
#define pAD_Leakage                            P15.1    //ANI 9
#define pAD_EVA_Temp_1                         P15.2    //ANI 10
#define pAD_COLD_Temp                          P15.3    //ANI 11
#define pAD_ROOM_Temp                          P15.4    //ANI 12
#define pAD_COLD_MIXING_TEMP                   P15.5    //ANI 13
#define pAD_OUT_Temp                           P15.6    //ANI 14




/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif

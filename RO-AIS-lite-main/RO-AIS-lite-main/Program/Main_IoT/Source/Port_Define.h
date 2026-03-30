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
#define UI2C_SCL                    P6.0    //(O)// EEPROM (SCL)
#define UI2C_SDA                    P6.1    //(IO)// EEPROM(SDA)

#define pIR_POWER                   P0.0
// #define pWifi_RESET                 P0.1
// #define pWIFI_TX                    P0.2
// #define pWIFI_RX                    P0.3
// #define P_WIFI_ON                    P0.4
#define pSWING_BAR                  P0.5
#define pVALVE_HOT_OUT              P0.6


#define pLEAKAGE_ON                 P1.0
#define pHERMES_RX                  P1.1
#define pHERMES_TX                  P1.2
#define pFRONT_TX                   P1.3
#define pFRONT_RX                   P1.4
#define pUV_LED_WATER_FAUCET        P1.5
//#define unused       P1.6
#define pVALVE_24V_POWER            P1.7

#define pAD_Hot_Temp_Out            P2.0    //ANI 0
#define pAD_COLD_Temp               P2.1    //ANI 1
#define pAD_ROOM_Temp               P2.2    //ANI 2
#define pAD_IR_Receive              P2.3    //ANI 3
#define pAD_OUT_Temp                P2.4    //ANI 4
#define pAD_EVA_Temp_1              P2.5    //ANI 5
#define pAD_EVA_Temp_2              P2.6    //ANI 6
#define pAD_Leakage                 P2.7    //ANI 7

//#define unused                    P3.0
//#define unused                    P3.1

#define pMOTOR_ICE_TRAY_CW          P4.1
#define pMOTOR_ICE_TRAY_CCW         P4.2
#define pMOTOR_ICE_OUT_CW           P4.3
#define pMOTOR_ICE_OUT_CCW          P4.4
#define pCOMP                       P4.5
#define pHEATER_ICE                 P4.6
#define p12V_POWER                  P4.7

#define pLEVEL_PURIFY_HIGH          P5.0
#define pLEVEL_PURIFY_LOW           P5.1
#define pLEVEL_OVERFLOW             P5.2
#define pICE_MICRO_SW_HIGH          P5.3
#define pICE_MICRO_SW_LOW           P5.4
#define pREED_TANK_COVER            P5.5
#define pUV_LED_ICE_TANK            P5.6
//#define unused                    P5.7

// EEPROM, RTC
#define P_I2C_SCL                   P6.0
#define P_I2C_SDA                   P6.1
#define pCOLD_TH_POWER              P6.2
#define pROOM_TH_POWER              P6.3
//#define unused                    P6.4
#define pBUZZER_PWM                 P6.5
#define pBUZZER_POWER               P6.6
#define pPUMP_TRAY_PWM              P6.7

//#define unused                    P7.0
#define pVALVE_FEED                 P7.1
#define pVALVE_NOS                  P7.2
#define pBOOST_PUMP_ON              P7.3
#define pOUT_PUMP_IN                P7.4
#define pLEVEL_ICE_DRAIN_HIGH       P7.5
#define pLEVEL_ICE_DRAIN_LOW        P7.6
#define pHEATER_HOT                 P7.7

#define pVALVE_ROOM_OUT             P8.0
#define pVALVE_COLD_OUT             P8.1
#define pVALVE_COLD_DRAIN           P8.2
#define pDC_FAN                     P8.3
#define pSTEP_MOTOR_ICE_DOOR_1      P8.4
#define pSTEP_MOTOR_ICE_DOOR_2      P8.5
#define pSTEP_MOTOR_ICE_DOOR_3      P8.6
#define pSTEP_MOTOR_ICE_DOOR_4      P8.7

//#define unused                    P10.0
#define pSTEP_MOTOR_GAS_SW_4        P10.1
#define pPUMP_DRAIN_PWM             P10.2    //TO06

#define pSTEP_MOTOR_GAS_SW_3        P11.0
#define pSTEP_MOTOR_GAS_SW_2        P11.1

//#define unused                    P12.0

//#define unused                    P13.0

//#define unused                    P14.0
#define pINT_FLOW                   P14.1    //INTP7
//#define unused                    P14.2
#define pFACTORY_TEST_RX            P14.3
#define pFACTORY_TEST_TX            P14.4
//#define unused                    P14.5
#define pSTEP_MOTOR_GAS_SW_1        P14.6
//#define unused                    P14.7

#define pAD_UV_2_LED_IAD            P15.0    //ANI 8
#define pAD_UV_1_LED_IAD            P15.1    //ANI 9
#define pAD_FAN_IAD                 P15.2    //ANI 10
#define pAD_PHOTO_TR                P15.3    //ANI 11
#define pAD_Hot_Pump_IAD            P15.4    //ANI 12
#define pAD_Drain_Pump_IAD          P15.5    //ANI 13
//#define unused                    P15.6    //ANI 14






#if 0
#define UI2C_SCL                    P6.0    //(O)// EEPROM (SCL)
#define UI2C_SDA                    P6.1    //(IO)// EEPROM(SDA)

//#define unused                  P0.0
#define pWifi_RESET               P0.1
#define pWIFI_TX                  P0.2
#define pWIFI_RX                  P0.3
#define pWifi_ON                  P0.4
#define pSTEP_MOTOR_GAS_SW_1      P0.5
#define pSTEP_MOTOR_GAS_SW_2      P0.6


#define pLCD_RESET                P1.0
#define pLCD_RX                   P1.1
#define pLCD_TX                   P1.2
#define pFRONT_RX                 P1.3
#define pFRONT_TX                 P1.4
#define pUV_LED_ICE_TANK          P1.5
#define pUV_LED_WATER_FAUCET              P1.6
#define pSTEP_MOTOR_ICE_DOOR_4    P1.7

#define pAD_TDS_Temp_IN           P2.0    //ANI 0
#define pAD_TDS_Temp_OUT          P2.1    //ANI 1
#define pAD_TDS_OUT               P2.2    //ANI 2
#define pAD_Drain_Pump_IAD        P2.3    //ANI 3
#define pAD_Hot_Pump_IAD          P2.4    //ANI 4
#define pAD_Hot_Temp_Out          P2.5    //ANI 5
#define pAD_EVA_Temp_1            P2.6    //ANI 6
#define pAD_EVA_Temp_2            P2.7    //ANI 7

#define pVALVE_COLD_DRAIN         P3.0
#define pRTC_FREQ_IN              P3.1

/*#define pMOTOR_ICE_TRAY_CCW       P4.1*/
/*#define pMOTOR_ICE_TRAY_CW        P4.2*/
#define pMOTOR_ICE_TRAY_CW        P4.1
#define pMOTOR_ICE_TRAY_CCW       P4.2
#define pMOTOR_ICE_OUT_CW         P4.3
#define pMOTOR_ICE_OUT_CCW        P4.4
#define pCOMP                     P4.5
#define pHEATER_ICE               P4.6
#define p12V_POWER                P4.7

#define pVALVE_ICE_TRAY_IN        P5.0
#define pSWING_BAR                P5.1
#define pDC_FAN                   P5.2
#define pVALVE_FEED               P5.3
#define pVALVE_NOS                P5.4
#define pSTEP_MOTOR_ICE_DOOR_1    P5.5
#define pSTEP_MOTOR_ICE_DOOR_2    P5.6
#define pSTEP_MOTOR_ICE_DOOR_3    P5.7

// EEPROM, RTC
#define P_I2C_SCL                 P6.0
#define P_I2C_SDA                 P6.1
#define pCOLD_TH_POWER            P6.2
#define pROOM_TH_POWER            P6.3
#define pHEATER_HOT_H_RELAY       P6.4
#define pBUZZER_PWM               P6.5
#define pBUZZER_POWER             P6.6
#define pPUMP_DRAIN_PWM           P6.7

#define pSTEP_MOTOR_GAS_SW_3      P7.0
#define pSTEP_MOTOR_GAS_SW_4      P7.1
#define pHEATER_HOT_TRIAC_L       P7.2
#define pMODEL_SELECT             P7.3
#define pTDS_OUT_Power1           P7.4
#define pINT_TDS_Data             P7.5
#define pTDS_IN_Power             P7.6
#define pINT_FLOW                 P7.7

#define pLEVEL_ICE_DRAIN_LOW      P8.0
#define pLEVEL_ICE_DRAIN_HIGH     P8.1
#define pLEVEL_OVERFLOW           P8.2
#define pVALVE_HOT_DRAIN          P8.3
#define pVALVE_HOT_OUT            P8.4
//#define pVALVE_HOT_OUT            P8.3
//#define pVALVE_HOT_DRAIN          P8.4
#define pVALVE_24V_POWER          P8.5
#define pVALVE_ROOM_OUT           P8.6
#define pVALVE_COLD_OUT           P8.7

#define pIR_POWER                 P10.0
#define pLEVEL_PURIFY_LOW         P10.1
#define pPUMP_HOT_PWM             P10.2

#define pLEVEL_PURIFY_HIGH        P11.0
/*#define pICE_MICRO_SW_LOW         P11.1*/
#define pICE_MICRO_SW_HIGH         P11.1


#define pAD_HOT_Heater_IAD        P12.0

#define pLEAKAGE_ON               P13.0

#define pREED_TANK_COVER          P14.0
//#define unused                    P14.1
//#define unused                    P14.2
#define pFACTORY_TEST_RX          P14.3
#define pFACTORY_TEST_TX          P14.4
#define pSERVICE_REED             P14.5
/*#define pICE_MICRO_SW_HIGH        P14.6*/
#define pICE_MICRO_SW_LOW         P14.6
#define pAD_HOT_HEATER_IN_TEMP    P14.7

#define pAD_IR_Receive            P15.0    //ANI 8
#define pAD_OUT_Temp              P15.1    //ANI 9
#define pAD_COLD_Temp             P15.2    //ANI 10
#define pAD_ROOM_Temp             P15.3    //ANI 11
#define pAD_Leakage               P15.4    //ANI 12
#define pAD_UV_LED_IAD            P15.5    //ANI 13
#define pAD_PHOTO_TR              P15.6    //ANI 14
#endif

















/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif

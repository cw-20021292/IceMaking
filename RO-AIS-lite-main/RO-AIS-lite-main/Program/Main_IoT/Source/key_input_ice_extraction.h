/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_ICE_EXT_
#define _KEY_INPUT_ICE_EXT_

//extern void power_saving_init(void);
extern void auto_drain_key_off_check(void);
extern void power_saving_init(void);
extern void PCB_Test_Mode_Ice_Key_Short_Input(void);
extern void BuzStep(U8 mu8Step);
extern void start_ice_lock_flick(void);
extern void start_all_lock_flick(void);
extern void start_ice_off_flick(void);
extern void stop_button_set_display( void );

extern void power_saving_init(void);

extern void SetWifiSystemStatus (E_WIFI_USER_VALUE_T mStatus, U8 mVal );



extern TYPE_BYTE          U8LedFlickerStateB;
#define            u8LedFlickerState                           U8LedFlickerStateB.byte
#define            Bit0_Ice_Lock_LED_Flick                U8LedFlickerStateB.Bit.b0
#define            Bit1_Ice_Lock_Extract_LED_Flick                U8LedFlickerStateB.Bit.b1
#define            Bit2_Hot_Water_Lock_LED_Flick                U8LedFlickerStateB.Bit.b2
#define            Bit3_All_Lock_Water_Extract_LED_Flick                U8LedFlickerStateB.Bit.b3





extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

extern TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6







extern bit F_ExtractKeySet;
extern bit F_Ice_Lock;
//extern U8 gu8ICELockLEDFlick;
extern bit F_Ice;
//extern U8 gu8IceOut;
extern bit F_IceOutCCW;
extern bit F_NightNoUseSave;
extern bit F_IceOpen;
extern U8 gu8IceOutCCWInterval;
extern bit F_NoUseSave;
extern U8 gu8IceClose;
extern U16 gu16IceOutOff;
extern bit F_DayNoUseSave;
//extern U16 gu16IceOutTest;
//extern U8 gu8ErrIceMotor;
//extern U16 gu16NoWaterOut;

extern U8 gu8_ice_lock_flick_tmr;
extern U8 gu8_ice_ext_flick_tmr;
extern bit F_FW_Version_Display_Mode;
extern bit F_All_Lock;
extern U8 gu8_all_lock_flick_tmr;
extern bit F_Extraction_LED_Display_Mode;



//extern bit F_Overflow;
extern U8 gu8_Room_Water_Level;
//extern U8 gu8ColdLEV;
//extern bit F_ServiceSet;
extern bit F_CheckIceTray;
extern bit F_IceInit;


extern bit F_auto_drain_off_check;
extern U16 gu16IceDoorCloseResetTimer;
extern U16 gu16StepMotor2;

//extern bit F_IceOn;


extern bit F_WaterOut;
extern bit F_IR;
extern bit F_LineTest;


extern bit bit_ice_out_back_state;
extern bit F_IceOn;
extern bit bit_setting_mode_start;

extern bit bit_wake_up;

extern bit bit_standby_input;
extern U8 gu8_durable_test_start;
extern U16 gu16_durable_test_step;

extern bit F_IceExtractUVSet;

extern U8 gu8_fota_start;
extern bit bit_self_test_start;


#endif

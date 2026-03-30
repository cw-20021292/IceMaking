/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_HANDLING_LONG_H_
#define _KEY_HANDLING_LONG_H_

extern void water_select_return_timer_control( U8 mu8_flag );
extern void setting_buzzer( U8 mu8_setting );
extern void BuzStep(U8 mu8Step);
extern void halt_my_cup_setting(void);
extern void start_defualt_cup_set_flick( void );
extern void start_button_set_display( U8 mu8_mode );
extern void start_time_setting_mode( U8 mu8_mode );
extern void send_wifi_each_data_control( U8 mu8_data );

extern TYPE_BYTE          U8LedFlickerStateB;
#define            u8LedFlickerState                           U8LedFlickerStateB.byte
#define            Bit0_Ice_Lock_LED_Flick                U8LedFlickerStateB.Bit.b0
#define            Bit1_Ice_Lock_Extract_LED_Flick                U8LedFlickerStateB.Bit.b1
#define            Bit2_Hot_Water_Lock_LED_Flick                U8LedFlickerStateB.Bit.b2
#define            Bit3_All_Lock_Water_Extract_LED_Flick                U8LedFlickerStateB.Bit.b3

extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2



extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2

extern TYPE_BYTE          U8TimeSettingLongKeyB;
#define            u8TimeSettingLongKey                        U8TimeSettingLongKeyB.byte
#define            Bit0_Hot_Continue                           U8TimeSettingLongKeyB.Bit.b0
#define            Bit1_Cold_Continue                          U8TimeSettingLongKeyB.Bit.b1


extern bit F_IceOutCCW;
extern U8 gu8IceClose;
extern bit F_PartIce;
extern bit F_BuzWarn;
extern bit F_IceOpen;
//extern U8 gu8IceOut;
//extern U8 gu8ErrIceMotor;
extern U8 gu8IceOutCCWInterval;


//extern U16 gu16NoWaterOut;
extern bit F_NightNoUseSave;
extern bit F_DayNoUseSave;
extern bit F_NoUseSave;
//extern U16 gu16IceOutTest;
//extern bit F_Sterilization;


//extern bit F_Service;

//extern U8 gu8ServiceStep;

//extern U16 gu16WashTime;
//extern U16 gu16Conty;
//extern U8 gu8LockLEDFlick;
//extern U8 gu8ContyCancel;
//extern bit F_ColdConty;
extern U16 gu16ExtrKeyDelay;
extern U8 gu8AltitudeStep;
//extern U16 gu16NeutralTime;
extern U8 gu8_hot_water_lock_flick_tmr;

extern bit F_WaterOut_Change_State;

extern U16 gu16_water_select_return_time;

extern bit F_ErrorSave;
extern U8 u8Memento_Buff[];

//extern U8 gu8_test_mode_timeout;
extern bit F_IceVV;
extern U16 gu16CompOffDelay;
extern bit F_IceHeater;
extern U16 gu16IceVVTime;
extern bit F_IceDoorClose;        /* ¾ÆÀÌ½º µµ¾î ´ÝÈû */

extern bit F_FW_Version_Display_Mode;
extern U8 gu8_led_version_step;
extern U16 gu16_auto_drain_start_timer_sec;
extern U16 gu16_auto_drain_start_timer_min;
extern U16 gu16_auto_drain_start_timer_hour;

extern bit F_Cold_Water_VeryLongKey_Disable;
extern bit F_Hot_Water_VeryLongKey_Disable;
//extern bit F_HardError;
extern bit F_DrainStatus;
extern bit F_Key_Very_Long_Push_State;
extern bit F_Cold_Enable;
extern U8 gu8Cup_level_Default;






extern bit F_Cody_Inspection;
extern U8 gu8_uv_depth;

extern bit F_Model_Select;
extern bit F_Model_Select_Finish;

extern U8 gu8_cold_setting_level;
extern U8 gu8_cup_led_select;
//extern U8 gu8_cup_select_time_init;
extern U8 gu8_user_led_select;
extern bit bit_date_setting_confirm;
extern bit bit_time_setting_confirm;

extern U8 gu8_memento_depth;



extern U8 gu8_product_info_depth;
extern U8 gu8Cup_level;

extern bit F_Extract_Led_OnOff;
extern bit bit_timer_expire;

extern bit F_Wifi_Tx_Condition;


extern bit F_All_Lock;
extern bit F_WaterOut;
extern bit F_Mute_Enable;
extern bit F_Hot_Enable;
extern bit F_Ice;
extern bit F_Hot_Lock;
extern bit bit_debug_mode_start;

extern LED_STEP gu8_Led_Display_Step;
extern bit F_IceOn;
extern bit F_IR;
extern bit bit_my_cup_first_display;
extern bit bit_my_cup_setting_start;
extern bit bit_my_cup_enable;
extern U8 gu8_cup_level_time_init;
extern bit F_Comp_Output;
extern bit bit_my_cup_finish_flick;

extern bit bit_time_setting_start;
extern U8 gu8_Wifi_Connect_State;

extern bit bit_self_test_start;

#endif


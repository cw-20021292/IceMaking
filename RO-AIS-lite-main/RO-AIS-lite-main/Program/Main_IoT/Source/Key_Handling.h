/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_HANDLING_H_
#define _KEY_HANDLING_H_

extern void water_select_return_timer_control( U8 mu8_flag );
extern void setting_buzzer( U8 mu8_setting );
extern void BuzStep(U8 mu8Step);
extern void start_set_flick( U8 mu8_mode );
extern void start_cold_off_flick(void);
extern void start_hot_off_flick(void);
extern void start_hot_lock_flick(void);
extern void start_all_lock_flick(void);
extern void halt_my_cup_setting(void);
extern void finish_my_cup_setting(void);
extern void calcel_comp_delay(void);
extern void start_button_set_display( U8 mu8_mode );
extern void start_ice_off_flick(void);

extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );
extern void send_wifi_each_data_control( U8 mu8_data );
void cold_water_enable_setting_job( U8 mu8_mode );

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

extern TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Eco_Set_Display                 U8SetDisplayB.Bit.b2
#define            Bit3_My_Cup_Set_Display              U8SetDisplayB.Bit.b3
#define            Bit4_My_Cup_Off_Display              U8SetDisplayB.Bit.b4



extern TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6

extern TYPE_BYTE          U8TimeSettingIndicatorLEDB;
#define            gu8_time_setting_indicator                  U8TimeSettingIndicatorLEDB.byte
#define            Bit0_Hot_Minus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b0
#define            Bit1_Cold_Plus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b1
#define            Bit2_Settings_Switch_Indicator              U8TimeSettingIndicatorLEDB.Bit.b2
#define            Bit3_Settings_3S_Finish_Indicator           U8TimeSettingIndicatorLEDB.Bit.b3



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
extern bit F_IceDoorClose;        /* ���̽� ���� ���� */

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
extern bit bit_setting_mode_start;

extern U8 gu8_cup_level_time_init;
extern U8 gu8_hot_select_time_init;


extern bit bit_setting_mode_start;
extern bit bit_my_cup_enable;
extern DEBUG_STEP gu8_fnd_debug_step;

extern U8 gu8_debug_timer;
extern bit bit_debug_mode_start;
extern LED_STEP gu8_Led_Display_Step;
extern bit bit_my_cup_setting_start;
extern bit bit_my_cup_enable;

extern U8 gu8_altitude_return_time;

extern bit bit_altitude_setting_start;

extern bit bit_memento_start;
extern U8 gu8_memento_display_num;
extern bit bit_my_cup_first_display;
extern bit bit_my_cup_finish_flick;

extern bit bit_time_setting_start;

extern bit bit_sleep_mode_enable;

extern bit bit_first_time_setting;

extern U16 gu16_water_return_wifi_time;

#endif


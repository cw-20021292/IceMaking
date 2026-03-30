/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_H_
#define _KEY_INPUT_H_






extern void key_setting_select_job(void);
extern void key_ice_select_job(void);
extern void key_hot_water_select_job(void);
extern void key_ambient_water_select_job(void);
extern void key_cold_water_select_job(void);
extern void key_amount_select_job(void);
extern void key_setting_ice_first(void);
extern void key_setting_ice_lock(void);
extern void key_setting_hot_lock(void);
extern void key_setting_auto_drain(void);
extern void key_setting_cold_temp(void);
extern void key_setting_cold_enable(void);
extern void key_setting_eco_mode(void);
extern void key_setting_my_cup(void);
extern void setting_buzzer( U8 mu8_setting );
extern void setting_mode_start(void);
extern void cold_water_enable_setting_job( U8 mu8_mode );
extern void hot_water_enable_setting_job( U8 mu8_mode);
extern void cody_inspection_select_job(void);
extern void debug_mode_select_job(void);
extern void TestUartStart(void);
extern void memento_mode_start(void);
extern void Key_Memento_Delete_Mode(void);
extern void auto_drain_key_off_check(void);
extern void diplay_test_start(void);
extern void factory_test_start(void);
extern void key_input_ice_extract(void);
extern void key_input_water_extract(void);
extern void power_saving_init(void);
extern void water_select_return_timer_control( U8 mu8_flag );
extern void Main_PBA_Test_Mode_Start(void);
extern void PCB_Test_Mode_Key_Short_Input( U16 u16key_input_value);
extern void BuzStep(U8 mu8Step);
extern void all_lock_setting_job( U8 mu8_mode );
extern void ice_on_off_setting_job(void);
extern void ice_on_setting_job(void);
extern void ice_off_setting_job(void);
extern void key_altitude_setting_job(void);
extern void memento_select_job(void);
extern void memento_delete_job(void);
extern void memento_finish_job(void);
extern void default_cup_setting_job(void);
extern void mute_setting_job(void);
extern void start_cody_takeoff_ice(void);
extern void start_ice_tray_test(void);
extern void calcel_comp_delay(void);
extern void manual_test_start(void);
extern void key_no_use_no_operation(void);
extern void stop_button_set_display( void );

#if CONFIG_TIME_SETTING
extern void key_time_setting_job(void);
extern void key_time_setting_hot_long_select_job(void);
extern void key_time_setting_cold_long_select_job(void);
#endif

extern void finish_pairing_screen(void);
extern void power_saving_init(void);


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2





extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3

extern TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Lock                     U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Eco_Mode                     U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp                    U8FrontSettingLEDB.Bit.b4
#define            Bit5_Front_Led_My_Cup                       U8FrontSettingLEDB.Bit.b5

//revised
extern TYPE_BYTE          U8TimeNWifiSettingLEDB;
#define            gu8_time_wifi_setting_led				   U8TimeNWifiSettingLEDB.byte
#define            Bit0_Time_Led_AM							   U8TimeNWifiSettingLEDB.Bit.b0
#define            Bit1_Time_Led_PM							   U8TimeNWifiSettingLEDB.Bit.b1
#define            Bit2_Time_Led_Colon						   U8TimeNWifiSettingLEDB.Bit.b2
#define            Bit3_Led_Wifi_Icon_White					   U8TimeNWifiSettingLEDB.Bit.b3
#define            Bit4_Led_Wifi_Icon_Blue					   U8TimeNWifiSettingLEDB.Bit.b4


extern TYPE_BYTE          U8ButtonSetDisplayB;
#define            u8ButtonSetDisplay                   U8ButtonSetDisplayB.byte
#define            Bit0_Hot_Button_Set_Display          U8ButtonSetDisplayB.Bit.b0
#define            Bit1_Cold_Button_Set_Display         U8ButtonSetDisplayB.Bit.b1
#define            Bit2_Ice_Button_Set_Display          U8ButtonSetDisplayB.Bit.b2
#define            Bit2_cold_Temp_Set_Display           U8ButtonSetDisplayB.Bit.b3

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
extern U16 gu16IceOutTest;
//extern bit F_Sterilization;


//extern bit F_Service;

//extern U8 gu8ServiceStep;

//extern U16 gu16WashTime;
//extern U16 gu16Conty;
//extern U8 gu8LockLEDFlick;
//extern U8 gu8ContyCancel;
//extern bit F_ColdConty;

extern bit F_Ice_Lock;
extern bit F_IceOutStop;
extern bit F_ExtractKeySet;
extern bit F_Ice;
extern bit F_IceKeySet;

extern bit F_HotOut;
extern bit F_ColdOut;
extern bit F_RoomOut;

extern bit F_All_Lock;

extern bit F_Cold_Enable;
extern bit F_Hot_Lock;
extern bit F_Hot_Enable;

extern U16 gu16_water_select_return_time;

extern U8 gu8_all_lock_flick_tmr;

//extern U8 gu8_test_mode_timeout;

extern bit F_WaterOut;
extern U8 gu8_Error_Code;
extern bit F_auto_drain_off_check;

extern bit F_Ice_Make_Priority_Setting_Mode;
extern U8 gu8_cup_level_time_init;
extern U8 gu8_hot_select_time_init;
extern bit F_Cody_Inspection;

extern U8 gu8_test_mode_timeout;

extern bit F_Model_Select;
extern bit F_Model_Select_Finish;


extern bit F_FW_Version_Display_Mode;
extern U16 gu16IceMakingADVal;

extern U8 gu8_Room_Water_Level;

extern bit F_Overflow;
extern U8 gu8_room_level;


extern bit bit_setting_mode_time_init;
extern bit bit_setting_mode_start;
extern bit bit_wake_up;
extern bit bit_my_cup_setting_start;

extern LED_STEP gu8_Led_Display_Step;
extern bit bit_memento_start;

extern bit bit_standby_input;
extern U8 gu8_durable_test_start;

extern U8 gu8_time_setting_return_time;

extern bit bit_time_setting_start;

extern bit bit_wifi_pairing_start;
extern bit bit_display_last_error;
extern U8 gu8_Wifi_Last_Error;

extern U8 gu8_wifi_ap_mode;
extern U8 gu8_ble_ap_mode;


//extern bit F_WaterOut_Change_State;
extern U16 gu16_water_return_wifi_time;
extern U8 gu8_pre_water_out_state;
extern U8 gu8_recovery_water_out_state;
extern bit F_wifi_change_time_state;

extern bit bit_self_test_start;
extern bit F_wifi_select_amount_init;

#endif


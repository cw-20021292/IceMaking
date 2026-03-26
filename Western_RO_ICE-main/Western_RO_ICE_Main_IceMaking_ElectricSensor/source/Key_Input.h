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
//extern void key_setting_extra_cold(void);
extern void key_setting_touch_lock(void);
//extern void key_setting_steam_off(void);
extern void key_manual_ice_tank_ster(void);

extern void setting_buzzer( U8 mu8_setting );





extern void setting_mode_start(void);
//extern void cold_water_enable_setting_job( U8 mu8_mode );
extern void hot_water_enable_setting_job( U8 mu8_mode);
//extern void cody_inspection_select_job(void);
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
//extern void ice_on_off_setting_job(void);
extern void ice_on_setting_job(void);
extern void ice_off_setting_job(void);
extern void key_select_touch_lock(void);
extern void key_disable_touch_lock(void);
extern void memento_select_job(void);
extern void memento_delete_job(void);
extern void memento_finish_job(void);
extern void default_cup_setting_job(void);
//extern void mute_setting_job(void);
extern void start_cody_takeoff_ice(void);
extern void start_ice_tray_test(void);
extern void calcel_comp_delay(void);
extern void stop_button_set_display( void );
extern void key_setting_eco_mode(void);
extern void finish_filter_alarm(void);
extern void cancel_filter_flushing(void);
extern void key_time_setting_job(void);
extern void key_reserve_time_setting_job(void);

extern void WifiKey ( E_WIFI_KEY_T mu8Key );
extern void forced_finish_flushing(void);

extern void key_altitude_setting_job(void);
extern void manual_test_start(void);
extern void key_change_unit(void);
//extern void hot_prepare_return_timer_init(void);
extern void key_no_use_no_operation_for_test(void);
extern void key_time_setting_hot_long_select_job(void);
extern void key_time_setting_cold_long_select_job(void);
extern void ice_disp_key_check(void);
extern void key_manual_drain(void);
extern void key_temporary_cold_off_job(void);
extern void Extract_No_Key(void);
extern void key_sound_setting_job(void);

extern void key_sound_change_job(void);
extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );
extern void play_melody_select_196( void );
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void key_change_language(void);
extern void play_voice_test_mode_151( void );
extern void finish_pairing_screen(void);
extern void key_ct_change_filter_order_job(void);
extern void key_ct_forced_flushing(void);
extern void key_recover_fast_ice_job(void);
extern void off_all_flick(void);
extern void key_acid_clean_job(void);


//


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
#define            Bit3_Front_Led_Touch_Lock                   U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Eco_Mode                     U8FrontSettingLEDB.Bit.b4



extern TYPE_BYTE          U8ButtonSetDisplayB;
#define            u8ButtonSetDisplay                   U8ButtonSetDisplayB.byte
#define            Bit0_Hot_Button_Set_Display          U8ButtonSetDisplayB.Bit.b0
#define            Bit1_Mute_Button_Set_Display         U8ButtonSetDisplayB.Bit.b1
#define            Bit2_Ice_Button_Set_Display          U8ButtonSetDisplayB.Bit.b2
#define            Bit3_Recover_Fast_Ice_Set_Display    U8ButtonSetDisplayB.Bit.b3




extern TYPE_BYTE          U8TimeSettingIndicatorLEDB;
#define            gu8_time_setting_indicator                  U8TimeSettingIndicatorLEDB.byte
#define            Bit0_Hot_Minus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b0
#define            Bit1_Cold_Plus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b1
#define            Bit2_Settings_Switch_Indicator              U8TimeSettingIndicatorLEDB.Bit.b2
#define            Bit3_Settings_3S_Finish_Indicator           U8TimeSettingIndicatorLEDB.Bit.b3

extern TYPE_BYTE          U8TimeSettingLongKeyB;
#define            u8TimeSettingLongKey                        U8TimeSettingLongKeyB.byte
#define            Bit0_Hot_Continue                           U8TimeSettingLongKeyB.Bit.b0
#define            Bit1_Cold_Continue                          U8TimeSettingLongKeyB.Bit.b1



extern TYPE_BYTE          U8FilterResetStateB;
#define            u8FilterResetState                            U8FilterResetStateB.byte
#define            Bit0_Neo_Filter_1_Reset_State                 U8FilterResetStateB.Bit.b0
#define            Bit1_Ro_Filter_2_Reset_State                  U8FilterResetStateB.Bit.b1
#define            Bit2_Ino_Filter_3_Reset_State                 U8FilterResetStateB.Bit.b2


extern TYPE_BYTE          U8PairingStepB;
#define            u8PairingStep                            U8PairingStepB.byte
#define            Bit0_Pairing_Step0_PrePare               U8PairingStepB.Bit.b0
#define            Bit1_Pairing_Step1_25_Percent            U8PairingStepB.Bit.b1
#define            Bit2_Pairing_Step2_50_Percent            U8PairingStepB.Bit.b2
#define            Bit3_Pairing_Step3_75_Percent            U8PairingStepB.Bit.b3
#define            Bit4_Pairing_Step_FINISH                 U8PairingStepB.Bit.b4
#define            Bit5_Pairing_Exit                        U8PairingStepB.Bit.b5
#define            Bit6_Pairing_Error                       U8PairingStepB.Bit.b6
#define            Bit7_Pairing_Forced_Exit                 U8PairingStepB.Bit.b7



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
/*extern U16 gu16IceOutTest;*/
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
extern bit F_Altitude;
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
extern U16 gu16ADLeakage;

extern U8 gu8_Room_Water_Level;

//extern U8 gu8_room_level;


extern bit bit_setting_mode_time_init;
extern bit bit_setting_mode_start;
extern bit bit_wake_up;
extern U16 gu16_button_set_display_timer;
extern FLUSHING_STEP gu8_flushing_mode;
extern U8 gu8_cup_level_order;

extern LED_STEP gu8_Led_Display_Step;
extern U8 gu8_filter_flushing_state;
//extern bit bit_filter_flushing_no_cancel;
extern bit bit_yes_no_popup;
extern U8 gu8_clear_block_error;
extern bit bit_time_setting_start;
extern bit bit_uv_display_finish;
extern bit bit_error_display_finish;
extern bit bit_filter_alarm_display_finish;

extern bit bit_altitude_setting_start;
extern U8 gu8_fota_start;
extern bit bit_debug_mode_start;
extern U8 gu8_child_release_timer;
extern bit F_Child_Lock;
extern U8 gu8_time_setting_return_time;
extern bit bit_ice_disp_pause;
extern U8 gu8_ice_disp_pause_timer;
extern U8 gu8_durable_test_start;
extern bit bit_memento_start;
extern U8 gu8_memento_display_num;
extern bit bit_sound_setting_start;
extern bit bit_wifi_pairing_start;
extern U8 gu8_wifi_ap_mode;
extern U8 gu8_ble_ap_mode;

extern U8 gu8_Wifi_Last_Error;
extern bit bit_display_last_error;
extern bit bit_self_test_start;
extern bit bit_ice_ster_test_debug_start;
extern U8 gu8_ice_ster_test_debug_step;
extern ICE_STER_MODE gu8_ice_ster_mode;
extern U8 gu8_melt_ice_count;
extern bit bit_ice_tank_ster_start;
extern bit bit_ct_filter_type_start;
extern bit bit_ct_flushing_standby_start;
extern bit bit_acid_clean_start;
extern U8 gu8_Wifi_Cert_State;


#endif


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
//extern void start_set_flick( U8 mu8_mode );
extern void start_cold_off_flick(void);
extern void start_hot_off_flick(void);
extern void start_hot_lock_flick(void);
extern void start_all_lock_flick(void);
extern void start_ice_tank_ster(void);
extern void stop_ice_tank_ster(void);
extern void start_button_set_display( U8 mu8_mode );
extern void send_wifi_each_data_control( U8 mu8_data );
//extern void stop_hot_preheating(void);
//extern void start_hot_preheating(void);
extern void send_wifi_water_select_data_control( U8 mu8_data );
extern void start_cooling_breath(void);
extern void stop_cooling_breath(void);
extern void play_melody_select_196( void );
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_melody_extract_complete_194( void );
extern void play_voice_setting_ice_lock_on_147( void );
extern void play_voice_setting_ice_lock_off_148( void );
extern void play_voice_setting_ice_on_149( void );
extern void play_voice_setting_ice_off_150( void );
extern void play_voice_sound_setting_voice_129( void );
extern void play_voice_sound_setting_melody_130( void );
extern void play_voice_sound_setting_mute_131( void );
extern void play_voice_all_lock_start_127( void );
extern void play_voice_setting_hot_lock_on_112( void );
extern void play_voice_setting_hot_lock_off_113( void );
extern void play_voice_cold_cooling_111( void );
extern void play_voice_hot_heating_109( void );
extern void play_voice_all_lock_select_103( void );
extern void play_voice_eco_mode_time_set_100( void );
extern void play_voice_hot_lcok_hot_select_93( void );
extern void play_voice_hot_off_hot_select_94( void );
extern void Play_Voice(U16 mu16MemoryAddress);

extern void play_voice_cold_error_7( void );
extern void play_voice_hot_error_9( void );
extern void play_voice_leakage_error_12( void );
extern void key_change_filter_type(void);
extern void play_voice_ice_off_ice_select_99( void );
extern void start_ice_off_flick(void);



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



extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3


extern TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Steam_Off_Set_Display           U8SetDisplayB.Bit.b2

extern TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6


extern TYPE_WORD          U16CupLevelSelectW;
#define            u16CupLevelSelect                          U16CupLevelSelectW.word
#define            u8CupLevelSelect_L                         U16CupLevelSelectW.byte[0]
#define            u8CupLevelSelect_H                         U16CupLevelSelectW.byte[1]
#define            Bit0_4_Oz_Select__120_ml                   U16CupLevelSelectW.Bit.b0
#define            Bit1_6_Oz_Select__175_ml                   U16CupLevelSelectW.Bit.b1
#define            Bit2_8_Oz_Select__235_ml                   U16CupLevelSelectW.Bit.b2
#define            Bit3_10_Oz_Select__295_ml                  U16CupLevelSelectW.Bit.b3
#define            Bit4_12_Oz_Select__355_ml                  U16CupLevelSelectW.Bit.b4
#define            Bit5_14_Oz_Select__415_ml                  U16CupLevelSelectW.Bit.b5
#define            Bit6_16_Oz_Select__475_ml                  U16CupLevelSelectW.Bit.b6
#define            Bit7_20_Oz_Select__590_ml                  U16CupLevelSelectW.Bit.b7
#define            Bit8_32_Oz_Select__945_ml                  U16CupLevelSelectW.Bit.b8
#define            Bit9_Continue_Select__Continue             U16CupLevelSelectW.Bit.b9


extern TYPE_BYTE          U8TimeSettingIndicatorLEDB;
#define            gu8_time_setting_indicator                  U8TimeSettingIndicatorLEDB.byte
#define            Bit0_Hot_Minus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b0
#define            Bit1_Cold_Plus_Indicator                    U8TimeSettingIndicatorLEDB.Bit.b1
#define            Bit2_Settings_Switch_Indicator              U8TimeSettingIndicatorLEDB.Bit.b2
#define            Bit3_Settings_3S_Finish_Indicator           U8TimeSettingIndicatorLEDB.Bit.b3


extern TYPE_BYTE          U8FrontNewTextLEDB;
#define            gu8_front_new_text_led                     U8FrontNewTextLEDB.byte
#define            Bit0_Front_New_Led_Ice_Making_Text         U8FrontNewTextLEDB.Bit.b0
#define            Bit1_Front_New_Led_Hot_Heating_Text        U8FrontNewTextLEDB.Bit.b1
#define            Bit2_Front_New_Led_Cold_Cooling_Text       U8FrontNewTextLEDB.Bit.b2
#define            Bit3_Front_New_Led_Low_Water_Text          U8FrontNewTextLEDB.Bit.b3
#define            Bit4_Front_New_Led_Replace_Filter_Text     U8FrontNewTextLEDB.Bit.b4
#define            Bit5_Front_New_Led_Replace_Filter_1_Num    U8FrontNewTextLEDB.Bit.b5
#define            Bit6_Front_New_Led_Replace_Filter_2_Num    U8FrontNewTextLEDB.Bit.b6
#define            Bit7_Front_New_Led_Replace_Filter_3_Num    U8FrontNewTextLEDB.Bit.b7

extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error__E45            U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error__E49                       U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error__E21                U32ControlErrorsD.Bit.b4    //E21
#define         Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use         U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Main_Water_Flow_Block_Error__E09               U32ControlErrorsD.Bit.b6    //E09
#define         Bit7_BLDC_Communication_Error__E27                  U32ControlErrorsD.Bit.b7    //E27
#define         Bit8_BLDC_Operation_Error_Current_Sensing__E81      U32ControlErrorsD.Bit.b8    //E81
#define         Bit9_BLDC_Operation_Error_Starting_Fail__E82        U32ControlErrorsD.Bit.b9    //E82
#define         Bit10_BLDC_Operation_Error_Over_Current__E83        U32ControlErrorsD.Bit.b10   //E83
#define         Bit11_BLDC_Operation_Error_Overheat__E84            U32ControlErrorsD.Bit.b11   //E84
#define         Bit12_BLDC_Operation_Error_Disconnection_Comm__E85  U32ControlErrorsD.Bit.b12   //E85
#define         Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86    U32ControlErrorsD.Bit.b13   //E86
#define         Bit14_Cold_Temp_Open_Short_Error__E44               U32ControlErrorsD.Bit.b14   //E44
#define         Bit15_Amb_Temp_Open_Short_Error__E43                U32ControlErrorsD.Bit.b15   //E43
#define         Bit16_Drain_Pump_Error__E60                         U32ControlErrorsD.Bit.b16   //E60
#define         Bit17_Tray_Micro_SW_Dual_Detect_Error__E61          U32ControlErrorsD.Bit.b17   //E61
#define         Bit18_Tray_Micro_SW_Up_Move_Error__E62              U32ControlErrorsD.Bit.b18   //E62
#define         Bit19_Tray_Micro_SW_Down_Move_Error__E63            U32ControlErrorsD.Bit.b19   //E63
#define         Bit20_Mixing_Out_Temp_Open_Short_Error__E52         U32ControlErrorsD.Bit.b20   //E52
#define         Bit21_Amb_Side_Temp_Open_Short_Error__E53           U32ControlErrorsD.Bit.b21   //E53
#define         Bit22_Tray_In_Temp_Open_Short_Error__E41_Not_Use    U32ControlErrorsD.Bit.b22   //E56
#define         Bit23_Water_Tank_1_2_UV_Error__E74                  U32ControlErrorsD.Bit.b23   //E74
#define         Bit24_Ice_Tank_1_2_Back_UV_Error__E75               U32ControlErrorsD.Bit.b24   //E75
#define         Bit25_Ice_Tray_1_2_UV_Error__E76                    U32ControlErrorsD.Bit.b25   //E76
#define         Bit26_Ice_Tank_3_Front_UV_Error__E79                U32ControlErrorsD.Bit.b26   //E79
#define         Bit27_Tds_In_Temp_Open_Short_Error__E90             U32ControlErrorsD.Bit.b27   //E90
#define         Bit28_Tds_Out_Temp_Open_Short_Error__E91            U32ControlErrorsD.Bit.b28   //E91
#define         Bit29_Tds_In_Data_Error__E92                        U32ControlErrorsD.Bit.b29   //E92
#define         Bit30_Tds_Out_Data_Error__E93                       U32ControlErrorsD.Bit.b30   //E93







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
extern U8 gu8AltitudeTime;
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

extern bit F_Model_Select;
extern bit F_Model_Select_Finish;

extern U8 gu8_cold_setting_level;
extern U8 gu8_cup_led_select;
//extern U8 gu8_cup_select_time_init;
extern U8 gu8_user_led_select;
extern bit bit_date_setting_confirm;
extern bit bit_time_setting_confirm;


extern U8 gu8Cup_level;

extern bit F_Extract_Led_OnOff;

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
extern bit bit_my_cup_enable;

extern U8 gu8_hot_setting_temperature;
//extern bit bit_steam_off;
extern U8 gu8_Room_Water_Level;
extern bit bit_hot_preheating_start;
extern U8 gu8_preheating_set_temp;
extern U8 gu8_cup_level_order;
extern U8 gu8_hot_level_order;
extern U8 gu8_hot_default_temp;

extern bit bit_time_setting_start;
extern bit bit_filter_reset_yes;
extern bit bit_filter_reset_no;
extern bit bit_periodic_ster_enable;
extern bit bit_ice_tank_ster_start;
extern bit bit_periodic_ster_first_display;

extern U8 gu8_Celcius_temp_old;
extern U8 gu8_Fahrenheit_temp_old;
extern U8 gu8_altitude_return_time;

extern bit bit_altitude_setting_start;
extern bit bit_sleep_mode_enable;
extern bit bit_first_time_setting;
extern bit F_IceInit;
extern bit F_Tank_Cover_Input;
extern U8 gu8_oF__oC_select;
extern U8 gu8_ml__oz_select;
extern U8 gu8_hot_prepare_stage;

extern bit bit_filter_cover;
extern bit bit_ro_filter_2_reed;
extern bit F_Child_Lock;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_manual_operation_count;
extern HOT_STER_OP_TEMP gu8_hot_ster_temp_mode;
extern U8 gu8_Room_Temperature_One_Degree;

extern bit bit_memento_start;
extern U8 gu8_memento_display_num;

extern bit bit_filter_all;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8InitStep;
extern U16 gu16IceMakeTime;
extern U16 gu16IceHeaterTime;
extern U8 gu8Sound_Type;
extern bit bit_sound_setting_start;
extern U8 gu8_sound_setting_return_time;
extern U8 gu8_voice_language_type;

extern bit bit_ice_ster_test_debug_start;
extern U8 gu8_ice_ster_test_debug_step;
extern bit bit_ct_filter_type_start;
extern U8 gu8_hot_spray_start_hot_temp;
extern U8 gu8_Wifi_Cert_State;
extern bit bit_bldc_operation_error_total;




#endif


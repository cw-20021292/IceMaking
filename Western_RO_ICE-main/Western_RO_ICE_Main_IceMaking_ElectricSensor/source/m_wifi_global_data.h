/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WIFI_GLOBAL_DATA_H_
#define _WIFI_GLOBAL_DATA_H_

//
//extern void get_wifi_time ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec );
//extern void initial_self_data(void);
//extern void wifi_self_test( U16 mu16_setting );
//extern void initial_each_self_data( U8 mu8_num );
//extern void start_fota(void);
extern void BuzStep(U8 mu8Step);
extern void init_wifi_elec_watt(void);
extern void get_wifi_time ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec );
extern void init_water_quantity(void);
extern void wifi_hot_lock( U16 mu16_setting );
extern void wifi_all_lock( U16 mu16_setting );
extern void wifi_child_lock( U16 mu16_setting );
extern void wifi_mute( U16 mu16_setting );
extern void wifi_ice_lock( U16 mu16_setting );
extern void wifi_hot_enable( U16 mu16_setting );
extern void wifi_altitude( U16 mu16_setting );
extern void wifi_ice_first( U16 mu16_setting );
extern void wifi_ice_enable( U16 mu16_setting );
extern void wifi_welcome_light( U16 mu16_setting );
extern void wifi_hot_default_temp( U16 mu16_setting );
extern void wifi_default_cup( U16 mu16_setting );
extern void wifi_4_oz_water_using( U16 mu16_setting );
extern void wifi_6_oz_water_using( U16 mu16_setting );
extern void wifi_8_oz_water_using( U16 mu16_setting );
extern void wifi_10_oz_water_using( U16 mu16_setting );
extern void wifi_12_oz_water_using( U16 mu16_setting );
extern void wifi_14_oz_water_using( U16 mu16_setting );
extern void wifi_16_oz_water_using( U16 mu16_setting );
extern void wifi_20_oz_water_using( U16 mu16_setting );
extern void wifi_32_oz_water_using( U16 mu16_setting );
extern void wifi_continue_water_using( U16 mu16_setting );
extern void wifi_cup_level_order( U16 mu16_setting );
extern void wifi_hot_temp_level_order( U16 mu16_setting );
extern void wifi_oF_oC_select( U16 mu16_setting );
extern void wifi_Oz_mL_select( U16 mu16_setting );
extern void wifi_period_ster_hour( U16 mu16_setting );
extern void wifi_period_ster_minute( U16 mu16_setting );
extern void wifi_sleep_mode_enable( U16 mu16_setting );
extern void wifi_sleep_start_hour( U16 mu16_setting );
extern void wifi_sleep_start_minute( U16 mu16_setting );
extern void wifi_sleep_finish_hour( U16 mu16_setting );
extern void wifi_sleep_finish_minute( U16 mu16_setting );
extern void wifi_unused_setting_time( U16 mu16_setting );
extern void start_fota(void);
extern void init_wifi_no_use_time(void);
extern void init_wifi_ice_out_time(void);
extern void wifi_voice( U16 mu16_setting );
extern void wifi_volume( U16 mu16_setting );
extern void wifi_voice_language( U16 mu16_setting );
extern void Play_Voice(U16 mu16MemoryAddress);
extern void wifi_self_test( U16 mu16_setting );
extern void initial_each_self_data( U8 mu8_num );
extern void wifi_filter_change_type( U16 mu16_setting );





extern TYPE_SELF_TEST_DATA             SELF_Test_Result_Data;
#define U16_FEED_1_1_DC_Current_PART_0000                        SELF_Test_Result_Data.word[0]
#define U16_NOS_1_2_DC_Current_PART_0001                         SELF_Test_Result_Data.word[1]
#define U16_HOT_OUT_3_3_DC_Current_PART_0002                     SELF_Test_Result_Data.word[2]
#define U16_PURE_OUT_3_2_DC_Current_PART_0003                    SELF_Test_Result_Data.word[3]
#define U16_COLD_OUT_3_1_DC_Current_PART_0004                    SELF_Test_Result_Data.word[4]
#define U16_HOT_IN_6_2_DC_Current_PART_0009                      SELF_Test_Result_Data.word[5]
#define U16_AIR_FEED_2_DC_Current_PART_000B                      SELF_Test_Result_Data.word[6]
#define U16_COLD_DRAIN_3_4_DC_Current_PART_000D                  SELF_Test_Result_Data.word[7]
#define U16_ICE_TRAY_IN_6_1_DC_Current_PART_0015                 SELF_Test_Result_Data.word[8]
#define U16_FLUSHING_FEED_8_2_DC_Current_PART_0018               SELF_Test_Result_Data.word[9]
#define U16_RO_FLUSHING_MOTOR_DC_Current_PART_0019               SELF_Test_Result_Data.word[10]
#define U16_HOT_OVERHEAT_5_3_DC_Current_PART_001A                SELF_Test_Result_Data.word[11]
#define U16_HOT_STER_LEFT_DC_Current_PART_001B                   SELF_Test_Result_Data.word[12]
#define U16_HOT_STER_RIGHT_DC_Current_PART_001C                  SELF_Test_Result_Data.word[13]
#define U16_FLUSHING_NOS_8_1_DC_Current_PART_001F                SELF_Test_Result_Data.word[14]
#define U16_COLD_FAN_DC_Furrent_PART_0204                        SELF_Test_Result_Data.word[15]
#define U16_ICE_TRAY_FLOW_SENSOR_PART_0403                       SELF_Test_Result_Data.word[16]
#define U16_RO_DRAIN_FLOW_SENSOR_PART_040C                       SELF_Test_Result_Data.word[17]
#define U16_UV_ICE_TANK_1_2_Back_DC_Current_PART_0503            SELF_Test_Result_Data.word[18]
#define U16_UV_ICE_TRAY_1_2_DC_Current_PART_0504                 SELF_Test_Result_Data.word[19]
#define U16_UV_COLD_TANK_1_2_DC_Current_PART_0505                SELF_Test_Result_Data.word[20]
#define U16_UV_ICE_TANK_3_Front_DC_Current_PART_0506             SELF_Test_Result_Data.word[21]
#define U16_SWING_BAR_DC_Current_PART_0802                       SELF_Test_Result_Data.word[22]
#define U16_ICE_DOOR_MOTOR_DC_Current_PART_0807                  SELF_Test_Result_Data.word[23]
#define U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808                SELF_Test_Result_Data.word[24]
#define U16_DRAIN_PUMP_DC_Current_PART_080A                      SELF_Test_Result_Data.word[25]
#define U16_ICE_TRAY_PUMP_DC_Current_PART_080B                   SELF_Test_Result_Data.word[26]
#define U16_ICE_FULL_SENSOR_PART_0801                            SELF_Test_Result_Data.word[27]


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







extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

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


extern TYPE_BYTE          U8TDS_ErrorB;
#define            gu8_TDS_Error                                             U8TDS_ErrorB.byte
#define            Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90         U8TDS_ErrorB.Bit.b0
#define            Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91        U8TDS_ErrorB.Bit.b1
#define            Bit2_No_Display_Tds_In_Data_Error__E92                    U8TDS_ErrorB.Bit.b2
#define            Bit3_No_Display_Tds_Out_Data_Error__E93                   U8TDS_ErrorB.Bit.b3
#define            Bit4_No_Display_Tds_In_Pollution_Error__E98               U8TDS_ErrorB.Bit.b4
#define            Bit5_No_Display_Tds_Remove_Error__E99                     U8TDS_ErrorB.Bit.b5



extern bit F_Wifi_Power;
extern bit F_Wifi_First_Paring;
extern bit F_Wifi_Fota_MODULE;
extern bit F_Wifi_Fota_MCU;

extern bit F_WaterOut;
extern U8 gu8_Error_Code;

extern bit F_Hot_Lock;
extern bit F_All_Lock;
extern bit bit_child_lock_enable;
extern bit F_Mute_Enable;
extern bit F_Ice_Lock;
extern bit F_Hot_Enable;
extern U8 gu8AltitudeStep;
extern bit bit_fast_ice_make;
extern bit F_IceOn;
extern bit F_Extract_Led_OnOff;



extern FLUSHING_STEP gu8_flushing_mode;
extern LED_STEP gu8_Led_Display_Step;

extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;

extern U16 gu16_wifi_total_watt;
extern bit F_Comp_Output;
extern U16 gu16_wifi_total_quant;
extern U8 gu8_wifi_water_send_count;
extern U8 gu8_wifi_ice_send_count;

extern bit bit_wifi_neo_filter_1_reset;
extern bit bit_wifi_ro_filter_2_reset;
extern bit bit_wifi_ino_filter_3_reset;

extern U8 gu8_cup_level_order;
extern U8 gu8_wifi_period_ster_hour;
extern U8 gu8_wifi_period_ster_minute;
extern bit bit_sleep_mode_enable;
extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;
extern U8 gu8_hot_default_temp;
extern U8 gu8Cup_level_Default;
extern U8 gu8_hot_level_order;
extern U8 gu8_oF__oC_select;
extern U8 gu8_ml__oz_select;


extern U8 gu8_hot_setting_temperature;
extern bit bit_filter_cover;
extern U8 gu8_cody_care_timer_msec;
extern U16 gu16_cody_care_timer_sec;
extern U16 gu16_silver_timer_min;
extern U8 u8FirstSilverCare;
extern bit F_Ice;
extern U32 gu32_wifi_ice_out_time;
extern bit F_Tank_Cover_Input;
extern bit bit_wifi_cold_low;
extern bit bit_wifi_first_cold_low;
extern bit bit_wifi_cold_high;
extern bit bit_wifi_first_cold_high;
extern bit bit_ice_tank_ster_start;
extern bit bit_wifi_first_ice_tank_ster;
extern bit bit_wifi_hot_heater;
extern bit bit_wifi_first_hot_heater;
extern bit bit_wifi_first_comp;
extern U16 gu16_wifi_total_usage_water;
extern bit F_IceFull;
extern bit bit_wifi_first_ice_full;
extern U8 gu8_wifi_ice_make_state;
extern bit F_drain_water_level_low;
extern bit bit_wifi_first_drain_low;
extern bit F_drain_water_level_high;
extern bit bit_wifi_first_drain_high;

extern bit bit_9_hour_no_use_start;
extern bit bit_wifi_first_no_use_save;
extern bit F_Heater_Output;

extern bit bit_wifi_comp_on_time_update;
extern U8 u8OutHot_Temp_AVG;
extern bit bit_uv_water_tank_out;
extern bit bit_wifi_first_water_tank_uv;
extern U16 gu16_wifi_filter_remain_day;
extern bit bit_uv_ice_tank_out;
extern bit bit_wifi_first_ice_tank_uv;
extern bit bit_uv_ice_tray_out;
extern bit bit_wifi_first_ice_tray_uv;

extern bit bit_wifi_heater_on_time_update;
extern U16 gu16_hot_target_reach_timer_sec;
extern U32 gu32_hot_target_reach_timer_ms;
extern bit bit_wifi_comp;
extern U16 gu16_cold_target_reach_timer_sec;
extern U32 gu32_cold_target_reach_timer_ms;

extern U32 gu32_wifi_ice_make_time;
extern U32 gu32_wifi_hot_gas_time;
extern U16 gu16_wifi_tray_in_time;
extern U16 gu16_wifi_tray_in_flow;

extern ICE_STEP gu8IceStep;
extern U8 gu8_wifi_flushing_state;
extern U16 gu16_wifi_no_use_timer_sec;
extern U16 gu16_wifi_no_use_timer_min;
extern U8 gu8_wifi_no_use_key;
extern U8 gu8_wifi_no_use_time_send;

extern FLUSHING_STEP gu8_flushing_mode;
extern POWER_SAVING_STATE gu8_smart_operation_mode;
extern bit bit_smart_first_send;
extern U8 gu8_wifi_smart_save;
extern U8 gu8_wifi_smart_unused_setting_time;


extern U8 gu8_Amb_Side_Temperature_One_Degree;
extern U8 gu8_Amb_Front_Temperature_One_Degree;

extern U8 gu8VoiceVolumeLevel;
extern U8 gu8Sound_Type;

extern bit bit_filter_all;
extern bit bit_neo_filter_1_reed;
extern bit bit_ro_filter_2_reed;
extern bit bit_ino_filter_3_reed;
extern U16 gu16_recent_tds_in_data;

extern bit bit_sleep_mode_start;
extern bit bit_wifi_first_sleep;
extern U8 gu8_voice_language_type;


extern U16 gu16_water_usage_neo_filter;
extern U16 gu16_water_usage_ro_filter;
extern U16 gu16_water_usage_ino_filter;

extern U16 gu16_neo_filter_1_remain_day;
extern U16 gu16_ro_filter_2_remain_day;
extern U16 gu16_ino_filter_3_remain_day;

extern bit bit_neo_filter_1_alarm;
extern bit bit_ro_filter_2_alarm;
extern bit bit_ino_filter_3_alarm;

extern bit bit_wifi_first_neo_alarm;
extern bit bit_wifi_first_ro_alarm;
extern bit bit_wifi_first_ino_alarm;

extern bit bit_self_test_start;
extern bit bit_self_test_stop;
extern U8 gu8_wifi_self_test_progress;
extern U8 gu8_wifi_self_test_state;
extern U8 gu8_bldc_error_code;
extern U16 gu16ADLeakage;
extern bit bit_Mixing_Out_Temp_Open_Short_Error__E52;
extern U8 gu8_Mixing_Out_Temperature_One_Degree;

//extern U8 gu8_TDS_In_Temperature_One_Degree;
extern bit bit_flushing_water_start;
extern U16 gu16_wifi_hot_target_time_min;
extern U8 gu8_filter_change_type;
extern U8 gu8Cup_level;
extern bit bit_wifi_neo_filter_1_alarm;
extern bit bit_wifi_ro_filter_2_alarm;
extern bit bit_wifi_ino_filter_3_alarm;
extern U8 gu8_wifi_ice_ster_state;
extern bit bit_ice_tray_making_enable;
extern bit bit_uv_ice_tank_front_out;
extern bit bit_wifi_first_ice_tank_front_uv;
extern bit bit_acid_reed;

//extern U16 gu16_recent_tds_out_data;
//extern U8 gu8_TDS_Out_Temperature_One_Degree;

extern bit bit_acid_clean_start;
extern U8 gu8_wifi_acid_clean_state;

extern U8 gu8_periodic_ster_count;
extern U16 gu16_periodic_ster_current_time_total;
extern U16 gu16_periodic_ster_time_total;
extern bit bit_bldc_operation_error_total;
extern bit bit_uv_fault_test_start;



#endif

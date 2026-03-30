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

extern void BuzStep(U8 mu8Step);
extern void init_wifi_elec_watt(void);
extern void get_wifi_time ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec );
extern void wifi_hot_lock( U16 mu16_setting );
extern void wifi_all_lock( U16 mu16_setting );
//extern void wifi_child_lock( U16 mu16_setting );
extern void wifi_mute( U16 mu16_setting );
extern void wifi_ice_lock( U16 mu16_setting );
extern void wifi_hot_enable( U16 mu16_setting );
extern void wifi_altitude( U16 mu16_setting );
extern void wifi_ice_first( U16 mu16_setting );
extern void wifi_ice_enable( U16 mu16_setting );
extern void wifi_default_cup( U16 mu16_setting );
extern void wifi_continue_water_using( U16 mu16_setting );
extern void wifi_sleep_mode_enable( U16 mu16_setting );
extern void wifi_sleep_start_hour( U16 mu16_setting );
extern void wifi_sleep_start_minute( U16 mu16_setting );
extern void wifi_sleep_finish_hour( U16 mu16_setting );
extern void wifi_sleep_finish_minute( U16 mu16_setting );
//extern void wifi_unused_setting_time( U16 mu16_setting );
extern void start_fota(void);
extern void init_wifi_no_use_time(void);
extern void init_wifi_ice_out_time(void);
//extern void wifi_voice( U16 mu16_setting );
//extern void wifi_volume( U16 mu16_setting );
extern void wifi_self_test( U16 mu16_setting );
extern void initial_each_self_data( U8 mu8_num );

/*.. sean [24-11-25] Wifi Data에 필요한 함수 ..*/
extern void init_water_quantity(void);
extern void wifi_welcome_light( U16 mu16_setting );
extern void wifi_cold_enable( mData );

//A1080/A1090
extern void initial_each_self_data( U8 mu8_num );

/*.. sean [24-11-25] Wifi Data에 필요한 구조체 ..*/
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

//error
extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error      U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error                 U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error          U32ControlErrorsD.Bit.b4    //E11
#define         Bit5_Hot_Heater_OverHeat_Error           U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Hot_Water_Flow_Block_Error          U32ControlErrorsD.Bit.b6    //E34
#define         Bit7_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b7    //E13
#define         Bit8_Feed_Valve_Error                    U32ControlErrorsD.Bit.b8    //E10
#define         Bit9_Room_Level_Unbalance_Error          U32ControlErrorsD.Bit.b9    //E14
#define         Bit10_Cold_Temp_Open_Short_Error         U32ControlErrorsD.Bit.b10   //E44
#define         Bit11_Amb_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b11   //E43
#define         Bit12_Drain_Pump_Error                   U32ControlErrorsD.Bit.b12   //E60
#define         Bit13_Tray_Micro_SW_Dual_Detect_Error    U32ControlErrorsD.Bit.b13   //E61
#define         Bit14_Tray_Micro_SW_Up_Move_Error        U32ControlErrorsD.Bit.b14   //E62
#define         Bit15_Tray_Micro_SW_Down_Move_Error      U32ControlErrorsD.Bit.b15   //E63
#define         Bit16_Eva_First_Temp_Open_Short_Error    U32ControlErrorsD.Bit.b16   //E63 - noerr
#define         Bit17_Eva_Second_Temp_Open_Short_Error   U32ControlErrorsD.Bit.b17   //E64 - noerr


//A1080/A1090
extern TYPE_SELF_TEST_DATA             SELF_Test_Result_Data;
#define U16_FEED_1_1_DC_Current_PART_0000                        SELF_Test_Result_Data.word[0]
#define U16_NOS_1_2_DC_Current_PART_0001                         SELF_Test_Result_Data.word[1]
#define U16_HOT_OUT_3_3_DC_Current_PART_0002                     SELF_Test_Result_Data.word[2]
#define U16_PURE_OUT_3_2_DC_Current_PART_0003                    SELF_Test_Result_Data.word[3]
#define U16_COLD_OUT_3_1_DC_Current_PART_0004                    SELF_Test_Result_Data.word[4]
#define U16_ICE_TRAY_FLOW_SENSOR_PART_0403                       SELF_Test_Result_Data.word[5]
#define U16_UV_FAUCET_DC_Current_PART_0501						 SELF_Test_Result_Data.word[6]
#define U16_UV_ICE_FAUCET_DC_Current_PART_0502					 SELF_Test_Result_Data.word[7]
#define U16_UV_ICE_TANK_DC_Current_PART_0503            		 SELF_Test_Result_Data.word[8]
#define U16_SWING_BAR_DC_Current_PART_0802                       SELF_Test_Result_Data.word[9]
#define U16_ICE_DOOR_MOTOR_DC_Current_PART_0807                  SELF_Test_Result_Data.word[10]
#define U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808                SELF_Test_Result_Data.word[11]
#define U16_DRAIN_PUMP_DC_Current_PART_080A                      SELF_Test_Result_Data.word[12]
#define U16_ICE_FULL_SENSOR_PART_0801                            SELF_Test_Result_Data.word[13]

/*.. sean [24-11-25] Wifi Data에 필요한 변수 ..*/
extern bit F_Cold_Enable;

extern bit F_Hot_Lock;
extern bit F_All_Lock;
extern bit F_Mute_Enable;
extern bit F_Ice_Lock;
extern bit F_Hot_Enable;

extern bit bit_fast_ice_make;
extern bit F_WaterOut;
extern U16 gu16_wifi_total_quant;

extern bit F_Tank_Cover_Input;
extern U8 gu8_cody_care_timer_msec;
extern U16 gu16_cody_care_timer_sec;
extern U16 gu16_silver_timer_min;
extern U8 u8FirstSilverCare;
extern bit F_Ice;
extern U32 gu32_wifi_ice_out_time;
extern U8 gu8_wifi_ice_send_count;
extern bit bit_filter_cover;
extern bit bit_self_test_start;
extern U8 gu8_wifi_self_test_state;
extern U8 gu8_wifi_self_test_progress;
extern bit F_Extract_Led_OnOff;
extern bit F_IceOn;
extern bit F_ExtractKeySet;

//extern U8 WifiSmartCheckResultData = 0;
extern bit bit_sleep_mode_enable;
extern U8 gu8Cup_level;

extern bit bit_wifi_first_hot_heater;
extern bit bit_wifi_hot_heater;
extern bit bit_wifi_heater_on_time_update;
extern U32 gu32_hot_target_reach_timer_ms;
extern U16 gu16_hot_target_reach_timer_sec;

extern bit bit_wifi_first_comp;
extern bit bit_wifi_comp;
extern bit bit_wifi_comp_on_time_update;
extern U32 gu32_cold_target_reach_timer_ms;
extern U16 gu16_cold_target_reach_timer_sec;
extern bit F_Comp_Output;

extern U8 gu8_wifi_ice_make_state;
extern ICE_STEP gu8IceStep;
extern U32 gu32_wifi_ice_make_time;
extern U32 gu32_wifi_ice_heater_time;

extern bit F_drain_water_level_low;
extern bit F_drain_water_level_high;
extern bit bit_wifi_first_drain_low;
extern bit bit_wifi_first_drain_high;

extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;

extern LED_STEP gu8_Led_Display_Step;

//sensor list
extern bit F_Heater_Output;
extern U16 gu16_wifi_total_watt;
extern U8 gu8_Room_Temperature_One_Degree;

//A1080/A1090
extern U16 gu16_wifi_hot_target_time_min;

extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;

extern bit F_Comp_Output;

extern U16 gu16_wifi_cold_target_time_min;
#endif

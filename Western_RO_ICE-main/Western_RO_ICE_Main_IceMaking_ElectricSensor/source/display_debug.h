/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_DEBUG_H_
#define _DISPLAY_DEBUG_H_

//
extern void fnd_left_out( U8 mu8_direct, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  );


extern U16 gu16CompOffDelay;
extern U8 gu8_Tray_Flow_1sec;


extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;
extern U8 gu8_Eva_Ice_Temperature_One_Degree;
extern U16 gu16ADCds;
extern U16 gu16ADIceFull;
extern U16 gu16ADLeakage;
extern ICE_STEP gu8IceStep;


extern bit F_ErrTrayMotor_DualInital;
extern bit F_Ice_Tray_Up_Move_Reset;
extern bit F_Ice_Tray_Down_Move_Reset;

extern bit F_drain_water_level_low;
extern bit F_drain_water_level_high;

extern U8 gu8_Filter_Flow_1sec;

extern U8 gu8_Mixing_Out_Temperature_One_Degree;
extern U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
extern U16 gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
extern U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current;
extern U16 gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
extern U8 gu8_bldc_opration_hz;
extern U8 gu8_bldc_target_hz;

extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Amb_Side_Temperature_One_Degree;
extern U8 gu8_Amb_Front_Temperature_One_Degree;

extern U8 gu8_Tray_Temperature_One_Degree;
extern U8 gu8_average_tray_temp;

extern U8 gu8_bldc_error_code;
extern U8 gu8_bldc_temperature;
extern U8 gu8_filter_change_type;
extern U16 gu16_reset_hour_neo_filter;
extern U16 gu16_reset_hour_ro_filter;
extern U16 gu16_reset_hour_ino_filter;

extern U16 gu16_water_usage_neo_filter;
extern U16 gu16_water_usage_ro_filter;
extern U16 gu16_water_usage_ino_filter;

extern U16 gu16_neo_filter_1_remain_day;
extern U16 gu16_ro_filter_2_remain_day;
extern U16 gu16_ino_filter_3_remain_day;
extern U8 gu8_ice_ster_drain_stop_count;
extern U8 gu8_ice_ster_low_water_stop_count;



#endif

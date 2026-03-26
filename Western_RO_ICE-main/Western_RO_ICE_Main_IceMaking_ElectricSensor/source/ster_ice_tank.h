/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _STER_ICE_TANK_H_
#define _STER_ICE_TANK_H_

//


extern void BuzStep(U8 mu8Step);
extern void up_tray_motor(void);
extern void down_tray_motor(void);
/*extern void run_init_flow(void);*/
extern void play_melody_warning_197( void );




extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3


extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3

extern TYPE_BYTE          U8TrayPumpOFFB;
#define            u8TrayPumpOFF                                   U8TrayPumpOFFB.byte
#define            Bit0_Tray_Pump_Low_Water_Off_State              U8TrayPumpOFFB.Bit.b0
#define            Bit1_Tray_Pump_Ster_Drain_Full_Off_State        U8TrayPumpOFFB.Bit.b1


#define ICE_TANK_STER__500CC              4500
#define ICE_TANK_STER_DELAY_TIME          5


#define ICE_TANK_STER_AIR_REMOVE_TIME     50


/*..hui [23-10-17오전 11:21:35] 90분..*/
/*#define ICE_MELT_FEED_MAX_TIME       54000*/
#define ICE_MELT_FEED_MAX_TIME            72000



/*#define ICE_MELT_TOTAL_TIME                    700*/
/*#define ICE_MELT_TOTAL_TIME                    600*/
/*#define ICE_MELT_TOTAL_TIME                    500*/
#define ICE_MELT_TOTAL_TIME                    400


#define ICE_TRAY_CLEAN_SPRAY_TIME_3_MIN        1800
/*#define ICE_TRAY_CLEAN_TIME_10_MIN              1800*/
#define ICE_TRAY_CLEAN_TIME_10_MIN              6000



/*#define ICE_MELT_PUMP_90_PERCENT_TIME          400*/
/*#define ICE_MELT_PUMP_90_PERCENT_TIME          300*/
#define ICE_MELT_PUMP_90_PERCENT_TIME          200


/*#define ICE_MELT_OPERATION_COUNT               3*/
/*#define ICE_MELT_OPERATION_COUNT               4*/
/*#define ICE_MELT_OPERATION_COUNT               3*/
/*..hui [24-2-22오후 4:23:31] 2회로 변경.. 2회에도 다 녹음..*/
#define ICE_MELT_OPERATION_COUNT               2


/*#define HOT_STER_FEEDER_REVERSE_1ST_TIME                  20*/
/*#define HOT_STER_FEEDER_REVERSE_TEST_TIME                  20*/
#define HOT_STER_FEEDER_REVERSE_TEST_TIME                  30


#define HOT_STER_FEEDER_REVERSE_1ST_TIME                  30
#define HOT_STER_FEEDER_REVERSE_2ND_TIME                  40



#define HOT_STER_FINISH_COLD_TEMP               15
#define HOT_STER_FINISH_ROOM_TEMP               20

#define HOT_STER_FINISH_MAX_TIME                36000

extern U16 gu16_Ice_Tray_Fill_Hz;
extern bit F_IceInit;
extern ICE_STEP gu8IceStep;
extern U8 gu8_cody_take_off_ice_start;

extern U8 gu8_Room_Water_Level;
extern U8 gu8IceTrayLEV;

extern bit F_Tank_Cover_Input;
extern U8 gu8_hot_flow_status;

extern U8 gu8_rtc_time_Y2K;       // 19 or 20
extern U8 gu8_rtc_time_DayWeek;   // 0 ~ 6
extern U8 gu8_rtc_time_Year;      // 0 ~ 99
extern U8 gu8_rtc_time_Month;     // 1 ~ 12
extern U8 gu8_rtc_time_Date;      // 1 ~ 31
extern U8 gu8_rtc_time_Hour;      // 0 ~ 23
extern U8 gu8_rtc_time_Min;       // 0 ~ 59
extern U8 gu8_rtc_time_Sec;       // 0 ~ 59

extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern bit F_Hot_Enable;
extern bit bit_first_time_setting;
extern bit bit_tray_pump_output;

extern bit bit_filter_cover;
extern bit bit_ro_filter_2_reed;
extern bit bit_flushing_water_start;
extern U8 gu8_ice_system_ok;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_steam_clean_percent;
extern bit F_IceFull;
extern bit F_Ice;
extern bit F_IceOn;
extern U8 gu8_Room_Temperature_One_Degree;
extern bit F_IR;
extern bit bit_filter_all;
extern U8 gu8Cup_level_Default;
extern bit bit_self_test_start;
extern bit bit_ice_ster_test_debug_start;
extern U8 gu8_ice_ster_drain_stop_count;
extern U8 gu8_ice_ster_low_water_stop_count;
extern bit F_TrayMotorDOWN;
extern bit F_TrayMotorUP;
extern U8 gu8AltitudeStep;
extern bit F_IceDoorClose;
extern bit bit_acid_clean_start;




#endif

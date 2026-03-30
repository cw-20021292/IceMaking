/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _CALC_EXTRACT_TIME_H_
#define _CALC_EXTRACT_TIME_H_

//

extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2



/*#define TOTAL_TANK_MAX_WATER           2000*/
/*..hui [23-5-12오전 9:23:03] 만수위 ~ 저수위까지 물양..*/
#define TOTAL_TANK_MAX_WATER           1500

#define ICE_TRAY_INPUT_WATER           300

#define FEED_WATER_TIME_1_MIN          600
#define FEED_TIME_1_MIN_PER_60ML       60


////////////////////////////////////////////////////////////////////////

#define ROOM_WATER_HALF_TIME_TANK_500ML      113
#define ROOM_WATER_HALF_TIME_TANK_1000ML     122
#define ROOM_WATER_HALF_TIME_TANK_1500ML     132

#define ROOM_WATER_ONE_TIME_TANK_500ML       221
#define ROOM_WATER_ONE_TIME_TANK_1000ML      231
#define ROOM_WATER_ONE_TIME_TANK_1500ML      281

#define ROOM_WATER_TWO_TIME_TANK_500ML       460
#define ROOM_WATER_TWO_TIME_TANK_1000ML      503
#define ROOM_WATER_TWO_TIME_TANK_1500ML      503

////////////////////////////////////////////////////////////////////////

#define COLD_WATER_HALF_TIME_TANK_500ML      108
#define COLD_WATER_HALF_TIME_TANK_1000ML     121
#define COLD_WATER_HALF_TIME_TANK_1500ML     122

#define COLD_WATER_ONE_TIME_TANK_500ML       219
#define COLD_WATER_ONE_TIME_TANK_1000ML      233
#define COLD_WATER_ONE_TIME_TANK_1500ML      244

#define COLD_WATER_TWO_TIME_TANK_500ML       466
#define COLD_WATER_TWO_TIME_TANK_1000ML      500
#define COLD_WATER_TWO_TIME_TANK_1500ML      528

////////////////////////////////////////////////////////////////////////

#define HOT_WATER_HALF_TIME_TANK_500ML       194
#define HOT_WATER_HALF_TIME_TANK_1000ML      200
#define HOT_WATER_HALF_TIME_TANK_1500ML      205

#define HOT_WATER_ONE_TIME_TANK_500ML        395
#define HOT_WATER_ONE_TIME_TANK_1000ML       400
#define HOT_WATER_ONE_TIME_TANK_1500ML       405

#define HOT_WATER_TWO_TIME_TANK_500ML        829
#define HOT_WATER_TWO_TIME_TANK_1000ML       834
#define HOT_WATER_TWO_TIME_TANK_1500ML       839


////////////////////////////////////////////////////////////////////////
#define TIME_PER_ML_DEIVDE                   50


#define FIXED_TIME_1500ML_COMPENSATION		 2

extern U8 gu8_Room_Water_Level;
extern bit bit_feed_output;
extern bit bit_nos_output;
extern bit F_WaterOut;
extern U16 u16Efluent_Time;
extern U8 u8Extract_Continue;
extern U8 gu8Cup_level;
extern ICE_STEP gu8IceStep;
extern bit F_FW_Version_Display_Mode;
extern U16 gu16_hot_mix_time;

extern U16 gu16_wifi_water_acc;

extern U16 gu16_my_cup_level_pure;
extern U16 gu16_my_cup_level_cold;
extern U16 gu16_my_cup_level_hot;
#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SELF_TEST_MANUAL_COMPONENT_H_
#define _SELF_TEST_MANUAL_COMPONENT_H_

//
extern U16 calculate_dc_current( U16 mu16_ad );
extern U16 calculate_fan_current( U16 mu16_ad );
extern U16 calculate_uv_current( U16 mu16_ad );
extern U16 calculate_pump_current( U16 mu16_ad );



extern void initial_each_self_data( U8 mu8_num );

extern void start_drain_pump( U16 u16_data );
extern void stop_drain_pump( void );
extern void start_tray_pump( U16 u16_data );
extern void stop_tray_pump( void );

extern void run_open_ro_drain(void);
extern void run_close_ro_drain(void);
extern void GasSwitchInit(void);



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





extern U8 gu8_ro_drain_status;
extern U16 gu16_AD_Result_Fan_Current;
extern bit F_IceDoorClose;

extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;
extern U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current;
extern U16 gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
extern U16 gu16_AD_Result_DC_Current_12V;
extern U16 gu16_AD_Result_DC_Current_24V;
extern U16 gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
extern U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;

extern U8 gu8_Tray_Flow_1sec;
extern U16 gu16ADIceFull;
extern U8 gu8_Filter_Flow_1sec;


/*#define DC_CURRENT_STABLE_TIME              10*/
#define DC_CURRENT_STABLE_TIME              45
#define CURRENT_DELAY_TIME                  5


#define SELF_MANUAL_FLOW_TEST_TIME          40


#define HEATER_TEST_PROHIBIT_TEMP           85



extern U16 gu16_AD_Result_DC_Current_24V;




#endif

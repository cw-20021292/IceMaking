/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SELF_TEST_AUTO_H_
#define _SELF_TEST_AUTO_H_

//
extern void send_wifi_self_test_function(void);
extern U16 GetWifiRequestValue ( E_WIFI_RQST_T mType );
extern void initial_each_self_data( U8 mu8_num );


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



extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3


extern TYPE_BYTE          U8FeedValveONB;
#define            u8FeedValveON                         U8FeedValveONB.byte
#define            Bit0_Low_Water_Filling_State          U8FeedValveONB.Bit.b0
#define            Bit1_Feed_Valve_Flushing_State        U8FeedValveONB.Bit.b1
#define            Bit2_Feed_Valve_Water_Flushing_State  U8FeedValveONB.Bit.b2
#define            Bit3_Feed_Valve_Flushing_Tank_State   U8FeedValveONB.Bit.b3

extern U8 gu8_Wifi_Connect_State;
extern bit F_WaterOut;

extern bit bit_self_test_start;

extern U8 gu8_Room_Water_Level;
extern bit bit_hot_first_op;
extern bit F_WaterOut;
extern bit F_Heater_Output;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_heater_off_temp;
extern bit F_Hot_Enable;


#define SELF_TEST_UPDATE_TIME_24HOUR    864000

#define SELF_TEST_TIME_1_HOUR           36000


#endif

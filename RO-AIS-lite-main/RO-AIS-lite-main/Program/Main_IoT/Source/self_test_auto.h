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


extern bit F_Cold_Enable;
extern U8 gu8_Cold_Temperature_One_Degree;
extern bit F_Comp_Output;
extern U16 mu16_cold_off_temp;

#endif

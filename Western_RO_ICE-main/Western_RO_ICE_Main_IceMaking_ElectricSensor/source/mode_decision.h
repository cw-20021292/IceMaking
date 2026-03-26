/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MODE_DECISION_H_
#define _MODE_DECISION_H_

//
extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3

extern TYPE_BYTE          U8CodyInspectOperationB;
#define            u8CodyInspectOperation                      U8CodyInspectOperationB.byte
#define            Bit0_Cody_Service_Kit_Start                 U8CodyInspectOperationB.Bit.b0
#define            Bit1_Empty_Tank_Start                       U8CodyInspectOperationB.Bit.b1
#define            Bit2_Ice_Tray_Test_Start                    U8CodyInspectOperationB.Bit.b2

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





extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3

extern TYPE_WORD          U16CompOnW;
#define            u16CompOn                               U16CompOnW.word
#define            u8CompOn_L                              U16CompOnW.byte[0]
#define            u8CompOn_H                              U16CompOnW.byte[1]
#define            Bit0_Cold_Mode_On_State                 U16CompOnW.Bit.b0
#define            Bit1_Ice_Make_On_State                  U16CompOnW.Bit.b1
#define            Bit2_Ice_Init_On_State                  U16CompOnW.Bit.b2
#define            Bit3_test_State                  U16CompOnW.Bit.b3

extern bit bit_acid_clean_start;







#define COLD_ON_TEMP_NORMAL         68
#define COLD_ON_TEMP_SAVING         100

#define COLD_OFF_REF_TEMP_AMB       300
#define COLD_OFF_TEMP_4_DEGREE      40
#define COLD_OFF_TEMP_5_DEGREE      50
#define PROTECT_COLD_TEMP           20

#define DUAL_OP_TEMP_AMB_20_DEGREE     200

#define COLD_ADD_OPERATION_TIME     18000


/*#define DRAIN_FULL_ICE_STOP_TIME    3000*/
#define DRAIN_FULL_ICE_STOP_TIME    6000


/*#define ICE_MAKE_GOGOGO       0x3F*/

/*#define ICE_MAKE_GOGOGO        0x1FF*/
/*#define COLD_MAKE_GOGOGO       0x7F*/

/*#define ICE_MAKE_GOGOGO              0x3FF*/
#define ICE_MAKE_GOGOGO              0x7FF
#define COLD_MAKE_GOGOGO             0xFF



/*..hui [24-4-11오후 4:01:39] 얼음우선 변경제어..*/
/*#define FAST_ICE_MAKE_COUNT          4*/
#define FAST_ICE_MAKE_COUNT          3
#define FAST_ICE_MAKE_ENABLE         0x3FF
#define FAST_ICE_COLD_MAX_OP_TIME    36000

//extern bit F_IceOn;
extern bit F_Cold_Enable;
//extern bit F_Fast_Ice_Make;
extern U16 gu16_Cold_Temperature;
extern U16 gu16_Amb_Front_Temperature;
extern U8 gu8_Room_Water_Level;
extern bit F_IceInit;
extern bit F_IceStop;
extern U8 gu8_GasSwitch_Status;
extern bit F_FW_Version_Display_Mode;
extern bit F_Safety_Routine;
extern bit F_ColdConty;
extern U8 gu8_cold_setting_level;
extern bit F_Sleep;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;


extern U8 gu8_Amb_Temperature_One_Degree;
extern bit bit_first_ice_full;
extern bit bit_fast_ice_make;
extern bit F_IceOn;
extern bit bit_sleep_mode_start;
extern bit bit_ice_tank_ster_start;
extern bit bit_extract_stop_before_ster_start;
extern bit bit_9_hour_no_use_start;
extern LED_STEP gu8_Led_Display_Step;
extern bit F_Ice_Tray_Down_Move_Reset;

extern ICE_STER_MODE gu8_ice_ster_mode;
extern bit bit_self_test_start;
extern bit F_Comp_Output;






#endif

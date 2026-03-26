/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _HEATING_CONTROL_H_
#define _HEATING_CONTROL_H_


//extern void mix_motor_control(void);
//extern void stop_hot_preheating(void);


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



extern TYPE_BYTE          U8HeaterMaxLimitB;
#define            u8HeaterMaxLimit                          U8HeaterMaxLimitB.byte
#define            Bit0_Over_1st_Limit                       U8HeaterMaxLimitB.Bit.b0
#define            Bit1_Over_2nd_Limit                       U8HeaterMaxLimitB.Bit.b1
#define            Bit2_Over_Flow_Increase_One               U8HeaterMaxLimitB.Bit.b2
#define            Bit3_Over_Flow_Increase_Two               U8HeaterMaxLimitB.Bit.b3
#define            Bit4_Over_Flow_Increase_Three             U8HeaterMaxLimitB.Bit.b4
#define            Bit5_Over_Flow_Increase_Four              U8HeaterMaxLimitB.Bit.b5
#define            Bit6_Over_Flow_Increase_Five              U8HeaterMaxLimitB.Bit.b6
#define            Bit7_Under_Flow_Decrease                  U8HeaterMaxLimitB.Bit.b7

extern TYPE_WORD          U16WaterHeaterOnW;
#define            u16WaterHeaterOn                          U16WaterHeaterOnW.word
#define            u16WaterHeater_L                          U16WaterHeaterOnW.byte[0]
#define            u16WaterHeater_H                          U16WaterHeaterOnW.byte[1]
#define            Bit0_Pre_Heating_State                    U16WaterHeaterOnW.Bit.b0
#define            Bit1_Main_Heating_State                   U16WaterHeaterOnW.Bit.b1
#define            Bit2_First_Heating_Check_State            U16WaterHeaterOnW.Bit.b2

extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern bit F_Hot_Enable;
extern bit F_ErrTrayMotor_DualInital;
extern U8 gu8_Room_Water_Level;
extern U8 gu8_hot_display_cnt;
//extern bit F_HardError;
//extern bit F_WaterInitSet;
extern U8 gu8AltitudeStep;
extern bit F_IceHeater;
extern bit F_FW_Version_Display_Mode;

extern bit F_CompHeater;                 // 콤프,히터 동시기동방지


//extern bit F_Hot_Water_Disable_Error;
extern bit F_Over_Ice_Heater_State;


extern bit F_IceInit;
extern bit F_Safety_Routine;
extern U8 gu8_over_ice_melt_proc;
extern bit F_Ice_Tray_Down_Move_Reset;


//extern bit F_ErrTrayMotor_Move;
extern U8 gu8_Room_Temperature_One_Degree;

extern bit F_WaterOut;
extern U8 gu8TriacLevelMax;
extern U16 gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;


extern bit F_Model_Select;



extern U8 gu8InitStep;
extern ICE_STEP gu8IceStep;
extern bit F_Hot_Enable;



extern U8 gu8_Tray_Flow_1sec;

extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_tray_pump_pwm_out;

extern U8 gu8_pre_heater_temp;

extern U8 gu8_Comp_Stable_State;

extern bit F_Sleep;
extern U8 u8_system_init_timer;
extern bit bit_hot_preheating_start;
extern U8 gu8_preheating_set_temp;
extern bit bit_9_hour_no_use_start;
extern bit bit_sleep_mode_start;
extern bit bit_ice_tank_ster_start;
extern ICE_STER_MODE gu8_ice_ster_mode;
extern HOT_STER_OP_TEMP gu8_hot_ster_temp_mode;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_hot_spray_start_hot_temp;
extern U8 gu8_ice_tray_start_hot_temp;
extern U8 gu8_mlet_ice_start_hot_temp;




/*#define HOT_SAFETY_TEMP                       100*/
#define HOT_SAFETY_TEMP                       99

#define HOT_SAFETY_DETECT_TIMNE               30


#define HEATER_ADD_OPERATION_TIME             100



#endif

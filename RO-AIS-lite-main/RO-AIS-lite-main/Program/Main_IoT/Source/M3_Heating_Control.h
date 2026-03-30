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

extern U16 conv_hot_hz( U8 mu8_flow_hz );



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






extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2



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
extern U16 gu16_AD_Result_UV_Ice_Tank_Current;


extern bit F_Model_Select;



extern U8 gu8InitStep;
extern ICE_STEP gu8IceStep;
extern bit F_Hot_Enable;



extern U8 gu8_Flow_1sec;

extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_hot_pump_pwm_out;

extern U8 gu8_pre_heater_temp;

extern U8 gu8_Comp_Stable_State;

//extern bit F_Sleep;
extern bit bit_9_hour_no_use_start;
extern bit bit_sleep_mode_start;


#define HOT_SAFETY_TEMP                       100
#define HOT_SAFETY_DETECT_TIMNE               30




#endif

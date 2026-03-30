/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _AC_MOTOR_OUTPUT_H_
#define _AC_MOTOR_OUTPUT_H_


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



extern bit F_IceOutCCW;
extern U8 gu8IceOutCCWInterval;


extern bit F_ErrTrayMotor_Move_D;
extern U16 gu16ErrIceOut;
//extern bit F_ErrTrayMotor_Move;
extern bit F_TrayMotorPreCW;
extern U8 gu8IceLEV;
extern bit F_IceInit;
//extern bit F_ErrTrayMotor_Dual;

//extern bit F_Tray_up_moving_retry_state;
extern bit F_TrayMotorPreCCW;
extern U16 gu16IceHeaterTime;
extern U16 gu16IceMakeTime;
extern bit F_Trayretry1;

//extern bit F_Reset;
extern U16 gu16ErrTrayMotor_Test_Mode;


extern bit F_Safety_Routine;
//extern bit F_IceMakeGo;
//extern bit F_Hotgas_Time;
extern bit F_IceHeater;
extern bit F_IceVV;
//extern bit F_ColdIn;
extern U16 gu16CompOffDelay;
//extern bit F_over_ice_melt_mode_cold_water_valve_out;


//extern U8 gu8ColdWaterLEV;
//extern bit F_ColdDIR;
extern bit F_ColdIce;
extern bit F_BarCW;
extern U8 gu8IRCount;
extern U8 gu8NoSBStep;
//extern U16 gu16MeltTime;
extern U8 gu8BarCNT;
//extern bit F_NoSelectBar;
extern bit F_NoColdBar;
extern bit F_NoIceBar;

//extern U16 Select_Delay;
extern U8 gu8InitStep;
extern U8 gu8IceTrayLEV;
extern bit F_TrayMotorCCW;
extern bit F_TrayMotorCW;
extern ICE_STEP gu8IceStep;

extern bit F_IR;                             // 만빙 검사
extern bit F_IceFull;






/*#define ICETRAY_CW_TIME 500*/                     // Ice Tray CW 25초 -> 50초
/*#define ICETRAY_CCW_TIME 500*/                    // Ice Tray CCW 25초 -> 50초


#define ICETRAY_CW_TIME 400                     // Ice Tray CW 25초 -> 50초
#define ICETRAY_CCW_TIME 400                    // Ice Tray CCW 25초 -> 50초



// 20161101 아이스트레이 마이크로 스위치 감지 개선
#define ICETRAY_RE_DELAY       220                                              //20161012 마이크로스위치 해지 안될 시 Ice Tray 정/역 딜레이 5초
#define ICETRAY_RE_DELAY1       220                                              //20161012 마이크로스위치 해지 안될 시 Ice Tray 정/역 딜레이 5초


#define TRAY_MOTOR_STOP            0
#define TRAY_MOTOR_CW_DIRECTION    1
#define TRAY_MOTOR_CCW_DIRECTION   2



#define TRAY_ERROR_STANDBY_TIME    6000


#define TRAY_UP_RESET_DELAY_TIME    12000




#endif

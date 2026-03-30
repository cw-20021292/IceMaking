/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MODE_CONTROL_H_
#define _MODE_CONTROL_H_


extern void Ice_Make_Process(void);
extern void auto_drain_control(void);
extern void ice_door_close_24_hour(void);

extern void ice_make_system_up_move_reset(void);
extern void ice_make_system_down_move_reset(void);
extern void execute_ice_tray_test(void);
extern void system_reset(void);
extern void logic_decision(void);
extern void Make_Mode_Decision(void);
extern void water_extract_control(void);
extern void check_ice_stop(void);
extern void service_check(void);
extern void cody_ice_tray_test(void);
extern void uart_test_mode_decision(void);
extern void model_select(void);
extern void calculate_electric_rate(void);
//extern void cody_empty_tank(void);
extern void cody_service(void);
extern void cody_takeoff_ice(void);

extern void down_tray_motor(void);
extern void setting_my_cup(void);
extern void calc_waterout_time(void);

extern void water_durable_test(void);

//extern void no_use_save_control(void);
extern void power_save_mode(void);

extern void time_setting(void);

extern void wifi_time_setting(void);
extern void wifi_smart_control(void);
extern void wifi_operation_control(void);


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






extern U8 gu8_Room_Water_Level;
extern bit F_IceHeater;


extern U16 gu16_AD_Result_Cold;
//extern bit F_Overflow;
//extern U8 gu8ErrOVFeedCnt;
//extern U8 gu8ErrOVRoomLEVCnt;
//extern bit F_ErrOVFeed;
//extern bit F_ErrOVFeed_D;
//extern bit F_ErrOVRoomLEV;
//extern bit F_ErrOVRoomLEV_D;
//extern bit F_ErrOVLEV;
//extern bit F_ErrOVLEV_D;
//extern bit F_Conty;
extern bit F_WaterOut;
extern bit F_HotOut;
extern bit F_Cold_Enable;
extern bit F_ColdOut;
extern bit F_RoomOut;
extern bit F_ContyGo;

extern U16 gu16IRInterval;
extern bit F_IceFull;
//extern bit F_ColdConty;
extern bit F_IceVV;
//extern bit F_ColdDIR;
//extern bit F_ColdIn;
//extern U8 gu8ContyCancel;
extern bit F_ColdIce;
extern bit F_BarCW;
extern bit F_TrayMotorCW;
extern U16 gu16CompOffDelay;
//extern bit F_IceMakeGo;
//extern U16 Select_Delay;
//extern bit F_Hotgas_Time;
extern bit F_IceInit;
//extern bit F_ReIceInit;
extern U8 gu8IRCount;
extern U8 gu8BarCNT;
extern U8 gu8NoSBStep;

extern bit F_NoColdBar;
extern bit F_NoIceBar;
//extern U16 gu32ServiceTime;

//extern bit F_Service;
//extern bit F_ErrOVF;
extern U16 u16Efluent_Time;

extern bit F_Hot_Temp_Setting;
extern bit F_Hot_Lock;

extern U8 gu8Cup_level_Default;


//extern U16 gu16NoWaterOut;
extern bit F_Save;
//extern bit F_IceOn;
extern U16 gu16IceMakeTime;

//extern U8 Tray_Comp_Delay;
extern U16 gu16IceOutOff;
extern U16 gu16ErrIceOut;
//extern U8 gu8ErrIceMotor;


extern U16 gu16IceHeaterTime;
//extern U16 gu16ErrPuriDelay;
//extern U16 gu16IceSupplyTime;
//extern U16 gu16LimitSterTime;
extern bit Be_COMP;
extern U16 gu16ColdVVOnTime;
//extern U8 gu8DrainErrorRetrayDelay;
//extern U8 gu8ICETrayRoomDelay;
//extern U16 gu16ErrOVHRoomTime;
//extern U16 gu16MaxSterTime;
//extern U8 gu8ICELockLEDFlick;
extern U8 gu8IRTime;
//extern U8 gu8ErrBar;

extern U8 gu8IceClose;

extern U8 gu8TrayCWInterval;
extern U8 gu8TrayCCWInterval;

//extern U16 gu16ErrColdLEVDelay;
//extern U16 gu16IceOutTest;

extern U8 gu8ErrDoor;
extern U8 gu8IceOutCCWInterval;

extern U8 u8_Tray_up_moving_retry_timer;
extern U8 u8Trayretry1;
//extern U16 gu16WashTime;
//extern U16 gu16NeutralTime;
extern U8 gu8_room_level_delay;
//extern U8 gu8ColdLEVDelay;
//extern U8 gu8IceDrainLEVDelay;


//extern U8 gu8LockLEDFlick;
extern U16 gu16ErrTrayMotor;

//extern U8 gu8ErrEW;
//extern U8 gu8LockFlick;
extern U8 gu8HeaterOffDelay;
extern U16 gu16IceVVTime;
//extern U16 gu16IceVVTime1;
//extern U8 gu8ColdWaterLEV;
//extern bit F_CyclePumpTimeFix;
//extern bit F_CyclePumpSet;
//extern bit F_CyclePump;
//extern U16 gu16IceVVTimeSetDelay;
//extern U8 gu8CyclePumpCNT;


extern bit F_Hot_Enable;
extern U8 gu8_Error_Code;

extern U8 u8Extract_Continue;


extern bit F_ColdConty;
extern U8 gu8Cup_level_Old;


extern bit F_Ice_Make_Priority_Setting_Mode;
extern U8 gu8_ice_make_priority_settiong_time;
extern bit F_WaterOut_Disable_State;

extern U16 gu16_cody_ice_make_time;
extern U8 gu8InitStep;
extern bit F_IR;
extern ICE_STEP gu8IceStep;


extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;


extern U8 gu8_cold_setting_level;
extern bit bit_cold_read_finish;
extern bit bit_hot_read_finish;
extern bit F_Tank_Cover_Input;
extern bit bit_9_hour_no_use_start;


extern bit F_FW_Version_Display_Mode;

extern bit F_Comp_Output;

#endif


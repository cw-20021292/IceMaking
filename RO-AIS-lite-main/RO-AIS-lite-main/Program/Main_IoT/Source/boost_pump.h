/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _BOOST_PUMP_H_
#define _BOOST_PUMP_H_


//



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




extern bit F_WaterOut;
extern bit bit_feed_output;
extern bit F_Flow_Block_State;
extern bit F_Err_OVF_Check;
extern U8 gu8_Room_Water_Level;

/*..hui [20-11-26오후 7:12:31] 피드 열리고 1초 후 펌프 가동..*/
#define PUMP_DELAY_TIME         10

/*#define PUMP_ON_40MIN           24000*/

/*..hui [21-4-1오전 11:36:43] 저소음 펌프로 변경됨에 따라 ON 시간 2시간으로 수정..*/
#define PUMP_ON_120MIN          72000

#define PUMP_ON_40MIN           24000


/*#define PUMP_ON_150MIN          90000*/
#define PUMP_ON_160MIN          96000


#define PUMP_OFF_20MIN          12000
#define PUMP_OFF_120MIN         72000

//#define PUMP_MAX_PWM            13600//28800 //0x3E80 * 2  //85%
//#define PUMP_MAX_PWM            14400
//#define PUMP_80_PERCENT_PWM     12800


#define BOOST_PUMP_ON_DETECT_TIME     30
#define BOOST_PUMP_OFF_DETECT_TIME    30







#endif

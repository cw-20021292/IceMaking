/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WATER_VALVE_CONTROL_H_
#define _WATER_VALVE_CONTROL_H_



extern void calc_mix_water(void);
extern void open_hot_valve(void);



extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

//extern bit F_Conty;
extern bit F_WaterOut;
extern bit F_HotOut;
extern bit F_ColdOut;
extern bit F_RoomOut;
extern bit F_ContyGo;
//extern U8 gu8ContyCancel;
//extern U16 gu16NoWaterOut;
extern bit F_NightNoUseSave;
extern bit F_DayNoUseSave;
//extern bit F_Service;

//extern U16 gu16Conty;
extern bit F_All_Lock;
extern bit F_Hot_Lock;
extern bit F_NoUseSave;


extern U8 gu8_Flow_1sec;
extern bit F_Effluent_OK;



extern U8 gu8_effluent_control_timer;
extern bit bit_open_hot_valve;

extern bit bit_my_cup_setting_start;
extern U8 gu8_Room_Water_Level;









#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MY_CUP_H_
#define _MY_CUP_H_

//
extern void start_my_cup_end_flick( void );
extern void start_set_flick( U8 mu8_mode );


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


extern bit F_WaterOut;
extern U16 u16Efluent_Time;
extern U16 gu16_my_cup_level_pure;
extern bit bit_my_cup_enable;
extern U16 gu16_my_cup_level_pure;
extern U16 gu16_my_cup_level_cold;
extern U16 gu16_my_cup_level_hot;
extern U8 gu8_my_cup_setting_step;
extern bit bit_my_cup_finish_flick;




#endif

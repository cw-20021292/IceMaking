/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _HOT_CONTROL_H_
#define _HOT_CONTROL_H_

//
extern void hot_prepare(void);
//extern void hot_preheating_control(void);
/*extern void run_init_flow(void);*/
/*extern void run_increase_flow( U16 mu16_move );*/
/*extern void run_decrease_flow( U16 mu16_move );*/
/*extern void run_target_flow( U16 mu16_target );*/
/*extern void ControlMixFlow(void);*/
//extern void hot_prepare_stage(void);


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


extern bit F_WaterOut;
extern U8 gu8_hot_setting_temperature;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_Mixing_Out_Temperature_One_Degree;
extern bit F_FW_Version_Display_Mode;
extern U8 gu8_hot_flow_mode;
extern U8 gu8_hot_flow_status;






#endif

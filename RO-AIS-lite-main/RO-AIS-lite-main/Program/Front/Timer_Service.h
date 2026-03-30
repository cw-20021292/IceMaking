/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#ifndef _Timer_Service_H_
#define _Timer_Service_H_


//
extern void Key_Input(void);
extern void service_check_input(void);
extern void cup_rgb_control(void);
extern void front_key_transition_check(void);
extern void Front_Communication(void);
extern void Led_Output(void);

extern bit bit_uv_ice_extraction_out;

#endif

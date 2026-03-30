/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _CODY_SERVICE_H_
#define _CODY_SERVICE_H_

//
extern void force_take_off_ice(void);

extern void stop_ice_cody_mode(void);

extern void BuzStep(U8 mu8Step);








extern bit F_IceInit;
extern U16 gu16IceMakeTime;


extern bit F_WaterOut;
extern U8 gu8_extract_display_cnt;
extern U16 u16Efluent_Time;
extern U16 gu16Water_Extract_Timer;
extern bit F_Ice;
extern bit F_Tank_Cover_Input;

extern ICE_STEP gu8IceStep;

extern bit F_All_Lock;
extern bit bit_tank_reed_read_finish;
extern bit F_FW_Version_Display_Mode;



#endif

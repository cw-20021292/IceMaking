/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _NO_USE_SAVE_H_
#define _NO_USE_SAVE_H_
/*
typedef enum
{
NONE, BASIC, ADVANCED
}POWER_SAVING_STATE;
*/



extern U8 gu8_Amb_Temperature_One_Degree;


extern void BuzStep(U8 mu8Step);



extern U16 gu16ADCds;
extern bit F_FW_Version_Display_Mode;

extern U8 gu8_wifi_no_use_key;


extern bit F_Hot_Enable;
extern bit F_Cold_Enable;
extern bit F_IceOn;

#endif

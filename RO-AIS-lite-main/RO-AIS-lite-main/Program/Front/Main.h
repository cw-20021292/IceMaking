/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_



extern void System_ini(void);
extern void Led_Output(void);
extern void service_check_input(void);
extern void Front_Communication(void);
extern void AD_Conversion(void);

extern U8 u8CountSync;
extern bit F_10ms;
extern bit F_20ms;
extern bit F_100ms;

extern bit F_ADC_Check;

#endif

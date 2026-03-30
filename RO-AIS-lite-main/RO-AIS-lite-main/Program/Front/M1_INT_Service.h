/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#ifndef _INT_SERVICE_H_
#define _INT_SERVICE_H_

//

extern void Timer_250us_Service(void);
extern void Uart_ISR2_Front_Panel_Rx(void);
extern void Uart_ISR2_Front_Panel_Tx (void);

#define FRAMING_ERROR    1
#define PARITY_ERROR     2
#define OVERRUN_ERROR    3
#define UNKNOWN_ERROR    4


#endif


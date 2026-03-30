/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Timer.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#pragma interrupt INTTM00 INTTM00


#pragma interrupt INTST2 INTST2
#pragma interrupt INTSR2 INTSR2
#pragma interrupt INTSRE2 INTSRE2
/***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "M1_INT_Service.h"
/***********************************************************************************************************************/




/***********************************************************************************************************************/
U8 u8MotorCnt_2_5ms;
U8 u8MotorCnt_3ms;
U8 u8Cnt_Check;
U8 u8MotorCnt_2ms;
bit F_100msErrControlState;

bit F_Powerin1sec;



U16 u16intempComm;

U8  u8Uart0_ErrorCode;
U8  u8Uart0_ErrorCnt;


U8  u8Uart1_ErrorCode;
U8  u8Uart1_ErrorCnt;


U8  u8Uart2_ErrorCode;
U8  u8Uart2_ErrorCnt;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTTM00 ( void ) /* 250us */
{
    Timer_250us_Service();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTST2 (void)
{
    Uart_ISR2_Front_Panel_Tx();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSR2 (void)
{
    U8 err_type = 0;

    err_type = (U8)(SSR11 & 0x0007);
    SIR11 = (U16)err_type;

    Uart_ISR2_Front_Panel_Rx();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSRE2 (void)
{
    U8 err_type;
    U8 rx_data = 0;

    rx_data = RXD2;

    //gu8_front_rx_receive_cnt = 0;

    if( (SSR11 & 1) == SET )
    {
        u8Uart2_ErrorCode = FRAMING_ERROR;
    }
    else if( (SSR11 & 2) == SET )
    {
        u8Uart2_ErrorCode = PARITY_ERROR;
    }
    else if( (SSR11 & 4) == SET )
    {
        u8Uart2_ErrorCode = OVERRUN_ERROR;
    }
    else
    {
        u8Uart2_ErrorCode = UNKNOWN_ERROR;
    }

    u8Uart2_ErrorCnt++;

    SS1 |= 0x0002 | 0x0001;    /* enable UART2 receive and transmit */

    SIR11 = 0x0007;
    SREIF2 = CLEAR;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



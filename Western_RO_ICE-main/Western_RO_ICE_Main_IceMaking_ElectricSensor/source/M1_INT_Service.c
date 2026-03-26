/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Timer.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#pragma interrupt INTTM00 INTTM00
#pragma interrupt INTTM02 INTTM02

//#pragma interrupt INTTM13 INTTM13

//#pragma interrupt INTAD INTAD

/*#pragma interrupt INTP4 INTP4*/
#pragma interrupt INTP7 INTP7
#pragma interrupt INTP11 INTP11

#pragma interrupt INTST0 INTST0
#pragma interrupt INTSR0 INTSR0
#pragma interrupt INTSRE0 INTSRE0

#pragma interrupt INTST1 INTST1
#pragma interrupt INTSR1 INTSR1
#pragma interrupt INTSRE1 INTSRE1

#pragma interrupt INTST2 INTST2
#pragma interrupt INTSR2 INTSR2
#pragma interrupt INTSRE2 INTSRE2

#pragma interrupt INTST3 INTST3
#pragma interrupt INTSR3 INTSR3
#pragma interrupt INTSRE3 INTSRE3

#pragma interrupt INTIICA0 INTIICA0


/***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M1_INT_Service.h"
/***********************************************************************************************************************/




/***********************************************************************************************************************/
U8 u8MotorCnt_2_5ms;
U8 u8MotorCnt_3ms;
U8 u8MotorCnt_30ms;

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

U8  u8Uart3_ErrorCode;
U8  u8Uart3_ErrorCnt;

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
__interrupt void INTTM02 ( void ) /* 500us */
{
    u8MotorCnt_2ms++;
    u8MotorCnt_2_5ms++;
    u8MotorCnt_3ms++;
    u8MotorCnt_30ms++;

    if(u8MotorCnt_2ms >= 4)
    {
        /*2ms*/
        u8MotorCnt_2ms = 0;
        /*..hui [23-9-18오후 5:21:46] 냉수 믹싱모터 삭제..*/
        /*HAL_ControlMixMotor();*/
    }
    else{}

    if(u8MotorCnt_3ms >= 6)
    {
        /*3ms*/
        u8MotorCnt_3ms = 0;

        /*..hui [17-11-30오전 11:23:40] Door 스텝 모터..*/
        motor_ice_door_output();
        HAL_ControlRoDrainMotor();
    }
    else{}

    if(u8MotorCnt_30ms >= 60)
    {
        /*3ms*/
        u8MotorCnt_30ms = 0;

        /*..hui [19-7-24오전 11:21:59] 냉매전환밸브..*/
        StepMotorTimerInterrupt();
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
__interrupt void INTTM13 ( void )
{
    //
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

//__interrupt void INTAD ( void )
//{
    //AD_Conversion();
//}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
__interrupt void INTP4 (void)
{
    //
    /*..hui [18-8-9오후 5:28:35] TDS INPUT..*/
    INTP4_TDS_Input();
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTP7 (void)
{
    //
    /*..hui [19-7-17오후 3:24:58] 필터 유량센서..*/
    INTP7_Filter_Flow_Sensor_Input();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTP11 (void)
{
    //
    /*..hui [19-7-17오후 3:24:58] 유량센서..*/
    INTP11_Tray_Flow_Sensor_Input();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTST0 (void)
{
    Uart_ISR0_Front_Panel_Tx();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSR0 (void)
{
    U8 err_type = 0;

    err_type = (U8)(SSR01 & 0x0007);
    SIR01 = (U16)err_type;

    Uart_ISR0_Front_Panel_Rx();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSRE0 (void)
{
    U8 err_type;
    U8 rx_data = 0;

    rx_data = RXD0;

    gu8_front_rx_receive_cnt = 0;

    if( (SSR01 & 1) == SET )
    {
        u8Uart0_ErrorCode = FRAMING_ERROR;
    }
    else if( (SSR01 & 2) == SET )
    {
        u8Uart0_ErrorCode = PARITY_ERROR;
    }
    else if( (SSR01 & 4) == SET )
    {
        u8Uart0_ErrorCode = OVERRUN_ERROR;
    }
    else
    {
        u8Uart0_ErrorCode = UNKNOWN_ERROR;
    }

    u8Uart0_ErrorCnt++;

    err_type = (U8)(SSR01 & 0x0007);
    SIR01 = (U16)err_type;

    /*SIR01 = 0x0007;*/

    SS0 |= 0x0002 | 0x0001;    /* enable UART0 receive and transmit */

    SREIF0 = CLEAR;//
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTST1 (void)
{
    InterruptUartWifiTx();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSR1 (void)
{
    InterruptUartWifiRx(RXD1);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSRE1 (void)
{
    InterruptUartWifiError();

#if 0
    U8 err_type;

    if( (SSR03 & 1) == SET )
    {
        u8Uart1_ErrorCode = FRAMING_ERROR;
    }
    else if( (SSR03 & 2) == SET )
    {
        u8Uart1_ErrorCode = PARITY_ERROR;
    }
    else if( (SSR03 & 4) == SET )
    {
        u8Uart1_ErrorCode = OVERRUN_ERROR;
    }
    else
    {
        u8Uart1_ErrorCode = UNKNOWN_ERROR;
    }

    u8Uart1_ErrorCnt++;

    SIR03 = 0x0007;
    SREIF1 = CLEAR;
#endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTST2 (void)
{
    //
    Uart_ISR2_Bldc_Comp_Tx();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSR2 (void)
{
    U8 err_type = 0;
    U8 rx_data;

    err_type = (U8)(SSR11 & 0x0007);
    SIR11 = (U16)err_type;

    Uart_ISR2_Bldc_Comp_Rx();
    /////rx_data = RXD2;
    ///////UART2_Receive_Interrupt(rx_data);
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


    #if 0
    rx_data = RXD2;

    F_UART2ErrorInterrupt = SET;

    UART2_Error_Interrupt();
    SIR11 = 0x0007;
    SREIF2 = CLEAR;
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTST3 (void)
{
    //
    #if 0
    if( u8FactoryTestMode > 0 )
    {
        int_UART3_AT_TX();
    }
    else
    {
        Uart_ISR3_PC_Tx();
    }
    #endif

    if(gu8_test_mode_timeout == 0 && u8FactoryTestMode == NONE_TEST_MODE)
    {
        Uart_ISR3_PC_Tx();
    }
    else
    {
        int_UART3_AT_TX();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSR3 (void)
{
    //
    #if 0
    if(u8FactoryTestMode > 0)
    {
        int_UART3_AT_RX();
    }
    else
    {
        Uart_ISR3_PC_Rx();
    }
    #endif

    if(gu8_test_mode_timeout == 0 && u8FactoryTestMode == NONE_TEST_MODE)
    {
        Uart_ISR3_PC_Rx();
    }
    else
    {
        int_UART3_AT_RX();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt void INTSRE3 (void)
{
    U8 err_type;
    U8 rx_data = 0;

    rx_data = RXD3;

    if( (SSR13 & 1) == SET )
    {
        u8Uart3_ErrorCode = FRAMING_ERROR;
    }
    else if( (SSR13 & 2) == SET )
    {
        u8Uart3_ErrorCode = PARITY_ERROR;
    }
    else if( (SSR13 & 4) == SET )
    {
        u8Uart3_ErrorCode = OVERRUN_ERROR;
    }
    else
    {
        u8Uart3_ErrorCode = UNKNOWN_ERROR;
    }

    u8Uart3_ErrorCnt++;

    SS1 |= 0x0008 | 0x0004;    /* enable UART3 receive and transmit */

    SIR13 = 0x0007;
    SREIF3 = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
__interrupt static void INTIICA0(void)
{
    if ((IICS0 & 0x80) == 0x80)
    {
        iica0_master_handler();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/







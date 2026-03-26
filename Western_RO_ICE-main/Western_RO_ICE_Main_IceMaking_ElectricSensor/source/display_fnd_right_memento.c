/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "display_fnd_right_memento.h"


void fnd_right_memento(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_memento(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8_memento_display_num == 0 )
    {
        if( u8Memento_Buff[0] == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;
        }
        else if( u8Memento_Buff[0] < 100 )
        {
            /*..hui [23-9-26오후 6:05:50] 일반 에러코드는 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)(u8Memento_Buff[0] / 10);
            mu8_temporary_one = (U8)(u8Memento_Buff[0] % 10);
        }
        else
        {
            /*..hui [23-9-26오후 6:05:27] E29 세부 에러코드는 ECx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = (U8)(u8Memento_Buff[0] % 100);
        }
    }
    else if( gu8_memento_display_num == 1 )
    {
        if( u8Memento_Buff[1] == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;
        }
        else if( u8Memento_Buff[1] < 100 )
        {
            /*..hui [23-9-26오후 6:05:50] 일반 에러코드는 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)(u8Memento_Buff[1] / 10);
            mu8_temporary_one = (U8)(u8Memento_Buff[1] % 10);
        }
        else
        {
            /*..hui [23-9-26오후 6:05:27] E29 세부 에러코드는 ECx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = (U8)(u8Memento_Buff[1] % 100);
        }
    }
    else if( gu8_memento_display_num == 2 )
    {
        if( u8Memento_Buff[2] == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;
        }
        else if( u8Memento_Buff[2] < 100 )
        {
            /*..hui [23-9-26오후 6:05:50] 일반 에러코드는 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)(u8Memento_Buff[2] / 10);
            mu8_temporary_one = (U8)(u8Memento_Buff[2] % 10);
        }
        else
        {
            /*..hui [23-9-26오후 6:05:27] E29 세부 에러코드는 ECx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = (U8)(u8Memento_Buff[2] % 100);
        }
    }
    else if( gu8_memento_display_num == 3 )
    {
        if( u8Memento_Buff[3] == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;
        }
        else if( u8Memento_Buff[3] < 100 )
        {
            /*..hui [23-9-26오후 6:05:50] 일반 에러코드는 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)(u8Memento_Buff[3] / 10);
            mu8_temporary_one = (U8)(u8Memento_Buff[3] % 10);
        }
        else
        {
            /*..hui [23-9-26오후 6:05:27] E29 세부 에러코드는 ECx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = (U8)(u8Memento_Buff[3] % 100);
        }
    }
    else /*if( gu8_memento_display_num == 4 )*/
    {
        if( u8Memento_Buff[4] == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;
        }
        else if( u8Memento_Buff[4] < 100 )
        {
            /*..hui [23-9-26오후 6:05:50] 일반 에러코드는 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)(u8Memento_Buff[4] / 10);
            mu8_temporary_one = (U8)(u8Memento_Buff[4] % 10);
        }
        else
        {
            /*..hui [23-9-26오후 6:05:27] E29 세부 에러코드는 ECx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = (U8)(u8Memento_Buff[4] % 100);
        }
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





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
#include    "display_fnd_right_filter.h"


void fnd_right_filter_open_state(void);
void fnd_right_filter_alarm_state(void);

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_filter_open_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_disp = 0;


    if( bit_filter_alarm_start == SET )
    {
        if( gu16_display_filter_remain_day < 10 )
        {
            if( gu16_display_filter_remain_day == 0 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = (U8)gu16_display_filter_remain_day;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = (U8)gu16_display_filter_remain_day;
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (U8)(gu16_display_filter_remain_day / 10);
            mu8_temporary_one = (U8)(gu16_display_filter_remain_day % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_filter_alarm_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_disp = 0;


    if( bit_filter_alarm_start == SET )
    {
        if( gu16_display_filter_remain_day < 10 )
        {
            if( gu16_display_filter_remain_day == 0 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = (U8)gu16_display_filter_remain_day;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = (U8)gu16_display_filter_remain_day;
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (U8)(gu16_display_filter_remain_day / 10);
            mu8_temporary_one = (U8)(gu16_display_filter_remain_day % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);


}







/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





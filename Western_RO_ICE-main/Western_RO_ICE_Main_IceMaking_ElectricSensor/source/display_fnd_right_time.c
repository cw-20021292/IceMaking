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
#include    "display_fnd_right_time.h"


void fnd_right_time_setting_state(void);

U8 gu8_min_setting_blink_timer;
bit bit_min_blink_500ms;
U8 gu8_time_blink_finish_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_time_setting_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8_time_setting_step == SETTING_TIME_HOUR )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
    }
    else if( gu8_time_setting_step == SETTING_TIME_MIN )
    {
        gu8_min_setting_blink_timer++;

        if( gu8_min_setting_blink_timer >= 5 )
        {
            if( u8TimeSettingLongKey > 0 )
            {
                gu8_min_setting_blink_timer = 0;
                bit_min_blink_500ms = CLEAR;
            }
            else
            {
                gu8_min_setting_blink_timer = 0;
                bit_min_blink_500ms ^= SET;
            }

            /*gu8_min_setting_blink_timer = 0;*/
            /*bit_min_blink_500ms ^= SET;*/
        }
        else{}

        #if 0
        /*..hui [23-8-1오후 3:57:44] 연속으로 바뀔때는 점등으로.. 바뀌는값이 안보임..*/
        if( u8TimeSettingLongKey > 0 )
        {
            gu8_min_setting_blink_timer = 0;
            bit_min_blink_500ms = CLEAR;
        }
        else{}
        #endif

        if( bit_min_blink_500ms == CLEAR )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
            mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else //if( gu8_time_setting_step == SETTING_TIME_FINISH )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}











/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





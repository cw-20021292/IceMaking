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
#include    "display_fnd_left_time.h"

void fnd_left_time_setting_state(void);

U8 gu8_hour_setting_blink_timer;
bit bit_hour_blink_500ms;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_time_setting_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;

    if( gu8_time_setting_step == SETTING_TIME_HOUR )
    {
        gu8_hour_setting_blink_timer++;

        if( gu8_hour_setting_blink_timer >= 5 )
        {
            /*..hui [23-8-2오전 9:23:04] 싱크 맞추기 위해 이쪽으로 이동.. 0.1초 켜지고 바로 다시 켜질수있음..*/
            if( u8TimeSettingLongKey > 0 )
            {
                gu8_hour_setting_blink_timer = 0;
                bit_hour_blink_500ms = CLEAR;
            }
            else
            {
                gu8_hour_setting_blink_timer = 0;
                bit_hour_blink_500ms ^= SET;
            }

            /*gu8_hour_setting_blink_timer = 0;*/
            /*bit_hour_blink_500ms ^= SET;*/
        }
        else{}

        #if 0
        if( u8TimeSettingLongKey > 0 )
        {
            gu8_hour_setting_blink_timer = 0;
            bit_hour_blink_500ms = CLEAR;
        }
        else{}
        #endif

        if( bit_hour_blink_500ms == CLEAR )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (U8)((gu8_temporary_Hour / 10) % 10);
            mu8_temporary_one = (U8)(gu8_temporary_Hour % 10);
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else if( gu8_time_setting_step == SETTING_TIME_MIN )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_temporary_Hour / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Hour % 10);
        gu8_hour_setting_blink_timer = 0;
        bit_hour_blink_500ms = CLEAR;
    }
    else //if( gu8_time_setting_step == SETTING_TIME_FINISH )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_temporary_Hour / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Hour % 10);
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





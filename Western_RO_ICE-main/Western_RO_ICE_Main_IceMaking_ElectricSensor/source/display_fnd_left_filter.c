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
#include    "display_fnd_left_filter.h"

void fnd_left_filter_open_state(void);
void fnd_left_filter_alarm_state(void);
//U8 fliter_flick_timer(U8 flick_time, U8 interval);
void finish_filter_alarm(void);

U16 gu16_filter_alarm_flick_timer;
U8 gu8_filter_alarm_flick_cnt;


U8 gu8_filter_alarm_dsp_timer;
bit bit_filter_alarm_display_finish;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_filter_open_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    #if 0
    if( u16_display_usage_water_gal < 100 )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((u16_display_usage_water_gal / 10) % 10);
        mu8_temporary_one = (U8)(u16_display_usage_water_gal % 10);
    }
    else if( u16_display_usage_water_gal < 1000 )
    {
        mu8_temporary_hundred = (U8)((u16_display_usage_water_gal / 100) % 10);
        mu8_temporary_ten = (U8)((u16_display_usage_water_gal / 10) % 10);
        mu8_temporary_one = (U8)(u16_display_usage_water_gal % 10);
    }
    else
    {
        mu8_temporary_hundred = (U8)((u16_display_usage_water_gal / 1000) % 10);
        mu8_temporary_ten = (U8)((u16_display_usage_water_gal / 100) % 10);
        mu8_temporary_one = (U8)((u16_display_usage_water_gal / 10) % 10);
    }
    #endif

    /*..hui [23-12-5오후 4:56:25] 필터커버 열림시 왼쪽 seg는 OFF..*/
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_filter_alarm_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    /*..hui [23-12-6오후 1:06:27] 필터 알람 표시는 왼쪽 seg OFF로 변경..*/
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    if( bit_filter_alarm_display_finish == SET )
    {
        bit_filter_alarm_display_finish = CLEAR;
        gu8_filter_alarm_dsp_timer = 70;
    }
    else{}

    gu8_filter_alarm_dsp_timer++;

    if( gu8_filter_alarm_dsp_timer >= 70 )
    {
        gu8_filter_alarm_dsp_timer = 0;
        gu8_filter_alarm_popup_enable = CLEAR;
    }
    else{}

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U8 fliter_flick_timer(U8 flick_time, U8 interval)
{
    static U8 u8flick_filter_state = 0;

    gu16_filter_alarm_flick_timer++;

    if( (gu16_filter_alarm_flick_timer % interval) == 0 )
    {
        u8flick_filter_state ^= SET;
        gu8_filter_alarm_flick_cnt++;
    }
    else{}

    if( gu8_filter_alarm_flick_cnt >= flick_time && u8flick_filter_state == SET )
    {
        //gu8_filter_alarm_flick_cnt = 0;
        gu16_filter_alarm_flick_timer = 0;
        //u8flick_filter_state = CLEAR;

        /////u8SetDisplay = ON_OFF_DISPLAY_OFF;
    }
    else{}

    return u8flick_filter_state;
}
#endif

void finish_filter_alarm(void)
{
    if( F_WaterOut == CLEAR )
    {
        gu8_filter_alarm_dsp_timer = 0;
        gu8_filter_alarm_popup_enable = CLEAR;
        gu8_filter_alarm_flick_cnt = 0;
        gu16_filter_alarm_flick_timer = 0;

        /////all_dimming_full_on();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





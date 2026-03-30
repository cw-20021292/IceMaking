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
#include    "display_fnd_flick.h"

void start_set_flick( U8 mu8_mode );
U8 on_off_flick_timer(U8 flick_time, U8 interval);
U8 error_flick_timer(U8 flick_time, U8 interval);
void start_my_cup_end_flick( void );
U8 my_cup_end_flick_timer(U8 flick_time, U8 interval);
void start_defualt_cup_set_flick( void );
U8 default_cup_set_flick_timer(U8 flick_time, U8 interval);
void start_button_set_display( U8 mu8_mode );
U8 button_set_display_timer( U8 flick_time );
void stop_button_set_display( void );

TYPE_BYTE          U8ButtonSetDisplayB;
#define            u8ButtonSetDisplay                   U8ButtonSetDisplayB.byte
#define            Bit0_Hot_Button_Set_Display          U8ButtonSetDisplayB.Bit.b0
#define            Bit1_Cold_Button_Set_Display         U8ButtonSetDisplayB.Bit.b1
#define            Bit2_Ice_Button_Set_Display          U8ButtonSetDisplayB.Bit.b2
#define            Bit2_cold_Temp_Set_Display           U8ButtonSetDisplayB.Bit.b3



U16 gu16_on_off_flick_timer;
U8 gu8_on_off_flick_cnt;

U8 gu8_error_flick_timer;
U8 gu8_error_flick_cnt;

U8 gu8_my_cup_end_flick_timer;
U8 gu8_my_cup_end_flick_cnt;

bit bit_default_cup_flick;
U8 gu8_default_cup_flick_state;
U8 gu8_default_flick_delay;

U8 gu8_default_cup_flick_timer;
U8 gu8_default_cup_flick_cnt;

U16 gu16_button_set_display_timer;
U8 u8flick_my_cup_state;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_set_flick( U8 mu8_mode )
{
    u8SetDisplay = mu8_mode;
    gu8_on_off_flick_cnt = 0;
    gu16_on_off_flick_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 on_off_flick_timer(U8 flick_time, U8 interval)
{
    static U8 u8flick_onoff_state = 0;

    /*..hui [23-3-15오후 5:46:39] 아이콘 아이스 = 점멸이 아니라 약 2초간 점등임.. 변경..*/
    gu16_on_off_flick_timer++;

    if( gu16_on_off_flick_timer >= flick_time )
    {
        gu8_on_off_flick_cnt = 0;
        gu16_on_off_flick_timer = 0;
        u8flick_onoff_state = CLEAR;

        u8SetDisplay = ON_OFF_DISPLAY_OFF;
        bit_my_cup_first_display = CLEAR;
    }
    else
    {
        u8flick_onoff_state = SET;
    }


    return u8flick_onoff_state;
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 error_flick_timer(U8 flick_time, U8 interval)
{
    static U8 u8flick_error_state = 0;

    if( gu8_error_flick_timer ==  0 )
    {
        u8flick_error_state = CLEAR;
    }
    else{}

    gu8_error_flick_timer++;

    if( (gu8_error_flick_timer % interval) == 0 )
    {
        u8flick_error_state ^= SET;
        gu8_error_flick_cnt++;
    }
    else{}

    if( gu8_error_flick_cnt >= flick_time && u8flick_error_state == SET )
    {
        gu8_error_flick_cnt = 0;
        gu8_error_flick_timer = 0;
        u8flick_error_state = CLEAR;

        gu8_error_popup_enable = CLEAR;
    }
    else{}

    return u8flick_error_state;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_my_cup_end_flick( void )
{
    bit_my_cup_finish_flick = SET;
    gu8_my_cup_end_flick_cnt = 0;
    gu8_my_cup_end_flick_timer = 0;
    u8flick_my_cup_state = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 my_cup_end_flick_timer(U8 flick_time, U8 interval)
{
    gu8_my_cup_end_flick_timer++;

    if( (gu8_my_cup_end_flick_timer % interval) == 0 )
    {
        if( gu8_my_cup_end_flick_cnt < flick_time )
        {
            u8flick_my_cup_state ^= SET;
            gu8_my_cup_end_flick_cnt++;
        }
        else{}
    }
    else{}

    if( gu8_my_cup_end_flick_cnt >= flick_time /*&& u8flick_my_cup_state == SET*/
        && gu8_my_cup_end_flick_timer >= ((flick_time * interval) + 10) )
    {
        gu8_my_cup_end_flick_cnt = 0;
        gu8_my_cup_end_flick_timer = 0;
        u8flick_my_cup_state = CLEAR;

        bit_my_cup_finish_flick = CLEAR;
        bit_my_cup_setting_start = CLEAR;

        /*..hui [23-3-22오후 5:25:27] 세팅 모드도 자동 종료..*/
        bit_setting_mode_start = CLEAR;
    }
    else{}

    return u8flick_my_cup_state;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_defualt_cup_set_flick( void )
{
    bit_default_cup_flick = SET;
    gu8_default_cup_flick_cnt = 0;
    gu8_default_cup_flick_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 default_cup_set_flick_timer(U8 flick_time, U8 interval)
{
    static U8 u8flick_default_cup_state = 0;

    if( gu8_default_cup_flick_timer ==  0 )
    {
        u8flick_default_cup_state = CLEAR;
    }
    else{}

    gu8_default_cup_flick_timer++;

    if( (gu8_default_cup_flick_timer % interval) == 0 )
    {
        u8flick_default_cup_state ^= SET;
        gu8_default_cup_flick_cnt++;
    }
    else{}

    if( gu8_default_cup_flick_cnt >= flick_time && u8flick_default_cup_state == SET )
    {
        gu8_default_cup_flick_cnt = 0;
        gu8_default_cup_flick_timer = 0;
        u8flick_default_cup_state = CLEAR;

        bit_default_cup_flick = CLEAR;
    }
    else{}

    return u8flick_default_cup_state;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_button_set_display( U8 mu8_mode )
{
    /*..hui [23-5-12오후 2:06:57] FND 표시 메인 화면에서만 표시..*/
    /*if( gu8_Led_Display_Step == LED_Display__MAIN )*/

    /*..hui [23-12-19오후 4:55:10] 온수 OFF -> 온수 선택 OFF표시중에 3초 누르고있으면 ON 표시안됨..*/
    if( gu8_Led_Display_Step == LED_Display__MAIN || gu8_Led_Display_Step == LED_Display__BUTTON_SET )
    {
        u8ButtonSetDisplay = mu8_mode;
        gu16_button_set_display_timer = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 button_set_display_timer( U8 flick_time )
{
    static U8 u8flick_button_state = 0;

    gu16_button_set_display_timer++;

    if( gu16_button_set_display_timer >= flick_time )
    {
        gu16_button_set_display_timer = 0;
        u8flick_button_state = CLEAR;

        u8ButtonSetDisplay = BUTTON_SET_DISPLAY_OFF;
    }
    else
    {
        u8flick_button_state = SET;
    }

    return u8flick_button_state;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_button_set_display( void )
{
    u8ButtonSetDisplay = BUTTON_SET_DISPLAY_OFF;
    gu16_button_set_display_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



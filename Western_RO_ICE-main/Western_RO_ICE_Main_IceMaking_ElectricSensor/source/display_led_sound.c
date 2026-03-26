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
#include    "display_led_sound.h"

void led_sound_setting(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_sound_setting(void)
{
    /*..hui [23-11-24오전 9:27:53] 정수+용량만 남기고 전부 OFF..*/
    Bit3_Front_Led_Ambient_Select = SET;
    Bit5_Front_Led_Amount_Select = SET;

    #if 0
    gu8_altitude_flick_timer++;

    if( gu8_altitude_flick_timer <= 5 )
    {
        Bit2_Front_Led_Hot_Select = SET;
    }
    else
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
    }

    if( gu8_altitude_flick_timer >= 10 )
    {
        gu8_altitude_flick_timer = 0;
    }
    else{}
    #endif

    ///funcition_led_output();
    ///temp_led_out();
    /*level_led_out();*/
    /*setting_led_out();*/
    /*extract_led_out();*/
    /*uv_led_out();*/
    /*steam_clean_led_out();*/

    /*icon_led_out();*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/








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
#include    "display_led_ct_mode.h"

void led_ct_filter_type_state(void);





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_ct_filter_type_state(void)
{
    /*..hui [24-2-19오후 1:45:39] 냉수 LED만 점등..*/
    Bit4_Front_Led_Cold_Select = SET;


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








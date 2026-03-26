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
#include    "display_led_sleep.h"


void led_sleep(void);
void led_all_lock(void);
void all_lock_setting_led(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_sleep(void)
{
    funcition_led_output();
    /*temp_led_out();*/
    //level_led_out();
    //setting_led_out();
    extract_led_out();
    //uv_led_out();
    //steam_clean_led_out();

    //icon_led_out();

    eco_icon_output();


    /*..hui [23-11-23오전 9:14:28] 변경된 UI 사양서에 WIFI 아이콘은 빠져있음..*/
    /*wifi_icon_output();*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_all_lock(void)
{
    all_lock_setting_led();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_lock_setting_led(void)
{
    U8 mu8_all_lock_flick_state = 0;

    if( Bit4_All_Lock_Indicator == CLEAR )
    {
        Bit3_Front_Led_Touch_Lock = SET;
    }
    else
    {
        /*mu8_all_lock_flick_state = all_lcok_flickering_timer(5, 5);*/
        mu8_all_lock_flick_state = all_lcok_flickering_timer(3, 5);

        if( mu8_all_lock_flick_state == SET )
        {
            Bit3_Front_Led_Touch_Lock = SET;
        }
        else
        {
            Bit3_Front_Led_Touch_Lock = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/











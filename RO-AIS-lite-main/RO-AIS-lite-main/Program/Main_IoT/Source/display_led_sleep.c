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


void display_sleep(void);
void save_icon_sleep(void);
void display_all_lock(void);
void all_lock_function_led(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_sleep(void)
{
    funcition_led_output();
    //temp_led_out();

    extract_led_out();
    /*set_led_duty( DUTY_OUT_ETC_ICON, DUTY_100_PERCENT);*/
    /*..sean [25-3-20 사양 정리] 취침모드일 때에 ..*/
    save_icon_sleep();

    set_led_duty( DUTY_OUT_ETC_ICON, DUTY_20_PERCENT);

    #if 0
    set_icon_duty( DIMMING__ICE_FULL, ICON_DIIMMING_10_PERCENT_ON );
    set_icon_duty( DIMMING__ICON_ICE_LOCK, ICON_DIIMMING_10_PERCENT_ON );
    set_icon_duty( DIMMING__ICON_HOT_LOCK, ICON_DIIMMING_10_PERCENT_ON );
    set_icon_duty( DIMMING__ICE_FIRST, ICON_DIIMMING_10_PERCENT_ON );
    #endif

    //ice_full_led_output();
    //ice_lock_icon_output();
    //hot_lock_icon_output();
    //ice_first_icon_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_icon_sleep(void)
{
    //set_icon_duty( DIMMING__ICON_SAVE, ICON_DIIMMING_10_PERCENT_ON );

	if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        /*set_duty_percent( DIMMING__PERCENT_ECCO_ICON, DIIMMING__10_PERCENT );*/
        /*set_duty_percent( DIMMING__PERCENT_ECCO_ICON, DIIMMING__100_PERCENT );*/
        set_icon_duty( DIMMING__ICON_SAVE, ICON_DIIMMING_10_PERCENT_ON );
    }
    else {}

    /*if( F_Save == SET )*/
    if( bit_sleep_mode_enable == SET )

    {
        Bit6_Front_Led_Icon_Save = SET;
    }
    else
    {
        Bit6_Front_Led_Icon_Save = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_all_lock(void)
{
    all_lock_function_led();
    /*all_lock_icon_output();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_lock_function_led(void)
{
    U8 mu8_all_lock_flick_state = 0;

    Bit0_Front_Led_Set_Select = CLEAR;
    set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);

    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit1_Front_Led_Ice_Select = CLEAR;
    set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_100_PERCENT);

    ///////////////////////////////////////////////////////////////////////////////////////////

    /*..hui [23-2-22오후 2:59:50] 버튼 누르면 온수, 정수 깜빡임..*/
    if( Bit4_All_Lock_Indicator == CLEAR )
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
        set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);

        Bit3_Front_Led_Ambient_Select = CLEAR;
        set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_100_PERCENT);
		
        Bit3_Front_Led_Ice_Extract = SET;
        set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
		
        Bit4_Front_Led_Water_Extract = SET;
        set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
    }
    else
    {
        mu8_all_lock_flick_state = all_lock_flick_timer(5, 5);

        if( mu8_all_lock_flick_state == SET )
        {
            Bit2_Front_Led_Hot_Select = SET;
            set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);

            Bit3_Front_Led_Ambient_Select = SET;
            set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
            set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);

            Bit3_Front_Led_Ambient_Select = CLEAR;
            set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_100_PERCENT);
        }
    }

    #if 0
    Bit2_Front_Led_Hot_Select = SET;
    set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_20_PERCENT);

    Bit3_Front_Led_Ambient_Select = SET;
    set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_20_PERCENT);
    #endif

    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit4_Front_Led_Cold_Select = CLEAR;
    set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);

    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit5_Front_Led_Amount_Select = CLEAR;
    set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_100_PERCENT);

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/











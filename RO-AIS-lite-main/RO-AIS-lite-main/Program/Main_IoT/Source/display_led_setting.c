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
#include    "display_led_setting.h"

void display_setting(void);
void setting_function_led(void);
void my_cup_led_out(void);
void display_altitude_setting(void);
void display_my_cup_setting(void);
void led_button_set(void);
void led_time_set(void);

U8 gu8_altitude_flick_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_setting(void)
{
    /*funcition_led_output();*/
    setting_function_led();
    //temp_led_out();
    //cup_level_led_out();
    extract_led_out();
    setting_led_out();


    set_led_duty( DUTY_OUT_ETC_ICON, DUTY_100_PERCENT);
    //ice_full_led_output();
    icon_led_out();

    /*..hui [23-4-4오후 2:49:10] 저수위일때 마이컵 설정 안되므로 저수위 표시 추가..*/
    low_water_led_out();

    //auto_drain_led_out();
    //uv_led_out();
    //percent_ml_led_out();
    my_cup_led_out();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_function_led(void)
{
    /*..hui [23-4-3오전 11:35:45] 마이컵 설정 중, 종료 표시중에는 Settings LED OFF..*/
    if( bit_my_cup_setting_start == SET || bit_my_cup_finish_flick == SET )
    {
        Bit0_Front_Led_Set_Select = CLEAR;
        set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
    }
    else
    {
        Bit0_Front_Led_Set_Select = SET;
        set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_IceOn == SET )
    {
        Bit1_Front_Led_Ice_Select = SET;
        set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_20_PERCENT);
    }
    else
    {
        Bit1_Front_Led_Ice_Select = CLEAR;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Hot_Enable == SET )
    {
        Bit2_Front_Led_Hot_Select = SET;
        set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_20_PERCENT);
    }
    else
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit3_Front_Led_Ambient_Select = SET;
    set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_20_PERCENT);
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Cold_Enable == SET )
    {
        Bit4_Front_Led_Cold_Select = SET;
        set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_20_PERCENT);
    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit5_Front_Led_Amount_Select = SET;
    set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_20_PERCENT);

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void my_cup_led_out(void)
{
    /*..hui [23-3-10오후 4:33:15] Set 표시 상태일때 항시 ON, OFF하면 FND에 OFF 깜빡이는동안 ON 유지..*/
    if( bit_my_cup_setting_start == SET || Bit3_My_Cup_Set_Display == SET )
    {
        Bit0_Front_Led_Cont = SET;
        set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
    }
    else
    {
        Bit0_Front_Led_Cont = CLEAR;
        set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);

    }

    #if 0
    /*..hui [23-3-3오후 3:56:07] 설정모드에서 마이컵 현재 상태 구분 어려움.. 현재상태 마이컵 폰트로 확인..*/
    if( bit_my_cup_enable == SET )
    {
        Bit0_Front_Led_Cont = SET;
        set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
    }
    else
    {
        Bit0_Front_Led_Cont = CLEAR;
        set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_altitude_setting(void)
{
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

    #if 0
    set_icon_duty( DIMMING__HOT_TEMP, ICON_DIIMMING_FULL_ON );


    switch( gu8AltitudeStep )
    {
        case ALTITUDE_1_MODE_HIGH:

            Bit0_Front_Led_Hot_Temp_1 = SET;
            Bit1_Front_Led_Hot_Temp_2 = CLEAR;
            Bit2_Front_Led_Hot_Temp_3 = CLEAR;

        break;

        case ALTITUDE_2_MODE_MID:

            Bit0_Front_Led_Hot_Temp_1 = SET;
            Bit1_Front_Led_Hot_Temp_2 = SET;
            Bit2_Front_Led_Hot_Temp_3 = CLEAR;

        break;

        case ALTITUDE_3_MODE_LOW:

            Bit0_Front_Led_Hot_Temp_1 = SET;
            Bit1_Front_Led_Hot_Temp_2 = SET;
            Bit2_Front_Led_Hot_Temp_3 = SET;

        break;

        default:

            Bit0_Front_Led_Hot_Temp_1 = SET;
            Bit1_Front_Led_Hot_Temp_2 = CLEAR;
            Bit2_Front_Led_Hot_Temp_3 = CLEAR;

        break;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_my_cup_setting(void)
{
    funcition_led_output();
    /*setting_function_led();*/
    temp_led_out();
    cup_level_led_out();
    extract_led_out();
    /*setting_led_out();*/


    set_led_duty( DUTY_OUT_ETC_ICON, DUTY_100_PERCENT);
    //ice_full_led_output();
    //icon_led_out();
    //low_water_led_out();
    //auto_drain_led_out();
    //uv_led_out();
    //percent_ml_led_out();

    /*..hui [23-2-23오후 7:16:46] FND 밑에 하단부만 켜짐..*/
    ice_full_led_output();
    ice_lock_icon_output();
    hot_lock_icon_output();
    ice_first_icon_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_button_set(void)
{
    /*..hui [24-4-24오후 7:13:00] 상단 아이콘은 전부 끄고 표시..*/
    funcition_led_output();
    temp_led_out();
    /*cup_level_led_out();*/
    extract_led_out();
    /*setting_led_out();*/


    /*..hui [23-2-10오후 2:45:03] 기타 아이콘들 흐리게 켜질떄 PWM..*/
    set_led_duty( DUTY_OUT_ETC_ICON, DUTY_100_PERCENT);

    ice_full_led_output();
    /*icon_led_out();*/
    ice_lock_icon_output();
    hot_lock_icon_output();
    /*all_lock_icon_output();*/
    /*save_icon_output();*/
    ice_first_icon_output();





    /*low_water_led_out();*/
    /*auto_drain_led_out();*/
    /*uv_led_out();*/
    /*percent_ml_led_out();*/


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void led_time_set(void)
{
    /*..hui [24-4-24오후 7:13:00] 상단 아이콘은 전부 끄고 표시..*/
    led_time_setting_state();
    /*temp_led_out();*/
    /*cup_level_led_out();*/
    /*extract_led_out();*/
    /*setting_led_out();*/
#if 0
    ice_full_led_output();
    /*icon_led_out();*/
    ice_lock_icon_output();
    hot_lock_icon_output();
    /*all_lock_icon_output();*/
    /*save_icon_output();*/
    ice_first_icon_output();
#endif
}










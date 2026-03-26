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

void led_setting(void);
void setting_function_led(void);
void led_button_set(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_setting(void)
{
    /*funcition_led_output();*/

    setting_function_led();
    /*temp_led_out();*/
    /*level_led_out();*/
    setting_led_out();
    /*extract_led_out();*/
    /*uv_led_out();*/

    ice_lock_icon_output();
    hot_lock_icon_output();
    ice_first_icon_output();
    eco_icon_output();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_function_led(void)
{
    /*..hui [23-5-12오후 3:39:45] 웨스턴 아이스는 설정모드에서 다른 버튼들 모두 OFF 하는걸로.. UI 사양서..*/
    Bit0_Front_Led_Set_Select = SET;
    Bit1_Front_Led_Ice_Select = CLEAR;
    Bit2_Front_Led_Hot_Select = CLEAR;
    Bit3_Front_Led_Ambient_Select = CLEAR;
    Bit4_Front_Led_Cold_Select = CLEAR;
    Bit5_Front_Led_Amount_Select = CLEAR;

    #if 0
    dimming_on_off_select( DIMMING__ON_OFF_ICE_SELECT,  DIIMMING_ON__10_PERCENT);
    dimming_on_off_select( DIMMING__ON_OFF_HOT_SELECT,  DIIMMING_ON__10_PERCENT);
    dimming_on_off_select( DIMMING__ON_OFF_AMBIENT_SELECT,  DIIMMING_ON__10_PERCENT);
    dimming_on_off_select( DIMMING__ON_OFF_COLD_SELECT,  DIIMMING_ON__10_PERCENT);
    dimming_on_off_select( DIMMING__ON_OFF_AMOUNT_SELECT,  DIIMMING_ON__10_PERCENT);


    Bit0_Front_Led_Set_Select = SET;

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_IceOn == SET )
    {
        Bit1_Front_Led_Ice_Select = SET;
    }
    else
    {
        Bit1_Front_Led_Ice_Select = CLEAR;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Hot_Enable == SET )
    {
        Bit2_Front_Led_Hot_Select = SET;
    }
    else
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit3_Front_Led_Ambient_Select = SET;
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Cold_Enable == SET )
    {
        Bit4_Front_Led_Cold_Select = SET;
    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    Bit5_Front_Led_Amount_Select = SET;
    #endif

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_button_set(void)
{
    /*..hui [23-5-12오후 2:45:42] 버튼 세팅(온수, 음소거) 화면 표시중에는 상단 모두 끄고 표시..*/
    funcition_led_output();
    /*temp_led_out();*/
    /*level_led_out();*/
    /*setting_led_out();*/
    extract_led_out();
    /*uv_led_out();*/

    /*icon_led_out();*/

    /*left_icon_led_output();*/
    /*right_icon_led_output();*/
    under_icon_led_output();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/











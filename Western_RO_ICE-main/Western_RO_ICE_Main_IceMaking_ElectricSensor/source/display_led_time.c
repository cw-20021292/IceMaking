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
#include    "display_led_time.h"

void led_time_setting_state(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_time_setting_state(void)
{
    Bit0_Front_Led_Set_Select = SET;
    Bit2_Front_Led_Hot_Select = SET;
    Bit4_Front_Led_Cold_Select = SET;

    /*..hui [23-9-15오후 1:18:39] 수동 살균 예약시간 설정 시 우선 스팀클린 표시로 구분..*/
    /*..hui [23-9-15오후 1:18:50] QS에 얘끼해놨음.. 나중에 확정되면 변경..*/
    if( gu8_time_setting_mode == CLEAN_RESERVE_TIME_SETTING_MODE )
    {
        Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_Tank_Clean_Text = CLEAR;
    }

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








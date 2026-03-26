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
#include    "display_led_memento.h"

void led_memento_state(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_memento_state(void)
{
    Bit5_Front_Led_Amount_Select = SET;


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








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
#include    "display_led_wifi.h"

void led_wifi_pairing(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_wifi_pairing(void)
{
    /*..hui [23-12-4오후 2:14:16] 페어링 화면에서는 wifi 아이콘이랑 퍼센트만 표시..*/
    wifi_icon_output();
    percent_oC_oF_icon_output();

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








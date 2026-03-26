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
#include    "display_led_filter_open.h"

void led_filter_open_state(void);
void led_filter_alarm_state(void);





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_filter_open_state(void)
{
    /*..hui [23-12-5오후 4:54:19] 사이드커버 열리면 물추출 LED 제외 전부 OFF..*/
    extract_led_out();


    /*wifi_icon_output();*/
    replace_filter_text_output();
    /*..hui [23-12-6오후 5:52:39] 필터 넘버 1,2,3 숫자 표시 추가..*/
    replace_filter_1_3_num_led_output();
    days_left_text_output();

    #if 0
    /*funcition_led_output();*/
    /*temp_led_out();*/
    /*level_led_out();*/
    /*setting_led_out();*/
    extract_led_out();
    /*uv_led_out();*/
    /*steam_clean_led_out();*/

    /*icon_led_out();*/

    /*water_usage_text_output();*/
    eco_icon_output();
    /*gal_text_output();*/

    replace_filter_text_output();
    wifi_icon_output();
    days_left_text_output();
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_filter_alarm_state(void)
{
    /*funcition_led_output();*/
    /*temp_led_out();*/
    /*level_led_out();*/
    /*setting_led_out();*/
    extract_led_out();
    /*uv_led_out();*/
    /*steam_clean_led_out();*/

    /*icon_led_out();*/

    //water_usage_text_output();
    //eco_icon_output();
    //gal_text_output();

    /*wifi_icon_output();*/
    replace_filter_text_output();
    /*..hui [23-12-6오후 5:52:39] 필터 넘버 1,2,3 숫자 표시 추가..*/
    replace_filter_1_3_num_led_output();
    days_left_text_output();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/








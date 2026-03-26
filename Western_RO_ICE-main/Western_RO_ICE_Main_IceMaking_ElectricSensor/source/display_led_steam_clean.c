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
#include    "display_led_steam_clean.h"

void led_steam_clean_state(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_steam_clean_state(void)
{
    /*..hui [23-12-15오후 2:15:22] 기능LED도 OFF.. 음성 추가되면서 사용할수없는데 선택되는게 이상해짐..*/
    /////////////////////////funcition_led_output();
    /*temp_led_out();*/
    /*level_led_out();*/
    /*..hui [24-1-8오후 5:50:25] UI 사양서에 표시안하는걸로 나와있음..*/
    /*cup_level_led_out();*/
    /*hot_level_led_out();*/



    /*setting_led_out();*/
    //////////extract_led_out();
    /*uv_led_out();*/
    /*..hui [24-1-9오후 3:08:32] 아이스탱크클린이랑 FND에 %만빼고 전부 OFF하는걸로..UI사양서에 나와있음..*/
    steam_clean_led_out();

    /*icon_led_out();*/
    /*eco_icon_output();*/
    /*..hui [23-5-23오후 7:21:10] 스팀살균중에는 Min / Left 제외하고 상단 LED 모드 끈다..*/
    percent_oC_oF_icon_output();
    ///////////wifi_icon_output();
    /*min_left_text_output();*/
    /*under_icon_led_output();*/


    #if 0
    /*..hui [23-12-15오후 2:15:22] 기능LED도 OFF.. 음성 추가되면서 사용할수없는데 선택되는게 이상해짐..*/
    /////////////////////////funcition_led_output();
    /*temp_led_out();*/
    /*level_led_out();*/
    /*..hui [24-1-8오후 5:50:25] UI 사양서에 표시안하는걸로 나와있음..*/
    /*cup_level_led_out();*/
    /*hot_level_led_out();*/



    /*setting_led_out();*/
    extract_led_out();
    /*uv_led_out();*/
    steam_clean_led_out();

    /*icon_led_out();*/
    eco_icon_output();
    /*..hui [23-5-23오후 7:21:10] 스팀살균중에는 Min / Left 제외하고 상단 LED 모드 끈다..*/
    percent_oC_oF_icon_output();
    wifi_icon_output();
    min_left_text_output();
    under_icon_led_output();
    #endif
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/








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
#include    "display_led_flushing.h"

void led_flushing_state(void);





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_flushing_state(void)
{
    /*..hui [23-6-8오후 4:38:40] 대기모드에서 필터플러싱 모드..*/
    /*..hui [23-6-8오후 4:38:52] 냉수 버튼으로 cancel 가능..*/
    if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
    {
        ///////if( gu8_filter_flushing_state == SET && bit_filter_flushing_no_cancel == CLEAR )
        if( bit_yes_no_popup == SET )
        {
            Bit4_Front_Led_Cold_Select = SET;
        }
        else
        {
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
    }

    extract_led_out();
    /*preparing_text_output();*/
    /*..hui [23-11-16오후 4:25:32] 필터플러싱 아이콘 추가..*/
    filter_flushing_text_output();
    percent_oC_oF_icon_output();

    wifi_icon_output();
    /*min_left_text_output();*/
    /*current_text_output();*/

    /*..hui [24-2-22오전 10:58:45] CT 모드일때는 플러싱 대기, 플러싱 진행중에도 Replace Filter, 교체된 필터 점멸로 표시..*/
    if( bit_ct_flushing_standby_start == SET || gu8_ct_forced_flushing_start == SET )
    {
        replace_filter_text_output();
        replace_filter_1_3_num_led_output();
    }
    else{}


    ///funcition_led_output();
    ///temp_led_out();
    /*level_led_out();*/
    /*setting_led_out();*/
    ////extract_led_out();
    /*uv_led_out();*/
    ///steam_clean_led_out();

    /*icon_led_out();*/
    /*..hui [23-5-23오후 7:21:10] 스팀살균중에는 Min / Left 제외하고 상단 LED 모드 끈다..*/
    ///percent_oC_oF_icon_output();

    ////min_left_text_output();
    ////under_icon_led_output();
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/








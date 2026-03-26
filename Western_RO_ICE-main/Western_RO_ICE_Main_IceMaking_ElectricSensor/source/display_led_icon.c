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
#include    "display_led_icon.h"

void icon_led_out(void);
void left_icon_led_output(void);
void preparing_text_output(void);
void current_text_output(void);
void filter_flushing_text_output(void);
//void water_usage_text_output(void);
void eco_icon_output(void);
void percent_oC_oF_icon_output(void);
//void gal_text_output(void);
void right_icon_led_output(void);
void replace_filter_text_output(void);
void replace_filter_1_3_num_led_output(void);
void wifi_icon_output(void);
void oz_ml_icon_output(void);
void min_left_text_output(void);
void days_left_text_output(void);
void under_icon_led_output(void);
void ice_full_led_output(void);
void ice_lock_icon_output(void);
void hot_lock_icon_output(void);
void ice_first_icon_output(void);
void making_text_led_output(void);
void heating_text_led_output(void);
void cooling_text_led_output(void);
void low_water_led_output(void);
void wifi_pairing_display(void);

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void icon_led_out(void)
{
    left_icon_led_output();
    right_icon_led_output();
    under_icon_led_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void left_icon_led_output(void)
{
    preparing_text_output();
    current_text_output();
    /*water_usage_text_output();*/
    eco_icon_output();
    filter_flushing_text_output();
    percent_oC_oF_icon_output();
    /*gal_text_output();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void preparing_text_output(void)
{

    if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        /*..hui [23-8-18오전 11:26:43] 얼음 추출중에는 끈다..*/
        Bit0_Front_Left_Led_Preparing_Text = CLEAR;
    }
    else if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( F_WaterOut == SET )
        {
            /*..hui [23-11-27오후 3:39:33] 프리페어링이 필요할때 물 추출할때는 OFF..*/
            Bit0_Front_Left_Led_Preparing_Text = CLEAR;
        }
        else if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_ON )
        {
            Bit0_Front_Left_Led_Preparing_Text = SET;
        }
        else /*if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_OFF )*/
        {
            Bit0_Front_Left_Led_Preparing_Text = CLEAR;
        }
    }
    else
    {
        Bit0_Front_Left_Led_Preparing_Text = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void current_text_output(void)
{
    if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        /*..hui [23-8-18오전 11:26:43] 얼음 추출중에는 끈다..*/
        Bit1_Front_Left_Led_Current_Text = CLEAR;
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        if( gu8_cooling_display_mode == COOLING_DISPLAY_1_ON )
        {
            /*..hui [23-11-17오후 12:06:13] 냉각중이 아니라.. 냉각이 필요한 상태..*/
            Bit1_Front_Left_Led_Current_Text = SET;
        }
        else
        {
            /*..hui [23-11-17오후 12:06:38] 충분히 차가울 정도로 냉각이 완료된상태..*/
            Bit1_Front_Left_Led_Current_Text = CLEAR;
        }
    }
    else if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( F_WaterOut == SET )
        {
            if( bit_hot_current_temp_on == SET )
            {
                Bit1_Front_Left_Led_Current_Text = SET;
            }
            else
            {
                Bit1_Front_Left_Led_Current_Text = CLEAR;
            }
        }
        else
        {
            Bit1_Front_Left_Led_Current_Text = CLEAR;
        }
    }
    else
    {
        Bit1_Front_Left_Led_Current_Text = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_flushing_text_output(void)
{

    /*..hui [23-6-2오후 12:01:22] 플러싱중에 점등..*/
    if( gu8_flushing_mode == FLUSHING_STANDBY_STATE || bit_flushing_halt == SET )
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = CLEAR;
    }
    else if( gu8_flushing_mode > FLUSHING_STANDBY_STATE )
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = SET;
    }
    else
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void water_usage_text_output(void)
{
    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
        && bit_filter_all == CLEAR )
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = SET;
    }
    else
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = CLEAR;
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eco_icon_output(void)
{
    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        /*set_duty_percent( DIMMING__PERCENT_ECCO_ICON, DIIMMING__10_PERCENT );*/
        /*set_duty_percent( DIMMING__PERCENT_ECCO_ICON, DIIMMING__100_PERCENT );*/
        set_duty_percent( DIMMING__PERCENT_ECCO_ICON, DIIMMING__20_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_ECCO_ICON, TOP_ICON__DIMMING__50_PERCENT );
    }

    /*..hui [23-3-2오후 7:14:46] 나중에 다시..*/
    //Bit3_Front_Left_Led_Eco_Icon = CLEAR;
    //return;

    /*if( F_Save == SET )*/
    if( bit_sleep_mode_enable == SET )
    {
        Bit3_Front_Left_Led_Eco_Icon = SET;
    }
    else
    {
        Bit3_Front_Left_Led_Eco_Icon = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void percent_oC_oF_icon_output(void)
{
    /*..hui [23-6-2오후 12:01:22] 플러싱중에 점등..*/
    /*..hui [23-6-5오전 10:30:55] 플러싱 중단하고 밸브 끄는시간 1초동안 디스플레이 off..*/
    if( (gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode == FLUSHING_STANDBY_STATE)
        || bit_flushing_halt == SET )
    {
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode > FLUSHING_STANDBY_STATE )
    {
        Bit5_Front_Left_Led_Percent_Icon = SET;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( bit_self_test_start == SET )
    {
        Bit5_Front_Left_Led_Percent_Icon = SET;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        if( bit_display_wifi_error == SET || bit_display_last_error == SET )
        {
            Bit5_Front_Left_Led_Percent_Icon = CLEAR;
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
            Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
        }
        else
        {
            /*..hui [23-12-4오후 2:14:01] 페어링 단계 표시화면에서는 퍼센트만 표시..*/
            Bit5_Front_Left_Led_Percent_Icon = SET;
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
            Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
        }
    }
    else if( gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__ERROR )
    {
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__STEAM_CLEAN )
    {
        Bit5_Front_Left_Led_Percent_Icon = SET;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__UV )
    {
        /*..hui [23-6-1오후 3:27:53] UV 진행률 표시..*/
        Bit5_Front_Left_Led_Percent_Icon = SET;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
    else
    {
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;

        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = SET;
            Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
        }
        else
        {
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
            Bit6_Front_Left_Led_Celcius_oC_Icon = SET;
        }
    }





}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void gal_text_output(void)
{
    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
        && bit_filter_all == CLEAR )
    {
        Bit7_Front_Left_Led_Gal_Icon = SET;
    }
    else
    {
        Bit7_Front_Left_Led_Gal_Icon = CLEAR;
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void right_icon_led_output(void)
{
    replace_filter_text_output();
    /*..hui [23-12-6오후 5:52:39] 필터 넘버 1,2,3 숫자 표시 추가..*/
    replace_filter_1_3_num_led_output();
    wifi_icon_output();
    oz_ml_icon_output();
    min_left_text_output();
    days_left_text_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void replace_filter_text_output(void)
{
    if( bit_ct_flushing_standby_start == SET || gu8_ct_forced_flushing_start == SET )
    {
        Bit4_Front_New_Led_Replace_Filter_Text = F_Wink_500ms;
    }
    else if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
            && bit_filter_all == CLEAR
            && bit_filter_alarm_start == SET )
    {
        Bit4_Front_New_Led_Replace_Filter_Text = SET;
    }
    /*else if( gu8_Led_Display_Step == LED_Display__FILTER_ALARM
        && bit_filter_alarm_start == SET )*/
    else if( bit_filter_alarm_start == SET )
    {
        Bit4_Front_New_Led_Replace_Filter_Text = SET;
    }
    else
    {
        Bit4_Front_New_Led_Replace_Filter_Text = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void replace_filter_1_3_num_led_output(void)
{
    if( bit_ct_flushing_standby_start == SET || gu8_ct_forced_flushing_start == SET )
    {
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

        #if 0
        Bit5_Front_New_Led_Replace_Filter_1_Num = Bit0_Neo_Filter_1_Reset_State & F_Wink_500ms;
        Bit6_Front_New_Led_Replace_Filter_2_Num = Bit1_Ro_Filter_2_Reset_State & F_Wink_500ms;
        Bit7_Front_New_Led_Replace_Filter_3_Num = Bit2_Ino_Filter_3_Reset_State & F_Wink_500ms;
        #endif

        Bit5_Front_New_Led_Replace_Filter_1_Num = Bit0_CT_Neo_Filter_1_Replace & F_Wink_500ms;
        Bit6_Front_New_Led_Replace_Filter_2_Num = Bit1_CT_Ro_Filter_2_Replace & F_Wink_500ms;
        Bit7_Front_New_Led_Replace_Filter_3_Num = Bit2_CT_Ino_Filter_3_Replace & F_Wink_500ms;
    }
    else if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
        && bit_filter_all == CLEAR
        && bit_filter_alarm_start == SET )
    {
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, DIIMMING__10_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
        }
    }
    else if( bit_filter_alarm_start == SET )
    {
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, DIIMMING__10_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, TOP_ICON__DIMMING__50_PERCENT );
            set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
        }
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );

        Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
        Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_icon_output(void)
{
    /*..hui [24-3-27오후 6:49:17] 화이트, 블루 퍼센트가 분리되어 아래쪽으로 이동..*/
    #if 0
    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        /*set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, DIIMMING__10_PERCENT );*/
        /*set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, DIIMMING__100_PERCENT );*/
        /*set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, DIIMMING__20_PERCENT );*/
        set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, DIIMMING__10_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, TOP_ICON__DIMMING__50_PERCENT );
    }
    #endif

    if( gu8_Wifi_Connect_State == WIFI_OFF )
    {
        Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        gu8_wifi_disp_timer = 0;
        gu16_wifi_pairing_30min_timer = 0;
        gu8_wifi_pairing_5sec_timer = 0;
        bit_pairing_5s_display_start = CLEAR;
    }
    else if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        gu8_wifi_disp_timer = 0;
        gu16_wifi_pairing_30min_timer = 0;
        gu8_wifi_pairing_5sec_timer = 0;
        bit_pairing_5s_display_start = CLEAR;
    }
    else /*if( gu8_Wifi_Connect_State == WIFI_DISCONNECT )*/
    {
        gu8_wifi_disp_timer++;

        if( gu8_wifi_disp_timer >= 10 )
        {
            gu8_wifi_disp_timer = 0;
        }
        else{}

        if( gu8_wifi_ap_mode == SET || gu8_ble_ap_mode == SET )
        {
            if( bit_install_flushing_state == SET )
            {
                /*..hui [24-8-6오전 9:49:17] 설치 플러싱중에는 끝날때까지 정상 표시..*/
                gu16_wifi_pairing_30min_timer = 0;
                gu8_wifi_pairing_5sec_timer = 0;
                bit_pairing_5s_display_start = CLEAR;
                wifi_pairing_display();
            }
            else
            {
                gu16_wifi_pairing_30min_timer++;

                if( gu16_wifi_pairing_30min_timer >= WIFI_PAIRING_START_30_MIN )
                {
                    /*..hui [24-8-6오전 9:50:14] 정상모드에서 30분동안 표시 후 OFF 표시..*/
                    gu16_wifi_pairing_30min_timer  = WIFI_PAIRING_START_30_MIN;

                    if( bit_pairing_5s_display_start == SET && gu8_Led_Display_Step != LED_Display__WATER_EXTRACT )
                    {
                        gu8_wifi_pairing_5sec_timer++;

                        /*..hui [24-8-6오전 9:58:42] 물 추출 종료되고 5초 동안 표시..*/
                        if( gu8_wifi_pairing_5sec_timer >= 50 )
                        {
                            gu8_wifi_pairing_5sec_timer = 0;
                            bit_pairing_5s_display_start = CLEAR;
                        }
                        else{}

                        wifi_pairing_display();
                    }
                    else
                    {
                        Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
                        Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
                        gu8_wifi_disp_timer = 0;
                        gu8_wifi_pairing_5sec_timer = 0;
                    }
                }
                else
                {
                    gu8_wifi_pairing_5sec_timer = 0;
                    bit_pairing_5s_display_start = CLEAR;
                    wifi_pairing_display();
                }
            }
        }
        else
        {
            gu16_wifi_pairing_30min_timer = 0;
            gu8_wifi_pairing_5sec_timer = 0;
            bit_pairing_5s_display_start = CLEAR;

            if( gu8_wifi_disp_timer >= 5 )
            {
                Bit1_Front_Right_Led_Wifi_Icon_White = SET;
                Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }
            else
            {
                Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }
        }
    }

    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, DIIMMING__20_PERCENT );
        set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, DIIMMING__20_PERCENT );
    }
    else
    {
        if( Bit1_Front_Right_Led_Wifi_Icon_White == SET && Bit2_Front_Right_Led_Wifi_Icon_Blue == SET )
        {
            /*..hui [24-3-27오후 7:32:46] 기존 블루만 켜지는 조건.. 화이트도 10%로 같이켜줌..*/
            set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, WIFI_BLUE_WITH_WHITE_LED_10_PERCENT );
            set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, WIFI_BLUE_LED_100_PERCENT );
        }
        else if( Bit1_Front_Right_Led_Wifi_Icon_White == SET && Bit2_Front_Right_Led_Wifi_Icon_Blue == CLEAR )
        {
            set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, WIFI_WHITE_LED_70_PERCENT );
            set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, WIFI_BLUE_LED_100_PERCENT );
        }
        else if( Bit1_Front_Right_Led_Wifi_Icon_White == CLEAR && Bit2_Front_Right_Led_Wifi_Icon_Blue == SET )
        {
            set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, WIFI_WHITE_LED_70_PERCENT );
            set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, WIFI_BLUE_LED_100_PERCENT );
        }
        else
        {
            set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, WIFI_WHITE_LED_70_PERCENT );
            set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, WIFI_BLUE_LED_100_PERCENT );
        }
    }


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_pairing_display(void)
{
    /*..hui [23-6-14오전 9:34:53] BLE일 경우 BLUE..*/
    if( gu8_ble_ap_mode == SET )
    {
        /*Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;*/

        if( gu8_wifi_disp_timer == 0 )
        {
            /*..hui [24-3-27오후 7:31:20] 블루 켤떄 화이트 10%로 같이 켜줌..디자ㅣㄴ..*/
            Bit2_Front_Right_Led_Wifi_Icon_Blue = SET;
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            /*..hui [24-3-27오후 7:31:20] 블루 켤떄 화이트 10%로 같이 켜줌..디자ㅣㄴ..*/
            Bit2_Front_Right_Led_Wifi_Icon_Blue = SET;
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else
        {
            Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
    }
    else
    {
        Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;

        if( gu8_wifi_disp_timer == 0 )
        {
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        }
        else
        {
            Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void oz_ml_icon_output(void)
{
    /*if( F_WaterOut == SET && u8Extract_Continue == SET )*/
    if( F_WaterOut == SET )
    {
        /*..hui [23-5-11오후 4:20:58] 물 추출할땐 켜고 연속 추출할땐 끄고..*/
        if( u8Extract_Continue == CLEAR )
        {
            if( gu8_ml__oz_select == Oz_SELECT )
            {
                Bit3_Front_Right_Led_OZ_Text = SET;
                Bit5_Front_Right_Led_ml_Text = CLEAR;
            }
            else
            {
                Bit3_Front_Right_Led_OZ_Text = CLEAR;
                Bit5_Front_Right_Led_ml_Text = SET;
            }
        }
        else
        {
            Bit3_Front_Right_Led_OZ_Text = CLEAR;
            Bit5_Front_Right_Led_ml_Text = CLEAR;

        }
    }
    else if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        /*..hui [23-5-11오후 3:55:08] 얼음 추출할때는 끈다..*/
        Bit3_Front_Right_Led_OZ_Text = CLEAR;
        Bit5_Front_Right_Led_ml_Text = CLEAR;
    }
    else
    {
        /*..hui [23-8-16오전 10:41:24] 연속이 메뉴속으로 추가.....*/
        if( gu8Cup_level == CUP_LEVEL__CONTINUE )
        {
            Bit3_Front_Right_Led_OZ_Text = CLEAR;
            Bit5_Front_Right_Led_ml_Text = CLEAR;
        }
        else
        {
            if( gu8_ml__oz_select == Oz_SELECT )
            {
                Bit3_Front_Right_Led_OZ_Text = SET;
                Bit5_Front_Right_Led_ml_Text = CLEAR;
            }
            else
            {
                Bit3_Front_Right_Led_OZ_Text = CLEAR;
                Bit5_Front_Right_Led_ml_Text = SET;
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void min_left_text_output(void)
{
    /*..hui [23-6-2오후 12:01:22] 플러싱중에 점등..*/
    if( (gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode == FLUSHING_STANDBY_STATE)
        || bit_flushing_halt == SET )
    {
        Bit4_Front_Right_Led_Min_Left_Text = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode > FLUSHING_STANDBY_STATE )
    {
        /*..hui [23-8-21오후 3:23:16] 플러싱할때도 %로만 표시하도록 변경됨..*/
        Bit4_Front_Right_Led_Min_Left_Text = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__UV )
    {
        Bit4_Front_Right_Led_Min_Left_Text = SET;
    }
    else
    {
        Bit4_Front_Right_Led_Min_Left_Text = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void days_left_text_output(void)
{
    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
        && bit_filter_all == CLEAR
        && bit_filter_alarm_start == SET )
    {
        Bit6_Front_Right_Led_Days_Left_Text = SET;
    }
    else if( gu8_Led_Display_Step == LED_Display__FILTER_ALARM
        && bit_filter_alarm_start == SET )
    {
        Bit6_Front_Right_Led_Days_Left_Text = SET;
    }
    else
    {
        Bit6_Front_Right_Led_Days_Left_Text = CLEAR;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void under_icon_led_output(void)
{
    ice_full_led_output();
    ice_lock_icon_output();
    hot_lock_icon_output();
    ice_first_icon_output();

    making_text_led_output();
    heating_text_led_output();
    cooling_text_led_output();
    low_water_led_output();
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full_led_output(void)
{
    if( F_IceFull == SET )
    {
        Bit5_Front_Under_Led_Ice_Full = SET;
    }
    else
    {
        Bit5_Front_Under_Led_Ice_Full = CLEAR;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_lock_icon_output(void)
{
    if( F_Ice_Lock == SET )
    {
        Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
    }
    else
    {
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_lock_icon_output(void)
{
    if( F_Hot_Lock == SET )
    {
        Bit2_Front_Under_Icon_Led_Hot_Lock = SET;
    }
    else
    {
        Bit2_Front_Under_Icon_Led_Hot_Lock = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_first_icon_output(void)
{

    #if 0
    if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
    {
        Bit0_Front_Under_Txt_Led_Ice_First = SET;
    }
    else
    {
        Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
    }
    #endif


    /*..hui [24-2-21오후 2:38:24] 얼음 OFF하면 아이스퍼스트도 OFF하도록..*/
    /*..hui [24-2-21오후 2:38:34] 단, 설정모드 진입시에는 설정상태에 따라 보여줘야함..*/
    if( bit_setting_mode_start == CLEAR )
    {
        if( F_IceOn == SET )
        {
            if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
            {
                Bit0_Front_Under_Txt_Led_Ice_First = SET;
            }
            else
            {
                Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
            }
        }
        else
        {
            Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
        }
    }
    else
    {
        if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
        {
            Bit0_Front_Under_Txt_Led_Ice_First = SET;
        }
        else
        {
            Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
        }
    }




}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void making_text_led_output(void)
{
    if( F_IceOn == CLEAR )
    {
        /*..hui [23-11-10오후 2:12:18] making off..*/
        Bit0_Front_New_Led_Ice_Making_Text = CLEAR;
    }
    else if( Bit2_Room_Temp_Open_Short_Error__E42 == SET
             /*|| Bit18_Tray_In_Temp_Open_Short_Error__E41 == SET*/
             || Bit1_Room_OverHeat_Error__E49 == SET
             || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
             || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
             || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET

             || Bit16_Drain_Pump_Error__E60 == SET
             || Bit4_Room_Low_Water_Level_Error__E21 == SET

             /*..hui [23-9-20오전 9:24:23] 둘 다 고장..*/
             || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
             /*|| Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET*/

             || Bit3_Leakage_Sensor_Error__E01 == SET

             || Bit7_BLDC_Communication_Error__E27 == SET
             || bit_bldc_operation_error_total == SET )
    {
        /*..hui [23-12-22오후 4:38:00] 얼음 만들수 없는 조건 에러 걸렸을때.. 인식..*/
        Bit0_Front_New_Led_Ice_Making_Text = CLEAR;
    }
    else if( F_IceFull == CLEAR )
    {
        /*..hui [20-1-28오후 4:10:16] 제빙 중..*/
        /*..hui [23-11-17오후 12:04:48] 제빙 중 -> 제빙이 필요한 상태..*/
        Bit0_Front_New_Led_Ice_Making_Text = SET;
    }
    else
    {
        /*..hui [20-1-28오후 4:10:22] 표시 없음..*/
        /*..hui [23-11-17오후 12:04:56] 만빙이랑 반대로 동작..*/
        Bit0_Front_New_Led_Ice_Making_Text = CLEAR;
    }

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void heating_text_led_output(void)
{
    if( gu8_heating_display_mode == HEATING_DISPLAY_2_ON )
    {
        /*..hui [23-11-27오후 2:26:18] 히팅이 필요한 상태..*/
        Bit1_Front_New_Led_Hot_Heating_Text = SET;
    }
    else
    {
        /*..hui [24-2-21오전 10:05:34] 92도일때.. Heating은 꺼져있는데 온수 선택시 Preparing은 켜져있는 구간 발생..*/
        /*..hui [24-2-21오전 10:05:55] 온수 선택했을때는 Heating OFF 조건이더라도 Preparing이 ON돼있으면 같이 켜도록 수정..*/
        /*..hui [24-2-21오전 10:06:02] 단, 에러 조건이 최우선..*/
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( gu8_heating_display_mode == HEATING_DISPLAY_0_INIT )
            {
                Bit1_Front_New_Led_Hot_Heating_Text = CLEAR;
            }
            else
            {
                if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_ON )
                {
                    Bit1_Front_New_Led_Hot_Heating_Text = SET;
                }
                else
                {
                    Bit1_Front_New_Led_Hot_Heating_Text = CLEAR;
                }
            }
        }
        else
        {
            /*..hui [23-11-27오후 2:26:27] 충분히 뜨거울 정도로 히팅이 완료된상태..*/
            Bit1_Front_New_Led_Hot_Heating_Text = CLEAR;
        }
    }


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cooling_text_led_output(void)
{

    if( gu8_cooling_display_mode == COOLING_DISPLAY_1_ON )
    {
        /*..hui [23-11-17오후 12:06:13] 냉각중이 아니라.. 냉각이 필요한 상태..*/
        Bit2_Front_New_Led_Cold_Cooling_Text = SET;
    }
    else
    {
        /*..hui [23-11-17오후 12:06:38] 충분히 차가울 정도로 냉각이 완료된상태..*/
        Bit2_Front_New_Led_Cold_Cooling_Text = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void low_water_led_output(void)
{
    U8 mu8_low_water_flick_state = 0;

    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        if( Bit5_Low_Water_Indicator == CLEAR )
        {
            Bit3_Front_New_Led_Low_Water_Text = SET;
        }
        else
        {
            mu8_low_water_flick_state = low_water_flickering_timer(3, 5);

            if( mu8_low_water_flick_state == SET )
            {
                Bit3_Front_New_Led_Low_Water_Text = SET;
            }
            else
            {
                Bit3_Front_New_Led_Low_Water_Text = CLEAR;
            }
        }
    }
    else
    {
        Bit3_Front_New_Led_Low_Water_Text = CLEAR;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



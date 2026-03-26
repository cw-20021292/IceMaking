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
#include    "display_main.h"


void led_display(void);
void init_water_extract_display(void);
void init_ice_extract_display(void);
void ice_disp_key_check(void);

bit bit_ice_disp_pause;
U8  gu8_ice_disp_pause_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_display(void)
{
    U8 mu8_return = 0;
    static LED_STEP before_display;

    gu8_animation_time = BREATH_ANIMATION_TIME;
    gu8_animation_duty = BREATH_ANIMATION_DUTY;

    /*..hui [23-5-25오후 3:18:14] 디밍 애니메이션..*/
    breath_control();

    switch( gu8_Led_Display_Step )
    {
        case LED_Display__VERSION:

            if( before_display == LED_Display__VERSION
                || before_display > LED_Display__VERSION )
            {
                before_display = LED_Display__VERSION;
                //all_dimming_full_on();
            }
            else{}

            display_version();

            break;

        case LED_Display__FOTA_START:

            if( before_display != LED_Display__FOTA_START )
            {
                before_display = LED_Display__FOTA_START;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            off_all_control_led();
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;

            break;

        case LED_Display__SELF_TEST:

            if( before_display != LED_Display__SELF_TEST )
            {
                before_display = LED_Display__SELF_TEST;
                off_all_control_led();
            }
            else{}

            led_self_test_state();
            fnd_left_self_test_state();
            fnd_right_self_test_state();

            break;

        case LED_Display__ACID_CLEAN:

            if( before_display != LED_Display__ACID_CLEAN )
            {
                before_display = LED_Display__ACID_CLEAN;
                off_all_control_led();
            }
            else{}

            led_acid();
            fnd_left_acid();
            fnd_right_acid();

            break;

        case LED_Display__FILTER_COVER_OPEN:

            if( before_display != LED_Display__FILTER_COVER_OPEN )
            {
                before_display = LED_Display__FILTER_COVER_OPEN;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_filter_open_state();
            fnd_left_filter_open_state();
            fnd_right_filter_open_state();

            break;

        case LED_Display__FLUSHING:

            if( before_display != LED_Display__FLUSHING )
            {
                before_display = LED_Display__FLUSHING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_flushing_state();
            fnd_left_flushing_state();
            fnd_right_flushing_state();

            break;

        case LED_Display__ALL_LOCK:

            if( before_display != LED_Display__ALL_LOCK )
            {
                before_display = LED_Display__ALL_LOCK;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_all_lock();
            fnd_left_all_lock();
            fnd_right_all_lock();

            break;

        case LED_Display__ALTITUDE_SETTING:

            if( before_display != LED_Display__ALTITUDE_SETTING )
            {
                before_display = LED_Display__ALTITUDE_SETTING;
                off_all_control_led();
                //all_dimming_full_on();
                gu8_altitude_flick_timer = 0;
            }
            else{}

            led_altitude_setting();
            fnd_left_altitude_setting();
            fnd_right_altitude_setting();

            break;

        case LED_Display__SOUND_SETTING:

            if( before_display != LED_Display__SOUND_SETTING )
            {
                before_display = LED_Display__SOUND_SETTING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_sound_setting();
            fnd_left_sound_setting();
            fnd_right_sound_setting();

            break;

        case LED_Display__MEMENTO:

            if( before_display != LED_Display__MEMENTO )
            {
                before_display = LED_Display__MEMENTO;
                off_all_control_led();
            }
            else{}

            led_memento_state();
            fnd_left_memento();
            fnd_right_memento();

            break;

        case LED_Display__CT_FILTER_TYPE:

            if( before_display != LED_Display__CT_FILTER_TYPE )
            {
                before_display = LED_Display__CT_FILTER_TYPE;
                off_all_control_led();
            }
            else{}

            led_ct_filter_type_state();
            fnd_left_ct_filter_type();
            fnd_right_ct_filter_type();

            break;

        case LED_Display__WATER_EXTRACT:

            if( before_display != LED_Display__WATER_EXTRACT )
            {
                before_display = LED_Display__WATER_EXTRACT;
                off_all_control_led();
                //all_dimming_full_on();
                init_water_extract_display();
                /////gu8_Fahrenheit_temp_old = 0;
            }
            else{}

            led_normal_state();
            fnd_left_normal_state();
            fnd_right_water_out();

            break;


        case LED_Display__ICE_EXTRACT:

            if( before_display != LED_Display__ICE_EXTRACT )
            {
                before_display = LED_Display__ICE_EXTRACT;
                off_all_control_led();
                //all_dimming_full_on();

                init_ice_extract_display();
                bit_return_ice = CLEAR;
                init_water_extract_display();
            }
            else{}

            led_normal_state();
            fnd_left_ice_out();
            fnd_right_ice_out();

            #if 0
            if( F_WaterOut == SET )
            {
                /*..hui [23-5-11오후 2:34:58] 얼음 추출중 물 추출..*/
                fnd_right_water_out();
                bit_return_ice = SET;
            }
            else
            {
                init_water_extract_display();
                fnd_right_ice_out();
            }
            #endif

            break;

        case LED_Display__FILTER_ALARM:

            if( before_display != LED_Display__FILTER_ALARM )
            {
                before_display = LED_Display__FILTER_ALARM;
                off_all_control_led();
                //all_dimming_full_on();

                gu8_filter_alarm_dsp_timer = 0;
                gu16_filter_alarm_flick_timer = 0;
                gu8_filter_alarm_flick_cnt = 0;
                bit_filter_alarm_display_finish = 0;

                /*..hui [24-1-10오후 3:32:10] 필터 교체 알람 음성 출력.. 물 추출 종료될때 최초 1회..*/
                play_voice_replace_filter();
            }
            else{}

            led_filter_alarm_state();
            fnd_left_filter_alarm_state();
            fnd_right_filter_alarm_state();

            break;

        case LED_Display__STEAM_CLEAN:

            if( before_display != LED_Display__STEAM_CLEAN )
            {
                before_display = LED_Display__STEAM_CLEAN;
                off_all_control_led();
                //all_dimming_full_on();
                gu8_steam_clean_level_timer = 0;
                bit_steam_clean_level_flick = CLEAR;
            }
            else{}

            led_steam_clean_state();
            fnd_left_steam_clean_state();
            fnd_right_steam_clean_state();

            break;

        case LED_Display__SETTING:

            if( before_display != LED_Display__SETTING )
            {
                before_display = LED_Display__SETTING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_setting();
            fnd_left_setting();
            fnd_right_setting();

            break;

        case LED_Display__TIME_SETTING:

            if( before_display != LED_Display__TIME_SETTING )
            {
                before_display = LED_Display__TIME_SETTING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_time_setting_state();
            fnd_left_time_setting_state();
            fnd_right_time_setting_state();

            break;


        case LED_Display__BUTTON_SET:

            if( before_display != LED_Display__BUTTON_SET )
            {
                before_display = LED_Display__BUTTON_SET;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_button_set();
            fnd_left_button_set();
            fnd_right_button_set();

            break;

        case LED_Display__SLEEP:

            if( before_display != LED_Display__SLEEP )
            {
                before_display = LED_Display__SLEEP;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_sleep();
            fnd_left_sleep();
            fnd_right_sleep();

            break;

        case LED_Display__ERROR:

            if( before_display != LED_Display__ERROR )
            {
                before_display = LED_Display__ERROR;
                off_all_control_led();
                gu8_error_flick_timer = 0;
                gu8_error_flick_cnt = 0;
                bit_error_display_finish = CLEAR;
            }
            else{}

            led_error_state();
            fnd_left_error();
            fnd_right_error();

            break;

        case LED_Display__UV:

            if( before_display != LED_Display__UV )
            {
                before_display = LED_Display__UV;
                off_all_control_led();
                gu16_uv_percent_flick_timer = 0;
                gu16_uv_time_flick_timer = 0;
                bit_uv_display_finish = CLEAR;
            }
            else{}

            led_uv_state();
            fnd_left_uv();
            fnd_right_uv();

            break;

        case LED_Display__WIFI_PAIRING:

            if( before_display != LED_Display__WIFI_PAIRING )
            {
                before_display = LED_Display__WIFI_PAIRING;
                off_all_control_led();

                u8PairingStep = 0;
                gu8_pairing_finish_timer = 0;

                bit_display_wifi_error = CLEAR;

                #if 0
                if( gu8_Wifi_Last_Error != 0 )
                {
                    bit_display_last_error = SET;
                }
                else{}
                #endif
            }
            else{}

            //led_wifi_pairing();
            fnd_left_wifi_pairing();
            fnd_right_wifi_pairing();
            led_wifi_pairing();

            break;

        case LED_Display__DEBUG:

            if( before_display != LED_Display__DEBUG )
            {
                before_display = LED_Display__DEBUG;
            }
            else{}

            led_normal_state();
            fnd_debug();

            break;

        case LED_Display__MAIN:

            if( before_display != LED_Display__MAIN )
            {
                before_display = LED_Display__MAIN;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_normal_state();
            fnd_left_normal_state();
            fnd_right_normal_state();

            break;

        default:

            gu8_Led_Display_Step = LED_Display__VERSION;

            break;
    }


    /*..hui [23-2-8오후 1:58:51] 에러 발생상태일 경우 얼음추출, 물 추출 후 에러 화면 표시..*/
    /*if( gu8_Led_Display_Step == LED_Display__WATER_EXTRACT
        || gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )*/
    /*..hui [23-6-23오후 12:05:50] 물 추출후에만 ..*/
    /*..hui [23-6-23오후 12:06:16] UV 살균 - 얼음추출하면 정지됨 - 추출모터 들어가고 다시 시작 - 표시할수없음..*/
    /*..hui [23-6-23오후 12:06:30] 탑커버 열렸을때도 마찬가지.. 열리면 OFF..*/
    if( gu8_Led_Display_Step == LED_Display__WATER_EXTRACT )
    {
        /*..hui [23-6-8오후 12:32:39] 우선순위. 1 에러안내 2 소모품 교체 3 UV 살균..*/
        if( gu8_Error_Code > 0 )
        {
            gu8_error_popup_enable = SET;
        }
        else if( bit_filter_alarm_start == SET )
        {
            gu8_filter_alarm_popup_enable = SET;
        }
        else if( bit_uv_water_tank_out == SET
                 && gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed < UV_COUPLE__ERROR_CHECT_OVER_AD
                 && gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed > UV_COUPLE__ERROR_CHECK_UNDER_AD
                 && bit_uv_fault_test_start == CLEAR )
        {
            /*..hui [24-11-28오전 10:03:48] 전원인가후 UV 테스트하는 동안에는 표시 안함 추가..*/
            gu8_uv_popup_enable = SET;
        }
        else if( ( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR )
                 && gu16_AD_Result_UV_Ice_Tray_1_2_Current < UV_COUPLE__ERROR_CHECT_OVER_AD
                 && gu16_AD_Result_UV_Ice_Tray_1_2_Current > UV_COUPLE__ERROR_CHECK_UNDER_AD
                 && bit_uv_fault_test_start == CLEAR )
        {
            gu8_uv_popup_enable = SET;
        }
        else if( bit_uv_ice_tank_out == SET
                 && gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current < UV_COUPLE__ERROR_CHECT_OVER_AD
                 && gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current > UV_COUPLE__ERROR_CHECK_UNDER_AD
                 && bit_uv_fault_test_start == CLEAR )
        {
            gu8_uv_popup_enable = SET;
        }
        else{}

        /*..hui [24-4-5오전 9:11:09] 얼음탱크 앞UV는 아이스트레이랑 연동되기 떄문에 표시 안함..*/
        #if 0
        else if( bit_uv_ice_tank_front_out == SET
                 && gu16_AD_Result_UV_Ice_Tank_3_Front_Current < UV_SOLO__ERROR_CHECK_OVER_AD
                 && gu16_AD_Result_UV_Ice_Tank_3_Front_Current > UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            gu8_uv_popup_enable = SET;
        }
        else{}
        #endif

        if( gu16_wifi_pairing_30min_timer >= WIFI_PAIRING_START_30_MIN )
        {
            /*..hui [24-8-6오전 10:52:13] 30분 경과후부터 추출 종료후 5초 동안 표시..*/
            bit_pairing_5s_display_start = SET;
        }
        else{}
    }
    else
    {
        if( gu8_Led_Display_Step == LED_Display__MAIN )
        {
            /*..hui [24-4-5오후 1:45:37] 초기화 해줘야함.. UV남은시간 표시 -> 추출 -> UV 종료 -> 추출종료..*/
            /*..hui [24-4-5오후 1:45:42] 되면 0으로 표시됨..*/
            gu8_error_popup_enable = CLEAR;
            gu8_filter_alarm_popup_enable = CLEAR;
            gu8_uv_popup_enable = CLEAR;
        }
        else{}
    }



    /*..hui [23-8-2오후 3:29:58] 얼음 추출중 -> 버튼 아무거나 누름 -> 일반 화면 표시 -> 7초 후 다시 얼음 추출 화면으로..*/
    /*..hui [23-8-2오후 3:30:07] UI 사양 변경됨..*/
    if( bit_ice_disp_pause == SET )
    {
        if( F_WaterOut == SET )
        {
            gu8_ice_disp_pause_timer = 0;
            bit_ice_disp_pause = CLEAR;
        }
        else{}

        if( F_Ice == SET )
        {
            gu8_ice_disp_pause_timer++;

            /*if( gu8_ice_disp_pause_timer >= 70 )*/
            if( gu8_ice_disp_pause_timer >= 69 )
            {
                gu8_ice_disp_pause_timer = 0;
                bit_ice_disp_pause = CLEAR;
            }
            else{}
        }
        else
        {
            gu8_ice_disp_pause_timer = 0;
            bit_ice_disp_pause = CLEAR;
        }
    }
    else
    {
        gu8_ice_disp_pause_timer = 0;
    }


}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_water_extract_display(void)
{
    gu8_fnd_water_step = 0;
    gu8_fnd_continue_timer = 0;
    gu16_extract_display_timer = 0;
    gu8_extract_display_cnt = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_ice_extract_display(void)
{
    gu8_fnd_left_ice_step = 0;
    gu8_fnd_left_ice_timer = 0;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_disp_key_check(void)
{
    /*..hui [23-8-2오후 3:35:25] 얼음 추출 -> 버튼 누름 -> 일반화면 전환 -> 7초후 얼음추출화면 전환..*/
    if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        bit_ice_disp_pause = SET;
    }
    else{}

    gu8_ice_disp_pause_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


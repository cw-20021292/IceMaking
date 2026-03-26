/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Key_Handling_Long.h"
#include "WIFI_SetFunctionData.h"


void setting_mode_start(void);
//void cold_water_enable_setting_job( U8 mu8_mode );
void hot_water_enable_setting_job( U8 mu8_mode);
//void all_lock_setting_job( U8 mu8_mode );
//void ice_on_off_setting_job(void);
void ice_on_setting_job(void);
void ice_off_setting_job(void);
//void cody_inspection_select_job(void);
void debug_mode_select_job(void);
void key_disable_touch_lock(void);
void key_altitude_setting_job(void);

void memento_select_job(void);
void memento_delete_job(void);
void memento_finish_job(void);
void default_cup_setting_job(void);
//void mute_setting_job(void);
void calcel_comp_delay(void);
void key_time_setting_job(void);
void key_reserve_time_setting_job(void);

void key_time_setting_hot_long_select_job(void);
void key_time_setting_cold_long_select_job(void);
void key_temporary_cold_off_job(void);
void key_sound_setting_job(void);
void key_ct_change_filter_order_job(void);
void key_ct_forced_flushing(void);
void key_recover_fast_ice_job(void);
void key_acid_clean_job(void);

bit bit_setting_mode_start;


bit bit_altitude_setting_start;
bit bit_memento_start;
U8 gu8_memento_display_num;

bit bit_sound_setting_start;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_mode_start(void)
{
    /*..hui [17-12-28오후 1:03:15] 추출중에는 변경못하도록 변경..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    if( bit_setting_mode_start == CLEAR )
    {
        bit_setting_mode_start = SET;
        play_melody_select_196();

        bit_periodic_ster_first_display = CLEAR;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void cold_water_enable_setting_job( U8 mu8_mode )
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if(F_WaterOut == SET)
    {
        return;
    }
    else{}

    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_Cold_Enable != SET)
        {
            F_Cold_Enable = SET;
            water_select_return_timer_control(0);

            if(F_Mute_Enable == CLEAR)
            {
                play_melody_setting_on_198();
            }
            else
            {
                /*BuzStep(BUZZER_SETUP_MUTE);*/
            }

            /*..hui [18-1-31오전 9:43:54] 냉수 미설정 상태에서 설정으로 변경시 5초 very long키 막음....*/
            /*..hui [18-1-31오전 9:44:00] 키 누르고있으면 연속해서 설정됐다 해제되는 문제..*/
            F_Cold_Water_VeryLongKey_Disable = SET;
        }
        else
        {
            F_Cold_Water_VeryLongKey_Disable = CLEAR;
        }
    }
    else
    {
        if(F_Cold_Enable == SET && F_Cold_Water_VeryLongKey_Disable == CLEAR)
        {
            F_Cold_Enable = CLEAR;
            water_select_return_timer_control(1);

            /*..hui [20-1-6오후 8:06:19] 냉수 버튼으로 냉수 끄면 냉수 설정도 OFF로 변경..*/
            /*..hui [20-2-24오후 7:44:02] 냉수 ONOFF랑 냉수온도 설정 메뉴 분리..*/
            /*gu8_cold_setting_level = COLD_TEMP_OFF;*/

            if(F_Mute_Enable == CLEAR)
            {
                play_melody_setting_off_199();
            }
            else
            {
                /*BuzStep(BUZZER_CANCEL_MUTE);*/
            }
        }
        else
        {
            F_Cold_Water_VeryLongKey_Disable = CLEAR;
        }
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_water_enable_setting_job( U8 mu8_mode)
{
//
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    #if 0
    if( F_Hot_Lock == SET )
    {
        return;
    }
    else{}
    #endif

    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_Hot_Enable != SET)
        {
            F_Hot_Enable = SET;
            water_select_return_timer_control(0);

            play_voice_setting_hot_on_121();

            /*..hui [18-1-31오전 9:43:54] 온수 미설정 상태에서 설정으로 변경시 5초 very long키 막음....*/
            /*..hui [18-1-31오전 9:44:00] 키 누르고있으면 연속해서 설정됐다 해제되는 문제..*/
            /*F_Hot_Water_VeryLongKey_Disable = SET;*/

            start_button_set_display( BUTTON_SET_HOT_DISPLAY );

            send_wifi_each_data_control( WIFI_FUNC_0039_HOT_SEL );
        }
        else{}

        /*..hui [23-5-12오후 3:15:30] 3초 지나면 7초 복귀 타이머 초기화..*/
        /*..hui [23-5-12오후 3:15:43] 7초동안 누르고있으면 전환되고 온수 OFF되기때문에 부자연스러움..*/
        gu16_water_select_return_time = 0;
    }
    else
    {
        /*if(F_Hot_Enable == SET && F_Hot_Water_VeryLongKey_Disable == CLEAR)*/
        if( F_Hot_Enable == SET )
        {
            F_Hot_Enable = CLEAR;
            water_select_return_timer_control(1);

            play_voice_setting_hot_off_122();

            start_button_set_display( BUTTON_SET_HOT_DISPLAY );

            send_wifi_each_data_control( WIFI_FUNC_0039_HOT_SEL );

        }
        else{}
    }


    /*send_wifi_each_data_control( WIFI_FUNC_0039_HOT_SEL );*/

    /*start_button_set_display( BUTTON_SET_HOT_DISPLAY );*/
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void all_lock_setting_job( U8 mu8_mode )
{
    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 추출중에는 변경못하도록 변경..*/
    if(F_WaterOut == SET || F_Ice == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}


    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_All_Lock != SET)
        {
            F_All_Lock = SET;
            BuzStep(BUZZER_SETUP);
        }
        else{}
    }
    else
    {
        if(F_All_Lock == SET)
        {
            F_All_Lock = CLEAR;
            BuzStep(BUZZER_CANCEL);
        }
        else{}
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void ice_on_off_setting_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    F_IceOn = ~F_IceOn;
    setting_buzzer( (U8)F_IceOn );

    if(F_IceOn == SET)
    {
        F_IR = SET;               // 만빙감지
        play_voice_setting_ice_on_149();
    }
    else
    {
        F_IceDoorClose = SET;
        play_voice_setting_ice_off_150();
    }

    send_wifi_each_data_control( WIFI_FUNC_0059_ICE_ONOFF_SEL );
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_on_setting_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    /*..hui [24-4-3오후 4:04:48] 얼음 ON돼있을경우 PASS..*/
    if( F_IceOn == SET )
    {
        return;
    }
    else{}

    F_IceOn = SET;
    setting_buzzer( (U8)F_IceOn );

    if( F_IceOn == SET )
    {
        F_IR = SET;               // 만빙감지
        play_voice_setting_ice_on_149();
    }
    else
    {
        F_IceDoorClose = SET;
        play_voice_setting_ice_off_150();
    }

    /*..hui [24-4-3오후 4:35:06] 얼음 설정 ON 표시..*/
    start_button_set_display( BUTTON_SET_ICE_OFF_DISPLAY );

    send_wifi_each_data_control( WIFI_FUNC_0059_ICE_ONOFF_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_off_setting_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    /*..hui [24-4-3오후 4:04:48] 얼음 OFF돼있을경우 PASS..*/
    if( F_IceOn == CLEAR )
    {
        return;
    }
    else{}

    F_IceOn = CLEAR;
    setting_buzzer( (U8)F_IceOn );

    if(F_IceOn == SET)
    {
        F_IR = SET;               // 만빙감지
        play_voice_setting_ice_on_149();
    }
    else
    {
        F_IceDoorClose = SET;
        play_voice_setting_ice_off_150();
    }

    /*..hui [24-4-3오후 4:35:06] 얼음 설정 OFF 표시..*/
    start_button_set_display( BUTTON_SET_ICE_OFF_DISPLAY );

    send_wifi_each_data_control( WIFI_FUNC_0059_ICE_ONOFF_SEL );
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void cody_inspection_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut != SET && F_Ice != SET )
    {
        //gu8_memento_depth = LCD_MENU_DEPTH_ONE;
        //gu8_product_info_depth = LCD_MENU_DEPTH_ONE;
        //show_cody_inspect_menu();
        play_melody_setting_on_198();
    }
    else{}
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void debug_mode_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:33:24] 메인 표시 상태에서만 진입..*/
    if(gu8_Led_Display_Step != LED_Display__MAIN)
    {
        if(gu8_Led_Display_Step == LED_Display__STEAM_CLEAN)
        {
            bit_ice_ster_test_debug_start = SET;
            gu8_ice_ster_test_debug_step = 0;
            play_voice_test_mode_151();
        }
        else{}

        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut != SET && F_Ice != SET )
    {
        /*..hui [20-3-13오후 3:06:31] 즉시 디버그 모드 진입..*/
        bit_debug_mode_start = SET;
        /*play_melody_setting_on_198();*/
        play_voice_test_mode_151();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_disable_touch_lock(void)
{
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    if( F_All_Lock == CLEAR )
    {
        return;
    }
    else{}

    if( bit_child_lock_enable == SET )
    {
        bit_temporary_release = SET;
        gu8_child_release_timer = 0;
        play_melody_setting_off_199();
        return;
    }
    else{}


    F_All_Lock = CLEAR;
    /////play_melody_setting_off_199();
    play_voice_all_lock_finish_128();
    Bit4_All_Lock_Indicator = CLEAR;

    send_wifi_each_data_control( WIFI_FUNC_0005_LOCK_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_altitude_setting_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( gu8_altutude_setting_timeout == 0 )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start != SET )
    {
        bit_altitude_setting_start = SET;
        play_melody_setting_on_198();
    }
    else
    {
        bit_altitude_setting_start = CLEAR;
        play_melody_setting_off_199();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_select_job(void)
{
    /*..hui [19-10-18오후 1:33:24] 메인 표시 상태에서만 진입..*/
    if(gu8_Led_Display_Step != LED_Display__MAIN )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    bit_memento_start = SET;
    gu8_memento_display_num = 0;
    /*play_melody_setting_on_198();*/
    play_voice_test_mode_151();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_finish_job(void)
{
    bit_memento_start = CLEAR;
    gu8_memento_display_num = 0;
    play_melody_setting_off_199();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_delete_job(void)
{
    F_ErrorSave = 1;

    u8Memento_Buff[0] = 0;
    u8Memento_Buff[1] = 0;
    u8Memento_Buff[2] = 0;
    u8Memento_Buff[3] = 0;
    u8Memento_Buff[4] = 0;

    play_melody_setting_on_198();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void default_cup_setting_job(void)
{
    /*..hui [17-12-19오후 2:25:35] 현재 디폴트 상태랑 동일한 키 입력시 패스....*/
    if( gu8Cup_level == gu8Cup_level_Default )
    {
        //
    }
    else
    {
        gu8Cup_level_Default = gu8Cup_level;
        play_voice_default_cup_setting_finish_141();

        /*..hui [23-3-22오후 4:16:20] Main 화면에서만 FND 점멸 표시..*/
        if( gu8_Led_Display_Step == LED_Display__MAIN )
        {
            //start_defualt_cup_set_flick();
        }
        else{}

        gu8_cup_level_time_init = SET;
    }

    send_wifi_each_data_control( WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void mute_setting_job(void)
{
    if(F_Mute_Enable != SET)
    {
        F_Mute_Enable = SET;
        /*..hui [23-7-26오후 7:11:02] 무음 설정이 취소음.. 무음 설정되는게 OFF임.. UI 사양..*/
        //////BuzStep(BUZZER_CANCEL_MUTE);
        play_melody_setting_off_199();
    }
    else
    {
        F_Mute_Enable = CLEAR;
        play_melody_setting_on_198();
    }

    start_button_set_display( BUTTON_SET_MUTE_DISPLAY );

    send_wifi_each_data_control( WIFI_FUNC_0006_MUTE_SEL );

    /*BuzStep(BUZZER_MUTE);*/
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calcel_comp_delay(void)
{
    /*..hui [19-10-25오전 9:21:25] 여기서 한번 더 필터링..*/
    if(F_Comp_Output == CLEAR && gu16CompOffDelay > 0)
    {
        /*..hui [19-10-25오전 9:22:56] 냉매전환밸브 초기화시간 고려..*/
        gu16CompOffDelay = DEVELOPE_COMP_DELAY_CANCEL_TIME;
        play_melody_setting_on_198();
    }
    else
    {
        play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_job(void)
{
    /*..hui [23-6-14오전 10:37:57] 와이파이 연결되면 시간설정 금지..*/
    if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        //start_all_lock_flick();
        return;
    }
    else{}

    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    #if 0
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}
    #endif

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        /*play_melody_warning_197();*/
        return;
    }
    else{}

    /*..hui [23-9-14오후 3:38:14] 현재시간, 설정시간 설정시에는 진입못하게..*/
    if( bit_time_setting_start == SET )
    {
        /*play_melody_warning_197();*/
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    if( bit_setting_mode_start != SET )
    {
        play_voice_time_setting_start_144();
        start_time_setting_mode( CURRENT_TIME_SETTING_MODE );
    }
    else
    {
        play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_reserve_time_setting_job(void)
{
    /*..hui [23-6-14오전 10:37:57] 와이파이 연결되면 시간설정 금지..*/
    if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /*..hui [23-9-14오후 3:38:14] 현재시간, 설정시간 설정시에는 진입못하게..*/
    if( bit_time_setting_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}


    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        //start_all_lock_flick();
        return;
    }
    else{}

    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    #if 0
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}
    #endif

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        /*play_melody_warning_197();*/
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}


    if( bit_setting_mode_start != SET )
    {
        play_melody_setting_on_198();
        start_time_setting_mode( CLEAN_RESERVE_TIME_SETTING_MODE );
    }
    else
    {
        play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_hot_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit0_Hot_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_cold_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit1_Cold_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_temporary_cold_off_job(void)
{
    if(F_Cold_Enable != SET)
    {
        F_Cold_Enable = SET;
        /*..hui [23-7-26오후 7:11:02] 무음 설정이 취소음.. 무음 설정되는게 OFF임.. UI 사양..*/
        /*play_melody_setting_on_198();*/
        play_voice_test_mode_151();
    }
    else
    {
        F_Cold_Enable = CLEAR;
        play_melody_setting_off_199();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_sound_setting_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        /*play_melody_warning_197();*/
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}


    if( bit_sound_setting_start != SET )
    {
        bit_sound_setting_start = SET;
        play_voice_sound_setting_start_132();
    }
    else
    {
        /*bit_altitude_setting_start = CLEAR;*/
        /*BuzStep(BUZZER_CANCEL);*/
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ct_change_filter_order_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_flushing_standby_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == CLEAR )
    {
        bit_ct_filter_type_start = SET;
        play_melody_setting_on_198();
    }
    else
    {
        bit_ct_filter_type_start = CLEAR;
        play_melody_setting_off_199();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ct_forced_flushing(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    /*..hui [24-2-22오후 1:42:12] 플러싱 시작 후에는 종료하지 못하도록..*/
    if( gu8_ct_forced_flushing_start == SET )
    {
        return;
    }
    else{}

    /*..hui [24-7-29오후 3:14:40] 구연산 세척 진행 중 시작 불가..*/
    if( bit_acid_clean_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_flushing_standby_start == CLEAR )
    {
        bit_ct_flushing_standby_start = SET;
        play_melody_setting_on_198();
    }
    else
    {
        bit_ct_flushing_standby_start = CLEAR;
        play_melody_setting_off_199();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_recover_fast_ice_job(void)
{
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_flushing_standby_start == SET )
    {
        return;
    }
    else{}

    if( gu8_recover_org_fast_ice == NEW_FAST_ICE )
    {
        gu8_recover_org_fast_ice = RECOVER_FAST_ICE;
        play_melody_setting_on_198();
    }
    else
    {
        gu8_recover_org_fast_ice = NEW_FAST_ICE;
        play_melody_setting_off_199();
    }

    /*..hui [24-4-11오후 7:30:11] 얼음우선 예전사양으로 복구.. 설정값 표시..*/
    start_button_set_display( BUTTON_SET_RECOVER_FAST_ICE_DISPLAY );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_acid_clean_job(void)
{
    #if 0
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_ct_flushing_standby_start == SET )
    {
        return;
    }
    else{}

    start_acid_clean();
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




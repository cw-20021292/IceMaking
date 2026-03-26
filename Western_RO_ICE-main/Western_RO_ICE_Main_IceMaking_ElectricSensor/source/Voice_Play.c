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
#include    "Voice_Play.h"


void play_melody_continue_extract_start_192( void );
void play_melody_normal_extract_start( void );
void play_voice_hot_water_extract( void );
void play_melody_extract_complete_194( void );
void play_melody_power_on_195( void );
void play_melody_select_196( void );
void play_melody_warning_197( void );
void play_melody_setting_on_198( void );
void play_melody_setting_off_199( void );


void play_voice_top_cover_open_2( void );
void play_voice_filter_cover_open_3( void );
void play_voice_top_cover_close_6( void );
void play_voice_cold_error_7( void );
void play_voice_hot_error_9( void );
void play_voice_ice_error_10( void );

void play_voice_flow_block_error_11( void );
void play_voice_leakage_error_12( void );
void play_voice_change_1_3_filter_13( void );
void play_voice_a_type_add_3_filter_change_15( void );
void play_voice_a_type_add_1_3_filter_change_16( void );
void play_voice_a_type_add_3_filter_change_17( void );
void play_voice_1_3_filter_change_detect_18( void );
void play_voice_1_3_filter_change_finish_19( void );

void play_voice_filter_flushing_start_23( void );
void play_voice_filter_flushing_finish_24( void );
void play_voice_filter_flushing_cancle_25( void );
void play_voice_replace_filter_1_3_26( void );
void play_voice_b_type_only_1_filter_change_43( void );
void play_voice_b_type_only_2_filter_change_44( void );
void play_voice_b_type_only_3_filter_change_45( void );
void play_voice_1_2_3_filter_change_finish_46( void );
void play_voice_change_all_filter_47( void );
void play_voice_replace_filter_1_2_3_49( void );



void play_voice_ice_tank_clean_extract_60( void );
void play_voice_start_self_test_61( void );
void play_voice_finish_self_no_error_test_62( void );
void play_voice_finish_self_error_test_63( void );

void play_voice_install_guide_75( void );
/*void play_voice_pairing_auto_start_76( void );*/


void play_voice_filter_cover_open_extract_89( void );

void play_voice_hot_lcok_hot_select_93( void );
void play_voice_hot_off_hot_select_94( void );

void play_voice_short_ice_out_97( void );
void play_voice_ice_lock_ice_out_98( void );
void play_voice_ice_off_ice_out_99( void );
void play_voice_ice_off_ice_select_99( void );

void play_voice_eco_mode_time_set_100( void );

void play_voice_eco_mode_ice_out_101( void );

void play_voice_all_lock_select_103( void );


void play_voice_low_water_hot_room_out_108( void );
void play_voice_hot_heating_109( void );

void play_voice_cold_cooling_111( void );

void play_voice_setting_hot_lock_on_112( void );
void play_voice_setting_hot_lock_off_113( void );

void play_voice_setting_hot_on_121( void );
void play_voice_setting_hot_off_122( void );

void play_voice_all_lock_start_127( void );
void play_voice_all_lock_finish_128( void );

void play_voice_sound_setting_start_132( void );
void play_voice_sound_setting_voice_129( void );
void play_voice_sound_setting_melody_130( void );
void play_voice_sound_setting_mute_131( void );

void play_voice_default_cup_setting_finish_141( void );
void play_voice_time_setting_start_144( void );
void play_voice_time_setting_finish_145( void );
void play_voice_setting_ice_lock_on_147( void );
void play_voice_setting_ice_lock_off_148( void );
void play_voice_setting_ice_on_149( void );
void play_voice_setting_ice_off_150( void );

void play_voice_test_mode_151( void );
void play_voice_replace_filter( void );


U8 gu8_125_select;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_normal_extract_start( void )
{
    /*..hui [21-9-2오후 3:17:18] 메뉴에서 연속 이외 선택 후 추출 할때..*/
    if(u8WaterOutState == HOT_WATER_SELECT)
    {
        if( gu8Sound_Type == SOUND_TYPE_VOICE )
        {
            Play_Voice(VOICE_79_WATCHOUT_HOT_WATER_CUP);
        }
        else if( gu8Sound_Type == SOUND_TYPE_MELODY )
        {
            Play_Voice(VOICE_193_MELODY_DISPENSE_START);
        }
        else{}
    }
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
        {
            /*play_voice_low_water_cold_out();*/

            if( gu8Sound_Type == SOUND_TYPE_VOICE )
            {
                Play_Voice(VOICE_107_NO_GUARANTEE_LOW_WATER);
            }
            else if( gu8Sound_Type == SOUND_TYPE_MELODY )
            {
                /*play_melody_warning_197();*/
                /*..hui [23-12-15오전 9:18:58] 저수위 - 냉수추출일때 멜로디이면 경고음이 아닌 추출음으로....*/
                Play_Voice(VOICE_193_MELODY_DISPENSE_START);
            }
            else{}
        }
        else
        {
            Play_Voice(VOICE_193_MELODY_DISPENSE_START);
        }
    }
    else
    {
        Play_Voice(VOICE_193_MELODY_DISPENSE_START);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_continue_extract_start_192( void )
{
    /*..hui [21-9-2오후 3:16:16] 메뉴에서 연속 설정하고 추출했을때..*/
    if(u8WaterOutState == HOT_WATER_SELECT)
    {
        if( gu8Sound_Type == SOUND_TYPE_VOICE )
        {
            Play_Voice(VOICE_80_WATCHOUT_HOT_WATER_CONTINUOUS);
        }
        else if( gu8Sound_Type == SOUND_TYPE_MELODY )
        {
            Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
        }
        else{}
    }
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
        {
            /*play_voice_low_water_cold_out();*/

            if( gu8Sound_Type == SOUND_TYPE_VOICE )
            {
                Play_Voice(VOICE_107_NO_GUARANTEE_LOW_WATER);
            }
            else if( gu8Sound_Type == SOUND_TYPE_MELODY )
            {
                /*play_melody_warning_197();*/
                /*..hui [23-12-15오전 9:18:58] 저수위 - 냉수추출일때 멜로디이면 경고음이 아닌 추출음으로....*/
                Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
            }
            else{}
        }
        else
        {
            Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
        }
    }
    else
    {
        Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_extract_complete_194( void )
{
    Play_Voice(VOICE_194_MELODY_DISPENSE_FINISH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_power_on_195( void )
{
    Play_Voice(VOICE_195_MELODY_PLUG_IN);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_select_196( void )
{
    Play_Voice(VOICE_196_MELODY_SELECT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_warning_197( void )
{
    Play_Voice(VOICE_197_MELODY_WARNING);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_setting_on_198( void )
{
    Play_Voice(VOICE_198_MELODY_SET_ON);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_setting_off_199( void )
{
    Play_Voice(VOICE_199_MELODY_SET_OFF);
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_top_cover_open_2( void )
{
    Play_Voice(VOICE_2_STOP_ICE_ICETANK_COVER);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_2_STOP_ICE_ICETANK_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_cover_open_3( void )
{
    Play_Voice(VOICE_3_SHUTOFF_WATER_SIDE_COVER);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_3_SHUTOFF_WATER_SIDE_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_top_cover_close_6( void )
{
    Play_Voice(VOICE_6_RESTART_ICE_COVER_OK);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_6_RESTART_ICE_COVER_OK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_cold_error_7( void )
{
    Play_Voice(VOICE_7_CALL_AS_COLD_WATER_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_error_9( void )
{
    Play_Voice(VOICE_9_CALL_AS_HOT_WATER_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_error_10( void )
{
    Play_Voice(VOICE_10_CALL_AS_ICE_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_flow_block_error_11( void )
{
    Play_Voice(VOICE_11_CALL_AS_WATER_SUPPLY_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_leakage_error_12( void )
{
    Play_Voice(VOICE_12_CALL_AS_WATER_LEAKAGE_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_change_1_3_filter_13( void )
{
    /*..hui [24-1-10오후 3:06:55] 1,3번 시기에 2번 레버 들어올리면..*/
    if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
    {
        Play_Voice(VOICE_13_REPLACE_ONLY_FILTER_NO1_NO3);
    }
    else
    {
        /*..hui [24-1-10오후 3:07:03] 1,2,3번 시기에는 불가음..*/
        play_melody_warning_197();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_a_type_add_3_filter_change_15( void )
{
    Play_Voice(VOICE_15_REPLACE_ADD_FILTER_NO3_PLEASE);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_a_type_add_1_3_filter_change_16( void )
{
    Play_Voice(VOICE_16_REPLACE_AFTER_CHECK_FILTER_NO1_NO3);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_a_type_add_3_filter_change_17( void )
{
    Play_Voice(VOICE_17_REPLACE_ADD_FILTER_NO1_PLEASE);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_1_3_filter_change_detect_18( void )
{
    Play_Voice(VOICE_18_CLOSE_COVER_AFTER_FILTER_NO1_NO3);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_1_3_filter_change_finish_19( void )
{
    Play_Voice(VOICE_19_PRESS_YES_OR_NO_AFTER_FILTER_NO1_NO3);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_start_23( void )
{
    Play_Voice(VOICE_23_START_FILTER_FLUSHING);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_23_START_FILTER_FLUSHING);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_finish_24( void )
{
    Play_Voice(VOICE_24_FINISH_FILTER_FLUSHING);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_24_FINISH_FILTER_FLUSHING);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_cancle_25( void )
{
    Play_Voice(VOICE_25_CHECK_FILTER_FLUSHING_MANUAL);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_25_CHECK_FILTER_FLUSHING_MANUAL);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter_1_3_26( void )
{
    Play_Voice(VOICE_26_REPLACE_FILTER_NO1_NO3);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_b_type_only_1_filter_change_43( void )
{
    Play_Voice(VOICE_43_REPLACE_ADD_FILTER_NO2_NO3_FOR_ALL);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_b_type_only_2_filter_change_44( void )
{
    Play_Voice(VOICE_44_REPLACE_ADD_FILTER_NO1_NO3_FOR_ALL);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_b_type_only_3_filter_change_45( void )
{
    Play_Voice(VOICE_45_REPLACE_ADD_FILTER_NO1_NO2_FOR_ALL);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_1_2_3_filter_change_finish_46( void )
{
    Play_Voice(VOICE_46_PRESS_YES_OR_NO_AFTER_ALL_FILTERS);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_change_all_filter_47( void )
{
    Play_Voice(VOICE_47_CHECK_REPLACE_ALL_FILTERS);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter_1_2_3_49( void )
{
    Play_Voice(VOICE_49_REPLACE_FILTER_ALL);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_tank_clean_extract_60( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_60_WAIT_ICE_TANK_CLEANING);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_start_self_test_61( void )
{
    Play_Voice(VOICE_61_START_SMART_TESTING_MODE);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_finish_self_no_error_test_62( void )
{
    #if 0
    Play_Voice(VOICE_62_FINISH_SMART_TESTING_MODE_NO_ERROR);
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_finish_self_error_test_63( void )
{
    #if 0
    Play_Voice(VOICE_63_FINISH_SMART_TESTING_MODE_WITH_ERROR);
    #endif
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_install_guide_75( void )
{
    Play_Voice(VOICE_75_PRESS_INSTALL_BUTTON);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_75_PRESS_INSTALL_BUTTON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void play_voice_pairing_auto_start_76( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_76_START_WIFI_AUTOMATIC_CONNECTION);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_cover_open_extract_89( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_89_CLOSE_SIDE_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_lcok_hot_select_93( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_93_PRESS_SETTING_MODE_HOT_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_off_hot_select_94( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_94_PRESS_BUTTON_HOT_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_short_ice_out_97( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_97_DISPENSE_ICE_WHILE_PRESS);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_lock_ice_out_98( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_98_INFORM_ICE_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_off_ice_out_99( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_99_PRESS_BUTTON_ICE_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_off_ice_select_99( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_99_PRESS_BUTTON_ICE_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_eco_mode_time_set_100( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_100_SET_CLOCK_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_eco_mode_ice_out_101( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_101_NO_GUARANTEE_ICE_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_select_103( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_103_PRESS_SETTING_MODE_ALL_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_low_water_hot_room_out_108( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_108_WAIT_LOW_WATER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_heating_109( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_109_INFORM_NOT_ENOUGH_HOT);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        /*play_melody_warning_197();*/
        play_melody_select_196();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_cold_cooling_111( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_111_INFORM_NOT_ENOUGH_COLD);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        /*play_melody_warning_197();*/
        play_melody_select_196();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_lock_on_112( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_112_INFORM_HOT_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_lock_off_113( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_113_INFORM_HOT_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_on_121( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_121_INFORM_HOT_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_off_122( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_122_INFORM_HOT_FUNCTION_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_start_127( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_127_INFORM_ALL_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_finish_128( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_128_INFORM_ALL_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_sound_setting_start_132( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_sound_setting_voice_129( void )
{
    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_125_MODE_SET);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
    #endif

    Play_Voice(VOICE_129_VOICE_MODE);

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_sound_setting_melody_130( void )
{
    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_125_MODE_SET);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
    #endif

    Play_Voice(VOICE_130_MELODY_MODE);

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_sound_setting_mute_131( void )
{
    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_125_MODE_SET);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
    #endif

    Play_Voice(VOICE_131_MUTE_MODE);

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_default_cup_setting_finish_141( void )
{
    gu8_125_select = 0;

    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_141_MODE_SET_DEFAULT_AMOUNT);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_time_setting_start_144( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_144_SETTING_MODE_CLOCK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_time_setting_finish_145( void )
{
    gu8_125_select = 1;

    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_145_MODE_SET_CLOCK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_lock_on_147( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_147_INFORM_ICE_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_lock_off_148( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_148_INFORM_ICE_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_on_149( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_149_INFORM_ICE_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_off_150( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_150_INFORM_ICE_FUNCTION_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_test_mode_151( void )
{
    Play_Voice(VOICE_151_SPECIAL_FUNCTION);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter( void )
{
    /*..hui [24-1-10오후 3:31:21] 최초 필터 알람 표시 후 첫 물 추출 종료하고 필터 알람 화면 표시할때 ..*/
    /*..hui [24-1-10오후 3:31:25] 1회만 음성 출력..*/
    if( bit_filter_alarm_1_3_voice == SET )
    {
        play_voice_replace_filter_1_3_26();
    }
    else if( bit_filter_alarm_1_2_3_voice == SET )
    {
        play_voice_replace_filter_1_2_3_49();
    }
    else{}

    bit_filter_alarm_1_3_voice = CLEAR;
    bit_filter_alarm_1_2_3_voice = CLEAR;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




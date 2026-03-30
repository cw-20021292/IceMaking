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
#include    "m_wifi_setting_data.h"


void wifi_hot_lock( U16 mu16_setting );
void wifi_all_lock( U16 mu16_setting );
void wifi_child_lock( U16 mu16_setting );
void wifi_mute( U16 mu16_setting );
void wifi_ice_lock( U16 mu16_setting );
void wifi_hot_enable( U16 mu16_setting );
void wifi_altitude( U16 mu16_setting );
void wifi_ice_first( U16 mu16_setting );
void wifi_ice_enable( U16 mu16_setting );
void wifi_welcome_light( U16 mu16_setting );
void wifi_hot_default_temp( U16 mu16_setting );
void wifi_default_cup( U16 mu16_setting );
void wifi_continue_water_using( U16 mu16_setting );
void wifi_cup_level_order( U16 mu16_setting );
void wifi_hot_temp_level_order( U16 mu16_setting );
void wifi_oF_oC_select( U16 mu16_setting );
void wifi_Oz_mL_select( U16 mu16_setting );
void wifi_period_ster_hour( U16 mu16_setting );
void wifi_period_ster_minute( U16 mu16_setting );
void wifi_sleep_mode_enable( U16 mu16_setting );
void wifi_sleep_start_hour( U16 mu16_setting );
void wifi_sleep_start_minute( U16 mu16_setting );
void wifi_sleep_finish_hour( U16 mu16_setting );
void wifi_sleep_finish_minute( U16 mu16_setting );
void wifi_unused_setting_time( U16 mu16_setting );
void wifi_voice_language( U16 mu16_setting );
void wifi_filter_change_type( U16 mu16_setting );
void wifi_cold_enable( U16 mu16_setting );

void start_fota(void);
void wifi_self_test( U16 mu16_setting );

U8 gu8_oF__oC_select;
U8 gu8_ml__oz_select;
U8 gu8_hot_level_order;
U8 gu8_hot_default_temp;




U8 gu8_temporary_sleep_mode_start_hour;
U8 gu8_temporary_sleep_mode_start_minute;
U8 gu8_temporary_sleep_mode_finish_hour;
U8 gu8_temporary_sleep_mode_finish_minute;


U8 gu8_temporary_period_ster_hour;
U8 gu8_temporary_period_ster_minute;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_hot_lock( U16 mu16_setting )
{
    U8 mu8_on_off = 0;
    U8 mu8_cold_level = 0;

    if( mu16_setting == WIFI_HOT_LOCK_ON )
    {
        F_Hot_Lock = SET;
        //play_voice_setting_hot_lock_on_112();

        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            water_select_return_timer_control(1);
        }
        else{}
    }
    else if( mu16_setting == WIFI_HOT_LOCK_OFF )
    {
        F_Hot_Lock = CLEAR;
        //play_voice_setting_hot_lock_off_113();
    }
    else
    {
        //play_melody_warning_197();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_all_lock( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_All_Lock = CLEAR;
            //play_voice_all_lock_finish_128();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_All_Lock = SET;
            //play_voice_all_lock_start_127();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_child_lock( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            	/* ◎ */
            //bit_child_lock_enable = CLEAR;
            //play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            	/* ◎ */
            //bit_child_lock_enable = SET;
            //play_melody_setting_on_198();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_mute( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Mute_Enable = CLEAR;
        }
        else /*if( mu16_setting == 1 )*/
        {
			
            F_Mute_Enable = SET;
            /*..hui [23-7-26오후 7:11:02] 무음 설정이 취소음.. 무음 설정되는게 OFF임.. UI 사양..*/
            //BuzStep(BUZZER_CANCEL_MUTE);
            /*..sean [25-02-12] 무음 설정이 설정음.. 무음 설정할 때에도 소리가 나도록 해야함..*/
            BuzStep(BUZZER_SETUP_MUTE);
            //play_melody_setting_off_199();
        }
    }
    else {}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_lock( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Ice_Lock = CLEAR;
            //play_voice_setting_ice_lock_off_148();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Ice_Lock = SET;
            //play_voice_setting_ice_lock_on_147();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_hot_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Hot_Enable = CLEAR;
            //play_voice_setting_hot_off_122();

            /*..hui [23-7-24오후 1:31:41] 프리히팅 중이었으면 프리히팅 종료..*/
            /////stop_hot_preheating();///////

            /*..hui [24-1-19오후 2:27:45] 온수 선택 상태에서 온수 OFF시 이전 선택으로..*/
            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                water_select_return_timer_control(1);
            }
            else{}
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Hot_Enable = SET;
            //play_voice_setting_hot_on_121();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_altitude( U16 mu16_setting )
{
    /*if( mu16_setting <= 2 )*/
    if( mu16_setting <= 3 )
    {
        if( mu16_setting == 0 )
        {
            gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;
            //play_melody_setting_on_198();
        }
        else if( mu16_setting == 1 )
        {
            gu8AltitudeStep = ALTITUDE_2_MODE_MID;
            //play_melody_setting_on_198();
        }
        else if( mu16_setting == 2 )
        {
            gu8AltitudeStep = ALTITUDE_3_MODE_LOW;
            //play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 3 )*/
        {
            gu8AltitudeStep = ALTITUDE_4_MODE_VERY_LOW;
            //play_melody_setting_on_198();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_first( U16 mu16_setting )
{
    if( mu16_setting == 1 )
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        //play_melody_setting_on_198();
    }
    else if( mu16_setting == 3 )
    {
        bit_fast_ice_make = ICE_FIRST_ICE_MAKE;
        //play_melody_setting_off_199();
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_IceOn = CLEAR;
            //play_voice_setting_ice_off_150();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_IceOn = SET;
            //play_voice_setting_ice_on_149();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_welcome_light( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Extract_Led_OnOff = CLEAR;
            //play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Extract_Led_OnOff = SET;
            //play_melody_setting_on_198();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_hot_default_temp( U16 mu16_setting )
{
    if( mu16_setting <= 3 )
    {
        if( mu16_setting == 0 )
        {
//            gu8_hot_default_temp = HOT_SET_TEMP_1__110_oF_43_oC;
        }
        else if( mu16_setting == 1 )
        {
//            gu8_hot_default_temp = HOT_SET_TEMP_2__170_oF_77_oC;
        }
        else if( mu16_setting == 2 )
        {
//            gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;
        }
        else /*if( mu16_setting == 3 )*/
        {
//            gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
        }

        //play_melody_setting_on_198();
    }
    else
    {
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_continue_water_using( U16 mu16_setting )
{
#if 0
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit9_Continue_Select__Continue = CLEAR;
            //play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit9_Continue_Select__Continue = SET;
            //play_melody_setting_on_198();
        }
    }
    else
    {
        //play_melody_warning_197();
    }
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_mode_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            	/* ◎ */
            bit_sleep_mode_enable = CLEAR;
        }
        else /*if( mu16_setting == 1 )*/
        {
            bit_sleep_mode_enable = SET;
        }
    }
    else
    {
        bit_sleep_mode_enable = CLEAR;
		BuzStep(BUZZER_CANCEL);
        //play_melody_warning_197();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_default_cup( U16 mu16_setting )
{
    if( mu16_setting <= 9 && mu16_setting != 8 )
    {
        if( mu16_setting == 0 )
        {
            gu8Cup_level_Default = CUP_LEVEL_HALF;
        }
        else if( mu16_setting == 1 )
        {
            gu8Cup_level_Default = CUP_LEVEL_ONE;
        }
        else if( mu16_setting == 2 )
        {
            gu8Cup_level_Default = CUP_LEVEL_TWO;
        }
        else if( mu16_setting == 3 )
        {
            gu8Cup_level_Default = CUP_LEVEL_FOUR;
        }
		/*
        else if( mu16_setting == 4 )
        {
            gu8Cup_level_Default = CUP_LEVEL_CONTINUE;
        }
		*/
        else if( mu16_setting == 4 )
        {
            gu8Cup_level_Default = CUP_LEVEL_MY_CUP;
        }
        else /*if( mu16_setting == 9 )*/
        {
            gu8Cup_level_Default = CUP_LEVEL_HALF;
        }

        gu8Cup_level = gu8Cup_level_Default;
    }
    else {}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_cold_enable( U16 mu16_setting )
{
    if( mu16_setting == SET )
    {
        F_Cold_Enable = SET;
    }
    else
    {
        F_Cold_Enable = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_start_hour( U16 mu16_setting )
{
    #if 1
    if( mu16_setting <= 23 )
    {
        gu8_sleep_mode_start_hour = (U8)mu16_setting;
        /*BuzStep(BUZZER_SETUP);*/
    }
    else
    {
        /*BuzStep(BUZZER_ERROR);*/
    }
    #endif

    gu8_temporary_sleep_mode_start_hour = (U8)mu16_setting;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_start_minute( U16 mu16_setting )
{
    #if 1
    if( mu16_setting <= 59 )
    {
        gu8_sleep_mode_start_minute = (U8)mu16_setting;
        /*BuzStep(BUZZER_SETUP);*/
    }
    else
    {
        /*BuzStep(BUZZER_ERROR);*/
    }
    #endif

    gu8_temporary_sleep_mode_start_minute = (U8)mu16_setting;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_finish_hour( U16 mu16_setting )
{
    #if 1
    if( mu16_setting <= 23 )
    {
        gu8_sleep_mode_finish_hour = (U8)mu16_setting;
        /*BuzStep(BUZZER_SETUP);*/
    }
    else
    {
        /*BuzStep(BUZZER_ERROR);*/
    }
    #endif

    gu8_temporary_sleep_mode_finish_hour = (U8)mu16_setting;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_finish_minute( U16 mu16_setting )
{
    gu8_temporary_sleep_mode_finish_minute = (U8)mu16_setting;


    if( gu8_temporary_sleep_mode_start_hour <= 23 && gu8_temporary_sleep_mode_start_minute <= 59
        && gu8_temporary_sleep_mode_finish_hour <= 23 && gu8_temporary_sleep_mode_finish_minute <= 59 )
    {
        gu8_sleep_mode_start_hour = gu8_temporary_sleep_mode_start_hour;
        gu8_sleep_mode_start_minute = gu8_temporary_sleep_mode_start_minute;
        gu8_sleep_mode_finish_hour = gu8_temporary_sleep_mode_finish_hour;
        gu8_sleep_mode_finish_minute = gu8_temporary_sleep_mode_finish_minute;
        //play_melody_setting_on_198();
    }
    else
    {
        //play_melody_warning_197();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_fota(void)
{
    gu8_fota_start = SET;

    /*off_all_test_load();*/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_self_test( U16 mu16_setting )
{
    /*..hui [21-8-25오후 5:47:58] 0이면 중지, 일반동작..*/
    if( mu16_setting == 0 )
    {
        /* ◎ */
        //if(1)
        if( bit_self_test_start == SET )
        {
            	/* ◎ */
            if( bit_self_test_stop == CLEAR )
            //if(1)
            {
            	/* ◎ */
                bit_self_test_stop = SET;

                /*..hui [21-9-8오전 10:26:04] 시작하면 wifi쪽에서 자동으로 보내기때문에 이쪽에서..*/
                gu8_wifi_self_test_state = WIFI_SELF_TEST_STOP;
                gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;
            }
            else{}
        }
        else{}
    }
    else if( mu16_setting == 1 )
    {
        /*..hui [21-8-25오후 5:48:08] 1이면 스마트 정밀진단 시작..*/
        /* ◎ */
        if( bit_self_test_start == CLEAR )
        //if(1)
        {
            /*bit_self_test_start = SET;*/

            /*..hui [21-9-8오전 11:02:26] 이쪽에서 한번 더 막아줌..*/
            if( gu8_wifi_self_test_state == WIFI_SELF_TEST_NO_OPERATION )
            {
            	/* ◎ */
                start_self_test();
            }
            else{}
        }
        else{}
    }
    else{}
}

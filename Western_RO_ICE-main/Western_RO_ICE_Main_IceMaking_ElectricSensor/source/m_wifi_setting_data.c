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
void wifi_4_oz_water_using( U16 mu16_setting );
void wifi_6_oz_water_using( U16 mu16_setting );
void wifi_8_oz_water_using( U16 mu16_setting );
void wifi_10_oz_water_using( U16 mu16_setting );
void wifi_12_oz_water_using( U16 mu16_setting );
void wifi_14_oz_water_using( U16 mu16_setting );
void wifi_16_oz_water_using( U16 mu16_setting );
void wifi_20_oz_water_using( U16 mu16_setting );
void wifi_32_oz_water_using( U16 mu16_setting );
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
        play_voice_setting_hot_lock_on_112();

        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            water_select_return_timer_control(1);
        }
        else{}
    }
    else if( mu16_setting == WIFI_HOT_LOCK_OFF )
    {
        F_Hot_Lock = CLEAR;
        play_voice_setting_hot_lock_off_113();
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
void wifi_all_lock( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_All_Lock = CLEAR;
            bit_child_lock_enable = CLEAR;      // 자동잠금 강제 OFF
            play_voice_all_lock_finish_128();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_All_Lock = SET;
            play_voice_all_lock_start_127();
        }
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
void wifi_child_lock( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            bit_child_lock_enable = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            bit_child_lock_enable = SET;
            play_melody_setting_on_198();
        }
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
void wifi_mute( U16 mu16_setting )
{
    #if 0
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Mute_Enable = CLEAR;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Mute_Enable = SET;
            /*..hui [23-7-26오후 7:11:02] 무음 설정이 취소음.. 무음 설정되는게 OFF임.. UI 사양..*/
            /////BuzStep(BUZZER_CANCEL_MUTE);
            play_melody_setting_off_199();
        }
    }
    else
    {
        play_melody_warning_197();
    }
    #endif
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
            play_voice_setting_ice_lock_off_148();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Ice_Lock = SET;
            play_voice_setting_ice_lock_on_147();
        }
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
void wifi_hot_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Hot_Enable = CLEAR;
            play_voice_setting_hot_off_122();

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
            play_voice_setting_hot_on_121();
        }
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
void wifi_altitude( U16 mu16_setting )
{
    /*if( mu16_setting <= 2 )*/
    if( mu16_setting <= 3 )
    {
        if( mu16_setting == 0 )
        {
            gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;
            play_melody_setting_on_198();
        }
        else if( mu16_setting == 1 )
        {
            gu8AltitudeStep = ALTITUDE_2_MODE_MID;
            play_melody_setting_on_198();
        }
        else if( mu16_setting == 2 )
        {
            gu8AltitudeStep = ALTITUDE_3_MODE_LOW;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 3 )*/
        {
            gu8AltitudeStep = ALTITUDE_4_MODE_VERY_LOW;
            play_melody_setting_on_198();
        }

        /*..hui [24-11-26오후 4:34:18] 고도모드 변경에따른 온수 디폴트 온도 변경..*/
        change_hot_default_altitude();
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
void wifi_ice_first( U16 mu16_setting )
{
    if( mu16_setting == 1 )
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        play_melody_setting_on_198();
    }
    else if( mu16_setting == 3 )
    {
        bit_fast_ice_make = ICE_FIRST_ICE_MAKE;
        play_melody_setting_off_199();
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
void wifi_ice_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_IceOn = CLEAR;
            play_voice_setting_ice_off_150();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_IceOn = SET;
            play_voice_setting_ice_on_149();
        }
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
void wifi_welcome_light( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            F_Extract_Led_OnOff = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            F_Extract_Led_OnOff = SET;
            play_melody_setting_on_198();
        }
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
void wifi_hot_default_temp( U16 mu16_setting )
{
    if( mu16_setting <= 3 )
    {
        if( mu16_setting == 0 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_1__110_oF_43_oC;
        }
        else if( mu16_setting == 1 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_2__170_oF_77_oC;
        }
        else if( mu16_setting == 2 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;
        }
        else /*if( mu16_setting == 3 )*/
        {
            gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
        }

        /*play_melody_setting_on_198();*/

        if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
        {
            /*..hui [24-11-26오후 4:47:48] 데이터 잘못들어온경우..3단계인데 온수설정 4단계 설정으로 온경우..*/
            if( gu8_hot_default_temp == HOT_SET_TEMP_4__200_oF_95_oC )
            {
                gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;
                play_melody_warning_197();
            }
            else
            {
                play_melody_setting_on_198();
            }
        }
        else if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )
        {
            /*..hui [24-11-26오후 4:48:27] 4단계인데 온수설정 3단계 or 4단계 설정으로 온경우..*/
            if( gu8_hot_default_temp == HOT_SET_TEMP_4__200_oF_95_oC || gu8_hot_default_temp == HOT_SET_TEMP_3__185_oF_85_oC )
            {
                gu8_hot_default_temp = HOT_SET_TEMP_2__170_oF_77_oC;
                play_melody_warning_197();
            }
            else
            {
                play_melody_setting_on_198();
            }
        }
        else
        {
            play_melody_setting_on_198();
        }
    }
    else
    {
        play_melody_warning_197();
    }


    #if 0
    if( mu16_setting <= 3 )
    {
        if( mu16_setting == 0 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_1__110_oF_43_oC;
        }
        else if( mu16_setting == 1 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_2__170_oF_77_oC;
        }
        else if( mu16_setting == 2 )
        {
            gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;
        }
        else /*if( mu16_setting == 3 )*/
        {
            gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
        }

        play_melody_setting_on_198();
    }
    else
    {
        play_melody_warning_197();
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_default_cup( U16 mu16_setting )
{
    /*if( mu16_setting <= 8 )*/
    /*if( mu16_setting <= 9 )*/
    /*..hui [23-10-4오후 3:24:02] 32 OZ 미사용..*/
    if( mu16_setting <= 9 && mu16_setting != 8 )
    {
        if( mu16_setting == 0 )
        {
            gu8Cup_level_Default = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( mu16_setting == 1 )
        {
            gu8Cup_level_Default = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( mu16_setting == 2 )
        {
            gu8Cup_level_Default = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( mu16_setting == 3 )
        {
            gu8Cup_level_Default = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( mu16_setting == 4 )
        {
            gu8Cup_level_Default = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( mu16_setting == 5 )
        {
            gu8Cup_level_Default = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( mu16_setting == 6 )
        {
            gu8Cup_level_Default = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( mu16_setting == 7 )
        {
            gu8Cup_level_Default = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( mu16_setting == 8 )
        {
            gu8Cup_level_Default = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else /*if( mu16_setting == 9 )*/
        {
            gu8Cup_level_Default = CUP_LEVEL__CONTINUE;
        }

        play_melody_setting_on_198();

        /*..hui [24-1-29오후 2:53:00] 현재 선택 용량 즉시 변경..*/
        gu8Cup_level = gu8Cup_level_Default;
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
void wifi_4_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit0_4_Oz_Select__120_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit0_4_Oz_Select__120_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_6_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit1_6_Oz_Select__175_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit1_6_Oz_Select__175_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_8_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit2_8_Oz_Select__235_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit2_8_Oz_Select__235_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_10_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit3_10_Oz_Select__295_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit3_10_Oz_Select__295_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_12_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit4_12_Oz_Select__355_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit4_12_Oz_Select__355_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_14_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit5_14_Oz_Select__415_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit5_14_Oz_Select__415_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_16_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit6_16_Oz_Select__475_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit6_16_Oz_Select__475_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_20_oz_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit7_20_Oz_Select__590_ml = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit7_20_Oz_Select__590_ml = SET;
            play_melody_setting_on_198();
        }
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
void wifi_32_oz_water_using( U16 mu16_setting )
{
    #if 0
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit8_32_Oz_Select__945_ml = CLEAR;
            BuzStep(BUZZER_CANCEL);
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit8_32_Oz_Select__945_ml = SET;
            BuzStep(BUZZER_SETUP);
        }
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
    #endif

    play_melody_warning_197();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_continue_water_using( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            Bit9_Continue_Select__Continue = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            Bit9_Continue_Select__Continue = SET;
            play_melody_setting_on_198();
        }
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
void wifi_cup_level_order( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            gu8_cup_level_order = CUP_LEVEL_ORDER__UP;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 1 )*/
        {
            gu8_cup_level_order = CUP_LEVEL_ORDER__DOWN;
            play_melody_setting_on_198();
        }
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
void wifi_hot_temp_level_order( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__UP;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 1 )*/
        {
            gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__DOWN;
            play_melody_setting_on_198();
        }
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
void wifi_oF_oC_select( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            gu8_oF__oC_select = Fahrenheit_oF_SELECT;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 1 )*/
        {
            gu8_oF__oC_select = Celsius_oC_SELECT;
            play_melody_setting_on_198();
        }
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
void wifi_Oz_mL_select( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            gu8_ml__oz_select = Oz_SELECT;
            play_melody_setting_on_198();
        }
        else /*if( mu16_setting == 1 )*/
        {
            gu8_ml__oz_select = mL_SELECT;
            play_melody_setting_on_198();
        }
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
void wifi_period_ster_hour( U16 mu16_setting )
{
    #if 0
    if( mu16_setting <= 23 )
    {
        gu8_wifi_period_ster_hour = (U8)mu16_setting;
        /*BuzStep(BUZZER_SETUP);*/
    }
    else
    {
        /*BuzStep(BUZZER_ERROR);*/
    }
    #endif

    gu8_temporary_period_ster_hour = (U8)mu16_setting;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_period_ster_minute( U16 mu16_setting )
{
    #if 0
    if( mu16_setting <= 59 )
    {
        gu8_wifi_period_ster_minute = (U8)mu16_setting;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
    #endif

    gu8_temporary_period_ster_minute = (U8)mu16_setting;

    if( gu8_temporary_period_ster_hour <= 23 && gu8_temporary_period_ster_minute <= 59 )
    {
        gu8_wifi_period_ster_hour = gu8_temporary_period_ster_hour;
        gu8_wifi_period_ster_minute = gu8_temporary_period_ster_minute;
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
void wifi_sleep_mode_enable( U16 mu16_setting )
{
    if( mu16_setting <= 1 )
    {
        if( mu16_setting == 0 )
        {
            bit_sleep_mode_enable = CLEAR;
            play_melody_setting_off_199();
        }
        else /*if( mu16_setting == 1 )*/
        {
            bit_sleep_mode_enable = SET;
            play_melody_setting_on_198();
        }
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
void wifi_sleep_start_hour( U16 mu16_setting )
{
    #if 0
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
    #if 0
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
    #if 0
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
    #if 0
    if( mu16_setting <= 59 )
    {
        gu8_sleep_mode_finish_minute = (U8)mu16_setting;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
    #endif

    gu8_temporary_sleep_mode_finish_minute = (U8)mu16_setting;


    if( gu8_temporary_sleep_mode_start_hour <= 23 && gu8_temporary_sleep_mode_start_minute <= 59
        && gu8_temporary_sleep_mode_finish_hour <= 23 && gu8_temporary_sleep_mode_finish_minute <= 59 )
    {
        gu8_sleep_mode_start_hour = gu8_temporary_sleep_mode_start_hour;
        gu8_sleep_mode_start_minute = gu8_temporary_sleep_mode_start_minute;
        gu8_sleep_mode_finish_hour = gu8_temporary_sleep_mode_finish_hour;
        gu8_sleep_mode_finish_minute = gu8_temporary_sleep_mode_finish_minute;
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
void wifi_unused_setting_time( U16 mu16_setting )
{
    if( mu16_setting >= USE_SAVE_LEARNEND_MODE_MIN_TIME && mu16_setting <= USE_SAVE_LEARNEND_MODE_MAX_TIME)
    {
        gu8_wifi_smart_unused_setting_time = (U8)mu16_setting;
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
void wifi_voice( U16 mu16_setting )
{
    if( mu16_setting == 3 )
    {
        gu8Sound_Type = SOUND_TYPE_VOICE;
        play_voice_sound_setting_voice_129();
    }
    else if( mu16_setting == 2 )
    {
        gu8Sound_Type = SOUND_TYPE_MELODY;
        play_voice_sound_setting_melody_130();
    }
    else if( mu16_setting == 1 )
    {
        gu8Sound_Type = SOUND_TYPE_MUTE;
        play_voice_sound_setting_mute_131();
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
void wifi_volume( U16 mu16_setting )
{
    if( mu16_setting == 1 )
    {
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_1;
    }
    else if( mu16_setting == 2 )
    {
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_2;
    }
    else if( mu16_setting == 3 )
    {
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_3;
    }
    else if( mu16_setting == 4 )
    {
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_4;
    }
    else /*if( mu16_setting == 5 )*/
    {
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_5;
    }

    play_melody_setting_on_198();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_voice_language( U16 mu16_setting )
{
    if( mu16_setting <= LANGUAGE_MAX )
    {
        if( mu16_setting == 0 )
        {
            gu8_voice_language_type = LANGUAGE_TYPE_KOREA;
        }
        else if( mu16_setting == 1 )
        {
            gu8_voice_language_type = LANGUAGE_TYPE_ENGLISH;
        }
        else if( mu16_setting == 2 )
        {
            gu8_voice_language_type = LANGUAGE_TYPE_SPANISH;
        }
        else if( mu16_setting == 3 )
        {
            gu8_voice_language_type = LANGUAGE_TYPE_CHINESE;
        }
        else /*if( mu16_setting == 4 )*/
        {
            gu8_voice_language_type = LANGUAGE_TYPE_FRANCE;
        }

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
        if( bit_self_test_start == SET )
        {
            if( bit_self_test_stop == CLEAR )
            {
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
        if( bit_self_test_start == CLEAR )
        {
            /*bit_self_test_start = SET;*/

            /*..hui [21-9-8오전 11:02:26] 이쪽에서 한번 더 막아줌..*/
            if( gu8_wifi_self_test_state == WIFI_SELF_TEST_NO_OPERATION )
            {
                start_self_test();
            }
            else{}
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_filter_change_type( U16 mu16_setting )
{
    if( mu16_setting == 1 )
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
        play_melody_setting_on_198();
    }
    else if( mu16_setting == 3 )
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_RO_INO_ALL;
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



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
#include    "Key_Handling.h"
#include "WIFI_SetFunctionData.h"


void key_setting_select_job(void);
void key_ice_select_job(void);
void key_hot_water_select_job(void);
void key_ambient_water_select_job(void);
void hot_setting_change(void);

void key_cold_water_select_job(void);
void key_amount_select_job(void);
void cup_select_order_up(void);
void cup_select_order_down(void);

void key_setting_ice_first(void);
void key_setting_ice_lock(void);
void key_setting_hot_lock(void);
void key_setting_touch_lock(void);
void key_select_touch_lock(void);
//void key_setting_extra_cold(void);
//void key_setting_steam_off(void);

void key_manual_ice_tank_ster(void);
void setting_buzzer( U8 mu8_setting );
void key_setting_eco_mode(void);
void key_change_unit(void);
void key_sound_change_job(void);
void key_change_language(void);
void change_hot_default_altitude(void);


//================================== Key Flag
bit F_KeySet;
bit F_ExtractKeySet;
bit F_TestKeySet;
bit F_LongKeySet;
bit F_IceKeySet;
bit F_Cold_Enable;
bit F_ColdOut;
bit F_ColdOn;
bit F_ColdOff;
bit F_Hot_Enable;
bit F_HotOut;
bit F_HotOn;
bit F_HotOff;
bit F_Room;
bit F_RoomOut;
bit F_Save;
bit F_Conty;
bit F_ContyGo;
bit F_Hot_Lock;
bit F_All_Lock;
bit F_Ice;
bit F_BeIce;
bit F_IceOn;
bit F_Ice_Lock;
bit F_IceOut;
bit F_IceOutStop;
bit F_LEDOff;
bit F_ColdSet;
bit F_HotSet;
bit F_IcemakeSet;
bit F_SaveSet;
bit F_KeySetBuz;
bit F_SterAuto;
bit F_SterLED;
bit F_Altitude;
bit Be_COMP;
bit Be_EW_POW;
bit Be_F_EWDrainPump;
//================================== S/W 센서
bit F_Out;
bit F_BeOut;
bit F_OutSet;
bit F_WaterOut;

U8 gu8LockFlick;
bit F_Mute_Enable;
bit F_Mute_Enable_Old;



bit F_Hot_Temp_Setting;
bit F_Circul_Drain;


bit F_Extraction_LED_Display_Mode;
bit F_Extraction_LED_Display_Mode_Old;




bit bit_fast_ice_make;

bit F_Ice_Make_Priority_Setting_Mode;

U8 gu8_ice_make_priority_settiong_time;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        Bit2_Settings_Switch_Indicator = SET;
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_melody_warning_197();

        if( bit_ice_ster_test_debug_start == SET )
        {
            gu8_ice_ster_test_debug_step++;

            if( gu8_ice_ster_test_debug_step >= 5 )
            {
                gu8_ice_ster_test_debug_step = 0;
            }
            else{}
        }
        else{}

        return;
    }
    else{}

    if( bit_debug_mode_start == SET
        && gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        gu8_fnd_debug_step++;

        if( gu8_fnd_debug_step > DEBUG__INO_STER_DRAIN_ERR)
        {
            gu8_fnd_debug_step = DEBUG__COMP_DELAY;
        }
        else{}

        gu8_debug_timer = 0;
    }
    else{}

    if( bit_setting_mode_start == SET )
    {
        bit_setting_mode_start = CLEAR;
        play_melody_setting_off_199();
    }
    else
    {
        if( F_WaterOut == SET || F_Ice == SET )
        {
            play_melody_warning_197();
        }
        else
        {
            play_melody_select_196();
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ice_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        start_all_lock_flick();
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
        play_melody_warning_197();
        return;
    }
    else{}


    if( bit_debug_mode_start == SET
        && gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        if( gu8_fnd_debug_step <= DEBUG__COMP_DELAY)
        {
            gu8_fnd_debug_step = DEBUG__INO_STER_DRAIN_ERR;
        }
        else
        {
            gu8_fnd_debug_step--;
        }

        gu8_debug_timer = 0;
    }
    else{}

    if( F_WaterOut == SET || F_Ice == SET )
    {
        play_melody_warning_197();
    }
    else
    {
        /*play_melody_select_196();*/
        if( F_IceOn == CLEAR )
        {
            start_ice_off_flick();
            /*..hui [24-4-3오후 4:29:57] 얼음 OFF 상태에서 얼음 버튼 선택시 OFF 표시..*/
            start_button_set_display( BUTTON_SET_ICE_OFF_DISPLAY );
            /*..hui [24-4-3오후 4:28:04] 얼음 OFF했을때 얼음 버튼 짧게 누르면 음성 출력..*/
            play_voice_ice_off_ice_select_99();
        }
        else
        {
            play_melody_select_196();
        }
    }


    #if 0
    if( bit_debug_mode_start == SET
        && gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        if( gu8_fnd_debug_step <= DEBUG__COMP_DELAY)
        {
            gu8_fnd_debug_step = DEBUG__INO_WATER_USAGE;
        }
        else
        {
            gu8_fnd_debug_step--;
        }

        gu8_debug_timer = 0;
    }
    else
    {
        if( F_WaterOut == SET || F_Ice == SET )
        {
            play_melody_warning_197();
        }
        else
        {
            play_melody_select_196();
        }

    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_hot_water_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        gu8AltitudeStep++;

        /*if( gu8AltitudeStep > ALTITUDE_3_MODE_LOW )*/
        if( gu8AltitudeStep > ALTITUDE_4_MODE_VERY_LOW )
        {
            gu8AltitudeStep = 0;
        }
        else{}

        gu8_altitude_return_time = 0;

        /*..hui [24-11-26오후 4:34:18] 고도모드 변경에따른 온수 디폴트 온도 변경..*/
        change_hot_default_altitude();

        play_melody_select_196();

        send_wifi_each_data_control( WIFI_FUNC_003D_HEIGHT_SEL );
        /*send_wifi_each_data_control( WIFI_FUNC_0065_DEFAULT_TEMP_SEL );*/

        return;
    }
    else{}


    if( bit_time_setting_start == SET )
    {
        Bit0_Hot_Minus_Indicator = SET;
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if( F_WaterOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}


    /*..hui [19-10-7오후 3:24:23] 팝업 노출 순위 뒤로..*/
    if(F_Hot_Lock == SET)
    {
        /*Bit1_Hot_Lock_Indicator = SET;*/
        start_hot_lock_flick();
        /*play_melody_warning_197();*/
        play_voice_hot_lcok_hot_select_93();
        return;
    }
    else{}

    /*..hui [23-5-31오후 2:06:19] 온수 최초 선택했을때만 표시하도록..*/
    if( u8WaterOutState != HOT_WATER_SELECT && F_Hot_Enable == CLEAR )
    {
        start_hot_off_flick();
        /*..hui [23-5-12오후 3:18:12] 온수 OFF 상태에서 온수 선택시에도 OFF 표시..*/
        start_button_set_display( BUTTON_SET_HOT_DISPLAY );
        /*play_melody_warning_197();*/
        play_voice_hot_off_hot_select_94();
    }
    else
    {
        /*play_melody_select_196();*/

        if( u8WaterOutState != HOT_WATER_SELECT )
        {
            /*..hui [23-12-15오후 4:19:07] 정수 과열에러도.. 히터 고장으로 오버히팅....*/
            /*if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                || Bit1_Room_OverHeat_Error__E49 )*/
            if( Bit3_Leakage_Sensor_Error__E01 == SET )
            {
                play_voice_leakage_error_12();
            }
            /*else if( Bit1_Hot_Operation_Disable_State == SET )*/
            else if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                     || Bit1_Room_OverHeat_Error__E49 == SET )
            {
                /*..hui [24-1-10오후 3:39:50] 온수에러 음성은 온수센서 에러, 정수 과열 에러만..*/
                play_voice_hot_error_9();
            }
            else if( Bit1_Front_New_Led_Hot_Heating_Text == SET )
            {
                play_voice_hot_heating_109();
            }
            else
            {
                play_melody_select_196();
            }
        }
        else
        {
            play_melody_select_196();
        }
    }

    gu16_water_select_return_time = 0;


    if(u8WaterOutState != HOT_WATER_SELECT)
    {
        /*hot_water_32_oz_pass();*/

        u8WaterOutState = HOT_WATER_SELECT;

        stop_cooling_breath();

        #if 0
        /*..hui [23-7-26오전 10:53:58] 가열중 -> 현재온도 표시 -> 냉/정 -> 온수버튼 -> 이전 가열중 화면으로..*/
        if( bit_hot_preheating_start == SET )
        {
            /*..hui [23-5-30오후 2:44:23] 프리히팅한 온도로 복귀..*/
            gu8_hot_setting_temperature = gu8_preheating_set_temp;
            gu8_hot_prepare_stage = HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON;
        }
        else
        {
            /*..hui [18-8-14오후 1:31:34] 온수온도 디폴트는 무조건 커피..*/
            /*..hui [23-5-11오후 4:29:49] 디폴트 온수온도 85도로 변경.. 85가 사용 빈도가 더 높음?..*/
            /*gu8_hot_setting_temperature = HOT_SET_TEMP_3__185_oF_85_oC;*/
            gu8_hot_setting_temperature = gu8_hot_default_temp;
        }

        /*..hui [23-9-1오후 4:45:24] 저수위 디밍하던거 정지..*/
        stop_low_water_breath();
        #endif

        /*..hui [18-8-14오후 1:31:34] 온수온도 디폴트는 무조건 커피..*/
        /*..hui [23-5-11오후 4:29:49] 디폴트 온수온도 85도로 변경.. 85가 사용 빈도가 더 높음?..*/
        /*gu8_hot_setting_temperature = HOT_SET_TEMP_3__185_oF_85_oC;*/
        gu8_hot_setting_temperature = gu8_hot_default_temp;

        /*..hui [23-9-25오후 3:37:28] 키 조작으로 선택 변경시에만 A1014만 보냄..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else
    {
        #if 0
        if( bit_hot_preheating_start == SET )
        {
            if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON )
            {
                gu8_hot_prepare_stage = HOT_PREPARE_STAGE_3_HOT_KEY_SETTING;
                hot_setting_change();
            }
            else if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING )
            {
                gu8_hot_prepare_stage = HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON;
                /*start_hot_preheating();*/
            }
            else if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_5_HOT_EXTRACT_FINISH )
            {
                stop_hot_preheating();
            }
            else
            {
                hot_setting_change();
            }
        }
        else
        {
            hot_setting_change();
        }
        #endif

        hot_setting_change();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_setting_change(void)
{
    if( gu8_hot_level_order == HOT_TEMP_LEVEL_ORDER__UP )
    {
        if( gu8_hot_setting_temperature > HOT_SET_TEMP_4__200_oF_95_oC )
        {
            gu8_hot_setting_temperature--;
        }
        else
        {
            gu8_hot_setting_temperature = HOT_SET_TEMP_1__110_oF_43_oC;
        }
    }
    else
    {
        if( gu8_hot_setting_temperature < HOT_SET_TEMP_1__110_oF_43_oC )
        {
            gu8_hot_setting_temperature++;
        }
        else
        {
            gu8_hot_setting_temperature = HOT_SET_TEMP_4__200_oF_95_oC;
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ambient_water_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*..hui [24-7-18오후 2:20:10] 전체잠금중 점유인증시 입력 가능하도록..*/
        if( gu8_Wifi_Cert_State == WIFI_CERTIFICATE_ON )
        {
            /*..hui [24-7-18오후 2:23:02] 점유인증중이면 띵..*/
            play_melody_select_196();
        }
        else
        {
            /*play_melody_warning_197();*/
            play_voice_all_lock_select_103();
            start_all_lock_flick();
        }

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
        play_melody_warning_197();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if(F_WaterOut == SET)
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        u8WaterOutState = PURE_WATER_SELECT;
        /*..hui [23-9-1오후 4:45:24] 저수위 디밍 정지..*/
        /*stop_low_water_breath();*/
        stop_cooling_breath();

        /*..hui [23-9-25오후 3:37:28] 키 조작으로 선택 변경시에만 A1014만 보냄..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );

        if( Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            play_voice_leakage_error_12();
        }
        else
        {
            play_melody_select_196();
        }
    }
    else
    {
        play_melody_select_196();
    }

    gu16_water_select_return_time = 0;

    /*play_melody_select_196();*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cold_water_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        key_change_filter_type();
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        Bit1_Cold_Plus_Indicator = SET;
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if(F_WaterOut == SET)
    {
        play_melody_warning_197();
        return;
    }
    else{}

    #if 0
    if(F_Cold_Enable == CLEAR)
    {
        start_cold_off_flick();
        play_melody_warning_197();
    }
    else
    {
        play_melody_select_196();
    }
    #endif


    /*u8WaterOutState = COLD_WATER_SELECT;*/

    if( u8WaterOutState != COLD_WATER_SELECT )
    {
        u8WaterOutState = COLD_WATER_SELECT;

        if( Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            play_voice_leakage_error_12();
        }
        else if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET
            /*|| Bit4_Room_Low_Water_Level_Error__E21 == SET*/
            || Bit7_BLDC_Communication_Error__E27 == SET
            || bit_bldc_operation_error_total == SET )
        {
            /*..hui [23-12-15오후 4:14:02] 냉수에러 음성 추가..*/
            /*..hui [24-1-10오후 3:38:37] 냉수 에러 음성은.. 냉수센서 에러, 컴프 에러일때만 출력하기로.. 함재진..*/
            play_voice_cold_error_7();
        }
        else if( Bit2_Front_New_Led_Cold_Cooling_Text == SET )
        {
            start_cooling_breath();
            play_voice_cold_cooling_111();
        }
        else
        {
            play_melody_select_196();
        }

        /*..hui [23-9-25오후 3:37:28] 키 조작으로 선택 변경시에만 A1014만 보냄..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else
    {
        play_melody_select_196();
    }

    gu16_water_select_return_time = 0;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_amount_select_job(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        start_all_lock_flick();
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
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        play_melody_select_196();

        gu8_memento_display_num++;

        if( gu8_memento_display_num > 4 )
        {
            gu8_memento_display_num = 0;
        }
        else{}

        return;
    }
    else{}

    gu8_cup_level_time_init = SET;
    /*..hui [19-8-22오후 2:45:46] 온수 선택 중 사용자/물량 버튼 눌릴 경우 복귀 시간 초기화..캐럿 사양..*/
    gu8_hot_select_time_init = SET;

    if( F_WaterOut != SET )
    {
        if( gu8_cup_level_order == CUP_LEVEL_ORDER__UP )
        {
            cup_select_order_up();
        }
        else
        {
            cup_select_order_down();
        }

        /*..hui [20-1-7오전 9:56:14] 물량 선택 LED 표시용..*/
        gu8_cup_led_select = SET;

        play_melody_select_196();
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
void cup_select_order_up(void)
{
    U8 mu8_pass_cup = 0;

    #if 0
    /*..hui [23-7-26오후 7:40:48] 온수에서는 32Oz 표시 안함..*/
    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( Bit8_32_Oz_Select__945_ml == SET )
        {
            mu8_pass_cup = SET;
        }
        else{}
    }
    else{}
    #endif

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else{}
    }
    else if(gu8Cup_level == CUP_LEVEL__12_OZ__355_ML)
    {
        if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else{}
    }
    else if(gu8Cup_level == CUP_LEVEL__16_OZ__475_ML)
    {
        if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        #if 0
        if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        else
        #endif

        if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else{}
    }

    #if 0
    else if( gu8Cup_level == CUP_LEVEL__32_OZ__945_ML )
    {
        if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else{}
    }
    #endif

    else if( gu8Cup_level == CUP_LEVEL__CONTINUE )
    {
        if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else{}
    }
    else
    {
        gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_select_order_down(void)
{
    U8 mu8_pass_cup = 0;

    #if 0
    /*..hui [23-7-26오후 7:40:48] 온수에서는 32Oz 표시 안함..*/
    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( Bit8_32_Oz_Select__945_ml == SET )
        {
            mu8_pass_cup = SET;
        }
        else{}
    }
    else{}
    #endif

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else{}

    }
    else if(gu8Cup_level == CUP_LEVEL__12_OZ__355_ML)
    {
        if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else{}

    }
    else if(gu8Cup_level == CUP_LEVEL__16_OZ__475_ML)
    {
        if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        #if 0
        else if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        #endif
        else{}

    }

    #if 0
    else if( gu8Cup_level == CUP_LEVEL__32_OZ__945_ML )
    {
        if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else if( Bit9_Continue_Select__Continue == SET )
        {
            gu8Cup_level = CUP_LEVEL__CONTINUE;
        }
        else{}

    }
    #endif

    else if( gu8Cup_level == CUP_LEVEL__CONTINUE )
    {
        #if 0
        if( Bit8_32_Oz_Select__945_ml == SET && mu8_pass_cup == CLEAR )
        {
            gu8Cup_level = CUP_LEVEL__32_OZ__945_ML;
        }
        else
        #endif

        if( Bit7_20_Oz_Select__590_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__20_OZ__590_ML;
        }
        else if( Bit6_16_Oz_Select__475_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__16_OZ__475_ML;
        }
        else if( Bit5_14_Oz_Select__415_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__14_OZ__415_ML;
        }
        else if( Bit4_12_Oz_Select__355_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__12_OZ__355_ML;
        }
        else if( Bit3_10_Oz_Select__295_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__10_OZ__295_ML;
        }
        else if( Bit2_8_Oz_Select__235_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__8_OZ__235_ML;
        }
        else if( Bit1_6_Oz_Select__175_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__6_OZ__175_ML;
        }
        else if( Bit0_4_Oz_Select__120_ml == SET )
        {
            gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
        }
        else{}

    }
    else
    {
        gu8Cup_level = CUP_LEVEL__4_OZ__120_ML;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_ice_first(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    if( bit_fast_ice_make == COLD_FIRST_ICE_MAKE )
    {
        bit_fast_ice_make = ICE_FIRST_ICE_MAKE;
        play_melody_setting_on_198();
    }
    else
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        play_melody_setting_off_199();
    }

    send_wifi_each_data_control( WIFI_FUNC_0008_ICE_SEL );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_ice_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    F_Ice_Lock = ~F_Ice_Lock;

    /*setting_buzzer( (U8)F_Ice_Lock );*/

    if( F_Ice_Lock == SET )
    {
        play_voice_setting_ice_lock_on_147();
    }
    else
    {
        play_voice_setting_ice_lock_off_148();
    }


    send_wifi_each_data_control( WIFI_FUNC_0032_ICELOCK_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_hot_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    F_Hot_Lock = ~F_Hot_Lock;
    ///////////////setting_buzzer( (U8)F_Hot_Lock );

    if( F_Hot_Lock == SET )
    {
        play_voice_setting_hot_lock_on_112();

        /*..hui [24-1-19오후 2:23:12] 온수 선택 상태 -> 온수잠금 시 온수 선택상태 해제되도록..*/
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            water_select_return_timer_control(1);
        }
        else{}
    }
    else
    {
        play_voice_setting_hot_lock_off_113();
    }





    send_wifi_each_data_control( WIFI_FUNC_0003_HOT_LOCK_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_touch_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        key_select_touch_lock();
        return;
    }
    else{}

    F_All_Lock = SET;
    /////play_melody_setting_on_198();
    play_voice_all_lock_start_127();

    bit_setting_mode_start = CLEAR;

    send_wifi_each_data_control( WIFI_FUNC_0005_LOCK_SEL );



    #if 0
    if( F_All_Lock != SET )
    {
        F_All_Lock = SET;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        F_All_Lock = CLEAR;
        BuzStep(BUZZER_CANCEL);
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_select_touch_lock(void)
{
    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        /*..hui [23-5-12오후 3:50:45] 전체잠금 선택된 상태에서 터치락 버튼 누르면 점멸 제외하는걸로..*/
        /*start_all_lock_flick();*/
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_manual_ice_tank_ster(void)
{
    if( bit_setting_mode_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    #if 0
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( Bit3_Ice_Tank_Ster_Operation_Disable_State == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}
    #endif

    /*..hui [23-5-22오후 7:17:44] 우선 물추출, 얼음추출중에는 막는걸로..*/
    if( F_WaterOut == SET || F_Ice == SET )
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

    /*bit_setting_mode_start = CLEAR;*/

    if( bit_ice_tank_ster_start != SET )
    {
        #if 0
        if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
        {
            BuzStep(BUZZER_ERROR);
            return;
        }
        else{}
        #endif

        if( gu8_Room_Water_Level != ROOM_LEVEL_FULL )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        if( Bit3_Ice_Tank_Ster_Operation_Disable_State == SET )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        if( F_Tank_Cover_Input == CLEAR )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        /*..hui [23-7-28오후 3:42:30] 중간에 사이드커버, RO 필터 열림 감지되면 정지..*/
        /*if( bit_filter_cover == CLEAR || bit_ro_filter_2_reed == CLEAR )*/
        if( bit_filter_all == CLEAR )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        /*..hui [23-8-24오후 5:43:29] 냉수온도 35도 이상일 경우 수동도 막음.. 이정환 부장님..*/
        /*if( gu8_Cold_Temperature_One_Degree >= STER_NO_OPERATION_COLD_TEMP )*/
        /*..hui [23-9-6오후 2:10:08] 이정환부장님.. 냉수가 아니라 정수온도를 보자..*/
        #if 0
        if( gu8_Room_Temperature_One_Degree > STER_NO_OPERATION_COLD_TEMP )
        {
            BuzStep(BUZZER_ERROR);
            return;
        }
        else{}
        #endif

        /*..hui [23-10-4오후 2:44:53] 냉수/정수 온도 둘 다 15도 이하여야 수동 세척 가능..*/
        /*..hui [23-10-4오후 2:45:18] 냉수 30도일때 수동세척 하면 냉수 온도가 42도까지 올라감..*/
        /*..hui [23-10-4오후 2:45:26] 이정환 부장님 요청..*/
        if( gu8_Cold_Temperature_One_Degree > STER_NO_OPERATION_COLD_TEMP )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        /*..hui [23-10-27오전 11:53:23] 온수온도 90도 미만일경우 시작 금지.. 정상적인 테스트를 위해서..*/
        /*if( gu8_Hot_Tank_Temperature_One_Degree < 90 )*/
        /*if( gu8_Hot_Tank_Temperature_One_Degree <= 92 )*/
        /*if( gu8_Hot_Tank_Temperature_One_Degree < HOT_SPRAY_STATE_START_HOT_TEMP )*/
        if( gu8_Hot_Tank_Temperature_One_Degree < gu8_hot_spray_start_hot_temp )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        #if 0
        /*..hui [23-8-28오후 4:49:26] 수동 세척.. 하루 최대 1회까지만..*/
        if( gu8_manual_operation_count >= 1 )
        {
            BuzStep(BUZZER_ERROR);
            return;
        }
        else{}
        #endif

        #if 0
        if( F_IceInit == SET )
        {
            BuzStep(BUZZER_ERROR);
            return;
        }
        else{}
        #endif

        /*..hui [23-10-27오전 11:56:29] 더미탈빙중이었으면 더미탈빙 취소..*/
        if( F_IceInit == SET )
        {
            F_IceInit = CLEAR;
            gu8InitStep = 0;
            gu16IceMakeTime = 0;
            gu16IceHeaterTime = 0;
        }
        else{}

        bit_ice_tank_ster_start = SET;
        play_melody_setting_on_198();

        /*gu8_hot_ster_temp_mode = HOT_STER_TEMP_LOW_MODE;*/

        start_ice_tank_ster();
        gu8_manual_operation_count++;
    }
    else
    {
        bit_ice_tank_ster_start = CLEAR;
        play_melody_setting_off_199();

        stop_ice_tank_ster();
    }

    /*start_set_flick( ON_OFF_DISPLAY_STEAM_OFF_SET );*/

}









/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_buzzer( U8 mu8_setting )
{
    if(mu8_setting == SET)
    {
        play_melody_setting_on_198();
    }
    else
    {
        play_melody_setting_off_199();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_eco_mode(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}

    /*..hui [23-12-15오전 11:05:52] 에코모드 설정된 상태에서 시간 설정 지워지면 해제는 가능하도록..*/
    if( bit_sleep_mode_enable == SET )
    {
        bit_sleep_mode_enable = !bit_sleep_mode_enable;
        setting_buzzer( (U8)bit_sleep_mode_enable );
        return;
    }
    else{}

    if( bit_first_time_setting == CLEAR )
    {
        /*play_melody_warning_197();*/
        play_voice_eco_mode_time_set_100();
        return;
    }
    else{}

    #if 0
    F_Save = !F_Save;

    setting_buzzer( (U8)F_Save );
    #endif

    bit_sleep_mode_enable = !bit_sleep_mode_enable;

    setting_buzzer( (U8)bit_sleep_mode_enable );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_change_unit(void)
{
    /*..hui [23-7-14오전 10:28:53] 테스트용 나중에 지워야함..*/
    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        gu8_oF__oC_select = Celsius_oC_SELECT;
        gu8_ml__oz_select = mL_SELECT;
    }
    else
    {
        gu8_oF__oC_select = Fahrenheit_oF_SELECT;
        gu8_ml__oz_select = Oz_SELECT;
    }

    play_melody_setting_on_198();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_sound_change_job(void)
{
    if( bit_sound_setting_start != SET )
    {
        return;
    }
    else{}

    gu8_sound_setting_return_time = 0;

    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        gu8Sound_Type = SOUND_TYPE_MELODY;
        play_voice_sound_setting_melody_130();
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        gu8Sound_Type = SOUND_TYPE_MUTE;
        play_voice_sound_setting_mute_131();
    }
    else /*if( gu8Sound_Type == SOUND_TYPE_MUTE )*/
    {
        gu8Sound_Type = SOUND_TYPE_VOICE;
        play_voice_sound_setting_voice_129();
    }


    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        gu8Sound_Type = SOUND_TYPE_MUTE;
        play_voice_sound_setting_mute_131();
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        gu8Sound_Type = SOUND_TYPE_VOICE;
        play_voice_sound_setting_voice_129();
    }
    else /*if( gu8Sound_Type == SOUND_TYPE_MUTE )*/
    {
        gu8Sound_Type = SOUND_TYPE_MELODY;
        play_voice_sound_setting_melody_130();
    }
    #endif
    /////play_voice_sound_type();

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_change_language(void)
{
    if( gu8_voice_language_type == LANGUAGE_TYPE_KOREA )
    {
        gu8_voice_language_type = LANGUAGE_TYPE_ENGLISH;
        /*Play_Voice(VOICE_87_SETTING_MODE);*/
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
    else if( gu8_voice_language_type == LANGUAGE_TYPE_ENGLISH )
    {
        gu8_voice_language_type = LANGUAGE_TYPE_SPANISH;
        /*Play_Voice(VOICE_87_SETTING_MODE);*/
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
    else if( gu8_voice_language_type == LANGUAGE_TYPE_SPANISH )
    {
        gu8_voice_language_type = LANGUAGE_TYPE_CHINESE;
        /*Play_Voice(VOICE_87_SETTING_MODE);*/
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
    else if( gu8_voice_language_type == LANGUAGE_TYPE_CHINESE )
    {
        gu8_voice_language_type = LANGUAGE_TYPE_FRANCE;
        /*Play_Voice(VOICE_87_SETTING_MODE);*/
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
    else
    {
        gu8_voice_language_type = LANGUAGE_TYPE_KOREA;
        /*Play_Voice(VOICE_87_SETTING_MODE);*/
        Play_Voice(VOICE_132_SETTING_MODE_SOUND);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void change_hot_default_altitude(void)
{
    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
    }
    else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
    {
        gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;
    }
    else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
    {
        gu8_hot_default_temp = HOT_SET_TEMP_2__170_oF_77_oC;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


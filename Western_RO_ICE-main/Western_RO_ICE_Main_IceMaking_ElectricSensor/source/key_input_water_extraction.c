/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "key_input_water_extraction.h"

void input_water_extract_key(void);
void extract_key_management(void);

void Extract_Key_Short_Input(void);
void water_extract_key(void);
void effluent_time_decision(void);
void effluent_time_decision_normal(void);
void effluent_time_ambient_normal(void);
void effluent_time_cold_normal(void);
void effluent_time_hot_normal(void);

void effluent_time_decision_low_water(void);
void effluent_time_ambient_low_water(void);
void effluent_time_cold_low_water(void);
void effluent_time_hot_low_water(void);

void Extract_Key_Long_Input(void);

void water_extract_long_key(void);

void key_input_water_extract(void);
void Extract_Key_Very_Long_Input(void);
void Extract_No_Key(void);

U8  gu8_Key_Water_Extract;
U8  u8Extract_Key_Buffer;
U16  u16Extract_Key_Sampling_Counter;
bit F_Extract_Key_Short_Push_State;
bit F_Extract_Key_Long_Push_State;
bit F_Extract_Key_Very_Long_Push_State;

U8  u8Extract_Key_Input_Value;

U16  u16Extract_Key_Long_Counter;
U16  u16Extract_Key_Short_Counter;

U8  u8Efluent_Time;


U8  u8Extract_Continue;

U16 u16Efluent_Time;
bit F_ColdConty;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_water_extract(void)
{
    input_water_extract_key();
    extract_key_management();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_water_extract_key(void)
{
    if(gu8_Key_Water_Extract == u8Extract_Key_Buffer)
    {
        if(u8Extract_Key_Buffer == UKey_Mask)
        {
            u16Extract_Key_Sampling_Counter = 0;
            F_Extract_Key_Short_Push_State = CLEAR;
            F_Extract_Key_Long_Push_State = CLEAR;
            F_Extract_Key_Very_Long_Push_State = CLEAR;
        }
        else
        {
            u16Extract_Key_Sampling_Counter++;
        }

        if(u16Extract_Key_Sampling_Counter >= 1)
        {
            u16Extract_Key_Short_Counter = u16Extract_Key_Sampling_Counter;
            u16Extract_Key_Long_Counter++;

            /*..hui [19-11-19오후 4:26:26] 키 눌려있는동안 온수 복귀 카운터 초기화..*/
            /*gu16_water_select_return_time = 0;*/
        }
        else{}
    }
    else
    {
        u8Extract_Key_Buffer = gu8_Key_Water_Extract;

        u16Extract_Key_Sampling_Counter = 0;
        u16Extract_Key_Long_Counter = 0;
        u16Extract_Key_Short_Counter = 0;
    }
}
/***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void extract_key_management(void)
{
    if(F_Extract_Key_Short_Push_State == CLEAR)
    {
        if( (u16Extract_Key_Short_Counter >= 1) && (u16Extract_Key_Short_Counter < 2000) )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                Extract_Key_Short_Input();
            }
            else
            {
                PCB_Test_Mode_Extract_Key_Short_Input();
            }

            F_Extract_Key_Short_Push_State = SET;
            u16Extract_Key_Short_Counter = 0;
        }
        else{}
    }
    else
    {
        if(F_Extract_Key_Long_Push_State == CLEAR)
        {
            if( u16Extract_Key_Long_Counter >= 2000 )
            {
                F_Extract_Key_Long_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    Extract_Key_Long_Input();
                }
                else{}
            }
            else{}
        }
        else
        {
            if(F_Extract_Key_Very_Long_Push_State == CLEAR)
            {
                if( u16Extract_Key_Long_Counter >= 8000 )
                {
                    F_Extract_Key_Very_Long_Push_State = SET;
                    u16Extract_Key_Long_Counter = 0;

                    if(u8FactoryTestMode == NONE_TEST_MODE)
                    {
                        Extract_Key_Very_Long_Input();
                    }
                    else{}
                }
                else{}
            }
            else{}
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Short_Input(void)
{
    /////F_lcd_standby_input = SET;
    gu16_water_select_return_time = 0;
    /*gu8_clear_block_error = SET;*/

    auto_drain_key_off_check();
    power_saving_init();

    /*..hui [23-5-12오후 3:27:25] 버튼 설정 ON, OFF 표시중 버튼 누르면 표시 바로 종료..*/
    stop_button_set_display();
    /*..hui [24-4-25오후 7:12:26] LED 점멸중이던거 중지..*/
    off_all_flick();

    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    water_extract_key();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_key(void)
{
    //F_WaterOut == 0이면 추출..
    //F_WaterOut = SET;
    /*..hui [17-12-11오후 1:55:46] 0이면 미추출, 1이면 추출로 변경..헷갈려서....*/

    if( gu8_fota_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        //bit_wifi_pairing_start = CLEAR;
        finish_pairing_screen();
    }
    else{}

    if( bit_memento_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /*..hui [24-5-23오후 7:31:11] 구연산 세정할때..*/
    if( gu8_Led_Display_Step == LED_Display__ACID_CLEAN )
    {
        #if 0
        if( bit_acid_clean_start == SET )
        {
            if( gu8_acid_clean_step == 8 || gu8_acid_clean_step == 20 )
            {
                bit_acid_start_key = SET;
            }
            else
            {
                play_melody_warning_197();
            }

            return;
        }
        else{}
        #endif

        /*..hui [24-7-30오전 10:35:07] 구연산 세척때 단수에러 걸리면 버튼 누르면 해제..*/
        if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
        {
            gu8_clear_block_error = SET;
            play_melody_select_196();
        }
        else
        {
            play_melody_warning_197();
        }

        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FLUSHING )
    {
        if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
        {
            /*..hui [23-8-16오후 5:42:18] 단수에러 걸리면 추출 버튼으로도 단수 에러 해제되도록..*/
            if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
            {
                gu8_clear_block_error = SET;
                play_melody_select_196();
            }
            else
            {
                gu8_flushing_okay_key_indicator = SET;
            }
        }
        else if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
        {
            /*gu8_flushing_okay_key_indicator = SET;*/

            /*..hui [23-8-16오후 4:07:57] 실제 플러싱 하고있을때만 취소 가능하도록..*/
            /*..hui [23-8-16오후 4:08:03] 초기 ro 드레인시에는 취소 불가..*/
            if( gu8_flushing_step == 8 )
            {
                gu8_flushing_okay_key_indicator = SET;
            }
            else
            {
                play_melody_warning_197();
            }
        }
        else if( gu8_flushing_mode == FLUSHING_TANK_STATE )
        {
            /*if( gu8_flushing_tank_step == 2 || gu8_flushing_tank_step == 3 )*/
            /*..hui [23-8-23오전 10:41:30] 10 이하 모든 구간에서 취소 가능하도록..*/
            /*if( gu8_flushing_tank_step <= 10 )*/
            if( gu8_flushing_tank_step <= 15 )
            {
                gu8_flushing_okay_key_indicator = SET;
            }
            else
            {
                play_melody_warning_197();
            }
        }
        else
        {
            play_melody_warning_197();
        }

        return;
    }
    else{}


    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        /*play_melody_warning_197();*/
        if( bit_filter_cover == CLEAR )
        {
            /*..hui [23-12-19오후 3:36:52] 필터커버 열렸을때 추출버튼 누르면..*/
            play_voice_filter_cover_open_extract_89();
        }
        else
        {
            /*..hui [23-12-19오후 3:37:15] 필터 커버는 닫혀있고 필터 리드가 감지되지 않을때.. 이때는 띠링띠링..*/
            play_melody_warning_197();
        }

        return;
    }
    else{}


    /*..hui [23-2-9오후 2:03:49] 세팅모드에서는 부저음없이 추출안됨..*/
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
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

    if( bit_ct_filter_type_start == SET )
    {
        return;
    }
    else{}

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        start_all_lock_flick();
        /*play_melody_warning_197();*/
        play_voice_all_lock_select_103();
        return;
    }
    else{}

    /*..hui [23-5-22오후 4:16:36] 우선 온수살균할때 물 추출, 얼음 추출은 막는걸로..*/
    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode > STER_MODE_NONE_STATE )
        {
            /*play_melody_warning_197();*/
            play_voice_ice_tank_clean_extract_60();
            start_breath_steam_clean();
            return;
        }
        else{}
    }
    else{}

    /*..hui [18-3-14오후 3:07:31] 정량추출 완료되고 500ms 동안 물 추출 버튼 disable..*/
    if(F_WaterOut_Disable_State == SET)
    {
        return;
    }
    else{}

    /*..hui [19-8-22오후 1:44:22] 중수위 또는 만수위에서만 온수 추출 시작..*/
    if(u8WaterOutState == HOT_WATER_SELECT)
    {
        if( F_WaterOut == CLEAR )
        {
            /*..hui [23-5-31오후 1:48:50] 최초 만수위 감지 이전에도 저수위로 표시.. 일단..*/
            /*if( gu8_Room_Water_Level == ROOM_LEVEL_LOW || bit_hot_first_op == CLEAR )*/
            /*..hui [24-2-20오후 4:11:02] 최초 만수위 감지 이전이더라도 온수 추출은 가능하도록 변경....*/
            /*..hui [24-2-20오후 4:11:09] 고문석님 메일 참조..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                ////////////////play_melody_warning_197();
                play_voice_low_water_hot_room_out_108();
                /*start_low_water_breath();*/
                start_low_water_flick();
                return;
            }
            else{}
        }
        else{}
    }
    else{}

    if(u8WaterOutState == PURE_WATER_SELECT)
    {
        if( F_WaterOut == CLEAR )
        {
            /*..hui [23-7-17오전 9:16:09] 정수도 저수위일떄는 추출 금지.. 웨스턴ro 사양...*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                ////////////////play_melody_warning_197();
                play_voice_low_water_hot_room_out_108();
                /*start_low_water_breath();*/
                start_low_water_flick();
                return;
            }
            else{}
        }
        else{}
    }
    else{}

    /*..hui [23-4-25오후 12:05:48] 온수 오버히팅에 의한 정수 과열 에러 추가..*/
    /*..hui [23-4-25오후 12:05:55] 정수 과열 에러 발생 시 정수 추출 불가..*/
    /*if( u8WaterOutState == PURE_WATER_SELECT )*/
    /*..hui [23-8-23오후 12:16:12] 정수 냉수 한몸이므로 둘 다 차단..*/
    if( u8WaterOutState == PURE_WATER_SELECT || u8WaterOutState == COLD_WATER_SELECT )
    {
        if( F_WaterOut == CLEAR )
        {
            if( Bit1_Room_OverHeat_Error__E49 == SET )
            {
                play_melody_warning_197();
                gu8_error_popup_enable = SET;
                return;
            }
            else{}
        }
        else{}
    }
    else{}


    finish_filter_alarm();

    stop_cooling_breath();

    if( F_WaterOut == CLEAR )
    {
        F_WaterOut = SET;
        F_Effluent_OK = CLEAR;

        /*..hui [19-9-5오후 4:49:47] 연속추출이 메뉴속으로..*/
        if( gu8Cup_level == CUP_LEVEL__CONTINUE )
        {
            u8Extract_Continue = SET;
            /*BuzStep(BUZZER_EFFLUENT_CONTINUE);*/
            play_melody_continue_extract_start_192();
        }
        else
        {
            /*BuzStep(BUZZER_EFFLUENT);*/
            play_melody_normal_extract_start();
        }
    }
    else
    {
        F_WaterOut = CLEAR;
        u8Extract_Continue = CLEAR;
        /*BuzStep(BUZZER_EFFLUENT_END);*/
        play_melody_extract_complete_194();
        /*hot_extract_return();*/
    }

    if(F_WaterOut == SET)
    {
        if(u8Extract_Continue != SET)
        {
            effluent_time_decision();

            water_out_compensation();
            gu16_water_out_time = u16Efluent_Time;
            calc_mix_water();
            /*Pure_Temp_Compensation_time_Cold_Big();*/
        }
        else
        {
            u16Efluent_Time = EXTRACT_TIME_CONTINUE;
            gu16_water_out_time = u16Efluent_Time;
            calc_mix_water();
        }
    }
    else
    {
        u16Efluent_Time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_decision(void)
{
    #if 0
    U8 mu8_a = 0;
    U8 mu8_b = 0;


    mu8_b = TARGET_HOT_43_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_a = gu8_Hot_Tank_Temperature_One_Degree - TARGET_HOT_43_TEMP;

////////////////////////////////////////////////////////////////////////////////////////

    if( mu8_b <= mu8_a - 10 )
    {
        bit_big_mode = COLD__BIG;
    }
    else
    {
        bit_big_mode = HOT__BIG;
    }
    #endif


    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        effluent_time_decision_low_water();
    }
    else
    {
        effluent_time_decision_normal();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_decision_normal(void)
{
    if(u8WaterOutState == PURE_WATER_SELECT)
    {
        /*effluent_time_ambient_normal();*/


        /*..hui [23-10-18오전 9:35:23] 정수는 냉수랑 동일..*/
        effluent_time_cold_normal();

    }
    //else if(F_ColdOut == SET)
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        effluent_time_cold_normal();


    }
    else if(u8WaterOutState == HOT_WATER_SELECT)
    {
        #if 0
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )
        {
            if( bit_big_mode == HOT__BIG )
            {
                effluent_time_hot_normal();
            }
            else
            {
                effluent_time_cold_normal();
            }
        }
        else
        {
            effluent_time_hot_normal();
        }
        #endif


        effluent_time_hot_normal();
    }
    else
    {
        /*u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ;*/
        u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML;
    }

    /*gu16_water_out_time = u16Efluent_Time;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void effluent_time_ambient_normal(void)
{
    #if 0
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ;

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_6_OZ;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_8_OZ;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_10_OZ;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_12_OZ;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_14_OZ;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_16_OZ;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_20_OZ;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_32_OZ;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ;

            break;
    }
    #endif


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void effluent_time_cold_normal(void)
{
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML;

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_6_OZ_175_ML;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_8_OZ_235_ML;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_10_OZ_295_ML;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_12_OZ_355_ML;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_14_OZ_415_ML;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_16_OZ_475_ML;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_20_OZ_590_ML;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_32_OZ;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML;

            break;
    }



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void effluent_time_hot_normal(void)
{
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_4_OZ_120_ML;

            #if 0
            /*..hui [23-11-29오전 9:57:20] 43도 물량은 120ml에 맞추도록....*/
            if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
            {
                u16Efluent_Time = u16Efluent_Time + 11;
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
            {
                u16Efluent_Time = u16Efluent_Time + 6;
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
            {
                u16Efluent_Time = u16Efluent_Time + 2;
            }
            else{}
            #endif

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_6_OZ_175_ML;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_8_OZ_235_ML;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_10_OZ_295_ML;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_12_OZ_355_ML;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_14_OZ_415_ML;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_16_OZ_475_ML;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_20_OZ_590_ML;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_32_OZ;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_4_OZ_120_ML;

            break;
    }



}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_decision_low_water(void)
{
    if(u8WaterOutState == PURE_WATER_SELECT)
    {
        /*effluent_time_ambient_low_water();*/

        /*..hui [23-10-18오전 9:35:46] 정수는 냉수랑 동일..*/
        effluent_time_cold_low_water();

    }
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {

        effluent_time_cold_low_water();

    }
    /*..hui [23-10-18오전 9:37:27] 온수는 저수위에 추출안됨..*/
    /*else if(u8WaterOutState == HOT_WATER_SELECT)
    {
        effluent_time_hot_low_water();

    }*/
    else
    {
        /*u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ__LOW_WATER;*/
        u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML__LOW_WATER;
    }

    /*gu16_water_out_time = u16Efluent_Time;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_ambient_low_water(void)
{
    #if 0
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_6_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_8_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_10_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_12_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_14_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_16_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_20_OZ__LOW_WATER;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_32_OZ__LOW_WATER;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_AMBIENT_WATER_4_OZ__LOW_WATER;

            break;
    }
    #endif

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_cold_low_water(void)
{
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML__LOW_WATER;

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_6_OZ_175_ML__LOW_WATER;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_8_OZ_235_ML__LOW_WATER;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_10_OZ_295_ML__LOW_WATER;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_12_OZ_355_ML__LOW_WATER;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_14_OZ_415_ML__LOW_WATER;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_16_OZ_475_ML__LOW_WATER;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_20_OZ_590_ML__LOW_WATER;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_32_OZ__LOW_WATER;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML__LOW_WATER;

            break;
    }



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_hot_low_water(void)
{
    #if 0
    switch(gu8Cup_level)
    {
        case CUP_LEVEL__4_OZ__120_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_4_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__6_OZ__175_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_6_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__8_OZ__235_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_8_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__10_OZ__295_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_10_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__12_OZ__355_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_12_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__14_OZ__415_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_14_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__16_OZ__475_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_16_OZ__LOW_WATER;

            break;

        case CUP_LEVEL__20_OZ__590_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_20_OZ__LOW_WATER;

            break;

    #if 0
        case CUP_LEVEL__32_OZ__945_ML:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_32_OZ__LOW_WATER;

            break;
    #endif

        default:

            u16Efluent_Time = EXTRACT_TIME_HOT_WATER_4_OZ__LOW_WATER;

            break;
    }
    #endif


}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Long_Input(void)
{
    /*..hui [19-9-25오전 9:41:46] 연속 추출이 메뉴속으로..*/
    /*..hui [19-11-8오후 12:50:23] 다시 추가.. 없으니까 넘 불편..*/
    /*..hui [23-10-4오후 2:52:27] 상품기획, 미국 법인.. 추출 롱키 연속 추출 기능 삭제..*/
    /*..hui [23-10-4오후 2:52:40] 미국인들은 롱키에 익숙치 않아 오작동 우려 있다고 함..*/
    /*water_extract_long_key();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_long_key(void)
{
    #if 0
    gu16_water_select_return_time = 0;

    /*..hui [19-11-18오후 2:48:30] 연속 메뉴로 시작 시..*/
    if(u8Extract_Continue == SET)
    {
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        if(F_LineTest == SET)
        {
            /*..hui [18-1-9오후 10:24:39] 라인테스트모드에서는 10분으로 변경..*/
            u16Efluent_Time = EXTRACT_TIME_CONTINUE_LINE_TEST;
        }
        else
        {
            /* 냉수 강제 배수 */
            if( F_Tank_Cover_Input == CLEAR && u8WaterOutState == COLD_WATER_SELECT )
            {
                F_ColdConty = SET;
                u16Efluent_Time = EXTRACT_TIME_COLD_DRAIN;

                /*..hui [19-12-18오후 8:47:04] 제빙중이면 강제탈빙 진행..*/
                /*..hui [20-1-30오전 10:15:03] 코디닥터 점검기능에서 진행..*/
                /*force_take_off_ice();*/
            }
            else
            {
                u16Efluent_Time = EXTRACT_TIME_CONTINUE;
            }
        }

        BuzStep(BUZZER_EFFLUENT_CONTINUE);
        u8Extract_Continue = SET;

        /*..hui [19-12-5오후 4:48:26] 추출 버튼으로 인한 연속추출은 물량은 변경 안하는걸로..*/
        /*gu8Cup_level = CUP_LEVEL_CONTINUE;*/
    }
    else
    {
        u16Efluent_Time = 0;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Very_Long_Input(void)
{
    gu16_water_select_return_time = 0;

    if( F_WaterOut == SET )
    {
        /*..hui [19-11-18오후 1:36:04] 7초 이상 추출키 눌려있을경우 즉시 추출 종료..*/
        gu16Water_Extract_Timer = u16Efluent_Time;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_No_Key(void)
{
    F_Extract_Key_Short_Push_State = SET;
    F_Extract_Key_Long_Push_State = SET;
    F_Extract_Key_Very_Long_Push_State = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



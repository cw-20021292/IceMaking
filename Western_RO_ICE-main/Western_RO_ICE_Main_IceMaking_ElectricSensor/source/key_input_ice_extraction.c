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
#include    "key_input_ice_extraction.h"

void key_input_ice_extract(void);

void input_ice_extract_key(void);
void ice_ext_button_operation(void);
void ice_extraction_start(void);
void ice_extraction_finish(void);

U8 u8ice_ext_on_decision_cnt;
U8 u8ice_ext_off_decision_cnt;


U8 gu8_Key_Ice_Extract;
bit F_Key_IceExtraction;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_ice_extract(void)
{
    input_ice_extract_key();

    if(u8FactoryTestMode == NONE_TEST_MODE)
    {
        ice_ext_button_operation();
    }
    else
    {
        PCB_Test_Mode_Ice_Key_Short_Input();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_extract_key(void)
{
    if(gu8_Key_Ice_Extract != SET)
    {
        u8ice_ext_on_decision_cnt = 0;
        u8ice_ext_off_decision_cnt++;

        if( u8ice_ext_off_decision_cnt >= 100 )
        {
            u8ice_ext_off_decision_cnt = 100;
            F_Key_IceExtraction = CLEAR;
        }
        else{}
    }
    else
    {
        u8ice_ext_off_decision_cnt = 0;
        u8ice_ext_on_decision_cnt++;

        if ( u8ice_ext_on_decision_cnt >= 100 )
        {
            u8ice_ext_on_decision_cnt = 100;
            F_Key_IceExtraction = SET;
            auto_drain_key_off_check();
            power_saving_init();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_ext_button_operation(void)
{
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    /*..hui [23-2-9오후 2:03:49] 세팅모드에서는 부저음없이 추출안됨..*/
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    /*..hui [23-8-2오후 1:20:19] 얼음 추출중 필터 도어 열림시 얼음추출도 정지..*/
    /*..hui [23-8-2오후 1:20:39] 굳이 정지할 필요는 없지만.. 필터 열렸을때 얼음 추출 막았으므로 동일하게 하기 위해서....*/
    if( bit_filter_all == CLEAR )
    {
        if( F_Ice == SET )
        {
            F_Key_IceExtraction = CLEAR;
        }
        else{}
    }
    else{}

    if(F_Key_IceExtraction == SET)
    {
        if(F_ExtractKeySet == CLEAR)
        {
            /*if(F_All_Lock == SET)*/
            if( F_All_Lock == SET && F_Child_Lock == SET )
            {
                start_all_lock_flick();
                /*play_melody_warning_197();*/
                play_voice_all_lock_select_103();
            }
            else
            {
                ice_extraction_start();
            }

            F_ExtractKeySet = SET;
        }
        else{}
    }
    else
    {
        if( gu8_durable_test_start == CLEAR )
        {
            ice_extraction_finish();
            F_ExtractKeySet = CLEAR;
        }
        else
        {
            if( gu16_durable_test_step != 8 )
            {
                ice_extraction_finish();
                F_ExtractKeySet = CLEAR;
            }
            else{}
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_start(void)
{
    /*..hui [23-5-12오후 3:27:25] 버튼 설정 ON, OFF 표시중 버튼 누르면 표시 바로 종료..*/
    stop_button_set_display();
    /*..hui [24-4-25오후 7:12:26] LED 점멸중이던거 중지..*/
    off_all_flick();

    gu8_clear_block_error = SET;

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
        if( bit_acid_clean_start == SET )
        {
            play_melody_warning_197();
            return;
        }
        else{}
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        /*..hui [24-7-18오후 1:13:05] 그 외 불가음.. 이재섭님..*/
        play_melody_warning_197();
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        /*..hui [23-9-15오후 1:56:15] 커버 오픈시에 모든버튼 에러음 나도록 표준화..*/
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_filter_all == CLEAR )
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

    if(F_Ice_Lock == SET)
    {
        F_Ice = CLEAR;
        F_IceOutCCW = CLEAR;

        /*Bit0_Ice_Lock_Indicator = SET;*/
        start_ice_lock_flick();
        /*play_melody_warning_197();*/
        play_voice_ice_lock_ice_out_98();
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

    /*if( gu8_ice_setting == ICE_SETTING_OFF )*/
    if(F_IceOn == CLEAR)
    {
        /*..hui [19-12-10오전 9:41:41] 물 추출중이 아닐 경우에만 표시하도록 ..*/
        if(F_WaterOut == CLEAR)
        {

        }
        else{}
    }
    else{}

    if(F_Ice != SET)
    {
        F_Ice = SET;

        if(F_Ice == SET)
        {
            /*..hui [23-12-15오전 11:15:04] 우선순위.. 얼음OFF -> 에코모드 ..*/
            if( F_IceOn == CLEAR )
            {
                /*..hui [24-4-3오후 5:45:48] 얼음 OFF돼있으면 얼음 추출할때도 얼음버튼 점멸 추가..*/
                start_ice_off_flick();
                play_voice_ice_off_ice_out_99();
            }
            else if( Bit3_Leakage_Sensor_Error__E01 == SET )
            {
                play_voice_leakage_error_12();
            }
            /*else if( Bit2_Room_Temp_Open_Short_Error__E42 == SET
                     || Bit1_Room_OverHeat_Error__E49 == SET
                     || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
                     || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
                     || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
                     || Bit16_Drain_Pump_Error__E60 == SET
                     || Bit4_Room_Low_Water_Level_Error__E21 == SET
                     || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
                     || Bit7_BLDC_Communication_Error__E27 == SET
                     || bit_bldc_operation_error_total == SET )*/
            else if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
                     || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
                     || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
                     || Bit16_Drain_Pump_Error__E60 == SET
                     || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
                     || Bit7_BLDC_Communication_Error__E27 == SET
                     || bit_bldc_operation_error_total == SET
                     || Bit2_Room_Temp_Open_Short_Error__E42 == SET )
            {
                /*..hui [24-1-10오후 3:42:03] 얼음에러는.. 트레이에러, 드레인펌프에러, 외기센서에러, 컴프에러..*/
                /*..hui [24-2-1오후 4:30:53] 정수 온도센서 에러도 추가..*/
                play_voice_ice_error_10();
            }
            else if( bit_sleep_mode_start == SET )
            {
                play_voice_eco_mode_ice_out_101();
            }
            else
            {
                play_melody_setting_on_198();
            }
        }
        else
        {
            play_melody_setting_off_199();
        }

        if(F_Ice == SET)
        {
            F_IceOpen = SET;
            F_IceOutCCW = SET;
            gu8IceOutCCWInterval = 30;

            /*..hui [20-4-16오전 10:39:30] 역회전 동작중이었으면 취소..*/
            bit_ice_out_back_state = CLEAR;

            /* 아이스 도어 강제 닫힘 기능값 겹치는 경우 FULL OPEN */
            if( gu16IceDoorCloseResetTimer  != 0 )
            {
                gu16StepMotor2  = 0;
            }
            else{}
        }
        else{}

        finish_filter_alarm();
    }
    else{}

    /*finish_filter_alarm();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_finish(void)
{
    #if 0
    if(F_Ice_Lock == SET || F_All_Lock == SET)        // 얼음잠금 시 닫힘완료음 없음
    {
        F_ExtractKeySet = CLEAR;
    }
    #endif

    if( F_Ice_Lock == SET )        // 얼음잠금 시 닫힘완료음 없음
    {
        F_ExtractKeySet = CLEAR;
    }
    else if( F_All_Lock == SET && F_Child_Lock == SET )        // 얼음잠금 시 닫힘완료음 없음
    {
        F_ExtractKeySet = CLEAR;
    }
    else if(F_Ice == SET && F_LineTest != SET)
    {
        F_Ice = CLEAR;

        /*..hui [20-4-22오전 10:44:03] 역회전 조건 만족하지 않을경우 즉시 만빙 감지..*/
        /*..hui [20-4-22오전 10:44:15] 역회전 조건이면 역회전 완료하고 만빙 감지..*/
        if( bit_ice_out_back_state == CLEAR )
        {
            F_IR = SET;
        }
        else{}

        F_IceOutCCW = CLEAR;
        gu8IceClose = 30;         // 얼음도어 닫힘지연 3초
        F_ExtractKeySet = CLEAR;

        /*..hui [19-8-22오전 9:39:28] 얼음 추출 종료음은 안나도록.. 캐럿 기준..*/
        /*play_melody_setting_off_199();*/

        if( gu8IceOutCCWInterval > 0 )
        {
            play_voice_short_ice_out_97();
        }
        else
        {
            play_melody_setting_off_199();
        }
    }
    else if(F_ExtractKeySet == SET)
    {
        F_ExtractKeySet = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


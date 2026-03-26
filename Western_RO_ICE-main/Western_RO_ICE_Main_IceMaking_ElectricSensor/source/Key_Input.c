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
#include    "Key_Input.h"


void Scan_Port_Select( U8 Scan_value );
void Led_Port_Clear(void);
void Key_Input_Check(U8 u8key_state, U8 u8key_num);
void Key_Matrix_Input( U8 Scan_value );
void Key_Input_Sampling( U16 u16key_input_value);
void Key_Management( U16 u16key_input_value);
void Key_Short_Input( U16 u16key_input_value);
void Key_Long_Input( U16 u16key_input_value);
void Key_Very_Long_Input( U16 u16key_input_value);
U8 key_short_enable_check( U16 u16key_input_value );
void Key_Normal_Long_Input( U16 u16key_input_value);
void Key_Middle_Input( U16 u16key_input_value);


//void Extract_KeyInput(void);




U8  u8Scan_Value;


U32  u32Fix_Key_Input_Value;


U16  gu16_Key_Input;

//U16  u16Key_Input;
U16  u16Key_Buffer;

U16  u16Key_Sampling_Counter;
bit F_Key_Short_Push_State;
bit F_Key_Middle_Push_State;
bit F_Key_Long_Push_State;
bit F_Key_Very_Long_Push_State;
bit F_Key_Normal_Long_Push_State;

U8  u8Key_Input_Value;

U16  u16Key_Long_Counter;
U16  u16Key_Short_Counter;
U16 u16LedOutValue;






bit F_CoverOpenSet;


U16 gu16ExtrKeyDelay;




bit F_SterReady;
bit F_SterProhibit;
bit F_SterComplete;
bit F_SterWashCancel;



U16 gu16IceOutOff;
U8 gu8ICELockLEDFlick;


//U16 gu16KeyTime;


bit F_Cold_Water_VeryLongKey_Disable;
bit F_Hot_Water_VeryLongKey_Disable;

U8 gu8_debug_finish_count;
U16 gu16_develop_key_clear_time;

U8 gu8_debug_input_count;
U16 gu16_debugp_key_clear_time;


U8 gu8_flushing_finish_input_count;
U16 gu16_flushing_finish_key_clear_time;

TYPE_BYTE          U8LedFlickerStateB;
#define            u8LedFlickerState                           U8LedFlickerStateB.byte
#define            Bit0_Ice_Lock_LED_Flick                     U8LedFlickerStateB.Bit.b0
#define            Bit1_Ice_Lock_Extract_LED_Flick             U8LedFlickerStateB.Bit.b1
#define            Bit2_Hot_Water_Lock_LED_Flick               U8LedFlickerStateB.Bit.b2
#define            Bit3_All_Lock_Water_Extract_LED_Flick       U8LedFlickerStateB.Bit.b3




bit bit_setting_start;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input(void)
{
    /*..hui [19-11-7오전 9:55:18] 초기 키 막음..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        if(u8FactoryTestMode == NONE_TEST_MODE)
        {
            Extract_No_Key();
        }
        else{}

        return;
    }
    else{}

    Key_Input_Sampling(gu16_Key_Input);
    Key_Management(gu16_Key_Input);

    key_input_ice_extract();
    key_input_water_extract();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input_Sampling( U16 u16key_input_value)
{
    U8 mu8_filter = 0;

    mu8_filter = 1;

    if(u16key_input_value == u16Key_Buffer)
    {
        if(u16Key_Buffer == UControl_Key_Mask)
        {
            u16Key_Sampling_Counter = 0;
            F_Key_Short_Push_State = CLEAR;
            F_Key_Middle_Push_State = CLEAR;
            F_Key_Long_Push_State = CLEAR;
            F_Key_Very_Long_Push_State = CLEAR;
            F_Key_Normal_Long_Push_State = CLEAR;

            u8TimeSettingLongKey = 0;
        }
        else
        {
            u16Key_Sampling_Counter++;
        }

        if(u16Key_Sampling_Counter >= mu8_filter)
        {
            u16Key_Short_Counter = u16Key_Sampling_Counter;
            u16Key_Long_Counter++;
        }
        else{}
    }
    else
    {
        u16Key_Buffer = u16key_input_value;
        u16Key_Sampling_Counter = 0;
        u16Key_Long_Counter = 0;
        u16Key_Short_Counter = 0;

        //F_Key_Short_Push_State = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Management( U16 u16key_input_value)
{
    if(F_Key_Short_Push_State == CLEAR)
    {
        if( (u16Key_Short_Counter >= 1) && (u16Key_Short_Counter < 1000) )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                Key_Short_Input( u16key_input_value );
            }
            else
            {
                PCB_Test_Mode_Key_Short_Input( u16key_input_value );
            }

            F_Key_Short_Push_State = SET;
            u16Key_Short_Counter = 0;
        }
        else{}
    }
    else
    {
        if(F_Key_Middle_Push_State == CLEAR)
        {
            if( (u16Key_Long_Counter >= 1000 && u16Key_Long_Counter < 2000) )
            {
                F_Key_Middle_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    Key_Middle_Input( u16key_input_value );
                }
                else{}
            }
            else{}
        }
        else
        {
            if(F_Key_Long_Push_State == CLEAR)
            {
                if( (u16Key_Long_Counter >= 2000 && u16Key_Long_Counter < 3000) )
                {
                    F_Key_Long_Push_State = SET;

                    if(u8FactoryTestMode == NONE_TEST_MODE)
                    {
                        Key_Long_Input( u16key_input_value );
                    }
                    else{}
                }
                else{}
            }
            else
            {
                if(F_Key_Normal_Long_Push_State == CLEAR)
                {
                    if( (u16Key_Long_Counter >= 3000 && u16Key_Long_Counter < 5000) )
                    {
                        F_Key_Normal_Long_Push_State = SET;

                        if(u8FactoryTestMode == NONE_TEST_MODE)
                        {
                            Key_Normal_Long_Input( u16key_input_value );
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    if(F_Key_Very_Long_Push_State == CLEAR)
                    {
                        if( u16Key_Long_Counter >= 7000 )
                        {
                            F_Key_Very_Long_Push_State = SET;
                            u16Key_Long_Counter = 0;

                            if(u8FactoryTestMode == NONE_TEST_MODE)
                            {
                                Key_Very_Long_Input( u16key_input_value );
                            }
                            else{}
                        }
                        else{}
                    }
                    else{}
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Short_Input( U16 u16key_input_value )
{
    U8 mu8_return = 0;

    gu8_child_release_timer = 0;
    gu8_time_setting_return_time = 0;

    bit_setting_mode_time_init = SET;
    gu8_clear_block_error = SET;

    /*..hui [23-6-23오전 10:03:50] UV 진행률 표시(7초)중에 버튼 누르면 사라지도록..*/
    bit_uv_display_finish = SET;
    bit_error_display_finish = SET;
    bit_filter_alarm_display_finish = SET;

    auto_drain_key_off_check();
    power_saving_init();

    /*hot_prepare_return_timer_init();*/

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
        if( u16key_input_value != KEY_AMOUNT_SELECT )
        {
            if( u16key_input_value == KEY_AMBIENT_SELECT )
            {
                play_melody_select_196();
            }
            else
            {
                play_melody_warning_197();
            }

            return;
        }
        else{}
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        if( u16key_input_value != LONG_KEY_3S_SOUND_SETTING && u16key_input_value != LONG_KEY_3S_SOUND_SETTING_MISS_TOUCH_1 )
        {
            return;
        }
        else{}
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

    /*..hui [23-8-2오후 3:35:25] 얼음 추출 -> 버튼 누름 -> 일반화면 전환 -> 7초후 얼음추출화면 전환..*/
    /*ice_disp_key_check();*/
    if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        bit_ice_disp_pause = SET;
        gu8_ice_disp_pause_timer = 0;

        /*..hui [23-8-2오후 5:39:43] 용량버튼 누를때는 그냥 웨이크업만 하고 빠져나감..*/
        if( u16key_input_value == KEY_AMOUNT_SELECT )
        {
            play_melody_select_196();
            return;
        }
        else{}
    }
    else{}

    gu8_ice_disp_pause_timer = 0;

    #if 0
    /*..hui [23-5-12오후 3:27:25] 버튼 설정 ON, OFF 표시중 버튼 누르면 표시 바로 종료..*/
    /*..hui [23-7-26오후 7:21:09] 음소거 기능 표시중에도 바로 종료..*/
    if( u8ButtonSetDisplay == BUTTON_SET_HOT_DISPLAY
        || u8ButtonSetDisplay == BUTTON_SET_MUTE_DISPLAY
        || u8ButtonSetDisplay == BUTTON_SET_ICE_OFF_DISPLAY )
    {
        /*..hui [23-5-31오후 2:18:04] 온수버튼 눌려도 상태표시 중지. ..*/
        stop_button_set_display();
    }
    else{}
    #endif

    stop_button_set_display();
    /*..hui [24-4-25오후 7:12:26] LED 점멸중이던거 중지..*/
    off_all_flick();

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
        {
            if( ( u8FilterResetState == NEO_INO_FILTER_CHANGE || u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )
                && ( u16key_input_value == KEY_COLD_SELECT || u16key_input_value == LONG_KEY_3S_COLD_MISS_TOUCH )
                && bit_yes_no_popup == SET && bit_ct_flushing_standby_start == CLEAR )
            {
                /*..hui [24-2-21오후 3:01:35] CT모드 아닐떄..*/
                play_melody_select_196();
            }
            else if( ( u8FilterResetState != FILTER_NO_CHANGE )
                && ( u16key_input_value == KEY_COLD_SELECT || u16key_input_value == LONG_KEY_3S_COLD_MISS_TOUCH )
                && bit_yes_no_popup == SET && bit_ct_flushing_standby_start == SET )
            {
                /*..hui [24-2-21오후 3:01:42] CT모드일때..*/
                play_melody_select_196();
            }
            else
            {
                /*..hui [23-9-15오후 2:05:21] 플러싱 화면에서 페어링 버튼(정수) 숏키 누르면 띵소리~..*/
                if( u16key_input_value == LONG_KEY_3S_BLE_FAIRING )
                {
                    play_melody_select_196();
                    gu8_flushing_finish_input_count++;
                }
                else
                {
                    /*..hui [24-7-18오후 1:13:05] 그 외 불가음.. 이재섭님..*/
                    play_melody_warning_197();
                }
            }
        }
        else
        {
            /*..hui [23-9-15오후 2:05:21] 플러싱 화면에서 페어링 버튼(정수) 숏키 누르면 띵소리~..*/
            if( u16key_input_value == LONG_KEY_3S_BLE_FAIRING )
            {
                play_melody_select_196();
                gu8_flushing_finish_input_count++;
            }
            else
            {
                /*..hui [24-7-18오후 1:13:05] 그 외 불가음.. 이재섭님..*/
                play_melody_warning_197();
            }
        }

        /*..hui [24-12-6오전 9:20:23] 시간 설정할때 설정/온수/냉수 미스터치 적용..*/
        if( bit_time_setting_start == SET )
        {
            if( u16key_input_value == KEY_SETTING_SELECT
                || u16key_input_value == LONG_KEY_3S_SETTING_MISS_TOUCH
                || u16key_input_value == KEY_HOT_SELECT
                || u16key_input_value == LONG_KEY_3S_HOT_MISS_TOUCH
                || u16key_input_value == KEY_COLD_SELECT
                || u16key_input_value == LONG_KEY_3S_COLD_MISS_TOUCH )
            {

            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        /*..hui [23-9-15오후 1:56:15] 커버 오픈시에 모든버튼 에러음 나도록 표준화..*/
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        /*..hui [24-12-6오전 9:14:56] 고도설정시 온수버튼 미스터치 적용..*/
        if( u16key_input_value != KEY_HOT_SELECT && u16key_input_value != LONG_KEY_3S_HOT_MISS_TOUCH )
        {
            return;
        }
        else{}
    }
    else{}

    if( bit_ct_filter_type_start == SET )
    {
        if( u16key_input_value != KEY_COLD_SELECT && u16key_input_value != LONG_KEY_3S_COLD_MISS_TOUCH )
        {
            return;
        }
        else{}
    }
    else{}

    switch(u16key_input_value)
    {
        case KEY_SETTING_SELECT:
        case LONG_KEY_3S_SETTING_MISS_TOUCH:

            //
            key_setting_select_job();

        break;

        case KEY_ICE:
        case LONG_KEY_3S_ICE_MISS_TOUCH:

            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_ice_select_job();
            }
            else{}

        break;

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:

            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_hot_water_select_job();
            }
            else{}

        break;

        case KEY_AMBIENT_SELECT:
        case LONG_KEY_3S_AMBIENT_MISS_TOUCH:

            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_ambient_water_select_job();
            }
            else{}

        break;

        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:

            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_cold_water_select_job();
            }
            else{}

            gu8_debug_input_count++;

        break;

        case KEY_AMOUNT_SELECT:
        /*case LONG_KEY_3S_AMOUNT_MISS_TOUCH:*/

            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_amount_select_job();
            }
            else{}

            /*..hui [23-7-27오후 2:41:00] 용량버튼 7번 누르면 디버그모드 해제..*/
            gu8_debug_finish_count++;

            if( gu8_debug_finish_count == 7 )
            {
                bit_debug_mode_start = CLEAR;
                bit_ice_ster_test_debug_start = CLEAR;
            }
            else{}

        break;


        case KEY_SETTING_ICE_FIRST:
            //
            if( Bit0_Front_Led_Ice_First == SET )
            {
                key_setting_ice_first();
            }
            else{}

        break;


        case KEY_SETTING_ICE_LOCK:
            //
            if( Bit1_Front_Led_Ice_Lock == SET )
            {
                key_setting_ice_lock();
            }
            else{}

        break;

        case KEY_SETTING_HOT_LOCK:
            //
            if( Bit2_Front_Led_Hot_Lock == SET )
            {
                key_setting_hot_lock();
            }
            else{}

        break;

        case KEY_SETTING_TOUCH_LOCK:
            //
            if( Bit3_Front_Led_Touch_Lock == SET )
            {
                key_setting_touch_lock();
            }
            else{}

        break;

        #if 0
        case KEY_SETTING_STEAM_OFF:
            //
            if( Bit4_Front_Led_Steam_Off == SET )
            {
                ///key_setting_extra_cold();
                //key_manual_ice_tank_ster();
                key_setting_steam_off();
            }
            else{}

        break;
        #endif

        case KEY_SETTING_ECO_MODE:
            //
            if( Bit4_Front_Led_Eco_Mode  == SET )
            {
                key_setting_eco_mode();
            }
            else{}

        break;

        case LONG_KEY_3S_SOUND_SETTING:
        case LONG_KEY_3S_SOUND_SETTING_MISS_TOUCH_1:

            key_sound_change_job();

        break;

        default:
            NOP();
        break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Middle_Input( U16 u16key_input_value)
{
    if( gu8_fota_start == SET )
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

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        if( bit_time_setting_start == SET )
        {

        }
        else
        {
            return;
        }
    }
    else{}

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        return;
    }
    else{}

    switch(u16key_input_value)
    {
        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            //
            key_time_setting_hot_long_select_job();

        break;

        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            //
            key_time_setting_cold_long_select_job();

        break;


        default:

            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Long_Input( U16 u16key_input_value)
{
    //power_saving_init();
    /*..hui [23-6-27오후 4:48:44] 플러싱중에도 검사모드 진입은 가능해야..*/
    #if 0
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}
    #endif

    if( gu8_fota_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    switch(u16key_input_value)
    {
        case LONG_KEY_PCB_TEST_MODE:
            //
            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0 )
            {
                Main_PBA_Test_Mode_Start();
            }
            else{}

        break;

        case LONG_KEY_DISPLAY_TEST_MODE_CHPI:
            //
            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            /*..hui [19-11-4오후 8:08:43] 모델 선택 완료된 후부터..*/
            /*..hui [19-11-7오전 10:02:43] 누수센서 쇼트 상태면 디스플레이 테스트 못들어가게..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
                /*&& gu16ADLeakage <= 200*/
                /*&& pLEVEL_ICE_DRAIN_LOW == CLEAR && pLEVEL_ICE_DRAIN_HIGH == CLEAR*/
                /*&& gu8_room_level == ROOM_LEVEL_LOW )*/
            {
                diplay_test_start();
            }
            else{}

        break;

        case LONG_KEY_MANUAL_FACTORY_TEST:
            //
            manual_test_start();

        break;


        case LONG_KEY_3S_CHANGE_UNIT:
            //
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_change_unit();
            }
            else{}

        break;

        case LONG_KEY_3S_CHANGE_LANGUAGE:
            //
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_change_language();
            }
            else{}

        break;

        case LONG_KEY_3S_NO_USE_NO_OPERATION:
            //
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_no_use_no_operation_for_test();
            }
            else{}

        break;


        case LONG_KEY_3S_NO_COLD:
            //
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_temporary_cold_off_job();
            }
            else{}

        break;

        case LONG_KEY_2S_MOVE_NEXT_STER:
            //
            if( bit_ice_tank_ster_start == SET
                || bit_ice_ster_test_debug_start == SET
                || gu8_ice_ster_test_debug_step == 3 )
            {
                if( gu8_ice_ster_mode < STER_MODE_ICE_TRAY_CLEAN_PREPARE )
                {
                    gu8_ice_ster_mode = STER_MODE_ICE_TRAY_CLEAN_PREPARE;
                }
                else if( gu8_ice_ster_mode < STER_MODE_MELT_ICE_PREPARE )
                {
                    gu8_ice_ster_mode = STER_MODE_MELT_ICE_PREPARE;
                }
                else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE || gu8_ice_ster_mode == STER_MODE_MELT_ICE )
                {
                    gu8_melt_ice_count++;
                }
                else{}
            }
            else{}

        break;


        default:

            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Normal_Long_Input( U16 u16key_input_value)
{
    if( gu8_fota_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        if( u16key_input_value == LONG_KEY_3S_BLE_FAIRING
            || u16key_input_value == LONG_KEY_3S_AMBIENT_MISS_TOUCH )
        {
            //
        }
        else
        {
            play_melody_warning_197();
            return;
        }
    }
    else{}

    /*..hui [24-5-23오후 7:31:11] 구연산 세정할때..*/
    if( gu8_Led_Display_Step == LED_Display__ACID_CLEAN )
    {
        if( bit_acid_clean_start == SET )
        {
            return;
        }
        else{}
    }
    else{}

    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        /*..hui [23-6-29오후 5:09:41] 플러싱모드에서 페어링 버튼 눌려야..*/
        if( u16key_input_value == LONG_KEY_3S_BLE_FAIRING
            || u16key_input_value == LONG_KEY_3S_AMBIENT_MISS_TOUCH
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_1
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_2
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_3
            || u16key_input_value == LONG_KEY_3S_WIFI_ONOFF
            || u16key_input_value == LONG_KEY_3S_WIFI_ONOFF_MISS_TOUCH_1 )
        {

        }
        else if( u16key_input_value == LONG_KEY_3S_FORCED_FINISH_FLUSHING
               || u16key_input_value == KEY_SETTING_TOUCH_LOCK
               || u16key_input_value == LONG_KEY_DEBUG_MODE
               || u16key_input_value == LONG_KEY_3S_TAKEOFF_ICE
               || u16key_input_value == LONG_KEY_3S_ICE_TRAY_TEST
               || u16key_input_value == LONG_KEY_3S_CANCEL_COMP_DELAY
               || u16key_input_value == LONG_KEY_MANUAL_FACTORY_TEST
               || u16key_input_value == LONG_KEY_3S_TIME_SETTING
               || u16key_input_value == LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_1
               || u16key_input_value == LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_2
               || u16key_input_value == LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_3
               || u16key_input_value == LONG_KEY_3S_STER_RESERVE_TIME_SETTING
               || u16key_input_value == LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_1
               || u16key_input_value == LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_2
               || u16key_input_value == LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_3 )
        {

        }
        else if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
        {
            if( ( u8FilterResetState == NEO_INO_FILTER_CHANGE || u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )
                && ( u16key_input_value == KEY_COLD_SELECT || u16key_input_value == LONG_KEY_3S_COLD_MISS_TOUCH )
                && bit_yes_no_popup == SET && bit_ct_flushing_standby_start == CLEAR )
            {
                /*..hui [24-2-21오후 3:02:55] 일반 모드..*/
                cancel_filter_flushing();
            }
            else if( ( u8FilterResetState != FILTER_NO_CHANGE )
                && ( u16key_input_value == KEY_COLD_SELECT || u16key_input_value == LONG_KEY_3S_COLD_MISS_TOUCH )
                && bit_yes_no_popup == SET && bit_ct_flushing_standby_start == SET )
            {
                /*..hui [24-2-21오후 3:02:50] CT 모드..*/
                cancel_filter_flushing();
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN )
    {
        /*..hui [23-6-29오후 5:09:41] 플러싱모드에서 페어링 버튼 눌려야..*/
        if( u16key_input_value == LONG_KEY_3S_BLE_FAIRING
            || u16key_input_value == LONG_KEY_3S_AMBIENT_MISS_TOUCH
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_1
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_2
            || u16key_input_value == LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_3
            || u16key_input_value == LONG_KEY_3S_WIFI_ONOFF
            || u16key_input_value == LONG_KEY_3S_WIFI_ONOFF_MISS_TOUCH_1 )
        {

        }
        else if( u16key_input_value == LONG_KEY_3S_FORCED_FINISH_FLUSHING
               || u16key_input_value == KEY_SETTING_TOUCH_LOCK
               || u16key_input_value == LONG_KEY_DEBUG_MODE
               || u16key_input_value == LONG_KEY_3S_TAKEOFF_ICE
               || u16key_input_value == LONG_KEY_3S_ICE_TRAY_TEST
               || u16key_input_value == LONG_KEY_3S_CANCEL_COMP_DELAY
               || u16key_input_value == LONG_KEY_MANUAL_FACTORY_TEST )
        {

        }
        else
        {
            return;
        }
    }
    else{}

    if( bit_altitude_setting_start == SET )
    {
        if( u16key_input_value != LONG_KEY_HOT_TEMP_SETTING && u16key_input_value != LONG_KEY_HOT_TEMP_SETTING_MISS_TOUCH_1 )
        {
            return;
        }
        else{}
    }
    else{}

    if( bit_sound_setting_start == SET )
    {
        if( u16key_input_value != LONG_KEY_3S_SOUND_SETTING && u16key_input_value != LONG_KEY_3S_SOUND_SETTING_MISS_TOUCH_1 )
        {
            return;
        }
        else{}
    }
    else{}

    switch(u16key_input_value)
    {
        case LONG_KEY_3S_DURABLE_TEST:

            if( F_All_Lock == CLEAR
                && F_FW_Version_Display_Mode == SET
                && u8FactoryTestMode == NONE_TEST_MODE
                && gu8_test_mode_timeout > 0
                && gu8_Led_Display_Step == LED_Display__MAIN )
            {
                if( gu8_durable_test_start == CLEAR )
                {
                    gu8_durable_test_start = SET;
                    /*play_melody_setting_on_198();*/
                    play_voice_test_mode_151();
                }
                else{}
            }
            else{}

        break;

        case LONG_KEY_3S_BLE_FAIRING:
        case LONG_KEY_3S_AMBIENT_MISS_TOUCH:
            //
            /*..hui [21-7-15오후 12:47:23] BLE 페어링 - 정수 3초..*/
            /*if(F_All_Lock == CLEAR)*/
            if( F_All_Lock == SET && F_Child_Lock == SET )
            {
                /*..hui [24-7-18오후 2:57:17] 전체 잠금이어도 플러싱중에는 페어링 가능..*/
                if( gu8_flushing_mode > FLUSHING_NONE_STATE )
                {
                    WifiKey(WIFI_KEY_BLE);
                }
                else
                {
                    /*..hui [24-7-18오후 2:20:10] 전체잠금중 점유인증시 입력 가능하도록..*/
                    /*..hui [24-7-18오후 2:57:34] 전체잠금 - 플러싱 이외 조건일떄..*/
                    if( gu8_Wifi_Cert_State == WIFI_CERTIFICATE_ON )
                    {
                        WifiKey(WIFI_KEY_BLE);
                    }
                    else{}
                }
            }
            else if( gu8_Led_Display_Step == LED_Display__MEMENTO
                && bit_memento_start == SET )
            {
                /*..hui [23-9-26오후 6:25:52] 메멘토 모드에서는 메멘토 내역 삭제로..*/
                memento_delete_job();
            }
            else
            {
                WifiKey(WIFI_KEY_BLE);

                if( gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    if( gu8_wifi_ap_mode == CLEAR && gu8_ble_ap_mode == CLEAR )
                    {
                        if( GetWifiStatusValue( WIFI_STATUS_DISP ) == WIFI_DISP_OFF )
                        {
                            /*gu8_Lcd_Display_Step = LCD_Display__WIFI_PAIRING;*/
                        }
                        else
                        {
                            /*bit_wifi_pairing_start = SET;*/

                            if( gu8_Wifi_Last_Error != 0 )
                            {
                                bit_display_last_error = SET;
                                bit_wifi_pairing_start = SET;
                            }
                            else
                            {
                                bit_display_last_error = CLEAR;
                            }
                        }
                    }
                    else
                    {
                        bit_wifi_pairing_start = CLEAR;
                    }
                }
                else
                {
                    bit_wifi_pairing_start = CLEAR;
                }
            }

        break;

        /*..hui [24-12-3오후 2:19:00] 와이파이 페어링 미스터치 적용..*/
        case LONG_KEY_3S_WIFI_FAIRING:
        case LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_1:
        case LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_2:
        case LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_3:
            //
            /*..hui [21-7-15오후 12:51:01] WIFI 페어링 - 정수+냉수 3초..*/
            /*if(F_All_Lock == CLEAR)*/
            if( F_All_Lock == SET && F_Child_Lock == SET )
            {

            }
            else
            {
                WifiKey(WIFI_KEY_AP);

                if( gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    if( gu8_wifi_ap_mode == CLEAR && gu8_ble_ap_mode == CLEAR )
                    {
                        if( GetWifiStatusValue( WIFI_STATUS_DISP ) == WIFI_DISP_OFF )
                        {
                            /*gu8_Lcd_Display_Step = LCD_Display__WIFI_PAIRING;*/
                        }
                        else
                        {
                            /*bit_wifi_pairing_start = SET;*/

                            if( gu8_Wifi_Last_Error != 0 )
                            {
                                bit_display_last_error = SET;
                                bit_wifi_pairing_start = SET;
                            }
                            else
                            {
                                bit_display_last_error = CLEAR;
                            }
                        }
                    }
                    else
                    {
                        bit_wifi_pairing_start = CLEAR;
                    }
                }
                else
                {
                    bit_wifi_pairing_start = CLEAR;
                }
            }

        break;

        /*..hui [24-12-3오후 2:19:19] 와이파이 ON/OFF 미스터치 적용..*/
        case LONG_KEY_3S_WIFI_ONOFF:
        case LONG_KEY_3S_WIFI_ONOFF_MISS_TOUCH_1:
            //
            /*..hui [21-7-15오후 12:51:33] WIFI 전원 ON/OFF - 냉수+용량 3초..*/
            /*..hui [21-7-15오후 1:45:24] 설정 메뉴에 추가됐기 때문에 버튼 설정은 삭제..*/
            /*if(F_All_Lock == CLEAR)*/
            if( F_All_Lock == SET && F_Child_Lock == SET )
            {

            }
            else
            {
                WifiKey(WIFI_KEY_ONOFF);
            }

        break;

        case LONG_KEY_3S_FORCED_FINISH_FLUSHING:
            //
            if( gu8_test_mode_timeout > 0 )
            {
                forced_finish_flushing();
            }
            else{}

        break;

        case LONG_KEY_MANUAL_ICE_TANK_STER:
            //
            if(gu8_debug_input_count == 3)
            {
                key_manual_ice_tank_ster();
            }
            else{}

        break;

        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            //
            /*..hui [23-2-24오후 2:39:10] 위생때문에 냉수 OFF 기능은 없음..*/
            #if 0
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                cold_water_enable_setting_job(SETTING_ENABLE);
            }
            else{}
            #endif

        break;

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_ENABLE);
            }
            else{}

        break;

        case LONG_KEY_3S_HOT_OFF:
        case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_1:
        case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_2:
        case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_3:
            //
            /*..hui [24-4-2오후 5:42:03] 온수 OFF 어렵게.. 조합키로.. 온수+정수+물량 3초..*/
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}

        break;

        case KEY_ICE:
        case LONG_KEY_3S_ICE_MISS_TOUCH:
            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                /*ice_on_off_setting_job();*/
                /*..hui [24-4-3오후 4:06:45] OFF를 조합키로 변경..*/
                ice_on_setting_job();
            }
            else{}

        break;

        case LONG_KEY_3S_ICE_OFF:
        case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_1:
        case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_2:
        case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_3:
            //
            /*..hui [24-4-3오후 4:07:19] 얼음 OFF 어렵게.. 조합키로.. 얼음+정수+물량 3초..*/
            if( bit_setting_mode_start == CLEAR )
            {
                ice_off_setting_job();
            }
            else{}

        break;


        case KEY_AMOUNT_SELECT:
        /*case LONG_KEY_3S_AMOUNT_MISS_TOUCH:*/
            //
            /*..hui [23-2-22오후 4:15:04] 디폴트 물량 설정은 마이컵도 가능..*/
            if( bit_setting_mode_start == CLEAR )
            {
                default_cup_setting_job();
            }
            else{}

        break;

        case KEY_SETTING_SELECT:
        case LONG_KEY_3S_SETTING_MISS_TOUCH:

            //
            #if 0
            if( bit_time_setting_start == SET )
            {
                Bit3_Settings_3S_Finish_Indicator = SET;
            }
            else
            {
                setting_mode_start();
            }
            #endif

            setting_mode_start();

        break;

        case KEY_SETTING_TOUCH_LOCK:
            //
            key_disable_touch_lock();

        break;

        /*..hui [24-12-3오후 1:30:13] 고도설정 미스터치 적용..*/
        case LONG_KEY_HOT_TEMP_SETTING:
        case LONG_KEY_HOT_TEMP_SETTING_MISS_TOUCH_1:

            key_altitude_setting_job();

        break;

        /*..hui [24-12-3오후 1:34:35] 음성 설정 미스터치 적용..*/
        case LONG_KEY_3S_SOUND_SETTING:
        case LONG_KEY_3S_SOUND_SETTING_MISS_TOUCH_1:

            /*mute_setting_job();*/
            key_sound_setting_job();

        break;

        /*..hui [24-12-3오후 1:51:11] 시간 설정 미스터치 적용..*/
        case LONG_KEY_3S_TIME_SETTING:
        case LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_1:
        case LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_2:
        case LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_3:

            key_time_setting_job();

        break;

        /*..hui [24-12-3오후 1:51:18] 세척시간 설정 미스터치 적용..*/
        case LONG_KEY_3S_STER_RESERVE_TIME_SETTING:
        case LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_1:
        case LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_2:
        case LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_3:

            #if 0
            /*if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )*/
            if( u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_reserve_time_setting_job();
            }
            else{}
            #endif

            key_reserve_time_setting_job();

        break;

        case LONG_KEY_DEBUG_MODE:
            //
            if(gu8_debug_input_count == 3)
            {
                debug_mode_select_job();
            }
            else{}

        break;

        case LONG_KEY_3S_MEMENTO:
            //
            if( F_All_Lock == CLEAR
                && F_FW_Version_Display_Mode == SET
                && u8FactoryTestMode == NONE_TEST_MODE
                && gu8_test_mode_timeout > 0
                && gu8_Led_Display_Step == LED_Display__MAIN )
            {
                gu8_test_mode_timeout = 0;
                memento_select_job();
            }
            else if( gu8_Led_Display_Step == LED_Display__MEMENTO
                     && bit_memento_start == SET )
            {
                /*memento_finish_job();*/
            }
            else{}

        break;


        //////////case KEY_AMBIENT_SELECT:
            //
            #if 0
            if( gu8_Led_Display_Step == LED_Display__MEMENTO
                && bit_memento_start == SET )
            {
                memento_delete_job();
            }
            else{}
            #endif

        //////////break;

        case LONG_KEY_3S_TAKEOFF_ICE:
            //
            start_cody_takeoff_ice();

        break;

        case LONG_KEY_3S_ICE_TRAY_TEST:
            //
            start_ice_tray_test();

        break;

        case LONG_KEY_3S_CANCEL_COMP_DELAY:
            //
            calcel_comp_delay();

        break;

        /*..hui [24-12-3오후 1:55:21] 수동배수 미스터치 적용..*/
        case LONG_KEY_3S_MANUAL_DRAIN:
        case LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_1:
        case LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_2:
        case LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_3:

            //
            key_manual_drain();

        break;

        /*..hui [24-12-3오후 2:02:20] CT 강제 플러싱 미스터치 적용..*/
        case LONG_KEY_3S_CT_FORCED_FLUSHING:
        case LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_1:
        case LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_2:
        case LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_3:

            //
            key_ct_forced_flushing();

        break;

        /*..hui [24-12-3오후 2:10:38] CT 필터 교체 주기 변경 모드 미스터치 적용..*/
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_1:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_2:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_3:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_4:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_5:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_6:
        case LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_7:

            //
            key_ct_change_filter_order_job();

        break;

        case LONG_KEY_3S_RECOVER_FAST_ICE:
            //
            if( bit_setting_mode_start == CLEAR )
            {
                key_recover_fast_ice_job();
            }
            else{}

        break;

        #if 0
        case LONG_KEY_3S_ACID_CLEAN:
            //
            if( bit_setting_mode_start == CLEAR )
            {
                //
                key_acid_clean_job();
            }
            else{}

        break;
        #endif


        default:

            NOP();

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Very_Long_Input( U16 u16key_input_value)
{
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

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( gu8_fota_start == SET )
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

    switch(u16key_input_value)
    {
        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            //
            /*..hui [23-2-24오후 2:39:10] 위생때문에 냉수 OFF 기능은 없음..*/
            #if  0
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            if( bit_setting_mode_start == CLEAR )
            {
                cold_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}
            #endif

        break;

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            //
            /*..hui [23-2-9오후 6:28:05] 세팅모드에서는 안눌림..*/
            /*..hui [24-4-2오후 5:40:53] 온수 OFF는 온수+정수+물량 조합키로 변경..*/
            #if 0
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}
            #endif

        break;


        default:
            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



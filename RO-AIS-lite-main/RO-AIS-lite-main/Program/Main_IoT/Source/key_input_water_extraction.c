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
void mmy_cup_time_decision(void);
void Extract_Key_Long_Input(void);

void water_extract_long_key(void);

void key_input_water_extract(void);
void Extract_Key_Very_Long_Input(void);

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
                //u16Extract_Key_Long_Counter = 0;

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
    bit_standby_input = SET;
    gu16_water_select_return_time = 0;

    auto_drain_key_off_check();
    power_saving_init();

    /*..hui [24-4-24오후 5:43:33] 표시중 버튼눌리면 바로 종료..*/
    /*..hui [23-5-31오후 2:18:04] 온수버튼 눌려도 상태표시 중지. ..*/
    stop_button_set_display();


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

    /*..hui [23-2-9오후 2:03:49] 세팅모드에서는 부저음없이 추출안됨..*/
    if( bit_setting_mode_start == SET )
    {
        if( bit_my_cup_setting_start == CLEAR && Bit3_My_Cup_Set_Display == CLEAR )
        {
            return;
        }
        else
        {
            /*..hui [23-4-3오후 1:05:13] 마이컵 버튼 눌러서 Set 표시 상태 -> 물 추출 눌렀는데 저수위인경우.. 마이컵 설정안됨..*/
            if( Bit3_My_Cup_Set_Display == SET )
            {
                if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
                {
                    BuzStep(BUZZER_ERROR);
                    start_low_water_flick();
                    return;
                }
                else{}
            }
            else{}
        }
    }
    else{}

    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}
	
    if( gu8_fota_start == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    /*..hui [19-8-22오후 1:44:22] 중수위 또는 만수위에서만 온수 추출 시작..*/
    if(u8WaterOutState == HOT_WATER_SELECT)
    {
        if( F_WaterOut == CLEAR )
        {
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                BuzStep(BUZZER_ERROR);
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
    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        if( F_WaterOut == CLEAR )
        {
            if( Bit1_Room_OverHeat_Error == SET )
            {
                BuzStep(BUZZER_ERROR);
                gu8_error_popup_enable = SET;
                return;
            }
            else{}
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

    if( F_WaterOut == CLEAR )
    {
        F_WaterOut = SET;
        F_Effluent_OK = CLEAR;
        BuzStep(BUZZER_EFFLUENT);

        /*..hui [23-3-23오후 1:49:27] 세팅모드 -> 마이컵 Set 표시된 상태에서.. 물 추출하면 그때부터 설정 시작..*/
        if( Bit3_My_Cup_Set_Display == SET )
        {
            start_my_cup_setting();
        }
        else{}
    }
    else
    {
        F_WaterOut = CLEAR;
        u8Extract_Continue = CLEAR;
        /*BuzStep(BUZZER_EFFLUENT_END);*/

        if( bit_my_cup_setting_start == SET )
        {
            if( gu16_my_cup_setting_time >= MY_CUP_SETTING_120mL_PURE_MIN )
            {
                BuzStep(BUZZER_SETUP);
            }
            else
            {
                BuzStep(BUZZER_ERROR);
                /*..hui [23-3-23오후 1:51:31] 마이컵 설정 종료. 다시 Set 표시 화면으로..*/
                halt_my_cup_setting();
            }
        }
        else
        {
            BuzStep(BUZZER_EFFLUENT_END);
        }
    }

    if(F_WaterOut == SET)
    {
        if(u8Extract_Continue != SET)
        {
            if( bit_my_cup_setting_start == SET )
            {
                mmy_cup_time_decision();
            }
            else
            {
                /*..hui [23-5-9오후 4:32:05] 추출시간 보상을 이쪽으로..*/
                /*final_compensation_time();*/
                effluent_time_decision();
                gu16_water_out_time = u16Efluent_Time;				
                /*..sean [25-02-10] 정수 차가움 이슈 개선 기능 제거..*/
                //calc_mix_water();
                //Pure_Temp_Compensation_time();
            }
        }
        else
        {
            u16Efluent_Time = EXTRACT_TIME_CONTINUE;
        	//calc_mix_water();
        }
    }
    else
    {
        u16Efluent_Time = 0;
    }

	//wifi 처리 
	// if(F_WaterOut == SET)
	// {
	// 	SetWifiSystemStatus(WIFI_RX_STATUS, SET);
	// 	SetWifiSystemStatus(WIFI_SMART_POSSIBLE_STATUS, SET);	
	// 	SetWifiSystemStatus(WIFI_FOTA_POSSIBLE_STATUS, SET);	
	// }
	// else
	// {
	// 	SetWifiSystemStatus(WIFI_RX_STATUS, CLEAR);
	// 	SetWifiSystemStatus(WIFI_SMART_POSSIBLE_STATUS, CLEAR);	
	// 	SetWifiSystemStatus(WIFI_FOTA_POSSIBLE_STATUS, CLEAR);	
	// }
    /*gu16_water_out_time = u16Efluent_Time;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_decision(void)
{
    if(u8WaterOutState == PURE_WATER_SELECT)
    {
        switch(gu8Cup_level)
        {
            case CUP_LEVEL_HALF:

                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_HALF;

                break;
			
            case CUP_LEVEL_ONE:

                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_ONE;

                break;

            case CUP_LEVEL_TWO:

                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_TWO;

                break;

            case CUP_LEVEL_FOUR:

                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_FOUR;

                break;

            case CUP_LEVEL_CONTINUE:

                u16Efluent_Time = EXTRACT_TIME_CONTINUE;;

                break;

            case CUP_LEVEL_MY_CUP:

                u16Efluent_Time = gu16_my_cup_level_pure;

                break;

            default:

                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_HALF;

                break;
        }

    }
    //else if(F_ColdOut == SET)
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        switch(gu8Cup_level)
        {
            case CUP_LEVEL_HALF:

                u16Efluent_Time = EXTRACT_TIME_COLD_WATER_HALF;

                break;

            case CUP_LEVEL_ONE:

                u16Efluent_Time = EXTRACT_TIME_COLD_WATER_ONE;

                break;

            case CUP_LEVEL_TWO:

                u16Efluent_Time = EXTRACT_TIME_COLD_WATER_TWO;

                break;

            case CUP_LEVEL_FOUR:

                u16Efluent_Time = EXTRACT_TIME_COLD_WATER_FOUR;

                break;

            case CUP_LEVEL_CONTINUE:

                u16Efluent_Time = EXTRACT_TIME_CONTINUE;;

                break;

            case CUP_LEVEL_MY_CUP:

                u16Efluent_Time = gu16_my_cup_level_cold;

                break;

            default:

                u16Efluent_Time = EXTRACT_TIME_COLD_WATER_HALF;

                break;
        }

    }
    else if(u8WaterOutState == HOT_WATER_SELECT)
    {
        switch(gu8Cup_level)
        {
            case CUP_LEVEL_HALF:

                u16Efluent_Time = EXTRACT_TIME_HOT_WATER_HALF;

                break;
			
            case CUP_LEVEL_ONE:

                u16Efluent_Time = EXTRACT_TIME_HOT_WATER_ONE;

                break;

            case CUP_LEVEL_TWO:

                u16Efluent_Time = EXTRACT_TIME_HOT_WATER_TWO;

                break;

            case CUP_LEVEL_FOUR:

                u16Efluent_Time = EXTRACT_TIME_HOT_WATER_FOUR;

                break;

            case CUP_LEVEL_CONTINUE:

                u16Efluent_Time = EXTRACT_TIME_CONTINUE;;

                break;

            case CUP_LEVEL_MY_CUP:

                u16Efluent_Time = gu16_my_cup_level_hot;

                break;

            default:

                u16Efluent_Time = EXTRACT_TIME_HOT_WATER_HALF;

                break;
        }
    }
    else
    {
        u16Efluent_Time = 0;
    }

    /*..hui [23-6-7오전 11:53:11] 에이징 테스트할때는 120ml..*/
    if( gu8_durable_test_start == SET )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            u16Efluent_Time = u16Efluent_Time / 2;
        }
        else{}
    }
    else{}

    /*gu16_water_out_time = u16Efluent_Time;*/

    /*..hui [23-5-9오후 4:34:11] 탱크 수위에 따른 추출 시간 보상..*/
    /*u16Efluent_Time  = u16Efluent_Time + gu8_compensation_time;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void mmy_cup_time_decision(void)
{
    u16Efluent_Time = MY_CUP_SETTING_800mL_PURE;


    #if 0
    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        u16Efluent_Time = MY_CUP_SETTING_800mL_PURE;
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        u16Efluent_Time = MY_CUP_SETTING_800mL_COLD;
    }
    else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
    {
        u16Efluent_Time = MY_CUP_SETTING_800mL_HOT;
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
    water_extract_long_key();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_long_key(void)
{
    gu16_water_select_return_time = 0;

    if( bit_my_cup_setting_start == SET )
    {
        return;
    }
    else{}

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
		gu8Cup_level = CUP_LEVEL_CONTINUE;
        calc_mix_water();
        //Pure_Temp_Compensation_time();

        /*..hui [19-12-5오후 4:48:26] 추출 버튼으로 인한 연속추출은 물량은 변경 안하는걸로..*/
        /*gu8Cup_level = CUP_LEVEL_CONTINUE;*/
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



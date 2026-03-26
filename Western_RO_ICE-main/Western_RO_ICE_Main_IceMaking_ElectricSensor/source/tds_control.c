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
#include    "tds_control.h"


#if 0
void tds_control(void);
void check_tds_status(void);
void turn_on_tds(void);
void turn_off_tds(void);
void check_tds_12_hour(void);
U8 tds_in_data_error_check(void);
U8 tds_out_data_error_check(void);
void tds_remove_ratio_error_check(void);


bit bit_recycling_success;


bit bit_reach_2liter;
bit bit_tds_check;



U8 gu8_tds_check_timer;

U16 gu16_recent_tds_in_data;
U16 gu16_recent_tds_out_data;



U16 gu16_tds_limit_timer_sec;
U16 gu16_tds_limit_timer_min;
U16 gu16_tds_limit_timer_hour;

U8 gu8_tds_in_error_count;
U8 gu8_tds_out_error_count;

U8 gu8_tds_pollution_error_count;

U8 gu8TDSCheckCount;
F32 f32_tds_remove_ratio;

U8 u8_tds_remove_ratio;
U8 u8_tds_remove_error_count;

U8 aaaaaaaaaaa;


U16 gu16_tds_water_in_timer;
U16 gu16_tds_water_acc;

bit bit_tds_flushing_check;

bit bit_tds_feed_check;
#endif



#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_control(void)
{
    //for test용으로 주석
    check_tds_status();
    check_tds_12_hour();
    tds_out_control();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_tds_status(void)
{
    U8 mu8_return_data1 = CLEAR;
    U8 mu8_return_data2 = CLEAR;

    #if 0
    /*if( gu8_water_input_step == 4 )*/
    if( Bit0_Low_Water_Filling_State == SET )
    {
        gu16_tds_water_in_timer++;

        /*..hui [21-7-8오후 8:16:57] 재정수 시간 연속 7분 이상 확인..*/
        if( gu16_tds_water_in_timer >= TDS_CHECK_WATER_IN_TIME )
        {
            gu16_tds_water_in_timer = TDS_CHECK_WATER_IN_TIME;
        }
        else{}
    }
    else
    {
        if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
        {
            /*..hui [21-7-8오후 8:17:25] 재 정수해서 만수위이고 재 정수가 연속 7분이상 했었다면 TDS 체크 시작..*/
            if( gu16_tds_water_in_timer >= TDS_CHECK_WATER_IN_TIME )
            {
                bit_recycling_success = SET;
            }
            else{}
        }
        else{}

        gu16_tds_water_in_timer = 0;
    }
    #endif

    if( gu8_flushing_mode > FLUSHING_NONE_STATE
        || bit_acid_clean_start == SET
        || bit_ice_tank_ster_start == SET )
    {
        /*..hui [24-8-16오후 3:14:09] 플러싱중,구연산중, 얼음탱크 세척중 추출물량 초기화..*/
        gu16_tds_water_acc = 0;
    }
    else{}

    /*..hui [24-8-7오전 11:18:36] 재정수할때..*/
    if( Bit0_Low_Water_Filling_State == SET )
    {
        /*..hui [24-8-7오전 11:18:48] 워터 플러싱 진행 조건에서만 확인..*/
        /*..hui [24-8-7오후 4:56:21] 제빙 완료후에는 그냥 체크..*/
        if( bit_flushing_water_start == SET || gu8IceStep == STATE_21_ICE_SWITCH_MOVE )
        {
            bit_tds_flushing_check = SET;
        }
        else
        {
            /*..hui [24-8-7오전 11:19:05] 120미리 이상 추출했을때만..*/
            if( bit_tds_flushing_check == SET && gu16_tds_water_acc >= 120 )
            {
                gu16_tds_water_in_timer++;

                /*..hui [21-7-8오후 8:16:57] 재정수 시간 연속 4분 이상 확인..*/
                /*..hui [24-8-7오전 11:19:12] 안전사양..*/
                /*..hui [24-8-16오후 5:25:31] 3분으로 변경..*/
                if( gu16_tds_water_in_timer >= TDS_CHECK_WATER_IN_TIME )
                {
                    gu16_tds_water_in_timer = TDS_CHECK_WATER_IN_TIME;
                }
                else{}
            }
            else
            {
                gu16_tds_water_in_timer = 0;
            }
        }

        bit_tds_feed_check = SET;
    }
    else
    {
        /*..hui [24-8-12오후 2:44:22] 얼음탱크 세척중.. TDS 온도센서 에러일경우 측정안함..*/
        if( gu8_Room_Water_Level == ROOM_LEVEL_FULL
            && bit_ice_tank_ster_start == CLEAR
            && Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 == CLEAR
            && Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 == CLEAR )
        {
            /*..hui [21-7-8오후 8:17:25] 재 정수해서 만수위이고 재 정수가 연속 7분이상 했었다면 TDS 체크 시작..*/
            if( gu16_tds_water_in_timer >= TDS_CHECK_WATER_IN_TIME )
            {
                bit_recycling_success = SET;
            }
            else{}
        }
        else{}

        bit_tds_flushing_check = CLEAR;
        /*gu16_tds_water_acc = 0;*/
        gu16_tds_water_in_timer = 0;

        /*..hui [24-8-16오후 2:31:12] 만수위일때만 추출 물량 초기화..*/
        /*..hui [24-8-16오후 2:52:51] 재정수하고나서 만수위됐을때만..*/
        /*..hui [24-8-16오후 2:53:14] 추출끝나고 재정수되는 사이에 여기서 초기화되버림..*/
        if( bit_tds_feed_check == SET )
        {
            bit_tds_feed_check = CLEAR;

            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_tds_water_acc = 0;
            }
            else{}
        }
        else{}
    }


    if(bit_recycling_success == SET)
    {
        /*..hui [19-1-25오후 2:16:47] 24시간당 3번까지만 체크..*/
        /*..hui [19-1-25오후 2:53:18] 유량 흐르는지 확인도 추가..*/
        /*if(F_WaterOut == CLEAR && gu8_Flow_1sec < 5 && gu8TDSCheckCount <= TDS_CHECK_LIMIT_ONE_DAY)*/
        if( F_WaterOut == CLEAR && bit_feed_output == CLEAR && gu8TDSCheckCount < TDS_CHECK_LIMIT_ONE_DAY )
        {
            gu8_tds_check_timer++;

            if(gu8_tds_check_timer < TDS_STABLE_TIME )
            {
                /*..hui [19-1-25오후 4:13:38] 3초간 안정화 대기한다..*/

            }
            else if(gu8_tds_check_timer >= TDS_STABLE_TIME && gu8_tds_check_timer < TDS_CHEAK_TIME)
            {
                /*..hui [19-1-25오후 4:12:56] TDS 켜고 3초 동안 대기한다..*/
                if(F_TDS_ON == CLEAR)
                {
                    turn_on_tds();
                }
                else{}
            }
            else
            {
                gu8_tds_check_timer = 0;
                mu8_return_data1 = tds_in_data_error_check();
                mu8_return_data2 = tds_out_data_error_check();

                /*..hui [24-8-7오전 9:18:27] 개별 업데이트하도록..*/
                if( mu8_return_data1 == CLEAR )
                {
                    gu16_recent_tds_in_data = gu16TDS_IN_Final;
                    /*..hui [21-8-3오후 4:33:11] TDS 값 업데이트 됐으니 서버 전송..*/
                    gu8_wifi_tds_update  = SET;
                }
                else{}

                if( mu8_return_data2 == CLEAR )
                {
                    gu16_recent_tds_out_data = gu16TDS_OUT_Final;
                    /*..hui [21-8-3오후 4:33:11] TDS 값 업데이트 됐으니 서버 전송..*/
                    gu8_wifi_tds_update  = SET;
                }
                else{}

                if(mu8_return_data1 == CLEAR && mu8_return_data2 == CLEAR)
                {
                    /*gu16_recent_tds_in_data = gu16TDS_IN_Final;*/
                    /*gu16_recent_tds_out_data = gu16TDS_OUT_Final;*/

                    tds_remove_ratio_error_check();

                    #if 0
                    if(gu8TDSCheckCount <= 200)
                    {
                        gu8TDSCheckCount++;
                    }
                    else{}
                    #endif

                    /*..hui [21-8-3오후 4:33:11] TDS 값 업데이트 됐으니 서버 전송..*/
                    gu8_wifi_tds_update  = SET;
                }
                else{}

                if(gu8TDSCheckCount <= 200)
                {
                    gu8TDSCheckCount++;
                }
                else{}

                /*.. 상태 체크 완료했으니 TDS 끄고, 측정값 초기화..*/
                turn_off_tds();
                /*bit_tds_check = CLEAR;*/
                bit_recycling_success = CLEAR;
            }
        }
        else
        {
            gu8_tds_check_timer = 0;
            turn_off_tds();

            /*..hui [19-1-25오후 2:46:55] 하루 횟수 초과로 이짝으로 온거면..*/
            if(gu8TDSCheckCount >= TDS_CHECK_LIMIT_ONE_DAY)
            {
                /*bit_tds_check = CLEAR;*/
                bit_recycling_success = CLEAR;
            }
            else{}
        }
    }
    else
    {
        gu8_tds_check_timer = 0;
        turn_off_tds();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void turn_on_tds(void)
{
    F_TDS_ON = SET;
    gu16TDS_OUT_Pulse_Time = 50;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void turn_off_tds(void)
{
    if(F_TDS_ON == SET)
    {
        F_TDS_ON = CLEAR;
        gu16TDS_OUT_Pulse_Time = 50;
        gu16TDS_IN_Final = 0;
        gu16TDS_OUT_Final = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_tds_12_hour(void)
{
    gu16_tds_limit_timer_sec++;

    if(gu16_tds_limit_timer_sec >= 600)
    {
        gu16_tds_limit_timer_sec = 0;
        gu16_tds_limit_timer_min++;

    }
    else{}

    if(gu16_tds_limit_timer_min >= 60)
    {
        gu16_tds_limit_timer_min = 0;
        gu16_tds_limit_timer_hour++;

    }
    else{}

    /*..hui [19-1-25오후 2:15:56] 최종 전원 ON 후 24시간 후에 TDS 체크 누적 카운트 초기화..*/
    /*if(gu16_tds_limit_timer_hour >= 24)*/
    /*..hui [24-8-6오후 2:06:03] 12시간에 한번 측ㅈ어..*/
    if(gu16_tds_limit_timer_hour >= 12)
    {
        gu8TDSCheckCount = 0;
        gu16_tds_limit_timer_hour = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 tds_in_data_error_check(void)
{
    U8 mu8_return = CLEAR;

    if( gu16TDS_IN_Final == 0 )
    {
        gu8_tds_pollution_error_count = 0;

        gu8_tds_in_error_count++;

        /*..hui [24-8-16오전 10:26:02] 5회로 변경.. 함재진님..*/
        if(gu8_tds_in_error_count >= TDS_DATA_ERROR_COUNT)
        {
            gu8_tds_in_error_count = TDS_DATA_ERROR_COUNT;
            Bit2_No_Display_Tds_In_Data_Error__E92 = SET;
        }
        else{}

        mu8_return = SET;
    }
    else if( gu16TDS_IN_Final >= 500 )
    {
        gu8_tds_in_error_count = 0;

        /*..hui [24-8-6오후 2:05:34] 입수가 500ppm 이상일 경우에 2회 더 추가 측정 후 에러..*/
        gu8_tds_pollution_error_count++;

        if( gu8_tds_pollution_error_count >= TDS_POLLUTION_ERROR_COUNT )
        {
            gu8_tds_pollution_error_count = TDS_POLLUTION_ERROR_COUNT;
            Bit4_No_Display_Tds_In_Pollution_Error__E98 = SET;
        }
        else{}

        /*..hui [24-8-16오후 5:22:37] 500ppm 이상 나왔을때도 값은 찍혔으므로 값 업데이트..*/
        mu8_return = CLEAR;
    }
    else
    {
        gu8_tds_in_error_count = 0;
        gu8_tds_pollution_error_count = 0;
        /*..hui [24-8-13오전 10:48:23] 정상 측정시 에러 해제..*/
        Bit2_No_Display_Tds_In_Data_Error__E92 = CLEAR;
        Bit4_No_Display_Tds_In_Pollution_Error__E98 = CLEAR;
        mu8_return = CLEAR;
    }

    return mu8_return;
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 tds_out_data_error_check(void)
{
    U8 mu8_return = CLEAR;

    if( gu16TDS_OUT_Final == 0 )
    {
        gu8_tds_out_error_count++;

        if(gu8_tds_out_error_count >= TDS_DATA_ERROR_COUNT)
        {
            gu8_tds_out_error_count = TDS_DATA_ERROR_COUNT;
            Bit3_No_Display_Tds_Out_Data_Error__E93 = SET;
        }
        else{}

        mu8_return = SET;
    }
    else
    {
        gu8_tds_out_error_count = 0;
        Bit3_No_Display_Tds_Out_Data_Error__E93 = CLEAR;
        mu8_return = CLEAR;
    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_remove_ratio_error_check(void)
{
    if( Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 == SET
        || Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 == SET
        || Bit2_No_Display_Tds_In_Data_Error__E92 == SET
        || Bit3_No_Display_Tds_Out_Data_Error__E93 == SET )
    {
        return;
    }
    else{}

    /*..hui [21-11-12오후 4:04:49] 입수 TDS 값은 60 이상일 경우에만 제거율 계산..*/
    /*..hui [21-11-12오후 4:05:41] 출수 TDS 값은 100 미만일 경우에만 제거율 계산..*/
    /*..hui [21-11-12오후 4:06:30] 영재 차장님이랑 협의완료~..*/
    /*..hui [21-11-12오후 4:14:43] 입수=출수 이거나, 입수가 출수보다 작게 계산됐을때도 그냥 pass~~~..*/
    #if 0
    if( gu16TDS_IN_Final < 60 || gu16TDS_OUT_Final > 100 )
    {
        return;
    }
    #endif

    /*..hui [24-8-6오후 2:03:15] 출수 15ppm 이하이면 측정 안함..*/
    if( gu16TDS_OUT_Final <= 15 )
    {
        return;
    }
    else if( gu16TDS_IN_Final <= gu16TDS_OUT_Final )
    {
        return;
    }
    else{}

    if( gu16TDS_IN_Final > gu16TDS_OUT_Final )
    {
        f32_tds_remove_ratio
            = (F32)((F32)((F32)((F32)gu16TDS_IN_Final - (F32)gu16TDS_OUT_Final) / (F32)gu16TDS_IN_Final) * (F32)100);
    }
    else
    {
        f32_tds_remove_ratio = 0;
    }

    u8_tds_remove_ratio = (U8)f32_tds_remove_ratio;

    if(f32_tds_remove_ratio < TDS_REMOVE_ERROR_RATIO)
    {
        u8_tds_remove_error_count++;

        if(u8_tds_remove_error_count >= TDS_REMOVE_ERROR_COUNT)
        {
            u8_tds_remove_error_count = TDS_REMOVE_ERROR_COUNT;
            Bit5_No_Display_Tds_Remove_Error__E99 = SET;
        }
        else{}
    }
    else
    {
        u8_tds_remove_error_count = 0;
        Bit5_No_Display_Tds_Remove_Error__E99 = CLEAR;
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



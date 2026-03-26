/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright  d x  : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "auto_drain.h"

void auto_drain_control(void);
void auto_drain_output(void);
void auto_drain_operate_check(void);
void auto_drain_check_timer(void);
void integrate_water_quantity(void);
void UseWater48HoursTotalCount(U8 mu8Type, U8 mu8Data);
void auto_mode_drain_pump_out(void);
void auto_drain_key_off_check(void);
void normal_mode_auto_drain_check_timer(void);
/*void test_mode_auto_drain_check_timer(void);*/


bit F_night;                      // 취침선택
U16 gu16_night_timer;

bit F_first_night_check;

U16 gu16_auto_drain_start_timer_sec;
U16 gu16_auto_drain_start_timer_min;
U16 gu16_auto_drain_start_timer_hour;
bit F_Auto_drain_time_expired;


bit F_drain_operate;

U16 gu16NormalEffluentTotal = 0;      // 24시간 정수(온수) 추출량
U8 gu8ColdEffluentTotal = 0;        // 24시간 냉수 추출량
U16 gu16EffluentTimeCNT = 0;        // 실제 추출 시간 카운터
bit F_AutoDrainCheckOK;             // 자동 배수 체크 완료 Flag
bit F_DrainStatus;                  // 주기 배수 동작 상태 Flag


U16 gu16_auto_drain_check_period;

U8 gu8AutoDrainStep;

U16 gu16ColdDrainTime;

bit F_Cold_Drain;


bit bit_auto_drain_pump_out;


bit F_auto_drain_drinking_check_before_1hour;



U8 gu8_before_drain_water_level;
U16 gu16_cold_drain_op_timer;



bit F_auto_drain_off_check;


U8 gu8_before_2hour_drinking_count;
bit F_save_count;
bit F_auto_drain_drinking_check_before_2hour;

U8 gu8_auto_drain_no_water_timer;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_drain_control(void)
{
    //
    auto_drain_operate_check();

    auto_drain_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_drain_output(void)
{
    U8 mu8_auto_drain_enable_check;

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}


    mu8_auto_drain_enable_check = (U8)(F_DrainStatus & !Bit2_Ice_Operation_Disable_State);

    if(mu8_auto_drain_enable_check == CLEAR)
    {
        gu16ColdDrainTime = 0;
        bit_auto_drain_pump_out = CLEAR;
        F_auto_drain_mode_cold_water_valve_out = CLEAR;
        gu8_before_drain_water_level = DRAIN_LEVEL_EMPTY;
        gu16_cold_drain_op_timer = 0;
        gu8_auto_drain_no_water_timer = 0;
    }
    else
    {
        gu16ColdDrainTime++;

        if(gu16ColdDrainTime >= COLD_DRAIN_TIME)
        {
            gu16ColdDrainTime = 0;
            F_DrainStatus = CLEAR;
        }
        else
        {
            auto_mode_drain_pump_out();
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_mode_drain_pump_out(void)
{
    switch(u8DrainWaterLevel)
    {
        case DRAIN_LEVEL_EMPTY :

             bit_auto_drain_pump_out = CLEAR;
             F_auto_drain_mode_cold_water_valve_out = SET;

             gu8_before_drain_water_level = DRAIN_LEVEL_EMPTY;
             gu16_cold_drain_op_timer = 0;
             gu8_auto_drain_no_water_timer = 0;

            break;

        case DRAIN_LEVEL_LOW :

             /*..hui [18-1-14오후 6:06:23] 물없는 상태에서 냉수 배수밸브 ON 상태로 저수위 진입하면..*/
             if(gu8_before_drain_water_level == DRAIN_LEVEL_EMPTY)
             {
                 gu16_cold_drain_op_timer++;

                 /*..hui [18-1-14오후 6:06:47] 40초 이상 냉수 배수했는데도 만수위에 도달하지 못하면..*/
                 /*..hui [18-1-14오후 6:07:00] 다시 드레인펌프 가동해서 드레인 시작..*/
                 /*..hui [18-1-14오후 6:11:06] 센서 오감지, 유로막힘등의 이유로.. 배수탱크 넘치지 않게 하기위해..???..*/
                 if(gu16_cold_drain_op_timer >= DRAIN_VALVE_OPEN_TIME)
                 {
                     /*gu16_cold_drain_op_timer = DRAIN_VALVE_OPEN_TIME;*/
                     bit_auto_drain_pump_out = SET;
                     F_auto_drain_mode_cold_water_valve_out = CLEAR;

                     /*..hui [18-1-25오후 4:11:59] 드레인펌프 가동으로 전환하고 3초후에 피드백 확인..*/
                     if(gu16_cold_drain_op_timer >= DRAIN_VALVE_OPEN_TIME + 30)
                     {
                         /*..hui [18-1-25오후 4:12:27] 피드백 이하이면 다시 냉수 밸브 ON..*/
                         if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                         {
                             gu16_cold_drain_op_timer = 0;
                         }
                         else
                         {
                             /*..hui [18-1-25오후 4:12:45] 피드백 초과이면 드레인펌프 ON 상태 유지..*/
                             gu16_cold_drain_op_timer = DRAIN_VALVE_OPEN_TIME + 30;
                         }
                     }
                     else{}
                 }
                 else
                 {
                     bit_auto_drain_pump_out = CLEAR;
                     F_auto_drain_mode_cold_water_valve_out = SET;
                 }
             }
             else
             {
                 gu16_cold_drain_op_timer = 0;
                 /*..hui [18-1-14오후 6:15:33] 만수위 감지되고 드레인펌프 가동하여 저수위까지 내려왔을때..*/
                 /*..hui [18-1-14오후 6:21:04] 이것도 센서 오감지나 유로 에어등의 이유로 물없음까지 잘 안내려갈때..*/
                 /*..hui [18-1-14오후 6:21:55] 다시 드레인펌프 OFF하고 냉수 밸브 ON하여 만수위로 가도록....*/
                 if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                 {
                     gu8_auto_drain_no_water_timer++;

                     if( gu8_auto_drain_no_water_timer >= 100 )
                     {
                         gu8_auto_drain_no_water_timer = 100;
                         bit_auto_drain_pump_out = CLEAR;
                         F_auto_drain_mode_cold_water_valve_out = SET;
                     }
                     else
                     {
                         bit_auto_drain_pump_out = SET;
                         F_auto_drain_mode_cold_water_valve_out = CLEAR;
                     }
                 }
                 else
                 {
                     gu8_auto_drain_no_water_timer = 0;
                     bit_auto_drain_pump_out = SET;
                     F_auto_drain_mode_cold_water_valve_out = CLEAR;
                 }
             }

            break;

        case DRAIN_LEVEL_ERROR :
        case DRAIN_LEVEL_HIGH :

             bit_auto_drain_pump_out = SET;
             F_auto_drain_mode_cold_water_valve_out = CLEAR;
             gu8_before_drain_water_level = DRAIN_LEVEL_HIGH;
             gu8_auto_drain_no_water_timer = 0;

            break;

        //=====================================================
        default :

             bit_auto_drain_pump_out = CLEAR;
             F_auto_drain_mode_cold_water_valve_out = CLEAR;
             gu8_before_drain_water_level = DRAIN_LEVEL_EMPTY;

            break;
      }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_drain_operate_check(void)
{
    auto_drain_check_timer();
    integrate_water_quantity();

    /*F_drain_operate = F_night & F_Auto_drain_time_expired;*/

    F_drain_operate = F_Auto_drain_time_expired;

    if(F_drain_operate == SET)
    {
        gu16_auto_drain_check_period++;

        /*..hui [18-1-9오전 10:23:34] 야간 절전 진입하고 24시간 지나고 3분동안 확인..*/
        /*..hui [18-1-14오후 7:28:36] 3분동안 정수 레벨 만수위 조건 안되면 체크 안하고 빠져나감..*/
        /*if(gu16_auto_drain_check_period >= 1800)*/
        /*..hui [23-7-31오후 3:04:56] 30분.. 제어사양서에 30분으로 나와있음..*/
        if(gu16_auto_drain_check_period >= 18000)
        {
            gu16_auto_drain_check_period = 0;
            gu16NormalEffluentTotal = 0;
            gu8ColdEffluentTotal = 0;
            F_Auto_drain_time_expired = CLEAR;
            F_DrainStatus = CLEAR;
        }
        else{}

        /*if(gu8_room_level == 2)*/
        if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
        {
            // 만수위인 경우(만수위 센서 감지 상태)
            if(F_AutoDrainCheckOK != SET)
            {
                F_AutoDrainCheckOK = SET;

                #if 0
                if (gu16NormalEffluentTotal <= 8)
                {
                    F_DrainStatus = SET;
                }
                else if (gu8ColdEffluentTotal <= 6)
                {
                    F_DrainStatus = SET;
                }
                else{}
                #endif

                /*..hui [23-7-31오후 3:11:01] 냉온정 통합으로 확인.. 제어사양서에 냉수 1.5L로 나와있음..*/
                /*..hui [23-7-31오후 3:11:21] 120cc 기준 12잔..*/
                if (gu16NormalEffluentTotal < AUTO_DRAIN_OPERATION_WATER)
                {
                    F_DrainStatus = SET;
                }
                else{}

                gu16NormalEffluentTotal = 0;
                gu8ColdEffluentTotal = 0;
                F_Auto_drain_time_expired = CLEAR;
            }
            else{}
        }
        else{}
    }
    else
    {
        F_AutoDrainCheckOK = CLEAR;
        gu16_auto_drain_check_period = 0;
    }

    /*..hui [18-1-14오후 7:35:24] 에러 걸리면 자동배수 안함..*/
    /*if(F_HardError == SET || F_Circul_Drain != SET || F_auto_drain_off_check == SET)*/
    if( Bit2_Ice_Operation_Disable_State == SET || F_Circul_Drain != SET
        || F_auto_drain_off_check == SET || F_WaterOut == SET || bit_filter_all == CLEAR )
    {
        F_auto_drain_off_check = CLEAR;
        F_DrainStatus = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_drain_key_off_check(void)
{
    if(F_DrainStatus == SET)
    {
        F_auto_drain_off_check = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void auto_drain_check_timer(void)
{
    #if 0
    if(F_LineTest == SET)
    {
        test_mode_auto_drain_check_timer();
    }
    else
    {
        normal_mode_auto_drain_check_timer();
    }
    #endif

    normal_mode_auto_drain_check_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_mode_auto_drain_check_timer(void)
{
    if(F_Circul_Drain != SET)
    {
        /*..hui [18-1-14오후 8:43:52] 순환배수 실행 중 기능 OFF 시 종료..*/
        F_Auto_drain_time_expired = CLEAR;
    }
    else{}

    /*..hui [18-1-14오후 8:53:23] 순환배수 기능이 OFF더라도 시간 카운트 및 조건 확인은 계속 하도록 변경....*/
    /*..hui [18-1-14오후 8:53:41] 그러면 나중에 다시 ON할때 야간시간으로 최적화 되있겠지..*/
    gu16_auto_drain_start_timer_sec++;

    if(gu16_auto_drain_start_timer_sec >= 600)
    {
        gu16_auto_drain_start_timer_sec = 0;
        gu16_auto_drain_start_timer_min++;

    }
    else{}

    if(gu16_auto_drain_start_timer_min >= 60)
    {
        gu16_auto_drain_start_timer_min = 0;
        gu16_auto_drain_start_timer_hour++;

    }
    else{}

    /*..hui [18-1-29오전 9:23:04] 24시간 되기 2시간 전에 물 먹었는지 확인..*/
    /*if(gu16_auto_drain_start_timer_hour >= 22)*/
    /*..hui [23-7-31오후 2:58:50] 72시간되기 2시간 전..*/
    if(gu16_auto_drain_start_timer_hour >= 70)
    {
        if(F_WaterOut == SET)
        {
            F_auto_drain_drinking_check_before_2hour = SET;
        }
        else{}
    }
    else{}

    /*..hui [18-1-14오후 7:02:24] 24시간되기 1시간 전에 물 먹었는제 확인..*/
    /*if(gu16_auto_drain_start_timer_hour >= 23)*/
    /*..hui [23-7-31오후 2:59:10] 72시간되기 1시간 전..*/
    if(gu16_auto_drain_start_timer_hour >= 71)
    {
        if(F_WaterOut == SET)
        {
            F_auto_drain_drinking_check_before_1hour = SET;
        }
        else{}
    }
    else{}

    /*if(gu16_auto_drain_start_timer_hour >= 24)*/
    /*..hui [23-7-31오후 2:59:28] 72시간 경과 확인..*/
    if(gu16_auto_drain_start_timer_hour >= 72)
    {
        /*..hui [18-1-14오후 7:19:19] 24시간되기 한시간 전에 물을 먹었으면..*/
        /*..hui [18-1-14오후 7:19:30] 한시간 더 후에 드레인 체크..*/
        if(F_auto_drain_drinking_check_before_1hour == SET)
        {
            gu8_before_2hour_drinking_count = 0;
        }
        else
        {
            gu16_auto_drain_start_timer_hour = 0;
            F_Auto_drain_time_expired = SET;

            gu16_auto_drain_start_timer_sec = 0;
            gu16_auto_drain_start_timer_min = 0;
            gu16_auto_drain_start_timer_hour = 0;
            F_auto_drain_drinking_check_before_1hour = CLEAR;

            /*..hui [18-1-29오전 9:47:42] 2시간 부터 물 음용이 없으면..*/
            if(F_auto_drain_drinking_check_before_2hour == CLEAR)
            {
                gu8_before_2hour_drinking_count++;

                /*..hui [18-1-29오전 9:53:21] 3일 연속 2시간 전부터 물 음용이 없으면 전체 시간  1시간 감소..*/
                if(gu8_before_2hour_drinking_count >= 7)
                {
                    gu8_before_2hour_drinking_count = 0;
                    gu16_auto_drain_start_timer_hour = 1;
                }
                else{}
            }
            else
            {
                gu8_before_2hour_drinking_count = 0;
                F_auto_drain_drinking_check_before_2hour = CLEAR;
            }
        }
    }
    else{}

    /*if(gu16_auto_drain_start_timer_hour >= 25)*/
    /*..hui [23-7-31오후 3:00:57] 73시간 1시간 지연 확인..*/
    if(gu16_auto_drain_start_timer_hour >= 73)
    {
        gu16_auto_drain_start_timer_hour = 0;
        F_Auto_drain_time_expired = SET;

        gu16_auto_drain_start_timer_sec = 0;
        gu16_auto_drain_start_timer_min = 0;
        gu16_auto_drain_start_timer_hour = 0;
        F_auto_drain_drinking_check_before_1hour = CLEAR;
        F_auto_drain_drinking_check_before_2hour = CLEAR;

    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void test_mode_auto_drain_check_timer(void)
{
    /*if(F_Auto_drain_time_expired == SET || F_Circul_Drain != SET)*/
    if(F_Circul_Drain != SET)
    {
        /*gu16_auto_drain_start_timer_sec = 0;
               gu16_auto_drain_start_timer_min = 0;
               gu16_auto_drain_start_timer_hour = 0;
              F_auto_drain_drinking_check_before_1hour = CLEAR;*/
        /*..hui [18-1-14오후 8:43:52] 순환배수 실행 중 기능 OFF 시 종료..*/
        F_Auto_drain_time_expired = CLEAR;
    }
    else
    {
        /*gu16_auto_drain_start_timer_sec++;*/
    }

    /*..hui [18-1-14오후 8:53:23] 순환배수 기능이 OFF더라도 시간 카운트 및 조건 확인은 계속 하도록 변경....*/
    /*..hui [18-1-14오후 8:53:41] 그러면 나중에 다시 ON할때 야간시간으로 최적화 되있겠지..*/
    gu16_auto_drain_start_timer_sec++;

    if(gu16_auto_drain_start_timer_sec >= 600)
    {
        gu16_auto_drain_start_timer_sec = 0;
        gu16_auto_drain_start_timer_hour++;

    }
    else{}


    /*..hui [18-1-29오전 9:23:04] 24시간 되기 2시간 전에 물 먹었는지 확인..*/
    if(gu16_auto_drain_start_timer_hour >= 8)
    {
        if(F_WaterOut == SET)
        {
            F_auto_drain_drinking_check_before_2hour = SET;
        }
        else{}
    }
    else{}


    /*..hui [18-1-14오후 7:02:24] 24시간되기 1시간 전에 물 먹었는제 확인..*/
    if(gu16_auto_drain_start_timer_hour >= 9)
    {
        if(F_WaterOut == SET)
        {
            F_auto_drain_drinking_check_before_1hour = SET;
        }
        else{}
    }
    else{}

    if(gu16_auto_drain_start_timer_hour >= 10)
    {
        /*..hui [18-1-14오후 7:19:19] 24시간되기 한시간 전에 물을 먹었으면..*/
        /*..hui [18-1-14오후 7:19:30] 한시간 더 후에 드레인 체크..*/
        if(F_auto_drain_drinking_check_before_1hour == SET)
        {
            gu8_before_2hour_drinking_count = 0;
        }
        else
        {
            gu16_auto_drain_start_timer_hour = 0;
            F_Auto_drain_time_expired = SET;

            gu16_auto_drain_start_timer_sec = 0;
            gu16_auto_drain_start_timer_min = 0;
            gu16_auto_drain_start_timer_hour = 0;
            F_auto_drain_drinking_check_before_1hour = CLEAR;

            /*..hui [18-1-29오전 9:47:42] 2시간 부터 물 음용이 없으면..*/
            if(F_auto_drain_drinking_check_before_2hour == CLEAR)
            {
                gu8_before_2hour_drinking_count++;

                /*..hui [18-1-29오전 9:53:21] 3일 연속 2시간 전부터 물 음용이 없으면 전체 시간  1시간 감소..*/
                if(gu8_before_2hour_drinking_count >= 3)
                {
                    gu8_before_2hour_drinking_count = 0;
                    gu16_auto_drain_start_timer_hour = 1;
                }
                else{}
            }
            else
            {
                gu8_before_2hour_drinking_count = 0;
                F_auto_drain_drinking_check_before_2hour = CLEAR;
            }
        }
    }
    else{}

    if(gu16_auto_drain_start_timer_hour >= 11)
    {
        gu16_auto_drain_start_timer_hour = 0;
        F_Auto_drain_time_expired = SET;

        gu16_auto_drain_start_timer_sec = 0;
        gu16_auto_drain_start_timer_min = 0;
        gu16_auto_drain_start_timer_hour = 0;
        F_auto_drain_drinking_check_before_1hour = CLEAR;
        F_auto_drain_drinking_check_before_2hour = CLEAR;
    }
    else{}
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void integrate_water_quantity(void)
{
    U8 mu8_minimum_time;

    if(u8WaterOutState == PURE_WATER_SELECT)
    {
        /*mu8_minimum_time = EXTRACT_TIME_AMBIENT_WATER_4_OZ;*/
        mu8_minimum_time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML;
    }
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        mu8_minimum_time = EXTRACT_TIME_COLD_WATER_4_OZ_120_ML;
    }
    else
    {
        mu8_minimum_time = EXTRACT_TIME_HOT_WATER_4_OZ_120_ML;
    }


    if(F_WaterOut == SET)
    {
        gu16EffluentTimeCNT++;

        if(gu16EffluentTimeCNT >= u16Efluent_Time - 1)
        {
            if(u8Extract_Continue == SET)
            {
                UseWater48HoursTotalCount(u8WaterOutState, (U8)(gu16EffluentTimeCNT / mu8_minimum_time));
            }
            else
            {
                // 24시간 물 사용량 적산
                /*UseWater48HoursTotalCount(u8WaterOutState, gu8Cup_level);*/
                UseWater48HoursTotalCount(u8WaterOutState, 255);
                gu16EffluentTimeCNT = 0;
            }
        }
        else
        {

        }
    }
    else
    {
        // 24시간 물 사용량 적산
        if(gu16EffluentTimeCNT != 0)
        {
            /*..hui [18-1-14오후 9:39:17] 중간에 멈췄을 경우에도 최소 한잔으로 인식하도록..*/
            if(gu16EffluentTimeCNT < mu8_minimum_time)
            {
                gu16EffluentTimeCNT = mu8_minimum_time;
            }
            else{}

            UseWater48HoursTotalCount(u8WaterOutState, (U8)(gu16EffluentTimeCNT / mu8_minimum_time));
            gu16EffluentTimeCNT = 0;
        }
        else{}
    }

    /*..hui [18-1-14오후 8:47:29] 순환 배수 기능 OFF시 음용량 초기화..*/
    /*..hui [18-1-14오후 8:56:16] 순환 배수 기능 OFF더라도 시간 조건 확인은 동작하도록 변경..*/
    /*if(F_Circul_Drain != SET)
    {
        gu16EffluentTimeCNT = 0;
        gu16NormalEffluentTotal = 0;
        gu8ColdEffluentTotal = 0;
    }
    else{}*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/// @brief    자동배수 기능을 위한 24시간 물 사용량 누적 함수(추출시 저장)
/// @param    mu8Type     : 추출 물종류
///           mu8Data     : 추출량
/// @return   void
void UseWater48HoursTotalCount(U8 mu8Type, U8 mu8Data)
{
    U16 mu16_w = 0;

    /*..hui [23-7-31오후 3:11:01] 냉온정 통합으로 확인.. 제어사양서에 냉수 1.5L로 나와있음..*/
    /*..hui [23-7-31오후 3:11:21] 120cc 기준 12잔..*/
    if (gu16NormalEffluentTotal >= AUTO_DRAIN_OPERATION_WATER)
    {
        gu16NormalEffluentTotal = AUTO_DRAIN_OPERATION_WATER;
    }
    else
    {
        /*..hui [23-7-31오후 5:18:07] 연속은 120미리 기준으로 시간으로 더해줌..*/
        /*if(u8Extract_Continue == SET)*/
        if(mu8Data != 255)
        {
            mu16_w = mu8Data * 120;
        }
        else
        {
            switch(gu8Cup_level)
            {
                case CUP_LEVEL__4_OZ__120_ML:

                    mu16_w = 120;

                    break;

                case CUP_LEVEL__6_OZ__175_ML:

                    mu16_w = 175;

                    break;

                case CUP_LEVEL__8_OZ__235_ML:

                    mu16_w = 235;

                    break;

                case CUP_LEVEL__10_OZ__295_ML:

                    mu16_w = 295;

                    break;

                case CUP_LEVEL__12_OZ__355_ML:

                    mu16_w = 355;

                    break;

                case CUP_LEVEL__14_OZ__415_ML:

                    mu16_w = 415;

                    break;

                case CUP_LEVEL__16_OZ__475_ML:

                    mu16_w = 475;

                    break;

                case CUP_LEVEL__20_OZ__590_ML:

                    mu16_w = 590;

                    break;

                #if 0
                case CUP_LEVEL__32_OZ__945_ML:

                    mu16_w = 945;

                    break;
                #endif

                default:

                    mu16_w = 0;

                    break;
            }
        }

        gu16NormalEffluentTotal = gu16NormalEffluentTotal + mu16_w;
    }



    #if 0
    if ((mu8Type == PURE_WATER_SELECT))
    {
        if (gu16NormalEffluentTotal >= 200)
        {
            gu16NormalEffluentTotal = 200;
        }
        else
        {
            gu16NormalEffluentTotal = gu16NormalEffluentTotal + mu8Data;    // 120cc를 기준으로 컵수 산정
        }
    }
    else if (mu8Type == COLD_WATER_SELECT)
    {
        if (gu8ColdEffluentTotal >= 200)
        {
            gu8ColdEffluentTotal = 200;
        }
        else
        {
            gu8ColdEffluentTotal = gu8ColdEffluentTotal + mu8Data;    // 120cc를 기준으로 컵수 산정
        }
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




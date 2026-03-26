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
#include    "ster_ice_tank.h"

void start_ice_tank_ster(void);
void stop_ice_tank_ster(void);
void ice_tank_ster_control(void);
void halt_ice_tank_ster(void);

void finish_ice_ster(void);
void skip_ice_ster(void);

U8 check_ice_ster_enable(void);
U8 prepare_ster(void);
U8 hot_circulation(void);

U8 hot_spray(void);
U8 overheat_circulation(void);
U8 lukewarm_spray(void);
U8 final_clean(void);
/////U8 ice_tank_ster_proc(void);
void init_ice_ster(void);
void periodic_ster(void);
void manual_disable_timer(void);
void hot_ster_temp_decision(void);
U8 prepare_melt_ice(void);
U8 melt_ice(void);
U8 wait_finish_clean(void);
U8 prepare_icetray_clean(void);
U8 icetray_clean(void);
void sel_start_temp(void);


/***********************************************************************************************************************/

TYPE_BYTE          U8SkipIceSterB;
#define            u8SkipIceSter                            U8SkipIceSterB.byte
#define            Bit0_Circulation_Hot_Skip_State          U8SkipIceSterB.Bit.b0
#define            Bit1_Hot_Spray_Skip_State                U8SkipIceSterB.Bit.b1
#define            Bit2_Lukewarm_Spray_Skip_State           U8SkipIceSterB.Bit.b2
#define            Bit3_Final_Clean_Skip_State              U8SkipIceSterB.Bit.b3
#define            Bit4_Ice_Tray_Clean_Skip_State           U8SkipIceSterB.Bit.b4
#define            Bit5_Melt_Ice_Skip_State                 U8SkipIceSterB.Bit.b5



/***********************************************************************************************************************/
U8 gu8_prepare_ster_step;
U16 gu16_prepare_ster_timer;
U16 gu16_prepare_ster_max_timer;

U8 gu8_hot_circulation_step;
U16 gu16_hot_circulation_timer;
U16 gu16_hot_circulation_max_timer;


U8 gu8_hot_spray_step;
U16 gu16_hot_spray_timer;
U16 gu16_hot_spray_max_timer;


U8 gu8_overheat_circul_step;
U16 gu16_overheat_circul_timer;

U8 gu8_lukewarm_spray_step;
U16 gu16_lukewarm_spray_timer;
U16 gu16_lukewarm_spray_max_timer;

U8 gu8_final_clean_step;
U16 gu16_final_clean_timer;
U16 gu16_final_clean_max_timer;

U8 gu8_ice_tray_prepare_step;
U16 gu16_ice_tray_prepare_timer;
U32 gu32_ice_tray_prepare_max_timer;

U8 gu8_ice_tray_clean_step;
U16 gu16_ice_tray_clean_timer;
U32 gu32_ice_tray_clean_max_timer;


U8 gu8_melt_ice_prepare_step;
U16 gu16_melt_ice_prepare_timer;
U32 gu32_melt_ice_prepare_max_timer;

U8 gu8_melt_ice_step;
U16 gu16_melt_ice_timer;
U32 gu32_melt_ice_max_timer;

U8 gu8_melt_ice_count;

U8 gu8_wait_finish_step;
U16 gu16_wait_finish_timer;
U16 gu16_wait_finish_max_timer;


U8 gu8_ice_tank_ster_step;
U16 gu16_ice_tank_ster_timer;

bit bit_ice_tank_ster_start;
U16 gu16_Ice_Tank_Ster_Hz;

/*..hui [23-2-28오후 7:53:51] steam off 설정용 임시..*/
bit bit_steam_off;


U16 gu16_steam_timer;

ICE_STER_MODE gu8_ice_ster_mode;
U16 gu16_ice_ster_op_timer;

bit bit_periodic_ster_enable;
bit bit_periodic_ster_first_display;

U8 gu8_wifi_period_ster_hour;
U8 gu8_wifi_period_ster_minute;


U8 gu8_ster_pump_stage;

U16 gu16_periodic_ster_time_total;
U16 gu16_periodic_ster_current_time_total;

U16 gu16_20_minute_before_ster;
U16 gu16_2_hour_before_ster;

bit bit_extract_stop_before_ster_start;

bit bit_periodic_ster_ready;

U16 gu16_ster_ready_max_timer;

U8 gu8_periodic_ster_count;
bit bit_ster_count_check;

U16 gu16_drain_fault_timer;


HOT_STER_OP_TEMP gu8_hot_ster_temp_mode;
U8 gu8_hot_ster_operation_temp;

bit bit_hot_ster_ice_full;
U8 gu8_ster_ice_extract_timer;
U8 gu8_ster_ice_extract_count;


U8 gu8_manual_operation_count;
U16 gu16_manual_minute;
U16 gu16_manual_hour;

bit bit_hot_ster_today;


U8 gu8_test_count;

bit bit_debug_skip_ice_ster;


U8 gu8_hot_spray_start_hot_temp;
U8 gu8_lukewarm_spray_start_hot_temp;
U8 gu8_final_clean_start_hot_temp;

U8 gu8_ice_tray_start_hot_temp;
U8 gu8_mlet_ice_start_hot_temp;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_tank_ster(void)
{
    bit_ice_tank_ster_start = SET;

    /*bit_extract_stop_before_ster_start = CLEAR;*/
    bit_periodic_ster_ready = CLEAR;

    gu8_steam_clean_percent = 0;
    gu16_drain_fault_timer = 0;

    init_ice_ster();

    #if 0
    /*..hui [23-8-29오전 10:10:01] 어떤 조건이더라도 시작 전에 만빙 상태이면 75도로..*/
    if( F_IceFull == SET )
    {
        gu8_hot_ster_temp_mode = HOT_STER_TEMP_HIGH_MODE;
    }
    else{}
    #endif

    /*..hui [23-9-7오후 3:59:14] 온수 추출 금지도 해제..*/
    /*bit_extract_stop_before_ster_start = CLEAR;*/

    gu8_melt_ice_count = 0;

    u8SkipIceSter = 0;
    bit_debug_skip_ice_ster = CLEAR;

    /*..hui [24-5-28오후 3:23:42] 아이스 도어 강제로 닫는다....*/
    /*..hui [24-5-28오후 3:23:54] 빠져있었는데 아무도 모름............. 신뢰성에서 발견..*/
    F_IceDoorClose = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_ice_tank_ster(void)
{
    bit_ice_tank_ster_start = CLEAR;

    bit_periodic_ster_ready = CLEAR;

    gu8_steam_clean_percent = 0;
    gu16_drain_fault_timer = 0;

    finish_ice_ster();

    /*..hui [23-8-28오후 4:36:23] 세척 시작하면 전부 초기화..*/

    /*..hui [23-11-8오후 2:10:48] 얼음양에 따른 제어 변경 삭제. 만빙 사양으로 통일..*/
    /*gu8_hot_ster_temp_mode = HOT_STER_TEMP_LOW_MODE;*/
    /*bit_hot_ster_ice_full = CLEAR;*/
    /*bit_extract_stop_before_ster_start = CLEAR;*/

    gu8_ster_ice_extract_timer = 0;
    gu8_ster_ice_extract_count = 0;

    /*..hui [23-9-7오후 3:59:14] 온수 추출 금지도 해제..*/
    /*bit_extract_stop_before_ster_start = CLEAR;*/

    gu8_melt_ice_count = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_tank_ster_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_enable = 0;

    halt_ice_tank_ster();

    manual_disable_timer();

    sel_start_temp();

    switch( gu8_ice_ster_mode )
    {
        case STER_MODE_NONE_STATE:

            mu8_enable = check_ice_ster_enable();

            if( mu8_enable == SET )
            {
                gu8_ice_ster_mode = STER_MODE_PREPARE;
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step = 0;
            }
            else{}

        break;

        case STER_MODE_PREPARE:

            mu8_enable = prepare_ster();

            if( mu8_enable == SET )
            {
                gu8_ice_ster_mode = STER_MODE_CIRCULATION_HOT_STATE;
                gu16_hot_circulation_timer = 0;
                gu8_hot_circulation_step = 0;
            }
            else{}

        break;

        case STER_MODE_CIRCULATION_HOT_STATE:

            mu8_enable = hot_circulation();

            if( mu8_enable == SET )
            {
                gu8_ice_ster_mode = STER_MODE_HOT_SPRAY_STATE;
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step = 0;
            }
            else{}

        break;


        case STER_MODE_HOT_SPRAY_STATE:

            mu8_finish = hot_spray();

            if( mu8_finish == SET )
            {
                gu8_ice_ster_mode = STER_MODE_LUKEWARM_SPRAY_STATE;
                gu16_lukewarm_spray_timer = 0;
                gu8_lukewarm_spray_step = 0;
            }
            else{}

        break;

        case STER_MODE_LUKEWARM_SPRAY_STATE:

            mu8_finish = lukewarm_spray();

            if( mu8_finish == SET )
            {
                gu8_ice_ster_mode = STER_MODE_FINAL_CLEAN_STATE;
                gu16_final_clean_timer = 0;
                gu8_final_clean_step = 0;
            }
            else{}

        break;

        case STER_MODE_FINAL_CLEAN_STATE:

            mu8_finish = final_clean();

            if( mu8_finish == SET )
            {
                #if 0
                /*finish_ice_ster();*/
                gu8_ice_ster_mode = STER_MODE_MELT_ICE_PREPARE;
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step = 0;

                gu8_melt_ice_count = 0;
                #endif

                gu8_ice_ster_mode = STER_MODE_ICE_TRAY_CLEAN_PREPARE;
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step = 0;
            }
            else{}

        break;

        case STER_MODE_ICE_TRAY_CLEAN_PREPARE:

            mu8_finish = prepare_icetray_clean();

            if( mu8_finish == SET )
            {
                gu8_ice_ster_mode = STER_MODE_ICE_TRAY_CLEAN;
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step = 0;
            }
            else{}

        break;

        case STER_MODE_ICE_TRAY_CLEAN:

            mu8_finish = icetray_clean();

            if( mu8_finish == SET )
            {
                gu8_ice_ster_mode = STER_MODE_MELT_ICE_PREPARE;
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step = 0;

                gu8_melt_ice_count = 0;
            }
            else{}

        break;


        case STER_MODE_MELT_ICE_PREPARE:

            mu8_finish = prepare_melt_ice();

            if( mu8_finish == SET )
            {
                gu8_ice_ster_mode = STER_MODE_MELT_ICE;
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step = 0;
            }
            else{}

        break;


        case STER_MODE_MELT_ICE:

            mu8_finish = melt_ice();

            if( mu8_finish == SET )
            {
                gu8_melt_ice_count++;

                /*..hui [23-10-17오후 2:23:54] 동일하게 3회 반복..*/
                /*if( gu8_melt_ice_count >= ICE_MELT_OPERATION_COUNT )*/
                /*if( gu8_melt_ice_count >= gu8_test_count )*/
                /*..hui [23-10-23오후 1:53:39] 4회 최종..*/
                /*..hui [24-1-25오전 11:50:07] 아이스 트레이 세척 추가되면서 3회로 다시 변경..*/
                if( gu8_melt_ice_count >= ICE_MELT_OPERATION_COUNT )
                {
                    gu8_ice_ster_mode = STER_MODE_FINISH;
                    gu8_melt_ice_count = 0;

                    gu8_wait_finish_step = 0;
                    gu16_wait_finish_timer = 0;
                    gu16_wait_finish_max_timer = 0;
                }
                else
                {
                    gu8_ice_ster_mode = STER_MODE_MELT_ICE_PREPARE;
                    gu16_melt_ice_prepare_timer = 0;
                    gu32_melt_ice_prepare_max_timer = 0;
                    gu8_melt_ice_prepare_step = 0;
                }
            }
            else{}

        break;

        case STER_MODE_FINISH:

            mu8_finish = wait_finish_clean();

            if( mu8_finish == SET )
            {
                finish_ice_ster();
            }
            else{}

        break;


        default:

            gu8_ice_ster_mode = STER_MODE_NONE_STATE;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void halt_ice_tank_ster(void)
{
    /*if( gu8_ice_ster_mode >= STER_MODE_HOT_SPRAY_STATE )*/
    if( gu8_ice_ster_mode >= STER_MODE_CIRCULATION_HOT_STATE )
    {
        if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
        {
            /*play_melody_warning_197();*/
            /*finish_ice_ster();*/
            /*..hui [24-1-31오후 5:32:20] 분사하다가 저수위 감지될때는 다음 단계로 이동하도록 수정..*/
            /*..hui [24-1-31오후 5:32:33] 어쩌다 한번 미감지될 경우에도 정상 동작하기위해..*/
            skip_ice_ster();

            if( bit_debug_skip_ice_ster == CLEAR )
            {
                bit_debug_skip_ice_ster = SET;

                gu8_ice_ster_low_water_stop_count++;

                if( gu8_ice_ster_low_water_stop_count >= 99 )
                {
                    gu8_ice_ster_low_water_stop_count = 99;
                }
                else{}
            }
            else{}
        }
        else
        {
            bit_debug_skip_ice_ster = CLEAR;
        }

        if( Bit3_Ice_Tank_Ster_Operation_Disable_State == SET )
        {
            /*play_melody_warning_197();*/
            finish_ice_ster();
        }
        else{}

        if( F_Tank_Cover_Input == CLEAR )
        {
            play_melody_warning_197();
            finish_ice_ster();
        }
        else{}

        /*..hui [23-7-28오후 3:42:30] 중간에 사이드커버, RO 필터 열림 감지되면 정지..*/
        /*if( bit_filter_cover == CLEAR || bit_ro_filter_2_reed == CLEAR )*/
        if( bit_filter_all == CLEAR )
        {
            play_melody_warning_197();
            finish_ice_ster();
        }
        else{}

        /*..hui [23-8-28오전 9:38:31] 드레인 센서 에러(만수감지/저수미감지)일 경우 세척 중단.. 이정환 부장님 요청..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        {
            gu16_drain_fault_timer++;

            /*if( gu16_drain_fault_timer >= 50 )*/
            /*if( gu16_drain_fault_timer >= 600 )*/
            /*..hui [24-2-19오후 5:09:36] 10분 동안 대기하고 빠져나오도록 변경..*/
            if( gu16_drain_fault_timer >= 6000 )
            {
                gu16_drain_fault_timer = 0;
                /*play_melody_warning_197();*/
                finish_ice_ster();

                gu8_ice_ster_drain_stop_count++;

                if( gu8_ice_ster_drain_stop_count >= 99 )
                {
                    gu8_ice_ster_drain_stop_count = 99;
                }
                else{}
            }
            else{}
        }
        else
        {
            gu16_drain_fault_timer = 0;
        }
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_ice_ster(void)
{
    bit_ice_tank_ster_start = CLEAR;
    gu8_ice_ster_mode = STER_MODE_NONE_STATE;

    /*..hui [23-2-28오후 7:52:59] NIC용으로 임시.....*/
    ////bit_steam_off  = CLEAR;

    /*..hui [23-8-28오후 4:36:23] 세척 시작하면 전부 초기화..*/
    /*gu8_hot_ster_temp_mode = HOT_STER_TEMP_LOW_MODE;*/
    /*bit_hot_ster_ice_full = CLEAR;*/

    init_ice_ster();

    /*..hui [23-5-22오후 7:08:41] 트레이 올라가있는 상태면 트레이 내림..*/
    /*if( gu8_ice_system_ok == SET && F_TrayMotorUP == CLEAR && gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )*/
    if( gu8_ice_system_ok == SET && gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )
    {
        down_tray_motor();
    }
    else{}

    /*..hui [23-9-7오후 3:59:14] 온수 추출 금지도 해제..*/
    /*bit_extract_stop_before_ster_start = CLEAR;*/

    gu8_melt_ice_count = 0;

    /*..hui [23-11-6오전 9:11:27] 세척 중간에 중단되거나 끝나면 만빙감지..*/
    F_IR = SET;

    u8SkipIceSter = 0;
    bit_debug_skip_ice_ster = CLEAR;

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void skip_ice_ster(void)
{

    if( gu8_ice_ster_mode == STER_MODE_CIRCULATION_HOT_STATE )
    {
        if( Bit0_Circulation_Hot_Skip_State == CLEAR )
        {
            Bit0_Circulation_Hot_Skip_State = SET;

            gu16_hot_circulation_timer = 0;
            gu16_hot_circulation_max_timer = 0;
            gu8_hot_circulation_step = 4;
        }
        else{}
    }
    else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
    {
        if( Bit1_Hot_Spray_Skip_State == CLEAR )
        {
            Bit1_Hot_Spray_Skip_State = SET;

            gu16_hot_spray_timer = 0;
            gu16_hot_spray_max_timer = 0;
            gu8_hot_spray_step = 11;
        }
        else{}
    }
    else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
    {
        if( Bit2_Lukewarm_Spray_Skip_State == CLEAR )
        {
            Bit2_Lukewarm_Spray_Skip_State = SET;

            gu16_lukewarm_spray_timer = 0;
            gu16_lukewarm_spray_max_timer = 0;
            gu8_lukewarm_spray_step = 13;
        }
        else{}
    }
    else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
    {
        if( Bit3_Final_Clean_Skip_State == CLEAR )
        {
            Bit3_Final_Clean_Skip_State = SET;

            gu16_final_clean_timer = 0;
            gu16_final_clean_max_timer = 0;
            gu8_final_clean_step = 15;
        }
        else{}
    }
    else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
    {
        if( Bit4_Ice_Tray_Clean_Skip_State == CLEAR )
        {
            Bit4_Ice_Tray_Clean_Skip_State = SET;

            gu16_ice_tray_clean_timer = 0;
            gu32_ice_tray_clean_max_timer = 0;
            gu8_ice_tray_clean_step = 19;
        }
        else{}
    }
    else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
    {
        if( Bit5_Melt_Ice_Skip_State == CLEAR )
        {
            Bit5_Melt_Ice_Skip_State = SET;

            gu16_melt_ice_timer = 0;
            gu32_melt_ice_max_timer = 0;
            gu8_melt_ice_step = 23;
        }
        else{}
    }
    else
    {
        u8SkipIceSter = 0;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 check_ice_ster_enable(void)
{
    U8 mu8_return = 0;

    periodic_ster();

    if( bit_ice_tank_ster_start == SET )
    {
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void periodic_ster(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;

    if( bit_periodic_ster_enable == CLEAR || bit_first_time_setting == CLEAR )
    {
        /*bit_extract_stop_before_ster_start = CLEAR;*/
        bit_periodic_ster_ready = CLEAR;
        gu16_ster_ready_max_timer = 0;
        bit_ster_count_check = CLEAR;
        /*gu8_periodic_ster_count = PERIODIC__STER_CYCLE;*/
        gu8_periodic_ster_count = FIRST_POWER_ON_PERIODIC__STER_CYCLE;

        gu8_ster_ice_extract_timer = 0;
        gu8_ster_ice_extract_count = 0;

        return;
    }
    else{}

    /*..hui [23-6-29오후 4:01:43] 시간, 분 분리되면 넘~~~~~~~~~~~~ 헷갈려서 통합해서....*/
    gu16_periodic_ster_current_time_total = (U16)((U16)gu8_rtc_time_Hour * 100);
    gu16_periodic_ster_current_time_total = gu16_periodic_ster_current_time_total + gu8_rtc_time_Min;

    gu16_periodic_ster_time_total = (U16)((U16)gu8_wifi_period_ster_hour * 100);
    gu16_periodic_ster_time_total = gu16_periodic_ster_time_total + gu8_wifi_period_ster_minute;


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    /*..hui [23-7-7오후 4:08:26] 새벽 1시 이전으로 설정되면.. 12시 00분 ~ 12시 59분 이전..*/
    if( gu16_periodic_ster_time_total < 100 )
    {
        gu16_2_hour_before_ster = (U16)((U16)22 * 100);
        gu16_2_hour_before_ster = gu16_2_hour_before_ster + gu8_wifi_period_ster_minute;
    }
    else if( gu16_periodic_ster_time_total < 200 )
    {
        /*..hui [23-8-28오전 10:51:04] 새벽 1시 이후부터 새벽 2시 이전으로 설정되면.. 1시 00분 ~ 1시 59분..*/
        gu16_2_hour_before_ster = (U16)((U16)23 * 100);
        gu16_2_hour_before_ster = gu16_2_hour_before_ster + gu8_wifi_period_ster_minute;
    }
    else
    {
        /*..hui [23-8-28오전 9:53:36] 2시간 전..*/
        gu16_2_hour_before_ster = gu16_periodic_ster_time_total - 200;
    }
    #endif

    #if 0
    if( gu8_periodic_ster_count >= (PERIODIC__STER_CYCLE - 1) )
    {
        /*..hui [23-9-6오후 3:31:40] 고온세척 하는날..*/
        bit_hot_ster_today = SET;
    }
    else
    {
        bit_hot_ster_today = CLEAR;
    }
    #endif


    #if 0
    if( bit_hot_ster_today == SET )
    {
        /*..hui [23-8-28오후 4:30:51] 세척 시작 2시간 전에 만빙인지 확인..*/
        if( gu16_periodic_ster_current_time_total == gu16_2_hour_before_ster )
        {
            /*..hui [23-8-28오전 11:06:21] 세척 시작 2시간 전에 1분동안 만빙 상태인지 확인..*/
            /*..hui [23-8-28오전 11:14:43] 세척하는날 당일에만..*/
            if( F_IceFull == SET )
            {
                bit_hot_ster_ice_full = SET;
            }
            else
            {
                bit_hot_ster_ice_full = CLEAR;
            }
        }
        else
        {
            if( bit_hot_ster_ice_full == SET )
            {
                if( F_Ice == SET )
                {
                    gu8_ster_ice_extract_timer++;

                    /*..hui [23-8-28오전 11:11:59] 만빙인 상태에서 얼음을 7초 이상 추출했거나..*/
                    /*..hui [23-8-28오전 11:12:10] 7초가 안되더라도 얼음을 2회 이상 추출했을 경우..*/
                    /*if( gu8_ster_ice_extract_timer >= 70 || gu8_ster_ice_extract_count >= 2 )*/
                    /*..hui [23-9-6오후 5:00:10] 3회로 우선 변경..*/
                    /*if( gu8_ster_ice_extract_timer >= 80 || gu8_ster_ice_extract_count >= 3 )*/
                    if( gu8_ster_ice_extract_timer >= 80 )
                    {
                        gu8_ster_ice_extract_timer = 80;
                        bit_hot_ster_ice_full = CLEAR;
                    }
                    else{}
                }
                else
                {
                    /*..hui [23-9-6오후 5:05:26] 8초 미만 추출했지만 3초 이상 추출 횟수가 3회 이상일 경우..*/
                    if( gu8_ster_ice_extract_timer >= 30 )
                    {
                        gu8_ster_ice_extract_count++;

                        if( gu8_ster_ice_extract_count >= 3 )
                        {
                            gu8_ster_ice_extract_count = 0;
                            bit_hot_ster_ice_full = CLEAR;
                        }
                        else{}
                    }
                    else{}

                    gu8_ster_ice_extract_timer = 0;
                }
            }
            else
            {
                gu8_ster_ice_extract_timer = 0;
                gu8_ster_ice_extract_count = 0;
            }
        }
    }
    else
    {
        bit_hot_ster_ice_full = CLEAR;
        gu8_ster_ice_extract_timer = 0;
        gu8_ster_ice_extract_count = 0;
    }
    #endif
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    /*..hui [23-8-28오전 10:54:17] 새벽 12시 20분 이전으로 설정되면.. 12시 00분 ~ 12시 20분..*/
    if( gu16_periodic_ster_time_total < 20 )
    {
        gu16_20_minute_before_ster = (U16)((U16)23 * 100);

        mu8_b = gu8_wifi_period_ster_minute + 40;

        gu16_20_minute_before_ster = gu16_20_minute_before_ster + mu8_b;
    }
    else
    {
        /*..hui [23-8-28오전 10:55:51] 20분 전..*/
        if( gu8_wifi_period_ster_minute < 20 )
        {
            mu8_b = gu8_wifi_period_ster_minute + 40;

            if( gu8_wifi_period_ster_hour == 0 )
            {
                gu16_20_minute_before_ster = (U16)((U16)23 * 100);
                gu16_20_minute_before_ster = gu16_20_minute_before_ster + mu8_b;
            }
            else
            {
                gu16_20_minute_before_ster = (U16)(((U16)gu8_wifi_period_ster_hour - 1) * 100);
                gu16_20_minute_before_ster = gu16_20_minute_before_ster + mu8_b;
            }
        }
        else
        {
            gu16_20_minute_before_ster = gu16_periodic_ster_time_total - 20;
        }
    }

    if( bit_hot_ster_today == SET )
    {
        if( gu16_periodic_ster_current_time_total == gu16_20_minute_before_ster )
        {
            /*..hui [23-7-7오후 4:27:56] 1시간 전 제빙 정지도 에러없고.. 뚜껑 닫히고.. 온수 켜져있을때만..*/
            /*..hui [23-10-4오후 2:42:31] 정수/냉수 온도도 15도 이하일 경우에만.. 15도 넘으면 어차피 안하기때문에..*/
            if( Bit3_Ice_Tank_Ster_Operation_Disable_State == CLEAR
                && F_Tank_Cover_Input == SET
                /*&& bit_filter_cover == SET && bit_ro_filter_2_reed == SET*/
                && bit_filter_all == SET
                /*..hui [23-10-5오전 9:37:34] 정수는 안보고 냉수만 확인하기로.. 이정환 부장님..*/
                /*&& gu8_Room_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP*/
                && gu8_Cold_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP
                && F_Hot_Enable == CLEAR )
                /*&& gu8_periodic_ster_count >= (PERIODIC__STER_CYCLE - 1) )*/
            {
                bit_extract_stop_before_ster_start = SET;
            }
            else
            {
                bit_extract_stop_before_ster_start = CLEAR;
            }
        }
        else
        {
            /*..hui [23-8-28오전 11:28:44] 20분 막는중 온수 켜면..?? 우선 해제..*/
            if( F_Hot_Enable == SET )
            {
                bit_extract_stop_before_ster_start = CLEAR;
            }
            else{}

            /*..hui [23-9-7오후 4:04:28] 가열하는 도중 세척 불가 조건 발생했을때.. 가열 즉시 중단..*/
            /*..hui [23-9-7오후 4:04:52] 필터커버 열림 -> 닫힘 이어도 한번 열리고나면 그냥 취소상태 유지..*/
            /*..hui [23-9-7오후 4:05:05] 20분후에 어떤 상태가 될지 알수없기 떄문에.....*/
            /*..hui [23-10-4오후 2:43:52] 냉수/정수 온도 15도 초과이면 온수 OFF시 예열도 중단....*/
            if( Bit3_Ice_Tank_Ster_Operation_Disable_State == SET
                || F_Tank_Cover_Input == CLEAR
                /*|| bit_filter_cover == CLEAR || bit_ro_filter_2_reed == CLEAR )*/
                || bit_filter_all == CLEAR
                /*|| gu8_Room_Temperature_One_Degree > STER_NO_OPERATION_COLD_TEMP*/
                || gu8_Cold_Temperature_One_Degree > STER_NO_OPERATION_COLD_TEMP )
            {
                bit_extract_stop_before_ster_start = CLEAR;
            }
            else{}
        }
    }
    else
    {
        /*..hui [23-9-7오후 3:56:29] 세척 안하는날은 초기화..*/
        bit_extract_stop_before_ster_start = CLEAR;
    }
    #endif

#if 0
0000 살균시간
2340 20분전

0019 살균시간
2359 20분전

0100 살균시간
0040 20분전

0010 살균시간
2350 20분전


1830 살균시간
1810 20분전


1305 살균시간
1245 20분전

20분전 시간이 현재 시간보다 크면???????


현재시간이 살균 시간 20분보다 작고????
현재시간이 살균 시간보다 크면?????


########
현재시간이 살균 시간 20분보다 크고
현재시간이 살균 시간 보다 작으면
동작진행
########
#endif




///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
    if( gu16_periodic_ster_current_time_total == gu16_periodic_ster_time_total )
    {
        if( bit_ster_count_check == CLEAR )
        {
            bit_ster_count_check = SET;

            gu8_periodic_ster_count++;

            if( gu8_periodic_ster_count >= PERIODIC__STER_CYCLE )
            {
                gu8_periodic_ster_count = PERIODIC__STER_CYCLE;
            }
            else{}
        }
        else{}

        /*..hui [23-7-7오후 4:27:56] 에러없고.. 뚜껑 닫히고.. 온수 켜져있을때만..*/
        /*..hui [23-10-4오후 2:39:55] 정수 / 냉수 온도 둘 다 15도 이하일때만 세척 진행..*/
        if( Bit3_Ice_Tank_Ster_Operation_Disable_State == CLEAR
            && F_Tank_Cover_Input == SET
            && bit_filter_all == SET
            /*&& F_Hot_Enable == SET*/
            /*&& gu8_Cold_Temperature_One_Degree < STER_NO_OPERATION_COLD_TEMP*/
            /*..hui [23-10-5오전 9:37:34] 정수는 안보고 냉수만 확인하기로.. 이정환 부장님..*/
            /*&& gu8_Room_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP*/
            && gu8_Cold_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP
            && gu8_periodic_ster_count >= PERIODIC__STER_CYCLE )
        {
            bit_periodic_ster_ready = SET;
        }
        else{}
    }
    else
    {
        bit_ster_count_check = CLEAR;
    }


    if( bit_periodic_ster_ready == SET )
    {
        /*..hui [24-7-29오후 2:51:38] 구연산 세정 중 시작 안함..*/
        if( Bit3_Ice_Tank_Ster_Operation_Disable_State == CLEAR
            && F_Tank_Cover_Input == SET
            && bit_filter_all == SET
            /*&& gu8_Hot_Tank_Temperature_One_Degree >= HOT_SPRAY_STATE_START_HOT_TEMP*/
            /*&& gu8_Cold_Temperature_One_Degree < STER_NO_OPERATION_COLD_TEMP*/
            /*..hui [23-10-5오전 9:37:34] 정수는 안보고 냉수만 확인하기로.. 이정환 부장님..*/
            /*&& gu8_Room_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP*/
            && gu8_Cold_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP
            && gu8_Room_Water_Level == ROOM_LEVEL_FULL
            && bit_self_test_start == CLEAR
            && bit_acid_clean_start == CLEAR )
        {
            /*hot_ster_temp_decision();*/
            start_ice_tank_ster();

            /*..hui [23-7-13오전 9:42:19] 실제 살균 시작하므로 싸이클 횟수 초기화..*/
            /*..hui [23-7-13오전 9:42:52] 시간됐는데 살균 못하는 조건이면.. 다음날.. 또 다음날.. 로 하루씩 밀림..*/
            if( gu8_periodic_ster_count >= PERIODIC__STER_CYCLE )
            {
                gu8_periodic_ster_count = 0;
            }
            else{}
        }
        else
        {
            gu16_ster_ready_max_timer++;

            /*..hui [23-7-7오후 4:26:42] 1시간동안 만수위, 온수 온도 못 맞추면 걍 끝..*/
            /*if( gu16_ster_ready_max_timer >= 36000 )*/
            /*..hui [23-8-28오전 11:31:55] 2분으로 변경.. 이정환 부장님..*/
            /*if( gu16_ster_ready_max_timer >= 1200 )*/
            /*..hui [23-8-29오후 2:38:34] 5분으로 변경..*/
            if( gu16_ster_ready_max_timer >= 3000 )
            {
                gu16_ster_ready_max_timer = 0;
                stop_ice_tank_ster();
            }
            else{}
        }
    }
    else
    {
        gu16_ster_ready_max_timer = 0;
    }


}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 prepare_ster(void)
{
    U8 mu8_return = 0;

    switch( gu8_prepare_ster_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:39:52] 대기..*/
            gu16_prepare_ster_timer++;

            if( gu16_prepare_ster_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step++;
            }
            else{}

            break;

        case 1:

            gu8_cody_take_off_ice_start = SET;
            gu16_prepare_ster_timer = 0;
            gu16_prepare_ster_max_timer = 0;
            gu8_prepare_ster_step++;

            break;

        case 2:

            /*..hui [23-9-18오후 5:25:23] 냉수 믹싱 모터 삭제..*/
            #if 0
            if( gu8_hot_flow_status != HOT_FLOW_MAX_CLOSE )
            {
                run_init_flow();
            }
            else{}
            #endif

            gu16_prepare_ster_timer = 0;
            gu16_prepare_ster_max_timer = 0;
            gu8_prepare_ster_step++;

            break;

        case 3:

            /*..hui [23-9-18오후 5:25:23] 냉수 믹싱 모터 삭제..*/
            #if 0
            if( gu8_hot_flow_status == HOT_FLOW_MAX_CLOSE )
            {
                gu16_prepare_ster_timer = 0;
                gu8_prepare_ster_step++;
            }
            else{}
            #endif

            gu16_prepare_ster_timer = 0;
            gu16_prepare_ster_max_timer = 0;
            gu8_prepare_ster_step++;

            break;

        case 4:

            if( gu8IceStep == STATE_0_STANDBY )
            {
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step++;
            }
            else
            {
                // 나중에 타이머 최대시간 추가
                /*..hui [23-5-22오전 11:15:23] 최대 제한시간은 핫가스 최대 시간 + 2분정도..*/
                gu16_prepare_ster_timer++;

                if( gu16_prepare_ster_timer >= HOT_GAS_TIME_9_UNDER_765S + 1200 )
                {
                    gu16_prepare_ster_timer = 0;
                    gu16_prepare_ster_max_timer = 0;
                    gu8_prepare_ster_step++;
                }
                else{}
            }

            break;

        case 5:

            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step++;
            }
            else
            {
                /*..hui [23-5-22오전 11:38:20] 드레인 대기 최대 시간은 우선 5분으로..*/
                gu16_prepare_ster_timer++;

                if( gu16_prepare_ster_timer >= 3000 )
                {
                    gu16_prepare_ster_timer = 0;
                    gu16_prepare_ster_max_timer = 0;
                    gu8_prepare_ster_step++;
                }
                else{}
            }

            break;

        case 6:

            /*..hui [23-11-8오후 3:38:12] 온수세척 진입 온수온도 조건 추가..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= 80 )*/
            /*..hui [23-11-17오후 4:42:45] 이정환 부장님 요청....*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= 85 )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= 93 )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_SPRAY_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_hot_spray_start_hot_temp )
            {
                gu16_prepare_ster_timer++;

                if( gu16_prepare_ster_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_prepare_ster_timer = 0;
                    gu16_prepare_ster_max_timer = 0;
                    gu8_prepare_ster_step++;
                }
                else{}
            }
            else
            {
                gu16_prepare_ster_max_timer++;

                /*..hui [23-11-8오후 3:45:01] 온수 가열 최대 시간은 30분..*/
                if( gu16_prepare_ster_max_timer >= 18000 )
                {
                    gu16_prepare_ster_timer = 0;
                    gu16_prepare_ster_max_timer = 0;
                    gu8_prepare_ster_step++;
                }
                else{}
            }

            break;

        case 7:

            gu16_prepare_ster_timer++;

            /*..hui [23-10-12오후 5:27:16] 10초 동안 냉수 드레인 밸브 OPEN..*/
            /*..hui [23-10-12오후 5:28:10] 에어밴트 밸브도 켜야함..*/
            /*..hui [23-10-17오전 9:58:01] 15초로 변경..*/
            /*if( gu16_prepare_ster_timer >= 150 )*/
            /*..hui [24-1-29오후 12:02:37] 15초 드레인 삭제..*/
            if( gu16_prepare_ster_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step++;
            }
            else{}

            break;


        case 8:

            if( bit_flushing_water_start == CLEAR )
            {
                gu16_prepare_ster_timer = 0;
                gu16_prepare_ster_max_timer = 0;
                gu8_prepare_ster_step++;
            }
            else
            {
                /*..hui [23-8-24오전 9:21:30] 필터 플러싱 최대 대기시간 3분..*/
                gu16_prepare_ster_timer++;

                if( gu16_prepare_ster_timer >= 1800 )
                {
                    gu16_prepare_ster_timer = 0;
                    gu16_prepare_ster_max_timer = 0;
                    gu8_prepare_ster_step++;
                }
                else{}
            }

            break;

        case 9:

            gu16_prepare_ster_timer = 0;
            gu16_prepare_ster_max_timer = 0;
            gu8_prepare_ster_step = 0;

            /*..hui [23-5-22오전 11:39:04] 살균 준비작업 종료..*/
            mu8_return = SET;

            break;

        default:

            gu16_prepare_ster_timer = 0;
            gu16_prepare_ster_max_timer = 0;
            gu8_prepare_ster_step = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 hot_circulation(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_ble_ap_mode = 0;

    switch( gu8_hot_circulation_step )
    {
        case 0:

            gu16_hot_circulation_timer++;

            if( gu16_hot_circulation_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_circulation_timer = 0;
                gu8_hot_circulation_step++;
            }
            else{}

            break;

        case 1:

            /*..hui [23-2-28오후 6:54:26] 래치 피드밸브 2 ON..*/
            gu16_hot_circulation_timer++;

            if( gu16_hot_circulation_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_circulation_timer = 0;
                gu8_hot_circulation_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-8-11오후 1:59:11] 오버히팅 NOS 밸브 5-3 OFF 상태 유지..*/
            /*..hui [23-8-11오후 1:59:23] 온수 입수 피드밸브 6-2 ON..*/
            gu16_hot_circulation_timer++;

            if( gu16_hot_circulation_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_circulation_timer = 0;
                gu16_hot_circulation_max_timer = 0;

                /*..hui [23-8-11오후 2:13:55] 기준온도 이하이면 펌프 가동하지 않고 패스..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= HOT_SPRAY_STATE_START_HOT_TEMP + 1 )*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_ster_operation_temp + 1 )*/
                /*..hui [23-10-12오후 5:23:28] 45도 조건, 75도 조건 둘 다 75도로..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= HOT_SPRAY_STATE_START_HOT_TEMP + 1 )*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= HOT_SPRAY_STATE_START_HOT_TEMP )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_spray_start_hot_temp )
                {
                    gu8_hot_circulation_step = 4;
                }
                else
                {
                    gu8_hot_circulation_step++;
                }
            }
            else{}

            break;

        case 3:

            /*..hui [23-8-11오후 2:02:06] 트레이 펌프 가동.. 온수 온도 맞출때까지..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= HOT_SPRAY_STATE_START_HOT_TEMP )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_ster_operation_temp )*/
            /*..hui [23-10-12오후 5:24:09] 45도 조건도 75도로.. 대신 hot spray는 짧게..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= HOT_SPRAY_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_spray_start_hot_temp )
            {
                gu16_hot_circulation_timer++;

                if( gu16_hot_circulation_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_hot_circulation_timer = 0;
                    gu16_hot_circulation_max_timer = 0;
                    gu8_hot_circulation_step++;
                }
                else{}
            }
            else
            {
                gu16_hot_circulation_max_timer++;

                /*..hui [23-8-11오후 2:06:34] 우선 최대 3분으로..*/
                /*..hui [23-8-11오후 5:31:02] 펌프 유량 1분당 대략 260cc == 2분이면 520cc == 온수 1리터중 절반..*/
                /*..hui [23-8-24오후 3:04:50] 3분으로 변경.. 이정환부장님..*/
                /*..hui [23-11-3오전 10:31:39] 최초 온수 순환시에는 5분으로.. 3분이내에 온수 안떨어짐..*/
                /*..hui [23-11-3오전 10:32:09] 나머지는 3분 유지..*/
                /*if( gu16_hot_circulation_max_timer >= HOT_CIRCULATION_MAX_TIME + 1200 )*/
                /*..hui [24-1-31오전 10:10:40] 온도 높이기위해 순환 최소화.. 10초..*/
                if( gu16_hot_circulation_max_timer >= HOT_CIRCULATION_MAX_TIME )
                {
                    gu16_hot_circulation_timer = 0;
                    gu16_hot_circulation_max_timer = 0;
                    gu8_hot_circulation_step++;
                }
                else{}
            }

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            break;

        case 4:

            /*..hui [23-8-11오후 2:07:49] 펌프 정지.. 온도 맞춤 종료..*/
            gu16_hot_circulation_timer++;

            if( gu16_hot_circulation_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_circulation_timer = 0;
                gu8_hot_circulation_step++;
            }
            else{}

            break;

        case 5:

            /*..hui [23-8-11오후 2:09:27] 고온세척 6-2번은 ON 상태 유지..*/
            /*..hui [23-8-11오후 2:09:47] 오비히팅NOS 5-3도 OFF 유지 상태에서 다음단계 진입..*/
            gu16_hot_circulation_timer = 0;
            gu8_hot_circulation_step = 0;

            /*..hui [23-5-15오후 7:43:06] 1차 고온 분사 종료..*/
            mu8_return = SET;

            break;

        default:

            gu16_hot_circulation_timer = 0;
            gu8_hot_circulation_step = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 hot_spray(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_ble_ap_mode = 0;

    switch( gu8_hot_spray_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:39:52] 대기..*/
            /*..hui [23-8-11오후 4:35:09] 래치 피드밸브 2 / 온수 입수 피드밸브 6-2 ON 상태에서 진입..*/
            /*..hui [23-8-11오후 4:35:19] 오버히팅 NOS는 계속 OFF 상태..*/
            gu16_hot_spray_timer++;

            if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 1:

            /*..hui [23-2-28오후 6:54:26] 래치 피드밸브 2 ON..*/
            gu16_hot_spray_timer++;

            if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-2-28오후 6:55:35] 오버히팅 NOS 밸브 5-3 ON..*/
            /*..hui [23-5-15오후 7:12:33] 트레이 입수 밸브 6-1 OFF..*/
            /*..hui [23-2-28오후 6:55:56] 온수 입수 피드밸브 6-2 ON..*/
            gu16_hot_spray_timer++;

            if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [23-5-15오후 7:15:25] 살균 피드 5-1 ON..*/
            gu16_hot_spray_timer++;

            if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-1번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_hot_spray_timer++;
            }
            else
            {
                gu16_hot_spray_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_hot_spray_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else{}
            }

            /*..hui [23-11-8오후 2:10:48] 얼음양에 따른 제어 변경 삭제. 만빙 사양으로 통일..*/
            /*if( gu16_hot_spray_timer >= 300 )*/
            if( gu16_hot_spray_timer >= 250 )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;


            #if 0
            /*if( gu16_hot_spray_timer <= 220 )*/
            if( gu16_hot_spray_timer <= 200 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 5:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_hot_spray_timer++;

            /*if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_hot_spray_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 6:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else
                {
                    gu16_hot_spray_timer++;

                    if( gu16_hot_spray_timer >= 600 )
                    {
                        gu16_hot_spray_timer = 0;
                        gu16_hot_spray_max_timer = 0;
                        gu8_hot_spray_step = 8;
                    }
                    else{}
                }
            }
            else
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step = 8;
            }

            break;

        case 7:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else
            {
                gu16_hot_spray_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_hot_spray_timer >= 600 )
                {
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else{}
            }

            break;

        case 8:

            /*..hui [23-5-15오후 7:17:17] 살균 피드 5-1 OFF..*/
            /*..hui [23-5-15오후 7:17:02] 살균 피드 5-2 ON..*/
            gu16_hot_spray_timer++;

            if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 9:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-2번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_hot_spray_timer++;
            }
            else
            {
                gu16_hot_spray_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_hot_spray_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else{}
            }

            /*..hui [23-11-8오후 2:10:48] 얼음양에 따른 제어 변경 삭제. 만빙 사양으로 통일..*/
            /*if( gu16_hot_spray_timer >= 250 )*/
            if( gu16_hot_spray_timer >= 200 )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;


            #if 0
            /*if( gu16_hot_spray_timer <= 170 )*/
            if( gu16_hot_spray_timer <= 150 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 10:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_hot_spray_timer++;

            /*if( gu16_hot_spray_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_hot_spray_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else{}

            break;

        case 11:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else
                {
                    gu16_hot_spray_timer++;

                    if( gu16_hot_spray_timer >= 600 )
                    {
                        gu16_hot_spray_timer = 0;
                        gu16_hot_spray_max_timer = 0;
                        gu8_hot_spray_step = 13;
                    }
                    else{}
                }
            }
            else
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step = 13;
            }

            break;

        case 12:

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_hot_spray_timer = 0;
                gu16_hot_spray_max_timer = 0;
                gu8_hot_spray_step++;
            }
            else
            {
                gu16_hot_spray_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_hot_spray_timer >= 600 )
                {
                    gu16_hot_spray_timer = 0;
                    gu16_hot_spray_max_timer = 0;
                    gu8_hot_spray_step++;
                }
                else{}
            }

            break;


        case 13:

            /*..hui [23-5-22오후 3:58:02] 밸브 5-2 OFF..*/
            gu16_hot_spray_timer = 0;
            gu16_hot_spray_max_timer = 0;
            gu8_hot_spray_step = 0;

            /*..hui [23-5-15오후 7:43:06] 1차 고온 분사 종료..*/
            mu8_return = SET;

            break;

        default:

            gu16_hot_spray_timer = 0;
            gu16_hot_spray_max_timer = 0;
            gu8_hot_spray_step = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 overheat_circulation(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_ble_ap_mode = 0;

    #if 0
    switch( gu8_overheat_circul_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:45:48] 5-1 OFF / 5-2 OFF / 5-3 ON / 6-1 OFF / 6-2 ON / PUMP OFF / 2 ON 상태에서 진입..*/
            gu16_overheat_circul_timer++;

            if( gu16_overheat_circul_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_overheat_circul_timer = 0;
                gu8_overheat_circul_step++;
            }
            else{}

            break;

        case 1:

            /*..hui [23-5-15오후 7:46:17] NOS 밸브 5-3 OFF..*/
            gu16_overheat_circul_timer++;

            if( gu16_overheat_circul_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_overheat_circul_timer = 0;
                gu8_overheat_circul_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-5-15오후 7:47:07] 트레이 펌프 가동.. 온수 오버히팅 순환 시작..*/
            gu16_overheat_circul_timer++;

            if( gu16_overheat_circul_timer >= 200 )
            {
                gu16_overheat_circul_timer = 0;
                gu8_overheat_circul_step++;
            }
            else{}


            break;

        case 3:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_overheat_circul_timer++;

            if( gu16_overheat_circul_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_overheat_circul_timer = 0;
                gu8_overheat_circul_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [23-5-22오후 3:17:06] NOS 밸브 ON..*/
            gu16_overheat_circul_timer = 0;
            gu8_overheat_circul_step = 0;

            /*..hui [23-5-15오후 7:48:11] 2차 오버히팅 순환 종료..*/
            mu8_return = SET;

            break;

        default:

            gu16_overheat_circul_timer = 0;
            gu8_overheat_circul_step = 0;

        break;

    }
    #endif

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 lukewarm_spray(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    switch( gu8_lukewarm_spray_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:45:48] 5-1 OFF / 5-2 OFF / 5-3 ON / 6-1 OFF / 6-2 ON / PUMP OFF / 2 ON 상태에서 진입..*/
            /*..hui [23-7-5오후 7:42:27] 트레이 탈빙 방향 상태에서 진입..*/
            gu16_lukewarm_spray_timer++;

            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                /*..hui [23-8-24오후 4:30:40] 기준온도 55도 이하일 경우에는 NOS 5-3 OFF 상태에서 바로 5-2 켜고..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= LUKEWARM_STATE_START_HOT_TEMP )*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_ster_operation_temp )*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= LUKEWARM_STATE_START_HOT_TEMP )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_lukewarm_spray_start_hot_temp )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step = 5;
                }
                else
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
            }
            else{}

            break;

        case 1:

            /*..hui [23-8-24오후 4:17:47] 오버히팅 NOS 5-3 OFF..*/
            gu16_lukewarm_spray_timer++;

            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-8-24오후 4:18:24] 온도 떨어질때까지 펌프 가동..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= LUKEWARM_STATE_START_HOT_TEMP )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_ster_operation_temp )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= LUKEWARM_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_lukewarm_spray_start_hot_temp )
            {
                gu16_lukewarm_spray_timer++;

                if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }
            else
            {
                gu16_lukewarm_spray_max_timer++;

                /*..hui [23-8-11오후 2:06:34] 우선 최대 3분으로..*/
                /*..hui [23-8-11오후 5:31:02] 펌프 유량 1분당 대략 260cc == 2분이면 520cc == 온수 1리터중 절반..*/
                /*..hui [23-8-24오후 3:04:50] 3분으로 변경.. 이정환부장님..*/
                if( gu16_lukewarm_spray_max_timer >= HOT_CIRCULATION_MAX_TIME )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            break;

        case 3:

            /*..hui [23-8-24오후 4:25:38] 펌프 정지. .오버히팅 순환 종료..*/
            gu16_lukewarm_spray_timer++;

            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            break;

        case 4:

            gu16_lukewarm_spray_timer++;

            /*..hui [23-8-24오후 4:26:46] 오버히팅 NOS 5-3 ON..*/
            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            break;

        case 5:

            /*..hui [23-5-15오후 7:50:38] 살균 피드 5-1 ON..*/
            gu16_lukewarm_spray_timer++;

            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            break;

        case 6:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-1번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_lukewarm_spray_timer++;
            }
            else
            {
                gu16_lukewarm_spray_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_lukewarm_spray_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }

            /*if( gu16_lukewarm_spray_timer >= 250 )*/
            if( gu16_lukewarm_spray_timer >= 200 )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            #if 0
            /*if( gu16_lukewarm_spray_timer <= 170 )*/
            if( gu16_lukewarm_spray_timer <= 150 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 7:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_lukewarm_spray_timer++;

            /*if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}


            break;

        case 8:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else
                {
                    gu16_lukewarm_spray_timer++;

                    if( gu16_lukewarm_spray_timer >= 600 )
                    {
                        gu16_lukewarm_spray_timer = 0;
                        gu16_lukewarm_spray_max_timer = 0;
                        gu8_lukewarm_spray_step = 10;
                    }
                    else{}
                }
            }
            else
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step = 10;
            }


            break;

        case 9:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else
            {
                gu16_lukewarm_spray_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_lukewarm_spray_timer >= 600 )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }

            break;

        case 10:

            /*..hui [23-5-15오후 7:17:17] 살균 피드 5-1 OFF..*/
            /*..hui [23-5-15오후 7:17:02] 살균 피드 5-2 ON..*/
            gu16_lukewarm_spray_timer++;

            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}


            break;

        case 11:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-2번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_lukewarm_spray_timer++;
            }
            else
            {
                gu16_lukewarm_spray_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_lukewarm_spray_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }

            /*if( gu16_lukewarm_spray_timer >= 250 )*/
            if( gu16_lukewarm_spray_timer >= 200 )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            #if 0
            /*if( gu16_lukewarm_spray_timer <= 170 )*/
            if( gu16_lukewarm_spray_timer <= 150 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 12:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_lukewarm_spray_timer++;

            /*if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_lukewarm_spray_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else{}


            break;

        case 13:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else
                {
                    gu16_lukewarm_spray_timer++;

                    if( gu16_lukewarm_spray_timer >= 600 )
                    {
                        gu16_lukewarm_spray_timer = 0;
                        gu16_lukewarm_spray_max_timer = 0;
                        gu8_lukewarm_spray_step = 15;
                    }
                    else{}
                }
            }
            else
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step = 15;
            }

            break;

        case 14:

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_lukewarm_spray_timer = 0;
                gu16_lukewarm_spray_max_timer = 0;
                gu8_lukewarm_spray_step++;
            }
            else
            {
                gu16_lukewarm_spray_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_lukewarm_spray_timer >= 600 )
                {
                    gu16_lukewarm_spray_timer = 0;
                    gu16_lukewarm_spray_max_timer = 0;
                    gu8_lukewarm_spray_step++;
                }
                else{}
            }

            break;

        case 15:

            /*..hui [23-5-22오후 3:56:19] 밸브 5-2 OFF..*/
            gu16_lukewarm_spray_timer = 0;
            gu16_lukewarm_spray_max_timer = 0;
            gu8_lukewarm_spray_step = 0;

            /*..hui [23-5-15오후 7:52:03] 3차 미온수 세척 종료..*/
            mu8_return = SET;

            break;

        default:

            gu16_lukewarm_spray_timer = 0;
            gu16_lukewarm_spray_max_timer = 0;
            gu8_lukewarm_spray_step = 0;


        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 final_clean(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    switch( gu8_final_clean_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:45:48] 5-1 OFF / 5-2 OFF / 5-3 ON / 6-1 OFF / 6-2 ON / PUMP OFF / 2 ON 상태에서 진입..*/
            /*..hui [23-7-5오후 7:46:26] 탈빙 위치에서 진입..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                /*gu8_hot_ster_operation_temp = FINAL_CLEAN_STATE_START_HOT_TEMP;*/

                /*..hui [23-8-24오후 4:30:40] 기준온도 45도 이하일 경우에는 NOS 5-3 OFF 상태에서 바로 5-2 켜고..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= FINAL_CLEAN_STATE_START_HOT_TEMP )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_final_clean_start_hot_temp )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step = 5;
                }
                else
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
            }
            else{}

            break;


        case 1:

            /*..hui [23-8-24오후 4:17:47] 오버히팅 NOS 5-3 OFF..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-8-24오후 4:18:24] 온도 떨어질때까지 펌프 가동..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= FINAL_CLEAN_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_final_clean_start_hot_temp )
            {
                gu16_final_clean_timer++;

                if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }
            else
            {
                gu16_final_clean_max_timer++;

                /*..hui [23-8-11오후 2:06:34] 우선 최대 3분으로..*/
                /*..hui [23-8-11오후 5:31:02] 펌프 유량 1분당 대략 260cc == 2분이면 520cc == 온수 1리터중 절반..*/
                /*..hui [23-8-24오후 3:04:50] 3분으로 변경.. 이정환부장님..*/
                if( gu16_final_clean_max_timer >= HOT_CIRCULATION_MAX_TIME )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            break;

        case 3:

            /*..hui [23-8-24오후 4:25:38] 펌프 정지. .오버히팅 순환 종료..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [23-8-24오후 4:26:46] 오버히팅 NOS 5-3 ON..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;


        case 5:

            /*..hui [23-5-15오후 7:50:38] 살균 피드 5-1 ON..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}


            break;

        case 6:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-1번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_final_clean_timer++;
            }
            else
            {
                gu16_final_clean_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_final_clean_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }

            /*..hui [23-11-24오후 2:35:53] 탱크 남은 물량 확보하기 위해 10초 줄임..*/
            /*if( gu16_final_clean_timer >= 500 )*/
            /*if( gu16_final_clean_timer >= 250 )*/
            if( gu16_final_clean_timer >= 200 )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            #if 0
            /*if( gu16_final_clean_timer <= 300 )*/
            /*if( gu16_final_clean_timer <= 170 )*/
            if( gu16_final_clean_timer <= 150 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 7:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_final_clean_timer++;

            /*if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_final_clean_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
                /*down_tray_motor();*/
            }
            else{}

            break;

        case 8:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else
                {
                    gu16_final_clean_timer++;

                    if( gu16_final_clean_timer >= 600 )
                    {
                        gu16_final_clean_timer = 0;
                        gu16_final_clean_max_timer = 0;
                        gu8_final_clean_step = 10;
                    }
                    else{}
                }
            }
            else
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step = 10;
            }

            break;

        case 9:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else
            {
                gu16_final_clean_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_final_clean_timer >= 600 )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }

            break;

        case 10:

            /*..hui [23-5-15오후 7:17:17] 살균 피드 5-1 OFF..*/
            /*..hui [23-5-15오후 7:17:02] 살균 피드 5-2 ON..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 11:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-2번 분사 시작..*/
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_final_clean_timer++;
            }
            else
            {
                gu16_final_clean_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu16_final_clean_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }

            /*..hui [23-11-24오후 2:35:53] 탱크 남은 물량 확보하기 위해 10초 줄임..*/
            /*if( gu16_final_clean_timer >= 500 )*/
            /*if( gu16_final_clean_timer >= 250 )*/
            if( gu16_final_clean_timer >= 200 )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            #if 0
            /*if( gu16_final_clean_timer <= 300 )*/
            /*if( gu16_final_clean_timer <= 170 )*/
            if( gu16_final_clean_timer <= 150 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif

            break;

        case 12:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_final_clean_timer++;

            /*if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [23-7-26오후 4:19:43] 압빼주는 동작.. 제대로 되는지 확인해봐야 함..*/
            /*..hui [23-7-26오후 4:20:02] 마지막에 오비히팅NOS 열면 오버히팅쪽으로 물 쏘는 현상..*/
            /*if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_final_clean_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 13:

            /*..hui [23-5-15오후 7:55:57] 밸브 5-2 OFF..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 14:

            /*..hui [23-5-15오후 7:55:37] 밸브 5-3 OFF, 6-2 OFF..*/
            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else{}

            break;

        case 15:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else
                {
                    gu16_final_clean_timer++;

                    if( gu16_final_clean_timer >= 600 )
                    {
                        gu16_final_clean_timer = 0;
                        gu16_final_clean_max_timer = 0;
                        gu8_final_clean_step = 17;
                    }
                    else{}
                }
            }
            else
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step = 17;
            }

            break;

        case 16:

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;
            }
            else
            {
                gu16_final_clean_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_final_clean_timer >= 600 )
                {
                    gu16_final_clean_timer = 0;
                    gu16_final_clean_max_timer = 0;
                    gu8_final_clean_step++;
                }
                else{}
            }

            break;

        case 17:

            gu16_final_clean_timer++;

            if( gu16_final_clean_timer >= 10 )
            {
                gu16_final_clean_timer = 0;
                gu16_final_clean_max_timer = 0;
                gu8_final_clean_step++;

                /*..hui [23-9-6오후 4:20:55] 얼음 녹았을테니 만빙감지..*/
                /*..hui [24-1-31오후 4:50:42] 만빙 감지는 끝나고나서..*/
                /*F_IR = SET;*/
            }
            else{}

            break;

        case 18:

            gu16_final_clean_timer = 0;
            gu16_final_clean_max_timer = 0;
            gu8_final_clean_step = 0;

            /*..hui [23-5-15오후 7:54:29] 최종 세척 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_final_clean_timer = 0;
            gu8_final_clean_step = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_ice_ster(void)
{
    gu16_prepare_ster_timer = 0;
    gu16_prepare_ster_max_timer = 0;
    gu8_prepare_ster_step = 0;

    gu16_hot_spray_timer = 0;
    gu16_hot_spray_max_timer = 0;
    gu8_hot_spray_step = 0;

    gu16_overheat_circul_timer = 0;
    gu8_overheat_circul_step = 0;

    gu16_lukewarm_spray_timer = 0;
    gu16_lukewarm_spray_max_timer = 0;
    gu8_lukewarm_spray_step = 0;

    gu16_final_clean_timer = 0;
    gu16_final_clean_max_timer = 0;
    gu8_final_clean_step = 0;

    gu8_ice_tray_prepare_step = 0;
    gu16_ice_tray_prepare_timer = 0;
    gu32_ice_tray_prepare_max_timer = 0;

    gu8_ice_tray_clean_step = 0;
    gu16_ice_tray_clean_timer = 0;
    gu32_ice_tray_clean_max_timer = 0;

    gu16_melt_ice_timer = 0;
    gu32_melt_ice_max_timer = 0;
    gu8_melt_ice_step = 0;

    gu16_melt_ice_prepare_timer = 0;
    gu32_melt_ice_prepare_max_timer = 0;
    gu8_melt_ice_prepare_step = 0;

    gu16_wait_finish_timer = 0;
    gu16_wait_finish_max_timer = 0;
    gu8_wait_finish_step = 0;

    /*..hui [24-1-29오후 3:35:24] 디버그모드 진입중이면 종료..*/
    bit_ice_ster_test_debug_start = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_disable_timer(void)
{
    gu16_manual_minute++;

    if( gu16_manual_minute >= 36000 )
    {
        gu16_manual_minute = 0;
        gu16_manual_hour++;
    }
    else{}

    if( gu16_manual_hour >= 24 )
    {
        gu16_manual_hour = 0;
        gu8_manual_operation_count = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_ster_temp_decision(void)
{
    #if 0
    if( F_IceFull == SET )
    {
        /*..hui [23-9-6오후 4:50:17] 시작하는 시점에 만빙이면 무조건 75도로..*/
        gu8_hot_ster_temp_mode = HOT_STER_TEMP_HIGH_MODE;
    }
    else
    {
        if( bit_hot_ster_ice_full == SET )
        {
            /*..hui [23-8-28오전 11:37:54] 얼음 만빙상태 & 추출 없을 경우 75도로 세척..*/
            /*..hui [23-9-6오후 4:14:07] 얼음이 꺼져있어도 만빙상태에 따라 온도 정함.. 이정환 부장님..*/
            gu8_hot_ster_temp_mode = HOT_STER_TEMP_HIGH_MODE;
        }
        else
        {
            /*..hui [23-8-28오전 11:38:22] 얼음 만빙상태 아니거나 얼음 추출 7초 이상 있었을 경우 45도로 세척..*/
            gu8_hot_ster_temp_mode = HOT_STER_TEMP_LOW_MODE;
        }
    }
    #endif
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
U8 prepare_melt_ice(void)
{
    U8 mu8_return = 0;

    switch( gu8_melt_ice_prepare_step )
    {
        case 0:

            /*..hui [23-10-17오전 11:18:31] 피드밸브 오픈..*/
            /*..hui [23-10-17오전 11:19:19] 여기부터 온수히터 제어.. 66도 OFF, 60도 ON..*/
            gu16_melt_ice_prepare_timer++;

            if( gu16_melt_ice_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else{}

            break;

        case 1:

            gu16_melt_ice_prepare_timer++;

            if( gu16_melt_ice_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-10-17오전 11:20:02] 재정수 만수위까지 대기.. 최대 대기 시간은 1시간 30분..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else
            {
                gu32_melt_ice_prepare_max_timer++;

                if( gu32_melt_ice_prepare_max_timer >= ICE_MELT_FEED_MAX_TIME )
                {
                    /*..hui [23-10-17오전 11:23:54] 우선은 그냥 끝내는걸로..*/
                    finish_ice_ster();
                }
                else{}
            }

            break;

        case 3:

            /*..hui [24-1-25오후 5:53:33] 아이스트레이 세척 진입 온도 조건 추가..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= MELT_ICE_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_mlet_ice_start_hot_temp )
            {
                gu16_melt_ice_prepare_timer++;

                if( gu16_melt_ice_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_melt_ice_prepare_timer = 0;
                    gu32_melt_ice_prepare_max_timer = 0;
                    gu8_melt_ice_prepare_step++;
                }
                else{}
            }
            else
            {
                gu32_melt_ice_prepare_max_timer++;

                /*..hui [23-11-8오후 3:45:01] 온수 가열 최대 시간은 30분..*/
                if( gu32_melt_ice_prepare_max_timer >= 18000 )
                {
                    gu16_melt_ice_prepare_timer = 0;
                    gu32_melt_ice_prepare_max_timer = 0;
                    gu8_melt_ice_prepare_step++;
                }
                else{}
            }

            break;

        case 4:

            /*if( gu8_Cold_Temperature_One_Degree <= 20 )*/
            if( gu8_Cold_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else
            {
                gu32_melt_ice_prepare_max_timer++;

                /*..hui [23-10-23오후 1:57:10] 냉각 대기시간 최대 1시간..*/
                if( gu32_melt_ice_prepare_max_timer >= 36000 )
                {
                    gu16_melt_ice_prepare_timer = 0;
                    gu32_melt_ice_prepare_max_timer = 0;
                    gu8_melt_ice_prepare_step++;
                }
                else{}
            }

            break;

        case 5:

            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else
            {
                /*..hui [23-5-22오전 11:38:20] 드레인 대기 최대 시간은 우선 5분으로..*/
                gu16_melt_ice_prepare_timer++;

                if( gu16_melt_ice_prepare_timer >= 3000 )
                {
                    gu16_melt_ice_prepare_timer = 0;
                    gu32_melt_ice_prepare_max_timer = 0;
                    gu8_melt_ice_prepare_step++;
                }
                else{}
            }

            break;

        case 6:

            gu16_melt_ice_prepare_timer++;

            if( gu16_melt_ice_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_prepare_timer = 0;
                gu32_melt_ice_prepare_max_timer = 0;
                gu8_melt_ice_prepare_step++;
            }
            else{}

            break;

        case 7:

            gu16_melt_ice_prepare_timer = 0;
            gu32_melt_ice_prepare_max_timer = 0;
            gu8_melt_ice_prepare_step = 0;

            /*..hui [23-10-17오전 11:22:52] 얼음 녹임 준비작업 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_melt_ice_prepare_timer = 0;
            gu32_melt_ice_prepare_max_timer = 0;
            gu8_melt_ice_prepare_step = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 melt_ice(void)
{
    U8 mu8_return = 0;

    switch( gu8_melt_ice_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:39:52] 대기..*/
            /*..hui [23-10-17오후 2:13:09] 에어밴트 밸브는 켜진 상태로 진입..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 1:

            /*..hui [23-10-17오전 11:36:33] 밸브류 전부 OFF 상태에서 진입..*/
            /*..hui [23-10-17오전 11:40:39] 온수 입수 피드밸브 6-2 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                /*gu8_hot_ster_operation_temp = MELT_ICE_STATE_START_HOT_TEMP;*/

                /*..hui [23-11-8오후 2:10:48] 얼음양에 따른 제어 변경 삭제. 만빙 사양으로 통일..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= MELT_ICE_STATE_START_HOT_TEMP )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_mlet_ice_start_hot_temp )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;

                    gu8_melt_ice_step = 5;
                }
                else
                {
                    /*..hui [23-10-23오전 11:16:59] 아니면 45도까지 오버히팅 순환후 시작..*/
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;

                    gu8_melt_ice_step++;
                }
            }
            else{}

            break;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

        case 2:

            /*..hui [23-10-17오후 2:09:06] 대기..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [23-10-17오전 11:41:17] 55도 이하 될때까지 펌프 가동..*/
            /*..hui [23-10-23오전 11:17:14] 얼음없는 조건 45도까지 오버히팅 순환..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= MELT_NO_ICE_START_HOT_TEMP )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_ster_operation_temp )*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= MELT_ICE_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_mlet_ice_start_hot_temp )
            {
                gu16_melt_ice_timer++;

                if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }
            else
            {
                gu32_melt_ice_max_timer++;

                /*..hui [23-10-17오전 11:42:56] 해빙작업시에는 최대 2분..*/
                /*if( gu32_melt_ice_max_timer >= MELT_ICE_HOT_CIRCULATION_MAX_TIME )*/
                /*..hui [24-1-31오전 10:13:51] 해빙때도 최대 10초..*/
                /*if( gu32_melt_ice_max_timer >= HOT_CIRCULATION_MAX_TIME )*/
                /*..hui [24-2-1오후 2:23:19] 해빙은 20초 유지..*/
                if( gu32_melt_ice_max_timer >= MELT_ICE_HOT_CIRCULATION_MAX_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            break;

        case 4:

            /*..hui [23-8-24오후 4:25:38] 펌프 정지. .오버히팅 순환 종료..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

        case 5:

            /*..hui [23-8-24오후 4:26:46] 오버히팅 NOS 5-3 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;



        case 6:

            /*..hui [23-5-15오후 7:50:38] 살균 피드 5-1 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 7:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-1번 분사 시작..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_melt_ice_timer++;
            }
            else
            {
                gu32_melt_ice_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_melt_ice_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }

            if( gu16_melt_ice_timer >= ICE_MELT_TOTAL_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            if( gu16_melt_ice_timer <= ICE_MELT_PUMP_90_PERCENT_TIME )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }


            break;

        case 8:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_melt_ice_timer++;

            /*if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_melt_ice_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 9:

            /*..hui [23-10-17오전 11:47:02] 살균피드 5-1 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 10:

            /*..hui [23-10-17오전 11:47:18] 살균피드 5-2 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 11:

            /*..hui [23-2-28오후 6:56:22] 트레이 펌프 가동.. 5-2번 분사 시작..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_melt_ice_timer++;
            }
            else
            {
                gu32_melt_ice_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_melt_ice_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }


            if( gu16_melt_ice_timer >= ICE_MELT_TOTAL_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            if( gu16_melt_ice_timer <= ICE_MELT_PUMP_90_PERCENT_TIME )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }

            break;

        case 12:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_melt_ice_timer++;

            /*if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_melt_ice_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 13:

            /*..hui [23-10-17오전 11:47:02] 살균피드 5-2 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 14:

            /*..hui [23-10-17오전 11:47:18] 살균피드 5-1 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 15:

            /*..hui [23-10-17오전 11:49:17] 트레이 펌프 가동.. 5-1번 2회째 분사 시작..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_melt_ice_timer++;
            }
            else
            {
                gu32_melt_ice_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_melt_ice_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }


            if( gu16_melt_ice_timer >= ICE_MELT_TOTAL_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            if( gu16_melt_ice_timer <= ICE_MELT_PUMP_90_PERCENT_TIME )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }



            break;






        case 16:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_melt_ice_timer++;

            /*if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_melt_ice_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 17:

            /*..hui [23-10-17오전 11:47:02] 살균피드 5-1 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 18:

            /*..hui [23-10-17오전 11:47:18] 살균피드 5-2 ON..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 19:

            /*..hui [23-10-17오전 11:49:17] 트레이 펌프 가동.. 5-2번 2회째 분사 시작..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_melt_ice_timer++;
            }
            else
            {
                gu32_melt_ice_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_melt_ice_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_melt_ice_timer = 0;
                    gu32_melt_ice_max_timer = 0;
                    gu8_melt_ice_step++;
                }
                else{}
            }


            if( gu16_melt_ice_timer >= ICE_MELT_TOTAL_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            if( gu16_melt_ice_timer <= ICE_MELT_PUMP_90_PERCENT_TIME )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }



            break;


        case 20:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_melt_ice_timer++;

            /*if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_melt_ice_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 21:

            /*..hui [23-10-17오전 11:47:02] 살균피드 5-2 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 22:

            /*..hui [23-10-17오후 1:45:29] 오버히팅 NOS 5-3 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 23:

            /*..hui [23-10-17오후 1:45:44] 온수 입수 피드밸브 6-2 OFF..*/
            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;

                /////if( gu8_melt_ice_count == 0 || gu8_melt_ice_count == 1 )
                /*if( gu8_melt_ice_count == 0 || gu8_melt_ice_count == 1 || gu8_melt_ice_count == 2 )*/
                /*if( gu8_melt_ice_count == 0 || gu8_melt_ice_count == 1 )*/
                if( gu8_melt_ice_count == 0 )
                {
                    gu8_melt_ice_step++;
                }
                else
                {
                    gu8_melt_ice_step = 25;
                }
            }
            else{}

            break;

        case 24:

            gu16_melt_ice_timer++;

            if( gu16_melt_ice_timer >= HOT_STER_FEEDER_REVERSE_TEST_TIME )
            {
                gu16_melt_ice_timer = 0;
                gu32_melt_ice_max_timer = 0;
                gu8_melt_ice_step++;
            }
            else{}

            break;

        case 25:

            gu16_melt_ice_timer = 0;
            gu32_melt_ice_max_timer = 0;
            gu8_melt_ice_step = 0;


            /*..hui [23-10-17오후 1:54:12] 해빙 작업 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_melt_ice_timer = 0;
            gu32_melt_ice_max_timer = 0;
            gu8_melt_ice_step = 0;


        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 wait_finish_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_wait_finish_step )
    {
        case 0:

            gu16_wait_finish_timer++;

            if( gu16_wait_finish_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_wait_finish_timer = 0;
                gu16_wait_finish_max_timer = 0;
                gu8_wait_finish_step++;
            }
            else{}

            break;

        case 1:

            gu16_wait_finish_timer++;

            /*..hui [24-2-15오후 5:03:20] 순환이 없어져서 끝날때 온도가 낮음....*/
            /*..hui [24-2-15오후 5:03:33] 재정수를 위해 최소 10분간은 유지 후 종료..*/
            if( gu16_wait_finish_timer >= 6000 )
            {
                gu16_wait_finish_timer = 0;
                gu16_wait_finish_max_timer = 0;
                gu8_wait_finish_step++;
            }
            else{}

            break;

        case 2:

            if( gu8_Cold_Temperature_One_Degree <= HOT_STER_FINISH_COLD_TEMP
                && gu8_Room_Temperature_One_Degree <= HOT_STER_FINISH_ROOM_TEMP )
            {
                gu16_wait_finish_timer = 0;
                gu16_wait_finish_max_timer = 0;
                gu8_wait_finish_step++;
            }
            else
            {
                gu16_wait_finish_max_timer++;

                /*..hui [23-10-23오후 1:41:04] 우선 최대 1시간으로..*/
                if( gu16_wait_finish_max_timer >= HOT_STER_FINISH_MAX_TIME )
                {
                    gu16_wait_finish_timer = 0;
                    gu16_wait_finish_max_timer = 0;
                    gu8_wait_finish_step++;
                }
                else{}
            }

            break;

        case 3:

            gu16_wait_finish_timer++;

            if( gu16_wait_finish_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_wait_finish_timer = 0;
                gu16_wait_finish_max_timer = 0;
                gu8_wait_finish_step++;
            }
            else{}

            break;

        case 4:

            gu16_wait_finish_timer = 0;
            gu16_wait_finish_max_timer = 0;
            gu8_wait_finish_step = 0;

            /*..hui [23-10-23오후 1:36:15] 제품 사용 준비 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_wait_finish_timer = 0;
            gu16_wait_finish_max_timer = 0;
            gu8_wait_finish_step = 0;

        break;

    }

    return mu8_return;
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
U8 prepare_icetray_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_ice_tray_prepare_step )
    {
        case 0:

            /*..hui [23-10-17오전 11:18:31] 피드밸브 오픈..*/
            /*..hui [24-1-24오후 5:29:19] 여기부터 온수히터 제어.. 96도 OFF, 93도 ON..*/
            gu16_ice_tray_prepare_timer++;

            if( gu16_ice_tray_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else{}

            break;

        case 1:

            gu16_ice_tray_prepare_timer++;

            if( gu16_ice_tray_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else
                {
                    gu16_ice_tray_prepare_timer++;

                    if( gu16_ice_tray_prepare_timer >= 600 )
                    {
                        gu16_ice_tray_prepare_timer = 0;
                        gu32_ice_tray_prepare_max_timer = 0;
                        gu8_ice_tray_prepare_step = 4;
                    }
                    else{}
                }
            }
            else
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step = 4;

            }

            break;

        case 3:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else
            {
                gu16_ice_tray_prepare_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_ice_tray_prepare_timer >= 600 )
                {
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else{}
            }

            break;

        case 4:

            /*..hui [23-10-17오전 11:20:02] 재정수 만수위까지 대기.. 최대 대기 시간은 1시간 30분..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else
            {
                gu32_ice_tray_prepare_max_timer++;

                if( gu32_ice_tray_prepare_max_timer >= ICE_MELT_FEED_MAX_TIME )
                {
                    /*..hui [23-10-17오전 11:23:54] 우선은 그냥 끝내는걸로..*/
                    finish_ice_ster();
                }
                else{}
            }

            break;

        case 5:

            /*..hui [24-1-25오후 5:53:33] 아이스트레이 세척 진입 온도 조건 추가..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree >= ICE_TRAY_CLEAN_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_ice_tray_start_hot_temp )
            {
                gu16_ice_tray_prepare_timer++;

                if( gu16_ice_tray_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else{}
            }
            else
            {
                gu32_ice_tray_prepare_max_timer++;

                /*..hui [23-11-8오후 3:45:01] 온수 가열 최대 시간은 30분..*/
                if( gu32_ice_tray_prepare_max_timer >= 18000 )
                {
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else{}
            }

            break;

        case 6:

            /*if( gu8_Cold_Temperature_One_Degree <= 20 )*/
            if( gu8_Cold_Temperature_One_Degree <= STER_NO_OPERATION_COLD_TEMP )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else
            {
                gu32_ice_tray_prepare_max_timer++;

                /*..hui [23-10-23오후 1:57:10] 냉각 대기시간 최대 1시간..*/
                if( gu32_ice_tray_prepare_max_timer >= 36000 )
                {
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else{}
            }

            break;

        case 7:

            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else
            {
                /*..hui [23-5-22오전 11:38:20] 드레인 대기 최대 시간은 우선 5분으로..*/
                gu16_ice_tray_prepare_timer++;

                if( gu16_ice_tray_prepare_timer >= 3000 )
                {
                    gu16_ice_tray_prepare_timer = 0;
                    gu32_ice_tray_prepare_max_timer = 0;
                    gu8_ice_tray_prepare_step++;
                }
                else{}
            }

            break;

        case 8:

            gu16_ice_tray_prepare_timer++;

            if( gu16_ice_tray_prepare_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_prepare_timer = 0;
                gu32_ice_tray_prepare_max_timer = 0;
                gu8_ice_tray_prepare_step++;
            }
            else{}

            break;

        case 9:

            gu16_ice_tray_prepare_timer = 0;
            gu32_ice_tray_prepare_max_timer = 0;
            gu8_ice_tray_prepare_step = 0;

            /*..hui [23-10-17오전 11:22:52] 얼음 녹임 준비작업 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_ice_tray_prepare_timer = 0;
            gu32_ice_tray_prepare_max_timer = 0;
            gu8_ice_tray_prepare_step = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 icetray_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_ice_tray_clean_step )
    {
        case 0:

            /*..hui [23-5-15오후 7:39:52] 대기..*/
            /*..hui [23-10-17오후 2:13:09] 에어밴트 밸브는 켜진 상태로 진입..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 1:

            /*..hui [23-10-17오전 11:36:33] 밸브류 전부 OFF 상태에서 진입..*/
            /*..hui [23-10-17오전 11:40:39] 온수 입수 피드밸브 6-2 ON..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= ICE_TRAY_CLEAN_STATE_START_HOT_TEMP )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_ice_tray_start_hot_temp )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;

                    gu8_ice_tray_clean_step = 5;
                }
                else
                {
                    /*..hui [24-1-25오전 9:38:48] 아니면 93도까지 순환후 시작..*/
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;

                    gu8_ice_tray_clean_step++;
                }
            }
            else{}

            break;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

        case 2:

            /*..hui [23-10-17오후 2:09:06] 대기..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [24-1-25오전 9:39:08] 93도 이하까지 펌프 가동..*/
            /*if( gu8_Hot_Tank_Temperature_One_Degree <= ICE_TRAY_CLEAN_STATE_START_HOT_TEMP )*/
            if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_ice_tray_start_hot_temp )
            {
                gu16_ice_tray_clean_timer++;

                if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }
            else
            {
                gu32_ice_tray_clean_max_timer++;

                /*..hui [24-1-25오전 9:39:37] 아이스트레이 순환 최대 2분..*/
                /*if( gu32_ice_tray_clean_max_timer >= ICE_TRAY_HOT_CIRCULATION_MAX_TIME )*/
                /*..hui [24-1-31오전 10:15:37] 아이스트레이 세척도 최대 10초..*/
                if( gu32_ice_tray_clean_max_timer >= HOT_CIRCULATION_MAX_TIME )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            break;

        case 4:

            /*..hui [23-8-24오후 4:25:38] 펌프 정지. .오버히팅 순환 종료..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

        case 5:

            /*..hui [23-8-24오후 4:26:46] 오버히팅 NOS 5-3 ON..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 6:

            /*..hui [23-5-15오후 7:50:38] 살균 피드 5-1 ON..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 7:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else
                {
                    gu16_ice_tray_clean_timer++;

                    if( gu16_ice_tray_clean_timer >= 600 )
                    {
                        gu16_ice_tray_clean_timer = 0;
                        gu32_ice_tray_clean_max_timer = 0;
                        gu8_ice_tray_clean_step = 9;
                    }
                    else{}
                }
            }
            else
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step = 9;
            }

            break;

        case 8:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else
            {
                gu16_ice_tray_clean_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_ice_tray_clean_timer >= 600 )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }

            break;

        case 9:

            /*..hui [24-1-25오전 9:51:54] 트레이 펌프 가동.. 왼쪽으로 5-1번으로만 3분 동안 분사..*/
            /*..hui [24-1-25오후 1:05:06] 여기서 냉수 드레인 밸브도 5초..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_ice_tray_clean_timer++;
            }
            else
            {
                gu32_ice_tray_clean_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_ice_tray_clean_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }

            if( gu16_ice_tray_clean_timer >= ICE_TRAY_CLEAN_SPRAY_TIME_3_MIN )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;

            #if 0
            if( gu16_ice_tray_clean_timer <= 900 )
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;
            }
            else
            {
                gu8_ster_pump_stage = STER_PUMP_STAGE_80_PERCENT;
            }
            #endif


            break;

        case 10:

            /*..hui [23-2-28오후 6:57:19] 펌프 정지.. 분사 종료..*/
            gu16_ice_tray_clean_timer++;

            /*if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-30오후 5:25:51] 밸브 열어놓은 상태로 5초간 대기.. ..*/
            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_AIR_REMOVE_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 11:

            /*..hui [23-10-17오전 11:47:02] 살균피드 5-1 OFF..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 12:

            /*..hui [24-1-25오전 9:54:07] 오버히팅 NOS 밸브 5-3 OFF..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 13:

            /*..hui [24-1-25오전 9:59:19] 고온세척 밸브 6-2 OFF..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 14:

            /*..hui [24-1-25오전 10:20:04] 물 담근채로 3분동안 대기..*/
            gu16_ice_tray_clean_timer++;

            if( gu16_ice_tray_clean_timer >= ICE_TRAY_CLEAN_TIME_10_MIN )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 15:

            gu16_ice_tray_clean_timer++;

            /*..hui [24-1-25오전 10:21:41] 아이스 트레이 입수 밸브 6-1 ON..*/
            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 16:

            /*..hui [24-1-25오전 10:22:41] 트레이 펌프 가동..*/
            /*..hui [24-1-25오전 10:22:50] 찬물 넣어서 중탕시켜줌..*/
            if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
            {
                gu16_ice_tray_clean_timer++;
            }
            else
            {
                gu32_ice_tray_clean_max_timer++;

                /*..hui [24-1-25오후 3:15:22] 만일 대비.. 10분넘게 정지상태 유지시 다음 단계로..*/
                if( gu32_ice_tray_clean_max_timer >= HOT_STER_SAFETY_TIME )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }

            /*..hui [24-1-25오전 10:23:01] 우선 10초로..*/
            /*if( gu16_ice_tray_clean_timer >= 100 )*/
            /*if( gu16_ice_tray_clean_timer >= 50 )*/
            /*if( gu16_ice_tray_clean_timer >= 150 )*/
            /*if( gu16_ice_tray_clean_timer >= 50 )*/
            /*if( gu16_ice_tray_clean_timer >= 80 )*/
            if( gu16_ice_tray_clean_timer >= 100 )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            gu8_ster_pump_stage = STER_PUMP_STAGE_90_PERCENT;


            break;

        case 17:

            gu16_ice_tray_clean_timer++;

            /*..hui [24-1-25오전 10:23:38] 펌프 정지 입수 종료..*/
            if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else{}

            break;

        case 18:

            gu16_ice_tray_clean_timer++;

            /*..hui [24-1-25오전 10:24:18] 트레이 입수 밸브 6-1 OFF..*/
            /*if( gu16_ice_tray_clean_timer >= ICE_TANK_STER_DELAY_TIME )*/
            /*..hui [24-1-26오전 9:33:42] 중탕시키고 10초간 대기..*/
            /*if( gu16_ice_tray_clean_timer >= 100 )*/
            /*..hui [24-2-14오후 5:54:24] 30초간 대기..*/
            if( gu16_ice_tray_clean_timer >= 300 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else
                {
                    gu32_ice_tray_clean_max_timer++;

                    if( gu32_ice_tray_clean_max_timer >= HOT_STER_SAFETY_TIME )
                    {
                        gu16_ice_tray_clean_timer = 0;
                        gu32_ice_tray_clean_max_timer = 0;
                        gu8_ice_tray_clean_step++;
                    }
                    else{}
                }
            }
            else{}

            break;

        case 19:

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else
                {
                    gu16_ice_tray_clean_timer++;

                    if( gu16_ice_tray_clean_timer >= 600 )
                    {
                        gu16_ice_tray_clean_timer = 0;
                        gu32_ice_tray_clean_max_timer = 0;
                        gu8_ice_tray_clean_step = 21;
                    }
                    else{}
                }
            }
            else
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step = 21;
            }

            break;

        case 20:

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_ice_tray_clean_timer = 0;
                gu32_ice_tray_clean_max_timer = 0;
                gu8_ice_tray_clean_step++;
            }
            else
            {
                gu16_ice_tray_clean_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_ice_tray_clean_timer >= 600 )
                {
                    gu16_ice_tray_clean_timer = 0;
                    gu32_ice_tray_clean_max_timer = 0;
                    gu8_ice_tray_clean_step++;
                }
                else{}
            }

            break;

        case 21:

            gu16_ice_tray_clean_timer = 0;
            gu32_ice_tray_clean_max_timer = 0;
            gu8_ice_tray_clean_step = 0;

            /*..hui [24-1-25오전 10:33:34] 아이스 트레이 세척 작업 완료..*/
            mu8_return = SET;

            break;

        default:

            gu16_ice_tray_clean_timer = 0;
            gu32_ice_tray_clean_max_timer = 0;
            gu8_ice_tray_clean_step = 0;


        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sel_start_temp(void)
{
    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        gu8_hot_spray_start_hot_temp = ALTITUDE__1__ICE_TANK_STER__HEATER_ON_TEMP;
        gu8_lukewarm_spray_start_hot_temp = 90;
        gu8_final_clean_start_hot_temp = 87;

        gu8_ice_tray_start_hot_temp = ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
        gu8_mlet_ice_start_hot_temp = ALTITUDE__1__MELT_ICE__HEATER_ON_TEMP;
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        gu8_hot_spray_start_hot_temp = ALTITUDE__2__ICE_TANK_STER__HEATER_ON_TEMP;
        gu8_lukewarm_spray_start_hot_temp = 87;
        gu8_final_clean_start_hot_temp = 84;

        gu8_ice_tray_start_hot_temp = ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
        gu8_mlet_ice_start_hot_temp = ALTITUDE__2__MELT_ICE__HEATER_ON_TEMP;
    }
    else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
    {
        gu8_hot_spray_start_hot_temp = ALTITUDE__3__ICE_TANK_STER__HEATER_ON_TEMP;
        gu8_lukewarm_spray_start_hot_temp = 84;
        gu8_final_clean_start_hot_temp = 81;

        gu8_ice_tray_start_hot_temp = ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
        gu8_mlet_ice_start_hot_temp = ALTITUDE__3__MELT_ICE__HEATER_ON_TEMP;
    }
    else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
    {
        gu8_hot_spray_start_hot_temp = ALTITUDE__4__ICE_TANK_STER__HEATER_ON_TEMP;
        gu8_lukewarm_spray_start_hot_temp = 82;
        gu8_final_clean_start_hot_temp = 79;

        gu8_ice_tray_start_hot_temp = ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
        gu8_mlet_ice_start_hot_temp = ALTITUDE__4__MELT_ICE__HEATER_ON_TEMP;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



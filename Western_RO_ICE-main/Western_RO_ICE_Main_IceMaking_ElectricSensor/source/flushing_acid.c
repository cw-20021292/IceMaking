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
#include    "flushing_acid.h"


void acid_control(void);
U8 check_acid_clean_enable(void);
void return_acid_clean(void);
void save_acid_clean(void);
U8 standby_acid_clean(void);
void start_acid_clean(void);
U8 prepare_acid_clean(void);
U8 change_filter_acid_clean(void);
U8 wait_1_hour_acid_clean(void);
U8 rinse_acid_clean(void);
U8 wait_finish_acid_clean(void);
void finish_acid_clean(void);
void init_acid_clean(void);
void acid_clean_pump_output(void);
void init_acid_clean_drain(void);
void check_acid_error(void);
void halt_acid_clean(void);
void acid_reset_filter(void);

TYPE_BYTE          U8AcidStopB;
#define            u8AcidStop                          U8AcidStopB.byte
#define            Bit0_Acid_Error_Stop_State          U8AcidStopB.Bit.b0
#define            Bit1_Acid_Cover_Open_Stop_State     U8AcidStopB.Bit.b1

bit bit_acid_clean_start;
U8 gu8_acid_clean_step;
U32 gu32_acid_clean_timer;
U32 gu32_acid_clean_max_timer;


ACID_CLEAN_STEP gu8_acid_clean_mode;

U8 gu8_acid_prepare_step;
U16 gu16_acid_prepare_timer;
U16 gu16_acid_prepare_max_timer;

U8 gu8_acid_change_filter_step;
U16 gu16_acid_change_filter_timer;
U16 gu16_acid_change_filter_max_timer;

U8 gu8_acid_wait_step;
U16 gu16_acid_wait_timer;
U32 gu32_acid_wait_max_timer;

U8 gu8_acid_rinse_step;
U16 gu16_acid_rinse_timer;
U32 gu32_acid_rinse_max_timer;

U8 gu8_acid_finish_step;
U16 gu16_acid_finish_timer;
U32 gu32_acid_finish_max_timer;



//bit bit_acid_filter_reed;
//bit bit_acid_start_key;

bit bit_neo_detect;
bit bit_ino_detect;
bit bit_all_detect;

bit bit_tank_empty;
U8 gu8_acid_clean_state;


bit bit_acid_drain_finish;
bit bit_acid_drain_pump_output;
bit bit_acid_drain_valve_output;
U8 gu8_before_acid_drain_level;
U16 gu16_acid_drain_op_timer;
U8 gu8_acid_drain_no_water_timer;

U16 gu16_acid_drain_finish_timer;

U16 gu16_acid_drain_error_finish_timer;


U8 gu8_acid_enable_step;
U8 gu8_acid_enable_timer;


U8 gu8_return_acid_step;

bit bit_acid_power_off_check;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void acid_control(void)
{
    U8 mu8_finish = 0;

    check_acid_error();

    /*..hui [24-7-26오후 1:59:56] 진행중에 에러 걸리면 대기모드로..*/
    if( gu8_acid_clean_mode >= ACID_CLEAN_PREPARE )
    {
        if( Bit0_Acid_Error_Stop_State == SET )
        {
            gu8_acid_clean_mode = ACID_CLEAN_STANDBY;
        }
        else if( Bit1_Acid_Cover_Open_Stop_State == SET )
        {
            /*..hui [24-7-26오후 3:47:51] 구연산 입수, 세척, 종료준비할때 커버나 필터 열리면 일시 중지..*/
            if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE
                || gu8_acid_clean_mode == ACID_CLEAN_RINSE
                || gu8_acid_clean_mode == ACID_CLEAN_FINISH )
            {
                gu8_acid_clean_mode = ACID_CLEAN_STANDBY;
            }
            else{}
        }
        else{}
    }
    else{}

    switch( gu8_acid_clean_mode )
    {
        case ACID_CLEAN_NONE_STATE:

            mu8_finish = check_acid_clean_enable();

            if( mu8_finish == SET )
            {
                bit_acid_clean_start = SET;
                gu8_acid_clean_mode = ACID_CLEAN_STANDBY;
            }
            else{}

        break;

        case ACID_CLEAN_STANDBY:

            mu8_finish = standby_acid_clean();

            if( mu8_finish == SET )
            {
                init_acid_clean_drain();
                return_acid_clean();
            }
            else{}

        break;

        case ACID_CLEAN_PREPARE:

            mu8_finish = prepare_acid_clean();

            if( mu8_finish == SET )
            {
                gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;
                gu8_acid_change_filter_step = 0;
            }
            else{}

        break;

        case ACID_CLEAN_CHANGE_FILTER:

            mu8_finish = change_filter_acid_clean();

            if( mu8_finish == SET )
            {
                gu8_acid_clean_mode = ACID_CLEAN_WAIT_1_HOUR;
                gu16_acid_wait_timer = 0;
                gu32_acid_wait_max_timer = 0;
                gu8_acid_wait_step = 0;
            }
            else{}

        break;

        case ACID_CLEAN_WAIT_1_HOUR:

            mu8_finish = wait_1_hour_acid_clean();

            if( mu8_finish == SET )
            {
                gu8_acid_clean_mode = ACID_CLEAN_RINSE;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
                gu8_acid_rinse_step = 0;
            }
            else{}

        break;

        case ACID_CLEAN_RINSE:

            mu8_finish = rinse_acid_clean();

            if( mu8_finish == SET )
            {
                gu8_acid_clean_mode = ACID_CLEAN_FINISH;
                gu16_acid_finish_timer = 0;
                gu32_acid_finish_max_timer = 0;
                gu8_acid_finish_step = 0;

                /*..hui [24-7-26오후 2:02:41] 세척까지 끝내면 정전보상 안함.. 껐다켜면 정상상태 유지..*/
                gu8_return_acid_step = 0;
            }
            else{}

        break;

        case ACID_CLEAN_FINISH:

            mu8_finish = wait_finish_acid_clean();

            if( mu8_finish == SET )
            {
                finish_acid_clean();
            }
            else{}

        break;

        default :

            init_acid_clean();

        break;

    }

    save_acid_clean();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void return_acid_clean(void)
{
    if( gu8_return_acid_step == 0 )
    {
        /*..hui [24-7-26오후 2:06:28] 정상 상태..*/
        gu8_acid_clean_mode = ACID_CLEAN_PREPARE;
        gu16_acid_prepare_timer = 0;
        gu16_acid_prepare_max_timer = 0;
        gu8_acid_prepare_step = 0;
    }
    else if( gu8_return_acid_step == 1 )
    {
        /*..hui [24-7-26오후 2:06:33] 탱크 배수..*/
        gu8_acid_clean_mode = ACID_CLEAN_PREPARE;
        gu16_acid_prepare_timer = 0;
        gu16_acid_prepare_max_timer = 0;
        gu8_acid_prepare_step = 0;
    }
    else if( gu8_return_acid_step == 2 )
    {
        /*..hui [24-7-26오후 2:06:48] 세정액 주입..*/
        gu8_acid_clean_mode = ACID_CLEAN_PREPARE;
        gu16_acid_prepare_timer = 0;
        gu16_acid_prepare_max_timer = 0;
        gu8_acid_prepare_step = 3;
    }
    else if( gu8_return_acid_step == 3 )
    {
        /*..hui [24-7-26오후 2:07:39] 필터 도어 OPEN..*/
        gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
        gu16_acid_change_filter_timer = 0;
        gu16_acid_change_filter_max_timer = 0;
        gu8_acid_change_filter_step = 0;
    }
    else if( gu8_return_acid_step == 4 )
    {
        /*..hui [24-7-26오후 2:09:19] 세정 필터 제거..*/
        gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
        gu16_acid_change_filter_timer = 0;
        gu16_acid_change_filter_max_timer = 0;
        gu8_acid_change_filter_step = 2;
    }
    else if( gu8_return_acid_step == 5 )
    {
        /*..hui [24-7-26오후 2:09:54] RO 필터 체결..*/
        gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
        gu16_acid_change_filter_timer = 0;
        gu16_acid_change_filter_max_timer = 0;
        gu8_acid_change_filter_step = 3;
    }
    else if( gu8_return_acid_step == 6 )
    {
        /*..hui [24-7-26오후 2:11:50] 네오, 이노 필터 교체..*/
        gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
        gu16_acid_change_filter_timer = 0;
        gu16_acid_change_filter_max_timer = 0;
        gu8_acid_change_filter_step = 4;
    }
    else if( gu8_return_acid_step == 7 )
    {
        /*..hui [24-7-26오후 2:50:21] 필터 커버 닫힘..*/
        gu8_acid_clean_mode = ACID_CLEAN_CHANGE_FILTER;
        gu16_acid_change_filter_timer = 0;
        gu16_acid_change_filter_max_timer = 0;
        gu8_acid_change_filter_step = 5;
    }
    else if( gu8_return_acid_step == 8 )
    {
        /*..hui [24-7-26오후 2:51:32] 1시간 대기..*/
        gu8_acid_clean_mode = ACID_CLEAN_WAIT_1_HOUR;
        gu16_acid_wait_timer = 0;
        gu32_acid_wait_max_timer = 0;
        gu8_acid_wait_step = 0;
    }
    else if( gu8_return_acid_step == 9 )
    {
        /*..hui [24-7-26오후 2:52:07] 구연산 세척수 배수..*/
        gu8_acid_clean_mode = ACID_CLEAN_RINSE;
        gu16_acid_rinse_timer = 0;
        gu32_acid_rinse_max_timer = 0;
        gu8_acid_rinse_step = 0;
    }
    else if( gu8_return_acid_step == 10 )
    {
        /*..hui [24-7-26오후 2:53:11] 만수위 재정수..*/
        gu8_acid_clean_mode = ACID_CLEAN_RINSE;
        gu16_acid_rinse_timer = 0;
        gu32_acid_rinse_max_timer = 0;
        gu8_acid_rinse_step = 2;
    }
    else if( gu8_return_acid_step == 11 )
    {
        /*..hui [24-7-26오후 2:53:45] 1차 배수..*/
        gu8_acid_clean_mode = ACID_CLEAN_RINSE;
        gu16_acid_rinse_timer = 0;
        gu32_acid_rinse_max_timer = 0;
        gu8_acid_rinse_step = 9;
    }
    else if( gu8_return_acid_step == 12 )
    {
        /*..hui [24-7-26오후 2:54:55] 2차 만수위 재정수..*/
        gu8_acid_clean_mode = ACID_CLEAN_RINSE;
        gu16_acid_rinse_timer = 0;
        gu32_acid_rinse_max_timer = 0;
        gu8_acid_rinse_step = 11;
    }
    else if( gu8_return_acid_step == 13 )
    {
        /*..hui [24-7-26오후 2:55:17] 2차 배수..*/
        gu8_acid_clean_mode = ACID_CLEAN_RINSE;
        gu16_acid_rinse_timer = 0;
        gu32_acid_rinse_max_timer = 0;
        gu8_acid_rinse_step = 12;
    }
    else if( gu8_return_acid_step == 14 )
    {
        /*..hui [24-7-26오후 2:56:27] 저수위까지 재정수..*/
        gu8_acid_clean_mode = ACID_CLEAN_FINISH;
        gu16_acid_finish_timer = 0;
        gu32_acid_finish_max_timer = 0;
        gu8_acid_finish_step = 0;
    }
    else
    {
        gu8_return_acid_step = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_acid_clean(void)
{
    /*..hui [24-7-30오전 10:58:49] 에러 걸렸을땐 저장하지 않는다.. ex) 단수에러 걸리고 step 0으로 초기화되고..*/
    /*..hui [24-7-30오전 10:59:03] 스탠바이 모드로 가기전에 0.1초 사이에 여기서 스텝 0으로 저장됨..*/
    /*if( Bit0_Acid_Error_Stop_State == SET )*/
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit6_Main_Water_Flow_Block_Error__E09 == SET
        || Bit16_Drain_Pump_Error__E60 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        return;
    }
    else{}

    if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE )
    {
        if( gu8_acid_prepare_step <= 1 )
        {
            gu8_return_acid_step = 1;
        }
        else if( gu8_acid_prepare_step <= 4 )
        {
            gu8_return_acid_step = 2;
        }
        else
        {
            gu8_return_acid_step = 3;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
    {
        if( gu8_acid_change_filter_step <= 1 )
        {
            gu8_return_acid_step = 3;
        }
        else if( gu8_acid_change_filter_step == 2 )
        {
            gu8_return_acid_step = 4;
        }
        else if( gu8_acid_change_filter_step == 3 )
        {
            gu8_return_acid_step = 5;
        }
        else if( gu8_acid_change_filter_step == 4 )
        {
            gu8_return_acid_step = 6;
        }
        else if( gu8_acid_change_filter_step == 5 )
        {
            gu8_return_acid_step = 7;
        }
        else
        {
            gu8_return_acid_step = 8;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR )
    {
        if( gu8_acid_wait_step <= 1 )
        {
            gu8_return_acid_step = 8;
        }
        else
        {
            gu8_return_acid_step = 9;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
    {
        if( gu8_acid_rinse_step <= 1 )
        {
            gu8_return_acid_step = 9;
        }
        else if( gu8_acid_rinse_step <= 8 )
        {
            gu8_return_acid_step = 10;
        }
        else if( gu8_acid_rinse_step <= 10 )
        {
            gu8_return_acid_step = 11;
        }
        else if( gu8_acid_rinse_step <= 11 )
        {
            gu8_return_acid_step = 12;
        }
        else if( gu8_acid_rinse_step <= 13 )
        {
            gu8_return_acid_step = 13;
        }
        else
        {
            gu8_return_acid_step = 14;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )
    {
        if( gu8_acid_finish_step <= 1 )
        {
            gu8_return_acid_step = 14;
        }
        else
        {
            gu8_return_acid_step = 0;
        }
    }
    else{}



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 check_acid_clean_enable(void)
{
    U8 mu8_return = 0;

    #if 0
    if( bit_acid_reed == SET && bit_filter_all == SET )
    {
        mu8_return = SET;
        bit_acid_clean_start = SET;
        play_melody_setting_on_198();
    }
    else
    {
        bit_acid_clean_start = CLEAR;
    }
    #endif

    if( bit_acid_power_off_check == CLEAR )
    {
        bit_acid_power_off_check = SET;

        /*..hui [24-7-26오후 3:18:51] 정전보상..*/
        /*if( gu8_return_acid_step >= 1 && gu8_return_acid_step <= 14)*/
        /*..hui [24-7-26오후 3:41:04] 다 끝내고 마지막 저수위 재정수중에 전원 껐다키면..*/
        /*..hui [24-7-26오후 3:41:26] 그때는 그냥 정상 상태 유지하도록.. 어차피 재정수는 정상모드에서도 하니까~~..*/
        if( gu8_return_acid_step >= 1 && gu8_return_acid_step <= 13)
        {
            mu8_return = SET;
            bit_acid_clean_start = SET;
            play_melody_setting_on_198();
        }
        else
        {
            gu8_return_acid_step  = 0;
        }
    }
    else
    {
        /*..hui [24-7-26오후 1:24:51] 구연산 세척 할 수 없는 에러가 발생된 상태면.. 아예 확인도 안하도록..*/
        if( Bit0_Acid_Error_Stop_State == SET )
        {
            gu8_acid_enable_step = 0;
            return mu8_return;
        }
        else{}

        switch( gu8_acid_enable_step )
        {
            case 0 :

                if( bit_filter_cover == CLEAR && bit_acid_reed == CLEAR &&  bit_ro_filter_2_reed == CLEAR )
                {
                    gu8_acid_enable_step++;
                    gu8_acid_enable_timer  = 0;
                }
                else{}

            break;

            case 1 :

                if( bit_filter_cover == CLEAR && bit_acid_reed == SET &&  bit_ro_filter_2_reed == SET )
                {
                    gu8_acid_enable_step++;
                    gu8_acid_enable_timer  = 0;
                }
                else{}

            break;

            case 2 :

                /*..hui [24-7-26오전 11:06:39] 전부다 장착 완료..*/
                if( bit_acid_reed == SET
                    && bit_neo_filter_1_reed == SET
                    && bit_ro_filter_2_reed == SET
                    && bit_ino_filter_3_reed == SET
                    && bit_filter_cover == SET )
                {
                    gu8_acid_enable_step++;
                    gu8_acid_enable_timer  = 0;
                }
                else{}

            break;

            case 3 :

                mu8_return = SET;
                bit_acid_clean_start = SET;
                play_melody_setting_on_198();

            break;

            default :

                gu8_acid_enable_step = 0;
                gu8_acid_enable_timer = 0;

            break;
        }
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 standby_acid_clean(void)
{
    U8 mu8_return = 0;

    /*..hui [24-7-26오후 1:46:56] 모든 에러 조건 해제되면 다시 이전 상태로..*/
    if( u8AcidStop == CLEAR )
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
void start_acid_clean(void)
{
    #if 0
    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
    {

        if( Bit3_Leakage_Sensor_Error__E01 == SET
            || Bit6_Main_Water_Flow_Block_Error__E09 == SET
            || Bit16_Drain_Pump_Error__E60 == SET
            || Bit4_Room_Low_Water_Level_Error__E21 == SET )
        {
            play_melody_warning_197();
        }
        else
        {
            bit_acid_clean_start = SET;

            gu8_acid_clean_step = 0;
            gu32_acid_clean_timer = 0;
            gu32_acid_clean_max_timer = 0;
            bit_acid_start_key = CLEAR;
            bit_neo_detect = CLEAR;
            bit_ino_detect = CLEAR;

            init_tank_flushing();
        }
    }
    else
    {
        /*..hui [24-5-21오후 6:00:33] 만수에서 진행이 가능합니다. 만수까지 기다렸다 진행해주세요.~ 음성 출력..*/
        play_melody_warning_197();
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 prepare_acid_clean(void)
{
    U8 mu8_return = 0;


    switch( gu8_acid_prepare_step )
    {
        case 0 :

            init_acid_clean_drain();
            gu8_acid_prepare_step++;
            gu16_acid_prepare_timer = 0;
            gu16_acid_prepare_max_timer = 0;

        break;

        case 1 :

            /*..hui [24-5-24오후 5:13:24] 워터 플러싱중이었으면 끝날때까지 기다렸다가..*/
            if( bit_flushing_water_start == CLEAR )
            {
                /*..hui [24-5-21오후 2:19:31] 만수위에서 시작했으니.. 전체 배수..*/
                /*..hui [24-5-21오후 2:28:21] 최대시간 말고.. 배수 완료 안되면 끝내도록 변경하는게 좋을듯....*/
                if( bit_acid_drain_finish == SET )
                {
                     /*..hui [24-5-27오후 5:28:25] 끝나고도 드레인밸브가 계속 켜있음..*/
                     init_acid_clean_drain();
                     gu8_acid_prepare_step++;
                     gu16_acid_prepare_timer = 0;
                     gu16_acid_prepare_max_timer = 0;
                }
                else
                {
                    gu16_acid_prepare_max_timer++;

                    /*..hui [24-7-22오후 2:05:01] 1시간이 지났는데 배수 완료 안되면 우선 드레인펌프 에러..*/
                    if( gu16_acid_prepare_max_timer >= ACID_CLEAN_TANK_EMPTY_MAX_TIME )
                    {
                        gu8_acid_prepare_step = 0;
                        gu16_acid_prepare_timer = 0;
                        gu16_acid_prepare_max_timer = 0;
                        Bit16_Drain_Pump_Error__E60 = SET;
                    }
                    else
                    {
                        acid_clean_pump_output();
                    }
                }
            }
            else{}

        break;

        case 2 :

            /*..hui [24-5-23오전 9:37:20] 드레인탱크 비워질때까지 대기..*/
            /*..hui [24-7-22오후 7:56:46] 탱크 비움에서 비워졌겠지만 혹시나....*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                gu8_acid_prepare_step++;
                gu16_acid_prepare_timer = 0;
                gu16_acid_prepare_max_timer = 0;
            }
            else
            {
                gu16_acid_prepare_max_timer++;

                /*..hui [24-5-23오전 9:34:04] 최대 시간 10분..*/
                /*..hui [24-7-22오후 2:48:55] 최대 시간 15분..*/
                if( gu16_acid_prepare_max_timer >= 9000 )
                {
                    gu8_acid_prepare_step++;
                    gu16_acid_prepare_timer = 0;
                    gu16_acid_prepare_max_timer = 0;
                }
                else{}
            }

        break;

        case 3 :

            /*..hui [24-5-21오후 2:34:57] 피드밸브 ON..*/
            /*..hui [24-7-22오후 2:55:25] 우선 저수위까지 채우고 드레인탱크 채우도록..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_MID || gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu8_acid_prepare_step++;
                gu16_acid_prepare_timer = 0;
                gu16_acid_prepare_max_timer = 0;
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu16_acid_prepare_max_timer++;

                /*..hui [24-5-21오후 2:34:47] 세정액 주입.. 최대 시간 10분..*/
                /*..hui [24-7-22오후 2:31:09] 최대 시간 20분..*/
                if( gu16_acid_prepare_max_timer >= ACID_WATER_FULL_MAX_TIME )
                {
                    gu8_acid_prepare_step = 0;
                    gu16_acid_prepare_timer = 0;
                    gu16_acid_prepare_max_timer = 0;

                    /*..hui [24-5-21오후 2:35:48] 단수 에러 발생..*/
                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

        break;

        case 4 :

            /*..hui [24-5-21오후 2:34:57] 피드밸브 ON..*/
            /*..hui [24-7-22오후 2:56:18] 저수위이상 채웠으니 여기서 냉수 드레인 밸브 연다..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_acid_prepare_timer++;

                /*..hui [24-7-22오후 2:30:22] 만수위 감지되고 5초간 추가입수..*/
                if( gu16_acid_prepare_timer >= 50 )
                {
                    /*..hui [24-5-21오후 2:35:15] 세정 준비가 완료되었습니다.~~~ 음성 출력..*/
                    play_melody_setting_on_198();
                    gu8_acid_prepare_step++;
                    gu16_acid_prepare_timer = 0;
                    gu16_acid_prepare_max_timer = 0;

                }
                else{}
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu16_acid_prepare_max_timer++;

                /*..hui [24-5-21오후 2:34:47] 세정액 주입.. 최대 시간 10분..*/
                /*..hui [24-7-22오후 2:31:09] 최대 시간 20분..*/
                if( gu16_acid_prepare_max_timer >= ACID_WATER_FULL_MAX_TIME )
                {
                    gu8_acid_prepare_step = 0;
                    gu16_acid_prepare_timer = 0;
                    gu16_acid_prepare_max_timer = 0;

                    /*..hui [24-5-21오후 2:35:48] 단수 에러 발생..*/
                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

        break;

        case 5:

            init_acid_clean_drain();
            gu16_acid_prepare_timer = 0;
            gu16_acid_prepare_max_timer = 0;
            gu8_acid_prepare_step = 0;

            /*..hui [24-7-22오후 1:32:46] 세정액 주입 및 준비 작업 완료..*/
            mu8_return = SET;

            break;

        default :

            init_acid_clean_drain();
            gu16_acid_prepare_timer = 0;
            gu16_acid_prepare_max_timer = 0;
            gu8_acid_prepare_step = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 change_filter_acid_clean(void)
{
    U8 mu8_return = 0;
    U8 mu8_neo = 0;
    U8 mu8_ino = 0;

    switch( gu8_acid_change_filter_step )
    {
        case 0 :

            gu8_acid_change_filter_step++;
            gu16_acid_change_filter_timer = 0;
            gu16_acid_change_filter_max_timer = 0;

        break;

        case 1 :

            /*..hui [24-5-21오후 1:55:25] 필터 커버 열림 확인..*/
            if( bit_filter_cover == CLEAR )
            {
                play_melody_setting_on_198();
                gu8_acid_change_filter_step++;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;
            }
            else{}

        break;

        case 2 :

            /*..hui [24-5-21오후 2:43:24] 구연산 필터 분리 완료. 필터 커버는 연린 상태..*/
            if( bit_acid_reed == CLEAR && bit_ro_filter_2_reed == CLEAR && bit_filter_cover == CLEAR )
            {
                play_melody_setting_on_198();
                gu8_acid_change_filter_step++;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;
            }
            else{}

        break;

        case 3 :

            /*..hui [24-5-21오후 2:45:39] RO 필터 감지되면... 구연산 리드, 필터 커버는 미 감지상태..*/
            if( bit_acid_reed == CLEAR && bit_ro_filter_2_reed == SET && bit_filter_cover == CLEAR )
            {
                play_melody_setting_on_198();
                gu8_acid_change_filter_step++;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;

                bit_neo_detect = CLEAR;
                bit_ino_detect = CLEAR;
            }
            else{}

        break;

        case 4 :

            if( bit_neo_filter_1_reed == CLEAR )
            {
                bit_neo_detect = SET;
            }
            else
            {
                if( bit_neo_detect == SET )
                {
                    mu8_neo = SET;
                }
                else{}
            }

            if( bit_ino_filter_3_reed == CLEAR )
            {
                bit_ino_detect = SET;
            }
            else
            {
                if( bit_ino_detect == SET )
                {
                    mu8_ino = SET;
                }
                else{}
            }

            /*..hui [24-5-21오후 2:53:25] 네오, 이노 둘 다 교체 감지되면..*/
            if( mu8_neo == SET && mu8_ino == SET )
            {
                play_melody_setting_on_198();

                gu8_acid_change_filter_step++;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;
                bit_neo_detect = CLEAR;
                bit_ino_detect = CLEAR;
            }
            else{}

        break;

        case 5 :

            /*..hui [24-5-21오후 2:56:01] 구연산 미감지, 필터 3종 모두 감지, 필터 커버 장작쵠 상태..*/
            if( bit_acid_reed == CLEAR
                && bit_neo_filter_1_reed == SET
                && bit_ro_filter_2_reed == SET
                && bit_ino_filter_3_reed == SET
                && bit_filter_cover == SET )
            {
                gu8_acid_change_filter_step++;
                gu16_acid_change_filter_timer = 0;
                gu16_acid_change_filter_max_timer = 0;
            }
            else{}

        break;

        case 6:

            gu8_acid_change_filter_step = 0;
            gu16_acid_change_filter_timer = 0;
            gu16_acid_change_filter_max_timer = 0;

            /*..hui [24-7-22오후 2:34:18] 필터 RO, INO, NEO 모두 교체 완료..*/
            mu8_return = SET;

            break;

        default :

            gu8_acid_change_filter_step = 0;
            gu16_acid_change_filter_timer = 0;
            gu16_acid_change_filter_max_timer = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 wait_1_hour_acid_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_acid_wait_step )
    {
        case 0 :

            gu8_acid_wait_step++;
            gu16_acid_wait_timer = 0;
            gu32_acid_wait_max_timer = 0;

        break;

        case 1 :

            gu32_acid_wait_max_timer++;

            if( gu32_acid_wait_max_timer >= ACID_CLEANING_WAIT_TIME )
            {
                gu8_acid_wait_step++;
                gu16_acid_wait_timer = 0;
                gu32_acid_wait_max_timer = 0;
            }
            else{}

        break;

        case 2:

            gu8_acid_wait_step = 0;
            gu16_acid_wait_timer = 0;
            gu32_acid_wait_max_timer = 0;

            /*..hui [24-7-22오후 3:04:39] 구연산 넣고 1시간 대기 완료..*/
            mu8_return = SET;

            break;

        default :

            gu8_acid_wait_step = 0;
            gu16_acid_wait_timer = 0;
            gu32_acid_wait_max_timer = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 rinse_acid_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_acid_rinse_step )
    {
        case 0 :

            gu8_acid_rinse_step++;
            gu16_acid_rinse_timer = 0;
            gu32_acid_rinse_max_timer = 0;
            init_acid_clean_drain();

        break;

        case 1 :

            /*..hui [24-7-22오후 6:44:47] 구연산 세척수 배수..*/
            if( bit_acid_drain_finish == SET )
            {
                 /*..hui [24-5-27오후 5:28:25] 끝나고도 드레인밸브가 계속 켜있음..*/
                 init_acid_clean_drain();
                 gu8_acid_rinse_step++;
                 gu16_acid_rinse_timer = 0;
                 gu32_acid_rinse_max_timer = 0;
            }
            else
            {
                gu32_acid_rinse_max_timer++;

                /*..hui [24-7-22오후 2:05:01] 1시간이 지났는데 배수 완료 안되면 우선 드레인펌프 에러..*/
                if( gu32_acid_rinse_max_timer >= ACID_CLEAN_TANK_EMPTY_MAX_TIME )
                {
                    gu8_acid_rinse_step = 0;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;
                    Bit16_Drain_Pump_Error__E60 = SET;
                }
                else
                {
                    acid_clean_pump_output();
                }
            }

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
        case 2 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:06:42] 8-2 플러싱 피드 ON..*/
            if( gu16_acid_rinse_timer >= 5 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}

        break;

        case 3 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:06:59] 8-1 플러싱 NOS ON..*/
            if( gu16_acid_rinse_timer >= 5 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}


        break;

        case 4 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:07:18] 피드밸브 ON..*/
            if( gu16_acid_rinse_timer >= 5 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}

        break;

        case 5 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:07:39] 10분동안 플러싱..*/
            if( gu16_acid_rinse_timer >= 6000 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}

        break;

        case 6 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:07:18] 피드밸브 OFF..*/
            if( gu16_acid_rinse_timer >= 5 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}

        break;

        case 7 :

            gu16_acid_rinse_timer++;

            /*..hui [24-5-23오후 1:08:32] 플러싱 NOS OFF..*/
            /*..hui [24-5-23오후 1:08:52] 플러싱 FEED OFF..*/
            if( gu16_acid_rinse_timer >= 5 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
            }
            else{}

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
        case 8 :

            /*..hui [24-5-21오후 2:34:57] 피드밸브 ON..*/
            /*..hui [24-5-21오후 5:20:05] 만수위까지 재정수..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_acid_rinse_timer++;

                /*..hui [24-7-22오후 3:21:45] 1분동안 추가 재정수.. 이쪽에서..*/
                if( gu16_acid_rinse_timer >= 600 )
                {
                    gu8_acid_rinse_step++;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;
                }
                else{}
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu32_acid_rinse_max_timer++;

                /*..hui [24-5-21오후 5:22:35] 최대 제한 시간 2시간..*/
                if( gu32_acid_rinse_max_timer >= ACID_CLEAN_FULL_MAX_TIME )
                {
                    gu8_acid_rinse_step = 0;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;

                    /*..hui [24-5-21오후 2:35:48] 단수 에러 발생..*/
                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

        break;

        case 9 :

            gu16_acid_rinse_timer++;

            /*..hui [24-7-22오후 3:25:39] 5초동안 대기..*/
            if( gu16_acid_rinse_timer >= 50 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
                init_acid_clean_drain();
            }
            else{}

        break;

        case 10 :

            /*..hui [24-5-21오후 2:19:31] 만수위에서 시작했으니.. 전체 배수..*/
            /*..hui [24-5-21오후 2:28:21] 최대시간 말고.. 배수 완료 안되면 끝내도록 변경하는게 좋을듯....*/
            if( bit_acid_drain_finish == SET )
            {
                 /*..hui [24-5-27오후 5:28:25] 끝나고도 드레인밸브가 계속 켜있음..*/
                 init_acid_clean_drain();
                 gu8_acid_rinse_step++;
                 gu16_acid_rinse_timer = 0;
                 gu32_acid_rinse_max_timer = 0;
            }
            else
            {
                gu32_acid_rinse_max_timer++;

                /*..hui [24-7-22오후 2:05:01] 1시간이 지났는데 배수 완료 안되면 우선 드레인펌프 에러..*/
                if( gu32_acid_rinse_max_timer >= ACID_CLEAN_TANK_EMPTY_MAX_TIME )
                {
                    gu8_acid_rinse_step = 0;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;
                    Bit16_Drain_Pump_Error__E60 = SET;
                }
                else
                {
                    acid_clean_pump_output();
                }
            }

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
        case 11 :

            /*..hui [24-5-21오후 2:34:57] 피드밸브 ON..*/
            /*..hui [24-5-21오후 5:20:05] 만수위까지 재정수..*/
            /*..hui [24-7-22오후 3:27:05] 두번째 재정수..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_acid_rinse_timer++;

                /*..hui [24-7-22오후 3:21:45] 1분동안 추가 재정수.. 이쪽에서..*/
                if( gu16_acid_rinse_timer >= 600 )
                {
                    gu8_acid_rinse_step++;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;
                }
                else{}
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu32_acid_rinse_max_timer++;

                /*..hui [24-5-21오후 5:22:35] 최대 제한 시간 2시간..*/
                if( gu32_acid_rinse_max_timer >= ACID_CLEAN_FULL_MAX_TIME )
                {
                    gu8_acid_rinse_step = 0;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;

                    /*..hui [24-5-21오후 2:35:48] 단수 에러 발생..*/
                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

        break;

        case 12 :

            gu16_acid_rinse_timer++;

            /*..hui [24-7-22오후 3:25:39] 5초동안 대기..*/
            if( gu16_acid_rinse_timer >= 50 )
            {
                gu8_acid_rinse_step++;
                gu16_acid_rinse_timer = 0;
                gu32_acid_rinse_max_timer = 0;
                init_acid_clean_drain();
            }
            else{}

        break;

        case 13 :

            /*..hui [24-5-21오후 2:19:31] 만수위에서 시작했으니.. 전체 배수..*/
            /*..hui [24-5-21오후 2:28:21] 최대시간 말고.. 배수 완료 안되면 끝내도록 변경하는게 좋을듯....*/
            if( bit_acid_drain_finish == SET )
            {
                 /*..hui [24-5-27오후 5:28:25] 끝나고도 드레인밸브가 계속 켜있음..*/
                 init_acid_clean_drain();
                 gu8_acid_rinse_step++;
                 gu16_acid_rinse_timer = 0;
                 gu32_acid_rinse_max_timer = 0;
            }
            else
            {
                gu32_acid_rinse_max_timer++;

                /*..hui [24-7-22오후 2:05:01] 1시간이 지났는데 배수 완료 안되면 우선 드레인펌프 에러..*/
                if( gu32_acid_rinse_max_timer >= ACID_CLEAN_TANK_EMPTY_MAX_TIME )
                {
                    gu8_acid_rinse_step = 0;
                    gu16_acid_rinse_timer = 0;
                    gu32_acid_rinse_max_timer = 0;
                    Bit16_Drain_Pump_Error__E60 = SET;
                }
                else
                {
                    acid_clean_pump_output();
                }
            }

        break;

        case 14:

            gu8_acid_rinse_step = 0;
            gu16_acid_rinse_timer = 0;
            gu32_acid_rinse_max_timer = 0;

            /*..hui [24-7-22오후 3:04:39] 구연산 넣고 1시간 대기 완료..*/
            /*..hui [24-7-22오후 3:28:23] 앞단 드레인, 1번째 재정수, 탱크 비움, 2번째 재정수, 탱크 비움까지 완료..*/
            mu8_return = SET;

            acid_reset_filter();

            break;

        default :

            gu8_acid_rinse_step = 0;
            gu16_acid_rinse_timer = 0;
            gu32_acid_rinse_max_timer = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 wait_finish_acid_clean(void)
{
    U8 mu8_return = 0;

    switch( gu8_acid_finish_step )
    {
        case 0 :

            gu8_acid_finish_step++;
            gu16_acid_finish_timer = 0;
            gu32_acid_finish_max_timer = 0;

        break;

        case 1 :

            /*..hui [24-7-22오후 3:41:38] 피드밸브 ON..*/
            /*..hui [24-7-22오후 3:42:00] 저수위까지 재정수..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_MID || gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu8_acid_finish_step++;
                gu16_acid_finish_timer = 0;
                gu32_acid_finish_max_timer = 0;
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu32_acid_finish_max_timer++;

                /*..hui [24-5-21오후 5:22:35] 최대 제한 시간 1시간..*/
                /*..hui [24-7-22오후 3:43:22] 이건 1시간동안 안되도 그냥 종료..*/
                if( gu32_acid_finish_max_timer >= 36000 )
                {
                    gu8_acid_finish_step++;
                    gu16_acid_finish_timer = 0;
                    gu32_acid_finish_max_timer = 0;
                }
                else{}
            }

        break;

        case 2 :

            gu16_acid_finish_timer++;

            /*..hui [24-5-21오후 5:23:30] 종료..*/
            if( gu16_acid_finish_timer >= 10 )
            {
                /*..hui [24-5-21오후 5:23:57] 모든 세정 및 필터 플러싱 작업이 완료되었습니다.~~ 음성 출력..*/
                play_melody_setting_on_198();
                gu8_acid_finish_step++;
                gu16_acid_finish_timer = 0;
                gu32_acid_finish_max_timer = 0;

            }
            else{}

        break;

        case 3:

            gu8_acid_finish_step = 0;
            gu16_acid_finish_timer = 0;
            gu32_acid_finish_max_timer = 0;

            /*..hui [24-7-22오후 3:43:49] 저수위까지 재정수 완료.. 완전 종료..*/
            mu8_return = SET;

            break;

        default :

            gu8_acid_finish_step = 0;
            gu16_acid_finish_timer = 0;
            gu32_acid_finish_max_timer = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_acid_clean(void)
{
    bit_acid_clean_start = CLEAR;

    bit_neo_detect = CLEAR;
    bit_ino_detect = CLEAR;

    init_acid_clean_drain();
    init_acid_clean();

    /*..hui [24-5-29오전 9:14:09] 진행상태 EEPROM 저장..*/
    /*..hui [24-5-29오전 9:15:28] 종료후에 완료..*/
    gu8_acid_clean_state = CLEAR;
    gu8_return_acid_step = 0;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_acid_clean(void)
{
    gu8_acid_clean_mode = ACID_CLEAN_NONE_STATE;

    gu16_acid_prepare_timer = 0;
    gu16_acid_prepare_max_timer = 0;
    gu8_acid_prepare_step = 0;
    gu16_acid_change_filter_timer = 0;
    gu16_acid_change_filter_max_timer = 0;
    gu8_acid_change_filter_step = 0;
    gu16_acid_wait_timer = 0;
    gu32_acid_wait_max_timer = 0;
    gu8_acid_wait_step = 0;
    gu16_acid_rinse_timer = 0;
    gu32_acid_rinse_max_timer = 0;
    gu8_acid_rinse_step = 0;
    gu16_acid_finish_timer = 0;
    gu32_acid_finish_max_timer = 0;
    gu8_acid_finish_step = 0;
    gu16_acid_finish_timer = 0;
    gu32_acid_finish_max_timer = 0;
    gu8_acid_finish_step = 0;

    gu8_acid_enable_step = 0;
    gu8_acid_enable_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void acid_clean_pump_output(void)
{
    /*..hui [23-8-14오후 4:17:30] 드레인 시간 - 만수위부터 시작..*/
    /* 600
       710
       757
       780
       775
       930
       930 */

    switch(u8DrainWaterLevel)
    {
        case DRAIN_LEVEL_EMPTY :

             bit_acid_drain_pump_output = CLEAR;
             bit_acid_drain_valve_output = SET;

             gu8_before_acid_drain_level = DRAIN_LEVEL_EMPTY;
             gu16_acid_drain_op_timer = 0;

             /*..hui [23-8-14오후 2:04:53] 냉수탱크 저수위 미감지 이하에서만 확인하도록..*/
             if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
             {
                 gu16_acid_drain_finish_timer++;

                 /*..hui [23-8-14오후 1:37:19] x분동안 드레인밸브 열었는데 저수위 이상 감지 안되면 종료..*/
                 if( gu16_acid_drain_finish_timer >= MANUAL_DRAIN_FINISH_CHECK_TIME )
                 {
                     gu16_acid_drain_finish_timer = 0;
                     /*gu16_tank_flushing_max_timer = FLUSHING_TANK_MAX_TIME;*/
                     //////////////gu32_tank_flushing_operation_timer = FLUSHING_TANK_MAX_TIME;
                     bit_acid_drain_finish = SET;
                 }
                 else{}
             }
             else
             {
                 gu16_acid_drain_finish_timer = 0;
             }

             gu16_acid_drain_error_finish_timer = 0;

            break;

        case DRAIN_LEVEL_LOW :

             gu16_acid_drain_finish_timer = 0;

             /*..hui [18-1-14오후 6:06:23] 물없는 상태에서 냉수 배수밸브 ON 상태로 저수위 진입하면..*/
             if(gu8_before_acid_drain_level == DRAIN_LEVEL_EMPTY)
             {
                 gu16_acid_drain_op_timer++;

                 /*..hui [18-1-14오후 6:06:47] 40초 이상 냉수 배수했는데도 만수위에 도달하지 못하면..*/
                 /*..hui [18-1-14오후 6:07:00] 다시 드레인펌프 가동해서 드레인 시작..*/
                 /*..hui [18-1-14오후 6:11:06] 센서 오감지, 유로막힘등의 이유로.. 배수탱크 넘치지 않게 하기위해..???..*/
                 if(gu16_acid_drain_op_timer >= DRAIN_VALVE_OPEN_TIME)
                 {
                     bit_acid_drain_pump_output = SET;
                     bit_acid_drain_valve_output = CLEAR;

                     /*..hui [18-1-25오후 4:11:59] 드레인펌프 가동으로 전환하고 3초후에 피드백 확인..*/
                     if(gu16_acid_drain_op_timer >= DRAIN_VALVE_OPEN_TIME + 30)
                     {
                         /*..hui [18-1-25오후 4:12:27] 피드백 이하이면 다시 냉수 밸브 ON..*/
                         if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                         {
                             gu16_acid_drain_op_timer = 0;
                         }
                         else
                         {
                             /*..hui [18-1-25오후 4:12:45] 피드백 초과이면 드레인펌프 ON 상태 유지..*/
                             gu16_acid_drain_op_timer = DRAIN_VALVE_OPEN_TIME + 30;
                         }
                     }
                     else{}
                 }
                 else
                 {
                     bit_acid_drain_pump_output = CLEAR;
                     bit_acid_drain_valve_output = SET;
                 }
             }
             else
             {
                 gu16_acid_drain_op_timer = 0;
                 /*..hui [18-1-14오후 6:15:33] 만수위 감지되고 드레인펌프 가동하여 저수위까지 내려왔을때..*/
                 /*..hui [18-1-14오후 6:21:04] 이것도 센서 오감지나 유로 에어등의 이유로 물없음까지 잘 안내려갈때..*/
                 /*..hui [18-1-14오후 6:21:55] 다시 드레인펌프 OFF하고 냉수 밸브 ON하여 만수위로 가도록....*/
                 if( gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK )
                 {
                     gu8_acid_drain_no_water_timer++;

                     if( gu8_acid_drain_no_water_timer >= 100 )
                     {
                         gu8_acid_drain_no_water_timer = 100;
                         bit_acid_drain_pump_output = CLEAR;
                         bit_acid_drain_valve_output = SET;

                         /*..hui [24-7-26오후 5:05:31] 여기에도 종료 조건 추가....*/
                         /*..hui [24-7-26오후 5:06:07] 드레인 만수위 - 펌프 가동 - 저수위로 감지되서 펌프 계속 가동했는데..*/
                         /*..hui [24-7-26오후 5:06:18] 저수위센서 물방울로 인해 해제가 안될때..*/
                         /*..hui [24-7-26오후 5:06:41] 거기에 플러스.. 냉수탱크에 물도 없어서 냉수드레인밸브 열었는데 만수위로도 못갈때..*/
                         /*..hui [24-7-26오후 5:07:10] 그럴경우 최대 5분동안 냉수드레인밸브 열어놓고 그냥 종료..*/
                         if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
                         {
                             gu16_acid_drain_error_finish_timer++;

                             if( gu16_acid_drain_error_finish_timer >= 3000 )
                             {
                                 gu16_acid_drain_error_finish_timer = 0;
                                 bit_acid_drain_finish = SET;
                             }
                             else{}
                         }
                         else
                         {
                             gu16_acid_drain_error_finish_timer = 0;
                         }
                     }
                     else
                     {
                         bit_acid_drain_pump_output = SET;
                         bit_acid_drain_valve_output = CLEAR;
                     }
                 }
                 else
                 {
                     gu8_acid_drain_no_water_timer = 0;
                     bit_acid_drain_pump_output = SET;
                     bit_acid_drain_valve_output = CLEAR;
                 }

             }

            break;

        case DRAIN_LEVEL_ERROR :
        case DRAIN_LEVEL_HIGH :

             bit_acid_drain_pump_output = SET;
             bit_acid_drain_valve_output = CLEAR;
             gu8_before_acid_drain_level = DRAIN_LEVEL_HIGH;
             gu16_acid_drain_error_finish_timer = 0;

            break;

        //=====================================================
        default :

             bit_acid_drain_pump_output = CLEAR;
             bit_acid_drain_valve_output = CLEAR;
             gu8_before_acid_drain_level = DRAIN_LEVEL_EMPTY;

            break;
      }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_acid_clean_drain(void)
{
    /////gu16_tank_flushing_max_timer = 0;
    bit_acid_drain_pump_output = CLEAR;
    bit_acid_drain_valve_output = CLEAR;
    gu8_before_acid_drain_level = DRAIN_LEVEL_EMPTY;
    gu16_acid_drain_op_timer = 0;
    gu16_acid_drain_finish_timer = 0;
    gu8_acid_drain_no_water_timer = 0;
    gu16_acid_drain_error_finish_timer = 0;

    bit_acid_drain_finish = CLEAR;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_acid_error(void)
{
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit6_Main_Water_Flow_Block_Error__E09 == SET
        || Bit16_Drain_Pump_Error__E60 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET
        || bit_self_test_start == SET
        || gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        Bit0_Acid_Error_Stop_State = SET;
    }
    else
    {
        Bit0_Acid_Error_Stop_State = CLEAR;
    }

    if( bit_filter_all == CLEAR )
    {
        Bit1_Acid_Cover_Open_Stop_State = SET;
    }
    else
    {
        Bit1_Acid_Cover_Open_Stop_State = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void acid_reset_filter(void)
{
    /*..hui [24-8-26오후 2:30:25] 구연산세척은 CT가 하기때문에(일시적) 필터 사용량, 주기 변경 없음..*/
    /*..hui [24-8-26오후 2:30:48] 서비스부품도 구연산필터만 구성.. 이정환 부장님 결론..*/
    #if 0
    Bit0_Neo_Filter_1_Reset_State = SET;
    Bit1_Ro_Filter_2_Reset_State = SET;
    Bit2_Ino_Filter_3_Reset_State = SET;

    reset_time_neo_filter();
    reset_time_ro_filter();
    reset_time_ino_filter();

    send_wifi_system_function();

    /*..hui [24-1-30오전 10:50:10] 와이파이 필터 알람 1,2,3 해제..*/
    wifi_neo_ro_ino_filter_alarm_stop();

    /*..hui [24-1-18오전 9:14:00] 필터 감지 상태도 초기화..*/
    u8FilterResetState = FILTER_NO_CHANGE;

    change_filter_type();
    #endif

    /*..hui [24-7-30오후 1:48:36] 설치 플러싱 조건이었다면 해제..*/
    bit_install_flushing_state = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


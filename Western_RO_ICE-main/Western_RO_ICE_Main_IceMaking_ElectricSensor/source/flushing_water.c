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
#include    "flushing_water.h"


void pre_water_flushing( U8 mu8_off_state, U8 mu8_on_state );
U8 water_flushing_proc(void);


TYPE_BYTE          U8PreWaterFlushingB;
#define            u8PreWaterFlushing                                         U8PreWaterFlushingB.byte
#define            Bit0_Pre_WF_Power_On_State                                 U8PreWaterFlushingB.Bit.b0
#define            Bit1_Pre_WF_Low_Water_State                                U8PreWaterFlushingB.Bit.b1
#define            Bit2_Pre_WF_6_Hour_No_Input_Water_State                    U8PreWaterFlushingB.Bit.b2
#define            Bit3_Pre_WF_24_Hour_No_Water_Flushing_State                U8PreWaterFlushingB.Bit.b3



U8 gu8_water_flushing_step;
U16 gu16_water_flushing_timer;

bit bit_first_water_flushing;

bit bit_feed_on_state;
bit bit_feed_on_state_old;


U32 gu32_wf_6hour_timer;

U32 gu32_wf_24hour_timer;
bit bit_flushing_water_start;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pre_water_flushing( U8 mu8_off_state, U8 mu8_on_state )
{
    U8 mu8_finish = 0;
    U8 mu8_start = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-6-15오전 10:00:33] 전원 인가 후 첫 번째 급수 전..*/
    if( bit_first_water_flushing == CLEAR )
    {
        bit_first_water_flushing = SET;
        /*Bit0_Pre_WF_Power_On_State = SET;*/

        /*..hui [24-1-4오전 11:28:09] 플러싱중에는 어차피 워터플러싱 하기 때문에 추가로 할 필요없음..*/
        if( gu8_flushing_mode == FLUSHING_NONE_STATE )
        {
            Bit0_Pre_WF_Power_On_State = SET;
        }
        else
        {
            Bit0_Pre_WF_Power_On_State = CLEAR;
        }
    }
    else{}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    /*..hui [23-6-15오전 10:01:06] 저수위 상태인 경우..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        if( bit_flushing_low_water == SET )
        {
            bit_flushing_low_water = CLEAR;
            Bit1_Pre_WF_Low_Water_State = SET;
        }
        else{}
    }
    else
    {
        bit_flushing_low_water = SET;
    }
    #endif


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

    if( bit_feed_output == SET )
    {
        gu32_wf_6hour_timer = 0;
    }
    else
    {
        gu32_wf_6hour_timer++;
    }

    if( gu32_wf_6hour_timer >= NO_INPUT_WATER_6_HOUR )
    {
        gu32_wf_6hour_timer = 0;
        Bit2_Pre_WF_6_Hour_No_Input_Water_State = SET;
    }
    else{}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

    gu32_wf_24hour_timer++;

    if( gu32_wf_24hour_timer >= NO_WATER_FLUSHING_24_HOUR )
    {
        gu32_wf_24hour_timer = 0;
        Bit3_Pre_WF_24_Hour_No_Water_Flushing_State = SET;
    }
    else{}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-8-23오후 3:08:33] 플러싱모드 아닐 경우에만..*/
    /*..hui [23-8-23오후 3:26:39] 필터 리드류 전부 감지일때만..*/
    /*..hui [23-8-24오전 9:12:35] 온수세척할떄는 시작안함..*/
    if( mu8_off_state == 0x00 && mu8_on_state == 0x01
        && gu8_flushing_mode == FLUSHING_NONE_STATE
        && bit_filter_all == SET
        && bit_ice_tank_ster_start == CLEAR
        && bit_self_test_start == CLEAR
        && bit_acid_clean_start == CLEAR )
    {
        if( bit_feed_on_state_old == SET )
        {
            bit_feed_on_state_old = CLEAR;

            if( u8PreWaterFlushing > 0 )
            {
                bit_feed_on_state = SET;
            }
            else{}
        }
        else{}
    }
    else
    {
        bit_feed_on_state_old = SET;
    }

    /*..hui [23-6-16오후 2:34:45] 조건이 만족한 상태에서 피드 ON 조건이되면 실행..*/
    if( u8PreWaterFlushing > 0 && bit_feed_on_state == SET )
    {
        mu8_finish = water_flushing_proc();

        if( mu8_finish == SET )
        {
            u8PreWaterFlushing = 0;

            /*..hui [23-6-15오후 12:12:08] 24시간 타이머 초기화..*/
            gu32_wf_24hour_timer = 0;
            bit_flushing_water_start = CLEAR;
            /*..hui [23-6-16오후 2:41:15] 피드 켜지기전에 실행하고, 계속 켜져있는 상태에서 다시 조건 만족했을때는 실행하지 않기위해..*/
            bit_feed_on_state = CLEAR;
        }
        else
        {
            bit_flushing_water_start = SET;
        }
    }
    else
    {
        gu8_water_flushing_step = 0;
        bit_flushing_water_start = CLEAR;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


}






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 water_flushing_proc(void)
{
    U8 mu8_return = 0;

    switch( gu8_water_flushing_step )
    {
        case 0:

            gu16_water_flushing_timer++;

            if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 1:

            gu16_water_flushing_timer++;

            /*..hui [23-6-14오후 7:30:47] 플러싱 유로전환 밸브 ON..*/
            if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 2:

            gu16_water_flushing_timer++;

            /*..hui [23-6-14오후 7:31:06] FEED 밸브 ON..*/
            if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 3:

            gu16_water_flushing_timer++;

            /*..hui [23-6-14오후 7:31:25] 3분 대기..*/
            if( gu16_water_flushing_timer >= PRE_WATER_FLUSHING_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;

                /*..hui [23-6-14오후 7:33:43] RO 플러싱 디스크 모터 OPEN..*/
                run_open_ro_drain();
            }
            else
            {
                /*..hui [23-8-23오후 3:16:51] 워터 플러싱 진행 중 플러싱으로 전환되면 중단..*/
                if( gu8_flushing_mode > FLUSHING_NONE_STATE
                    || bit_filter_all == CLEAR
                    || bit_ice_tank_ster_start == SET )
                {
                    gu16_water_flushing_timer = 0;
                    gu8_water_flushing_step = 6;
                }
                else{}
            }

            break;

        case 4:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 OPEN 완료되면..*/
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_OPEN )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 5:

            gu16_water_flushing_timer++;

            /*..hui [23-6-14오후 7:37:37] 3초 동안 플러싱..*/
            if( gu16_water_flushing_timer >= RO_WATER_FLUSHING_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 6:

            gu16_water_flushing_timer++;

            /*..hui [23-6-14오후 7:38:36] FEED 밸브 닫음..*/
            /*if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )*/
            if( gu16_water_flushing_timer >= 20 )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;

                /*run_close_ro_drain();*/
            }
            else{}

            break;

        case 7:

            gu16_water_flushing_timer++;

            /*..hui [23-6-16오후 2:47:15] 플러싱 유로전환 밸브 OFF..*/
            if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;

                run_close_ro_drain();
            }
            else{}

            break;

        case 8:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 CLOSE 완료되면..*/
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 9:

            gu16_water_flushing_timer++;

            /*..hui [23-6-16오후 2:48:42] 재정수를 위해 피드밸브 ON할때까지 0.5초 대기..*/
            if( gu16_water_flushing_timer >= FLUSHING_WATER_DELAY_TIME )
            {
                gu16_water_flushing_timer = 0;
                gu8_water_flushing_step++;
            }
            else{}

            break;

        case 10:

            gu8_water_flushing_step = 0;
            gu16_water_flushing_timer = 0;

            /*..hui [23-6-14오후 7:40:33] 급수 플러싱 종료..*/
            mu8_return = SET;


            break;


        default:

            gu8_water_flushing_step = 0;
            gu16_water_flushing_timer = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



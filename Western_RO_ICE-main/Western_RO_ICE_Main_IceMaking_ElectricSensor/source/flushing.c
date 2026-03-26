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
#include    "flushing.h"

void flushing_main(void);
void check_flushing_enable(void);
void flushing_standby(void);
void flushing_control(void);
U8 flushing_proc(void);
void flushing_finish(void);
void calc_flushing_remain_time(void);
void halt_flushing(void);
void flushing_pairing_start(void);
void forced_finish_flushing(void);
/////void check_acid_error(void);
void check_flushing_error(void);
void flushing_tank_control(void);
U8 flushing_tank_proc(void);
void tank_flushing_pump_output(void);
void init_tank_flushing(void);
void calc_flushing_total_time(void);
void halt_tank_flushing(void);
void save_return_step( U8 mu8_step );
void convert_filter_change_type(void);
void change_filter_type(void);

TYPE_BYTE          U8InstallFlushingEnableB;
#define            u8InstallFlushingEnable                 U8InstallFlushingEnableB.byte
#define            Bit0_First_Turn_On_State                U8InstallFlushingEnableB.Bit.b0
#define            Bit1_Filter_Flushing_Ing_State          U8InstallFlushingEnableB.Bit.b1


TYPE_BYTE          U8FlushingStopB;
#define            u8FlushingStop                          U8FlushingStopB.byte
#define            Bit0_Flushing_Error_Stop_State          U8FlushingStopB.Bit.b0
#define            Bit1_Flushing_Cover_Open_Stop_State     U8FlushingStopB.Bit.b1



bit bit_install_flushing_state;


U8 gu8_filter_flushing_state;

FLUSHING_STEP gu8_flushing_mode;
bit bit_flushing_check_finish;
bit bit_flushing_start;
U8 gu8_flushing_step;
U16 gu16_flushing_timer;
U8 gu8_flushing_operation_timer_min;

U8 gu8_display_flushing_reamin_minute;
U8 gu8_display_flushing_elapsed_percent;

U8 gu8_display_flushing_total_percent;

U8 gu8_flushing_okay_key_indicator;
bit bit_flushing_halt;
bit bit_tank_flushing_halt;

bit bit_filter_flushing_no_cancel;


bit bit_flushing_tank_start;
U8 gu8_flushing_tank_step;
U8 gu8_return_flushing_tank_step;


U16 gu16_flushing_tank_timer;
U16 gu16_tank_flushing_max_timer;
U32 gu32_tank_flushing_operation_timer;

bit bit_tank_drain_pump_output;
bit bit_tank_drain_valve_output;
U8 gu8_before_tank_drain_level;
U16 gu16_tank_drain_op_timer;

U8 gu8_tank_drain_no_water_timer;

U16 gu16_tank_drain_finish_timer;

bit bit_ro_drain_finish;


bit bit_install_voice_start;
U8 gu8_install_voice_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_main(void)
{
    switch( gu8_flushing_mode )
    {
        case FLUSHING_NONE_STATE:

            /*..hui [23-6-2오전 11:08:29] 플러싱 가능 상태 확인..*/
            check_flushing_enable();

        break;

        case FLUSHING_STANDBY_STATE:

            /*..hui [23-6-2오전 11:08:33] 플러싱 대기..*/
            flushing_standby();

        break;

        case FLUSHING_MAIN_STATE:

            /*..hui [23-6-2오전 11:08:38] 플러싱 제어..*/
            flushing_control();

        break;

        case FLUSHING_TANK_STATE:

            /*..hui [23-8-14오후 4:21:35] 앞단 플러싱 완료 후 탱크 만수위 -> 비움 1회 실행..*/
            flushing_tank_control();

        break;

        case FLUSHING_FINISH_STATE:

            /*..hui [23-6-2오전 11:08:42] 플러싱 종료..*/
            flushing_finish();

        break;

        default:

            gu8_flushing_mode = FLUSHING_NONE_STATE;
            init_tank_flushing();

        break;
    }

    calc_flushing_total_time();

    gu8_flushing_okay_key_indicator = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_flushing_enable(void)
{
    if( bit_flushing_check_finish == SET )
    {
        /*init_tank_flushing();*/
        return;
    }
    else{}

    if( bit_install_flushing_state == SET )
    {
        gu8_flushing_mode = FLUSHING_STANDBY_STATE;
        gu8_flushing_operation_timer_min = 0;
        gu8_display_flushing_reamin_minute = 30;
        gu8_display_flushing_elapsed_percent = 0;
        gu8_display_flushing_total_percent = 0;
        gu32_tank_flushing_operation_timer = 0;

        /*..hui [21-10-6오전 9:31:55] 필터 플러싱 진입 이후 전원OFF -> PBA 교체?로 설치 플러싱 들어간 경우..*/
        /*..hui [21-10-6오전 9:32:06] 설치 플러싱이 필터 플러싱보다 우선하도록..*/
        gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
        /////Bit1_Filter_Flushing_Ing_State = CLEAR;

        /*play_voice_install_guide_75();*/
        /*..hui [23-12-15오후 1:32:25] 코웨이 부팅음 완료되고 출력되게 하기위해..*/
        bit_install_voice_start = SET;

        /*..hui [23-12-19오후 3:27:33] 설치플러싱일경우 필터 관련 데이타 전부 초기화..*/
        init_filter_data();

        /*..hui [24-2-21오후 4:11:06] CT 강제 플러싱 종료..*/
        finish_ct_forced_flushing();
    }
    else
    {
        /////Bit0_First_Turn_On_State = CLEAR;

        /*..hui [21-10-6오전 9:43:12] 필터 플러싱 진행상태가 아닌경우..*/
        if( gu8_filter_flushing_state > FILTER_FLUSHING_NONE )
        {
            gu8_flushing_mode = FLUSHING_STANDBY_STATE;
            gu8_flushing_operation_timer_min = 0;
            gu8_display_flushing_elapsed_percent = 0;
            gu8_display_flushing_total_percent = 0;
            gu32_tank_flushing_operation_timer = 0;
        }
        else
        {
            gu8_flushing_mode = FLUSHING_NONE_STATE;
            gu8_display_flushing_total_percent = 0;
            gu32_tank_flushing_operation_timer = 0;

            /*..hui [24-2-21오후 4:11:06] CT 강제 플러싱 종료..*/
            finish_ct_forced_flushing();
        }
    }

    bit_tank_flushing_halt = CLEAR;

    /*..hui [23-8-16오후 3:34:07] 플러싱 초기 ro 드레인 10초간 실행..*/
    bit_ro_drain_finish = CLEAR;
    bit_flushing_check_finish = SET;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_standby(void)
{
    if( gu8_flushing_okay_key_indicator == SET )
    {
        if( bit_filter_all == CLEAR
            || Bit3_Leakage_Sensor_Error__E01 == SET
            || Bit6_Main_Water_Flow_Block_Error__E09 == SET
            || Bit16_Drain_Pump_Error__E60 == SET
            || Bit4_Room_Low_Water_Level_Error__E21 == SET )
        {
            play_melody_warning_197();
        }
        else
        {
            if( bit_tank_flushing_halt == SET )
            {
                gu8_flushing_mode = FLUSHING_TANK_STATE;
                /*..hui [23-8-22오전 10:12:26] 이전에 일시정지됐던 스텝으로 이동..*/
                gu8_flushing_tank_step = gu8_return_flushing_tank_step;
            }
            else
            {
                gu8_flushing_mode = FLUSHING_MAIN_STATE;
            }

            bit_tank_flushing_halt = CLEAR;

            gu8_flushing_step = 0;
            bit_flushing_halt = CLEAR;
            /*play_melody_setting_on_198();*/
            play_voice_filter_flushing_start_23();


            /*..hui [24-1-17오후 4:55:43] yes, no 팝업 뜬 상태에서 추출 버튼 누를 경우에만....*/
            /*..hui [24-1-17오후 4:55:52] RO 교체해도 취소 가능하도록 바뀜..*/
            if( bit_yes_no_popup == SET )
            {
                bit_yes_no_popup = CLEAR;
                bit_filter_reset_yes = SET;
                bit_filter_reset_no = CLEAR;
            }
            else{}
        }

        /*..hui [23-12-15오후 1:34:47] 추출버튼을 한번 누른 후에는 출력안함..*/
        bit_install_voice_start = CLEAR;
    }
    else
    {
        if( bit_install_voice_start == SET )
        {
            gu8_install_voice_timer++;

            if( gu8_install_voice_timer >= 70 )
            {
                play_voice_install_guide_75();
                gu8_install_voice_timer = 0;
                bit_install_voice_start = CLEAR;
            }
            else{}
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_control(void)
{
    U8 mu8_finish = 0;

    check_flushing_error();

    if( u8FlushingStop == CLEAR )
    {
        if( bit_flushing_start == CLEAR )
        {
            bit_flushing_start = SET;
        }
        else{}
    }
    else
    {
        if( bit_flushing_start == SET )
        {
            halt_flushing();
            /*gu8_flushing_okay_key_indicator = SET;*/
        }
        else{}
    }

    if( bit_flushing_start == SET )
    {
        mu8_finish = flushing_proc();

        if( mu8_finish == SET )
        {
            init_tank_flushing();

            /*..hui [23-8-21오전 11:11:16] 탱크 1회 채움 동작은 설치 플러싱때만..*/
            if( bit_install_flushing_state == SET )
            {
                gu8_flushing_mode = FLUSHING_TANK_STATE;
            }
            else
            {
                gu8_flushing_mode = FLUSHING_FINISH_STATE;
            }

            bit_flushing_start = CLEAR;
        }
        else{}
    }
    else
    {
        gu8_flushing_step = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 flushing_proc(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_ble_ap_mode = 0;
    U8 mu8_time = 0;

    switch( gu8_flushing_step )
    {
        case 0:

            /*..hui [23-8-23오후 3:20:00] 워터 플러싱 중이었으면 끝날때까지 대기..*/
            if( bit_flushing_water_start == CLEAR )
            {
                /*gu16_flushing_timer = 0;*/
                /*gu8_flushing_step++;*/

                gu16_flushing_timer++;

                /*..hui [23-12-15오후 1:45:02] 필터 플러싱을 시작합니다~ 음성 끝나면 시작하기위해....*/
                /*..hui [23-12-15오후 1:45:10] 와이파이 연결을 자동으로~ 음성이랑 겹침....*/
                /*if( gu16_flushing_timer >= 50 )*/
                /*..hui [24-1-10오후 2:15:51] 와이파이 연결을 자동으로~ 음성 출력 안함..*/
                /*if( gu16_flushing_timer >= 10 )*/
                if( gu16_flushing_timer >= 50 )
                {
                    gu16_flushing_timer = 0;
                    gu8_flushing_step++;
                }
                else{}
            }
            else
            {
                gu16_flushing_timer++;

                if( gu16_flushing_timer >= 1800 )
                {
                    gu16_flushing_timer = 0;
                    gu8_flushing_step++;
                }
                else{}
            }

            break;

        case 1:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:32:54] 플러싱 유로전환 밸브 ON..*/
            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                /*..hui [23-6-14오전 11:24:50] 페어링 시작..*/
                flushing_pairing_start();
                gu16_flushing_timer = 0;

                /*..hui [23-8-16오후 3:32:02] ro 드레인 10초 완료하고 중간에 취소되면 다시 안함..*/
                if( bit_ro_drain_finish == SET )
                {
                    gu8_flushing_step = 7;
                }
                else
                {
                    gu8_flushing_step++;
                }
            }
            else{}

            break;

        case 2:

            gu16_flushing_timer++;

            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;

                /*..hui [23-6-14오후 7:33:43] RO 플러싱 디스크 모터 OPEN..*/
                run_open_ro_drain();
            }
            else{}

            break;

        case 3:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 OPEN 완료되면..*/
            #if 0
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_OPEN )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}
            #endif

            if( gu8_ro_drain_status == RO_DRAIN_STATUS_OPEN )
            {
                gu16_flushing_timer++;

                /*..hui [23-11-1오후 1:55:11] 공필터 물 채우는 시간 고려 ..*/
                /*if( gu16_flushing_timer >= 100 )*/
                /*..hui [24-1-11오전 10:31:22] 피드밸브 안켜지는 구간임.. 30초면 필터 물채우는시간 충분할듯....*/
                if( gu16_flushing_timer >= 10 )
                {
                    gu16_flushing_timer = 0;
                    gu8_flushing_step++;
                }
                else{}
            }
            else{}

            break;

        case 4:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:33:19] 피드밸브 ON..*/
            /*..hui [23-8-16오후 3:12:14] 10초 동안 진행..*/
            /*..hui [23-8-18오후 2:53:51] 10초 완료 후 피드밸브 OFF..*/
            /*if( gu16_flushing_timer >= 100 )*/
            /*..hui [23-9-21오후 2:00:13] 30초로 변경.. 조성곤 과장..ro ct랑 같이 변경.. 길수록 좋음..*/
            /*..hui [23-9-21오후 2:00:23] 이 시간에만 유량 단수 감지하는걸로 제어 변경예정..*/
            if( gu16_flushing_timer >= RO_DRAIN_FLUSHING_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 5:

            gu16_flushing_timer++;

            /*if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )*/
            if( gu16_flushing_timer >= 20 )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;

                /*..hui [23-8-16오후 3:12:54] 피드밸브 닫고 ro 드레인 밸브 닫음..*/
                run_close_ro_drain();
                /*..hui [23-8-16오후 3:32:29] ro 드레인 완료..*/
                bit_ro_drain_finish = SET;
            }
            else{}

            break;

        case 6:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 CLOSE 완료되면..*/
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 7:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:33:19] 피드밸브 ON..*/
            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
                bit_flushing_halt = CLEAR;
            }
            else{}

            break;

        case 8:

            gu16_flushing_timer++;

            if( gu16_flushing_timer >= 600 )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_operation_timer_min++;
            }
            else{}

            if( bit_install_flushing_state == SET )
            {
                mu8_time = INSTALL_FLUSHING_TIME;
            }
            else
            {
                if( gu8_filter_flushing_state == FILTER_FLUSHING_RO )
                {
                    mu8_time = INSTALL_FLUSHING_TIME;
                }
                else
                {
                    mu8_time = NEO_INO_REPLACE_FLUSHING_TIME;
                }
            }

            /*..hui [23-6-1오후 7:33:54] 30분 대기..*/
            /*if( gu8_flushing_operation_timer_min >= INSTALL_FLUSHING_TIME )*/
            if( gu8_flushing_operation_timer_min >= mu8_time )
            {
                gu16_flushing_timer = 0;
                //gu8_flushing_operation_timer_min = 0;
                gu8_flushing_step++;
            }
            else
            {
                if( gu8_flushing_okay_key_indicator == SET )
                {
                    /*halt_flushing();*/
                    gu16_flushing_timer = 0;
                    gu8_flushing_step++;
                    bit_flushing_halt = SET;

                    /*..hui [23-6-14오후 1:06:11] 에러나 커버 열려서 멈췄을때 부저음 안내기위해..*/
                    if( u8FlushingStop == CLEAR )
                    {
                        play_melody_setting_off_199();
                    }
                    else{}
                }
                else{}
            }

            /*..hui [23-8-18오후 3:21:14] 퍼센트만 표시로 바꼈지만 우선 남겨놓음.. 호출은 하는데 표시할때 안쓰는걸로..*/
            /*calc_flushing_remain_time();*/

            break;

        case 9:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:34:21] 피드 밸브 OFF..*/
            /*if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )*/
            /*..hui [23-8-18오후 3:03:38] OFF하고 2초 대기..*/
            if( gu16_flushing_timer >= 20 )
            {
                gu16_flushing_timer = 0;

                if( bit_flushing_halt == CLEAR )
                {
                    gu8_flushing_step++;
                }
                else
                {
                    gu8_flushing_step = 15;
                }
            }
            else{}

            break;

        case 10:

            gu16_flushing_timer++;

            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;

                /*..hui [23-6-14오후 7:33:43] RO 플러싱 디스크 모터 OPEN..*/
                run_open_ro_drain();
            }
            else{}


            break;

        case 11:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 OPEN 완료되면..*/
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_OPEN )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 12:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:33:19] 피드밸브 ON..*/
            /*..hui [23-8-16오후 3:12:14] 10초 동안 진행..*/
            /*..hui [23-8-18오후 2:53:51] 10초 완료 후 피드밸브 OFF..*/
            /*if( gu16_flushing_timer >= 100 )*/
            /*..hui [23-9-21오후 2:00:13] 30초로 변경.. 조성곤 과장..ro ct랑 같이 변경.. 길수록 좋음..*/
            /*..hui [23-9-21오후 2:00:23] 이 시간에만 유량 단수 감지하는걸로 제어 변경예정..*/
            if( gu16_flushing_timer >= RO_DRAIN_FLUSHING_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 13:

            gu16_flushing_timer++;

            if( gu16_flushing_timer >= 20 )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;

                /*..hui [23-8-16오후 3:12:54] 피드밸브 닫고 ro 드레인 밸브 닫음..*/
                run_close_ro_drain();
            }
            else{}

            break;

        case 14:

            /*..hui [23-6-14오후 7:37:24] RO 드레인 모터 CLOSE 완료되면..*/
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 15:

            gu16_flushing_timer++;

            /*..hui [23-9-22오후 1:29:44] 플러싱 NOS 밸브 닫음..*/
            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 16:

            gu16_flushing_timer++;

            /*..hui [23-6-1오후 7:34:41] 플러싱 유로전환 피드 밸브 OFF..*/
            if( gu16_flushing_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_timer = 0;
                gu8_flushing_step++;
            }
            else{}

            break;

        case 17:

            gu8_flushing_step = 0;
            gu16_flushing_timer = 0;

            if( bit_flushing_halt == SET )
            {
                halt_flushing();
            }
            else
            {
                /*..hui [21-5-28오후 4:50:52]   플러싱 종료..*/
                mu8_return = SET;
            }

            break;


        default:

            gu8_flushing_step = 0;
            gu16_flushing_timer = 0;
            gu8_flushing_operation_timer_min = 0;

        break;

    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_finish(void)
{
    /*..hui [23-12-18오후 7:04:18] 플러싱 물 사용량 계산..*/
    calc_flushing_water();

    convert_filter_change_type();

    bit_install_flushing_state = CLEAR;
    ////////u8FilterResetState = FILTER_NO_CHANGE;
    gu8_filter_flushing_state = FILTER_FLUSHING_NONE;

    gu8_flushing_mode = FLUSHING_NONE_STATE;
    gu8_flushing_operation_timer_min = 0;

    init_tank_flushing();

    /*..hui [23-8-16오후 3:35:12] 다음에 다시 플러싱 하게될때 ro 드레인부터 하기위해..*/
    bit_ro_drain_finish = CLEAR;

    /*..hui [23-12-15오후 1:24:51] 플터 플러싱이 완료되어 제품 사용이 가능합니다...*/
    play_voice_filter_flushing_finish_24();

    /*..hui [24-1-11오전 10:43:17] 설치 플러싱 완료 -> 바로 필터플러싱 들어가면.. 100%부터 시작함..*/
    gu8_display_flushing_total_percent = 0;

    /*..hui [24-1-18오전 9:14:00] 필터 감지 상태도 초기화..*/
    u8FilterResetState = FILTER_NO_CHANGE;

    /*..hui [24-2-21오후 4:11:06] CT 강제 플러싱 종료..*/
    finish_ct_forced_flushing();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_flushing_remain_time(void)
{
    U8 mu8_time = 0;
    U8 mu8_percent = 0;

    #if 0
    if( bit_install_flushing_state == SET )
    {
        mu8_time = (U8)(INSTALL_FLUSHING_TIME - gu8_flushing_operation_timer_min);
        mu8_percent = (U8)((U8)(gu8_flushing_operation_timer_min / 3) * 10);

        gu8_display_flushing_reamin_minute = mu8_time;
        gu8_display_flushing_elapsed_percent = mu8_percent;
    }
    else
    {
        /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )*/
        if( gu8_filter_flushing_state == FILTER_FLUSHING_NEO_INO )
        {
            mu8_time = (U8)(NEO_INO_REPLACE_FLUSHING_TIME - gu8_flushing_operation_timer_min);

            if( mu8_time == 2 )
            {
                mu8_percent = 0;
            }
            else if( mu8_time == 1 )
            {
                mu8_percent = 50;
            }
            else
            {
                mu8_percent = 100;
            }

            gu8_display_flushing_reamin_minute = mu8_time;
            gu8_display_flushing_elapsed_percent = mu8_percent;
        }
        else
        {
            mu8_time = (U8)(INSTALL_FLUSHING_TIME - gu8_flushing_operation_timer_min);
            mu8_percent = (U8)((U8)(gu8_flushing_operation_timer_min / 3) * 10);

            gu8_display_flushing_reamin_minute = mu8_time;
            gu8_display_flushing_elapsed_percent = mu8_percent;
        }
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void halt_flushing(void)
{
    bit_flushing_start = CLEAR;
    gu8_flushing_step = 0;
    gu16_flushing_timer = 0;
    bit_flushing_halt = CLEAR;

    gu8_flushing_mode = FLUSHING_STANDBY_STATE;

    /*..hui [23-6-8오후 5:03:08] 필터플러싱 -> 시작 -> 중단했을때 냉수 버튼 OFF.. 취소안됨..*/
    ///////bit_filter_flushing_no_cancel = SET;

    /*..hui [24-1-5오후 4:06:20] 커버 오픈시에도 초기화.. 필터 추가 교체했을수있으니..?..*/
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit6_Main_Water_Flow_Block_Error__E09 == SET
        || Bit16_Drain_Pump_Error__E60 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET
        || Bit1_Flushing_Cover_Open_Stop_State == SET )
    {
        gu8_flushing_operation_timer_min = 0;

        /*..hui [23-8-21오후 4:17:55] 표시 진행률도 초기화..*/
        gu8_display_flushing_total_percent = 0;

        /*..hui [23-8-21오후 4:23:05] 단수면 ro 드레인도 제대로 안됐을테니 다시..*/
        if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
        {
            bit_ro_drain_finish = CLEAR;
        }
        else{}
    }
    else{}

    bit_flushing_tank_start = CLEAR;
    gu8_flushing_tank_step = 0;
    gu16_flushing_tank_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void halt_tank_flushing(void)
{
    bit_flushing_tank_start = CLEAR;
    gu8_flushing_tank_step = 0;
    gu16_flushing_tank_timer = 0;
    /*bit_tank_flushing_halt = CLEAR;*/

    gu8_flushing_mode = FLUSHING_STANDBY_STATE;

    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit6_Main_Water_Flow_Block_Error__E09 == SET
        || Bit16_Drain_Pump_Error__E60 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        gu8_flushing_operation_timer_min = 0;

        /*..hui [23-8-21오후 4:17:55] 표시 진행률도 초기화..*/
        gu8_display_flushing_total_percent = 0;

        /*..hui [23-8-23오후 2:45:13] 에러 걸리면 아예 처음부터 다시..*/
        gu8_return_flushing_tank_step = 0;
        bit_tank_flushing_halt = CLEAR;
        gu32_tank_flushing_operation_timer = 0;

        /*..hui [23-8-21오후 4:23:05] 단수면 ro 드레인도 제대로 안됐을테니 다시..*/
        if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
        {
            bit_ro_drain_finish = CLEAR;
        }
        else{}
    }
    else{}

    init_tank_flushing();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_pairing_start(void)
{
    U8 mu8_ble_ap_mode = 0;

    /*..hui [21-8-10오후 9:04:14] 필터 플러싱 초기화 취소 기능 추가됨..*/
    /*..hui [21-8-10오후 9:04:33] 취소했다가 다시 시작하면 연결 끊어지니까 확인 후에~~..*/
    mu8_ble_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_BLE );


    if( bit_install_flushing_state == SET
        && mu8_ble_ap_mode == CLEAR
        && gu8_wifi_ap_first_temporary == CLEAR )
    {
        WifiKey(WIFI_KEY_BLE);

        /*..hui [24-1-10오후 2:13:36] 자동으로 시작합니다 음성 출력 안함..*/
        /*play_voice_pairing_auto_start_76();*/
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void forced_finish_flushing(void)
{
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        /*bit_install_flushing_state = CLEAR;*/
        /*gu8_filter_flushing_state = FILTER_FLUSHING_NONE;*/

        /*..hui [24-1-19오후 3:33:18] 냉수 3회 누른경우에느 아예 취소..*/
        if( gu8_flushing_finish_input_count == 3 )
        {
            bit_install_flushing_state = CLEAR;
            gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
        }
        else{}

        gu8_flushing_mode = FLUSHING_NONE_STATE;
        gu8_flushing_operation_timer_min = 0;
        /*play_melody_setting_on_198();*/
        play_voice_test_mode_151();
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
void check_flushing_error(void)
{
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit6_Main_Water_Flow_Block_Error__E09 == SET
        || Bit16_Drain_Pump_Error__E60 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        Bit0_Flushing_Error_Stop_State = SET;
    }
    else
    {
        Bit0_Flushing_Error_Stop_State = CLEAR;
    }

    /*if( bit_filter_cover == CLEAR || bit_ro_filter_2_reed == CLEAR )*/
    if( bit_filter_all == CLEAR )
    {
        Bit1_Flushing_Cover_Open_Stop_State = SET;
    }
    else
    {
        Bit1_Flushing_Cover_Open_Stop_State = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_tank_control(void)
{
    U8 mu8_finish = 0;

    check_flushing_error();

    if( u8FlushingStop == CLEAR )
    {
        if( bit_flushing_tank_start == CLEAR )
        {
            bit_flushing_tank_start = SET;
        }
        else{}
    }
    else
    {
        if( bit_flushing_tank_start == SET )
        {
            halt_tank_flushing();
        }
        else{}
    }

    if( bit_flushing_tank_start == SET )
    {
        mu8_finish = flushing_tank_proc();

        if( mu8_finish == SET )
        {
            gu8_flushing_mode = FLUSHING_FINISH_STATE;
            bit_flushing_tank_start = CLEAR;
        }
        else{}
    }
    else
    {
        gu8_flushing_tank_step = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 flushing_tank_proc(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_ble_ap_mode = 0;
    U8 mu8_time = 0;

    /*..hui [23-8-23오전 10:38:44] 헷갈려서 이쪽으로 이동..*/
    /*..hui [23-8-23오전 10:38:54] 탱크 플러싱은 모든 단계에서 취소 가능하도록 변경..*/
    if( gu8_flushing_okay_key_indicator == SET )
    {
        if( gu8_flushing_tank_step <= 2 )
        {
            save_return_step(0);
        }
        else if( gu8_flushing_tank_step == 3 )
        {
            save_return_step(3);
        }
        else if( gu8_flushing_tank_step == 4 || gu8_flushing_tank_step == 5 )
        {
            save_return_step(4);
        }
        else if( gu8_flushing_tank_step == 6 || gu8_flushing_tank_step == 7 )
        {
            save_return_step(6);
        }
        else if( gu8_flushing_tank_step == 8 || gu8_flushing_tank_step == 9 || gu8_flushing_tank_step == 10 )
        {
            save_return_step(8);
        }
        else{}

        gu16_flushing_tank_timer = 0;
        gu8_flushing_tank_step = 12;
        bit_tank_flushing_halt = SET;

        /*..hui [23-6-14오후 1:06:11] 에러나 커버 열려서 멈췄을때 부저음 안내기위해..*/
        if( u8FlushingStop == CLEAR )
        {
            play_melody_setting_off_199();
        }
        else{}
    }
    else{}

    switch( gu8_flushing_tank_step )
    {
        case 0:

            gu16_flushing_tank_timer = 0;
            gu8_flushing_tank_step++;

            break;

        case 1:

            gu16_flushing_tank_timer++;

            /*..hui [23-8-14오후 4:34:13] 피드밸브 ON..*/
            if( gu16_flushing_tank_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [23-8-14오후 4:35:57] 저수위센서 감지 시 다음 단계로 이동..*/
            /*..hui [23-8-23오전 9:14:28] 만약 만수위일 경우에도..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_MID || gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_flushing_tank_timer++;

                /*..hui [23-8-23오전 9:18:57] 만수위에서 시작하는 경우.. 최소 5초간 유지후 다음 단계로..*/
                if( gu16_flushing_tank_timer >= 60 )
                {
                    gu16_flushing_tank_timer = 0;
                    gu32_tank_flushing_operation_timer = 0;
                    gu8_flushing_tank_step++;
                }
                else
                {
                    /*..hui [23-8-23오전 9:40:34] 중수위, 만수위 감지 상태에서 시작했을 경우..*/
                    /*..hui [23-8-23오전 9:40:47] 3초동안 50% 표시, 이후 3초동안 60% 표시..*/
                    if( gu32_tank_flushing_operation_timer == 0 )
                    {
                        if( gu16_flushing_tank_timer >= 30 )
                        {
                            gu32_tank_flushing_operation_timer = 6001;
                        }
                        else{}
                    }
                    else{}
                }
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu32_tank_flushing_operation_timer++;

                /*..hui [23-9-22오후 1:43:57] 에러 추가하면서 저수위까지는 온수 채우는 시간도 있기 때문에 최대시간 1시간 30분으로..*/
                /*..hui [23-11-13오후 3:36:46] 저수위까지 2시간30분.. 이정환부장님.. 안전사양..*/
                /*..hui [23-11-13오후 3:37:04] 저수위 - 만수위까지는 2시간..*/
                if( gu32_tank_flushing_operation_timer >= FLUSHING_LOW_WATER_MAX_TIME )
                {
                    gu16_flushing_tank_timer = 0;
                    gu32_tank_flushing_operation_timer = 0;
                    gu8_flushing_tank_step++;

                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

            break;

        case 3:

            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_flushing_tank_timer++;

                /*..hui [23-8-23오전 9:18:57] 만수위에서 시작하는 경우.. 최소 5초간 유지후 다음 단계로..*/
                if( gu16_flushing_tank_timer >= 30 )
                {
                    gu16_flushing_tank_timer = 0;
                    gu32_tank_flushing_operation_timer = 0;
                    gu8_flushing_tank_step++;
                }
                else{}
            }
            else
            {
                /*..hui [23-8-14오후 4:36:05] 최대 시간 제한 추가..*/
                gu32_tank_flushing_operation_timer++;

                /*..hui [23-9-22오후 1:44:16] 저수위에서 만수위는 1시간으로..*/
                if( gu32_tank_flushing_operation_timer >= FLUSHING_HIGH_WATER_MAX_TIME )
                {
                    gu16_flushing_tank_timer = 0;
                    gu32_tank_flushing_operation_timer = 0;
                    gu8_flushing_tank_step++;

                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                }
                else{}
            }

            break;

        case 4:

            if( gu8_ice_system_ok == SET )
            {
                /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                up_tray_motor();
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else
            {
                /*..hui [23-8-24오후 2:28:45] 트레이 고장이거나 재시도중에는 그냥 얼음통에 버림..*/
                /*..hui [23-8-24오후 2:30:43] 그냥 전부 드레인으로 배수하는걸로..*/
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step = 10;
            }

            break;

        case 5:

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else
            {
                gu16_tank_flushing_max_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_tank_flushing_max_timer >= 600 )
                {
                    gu16_flushing_tank_timer = 0;
                    gu16_tank_flushing_max_timer = 0;
                    gu8_flushing_tank_step++;
                }
                else{}
            }

            break;

        case 6:

            gu16_flushing_tank_timer++;

            /*..hui [23-8-16오후 1:13:02] 트레이 입수 밸브 ON..*/
            if( gu16_flushing_tank_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu32_tank_flushing_operation_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 7:

            gu32_tank_flushing_operation_timer++;

            /*..hui [23-8-16오후 1:13:21] 트레이 입수 펌프 ON..*/
            /*..hui [23-8-16오후 1:14:17] 1분동안 넣어준다..*/
            if( gu32_tank_flushing_operation_timer >= ICE_TRAY_FLUSHING_TIME )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu32_tank_flushing_operation_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 8:

            gu16_flushing_tank_timer++;

            /*..hui [23-8-16오후 1:15:43] 트레이 입수 펌프 OFF..*/
            if( gu16_flushing_tank_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 9:

            gu16_flushing_tank_timer++;

            /*..hui [23-8-16오후 1:16:03] 트레이 입수 밸브 OFF..*/
            if( gu16_flushing_tank_timer >= FLUSHING_DELAY_TIME )
            {
                /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                down_tray_motor();

                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 10:

            gu32_tank_flushing_operation_timer++;

            /*..hui [23-8-14오후 4:42:57] 플러싱 배수 최대 시간은 우선 30분..*/
            /*..hui [23-8-16오후 1:16:30] 남은 물 배수..*/
            if(gu32_tank_flushing_operation_timer >= FLUSHING_TANK_MAX_TIME)
            {
                gu16_flushing_tank_timer = 0;
                gu32_tank_flushing_operation_timer = 0;
                gu8_flushing_tank_step++;

                /*..hui [24-5-27오후 5:28:25] 끝나고도 드레인밸브가 계속 켜있음..*/
                init_tank_flushing();
            }
            else
            {
                tank_flushing_pump_output();
            }

            break;

        case 11:

            gu16_flushing_tank_timer++;

            if( gu16_flushing_tank_timer >= FLUSHING_DELAY_TIME )
            {
                gu16_flushing_tank_timer = 0;
                gu16_tank_flushing_max_timer = 0;
                gu8_flushing_tank_step++;
            }
            else{}

            break;

        case 12:

            gu8_flushing_tank_step = 0;
            gu16_flushing_tank_timer = 0;
            gu16_tank_flushing_max_timer = 0;

            if( bit_tank_flushing_halt == SET )
            {
                halt_tank_flushing();
            }
            else
            {
                /*..hui [21-5-28오후 4:50:52]   플러싱 종료..*/
                mu8_return = SET;
            }

            /*..hui [21-5-28오후 4:50:52]   플러싱 종료..*/
            /*mu8_return = SET;*/

            break;


        default:

            gu8_flushing_tank_step = 0;
            gu16_flushing_tank_timer = 0;
            gu16_tank_flushing_max_timer = 0;

        break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tank_flushing_pump_output(void)
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

             bit_tank_drain_pump_output = CLEAR;
             bit_tank_drain_valve_output = SET;

             gu8_before_tank_drain_level = DRAIN_LEVEL_EMPTY;
             gu16_tank_drain_op_timer = 0;
             gu8_tank_drain_no_water_timer = 0;

             /*..hui [23-8-14오후 2:04:53] 냉수탱크 저수위 미감지 이하에서만 확인하도록..*/
             if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
             {
                 gu16_tank_drain_finish_timer++;

                 /*..hui [23-8-14오후 1:37:19] x분동안 드레인밸브 열었는데 저수위 이상 감지 안되면 종료..*/
                 if( gu16_tank_drain_finish_timer >= MANUAL_DRAIN_FINISH_CHECK_TIME )
                 {
                     gu16_tank_drain_finish_timer = 0;
                     /*gu16_tank_flushing_max_timer = FLUSHING_TANK_MAX_TIME;*/
                     gu32_tank_flushing_operation_timer = FLUSHING_TANK_MAX_TIME;
                 }
                 else{}
             }
             else
             {
                 gu16_tank_drain_finish_timer = 0;
             }

            break;

        case DRAIN_LEVEL_LOW :

             gu16_tank_drain_finish_timer = 0;

             /*..hui [18-1-14오후 6:06:23] 물없는 상태에서 냉수 배수밸브 ON 상태로 저수위 진입하면..*/
             if(gu8_before_tank_drain_level == DRAIN_LEVEL_EMPTY)
             {
                 gu16_tank_drain_op_timer++;

                 /*..hui [18-1-14오후 6:06:47] 40초 이상 냉수 배수했는데도 만수위에 도달하지 못하면..*/
                 /*..hui [18-1-14오후 6:07:00] 다시 드레인펌프 가동해서 드레인 시작..*/
                 /*..hui [18-1-14오후 6:11:06] 센서 오감지, 유로막힘등의 이유로.. 배수탱크 넘치지 않게 하기위해..???..*/
                 if(gu16_tank_drain_op_timer >= DRAIN_VALVE_OPEN_TIME)
                 {
                     bit_tank_drain_pump_output = SET;
                     bit_tank_drain_valve_output = CLEAR;

                     /*..hui [18-1-25오후 4:11:59] 드레인펌프 가동으로 전환하고 3초후에 피드백 확인..*/
                     if(gu16_tank_drain_op_timer >= DRAIN_VALVE_OPEN_TIME + 30)
                     {
                         /*..hui [18-1-25오후 4:12:27] 피드백 이하이면 다시 냉수 밸브 ON..*/
                         if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                         {
                             gu16_tank_drain_op_timer = 0;
                         }
                         else
                         {
                             /*..hui [18-1-25오후 4:12:45] 피드백 초과이면 드레인펌프 ON 상태 유지..*/
                             gu16_tank_drain_op_timer = DRAIN_VALVE_OPEN_TIME + 30;
                         }
                     }
                     else{}
                 }
                 else
                 {
                     bit_tank_drain_pump_output = CLEAR;
                     bit_tank_drain_valve_output = SET;
                 }
             }
             else
             {
                 gu16_tank_drain_op_timer = 0;
                 /*..hui [18-1-14오후 6:15:33] 만수위 감지되고 드레인펌프 가동하여 저수위까지 내려왔을때..*/
                 /*..hui [18-1-14오후 6:21:04] 이것도 센서 오감지나 유로 에어등의 이유로 물없음까지 잘 안내려갈때..*/
                 /*..hui [18-1-14오후 6:21:55] 다시 드레인펌프 OFF하고 냉수 밸브 ON하여 만수위로 가도록....*/
                 if( gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK )
                 {
                     gu8_tank_drain_no_water_timer++;

                     if( gu8_tank_drain_no_water_timer >= 100 )
                     {
                         gu8_tank_drain_no_water_timer = 100;
                         bit_tank_drain_pump_output = CLEAR;
                         bit_tank_drain_valve_output = SET;
                     }
                     else
                     {
                         bit_tank_drain_pump_output = SET;
                         bit_tank_drain_valve_output = CLEAR;
                     }
                 }
                 else
                 {
                     gu8_tank_drain_no_water_timer = 0;
                     bit_tank_drain_pump_output = SET;
                     bit_tank_drain_valve_output = CLEAR;
                 }
             }

            break;

        case DRAIN_LEVEL_ERROR :
        case DRAIN_LEVEL_HIGH :

             bit_tank_drain_pump_output = SET;
             bit_tank_drain_valve_output = CLEAR;
             gu8_before_tank_drain_level = DRAIN_LEVEL_HIGH;
             gu8_tank_drain_no_water_timer = 0;

            break;

        //=====================================================
        default :

             bit_tank_drain_pump_output = CLEAR;
             bit_tank_drain_valve_output = CLEAR;
             gu8_before_tank_drain_level = DRAIN_LEVEL_EMPTY;

            break;
      }
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_tank_flushing(void)
{
    /////gu16_tank_flushing_max_timer = 0;
    bit_tank_drain_pump_output = CLEAR;
    bit_tank_drain_valve_output = CLEAR;
    gu8_before_tank_drain_level = DRAIN_LEVEL_EMPTY;
    gu16_tank_drain_op_timer = 0;
    gu16_tank_drain_finish_timer = 0;
    gu8_tank_drain_no_water_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_flushing_total_time(void)
{
    U8 mu8_time = 0;
    U8 mu8_percent = 0;

    if( gu8_flushing_mode == FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
    {
        return;
    }
    else{}

    if( bit_flushing_halt == SET )
    {
        return;
    }
    else{}

    if( bit_tank_flushing_halt == SET )
    {
        return;
    }
    else{}

    if( bit_install_flushing_state == SET )
    {
        /*..hui [23-12-12오전 11:27:26] 설치플러싱..RO 필터 플러싱..*/
        if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
        {
            if( gu8_flushing_step <= 7 )
            {
                if( gu8_display_flushing_total_percent < 10 )
                {
                    gu8_display_flushing_total_percent = 0;
                }
                else{}
            }
            else if( gu8_flushing_step == 8 )
            {
                if( gu8_flushing_operation_timer_min <= 3 )
                {
                    if( gu8_display_flushing_total_percent < 10 )
                    {
                        gu8_display_flushing_total_percent = 0;
                    }
                    else{}
                }
                else if( gu8_flushing_operation_timer_min <= 10 )
                {
                    if( gu8_display_flushing_total_percent < 10 )
                    {
                        gu8_display_flushing_total_percent = 10;
                    }
                    else{}
                }
                else if( gu8_flushing_operation_timer_min <= 17 )
                {
                    if( gu8_display_flushing_total_percent < 20 )
                    {
                        gu8_display_flushing_total_percent = 20;
                    }
                    else{}
                }
                else if( gu8_flushing_operation_timer_min <= 24 )
                {
                    if( gu8_display_flushing_total_percent < 30 )
                    {
                        gu8_display_flushing_total_percent = 30;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 40 )
                    {
                        gu8_display_flushing_total_percent = 40;
                    }
                    else{}
                }
            }
            else if( gu8_flushing_step >= 9 )
            {
                if( gu8_display_flushing_total_percent < 40 )
                {
                    gu8_display_flushing_total_percent = 40;
                }
                else{}
            }
        }
        else if( gu8_flushing_mode == FLUSHING_TANK_STATE )
        {
            if( gu8_flushing_tank_step <= 1 )
            {
                if( gu8_display_flushing_total_percent < 40 )
                {
                    gu8_display_flushing_total_percent = 40;
                }
                else{}
            }
            else if( gu8_flushing_tank_step == 2 )
            {
                if( gu32_tank_flushing_operation_timer <= 6000 )
                {
                    if( gu8_display_flushing_total_percent < 50 )
                    {
                        gu8_display_flushing_total_percent = 50;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 60 )
                    {
                        gu8_display_flushing_total_percent = 60;
                    }
                    else{}
                }
            }
            else if( gu8_flushing_tank_step == 3 )
            {
                /*..hui [24-1-4오후 1:58:30] 저수위 -> 만수위 채우는 중.. 70%로 통일..*/
                if( gu8_display_flushing_total_percent < 70 )
                {
                    gu8_display_flushing_total_percent = 70;
                }
                else{}

                #if 0
                if( gu32_tank_flushing_operation_timer <= 3000 )
                {
                    if( gu8_display_flushing_total_percent < 70 )
                    {
                        gu8_display_flushing_total_percent = 70;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 80 )
                    {
                        gu8_display_flushing_total_percent = 80;
                    }
                    else{}
                }
                #endif
            }
            /*else if( gu8_flushing_tank_step >= 4 && gu8_flushing_tank_step <= 14 )*/
            else if( gu8_flushing_tank_step >= 4 && gu8_flushing_tank_step <= 9 )
            {
                if( gu8_display_flushing_total_percent < 80 )
                {
                    gu8_display_flushing_total_percent = 80;
                }
                else{}
            }
            /*else if( gu8_flushing_tank_step == 15 )*/
            else if( gu8_flushing_tank_step == 10 )
            {
                if( gu32_tank_flushing_operation_timer <= 3000 )
                {
                    if( gu8_display_flushing_total_percent < 80 )
                    {
                        gu8_display_flushing_total_percent = 80;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 90 )
                    {
                        gu8_display_flushing_total_percent = 90;
                    }
                    else{}
                }
            }
            else
            {
                if( gu8_display_flushing_total_percent < 100 )
                {
                    gu8_display_flushing_total_percent = 100;
                }
                else{}
            }
        }
        else
        {
            gu8_display_flushing_total_percent = 100;
        }
    }
    else
    {
        if( gu8_filter_flushing_state == FILTER_FLUSHING_NEO_INO )
        {
            /*..hui [23-12-12오후 12:15:00] 이 조건을 안넣으면 종료되기전에 finish state에서 step이 0이되면서 잠깐 0이표시될수이씀..*/
            if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
            {
                /*..hui [23-12-12오전 11:27:33] 네오,이노 교체 플러싱..*/
                if( gu8_flushing_step <= 3 )
                {
                    if( gu8_display_flushing_total_percent < 10 )
                    {
                        gu8_display_flushing_total_percent = 0;
                    }
                    else{}
                }
                else if( gu8_flushing_step == 4 )
                {
                    if( gu8_display_flushing_total_percent < 10 )
                    {
                        gu8_display_flushing_total_percent = 10;
                    }
                    else{}
                }
                else if( gu8_flushing_step <= 7 )
                {
                    if( gu8_display_flushing_total_percent < 20 )
                    {
                        gu8_display_flushing_total_percent = 20;
                    }
                    else{}
                }
                else if( gu8_flushing_step == 8 )
                {
                    if( gu8_flushing_operation_timer_min == 0 )
                    {
                        if( gu16_flushing_timer <= 200 )
                        {
                            if( gu8_display_flushing_total_percent < 30 )
                            {
                                gu8_display_flushing_total_percent = 30;
                            }
                            else{}
                        }
                        else if( gu16_flushing_timer <= 400 )
                        {
                            if( gu8_display_flushing_total_percent < 40 )
                            {
                                gu8_display_flushing_total_percent = 40;
                            }
                            else{}
                        }
                        else
                        {
                            if( gu8_display_flushing_total_percent < 50 )
                            {
                                gu8_display_flushing_total_percent = 50;
                            }
                            else{}
                        }
                    }
                    else
                    {
                        if( gu16_flushing_timer <= 200 )
                        {
                            if( gu8_display_flushing_total_percent < 60 )
                            {
                                gu8_display_flushing_total_percent = 60;
                            }
                            else{}
                        }
                        else if( gu16_flushing_timer <= 400 )
                        {
                            if( gu8_display_flushing_total_percent < 70 )
                            {
                                gu8_display_flushing_total_percent = 70;
                            }
                            else{}
                        }
                        else
                        {
                            if( gu8_display_flushing_total_percent < 80 )
                            {
                                gu8_display_flushing_total_percent = 80;
                            }
                            else{}
                        }
                    }
                }
                else if( gu8_flushing_step <= 14 )
                {
                    if( gu8_display_flushing_total_percent < 90 )
                    {
                        gu8_display_flushing_total_percent = 90;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 100 )
                    {
                        gu8_display_flushing_total_percent = 100;
                    }
                    else{}
                }
            }
            else
            {
                gu8_display_flushing_total_percent = 100;
            }
        }
        else /*if( gu8_filter_flushing_state == FILTER_FLUSHING_RO )*/
        {
            if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
            {
                /*..hui [23-12-12오후 12:01:58] RO필터 교체 플러싱... 30분..*/
                if( gu8_flushing_step <= 7 )
                {
                    if( gu8_display_flushing_total_percent < 10 )
                    {
                        gu8_display_flushing_total_percent = 0;
                    }
                    else{}
                }
                else if( gu8_flushing_step == 8 )
                {
                    if( gu8_flushing_operation_timer_min <= 4 )
                    {
                        if( gu8_display_flushing_total_percent < 10 )
                        {
                            gu8_display_flushing_total_percent = 10;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 8 )
                    {
                        if( gu8_display_flushing_total_percent < 20 )
                        {
                            gu8_display_flushing_total_percent = 20;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 12 )
                    {
                        if( gu8_display_flushing_total_percent < 30 )
                        {
                            gu8_display_flushing_total_percent = 30;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 16 )
                    {
                        if( gu8_display_flushing_total_percent < 40 )
                        {
                            gu8_display_flushing_total_percent = 40;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 20 )
                    {
                        if( gu8_display_flushing_total_percent < 50 )
                        {
                            gu8_display_flushing_total_percent = 50;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 24 )
                    {
                        if( gu8_display_flushing_total_percent < 60 )
                        {
                            gu8_display_flushing_total_percent = 60;
                        }
                        else{}
                    }
                    else if( gu8_flushing_operation_timer_min <= 27 )
                    {
                        if( gu8_display_flushing_total_percent < 70 )
                        {
                            gu8_display_flushing_total_percent = 70;
                        }
                        else{}
                    }
                    else
                    {
                        if( gu8_display_flushing_total_percent < 80 )
                        {
                            gu8_display_flushing_total_percent = 80;
                        }
                        else{}
                    }
                }
                else if( gu8_flushing_step <= 14 )
                {
                    if( gu8_display_flushing_total_percent < 90 )
                    {
                        gu8_display_flushing_total_percent = 90;
                    }
                    else{}
                }
                else
                {
                    if( gu8_display_flushing_total_percent < 100 )
                    {
                        gu8_display_flushing_total_percent = 100;
                    }
                    else{}
                }
            }
            else
            {
                gu8_display_flushing_total_percent = 100;
            }
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_return_step( U8 mu8_step )
{
    gu8_return_flushing_tank_step = mu8_step;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_filter_change_type(void)
{
    /*..hui [23-12-12오후 12:51:07] 설치 플러싱 말고.. 필터 플러싱 종료되면 순서 변경..*/
    if( gu8_filter_flushing_state == FILTER_FLUSHING_NONE )
    {
        return;
    }
    else{}

    if( bit_install_flushing_state == SET )
    {
        return;
    }
    else{}

    /*..hui [24-2-21오후 4:12:01] CT 강제 플러싱 할때도 교환 순서 변경 없음..*/
    if( gu8_ct_forced_flushing_start == SET )
    {
        return;
    }
    else{}

    #if 0
    if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_RO_INO_ALL;
    }
    else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
    }
    #endif

    /*..hui [24-7-30오후 1:47:36] 구연산에서도 변환해야해서 분리..*/
    change_filter_type();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void change_filter_type(void)
{
    if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_RO_INO_ALL;
    }
    else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



















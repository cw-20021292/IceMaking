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
#include    "uv_ice_tray.h"



void output_ice_tray_uv(void);
U8 uv_ice_tray_control(void);
void ice_tray_uv_operation_timer(void);
U8 ice_tray_uv_standby(void);
void start_ice_tray_uv(void);
void finish_ice_tray_uv(void);
void initial_ice_tray_uv_timer(void);
void uv_ice_tray_24_hour_timer(void);
U8 ice_tray_uv_making(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8IceTrayUvONB;
#define            u8IceTrayUvON                                          U8IceTrayUvONB.byte
#define            Bit0_Ice_Tray_1_2_UV_On_State                          U8IceTrayUvONB.Bit.b0
#define            Bit1_Ice_Tray_1_2_UV_Ice_Tank_Clean_On_State           U8IceTrayUvONB.Bit.b1
#define            Bit2_Ice_Tray_1_2_UV_Ice_Off_On_State                  U8IceTrayUvONB.Bit.b2
#define            Bit3_Ice_Tray_1_2_UV_Fault_Test_On_State               U8IceTrayUvONB.Bit.b3




TYPE_BYTE          U8IceTrayUvOFFB;
#define            u8IceTrayUvOFF                                         U8IceTrayUvOFFB.byte
#define            Bit0_Ice_Tray_UV_Tank_Open_Off_State                   U8IceTrayUvOFFB.Bit.b0
#define            Bit1_Ice_Tray_UV_Ice_Extract_Off_State                 U8IceTrayUvOFFB.Bit.b1
#define            Bit2_Ice_Tray_UV_Retry_3S_Off_State                    U8IceTrayUvOFFB.Bit.b2
#define            Bit3_Ice_Tray_UV_Error_Off_State                       U8IceTrayUvOFFB.Bit.b3






/***********************************************************************************************************************/
bit bit_ice_tray_1_2_uv_start;

U16 gu16_ice_tray_1_2_uv_operation_timer_sec;
U8 gu8_ice_tray_1_2_uv_operation_timer_min;
U16 gu16_ice_tray_1_2_uv_operation_timer_hour;

U16 gu16_ice_tray_1_2_uv_standby_timer_sec;
U16 gu16_ice_tray_1_2_uv_standby_timer_min;
U16 gu16_ice_tray_1_2_uv_standby_timer_hour;

U16 gu16_ice_tray_uv_24_hour_timer_sec;
U16 gu16_ice_tray_uv_24_hour_timer_min;
U16 gu16_ice_tray_uv_24_hour_timer_hour;

U8 gu8_uv_ice_tray_step;

bit bit_uv_ice_tray_out;

bit bit_uv_ice_full_state;

bit bit_ice_tray_uv_op_1;
bit bit_ice_tray_uv_op_2;

U8 gu8_tray_uv_throw_count_one_day;
U8 gu8_uv_ice_tray_retry_timer;


U32 gu32_ice_tray_up_max_timer;
U8 gu8_tray_uv_making_count_one_day;
bit bit_ice_tray_before;
bit bit_ice_tray_making_enable;

U16 gu16_uv_ice_make_time;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_tray_uv(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    Bit0_Ice_Tray_1_2_UV_On_State = uv_ice_tray_control();

    /*..hui [24-1-26오후 2:56:06] 얼음탱크 세척 중.. 아이스트레이 세척할때 제빙 방향에서 UV 조사..*/
    /*..hui [24-1-26오후 2:56:11] 최대 시간은 30분으로..*/
    /*..hui [24-2-2오후 2:23:55] 얼음탱크 뒤쪽 UV 출력할때 같이 출력..*/
    Bit1_Ice_Tray_1_2_UV_Ice_Tank_Clean_On_State = Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State;

    /*..hui [24-2-14오후 2:32:58] 얼음 OFF 했을때.. 얼음 탱크와 동일하게 동작..*/
    Bit2_Ice_Tray_1_2_UV_Ice_Off_On_State = Bit2_Ice_Tank_UV_Ice_Off_On_State;

    /*..hui [24-11-28오전 10:26:11] 전원 인가 후 1분 30초 동안 계속 켜서 고장 확인..*/
    /*..hui [24-11-28오전 10:26:47] UV 교체 후 정상 확인하려면 6시간동안 기다려야하는 문제..*/
    /*..hui [24-11-28오전 10:27:03] 서비스기획팀 요청~~~..*/
    /*..hui [24-11-28오후 1:19:16] 얼음 탱크 UV 테스트중 동일하게 동작..*/
    if( bit_uv_fault_test_start == SET )
    {
        Bit3_Ice_Tray_1_2_UV_Fault_Test_On_State = Bit3_Ice_Tank_UV_Fault_Test_On_State;
    }
    else
    {
        Bit3_Ice_Tray_1_2_UV_Fault_Test_On_State = CLEAR;
    }

    /***********************************************************************************************/
    /*..hui [19-10-24오후 8:04:35] 탱크 커버 열렸을경우 정지..*/
    /*..hui [20-2-19오후 5:59:39] 탱크 커버 열리면 즉시 꺼지도록 커버 입력부 분리..*/
    /*..hui [20-2-19오후 5:59:45] 코디 건강을위해.....*/
    Bit0_Ice_Tray_UV_Tank_Open_Off_State = ~bit_uv_tank_input;

    /*..hui [19-10-24오후 8:04:54] 얼음 추출 시 정지..*/
    /*Bit1_Ice_Tray_UV_Ice_Extract_Off_State = F_Ice;*/
    /*..hui [20-2-19오후 7:31:38] 얼음 추출구 열릴때 끄고 완전히 닫힌 후 켜도록 수정..*/
    if( F_Ice == SET )
    {
        Bit1_Ice_Tray_UV_Ice_Extract_Off_State = F_Ice;
    }
    else
    {
        if( gu16StepMotor2 == 0 )
        {
            Bit1_Ice_Tray_UV_Ice_Extract_Off_State = CLEAR;
        }
        else{}
    }


    if( bit_ice_tray_uv_retry_stop == SET )
    {
        gu8_uv_ice_tray_retry_timer++;

        if( gu8_uv_ice_tray_retry_timer >= 30 )
        {
            bit_ice_tray_uv_retry_stop = CLEAR;
            gu8_uv_ice_tray_retry_timer = 0;
            Bit2_Ice_Tray_UV_Retry_3S_Off_State = CLEAR;
        }
        else
        {
            Bit2_Ice_Tray_UV_Retry_3S_Off_State = SET;
        }
    }
    else
    {
        gu8_uv_ice_tray_retry_timer = 0;
        Bit2_Ice_Tray_UV_Retry_3S_Off_State = CLEAR;
    }

    Bit3_Ice_Tray_UV_Error_Off_State = Bit25_Ice_Tray_1_2_UV_Error__E76;




/***********************************************************************************************/
    if( u8IceTrayUvOFF > 0 )
    {
        pUV_LED_ICE_TRAY_1_2 = CLEAR;                  /*off*/
        Bit4_Ice_Tray_UV_12V_Out_State = CLEAR;
        bit_uv_ice_tray_out = CLEAR;
    }
    else
    {
        if( u8IceTrayUvON > 0 )
        {
            pUV_LED_ICE_TRAY_1_2 = SET;                 /*on*/
            Bit4_Ice_Tray_UV_12V_Out_State = SET;
            bit_uv_ice_tray_out = SET;
        }
        else
        {
            pUV_LED_ICE_TRAY_1_2 = CLEAR;                  /*off*/
            Bit4_Ice_Tray_UV_12V_Out_State = CLEAR;
            bit_uv_ice_tray_out = CLEAR;
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_ice_tray_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;
    U8 mu8_making_uv = 0;

    uv_ice_tray_24_hour_timer();

    /*..hui [23-6-30오전 10:20:26] 설치 플러싱할때도 안함..*/
    /*if( F_IceOn == CLEAR || bit_install_flushing_state == SET )*/
    /*..hui [24-1-12오후 2:43:29] 얼음 OFF일떄도 UV 동작하도록..*/
    /*if( bit_install_flushing_state == SET )*/
    /*..hui [24-2-2오후 3:27:57] 얼음 OFF일때는 따로 제어사양 추가..*/
    if( F_IceOn == CLEAR || bit_install_flushing_state == SET )
    {
        initial_ice_tray_uv_timer();
        gu8_uv_ice_tray_step = 0;
        bit_ice_tray_1_2_uv_start = CLEAR;
        return CLEAR;
    }
    else{}

/********************************************************************************************/
    switch( gu8_uv_ice_tray_step )
    {
        case 0 :

            mu8_finish = ice_tray_uv_standby();

            if(mu8_finish == SET)
            {
                gu8_uv_ice_tray_step = 1;
                start_ice_tray_uv();
            }
            else
            {
                mu8_return = ice_tray_uv_making();
            }

        break;

        case 1 :

            /*..hui [23-5-31오후 4:20:15] 아이스트레이 살균.. 1시간 동작..*/
            if(bit_ice_tray_1_2_uv_start == SET)
            {
                if( gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )
                {
                    /*..hui [23-5-31오후 4:22:58] 아이스 트레이 제빙 위치로 이동하면 취소..*/
                    finish_ice_tray_uv();
                }
                /*else if( u8IceTrayUvOFF == 0 )*/
                else if( Bit0_Ice_Tray_UV_Tank_Open_Off_State == CLEAR && Bit1_Ice_Tray_UV_Ice_Extract_Off_State == CLEAR )
                {
                    /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                    ice_tray_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu8_uv_ice_tray_step = 0;
            }

        break;

        default :

            gu8_uv_ice_tray_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_tray_uv_operation_timer(void)
{
    gu16_ice_tray_1_2_uv_operation_timer_sec++;

    if(gu16_ice_tray_1_2_uv_operation_timer_sec >= 600)
    {
        gu16_ice_tray_1_2_uv_operation_timer_sec = 0;
        gu8_ice_tray_1_2_uv_operation_timer_min++;
    }
    else{}

    /*..hui [23-5-31오후 4:08:05] 아이스트레이 UV는 1시간동안 동작..*/
    if(gu8_ice_tray_1_2_uv_operation_timer_min >= UV_ICE_TRAY_OPERATION_TIME_MIN)
    {
        bit_ice_tray_1_2_uv_start = CLEAR;
        initial_ice_tray_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_tray_uv_standby(void)
{
    U8 mu8_return = 0;

    if( F_IceFull == SET )
    {
        /*..hui [23-5-31오후 4:04:19] 만빙 아님 -> 만빙으로 전환 시..*/
        if( bit_uv_ice_full_state == CLEAR )
        {
            bit_uv_ice_full_state = SET;
            bit_ice_tray_uv_op_1 = SET;
        }
        else{}

        /*..hui [23-5-31오후 4:04:34] 만빙되고나서 트레이가 탈빙 위치로 이동 완료하면..*/
        if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
        {
            bit_ice_tray_uv_op_2 = bit_ice_tray_uv_op_1;
        }
        else{}
    }
    else
    {
        bit_uv_ice_full_state = CLEAR;
        bit_ice_tray_uv_op_1 = CLEAR;
        bit_ice_tray_uv_op_2 = CLEAR;
    }

    if( bit_ice_tray_uv_op_1 == SET && bit_ice_tray_uv_op_2 == SET && gu8_tray_uv_throw_count_one_day < ICE_TRAY_UV_MAX_OPERATION_PER_ONE_DAY )
    {
        initial_ice_tray_uv_timer();
        bit_ice_tray_uv_op_1 = CLEAR;
        bit_ice_tray_uv_op_2 = CLEAR;
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_tray_uv(void)
{
    bit_ice_tray_1_2_uv_start = SET;
    initial_ice_tray_uv_timer();


    gu8_tray_uv_throw_count_one_day++;

    if( gu8_tray_uv_throw_count_one_day >= ICE_TRAY_UV_MAX_OPERATION_PER_ONE_DAY )
    {
        gu8_tray_uv_throw_count_one_day = ICE_TRAY_UV_MAX_OPERATION_PER_ONE_DAY;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_ice_tray_uv(void)
{
    bit_ice_tray_1_2_uv_start = CLEAR;
    initial_ice_tray_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tray_uv_timer(void)
{
    gu16_ice_tray_1_2_uv_operation_timer_sec = 0;
    gu8_ice_tray_1_2_uv_operation_timer_min = 0;
    gu16_ice_tray_1_2_uv_operation_timer_hour = 0;

    gu16_ice_tray_1_2_uv_standby_timer_sec = 0;
    gu16_ice_tray_1_2_uv_standby_timer_min = 0;
    gu16_ice_tray_1_2_uv_standby_timer_hour = 0;

    //gu16_ice_tray_uv_24_hour_timer_sec = 0;
    //gu16_ice_tray_uv_24_hour_timer_min = 0;
    //gu16_ice_tray_uv_24_hour_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_ice_tray_24_hour_timer(void)
{
    gu16_ice_tray_uv_24_hour_timer_sec++;

    if(gu16_ice_tray_uv_24_hour_timer_sec >= 600)
    {
        gu16_ice_tray_uv_24_hour_timer_sec = 0;
        gu16_ice_tray_uv_24_hour_timer_min++;
    }
    else{}

    if(gu16_ice_tray_uv_24_hour_timer_min >= 60)
    {
        gu16_ice_tray_uv_24_hour_timer_min = 0;
        gu16_ice_tray_uv_24_hour_timer_hour++;
    }
    else{}

    if(gu16_ice_tray_uv_24_hour_timer_hour >= 24)
    {
        gu16_ice_tray_uv_24_hour_timer_sec = 0;
        gu16_ice_tray_uv_24_hour_timer_min = 0;
        gu16_ice_tray_uv_24_hour_timer_hour = 0;
        gu8_tray_uv_throw_count_one_day = 0;

        /*..hui [24-2-5오전 10:07:13] 제빙 방향 최대 횟수..*/
        gu8_tray_uv_making_count_one_day = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_tray_uv_making(void)
{
    U8 mu8_out = 0;

    if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
    {
        if( bit_ice_tray_before == CLEAR )
        {
            bit_ice_tray_before = SET;

            gu8_tray_uv_making_count_one_day++;

            if( gu8_tray_uv_making_count_one_day >= 7 )
            {
                gu8_tray_uv_making_count_one_day = 7;
                bit_ice_tray_making_enable = CLEAR;
            }
            else
            {
                /*..hui [24-2-5오전 10:09:37] 횟수 초과, 제빙 중 24시간되어 횟수 초기화됐을때 다음 제빙부터 동작하게 하기위해..*/
                bit_ice_tray_making_enable = SET;
            }
        }
        else{}

        /*..hui [24-2-5오전 9:59:38] 하루 최대 6회..*/
        /*if( u8IceTrayUvOFF == 0 && bit_ice_tray_making_enable == SET )*/
        if( Bit0_Ice_Tray_UV_Tank_Open_Off_State == CLEAR
            && Bit1_Ice_Tray_UV_Ice_Extract_Off_State == CLEAR
            && bit_ice_tray_making_enable == SET )
        {
            gu32_ice_tray_up_max_timer++;

            /*..hui [24-2-5오전 9:59:32] 1회 최대 가동시간 30분..*/
            if( gu32_ice_tray_up_max_timer >= ICE_TRAY_UV_MAKING_MAX_TIME )
            {
                gu32_ice_tray_up_max_timer = ICE_TRAY_UV_MAKING_MAX_TIME;
            }
            else
            {
                mu8_out = SET;
            }
        }
        else{}
    }
    else
    {
        gu32_ice_tray_up_max_timer = 0;
        bit_ice_tray_before = CLEAR;
        bit_ice_tray_making_enable = CLEAR;
    }

    return mu8_out;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



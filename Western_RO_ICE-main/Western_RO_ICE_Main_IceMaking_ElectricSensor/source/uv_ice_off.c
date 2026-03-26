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
#include    "uv_ice_off.h"


U8 uv_ice_off_control(void);
void ice_off_uv_operation_timer(void);
U8 ice_off_uv_standby_timer(void);
void start_ice_off_uv(void);
void initial_ice_off_uv_timer(void);


/***********************************************************************************************************************/

U16 gu16_ice_off_uv_standby_timer_sec;
U16 gu16_ice_off_uv_standby_timer_min;
U16 gu16_ice_off_uv_standby_timer_hour;

U16 gu16_ice_off_uv_operation_timer_sec;
U8 gu8_ice_off_uv_operation_timer_min;

U8 gu8_uv_ice_off_step;
bit bit_ice_off_uv_start;

U16 gu16_uv_ice_off_timer;
/***********************************************************************************************************************/



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_ice_off_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    /*..hui [24-2-8오전 10:23:35] 더미탈빙 완료 전에도 미진행..*/
    /*..hui [24-2-8오전 10:42:29] 제빙 대기중이 아닐 경우에도..*/
    if( F_IceOn == SET
        || F_IceInit == SET
        || gu8IceStep > STATE_0_STANDBY
        || bit_install_flushing_state == SET
        || bit_ice_tank_ster_start == SET
        || Bit2_Ice_Tray_Test_Start == SET
        || gu8_cody_take_off_ice_start == SET
        /*|| F_Tank_Cover_Input == CLEAR )*/
        || bit_uv_tank_input == CLEAR )
    {
        /*..hui [24-2-8오전 10:59:29] 끝낸(취소된) 시점이 트레이가 올라가있는 상태이면 내리고 종료..*/
        if( gu8_uv_ice_off_step >= 5 && gu8_uv_ice_off_step <= 8 )
        {
            if( gu8_ice_system_ok == SET && F_TrayMotorUP == CLEAR && gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )
            {
                down_tray_motor();
            }
            else{}
        }
        else{}

        initial_ice_off_uv_timer();
        gu8_uv_ice_off_step = 0;
        bit_ice_off_uv_start = CLEAR;
        return CLEAR;
    }
    else{}

/********************************************************************************************/
/********************************************************************************************/
    switch( gu8_uv_ice_off_step )
    {
        case 0 :

            mu8_finish = ice_off_uv_standby_timer();

            if(mu8_finish == SET)
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
                start_ice_off_uv();
            }
            else{}

        break;

        case 1 :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = 3;
                    }
                    else{}
                }
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = 3;
            }

        break;

        case 2 :

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case 3 :

             /*..hui [24-2-7오후 5:48:06] 탈빙 방향 2시간 가동..*/
            if( bit_ice_off_uv_start == SET )
            {
                /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                /*if( u8IceTankUvOFF == 0 )*/
                if( Bit0_Tank_Open_UV_Off_State == CLEAR && Bit1_Ice_Extract_UV_Off_State == CLEAR )
                {
                    ice_off_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }

        break;

        case 4 :

            mu8_finish = ice_off_uv_standby_timer();

            if(mu8_finish == SET)
            {
                gu8_uv_ice_off_step++;
                start_ice_off_uv();
            }
            else{}

        break;

        case 5 :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorDOWN == CLEAR )
                {
                    /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
                    up_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = 7;
                    }
                    else{}
                }
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = 7;
            }

        break;

        case 6 :

            /*..hui [23-7-5오후 7:37:03] 트레이 제빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case 7 :

            /*..hui [24-2-7오후 5:52:12] 제빙 방향 2시간 가동..*/
            if( bit_ice_off_uv_start == SET )
            {
                /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                /*if( u8IceTankUvOFF == 0 )*/
                if( Bit0_Tank_Open_UV_Off_State == CLEAR && Bit1_Ice_Extract_UV_Off_State == CLEAR )
                {
                    ice_off_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                /*gu8_uv_ice_off_step = 0;*/
                gu8_uv_ice_off_step++;
            }

        break;

        case 8 :

            /*..hui [23-8-24오후 2:21:23] 트레이 재시도 중이거나 에러일 경우..*/
            if( gu8_ice_system_ok == SET )
            {
                if( F_TrayMotorUP == CLEAR )
                {
                    /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
                    down_tray_motor();
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else
                {
                    gu16_uv_ice_off_timer++;

                    if( gu16_uv_ice_off_timer >= 600 )
                    {
                        gu16_uv_ice_off_timer = 0;
                        gu8_uv_ice_off_step = 10;
                    }
                    else{}
                }
            }
            else
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step = 10;
            }

        break;

        case 9 :

            /*..hui [23-7-5오후 7:41:30] 트레이 탈빙 방향 이동..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW )
            {
                gu16_uv_ice_off_timer = 0;
                gu8_uv_ice_off_step++;
            }
            else
            {
                gu16_uv_ice_off_timer++;

                /*..hui [23-8-16오후 1:12:24] 트레이 이동 최대 시간 1분..*/
                if( gu16_uv_ice_off_timer >= 600 )
                {
                    gu16_uv_ice_off_timer = 0;
                    gu8_uv_ice_off_step++;
                }
                else{}
            }

        break;

        case 10 :

            /*..hui [24-2-8오전 10:27:18] 종료.. 다시 처음부터..*/
            gu16_uv_ice_off_timer = 0;
            gu8_uv_ice_off_step = 0;
            initial_ice_off_uv_timer();

        break;


        default :

            gu16_uv_ice_off_timer = 0;
            gu8_uv_ice_off_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_off_uv_operation_timer(void)
{
    gu16_ice_off_uv_operation_timer_sec++;

    if(gu16_ice_off_uv_operation_timer_sec >= 600)
    {
        gu16_ice_off_uv_operation_timer_sec = 0;
        gu8_ice_off_uv_operation_timer_min++;
    }
    else{}

    if(gu8_ice_off_uv_operation_timer_min >= UV_ICE_OFF_OPERATION_TIME_MIN)
    {
        bit_ice_off_uv_start = CLEAR;
        initial_ice_off_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_off_uv_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_ice_off_uv_standby_timer_sec++;

    if(gu16_ice_off_uv_standby_timer_sec >= 600)
    {
        gu16_ice_off_uv_standby_timer_sec = 0;
        gu16_ice_off_uv_standby_timer_min++;
    }
    else{}

    if(gu16_ice_off_uv_standby_timer_min >= 60)
    {
        gu16_ice_off_uv_standby_timer_min = 0;
        gu16_ice_off_uv_standby_timer_hour++;
    }
    else{}

    if( gu16_ice_off_uv_standby_timer_hour >= 10 )
    {
        initial_ice_off_uv_timer();
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_off_uv(void)
{
    bit_ice_off_uv_start = SET;
    initial_ice_off_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_off_uv_timer(void)
{
    gu16_ice_off_uv_operation_timer_sec = 0;
    gu8_ice_off_uv_operation_timer_min = 0;

    gu16_ice_off_uv_standby_timer_sec = 0;
    gu16_ice_off_uv_standby_timer_min = 0;
    gu16_ice_off_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



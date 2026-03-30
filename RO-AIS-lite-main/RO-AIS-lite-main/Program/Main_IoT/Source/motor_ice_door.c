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
#include    "motor_ice_door.h"

void motor_ice_door_output(void);
void ice_door_close_24_hour(void);
U8 finish_ice_setting(void);


bit F_DoorCW;                    // 살균 후 ICE Door Reset
U16 gu16StepMotor2;
bit F_DoorCW;                    // 살균 후 ICE Door Reset

U16 gu16IceDoorCloseTimer_Min = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceDoorCloseTimer_Hour = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceDoorCloseResetTimer = 0;
bit F_IceDoorClose;        /* 아이스 도어 닫힘 */

bit bit_ice_off_door_close;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : StepMotor
// 개요       : 스텝모터 구동 Door 3msec cycle
//----------------------------------------------------------------------------
// 기능       :
//              ICE Door 열림 닫힘
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void motor_ice_door_output(void)
{
    //======================================================// Ice Door 전환
    if(F_IceOpen == SET)                                       // 열림
    {
        if(F_DoorCW != SET)
        {
            F_DoorCW=1;
        }
        else{}

        if(gu16StepMotor2 < STEP_ANGLE2)
        {
            gu16StepMotor2++;
            //gu8ErrDoor = 30;
        }
        else
        {
            gu16StepMotor2 = STEP_ANGLE2;
            pSTEP_MOTOR_ICE_DOOR_1 = 0;
            pSTEP_MOTOR_ICE_DOOR_2 = 0;
            pSTEP_MOTOR_ICE_DOOR_3 = 0;
            pSTEP_MOTOR_ICE_DOOR_4 = 0;

            if(F_Ice != SET)
            {
                F_IceOpen = 0;              // Door 열림 완료 후 Off
            }
            else{}
        }
    }
    else                                                  // 닫힘
    {
        if(F_DoorCW == SET)
        {
            gu16StepMotor2 = STEP_ANGLE2;
            F_DoorCW = 0;
        }
        else{}

        if(gu16StepMotor2 > 0)
        {
            if(gu8IceClose == 0)
            {
                gu16StepMotor2--;
            }
            else{}

            //gu8ErrDoor = 30;
        }
        else
        {
            //gu8ErrDoor=30;

            gu16StepMotor2=0;
            pSTEP_MOTOR_ICE_DOOR_1 = 0;
            pSTEP_MOTOR_ICE_DOOR_2 = 0;
            pSTEP_MOTOR_ICE_DOOR_3 = 0;
            pSTEP_MOTOR_ICE_DOOR_4 = 0;
        }
    }

    if(gu16StepMotor2 == 0 || gu16StepMotor2 == STEP_ANGLE2)
    {
        pSTEP_MOTOR_ICE_DOOR_1 = 0;
        pSTEP_MOTOR_ICE_DOOR_2 = 0;
        pSTEP_MOTOR_ICE_DOOR_3 = 0;
        pSTEP_MOTOR_ICE_DOOR_4 = 0;
    }
    else
    {
        switch(gu16StepMotor2 % 8)
        {
            case 0 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 1;
                    pSTEP_MOTOR_ICE_DOOR_2 = 0;
                    pSTEP_MOTOR_ICE_DOOR_3 = 0;
                    pSTEP_MOTOR_ICE_DOOR_4 = 0;

                    break;

            case 1 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 1;
                    pSTEP_MOTOR_ICE_DOOR_2 = 0;
                    pSTEP_MOTOR_ICE_DOOR_3 = 0;
                    pSTEP_MOTOR_ICE_DOOR_4 = 1;

                    break;

            case 2 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 0;
                    pSTEP_MOTOR_ICE_DOOR_2 = 0;
                    pSTEP_MOTOR_ICE_DOOR_3 = 0;
                    pSTEP_MOTOR_ICE_DOOR_4 = 1;

                    break;

            case 3 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 0;
                    pSTEP_MOTOR_ICE_DOOR_2 = 0;
                    pSTEP_MOTOR_ICE_DOOR_3 = 1;
                    pSTEP_MOTOR_ICE_DOOR_4 = 1;

                    break;

            case 4 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 0;
                    pSTEP_MOTOR_ICE_DOOR_2 = 0;
                    pSTEP_MOTOR_ICE_DOOR_3 = 1;
                    pSTEP_MOTOR_ICE_DOOR_4 = 0;

                    break;

            case 5 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 0;
                    pSTEP_MOTOR_ICE_DOOR_2 = 1;
                    pSTEP_MOTOR_ICE_DOOR_3 = 1;
                    pSTEP_MOTOR_ICE_DOOR_4 = 0;

                    break;

            case 6 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 0;
                    pSTEP_MOTOR_ICE_DOOR_2 = 1;
                    pSTEP_MOTOR_ICE_DOOR_3 = 0;
                    pSTEP_MOTOR_ICE_DOOR_4 = 0;

                    break;

            case 7 :

                    pSTEP_MOTOR_ICE_DOOR_1 = 1;
                    pSTEP_MOTOR_ICE_DOOR_2 = 1;
                    pSTEP_MOTOR_ICE_DOOR_3 = 0;
                    pSTEP_MOTOR_ICE_DOOR_4 = 0;

                    break;

            default:

                break;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_door_close_24_hour(void)
{
    U16 mu16_forced_close_time_min = 0;
    U16 mu16_forced_close_time_hour = 0;
    U8 mu8_return = 0;

    //====================================================
    /* 아이스 도어 주기적으로 닫는 로직( 24시간 기준으로 반복 )
     * 아이스 도어가 강제로 열린 경우를 가정해서 24시간 기준으로 닫아 준다.*/

    if( F_LineTest == SET )
    {
        /*..hui [18-1-23오후 2:29:46] 테스트 모드시 60초..*/
        mu16_forced_close_time_min = 600;
        /*..hui [18-1-23오후 2:29:52] 테스트 모드시 1분..*/
        mu16_forced_close_time_hour = 5;
    }
    else
    {
        /*..hui [18-1-23오후 2:29:03] 일반 모드시 60분..*/
        mu16_forced_close_time_min = 36000;
        /*..hui [18-1-23오후 2:29:09] 일반 모드시 24시간..*/
        mu16_forced_close_time_hour = 24;
    }

    mu8_return = finish_ice_setting();

    if( mu8_return == SET )
    {
        F_IceDoorClose = SET;
    }
    else{}

    if( F_Ice == SET )
    {
        gu16IceDoorCloseTimer_Min = 0;
        gu16IceDoorCloseTimer_Hour = 0;
    }
    else{}

    /*..hui [18-1-23오후 2:12:10] 60분 타이머..*/
    gu16IceDoorCloseTimer_Min++;

    if(gu16IceDoorCloseTimer_Min >= mu16_forced_close_time_min)
    {
        gu16IceDoorCloseTimer_Min = 0;
        gu16IceDoorCloseTimer_Hour++;
    }
    else{}

    /*..hui [18-1-23오후 2:12:15] 24시간 타이머..*/
    if(gu16IceDoorCloseTimer_Hour >= mu16_forced_close_time_hour)
    {
        F_IceDoorClose = SET;
        gu16IceDoorCloseTimer_Hour = 0;
    }
    else{}

    if( F_IceDoorClose == SET )
    {
        F_IceDoorClose = CLEAR;

        gu16IceDoorCloseTimer_Min = 0;
        gu16IceDoorCloseTimer_Hour = 0;

        gu16IceDoorCloseResetTimer = 70;
        gu16StepMotor2 = STEP_ANGLE2;
    }
    else{}

    /*..hui [18-1-23오후 2:44:04] 아이스도어 강제 CLOSE중에 얼음 추출할경우 FULL OPEN..*/
    if(gu16IceDoorCloseResetTimer > 0)
    {
        gu16IceDoorCloseResetTimer--;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 finish_ice_setting(void)
{
    U8 mu8_return = 0;

    if(bit_ice_off_door_close == SET)
    {
        //if(gu8_function_depth != LCD_MENU_DEPTH_TWO)
        //{
        //    bit_ice_off_door_close = CLEAR;
        //   mu8_return = SET;
        //}
        //else{}
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




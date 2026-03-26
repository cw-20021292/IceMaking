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
#include    "uv_ice_tank_front.h"




/***********************************************************************************************************************/
TYPE_BYTE          U8IceTankFrontUvONB;
#define            u8IceTankFrontUvON                                   U8IceTankFrontUvONB.byte
#define            Bit0_ITF_Auto_UV_On_State                            U8IceTankFrontUvONB.Bit.b0
#define            Bit1_ITF_UV_Ice_Tank_Clean_On_State                  U8IceTankFrontUvONB.Bit.b1
#define            Bit2_ITF_UV_Ice_Off_On_State                         U8IceTankFrontUvONB.Bit.b2
#define            Bit3_ITF_UV_Fault_Test_On_State                      U8IceTankFrontUvONB.Bit.b3




TYPE_BYTE          U8IceTankFrontUvOFFB;
#define            u8IceTankFrontUvOFF                                  U8IceTankFrontUvOFFB.byte
#define            Bit0_ITF_Tank_Open_UV_Off_State                      U8IceTankFrontUvOFFB.Bit.b0
#define            Bit1_ITF_Ice_Extract_UV_Off_State                    U8IceTankFrontUvOFFB.Bit.b1
#define            Bit2_ITF_Ice_Tank_UV_Retry_3S_Off_State              U8IceTankFrontUvOFFB.Bit.b2
#define            Bit3_ITF_Ice_Tank_UV_Error_Off_State                 U8IceTankFrontUvOFFB.Bit.b3


/***********************************************************************************************************************/


bit bit_uv_ice_tank_front_out;

U8 gu8_uv_ice_tank_front_retry_timer;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_tank_front_uv(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}


    /*..hui [24-2-14오후 3:41:14] 자동살균.. 아이스트레이 UV 동작할때.. 단 횟수는 다름..*/
    if( Bit0_Ice_Tray_1_2_UV_On_State == SET )
    {
        if( bit_ice_tray_1_2_uv_start == SET )
        {
            /*..hui [24-2-14오후 3:39:04] 탈빙위치 UV 살균.. 아이스트레이 할때 같이.. ..*/
            /*..hui [24-2-14오후 3:39:10] 단 최대 살균횟수는 하루 1회..*/
            /*if( gu8_tray_uv_throw_count_one_day <= 1 )*/
            if( gu8_tray_uv_throw_count_one_day <= 1 )
            {
                Bit0_ITF_Auto_UV_On_State = SET;
            }
            else
            {
                Bit0_ITF_Auto_UV_On_State = CLEAR;
            }
        }
        else
        {
            /*..hui [24-2-14오후 3:40:32] 제빙중 UV 살균.. 아이스트레이 할때 같이..*/
            /*..hui [24-2-14오후 3:40:40] 단 최대 살균횟수는 하루 3회..*/
            if( gu8_uv_ice_tray_step == 0 )
            {
                /*if( gu8_tray_uv_making_count_one_day <= 3 )*/
                if( gu8_tray_uv_making_count_one_day <= 3 )
                {
                    Bit0_ITF_Auto_UV_On_State = SET;
                }
                else
                {
                    Bit0_ITF_Auto_UV_On_State = CLEAR;
                }
            }
            else
            {
                Bit0_ITF_Auto_UV_On_State = CLEAR;
            }

        }
    }
    else
    {
        Bit0_ITF_Auto_UV_On_State = CLEAR;
    }



    /*..hui [24-1-26오후 2:56:06] 얼음탱크 세척 중.. 아이스트레이 세척할때 제빙 방향에서 UV 조사..*/
    /*..hui [24-1-26오후 2:56:11] 최대 시간은 30분으로..*/
    /*..hui [24-2-2오후 2:23:55] 얼음탱크 뒤쪽 UV 출력할때 같이 출력..*/
    Bit1_ITF_UV_Ice_Tank_Clean_On_State = Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State;


    /*..hui [24-2-14오후 3:47:31] 얼음 OFF 했을때 UV 살균..*/
    /*..hui [24-2-14오후 3:47:43] 아이스탱크 동작할떄 동일하게 동작..*/
    /*..hui [24-2-14오후 3:47:51] 단, 1시간씩만 동작..*/
    if( Bit2_Ice_Tank_UV_Ice_Off_On_State == SET )
    {
        if( gu8_uv_ice_off_step == 3 || gu8_uv_ice_off_step == 7 )
        {
            /*..hui [24-5-28오후 3:07:14] 조건 추가....*/
            /*..hui [24-5-28오후 3:07:31] 60분 ON하고.. 120분될때 타이머가 초기화되면서 0.1초 켜질수있음..*/
            if( bit_ice_off_uv_start == SET )
            {
                if( gu8_ice_off_uv_operation_timer_min < 60 )
                {
                    Bit2_ITF_UV_Ice_Off_On_State = SET;
                }
                else
                {
                    Bit2_ITF_UV_Ice_Off_On_State = CLEAR;
                }
            }
            else
            {
                Bit2_ITF_UV_Ice_Off_On_State = CLEAR;
            }
        }
        else
        {
            Bit2_ITF_UV_Ice_Off_On_State = CLEAR;
        }
    }
    else
    {
        Bit2_ITF_UV_Ice_Off_On_State = CLEAR;
    }

    /*..hui [24-11-28오전 10:26:11] 전원 인가 후 1분 30초 동안 계속 켜서 고장 확인..*/
    /*..hui [24-11-28오전 10:26:47] UV 교체 후 정상 확인하려면 6시간동안 기다려야하는 문제..*/
    /*..hui [24-11-28오전 10:27:03] 서비스기획팀 요청~~~..*/
    /*..hui [24-11-28오후 1:19:16] 얼음 탱크 UV 테스트중 동일하게 동작..*/
    if( bit_uv_fault_test_start == SET )
    {
        Bit3_ITF_UV_Fault_Test_On_State = Bit3_Ice_Tank_UV_Fault_Test_On_State;
    }
    else
    {
        Bit3_ITF_UV_Fault_Test_On_State = CLEAR;
    }

    /***********************************************************************************************/
    /*..hui [19-10-24오후 8:04:35] 탱크 커버 열렸을경우 정지..*/
    /*..hui [20-2-19오후 5:59:39] 탱크 커버 열리면 즉시 꺼지도록 커버 입력부 분리..*/
    /*..hui [20-2-19오후 5:59:45] 코디 건강을위해.....*/
    Bit0_ITF_Tank_Open_UV_Off_State = ~bit_uv_tank_input;

    /*..hui [19-10-24오후 8:04:54] 얼음 추출 시 정지..*/
    /*Bit1_Ice_Extract_UV_Off_State = F_Ice;*/
    /*..hui [20-2-19오후 7:31:38] 얼음 추출구 열릴때 끄고 완전히 닫힌 후 켜도록 수정..*/
    if( F_Ice == SET )
    {
        Bit1_ITF_Ice_Extract_UV_Off_State = F_Ice;
    }
    else
    {
        if( gu16StepMotor2 == 0 )
        {
            Bit1_ITF_Ice_Extract_UV_Off_State = CLEAR;
        }
        else{}
    }

    if( bit_ice_tank_front_uv_retry_stop == SET )
    {
        gu8_uv_ice_tank_front_retry_timer++;

        if( gu8_uv_ice_tank_front_retry_timer >= 30 )
        {
            bit_ice_tank_front_uv_retry_stop = CLEAR;
            gu8_uv_ice_tank_front_retry_timer = 0;
            Bit2_ITF_Ice_Tank_UV_Retry_3S_Off_State = CLEAR;
        }
        else
        {
            Bit2_ITF_Ice_Tank_UV_Retry_3S_Off_State = SET;
        }
    }
    else
    {
        gu8_uv_ice_tank_front_retry_timer = 0;
        Bit2_ITF_Ice_Tank_UV_Retry_3S_Off_State = CLEAR;
    }

    Bit3_ITF_Ice_Tank_UV_Error_Off_State = Bit26_Ice_Tank_3_Front_UV_Error__E79;



/***********************************************************************************************/
    if( u8IceTankFrontUvOFF > 0 )
    {
        pUV_LED_ICE_TANK_3_FRONT = CLEAR;                  /*off*/
        Bit5_Ice_Tank_Front_UV_12V_Out_State = CLEAR;
        bit_uv_ice_tank_front_out = CLEAR;
    }
    else
    {
        if( u8IceTankFrontUvON > 0 )
        {
            pUV_LED_ICE_TANK_3_FRONT = SET;                 /*on*/
            Bit5_Ice_Tank_Front_UV_12V_Out_State = SET;
            bit_uv_ice_tank_front_out = SET;
        }
        else
        {
            pUV_LED_ICE_TANK_3_FRONT = CLEAR;              /*off*/
            Bit5_Ice_Tank_Front_UV_12V_Out_State = CLEAR;
            bit_uv_ice_tank_front_out = CLEAR;
        }
    }
/***********************************************************************************************/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



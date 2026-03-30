/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Mode_Control.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M2_Mode_Control.h"

void Mode_Control(void);
void cold_temp_level_decision(void);
void hot_temp_level_decision(void);

void System(void);
void water_select_return_timer_control( U8 mu8_flag );
void cody_test_mode(void);
void stop_ice_cody_mode(void);
void cold_level_setting_hi(void);
void cold_level_setting_lo(void);

void ice_durable_test(void);

bit F_6HourNoUse;                 // 미사용 절전
//----------------------------------------------------// 냉수,온수
U8 gu8ColdTemp;
U8 gu8HotTemp;
//----------------------------------------------------// Heater
U8 gu8HotH2_On;
U8 gu8HotH3_On;
U8 gu8HotH2_Off;
U8 gu8HotH3_Off;




//----------------------------------------------------// Test
U8 gu8TestGo;
U8 gu8TestTemp;
U8 gu8VersionCount;
U8 gu8VersionTime;
//U16 gu16TestTime;

bit F_Reset;
U16 ucErrOvice_Valve;
U16 ucErrOVice_Heater;
U16 ucTime_10min_cycle;
U16 ucErrOvice_Time;
// 20130315 NFC TEST MODE에서 무부하 전류 5초 → 8초 변경




//U16 gu16MeltTime;

bit F_TrayCut;
bit F_NoSelectBar;
bit F_Melt;
bit F_Safety_Routine;
bit F_TrayStop;                       // 토출중 트레이이동 정지
bit F_Tray_up_moving_retry_state;
bit F_Trayretry1;
bit F_Trayretryfinal;



TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


//U8 gu8_pre_water_out_state;

//U8 gu8_recovery_water_out_state;


//U8 gu8_water_out_mode;

//bit F_WaterOut_Change_State;

//bit F_WaterOut_Recover_Enable;


//U16 gu16DummyIce;
//U16 gu16DummyIceDelay;
//U16 gu16IceStopTime; // 보냉


//----------------------------------------------------// Altitude
U8 gu8AltitudeTime;
U8 gu8AltitudeStep;



U16 gu16Water_Extract_Timer;
U16	gu16Water_continue_Extract_timer;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Mode_Control(void)
{
    model_select();

    uart_test_mode_decision();

    cold_temp_level_decision();
    hot_temp_level_decision();

    System();

    water_extract_control();
    setting_my_cup();

    /*..hui [20-3-5오후 2:57:22] 온수 첫잔 드레인 자동으로 되도록 개선.........*/
    /////hot_water_filling_control();
    /////hot_water_extract_control();

    /*..hui [20-4-9오전 9:41:09] 온수 과열에러 발생시 히터 쿨링..*/
    //////hot_cooling_control();

    /*..hui [23-5-9오후 4:38:14] 추출 시간 보상.. 추출 물량 계산..*/
	/*.. sean [25-02-11] wifi 추출량 확인 위해 추가 ..*/
    calc_waterout_time();

    logic_decision();

    /*..hui [19-11-1오후 7:31:38] 전기 사용량 계산 추가..*/
    /////calculate_electric_rate();

    /*..hui [18-1-14오후 5:50:58] 순환배수 기능 추가..*/
    auto_drain_control();

    /*..hui [17-12-29오후 1:22:03] 서버스 점검..*/
    //service_check();

    /*..hui [18-1-23오후 2:33:06] 24시간 마다 아이스도어 CLOSE..*/
    ice_door_close_24_hour();

    /*..hui [19-7-25오후 8:27:11] 절전진입시 만빙 후 6시간 제빙 정지..*/
    /*check_ice_stop();*/

    /*..hui [19-10-23오후 8:26:29] 서비스체크 추가..*/
    service_check();

    /*..hui [20-1-8오후 4:22:39] 코디 테스트 모드..*/
    cody_test_mode();
	
    /*..sean [ 24-10-04 ] 시간 설정 추가 ..*/
    time_setting();

    /*..sean [24-10-24] WIFI 관련 제어 추가..*/
    wifi_operation_control();
    wifi_smart_control();
    wifi_time_setting();

    water_durable_test();

    /*..hui [23-8-17오후 4:25:47] 미사용 절전 모드..*/
    //no_use_save_control();
    power_save_mode();
    ice_durable_test();      
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp_level_decision(void)
{
    /*..hui [23-3-3오후 3:28:59] 냉수센서 에러 최초 읽기전까지는 1단..*/
    if( bit_cold_read_finish == CLEAR )
    {
        gu8ColdTemp = TEMP_DISPLAY_0_INIT;
        return;
    }
    else{}

    /*..hui [19-12-18오후 10:50:28] 냉수센서 에러시 3단으로 고정..*/
    if( Bit10_Cold_Temp_Open_Short_Error == SET )
    {
        gu8ColdTemp = TEMP_DISPLAY_0_INIT;
        return;
    }
    else{}

    /*..hui [20-1-6오후 9:08:55] 냉수 설정 해제 시 1단..*/
    if( F_Cold_Enable == CLEAR )
    {
        gu8ColdTemp = TEMP_DISPLAY_0_INIT;
        return;
    }
    else{}

    #if 0
    if( gu8_cold_setting_level == COLD_TEMP_LOW )
    {
        cold_level_setting_hi();
    }
    else
    {
        cold_level_setting_lo();
    }
    #endif

    if( gu8_cold_setting_level == COLD_TEMP_LOW )
    {
        cold_level_setting_lo();
    }
    else
    {
        cold_level_setting_hi();
    }
    //-------------------------------------------------------------------------
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_level_setting_hi(void)
{
    switch( gu8ColdTemp )
    {
        case TEMP_DISPLAY_0_INIT :
        case TEMP_DISPLAY_1_LOW :

                /*..hui [20-1-20오후 3:16:33] 냉수온도 10도 이하..*/
                if( gu8_Cold_Temperature_One_Degree <= 10 )
                { 
                    gu8ColdTemp = TEMP_DISPLAY_2_MID;
                }
                else
                {
                    gu8ColdTemp = TEMP_DISPLAY_1_LOW;
                }

                break;

        case TEMP_DISPLAY_2_MID :

                /*..hui [20-1-20오후 3:16:42] 냉수 온도 13도 이상..*/
                if(gu8_Cold_Temperature_One_Degree >= 13)
                {
                    gu8ColdTemp = TEMP_DISPLAY_1_LOW;
                }
                /*else if( gu8_Cold_Temperature_One_Degree <= 6 )*/
                /*..hui [23-5-22오전 11:32:51] 지연가동했을때 도달 못하는 현상 개선..*/
                else if( gu8_Cold_Temperature_One_Degree <= 7 )
                {
                    /*..hui [23-2-6오후 5:03:53] 냉수온도 6도 이하..*/
                    gu8ColdTemp = TEMP_DISPLAY_3_HIGH;
                }
                else{}

                break;

        case TEMP_DISPLAY_3_HIGH :

                if( gu8_Cold_Temperature_One_Degree >= 10 )
                {
                    gu8ColdTemp = TEMP_DISPLAY_2_MID;
                }
                else{}

                break;

        default :

                gu8ColdTemp = TEMP_DISPLAY_1_LOW;

                break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_level_setting_lo(void)
{

    switch( gu8ColdTemp )
    {
        case TEMP_DISPLAY_0_INIT :
        case TEMP_DISPLAY_1_LOW :

                /*..hui [20-1-20오후 3:16:33] 냉수온도 14도 이하..*/
                if( gu8_Cold_Temperature_One_Degree <= 14 )
                {
                    gu8ColdTemp = TEMP_DISPLAY_2_MID;
                }
                else
                {
                    gu8ColdTemp = TEMP_DISPLAY_1_LOW;
                }

                break;

        case TEMP_DISPLAY_2_MID :

                /*..hui [20-1-20오후 3:16:42] 냉수 온도 18도 이상..*/
                if(gu8_Cold_Temperature_One_Degree >= 18)
                {
                    gu8ColdTemp = TEMP_DISPLAY_1_LOW;
                }
                /*else if( gu8_Cold_Temperature_One_Degree <= 10 )*/
                /*..hui [23-5-22오전 11:32:51] 지연가동했을때 도달 못하는 현상 개선..*/
                else if( gu8_Cold_Temperature_One_Degree <= 11 )
                {
                    /*..hui [23-2-6오후 5:03:53] 냉수온도 10도 이하..*/
                    gu8ColdTemp = TEMP_DISPLAY_3_HIGH;
                }
                else{}

                break;

        case TEMP_DISPLAY_3_HIGH :

                if( gu8_Cold_Temperature_One_Degree >= 14 )
                {
                    gu8ColdTemp = TEMP_DISPLAY_2_MID;
                }
                else{}

                break;

        default :

                gu8ColdTemp = TEMP_DISPLAY_1_LOW;

                break;
    }

}









/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_temp_level_decision(void)
{
    /*..hui [23-8-17오후 4:45:12] 미사용 절전시 표시 사양..*/
    if( bit_9_hour_no_use_start == SET )
    {
        switch( gu8AltitudeStep )
        {
            case ALTITUDE_1_MODE_HIGH :
                    //gu8HotH2_On = 73;      // 1모드
                    gu8HotH2_On = 63;      // 1모드
                    //gu8HotH2_Off = 60;
                    gu8HotH2_Off = 50;

                    gu8HotH3_On = 90;
                    gu8HotH3_Off = 63;
                    //gu8HotH3_Off = 73;
            break;

            case ALTITUDE_2_MODE_MID :
                    //gu8HotH2_On = 73;      // 2모드
                    gu8HotH2_On = 63;      // 2모드
                    //gu8HotH2_Off = 60;
                    gu8HotH2_Off = 50;

                    gu8HotH3_On = 88;
                    gu8HotH3_Off = 63;
                    //gu8HotH3_Off = 73;
            break;

            case ALTITUDE_3_MODE_LOW :
                    //gu8HotH2_On = 73;      // 3모드
                    gu8HotH2_On = 63;      // 3모드
                    //gu8HotH2_Off = 60;
                    gu8HotH2_Off = 50;

                    gu8HotH3_On = 85;
                    //gu8HotH3_Off = 73;
                    gu8HotH3_Off = 63;
            break;

            default :

                gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;

                break;
        }
    }
    else
    {
        switch( gu8AltitudeStep )
        {
            case ALTITUDE_1_MODE_HIGH :
                    gu8HotH2_On = 80;      // 1모드
                    gu8HotH2_Off = 70;

                    gu8HotH3_On = 90;
                    gu8HotH3_Off = 80;
            break;

            case ALTITUDE_2_MODE_MID :
                    gu8HotH2_On = 78;      // 2모드
                    gu8HotH2_Off = 68;

                    gu8HotH3_On = 88;
                    gu8HotH3_Off = 78;
            break;

            case ALTITUDE_3_MODE_LOW :
                    gu8HotH2_On = 74;      // 3모드
                    gu8HotH2_Off = 60;

                    gu8HotH3_On = 85;
                    gu8HotH3_Off = 74;
            break;

            default :

                gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;

                break;
        }
    }


    /*..hui [23-3-3오후 3:28:59] 온수센서 에러 최초 읽기전까지는 1단..*/
    if( bit_hot_read_finish == CLEAR )
    {
        gu8HotTemp = TEMP_DISPLAY_0_INIT;
        return;
    }
    else{}

    /*if( Bit1_Room_OverHeat_Error == SET )*/
    if( Bit0_Hot_Tank_Temp_Open_Short_Error == SET )
    {
        gu8HotTemp = TEMP_DISPLAY_1_LOW;
        return;
    }
    else{}

    /*..hui [20-1-6오후 9:08:55] 온수 설정 해제 시 1단..*/
    if( F_Hot_Enable == CLEAR )
    {
        gu8HotTemp = TEMP_DISPLAY_1_LOW;
        return;
    }
    else{}


    switch( gu8HotTemp )
    {
        case TEMP_DISPLAY_0_INIT :
        case TEMP_DISPLAY_1_LOW :

                if( gu8_Hot_Tank_Temperature_One_Degree >= gu8HotH2_On )
                {
                    gu8HotTemp = TEMP_DISPLAY_2_MID;
                }
                else
                {
                    gu8HotTemp = TEMP_DISPLAY_1_LOW;
                }

                break;

        case TEMP_DISPLAY_2_MID :

                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8HotH2_Off )
                {
                    gu8HotTemp = TEMP_DISPLAY_1_LOW;
                }
                else if( gu8_Hot_Tank_Temperature_One_Degree >= gu8HotH3_On )
                {
                    gu8HotTemp = TEMP_DISPLAY_3_HIGH;
                }
                else{}

                break;

        case TEMP_DISPLAY_3_HIGH :

                if( gu8_Hot_Tank_Temperature_One_Degree <= gu8HotH3_Off )
                {
                    gu8HotTemp = TEMP_DISPLAY_2_MID;
                }
                else{}

                break;

        default :

                gu8HotTemp = TEMP_DISPLAY_1_LOW;
                break;
    }
}






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : System
// 개요       :
//----------------------------------------------------------------------------
// 기능       :
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************

void System(void)
{
    if(gu16IRInterval > 0)
    {
        gu16IRInterval--;            // 만빙검사 주기 15분
    }
    else{}

    if(gu16IRInterval == 0)
    {
        F_IR = SET;
    }
    else{}


    //===================================================// 취침모드시 6시간 제빙정지
    //if(F_Sleep == SET && F_IceFull == SET && F_IceStop != SET)
    //{
    //    F_IceStop = SET;
    //    gu16IceStopTime = ICESTOP_TIME_SIX_HOURS;
    //}
    //else if(F_Sleep != SET || gu16IceStopTime == 0)
    //{
    //    F_IceStop = CLEAR;
    //}
    //else{}


    /*..hui [18-3-6오후 5:17:36] 테스트모드 자동 해제..*/
    //if(gu16TestTime == 0 && F_LineTest == SET)
    //{
    //    F_LineTest = CLEAR;
    //    system_reset();
    //}
    //else{}

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_test_mode(void)
{
    cody_ice_tray_test();
    cody_service();
    cody_takeoff_ice();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void force_take_off_ice(void)
{
    if( F_IceInit == SET )
    {
        /*..hui [20-2-19오후 3:26:02] 더미탈빙 대기 중 또는 진행 중 강제 탈빙하면 더미탈빙 취소..*/
        /*..hui [20-2-19오후 3:26:14] 최인식과 협의 아이스소다 동일..*/
        F_IceInit = CLEAR;
        gu8InitStep = 0;
        gu16IceMakeTime = 0;
        gu16IceHeaterTime = 0;
    }
    else if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
    {
        if( gu16IceMakeTime <= (U16)(gu16_cody_ice_make_time - HEATING_PASS_TIME_THREE_MIN) )
        {
            /*..hui [20-2-19오후 7:48:07] 제빙 시작하고 3분 경과 시 탈빙 단계로 이동..*/
            gu16IceMakeTime = 0;
        }
        else
        {
            /*..hui [20-2-19오후 7:48:19] 제빙 시작 후 3분 이전일 경우 탈빙 없이 즉시 종료..*/
            /*..hui [20-2-19오후 7:48:48] 컴프 가동없이 탈빙하면 화상 및 탈빙히터 고장 위험..*/
            gu16IceMakeTime = 0;
            F_IceHeater = CLEAR;
            /*..hui [20-2-19오후 7:45:46] 탈빙 및 만빙체크없이 즉시 종료..*/
            gu8IceStep = STATE_51_FINISH_ICE_MAKE;
            /*..hui [20-1-29오후 3:53:01] 트레이도 올라가는 중이었으면 내리고..*/
            down_tray_motor();
        }
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_ice_cody_mode(void)
{
    if( F_IceInit == SET )
    {
        /*..hui [20-2-19오후 3:26:02] 더미탈빙 대기 중 또는 진행 중 강제 탈빙하면 더미탈빙 취소..*/
        /*..hui [20-2-19오후 3:26:14] 최인식과 협의 아이스소다 동일..*/
        F_IceInit = CLEAR;
        gu8InitStep = 0;
        gu16IceMakeTime = 0;
        gu16IceHeaterTime = 0;
    }
    else
    {
        if( gu8IceStep != STATE_0_STANDBY )
        {
            if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP
                && gu8IceStep <= STATE_30_CALC_ICE_MAKING_TIME )
            {
                /*..hui [20-1-29오후 3:48:29] 제빙 전단계이면 바로 만빙체크 후 종료..*/
                /*..hui [20-2-19오후 7:46:55] 수정 - 제빙 안들어갔으므로 만빙 체크 없이 즉시 종료..*/
                gu8IceStep = STATE_51_FINISH_ICE_MAKE;
                /*..hui [20-1-29오후 3:53:01] 트레이도 올라가는 중이었으면 내리고..*/
                down_tray_motor();
            }
            else if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
            {
                /*..hui [20-1-29오후 3:48:38] 제빙중이면 제빙 종료 후 탈빙 단계로 이동..*/
                if( gu16IceMakeTime <= (U16)(gu16_cody_ice_make_time - HEATING_PASS_TIME_THREE_MIN) )
                {
                    /*..hui [20-2-19오후 7:48:07] 제빙 시작하고 3분 경과 시 탈빙 단계로 이동..*/
                    gu16IceMakeTime = 0;
                }
                else
                {
                    /*..hui [20-2-19오후 7:48:19] 제빙 시작 후 3분 이전일 경우 탈빙 없이 즉시 종료..*/
                    /*..hui [20-2-19오후 7:48:48] 컴프 가동없이 탈빙하면 화상 및 탈빙히터 고장 위험..*/
                    gu16IceMakeTime = 0;
                    F_IceHeater = CLEAR;
                    /*..hui [20-2-19오후 7:45:46] 탈빙 및 만빙체크없이 즉시 종료..*/
                    gu8IceStep = STATE_51_FINISH_ICE_MAKE;
                    /*..hui [20-1-29오후 3:53:01] 트레이도 올라가는 중이었으면 내리고..*/
                    down_tray_motor();
                }
            }
            else if( gu8IceStep >= STATE_40_ICE_TRAY_MOVE_DOWN
                     && gu8IceStep <= STATE_41_ICE_TAKE_OFF )
            {
                /*..hui [20-1-29오후 3:47:24] 탈빙 이동중이거나 탈빙중일경우 하던거 계속 진행..*/

            }
            else{}
        }
        else{}
    }
}



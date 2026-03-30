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
#include    "service_check.h"



void service_check(void);
void service_check_timer(void);
void service_clear_check(void);

void service_reed_sw_input(void);


U8 gu8_service_reed_on_decision_cnt;
U8 gu8_service_reed_off_decision_cnt;

U16 gu16_service_timer_sec;
U16 gu16_service_timer_min;
U16 gu16_service_timer_hour;
U8 gu8_service_timer_1day;
U8 gu8_service_timer_1day_old;



bit F_Tank_Cover_Input;

bit F_Service_Elaspe_State;

bit bit_tank_reed_read_finish;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void service_check(void)
{
    if(F_FW_Version_Display_Mode == SET)
    {
        /*..hui [19-11-4오후 10:17:53] 서비스 점검 표시 삭제..*/
        /*service_check_timer();*/
        /*service_clear_check();*/
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void service_check_timer(void)
{
    gu16_service_timer_sec++;

    if(gu16_service_timer_sec >= 600)
    {
        gu16_service_timer_sec = 0;
        gu16_service_timer_min++;
    }
    else{}

    if(gu16_service_timer_min >= 60)
    {
        gu16_service_timer_min = 0;
        gu16_service_timer_hour++;
    }
    else{}

    if(gu16_service_timer_hour >= 24)
    {
        gu16_service_timer_hour = 0;
        gu8_service_timer_1day++;
    }
    else{}

    if(gu8_service_timer_1day >= SERVICE_ELAPSE_TIME)
    {
        gu8_service_timer_1day = SERVICE_ELAPSE_TIME;
        F_Service_Elaspe_State = SET;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void service_clear_check(void)
{
    if(F_Tank_Cover_Input == CLEAR)
    {
        gu16_service_timer_sec = 0;
        gu16_service_timer_min = 0;
        gu16_service_timer_hour = 0;
        gu8_service_timer_1day = 0;
        F_Service_Elaspe_State = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void service_reed_sw_input(void)
{
    if( pREED_TANK_COVER == CLEAR )
    {
        gu8_service_reed_off_decision_cnt = 0;
        gu8_service_reed_on_decision_cnt++;

        if( gu8_service_reed_on_decision_cnt >= SERVICE_REED_ON_DETECT_TIME )
        {
            /*..hui [19-1-29오후 3:51:34] 탱크 커버 닫힘..*/
            gu8_service_reed_on_decision_cnt = SERVICE_REED_ON_DETECT_TIME;
            F_Tank_Cover_Input = SET;
            bit_tank_reed_read_finish = SET;
        }
        else{}
    }
    else
    {
        gu8_service_reed_on_decision_cnt = 0;
        gu8_service_reed_off_decision_cnt++;

        if( gu8_service_reed_off_decision_cnt >= SERVICE_REED_OFF_DETECT_TIME )
        {
            /*..hui [19-1-29오후 3:51:38] 탱크 커버 열림..*/
            gu8_service_reed_off_decision_cnt = SERVICE_REED_OFF_DETECT_TIME;
            F_Tank_Cover_Input = CLEAR;
            bit_tank_reed_read_finish = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




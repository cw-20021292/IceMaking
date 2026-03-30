/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "service_input.h"

void service_check_input(void);
U8 gu8_service_check_on_decision_cnt;
U8 gu8_service_check_off_decision_cnt;
bit F_Service_Check_Input;

bit F_Service_First_Check;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 
***********************************************************************************************************************/
void service_check_input(void)
{
#if 0
    if(pSW_SERVICE == CLEAR)
    {
        gu8_service_check_on_decision_cnt = 0;
        gu8_service_check_off_decision_cnt++;

        if( gu8_service_check_off_decision_cnt >= SERVICE_CHECK_INPUT_TIME )
        {
            gu8_service_check_off_decision_cnt = SERVICE_CHECK_INPUT_TIME;
            F_Service_Check_Input = SET;
            F_Service_First_Check = SET;
        }
        else{}
    }
    else
    {
        if( pSW_SERVICE >= SET )
        {
            gu8_service_check_off_decision_cnt = 0;
            gu8_service_check_on_decision_cnt++;
        
            if ( gu8_service_check_on_decision_cnt >= SERVICE_CHECK_INPUT_TIME )
            {
                gu8_service_check_on_decision_cnt = SERVICE_CHECK_INPUT_TIME;
                F_Service_Check_Input = CLEAR;
                F_Service_First_Check = SET;
            }
            else{}
        }
        else{}

    }
#endif
}


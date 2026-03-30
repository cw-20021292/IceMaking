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
#include    "display_fnd_sleep.h"

void sleep_mode_decesion(void);

bit bit_standby_input;
U16 gu16_sleep_timer;
bit bit_sleep_mode_start;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sleep_mode_decesion(void)
{
    if( bit_sleep_mode_enable == CLEAR )
    {
        bit_sleep_mode_start = CLEAR;
        bit_display_sleep_start = CLEAR;
        gu16_display_sleep_timer = 0;

        return;
    }
    else{}

	/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
    gu16_current_time_total = (U16)((U16)gu8_rtc_time_Hour * 100);
    gu16_current_time_total = gu16_current_time_total + gu8_rtc_time_Min;

    gu16_start_time_total = (U16)((U16)gu8_sleep_mode_start_hour * 100);
    gu16_start_time_total = gu16_start_time_total + gu8_sleep_mode_start_minute;

    gu16_finish_time_total = (U16)((U16)gu8_sleep_mode_finish_hour * 100);
    gu16_finish_time_total = gu16_finish_time_total + gu8_sleep_mode_finish_minute;
	
    if( bit_sleep_mode_start == CLEAR )
    {
        if( gu16_start_time_total > gu16_finish_time_total )
        {
            if( gu16_current_time_total >= gu16_start_time_total || gu16_current_time_total < gu16_finish_time_total )
            {
                bit_sleep_mode_start = SET;
                /*..hui [23-6-29오후 2:51:39] 디스플레이 슬립 바로 시작..*/
                /*..hui [23-12-18오전 10:58:17] 메인 화면에서만 진입하도록 변경..*/
                /*..hui [23-12-18오전 10:58:39] 설정모드 진입 -> 에코모드 해제 -> 설정모드에서 바로 진입됨....*/
                if( bit_display_sleep_start != SET && gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    bit_display_sleep_start = SET;
                }
                else{}
            }
            else{}
        }
        else if( gu16_start_time_total < gu16_finish_time_total )
        {
            if( gu16_current_time_total >= gu16_start_time_total && gu16_current_time_total < gu16_finish_time_total )
            {
                bit_sleep_mode_start = SET;
                /*..hui [23-6-29오후 2:51:39] 디스플레이 슬립 바로 시작..*/
                /*..hui [23-12-18오전 10:58:17] 메인 화면에서만 진입하도록 변경..*/
                /*..hui [23-12-18오전 10:58:39] 설정모드 진입 -> 에코모드 해제 -> 설정모드에서 바로 진입됨....*/
                if( bit_display_sleep_start != SET && gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    bit_display_sleep_start = SET;
                }
                else{}
            }
            else{}
        }
        else{}
    }
    else
    {
        if( gu16_start_time_total > gu16_finish_time_total )
        {
            if( gu16_current_time_total < gu16_start_time_total && gu16_current_time_total >= gu16_finish_time_total )
            {
                if( bit_sleep_mode_start == SET )
                {
                    bit_sleep_mode_start = CLEAR;
                    /*..hui [23-6-29오후 2:55:49] 취침모드 들어갔다가 해제될때는 미사용 절전도 해제해야함..*/
                    //power_saving_init();
                    no_use_save_init();
                }
                else{}
            }
            else{}
        }
        else if( gu16_start_time_total < gu16_finish_time_total )
        {
            if( gu16_current_time_total < gu16_start_time_total || gu16_current_time_total >= gu16_finish_time_total )
            {
                if( bit_sleep_mode_start == SET )
                {
                    bit_sleep_mode_start = CLEAR;
                    /*..hui [23-6-29오후 2:55:49] 취침모드 들어갔다가 해제될때는 미사용 절전도 해제해야함..*/
                    //power_saving_init();
                    no_use_save_init();
                }
                else{}
            }
            else{}
        }
        else
        {
            /*..hui [23-10-5오후 1:58:25] 시작시간 종료시간 동일.. 하면 그냥 종료..*/
            if( bit_sleep_mode_start == SET )
            {
                bit_sleep_mode_start = CLEAR;
                /*..hui [23-6-29오후 2:55:49] 취침모드 들어갔다가 해제될때는 미사용 절전도 해제해야함..*/
                //no_use_save_init();
            }
            else{}
        }
    }

    //if( bit_illumi_State == SET )
    if( bit_sleep_mode_start == SET )
    {
        gu16_display_sleep_timer++;

        if( gu16_display_sleep_timer >= DISPLAY_SLEEP_TIME )
        {
            gu16_display_sleep_timer = DISPLAY_SLEEP_TIME;

            /*if( bit_display_sleep_start != SET )*/
            /*..hui [23-12-15오전 10:59:18] 메인화면에서만 진입..*/
            if( bit_display_sleep_start != SET && gu8_Led_Display_Step == LED_Display__MAIN )
            {
                bit_display_sleep_start = SET;
            }
            else{}
        }
        else{}
    }
    else
    {
        if( bit_display_sleep_start == SET )
        {
            bit_display_sleep_start = CLEAR;
            /*..hui [23-6-29오후 2:55:49] 취침모드 들어갔다가 해제될때는 미사용 절전도 해제해야함..*/
            /*power_saving_init();*/
        }
        else{}

        gu16_display_sleep_timer = 0;
    }
	
#if 0
    if(bit_sleep_mode_start == SET)
    {
        /*..hui [23-4-4오후 5:50:10] 물 추출, 얼음 추출시 시간 초기화 추가..*/
        if( bit_standby_input == SET || F_WaterOut == SET || F_Ice == SET )
        {
            bit_standby_input = CLEAR;
            gu16_sleep_timer = 0;
            bit_sleep_mode_start = CLEAR;
        }
        else
        {
            gu16_sleep_timer++;

            if(gu16_sleep_timer >= DISPLAY_SLEEP_TIME)
            {
                gu16_sleep_timer = DISPLAY_SLEEP_TIME;

                if(bit_sleep_mode_start != SET)
                {
                    bit_sleep_mode_start = SET;
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        bit_standby_input = CLEAR;
        gu16_sleep_timer = 0;
        bit_sleep_mode_start = CLEAR;
    }
#endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





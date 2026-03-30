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
#include    "no_use_save.h"


void power_save_mode(void);
void no_use_save_control(void);
void detect_no_use_cds(void);
void power_saving_init(void);
void no_use_save_init(void);
void key_no_use_no_operation(void);
void powersaving_learned_mode_decision(void);
void smart_no_use_timer(void);
void smart_one_week_timer(void);
/*
U16 gu16LuxNoUse;
bit F_NoUseSave;
bit F_DayNoUseSave;
bit F_NightNoUseSave;             // 낮 해제를 위해

bit bit_9_hour_no_use_start;
U16 gu16_no_use_timer_min;
U8 gu8_no_use_timer_hour;
U8 gu8_one_week_timer_hour;
bit bit_temporary_no_operation;

POWER_SAVING_STATE gu8_smart_operation_mode;

bit no_use_break;


U8 gu8_unused_time_hour;

U8 mu8_no_use_timer;
U8 gu8_unused_count;
U8 gu8_total_no_use_timer_hour;
U16	gu16_one_week_timer;

bit f_one_week_judgement;
bit f_direct_mode_conversion;
bit f_normal_use_start;
*/

U16 gu16LuxNoUse;
bit F_NoUseSave;
bit F_DayNoUseSave;
bit F_NightNoUseSave;             // 낮 해제를 위해

bit bit_9_hour_no_use_start;

U16 gu16_no_use_timer_min;
U8 gu8_no_use_timer_hour;

U16 gu16_smart_unused_timer_min;
U8 gu8_smart_one_week_timer_hour;
U8 gu8_smart_unused_timer_hour;

bit bit_display_sleep_start;
U16 gu16_display_sleep_timer;


bit bit_first_time_setting;


U16 gu16_current_time_total;
U16 gu16_start_time_total;
U16 gu16_finish_time_total;


bit bit_temporary_no_operation;

//U8 mu8_no_use_timer;
U8 gu8_smart_unused_count;
U8 gu8_week;
U8 gu8_smart_total_no_use_timer_hour;

bit f_one_week_judgement;
bit f_direct_mode_conversion;
bit f_normal_use_start;
bit f_initial_smart_saving;



POWER_SAVING_STATE gu8_smart_operation_mode;

bit no_use_break;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void power_save_mode(void)
{

    /*..hui [23-6-29오후 2:57:07] 미사용 절전 모드 설정..*/
    powersaving_learned_mode_decision();

    /*..hui [23-6-29오후 2:56:55] 미사용 절전..*/
    no_use_save_control();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void no_use_save_control(void)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
		/*..hui [23-7-31오후 3:21:56] 냉동 요청.. 강제 미사용 절전 해제 기능..*/
		/*..hui [23-7-31오후 3:22:04] 전원 껐다 켜면 매번 설정해줘야 함..*/
		if( bit_temporary_no_operation == SET || F_FW_Version_Display_Mode == CLEAR )
		{
			gu16_no_use_timer_min = 0;
			gu8_no_use_timer_hour = 0;
			bit_9_hour_no_use_start = CLEAR;
	
			f_one_week_judgement = CLEAR;
			f_direct_mode_conversion = CLEAR;
	
			gu8_smart_unused_count = 0;
			gu8_smart_one_week_timer_hour = 0;
			gu8_smart_total_no_use_timer_hour = 0;
	
			gu16_smart_unused_timer_min = 0;
			gu8_smart_unused_timer_hour = 0;
	
			gu8_smart_operation_mode = GREEN_WEEK;
			return;
		}
		else{}
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
		/*..hui [23-8-31오후 3:35:38] 미사용 절전 9시간 타이머..*/
		gu16_no_use_timer_min++;
	
		/*..hui [23-8-30오후 3:27:06] 1시간 체크..*/
		if( gu16_no_use_timer_min >= 36000 )
		{
			gu16_no_use_timer_min = 0;
			gu8_no_use_timer_hour++;
		}
		else{}
	
		/*..hui [23-8-31오후 3:36:05] 9시간 경과 확인..*/
		if( gu8_no_use_timer_hour >= NO_USE_SAVE_MODE_TIME )
		{
			if( f_normal_use_start == SET )
			{
				bit_9_hour_no_use_start = CLEAR;
			}
			else
			{
				bit_9_hour_no_use_start = SET;
			}
		}
		else{}
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
		/*..hui [23-8-31오후 3:36:36] 스마트절전 관련 타이머..*/
		gu16_smart_unused_timer_min++;
	
		/*..hui [23-8-31오후 3:31:51] 스마트 절전 미사용 1시간 체크..*/
		if( gu16_smart_unused_timer_min >= 36000 )
		{
			gu16_smart_unused_timer_min = 0;
	
			smart_no_use_timer();
			gu8_smart_one_week_timer_hour++;
		}
		else{}
	
		smart_one_week_timer();

		detect_no_use_cds();
	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
		/*.. sean [23-8-24 오후 1:27:11 ] 외기에 의한 Sleep 모드 해제 조건 추가 ..*/
		if( (gu8_Amb_Temperature_One_Degree < 24) || (gu8_Amb_Temperature_One_Degree > 32 ) )
		{
			no_use_save_init();
		}
		else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void powersaving_learned_mode_decision(void)
{
    //1주일 지났는지 확인하여 모드 설정
    if( f_one_week_judgement == SET )
    {
        if( gu8_smart_total_no_use_timer_hour >= TOTAL_MAXIMUM_REST_TIME )
        {
            gu8_smart_operation_mode = GREEN_WEEK;
        }
        else
        {
            //84시간 사용 안할 시, 1주일 후 Green Week;
            if( f_direct_mode_conversion == SET )
            {
                gu8_smart_operation_mode = GREEN_WEEK;
                f_direct_mode_conversion = CLEAR;
            }
            else
            {
                //GreenWeek 여부 확인
                if( gu8_smart_operation_mode == GREEN_WEEK )
                {
                    if( gu8_smart_unused_count <= 2 )
                    {
                        gu8_smart_operation_mode = INTENSIVE_WEEK;
                    }
                    else
                    {
                        gu8_smart_operation_mode = GREEN_WEEK;
                    }
                }
                else //if(gu8_smart_operation_mode[gu8_week] == INTENSIVE_WEEK)
                {
                    if( gu8_smart_unused_count >= 4 )
                    {
                        gu8_smart_operation_mode = GREEN_WEEK;
                    }
                    else
                    {
                        gu8_smart_operation_mode = INTENSIVE_WEEK;
                    }
                }
            }
        }

        f_one_week_judgement = CLEAR;
        f_direct_mode_conversion = CLEAR;

        /*..hui [23-8-31오전 10:51:14] 16시간 이상 미사용 횟수 카운트 초기화..*/
        gu8_smart_unused_count = 0;
        /*..hui [23-8-31오전 10:51:54] 16시간 이상 미사용 체크 타이머 초기화..*/
        gu16_smart_unused_timer_min = 0;
        gu8_smart_unused_timer_hour = 0;

        /*..hui [23-8-31오전 10:50:10] 일주일 경과 타이머 초기화..*/
        gu8_smart_one_week_timer_hour = 0;
        /*..hui [23-8-31오전 10:51:00] 16시간 이상 총 누적시간(144시간) 타이머 초기화..*/
        gu8_smart_total_no_use_timer_hour = 0;

        /*..hui [23-8-31오후 4:13:33] 일주일 지나면 무조건 초기화.. 양대리 - 팀장님 지시..*/
        no_use_save_init();

        /*..hui [23-8-31오전 11:39:17] 미사용절전 진입 타이머 초기화..*/
        /*..hui [23-8-31오전 11:39:43] 매주 1주일 경과시마다 다시 9시간 미사용해야 절전모드 진입됨..*/
        /*gu16_no_use_timer_min = 0;*/
        /*gu8_no_use_timer_hour = 0;*/

        /*..hui [23-8-31오후 1:21:20] 일주일 지나면 미사용절전 중이더라도 해제하고 9시간 다시 판단..*/
        /*..hui [23-8-31오후 1:22:33] 이부분 중요.. gu8_no_use_timer_hour만 0으로 초기화된다고 해제되지 않음..*/
        /*bit_9_hour_no_use_start = CLEAR;*/
    }
    else
    {
        //Green Week에서 터치 들어올 시,
        if( no_use_break == SET )
        {
            if( gu8_smart_unused_timer_hour >= USE_SAVE_LEARNEND_MODE_TIME )
            {
                /*..hui [23-8-30오후 3:33:26] 16시간 이상 미사용 카운트 횟수 증가..*/
                gu8_smart_unused_count++;
            }
            else{}

            gu16_smart_unused_timer_min = 0;
            gu8_smart_unused_timer_hour = 0;
            no_use_break = CLEAR;
        }
        else
        {
            // 안쓴 시간이 84시간이 넘어갔을 경우에는 즉시 Green Week 변경
            if( gu8_smart_unused_timer_hour >= TRIP_REST_TIME )
            {
                f_direct_mode_conversion = SET;
                gu8_smart_operation_mode = GREEN_WEEK;
            }
            else{}
        }
    }

    if( gu8_smart_operation_mode == GREEN_WEEK )
    {
        f_normal_use_start = CLEAR;
    }
    else
    {
        f_normal_use_start = SET;
        /*..hui [23-8-31오후 3:18:27] 인텐시브위크면 9시간 초기화 및 미사용절전 해제..*/
        /*..hui [23-8-31오후 3:18:38] 이후 그린위크로 들어가면 그때부터 9시간 다시 카운팅함..*/
        no_use_save_init();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void smart_no_use_timer(void)
{
    gu8_smart_unused_timer_hour++;

    /*..hui [23-8-30오후 3:46:44] 미사용 144시간 체크..*/
    if( gu8_smart_unused_timer_hour == USE_SAVE_LEARNEND_MODE_TIME )
    {
        /*..hui [23-8-30오후 3:28:49] 16시간되면 16더해줌..*/
        gu8_smart_total_no_use_timer_hour = gu8_smart_total_no_use_timer_hour + gu8_smart_unused_timer_hour;
    }
    else if( gu8_smart_unused_timer_hour > USE_SAVE_LEARNEND_MODE_TIME )
    {
        /*..hui [23-8-30오후 3:28:58] 17시간부터는 1씩 더해줌..*/
        gu8_smart_total_no_use_timer_hour = gu8_smart_total_no_use_timer_hour + 1;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void smart_one_week_timer(void)
{
    /*..hui [23-8-31오전 10:56:04] 일주일 경과 체크..*/
    if( gu8_smart_one_week_timer_hour >= ONE_WEEK_TIME_HOUR )
    {
        gu8_smart_one_week_timer_hour = 0;
        f_one_week_judgement = SET;

		f_initial_smart_saving = CLEAR;
    }
    else{}
    /*..hui [23-8-31오전 10:56:04] 일주일 경과 체크..*/
	if((F_Hot_Enable == SET) && (F_IceOn == CLEAR) && (F_Cold_Enable == CLEAR) )
	{
		f_initial_smart_saving = CLEAR;
	}
	else {}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_no_use_no_operation(void)
{
    if( bit_temporary_no_operation == CLEAR )
    {
        bit_temporary_no_operation = SET;
        BuzStep(BUZZER_SETUP);
        f_normal_use_start = CLEAR;
    }
    else
    {
        bit_temporary_no_operation = CLEAR;
        BuzStep(BUZZER_CANCEL);
        f_normal_use_start = SET;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void power_saving_init(void)
{
    /*..hui [23-6-29오후 2:54:25] 취침모드 디스플레이만 해제..*/
    bit_display_sleep_start = CLEAR;
    gu16_display_sleep_timer = 0;

    no_use_break = SET;

    gu8_wifi_no_use_key = SET;

    no_use_save_init();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void no_use_save_init(void)
{
    F_NightNoUseSave = 0;           // 미사용 절전진입 초기화
    F_DayNoUseSave = 0;
    F_NoUseSave = 0;

    bit_9_hour_no_use_start = 0;
	gu8_no_use_timer_hour = 0;
	gu16_no_use_timer_min = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_no_use_cds(void)
{
//---------------------------------------
    /*if( F_Save != SET && gu16NoWaterOut == 0 )*/       // 야간절전해제 와 6시간 미사용 시 미사용 절전 진입
    /*..hui [23-8-17오후 4:03:31] 9시간 미사용 절전 진입 중..*/
    if( bit_9_hour_no_use_start == SET )
    {
        if( F_NoUseSave != SET )                    // 미사용 절전 진입 조건
        {
            if( SLEEP_IN > gu16ADCds )            // 절전진입-밤
            {
                gu16LuxNoUse++;

                if(gu16LuxNoUse >= NOW_USE_PHOTO)
                {
                    F_NoUseSave = 1;
                    F_NightNoUseSave = 1;
                    F_DayNoUseSave = 0;

                    gu16LuxNoUse = 0;
                }      // 10분경과시 절전진입
            }
            else if(gu16ADCds > SLEEP_OUT)      // 절전진입-낮
            {
                gu16LuxNoUse++;

                if(gu16LuxNoUse >= NOW_USE_PHOTO)
                {
                    F_NoUseSave = 1;
                    F_NightNoUseSave = 0;
                    F_DayNoUseSave = 1;

                    gu16LuxNoUse = 0;
                }      // 10분경과시 절전진입
                else{}
            }
            else
            {
                gu16LuxNoUse++;

                if(gu16LuxNoUse >= NOW_USE_PHOTO)
                {
                    F_NoUseSave = 1;
                    F_NightNoUseSave = 0;
                    F_DayNoUseSave = 1;              // 중간값에서는 낮시작으로

                    gu16LuxNoUse = 0;
                }
                else{}
            }
        }
        else                                      // 미사용 절전 해제 조건
        {
            if( F_DayNoUseSave == SET )
            {
                if(SLEEP_IN > gu16ADCds)                // 절전진입-밤
                {
                    if(++gu16LuxNoUse >= NOW_USE_PHOTO)             // 10min Continue
                    {
                        F_DayNoUseSave = 0;
                        F_NightNoUseSave = 1;             // 낮 해제를 위해

                        gu16LuxNoUse = 0;
                    }      // 10분경과시 절전진입
                }
                else
                {
                    gu16LuxNoUse = 0;
                }
            }
            else{}

            if( F_NightNoUseSave == SET )
            {
                if( gu16ADCds > SLEEP_OUT )               // 미사용 절전해제-낮
                {
                    if(++gu16LuxNoUse >= NOW_USE_PHOTO)           // 10min Continue
                    {
                        #if 0
                        gu16NoWaterOut = NoWaterOutTime;      // 6시간 절전 해제
                        F_6HourNoUse = 0;

                        F_NightNoUseSave = 0;           // 미사용 절전진입 초기화
                        F_DayNoUseSave = 0;
                        F_NoUseSave = 0;
                        #endif

                        no_use_save_init();

                        gu16LuxNoUse = 0;
                    }      // 10분경과시 절전진입
                }
                else
                {
                    gu16LuxNoUse = 0;
                }
            }
        }
    }

}




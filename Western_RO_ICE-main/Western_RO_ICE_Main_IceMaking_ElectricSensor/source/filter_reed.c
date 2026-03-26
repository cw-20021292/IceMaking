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
#include    "filter_reed.h"

void input_filter_reed_sw(void);
void input_filter_cover_reed(void);
void input_filter_reed_neo(void);
void input_filter_reed_ro(void);
void input_filter_reed_ino(void);
void input_filter_reed_acid(void);

void input_filter_all(void);

void init_filter(void);
void filter_reset_timer(void);
void filter_reset_timer__neo(void);
void filter_reset_timer__ro(void);
void filter_reset_timer__ino(void);

void decesion_filter_flushing(void);
void decesion_normal_mode(void);
void decesion_ct_mode(void);

void filter_reset(void);

void reset_time_neo_filter(void);
void reset_time_ro_filter(void);
void reset_time_ino_filter(void);
void neo_ino_filter_alarm(void);
void neo_ro_ino_all_filter_alarm(void);

void display_filter_alarm(void);
void calc_remain_day( U16 mu16_day );

void neo_filter_alarm(void);
void ro_filter_alarm(void);
void ino_filter_alarm(void);

void start_filter_flushing(void);
void cancel_filter_flushing(void);
void init_filter_data(void);

TYPE_BYTE          U8FilterResetStateB;
#define            u8FilterResetState                            U8FilterResetStateB.byte
#define            Bit0_Neo_Filter_1_Reset_State                 U8FilterResetStateB.Bit.b0
#define            Bit1_Ro_Filter_2_Reset_State                  U8FilterResetStateB.Bit.b1
#define            Bit2_Ino_Filter_3_Reset_State                 U8FilterResetStateB.Bit.b2


bit bit_filter_cover;
bit bit_filter_cover_open_to_close;


bit bit_neo_filter_1_reed;
bit bit_ro_filter_2_reed;
bit bit_ino_filter_3_reed;

bit bit_acid_reed;


U8 gu8_filter_cover_reed_on_decision_cnt;
U8 gu8_filter_cover_reed_off_decision_cnt;

U8 gu8_neo_reed_on_decision_cnt;
U8 gu8_neo_reed_off_decision_cnt;


U8 gu8_ro_reed_on_decision_cnt;
U8 gu8_ro_reed_off_decision_cnt;

U8 gu8_ino_reed_on_decision_cnt;
U8 gu8_ino_reed_off_decision_cnt;

U8 gu8_acid_reed_on_decision_cnt;
U8 gu8_acid_reed_off_decision_cnt;


bit bit_neo_filter_1_reed_old;
bit bit_ro_filter_2_reed_old;
bit bit_ino_filter_3_reed_old;

bit bit_acid_reed_old;

#if 0
U16 gu16_neo_filter_reset_timer_sec;
U8 gu8_neo_filter_reset_timer_min;
U8 gu8_neo_filter_reset_timer_hour;


U16 gu16_ro_filter_reset_timer_sec;
U8 gu8_ro_filter_reset_timer_min;
U8 gu8_ro_filter_reset_timer_hour;
#endif




/*U16 gu16_filter_reset_day_neo;*/
/*U16 gu16_filter_reset_day_ro;*/


U16 gu16_reset_hour_neo_filter;
U16 gu16_reset_hour_ro_filter;
U16 gu16_reset_hour_ino_filter;


U16 gu16_neo_filter_reset_timer_sec;
U8 gu8_neo_filter_reset_timer_min;
U8 gu8_neo_filter_reset_timer_hour;


U16 gu16_ro_filter_reset_timer_sec;
U8 gu8_ro_filter_reset_timer_min;
U8 gu8_ro_filter_reset_timer_hour;

U16 gu16_ino_filter_reset_timer_sec;
U8 gu8_ino_filter_reset_timer_min;
U8 gu8_ino_filter_reset_timer_hour;


U16 gu16_display_filter_remain_day;
bit bit_filter_alarm_start;



bit bit_filter_alarm_1_3_voice;
bit bit_filter_alarm_1_2_3_voice;



bit bit_neo_filter_1_alarm;
bit bit_ro_filter_2_alarm;
bit bit_ino_filter_3_alarm;

U16 gu16_neo_filter_1_remain_day;
U16 gu16_ro_filter_2_remain_day;
U16 gu16_ino_filter_3_remain_day;


U8 gu8_filter_change_type;


U8 gu8_filter_alarm_popup_enable;


bit bit_yes_no_popup;
bit bit_filter_all;

bit bit_filter_reset_yes;
bit bit_filter_reset_no;

bit bit_wifi_neo_filter_1_reset;
bit bit_wifi_ro_filter_2_reset;
bit bit_wifi_ino_filter_3_reset;


U16 gu16_filter_change_reset_timer;

U16 gu16_1_3_remain_day_before;
U16 gu16_1_2_3_remain_day_before;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_filter_reed_sw(void)
{
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        init_filter();
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /*..hui [23-9-27오후 1:40:56] 필터 커버 리드스위치..*/
    input_filter_cover_reed();


    /*..hui [23-10-4오후 1:12:09] NEO필터 리드스위치..*/
    input_filter_reed_neo();

    /*..hui [23-9-27오후 1:41:06] RO필터 리드스위치..*/
    input_filter_reed_ro();

    /*..hui [23-10-4오후 1:12:19] INO 필터 리드스위치..*/
    input_filter_reed_ino();

    /*..hui [24-7-17오후 6:52:09] 구연산 리드스위치..*/
    input_filter_reed_acid();

    input_filter_all();

    filter_reset_timer();
    decesion_filter_flushing();
    filter_reset();

    display_filter_alarm();

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_filter_cover_reed(void)
{

    ///////bit_filter_cover= 1;
    ///////return;

    if( pREED_FILTER_COVER == SET )
    {
        gu8_filter_cover_reed_off_decision_cnt = 0;
        gu8_filter_cover_reed_on_decision_cnt++;

        if ( gu8_filter_cover_reed_on_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_filter_cover_reed_on_decision_cnt = FILTER_REED_DETECT_TIME;

            if( bit_filter_cover == SET )
            {
                /*..hui [21-8-3오후 12:49:03] 열림..*/
                bit_filter_cover = CLEAR;
                ///////bit_filter_flushing_no_cancel = CLEAR;
                /*play_melody_warning_197();*/
                play_voice_filter_cover_open_3();
                power_saving_init();

            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_filter_cover_reed_on_decision_cnt = 0;
        gu8_filter_cover_reed_off_decision_cnt++;

        if( gu8_filter_cover_reed_off_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_filter_cover_reed_off_decision_cnt = FILTER_REED_DETECT_TIME;

            /*..hui [21-8-3오후 12:49:07] 닫힘..*/
            if( bit_filter_cover == CLEAR )
            {
                bit_filter_cover = SET;
                play_melody_setting_on_198();

                /*start_filter_flushing();*/
                /////////////////////bit_filter_cover_open_to_close = SET;

                /*..hui [24-1-17오후 5:01:07] 최초 필터 플러싱 시작 전에만.. 필터 관련 음성 출력..*/
                /*..hui [24-1-17오후 5:01:25] 1,3번으로 필터 플러싱 중에 커버 열어서 중단하고 2번 교체 감지가 되면..*/
                /*..hui [24-1-17오후 5:01:41] 닫았을때 필터 음성은 안내보내고 플러싱 시간만 ro 플러싱 30분으로 변경한다..*/
                if( gu8_filter_flushing_state == FILTER_FLUSHING_NONE )
                {
                    bit_filter_cover_open_to_close = SET;
                }
                else
                {
                    /*..hui [24-1-17오후 5:52:16] 네오,이노 교체후 플러싱 진행중에 RO 교체 감지되면.....*/
                    if( gu8_filter_flushing_state == FILTER_FLUSHING_NEO_INO  )
                    {
                        /*if( u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )*/
                        if( Bit1_Ro_Filter_2_Reset_State == SET )
                        {
                            gu8_filter_flushing_state = FILTER_FLUSHING_RO;
                        }
                        else{}
                    }
                    else{}
                }
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
void input_filter_reed_neo(void)
{
    ///////bit_neo_filter_1_reed = 1;
    ///////return;

    if( pREED_NEO_1_FILTER == SET )
    {
        gu8_neo_reed_off_decision_cnt = 0;
        gu8_neo_reed_on_decision_cnt++;

        if ( gu8_neo_reed_on_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_neo_reed_on_decision_cnt = FILTER_REED_DETECT_TIME;

            if( bit_neo_filter_1_reed == SET )
            {
                /*..hui [21-8-3오후 12:49:03] 열림..*/
                bit_neo_filter_1_reed = CLEAR;
                play_melody_warning_197();
                power_saving_init();
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_neo_reed_on_decision_cnt = 0;
        gu8_neo_reed_off_decision_cnt++;

        if( gu8_neo_reed_off_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_neo_reed_off_decision_cnt = FILTER_REED_DETECT_TIME;

            /*..hui [21-8-3오후 12:49:07] 닫힘..*/
            if( bit_neo_filter_1_reed == CLEAR )
            {
                bit_neo_filter_1_reed = SET;
                play_melody_setting_on_198();
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
void input_filter_reed_ro(void)
{
    ///////bit_ro_filter_2_reed = 1;
    ///////return;

    if( pREED_RO_2_FILTER == SET )
    {
        gu8_ro_reed_off_decision_cnt = 0;
        gu8_ro_reed_on_decision_cnt++;

        if ( gu8_ro_reed_on_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_ro_reed_on_decision_cnt = FILTER_REED_DETECT_TIME;

            if( bit_ro_filter_2_reed == SET )
            {
                /*..hui [21-8-3오후 12:49:03] 열림..*/
                bit_ro_filter_2_reed = CLEAR;

                /*play_melody_warning_197();*/
                /*..hui [24-4-3오전 10:20:16] 설치 플러싱 할때도 음성 없도록.. 신뢰성..*/
                /*..hui [24-7-29오후 3:11:07] 구연산 세척할때도 음성 x..*/
                if( bit_ct_flushing_standby_start == CLEAR && bit_install_flushing_state == CLEAR && bit_acid_clean_start == CLEAR )
                {
                    play_voice_change_1_3_filter_13();
                }
                else
                {
                    /*..hui [24-3-6오후 4:19:03] 강제 플러싱 모드에서는 음성없이 그냥 띠링띠링만 나도록.. 함재진이 발견해줌..*/
                    play_melody_warning_197();
                }

                power_saving_init();

            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_ro_reed_on_decision_cnt = 0;
        gu8_ro_reed_off_decision_cnt++;

        if( gu8_ro_reed_off_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_ro_reed_off_decision_cnt = FILTER_REED_DETECT_TIME;

            /*..hui [21-8-3오후 12:49:07] 닫힘..*/
            if( bit_ro_filter_2_reed == CLEAR )
            {
                bit_ro_filter_2_reed = SET;
                play_melody_setting_on_198();

                /*..hui [23-7-4오전 9:45:44] 커버 닫힌상태 -> 필터 감지 -> yes,no 화면 없어져야함..*/
                /*..hui [23-7-4오전 9:45:57] 실제 제품에서 나올수는 없음.....*/
                if( bit_filter_cover == SET )
                {
                    bit_yes_no_popup = CLEAR;
                }
                else{}
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
void input_filter_reed_ino(void)
{
    ///////bit_ino_filter_3_reed = 1;
    ///////return;

    if( pREED_INO_3_FILTER == SET )
    {
        gu8_ino_reed_off_decision_cnt = 0;
        gu8_ino_reed_on_decision_cnt++;

        if ( gu8_ino_reed_on_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_ino_reed_on_decision_cnt = FILTER_REED_DETECT_TIME;

            if( bit_ino_filter_3_reed == SET )
            {
                /*..hui [21-8-3오후 12:49:03] 열림..*/
                bit_ino_filter_3_reed = CLEAR;
                play_melody_warning_197();
                power_saving_init();
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_ino_reed_on_decision_cnt = 0;
        gu8_ino_reed_off_decision_cnt++;

        if( gu8_ino_reed_off_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_ino_reed_off_decision_cnt = FILTER_REED_DETECT_TIME;

            /*..hui [21-8-3오후 12:49:07] 닫힘..*/
            if( bit_ino_filter_3_reed == CLEAR )
            {
                bit_ino_filter_3_reed = SET;
                play_melody_setting_on_198();
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
void input_filter_reed_acid(void)
{
    if( pREED_ACID == SET )
    {
        gu8_acid_reed_off_decision_cnt = 0;
        gu8_acid_reed_on_decision_cnt++;

        if ( gu8_acid_reed_on_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_acid_reed_on_decision_cnt = FILTER_REED_DETECT_TIME;

            if( bit_acid_reed == SET )
            {
                /*..hui [21-8-3오후 12:49:03] 열림..*/
                /*..hui [24-7-18오후 1:47:21] 장착해제..*/
                bit_acid_reed = CLEAR;
                /*play_melody_warning_197();*/
                /*power_saving_init();*/
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_acid_reed_on_decision_cnt = 0;
        gu8_acid_reed_off_decision_cnt++;

        if( gu8_acid_reed_off_decision_cnt >= FILTER_REED_DETECT_TIME )
        {
            gu8_acid_reed_off_decision_cnt = FILTER_REED_DETECT_TIME;

            /*..hui [21-8-3오후 12:49:07] 닫힘..*/
            /*..hui [24-7-18오후 1:47:28] 장착..*/
            if( bit_acid_reed == CLEAR )
            {
                bit_acid_reed = SET;
                play_melody_setting_on_198();
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
void input_filter_all(void)
{
    /*if( bit_filter_cover == CLEAR
        || bit_ro_filter_2_reed == CLEAR )*/
    if( bit_filter_cover == CLEAR
        || bit_neo_filter_1_reed == CLEAR
        || bit_ro_filter_2_reed == CLEAR
        || bit_ino_filter_3_reed == CLEAR )
    {
        bit_filter_all = CLEAR;
    }
    else
    {
        bit_filter_all = SET;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_filter(void)
{
    gu8_filter_cover_reed_on_decision_cnt = 0;
    gu8_filter_cover_reed_off_decision_cnt = 0;
    bit_filter_cover = SET;

    gu8_neo_reed_on_decision_cnt = 0;
    gu8_neo_reed_off_decision_cnt = 0;
    bit_neo_filter_1_reed = SET;

    gu8_ro_reed_on_decision_cnt = 0;
    gu8_ro_reed_off_decision_cnt = 0;
    bit_ro_filter_2_reed = SET;

    gu8_ino_reed_on_decision_cnt = 0;
    gu8_ino_reed_off_decision_cnt = 0;
    bit_ino_filter_3_reed = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_reset_timer(void)
{
    filter_reset_timer__neo();
    filter_reset_timer__ro();
    filter_reset_timer__ino();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_reset_timer__neo(void)
{
    /*..hui [23-12-19오후 3:13:15] 설치 플러싱일때는 확인하지 않는다..*/
    /*..hui [24-7-29오후 3:09:52] 구연산 세척때도 미 확인..*/
    if( bit_install_flushing_state == SET || bit_acid_clean_start == SET )
    {
        return;
    }
    else{}

    if( bit_neo_filter_1_reed == CLEAR )
    {
        bit_neo_filter_1_reed_old = SET;
    }
    else
    {
        if( bit_neo_filter_1_reed_old == SET )
        {
            bit_neo_filter_1_reed_old = CLEAR;
            Bit0_Neo_Filter_1_Reset_State = SET;

            /*..hui [24-2-22오전 10:43:52] CT 모드 아닐 경우에만 음성 출력..*/
            if( bit_ct_flushing_standby_start == CLEAR )
            {
                if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
                {
                    if( u8FilterResetState == NEO_INO_FILTER_CHANGE )
                    {
                        play_voice_1_3_filter_change_detect_18();
                    }
                    else{}
                }
                else{}
            }
            else
            {
                /*..hui [24-2-22오전 10:46:01] CT 강제 플러싱 표시용..*/
                Bit0_CT_Neo_Filter_1_Replace = SET;
            }
        }
        else{}
    }

    gu16_neo_filter_reset_timer_sec++;

    if(gu16_neo_filter_reset_timer_sec >= 600)
    {
        gu16_neo_filter_reset_timer_sec = 0;
        gu8_neo_filter_reset_timer_min++;
    }
    else{}

    if(gu8_neo_filter_reset_timer_min >= 60)
    {
        gu8_neo_filter_reset_timer_min = 0;
        /*gu8_neo_filter_reset_timer_hour++;*/

        gu16_reset_hour_neo_filter++;
    }
    else{}

    if( gu16_reset_hour_neo_filter >= FILTER_RESET_MAX_HOUR__NEO )
    {
        gu16_reset_hour_neo_filter = FILTER_RESET_MAX_HOUR__NEO;
    }
    else{}


}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_reset_timer__ro(void)
{
    /*..hui [23-12-19오후 3:13:15] 설치 플러싱일때는 확인하지 않는다..*/
    /*..hui [24-7-29오후 3:09:52] 구연산 세척때도 미 확인..*/
    if( bit_install_flushing_state == SET || bit_acid_clean_start == SET )
    {
        return;
    }
    else{}

    if( bit_ro_filter_2_reed == CLEAR )
    {
        bit_ro_filter_2_reed_old = SET;
    }
    else
    {
        if( bit_ro_filter_2_reed_old == SET )
        {
            bit_ro_filter_2_reed_old = CLEAR;
            /*Bit1_Ro_Filter_2_Reset_State = SET;*/

            ///////#if 0
            /*..hui [21-10-15오후 7:03:01] 필터 체결했는데 커버가 열려있을 경우에만 set..*/
            /*..hui [21-10-15오후 7:03:46] 커버 on -> 필터 off -> on -> 커버 off -> 커버 on시 yesno나옴..*/
            /*..hui [23-7-28오후 4:05:13] 사이드커버 장착 상태에서 RO 필터 리드만 OFF->ON 됐을 경우을 얘기하는거임....*/
            /*..hui [23-7-28오후 4:05:34] 사이드커버 장착 상태, RO 필터리드 OFF->ON, 정상상태 진입..*/
            /*..hui [23-7-28오후 4:05:48] 이후 사이드 커버만 OFF->ON시 RO플러싱으로 넘어감..*/
            /*..hui [23-7-28오후 4:06:04] RO 필터 리드는 사이드 커버가 열려있을때만 확인하는걸로..*/
            if( bit_filter_cover == CLEAR )
            {
                Bit1_Ro_Filter_2_Reset_State = SET;
            }
            else{}
            ///////#endif

            /*if( bit_ct_flushing_standby_start == CLEAR )*/
            if( bit_ct_flushing_standby_start == SET )
            {
                /*..hui [24-2-22오전 10:46:01] CT 강제 플러싱 표시용..*/
                Bit1_CT_Ro_Filter_2_Replace = SET;
            }
            else{}

        }
        else{}
    }

    gu16_ro_filter_reset_timer_sec++;

    if(gu16_ro_filter_reset_timer_sec >= 600)
    {
        gu16_ro_filter_reset_timer_sec = 0;
        gu8_ro_filter_reset_timer_min++;
    }
    else{}

    if(gu8_ro_filter_reset_timer_min >= 60)
    {
        gu8_ro_filter_reset_timer_min = 0;
        /*gu8_ro_filter_reset_timer_hour++;*/

        gu16_reset_hour_ro_filter++;
    }
    else{}

    if( gu16_reset_hour_ro_filter >= FILTER_RESET_MAX_HOUR__RO )
    {
        gu16_reset_hour_ro_filter = FILTER_RESET_MAX_HOUR__RO;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_reset_timer__ino(void)
{
    /*..hui [23-12-19오후 3:13:15] 설치 플러싱일때는 확인하지 않는다..*/
    /*..hui [24-7-29오후 3:09:52] 구연산 세척때도 미 확인..*/
    if( bit_install_flushing_state == SET || bit_acid_clean_start == SET )
    {
        return;
    }
    else{}

    if( bit_ino_filter_3_reed == CLEAR )
    {
        bit_ino_filter_3_reed_old = SET;
    }
    else
    {
        if( bit_ino_filter_3_reed_old == SET )
        {
            bit_ino_filter_3_reed_old = CLEAR;
            Bit2_Ino_Filter_3_Reset_State = SET;

            /*..hui [24-2-22오전 10:43:52] CT 모드 아닐 경우에만 음성 출력..*/
            if( bit_ct_flushing_standby_start == CLEAR )
            {
                if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
                {
                    if( u8FilterResetState == NEO_INO_FILTER_CHANGE )
                    {
                        play_voice_1_3_filter_change_detect_18();
                    }
                    else{}
                }
                else{}
            }
            else
            {
                /*..hui [24-2-22오전 10:46:01] CT 강제 플러싱 표시용..*/
                Bit2_CT_Ino_Filter_3_Replace = SET;
            }
        }
        else{}
    }

    gu16_ino_filter_reset_timer_sec++;

    if(gu16_ino_filter_reset_timer_sec >= 600)
    {
        gu16_ino_filter_reset_timer_sec = 0;
        gu8_ino_filter_reset_timer_min++;
    }
    else{}

    if(gu8_ino_filter_reset_timer_min >= 60)
    {
        gu8_ino_filter_reset_timer_min = 0;
        /*gu8_ino_filter_reset_timer_hour++;*/

        gu16_reset_hour_ino_filter++;
    }
    else{}

    if( gu16_reset_hour_ino_filter >= FILTER_RESET_MAX_HOUR__INO )
    {
        gu16_reset_hour_ino_filter = FILTER_RESET_MAX_HOUR__INO;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void decesion_filter_flushing(void)
{
    /*..hui [23-12-6오후 2:29:59] 필터 커버가 닫힌 후 30분후에 필터 리드 감지상태 초기화..*/
    /*..hui [23-12-6오후 2:30:18] 1,3번 차례인데 1번만 교체 후 커버닫음... 30분이내에 3번만 감지되도 플러싱 하기위해..*/
    if( bit_filter_cover == SET )
    {
        if( u8FilterResetState > 0 )
        {
            gu16_filter_change_reset_timer++;

            /*..hui [24-1-3오후 4:01:19] 15분으로 변경.. 강제 플러싱 기능과 동일하게 가져가기위해..*/
            /*..hui [24-1-3오후 4:01:38] 함재진, 이제호와 협의 및 확정..*/
            if( gu16_filter_change_reset_timer >= FILTER_CHANGE_RESET_TIME )
            {
                gu16_filter_change_reset_timer = 0;
                u8FilterResetState = 0;
            }
            else{}
        }
        else
        {
            gu16_filter_change_reset_timer = 0;
        }
    }
    else
    {
        gu16_filter_change_reset_timer = 0;
    }

    /*..hui [23-12-6오후 2:53:11] 필터커버 미감지 -> 감지된 후..*/
    if( bit_filter_cover_open_to_close == SET )
    {
        bit_filter_cover_open_to_close = CLEAR;

        /*..hui [24-7-29오후 3:05:19] 구연산 세척 중 필터 플러싱 패스..*/
        if( bit_acid_clean_start == CLEAR )
        {
            /*..hui [24-2-21오후 2:50:02] CT 강제 플러싱 모드 추가에 따라 분리..*/
            if( bit_ct_flushing_standby_start == CLEAR )
            {
                decesion_normal_mode();
            }
            else
            {
                decesion_ct_mode();
            }
        }
        else{}
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void decesion_normal_mode(void)
{
    /*..hui [23-12-11오후 5:42:14] 필터커버 OPEN->CLOSE했을때.. 필터 리드스위치가 정상 감지됐을때만..*/
    if( u8FilterResetState == NEO_INO_FILTER_CHANGE
        || u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )
    {
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            if( u8FilterResetState == NEO_INO_FILTER_CHANGE )
            {
                start_filter_flushing();
            }
            else
            {
                /*..hui [23-12-6오후 2:22:33] 1,3번 교체차례인데 1,2,3이 감지가되도 플러싱 진행..*/
                /*..hui [23-12-6오후 2:22:40] 단, 리셋은 1,3번만 한다..*/
                start_filter_flushing();
            }

            /*..hui [23-12-15오후 7:32:33] 1,3번 시기에 1,3 또는 1,2,3 교체됐을 경우 출수버튼을 누러주세요~..*/
            play_voice_1_3_filter_change_finish_19();
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            /*..hui [23-12-6오후 2:25:34] 1,2,3 차례에서는 전부 다 감지되야.....*/
            if( u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )
            {
                start_filter_flushing();

                /*..hui [24-1-4오후 5:41:42] 1,2,3번 시기에 1,2,3 전부 잘 교체됐을경우.. 출수 버튼을 눌러주세요~..*/
                play_voice_1_2_3_filter_change_finish_46();
            }
            else
            {
                /*..hui [23-12-15오후 7:07:12] ro 순서인데 1,3번만 교체됨..*/
                play_voice_change_all_filter_47();
            }
        }
    }
    else
    {
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            /*..hui [23-12-15오후 7:07:38] 1번, 3번, 1/2번, 1/3번 교체..*/
            /////play_voice_change_1_3_filter_13();
            if( u8FilterResetState == 0 )
            {
                /*..hui [23-12-19오후 3:16:26] 필터 감지 아예 안됐을때는 아무 음성도 출력하지않음..*/
                //
            }
            else if( u8FilterResetState == 1 || u8FilterResetState == 3 )
            {
                /*..hui [23-12-15오후 7:30:46] 1,3번 시기인데 1번만 교체됐을때..*/
                /*..hui [24-1-10오후 2:57:50] 1,3번 시기인데 1,2번만 교체됐을때..*/
                play_voice_a_type_add_3_filter_change_15();
            }
            else if( u8FilterResetState == 2 )
            {
                /*..hui [23-12-15오후 7:31:05] 1,3번 시기인데 2번만 교체됐을때..*/
                play_voice_a_type_add_1_3_filter_change_16();
            }
            else if( u8FilterResetState == 4 || u8FilterResetState == 6 )
            {
                /*..hui [23-12-15오후 7:31:19] 1,3번 시기인데 3번만 교체됐을때..*/
                /*..hui [24-1-10오후 2:58:40] 1,3번 시기인데 2,3번만 교체됐을때..*/
                play_voice_a_type_add_3_filter_change_17();
            }
            else
            {
                /*..hui [23-12-15오후 7:31:39] 그 외의경우..*/
                /*play_voice_change_1_3_filter_13();*/
                /*..hui [24-1-10오후 3:04:36] 13번은 레버 올렸다 내렸을때로..*/
                /*play_voice_change_1_3_filter_13();*/
            }
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            if( u8FilterResetState == 0 )
            {
                /*..hui [23-12-19오후 3:16:26] 필터 감지 아예 안됐을때는 아무 음성도 출력하지않음..*/
                //
            }
            else if( u8FilterResetState == 1 )
            {
                /*..hui [24-1-4오후 5:34:09] 1,2,3번 시기인데 1번만 교체됐을때..*/
                play_voice_b_type_only_1_filter_change_43();
            }
            else if( u8FilterResetState == 2 )
            {
                /*..hui [24-1-4오후 5:34:23] 1,2,3번 시기인데 2번만 교체됐을대..*/
                play_voice_b_type_only_2_filter_change_44();
            }
            else if( u8FilterResetState == 4 )
            {
                /*..hui [24-1-4오후 5:34:33] 1,2,3번 시기인데 3번만 교체됐을때..*/
                play_voice_b_type_only_3_filter_change_45();
            }
            else
            {
                /*..hui [24-1-4오후 5:36:19] 1,2,3 교체 시기인데 1/2번, 2/3번, 1/3번이 교체됐을때..*/
                /*..hui [24-1-4오후 5:36:38] 1/3번 교체됐을때는 위쪽에서 처리..*/
                play_voice_change_all_filter_47();
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void decesion_ct_mode(void)
{
    /*..hui [24-2-21오후 2:52:58] CT 모드에서는 하나이상 필터 감지되면 플러싱 진행..*/
    if( u8FilterResetState != FILTER_NO_CHANGE )
    {
        start_filter_flushing();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_reset(void)
{
    /*..hui [23-12-6오후 2:10:20] 여기는 사이드커버 닫고 Yes 선택했을때만 들어옴.....*/
    if( bit_filter_reset_yes == SET )
    {
        bit_filter_reset_yes = CLEAR;
    }
    else if( bit_filter_reset_no == SET )
    {
        bit_filter_reset_no = CLEAR;
        u8FilterResetState = FILTER_NO_CHANGE;
        return;
    }
    else
    {
        return;
    }

    if( bit_ct_flushing_standby_start == CLEAR )
    {
        /*..hui [24-2-21오후 3:26:49] CT 모드 아닐때..*/
        if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
        {
            if( u8FilterResetState == NEO_INO_FILTER_CHANGE )
            {
                gu8_filter_flushing_state = FILTER_FLUSHING_NEO_INO;
                reset_time_neo_filter();
                reset_time_ino_filter();

                send_wifi_system_function();
            }
            else
            {
                /*..hui [23-12-6오후 2:22:33] 1,3번 교체차례인데 1,2,3이 감지가되도 플러싱 진행..*/
                /*..hui [23-12-6오후 2:22:40] 단, 리셋은 1,3번만 한다..*/
                gu8_filter_flushing_state = FILTER_FLUSHING_RO;
                reset_time_neo_filter();
                reset_time_ino_filter();

                send_wifi_system_function();
            }

            /*..hui [24-1-30오전 10:50:10] 와이파이 필터 알람 1,3 해제..*/
            wifi_neo_ino_filter_alarm_stop();
        }
        else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
        {
            /*..hui [23-12-6오후 2:25:34] 1,2,3 차례에서는 전부 다 감지되야.....*/
            if( u8FilterResetState == ALL_NEO_INO_RO_FILTER_CHANGE )
            {
                gu8_filter_flushing_state = FILTER_FLUSHING_RO;
                reset_time_neo_filter();
                reset_time_ro_filter();
                reset_time_ino_filter();

                send_wifi_system_function();

                /*..hui [24-1-30오전 10:50:10] 와이파이 필터 알람 1,2,3 해제..*/
                wifi_neo_ro_ino_filter_alarm_stop();
            }
            else{}
        }
    }
    else
    {
        /*..hui [24-2-21오후 4:01:53] CT 강제 플러싱 모드에서는 개별로..*/
        if( Bit0_Neo_Filter_1_Reset_State == SET )
        {
            reset_time_neo_filter();
        }
        else{}

        if( Bit1_Ro_Filter_2_Reset_State == SET )
        {
            reset_time_ro_filter();
        }
        else{}

        if( Bit2_Ino_Filter_3_Reset_State == SET )
        {
            reset_time_ino_filter();
        }
        else{}

        /*..hui [24-2-21오후 5:03:18] display filter alarm 이쪽에서 초기화된거랑 기존거 경과일 확인해서 ..*/
        /*..hui [24-2-21오후 5:03:31] 필터 알람 종료 보내줄지 말지 결정..*/
        bit_filter_cycle_change = SET;

        /*..hui [24-2-21오후 4:05:00] CT 모드 플러싱은 무조건 RO로..*/
        gu8_filter_flushing_state = FILTER_FLUSHING_RO;
        /*..hui [24-2-21오후 4:10:12] CT 강제 플러싱 시작..*/
        /*..hui [24-2-21오후 4:10:22] 이후부터 전원 껐다 켜도 플러싱 무조건 해야함..*/
        gu8_ct_forced_flushing_start = SET;
        send_wifi_system_function();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reset_time_neo_filter(void)
{
    if( Bit0_Neo_Filter_1_Reset_State == SET )
    {
        Bit0_Neo_Filter_1_Reset_State = CLEAR;

        gu16_neo_filter_reset_timer_sec = 0;
        gu8_neo_filter_reset_timer_min = 0;
        gu8_neo_filter_reset_timer_hour = 0;

        gu16_reset_hour_neo_filter = 0;
        /*..hui [23-12-6오후 3:55:59] 물 사용량도 초기화..*/
        gu16_water_usage_neo_filter = 0;

        gu16_temporary_save_usage = 0;

        bit_wifi_neo_filter_1_reset = SET;
    }
    else{}


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reset_time_ro_filter(void)
{
    if( Bit1_Ro_Filter_2_Reset_State == SET )
    {
        Bit1_Ro_Filter_2_Reset_State = CLEAR;

        gu16_ro_filter_reset_timer_sec = 0;
        gu8_ro_filter_reset_timer_min = 0;
        gu8_ro_filter_reset_timer_hour = 0;

        gu16_reset_hour_ro_filter = 0;
        /*..hui [23-12-6오후 3:55:59] 물 사용량도 초기화..*/
        gu16_water_usage_ro_filter = 0;

        gu16_temporary_save_usage = 0;

        bit_wifi_ro_filter_2_reset = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void reset_time_ino_filter(void)
{
    if( Bit2_Ino_Filter_3_Reset_State == SET )
    {
        Bit2_Ino_Filter_3_Reset_State = CLEAR;

        gu16_ino_filter_reset_timer_sec = 0;
        gu8_ino_filter_reset_timer_min = 0;
        gu8_ino_filter_reset_timer_hour = 0;

        gu16_reset_hour_ino_filter = 0;
        /*..hui [23-12-6오후 3:55:59] 물 사용량도 초기화..*/
        gu16_water_usage_ino_filter = 0;

        gu16_temporary_save_usage = 0;

        bit_wifi_ino_filter_3_reset = SET;
    }
    else{}


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_filter_alarm(void)
{
    neo_filter_alarm();
    ro_filter_alarm();
    ino_filter_alarm();


    if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
    {
        /*..hui [23-12-6오후 3:58:59] 1,3번 교체주기일때..*/
        /*..hui [23-12-6오후 3:59:09] 1번이나 3번 둘중 하나라도 도달하면 표시..*/
        /*..hui [23-12-6오후 3:59:15] RO만 도달했을때는 미표시..*/
        if( bit_neo_filter_1_alarm == SET || bit_ino_filter_3_alarm == SET )
        {

            /*..hui [23-12-6오후 4:07:42] 표시할때는 INO/NEO 중 남은일수가 더 작은걸로 표시..*/
            /*..hui [24-2-16오후 1:50:47] 24시간마다 다시 보내주는거때문에 위치 이동..*/
            if( gu16_neo_filter_1_remain_day > gu16_ino_filter_3_remain_day  )
            {
                /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day;*/
                /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day / 24;*/
                /*..hui [24-1-9오후 3:26:31] 24 미만은 1로 표시해야함.. 1씩 올려줌..*/
                calc_remain_day( gu16_ino_filter_3_remain_day );
            }
            else
            {
                /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day;*/
                /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day / 24;*/
                calc_remain_day( gu16_neo_filter_1_remain_day );
            }


            if( bit_filter_alarm_start == CLEAR )
            {
                bit_filter_alarm_start = SET;
                /*..hui [24-1-10오후 3:18:31] 최초 1,3 필터알람 표시시.. 물 추출 종료되고 난 후에 1회 음성 출력..*/
                /*..hui [24-1-10오후 3:18:55] 1번과 3번 필터를 교체해주세요..*/
                bit_filter_alarm_1_3_voice = SET;

                /*..hui [24-1-30오전 10:43:04] 하나만 알람 떴어도 와이파이 알람은 1,3 세트로..*/
                /*..hui [24-2-16오후 1:20:55] 최초 알람 발생했을때 보내는거..*/
                wifi_neo_ino_filter_alarm_start();
                gu16_1_3_remain_day_before = gu16_display_filter_remain_day;
            }
            else
            {
                if( gu16_1_3_remain_day_before != gu16_display_filter_remain_day )
                {
                    gu16_1_3_remain_day_before = gu16_display_filter_remain_day;
                    /*..hui [24-2-16오후 1:23:19] 최초 보낸후에 24시간 경과시마다 또 보내줌..*/
                    wifi_neo_ino_filter_alarm_start();
                    send_wifi_system_function();
                }
                else{}
            }
        }
        else
        {
            if( bit_filter_alarm_start == SET )
            {
                bit_filter_alarm_start = CLEAR;

                /*..hui [24-2-19오전 9:26:20] 알람 표시중 주기 바꿔서 알람 해제될경우..*/
                if( bit_filter_cycle_change == SET )
                {
                    bit_filter_cycle_change = CLEAR;
                    wifi_neo_ino_filter_alarm_stop();
                    send_wifi_system_function();
                }
                else{}
            }
            else{}
        }

        #if 0
        if( bit_filter_alarm_start == SET )
        {
            /*..hui [23-12-6오후 4:07:42] 표시할때는 INO/NEO 중 남은일수가 더 작은걸로 표시..*/
            if( gu16_neo_filter_1_remain_day > gu16_ino_filter_3_remain_day  )
            {
                /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day;*/
                /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day / 24;*/
                /*..hui [24-1-9오후 3:26:31] 24 미만은 1로 표시해야함.. 1씩 올려줌..*/
                calc_remain_day( gu16_ino_filter_3_remain_day );
            }
            else
            {
                /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day;*/
                /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day / 24;*/
                calc_remain_day( gu16_neo_filter_1_remain_day );
            }
        }
        else{}
        #endif

        bit_filter_alarm_1_2_3_voice = CLEAR;
    }
    else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
    {
        /*..hui [23-12-6오후 4:01:30] 1,2,3번 교체주기일때..*/
        /*..hui [23-12-6오후 4:01:41] 2번만 도달해도 알람표시..*/
        /*..hui [23-12-6오후 4:01:55] 그 외 1,3번 감지되더라도 2번이 미감지면 무조건 미표시..*/
        /*if( bit_ro_filter_2_alarm == SET )*/
        /*..hui [23-12-19오전 9:19:41] 변경.. 셋중 하나라도 도달시 표시..*/
        if( bit_neo_filter_1_alarm == SET || bit_ro_filter_2_alarm == SET || bit_ino_filter_3_alarm == SET )
        {
            /*..hui [23-12-6오후 4:10:42] 표시할때는 RO 남은일수를 표시..*/
            /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day;*/
            ///////////////gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;


            /*..hui [23-12-19오전 9:29:05] B순서일때도 셋 중 하나라도 도달하면 알람 표시로 변경..*/
            /*..hui [23-12-19오전 9:29:19] 알람은 제일 빠른날짜 기준으로..*/
            /*..hui [24-2-16오후 1:50:47] 24시간마다 다시 보내주는거때문에 위치 이동..*/
            if( gu16_neo_filter_1_remain_day > gu16_ino_filter_3_remain_day  )
            {
                if( gu16_ino_filter_3_remain_day > gu16_ro_filter_2_remain_day )
                {
                    /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;*/
                    calc_remain_day( gu16_ro_filter_2_remain_day );
                }
                else
                {
                    /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day / 24;*/
                    calc_remain_day( gu16_ino_filter_3_remain_day );
                }
            }
            else
            {
                if( gu16_neo_filter_1_remain_day > gu16_ro_filter_2_remain_day )
                {
                    /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;*/
                    calc_remain_day( gu16_ro_filter_2_remain_day );
                }
                else
                {
                    /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day / 24;*/
                    calc_remain_day( gu16_neo_filter_1_remain_day );
                }
            }

            if( bit_filter_alarm_start == CLEAR )
            {
                bit_filter_alarm_start = SET;
                /*..hui [24-1-10오후 3:18:31] 최초 1,2,3 필터알람 표시시.. 물 추출 종료되고 난 후에 1회 음성 출력..*/
                /*..hui [24-1-10오후 3:18:55] 모든 필터를 교체해주세요..*/
                bit_filter_alarm_1_2_3_voice = SET;

                /*..hui [24-1-30오전 10:43:04] 하나만 알람 떴어도 와이파이 알람은 1,2,3 세트로..*/
                wifi_neo_ro_ino_filter_alarm_start();

                gu16_1_2_3_remain_day_before = gu16_display_filter_remain_day;
            }
            else
            {
                if( gu16_1_2_3_remain_day_before != gu16_display_filter_remain_day )
                {
                    gu16_1_2_3_remain_day_before = gu16_display_filter_remain_day;
                    /*..hui [24-2-16오후 1:23:19] 최초 보낸후에 24시간 경과시마다 또 보내줌..*/
                    wifi_neo_ro_ino_filter_alarm_start();
                    send_wifi_system_function();
                }
                else{}
            }
        }
        else
        {
            if( bit_filter_alarm_start == SET )
            {
                bit_filter_alarm_start = CLEAR;

                /*..hui [24-2-19오전 9:26:20] 알람 표시중 주기 바꿔서 알람 해제될경우..*/
                if( bit_filter_cycle_change == SET )
                {
                    bit_filter_cycle_change = CLEAR;
                    wifi_neo_ro_ino_filter_alarm_stop();
                    send_wifi_system_function();
                }
                else{}
            }
            else{}
        }


        #if 0
        if( bit_filter_alarm_start == SET )
        {
            /*..hui [23-12-6오후 4:10:42] 표시할때는 RO 남은일수를 표시..*/
            /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day;*/
            ///////////////gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;


            /*..hui [23-12-19오전 9:29:05] B순서일때도 셋 중 하나라도 도달하면 알람 표시로 변경..*/
            /*..hui [23-12-19오전 9:29:19] 알람은 제일 빠른날짜 기준으로..*/
            if( gu16_neo_filter_1_remain_day > gu16_ino_filter_3_remain_day  )
            {
                if( gu16_ino_filter_3_remain_day > gu16_ro_filter_2_remain_day )
                {
                    /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;*/
                    calc_remain_day( gu16_ro_filter_2_remain_day );
                }
                else
                {
                    /*gu16_display_filter_remain_day = gu16_ino_filter_3_remain_day / 24;*/
                    calc_remain_day( gu16_ino_filter_3_remain_day );
                }
            }
            else
            {
                if( gu16_neo_filter_1_remain_day > gu16_ro_filter_2_remain_day )
                {
                    /*gu16_display_filter_remain_day = gu16_ro_filter_2_remain_day / 24;*/
                    calc_remain_day( gu16_ro_filter_2_remain_day );
                }
                else
                {
                    /*gu16_display_filter_remain_day = gu16_neo_filter_1_remain_day / 24;*/
                    calc_remain_day( gu16_neo_filter_1_remain_day );
                }
            }
        }
        else{}
        #endif

        bit_filter_alarm_1_3_voice = CLEAR;
    }

    bit_filter_cycle_change = CLEAR;

    #if 0
    gu16_display_filter_remain_day = (U16)(FILTER_RESET_DAY__NEO_INO - gu16_reset_hour_neo_filter);

    if( gu16_display_filter_remain_day >= FILTER_RESET_DAY__NEO_INO )
    {
        gu16_display_filter_remain_day = FILTER_RESET_DAY__NEO_INO;
    }
    else{}

    /*..hui [23-6-26오후 7:26:26] WIFI 전송용..*/
    gu16_wifi_filter_remain_day = gu16_display_filter_remain_day;

    if( gu16_display_filter_remain_day <= FILTER_ALARM_BEFORE_30_DAYS__NEO_INO )
    {
        bit_filter_alarm_start = SET;
    }
    else
    {
        bit_filter_alarm_start = CLEAR;
    }


    if( gu16_display_filter_remain_day <= FILTER_ALARM_BEFORE_30_DAYS__NEO_INO )
    {
        /*..hui [23-6-8오후 1:17:28] 표시는 이노네오 기준이기 때문에.. 타이머 오차 고려해서 ..*/
        /*..hui [23-6-8오후 1:17:53] 네오이노가 30일 이전이고 RO가 60일 이전이면 ALL로 표시..*/
        if( gu16_reset_hour_ro_filter >= FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO - 60 )
        {
            gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_RO_INO_ALL;
        }
        else
        {
            gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
        }
    }
    else
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_remain_day( U16 mu16_day )
{
    U16 mu16_mod = 0;

    mu16_mod = (mu16_day % 24);

    if( mu16_mod == 0 )
    {
        gu16_display_filter_remain_day = mu16_day / 24;
    }
    else
    {
        gu16_display_filter_remain_day = mu16_day / 24;
        /*..hui [24-1-9오후 3:25:30] 24일 미만은 1일로 표시해야함.. 1씩 반올림..*/
        gu16_display_filter_remain_day = gu16_display_filter_remain_day + 1;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void neo_filter_alarm(void)
{
    /*..hui [24-2-16오전 10:42:35] 경과일이 교체주기보다 작을때..*/
    if( gu16_define_filter_period__neo > gu16_reset_hour_neo_filter )
    {
        /*..hui [24-2-16오전 10:42:44] 남은 시간..*/
        gu16_neo_filter_1_remain_day = (U16)(gu16_define_filter_period__neo - gu16_reset_hour_neo_filter);
    }
    else
    {
        gu16_neo_filter_1_remain_day = 0;
    }

    if( gu16_neo_filter_1_remain_day >= gu16_define_filter_period__neo )
    {
        gu16_neo_filter_1_remain_day = gu16_define_filter_period__neo;
    }
    else{}


    if( gu16_neo_filter_1_remain_day <= FILTER_ALARM_REMAIN_30_DAYS )
    {
        bit_neo_filter_1_alarm = SET;
    }
    else if( gu16_water_usage_neo_filter >= NEO_TOTAL_USAGE_MAX_WATER - FILTER_ALARM_REMAIN_315_LITER )
    {
        /*..hui [23-12-6오후 3:35:21] 필터 사용일보다 사용량이 빨리 도달하면 사용일을 426일로 변경..*/
        if (gu16_reset_hour_neo_filter < (gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS))
        {
            if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO)
            {
                gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            }
            else if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL)
            {
                gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ro_filter = gu16_define_filter_period__ro - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            }
            else{}
        }
        bit_neo_filter_1_alarm = CLEAR;
    }
    else
    {
        bit_neo_filter_1_alarm = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ro_filter_alarm(void)
{
    if( gu16_define_filter_period__ro > gu16_reset_hour_ro_filter )
    {
        gu16_ro_filter_2_remain_day = (U16)(gu16_define_filter_period__ro - gu16_reset_hour_ro_filter);
    }
    else
    {
        gu16_ro_filter_2_remain_day = 0;
    }

    if( gu16_ro_filter_2_remain_day >= gu16_define_filter_period__ro )
    {
        gu16_ro_filter_2_remain_day = gu16_define_filter_period__ro;
    }
    else{}


    if( gu16_ro_filter_2_remain_day <= FILTER_ALARM_REMAIN_30_DAYS )
    {
        bit_ro_filter_2_alarm = SET;
    }
    else if( gu16_water_usage_ro_filter >= RO_TOTAL_USAGE_MAX_WATER - FILTER_ALARM_REMAIN_315_LITER )
    {
        /*..hui [23-12-6오후 3:35:21] 필터 사용일보다 사용량이 빨리 도달하면 사용일을 426일로 변경..*/\
        if (gu16_reset_hour_ro_filter < (gu16_define_filter_period__ro - FILTER_ALARM_REMAIN_30_DAYS))
        {
            // if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO)
            // {
                // gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                // gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            // }
            // else if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL)
            if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL)
            {
                gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ro_filter = gu16_define_filter_period__ro - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            }
            else{}
        }
        bit_ro_filter_2_alarm = CLEAR;
    }
    else
    {
        bit_ro_filter_2_alarm = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ino_filter_alarm(void)
{

    if( gu16_define_filter_period__ino > gu16_reset_hour_ino_filter )
    {
        gu16_ino_filter_3_remain_day = (U16)(gu16_define_filter_period__ino - gu16_reset_hour_ino_filter);
    }
    else
    {
        gu16_ino_filter_3_remain_day = 0;
    }

    if( gu16_ino_filter_3_remain_day >= gu16_define_filter_period__ino )
    {
        gu16_ino_filter_3_remain_day = gu16_define_filter_period__ino;
    }
    else{}


    if( gu16_ino_filter_3_remain_day <= FILTER_ALARM_REMAIN_30_DAYS )
    {
        bit_ino_filter_3_alarm = SET;
    }
    else if( gu16_water_usage_ino_filter >= INO_TOTAL_USAGE_MAX_WATER - FILTER_ALARM_REMAIN_315_LITER )
    {
        /*..hui [23-12-6오후 3:35:21] 필터 사용일보다 사용량이 빨리 도달하면 사용일을 426일로 변경..*/
        if (gu16_reset_hour_ino_filter < (gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS))
        {
            if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO)
            {
                gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            }
            else if (gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL)
            {
                gu16_reset_hour_neo_filter = gu16_define_filter_period__neo - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ro_filter = gu16_define_filter_period__ro - FILTER_ALARM_REMAIN_30_DAYS;
                gu16_reset_hour_ino_filter = gu16_define_filter_period__ino - FILTER_ALARM_REMAIN_30_DAYS;
            }
            else{}
        }

        bit_ino_filter_3_alarm = CLEAR;
    }
    else
    {
        bit_ino_filter_3_alarm = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_filter_flushing(void)
{
    gu8_flushing_mode = FLUSHING_STANDBY_STATE;

    /*..hui [23-6-14오후 6:44:36] 필터 플러싱 한번 시작하면 취소 안되게..*/
    /*..hui [23-6-14오후 6:44:55] 이후에 다시 커버 열렸다 닫혀도 yes no 표시 안함..*/
    /*if( gu8_filter_flushing_state == FILTER_FLUSHING_NONE )*/

    /*..hui [23-9-1오전 9:44:25] 필터플러싱 모드도 아니고, 설치플러싱도 아닐때..*/
    /*..hui [23-9-1오전 9:44:44] 설치플러싱 => 사이드커버 열림 => 사이드커버 닫힘 => 취소 => 메인화면으로 돌아감..*/
    if( gu8_filter_flushing_state == FILTER_FLUSHING_NONE && bit_install_flushing_state == CLEAR )
    {
        bit_yes_no_popup = SET;

        /*..hui [24-1-11오전 10:48:12] 여기서도 초기화.. 설치 플러싱 종료 = 100% = 필터플러싱 바로 시작하면 100%로 시작됨..*/
        gu8_display_flushing_total_percent = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cancel_filter_flushing(void)
{
    /*play_melody_setting_off_199();*/

    play_voice_filter_flushing_cancle_25();
    gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
    gu8_flushing_mode = FLUSHING_NONE_STATE;

    if( bit_yes_no_popup == SET )
    {
        bit_yes_no_popup = CLEAR;
        bit_filter_reset_yes = CLEAR;
        bit_filter_reset_no = SET;
    }
    else{}

    /*..hui [24-2-21오후 4:11:06] CT 강제 플러싱 종료..*/
    finish_ct_forced_flushing();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_filter_data(void)
{
    gu16_reset_hour_neo_filter = 0;
    gu16_reset_hour_ro_filter = 0;
    gu16_reset_hour_ino_filter = 0;

    gu16_neo_filter_reset_timer_sec = 0;
    gu8_neo_filter_reset_timer_min = 0;
    gu8_neo_filter_reset_timer_hour = 0;

    gu16_ro_filter_reset_timer_sec = 0;
    gu8_ro_filter_reset_timer_min = 0;
    gu8_ro_filter_reset_timer_hour = 0;

    gu16_ino_filter_reset_timer_sec = 0;
    gu8_ino_filter_reset_timer_min = 0;
    gu8_ino_filter_reset_timer_hour = 0;

    gu16_water_usage_neo_filter = 0;
    gu16_water_usage_ro_filter = 0;
    gu16_water_usage_ino_filter = 0;

    gu16_temporary_save_usage = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





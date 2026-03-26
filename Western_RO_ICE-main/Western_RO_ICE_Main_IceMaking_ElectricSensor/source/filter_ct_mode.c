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
#include    "filter_ct_mode.h"

void ct_mode(void);
void key_change_filter_type(void);
void ct_forced_flushing_timeout_check(void);
void ct_filter_type_timeout_check(void);
void finish_ct_forced_flushing(void);

TYPE_BYTE          U8CTFilterReplaceB;
#define            gu8CTFilterReplace                           U8CTFilterReplaceB.byte
#define            Bit0_CT_Neo_Filter_1_Replace                 U8CTFilterReplaceB.Bit.b0
#define            Bit1_CT_Ro_Filter_2_Replace                  U8CTFilterReplaceB.Bit.b1
#define            Bit2_CT_Ino_Filter_3_Replace                 U8CTFilterReplaceB.Bit.b2


bit bit_ct_filter_type_start;
U8 gu8_ct_filter_type_return_time;


bit bit_ct_flushing_standby_start;
U16 gu16_ct_flushing_standby_return_time;

U8 gu8_ct_forced_flushing_start;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ct_mode(void)
{

    /*..hui [24-2-19오후 1:19:54] CT모드 필터 교체 주기 타입 변경시 10초간 버튼 입력 없으면 자동 종료..*/
    ct_filter_type_timeout_check();

    /*..hui [24-2-20오전 10:15:42] CT모드 강제 플러싱 15분간 교체없으면 자동 종료..*/
    ct_forced_flushing_timeout_check();

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_change_filter_type(void)
{
    gu8_ct_filter_type_return_time = 0;

    if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_RO_INO_ALL;
    }
    else
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
    }

    play_melody_setting_on_198();
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ct_filter_type_timeout_check(void)
{
    if( bit_ct_filter_type_start == SET )
    {
        /*..hui [23-8-2오전 9:45:42] 필터 열림 감지시 강제 종료..*/
        if( bit_filter_all == CLEAR )
        {
            gu8_ct_filter_type_return_time = 0;
            bit_ct_filter_type_start = CLEAR;
        }
        else{}

        gu8_ct_filter_type_return_time++;

        if( gu8_ct_filter_type_return_time >= 100 )
        {
            gu8_ct_filter_type_return_time = 0;
            bit_ct_filter_type_start = CLEAR;
            play_melody_setting_off_199();
        }
        else{}
    }
    else
    {
        gu8_ct_filter_type_return_time = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ct_forced_flushing_timeout_check(void)
{
    /*..hui [24-2-22오전 11:38:41] 필터 커버 열리면 시간 초기화....*/
    /*..hui [24-2-22오전 11:39:02] 닫힌채로 15분동안 아무것도 안하면 자동 종료..*/
    if( bit_filter_cover == CLEAR )
    {
        gu16_ct_flushing_standby_return_time = 0;
    }
    else{}

    /*..hui [24-2-22오전 11:41:24] 필터 교체 후 커버 닫아서 필터 플러싱 대기 상태로 진입하면 자동 종료 없음..*/
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        gu16_ct_flushing_standby_return_time = 0;
    }
    else{}

    /*..hui [24-2-22오전 11:41:42] 플러싱 시작하고나면 자동종료 없음..*/
    if( gu8_ct_forced_flushing_start == SET )
    {
        gu16_ct_flushing_standby_return_time = 0;
    }
    else{}


    if( bit_ct_flushing_standby_start == SET )
    {
        gu16_ct_flushing_standby_return_time++;

        if( gu16_ct_flushing_standby_return_time >= 9000 )
        {
            gu16_ct_flushing_standby_return_time = 0;
            play_melody_setting_off_199();

            finish_ct_forced_flushing();
        }
        else{}
    }
    else
    {
        gu16_ct_flushing_standby_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_ct_forced_flushing(void)
{

    /*..hui [24-2-21오후 4:11:06] CT 강제 플러싱 종료..*/
    gu8_ct_forced_flushing_start = CLEAR;
    /*..hui [24-2-21오후 5:11:30] CT 강제 플러싱 모드 종료..*/
    bit_ct_flushing_standby_start = CLEAR;

    /*..hui [24-2-22오전 11:10:04] 교체된 필터 상태 초기화..*/
    gu8CTFilterReplace = 0;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





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
#include    "my_cup.h"

void setting_my_cup(void);
void halt_my_cup_setting(void);
void success_my_cup_setting(void);
void start_my_cup_setting(void);
void finish_my_cup_setting(void);


bit bit_my_cup_setting_start;
U16 gu16_my_cup_setting_time;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_my_cup(void)
{
    if( bit_my_cup_setting_start == CLEAR )
    {
        gu16_my_cup_setting_time = 0;
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        gu16_my_cup_setting_time++;

        if(gu16_my_cup_setting_time >= u16Efluent_Time)
        {
            gu16_my_cup_setting_time = u16Efluent_Time;
        }
        else{}
    }
    else
    {
        if( gu16_my_cup_setting_time >= MY_CUP_SETTING_120mL_PURE_MIN )
        {
            gu16_my_cup_level_pure = gu16_my_cup_setting_time;
            gu16_my_cup_level_cold = gu16_my_cup_level_pure;

            if(gu16_my_cup_setting_time < EXTRACT_TIME_PURE_WATER_ONE)
            {
                gu16_my_cup_level_hot = (U16)(gu16_my_cup_setting_time * 1.5 + ((gu16_my_cup_setting_time / 10) * 2) );
            }
            else // gu16_my_cup_setting_time > EXTRACT_TIME_PURE_WATER_HALF
            {
                gu16_my_cup_level_hot = (U16)(gu16_my_cup_setting_time * 1.67);
            }

            success_my_cup_setting();
        }
        else{}
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void halt_my_cup_setting(void)
{
    /*..hui [23-3-23오후 2:51:44] 마이컵 설정 - 물 추출 중 최소 유량 미만 추출해서 종료될때..*/
    bit_my_cup_setting_start = CLEAR;
    bit_my_cup_enable = CLEAR;
    /*..hui [23-3-23오후 2:14:01] 다시 Set 표시 화면으로....*/
    start_set_flick( ON_OFF_DISPLAY_MY_CUP_SET );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void success_my_cup_setting(void)
{
    /*..hui [23-3-23오후 2:52:06] 마이컵 설정 - 물 추출 완료 성공..*/
    /*bit_my_cup_setting_start = CLEAR;*/
    bit_my_cup_enable = SET;
    start_my_cup_end_flick();

    gu16_my_cup_setting_time = 0;

    /*start_set_flick( ON_OFF_DISPLAY_OFF );*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_my_cup_setting(void)
{
    /*..hui [23-3-23오후 2:52:31] 마이컵 설정 - Set 표시 - 물 추출 시작부터 마이컵 세팅 시작..*/
    bit_my_cup_setting_start = SET;
    gu8_my_cup_setting_step = 0;
    bit_my_cup_finish_flick = CLEAR;

    /*..hui [23-3-23오후 2:02:41] Set 표시하던거 종료..*/
    start_set_flick( ON_OFF_DISPLAY_OFF );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_my_cup_setting(void)
{
    /*..hui [23-3-23오후 2:52:48] 마이컵 설정 - Off 선택하면 마이컵 끔..*/
    bit_my_cup_setting_start = CLEAR;
    bit_my_cup_enable = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




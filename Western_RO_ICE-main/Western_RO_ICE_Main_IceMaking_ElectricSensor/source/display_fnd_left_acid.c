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
#include    "display_fnd_left_acid.h"

void fnd_left_acid(void);

U8 gu8_acid_display_step;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_acid(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;


    if( gu8_acid_clean_mode == ACID_CLEAN_NONE_STATE )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_STANDBY )
    {
        if( Bit0_Acid_Error_Stop_State == SET )
        {
            /*..hui [24-7-26오후 1:37:27] 구연산 에러 표시..*/
            if( Bit3_Leakage_Sensor_Error__E01 == SET )
            {
                /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
            {
                /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else if( Bit16_Drain_Pump_Error__E60 == SET )
            {
                /*..hui [23-8-18오후 3:15:33] 탱크 플러싱 추가때문에.. 드레인펌프 고장일 경우 진행안됨..*/
                /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = DISPLAY_NUM_6;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( Bit4_Room_Low_Water_Level_Error__E21 == SET )
            {
                /*..hui [23-8-23오전 10:26:55] 탱크 플러싱 추가때문에.. 탱크 비워야하기 때문에 수위센서 에러면 진행못함..*/
                /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = DISPLAY_NUM_2;
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }
        }
        else if( Bit1_Acid_Cover_Open_Stop_State == SET )
        {
            if( bit_filter_cover == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_NUM_SMALL_d;
                mu8_temporary_ten = DISPLAY_NUM_SMALL_o;
                mu8_temporary_one = DISPLAY_NUM_SMALL_r;
            }
            else if( bit_neo_filter_1_reed == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
                mu8_temporary_one = DISPLAY_NUM_SMALL_b;
            }
            else if( bit_ro_filter_2_reed == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_SMALL_r;
                mu8_temporary_one = DISPLAY_NUM_SMALL_o;
            }
            else if( bit_ino_filter_3_reed == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_SMALL_u;
                mu8_temporary_one = DISPLAY_NUM_SMALL_b;
            }
            else{}
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE )
    {
        if( gu8_acid_prepare_step == 0 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 1;
        }
        else if( gu8_acid_prepare_step == 1 )
        {
            if( gu16_acid_prepare_max_timer <= 1200 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu16_acid_prepare_max_timer <= 2400 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_1;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu16_acid_prepare_max_timer <= 3600 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_2;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu16_acid_prepare_max_timer <= 4800 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_3;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu16_acid_prepare_max_timer <= 6000 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_4;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu16_acid_prepare_max_timer <= 7200 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_5;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else //if( gu16_acid_prepare_max_timer <= 8400 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_6;
                mu8_temporary_one = DISPLAY_NUM_0;
            }

            gu8_acid_display_step = 1;
        }
        else if( gu8_acid_prepare_step == 2 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_6;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 1;
        }
        else if( gu8_acid_prepare_step == 3 )
        {
            if( gu16_acid_prepare_max_timer <= 600 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_7;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_8;
                mu8_temporary_one = DISPLAY_NUM_0;
            }

            gu8_acid_display_step = 2;
        }
        else if( gu8_acid_prepare_step == 4 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_9;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 2;
        }
        else /*if( gu8_acid_prepare_step == 5 )*/
        {
            mu8_temporary_hundred = DISPLAY_NUM_1;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 2;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
    {
        if( gu8_acid_change_filter_step <= 1 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_d;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_o;
            mu8_temporary_one = DISPLAY_NUM_SMALL_r;
            gu8_acid_display_step = 3;
        }
        else if( gu8_acid_change_filter_step == 2 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_L;
            mu8_temporary_one = DISPLAY_NUM_SMALL_n;
            gu8_acid_display_step = 4;
        }
        else if( gu8_acid_change_filter_step == 3 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_r;
            mu8_temporary_one = DISPLAY_NUM_SMALL_o;
            gu8_acid_display_step = 5;
        }
        else if( gu8_acid_change_filter_step == 4 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = DISPLAY_NUM_SMALL_b;
            gu8_acid_display_step = 6;
        }
        else if( gu8_acid_change_filter_step == 5 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_d;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_o;
            mu8_temporary_one = DISPLAY_NUM_SMALL_r;
            gu8_acid_display_step = 7;
        }
        else /*if( gu8_acid_change_filter_step == 6 )*/
        {
             mu8_temporary_hundred = DISPLAY_OFF;
             mu8_temporary_ten = DISPLAY_OFF;
             mu8_temporary_one = DISPLAY_OFF;
             gu8_acid_display_step = 7;
        }
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR )
    {
        if( gu8_acid_wait_step == 0 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
        else if( gu8_acid_wait_step == 1 )
        {
            if( gu32_acid_wait_max_timer <= 9000 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu32_acid_wait_max_timer <= 18000 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_1;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if( gu32_acid_wait_max_timer <= 27000 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_2;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else /*if( gu32_acid_wait_max_timer <= 36000 )*/
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_NUM_3;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_3;
            mu8_temporary_one = DISPLAY_NUM_0;
        }

        gu8_acid_display_step = 8;
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
    {
        if( gu8_acid_rinse_step <= 1 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_4;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 9;
        }
        else if( gu8_acid_rinse_step >= 2 && gu8_acid_rinse_step <= 8 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_5;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 10;
        }
        else if( gu8_acid_rinse_step >= 9 && gu8_acid_rinse_step <= 10 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_6;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 11;
        }
        else if( gu8_acid_rinse_step == 11 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_7;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 12;
        }
        else /*if( gu8_acid_rinse_step >= 12 && gu8_acid_rinse_step <= 14 )*/
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 13;
        }

    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )
    {
        if( gu8_acid_finish_step <= 1 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_9;
            mu8_temporary_one = DISPLAY_NUM_0;
            gu8_acid_display_step = 14;
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_NUM_1;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_NUM_1;
        mu8_temporary_ten = DISPLAY_NUM_0;
        mu8_temporary_one = DISPLAY_NUM_0;
    }


    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





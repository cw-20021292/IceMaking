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
#include    "display_fnd_left_flushing.h"

void fnd_left_flushing_state(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_flushing_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;

    if( gu8_flushing_mode == FLUSHING_STANDBY_STATE || bit_flushing_halt == SET )
    {
        /*..hui [23-6-14오후 4:30:12] 플러싱 안되는 에러 발생시 에러번호 표시..*/
        if( Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            /*mu8_temporary_hundred = DISPLAY_OFF;*/
            /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_1;
        }
        else if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
        {
            /*mu8_temporary_hundred = DISPLAY_OFF;*/
            /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_9;
        }
        else if( Bit16_Drain_Pump_Error__E60 == SET )
        {
            /*..hui [23-8-18오후 3:15:33] 탱크 플러싱 추가때문에.. 드레인펌프 고장일 경우 진행안됨..*/
            /*mu8_temporary_hundred = DISPLAY_OFF;*/
            /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_6;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
        else if( Bit4_Room_Low_Water_Level_Error__E21 == SET )
        {
            /*..hui [23-8-23오전 10:26:55] 탱크 플러싱 추가때문에.. 탱크 비워야하기 때문에 수위센서 에러면 진행못함..*/
            /*mu8_temporary_hundred = DISPLAY_OFF;*/
            /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            /*mu8_temporary_ten = DISPLAY_NUM_1;*/
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
    else
    {
        if( gu8_display_flushing_total_percent < 100 )
        {
            if( gu8_display_flushing_total_percent == 0 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = (gu8_display_flushing_total_percent / 10);
                mu8_temporary_one = (gu8_display_flushing_total_percent % 10);
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_NUM_1;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





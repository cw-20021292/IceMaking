/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Fan_Control.h"




void output_fan(void);



TYPE_BYTE          U8CoolingFanONB;
#define            u8CoolingFanON                                U8CoolingFanONB.byte
#define            Bit0_CF_Comp_Operation_State                  U8CoolingFanONB.Bit.b0
#define            Bit1_CF_Fan_Delay_Operation_State             U8CoolingFanONB.Bit.b1
#define            Bit2_CF_Fan_First_Operation_State             U8CoolingFanONB.Bit.b2
#define            Bit3_CF_Acid_Clean_Operation_State            U8CoolingFanONB.Bit.b3




TYPE_BYTE          U8CoolingFanOFFB;
#define            u8CoolingFanOFF                       U8CoolingFanOFFB.byte
//#define            Bit0_Filling_Valve_Error_State                U8CoolingFanOFFB.Bit.b0

U16 gu16_fan_delay_timer;

bit bit_fan_first;
U16 gu16_fan_first_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_fan(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    Bit0_CF_Comp_Operation_State = F_Comp_Output;

    if( F_Comp_Output == SET )
    {
        /*..hui [23-5-17오후 6:40:40] 외기 온도 39도 이상일 경우 COMP OFF되도 10분 지연 후 꺼짐 추가..*/
        /*..hui [23-5-17오후 6:40:51] 저전압 고온에서 COMP 트립 현상.. 냉동..*/
        /*if( gu8_Amb_Temperature_One_Degree >= 39 )*/
        /*..hui [23-7-12오전 11:28:04] 외기 34도 이상일경우 COMP OFF 하고 5분 추가 가동 후 종료..*/
        /*..sean [25-02-24] 마진 부족으로 30 이상일 경우 fan 추가 제어..*/
        if( gu8_Amb_Temperature_One_Degree >= 30 )
        {
            Bit1_CF_Fan_Delay_Operation_State = SET;
            gu16_fan_delay_timer = 0;
        }
        else{}
    }
    else
    {
        if( Bit1_CF_Fan_Delay_Operation_State == SET )
        {
            gu16_fan_delay_timer++;

            /*..hui [23-5-17오후 6:40:17] 10분 지연 가동 후 FAN 정지..*/
            if( gu16_fan_delay_timer >= FAN_DELAY_10_MIN )
            {
                gu16_fan_delay_timer  = 0;
                Bit1_CF_Fan_Delay_Operation_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_fan_delay_timer = 0;
        }
    }

    if( bit_fan_first == CLEAR )
    {
        gu16_fan_first_timer++;

        /*..hui [23-7-12오전 11:21:08] 처음 전원켜고 더미탈빙 전 5분동안 FAN 가동 - 경종과장..*/
        if( gu16_fan_first_timer >= 3000 )
        {
            bit_fan_first = SET;

            gu16_fan_first_timer = 0;
            Bit2_CF_Fan_First_Operation_State = CLEAR;
        }
        else
        {
            Bit2_CF_Fan_First_Operation_State = SET;
        }
    }
    else
    {
        gu16_fan_first_timer = 0;
        Bit2_CF_Fan_First_Operation_State = CLEAR;
    }

/***********************************************************************************************/
    if (u8CoolingFanOFF > 0)
    {
        pDC_FAN = CLEAR;  /*off*/
    }
    else
    {
        if (u8CoolingFanON > 0)
        {
            pDC_FAN = SET; /*on*/
        }
        else
        {
            pDC_FAN = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



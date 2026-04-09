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
#include    "Comp_Control.h"

void output_comp_control(void);
void Air_Temp_Level(void);
void comp_stable_check(void);
U8 cold_init_operation( U8 mu8_disable );




TYPE_WORD          U16CompOnW;
#define            u16CompOn                               U16CompOnW.word
#define            u8CompOn_L                              U16CompOnW.byte[0]
#define            u8CompOn_H                              U16CompOnW.byte[1]
#define            Bit0_Cold_Mode_On_State                 U16CompOnW.Bit.b0
#define            Bit1_Ice_Make_On_State                  U16CompOnW.Bit.b1
#define            Bit2_Ice_Init_On_State                  U16CompOnW.Bit.b2




TYPE_WORD          U16CompOffW;
#define            u16CompOff                              U16CompOffW.word
#define            u8CompOff_L                             U16CompOffW.byte[0]
#define            u8CompOff_H                             U16CompOffW.byte[1]
#define            Bit0_Restart_5min_Delay_State           U16CompOffW.Bit.b0
#define            Bit1_Max_90min_CutOff_State             U16CompOffW.Bit.b1
#define            Bit2_Safty_Routine_State                U16CompOffW.Bit.b2
#define            Bit3_Ice_Making_Err_State               U16CompOffW.Bit.b3
#define            Bit4_Hot_Water_COMP_Off_State           U16CompOffW.Bit.b4




bit F_Comp_Output;
U16 gu16_Comp_fisrt_turn_on_timer;
U32 gu32_Comp_max_turn_on_timer;


U16 gu16_mid_temp_90s_keep_timer;

U16 gu16_air_temp_delay_sec_timer;
U16 gu16_air_temp_delay_min_timer;
U16 gu16_air_comp_restart_time;


U16 gu16_hot_water_comp_delay_tiemr;
bit F_Comp_On_Off_Decision;
U8 gu8_Comp_Stable_Time;
U8 gu8_Comp_Stable_State;

U8  gu8AirTempLevel;
U16 gu16CompOffDelay;

bit F_Cold_Operation_Init;
U8 gu8_cold_init_step;

U8 gu8_cold_setting_level;
U8 gu8_cold_setting_level_old;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_comp_control(void)
{

/***********************************************************************************************************/
/***********************************************************************************************************/
    /* ON */
    if(Bit0_Cold_Make_Go == SET)
    {
        Bit0_Cold_Mode_On_State = cold_init_operation( Bit0_Restart_5min_Delay_State );
    }
    else
    {
        Bit0_Cold_Mode_On_State = CLEAR;
        gu8_cold_init_step = 0;
    }

    if(gu8IceStep == STATE_31_MAIN_ICE_MAKING)
    {
        Bit1_Ice_Make_On_State = Bit1_Ice_Make_Go;
    }
    else
    {
        Bit1_Ice_Make_On_State = CLEAR;
    }

    if(gu8InitStep == 5)
    {
        if(gu16IceMakeTime > 0)
        {
            Bit2_Ice_Init_On_State = F_IceInit;
        }
        else
        {
            Bit2_Ice_Init_On_State = CLEAR;
        }
    }
    else
    {
        Bit2_Ice_Init_On_State = CLEAR;
    }

/***********************************************************************************************************/
/***********************************************************************************************************/
    /* OFF */
    //===========================================================================//
    /*..hui [18-10-23���� 3:24:08] COMP 150�� ���� ������ ���� ����..*/
    if( F_Comp_Output == CLEAR )
    {
        gu32_Comp_max_turn_on_timer = 0;
        Bit1_Max_90min_CutOff_State = CLEAR;
    }
    else
    {
        gu32_Comp_max_turn_on_timer++;

        if( gu32_Comp_max_turn_on_timer >= COMP_MAX_TURN_ON_150MIN_TIME )
        {
            gu32_Comp_max_turn_on_timer = COMP_MAX_TURN_ON_150MIN_TIME;

            /*..hui [19-7-26���� 8:53:31] ����� ��ȣ�ð� �ʰ��� �������� �������� �������ϰ� COMP OFF..*/
            if( gu8IceStep == STATE_0_STANDBY )
            {
                Bit1_Max_90min_CutOff_State = SET;
            }
            else{}
        }
        else
        {
            Bit1_Max_90min_CutOff_State = CLEAR;
        }
    }

    //===========================================================================//
    /*..hui [18-10-23���� 3:28:54] ���� ���� �� ���� �� �����ð� 5�� ���Ŀ� �� �ð� ���� ������ �� �ð� ����..*/
    if(F_Comp_Output == SET)
    {
        /*..hui [23-5-17���� 6:41:27] ���� ��⵿ ��� �ð� 8������ ����..*/
        /*..hui [23-5-17���� 6:41:36] ������ ���¿��� Ʈ�� ����.. �õ�..*/
        gu16CompOffDelay = COMP_START_TIME;
        Bit0_Restart_5min_Delay_State = CLEAR;
    }
    else
    {
        if(gu16CompOffDelay > 0)
        {
            /*..hui [22-9-15���� 9:31:22] ��������� ��� Ʈ�����̵� + �޼��ð��� �ֱ� ������ �ð� ����..*/
            if( gu8_Make_Mode == MAKE_ICE )
            {
                /*if( gu8_Amb_Temperature_One_Degree < 39 )*/
                /*..hui [23-8-17���� 10:47:05] �������� ��û..*/
                //if( gu8_Amb_Temperature_One_Degree < 40 )
                /*..sean [25-2-21 ] �������� ��û..*/
                //if( gu8_Amb_Temperature_One_Degree < 33 )
                /*..sean [25-2-25 ] �������� ��û �ŷڼ� ���� ��û���� 33�� �� 30���� ���� ..*/
                if( gu8_Amb_Temperature_One_Degree < 30 )
                {
                    /*..hui [23-5-17���� 6:44:59] 2�� �������� Ʈ���� �ø�..*/
                    /*if( gu16CompOffDelay <= 1200 )*/
                    /*..hui [23-5-17���� 7:09:08] 3�� �������� Ʈ���� �ø�..*/
                    /*..sean [25-03-20] 5�� �������� Ʈ���� �ø�..*/
                    if( gu16CompOffDelay <= 3000 )
                    {
                        gu16CompOffDelay = 1;
                    }
                    else{}
                }
                else{}
            }
            else{}

            gu16CompOffDelay--;                                   // ���� 5�� ��⵿���
            Bit0_Restart_5min_Delay_State = SET;
        }
        else
        {
            Bit0_Restart_5min_Delay_State = CLEAR;
        }
    }

    //===========================================================================//
    /*..hui [19-12-18���� 7:26:16] �ð�/���� �� �� �����ϋ�..*/
    Bit3_Ice_Making_Err_State = (Bit2_Ice_Operation_Disable_State & Bit0_Cold_Operation_Disable_State);


    //===========================================================================//
/***********************************************************************************************************/

    if (u16CompOff > 0)
    {
        pCOMP = CLEAR;            /*off*/
        F_Comp_Output = CLEAR;
    }
    else
    {
        if (u16CompOn > 0)
        {
            pCOMP = SET; /*on*/
            F_Comp_Output = SET;
        }
        else
        {
            pCOMP = CLEAR;  /*off*/
            F_Comp_Output = CLEAR;
        }
    }

    /*..hui [20-2-12���� 7:27:14] �¼� �����߿��� ���� ���� �����Ƿ� �ʿ����..*/
    comp_stable_check();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_stable_check(void)
{
    if(F_Comp_Output == CLEAR)
    {
        gu8_Comp_Stable_Time = 0;
        gu8_Comp_Stable_State = SET;
    }
    else
    {
        gu8_Comp_Stable_Time++;

        if(gu8_Comp_Stable_Time >= COMP_STABLE_TIME)
        {
            gu8_Comp_Stable_Time = COMP_STABLE_TIME;
            gu8_Comp_Stable_State = SET;
        }
        else
        {
            gu8_Comp_Stable_State = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 cold_init_operation( U8 mu8_disable )
{
    U8 mu8_return = 0;

    if(mu8_disable == SET)
    {
        return mu8_return;
    }
    else{}

    switch(gu8_cold_init_step)
    {
        case 0:

            GasSwitchCold();
            gu8_cold_init_step++;

        break;

        case 1:

            if(gu8_GasSwitch_Status == GAS_SWITCH_COLD)
            {
                gu8_cold_init_step++;
            }
            else{}

        break;

        case 2:

            mu8_return = SET;

        break;

        default:

            gu8_cold_init_step = 0;

        break;
    }

    /*..hui [19-7-26���� 4:47:09] ���� �������̶�� �������� ��� �ü������� �̵�..*/
    if(F_Comp_Output == SET)
    {
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



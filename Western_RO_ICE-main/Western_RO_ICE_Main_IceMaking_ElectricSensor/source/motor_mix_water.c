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
#include    "motor_mix_water.h"


/*..hui [23-9-18오후 5:28:13] 냉수 믹싱 모터 삭제..*/
#if 0
void ControlMixFlow(void);
U8 Init_Flow(void);
U8 Increase_Flow( void );
U8 Decrease_flow( void );
void HAL_ControlMixMotor( void );
void MIX_Motor_MoveStep( void );
void Mix_Motor_Operation( U8 mode );
void run_init_flow(void);
void run_increase_flow( U16 mu16_move );
void run_decrease_flow( U16 mu16_move );
void run_target_flow( U16 mu16_target );
#endif

U16 gu16_flow_info_target;
U16 gu16_flow_info_current;

U8 gu8_flow_hold_start_step;
U8 gu8_flow_hold_stop_step;


U8 gu8_flow_info_current_step;
U8 gu8_flow_info_prev_step;

const U8 gu8FlowPhaseTable[ FLOW_STEP_NUM ] =
{ 0x01, 0x02, 0x03, 0x04 };


U8 gu8_hot_flow_mode;

U8 gu8_flow_init_step;
U8 gu8_flow_increase_step;
U8 gu8_flow_decrease_step;


U16 gu16_increase_pulse;
U16 gu16_decrease_pulse;

U16 gu16_moving_pulse;

U8 gu8_aaa;
U8 gu8_bbb;
U16 gu16_aaaaaaaaa;
U16 gu16_bbbbbbbbb;

U8 gu8_hot_flow_status;
U8 gu8_ccc;
U16 gu16_ccccc;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void ControlMixFlow(void)
{
    U8 mu8Ret = FALSE;

/////#if 0
    if( gu8_aaa == 1 )
    {
        gu8_aaa  = 0;
        /////run_increase_flow(gu16_aaaaaaaaa);
        run_increase_flow(gu16_aaaaaaaaa);
    }
    else{}


    if( gu8_bbb == 1 )
    {
        gu8_bbb  = 0;
        run_decrease_flow(gu16_bbbbbbbbb);
    }
    else{}


    if( gu8_ccc == 1 )
    {
        gu8_ccc = 0;
        run_target_flow(gu16_ccccc);
    }
    else{}
/////#endif

    /* Init */
    if( gu8_hot_flow_mode == FLOW_MODE_INIT )
    {
        mu8Ret = Init_Flow();
        if( mu8Ret == TRUE )
        {
            gu8_hot_flow_mode = FLOW_MODE_NONE;
            gu8_flow_init_step = 0;

            gu8_hot_flow_status = HOT_FLOW_MAX_CLOSE;
        }
        else{}

        return;
    }

    /* Open */
    if( gu8_hot_flow_mode == FLOW_MODE_INCREASE )
    {
        mu8Ret = Increase_Flow();
        if( mu8Ret == TRUE )
        {
            gu8_hot_flow_mode = FLOW_MODE_NONE;
            gu8_flow_increase_step = 0;

            if( gu16_flow_info_current >= MAX_INCREASE_FLOW )
            {
                gu8_hot_flow_status = HOT_FLOW_MAX_OPEN;
            }
            else
            {
                gu8_hot_flow_status = HOT_FLOW_MOVING;
            }

            /////gu8_hot_45_moving_finish = HOT_FLOW_INCREASE_FINISH;
            gu8_hot_45_moving_finish = SET;
        }
        else{}

        return;
    }

    /* Close */
    if( gu8_hot_flow_mode == FLOW_MODE_DECREASE )
    {
        mu8Ret = Decrease_flow();
        if( mu8Ret == TRUE )
        {
            gu8_hot_flow_mode = FLOW_MODE_NONE;
            gu8_flow_decrease_step = 0;

            if( gu16_flow_info_current == 0 )
            {
                gu8_hot_flow_status = HOT_FLOW_MAX_CLOSE;
            }
            else
            {
                gu8_hot_flow_status = HOT_FLOW_MOVING;
            }

            gu8_hot_45_moving_finish = SET;
        }
        else{}

        return;
    }
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 Init_Flow(void)
{
    switch( gu8_flow_init_step )
    {
        case 0:

            gu16_flow_info_target = 0;

            gu16_flow_info_current = FLOW_VALVE_MAX_OPEN;
            gu16_flow_info_target = 0;

            gu8_flow_init_step++;
            break;

        case 1:

            if( gu16_flow_info_target == gu16_flow_info_current )
            {
                gu16_flow_info_target = 0;
                gu16_flow_info_current = 0;
                gu8_flow_init_step++;
            }
            break;

        case 2:

            //gu16_flow_info_target = (U16)(FLOW_VALVE_MAX_OPEN - FLOW_VALVE_ADJUST);
            gu16_flow_info_target = FLOW_VALVE_ADJUST;

            gu8_flow_init_step++;
            break;

        case 3:

            if( gu16_flow_info_target == gu16_flow_info_current )
            {
                gu16_flow_info_target = 0;
                gu16_flow_info_current = 0;
                gu8_flow_init_step++;
            }
            break;

        case 4:
            return TRUE;

    }

    return FALSE;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 Decrease_flow( void )
{
    switch( gu8_flow_decrease_step )
    {
        case 0:

            gu8_flow_hold_start_step = FLOW_HOLD_STEP;
            gu8_flow_hold_stop_step = FLOW_HOLD_STEP;

            if( gu16_flow_info_target > gu16_moving_pulse )
            {
                gu16_flow_info_target = gu16_flow_info_target - gu16_moving_pulse;
            }
            else
            {
                gu16_flow_info_target = 0;
            }

            gu8_flow_decrease_step++;

            break;

        case 1:

            if( gu16_flow_info_target == gu16_flow_info_current )
            {
                gu8_flow_decrease_step++;
                gu16_moving_pulse = 0;
            }
            else{}

            break;

        case 2:
            return TRUE;

    }

    return FALSE;

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 Increase_Flow( void )
{
    switch( gu8_flow_increase_step )
    {
        case 0:

            gu8_flow_hold_start_step = FLOW_HOLD_STEP;
            gu8_flow_hold_stop_step = FLOW_HOLD_STEP;

            gu16_flow_info_target = gu16_flow_info_target + gu16_moving_pulse;

            gu8_flow_increase_step++;
            break;

        case 1:

            if( gu16_flow_info_target == gu16_flow_info_current )
            {
                gu8_flow_increase_step++;
                gu16_moving_pulse = 0;
                /////bit_first_delay = 1;
            }
            break;

        case 2:
            return TRUE;

    }

    return FALSE;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void HAL_ControlMixMotor( void )
{
    S16 val = 0;
    S16 target = 0;
    S16 current = 0;


    /* CALC STEP, TARGET - CURRENT */

    //if( gu16_flow_info_target != gu16_flow_info_current )
    if( gu16_flow_info_target != gu16_flow_info_current )
    {
        //gu16_flow_info_move_step = gu16_flow_info_target - gu16_flow_info_current;

        //gu8_flow_hold_start_step = FLOW_HOLD_STEP;
        //gu8_flow_hold_stop_step = FLOW_HOLD_STEP;
    }
    else{}

    MIX_Motor_MoveStep();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void MIX_Motor_MoveStep( void )
{
    U8 val = 0;

    /* START HOLD */
    if( gu8_flow_hold_start_step > 0 )
    {
        gu8_flow_hold_start_step--;
        val = gu8FlowPhaseTable[ gu8_flow_info_prev_step ];
    }
    else if( gu16_flow_info_current == gu16_flow_info_target )
    {
        /* STOP HOLD */
        if( gu8_flow_hold_stop_step > 0 )
        {
            gu8_flow_hold_stop_step--;
            val = gu8FlowPhaseTable[ gu8_flow_info_current_step ];
        }
        else
        {
            /* STOP */
            val = 0x00;
        }
    }
    /* MOVE FORWARD */
    else if( gu16_flow_info_current < gu16_flow_info_target )
    {
        /* OPEN */
        /*..hui [21-6-24오후 2:24:48] 이쪽이 유량 줄이기로..*/
        gu16_flow_info_current++;

        if(gu8_flow_info_current_step == 0)
        {
            gu8_flow_info_current_step = FLOW_STEP_NUM - 1;
        }
        else
        {
            gu8_flow_info_current_step--;
        }

        gu8_flow_info_prev_step = gu8_flow_info_current_step;

        val = gu8FlowPhaseTable[ gu8_flow_info_current_step ];
    }
    /* MOVE BACKWARD */
    else if( gu16_flow_info_current > gu16_flow_info_target )
    {
        /* CLOSE */
        gu16_flow_info_current--;

        gu8_flow_info_current_step++;
        if( gu8_flow_info_current_step >= FLOW_STEP_NUM )
        {
            gu8_flow_info_current_step = 0;
        }
        else{}

        gu8_flow_info_prev_step = gu8_flow_info_current_step;

        val = gu8FlowPhaseTable[ gu8_flow_info_current_step ];
    }
    else{}

    Mix_Motor_Operation( val );
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Mix_Motor_Operation( U8 mode )
{
    switch( mode )
    {
        case 0:

            pSTEP_MOTOR_COLD_MIX_1  = 0;
            pSTEP_MOTOR_COLD_MIX_2  = 0;
            pSTEP_MOTOR_COLD_MIX_3  = 0;
            pSTEP_MOTOR_COLD_MIX_4  = 0;

            break;

        case 1:

            pSTEP_MOTOR_COLD_MIX_1 = 1;
            pSTEP_MOTOR_COLD_MIX_2 = 0;
            pSTEP_MOTOR_COLD_MIX_3 = 0;
            pSTEP_MOTOR_COLD_MIX_4 = 1;

            break;

        case 2:

            pSTEP_MOTOR_COLD_MIX_1 = 0;
            pSTEP_MOTOR_COLD_MIX_2 = 0;
            pSTEP_MOTOR_COLD_MIX_3 = 1;
            pSTEP_MOTOR_COLD_MIX_4 = 1;


            break;

        case 3:

            pSTEP_MOTOR_COLD_MIX_1 = 0;
            pSTEP_MOTOR_COLD_MIX_2 = 1;
            pSTEP_MOTOR_COLD_MIX_3 = 1;
            pSTEP_MOTOR_COLD_MIX_4 = 0;

            break;

        case 4:

            pSTEP_MOTOR_COLD_MIX_1 = 1;
            pSTEP_MOTOR_COLD_MIX_2 = 1;
            pSTEP_MOTOR_COLD_MIX_3 = 0;
            pSTEP_MOTOR_COLD_MIX_4 = 0;

            break;

        default:

        pSTEP_MOTOR_COLD_MIX_1  = 0;
        pSTEP_MOTOR_COLD_MIX_2  = 0;
        pSTEP_MOTOR_COLD_MIX_3  = 0;
        pSTEP_MOTOR_COLD_MIX_4  = 0;

        break;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_init_flow(void)
{
    gu8_hot_flow_mode = FLOW_MODE_INIT;
    gu8_flow_init_step = 0;
    gu8_flow_increase_step = 0;
    gu8_flow_decrease_step = 0;
    gu16_moving_pulse = 0;

    gu8_flow_hold_start_step = FLOW_HOLD_STEP;
    gu8_flow_hold_stop_step = FLOW_HOLD_STEP;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_increase_flow( U16 mu16_move )
{
    /*..hui [21-8-4오전 11:30:58] 유량 늘림..*/
    gu8_hot_flow_mode = FLOW_MODE_INCREASE;
    gu8_flow_decrease_step = 0;

    gu8_flow_hold_start_step = FLOW_HOLD_STEP;
    gu8_flow_hold_stop_step = FLOW_HOLD_STEP;

    if( (gu16_flow_info_target + mu16_move) >= MAX_INCREASE_FLOW )
    {
        gu16_moving_pulse = MAX_INCREASE_FLOW - gu16_flow_info_target;
    }
    else
    {
        gu16_moving_pulse = mu16_move;
    }

    /////gu8_hot_45_moving_finish = HOT_FLOW_INCREASE_MOVING;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_decrease_flow( U16 mu16_move )
{
    /*..hui [21-8-4오전 9:34:59] 유량 줄임.. 펄스는 원점에서 늘림..*/
    gu8_hot_flow_mode = FLOW_MODE_DECREASE;
    gu8_flow_increase_step = 0;

    gu8_flow_hold_start_step = FLOW_HOLD_STEP;
    gu8_flow_hold_stop_step = FLOW_HOLD_STEP;

    if( mu16_move > gu16_flow_info_target )
    {
        gu16_moving_pulse = gu16_flow_info_target;
    }
    else
    {
        gu16_moving_pulse = mu16_move;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_target_flow( U16 mu16_target )
{
    U16 mu16_moving = 0;

    if( gu16_flow_info_current > mu16_target )
    {
        mu16_moving = gu16_flow_info_current - mu16_target;
        run_decrease_flow( mu16_moving );
    }
    else if( gu16_flow_info_current < mu16_target )
    {
        mu16_moving = mu16_target - gu16_flow_info_current;
        run_increase_flow( mu16_moving );
    }
    else
    {
        gu8_hot_45_moving_finish = SET;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





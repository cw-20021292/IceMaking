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
#include    "motor_ro_drain.h"





void ControlRoDrain(void);
U8 Init_Ro_Drain(void);
U8 Open_RO_Drain( void );
U8 Close_RO_Drain( void );
void HAL_ControlRoDrainMotor( void );
void RO_Drain_Motor_MoveStep( void );
void Ro_Drain_Motor_Operation( U8 mode );
void run_init_ro_drain(void);
void run_open_ro_drain(void);
void run_close_ro_drain(void);


U16 gu16_ro_drain_target;
U16 gu16_ro_drain_current;

U8 gu8_ro_drain_hold_start_step;
U8 gu8_ro_drain_hold_stop_step;


U8 gu8_ro_drain_current_step;
U8 gu8_ro_drain_prev_step;

const U8 gu8rRoDrainPhaseTable[ RO_DRAIN_STEP_NUM ] =
{ 0x01, 0x02, 0x03, 0x04 };


U8 gu8_ro_drain_mode;

U8 gu8_ro_drain_init_step;
U8 gu8_ro_drain_open_step;
U8 gu8_ro_drain_close_step;


U16 gu16_ro_drain_open_pulse;
U16 gu16_ro_drain_close_pulse;

U16 gu16_ro_drain_moving_pulse;

U8 gu8_11111111;
U8 gu8_22222222;
U8 gu8_ro_drain_status;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ControlRoDrain(void)
{
    U8 mu8Ret = FALSE;

    #if 0
    if( gu8_11111111 == 1 )
    {
        gu8_11111111  = 0;
        run_open_ro_drain();
    }
    else{}


    if( gu8_22222222 == 1 )
    {
        gu8_22222222  = 0;
        run_close_ro_drain();
    }
    else{}
    #endif

    /* Init */
    if( gu8_ro_drain_mode == RO_DRAIN_MODE_INIT )
    {
        mu8Ret = Init_Ro_Drain();
        if( mu8Ret == TRUE )
        {
            gu8_ro_drain_mode = RO_DRAIN_MODE_NONE;
            gu8_ro_drain_init_step = 0;
            gu8_ro_drain_status = RO_DRAIN_STATUS_CLOSE;
        }
        else{}

        return;
    }

    /* Open */
    if( gu8_ro_drain_mode == RO_DRAIN_MODE_OPEN )
    {
        mu8Ret = Open_RO_Drain();
        if( mu8Ret == TRUE )
        {
            gu8_ro_drain_mode = RO_DRAIN_MODE_NONE;
            gu8_ro_drain_open_step = 0;
            gu8_ro_drain_status = RO_DRAIN_STATUS_OPEN;

        }
        else{}

        return;
    }

    /* Close */
    if( gu8_ro_drain_mode == RO_DRAIN_MODE_CLOSE )
    {
        mu8Ret = Close_RO_Drain();
        if( mu8Ret == TRUE )
        {
            gu8_ro_drain_mode = RO_DRAIN_MODE_NONE;
            gu8_ro_drain_close_step = 0;
            gu8_ro_drain_status = RO_DRAIN_STATUS_CLOSE;

        }
        else{}

        return;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 Init_Ro_Drain(void)
{
    switch( gu8_ro_drain_init_step )
    {
        case 0:

            gu16_ro_drain_target = 0;

            gu16_ro_drain_current = RO_DRAIN_MAX_CLOSE;
            gu16_ro_drain_target = 0;

            gu8_ro_drain_init_step++;
            break;

        case 1:

            if( gu16_ro_drain_target == gu16_ro_drain_current )
            {
                gu16_ro_drain_target = 0;
                gu16_ro_drain_current = 0;
                gu8_ro_drain_init_step++;
            }
            break;

        case 2:

            //gu16_ro_drain_target = (U16)(FLOW_VALVE_MAX_OPEN - FLOW_VALVE_ADJUST);
            gu16_ro_drain_target = RO_DRAIN_INIT_ADJUST;
            gu8_ro_drain_init_step++;
            break;

        case 3:

            if( gu16_ro_drain_target == gu16_ro_drain_current )
            {
                gu16_ro_drain_target = 0;
                gu16_ro_drain_current = 0;
                gu8_ro_drain_init_step++;
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
U8 Open_RO_Drain( void )
{
    switch( gu8_ro_drain_open_step )
    {
        case 0:

            gu8_ro_drain_hold_start_step = RO_DRAIN_HOLD_STEP;
            gu8_ro_drain_hold_stop_step = RO_DRAIN_HOLD_STEP;

            #if 0
            if( gu16_ro_drain_target > gu16_ro_drain_moving_pulse )
            {
                gu16_ro_drain_target = gu16_ro_drain_target - gu16_ro_drain_moving_pulse;
            }
            else
            {
                gu16_ro_drain_target = 0;
            }
            #endif

            gu16_ro_drain_target = RO_DRAIN_OPEN_PULSE;

            gu8_ro_drain_open_step++;

            break;

        case 1:

            if( gu16_ro_drain_target == gu16_ro_drain_current )
            {
                gu8_ro_drain_open_step++;
                gu16_ro_drain_moving_pulse = 0;
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
U8 Close_RO_Drain( void )
{
    switch( gu8_ro_drain_close_step )
    {
        case 0:

            gu8_ro_drain_hold_start_step = RO_DRAIN_HOLD_STEP;
            gu8_ro_drain_hold_stop_step = RO_DRAIN_HOLD_STEP;

            /*gu16_ro_drain_target = gu16_ro_drain_target + gu16_ro_drain_moving_pulse;*/
            gu16_ro_drain_target = 0;

            gu8_ro_drain_close_step++;
            break;

        case 1:

            if( gu16_ro_drain_target == gu16_ro_drain_current )
            {
                gu8_ro_drain_close_step++;
                gu16_ro_drain_moving_pulse = 0;
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
void HAL_ControlRoDrainMotor( void )
{
    S16 val = 0;
    S16 target = 0;
    S16 current = 0;


    /* CALC STEP, TARGET - CURRENT */
    RO_Drain_Motor_MoveStep();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void RO_Drain_Motor_MoveStep( void )
{
    U8 val = 0;

    /* START HOLD */
    if( gu8_ro_drain_hold_start_step > 0 )
    {
        gu8_ro_drain_hold_start_step--;
        val = gu8rRoDrainPhaseTable[ gu8_ro_drain_prev_step ];
    }
    else if( gu16_ro_drain_current == gu16_ro_drain_target )
    {
        /* STOP HOLD */
        if( gu8_ro_drain_hold_stop_step > 0 )
        {
            gu8_ro_drain_hold_stop_step--;
            val = gu8rRoDrainPhaseTable[ gu8_ro_drain_current_step ];
        }
        else
        {
            /* STOP */
            val = 0x00;
        }
    }
    /* MOVE FORWARD */
    else if( gu16_ro_drain_current < gu16_ro_drain_target )
    {
        /* OPEN */
        /*..hui [21-6-24오후 2:24:48] 이쪽이 유량 줄이기로..*/
        gu16_ro_drain_current++;

        if(gu8_ro_drain_current_step == 0)
        {
            gu8_ro_drain_current_step = RO_DRAIN_STEP_NUM - 1;
        }
        else
        {
            gu8_ro_drain_current_step--;
        }

        gu8_ro_drain_prev_step = gu8_ro_drain_current_step;

        val = gu8rRoDrainPhaseTable[ gu8_ro_drain_current_step ];
    }
    /* MOVE BACKWARD */
    else if( gu16_ro_drain_current > gu16_ro_drain_target )
    {
        /* CLOSE */
        gu16_ro_drain_current--;

        gu8_ro_drain_current_step++;
        if( gu8_ro_drain_current_step >= RO_DRAIN_STEP_NUM )
        {
            gu8_ro_drain_current_step = 0;
        }
        else{}

        gu8_ro_drain_prev_step = gu8_ro_drain_current_step;

        val = gu8rRoDrainPhaseTable[ gu8_ro_drain_current_step ];
    }
    else{}

    Ro_Drain_Motor_Operation( val );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ro_Drain_Motor_Operation( U8 mode )
{
    switch( mode )
    {
        case 0:
            pSTEP_MOTOR_RO_DRAIN_1  = 0;
            pSTEP_MOTOR_RO_DRAIN_2  = 0;
            pSTEP_MOTOR_RO_DRAIN_3  = 0;
            pSTEP_MOTOR_RO_DRAIN_4  = 0;

            break;

        case 1:
            pSTEP_MOTOR_RO_DRAIN_1 = 1;
            pSTEP_MOTOR_RO_DRAIN_2 = 0;
            pSTEP_MOTOR_RO_DRAIN_3 = 0;
            pSTEP_MOTOR_RO_DRAIN_4 = 1;

            break;

        case 2:
            pSTEP_MOTOR_RO_DRAIN_1 = 1;
            pSTEP_MOTOR_RO_DRAIN_2 = 1;
            pSTEP_MOTOR_RO_DRAIN_3 = 0;
            pSTEP_MOTOR_RO_DRAIN_4 = 0;

            break;

        case 3:
            pSTEP_MOTOR_RO_DRAIN_1 = 0;
            pSTEP_MOTOR_RO_DRAIN_2 = 1;
            pSTEP_MOTOR_RO_DRAIN_3 = 1;
            pSTEP_MOTOR_RO_DRAIN_4 = 0;

            break;
        case 4:
            pSTEP_MOTOR_RO_DRAIN_1 = 0;
            pSTEP_MOTOR_RO_DRAIN_2 = 0;
            pSTEP_MOTOR_RO_DRAIN_3 = 1;
            pSTEP_MOTOR_RO_DRAIN_4 = 1;

            break;
        default:
            pSTEP_MOTOR_RO_DRAIN_1  = 0;
            pSTEP_MOTOR_RO_DRAIN_2  = 0;
            pSTEP_MOTOR_RO_DRAIN_3  = 0;
            pSTEP_MOTOR_RO_DRAIN_4  = 0;
            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_init_ro_drain(void)
{
    gu8_ro_drain_mode = RO_DRAIN_MODE_INIT;
    gu8_ro_drain_init_step = 0;
    gu8_ro_drain_open_step = 0;
    gu8_ro_drain_close_step = 0;
    gu16_ro_drain_moving_pulse = 0;

    gu8_ro_drain_hold_start_step = RO_DRAIN_HOLD_STEP;
    gu8_ro_drain_hold_stop_step = RO_DRAIN_HOLD_STEP;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_open_ro_drain(void)
{
    gu8_ro_drain_mode = RO_DRAIN_MODE_OPEN;
    gu8_ro_drain_close_step = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_close_ro_drain(void)
{
    gu8_ro_drain_mode = RO_DRAIN_MODE_CLOSE;
    gu8_ro_drain_open_step = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



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
#include    "tray_pump_control.h"


void output_tray_pump(void);
U16 confirm_tray_pump_pwm(void);
void start_tray_pump( U16 u16_data );
void stop_tray_pump( void );


TYPE_BYTE          U8TrayPumpONB;
#define            u8TrayPumpON                              U8TrayPumpONB.byte
#define            Bit0_Ice_Tray_Water_Input_State          U8TrayPumpONB.Bit.b0
#define            Bit1_Safty_Ice_Melt_State                U8TrayPumpONB.Bit.b1




TYPE_BYTE          U8TrayPumpOFFB;
#define            u8TrayPumpOFF                             U8TrayPumpOFFB.byte
#define            Bit0_Tray_Pump_Low_Water_Off_State        U8TrayPumpOFFB.Bit.b0


U8 gu8_trayvalve_wait_timer;
U16 gu16_hot_pump_pwm_out;
bit bit_tray_pump_output;

U16 gu16_adjust_hot_pwm;
U16 gu16_adjust_preheat_pwm;


U8 gu8_hot_pump_starting_timer;

U16 gu16_current_hot_pwm;


U8 gu8_hot_first_full_timer;

U8 gu8_ice_melt_wait_timer;

U8 gu8_steam_drain_timer;
U8 gu8_preheat_steam_state;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_tray_pump(void)
{
    U8 mu8_preheat_state = 0;

    /***************************************************************************************************/
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        /*..hui [19-8-27오후 7:26:07] 온수 추출 뿐만아니라 냉수/정수 추출중에도 잠시 대기..*/
        /*if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)*/
        /*..hui [19-8-28오후 2:44:21] 트레이 입수 안될경우 재시도 대기 시간동안 OFF 추가..*/
        if( F_WaterOut == SET )
           /*|| F_Tray_In_Error_Temporary  == SET)*/
        {
            /*..hui [19-7-23오후 5:14:13] 온수 추출하면 끄자..*/
            gu8_trayvalve_wait_timer = 0;
            Bit0_Ice_Tray_Water_Input_State = CLEAR;
        }
        else
        {
            //if(pVALVE_ICE_TRAY_IN == SET)
            //{
                if(gu8_trayvalve_wait_timer >= 3)
                {
                    gu8_trayvalve_wait_timer = 3;
                    Bit0_Ice_Tray_Water_Input_State = SET;
                }
                else
                {
                    gu8_trayvalve_wait_timer++;
                }
            //}
            //else
            //{
            ///    gu8_trayvalve_wait_timer = 0;
            //    Bit0_Ice_Tray_Water_Input_State = CLEAR;
            ///}
        }
    }
    else
    {
        gu8_trayvalve_wait_timer = 0;
        Bit0_Ice_Tray_Water_Input_State = CLEAR;
    }

    /***************************************************************************************************/
    if(F_Safety_Routine == SET)
    {
        if(F_Ice_Tray_Down_Move_Reset == SET)
        {
            if( gu8_over_ice_melt_proc == 1
                || gu8_over_ice_melt_proc == 4)
            {
                /*..hui [20-4-29오전 11:22:04] 온수 추출시 과제빙 해제 입수 정지..*/
                if( u8WaterOutState == HOT_WATER_SELECT
                    && F_WaterOut == SET )
                {
                    gu8_ice_melt_wait_timer = 0;
                    Bit0_Ice_Tray_Water_Input_State = CLEAR;
                }
                else
                {
                    //if(pVALVE_ICE_TRAY_IN == SET)
                   // {
                        /*..hui [20-4-29오전 11:13:35] 트레이 밸브 켜지고 300ms후에 펌프 켜지도록..*/
                        if(gu8_ice_melt_wait_timer >= 3)
                        {
                            gu8_ice_melt_wait_timer = 3;
                            Bit0_Ice_Tray_Water_Input_State = SET;
                        }
                        else
                        {
                            gu8_ice_melt_wait_timer++;
                        }
                   // }
                   // else
                    ///{
                   //     gu8_ice_melt_wait_timer = 0;
                   //     Bit0_Ice_Tray_Water_Input_State = CLEAR;
                   /// }
                }
            }
            else
            {
                gu8_ice_melt_wait_timer = 0;
                Bit1_Safty_Ice_Melt_State = CLEAR;
            }
        }
        else
        {
            gu8_ice_melt_wait_timer = 0;
            Bit1_Safty_Ice_Melt_State = CLEAR;
        }
    }
    else
    {
        gu8_ice_melt_wait_timer = 0;
        Bit1_Safty_Ice_Melt_State = CLEAR;
    }

    /***************************************************************************************************/
    /*..hui [19-12-13오후 3:09:53] 그 외 조건일 경우 저수위 미만일때만 닫음..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
    {
        Bit0_Tray_Pump_Low_Water_Off_State = SET;
    }
    else
    {
        Bit0_Tray_Pump_Low_Water_Off_State = CLEAR;
    }

    /***************************************************************************************************/
    gu16_hot_pump_pwm_out = confirm_tray_pump_pwm();

/***********************************************************************************************/
/***********************************************************************************************/
    if( u8TrayPumpOFF > 0 )
    {
        stop_tray_pump();               /*off*/
        bit_tray_pump_output = CLEAR;
        gu8_hot_pump_starting_timer = 0;
    }
    else
    {
        if( u8TrayPumpON > 0 )
        {
            gu8_hot_pump_starting_timer++;

            if( gu8_hot_pump_starting_timer >= TRAY_PUMP_STARTING_OP_TIME )
            {
                gu8_hot_pump_starting_timer = TRAY_PUMP_STARTING_OP_TIME;
                start_tray_pump( gu16_hot_pump_pwm_out ); /*on*/
            }
            else
            {
                /*..hui [19-10-25오후 7:33:52] 초기 기동 1초간 18V 이상..*/
                start_tray_pump( TRAY_PUMP_STARTING_PWM ); /*on*/
            }

            bit_tray_pump_output = SET;
        }
        else
        {
            stop_tray_pump();            /*off*/
            bit_tray_pump_output = CLEAR;
            gu8_hot_pump_starting_timer = 0;
        }
    }
/***********************************************************************************************/
/***********************************************************************************************/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 confirm_tray_pump_pwm(void)
{
    U16 mu16_return = 0;

    if(Bit0_Ice_Tray_Water_Input_State == SET)
    {
        /*..hui [20-11-30오후 3:55:25] 유량센서 10초 이상 감지되지 않으면 남은시간 동안 FULL로 가동..*/
        if( F_Tray_In_Error_Temporary == SET )
        {
            mu16_return = ICE_TRAY_IN_MAX_PWM;
        }
        else
        {
            mu16_return = ICE_TRAY_IN_PWM;
        }
    }
    else if( Bit1_Safty_Ice_Melt_State == SET )
    {
        mu16_return = TRAY_PUMP_PWM_MAX;
    }
    else
    {
        mu16_return = 0;
    }

    return mu16_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_tray_pump( U16 u16_data )
{
    gu16_current_hot_pwm = u16_data;
    TDR13 = gu16_current_hot_pwm;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_tray_pump( void )
{
    gu16_current_hot_pwm = 0;
    TDR13 = gu16_current_hot_pwm;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


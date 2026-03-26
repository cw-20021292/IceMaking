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
#define            u8TrayPumpON                                    U8TrayPumpONB.byte
#define            Bit0_Ice_Tray_Water_Input_State                 U8TrayPumpONB.Bit.b0
#define            Bit1_Safty_Ice_Melt_State                       U8TrayPumpONB.Bit.b1
#define            Bit2_Hot_Ster_Pump_Out_State                    U8TrayPumpONB.Bit.b2
#define            Bit3_Pump_Tray_Flushing_State                   U8TrayPumpONB.Bit.b3




TYPE_BYTE          U8TrayPumpOFFB;
#define            u8TrayPumpOFF                                   U8TrayPumpOFFB.byte
#define            Bit0_Tray_Pump_Low_Water_Off_State              U8TrayPumpOFFB.Bit.b0
#define            Bit1_Tray_Pump_Ster_Drain_Full_Off_State        U8TrayPumpOFFB.Bit.b1


U8 gu8_trayvalve_wait_timer;
U16 gu16_tray_pump_pwm_out;
bit bit_tray_pump_output;

U16 gu16_adjust_hot_pwm;
U16 gu16_adjust_preheat_pwm;


U8 gu8_hot_pump_starting_timer;

U16 gu16_current_tray_pwm;


U8 gu8_hot_first_full_timer;

U8 gu8_ice_melt_wait_timer;

U8 gu8_steam_drain_timer;
U8 gu8_preheat_steam_state;

U8 gu8_hot_ster_pump_wait_timer;


U16 gu16_ster_drain_delay_timer;

U16 gu16_low_level_delay_timer;

U16 gu16_test_pwm;
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
        if( F_WaterOut == SET )
        {
            gu8_trayvalve_wait_timer = 0;
            Bit0_Ice_Tray_Water_Input_State = CLEAR;
        }
        else
        {
            if( pVALVE_ICE_TRAY_IN_FEED == SET )
            {
                if(gu8_trayvalve_wait_timer >= 3)
                {
                    gu8_trayvalve_wait_timer = 3;
                    Bit0_Ice_Tray_Water_Input_State = SET;
                }
                else
                {
                    gu8_trayvalve_wait_timer++;
                }
            }
            else
            {
                gu8_trayvalve_wait_timer = 0;
                Bit0_Ice_Tray_Water_Input_State = CLEAR;
            }
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
            /*if( gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)*/
            /*if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 6)*/
            if( gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)
            {
                 if(pVALVE_ICE_TRAY_IN_FEED == SET)
                 {
                     /*..hui [20-4-29오전 11:13:35] 트레이 밸브 켜지고 300ms후에 펌프 켜지도록..*/
                     if(gu8_ice_melt_wait_timer >= 3)
                     {
                         gu8_ice_melt_wait_timer = 3;
                         Bit1_Safty_Ice_Melt_State = SET;
                     }
                     else
                     {
                         gu8_ice_melt_wait_timer++;
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
    }
    else
    {
        gu8_ice_melt_wait_timer = 0;
        Bit1_Safty_Ice_Melt_State = CLEAR;
    }


    /***************************************************************************************************/


    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_CIRCULATION_HOT_STATE )
        {
            if( gu8_hot_circulation_step == 3 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            /*if( gu8_hot_spray_step == 4 || gu8_hot_spray_step == 7 )*/
            if( gu8_hot_spray_step == 4 || gu8_hot_spray_step == 9 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            /*if( gu8_lukewarm_spray_step == 2 || gu8_lukewarm_spray_step == 5 )*/
            if( gu8_lukewarm_spray_step == 2 || gu8_lukewarm_spray_step == 6 || gu8_lukewarm_spray_step == 11 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            /*if( gu8_final_clean_step == 2 || gu8_final_clean_step == 5 )*/
            if( gu8_final_clean_step == 2 || gu8_final_clean_step == 6 || gu8_final_clean_step == 11 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step == 3 || gu8_ice_tray_clean_step == 9 || gu8_ice_tray_clean_step == 16 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            if( gu8_melt_ice_step == 3 || gu8_melt_ice_step == 7 || gu8_melt_ice_step == 11
                || gu8_melt_ice_step == 15 || gu8_melt_ice_step == 19 )
            {
                Bit2_Hot_Ster_Pump_Out_State = SET;
            }
            else
            {
                Bit2_Hot_Ster_Pump_Out_State = CLEAR;
            }
        }
        else
        {
            Bit2_Hot_Ster_Pump_Out_State = CLEAR;
        }
    }
    else
    {
        /*gu8_hot_ster_pump_wait_timer = 0;*/
        Bit2_Hot_Ster_Pump_Out_State = CLEAR;
    }


    #if 0
    /*..hui [23-8-16오후 1:24:20] 탱크 플러싱할때..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        /*if( gu8_flushing_tank_step == 7 )*/
        /*..hui [24-1-4오후 2:02:48] 만수후 온수탱크 에어빼기 기능 추가..*/
        if( gu8_flushing_tank_step == 5 )
        {
            Bit3_Pump_Tray_Flushing_State = bit_flushing_tank_start;
        }
        else if( gu8_flushing_tank_step == 12 )
        {
            Bit3_Pump_Tray_Flushing_State = bit_flushing_tank_start;
        }
        else
        {
            Bit3_Pump_Tray_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit3_Pump_Tray_Flushing_State = CLEAR;
    }
    #endif

    /*..hui [23-8-16오후 1:24:20] 탱크 플러싱할때..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        if( gu8_flushing_tank_step == 7 )
        {
            Bit3_Pump_Tray_Flushing_State = bit_flushing_tank_start;
        }
        else
        {
            Bit3_Pump_Tray_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit3_Pump_Tray_Flushing_State = CLEAR;
    }



    /***************************************************************************************************/
    /***************************************************************************************************/
    /***************************************************************************************************/
    /*..hui [19-12-13오후 3:09:53] 그 외 조건일 경우 저수위 미만일때만 닫음..*/
    #if 0
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
    {
        Bit0_Tray_Pump_Low_Water_Off_State = SET;
        gu16_low_level_delay_timer = 0;
    }
    else
    {
        if( Bit0_Tray_Pump_Low_Water_Off_State == SET )
        {
            gu16_low_level_delay_timer++;

            /*..hui [23-7-21오후 3:37:53] 저수위 해제되고 1분동안 재정수 후 다시 재 시작..*/
            if( gu16_low_level_delay_timer >= 600 )
            {
                gu16_low_level_delay_timer = 0;
                Bit0_Tray_Pump_Low_Water_Off_State = CLEAR;
            }
            else{}
        }
        else{}
    }
    #endif

    /*..hui [23-7-21오후 5:27:58] 다시 변경.. 그냥 저수위 해제되면 바로 해제..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
    {
        Bit0_Tray_Pump_Low_Water_Off_State = SET;
    }
    else
    {
        Bit0_Tray_Pump_Low_Water_Off_State = CLEAR;
    }



    if( Bit0_Ice_Tray_Water_Input_State == CLEAR )
    {
        /*if( bit_ice_tank_ster_start == SET && Bit2_Hot_Ster_Pump_Out_State == SET)*/
        /*..hui [24-2-6오후 5:38:33] 만수 감지 이후 트레이 펌프 정지 중(트레이 이동중등)에 만수위 해제되면..*/
        /*..hui [24-2-6오후 5:38:56] 배수랑 분사랑 동시에 될수있음..*/
        if( bit_ice_tank_ster_start == SET )
        {
            /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH)*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
            {
                /*..hui [23-7-6오전 11:57:05] 온수 살균중 드레인 만수위면 잠시 중단..*/
                Bit1_Tray_Pump_Ster_Drain_Full_Off_State = SET;
                gu16_ster_drain_delay_timer = 0;
            }
            else
            {
                #if 0
                gu16_ster_drain_delay_timer++;

                /*..hui [23-7-6오전 11:58:19] 만수위 해제 후 10초간 지연 가동..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || gu16_ster_drain_delay_timer >= 300 )
                {
                    gu16_ster_drain_delay_timer = 300;
                    Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
                }
                else{}
                #endif

                #if 0
                /*..hui [24-2-5오후 5:18:25] 한번 만수위 감지되면 탱크 비울때까지 배수..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                {
                    Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
                }
                else{}
                #endif

                #if 0
                /*..hui [24-2-5오후 5:18:25] 한번 만수위 감지되면 탱크 비울때까지 배수..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                {
                    Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
                }
                else if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    gu16_ster_drain_delay_timer++;

                    if( gu16_ster_drain_delay_timer >= 3000 )
                    {
                        gu16_ster_drain_delay_timer = 3000;
                        Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
                    }
                    else{}
                }
                else{}
                #endif

                /*..hui [24-2-5오후 5:18:25] 한번 만수위 감지되면 탱크 비울때까지 배수..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                {
                    Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
                }
                else{}
            }
        }
        else
        {
            Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
            gu16_ster_drain_delay_timer = 0;
        }
    }
    else
    {
        Bit1_Tray_Pump_Ster_Drain_Full_Off_State = CLEAR;
        gu16_ster_drain_delay_timer = 0;
    }

    /***************************************************************************************************/
    /***************************************************************************************************/
    /***************************************************************************************************/
    gu16_tray_pump_pwm_out = confirm_tray_pump_pwm();

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
                start_tray_pump( gu16_tray_pump_pwm_out ); /*on*/
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
    else if( Bit2_Hot_Ster_Pump_Out_State == SET )
    {
        if( gu8_ster_pump_stage == STER_PUMP_STAGE_90_PERCENT )
        {
            mu16_return = TRAY_PUMP_PWM_90_PERCENT;
        }
        else if( gu8_ster_pump_stage == STER_PUMP_STAGE_80_PERCENT )
        {
            mu16_return = TRAY_PUMP_PWM_80_PERCENT;
        }
        else
        {
            mu16_return = TRAY_PUMP_PWM_90_PERCENT;
        }
    }
    else if( Bit3_Pump_Tray_Flushing_State == SET )
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
    gu16_current_tray_pwm = u16_data;
    TDR12 = gu16_current_tray_pwm;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_tray_pump( void )
{
    gu16_current_tray_pwm = 0;
    TDR12 = gu16_current_tray_pwm;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


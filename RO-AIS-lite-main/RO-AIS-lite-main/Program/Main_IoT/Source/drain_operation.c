/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "drain_operation.h"



void output_drain_pump(void);
void drain_pump_output_decision(void);
void detect_drain_tank_high_level( void );
void drain_operation(void);
void drain_operation_24hour(void);
//void IceWaterExtrate(void);
void drain_retry_operation(void);
void keep_3_hour_check(void);
void ice_full_condition_check(void);
void detect_drain_pump_error(void);
U8 drain_pump_error_retry_proc( void );
void forced_drain_check(void);
void ice_off_check(void);
void first_drain_check(void);
void start_drain_pump( U16 u16_data );
void stop_drain_pump( void );
void check_empty_ice_tray_in(void);





TYPE_BYTE          U8DrainOperateB;
#define            u8DrainOperate                       U8DrainOperateB.byte
#define            Bit0_Drain_Level_Full                U8DrainOperateB.Bit.b0
#define            Bit1_Drain_Low_3_Hour                U8DrainOperateB.Bit.b1
#define            Bit2_Drain_Ice_Full                  U8DrainOperateB.Bit.b2
#define            Bit3_Drain_Forced                    U8DrainOperateB.Bit.b3
#define            Bit4_Drain_Ice_Tray_In               U8DrainOperateB.Bit.b4
#define            Bit5_Drain_Ice_Off                   U8DrainOperateB.Bit.b5
#define            Bit6_Drain_First                     U8DrainOperateB.Bit.b6



TYPE_BYTE          U8DrainPumpONB;
#define            u8DrainPumpON                        U8DrainPumpONB.byte
#define            Bit0_Drain_Tank_Level_Full_State     U8DrainPumpONB.Bit.b0
#define            Bit1_Drain_Error_Check_On_State      U8DrainPumpONB.Bit.b1
#define            Bit2_Drain_3_hour_State              U8DrainPumpONB.Bit.b2
#define            Bit3_Drain_ice_full_State            U8DrainPumpONB.Bit.b3
#define            Bit4_Auto_drain_State                U8DrainPumpONB.Bit.b4



TYPE_BYTE          U8DrainPumpOFFB;
#define            u8DrainPumpOFF                       U8DrainPumpOFFB.byte
#define            Bit0_Drain_Error_Check_Off_State     U8DrainPumpOFFB.Bit.b0
#define            Bit1_Drain_Error_Confirm_State       U8DrainPumpOFFB.Bit.b1
#define            Bit2_Bldc_Over_Current_Off_State     U8DrainPumpOFFB.Bit.b2


U8 gu8drain_1s_time;


U16 gu16_drain_pump_first_op_timer;
U8 gu8drain_pump_error_retry_chk_mode;

U16 gu16_drain_pump_1min_off_timer;
U16 gu16_drain_pump_2min_on_timer;

U16 gu16_drain_low_water_1min_tmr;
U16 gu16_drain_low_water_3hour_tmr;


U16 gu16_over_current_off_timer;
U16 gu16_over_current_detect_timer;



bit F_Drain_Pump_Output;


U8 gu8_drain_err_10_count;

bit F_old_ice_full;
bit F_old_ice_on;

U16 gu16_ice_off_drain_timer;

//bit Bit2_Drain_Ice_Full;

bit F_drain_err_check_on_state;
bit F_drain_err_check_off_state;


bit F_drain_error_check_enable;

U8 gu8_drain_pump_max_operation_count;

bit bit_first_drain;

bit F_forced_drain_enable;

U8 gu8_forced_drain_add_timer;


bit F_Drain_Pump_Output;

U16 gu16_drain_pwm_out;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 dbg_drainpump;
U16 dbg_pumppwmVal;
void output_drain_pump(void)
{
    /*..hui [17-12-18오후 5:49:56] 드레인펌프 에러 확인..*/
    detect_drain_pump_error();
/*	
	if(pLEVEL_ICE_DRAIN_LOW == CLEAR)
		{
	F_drain_err_check_on_state = CLEAR;
		}
*/
    /*..hui [17-12-18오후 5:50:02] 최종 출력 결정..*/
    drain_pump_output_decision();

	//for test
	if(dbg_drainpump == SET)
	{
        start_drain_pump( dbg_pumppwmVal ); /*on*/

		return;
	}

    if( u8DrainPumpOFF > 0 )
    {
        stop_drain_pump();  /*off*/
        gu8_drain_pump_max_operation_count = 0;
        F_Drain_Pump_Output = CLEAR;
		Bit5_Drain_Pump_12V_Out_State = CLEAR;
    }
    else
    {
        if( u8DrainPumpON > 0 )
        {
        	Bit5_Drain_Pump_12V_Out_State = SET;
            /*..hui [18-1-30오후 3:11:35] 가동 초반 3초동안 max로 가동하다가 약 66%로 변경.. ..*/
            /*..hui [18-1-30오후 3:11:53] 다른모델이 75%라고 돼있으나 실제로는 66%임..*/
            gu8_drain_pump_max_operation_count++;

            if(gu8_drain_pump_max_operation_count >= DRAIN_PUMP_MAX_OP_TIME)
            {
                gu8_drain_pump_max_operation_count = DRAIN_PUMP_MAX_OP_TIME;

                /*..hui [18-7-19오후 1:31:20] 재시도 10회 중 2회째부터는 Full duty로 가동한다...*/
                /*..hui [18-7-19오후 1:31:46] 배수 안되서 에러 발생하는 것 보다 소음나는게 더 낫지....*/
                if(gu8_drain_err_10_count >= DRAIN_PUMP_MAX_OUTPUT_ERROR_COUNT)
                {
                    start_drain_pump( DRAIN_PUMP_PWM_MAX ); /*on*/
                }
                else
                {
                    start_drain_pump( DRAIN_PUMP_PWM_OP ); /*on*/
                }
            }
            else
            {
                start_drain_pump( DRAIN_PUMP_PWM_MAX ); /*on*/
            }

            F_Drain_Pump_Output = SET;
        }
        else
        {
            stop_drain_pump(); /*off*/
            gu8_drain_pump_max_operation_count = 0;
            F_Drain_Pump_Output = CLEAR;
        }
    }


}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_pump_output_decision(void)
{
	//Bit4_Auto_drain_State = SET;
	//return;
/***************************************************************************************************/

    /*..hui [18-1-14오후 8:57:59] 순환배수 기능 실행중일때는 에러체크 안함..*/
    Bit1_Drain_Error_Check_On_State = F_drain_err_check_on_state & ~F_DrainStatus;

    Bit4_Auto_drain_State = F_auto_drain_mode_pump_out;

/***************************************************************************************************/
    Bit0_Drain_Error_Check_Off_State = F_drain_err_check_off_state & ~F_DrainStatus;

    Bit1_Drain_Error_Confirm_State = Bit12_Drain_Pump_Error;
#if 1
    /*..hui [23-7-7오후 12:06:47] BLDC 과전류로 OFF 됐을때 다시 켜줘야 함..*/
	/*..sean [25-3-18] bldc pump 전류 피드백 수정 필요..*/
    //if( Bit1_Drain_Error_Check_On_State == SET && Bit2_Bldc_Over_Current_Off_State == CLEAR )
    if( pLEVEL_ICE_DRAIN_LOW == SET && Bit2_Bldc_Over_Current_Off_State == CLEAR )
    {
        if( gu16_AD_Drain_Pump_Current <= PUMP_OVER_CURRENT_ADC )
        {
            gu16_over_current_detect_timer++;

            if( gu16_over_current_detect_timer >= PUMP_OVER_CURRENT_DETECT_TIME )
            {
                gu16_over_current_detect_timer = 0;
                gu16_over_current_off_timer = 0;
                Bit2_Bldc_Over_Current_Off_State = SET;
            }
            else{}
        }
        else
        {
            gu16_over_current_detect_timer = 0;
            gu16_over_current_off_timer = 0;
        }
    }
    else
    {
        if( Bit2_Bldc_Over_Current_Off_State == SET )
        {
            gu16_over_current_off_timer++;

            if( gu16_over_current_off_timer >= PUMP_OVER_CURRENT_OFF_TIME )
            {
                gu16_over_current_detect_timer = 0;
                gu16_over_current_off_timer = 0;
                Bit2_Bldc_Over_Current_Off_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_over_current_detect_timer = 0;
            gu16_over_current_off_timer = 0;
        }
    }
#endif
    #if 0
    /*..hui [19-10-23오전 10:59:24] 온수 드레인 또는 추출중에 피드밸브 닫는다..*/
    /*..hui [19-10-23오전 10:59:34] 배수 유로 동일해서 압 걸림..*/
    /*..hui [19-10-23오전 11:12:41] 드레인펌프도 정지한다..*/
    if(F_WaterOut == SET)
    {
        if(u8WaterOutState == HOT_WATER_SELECT)
        {
            Bit2_Hot_Water_Drain_Off_State = F_WaterOut;
        }
        else
        {
            Bit2_Hot_Water_Drain_Off_State = CLEAR;
        }
    }
    else
    {
        Bit2_Hot_Water_Drain_Off_State = CLEAR;
    }
    #endif

    #if 0
    if( F_First_Hot_Effluent == SET )
    {
        Bit3_Hot_Filling_Drain_Off_State = bit_hot_filling_start;
    }
    else
    {
        Bit3_Hot_Filling_Drain_Off_State = CLEAR;
    }
    #endif

    #if 0
    /*..hui [20-4-8오후 8:18:56] 온수 과열 쿨링..*/
    if( Bit5_Hot_Heater_OverHeat_Error == SET )
    {
        Bit4_Hot_Cooling_Drain_Off_State = bit_hot_colling_start;
    }
    else
    {
        Bit4_Hot_Cooling_Drain_Off_State = CLEAR;
    }
    #endif
/***************************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full_condition_check(void)
{
    /*..hui [18-1-8오후 3:50:20] 제빙 설정상태 추가..*/
    if(F_IceFull == SET)
    {
        if(F_old_ice_full != F_IceFull)
        {
            F_old_ice_full = F_IceFull;

            if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)
            {
                Bit2_Drain_Ice_Full = SET;
            }
            else
            {
                Bit2_Drain_Ice_Full = CLEAR;
            }
        }
        else
        {
            if(Bit2_Drain_Ice_Full == SET)
            {
                if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
                {
                    Bit2_Drain_Ice_Full = CLEAR;
                }
                else{}
            }
            else
            {

            }
        }
    }
    else
    {
        F_old_ice_full = CLEAR;

        if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
        {
            Bit2_Drain_Ice_Full = CLEAR;
        }
        else{}
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void keep_3_hour_check(void)
{
    /*..hui [17-12-18오후 1:05:30] 저수위 감지 3시간 이상 유지시 저수위 미감지까지 배수 ..*/
    if(u8DrainWaterLevel == DRAIN_LEVEL_LOW)
    {
        /*..hui [17-12-18오후 1:16:57] 드레인펌프 가동중에는 카운트 정지..*/
        if(Bit1_Drain_Low_3_Hour == SET)
        {

        }
        else
        {
            gu16_drain_low_water_1min_tmr++;
        }

        if(gu16_drain_low_water_1min_tmr >= 600)
        {
            gu16_drain_low_water_1min_tmr = 0;

            gu16_drain_low_water_3hour_tmr++;

            if(gu16_drain_low_water_3hour_tmr >= 180)
            {
                Bit1_Drain_Low_3_Hour = SET;
                gu16_drain_low_water_3hour_tmr = 0;
            }
            else{}
        }
        else{}
    }
    else
    {
        if(Bit1_Drain_Low_3_Hour == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                Bit1_Drain_Low_3_Hour = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_drain_low_water_1min_tmr = 0;
            gu16_drain_low_water_3hour_tmr = 0;
        }
    }
}



#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 detect_drain_tank_high_level( U8 mu8_current_state )
{
    U8 mu8_return = 0;

    /*..hui [17-12-15오후 10:40:27] 만수위 감지시 저수위 미감지될때까지 드레인펌프 가동..*/
    /*..hui [17-12-18오전 10:27:56] 수위센서 에러시(저수위 미감지,고수위 감지)에도 배수 진행..*/
    if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)
    {
        mu8_current_state = SET;
    }
    else
    {
        if(Bit0_Drain_Tank_Level_Full_State == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                mu8_current_state = CLEAR;
            }
            else{}
        }
        else{}
    }

    return mu8_current_state;

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_drain_tank_high_level( void )
{
    U8 mu8_return = 0;

    /*..hui [17-12-15오후 10:40:27] 만수위 감지시 저수위 미감지될때까지 드레인펌프 가동..*/
    /*..hui [17-12-18오전 10:27:56] 수위센서 에러시(저수위 미감지,고수위 감지)에도 배수 진행..*/
    if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)
    {
        Bit0_Drain_Level_Full = SET;
    }
    else
    {
        if(Bit0_Drain_Level_Full == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                Bit0_Drain_Level_Full = CLEAR;
            }
            else{}
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_off_check(void)
{
    /*..hui [19-12-2오후 2:07:02] 얼음 기능 ON->OFF될 경우 저수위 이상이면 드레인 펌프 가동..*/
    /*if(F_IceOn == CLEAR)*/

    /*if( gu8_ice_setting == ICE_SETTING_OFF )*/
    if(F_IceOn == CLEAR)
    {
        if( F_old_ice_on == SET )
        {
            F_old_ice_on = CLEAR;

            if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)
            {
                Bit5_Drain_Ice_Off = SET;
            }
            else
            {
                Bit5_Drain_Ice_Off = CLEAR;
            }
        }
        else
        {
            if(Bit5_Drain_Ice_Off == SET)
            {
                if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
                {
                    Bit5_Drain_Ice_Off = CLEAR;
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        F_old_ice_on = SET;

        if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
        {
            Bit5_Drain_Ice_Off = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_empty_ice_tray_in(void)
{
    /*..hui [19-12-2오후 2:04:44] 사용안함.. 방식 변경..*/
    if(gu8IceStep > STATE_0_STANDBY
        && gu8IceStep <= STATE_12_CHECK_DRAIN_LEVEL)
    {
        if(u8DrainWaterLevel > DRAIN_LEVEL_EMPTY)
        {
            Bit4_Drain_Ice_Tray_In = SET;
        }
        else
        {
            if(Bit4_Drain_Ice_Tray_In == SET)
            {
                if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
                {
                    Bit4_Drain_Ice_Tray_In = CLEAR;
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        Bit4_Drain_Ice_Tray_In = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void first_drain_check(void)
{
    /*..hui [23-4-4오후 2:35:55] 드레인 탱크 센서 읽는시간 대기..*/
    if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

    if( bit_first_drain == SET )
    {
        bit_first_drain = CLEAR;

        if(u8DrainWaterLevel == DRAIN_LEVEL_LOW)
        {
            Bit6_Drain_First = SET;
        }
        else
        {
            Bit6_Drain_First = CLEAR;
        }
    }
    else
    {
        if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
        {
            Bit6_Drain_First = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_drain_pump_error(void)
{
    U8 mu8_error_chk_enable = 0;

    /*..hui [17-12-15오후 10:40:27] 만수위 감지시 저수위 미감지될때까지 드레인펌프 가동..*/
    /*..hui [17-12-18오후 1:19:04] 수위센서 에러시 가동 추가..*/
    detect_drain_tank_high_level();

    /*..hui [17-12-18오후 5:49:40] 저수위 3시간 유지 확인..*/
    keep_3_hour_check();

    /*..hui [17-12-18오후 5:49:47] 만빙 상태 확인..*/
    ice_full_condition_check();

    /*..hui [19-12-2오후 2:16:19] 얼음기능 OFF 체크..*/
    ice_off_check();

    /*..hui [18-2-12오후 4:08:15] 탱크 강제 배수 기능 실행 확인..*/
    forced_drain_check();

    /*..hui [23-4-4오후 2:38:22] 최초 전원 ON시 드레인 저수위 감지 상태이면 가동.. 아이콘아이스 사양 추가..*/
    first_drain_check();

    /*check_empty_ice_tray_in();*/

    /*..hui [18-1-22오후 4:34:56] 순환배수 기능 작동중일때 동작하지 않도록 변경..*/
    /*..hui [19-10-23오전 11:39:05] 온수 추출중일때는 정지했다 처음부터 다시 시작(펌프 압)..*/
    /*..hui [20-4-21오후 12:30:57] 첫잔드레인 및 히터 쿨링시 드레인 종료 후 다시 시작 추가..*/
    /*..hui [23-4-4오후 2:40:31] 최초 전원 ON시 저수위일경우 가동 추가 - 아이콘아이스 사양 - 신뢰성..*/
    F_drain_error_check_enable
        = ( ( Bit0_Drain_Level_Full | Bit1_Drain_Low_3_Hour
              | Bit2_Drain_Ice_Full | Bit3_Drain_Forced | Bit5_Drain_Ice_Off | Bit6_Drain_First )
              & ~F_DrainStatus );


    if(F_drain_error_check_enable == SET)
    {
        mu8_error_chk_enable = SET;
    }
    else
    {
        mu8_error_chk_enable = CLEAR;
    }

    if(mu8_error_chk_enable != SET || Bit12_Drain_Pump_Error == SET)
    {
        gu16_drain_pump_first_op_timer = 0;
        gu8drain_pump_error_retry_chk_mode = DRAIN_PUMP_OFF_PROC;
        gu16_drain_pump_2min_on_timer = 0;
        gu16_drain_pump_1min_off_timer = 0;
        F_drain_err_check_on_state = CLEAR;
        F_drain_err_check_off_state = CLEAR;
        gu8_drain_err_10_count = 0;
    }
    else
    {
        gu16_drain_pump_first_op_timer++;

        if(gu16_drain_pump_first_op_timer >= DRAIN_ERROR_PUMP_ON_10_MIN)   //10min
        {
            gu16_drain_pump_first_op_timer = DRAIN_ERROR_PUMP_ON_10_MIN;

            F_drain_err_check_on_state = drain_pump_error_retry_proc();
            F_drain_err_check_off_state = ~F_drain_err_check_on_state;
        }
        else
        {
            F_drain_err_check_on_state = SET;
            F_drain_err_check_off_state = CLEAR;
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 drain_pump_error_retry_proc( void )
{
    U8 mu8_return = CLEAR;

    /*..hui [17-12-18오후 3:29:43] 10분 가동해도 저수위 해제가 안되면 2분 ON, 1분 OFF 10회 반복..*/
    switch(gu8drain_pump_error_retry_chk_mode)
    {
        case DRAIN_PUMP_OFF_PROC :

            gu16_drain_pump_1min_off_timer++;

            if(gu16_drain_pump_1min_off_timer >= DRAIN_ERROR_PUMP_OFF_1_MIN)
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;
                gu8drain_pump_error_retry_chk_mode = DRAIN_PUMP_ON_PROC;
                /*mu8_return = SET;*/

                if(gu8_drain_err_10_count >= 10)
                {
                    /*..hui [17-12-18오후 5:33:37] 에러 set..*/
                    gu8_drain_err_10_count = 0;

                    Bit12_Drain_Pump_Error = SET;
                    mu8_return = CLEAR;
                }
                else
                {
                    mu8_return = SET;
                }

            }
            else
            {
                mu8_return = CLEAR;
            }

            break;

        case DRAIN_PUMP_ON_PROC :

            gu16_drain_pump_2min_on_timer++;

            if(gu16_drain_pump_2min_on_timer >= DRAIN_ERROR_PUMP_ON_2_MIN)
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;
                gu8drain_pump_error_retry_chk_mode = DRAIN_PUMP_OFF_PROC;

                gu8_drain_err_10_count++;
                mu8_return = CLEAR;
            }
            else
            {
                mu8_return = SET;
            }

            break;

        default :
             //
             mu8_return = CLEAR;
            break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void forced_drain_check(void)
{
    /*..hui [18-2-12오후 4:13:12] 정수탱크, 냉수탱크 비움상태일때 드레인탱크가 저수위 이상이면 강제배수 기능 실행..*/
    if( u8DrainWaterLevel >= DRAIN_LEVEL_LOW
        && gu8_Room_Water_Level == ROOM_LEVEL_LOW
        && F_Tank_Cover_Input == CLEAR
        && F_Overflow == CLEAR )
    {
        Bit3_Drain_Forced = SET;
        gu8_forced_drain_add_timer = 0;
    }
    else
    {
        if(Bit3_Drain_Forced == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                gu8_forced_drain_add_timer++;

                /*..hui [18-2-12오후 4:14:14] 배수 완료 후 10초 추가 배수..*/
                if(gu8_forced_drain_add_timer >= FORCED_DRAIN_ADDITIONAL_TIME)
                {
                    gu8_forced_drain_add_timer = 0;
                    Bit3_Drain_Forced = CLEAR;
                }
                else
                {
                    Bit3_Drain_Forced = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_forced_drain_add_timer = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_drain_pump( U16 u16_data )
{
    gu16_drain_pwm_out = u16_data;
    TDR06 = gu16_drain_pwm_out;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_drain_pump( void )
{
    gu16_drain_pwm_out = 0;
    TDR06 = gu16_drain_pwm_out;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




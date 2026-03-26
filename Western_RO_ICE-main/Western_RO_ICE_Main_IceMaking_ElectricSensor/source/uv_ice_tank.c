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
#include    "uv_ice_tank.h"



void output_ice_tank_uv(void);
U8 uv_ice_tank_control(void);
void ice_tank_uv_operation_timer(void);
U8 ice_tank_uv_standby_timer(void);
void start_ice_tank_uv(void);
void initial_ice_tank_uv_timer(void);
void uv_tank_reed_sw_input(void);
void calc_uv_remain_time(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8IceTankUvONB;
#define            u8IceTankUvON                                        U8IceTankUvONB.byte
#define            Bit0_Ice_Tank_UV_On_State                            U8IceTankUvONB.Bit.b0
#define            Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State             U8IceTankUvONB.Bit.b1
#define            Bit2_Ice_Tank_UV_Ice_Off_On_State                    U8IceTankUvONB.Bit.b2
#define            Bit3_Ice_Tank_UV_Fault_Test_On_State                 U8IceTankUvONB.Bit.b3




TYPE_BYTE          U8IceTankUvOFFB;
#define            u8IceTankUvOFF                                       U8IceTankUvOFFB.byte
#define            Bit0_Tank_Open_UV_Off_State                          U8IceTankUvOFFB.Bit.b0
#define            Bit1_Ice_Extract_UV_Off_State                        U8IceTankUvOFFB.Bit.b1
#define            Bit2_Ice_Tank_UV_Retry_3S_Off_State                  U8IceTankUvOFFB.Bit.b2
#define            Bit3_Ice_Tank_UV_Error_Off_State                     U8IceTankUvOFFB.Bit.b3



TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                                    U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State                        U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State                       U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State                            U812VPowerControl.Bit.b2
#define            Bit3_Water_Tank_UV_12V_Out_State                     U812VPowerControl.Bit.b3
#define            Bit4_Ice_Tray_UV_12V_Out_State                       U812VPowerControl.Bit.b4
#define            Bit5_Ice_Tank_Front_UV_12V_Out_State                 U812VPowerControl.Bit.b5
#define            Bit6_Drain_Pump_FeedBack_12V_Out_State               U812VPowerControl.Bit.b6




/***********************************************************************************************************************/


bit F_Auto_UV_Control;
bit bit_ice_tank_uv_start;

U8 gu8_uv_ster_timer_per_min;

U8 gu8_UV_Ster_Count_One_Day;

U8 gu8_uv_ster_max_operation_one_day;


U16 gu16_ice_tank_uv_operation_timer_sec;
U8 gu8_ice_tank_uv_operation_timer_min;
U16 gu16_ice_tank_uv_operation_timer_hour;

U16 gu16_ice_tank_uv_standby_timer_sec;
U16 gu16_ice_tank_uv_standby_timer_min;
U16 gu16_ice_tank_uv_standby_timer_hour;


U8 gu8_uv_ice_tank_step;
bit F_Immediately_Uv_Ster;

bit bit_uv_power_on;

U8 gu8_uv_service_reed_on_cnt;
U8 gu8_uv_service_reed_off_cnt;

bit bit_uv_tank_input;

bit bit_uv_ice_tank_out;

U8 gu8_display_uv_reamin_minute;
U8 gu8_display_uv_elapsed_percent;
U8 gu8_uv_popup_enable;

U8 gu8_uv_ice_tank_retry_timer;

U16 gu16_tank_clean_uv_up_max_timer;
U16 gu16_tank_clean_uv_down_max_timer;

bit bit_uv_fault_test_start;
U16 gu16_fault_test_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_tank_uv(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    Bit0_Ice_Tank_UV_On_State = uv_ice_tank_control();

    /*..hui [24-1-26오후 2:56:06] 얼음탱크 세척 중.. 아이스트레이 세척할때 제빙 방향에서 UV 조사..*/
    /*..hui [24-1-26오후 2:56:11] 최대 시간은 30분으로..*/
    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE
            || gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            gu16_tank_clean_uv_up_max_timer++;

            if( gu16_tank_clean_uv_up_max_timer >= ICE_TANK_CLEAN_UV_MAX_TIME )
            {
                gu16_tank_clean_uv_up_max_timer = ICE_TANK_CLEAN_UV_MAX_TIME;
                Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = CLEAR;
            }
            else
            {
                Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = SET;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
        {
            gu16_tank_clean_uv_down_max_timer++;

            if( gu16_tank_clean_uv_down_max_timer >= ICE_TANK_CLEAN_UV_MAX_TIME )
            {
                gu16_tank_clean_uv_down_max_timer = ICE_TANK_CLEAN_UV_MAX_TIME;
                Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = CLEAR;
            }
            else
            {
                Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = SET;
            }
        }
        else
        {
            gu16_tank_clean_uv_up_max_timer = 0;
            gu16_tank_clean_uv_down_max_timer = 0;
            Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = CLEAR;
        }
    }
    else
    {
        gu16_tank_clean_uv_up_max_timer = 0;
        gu16_tank_clean_uv_down_max_timer = 0;
        Bit1_Ice_Tank_UV_Ice_Tank_Clean_On_State = CLEAR;
    }


    /*..hui [24-2-8오전 10:03:44] 제빙 OFF했을때 UV 제어..*/
    Bit2_Ice_Tank_UV_Ice_Off_On_State = uv_ice_off_control();

    /*..hui [24-11-28오전 10:26:11] 전원 인가 후 1분 30초 동안 계속 켜서 고장 확인..*/
    /*..hui [24-11-28오전 10:26:47] UV 교체 후 정상 확인하려면 6시간동안 기다려야하는 문제..*/
    /*..hui [24-11-28오전 10:27:03] 서비스기획팀 요청~~~..*/
    if( bit_uv_fault_test_start == SET )
    {
        gu16_fault_test_timer++;

        if( gu16_fault_test_timer >= UV_FAULT_TEST_1MIN_30SEC )
        {
            gu16_fault_test_timer = UV_FAULT_TEST_1MIN_30SEC;
            Bit3_Ice_Tank_UV_Fault_Test_On_State = CLEAR;
            bit_uv_fault_test_start = CLEAR;
        }
        else
        {
            Bit3_Ice_Tank_UV_Fault_Test_On_State = SET;
        }
    }
    else
    {
        gu16_fault_test_timer = 0;
        Bit3_Ice_Tank_UV_Fault_Test_On_State = CLEAR;
    }



    /***********************************************************************************************/
    /*..hui [19-10-24오후 8:04:35] 탱크 커버 열렸을경우 정지..*/
    /*..hui [20-2-19오후 5:59:39] 탱크 커버 열리면 즉시 꺼지도록 커버 입력부 분리..*/
    /*..hui [20-2-19오후 5:59:45] 코디 건강을위해.....*/
    Bit0_Tank_Open_UV_Off_State = ~bit_uv_tank_input;

    /*..hui [19-10-24오후 8:04:54] 얼음 추출 시 정지..*/
    /*Bit1_Ice_Extract_UV_Off_State = F_Ice;*/
    /*..hui [20-2-19오후 7:31:38] 얼음 추출구 열릴때 끄고 완전히 닫힌 후 켜도록 수정..*/
    if( F_Ice == SET )
    {
        Bit1_Ice_Extract_UV_Off_State = F_Ice;
    }
    else
    {
        if( gu16StepMotor2 == 0 )
        {
            Bit1_Ice_Extract_UV_Off_State = CLEAR;
        }
        else{}
    }


    if( bit_ice_tank_uv_retry_stop == SET )
    {
        gu8_uv_ice_tank_retry_timer++;

        if( gu8_uv_ice_tank_retry_timer >= 30 )
        {
            bit_ice_tank_uv_retry_stop = CLEAR;
            gu8_uv_ice_tank_retry_timer = 0;
            Bit2_Ice_Tank_UV_Retry_3S_Off_State = CLEAR;
        }
        else
        {
            Bit2_Ice_Tank_UV_Retry_3S_Off_State = SET;
        }
    }
    else
    {
        gu8_uv_ice_tank_retry_timer = 0;
        Bit2_Ice_Tank_UV_Retry_3S_Off_State = CLEAR;
    }

    Bit3_Ice_Tank_UV_Error_Off_State = Bit24_Ice_Tank_1_2_Back_UV_Error__E75;



/***********************************************************************************************/
    if( u8IceTankUvOFF > 0 )
    {
        pUV_LED_ICE_TANK_1_2_BACK = CLEAR;                  /*off*/
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
        bit_uv_ice_tank_out = CLEAR;
    }
    else
    {
        if( u8IceTankUvON > 0 )
        {
            pUV_LED_ICE_TANK_1_2_BACK = SET;                 /*on*/
            Bit1_Ice_Tank_UV_12V_Out_State = SET;
            bit_uv_ice_tank_out = SET;
        }
        else
        {
            pUV_LED_ICE_TANK_1_2_BACK = CLEAR;              /*off*/
            Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
            bit_uv_ice_tank_out = CLEAR;
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_ice_tank_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    /*..hui [23-6-30오전 10:20:26] 설치 플러싱할때도 안함..*/
    /*if( F_IceOn == CLEAR || bit_install_flushing_state == SET )*/
    /*..hui [24-1-12오후 2:43:29] 얼음 OFF일떄도 UV 동작하도록..*/
    /*if( bit_install_flushing_state == SET )*/
    /*..hui [24-2-2오후 3:27:57] 얼음 OFF일때는 따로 제어사양 추가..*/
    if( F_IceOn == CLEAR || bit_install_flushing_state == SET )
    {
        initial_ice_tank_uv_timer();
        gu8_uv_ice_tank_step = 0;
        bit_ice_tank_uv_start = CLEAR;
        return CLEAR;
    }
    else{}

/********************************************************************************************/
    switch( gu8_uv_ice_tank_step )
    {
        case 0 :

            /*..hui [19-10-24오후 8:34:44] 6시간 대기..*/
            mu8_finish = ice_tank_uv_standby_timer();

            if(mu8_finish == SET)
            {
                gu8_uv_ice_tank_step = 1;
                start_ice_tank_uv();
            }
            else{}

        break;

        case 1 :

            /*..hui [19-10-24오후 8:34:49] 2시간 가동..*/
            if(bit_ice_tank_uv_start == SET)
            {
                /*..hui [19-10-25오전 9:41:56] 추출 또는 뚜껑열렸을 경우에는 정지..*/
                if( u8IceTankUvOFF == 0 )
                {
                    ice_tank_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu8_uv_ice_tank_step = 0;
            }

        break;

        default :

            gu8_uv_ice_tank_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_tank_uv_operation_timer(void)
{
    gu16_ice_tank_uv_operation_timer_sec++;

    if(gu16_ice_tank_uv_operation_timer_sec >= 600)
    {
        gu16_ice_tank_uv_operation_timer_sec = 0;
        gu8_ice_tank_uv_operation_timer_min++;
    }
    else{}

    /*..hui [19-10-24오후 8:23:29] 시간 단위가 아닌 그냥 분단위로..LCD 관련..*/
    if(gu8_ice_tank_uv_operation_timer_min >= UV_ICE_TANK_OPERATION_TIME_MIN)
    {
        bit_ice_tank_uv_start = CLEAR;
        initial_ice_tank_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_tank_uv_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_ice_tank_uv_standby_timer_sec++;

    if(gu16_ice_tank_uv_standby_timer_sec >= 600)
    {
        gu16_ice_tank_uv_standby_timer_sec = 0;
        gu16_ice_tank_uv_standby_timer_min++;
    }
    else{}

    if(gu16_ice_tank_uv_standby_timer_min >= 60)
    {
        gu16_ice_tank_uv_standby_timer_min = 0;
        gu16_ice_tank_uv_standby_timer_hour++;
    }
    else{}

    if( gu16_ice_tank_uv_standby_timer_hour >= 6 )
    {
        initial_ice_tank_uv_timer();
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_tank_uv(void)
{
    bit_ice_tank_uv_start = SET;
    initial_ice_tank_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tank_uv_timer(void)
{
    gu16_ice_tank_uv_operation_timer_sec = 0;
    gu8_ice_tank_uv_operation_timer_min = 0;
    gu16_ice_tank_uv_operation_timer_hour = 0;

    gu16_ice_tank_uv_standby_timer_sec = 0;
    gu16_ice_tank_uv_standby_timer_min = 0;
    gu16_ice_tank_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_tank_reed_sw_input(void)
{
    if(pREED_TANK_COVER == CLEAR)
    {
        gu8_uv_service_reed_off_cnt = 0;
        gu8_uv_service_reed_on_cnt++;

        if( gu8_uv_service_reed_on_cnt >= UV_TANK_COVER_REED_DETECT_TIME )
        {
            /*..hui [19-1-29오후 3:51:34] 탱크 커버 닫힘..*/
            gu8_uv_service_reed_on_cnt = UV_TANK_COVER_REED_DETECT_TIME;
            bit_uv_tank_input = SET;
        }
        else{}
    }
    else
    {
        gu8_uv_service_reed_on_cnt = 0;
        gu8_uv_service_reed_off_cnt++;

        if( gu8_uv_service_reed_off_cnt >= UV_TANK_COVER_REED_DETECT_TIME )
        {
            /*..hui [19-1-29오후 3:51:38] 탱크 커버 열림..*/
            gu8_uv_service_reed_on_cnt = UV_TANK_COVER_REED_DETECT_TIME;
            bit_uv_tank_input = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_uv_remain_time(void)
{
    U8 mu8_time_water_tank = 0;
    U8 mu8_percent_water_tank = 0;
    U8 mu8_time_tray = 0;
    U8 mu8_percent_tray = 0;
    U8 mu8_time_ice_tank = 0;
    U8 mu8_percent_ice_tank = 0;
    U8 mu8_a = 0;
    U8 mu8_b = 0;

    U16 mu16_x = 0;
    U16 mu16_y = 0;


    if( bit_uv_water_tank_out == SET )
    {
        mu8_time_water_tank = (U8)(UV_WATER_TANK_OPERATION_TIME_MIN - gu8_water_tank_uv_operation_timer_min);
        mu8_percent_water_tank = (U8)((U8)(gu8_water_tank_uv_operation_timer_min / 12) * 10);
    }
    else{}

    if( bit_uv_ice_tank_out == SET )
    {
        if( Bit2_Ice_Tank_UV_Ice_Off_On_State == SET )
        {
            /*..hui [24-2-14오후 4:21:16] 얼음 OFF했을때 2시간..*/
            mu8_time_ice_tank = (U8)(UV_ICE_OFF_OPERATION_TIME_MIN - gu8_ice_off_uv_operation_timer_min);
            mu8_percent_ice_tank = (U8)((U8)(gu8_ice_off_uv_operation_timer_min / 12) * 10);
        }
        else
        {
            mu8_time_ice_tank = (U8)(UV_ICE_TANK_OPERATION_TIME_MIN - gu8_ice_tank_uv_operation_timer_min);
            mu8_percent_ice_tank = (U8)((U8)(gu8_ice_tank_uv_operation_timer_min / 12) * 10);
        }
    }
    else{}

    /*if( bit_uv_ice_tray_out == SET )*/
    if( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR )
    {
        /*..hui [24-4-5오전 9:06:45] 제빙중에는 표시하지 않는다..*/
        if( Bit2_Ice_Tray_1_2_UV_Ice_Off_On_State == SET )
        {
            /*..hui [24-2-14오후 4:21:16] 얼음 OFF했을때 2시간..*/
            mu8_time_tray = (U8)(UV_ICE_OFF_OPERATION_TIME_MIN - gu8_ice_off_uv_operation_timer_min);
            mu8_percent_tray = (U8)((U8)(gu8_ice_off_uv_operation_timer_min / 12) * 10);
        }
        else
        {
            mu8_time_tray = (U8)(UV_ICE_TRAY_OPERATION_TIME_MIN - gu8_ice_tray_1_2_uv_operation_timer_min);
            mu8_percent_tray = (U8)((U8)(gu8_ice_tray_1_2_uv_operation_timer_min / 6) * 10);
        }

        #if 0
        if( Bit0_Ice_Tray_1_2_UV_On_State == SET
            && gu8IceStep == STATE_31_MAIN_ICE_MAKING )
        {
            /*..hui [24-2-14오후 5:17:37] 아이스트레이-제빙중에는 제빙 시간으로 계산..*/
            mu8_time_tray = (U8)(gu16IceMakeTime / 600);

            mu16_x = gu16_uv_ice_make_time / 10;
            mu16_y = gu16_uv_ice_make_time - gu16IceMakeTime;
            mu8_percent_tray = (U8)((U8)(mu16_y / mu16_x) * 10);
        }fwwf
        else if( Bit2_Ice_Tray_1_2_UV_Ice_Off_On_State == SET )
        {
            /*..hui [24-2-14오후 4:21:16] 얼음 OFF했을때 2시간..*/
            mu8_time_tray = mu8_time_ice_tank;
            mu8_percent_tray = mu8_percent_ice_tank;
        }
        else
        {
            mu8_time_tray = (U8)(UV_ICE_TRAY_OPERATION_TIME_MIN - gu8_ice_tray_1_2_uv_operation_timer_min);
            mu8_percent_tray = (U8)((U8)(gu8_ice_tray_1_2_uv_operation_timer_min / 6) * 10);
        }
        #endif
    }
    else{}


    if( mu8_time_water_tank > mu8_time_tray )
    {
        mu8_a = mu8_time_water_tank;
        mu8_b = mu8_percent_water_tank;
    }
    else
    {
        mu8_a = mu8_time_tray;
        mu8_b = mu8_percent_tray;
    }

    if( mu8_time_ice_tank > mu8_a )
    {
        mu8_a = mu8_time_ice_tank;
        mu8_b = mu8_percent_ice_tank;
    }
    else{}

    gu8_display_uv_reamin_minute = mu8_a;
    gu8_display_uv_elapsed_percent = mu8_b;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



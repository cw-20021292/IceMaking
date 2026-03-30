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


/***********************************************************************************************************************/
TYPE_BYTE          U8IceTankUvONB;
#define            u8IceTankUvON                         U8IceTankUvONB.byte
#define            Bit0_Ice_Tank_UV_On_State             U8IceTankUvONB.Bit.b0




TYPE_BYTE          U8IceTankUvOFFB;
#define            u8IceTankUvOFF                        U8IceTankUvOFFB.byte
#define            Bit0_Tank_Open_UV_Off_State           U8IceTankUvOFFB.Bit.b0
#define            Bit1_Ice_Tank_UV_Off_State         U8IceTankUvOFFB.Bit.b1
#define            Bit2_Auto_UV_Off_State                U8IceTankUvOFFB.Bit.b2
#define            Bit3_Ice_Error_UV_Off_State           U8IceTankUvOFFB.Bit.b3



TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                     U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State         U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State        U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State             U812VPowerControl.Bit.b2
#define            Bit3_Faucet_UV_12V_Out_State          U812VPowerControl.Bit.b3
#define			   Bit4_Ice_Extraction_UV_12V_Out_State	 U812VPowerControl.Bit.b4
#define			   Bit5_Drain_Pump_12V_Out_State	 	 U812VPowerControl.Bit.b5




/***********************************************************************************************************************/


bit F_Auto_UV_Control;
bit bit_ice_tank_uv_start;

U8 gu8_uv_ster_timer_per_min;

U8 gu8_UV_Ster_Count_One_Day;

U8 gu8_uv_ster_max_operation_one_day;


U16 gu16_ice_tank_uv_operation_timer_sec;
U16 gu16_ice_tank_uv_operation_timer_min;
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
        Bit1_Ice_Tank_UV_Off_State = F_Ice;
    }
    else
    {
        if( gu16StepMotor2 == 0 )
        {
            Bit1_Ice_Tank_UV_Off_State = CLEAR;
        }
        else{}
    }

/***********************************************************************************************/
    if( u8IceTankUvOFF > 0 )
    {
        pUV_LED_ICE_TANK = CLEAR;                  /*off*/
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
        bit_uv_ice_tank_out = CLEAR;
    }
    else
    {
        if( u8IceTankUvON > 0 )
        {
            pUV_LED_ICE_TANK = SET;                 /*on*/
            Bit1_Ice_Tank_UV_12V_Out_State = SET;
            bit_uv_ice_tank_out = SET;
        }
        else
        {
            pUV_LED_ICE_TANK = CLEAR;              /*off*/
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

    if( F_IceOn == CLEAR )
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
        gu16_ice_tank_uv_operation_timer_min++;
    }
    else{}

    /*..hui [19-10-24오후 8:23:29] 시간 단위가 아닌 그냥 분단위로..LCD 관련..*/
    if(gu16_ice_tank_uv_operation_timer_min >= 120)
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
    gu16_ice_tank_uv_operation_timer_min = 0;
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



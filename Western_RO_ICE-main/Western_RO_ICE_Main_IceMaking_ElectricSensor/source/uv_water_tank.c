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
#include    "uv_water_tank.h"


void output_water_tank_uv(void);
U8 uv_water_tank_control(void);
void uv_water_tank_operation_timer(void);
U8 uv_water_tank_standby_timer(void);
void start_water_tank_uv(void);
void initial_water_tank_uv_timer(void);



/***********************************************************************************************************************/
TYPE_BYTE          U8WaterTankUVONB;
#define            gu8WaterTankUVOn                           U8WaterTankUVONB.byte
#define            Bit0_Water_Tank_UV_On_State                U8WaterTankUVONB.Bit.b0
#define            Bit1_Water_Tank_UV_Fault_Test_State        U8WaterTankUVONB.Bit.b1


TYPE_BYTE          U8WaterTankUVOFFB;
#define            u8WaterTankUvOFF                           U8WaterTankUVOFFB.byte
#define            Bit0_Water_Tank_UV_Tank_Open_Off_State     U8WaterTankUVOFFB.Bit.b0
#define            Bit1_Water_Tank_UV_Retry_3S_Off_State      U8WaterTankUVOFFB.Bit.b1
#define            Bit2_Water_Tank_UV_Error_Off_State         U8WaterTankUVOFFB.Bit.b2

/***********************************************************************************************************************/
bit bit_water_tank_uv_start;

U16 gu16_water_tank_uv_operation_timer_sec;
U8 gu8_water_tank_uv_operation_timer_min;
U16 gu16_water_tank_uv_operation_timer_hour;

U16 gu16_water_tank_uv_standby_timer_sec;
U16 gu16_water_tank_uv_standby_timer_min;
U16 gu16_water_tank_uv_standby_timer_hour;

U8 gu8_uv_water_tank_step;


bit bit_uv_water_tank_out;


U8 gu8_uv_water_tank_retry_timer;


bit bit_water_uv_first;
U16 gu16_water_uv_first_timer;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_water_tank_uv(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    Bit0_Water_Tank_UV_On_State = uv_water_tank_control();


    /*..hui [24-11-28오전 10:26:11] 전원 인가 후 1분 30초 동안 계속 켜서 고장 확인..*/
    /*..hui [24-11-28오전 10:26:47] UV 교체 후 정상 확인하려면 6시간동안 기다려야하는 문제..*/
    /*..hui [24-11-28오전 10:27:03] 서비스기획팀 요청~~~..*/
    /*..hui [24-11-28오후 1:19:16] 얼음 탱크 UV 테스트중 동일하게 동작..*/
    if( bit_uv_fault_test_start == SET )
    {
        Bit1_Water_Tank_UV_Fault_Test_State = Bit3_Ice_Tank_UV_Fault_Test_On_State;
    }
    else
    {
        Bit1_Water_Tank_UV_Fault_Test_State = CLEAR;
    }



    #if 0
    if( bit_water_uv_first == CLEAR )
    {
        if( gu8_water_uv_error_elasped_day >= 1 )
        {
            gu16_water_uv_first_timer++;

            if( gu16_water_uv_first_timer >= 600 )
            {
                gu16_water_uv_first_timer = 0;
                bit_water_uv_first = SET;
                Bit1_Water_Tank_UV_Fault_Test_State = CLEAR;
            }
            else
            {
                Bit1_Water_Tank_UV_Fault_Test_State = SET;
            }
        }
        else
        {
            gu16_water_uv_first_timer = 0;
            bit_water_uv_first = SET;
            Bit1_Water_Tank_UV_Fault_Test_State = CLEAR;
        }
    }
    else
    {
        gu16_water_uv_first_timer = 0;
        Bit1_Water_Tank_UV_Fault_Test_State = CLEAR;
    }
    #endif
    /***********************************************************************************************/
    /*..hui [23-5-31오후 3:13:54] 탑커버 열릴경우 일시정지..*/
    Bit0_Water_Tank_UV_Tank_Open_Off_State = ~bit_uv_tank_input;

    if( bit_water_tank_uv_retry_stop == SET )
    {
        gu8_uv_water_tank_retry_timer++;

        if( gu8_uv_water_tank_retry_timer >= 30 )
        {
            bit_water_tank_uv_retry_stop = CLEAR;
            gu8_uv_water_tank_retry_timer = 0;
            Bit1_Water_Tank_UV_Retry_3S_Off_State = CLEAR;
        }
        else
        {
            Bit1_Water_Tank_UV_Retry_3S_Off_State = SET;
        }
    }
    else
    {
        gu8_uv_water_tank_retry_timer = 0;
        Bit1_Water_Tank_UV_Retry_3S_Off_State = CLEAR;
    }

    Bit2_Water_Tank_UV_Error_Off_State = Bit23_Water_Tank_1_2_UV_Error__E74;

/***********************************************************************************************/
    if( u8WaterTankUvOFF > 0 )
    {
        pUV_LED_WATER_TANK_1_2 = CLEAR;                  /*off*/
        Bit3_Water_Tank_UV_12V_Out_State = CLEAR;
        bit_uv_water_tank_out = CLEAR;
    }
    else
    {
        if( gu8WaterTankUVOn > 0 )
        {
            pUV_LED_WATER_TANK_1_2 = SET;                 /*on*/
            Bit3_Water_Tank_UV_12V_Out_State = SET;
            bit_uv_water_tank_out = SET;
        }
        else
        {
            pUV_LED_WATER_TANK_1_2 = CLEAR;              /*off*/
            Bit3_Water_Tank_UV_12V_Out_State = CLEAR;
            bit_uv_water_tank_out = CLEAR;
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_water_tank_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

    /*..hui [23-6-30오전 10:20:26] 설치 플러싱할때도 안함..*/
    if( bit_install_flushing_state == SET )
    {
        initial_water_tank_uv_timer();
        gu8_uv_water_tank_step = 0;
        bit_water_tank_uv_start = CLEAR;
        return CLEAR;
    }
    else{}

/********************************************************************************************/
    switch( gu8_uv_water_tank_step )
    {
        case 0 :

            /*..hui [19-10-24오후 8:34:44] 6시간 대기..*/
            mu8_finish = uv_water_tank_standby_timer();

            if(mu8_finish == SET)
            {
                gu8_uv_water_tank_step = 1;
                start_water_tank_uv();
            }
            else{}

        break;

        case 1 :

            /*..hui [23-2-10오전 10:55:28] 파우셋 UV는 30분만 가동..*/
            if(bit_water_tank_uv_start == SET)
            {
                /*..hui [23-2-10오전 10:55:38] 물 추출중에는 정지..*/
                if( u8WaterTankUvOFF == 0 )
                {
                    uv_water_tank_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu8_uv_water_tank_step = 0;
            }

        break;

        default :

            gu8_uv_water_tank_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_water_tank_operation_timer(void)
{
    gu16_water_tank_uv_operation_timer_sec++;

    if(gu16_water_tank_uv_operation_timer_sec >= 600)
    {
        gu16_water_tank_uv_operation_timer_sec = 0;
        gu8_water_tank_uv_operation_timer_min++;
    }
    else{}

    /*..hui [23-5-31오후 3:10:41] 6시간 대기 - 2시간 동작..*/
    if(gu8_water_tank_uv_operation_timer_min >= UV_WATER_TANK_OPERATION_TIME_MIN)
    {
        bit_water_tank_uv_start = CLEAR;
        initial_water_tank_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_water_tank_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_water_tank_uv_standby_timer_sec++;

    if(gu16_water_tank_uv_standby_timer_sec >= 600)
    {
        gu16_water_tank_uv_standby_timer_sec = 0;
        gu16_water_tank_uv_standby_timer_min++;
    }
    else{}

    if(gu16_water_tank_uv_standby_timer_min >= 60)
    {
        gu16_water_tank_uv_standby_timer_min = 0;
        gu16_water_tank_uv_standby_timer_hour++;
    }
    else{}

    if( gu16_water_tank_uv_standby_timer_hour >= 6 )
    {
        initial_water_tank_uv_timer();
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_water_tank_uv(void)
{
    bit_water_tank_uv_start = SET;
    initial_water_tank_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_water_tank_uv_timer(void)
{
    gu16_water_tank_uv_operation_timer_sec = 0;
    gu8_water_tank_uv_operation_timer_min = 0;
    gu16_water_tank_uv_operation_timer_hour = 0;

    gu16_water_tank_uv_standby_timer_sec = 0;
    gu16_water_tank_uv_standby_timer_min = 0;
    gu16_water_tank_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



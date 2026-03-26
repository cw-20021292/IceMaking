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
#include    "error_leakage.h"

void check_flow_error(void);
void check_error_leakage_sensor(void);
void check_error_blocked_trayin(void);
void check_error_blocked_water_flow(void);
U8 flow_block_condition(void);

TYPE_BYTE          U8FlowBlockCheckStateB;
#define            u8FlowBlockCheckState                       U8FlowBlockCheckStateB.byte
#define            Bit0_Flow_Block_Check_State1                U8FlowBlockCheckStateB.Bit.b0
#define            Bit1_Flow_Block_Check_State2                U8FlowBlockCheckStateB.Bit.b1
#define            Bit2_Flow_Block_Check_State3                U8FlowBlockCheckStateB.Bit.b2
#define            Bit3_Flow_Block_Check_State4                U8FlowBlockCheckStateB.Bit.b3
#define            Bit4_Flow_Block_Check_State5                U8FlowBlockCheckStateB.Bit.b4
#define            Bit5_Flow_Block_Check_State6                U8FlowBlockCheckStateB.Bit.b5
#define            Bit6_Flow_Block_Check_State7                U8FlowBlockCheckStateB.Bit.b6
#define            Bit7_Flow_Block_Check_State8                U8FlowBlockCheckStateB.Bit.b7

U16 gu16_LeakageCheckCount;
U16 gu16_LeakageCheckCount2;


U16 u16_tray_water_in_timer;
U16 u16_tray_flow_check_timer;

bit F_Tray_In_Error_Temporary;
U16 u16_tray_input_add_timer;

U8 gu8_tray_wrong_flow_retry_cnt;
U8 gu8_tray_normal_flow_retry_cnt;

U16 gu16_flow_block_check_timer;
U16 gu16_flow_block_clear_timer;

U8 gu8_clear_block_error;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_flow_error(void)
{
    /*..hui [18-11-22오후 3:36:39] 누수 센서 에러..*/
    check_error_leakage_sensor();
    /*..hui [18-11-22오후 3:36:46] 유량센서 누수 에러..*/
    //check_error_leaked_water_flow();
    /*..hui [18-11-22오후 3:36:52] 단수 에러..*/
    //check_error_blocked_water_flow();

    check_error_blocked_trayin();

    /*..hui [23-6-9오후 2:43:47] 단수에러..*/
    check_error_blocked_water_flow();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_leakage_sensor(void)
{
    if(gu16ADLeakage >= LEAKAGE_DETECT_AD)
    {
        gu16_LeakageCheckCount2 = 0;

        if (gu16_LeakageCheckCount < LEAKAGE_ERROR_DETECT_TIME)
        {
            gu16_LeakageCheckCount++;
        }
        else
        {
            if(Bit3_Leakage_Sensor_Error__E01 != SET)
            {
                Bit3_Leakage_Sensor_Error__E01 = SET;
                play_voice_leakage_error_12();
            }
            else{}
        }
    }
    else
    {
        gu16_LeakageCheckCount = 0;

        if(gu16_LeakageCheckCount2 < LEAKAGE_ERROR_CLEAR_TIME)
        {
            gu16_LeakageCheckCount2++;
        }
        else
        {
            Bit3_Leakage_Sensor_Error__E01 = CLEAR;
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_blocked_trayin(void)
{
    U16 mu16_clear_time = 0;

    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY
       && F_Tray_In_Error_Temporary != SET)
    {
        /*if(pVALVE_ICE_TRAY_IN == SET && bit_tray_pump_output == SET)*/
        if( bit_tray_pump_output == SET )
        {
            /*..hui [20-11-30오후 3:33:32] 5Hz 이하로 10초 이상 감지 시 펌프 전압 FULL로 변경..*/
            if( gu8_Tray_Flow_1sec <= HOT_BLOCKED_FLOW_HZ )
            {
                u16_tray_flow_check_timer++;

                if(u16_tray_flow_check_timer >= BLOCKED_TRAIN_IN_CHECK_TIME)
                {
                    u16_tray_flow_check_timer = 0;
                    F_Tray_In_Error_Temporary = SET;
                }
                else{}
            }
            else
            {
                u16_tray_flow_check_timer = 0;
            }
        }
        else
        {
            if( F_WaterOut == SET )
            {
                /*..hui [20-6-22오전 10:21:02] 추출할때 카운트 초기화하도록 수정.. 반복적인 추출일때 해제동작이 제대로 안이루어질수있음..*/
                /*..hui [20-6-22오전 10:21:06] 이승헌과장..*/
                u16_tray_flow_check_timer = 0;
            }
            else{}
        }
    }
    else
    {
        u16_tray_flow_check_timer = 0;
    }

    if( F_Tray_In_Error_Temporary == SET )
    {
        mu16_clear_time = BLOCKED_TRAY_ADD_TIME;

        /*..hui [20-11-30오후 4:05:29] 트레이 밸브 열려있고 펌프 가동중에만 카운트하는걸로..*/
        /*if(pVALVE_ICE_TRAY_IN == SET && bit_tray_pump_output == SET)*/
        if( bit_tray_pump_output == SET )
        {
            u16_tray_input_add_timer++;
        }
        else{}

        /*..hui [20-11-30오후 3:52:36] 1분동안 펌프 FULL로 가동 후 제빙 진입..*/
        if( u16_tray_input_add_timer >= mu16_clear_time )
        {
            F_Tray_In_Error_Temporary = CLEAR;
            u16_tray_input_add_timer = 0;

            /*..hui [20-11-30오후 3:57:17] 유량센서 감지 안되더라도 일정시간동안 FULL로 가동 후 물이 들어갔다고 판단하고 종료..*/
            /*..hui [20-11-30오후 3:57:42] 노용연 차장님..에러를 그냥 지우자..*/
            /*..hui [20-11-30오후 3:57:46] 대신 감지 안될때 FULL로 가동하는 사양은 남겨두는게 좋을 것 같음..*/
            gu16_Ice_Tray_Fill_Hz = 0;
        }
        else{}
    }
    else
    {
        u16_tray_input_add_timer = 0;
    }

    /*..hui [20-11-30오후 4:57:17] 펌프 FULL 가동중 유량센서 정상으로 돌아와서 종료될 경우 대비..*/
    /*..hui [20-11-30오후 4:57:30] 트레이 입수 state 제외하고는 초기화하도록..*/
    if( gu8IceStep != STATE_20_WATER_IN_ICE_TRAY )
    {
        F_Tray_In_Error_Temporary = CLEAR;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_blocked_water_flow(void)
{
    U8 u8_check_enable = CLEAR;
    U8 u8_block_error_fix = CLEAR;
    U16 mu16_time = 0;
    U8 mu8_hz = 0;

    u8_check_enable = flow_block_condition();

    if( u8_check_enable == SET )
    {
        if( Bit6_Main_Water_Flow_Block_Error__E09 != SET )
        {
            if( gu8_Filter_Flow_1sec < FILTER_FLOW_BLOCK_DETECT_HZ_0_1_LPM )
            {
                gu16_flow_block_check_timer++;

                if(gu16_flow_block_check_timer >= FLOW_BLOCK_ERROR_CHECK_TIME)
                {
                    gu16_flow_block_check_timer = 0;
                    Bit6_Main_Water_Flow_Block_Error__E09 = SET;
                    play_voice_flow_block_error_11();
                }
                else{}
            }
            else
            {
                gu16_flow_block_check_timer = 0;
            }
        }
        else{}
    }
    else
    {
        gu16_flow_block_check_timer = 0;
    }

    if(gu8_clear_block_error == SET)
    {
        gu8_clear_block_error = CLEAR;
        gu16_flow_block_clear_timer = FLOW_BLOCK_ERROR_CLEAR_TIME;
    }
    else
    {
        /*..hui [23-11-1오전 11:31:02] 플러싱때 단수에러는 버튼 누르기 전까지는 계속 표시하고있는걸로..*/
        gu16_flow_block_clear_timer = 0;
    }

    if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
    {
        gu16_flow_block_clear_timer++;

        if(gu16_flow_block_clear_timer >= FLOW_BLOCK_ERROR_CLEAR_TIME)
        {
            gu16_flow_block_clear_timer = 0;
            Bit6_Main_Water_Flow_Block_Error__E09 = CLEAR;
        }
        else{}
    }
    else
    {
        gu16_flow_block_clear_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 flow_block_condition(void)
{
    U8 mu8_return = 0;



    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        /*if( gu8_flushing_step == 3 )*/
        /*if( gu8_flushing_step == 8 )*/
        /*..hui [23-9-21오후 2:04:27] RO 디스크 열고 30초 동안 플러싱 할때만 단수 감지하도록 변경..*/
        /*..hui [23-9-21오후 2:04:42] 저압 저유량일때 유량센서가 간헐적으로 감지가 잘 안됨..*/
        /*..hui [23-9-22오후 1:36:08] 플러싱 시작할때 한번, 끝나고 한번..*/
        if( gu8_flushing_step == 4 )
        {
            Bit0_Flow_Block_Check_State1 = SET;
        }
        else if( gu8_flushing_step == 12 )
        {
            Bit0_Flow_Block_Check_State1 = SET;
        }
        else
        {
            Bit0_Flow_Block_Check_State1 = CLEAR;
        }
    }
    else
    {
        Bit0_Flow_Block_Check_State1 = CLEAR;
    }



    #if 0
    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        /*if( gu8_flushing_step == 3 )*/
        if( gu8_flushing_step == 8 )
        {
            if( bit_install_flushing_state == SET )
            {
                if( gu8_flushing_operation_timer_min >= 5 )
                {
                    Bit0_Flow_Block_Check_State1 = SET;
                }
                else
                {
                    Bit0_Flow_Block_Check_State1 = CLEAR;
                }
            }
            else
            {
                if( gu8_filter_flushing_state == FILTER_FLUSHING_NEO_INO )
                {
                    if( gu16_flushing_timer >= 300 || gu8_flushing_operation_timer_min >= 1 )
                    {
                        Bit0_Flow_Block_Check_State1 = SET;
                    }
                    else
                    {
                        Bit0_Flow_Block_Check_State1 = CLEAR;
                    }
                }
                else
                {
                    if( gu8_flushing_operation_timer_min >= 5 )
                    {
                        Bit0_Flow_Block_Check_State1 = SET;
                    }
                    else
                    {
                        Bit0_Flow_Block_Check_State1 = CLEAR;
                    }
                }
            }
        }
        else
        {
            Bit0_Flow_Block_Check_State1 = CLEAR;
        }
    }
    else
    {
        Bit0_Flow_Block_Check_State1 = CLEAR;
    }
    #endif

    /*..hui [23-9-21오후 2:01:39] 탱크 입수할때는 단수검사 안함..*/
    /*..hui [23-9-21오후 2:01:57] 유량센서 오감지 우려..*/
    #if 0
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        if( gu8_flushing_tank_step == 2 )
        {
            if( gu32_tank_flushing_operation_timer >= 3000 )
            {
                Bit1_Flow_Block_Check_State2 = SET;
            }
            else
            {
                Bit1_Flow_Block_Check_State2 = CLEAR;
            }
        }
        else if( gu8_flushing_tank_step == 3 )
        {
            Bit1_Flow_Block_Check_State2 = SET;
        }
        else
        {
            Bit1_Flow_Block_Check_State2 = CLEAR;
        }
    }
    else
    {
        Bit1_Flow_Block_Check_State2 = CLEAR;
    }
    #endif

    Bit1_Flow_Block_Check_State2 = CLEAR;

    /*Bit1_Flow_Block_Check_State2 = CLEAR;*/
    Bit2_Flow_Block_Check_State3 = CLEAR;
    Bit3_Flow_Block_Check_State4 = CLEAR;
    Bit4_Flow_Block_Check_State5 = CLEAR;
    Bit5_Flow_Block_Check_State6 = CLEAR;
    Bit6_Flow_Block_Check_State7 = CLEAR;
    Bit7_Flow_Block_Check_State8 = CLEAR;

    if( u8FlowBlockCheckState > 0 )
    {
        /*..hui [19-2-14오후 6:26:57] 메인 NOS 밸브가 잠궈져있지 않을때만.. 혹시나해서..*/
        /*..hui [23-8-23오후 2:10:37] FEED 열려있을때 추가..*/
        if( pVALVE_NOS != SET && pVALVE_FEED == SET )
        {
            mu8_return = SET;
        }
        else
        {
            mu8_return = CLEAR;
        }
    }
    else
    {
        mu8_return = CLEAR;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



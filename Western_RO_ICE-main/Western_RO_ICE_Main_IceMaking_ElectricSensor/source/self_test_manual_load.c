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
#include    "self_test_manual_load.h"



U8 manual_test_load(void);
U8 check_current( U8 mu8_load );
void output_load( U8 mu8_load, U8 mu8_out );
U8 manual_test_faucet(void);
U8 manual_test_flow(void);



U8 gu8_component_test_step;
U16 gu16_component_test_timer;

U8 gu8_current_check_step;
U16 gu16_current_check_timer;



U8 gu8_self_flow_test_step;
U16 gu16_self_flow_test_timer;


bit bit_self_faucet_reed_1;
bit bit_self_faucet_reed_2;
bit bit_self_faucet_reed_3;
bit bit_self_faucet_reed_4;

U16 gu16_self_tray_flow_save;
U16 gu16_self_ro_flow_save;



U16 gu16_gas_switch_current_max;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 manual_test_load(void)
{
    U16 mu16_val = 0;
    U8 mu8_decision = 0;
    U8 mu8_ok = 0;
    U8 mu8_return = 0;

    switch( gu8_component_test_step )
    {
        case 0 :

            gu16_component_test_timer = 0;
            gu16_current_check_timer = 0;
            gu8_component_test_step++;

        break;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
        case 1 :

            mu8_ok = check_current( DC_LOAD_1__FEED_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 2 :

            mu8_ok = check_current( DC_LOAD_2__NOS_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 3 :

            mu8_ok = check_current( DC_LOAD_3__HOT_OUT_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 4 :

            mu8_ok = check_current( DC_LOAD_4__PURE_OUT_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 5 :

            mu8_ok = check_current( DC_LOAD_5__COLD_OUT_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 6 :

            mu8_ok = check_current( DC_LOAD_6__HOT_IN_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 7 :

            mu8_ok = check_current( DC_LOAD_7__AIR_FEED_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 8 :

            mu8_ok = check_current( DC_LOAD_8__COLD_DRAIN_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 9 :

            mu8_ok = check_current( DC_LOAD_9__ICE_TRAY_IN_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 10 :

            mu8_ok = check_current( DC_LOAD_10__FLUSHING_FEED );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}


        break;

        case 11 :

            mu8_ok = check_current( DC_LOAD_11__RO_FLUSHING_MOTOR );

            if( mu8_ok == SET )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;

        case 12 :

            #if 0
            if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else
            {
                run_close_ro_drain();
            }
            #endif

            gu16_component_test_timer++;

            if( gu16_component_test_timer >= 50 )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;


        case 13 :

            mu8_ok = check_current( DC_LOAD_12__HOT_OVERHEAT_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 14 :

            mu8_ok = check_current( DC_LOAD_13__HOT_STER_LEFT_VALVE );


            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 15 :

            mu8_ok = check_current( DC_LOAD_14__HOT_STER_RIGHT_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 16 :

            mu8_ok = check_current( DC_LOAD_15__FLUSHING_NOS_VALVE );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 17 :

            mu8_ok = check_current( DC_LOAD_16__COLD_FAN );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 18 :

            mu8_ok = check_current( DC_LOAD_19__UV_ICE_TANK_1_2_BACK );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

        case 19 :

            mu8_ok = check_current( DC_LOAD_23__SWING_BAR );

            if( mu8_ok == SET )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;

        case 20 :

            mu8_ok = check_current( DC_LOAD_24__ICE_DOOR_MOTOR );

            if( mu8_ok == SET )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;

        case 21 :

            gu16_component_test_timer++;

            if( gu16_component_test_timer >= 50 )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;

        case 22 :

            mu8_ok = check_current( DC_LOAD_25__GAS_SWITCH_MOTOR );

            if( mu8_ok == SET )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;

            }
            else{}

        break;

        case 23 :

            gu16_component_test_timer++;

            if( gu16_component_test_timer >= 50 )
            {
                gu16_component_test_timer = 0;
                gu8_component_test_step++;
            }
            else{}

        break;



        case 24 :

            mu8_ok = check_current( DC_LOAD_26__DRAIN_PUMP );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;


        case 25 :

            mu8_ok = check_current( DC_LOAD_27__ICE_TRAY_PUMP );

            if( mu8_ok == SET )
            {
                gu8_component_test_step++;
            }
            else{}

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

        case 26 :

            gu8_component_test_step = 0;
            gu16_component_test_timer = 0;
            mu8_return = SET;

        break;

        default :

            gu8_component_test_step = 0;
            gu16_component_test_timer = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 check_current( U8 mu8_load )
{
    U16 mu16_val = 0;
    U8 mu8_decision = 0;
    U8 mu8_return = 0;
    U16 mu16_stable_time = 0;

    if( mu8_load == DC_LOAD_3__HOT_OUT_VALVE )
    {
        mu16_stable_time = 30;
    }
    else if( mu8_load == DC_LOAD_4__PURE_OUT_VALVE )
    {
        mu16_stable_time = 30;
    }
    else if( mu8_load == DC_LOAD_5__COLD_OUT_VALVE )
    {
        mu16_stable_time = 30;
    }
    else if( mu8_load == DC_LOAD_11__RO_FLUSHING_MOTOR )
    {
        mu16_stable_time = 20;
    }
    else if( mu8_load == DC_LOAD_24__ICE_DOOR_MOTOR )
    {
        mu16_stable_time = 20;
    }
    else if( mu8_load == DC_LOAD_25__GAS_SWITCH_MOTOR )
    {
        /*mu16_stable_time = 30;*/
        /*..hui [24-1-19오후 5:41:01] 냉매전환밸브 최대 전류값으로 하기 위해 변경..*/
        mu16_stable_time = 100;
    }
    else
    {
        mu16_stable_time = DC_CURRENT_STABLE_TIME;
    }

    switch( gu8_current_check_step )
    {
        case 0 :

            gu16_current_check_timer = 0;
            gu8_current_check_step++;

        break;

        case 1 :

            gu16_current_check_timer++;

            /*..hui [20-10-28오후 3:08:07] 전류 떨어질때까지 1초 대기..*/
            if( gu16_current_check_timer >= CURRENT_DELAY_TIME )
            {
                gu16_current_check_timer = 0;
                gu8_current_check_step++;
                gu16_gas_switch_current_max = 0;
            }
            else{}

        break;

        case 2 :

            output_load( mu8_load, ON );
            gu8_current_check_step++;

        break;

        case 3 :

            gu16_current_check_timer++;

            /*..hui [20-10-28오후 1:30:44] 부하 켜고 3초 후 전류 체크..*/
            if( gu16_current_check_timer >= mu16_stable_time )
            {
                gu16_current_check_timer = 0;

                if( mu8_load == DC_LOAD_16__COLD_FAN )
                {
                    mu16_val = calculate_fan_current( gu16_AD_Result_Fan_Current );
                    /*..hui [20-10-28오후 9:26:06] 최종 값 업데이트..*/
                    SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;
                }
                else if( mu8_load == DC_LOAD_19__UV_ICE_TANK_1_2_BACK )
                {
                    mu16_val = calculate_uv_current( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current );
                    SELF_Test_Result_Data.word[ DC_LOAD_19__UV_ICE_TANK_1_2_BACK ] = mu16_val;

                    mu16_val = calculate_uv_current( gu16_AD_Result_UV_Ice_Tray_1_2_Current );
                    SELF_Test_Result_Data.word[ DC_LOAD_20__UV_ICE_TRAY_1_2 ] = mu16_val;

                    mu16_val = calculate_uv_current( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed );
                    SELF_Test_Result_Data.word[ DC_LOAD_21__UV_COLD_TANK_1_2 ] = mu16_val;

                    //////mu16_val = calculate_uv_current( gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed );
                    mu16_val = calculate_uv_current( gu16_AD_Result_UV_Ice_Tank_3_Front_Current );

                    SELF_Test_Result_Data.word[ DC_LOAD_22__UV_ICE_TANK_3_FRONT ] = mu16_val;
                }
                else if( mu8_load == DC_LOAD_25__GAS_SWITCH_MOTOR )
                {
                    /*mu16_val = calculate_fan_current( gu16_AD_Result_DC_Current_12V );*/
                    mu16_val = calculate_fan_current( gu16_gas_switch_current_max );

                    /*..hui [24-1-9오후 2:40:02] 냉매전환밸브는 12V..*/
                    SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;
                }
                else if( mu8_load == DC_LOAD_26__DRAIN_PUMP )
                {
                    mu16_val = calculate_pump_current( gu16_AD_Drain_Pump_Current );
                    /*..hui [20-10-28오후 9:26:06] 최종 값 업데이트..*/
                    SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;
                }
                else if( mu8_load == DC_LOAD_27__ICE_TRAY_PUMP )
                {
                    mu16_val = calculate_pump_current( gu16_AD_Tray_Pump_Current );
                    /*..hui [20-10-28오후 9:26:06] 최종 값 업데이트..*/
                    SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;
                }
                else
                {
                    mu16_val = calculate_dc_current( gu16_AD_Result_DC_Current_24V );
                    /*..hui [20-10-28오후 9:26:06] 최종 값 업데이트..*/
                    SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;
                }

                /*..hui [20-10-28오후 9:26:06] 최종 값 업데이트..*/
                /*SELF_Test_Result_Data.word[ mu8_load ] = mu16_val;*/

                //
                output_load( mu8_load, OFF );
                //

                gu8_current_check_step++;
            }
            else
            {
                if( mu8_load == DC_LOAD_25__GAS_SWITCH_MOTOR )
                {
                    /*..hui [24-1-19오후 5:43:31] 냉매전환밸브 최대값으로 하기위해..*/
                    if( gu16_gas_switch_current_max < gu16_AD_Result_DC_Current_12V )
                    {
                        gu16_gas_switch_current_max  = gu16_AD_Result_DC_Current_12V;
                    }
                    else{}
                }
                else
                {
                    gu16_gas_switch_current_max = 0;
                }
            }

        break;

        case 4 :

            mu8_return = SET;
            gu8_current_check_step = 0;
            gu16_current_check_timer = 0;

        break;

        default :

            gu8_current_check_step = 0;
            gu16_current_check_timer = 0;

        break;
    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_load( U8 mu8_load, U8 mu8_out )
{
    if( mu8_load == DC_LOAD_1__FEED_VALVE )
    {
        pVALVE_FEED = mu8_out;
    }
    else if( mu8_load == DC_LOAD_2__NOS_VALVE )
    {
        pVALVE_NOS = mu8_out;
    }
    else if( mu8_load == DC_LOAD_3__HOT_OUT_VALVE )
    {
        pVALVE_HOT_OUT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_4__PURE_OUT_VALVE )
    {
        pVALVE_ROOM_OUT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_5__COLD_OUT_VALVE )
    {
        pVALVE_COLD_OUT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_6__HOT_IN_VALVE )
    {
        pVALVE_HOT_IN_FEED = mu8_out;
    }
    else if( mu8_load == DC_LOAD_7__AIR_FEED_VALVE )
    {
        pVALVE_AIR_VENT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_8__COLD_DRAIN_VALVE )
    {
        pVALVE_COLD_DRAIN = mu8_out;
    }
    else if( mu8_load == DC_LOAD_9__ICE_TRAY_IN_VALVE )
    {
        pVALVE_ICE_TRAY_IN_FEED = mu8_out;
    }
    else if( mu8_load == DC_LOAD_10__FLUSHING_FEED )
    {
        pVALVE_FLUSHING_FEED = mu8_out;
    }
    else if( mu8_load == DC_LOAD_11__RO_FLUSHING_MOTOR )
    {
        if( mu8_out == ON )
        {
            run_open_ro_drain();
        }
        else
        {
            run_close_ro_drain();
        }
    }
    else if( mu8_load == DC_LOAD_12__HOT_OVERHEAT_VALVE )
    {
        pVALVE_OVERHEATING_NOS = mu8_out;
    }
    else if( mu8_load == DC_LOAD_13__HOT_STER_LEFT_VALVE )
    {
        pVALVE_ICE_TANK_STER_FEED_LEFT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_14__HOT_STER_RIGHT_VALVE )
    {
        pVALVE_ICE_TANK_STER_FEED_RIGHT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_15__FLUSHING_NOS_VALVE )
    {
        pVALVE_FLUSHING_NOS = mu8_out;
    }
    else if( mu8_load == DC_LOAD_16__COLD_FAN )
    {
        pDC_FAN = mu8_out;
    }
    else if( mu8_load == DC_LOAD_19__UV_ICE_TANK_1_2_BACK )
    {
        pUV_LED_ICE_TANK_1_2_BACK = mu8_out;
        pUV_LED_ICE_TRAY_1_2 = mu8_out;
        pUV_LED_WATER_TANK_1_2 = mu8_out;
        pUV_LED_ICE_TANK_3_FRONT = mu8_out;
    }
    else if( mu8_load == DC_LOAD_23__SWING_BAR )
    {
        pSWING_BAR = mu8_out;
    }
    else if( mu8_load == DC_LOAD_24__ICE_DOOR_MOTOR )
    {
        F_IceDoorClose = SET;
    }
    else if( mu8_load == DC_LOAD_25__GAS_SWITCH_MOTOR )
    {
        GasSwitchInit();
    }
    else if( mu8_load == DC_LOAD_26__DRAIN_PUMP )
    {
        if( mu8_out == ON )
        {
            start_drain_pump( PUMP_PWM_MAX );
        }
        else
        {
            stop_drain_pump();
        }
    }
    else if( mu8_load == DC_LOAD_27__ICE_TRAY_PUMP )
    {
        if( mu8_out == ON )
        {
            start_tray_pump( PUMP_PWM_MAX );
        }
        else
        {
            stop_tray_pump();
        }
    }
    else{}
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 manual_test_flow(void)
{
    U8 mu8_return = 0;
    U16 mu16_val = 0;

    switch( gu8_self_flow_test_step )
    {
        case 0:

            U16_ICE_TRAY_FLOW_SENSOR_PART_0403 = 0;
            U16_RO_DRAIN_FLOW_SENSOR_PART_040C = 0;
            gu16_self_tray_flow_save = 0;
            gu16_self_ro_flow_save = 0;

            gu16_self_flow_test_timer = 0;
            gu8_self_flow_test_step++;

            break;

        case 1:

            gu16_self_flow_test_timer++;

            if( gu16_self_flow_test_timer >= SELF_MANUAL_FLOW_TEST_TIME )
            {
                pVALVE_ICE_TRAY_IN_FEED = CLEAR;
                stop_tray_pump();

                gu16_self_flow_test_timer = 0;
                gu8_self_flow_test_step++;

                /*..hui [23-12-21오전 11:01:02] 47hz === 300cc..*/
                /*..hui [23-12-21오전 11:01:08] 79hz == 500cc..*/
                /*..hui [23-12-21오전 11:01:14] 161hz ===1000cc..*/
                /*..hui [23-12-21오전 11:01:29] hz에 6 곱하고 20 더해주면 얼추 비슷하게 나옴....*/
                U16_ICE_TRAY_FLOW_SENSOR_PART_0403 = gu16_self_tray_flow_save * 6;
                U16_ICE_TRAY_FLOW_SENSOR_PART_0403 = U16_ICE_TRAY_FLOW_SENSOR_PART_0403 + 20;

                U16_ICE_FULL_SENSOR_PART_0801 = gu16ADIceFull;
                pIR_POWER = CLEAR;
            }
            else
            {
                pVALVE_ICE_TRAY_IN_FEED = SET;
                start_tray_pump( PUMP_PWM_MAX );

                if( gu8_Tray_Flow_1sec > gu16_self_tray_flow_save )
                {
                    gu16_self_tray_flow_save = gu8_Tray_Flow_1sec;
                }
                else{}

                /*..hui [23-12-22오전 9:20:26] 만빙센서 검사도 여기서..*/
                pIR_POWER = SET;
            }

            break;

        case 2:

            run_open_ro_drain();
            gu16_self_flow_test_timer = 0;
            gu8_self_flow_test_step++;

            break;

        case 3:

            if( gu8_ro_drain_status == RO_DRAIN_STATUS_OPEN )
            {
                gu16_self_flow_test_timer = 0;
                gu8_self_flow_test_step++;
                pVALVE_FEED = SET;
            }
            else{}

            break;

        case 4:

            gu16_self_flow_test_timer++;

            if( gu16_self_flow_test_timer >= SELF_MANUAL_FLOW_TEST_TIME )
            {
                pVALVE_FEED = CLEAR;
                run_close_ro_drain();

                gu16_self_flow_test_timer = 0;
                gu8_self_flow_test_step++;

                /*..hui [23-12-21오전 11:01:02] 47hz === 300cc..*/
                /*..hui [23-12-21오전 11:01:08] 79hz == 500cc..*/
                /*..hui [23-12-21오전 11:01:14] 161hz ===1000cc..*/
                /*..hui [23-12-21오전 11:01:29] hz에 6 곱하고 20 더해주면 얼추 비슷하게 나옴....*/
                U16_RO_DRAIN_FLOW_SENSOR_PART_040C = gu16_self_ro_flow_save * 6;
                U16_RO_DRAIN_FLOW_SENSOR_PART_040C = U16_RO_DRAIN_FLOW_SENSOR_PART_040C + 20;
            }
            else
            {
                pVALVE_FEED = SET;

                #if 0
                if( gu8_Tray_Flow_1sec > gu16_self_ro_flow_save )
                {
                    gu16_self_ro_flow_save = gu8_Tray_Flow_1sec;
                }
                else{}
                #endif

                /*..hui [24-11-27오후 2:46:35] 트레이 입수 유량으로 돼있었음.. 손선국님 발견.. 큰일날뻔~~..*/
                if( gu8_Filter_Flow_1sec > gu16_self_ro_flow_save )
                {
                    gu16_self_ro_flow_save = gu8_Filter_Flow_1sec;
                }
                else{}
            }

            break;

        case 5:

            if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
            {
                gu16_self_flow_test_timer = 0;
                gu8_self_flow_test_step++;
            }
            else{}

            break;

        case 6:

            gu16_self_flow_test_timer = 0;
            gu8_self_flow_test_step = 0;

            mu8_return = SET;

            break;

        default:

            gu16_self_flow_test_timer = 0;
            gu8_self_flow_test_step = 0;

            break;
    }

    return mu8_return;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



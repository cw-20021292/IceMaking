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
#include    "display_debug.h"


void fnd_debug(void);


bit bit_debug_mode_start;
DEBUG_STEP gu8_fnd_debug_step;

U8 gu8_debug_timer;

bit bit_ice_ster_test_debug_start;
U8 gu8_ice_ster_test_debug_step;
U8 gu8_ice_ster_drain_stop_count;
U8 gu8_ice_ster_low_water_stop_count;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_debug(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U16 mu16_a = 0;

    gu8_debug_timer++;

    if( gu8_debug_timer < 10 )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_fnd_debug_step / 10) % 10);
        mu8_temporary_one = (U8)(gu8_fnd_debug_step % 10);

        fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        return;
    }
    else
    {
        gu8_debug_timer = 10;
    }

    switch( gu8_fnd_debug_step )
    {
        case DEBUG__COMP_DELAY:

            mu8_temporary_hundred = (U8)((gu16CompOffDelay / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16CompOffDelay / 100) % 10);
            mu8_temporary_one = (U8)((gu16CompOffDelay / 10) % 10);

        break;

        case DEBUG__COLD_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
            mu8_temporary_ten = (U8)((gu8_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Cold_Temperature_One_Degree % 10);

        break;

        case DEBUG__ROOM_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_SMALL_r;
            mu8_temporary_ten = (U8)((gu8_Room_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Room_Temperature_One_Degree % 10);

        break;

        case DEBUG__HOT_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_H;
            mu8_temporary_ten = (U8)((gu8_Hot_Tank_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Hot_Tank_Temperature_One_Degree % 10);

        break;

        case DEBUG__MIXING_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_SMALL_n;
            mu8_temporary_ten = (U8)((gu8_Mixing_Out_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Mixing_Out_Temperature_One_Degree % 10);

        break;

        case DEBUG__OUT_DOOR_FRONT_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_SMALL_o;
            mu8_temporary_ten = (U8)((gu8_Amb_Front_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Amb_Front_Temperature_One_Degree % 10);

        break;

        case DEBUG__OUT_DOOR_SIDE_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
            mu8_temporary_ten = (U8)((gu8_Amb_Side_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Amb_Side_Temperature_One_Degree % 10);

        break;

        case DEBUG__OUT_DOOR_FINAL_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_F;
            mu8_temporary_ten = (U8)((gu8_Amb_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Amb_Temperature_One_Degree % 10);

        break;

        #if 0
        case DEBUG__TRAY_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_SMALL_t;
            mu8_temporary_ten = (U8)((gu8_Tray_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Tray_Temperature_One_Degree % 10);

        break;

        case DEBUG__TRAY_AVERAGE_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_A;
            mu8_temporary_ten = (U8)((gu8_average_tray_temp / 10) % 10);
            mu8_temporary_one = (U8)(gu8_average_tray_temp % 10);

        break;
        #endif







        case DEBUG__EVA_ICE_TEMP:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)((gu8_Eva_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Eva_Cold_Temperature_One_Degree % 10);

        break;

        case DEBUG__FLOW_HZ:

            mu8_temporary_hundred = (U8)((gu8_Tray_Flow_1sec / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_Tray_Flow_1sec / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Tray_Flow_1sec % 10);

        break;

        case DEBUG__DRAIN_HZ:

            mu8_temporary_hundred = (U8)((gu8_Filter_Flow_1sec / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_Filter_Flow_1sec / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Filter_Flow_1sec % 10);

        break;

        case DEBUG__ICE_FULL_AD:

            if( gu16ADIceFull >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16ADIceFull / 100) % 10);
                mu8_temporary_ten = (U8)((gu16ADIceFull / 10) % 10);
                mu8_temporary_one = (U8)(gu16ADIceFull % 10);
            }

        break;

        case DEBUG__LEAK_AD:

            if( gu16ADLeakage >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16ADLeakage / 100) % 10);
                mu8_temporary_ten = (U8)((gu16ADLeakage / 10) % 10);
                mu8_temporary_one = (U8)(gu16ADLeakage % 10);
            }

        break;

        case DEBUG__UV_WATER_AD:

            if( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed / 100) % 10);
                mu8_temporary_ten = (U8)((gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed / 10) % 10);
                mu8_temporary_one = (U8)(gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed % 10);
            }

        case DEBUG__UV_ICE_TANK_AD:

            if( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current / 100) % 10);
                mu8_temporary_ten = (U8)((gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current / 10) % 10);
                mu8_temporary_one = (U8)(gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current % 10);
            }

        break;

        case DEBUG__UV_ICE_TRAY_1_AD:

            if( gu16_AD_Result_UV_Ice_Tray_1_2_Current >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16_AD_Result_UV_Ice_Tray_1_2_Current / 100) % 10);
                mu8_temporary_ten = (U8)((gu16_AD_Result_UV_Ice_Tray_1_2_Current / 10) % 10);
                mu8_temporary_one = (U8)(gu16_AD_Result_UV_Ice_Tray_1_2_Current % 10);
            }

        break;

        case DEBUG__UV_ICE_TRAY_2_AD:

            if( gu16_AD_Result_UV_Ice_Tank_3_Front_Current >= 1000 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_9;
                mu8_temporary_ten = DISPLAY_NUM_9;
                mu8_temporary_one = DISPLAY_NUM_9;
            }
            else
            {
                mu8_temporary_hundred = (U8)((gu16_AD_Result_UV_Ice_Tank_3_Front_Current / 100) % 10);
                mu8_temporary_ten = (U8)((gu16_AD_Result_UV_Ice_Tank_3_Front_Current / 10) % 10);
                mu8_temporary_one = (U8)(gu16_AD_Result_UV_Ice_Tank_3_Front_Current % 10);
            }

        break;

        case DEBUG__BLDC_TARGET:

            mu8_temporary_hundred = (U8)((gu8_bldc_target_hz / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_bldc_target_hz / 10) % 10);
            mu8_temporary_one = (U8)(gu8_bldc_target_hz % 10);


        break;

        case DEBUG__BLDC_OPERATION:

            mu8_temporary_hundred = (U8)((gu8_bldc_opration_hz / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_bldc_opration_hz / 10) % 10);
            mu8_temporary_one = (U8)(gu8_bldc_opration_hz % 10);

        break;

        case DEBUG__BLDC_ERROR:

            mu8_temporary_hundred = (U8)((gu8_bldc_error_code / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_bldc_error_code / 10) % 10);
            mu8_temporary_one = (U8)(gu8_bldc_error_code % 10);

        break;

        case DEBUG__BLDC_TEMP:

            mu8_temporary_hundred = (U8)((gu8_bldc_temperature / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_bldc_temperature / 10) % 10);
            mu8_temporary_one = (U8)(gu8_bldc_temperature % 10);

        break;

        case DEBUG__ICE_STEP:

            mu8_temporary_hundred = DISPLAY_OFF;

            mu8_temporary_ten = (U8)((gu8IceStep / 10) % 10);
            mu8_temporary_one = (U8)(gu8IceStep % 10);

        break;

        case DEBUG__ICE_TRAY_INPUT:

            if( pICE_MICRO_SW_HIGH == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            mu8_temporary_ten = DISPLAY_BAR;

            if( pICE_MICRO_SW_LOW == CLEAR )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;

        case DEBUG__ICE_TRAY_ERROR:

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;

            if( F_ErrTrayMotor_DualInital == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_3;
            }
            else if( F_Ice_Tray_Up_Move_Reset == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else if( F_Ice_Tray_Down_Move_Reset == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_2;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;

        case DEBUG__ICE_WATER_LEVEL:


            if( pLEVEL_PURIFY_LOW == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( pLEVEL_PURIFY_HIGH == SET )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            mu8_temporary_one = DISPLAY_OFF;

        break;

        case DEBUG__ICE_DRAIN_LEVEL:


            if( F_drain_water_level_low == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( F_drain_water_level_high == SET )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            mu8_temporary_one = DISPLAY_OFF;

        break;

        case DEBUG__FEED_NOS_DCFAN:


            if( pVALVE_FEED == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( pVALVE_NOS == SET )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            if( pDC_FAN == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;

        case DEBUG__ROOM_COLD_HOT:

            if( pVALVE_HOT_OUT == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( pVALVE_ROOM_OUT == SET )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            if( pVALVE_COLD_OUT == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }


        break;

        case DEBUG__ROOM_FILTER_REED:

            if( pREED_NEO_1_FILTER == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( pREED_RO_2_FILTER == CLEAR )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            if( pREED_INO_3_FILTER == CLEAR )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }


        break;

        case DEBUG__ROOM_TOP_REED:

            if( pREED_FILTER_COVER == CLEAR )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            mu8_temporary_ten = DISPLAY_BAR;


            if( pREED_TANK_COVER == CLEAR )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }


        break;

        case DEBUG__COMP_ICEHEATER_HOTHEATER:

            if( pCOMP == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            //if( pHEATER_ICE == SET )
            //{
            //    mu8_temporary_ten = DISPLAY_NUM_1;
            //}
            //else
            //{
            //    mu8_temporary_ten = DISPLAY_NUM_0;
            //}

            mu8_temporary_ten = DISPLAY_OFF;

            if( pHEATER_HOT == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;



        case DEBUG__FILTER_CHANGE_TYPE:

            if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
                mu8_temporary_ten = DISPLAY_NUM_1;
                mu8_temporary_one = DISPLAY_NUM_1;
            }

        break;

        case DEBUG__NEO_RESET_DAY:

            #if 0
            mu8_temporary_hundred = (U8)((gu16_reset_hour_neo_filter / 100) % 10);
            mu8_temporary_ten = (U8)((gu16_reset_hour_neo_filter / 10) % 10);
            mu8_temporary_one = (U8)(gu16_reset_hour_neo_filter % 10);
            #endif

            mu16_a = gu16_neo_filter_1_remain_day / 24;

            mu8_temporary_hundred = (U8)((mu16_a / 100) % 10);
            mu8_temporary_ten = (U8)((mu16_a / 10) % 10);
            mu8_temporary_one = (U8)(mu16_a % 10);

        break;

        case DEBUG__RO_RESET_DAY:

            #if 0
            mu8_temporary_hundred = (U8)((gu16_reset_hour_ro_filter / 100) % 10);
            mu8_temporary_ten = (U8)((gu16_reset_hour_ro_filter / 10) % 10);
            mu8_temporary_one = (U8)(gu16_reset_hour_ro_filter % 10);
            #endif

            mu16_a = gu16_ro_filter_2_remain_day / 24;

            mu8_temporary_hundred = (U8)((mu16_a / 100) % 10);
            mu8_temporary_ten = (U8)((mu16_a / 10) % 10);
            mu8_temporary_one = (U8)(mu16_a % 10);

        break;

        case DEBUG__INO_RESET_DAY:

            #if 0
            mu8_temporary_hundred = (U8)((gu16_reset_hour_ino_filter / 100) % 10);
            mu8_temporary_ten = (U8)((gu16_reset_hour_ino_filter / 10) % 10);
            mu8_temporary_one = (U8)(gu16_reset_hour_ino_filter % 10);
            #endif

            mu16_a = gu16_ino_filter_3_remain_day / 24;

            mu8_temporary_hundred = (U8)((mu16_a / 100) % 10);
            mu8_temporary_ten = (U8)((mu16_a / 10) % 10);
            mu8_temporary_one = (U8)(mu16_a % 10);

        break;

        case DEBUG__NEO_WATER_USAGE:

            mu8_temporary_hundred = (U8)((gu16_water_usage_neo_filter / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16_water_usage_neo_filter / 100) % 10);
            mu8_temporary_one = (U8)(gu16_water_usage_neo_filter / 10 % 10);

        break;

        case DEBUG__RO_WATER_USAGE:

            mu8_temporary_hundred = (U8)((gu16_water_usage_ro_filter / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16_water_usage_ro_filter / 100) % 10);
            mu8_temporary_one = (U8)(gu16_water_usage_ro_filter / 10 % 10);

        break;

        case DEBUG__INO_WATER_USAGE:

            mu8_temporary_hundred = (U8)((gu16_water_usage_ino_filter / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16_water_usage_ino_filter / 100) % 10);
            mu8_temporary_one = (U8)(gu16_water_usage_ino_filter / 10 % 10);

        break;

        case DEBUG__STER_LOW_WATER_ERR:

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_L;
            mu8_temporary_ten = (U8)((gu8_ice_ster_low_water_stop_count / 10) % 10);
            mu8_temporary_one = (U8)(gu8_ice_ster_low_water_stop_count % 10);

        break;

        case DEBUG__INO_STER_DRAIN_ERR:

            mu8_temporary_hundred = DISPLAY_NUM_SMALL_d;
            mu8_temporary_ten = (U8)((gu8_ice_ster_drain_stop_count / 10) % 10);
            mu8_temporary_one = (U8)(gu8_ice_ster_drain_stop_count % 10);

        break;


        default:

            gu8_fnd_debug_step = DEBUG__COMP_DELAY;

        break;

    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}






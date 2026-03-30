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

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_debug(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    gu8_debug_timer++;

    if( gu8_debug_timer < 10 )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = (U8)((gu8_fnd_debug_step / 10) % 10);
        mu8_temporary_one = (U8)(gu8_fnd_debug_step % 10);

        fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        return;
    }
    else
    {
        gu8_debug_timer = 10;
    }

    switch( gu8_fnd_debug_step )
    {
        case DEBUG__COMP_DELAY:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

            mu8_temporary_hundred = (U8)((gu16CompOffDelay / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16CompOffDelay / 100) % 10);
            mu8_temporary_one = (U8)((gu16CompOffDelay / 10) % 10);

        break;

        case DEBUG__FLOW_HZ:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

            mu8_temporary_hundred = (U8)((gu8_Flow_1sec / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_Flow_1sec / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Flow_1sec % 10);

        break;

        case DEBUG__COLD_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;

            mu8_temporary_ten = (U8)((gu8_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Cold_Temperature_One_Degree % 10);

        break;

        case DEBUG__ROOM_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_r;

            mu8_temporary_ten = (U8)((gu8_Room_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Room_Temperature_One_Degree % 10);

        break;

        case DEBUG__HOT_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_H;

            mu8_temporary_ten = (U8)((gu8_Hot_Tank_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Hot_Tank_Temperature_One_Degree % 10);

        break;

        case DEBUG__OUT_DOOR_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_o;

            mu8_temporary_ten = (U8)((gu8_Amb_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Amb_Temperature_One_Degree % 10);

        break;

        case DEBUG__EVA_COLD_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;

            mu8_temporary_ten = (U8)((gu8_Eva_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Eva_Cold_Temperature_One_Degree % 10);

        break;

        case DEBUG__EVA_ICE_TEMP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;

            mu8_temporary_ten = (U8)((gu8_Eva_Ice_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Eva_Ice_Temperature_One_Degree % 10);

        break;

        case DEBUG__ICE_FULL_AD:

            if( gu16ADIceFull >= 1000 )
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            }
            else
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            }

            mu8_temporary_hundred = (U8)((gu16ADIceFull / 100) % 10);
            mu8_temporary_ten = (U8)((gu16ADIceFull / 10) % 10);
            mu8_temporary_one = (U8)(gu16ADIceFull % 10);

        break;

        case DEBUG__LEAK_AD:

            if( gu16IceMakingADVal >= 1000 )
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            }
            else
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            }

            mu8_temporary_hundred = (U8)((gu16IceMakingADVal / 100) % 10);
            mu8_temporary_ten = (U8)((gu16IceMakingADVal / 10) % 10);
            mu8_temporary_one = (U8)(gu16IceMakingADVal % 10);

        break;

        case DEBUG__CDS_AD:

            if( gu16ADCds >= 1000 )
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            }
            else
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            }

            mu8_temporary_hundred = (U8)((gu16ADCds / 100) % 10);
            mu8_temporary_ten = (U8)((gu16ADCds / 10) % 10);
            mu8_temporary_one = (U8)(gu16ADCds % 10);

        break;

        case DEBUG__ICE_STEP:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;

            mu8_temporary_ten = (U8)((gu8IceStep / 10) % 10);
            mu8_temporary_one = (U8)(gu8IceStep % 10);

        break;

        case DEBUG__ICE_TRAY_INPUT:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

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

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
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

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

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

            if( pLEVEL_OVERFLOW == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;

        case DEBUG__ICE_DRAIN_LEVEL:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

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

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

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

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

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

        case DEBUG__COMP_ICEHEATER_HOTHEATER:

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

            if( pCOMP == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            if( pHEATER_ICE == SET )
            {
                mu8_temporary_ten = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_ten = DISPLAY_NUM_0;
            }

            if( pHEATER_HOT == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;

        default:

            gu8_fnd_debug_step = DEBUG__COMP_DELAY;

        break;

    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}






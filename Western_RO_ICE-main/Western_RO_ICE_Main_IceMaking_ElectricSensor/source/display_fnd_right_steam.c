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
#include    "display_fnd_right_steam.h"


void fnd_right_steam_clean_state(void);

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_steam_clean_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_steam_clean_step = 0;

    if( bit_ice_ster_test_debug_start == SET )
    {
        if( gu8_ice_ster_test_debug_step == 0 )
        {
            if( F_drain_water_level_low == SET )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_NUM_0;
            }

            mu8_temporary_ten = DISPLAY_BAR;

            if( F_drain_water_level_high == SET )
            {
                mu8_temporary_one = DISPLAY_NUM_1;
            }
            else
            {
                mu8_temporary_one = DISPLAY_NUM_0;
            }
        }
        else if( gu8_ice_ster_test_debug_step == 1 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
            mu8_temporary_ten = (U8)((gu8_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Cold_Temperature_One_Degree % 10);
        }
        else if( gu8_ice_ster_test_debug_step == 2 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_H;
            mu8_temporary_ten = (U8)((gu8_Hot_Tank_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Hot_Tank_Temperature_One_Degree % 10);
        }
        else if( gu8_ice_ster_test_debug_step == 3 )
        {
            if( gu8_ice_ster_mode == STER_MODE_NONE_STATE)
            {
                mu8_steam_clean_step = 0;
            }
            else if( gu8_ice_ster_mode == STER_MODE_PREPARE)
            {
                mu8_steam_clean_step = 1;
            }
            else if( gu8_ice_ster_mode == STER_MODE_CIRCULATION_HOT_STATE)
            {
                mu8_steam_clean_step = 2;
            }
            else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE)
            {
                mu8_steam_clean_step = 3;
            }
            else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE)
            {
                mu8_steam_clean_step = 4;
            }
            else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE)
            {
                mu8_steam_clean_step = 5;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE)
            {
                mu8_steam_clean_step = 6;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN)
            {
                mu8_steam_clean_step = 7;
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE)
            {
                if( gu8_melt_ice_count == 0 )
                {
                    mu8_steam_clean_step = 8;
                }
                else /*if( gu8_melt_ice_count == 1 )*/
                {
                    mu8_steam_clean_step = 10;
                }
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE)
            {
                if( gu8_melt_ice_count == 0 )
                {
                    mu8_steam_clean_step = 9;
                }
                else /*if( gu8_melt_ice_count == 1 )*/
                {
                    mu8_steam_clean_step = 11;
                }
            }
            else if( gu8_ice_ster_mode == STER_MODE_FINISH)
            {
                mu8_steam_clean_step = 12;
            }
            else{}

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_L;
            mu8_temporary_ten = (U8)((mu8_steam_clean_step / 10) % 10);
            mu8_temporary_one = (U8)(mu8_steam_clean_step % 10);
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_NUM_5;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_t;
            mu8_temporary_one = gu8_ice_ster_drain_stop_count;
        }
    }
    else
    {
        /*..hui [23-6-15오후 12:58:42] 시간이 가변적이라 표시할수없음.. 용량바로 표시하기로 - 디자인..*/
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}











/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





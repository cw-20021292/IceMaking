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
#include    "display_fnd_left_steam.h"

void fnd_left_steam_clean_state(void);

U8 gu8_steam_clean_percent;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_steam_clean_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;

    if( gu8_ice_ster_mode == STER_MODE_PREPARE )
    {
        gu8_steam_clean_percent = 0;
    }
    else if( gu8_ice_ster_mode == STER_MODE_CIRCULATION_HOT_STATE )
    {
        gu8_steam_clean_percent = 10;
    }
    else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
    {
        gu8_steam_clean_percent = 10;
    }
    else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
    {
        gu8_steam_clean_percent = 20;
    }
    else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
    {
        gu8_steam_clean_percent = 20;
    }
    else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
    {
        gu8_steam_clean_percent = 30;
    }
    else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
    {
        gu8_steam_clean_percent = 40;
    }
    else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
    {
        if( gu8_melt_ice_count == 0 )
        {
            gu8_steam_clean_percent = 50;
        }
        else /*if( gu8_melt_ice_count == 1 )*/
        {
            gu8_steam_clean_percent = 70;
        }
    }
    else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
    {
        if( gu8_melt_ice_count == 0 )
        {
            gu8_steam_clean_percent = 60;
        }
        else /*if( gu8_melt_ice_count == 1 )*/
        {
            gu8_steam_clean_percent = 80;
        }
    }
    else if( gu8_ice_ster_mode == STER_MODE_FINISH )
    {
        if( gu8_wait_finish_step <= 2 )
        {
            gu8_steam_clean_percent = 90;
        }
        else
        {
            gu8_steam_clean_percent = 100;
        }
    }
    else
    {
        gu8_steam_clean_percent = 100;
    }

    if( gu8_steam_clean_percent < 100 )
    {
        if( gu8_steam_clean_percent == 0 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (gu8_steam_clean_percent / 10);
            mu8_temporary_one = (gu8_steam_clean_percent % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_NUM_1;
        mu8_temporary_ten = DISPLAY_NUM_0;
        mu8_temporary_one = DISPLAY_NUM_0;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





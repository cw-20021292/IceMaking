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
#include    "valve_hot_in.h"

void output_valve_hot_in(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8HotInFeedONB;
#define            u8HotInValveON                           U8HotInFeedONB.byte
#define            Bit0_Hot_In_Hot_Ster_State               U8HotInFeedONB.Bit.b0
#define            Bit1_Hot_In_Flushing_Air_Remove_State    U8HotInFeedONB.Bit.b1




TYPE_BYTE          U8HotInFeedOFFB;
#define            u8HotInValveOFF                          U8HotInFeedOFFB.byte
#define            Bit0_Hot_In_Off_State                    U8HotInFeedOFFB.Bit.b0



/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_hot_in(void)
{

    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_CIRCULATION_HOT_STATE )
        {
            if( gu8_hot_circulation_step >= 2 )
            {
                Bit0_Hot_In_Hot_Ster_State = SET;
            }
            else
            {
                Bit0_Hot_In_Hot_Ster_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            /*..hui [23-8-11오후 4:37:54] 온수 온도 맞춤 단계에서 ON 상태로 진입..*/
            Bit0_Hot_In_Hot_Ster_State = SET;
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            Bit0_Hot_In_Hot_Ster_State = SET;
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            /*if( gu8_final_clean_step <= 7 )*/
            /*if( gu8_final_clean_step <= 10 )*/
            if( gu8_final_clean_step <= 14 )
            {
                Bit0_Hot_In_Hot_Ster_State = SET;
            }
            else
            {
                Bit0_Hot_In_Hot_Ster_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step >= 1 && gu8_ice_tray_clean_step <= 12 )
            {
                Bit0_Hot_In_Hot_Ster_State = SET;
            }
            else
            {
                Bit0_Hot_In_Hot_Ster_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            /*if( gu8_melt_ice_step >= 1 && gu8_melt_ice_step <= 22 )*/
            if( gu8_melt_ice_step >= 1 && gu8_melt_ice_step <= 23 )
            {
                Bit0_Hot_In_Hot_Ster_State = SET;
            }
            else
            {
                Bit0_Hot_In_Hot_Ster_State = CLEAR;
            }
        }
        else
        {
            Bit0_Hot_In_Hot_Ster_State = CLEAR;
        }

    }
    else
    {
        Bit0_Hot_In_Hot_Ster_State = CLEAR;
    }

    #if 0
    /*..hui [24-1-4오후 2:04:50] 탱크 플러싱할때.. 만수위 채우고 온수탱크 에어빼기..*/
    /*..hui [24-1-4오후 2:05:02] 10초가량 오버히팅쪽으로 순환시켜줌..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        if( gu8_flushing_tank_step >= 4 && gu8_flushing_tank_step <= 6 )
        {
            Bit1_Hot_In_Flushing_Air_Remove_State = bit_flushing_tank_start;
        }
        else
        {
            Bit1_Hot_In_Flushing_Air_Remove_State = CLEAR;
        }
    }
    else
    {
        Bit1_Hot_In_Flushing_Air_Remove_State = CLEAR;
    }
    #endif

    Bit1_Hot_In_Flushing_Air_Remove_State = CLEAR;

/***********************************************************************************************/





/***********************************************************************************************/
    if (u8HotInValveOFF > 0)
    {
        pVALVE_HOT_IN_FEED = CLEAR;      /*off*/
    }
    else
    {
        if (u8HotInValveON > 0)
        {
            pVALVE_HOT_IN_FEED = SET;    /*on*/
        }
        else
        {
            pVALVE_HOT_IN_FEED = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





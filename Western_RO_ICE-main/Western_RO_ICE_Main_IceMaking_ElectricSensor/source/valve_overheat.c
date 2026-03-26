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
#include    "valve_overheat.h"

void output_valve_overheat_nos(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8NOSOverheatValveONB;
#define            u8NOSOverheatValveON                      U8NOSOverheatValveONB.byte
#define            Bit0_Overheat_NOS_Hot_Ster_On_State       U8NOSOverheatValveONB.Bit.b0




TYPE_BYTE          U8NOSOverheatValveOFFB;
#define            u8NOSOverheatValveOFF                     U8NOSOverheatValveOFFB.byte
#define            Bit0_Overheat_NOS_Off_State               U8NOSOverheatValveOFFB.Bit.b0



/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_overheat_nos(void)
{


    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            if( gu8_hot_spray_step >= 2 )
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            if( gu8_lukewarm_spray_step == 0 || gu8_lukewarm_spray_step >= 4 )
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            if( gu8_final_clean_step == 0 || gu8_final_clean_step >= 4 )
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step >= 5 && gu8_ice_tray_clean_step <= 11 )
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            if( gu8_melt_ice_step >= 5 && gu8_melt_ice_step <= 22 )
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
            }
        }
        else
        {
            Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Overheat_NOS_Hot_Ster_On_State = CLEAR;
    }



/***********************************************************************************************/





/***********************************************************************************************/
    if (u8NOSOverheatValveOFF > 0)
    {
        pVALVE_OVERHEATING_NOS = CLEAR;      /*off*/
    }
    else
    {
        if (u8NOSOverheatValveON > 0)
        {
            pVALVE_OVERHEATING_NOS = SET;    /*on*/
        }
        else
        {
            pVALVE_OVERHEATING_NOS = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





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
#include    "valve_nos.h"

void output_valve_nos(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8NOSValveONB;
#define            u8NOSValveON                         U8NOSValveONB.byte
#define            Bit0_Water_Error_NOS_On_State          U8NOSValveONB.Bit.b0
#define            Bit1_Water_OverFlow_NOS_On_State          U8NOSValveONB.Bit.b1




TYPE_BYTE          U8NOSValveOFFB;
#define            u8NOSValveOFF                       U8NOSValveOFFB.byte
#define            Bit0_Not_Use_State                U8NOSValveOFFB.Bit.b0


bit bit_nos_output;
/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_nos(void)
{
    /***********************************************************************************************/

    if( Bit3_Leakage_Sensor_Error == SET
        || Bit7_Room_High_Water_Level_Error == SET
        || Bit8_Feed_Valve_Error  == SET
        || Bit9_Room_Level_Unbalance_Error == SET)
    {
        Bit0_Water_Error_NOS_On_State = SET;
    }
    else
    {
        Bit0_Water_Error_NOS_On_State = CLEAR;
    }

    Bit1_Water_OverFlow_NOS_On_State = F_Err_OVF_Check;

/***********************************************************************************************/
    if (u8NOSValveOFF > 0)
    {
        pVALVE_NOS = CLEAR;      /*off*/
        bit_nos_output = CLEAR;
    }
    else
    {
        if (u8NOSValveON > 0)
        {
            pVALVE_NOS = SET;    /*on*/
            bit_nos_output = SET;
        }
        else
        {
            pVALVE_NOS = CLEAR;  /*off*/
            bit_nos_output = CLEAR;
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





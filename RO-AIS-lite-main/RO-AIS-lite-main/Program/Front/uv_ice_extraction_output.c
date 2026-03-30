/***********************************************************************************************************************
* Version      : RO AIS LITE
* File Name    : uv_ice_extraction_output.c
* Device(s)    : R5F100PH
* Creation Date: 2024-11-20
* Copyright    : Coway_Software Team (sean)
* Description  :
***********************************************************************************************************************/

#include    "Port_Define.h"
#include    "Macrodriver.h"

bit bit_uv_ice_extraction_out;

void output_ice_extraction_uv(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_extraction_uv(void)
{

/***********************************************************************************************/
    if( bit_uv_ice_extraction_out == SET )
    {
        pLED_UV_ICE_FAUCET = SET;                  /*off*/
        pUV_ON_OFF = SET;
    }
    else
    {
        if( bit_uv_ice_extraction_out == CLEAR )
        {
            pLED_UV_ICE_FAUCET = CLEAR;                 /*on*/
            pUV_ON_OFF = CLEAR;
        }
        else
        {
            pLED_UV_ICE_FAUCET = CLEAR;              /*off*/
            pUV_ON_OFF = CLEAR;
        }
    }
}



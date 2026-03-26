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
#include    "display_fnd_left_sleep.h"

void fnd_left_sleep(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_sleep(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





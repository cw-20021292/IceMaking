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
#include    "display_fnd_right_altitude.h"


void fnd_right_altitude_setting(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_altitude_setting(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    #if 0
    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        mu8_temporary_one = DISPLAY_NUM_1;
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        mu8_temporary_one = DISPLAY_NUM_2;
    }
    else /*if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )*/
    {
        mu8_temporary_one = DISPLAY_NUM_3;
    }
    #endif

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





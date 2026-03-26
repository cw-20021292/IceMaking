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
#include    "display_fnd_left_self_test.h"

void fnd_left_self_test_state(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_self_test_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;


    if( gu8_wifi_self_test_progress < 100 )
    {
        if( gu8_wifi_self_test_progress == 0 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (gu8_wifi_self_test_progress / 10);
            mu8_temporary_one = (gu8_wifi_self_test_progress % 10);
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





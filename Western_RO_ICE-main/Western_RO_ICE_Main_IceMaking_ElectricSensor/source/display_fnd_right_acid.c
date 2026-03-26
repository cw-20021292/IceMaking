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
#include    "display_fnd_right_acid.h"


void fnd_right_acid(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_acid(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //mu8_temporary_hundred = DISPLAY_OFF;
    //mu8_temporary_ten = DISPLAY_OFF;
    //mu8_temporary_one = DISPLAY_OFF;

    if( gu8_acid_clean_mode >= ACID_CLEAN_PREPARE )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )
        {
            if( gu8_acid_finish_step <= 1 )
            {
                if( gu8_acid_display_step < 10 )
                {
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = gu8_acid_display_step;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = gu8_acid_display_step / 10;
                    mu8_temporary_one = gu8_acid_display_step % 10;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }
        }
        else
        {
            if( gu8_acid_display_step < 10 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = gu8_acid_display_step;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = gu8_acid_display_step / 10;
                mu8_temporary_one = gu8_acid_display_step % 10;
            }
        }
    }
    else
    {
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





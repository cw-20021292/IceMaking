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
#include    "display_fnd_left_sound.h"

void fnd_left_sound_setting(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_sound_setting(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = DISPLAY_BAR;

    /*..hui [23-11-23오후 5:57:21] 음성 3, 효과음 2, 무음 1..*/
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        mu8_temporary_ten = DISPLAY_NUM_3;
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        mu8_temporary_ten = DISPLAY_NUM_2;
    }
    else if( gu8Sound_Type == SOUND_TYPE_MUTE )
    {
        mu8_temporary_ten = DISPLAY_NUM_1;
    }

    mu8_temporary_one = DISPLAY_BAR;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}










/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





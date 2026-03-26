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
#include    "my_cup.h"

//void setting_my_cup(void);

//bit bit_my_cup_setting_start;
//U16 gu16_my_cup_setting_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void setting_my_cup(void)
{
    if( bit_my_cup_setting_start == CLEAR )
    {
        gu16_my_cup_setting_timer = 0;
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        gu16_my_cup_setting_timer++;

        if(gu16_my_cup_setting_timer >= u16Efluent_Time)
        {
            gu16_my_cup_setting_timer = u16Efluent_Time;
        }
        else{}
    }
    else
    {
        #if 0
        if( gu16_my_cup_setting_timer >= MY_CUP_SETTING_130mL_MIN )
        {
            bit_my_cup_setting_start = CLEAR;
            gu16_my_cup_level = gu16_my_cup_setting_timer;
            bit_my_cup_enable = SET;
        }
        else{}
        #endif
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




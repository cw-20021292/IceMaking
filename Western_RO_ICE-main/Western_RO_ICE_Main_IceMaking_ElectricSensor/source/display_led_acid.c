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
#include    "display_led_acid.h"


void led_acid(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_acid(void)
{
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
    set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
    Bit3_Front_Under_Led_Ice_Extract = CLEAR;
    /*Bit4_Front_Under_Led_Water_Extract = CLEAR;*/
    Bit4_Front_Under_Led_Water_Extract = SET;

    wifi_icon_output();

    if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE
        || gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR
        || gu8_acid_clean_mode == ACID_CLEAN_RINSE
        || gu8_acid_clean_mode == ACID_CLEAN_FINISH )
    {
        Bit5_Front_Left_Led_Percent_Icon = SET;
    }
    else
    {
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;
    }


    if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
    {
        if( gu8_acid_change_filter_step == 2 )
        {
            #if 0
            Bit4_Front_New_Led_Replace_Filter_Text = SET;
            Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
            #endif

            Bit4_Front_New_Led_Replace_Filter_Text = F_Wink_500ms;
            Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
            Bit6_Front_New_Led_Replace_Filter_2_Num = F_Wink_500ms;
            Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
        }
        else if( gu8_acid_change_filter_step == 4 )
        {
            #if 0
            Bit4_Front_New_Led_Replace_Filter_Text = SET;
            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
            #endif

            Bit4_Front_New_Led_Replace_Filter_Text = F_Wink_500ms;
            Bit5_Front_New_Led_Replace_Filter_1_Num = F_Wink_500ms;
            Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
            Bit7_Front_New_Led_Replace_Filter_3_Num = F_Wink_500ms;
        }
        else
        {
            Bit4_Front_New_Led_Replace_Filter_Text = CLEAR;
            Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
            Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
            Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
        }
    }
    else
    {
        Bit4_Front_New_Led_Replace_Filter_Text = CLEAR;
        Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
        Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
    }



}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/











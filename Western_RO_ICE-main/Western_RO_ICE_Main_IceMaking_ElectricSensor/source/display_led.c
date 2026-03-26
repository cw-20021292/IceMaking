/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "display_led.h"



void led_normal_state(void);
void funcition_led_output(void);
void temp_led_out(void);
void hot_temp_led_out(void);
void cold_temp_led_out(void);
void level_led_out(void);
void cup_level_led_out(void);
//void cup_level_steam_clean_out(void);
//void cup_level_continue_out(void);
void cup_level_extract_out(void);
void cup_level_ice_out(void);
void cup_level_normal_out(void);
void hot_level_led_out(void);
void setting_led_out(void);
void extract_led_out(void);
void make_rgb_color( U8 mu8_color );

void steam_clean_led_out(void);
void uv_led_out(void);





TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6


U16 gu16_my_cup_level;
bit bit_my_cup_enable;


U8 gu8_cup_total_number;
U8 gu8_cup_current_number;


U8 gu8_steam_clean_level_timer;
bit bit_steam_clean_level_flick;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_normal_state(void)
{
    funcition_led_output();
    /*temp_led_out();*/
    level_led_out();
    setting_led_out();
    extract_led_out();
    uv_led_out();
    steam_clean_led_out();

    icon_led_out();
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void funcition_led_output(void)
{
    U8 mu8_flick_state = 0;
    U8 mu8_cold_flick_state = 0;
    U8 mu8_hot_flick_state = 0;

    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        /*..hui [23-11-17오후 12:10:09] 다시 흐리게.. 디자인..*/
        set_duty_percent( DIMMING__PERCENT_SETTING_SELECT, DIIMMING__20_PERCENT );
        set_duty_percent( DIMMING__PERCENT_ICE_SELECT, DIIMMING__20_PERCENT );

        set_duty_percent( DIMMING__PERCENT_HOT_SELECT, DIIMMING__20_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, DIIMMING__20_PERCENT );

        set_duty_percent( DIMMING__PERCENT_COLD_SELECT, DIIMMING__20_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, DIIMMING__20_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_SETTING_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
        set_duty_percent( DIMMING__PERCENT_ICE_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );

        set_duty_percent( DIMMING__PERCENT_HOT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );

        set_duty_percent( DIMMING__PERCENT_COLD_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
    }


    if( Bit0_Ice_Lock_Indicator == SET )
    {
        mu8_flick_state = indicator_flick_timer(5, 5);

        if( mu8_flick_state == SET )
        {
            Bit0_Front_Led_Set_Select = SET;
        }
        else
        {
            Bit0_Front_Led_Set_Select = CLEAR;
        }
    }
    else if( Bit1_Hot_Lock_Indicator == SET )
    {
        mu8_flick_state = indicator_flick_timer(5, 5);

        if( mu8_flick_state == SET )
        {
            Bit0_Front_Led_Set_Select = SET;
        }
        else
        {
            Bit0_Front_Led_Set_Select = CLEAR;
        }
    }
    else
    {
        Bit0_Front_Led_Set_Select = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-4-3오후 4:23:49] 얼음 OFF됐을때 얼음 버튼 누르면 점멸..*/
    if( F_IceOn == SET )
    {
        Bit1_Front_Led_Ice_Select = SET;
    }
    else
    {
        /*Bit1_Front_Led_Ice_Select = CLEAR;*/
        if( Bit6_Ice_Off_Indicator == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
        }
        else
        {
            mu8_hot_flick_state = ice_off_flickering_timer(5, 5);

            if( mu8_hot_flick_state == SET )
            {
                Bit1_Front_Led_Ice_Select = SET;

            }
            else
            {
                Bit1_Front_Led_Ice_Select = CLEAR;
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Hot_Enable == SET )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            Bit2_Front_Led_Hot_Select = SET;
        }
        else
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
    }
    else
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( Bit3_Hot_Off_Indicator == CLEAR )
            {
                Bit2_Front_Led_Hot_Select = SET;
            }
            else
            {
                /*mu8_hot_flick_state = hot_off_flickering_timer(5, 5);*/
                mu8_hot_flick_state = hot_off_flickering_timer(5, 5);

                if( mu8_hot_flick_state == SET )
                {
                    Bit2_Front_Led_Hot_Select = SET;

                }
                else
                {
                    Bit2_Front_Led_Hot_Select = CLEAR;
                }
            }
        }
        else
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        Bit3_Front_Led_Ambient_Select = SET;
    }
    else
    {
        //Bit3_Front_Led_Ambient_Select = CLEAR;
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Cold_Enable == SET )
    {
        if( u8WaterOutState == COLD_WATER_SELECT )
        {
            Bit4_Front_Led_Cold_Select = SET;
        }
        else
        {
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
    }
    else
    {
        if( u8WaterOutState == COLD_WATER_SELECT )
        {
            if( Bit2_Cold_Off_Indicator == CLEAR )
            {
                Bit4_Front_Led_Cold_Select = SET;
            }
            else
            {
                /*mu8_cold_flick_state = cold_off_flickering_timer(5, 5);*/
                mu8_cold_flick_state = cold_off_flickering_timer(3, 5);

                if( mu8_cold_flick_state == SET )
                {
                    Bit4_Front_Led_Cold_Select = SET;
                }
                else
                {
                    Bit4_Front_Led_Cold_Select = CLEAR;
                }
            }
        }
        else
        {
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( gu8_cup_led_select == SET )
    {
        /*..hui [20-1-7오전 10:01:44] 물 추출하면 즉시 OFF..*/
        if( F_WaterOut == SET )
        {
            gu8_cup_led_select = CLEAR;
        }
        else{}

        gu8_cup_led_off_time++;

        /*..hui [20-1-7오전 10:01:54] 선택하고 7초 후 OFF..*/
        if( gu8_cup_led_off_time < CUP_SELECT_LED_OFF_TIME )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            gu8_cup_led_select = CLEAR;
        }
    }
    else
    {
        //Bit5_Front_Led_Amount_Select = CLEAR;
        Bit5_Front_Led_Amount_Select = CLEAR;
        gu8_cup_led_off_time = 0;
    }
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void temp_led_out(void)
{
    /*hot_temp_led_out();*/
    /*cold_temp_led_out();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_temp_led_out(void)
{
    #if 0
    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_NEW_ICE_MAKING_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_HOT_HEATING_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_COLD_COOLING_TEXT, DIIMMING__100_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_NEW_ICE_MAKING_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_HOT_HEATING_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_COLD_COOLING_TEXT, DIIMMING__100_PERCENT );
    }



    if( F_Hot_Enable == SET )
    {
        switch( gu8HotTemp )
        {
            case TEMP_DISPLAY_0_INIT:
            case TEMP_DISPLAY_1_LOW:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = CLEAR;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_2_MID:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = SET;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_3_HIGH:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = SET;
                Bit2_Front_Led_Hot_Temp_3 = SET;
                break;

            default:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = CLEAR;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;
        }
    }
    else
    {
        Bit0_Front_Led_Hot_Temp_1 = CLEAR;
        Bit1_Front_Led_Hot_Temp_2 = CLEAR;
        Bit2_Front_Led_Hot_Temp_3 = CLEAR;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp_led_out(void)
{
    #if 0
    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_NEW_LOW_WATER_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_COLD_TEMP_3, DIIMMING__100_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_NEW_LOW_WATER_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_TEXT, DIIMMING__100_PERCENT );
        set_duty_percent( DIMMING__PERCENT_COLD_TEMP_3, DIIMMING__100_PERCENT );
    }

    if( F_Cold_Enable == SET )
    {
        switch( gu8ColdTemp )
        {
            case TEMP_DISPLAY_0_INIT:
            case TEMP_DISPLAY_1_LOW:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = CLEAR;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_2_MID:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = SET;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_3_HIGH:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = SET;
                Bit5_Front_Led_Cold_Temp_3 = SET;
                break;

            default:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = CLEAR;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;
        }
    }
    else
    {
        Bit3_Front_Led_Cold_Temp_1 = CLEAR;
        Bit4_Front_Led_Cold_Temp_2 = CLEAR;
        Bit5_Front_Led_Cold_Temp_3 = CLEAR;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void level_led_out(void)
{
    cup_level_led_out();
    hot_level_led_out();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_led_out(void)
{
    /*..hui [24-1-8오후 5:49:52] 온수세척은 표시 안하는걸로..*/
    if( F_WaterOut == SET && u8Extract_Continue == SET )
    {
        ////////cup_level_continue_out();
        /*..hui [24-2-26오후 1:24:30] 다 켜지지않고 이전 상태 유지하도록....*/
        cup_level_normal_out();
    }
    else if( F_WaterOut == SET && u8Extract_Continue == CLEAR )
    {
        cup_level_extract_out();
    }
    else if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        cup_level_ice_out();
    }
    else
    {
        cup_level_normal_out();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void cup_level_steam_clean_out(void)
{
    gu8_steam_clean_level_timer++;

    if( gu8_steam_clean_level_timer >= 5 )
    {
        gu8_steam_clean_level_timer = 0;
        bit_steam_clean_level_flick ^= SET;
    }
    else{}

    if( gu8_steam_clean_percent <= 20 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = bit_steam_clean_level_flick;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else if( gu8_steam_clean_percent <= 40 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = bit_steam_clean_level_flick;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else if( gu8_steam_clean_percent <= 60 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = bit_steam_clean_level_flick;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else if( gu8_steam_clean_percent <= 80 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = bit_steam_clean_level_flick;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else /*if( gu8_steam_clean_percent <= 100 )*/
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = bit_steam_clean_level_flick;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void cup_level_continue_out(void)
{

    #if 0
    /*..hui [23-5-17오후 3:30:22] 연속 표시할때는 물량표시 끄니까 duty는 이전상태 유지..*/
    Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
    Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
    Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
    Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
    Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    #endif


    /*..hui [23-12-19오후 4:43:41] 연속추출할때 아래4개 흐리게, 연속아이콘 ON으로 변경됨..*/
    Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
    Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
    Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
    Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
    Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_extract_out(void)
{
    U16 mu16_out_time = 0;

    mu16_out_time = u16Efluent_Time - 4;

    gu16_extract_display_timer = (U16)( (mu16_out_time) / EXTRACT_TOTAL_STEP );

    if( 0 >= gu16Water_Extract_Timer % gu16_extract_display_timer )
    {
        gu8_extract_display_cnt++;

        if(gu8_extract_display_cnt >= EXTRACT_TOTAL_STEP)
        {
            gu8_extract_display_cnt = EXTRACT_TOTAL_STEP;
        }
        else{}
    }
    else{}

    if( gu8_extract_display_cnt == 0 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
    else if( gu8_extract_display_cnt == 1 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
    else if( gu8_extract_display_cnt == 2 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
    else if( gu8_extract_display_cnt == 3 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
    else if( gu8_extract_display_cnt == 4 )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, TOP_ICON__DIMMING__50_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
    else
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_ice_out(void)
{
    U16 mu16_out_time = 0;

    /*..hui [23-8-2오전 10:54:32] 얼음추출할때는 전부끈다..*/
    Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
    Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
    Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
    Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
    Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_normal_out(void)
{
    U8 mu8_i = 0;
    U8 mu8_pass_cup = 0;
    U8 mu8_total_cup = 0;
    U8 mu8_cup_current_number = 0;
    U8 mu8_cup_total_number = 0;


    gu8_cup_current_number = 0;
    gu8_cup_total_number = 0;

    #if 0
    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( Bit8_32_Oz_Select__945_ml == SET )
        {
            mu8_pass_cup = SET;
        }
        else{}
    }
    else{}
    #endif

    if( Bit0_4_Oz_Select__120_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit1_6_Oz_Select__175_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit2_8_Oz_Select__235_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit3_10_Oz_Select__295_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit4_12_Oz_Select__355_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit5_14_Oz_Select__415_ml == SET )
    {
         gu8_cup_total_number++;

         if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
         {
             gu8_cup_current_number = gu8_cup_total_number;
         }
         else{}
    }
    else{}

    if( Bit6_16_Oz_Select__475_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( Bit7_20_Oz_Select__590_ml == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    #if 0
    if( mu8_pass_cup == CLEAR )
    {
        if( Bit8_32_Oz_Select__945_ml == SET )
        {
            gu8_cup_total_number++;

            if( gu8Cup_level == CUP_LEVEL__32_OZ__945_ML )
            {
                gu8_cup_current_number = gu8_cup_total_number;
            }
            else{}
        }
        else{}
    }
    else{}
    #endif

    if( Bit9_Continue_Select__Continue == SET )
    {
        gu8_cup_total_number++;

        if( gu8Cup_level == CUP_LEVEL__CONTINUE )
        {
            gu8_cup_current_number = gu8_cup_total_number;
        }
        else{}
    }
    else{}

    if( gu8_cup_total_number == 5 )
    {
        if( gu8_cup_current_number == 1 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else if( gu8_cup_current_number == 2 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else if( gu8_cup_current_number == 3 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else if( gu8_cup_current_number == 4 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, TOP_ICON__DIMMING__50_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else /*if( gu8_cup_current_number == 5 )*/
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
        }
    }
    else if( gu8_cup_total_number == 4 )
    {
        if( gu8_cup_current_number == 1 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else if( gu8_cup_current_number == 2 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );

        }
        else if( gu8_cup_current_number == 3 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );

        }
        else /*if( gu8_cup_current_number == 4 )*/
        {
             Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
             set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

             Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
             set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

             Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
             set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

             Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
             set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

             Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
             set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
        }
    }
    else if( gu8_cup_total_number == 3 )
    {
        if( gu8_cup_current_number == 1 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else if( gu8_cup_current_number == 2 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );

        }
        else /*if( gu8_cup_current_number == 3 )*/
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );
        }
    }
    else /*if( gu8_cup_total_number == 2 )*/
    {
        if( gu8_cup_current_number == 1 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
        }
        else /*if( gu8_cup_current_number == 2 )*/
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );

            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );


        }
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_level_led_out(void)
{

    /*..hui [23-8-18오전 11:28:50] 얼음 추출중에는 끈다..*/
    if( F_Ice == SET && gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
    }
    else if( u8WaterOutState == PURE_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
    }
    else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, TOP_ICON__DIMMING__50_PERCENT );

        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, TOP_ICON__DIMMING__50_PERCENT );

            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );

        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );

            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, TOP_ICON__DIMMING__50_PERCENT );

            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, TOP_ICON__DIMMING__50_PERCENT );

            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );

            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );

            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_led_out(void)
{
    U8 mu8_flick_state = 0;

    if( bit_setting_mode_start == SET )
    {
        Bit0_Front_Led_Ice_First = SET;
        Bit1_Front_Led_Ice_Lock = SET;
        Bit2_Front_Led_Hot_Lock = SET;
        Bit3_Front_Led_Touch_Lock = SET;
        Bit4_Front_Led_Eco_Mode = SET;
        //Bit5_Front_Led_Eco_Mode = SET;
    }
    else
    {
        if( Bit0_Ice_Lock_Indicator == SET )
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = Bit0_Front_Led_Set_Select;
            Bit2_Front_Led_Hot_Lock = CLEAR;
            Bit3_Front_Led_Touch_Lock = CLEAR;
            Bit4_Front_Led_Eco_Mode = CLEAR;
            //Bit5_Front_Led_Eco_Mode = CLEAR;
        }
        else if( Bit1_Hot_Lock_Indicator == SET )
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = CLEAR;
            Bit2_Front_Led_Hot_Lock = Bit0_Front_Led_Set_Select;
            Bit3_Front_Led_Touch_Lock = CLEAR;
            Bit4_Front_Led_Eco_Mode = CLEAR;
            //Bit5_Front_Led_Eco_Mode = CLEAR;
        }
        else
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = CLEAR;
            Bit2_Front_Led_Hot_Lock = CLEAR;
            Bit3_Front_Led_Touch_Lock = CLEAR;
            Bit4_Front_Led_Eco_Mode = CLEAR;
            //Bit5_Front_Led_Eco_Mode = CLEAR;
        }
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void extract_led_out(void)
{
    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        /*set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__20_PERCENT );*/
        /*set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__20_PERCENT );*/
        set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__10_PERCENT );
        set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__10_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
        set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
    }

    /*..hui [23-6-2오후 12:23:06] 플러싱 대기중 점등..*/
    if( gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode == FLUSHING_STANDBY_STATE )
    {
        Bit3_Front_Under_Led_Ice_Extract = CLEAR;
        Bit4_Front_Under_Led_Water_Extract = SET;

        make_rgb_color( RGB_OFF );
    }
    else if( gu8_Led_Display_Step == LED_Display__FLUSHING
        && gu8_flushing_mode > FLUSHING_STANDBY_STATE )
    {
        /*..hui [23-6-2오후 12:23:12] 플러싱 진행중 점등..*/
        Bit3_Front_Under_Led_Ice_Extract = CLEAR;
        Bit4_Front_Under_Led_Water_Extract = SET;

        make_rgb_color( RGB_OFF );
    }
    else if( gu8_Led_Display_Step == LED_Display__FILTER_COVER_OPEN
        && bit_filter_all == CLEAR )
    {
        /*..hui [23-6-8오후 12:12:45] 필터 커버 열림시 물 추출만 점등..*/
        Bit3_Front_Under_Led_Ice_Extract = CLEAR;
        Bit4_Front_Under_Led_Water_Extract = SET;

        make_rgb_color( RGB_OFF );
    }
    else if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-12-15오후 2:23:02] 온수세척시..*/
        /*..hui [23-12-15오후 2:23:12] 물추출 하얀색만 점등으로..*/
        Bit3_Front_Under_Led_Ice_Extract = SET;
        Bit4_Front_Under_Led_Water_Extract = SET;

        make_rgb_color( RGB_OFF );
    }
    else if( bit_manual_drain_start == SET )
    {
        if( F_Extract_Led_OnOff == SET )
        {
            Bit3_Front_Under_Led_Ice_Extract = SET;
            Bit4_Front_Under_Led_Water_Extract ^= SET;
        }
        else
        {
            Bit3_Front_Under_Led_Ice_Extract = CLEAR;
            Bit4_Front_Under_Led_Water_Extract ^= SET;
        }

        make_rgb_color( RGB_OFF );
    }
    else if( gu8_durable_test_start == SET )
    {
        if( gu16_durable_test_step == 10 || gu8_Error_Code != 0 )
        {
            Bit3_Front_Under_Led_Ice_Extract ^= SET;
        }
        else
        {
            Bit3_Front_Under_Led_Ice_Extract = F_Wink_500ms;
        }

        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_rgb_color( RGB_COLOR_HOT );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else if( u8WaterOutState == COLD_WATER_SELECT )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_rgb_color( RGB_COLOR_COLD );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else /*if( u8WaterOutState == PURE_WATER_SELECT )*/
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_rgb_color( RGB_OFF );
            /*set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );*/
        }
    }
    else
    {
        if( F_Extract_Led_OnOff == SET )
        {
            Bit3_Front_Under_Led_Ice_Extract = SET;

            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                Bit4_Front_Under_Led_Water_Extract = SET;
                make_rgb_color( RGB_COLOR_HOT );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                Bit4_Front_Under_Led_Water_Extract = SET;
                make_rgb_color( RGB_COLOR_COLD );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else /*if( u8WaterOutState == PURE_WATER_SELECT )*/
            {
                Bit4_Front_Under_Led_Water_Extract = SET;
                make_rgb_color( RGB_OFF );
                /*set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );*/

            }
        }
        else
        {
            Bit3_Front_Under_Led_Ice_Extract = CLEAR;
            Bit4_Front_Under_Led_Water_Extract = CLEAR;
            make_rgb_color( RGB_OFF );
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10오후 1:09:30] 주기 10ms로 변경.. 제호 RO CT 기준..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == RGB_COLOR_HOT )
    {
        if( gu8_Led_Display_Step == LED_Display__SLEEP )
        {
            /*..hui [24-2-22오후 5:08:35] 절전모드.. 레드만 10%..*/
            gu8_rgb_red_on_time = 4;
            gu8_rgb_green_on_time = 0;
            gu8_rgb_blue_on_time = 0;
        }
        else
        {
            /*..hui [23-12-1오후 5:28:18] 레드만 20%..*/
            /*gu8_rgb_red_on_time = 8;*/
            /*..hui [24-2-22오후 5:01:06] 레드만 40%..*/
            gu8_rgb_red_on_time = 16;
            gu8_rgb_green_on_time = 0;
            gu8_rgb_blue_on_time = 0;
        }
    }
    else if( mu8_color == RGB_COLOR_COLD )
    {
        if( gu8_Led_Display_Step == LED_Display__SLEEP )
        {
            /*..hui [24-2-22오후 5:09:07] 절전모드.. 그린 10%, 블루 20%..*/
            gu8_rgb_red_on_time = 0;
            gu8_rgb_green_on_time = 4;
            gu8_rgb_blue_on_time = 8;
        }
        else
        {
            /*..hui [23-12-1오후 5:28:27] 그린 20%, 블루 50%..*/
            //gu8_rgb_red_on_time = 0;
            //gu8_rgb_green_on_time = 8;
            //gu8_rgb_blue_on_time = 20;
            /*..hui [24-2-22오후 5:02:02] 그린 40%, 블루 80%..*/
            gu8_rgb_red_on_time = 0;
            gu8_rgb_green_on_time = 16;
            gu8_rgb_blue_on_time = 32;
        }
    }
    else
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void steam_clean_led_out(void)
{
    U8 mu8_steam_breath_state = 0;

    /*..hui [23-2-28오후 7:45:16] 얼음 탱크 온수 살균..*/
    if( gu8_Led_Display_Step == LED_Display__STEAM_CLEAN )
    {
        if( bit_ice_tank_ster_start == SET )
        {
            Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
        }
        else
        {
            Bit0_Front_Led_Ice_Tank_Clean_Text = CLEAR;
        }
    }
    else
    {
        Bit0_Front_Led_Ice_Tank_Clean_Text = CLEAR;

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_led_out(void)
{
    #if 0
    /*..hui [23-2-28오후 7:45:16] 얼음 탱크 온수 살균..*/
    if( bit_ice_tank_ster_start == SET )
    {
        Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_Tank_Clean_Text = CLEAR;
    }
    #endif

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-5-31오후 5:14:47] 셋 중 하나 이상 켜져있으면 UV Care랑 언더바 ON..*/
    /*if( bit_uv_water_tank_out == SET || bit_uv_ice_tray_out == SET || bit_uv_ice_tank_out == SET )*/
    /*..hui [24-4-5오전 10:57:03] 아이스트레이 제빙중에는 표시 안함..*/
    if( bit_uv_water_tank_out == SET
        || ( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR )
        || bit_uv_ice_tank_out == SET )
    {
        Bit1_Front_Led_UV_Care_Txt_Under_bar = SET;
        //Bit2_Front_Led_Care_Under_Bar = SET;
    }
    else
    {
        Bit1_Front_Led_UV_Care_Txt_Under_bar = CLEAR;
        //Bit2_Front_Led_Care_Under_Bar = CLEAR;
    }

    if( Bit1_Front_Led_UV_Care_Txt_Under_bar == SET )
    {
        if( bit_uv_water_tank_out == SET )
        {
            Bit2_Front_Led_Water_Tank_Text = SET;
        }
        else
        {
            Bit2_Front_Led_Water_Tank_Text = CLEAR;
        }

        /*if( bit_uv_ice_tray_out == SET )*/
        if( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR )
        {
            Bit3_Front_Led_Ice_Tray_Text = SET;
        }
        else
        {
            Bit3_Front_Led_Ice_Tray_Text = CLEAR;
        }

        if( bit_uv_ice_tank_out == SET )
        {
            Bit4_Front_Led_Ice_Tank_Text = SET;
        }
        else
        {
            Bit4_Front_Led_Ice_Tank_Text = CLEAR;
        }
    }
    else
    {
        Bit2_Front_Led_Water_Tank_Text = CLEAR;
        Bit4_Front_Led_Ice_Tank_Text = CLEAR;
        Bit3_Front_Led_Ice_Tray_Text = CLEAR;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


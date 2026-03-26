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
#include    "display_breath.h"

void breath_control(void);
void start_breath_steam_clean(void);
U8 steam_clean_breath_timer(U8 breath_time );
void steam_clean_breath_control(void);

void low_water_breath_control(void);
//void set_low_water_breath(void);
//void clear_low_water_breath(void);

//void preparing_breath_control(void);
void uv_popup_breath_control(void);
void water_extract_breath_control(void);
void replace_filter_breath_control(void);
void start_cooling_breath(void);
void stop_cooling_breath(void);
U8 cooling_breath_timer(U8 breath_time );
void cooling_breath_control(void);
void heating_breath_control(void);

void breath_on_off_select( U8 mu8_number, U8 mu8_on_off );
//void all_breath_start(void);
void all_breath_stop(void);

bit bit_steam_clean_breath_start;
U16 gu16_steam_clean_breath_timer;

bit bit_low_water_breath_start;
U16 gu16_low_water_breath_timer;

bit bit_cooling_breath_start;
U16 gu16_cooling_breath_timer;

bit bit_heating_breath_start;
U16 gu16_heating_breath_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void breath_control(void)
{
    steam_clean_breath_control();
    /*hot_preheat_breath_control();*/
    /*hot_select_breath_control();*/

    /*..hui [23-11-23오후 1:02:01] 기존 preparing + 물용량 디밍하는걸 low water 아이콘이 추가됨..*/
    low_water_breath_control();

    /*preparing_breath_control();*/

    /*..hui [23-6-1오후 4:56:14] UV 퍼센트, 남은시간 표시할때 디밍..*/
    uv_popup_breath_control();
    water_extract_breath_control();

    /*..hui [23-6-8오후 12:27:42] 필터교체 텍스트 디밍..*/
    replace_filter_breath_control();

    cooling_breath_control();
    heating_breath_control();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_breath_steam_clean(void)
{
    bit_steam_clean_breath_start = SET;
    gu16_steam_clean_breath_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 steam_clean_breath_timer(U8 breath_time )
{
    static U8 u8breath_steam_state = 0;

    gu16_steam_clean_breath_timer++;

    if( gu16_steam_clean_breath_timer >= breath_time )
    {
        gu16_steam_clean_breath_timer = 0;
        u8breath_steam_state = CLEAR;
        bit_steam_clean_breath_start = CLEAR;
    }
    else
    {
        u8breath_steam_state = SET;
    }

    return u8breath_steam_state;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void steam_clean_breath_control(void)
{
    U8 mu8_steam_breath_state = 0;

    if( gu8_Led_Display_Step == LED_Display__STEAM_CLEAN )
    {
        if( bit_ice_tank_ster_start == SET )
        {
            if( bit_steam_clean_breath_start == SET )
            {
                mu8_steam_breath_state = steam_clean_breath_timer( BREATH_FLICKER_COUNT );

                if( mu8_steam_breath_state == SET )
                {
                    breath_on_off_select( ANIMATION__DIMMING__ICE_TANK_CLEAN, START_ANIMATION_DIIMMING );
                }
                else
                {
                    breath_on_off_select( ANIMATION__DIMMING__ICE_TANK_CLEAN, STOP_ANIMATION_DIIMMING );
                }
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__ICE_TANK_CLEAN, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__ICE_TANK_CLEAN, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__ICE_TANK_CLEAN, STOP_ANIMATION_DIIMMING );
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void low_water_breath_control(void)
{
    U8 mu8_low_water_breath_state = 0;

    if( F_WaterOut == SET ) /*gu8_Led_Display_Step == LED_Display__WATER_EXTRACT )*/
    {
        if( u8WaterOutState == COLD_WATER_SELECT )
        {
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                /*..hui [23-11-23오후 1:09:39] 냉수 추출 - 저수위 디밍..*/
                breath_on_off_select( ANIMATION__DIMMING__NEW_LOW_WATER, START_ANIMATION_DIIMMING );
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__NEW_LOW_WATER, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__NEW_LOW_WATER, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__NEW_LOW_WATER, STOP_ANIMATION_DIIMMING );
    }

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void preparing_breath_control(void)
{
    /*..hui [23-7-26오후 4:41:11] 저수위 - 냉수 추출할때만 물량이랑 프리페어링 디밍..*/
    if( Bit3_Animation_Dimming_Oz_State == SET
        || Bit6_Animation_Dimming_ml_State == SET )
    {
        breath_on_off_select( ANIMATION__DIMMING__PREPARING, START_ANIMATION_DIIMMING );
    }
    else
    {

        breath_on_off_select( ANIMATION__DIMMING__PREPARING, STOP_ANIMATION_DIIMMING );

    }

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_popup_breath_control(void)
{
    if( gu8_Led_Display_Step == LED_Display__UV )
    {
        /*..hui [23-8-28오후 4:13:24] 개별 디밍하지않고 UV Care 만 디밍하도록 변경.. 디자인..*/
        breath_on_off_select( ANIMATION__DIMMING__UV_CARE_UNDERBAR, START_ANIMATION_DIIMMING );
    }
    else
    {
        #if 0
        breath_on_off_select( ANIMATION__DIMMING__WATER_TANK, STOP_ANIMATION_DIIMMING );
        breath_on_off_select( ANIMATION__DIMMING__ICE_TRAY, STOP_ANIMATION_DIIMMING );
        breath_on_off_select( ANIMATION__DIMMING__ICE_TANK, STOP_ANIMATION_DIIMMING );
        #endif

        breath_on_off_select( ANIMATION__DIMMING__UV_CARE_UNDERBAR, STOP_ANIMATION_DIIMMING );
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_breath_control(void)
{
    if( gu8_Led_Display_Step == LED_Display__FLUSHING )
    {
        if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
        {
            breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, START_ANIMATION_DIIMMING );
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, STOP_ANIMATION_DIIMMING );
    }



    #if 0
    else if( gu8_Led_Display_Step == LED_Display__ACID_CLEAN )
    {
        if( bit_acid_clean_start == SET )
        {
            /*..hui [24-5-23오후 7:26:34] 구연산 세척할때 디밍..*/
            if( gu8_acid_clean_step == 8 || gu8_acid_clean_step == 20 )
            {
                breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, START_ANIMATION_DIIMMING );
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__WATER_OUT, STOP_ANIMATION_DIIMMING );
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void replace_filter_breath_control(void)
{
    if( gu8_Led_Display_Step == LED_Display__WATER_EXTRACT
        || gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        if( F_WaterOut == SET || F_Ice == SET )
        {
            if( bit_filter_alarm_start == SET )
            {
                breath_on_off_select( ANIMATION__DIMMING__FILTER_FLUSHING, START_ANIMATION_DIIMMING );
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__FILTER_FLUSHING, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__FILTER_FLUSHING, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__FILTER_FLUSHING, STOP_ANIMATION_DIIMMING );
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_cooling_breath(void)
{
    bit_cooling_breath_start = SET;
    gu16_cooling_breath_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_cooling_breath(void)
{
    bit_cooling_breath_start = CLEAR;
    gu16_cooling_breath_timer = 0;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 cooling_breath_timer(U8 breath_time )
{
    static U8 u8breath_cooling = 0;

    gu16_cooling_breath_timer++;

    if( gu16_cooling_breath_timer >= breath_time )
    {
        gu16_cooling_breath_timer = 0;
        u8breath_cooling = CLEAR;
        bit_cooling_breath_start = CLEAR;
    }
    else
    {
        u8breath_cooling = SET;
    }

    return u8breath_cooling;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cooling_breath_control(void)
{
    U8 mu8_cooling_breath_state = 0;

    if( gu8_Led_Display_Step == LED_Display__MAIN )
    {
        if( bit_cooling_breath_start == SET && Bit2_Front_New_Led_Cold_Cooling_Text == SET)
        {
            mu8_cooling_breath_state = cooling_breath_timer( 62 );

            if( mu8_cooling_breath_state == SET )
            {
                breath_on_off_select( ANIMATION__DIMMING__NEW_COLD_COOLING, START_ANIMATION_DIIMMING );
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__NEW_COLD_COOLING, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__NEW_COLD_COOLING, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__NEW_COLD_COOLING, STOP_ANIMATION_DIIMMING );
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void heating_breath_control(void)
{
    U8 mu8_heating_breath_state = 0;

    if( gu8_Led_Display_Step == LED_Display__MAIN )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            /*if( bit_heating_breath_start == SET && Bit1_Front_New_Led_Hot_Heating_Text == SET)*/
            /*..hui [23-11-27오후 3:01:07] 히팅 아이콘은.. 온수 선택 상태에서 preparing 아이콘 ON 조건일떄 디밍..*/
            if( Bit0_Front_Left_Led_Preparing_Text == SET && Bit1_Front_New_Led_Hot_Heating_Text == SET )
            {
                breath_on_off_select( ANIMATION__DIMMING__NEW_HOT_HEATING, START_ANIMATION_DIIMMING );
            }
            else
            {
                breath_on_off_select( ANIMATION__DIMMING__NEW_HOT_HEATING, STOP_ANIMATION_DIIMMING );
            }
        }
        else
        {
            breath_on_off_select( ANIMATION__DIMMING__NEW_HOT_HEATING, STOP_ANIMATION_DIIMMING );
        }
    }
    else
    {
        breath_on_off_select( ANIMATION__DIMMING__NEW_HOT_HEATING, STOP_ANIMATION_DIIMMING );
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void breath_on_off_select( U8 mu8_number, U8 mu8_on_off )
{
    if(  mu8_number > ANIMATION__DIMMING__NEW_REPLACE_FILTER_3_NUM || mu8_on_off > START_ANIMATION_DIIMMING )
    {
        return;
    }
    else{}

    switch( mu8_number )
    {
        case ANIMATION__DIMMING__WATER_OUT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_Water_Out_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_Water_Out_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_OUT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_Ice_Out_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_Ice_Out_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__FILTER_FLUSHING:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit2_Animation_Dimming_Filter_Flushing_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit2_Animation_Dimming_Filter_Flushing_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__CURRENT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit3_Animation_Dimming_Current_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit3_Animation_Dimming_Current_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__PREPARING:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_Preparing_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_Preparing_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_TANK_CLEAN:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit5_Animation_Dimming_Ice_Tank_Clean_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit5_Animation_Dimming_Ice_Tank_Clean_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__UV_CARE_UNDERBAR:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit6_Animation_Dimming_UV_Care_Under_Bar_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit6_Animation_Dimming_UV_Care_Under_Bar_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__WATER_TANK:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit7_Animation_Dimming_Water_Tank_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit7_Animation_Dimming_Water_Tank_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_TRAY:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit8_Animation_Dimming_Ice_Tray_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit8_Animation_Dimming_Ice_Tray_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_TANK:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit9_Animation_Dimming_Ice_Tank_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit9_Animation_Dimming_Ice_Tank_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SEG_1_0_0:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit10_Animation_Dimming_Left_Seg_1_0_0_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit10_Animation_Dimming_Left_Seg_1_0_0_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SEG_0_2_0:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit11_Animation_Dimming_Left_Seg_0_2_0_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit11_Animation_Dimming_Left_Seg_0_2_0_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SEG_0_0_3:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit12_Animation_Dimming_Left_Seg_0_0_3_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit12_Animation_Dimming_Left_Seg_0_0_3_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__RIGHT_SEG_1_0_0:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit13_Animation_Dimming_Right_Seg_1_0_0_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit13_Animation_Dimming_Right_Seg_1_0_0_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__RIGHT_SEG_0_2_0:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit14_Animation_Dimming_Right_Seg_0_2_0_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit14_Animation_Dimming_Right_Seg_0_2_0_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__RIGHT_SEG_0_0_3:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit15_Animation_Dimming_Right_Seg_0_0_3_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit15_Animation_Dimming_Right_Seg_0_0_3_State = CLEAR;
            }

        break;

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
        case ANIMATION__DIMMING__oF:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_oF_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_oF_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__PERCENT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_Percent_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_Percent_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__oC:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit2_Animation_Dimming_oC_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit2_Animation_Dimming_oC_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__Oz:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit3_Animation_Dimming_Oz_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit3_Animation_Dimming_Oz_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__Min_Left:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_Min_Left_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_Min_Left_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__mL:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit6_Animation_Dimming_ml_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit6_Animation_Dimming_ml_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__Days_Left:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit7_Animation_Dimming_Days_Left_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit7_Animation_Dimming_Days_Left_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SETTING_BAR_1_1:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit5_Animation_Dimming_Temp_Setting_Bar_1_1_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit5_Animation_Dimming_Temp_Setting_Bar_1_1_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SETTING_BAR_1_2:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit8_Animation_Dimming_Temp_Setting_Bar_1_2_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit8_Animation_Dimming_Temp_Setting_Bar_1_2_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SETTING_BAR_1_3:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit9_Animation_Dimming_Temp_Setting_Bar_1_3_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit9_Animation_Dimming_Temp_Setting_Bar_1_3_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__LEFT_SETTING_BAR_1_4:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit10_Animation_Dimming_Temp_Setting_Bar_1_4_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit10_Animation_Dimming_Temp_Setting_Bar_1_4_State = CLEAR;
            }

        break;





        case ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_1:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit11_Animation_Dimming_Amount_Setting_Bar_2_1_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit11_Animation_Dimming_Amount_Setting_Bar_2_1_State = CLEAR;
            }

        break;


        case ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_2:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit12_Animation_Dimming_Amount_Setting_Bar_2_2_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit12_Animation_Dimming_Amount_Setting_Bar_2_2_State = CLEAR;
            }

        break;


        case ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_3:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit13_Animation_Dimming_Amount_Setting_Bar_2_3_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit13_Animation_Dimming_Amount_Setting_Bar_2_3_State = CLEAR;
            }

        break;


        case ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_4:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit14_Animation_Dimming_Amount_Setting_Bar_2_4_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit14_Animation_Dimming_Amount_Setting_Bar_2_4_State = CLEAR;
            }

        break;


        case ANIMATION__DIMMING__AMOUNT_SETTING_BAR_CONTINUE:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit15_Animation_Dimming_Amount_Setting_Bar_Continue_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit15_Animation_Dimming_Amount_Setting_Bar_Continue_State = CLEAR;
            }

        break;


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

        case ANIMATION__DIMMING__SETTINGS:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_Settings_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_Settings_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_Ice_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_Ice_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__HOT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit2_Animation_Dimming_Hot_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit2_Animation_Dimming_Hot_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__AMBIENT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_Ambient_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_Ambient_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__COLD:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit5_Animation_Dimming_Cold_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit5_Animation_Dimming_Cold_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__AMOUNT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit7_Animation_Dimming_Amount_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit7_Animation_Dimming_Amount_State = CLEAR;
            }

        break;




///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

        case ANIMATION__DIMMING__ECO_ICON:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_Eco_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_Eco_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__WIFI_ICON:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_Wifi_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_Wifi_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_FIRST_TEXT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit3_Animation_Dimming_Ice_First_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit3_Animation_Dimming_Ice_First_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_FULL_TEXT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_Ice_Full_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_Ice_Full_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__ICE_LOCK_ICON:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit5_Animation_Dimming_Ice_Lock_Icon_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit5_Animation_Dimming_Ice_Lock_Icon_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__HOT_LOCK_ICON:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit6_Animation_Dimming_Hot_Lock_Icon_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit6_Animation_Dimming_Hot_Lock_Icon_State = CLEAR;
            }

        break;


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

        case ANIMATION__DIMMING__SETTING_ICE_FIRST:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_Setting_Ice_First_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_Setting_Ice_First_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__SETTING_ICE_LOCK:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_Setting_Ice_Lock_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_Setting_Ice_Lock_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__SETTING_HOT_LOCK:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit2_Animation_Dimming_Setting_Hot_Lock_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit2_Animation_Dimming_Setting_Hot_Lock_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__SETTING_TOUCH_LOCK:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit3_Animation_Dimming_Setting_Touch_Lock_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit3_Animation_Dimming_Setting_Touch_Lock_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__SETTING_ECO_MODE:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_Setting_Eco_Mode_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_Setting_Eco_Mode_State = CLEAR;
            }

        break;



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

        case ANIMATION__DIMMING__NEW_ICE_MAKING:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit0_Animation_Dimming_New_Ice_Making_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit0_Animation_Dimming_New_Ice_Making_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_HOT_HEATING:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit1_Animation_Dimming_New_Hot_Heating_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit1_Animation_Dimming_New_Hot_Heating_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_COLD_COOLING:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit2_Animation_Dimming_New_Cold_Cooling_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit2_Animation_Dimming_New_Cold_Cooling_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_LOW_WATER:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit3_Animation_Dimming_New_Low_Water_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit3_Animation_Dimming_New_Low_Water_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_REPLACE_FILTER_TEXT:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit4_Animation_Dimming_New_Replace_Filter_Txt_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit4_Animation_Dimming_New_Replace_Filter_Txt_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_REPLACE_FILTER_1_NUM:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit5_Animation_Dimming_New_Replace_Filter_1_Num_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit5_Animation_Dimming_New_Replace_Filter_1_Num_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_REPLACE_FILTER_2_NUM:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit6_Animation_Dimming_New_Replace_Filter_2_Num_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit6_Animation_Dimming_New_Replace_Filter_2_Num_State = CLEAR;
            }

        break;

        case ANIMATION__DIMMING__NEW_REPLACE_FILTER_3_NUM:

            if( mu8_on_off == START_ANIMATION_DIIMMING)
            {
                Bit7_Animation_Dimming_New_Replace_Filter_3_Num_State = SET;
            }
            else /*if( mu8_on_off == STOP_ANIMATION_DIIMMING)*/
            {
                Bit7_Animation_Dimming_New_Replace_Filter_3_Num_State = CLEAR;
            }

        break;


        default:

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void all_breath_start(void)
{
    gu16_animation_dimming = 0xffff;
    gu16_animation_dimming_two = 0xffff;
    gu8_animation_dimming_three = 0xff;
    gu8_animation_dimming_four = 0x7f;
    gu8_animation_dimming_five = 0x4f;
    gu8_animation_dimming_six = 0xff;
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_breath_stop(void)
{
    gu16_animation_dimming = 0;
    gu16_animation_dimming_two = 0;
    gu8_animation_dimming_three = 0;
    gu8_animation_dimming_four = 0;
    gu8_animation_dimming_five = 0;
    gu8_animation_dimming_six = 0;
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





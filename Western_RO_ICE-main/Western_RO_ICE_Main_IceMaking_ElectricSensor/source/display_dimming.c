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
#include    "display_dimming.h"


//void set_led_duty( U8 mu8_number, U8 mu8_duty );
//void dimming_on_off_select( U8 mu8_number, U8 mu8_on_off );
//void all_dimming_full_on(void);
void set_duty_percent( U8 mu8_number, U8 mu8_percent );
void all_duty_100_percent(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void set_duty_percent( U8 mu8_number, U8 mu8_percent )
{
    if(  mu8_number > DIMMING__PERCENT_WATER_EXTRACT )
    {
        return;
    }
    else{}

    if( mu8_percent > DIIMMING__100_PERCENT )
    {
        mu8_percent = DIIMMING__100_PERCENT;
    }
    else{}

    switch( mu8_number )
    {
        case DIMMING__PERCENT_SETTING_SELECT:

            bit_0_3_setting_select = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_SELECT:

            bit_4_7_ice_select = mu8_percent;

        break;

        case DIMMING__PERCENT_HOT_SELECT:

            bit_0_3_hot_select = mu8_percent;

        break;

        case DIMMING__PERCENT_AMBIENT_SELECT:

            bit_4_7_ambient_select = mu8_percent;

        break;

        case DIMMING__PERCENT_COLD_SELECT:

            bit_0_3_cold_select = mu8_percent;

        break;

        case DIMMING__PERCENT_AMOUNT_SELECT:

            bit_4_7_amount_select = mu8_percent;

        break;

        case DIMMING__PERCENT_SETTING_ICE_FIRST:

            bit_0_3_setting_ice_first = mu8_percent;

        break;

        case DIMMING__PERCENT_SETTING_ICE_LCOK:

            bit_4_7_setting_ice_lock = mu8_percent;

        break;

        case DIMMING__PERCENT_SETTING_HOT_LOCK:

            bit_0_3_setting_hot_lock = mu8_percent;

        break;

        case DIMMING__PERCENT_SETTING_TOUCH_LOCK:

            bit_4_7_setting_touch_lock = mu8_percent;

        break;

        case DIMMING__PERCENT_SETTING_ECO_MODE:

            bit_0_3_setting_eco_mode = mu8_percent;

        break;

        case DIMMING__PERCENT_PREPARING_TEXT:

            bit_0_3_preparing_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_CURRENT_TEXT:

            bit_4_7_current_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_FILTER_FLUSHING_TEXT:

            bit_0_3_filter_flushing_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ECCO_ICON:

            bit_4_7_eco_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_oF_ICON:

            bit_0_3_oF_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_PERCENT_ICON:

            bit_4_7_percent_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_oC_ICON:

            bit_0_3_oC_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_TANK_CLEAN_TEXT:

            bit_0_3_ice_tank_clean_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_UV_CARE_UNDER_BAR_TEXT:

            bit_4_7_uv_care_under_bar_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_WIFI_BLUE_ICON:

            bit_0_3_wifi_blue_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_WATER_TANK_TEXT:

            bit_4_7_water_tank_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_TRAY_TEXT:

            bit_0_3_ice_tray_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_TANK_TEXT:

            bit_4_7_ice_tank_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_WIFI_WHITE_ICON:

            bit_0_3_wifi_white_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_Oz_ICON:

            bit_4_7_oz_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_Min_Left_ICON:

            bit_0_3_Min_Left_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ml_ICON:

            bit_4_7_ml_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_days_Left_ICON:

            bit_0_3_Days_Left_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_FIRST_TEXT:

            bit_4_7_ice_first_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_LOCK_ICON:

            bit_0_3_ice_lock_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_HOT_LOCK_ICON:

            bit_4_7_hot_lock_icon = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_FULL_TEXT:

            bit_0_3_ice_full_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_ICE_MAKING_TEXT:

            bit_4_7_new_ice_making_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_HOT_HEATING_TEXT:

            bit_0_3_new_hot_heating_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_COLD_COOLING_TEXT:

            bit_4_7_new_cold_cooling_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_LOW_WATER_TEXT:

            bit_0_3_new_low_water_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_REPLACE_FILTER_TEXT:

            bit_4_7_new_replace_filter_txt = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM:

            bit_0_3_new_replace_filter_1_num = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM:

            bit_4_7_new_replace_filter_2_num = mu8_percent;

        break;

        case DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM:

            bit_0_3_new_replace_filter_3_num = mu8_percent;

        break;


        case DIMMING__PERCENT_AMOUNT_BAR_2_1:

            bit_4_7_amount_bar_2_1 = mu8_percent;

        break;

        case DIMMING__PERCENT_AMOUNT_BAR_2_2:

            bit_0_3_amount_bar_2_2 = mu8_percent;

        break;

        case DIMMING__PERCENT_AMOUNT_BAR_2_3:

            bit_4_7_amount_bar_2_3 = mu8_percent;

        break;

        case DIMMING__PERCENT_AMOUNT_BAR_2_4:

            bit_0_3_amount_bar_2_4 = mu8_percent;

        break;

        case DIMMING__PERCENT_AMOUNT_BAR_CONTINUE:

            bit_4_7_amount_bar_continue = mu8_percent;

        break;

        case DIMMING__PERCENT_TEMP_BAR_1_1:

            bit_0_3_temp_bar_1_1 = mu8_percent;

        break;

        case DIMMING__PERCENT_TEMP_BAR_1_2:

            bit_4_7_temp_bar_1_2 = mu8_percent;

        break;

        case DIMMING__PERCENT_TEMP_BAR_1_3:

            bit_0_3_temp_bar_1_3 = mu8_percent;

        break;

        case DIMMING__PERCENT_TEMP_BAR_1_4:

            bit_4_7_temp_bar_1_4 = mu8_percent;

        break;

        case DIMMING__PERCENT_LEFT_SEGMENT_1_0_0:

            bit_0_3_left_seg_1_0_0 = mu8_percent;

        break;

        case DIMMING__PERCENT_LEFT_SEGMENT_0_2_0:

            bit_4_7_left_seg_0_2_0 = mu8_percent;

        break;

        case DIMMING__PERCENT_LEFT_SEGMENT_0_0_3:

            bit_0_3_left_seg_0_0_3 = mu8_percent;

        break;

        case DIMMING__PERCENT_RIGHT_SEGMENT_1_0_0:

            bit_4_7_right_seg_1_0_0 = mu8_percent;

        break;

        case DIMMING__PERCENT_RIGHT_SEGMENT_0_2_0:

            bit_0_3_right_seg_0_2_0 = mu8_percent;

        break;

        case DIMMING__PERCENT_RIGHT_SEGMENT_0_0_3:

            bit_4_7_right_seg_0_0_3 = mu8_percent;

        break;

        case DIMMING__PERCENT_ICE_EXTRACT:

            bit_0_3_ice_extract = mu8_percent;

        break;

        case DIMMING__PERCENT_WATER_EXTRACT:

            bit_4_7_water_extract = mu8_percent;

        break;

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


        default:

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_duty_100_percent(void)
{
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:26:02] 기능부..*/////////////////////////////////
    set_duty_percent( DIMMING__PERCENT_SETTING_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
    set_duty_percent( DIMMING__PERCENT_ICE_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );

    set_duty_percent( DIMMING__PERCENT_HOT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );

    set_duty_percent( DIMMING__PERCENT_COLD_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, FUNCTION_ICON__DIMMING__70_PERCENT );
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:26:07] 설정부..*/
    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_FIRST, SETTING_TEXT__DIMMING__50_PERCETN );
    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_LCOK, SETTING_TEXT__DIMMING__50_PERCETN );

    set_duty_percent( DIMMING__PERCENT_SETTING_HOT_LOCK, SETTING_TEXT__DIMMING__50_PERCETN );
    set_duty_percent( DIMMING__PERCENT_SETTING_TOUCH_LOCK, SETTING_TEXT__DIMMING__50_PERCETN );

    set_duty_percent( DIMMING__PERCENT_SETTING_ECO_MODE, SETTING_TEXT__DIMMING__50_PERCETN );
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:32:07] 상단아이콘부..*/
    set_duty_percent( DIMMING__PERCENT_PREPARING_TEXT, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_CURRENT_TEXT, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_FILTER_FLUSHING_TEXT, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_ECCO_ICON, TOP_ICON__DIMMING__50_PERCENT );    /////

    set_duty_percent( DIMMING__PERCENT_oF_ICON, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_PERCENT_ICON, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_oC_ICON, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_ICE_TANK_CLEAN_TEXT, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_UV_CARE_UNDER_BAR_TEXT, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_WIFI_BLUE_ICON, WIFI_BLUE_LED_100_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_WATER_TANK_TEXT, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_ICE_TRAY_TEXT, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_ICE_TANK_TEXT, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_WIFI_WHITE_ICON, WIFI_WHITE_LED_70_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_Oz_ICON, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_Min_Left_ICON, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_ml_ICON, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_days_Left_ICON, TOP_ICON__DIMMING__50_PERCENT );
    /*set_duty_percent( DIMMING__PERCENT_ICE_FIRST_TEXT, DIIMMING__100_PERCENT );*/

    set_duty_percent( DIMMING__PERCENT_ICE_LOCK_ICON, TOP_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_HOT_LOCK_ICON, TOP_ICON__DIMMING__50_PERCENT );

    /*set_duty_percent( DIMMING__PERCENT_ICE_FULL_TEXT, DIIMMING__100_PERCENT );*/
    /*set_duty_percent( DIMMING__PERCENT_NEW_ICE_MAKING_TEXT, DIIMMING__100_PERCENT );*/

    /*set_duty_percent( DIMMING__PERCENT_NEW_HOT_HEATING_TEXT, DIIMMING__100_PERCENT );*/
    /*set_duty_percent( DIMMING__PERCENT_NEW_COLD_COOLING_TEXT, DIIMMING__100_PERCENT );*/

    /*set_duty_percent( DIMMING__PERCENT_NEW_LOW_WATER_TEXT, DIIMMING__100_PERCENT );*/
    set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_TEXT, TOP_ICON__DIMMING__50_PERCENT );

    set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM, TOP_ICON__DIMMING__50_PERCENT );    /////

    set_duty_percent( DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, TOP_ICON__DIMMING__50_PERCENT );    /////

    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, TOP_ICON__DIMMING__50_PERCENT );    /////

    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, TOP_ICON__DIMMING__50_PERCENT );    //////

    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, TOP_ICON__DIMMING__50_PERCENT );    /////

    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, TOP_ICON__DIMMING__50_PERCENT );    /////
    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, TOP_ICON__DIMMING__50_PERCENT );    /////

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:29:05] 중간 텍스트 아이콘부..*/
    set_duty_percent( DIMMING__PERCENT_ICE_FIRST_TEXT, CENTER_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_NEW_ICE_MAKING_TEXT, CENTER_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_NEW_HOT_HEATING_TEXT, CENTER_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_NEW_COLD_COOLING_TEXT, CENTER_ICON__DIMMING__50_PERCENT );
    set_duty_percent( DIMMING__PERCENT_NEW_LOW_WATER_TEXT, CENTER_ICON__DIMMING__50_PERCENT );

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:29:30] 얼음 가득..*/
    /*set_duty_percent( DIMMING__PERCENT_ICE_FULL_TEXT, DIIMMING__100_PERCENT );*/
    set_duty_percent( DIMMING__PERCENT_ICE_FULL_TEXT, ICE_FULL__DIMMING__40_PERCETN );


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:26:36] 세그먼트부..*/
    set_duty_percent( DIMMING__PERCENT_LEFT_SEGMENT_1_0_0, SEGMENT__DIMMING__90_PERCENT );
    set_duty_percent( DIMMING__PERCENT_LEFT_SEGMENT_0_2_0, SEGMENT__DIMMING__90_PERCENT );

    set_duty_percent( DIMMING__PERCENT_LEFT_SEGMENT_0_0_3, SEGMENT__DIMMING__90_PERCENT );
    set_duty_percent( DIMMING__PERCENT_RIGHT_SEGMENT_1_0_0, SEGMENT__DIMMING__90_PERCENT );

    set_duty_percent( DIMMING__PERCENT_RIGHT_SEGMENT_0_2_0, SEGMENT__DIMMING__90_PERCENT );
    set_duty_percent( DIMMING__PERCENT_RIGHT_SEGMENT_0_0_3, SEGMENT__DIMMING__90_PERCENT );
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-2-22오후 5:26:40] 추출..*/
    /*set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__100_PERCENT );*/
    /*set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__100_PERCENT );*/
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
    set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





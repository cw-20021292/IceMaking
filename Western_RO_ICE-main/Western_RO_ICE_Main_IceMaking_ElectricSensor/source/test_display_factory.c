/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "test_display_factory.h"

void diplay_test_start(void);
void Display_Test_Main(void);
void display_filter_cover(void);
void display_test_factory_input(void);
void display_test_factory_job(void);
/*void display_test_tds(void);*/
void display_test_error(void);
void make_test_mode_rgb_color( U8 mu8_color );
void initial_all_data(void);



bit F_cds_detect;
U8 gu8_user_lcd_output;
U8 gu8_hot_lcd_output;
U8 gu8_room_lcd_output;
U8 gu8_cold_lcd_output;
U8 gu8_cup_lcd_output;

U8 gu8_initial_all_data;
U8 u8_water_select_testmode;
U8 u8_cup_select_testmode;

U8 gu8_hot_temp_off_timer;
U8 gu8_cup_level_off_timer;
U8 gu8_left_fnd_off_timer;
U8 gu8_right_fnd_off_timer;

U8 gu8_display_test_error;
bit bit_display_error_state;

bit bit_tank_cover_first_read;
bit bit_tank_cover_error;

bit bit_side_cover_first_read;
bit bit_side_cover_error;
U8 gu8_reed_first_read_timer;


U8 gu8_display_reed_test_step;
U8 gu8_display_reed_test_timer;

bit bit_display_test_neo_filter;
bit bit_display_test_ro_filter;
bit bit_display_test_ino_filter;


bit bit_display_test_neo_filter_old;
bit bit_display_test_ro_filter_old;
bit bit_display_test_ino_filter_old;


bit bit_display_test_filter_reed_error;


U8 gu8_water_color_change_timer;

U16 gu16_display_tds_in_max;
U16 gu16_display_tds_out_max;

U16 gu16_tds_test_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void diplay_test_start(void)
{
    gu8_test_mode_timeout = 0;
    /*play_melody_select_196();*/
    play_voice_test_mode_151();

    off_all_control_led();
    UARTest_NO_LOAD_Set();
    F_TrayMotorUP = 0;
    F_TrayMotorDOWN = 0;

    /*..hui [17-12-28오후 10:54:12] 버전만 표시..*/
    F_FW_Version_Display_Mode = CLEAR;
    gu8_led_version_step = 2;
    gu8_version_display_Timer = 0;

    u8FactoryTestMode = DISPLAY_TEST_MODE;

    /*..hui [19-11-5오후 5:57:28] EEPROM / RTC 시간 초기화..*/
    gu8_initial_all_data = 1;

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14오후 8:15:16] 12V 전원 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    bit_setting_test_finish = CLEAR;
    bit_ice_test_finish = CLEAR;
    bit_hot_test_finish = CLEAR;
    bit_ambient_test_finish = CLEAR;
    bit_cold_tst_finish = CLEAR;
    bit_amount_test_finish = CLEAR;
    bit_ice_first_test_finish = CLEAR;
    bit_ice_lock_test_finish = CLEAR;
    bit_hot_lock_test_finish = CLEAR;
    bit_touch_lock_test_finish = CLEAR;
    bit_steam_off_test_finish = CLEAR;
    bit_eco_test_finish = CLEAR;

    bit_water_extract_test_finish = CLEAR;
    bit_ice_extract_test_finish = CLEAR;

    bit_manual_test_start = CLEAR;

    all_breath_stop();

    bit_tank_cover_first_read = CLEAR;
    bit_side_cover_first_read = CLEAR;
    gu8_reed_first_read_timer = 0;

    bit_filter_cover_old = SET;
    gu8_display_reed_test_step = 0;
    bit_display_test_filter_reed_error = CLEAR;

    #if 0
    /*..hui [24-11-13오후 4:24:14] TDS 삭제..*/
    gu16_tds_test_timer = 0;
    gu16_display_tds_in_max = 0;
    gu16_display_tds_out_max = 0;
    #endif


    #if 0
    /*..hui [24-11-13오후 4:00:55] 드레인 전압 삭제..*/
    /*..hui [24-7-26오후 5:39:25] 드레인 수위센서 전원 항상 킴..*/
    pPower_Drain_Level = CLEAR;
    bit_drain_level_power_output = SET;
    #endif


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Test_Main(void)
{
    all_breath_stop();
    //all_dimming_full_on();
    all_duty_100_percent();

    if(F_FW_Version_Display_Mode != SET)
    {
        display_version();
    }
    else
    {
        /*..hui [24-11-13오후 4:24:29] TDS 삭제..*/
        /*display_test_tds();*/
        display_test_error();

        display_test_factory_input();
        display_test_factory_job();

        fnd_left_display_test();
        fnd_right_display_test();

        /*..hui [23-6-30오후 1:22:01] 디스플레이 검사할때도 DC FAN은 항시 ON하도록..*/
        pDC_FAN = SET;
    }

    initial_all_data();
    initial_ice_tray();
    display_filter_cover();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_filter_cover(void)
{
    /*..hui [21-10-6오후 7:48:43] 감지..*/
    if( pREED_FILTER_COVER == CLEAR )
    {
        if( bit_filter_cover_old == SET )
        {
            bit_filter_cover_old = CLEAR;

            /*..hui [21-10-6오후 7:50:14] 미감지 -> 감지로 변경된 경우에만 정상..*/
            bit_uart_filter_cover_reed = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_filter_cover_old == CLEAR )
        {
            bit_filter_cover_old = SET;
            play_melody_warning_197();
        }
        else{}
    }



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_input(void)
{
    //if(gu16ADCds < 700)
    /*..hui [19-11-18오전 11:28:17] 프론트 LED 다 꺼진 상태에서 조도센서 입력..*/
    /*..hui [19-11-18오후 12:55:19] 트레이 다 올리고나서부터 감지..*/
    /*..hui [20-2-11오후 5:55:02] 탱크 리드스위치 입력 추가.. 닫혔을 경우에만..*/
    /*..hui [20-2-17오후 3:24:39] 트레이도 제빙쪽으로 다 올라갔을 경우에만 완료되도록..*/
    /*..hui [23-12-15오전 9:28:30] 탑커버 체결상태도 추가..*/
    if( gu8_front_temp_fnd_hundred == 0
        && gu8_front_temp_fnd_ten == 0
        && gu8_front_temp_fnd_one == 0
        && gu8_front_amount_fnd_hundred == 0
        && gu8_front_amount_fnd_ten == 0
        && gu8_front_amount_fnd_one == 0
        && gu8_front_select_led == 0
        && gu8_front_new_text_led == 0
        && gu8_front_setting_led == 0
        && gu8_front_under_icon_led == 0
        && gu8_front_uv_care_txt_led == 0
        && gu8_front_left_led == 0
        && gu8_front_right_led == 0
        && gu8_front_temp_setting_bar_led == 0
        && gu8_front_amount_setting_bar_led == 0

        /*&& gu8_service_reed_uart == SET*/
        && pREED_FILTER_COVER == CLEAR
        && pREED_NEO_1_FILTER == CLEAR
        && pREED_RO_2_FILTER == CLEAR
        && pREED_INO_3_FILTER == CLEAR

        && pREED_TANK_COVER == CLEAR
        && gu8_uart_tray_initial_step == 3
        && gu8_display_test_error == 0

        && pREED_ACID == SET )
    {
        F_cds_detect = 1;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_job(void)
{
    led_blink_timer();

    if( bit_display_test_filter_reed_error == SET )
    {
        gu8_front_select_led = 0;
        gu8_front_new_text_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_under_icon_led = 0;
        gu8_front_uv_care_txt_led = 0;

        gu8_front_left_led = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        return;
    }
    else if( gu8_display_test_error != 0 )
    {
        gu8_front_select_led = 0;
        gu8_front_new_text_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_under_icon_led = 0;
        gu8_front_uv_care_txt_led = 0;

        gu8_front_left_led = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        return;
    }
    else{}

    if(gu8_setting_test_input == 1)
    {
        Bit0_Front_Led_Set_Select = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Left_Led_Preparing_Text = F_cds_detect & F_Wink_500ms;
        bit_setting_test_finish = SET;
    }
    else
    {
        if( bit_setting_test_finish == CLEAR )
        {
            Bit0_Front_Led_Set_Select = SET;
            Bit0_Front_Left_Led_Preparing_Text = SET;
        }
        else
        {
            gu8_setting_test_input = 1;
        }
    }

    if(gu8_ice_test_input == 1)
    {
        Bit1_Front_Led_Ice_Select = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Left_Led_Filter_Flushing_Text = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Left_Led_Celcius_oC_Icon = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = F_cds_detect & F_Wink_500ms;
        bit_ice_test_finish = SET;
    }
    else
    {
        if( bit_ice_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = SET;
            Bit2_Front_Left_Led_Filter_Flushing_Text = SET;
            Bit6_Front_Left_Led_Celcius_oC_Icon = SET;
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = SET;
        }
        else
        {
            gu8_ice_test_input = 1;
        }
    }

    if(gu8_hot_test_input == 1)
    {
        Bit2_Front_Led_Hot_Select = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Left_Led_Current_Text = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Left_Led_Percent_Icon = F_cds_detect & F_Wink_500ms;

        bit_hot_test_finish = SET;
    }
    else
    {
        if( bit_hot_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Select = SET;
            Bit1_Front_Left_Led_Current_Text = SET;
            Bit5_Front_Left_Led_Percent_Icon = SET;
        }
        else
        {
            gu8_hot_test_input = 1;
        }
    }

    if(gu8_ambient_test_input == 1)
    {
        Bit3_Front_Led_Ambient_Select = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Led_Ice_Tank_Clean_Text = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Led_Water_Tank_Text = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Led_Ice_Tank_Text = F_cds_detect & F_Wink_500ms;
        Bit5_Front_New_Led_Replace_Filter_1_Num = F_cds_detect & F_Wink_500ms;

        bit_ambient_test_finish = SET;
    }
    else
    {
        if( bit_ambient_test_finish == CLEAR )
        {
            Bit3_Front_Led_Ambient_Select = SET;
            Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
            Bit2_Front_Led_Water_Tank_Text = SET;
            Bit4_Front_Led_Ice_Tank_Text = SET;
            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
        }
        else
        {
            gu8_ambient_test_input = 1;
        }
    }

    if(gu8_cold_test_input == 1)
    {
        Bit4_Front_Led_Cold_Select = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Led_UV_Care_Txt_Under_bar = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Led_Ice_Tray_Text = F_cds_detect & F_Wink_500ms;
        Bit6_Front_New_Led_Replace_Filter_2_Num = F_cds_detect & F_Wink_500ms;

        bit_cold_tst_finish = SET;
    }
    else
    {
        if( bit_cold_tst_finish == CLEAR )
        {
            Bit4_Front_Led_Cold_Select = SET;
            Bit1_Front_Led_UV_Care_Txt_Under_bar = SET;
            Bit3_Front_Led_Ice_Tray_Text = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
        }
        else
        {
            gu8_cold_test_input = 1;
        }
    }

    if(gu8_amount_test_input == 1)
    {
        Bit5_Front_Led_Amount_Select = F_cds_detect & F_Wink_500ms;
        Bit4_Front_New_Led_Replace_Filter_Text = F_cds_detect & F_Wink_500ms;
        Bit7_Front_New_Led_Replace_Filter_3_Num = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Right_Led_ml_Text = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Right_Led_OZ_Text = F_cds_detect & F_Wink_500ms;

        bit_amount_test_finish = SET;
    }
    else
    {
        if( bit_amount_test_finish == CLEAR )
        {
            Bit5_Front_Led_Amount_Select = SET;
            Bit4_Front_New_Led_Replace_Filter_Text = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
            Bit5_Front_Right_Led_ml_Text = SET;
            Bit3_Front_Right_Led_OZ_Text = SET;
        }
        else
        {

            gu8_amount_test_input = 1;
        }
    }

    if(gu8_setting_ice_first_test_input == 1)
    {
        Bit0_Front_Led_Ice_First = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Under_Txt_Led_Ice_First = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Right_Led_Days_Left_Text = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Right_Led_Wifi_Icon_White = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = SET;

        bit_ice_first_test_finish = SET;
    }
    else
    {
        if( bit_ice_first_test_finish == CLEAR )
        {
            Bit0_Front_Led_Ice_First = SET;
            Bit0_Front_Under_Txt_Led_Ice_First = SET;
            Bit6_Front_Right_Led_Days_Left_Text = SET;
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
            Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        }
        else
        {
            gu8_setting_ice_first_test_input = 1;
        }
    }

    if(gu8_setting_ice_lock_test_input == 1)
    {
        Bit1_Front_Led_Ice_Lock = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Under_Icon_Led_Ice_Lock = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Right_Led_Wifi_Icon_White = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = F_cds_detect & F_Wink_500ms;
        Bit0_Front_New_Led_Ice_Making_Text = F_cds_detect & F_Wink_500ms;

        bit_ice_lock_test_finish = SET;
    }
    else
    {
        if( bit_ice_lock_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Lock = SET;
            Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
            Bit0_Front_New_Led_Ice_Making_Text = SET;
        }
        else
        {
            gu8_setting_ice_lock_test_input = 1;
            Bit2_Front_Right_Led_Wifi_Icon_Blue = F_cds_detect & F_Wink_500ms;
        }
    }

    if(gu8_setting_hot_lock_test_input == 1)
    {
        Bit2_Front_Led_Hot_Lock = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Under_Icon_Led_Hot_Lock = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Right_Led_Min_Left_Text = F_cds_detect & F_Wink_500ms;
        Bit1_Front_New_Led_Hot_Heating_Text = F_cds_detect & F_Wink_500ms;

        bit_hot_lock_test_finish = SET;
    }
    else
    {
        if( bit_hot_lock_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Lock = SET;
            Bit2_Front_Under_Icon_Led_Hot_Lock = SET;
            Bit4_Front_Right_Led_Min_Left_Text = SET;
            Bit1_Front_New_Led_Hot_Heating_Text = SET;
        }
        else
        {
            gu8_setting_hot_lock_test_input = 1;
        }
    }



    if(gu8_setting_touch_lock_test_input == 1)
    {
        Bit3_Front_Led_Touch_Lock = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Under_Led_Ice_Full = F_cds_detect & F_Wink_500ms;
        Bit2_Front_New_Led_Cold_Cooling_Text = F_cds_detect & F_Wink_500ms;

        gu8_hot_temp_off_timer++;

        if( gu8_hot_temp_off_timer <= 3 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else if( gu8_hot_temp_off_timer <= 6 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else if( gu8_hot_temp_off_timer <= 9 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else
        {
            gu8_hot_temp_off_timer = 10;
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = F_cds_detect & F_Wink_500ms;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = F_cds_detect & F_Wink_500ms;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = F_cds_detect & F_Wink_500ms;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = F_cds_detect & F_Wink_500ms;
        }

        bit_touch_lock_test_finish = SET;
    }
    else
    {
        if( bit_touch_lock_test_finish == CLEAR )
        {
            Bit3_Front_Led_Touch_Lock = SET;
            Bit5_Front_Under_Led_Ice_Full = SET;
            Bit2_Front_New_Led_Cold_Cooling_Text = SET;

            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            gu8_hot_temp_off_timer = 0;
        }
        else
        {
            gu8_setting_touch_lock_test_input = 1;
        }
    }

    if(gu8_setting_eco_mode_test_input == 1)
    {
        Bit4_Front_Led_Eco_Mode = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Left_Led_Eco_Icon = F_cds_detect & F_Wink_500ms;
        Bit3_Front_New_Led_Low_Water_Text = F_cds_detect & F_Wink_500ms;

        gu8_cup_level_off_timer++;

        if( gu8_cup_level_off_timer <= 3 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 6 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 9 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 12 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else
        {
            gu8_cup_level_off_timer = 13;
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = F_cds_detect & F_Wink_500ms;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = F_cds_detect & F_Wink_500ms;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = F_cds_detect & F_Wink_500ms;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = F_cds_detect & F_Wink_500ms;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = F_cds_detect & F_Wink_500ms;
        }

        bit_eco_test_finish = SET;
    }
    else
    {
        if( bit_eco_test_finish == CLEAR )
        {
            Bit4_Front_Led_Eco_Mode = SET;
            Bit3_Front_Left_Led_Eco_Icon = SET;
            Bit3_Front_New_Led_Low_Water_Text = SET;

            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            gu8_cup_level_off_timer = 0;

        }
        else
        {
            gu8_setting_eco_mode_test_input = 1;
        }
    }


    if(gu8_water_ext_test_input == 1)
    {
        gu8_water_color_change_timer++;

        if( gu8_water_color_change_timer <= 5 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else if( gu8_water_color_change_timer <= 10 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else if( gu8_water_color_change_timer <= 15 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else
        {
            gu8_water_color_change_timer = 16;
            Bit4_Front_Under_Led_Water_Extract = F_cds_detect & F_Wink_500ms;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
            bit_water_extract_test_finish = SET;
        }
    }
    else
    {
        if( bit_water_extract_test_finish == CLEAR )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
        }
        else
        {
            gu8_water_ext_test_input = 1;
        }
    }


    if(gu8_ice_ext_test_input == 1)
    {
        Bit3_Front_Under_Led_Ice_Extract = F_cds_detect & F_Wink_500ms;

        bit_ice_extract_test_finish = SET;
    }
    else
    {
        if( bit_ice_extract_test_finish == CLEAR )
        {
            Bit3_Front_Under_Led_Ice_Extract = SET;
        }
        else
        {
            gu8_ice_ext_test_input = 1;
        }
    }
}

#if 0
void display_test_tds(void)
{
    F_TDS_ON = SET;

    gu16_tds_test_timer++;

    if( gu16_tds_test_timer >= 110 )
    {
        gu16_tds_test_timer = 110;
    }
    else{}

    if( bit_display_test_filter_reed_error == CLEAR && F_cds_detect == 0 && gu16_tds_test_timer >= 110 )
    {
        gu16_display_tds_in_max = gu16_uart_test_pulse;
        gu16_display_tds_out_max = gu16_AD_Result_TDS_Out_Data;
    }
    else
    {
        gu16_display_tds_in_max = 0;
        gu16_display_tds_out_max = 0;
    }
}
#endif



void display_test_error(void)
{
    pLEAKAGE_ON = CLEAR;

    /*..hui [23-12-7오후 3:38:44] 필터 3종 리드스위치 검사 후 디스플레이 검사모드 진입..*/
    switch( gu8_display_reed_test_step )
    {
        case 0:

            if( pREED_NEO_1_FILTER == CLEAR && pREED_RO_2_FILTER == CLEAR && pREED_INO_3_FILTER == CLEAR )
            {
                gu8_display_reed_test_timer++;

                if( gu8_display_reed_test_timer >= 2 )
                {
                    gu8_display_reed_test_timer = 0;
                    gu8_display_reed_test_step++;
                    bit_display_test_neo_filter = CLEAR;
                    bit_display_test_ro_filter = CLEAR;
                    bit_display_test_ino_filter = CLEAR;
                    play_melody_setting_on_198();

                    bit_display_test_neo_filter_old = CLEAR;
                    bit_display_test_ro_filter_old = CLEAR;
                    bit_display_test_ino_filter_old = CLEAR;
                }
                else{}
            }
            else
            {
                gu8_display_reed_test_timer = 0;

                if( pREED_NEO_1_FILTER == SET )
                {
                    if( bit_display_test_neo_filter == CLEAR )
                    {
                        bit_display_test_neo_filter = SET;
                        play_melody_warning_197();
                    }
                    else{}
                }
                else
                {
                    bit_display_test_neo_filter = CLEAR;
                }

                if( pREED_RO_2_FILTER == SET )
                {
                    if( bit_display_test_ro_filter == CLEAR )
                    {
                        bit_display_test_ro_filter = SET;
                        play_melody_warning_197();
                    }
                    else{}
                }
                else
                {
                    bit_display_test_ro_filter = CLEAR;
                }

                if( pREED_INO_3_FILTER == SET )
                {
                    if( bit_display_test_ino_filter == CLEAR )
                    {
                        bit_display_test_ino_filter = SET;
                        play_melody_warning_197();
                    }
                    else{}
                }
                else
                {
                    bit_display_test_ino_filter = CLEAR;
                }
            }

        break;

        case 1:

            if( pREED_NEO_1_FILTER == SET )
            {
                bit_display_test_neo_filter_old = SET;
                gu8_display_reed_test_timer = 0;
            }
            else
            {
                if( bit_display_test_neo_filter_old == SET )
                {
                    gu8_display_reed_test_timer++;

                    if( gu8_display_reed_test_timer >= 2 )
                    {
                        gu8_display_reed_test_timer = 0;
                        gu8_display_reed_test_step++;

                        bit_display_test_neo_filter = CLEAR;
                        bit_display_test_ro_filter = CLEAR;
                        bit_display_test_ino_filter = CLEAR;
                        play_melody_setting_on_198();

                        bit_display_test_ro_filter_old = CLEAR;
                    }
                    else{}
                }
                else{}
            }

        break;

        case 2:

            if( pREED_RO_2_FILTER == SET )
            {
                bit_display_test_ro_filter_old = SET;
                gu8_display_reed_test_timer = 0;
            }
            else
            {
                if( bit_display_test_ro_filter_old == SET )
                {
                    gu8_display_reed_test_timer++;

                    if( gu8_display_reed_test_timer >= 2 )
                    {
                        gu8_display_reed_test_timer = 0;
                        gu8_display_reed_test_step++;

                        bit_display_test_neo_filter = CLEAR;
                        bit_display_test_ro_filter = CLEAR;
                        bit_display_test_ino_filter = CLEAR;
                        play_melody_setting_on_198();

                        bit_display_test_ino_filter_old = CLEAR;
                    }
                    else{}
                }
                else{}
            }


        break;

        case 3:

            if( pREED_INO_3_FILTER == SET )
             {
                 bit_display_test_ino_filter_old = SET;
                 gu8_display_reed_test_timer = 0;
             }
             else
             {
                 if( bit_display_test_ino_filter_old == SET )
                 {
                     gu8_display_reed_test_timer++;

                     if( gu8_display_reed_test_timer >= 2 )
                     {
                         gu8_display_reed_test_timer = 0;
                         gu8_display_reed_test_step++;

                         bit_display_test_neo_filter = CLEAR;
                         bit_display_test_ro_filter = CLEAR;
                         bit_display_test_ino_filter = CLEAR;
                         play_melody_setting_on_198();
                     }
                     else{}
                 }
                 else{}
             }


        break;

        case 4:

            //
            bit_display_test_filter_reed_error = CLEAR;

        break;


        default:

            gu8_display_reed_test_step = 0;
            gu8_display_reed_test_timer = 0;

        break;
    }

    if( gu8_display_reed_test_step < 4 )
    {
        bit_display_test_filter_reed_error = SET;
        return;
    }
    else
    {
        bit_display_test_filter_reed_error = CLEAR;
    }


    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)
    {
        gu8_display_test_error = 1;
    }
    else if(gu16_AD_Result_Hot_Tank_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Tank_Temp >= TEMP_SENSOR_OPEN)
    {
        gu8_display_test_error = 2;
    }
    else if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)
    {
        gu8_display_test_error = 3;
    }
    else if( gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN
             || gu16_AD_Result_Amb_Side <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb_Side >= TEMP_SENSOR_OPEN )
    {
        /*..hui [23-12-20오전 9:53:19] 외기온도센서 1개 추가, 2개 다 정상일때만 정상..*/
        gu8_display_test_error = 4;
    }
    else if(gu16_AD_Result_Mixing_Out <= TEMP_SENSOR_SHORT || gu16_AD_Result_Mixing_Out >= TEMP_SENSOR_OPEN)
    {
        gu8_display_test_error = 5;
    }
    else if(pLEVEL_PURIFY_LOW == SET)
    {
        gu8_display_test_error = 6;
    }
    else if(pLEVEL_PURIFY_HIGH == SET)
    {
        gu8_display_test_error = 7;
    }
    else if(pLEVEL_ICE_DRAIN_LOW == SET)
    {
        gu8_display_test_error = 8;
    }
    else if(pLEVEL_ICE_DRAIN_HIGH == SET)
    {
        gu8_display_test_error = 9;
    }
    else if(gu16ADLeakage > 615)
    {
        gu8_display_test_error = 10;
    }
    /*else if(pREED_FILTER_COVER == CLEAR )*/
    /*else if(pREED_TANK_COVER == SET )*/
    else if(pREED_RO_2_FILTER == SET )
    {
        /*..hui [23-6-27오후 3:18:52] RO 필터 커버가 미 체결일 경우 에러 ero..*/
        gu8_display_test_error = 12;
    }
    else if(pREED_INO_3_FILTER == SET )
    {
        /*..hui [23-12-7오후 5:05:06] INO 필터 미 체결일 경우 에러 EIO..*/
        gu8_display_test_error = 14;
    }
    else if(pREED_NEO_1_FILTER == SET )
    {
        /*..hui [23-12-7오후 5:05:29] 네오 필터 미 체결일 경우 에러 EnO..*/
        gu8_display_test_error = 15;
    }
    else if( pREED_ACID == CLEAR )
    {
        /*..hui [24-7-18오후 4:07:35] 구연산 리드 감지되면 EcS..*/
        gu8_display_test_error = 16;
    }
    else
    {
        gu8_display_test_error = 0;
    }

    #if 0
    else if(gu16_AD_Result_TDS_In_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_TDS_In_Temp >= TEMP_SENSOR_OPEN)
    {
        /*..hui [24-7-18오후 4:11:58] TDS 입수 온도센서 불량 EIT..*/
        gu8_display_test_error = 17;
    }
    else if(gu16_AD_Result_TDS_Out_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_TDS_Out_Temp >= TEMP_SENSOR_OPEN)
    {
        /*..hui [24-7-18오후 4:12:18] TDS 출수 온도센서 불량 EIS..*/
        gu8_display_test_error = 18;
    }
    /*else if(gu16_display_tds_in_max >= 5 && gu16_display_tds_in_max <= 600)*/
    /*else if(gu16_display_tds_in_max >= 15 && gu16_display_tds_in_max <= 600)*/
    else if( gu16_display_tds_in_max >= 10 )
    {
        /*..hui [24-7-25오전 11:05:40] TDS 입수 센서 - EIS..*/
        /*..hui [24-8-12오후 3:33:34] 쇼트일경우 520..*/
        /*..hui [24-8-12오후 3:33:44] 10k 입력시 40정도..*/
        gu8_display_test_error = 19;
    }
    /*else if(gu16_display_tds_out_max >= 5 && gu16_display_tds_out_max <= 600)*/
    /*else if(gu16_display_tds_out_max >= 15 && gu16_display_tds_out_max <= 600)*/
    else if( gu16_display_tds_out_max >= 10 )
    {
        /*..hui [24-7-25오전 11:05:50] TDS 출수 센서 - EOS..*/
        /*..hui [24-8-12오후 3:35:11] 10k 연결돼있으면 105..*/
        /*..hui [24-8-12오후 3:38:31] 쇼트면 1000..*/
        gu8_display_test_error = 20;
    }
    else
    {
        gu8_display_test_error = 0;
    }
    #endif


    if(pREED_TANK_COVER == CLEAR )
    {
        if( bit_tank_cover_first_read == CLEAR )
        {
            bit_tank_cover_first_read = SET;
            /*..hui [23-7-5오후 5:46:07] 탑 커버 감지 시 에러 eto..*/
            //gu8_display_test_error = 11;
            bit_tank_cover_error = SET;
        }
        else{}
    }
    else
    {
        bit_tank_cover_first_read = SET;
        bit_tank_cover_error = CLEAR;
    }

    if( bit_tank_cover_error == SET )
    {
        gu8_display_test_error = 11;
    }
    else{}


    if(pREED_FILTER_COVER == CLEAR )
    {
        if( bit_side_cover_first_read == CLEAR )
        {
            bit_side_cover_first_read = SET;
            /*..hui [23-7-5오후 5:46:07] 사이드커버        감지 시 에러 efd..*/
            //gu8_display_test_error = 13;
            bit_side_cover_error = SET;
        }
        else{}
    }
    else
    {
        bit_side_cover_first_read = SET;
        bit_side_cover_error = CLEAR;
    }

    if( bit_side_cover_error == SET )
    {
        gu8_display_test_error = 13;
    }
    else{}

    //else
    //{
    //    gu8_display_test_error = 0;
    //}

    if( gu8_display_test_error != 0 )
    {
        if( bit_display_error_state == CLEAR )
        {
            bit_display_error_state = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        bit_display_error_state = CLEAR;

    }

    gu8_reed_first_read_timer++;

    if( gu8_reed_first_read_timer >= 30 )
    {
        gu8_reed_first_read_timer = 30;
        bit_tank_cover_first_read = SET;
        bit_side_cover_first_read = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10오후 1:09:30] 주기 10ms로 변경.. 제호 RO CT 기준..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22오후 5:01:06] 레드만 40%..*/
        gu8_rgb_red_on_time = 16;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 40;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22오후 5:02:02] 그린 40%, 블루 80%..*/
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 16;
        gu8_rgb_blue_on_time = 32;
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
void initial_all_data(void)
{
    if(gu8_initial_all_data == 1)
    {
        eeprom_initial();
        gu8_initial_all_data = 0;
        /*FactoryResetRtc();*/
        InitRtcTime();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



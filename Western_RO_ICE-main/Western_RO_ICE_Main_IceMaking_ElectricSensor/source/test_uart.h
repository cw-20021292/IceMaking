/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TEST_UART_H_
#define _TEST_UART_H_

//

extern void UARTest_NO_LOAD_Set(void);
extern void eeprom_initial(void);
extern void AT_UART_Communication(void);
extern void UARTest_RUN(void);
extern void calculate_tray_flow_input(void);
extern void calculate_filter_flow_input(void);

extern void start_drain_pump( U16 u16_data );
extern void stop_drain_pump( void );
extern void start_tray_pump( U16 u16_data );
extern void stop_tray_pump( void );
extern void input_ice_tray_micro_sw(void);
extern void check_error_micro_sw_movement(void);
extern void down_tray_motor(void);
extern void up_tray_motor(void);

extern void ControlGasSwitch(void);
extern void GasSwitchIce(void);
extern void GasSwitchInit(void);
extern void GasSwitchCold(void);
extern void GasSwitchHotGas(void);
extern void inverse_direction_time_check(void);
extern void BuzStep(U8 mu8Step);
extern void test_uart_rtc(void);
extern void eeprom_test(void);
//extern void InitRtcTime(void);
extern void led_blink_timer(void);
extern void initial_all_data(void);
extern void fnd_front_test_mode_(void);
extern void fnd_uart_test_mode_(void);
extern void on_all_control_led( void );
extern void off_all_control_led( void );
extern void display_test_error(void);
extern void fnd_left_display_test(void);
extern void fnd_right_display_test(void);

extern void WifiKey ( E_WIFI_KEY_T mu8Key );
extern void fnd_left_uart_test(void);
extern void fnd_right_uart_test(void);
extern void ControlRoDrain(void);
extern void run_open_ro_drain(void);
/*extern void ControlMixFlow(void);*/
/*extern void run_increase_flow( U16 mu16_move );*/
extern void comp_off(void);
extern void comp_on(void);
extern void Bldc_Comp_Communication(void);
extern void clear_bldc_buffer(void);
extern void all_breath_stop(void);

extern void set_duty_percent( U8 mu8_number, U8 mu8_percent );
extern void all_duty_100_percent(void);
extern U8 get_ice_mode_comp_rps(void);
extern U8 get_hotgas_mode_comp_rps(void);
extern U8 get_cold_mode_comp_rps(void);
extern void make_test_mode_rgb_color( U8 mu8_color );
extern void play_melody_select_196( void );
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_voice_test_mode_151( void );
extern void eeprom_test(void);
//extern void tds_out_control(void);





extern TYPE_BYTE          U8FrontTempHundredB;
#define            gu8_front_temp_fnd_hundred                  U8FrontTempHundredB.byte
#define            Bit0_Front_Temp_Fnd_Hundred_1               U8FrontTempHundredB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Hundred_2               U8FrontTempHundredB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Hundred_3               U8FrontTempHundredB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Hundred_4               U8FrontTempHundredB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Hundred_5               U8FrontTempHundredB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Hundred_6               U8FrontTempHundredB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Hundred_7               U8FrontTempHundredB.Bit.b6

extern TYPE_BYTE          U8FrontTempTenB;
#define            gu8_front_temp_fnd_ten                      U8FrontTempTenB.byte
#define            Bit0_Front_Temp_Fnd_Ten_1                   U8FrontTempTenB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Ten_2                   U8FrontTempTenB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Ten_3                   U8FrontTempTenB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Ten_4                   U8FrontTempTenB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Ten_5                   U8FrontTempTenB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Ten_6                   U8FrontTempTenB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Ten_7                   U8FrontTempTenB.Bit.b6

extern TYPE_BYTE          U8FrontTempOneB;
#define            gu8_front_temp_fnd_one                      U8FrontTempOneB.byte
#define            Bit0_Front_Temp_Fnd_One_1                   U8FrontTempOneB.Bit.b0
#define            Bit1_Front_Temp_Fnd_One_2                   U8FrontTempOneB.Bit.b1
#define            Bit2_Front_Temp_Fnd_One_3                   U8FrontTempOneB.Bit.b2
#define            Bit3_Front_Temp_Fnd_One_4                   U8FrontTempOneB.Bit.b3
#define            Bit4_Front_Temp_Fnd_One_5                   U8FrontTempOneB.Bit.b4
#define            Bit5_Front_Temp_Fnd_One_6                   U8FrontTempOneB.Bit.b5
#define            Bit6_Front_Temp_Fnd_One_7                   U8FrontTempOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8FrontAmountHundredB;
#define            gu8_front_amount_fnd_hundred                U8FrontAmountHundredB.byte
#define            Bit0_Front_Amount_Fnd_Hundred_1             U8FrontAmountHundredB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Hundred_2             U8FrontAmountHundredB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Hundred_3             U8FrontAmountHundredB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Hundred_4             U8FrontAmountHundredB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Hundred_5             U8FrontAmountHundredB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Hundred_6             U8FrontAmountHundredB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Hundred_7             U8FrontAmountHundredB.Bit.b6

extern TYPE_BYTE          U8FrontAmountTenB;
#define            gu8_front_amount_fnd_ten                    U8FrontAmountTenB.byte
#define            Bit0_Front_Amount_Fnd_Ten_1                 U8FrontAmountTenB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Ten_2                 U8FrontAmountTenB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Ten_3                 U8FrontAmountTenB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Ten_4                 U8FrontAmountTenB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Ten_5                 U8FrontAmountTenB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Ten_6                 U8FrontAmountTenB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Ten_7                 U8FrontAmountTenB.Bit.b6

extern TYPE_BYTE          U8FrontAmountOneB;
#define            gu8_front_amount_fnd_one                    U8FrontAmountOneB.byte
#define            Bit0_Front_Amount_Fnd_One_1                 U8FrontAmountOneB.Bit.b0
#define            Bit1_Front_Amount_Fnd_One_2                 U8FrontAmountOneB.Bit.b1
#define            Bit2_Front_Amount_Fnd_One_3                 U8FrontAmountOneB.Bit.b2
#define            Bit3_Front_Amount_Fnd_One_4                 U8FrontAmountOneB.Bit.b3
#define            Bit4_Front_Amount_Fnd_One_5                 U8FrontAmountOneB.Bit.b4
#define            Bit5_Front_Amount_Fnd_One_6                 U8FrontAmountOneB.Bit.b5
#define            Bit6_Front_Amount_Fnd_One_7                 U8FrontAmountOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8FrontSelectLEDB;
#define            gu8_front_select_led                        U8FrontSelectLEDB.byte
#define            Bit0_Front_Led_Set_Select                   U8FrontSelectLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Select                   U8FrontSelectLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Select                   U8FrontSelectLEDB.Bit.b2
#define            Bit3_Front_Led_Ambient_Select               U8FrontSelectLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Select                  U8FrontSelectLEDB.Bit.b4
#define            Bit5_Front_Led_Amount_Select                U8FrontSelectLEDB.Bit.b5

extern TYPE_BYTE          U8FrontNewTextLEDB;
#define            gu8_front_new_text_led                     U8FrontNewTextLEDB.byte
#define            Bit0_Front_New_Led_Ice_Making_Text         U8FrontNewTextLEDB.Bit.b0
#define            Bit1_Front_New_Led_Hot_Heating_Text        U8FrontNewTextLEDB.Bit.b1
#define            Bit2_Front_New_Led_Cold_Cooling_Text       U8FrontNewTextLEDB.Bit.b2
#define            Bit3_Front_New_Led_Low_Water_Text          U8FrontNewTextLEDB.Bit.b3
#define            Bit4_Front_New_Led_Replace_Filter_Text     U8FrontNewTextLEDB.Bit.b4
#define            Bit5_Front_New_Led_Replace_Filter_1_Num    U8FrontNewTextLEDB.Bit.b5
#define            Bit6_Front_New_Led_Replace_Filter_2_Num    U8FrontNewTextLEDB.Bit.b6
#define            Bit7_Front_New_Led_Replace_Filter_3_Num    U8FrontNewTextLEDB.Bit.b7



extern TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Lock                     U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Touch_Lock                   U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Eco_Mode                     U8FrontSettingLEDB.Bit.b4    //


extern TYPE_BYTE          U8FrontUnderIconLEDB;
#define            gu8_front_under_icon_led                    U8FrontUnderIconLEDB.byte
#define            Bit0_Front_Under_Txt_Led_Ice_First          U8FrontUnderIconLEDB.Bit.b0
#define            Bit1_Front_Under_Icon_Led_Ice_Lock          U8FrontUnderIconLEDB.Bit.b1
#define            Bit2_Front_Under_Icon_Led_Hot_Lock          U8FrontUnderIconLEDB.Bit.b2
#define            Bit3_Front_Under_Led_Ice_Extract            U8FrontUnderIconLEDB.Bit.b3
#define            Bit4_Front_Under_Led_Water_Extract          U8FrontUnderIconLEDB.Bit.b4
#define            Bit5_Front_Under_Led_Ice_Full               U8FrontUnderIconLEDB.Bit.b5





extern TYPE_BYTE          U8FrontUVCareLEDB;
#define            gu8_front_uv_care_txt_led                   U8FrontUVCareLEDB.byte
#define            Bit0_Front_Led_Ice_Tank_Clean_Text          U8FrontUVCareLEDB.Bit.b0
#define            Bit1_Front_Led_UV_Care_Txt_Under_bar        U8FrontUVCareLEDB.Bit.b1
#define            Bit2_Front_Led_Water_Tank_Text              U8FrontUVCareLEDB.Bit.b2
#define            Bit3_Front_Led_Ice_Tray_Text                U8FrontUVCareLEDB.Bit.b3
#define            Bit4_Front_Led_Ice_Tank_Text                U8FrontUVCareLEDB.Bit.b4



extern TYPE_BYTE          U8FrontLeftLEDB;
#define            gu8_front_left_led                          U8FrontLeftLEDB.byte
#define            Bit0_Front_Left_Led_Preparing_Text          U8FrontLeftLEDB.Bit.b0
#define            Bit1_Front_Left_Led_Current_Text            U8FrontLeftLEDB.Bit.b1
#define            Bit2_Front_Left_Led_Filter_Flushing_Text    U8FrontLeftLEDB.Bit.b2
#define            Bit3_Front_Left_Led_Eco_Icon                U8FrontLeftLEDB.Bit.b3
#define            Bit4_Front_Left_Led_Fahrenheit_oF_Icon      U8FrontLeftLEDB.Bit.b4
#define            Bit5_Front_Left_Led_Percent_Icon            U8FrontLeftLEDB.Bit.b5
#define            Bit6_Front_Left_Led_Celcius_oC_Icon         U8FrontLeftLEDB.Bit.b6


extern TYPE_BYTE          U8FrontRightLEDB;
#define            gu8_front_right_led                         U8FrontRightLEDB.byte
#define            Bit0_Front_Right_Not_Used                   U8FrontRightLEDB.Bit.b0  //
#define            Bit1_Front_Right_Led_Wifi_Icon_White        U8FrontRightLEDB.Bit.b1
#define            Bit2_Front_Right_Led_Wifi_Icon_Blue         U8FrontRightLEDB.Bit.b2
#define            Bit3_Front_Right_Led_OZ_Text                U8FrontRightLEDB.Bit.b3
#define            Bit4_Front_Right_Led_Min_Left_Text          U8FrontRightLEDB.Bit.b4
#define            Bit5_Front_Right_Led_ml_Text                U8FrontRightLEDB.Bit.b5
#define            Bit6_Front_Right_Led_Days_Left_Text         U8FrontRightLEDB.Bit.b6

extern TYPE_BYTE          U8FrontTempSettingLEDB;
#define            gu8_front_temp_setting_bar_led              U8FrontTempSettingLEDB.byte
#define            Bit0_Front_Led_Temp_Setting_Bar_1_1         U8FrontTempSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Temp_Setting_Bar_1_2         U8FrontTempSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Temp_Setting_Bar_1_3         U8FrontTempSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Temp_Setting_Bar_1_4         U8FrontTempSettingLEDB.Bit.b3

extern TYPE_BYTE          U8FrontAmountSettingLEDB;
#define            gu8_front_amount_setting_bar_led            U8FrontAmountSettingLEDB.byte
#define            Bit0_Front_Led_Amount_Setting_Bar_2_1       U8FrontAmountSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Amount_Setting_Bar_2_2       U8FrontAmountSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Amount_Setting_Bar_2_3       U8FrontAmountSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Amount_Setting_Bar_2_4       U8FrontAmountSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Amount_Setting_Bar_Continue  U8FrontAmountSettingLEDB.Bit.b4

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
extern TYPE_DIMMING       U8DimmingPercentNo1;
#define            gu8_dimming_set_one                         U8DimmingPercentNo1.byte
#define            bit_0_3_setting_select                      U8DimmingPercentNo1.nibble.b0_3
#define            bit_4_7_ice_select                          U8DimmingPercentNo1.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo2;
#define            gu8_dimming_set_two                         U8DimmingPercentNo2.byte
#define            bit_0_3_hot_select                          U8DimmingPercentNo2.nibble.b0_3
#define            bit_4_7_ambient_select                      U8DimmingPercentNo2.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo3;
#define            gu8_dimming_set_three                       U8DimmingPercentNo3.byte
#define            bit_0_3_cold_select                         U8DimmingPercentNo3.nibble.b0_3
#define            bit_4_7_amount_select                       U8DimmingPercentNo3.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo4;
#define            gu8_dimming_set_four                        U8DimmingPercentNo4.byte
#define            bit_0_3_setting_ice_first                   U8DimmingPercentNo4.nibble.b0_3
#define            bit_4_7_setting_ice_lock                    U8DimmingPercentNo4.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo5;
#define            gu8_dimming_set_five                        U8DimmingPercentNo5.byte
#define            bit_0_3_setting_hot_lock                    U8DimmingPercentNo5.nibble.b0_3
#define            bit_4_7_setting_touch_lock                  U8DimmingPercentNo5.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo6;
#define            gu8_dimming_set_six                         U8DimmingPercentNo6.byte
#define            bit_0_3_setting_eco_mode                    U8DimmingPercentNo6.nibble.b0_3
#define            bit_4_7_no_6_not_used                       U8DimmingPercentNo6.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo7;
#define            gu8_dimming_set_seven                       U8DimmingPercentNo7.byte
#define            bit_0_3_preparing_txt                       U8DimmingPercentNo7.nibble.b0_3
#define            bit_4_7_current_txt                         U8DimmingPercentNo7.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo8;
#define            gu8_dimming_set_eight                       U8DimmingPercentNo8.byte
#define            bit_0_3_filter_flushing_txt                 U8DimmingPercentNo8.nibble.b0_3
#define            bit_4_7_eco_icon                            U8DimmingPercentNo8.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo9;
#define            gu8_dimming_set_nine                        U8DimmingPercentNo9.byte
#define            bit_0_3_oF_icon                             U8DimmingPercentNo9.nibble.b0_3
#define            bit_4_7_percent_icon                        U8DimmingPercentNo9.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo10;
#define            gu8_dimming_set_ten                         U8DimmingPercentNo10.byte
#define            bit_0_3_oC_icon                             U8DimmingPercentNo10.nibble.b0_3
#define            bit_4_7_no_10_not_used                      U8DimmingPercentNo10.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo11;
#define            gu8_dimming_set_eleven                      U8DimmingPercentNo11.byte
#define            bit_0_3_ice_tank_clean_txt                  U8DimmingPercentNo11.nibble.b0_3
#define            bit_4_7_uv_care_under_bar_txt               U8DimmingPercentNo11.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo12;
#define            gu8_dimming_set_twelve                      U8DimmingPercentNo12.byte
#define            bit_0_3_wifi_blue_icon                      U8DimmingPercentNo12.nibble.b0_3
#define            bit_4_7_water_tank_txt                      U8DimmingPercentNo12.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo13;
#define            gu8_dimming_set_thirteen                    U8DimmingPercentNo13.byte
#define            bit_0_3_ice_tray_txt                        U8DimmingPercentNo13.nibble.b0_3
#define            bit_4_7_ice_tank_txt                        U8DimmingPercentNo13.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo14;
#define            gu8_dimming_set_fourteen                    U8DimmingPercentNo14.byte
#define            bit_0_3_wifi_white_icon                     U8DimmingPercentNo14.nibble.b0_3
#define            bit_4_7_oz_icon                             U8DimmingPercentNo14.nibble.b4_7



extern TYPE_DIMMING       U8DimmingPercentNo15;
#define            gu8_dimming_set_fifteen                     U8DimmingPercentNo15.byte
#define            bit_0_3_Min_Left_txt                             U8DimmingPercentNo15.nibble.b0_3
#define            bit_4_7_ml_txt                        U8DimmingPercentNo15.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo16;
#define            gu8_dimming_set_sixteen                     U8DimmingPercentNo16.byte
#define            bit_0_3_Days_Left_txt                              U8DimmingPercentNo16.nibble.b0_3
#define            bit_4_7_ice_first_txt                       U8DimmingPercentNo16.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo17;
#define            gu8_dimming_set_seventeen                   U8DimmingPercentNo17.byte
#define            bit_0_3_ice_lock_icon                       U8DimmingPercentNo17.nibble.b0_3
#define            bit_4_7_hot_lock_icon                       U8DimmingPercentNo17.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo18;
#define            gu8_dimming_set_eighteen                    U8DimmingPercentNo18.byte
#define            bit_0_3_ice_full_txt                        U8DimmingPercentNo18.nibble.b0_3
#define            bit_4_7_new_ice_making_txt                  U8DimmingPercentNo18.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////
extern TYPE_DIMMING       U8DimmingPercentNo19;
#define            gu8_dimming_set_nineteen                    U8DimmingPercentNo19.byte
#define            bit_0_3_new_hot_heating_txt                 U8DimmingPercentNo19.nibble.b0_3
#define            bit_4_7_new_cold_cooling_txt                U8DimmingPercentNo19.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo20;
#define            gu8_dimming_set_twenty                      U8DimmingPercentNo20.byte
#define            bit_0_3_new_low_water_txt                   U8DimmingPercentNo20.nibble.b0_3
#define            bit_4_7_new_replace_filter_txt              U8DimmingPercentNo20.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo21;
#define            gu8_dimming_set_twenty_one                  U8DimmingPercentNo21.byte
#define            bit_0_3_new_replace_filter_1_num            U8DimmingPercentNo21.nibble.b0_3
#define            bit_4_7_new_replace_filter_2_num            U8DimmingPercentNo21.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo22;
#define            gu8_dimming_set_twenty_two                  U8DimmingPercentNo22.byte
#define            bit_0_3_new_replace_filter_3_num            U8DimmingPercentNo22.nibble.b0_3
#define            bit_4_7_amount_bar_2_1                      U8DimmingPercentNo22.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo23;
#define            gu8_dimming_set_twenty_three                U8DimmingPercentNo23.byte
#define            bit_0_3_amount_bar_2_2                      U8DimmingPercentNo23.nibble.b0_3
#define            bit_4_7_amount_bar_2_3                      U8DimmingPercentNo23.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo24;
#define            gu8_dimming_set_twenty_four                 U8DimmingPercentNo24.byte
#define            bit_0_3_amount_bar_2_4                      U8DimmingPercentNo24.nibble.b0_3
#define            bit_4_7_amount_bar_continue                 U8DimmingPercentNo24.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo25;
#define            gu8_dimming_set_twenty_five                 U8DimmingPercentNo25.byte
#define            bit_0_3_temp_bar_1_1                        U8DimmingPercentNo25.nibble.b0_3
#define            bit_4_7_temp_bar_1_2                        U8DimmingPercentNo25.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo26;
#define            gu8_dimming_set_twenty_six                  U8DimmingPercentNo26.byte
#define            bit_0_3_temp_bar_1_3                        U8DimmingPercentNo26.nibble.b0_3
#define            bit_4_7_temp_bar_1_4                        U8DimmingPercentNo26.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo27;
#define            gu8_dimming_set_twenty_seven                U8DimmingPercentNo27.byte
#define            bit_0_3_left_seg_1_0_0                      U8DimmingPercentNo27.nibble.b0_3
#define            bit_4_7_left_seg_0_2_0                      U8DimmingPercentNo27.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo28;
#define            gu8_dimming_set_twenty_eight                U8DimmingPercentNo28.byte
#define            bit_0_3_left_seg_0_0_3                      U8DimmingPercentNo28.nibble.b0_3
#define            bit_4_7_right_seg_1_0_0                     U8DimmingPercentNo28.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo29;
#define            gu8_dimming_set_twenty_nine                 U8DimmingPercentNo29.byte
#define            bit_0_3_right_seg_0_2_0                     U8DimmingPercentNo29.nibble.b0_3
#define            bit_4_7_right_seg_0_0_3                     U8DimmingPercentNo29.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo30;
#define            gu8_dimming_set_thirty                      U8DimmingPercentNo30.byte
#define            bit_0_3_ice_extract                         U8DimmingPercentNo30.nibble.b0_3
#define            bit_4_7_water_extract                       U8DimmingPercentNo30.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_WORD          U16AnimationDimmingW;
#define            gu16_animation_dimming                                     U16AnimationDimmingW.word
#define            u8AnimationDimming_L                                       U16AnimationDimmingW.byte[0]
#define            u8AnimationDimming_H                                       U16AnimationDimmingW.byte[1]
#define            Bit0_Animation_Dimming_Water_Out_State                     U16AnimationDimmingW.Bit.b0
#define            Bit1_Animation_Dimming_Ice_Out_State                       U16AnimationDimmingW.Bit.b1
#define            Bit2_Animation_Dimming_Filter_Flushing_State               U16AnimationDimmingW.Bit.b2
#define            Bit3_Animation_Dimming_Current_State                       U16AnimationDimmingW.Bit.b3
#define            Bit4_Animation_Dimming_Preparing_State                     U16AnimationDimmingW.Bit.b4
#define            Bit5_Animation_Dimming_Ice_Tank_Clean_State                U16AnimationDimmingW.Bit.b5
#define            Bit6_Animation_Dimming_UV_Care_Under_Bar_State             U16AnimationDimmingW.Bit.b6
#define            Bit7_Animation_Dimming_Water_Tank_State                    U16AnimationDimmingW.Bit.b7
#define            Bit8_Animation_Dimming_Ice_Tray_State                      U16AnimationDimmingW.Bit.b8
#define            Bit9_Animation_Dimming_Ice_Tank_State                      U16AnimationDimmingW.Bit.b9
#define            Bit10_Animation_Dimming_Left_Seg_1_0_0_State               U16AnimationDimmingW.Bit.b10
#define            Bit11_Animation_Dimming_Left_Seg_0_2_0_State               U16AnimationDimmingW.Bit.b11
#define            Bit12_Animation_Dimming_Left_Seg_0_0_3_State               U16AnimationDimmingW.Bit.b12
#define            Bit13_Animation_Dimming_Right_Seg_1_0_0_State              U16AnimationDimmingW.Bit.b13
#define            Bit14_Animation_Dimming_Right_Seg_0_2_0_State              U16AnimationDimmingW.Bit.b14
#define            Bit15_Animation_Dimming_Right_Seg_0_0_3_State              U16AnimationDimmingW.Bit.b15


extern TYPE_WORD          U16AnimationDimmingTwoW;
#define            gu16_animation_dimming_two                                 U16AnimationDimmingTwoW.word
#define            u8AnimationDimmingTwo_L                                    U16AnimationDimmingTwoW.byte[0]
#define            u8AnimationDimmingTwo_H                                    U16AnimationDimmingTwoW.byte[1]
#define            Bit0_Animation_Dimming_oF_State                            U16AnimationDimmingTwoW.Bit.b0
#define            Bit1_Animation_Dimming_Percent_State                       U16AnimationDimmingTwoW.Bit.b1
#define            Bit2_Animation_Dimming_oC_State                            U16AnimationDimmingTwoW.Bit.b2
#define            Bit3_Animation_Dimming_Oz_State                            U16AnimationDimmingTwoW.Bit.b3
#define            Bit4_Animation_Dimming_Min_Left_State                      U16AnimationDimmingTwoW.Bit.b4
#define            Bit5_Animation_Dimming_Temp_Setting_Bar_1_1_State          U16AnimationDimmingTwoW.Bit.b5
#define            Bit6_Animation_Dimming_ml_State                            U16AnimationDimmingTwoW.Bit.b6
#define            Bit7_Animation_Dimming_Days_Left_State                     U16AnimationDimmingTwoW.Bit.b7
#define            Bit8_Animation_Dimming_Temp_Setting_Bar_1_2_State          U16AnimationDimmingTwoW.Bit.b8
#define            Bit9_Animation_Dimming_Temp_Setting_Bar_1_3_State          U16AnimationDimmingTwoW.Bit.b9
#define            Bit10_Animation_Dimming_Temp_Setting_Bar_1_4_State         U16AnimationDimmingTwoW.Bit.b10
#define            Bit11_Animation_Dimming_Amount_Setting_Bar_2_1_State       U16AnimationDimmingTwoW.Bit.b11
#define            Bit12_Animation_Dimming_Amount_Setting_Bar_2_2_State       U16AnimationDimmingTwoW.Bit.b12
#define            Bit13_Animation_Dimming_Amount_Setting_Bar_2_3_State       U16AnimationDimmingTwoW.Bit.b13
#define            Bit14_Animation_Dimming_Amount_Setting_Bar_2_4_State       U16AnimationDimmingTwoW.Bit.b14
#define            Bit15_Animation_Dimming_Amount_Setting_Bar_Continue_State  U16AnimationDimmingTwoW.Bit.b15


extern TYPE_BYTE          U8AnimationDimmingThreeB;
#define            gu8_animation_dimming_three                                U8AnimationDimmingThreeB.byte
#define            Bit0_Animation_Dimming_Settings_State                      U8AnimationDimmingThreeB.Bit.b0
#define            Bit1_Animation_Dimming_Ice_State                           U8AnimationDimmingThreeB.Bit.b1
#define            Bit2_Animation_Dimming_Hot_State                           U8AnimationDimmingThreeB.Bit.b2
#define            Bit3_Animation_Dimming_Three_Not_Use                       U8AnimationDimmingThreeB.Bit.b3
#define            Bit4_Animation_Dimming_Ambient_State                       U8AnimationDimmingThreeB.Bit.b4
#define            Bit5_Animation_Dimming_Cold_State                          U8AnimationDimmingThreeB.Bit.b5
#define            Bit6_Animation_Dimming_Three_Not_Use                       U8AnimationDimmingThreeB.Bit.b6
#define            Bit7_Animation_Dimming_Amount_State                        U8AnimationDimmingThreeB.Bit.b7

extern TYPE_BYTE          U8AnimationDimmingFourB;
#define            gu8_animation_dimming_four                                 U8AnimationDimmingFourB.byte
#define            Bit0_Animation_Dimming_Eco_State                           U8AnimationDimmingFourB.Bit.b0
#define            Bit1_Animation_Dimming_Wifi_State                          U8AnimationDimmingFourB.Bit.b1
#define            Bit2_Animation_Dimming_Four_Not_use                        U8AnimationDimmingFourB.Bit.b2
#define            Bit3_Animation_Dimming_Ice_First_State                     U8AnimationDimmingFourB.Bit.b3
#define            Bit4_Animation_Dimming_Ice_Full_State                      U8AnimationDimmingFourB.Bit.b4
#define            Bit5_Animation_Dimming_Ice_Lock_Icon_State                 U8AnimationDimmingFourB.Bit.b5
#define            Bit6_Animation_Dimming_Hot_Lock_Icon_State                 U8AnimationDimmingFourB.Bit.b6

extern TYPE_BYTE          U8AnimationDimmingFiveB;
#define            gu8_animation_dimming_five                                 U8AnimationDimmingFiveB.byte
#define            Bit0_Animation_Dimming_Setting_Ice_First_State             U8AnimationDimmingFiveB.Bit.b0
#define            Bit1_Animation_Dimming_Setting_Ice_Lock_State              U8AnimationDimmingFiveB.Bit.b1
#define            Bit2_Animation_Dimming_Setting_Hot_Lock_State              U8AnimationDimmingFiveB.Bit.b2
#define            Bit3_Animation_Dimming_Setting_Touch_Lock_State            U8AnimationDimmingFiveB.Bit.b3
#define            Bit4_Animation_Dimming_Setting_Eco_Mode_State              U8AnimationDimmingFiveB.Bit.b4


extern TYPE_BYTE          U8AnimationDimmingSixB;
#define            gu8_animation_dimming_six                                  U8AnimationDimmingSixB.byte
#define            Bit0_Animation_Dimming_New_Ice_Making_State                U8AnimationDimmingSixB.Bit.b0
#define            Bit1_Animation_Dimming_New_Hot_Heating_State               U8AnimationDimmingSixB.Bit.b1
#define            Bit2_Animation_Dimming_New_Cold_Cooling_State              U8AnimationDimmingSixB.Bit.b2
#define            Bit3_Animation_Dimming_New_Low_Water_State                 U8AnimationDimmingSixB.Bit.b3
#define            Bit4_Animation_Dimming_New_Replace_Filter_Txt_State        U8AnimationDimmingSixB.Bit.b4
#define            Bit5_Animation_Dimming_New_Replace_Filter_1_Num_State      U8AnimationDimmingSixB.Bit.b5
#define            Bit6_Animation_Dimming_New_Replace_Filter_2_Num_State      U8AnimationDimmingSixB.Bit.b6
#define            Bit7_Animation_Dimming_New_Replace_Filter_3_Num_State      U8AnimationDimmingSixB.Bit.b7

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3



extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                                    U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State                        U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State                       U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State                            U812VPowerControl.Bit.b2
#define            Bit3_Water_Tank_UV_12V_Out_State                     U812VPowerControl.Bit.b3
#define            Bit4_Ice_Tray_UV_12V_Out_State                       U812VPowerControl.Bit.b4
#define            Bit5_Ice_Tank_Front_UV_12V_Out_State                 U812VPowerControl.Bit.b5
#define            Bit6_Drain_Pump_FeedBack_12V_Out_State               U812VPowerControl.Bit.b6





extern U8 AT_gu8TX_ERROR;
extern bit AT_F_Rx_NG;
extern U16 gu16ADLeakage;
extern bit F_Uart_Final;
extern U16 gu16StepMotor2;
extern bit F_IceOpen;


extern U8 gu8_Room_Water_Level;

extern U16 gu16_AD_Result_Hot_Tank_Temp;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_AD_Result_Hot_Tank_Temp;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U16 gu16_AD_Result_Eva_First;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;
extern U16 gu16_AD_Result_Eva_Second;
extern U8 gu8_Eva_Ice_Temperature_One_Degree;
extern U16 gu16_AD_Result_Amb;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U16 gu16_AD_Result_Cold;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U16 gu16_AD_Result_Room;
extern U8 gu8_Room_Temperature_One_Degree;
extern U16 gu16ADIceFull;
extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;
extern U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current;
extern U16 gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
extern U16 gu16_AD_Result_DC_Current_12V;
extern U16 gu16_AD_Result_DC_Current_24V;
extern U16 gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
extern U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;

extern U8 gu8_Tray_Flow_1sec;
extern U8 gu8_Filter_Flow_1sec;


extern bit F_ErrTrayMotor_DualInital;
extern U8 gu8_GasSwitch_Status;

extern bit F_GasSwitch_Initial;
extern U8 gu8_GasSwitch_Mode;
extern bit F_Model_Select_Finish;
extern bit F_Overflow;

extern bit F_FW_Version_Display_Mode;

extern bit bit_adc_cold_start;
extern bit bit_adc_room_start;
extern U8 gu8IceTrayLEV;
extern bit F_TrayMotorDOWN;
extern bit F_TrayMotorUP;
extern bit F_Model_Select;

extern U8 gu8_setting_test_input;
extern U8 gu8_ice_test_input;
extern U8 gu8_hot_test_input;
extern U8 gu8_ambient_test_input;
extern U8 gu8_cold_test_input;
extern U8 gu8_amount_test_input;
extern U8 gu8_setting_ice_first_test_input;
extern U8 gu8_setting_ice_lock_test_input;
extern U8 gu8_setting_hot_lock_test_input;
extern U8 gu8_setting_touch_lock_test_input;
extern U8 gu8_setting_steam_off_test_input;
extern U8 gu8_setting_eco_mode_test_input;

extern U8 gu8_water_ext_test_input;
extern U8 gu8_ice_ext_test_input;


extern bit bit_setting_test_finish;
extern bit bit_ice_test_finish;
extern bit bit_hot_test_finish;
extern bit bit_ambient_test_finish;
extern bit bit_cold_tst_finish;
extern bit bit_amount_test_finish;
extern bit bit_ice_first_test_finish;
extern bit bit_ice_lock_test_finish;
extern bit bit_hot_lock_test_finish;
extern bit bit_touch_lock_test_finish;
extern bit bit_steam_off_test_finish;
extern bit bit_eco_test_finish;

extern bit bit_water_extract_test_finish;
extern bit bit_ice_extract_test_finish;


extern bit F_Wink_500ms;
extern bit F_cds_detect;
extern U8 gu8_uart_test_mode;
extern U8 gu8_initial_all_data;
extern U16 gu16_AD_Result_Fan_Current;



extern U8 gu8_display_test_error;
extern U8 gu8_hot_temp_off_timer;
extern U8 gu8_cup_level_off_timer;


extern U8 gu8_ro_drain_status;
extern U8 gu8_hot_flow_status;
extern U8 gu8_uart_comp_start;
extern U8 gu8_uart_comp_rps;
extern U8 gu8_bldc_target_hz;

extern S16 gs16_sm_info_target;
extern S16 gs16_sm_info_current;

extern U16 gu16_drain_pwm_out;
extern U16 gu16_current_tray_pwm;
extern U8 gu8_water_color_change_timer;

extern bit F_TDS_ON;
extern U16 gu16TDS_OUT_Pulse_Time;
extern U16 gu16TDS_IN_Pulse;
extern U16 gu16_AD_Result_TDS_Out_Data;
/////extern bit bit_drain_level_power_output;

#define UART_TEMP_SENSOR_ERROR    0xFF






#endif

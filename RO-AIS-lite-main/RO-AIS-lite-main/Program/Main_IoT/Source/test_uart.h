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
extern void calculate_flow_input(void);

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
extern void inverse_direction_time_check(void);
extern void BuzStep(U8 mu8Step);
extern void test_uart_rtc(void);
extern U8 eeprom_test(void);
//extern void InitRtcTime(void);
extern void led_blink_timer(void);
extern void initial_all_data(void);
extern void fnd_front_test_mode_(void);
extern void fnd_uart_test_mode_(void);
extern void on_all_control_led( void );
extern void off_all_control_led( void );
extern void fnd_manual_test_mode_(void);

extern void WifiKey ( E_WIFI_KEY_T mu8Key );
extern void SetWifiSystemStatus (E_WIFI_USER_VALUE_T mStatus, U8 mVal );
extern void ProcessRtc(void);

extern TYPE_BYTE          U8FrontThousandB;
#define            gu8_front_fnd_thousand                      U8FrontThousandB.byte
#define            Bit0_Front_Fnd_Thousand_1                   U8FrontThousandB.Bit.b0
#define            Bit1_Front_Fnd_Thousand_2                   U8FrontThousandB.Bit.b1

extern TYPE_BYTE          U8FrontHundredB;
#define            gu8_front_fnd_hundred                       U8FrontHundredB.byte
#define            Bit0_Front_Fnd_Hundred_1                    U8FrontHundredB.Bit.b0
#define            Bit1_Front_Fnd_Hundred_2                    U8FrontHundredB.Bit.b1
#define            Bit2_Front_Fnd_Hundred_3                    U8FrontHundredB.Bit.b2
#define            Bit3_Front_Fnd_Hundred_4                    U8FrontHundredB.Bit.b3
#define            Bit4_Front_Fnd_Hundred_5                    U8FrontHundredB.Bit.b4
#define            Bit5_Front_Fnd_Hundred_6                    U8FrontHundredB.Bit.b5
#define            Bit6_Front_Fnd_Hundred_7                    U8FrontHundredB.Bit.b6

extern TYPE_BYTE          U8FrontTenB;
#define            gu8_front_fnd_ten                           U8FrontTenB.byte
#define            Bit0_Front_Fnd_Ten_1                        U8FrontTenB.Bit.b0
#define            Bit1_Front_Fnd_Ten_2                        U8FrontTenB.Bit.b1
#define            Bit2_Front_Fnd_Ten_3                        U8FrontTenB.Bit.b2
#define            Bit3_Front_Fnd_Ten_4                        U8FrontTenB.Bit.b3
#define            Bit4_Front_Fnd_Ten_5                        U8FrontTenB.Bit.b4
#define            Bit5_Front_Fnd_Ten_6                        U8FrontTenB.Bit.b5
#define            Bit6_Front_Fnd_Ten_7                        U8FrontTenB.Bit.b6

extern TYPE_BYTE          U8FrontOneB;
#define            gu8_front_fnd_one                           U8FrontOneB.byte
#define            Bit0_Front_Fnd_One_1                        U8FrontOneB.Bit.b0
#define            Bit1_Front_Fnd_One_2                        U8FrontOneB.Bit.b1
#define            Bit2_Front_Fnd_One_3                        U8FrontOneB.Bit.b2
#define            Bit3_Front_Fnd_One_4                        U8FrontOneB.Bit.b3
#define            Bit4_Front_Fnd_One_5                        U8FrontOneB.Bit.b4
#define            Bit5_Front_Fnd_One_6                        U8FrontOneB.Bit.b5
#define            Bit6_Front_Fnd_One_7                        U8FrontOneB.Bit.b6


extern TYPE_BYTE          U8FrontExtractUVLEDB;
#define            gu8_front_extract_uv_led                    U8FrontExtractUVLEDB.byte
#define            Bit0_Front_Led_UV_Sterilization             U8FrontExtractUVLEDB.Bit.b0
#define            Bit1_Front_Led_Faucet                       U8FrontExtractUVLEDB.Bit.b1
#define            Bit2_Front_Led_Ice_Tank                     U8FrontExtractUVLEDB.Bit.b2
#define            Bit3_Front_Led_Ice_Extract                  U8FrontExtractUVLEDB.Bit.b3
#define            Bit4_Front_Led_Water_Extract                U8FrontExtractUVLEDB.Bit.b4
//#define            Bit5_Front_Led_Icon_All_Lock                U8FrontExtractUVLEDB.Bit.b5
#define            Bit5_Front_Led_Icon_ice_faucet			   U8FrontExtractUVLEDB.Bit.b5
#define            Bit6_Front_Led_Icon_Save                    U8FrontExtractUVLEDB.Bit.b6
#define            Bit7_Front_Led_Icon_Ice_First               U8FrontExtractUVLEDB.Bit.b7



extern TYPE_BYTE          U8FrontETCLEDB;
#define            gu8_front_etc_led                           U8FrontETCLEDB.byte
#define            Bit0_Front_Led_Cont                         U8FrontETCLEDB.Bit.b0
#define            Bit1_Front_Led_Pot                          U8FrontETCLEDB.Bit.b1
#define            Bit2_Front_Led_2_Cups                       U8FrontETCLEDB.Bit.b2
#define            Bit3_Front_Led_1_Cup                        U8FrontETCLEDB.Bit.b3
#define            Bit4_Front_Led_ml                           U8FrontETCLEDB.Bit.b4
#define            Bit5_Front_Led_Percent                      U8FrontETCLEDB.Bit.b5
//#define            Bit6_Front_Led_Auto_Drain                   U8FrontETCLEDB.Bit.b6
#define            Bit6_Front_Led_half_Cup					   U8FrontETCLEDB.Bit.b6 // Revised
#define            Bit7_Front_Led_Low_Water                    U8FrontETCLEDB.Bit.b7

extern TYPE_BYTE          U8FrontSelectLEDB;
#define            gu8_front_select_led                        U8FrontSelectLEDB.byte
#define            Bit0_Front_Led_Set_Select                   U8FrontSelectLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Select                   U8FrontSelectLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Select                   U8FrontSelectLEDB.Bit.b2
#define            Bit3_Front_Led_Ambient_Select               U8FrontSelectLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Select                  U8FrontSelectLEDB.Bit.b4
#define            Bit5_Front_Led_Amount_Select                U8FrontSelectLEDB.Bit.b5
#define            Bit6_Front_Led_Icon_Ice_Lock                U8FrontSelectLEDB.Bit.b6
#define            Bit7_Front_Led_Icon_Hot_Lock                U8FrontSelectLEDB.Bit.b7


extern TYPE_BYTE          U8FrontTempLEDB;
#define            gu8_front_temp_led                          U8FrontTempLEDB.byte
#define            Bit0_Front_Led_Hot_Temp_1                   U8FrontTempLEDB.Bit.b0
#define            Bit1_Front_Led_Hot_Temp_2                   U8FrontTempLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Temp_3                   U8FrontTempLEDB.Bit.b2
#define            Bit3_Front_Led_Cold_Temp_1                  U8FrontTempLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp_2                  U8FrontTempLEDB.Bit.b4
#define            Bit5_Front_Led_Cold_Temp_3                  U8FrontTempLEDB.Bit.b5
#define            Bit6_Front_Led_Ice_Full                     U8FrontTempLEDB.Bit.b6

extern TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Lock                     U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Eco_Mode                     U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp                    U8FrontSettingLEDB.Bit.b4
#define            Bit5_Front_Led_My_Cup                       U8FrontSettingLEDB.Bit.b5

//revised
extern TYPE_BYTE          U8TimeNWifiSettingLEDB;
#define            gu8_time_wifi_setting_led				   U8TimeNWifiSettingLEDB.byte
#define            Bit0_Time_Led_AM							   U8TimeNWifiSettingLEDB.Bit.b0
#define            Bit1_Time_Led_PM							   U8TimeNWifiSettingLEDB.Bit.b1
#define            Bit2_Time_Led_Colon						   U8TimeNWifiSettingLEDB.Bit.b2
#define            Bit3_Led_Wifi_Icon_White					   U8TimeNWifiSettingLEDB.Bit.b3
#define            Bit4_Led_Wifi_Icon_Blue					   U8TimeNWifiSettingLEDB.Bit.b4



//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


extern TYPE_DIMMING       U8DimmingNo1;
#define            gu8_dimming_set_ice_first                   U8DimmingNo1.byte
#define            bit_0_3_dimming_set_select                  U8DimmingNo1.nibble.b0_3
#define            bit_4_7_dimming_ice_select                  U8DimmingNo1.nibble.b4_7


extern TYPE_DIMMING       U8DimmingNo2;
#define            gu8_dimming_hot_ambient                     U8DimmingNo2.byte
#define            bit_0_3_dimming_hot_select                  U8DimmingNo2.nibble.b0_3
#define            bit_4_7_dimming_ambient_select              U8DimmingNo2.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo3;
#define            gu8_dimming_cold_amount                     U8DimmingNo3.byte
#define            bit_0_3_dimming_cold_select                 U8DimmingNo3.nibble.b0_3
#define            bit_4_7_dimming_amount_select               U8DimmingNo3.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo4;
#define            gu8_dimming_extract                         U8DimmingNo4.byte
#define            bit_0_3_dimming_ice_extract                 U8DimmingNo4.nibble.b0_3
#define            bit_4_7_dimming_water_extract               U8DimmingNo4.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo5;
#define            gu8_dimming_setting_etc                     U8DimmingNo5.byte
#define            bit_0_3_dimming_setting_menu                U8DimmingNo5.nibble.b0_3
#define            bit_4_7_dimming_etc_icon                    U8DimmingNo5.nibble.b4_7


extern TYPE_DIMMING       U8DimmingNo6;
#define            gu8_dimming_temp                            U8DimmingNo6.byte
#define            bit_0_3_dimming_hot_temp                    U8DimmingNo6.nibble.b0_3
#define            bit_4_7_dimming_cold_temp                   U8DimmingNo6.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo7;
#define            gu8_dimming_cont_pot                        U8DimmingNo7.byte
#define            bit_0_3_dimming_cont                        U8DimmingNo7.nibble.b0_3
#define            bit_4_7_dimming_pot                         U8DimmingNo7.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo8;
#define            gu8_dimming_2cups_1cup                      U8DimmingNo8.byte
#define            bit_0_3_dimming_2cups                       U8DimmingNo8.nibble.b0_3
#define            bit_4_7_dimming_1cup                        U8DimmingNo8.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo9;
#define            gu8_dimming_half_cups_colon					U8DimmingNo9.byte
#define            bit_0_3_dimming_half_cup						U8DimmingNo9.nibble.b0_3
#define            bit_4_7_dimming_colon						U8DimmingNo9.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo10;
#define            gu8_dimming_Am_Pm							U8DimmingNo10.byte
#define            bit_0_3_dimming_Am							U8DimmingNo10.nibble.b0_3
#define            bit_4_7_dimming_Pm							U8DimmingNo10.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo11;
#define            gu8_dimming_Wifi								U8DimmingNo11.byte
#define            bit_0_3_dimming_White						U8DimmingNo10.nibble.b0_3
#define            bit_4_7_dimming_Blue							U8DimmingNo10.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo12;
#define            gu8_dimming_fnd_2_1							U8DimmingNo12.byte
#define            bit_0_3_fnd_0_0_0_1							U8DimmingNo12.nibble.b0_3
#define            bit_4_7_fnd_0_0_2_0							U8DimmingNo12.nibble.b4_7

extern TYPE_DIMMING       U8DimmingNo13;
#define            gu8_dimming_fnd_4_3							U8DimmingNo13.byte
#define            bit_0_3_fnd_0_3_0_0							U8DimmingNo13.nibble.b0_3
#define            bit_4_7_fnd_4_0_0_0							U8DimmingNo13.nibble.b4_7

extern TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3

extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                     U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State         U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State        U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State             U812VPowerControl.Bit.b2
#define            Bit3_Faucet_UV_12V_Out_State          U812VPowerControl.Bit.b3
#define			   Bit4_Ice_Extraction_UV_12V_Out_State	 U812VPowerControl.Bit.b4
#define			   Bit5_Drain_Pump_12V_Out_State	 	 U812VPowerControl.Bit.b5





extern U8 AT_gu8TX_ERROR;
extern bit AT_F_Rx_NG;
extern U16 gu16IceMakingADVal;
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
extern U16 gu16_AD_Hot_Pump_Current;
extern U16 gu16_AD_Result_UV_Faucet_Current;
extern U16 gu16_AD_Result_UV_Ice_Tank_Current;

extern U8 gu8_Flow_1sec;
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
extern bit F_TrayMotorCCW;
extern bit F_TrayMotorCW;
extern bit F_Model_Select;
//extern bit bit_illumi_State;

extern U8 gu8_setting_test_input;
extern U8 gu8_ice_test_input;
extern U8 gu8_hot_test_input;
extern U8 gu8_ambient_test_input;
extern U8 gu8_cold_test_input;
extern U8 gu8_amount_test_input;
extern U8 gu8_setting_ice_first_test_input;
extern U8 gu8_setting_ice_lock_test_input;
extern U8 gu8_setting_hot_lock_test_input;
extern U8 gu8_setting_eco_mode_test_input;
extern U8 gu8_setting_cold_temp_test_input;
extern U8 gu8_setting_my_cup_test_input;

extern bit F_Wink_500ms;
extern bit F_cds_detect;
extern U8 gu8_uart_test_mode;
extern U8 gu8_initial_all_data;
extern U8 gu8_water_ext_test_input;
extern U8 gu8_ice_ext_test_input;
extern U16 gu16ADCds;
extern U16 gu16_AD_Result_Fan_Current;
extern bit bit_setting_test_finish;
extern bit bit_ice_test_finish;
extern bit bit_hot_test_finish;
extern bit bit_ambient_test_finish;
extern bit bit_cold_tst_finish;
extern bit bit_amount_test_finish;
extern bit bit_ice_first_test_finish;
extern bit bit_ice_lock_test_finish;
extern bit bit_hot_lock_test_finish;
extern bit bit_eco_test_finish;
extern bit bit_cold_temp_test_finish;
extern bit bit_my_cup_test_finish;

extern bit bit_water_extract_test_finish;
extern bit bit_ice_extract_test_finish;

extern S16 gs16_sm_info_target;
extern S16 gs16_sm_info_current;



extern U8 gu8_diff_second_rtc;
extern U8 gu8_diff_second_prev;
extern U8 gu8_diff_second_post;
extern U8 gu8_diff_min_rtc;
extern U8 gu8_diff_min_prev;
extern U8 gu8_diff_min_post;

extern U8 gu8_rtc_time_Sec;
extern U8 gu8_rtc_time_Min;

extern bit bit_sleep_mode_start;



#define UART_TEMP_SENSOR_ERROR    0xFF






#endif

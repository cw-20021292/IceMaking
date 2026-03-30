/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_LED_H_
#define _DISPLAY_LED_H_




//
extern void off_all_control_led( void );
extern void display_version( void );
extern void fnd_water_out(void);
extern void fnd_ice_out(void);
extern void display_setting(void);
extern void fnd_setting(void);
extern void fnd_error(void);
extern void fnd_normal_state(void);
extern U8 indicator_flick_timer(U8 flick_time, U8 interval);
extern U8 cold_off_flickering_timer(U8 flick_time, U8 interval);
extern U8 hot_off_flickering_timer(U8 flick_time, U8 interval);
extern void fnd_sleep(void);
extern void display_sleep(void);
extern void fnd_all_lock(void);
extern void display_all_lock(void);
extern void fnd_debug(void);
extern void fnd_altitude_setting(void);
extern void display_altitude_setting(void);
extern void fnd_memento(void);
extern void display_my_cup_setting(void);
extern void fnd_my_cup_setting_state(void);
extern U8 default_cup_set_flick_timer(U8 flick_time, U8 interval);
extern U8 low_water_flick_timer(U8 flick_time, U8 interval);
extern void fnd_button_set(void);
extern U8 ice_off_flickering_timer(U8 flick_time, U8 interval);
extern void led_button_set(void);
extern void fnd_time_set(void);
extern void led_time_set(void);

extern void fnd_wifi_set(void);
extern void led_wifi_pairing(void);
extern void wifi_icon_output(void);
extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );

extern void led_self_test_state(void);
extern void fnd_self_test_state(void);

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


extern TYPE_WORD          U16ETCDimmingSelW;
#define            u16ETCDimmingSel                            U16ETCDimmingSelW.word
#define            u8ETCDimmingSel_L                           U16ETCDimmingSelW.byte[0]
#define            u8ETCDimmingSel_H                           U16ETCDimmingSelW.byte[1]
#define            Bit0_Hot_Temp_1_2_3_Dimming_State           U16ETCDimmingSelW.Bit.b0
#define            Bit1_Cold_Temp_1_2_3_Dimming_State          U16ETCDimmingSelW.Bit.b1
#define            Bit2_UV_Care_Dimming_State                  U16ETCDimmingSelW.Bit.b2
#define            Bit3_Faucet_Dimming_State                   U16ETCDimmingSelW.Bit.b3
#define            Bit4_Ice_Tank_Dimming_State                 U16ETCDimmingSelW.Bit.b4
#define            Bit5_ml_Dimming_State                       U16ETCDimmingSelW.Bit.b5
#define            Bit6_Percent_Dimming_State                  U16ETCDimmingSelW.Bit.b6
#define            Bit7_Auto_Drain_Dimming_State               U16ETCDimmingSelW.Bit.b7
#define            Bit8_Low_Water_Dimming_State                U16ETCDimmingSelW.Bit.b8
#define            Bit9_Icon_Ice_Lock_Dimming_State            U16ETCDimmingSelW.Bit.b9
#define            Bit10_Icon_Hot_Lock_Dimming_State           U16ETCDimmingSelW.Bit.b10
#define            Bit11_Icon_All_Lock_Dimming_State           U16ETCDimmingSelW.Bit.b11
#define            Bit12_Icon_Save_Dimming_State               U16ETCDimmingSelW.Bit.b12
#define            Bit13_Ice_First_Dimming_State               U16ETCDimmingSelW.Bit.b13
#define            Bit14_Ice_Full_Dimming_State                U16ETCDimmingSelW.Bit.b14
#define            Bit15_Ice_faucet_Dimming_State              U16ETCDimmingSelW.Bit.b15


extern TYPE_BYTE          U8FNDDimmingselB;
#define            gu8_Dimming_seg							   U8FNDDimmingselB.byte
#define            Bit0_Seg_0_0_0_1_state					   U8FNDDimmingselB.Bit.b0
#define            Bit1_Seg_0_0_2_0_state					   U8FNDDimmingselB.Bit.b1
#define            Bit2_Seg_0_3_0_0_state					   U8FNDDimmingselB.Bit.b2
#define            Bit3_Seg_4_0_0_0_state					   U8FNDDimmingselB.Bit.b3


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

extern TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Eco_Set_Display                 U8SetDisplayB.Bit.b2
#define            Bit3_My_Cup_Set_Display              U8SetDisplayB.Bit.b3
#define            Bit4_My_Cup_Off_Display              U8SetDisplayB.Bit.b4

/*..sean [24-12-27] error일때에는 Colon 표시하지않도록 함..*/

extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error      U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error                 U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error          U32ControlErrorsD.Bit.b4    //E11
#define         Bit5_Hot_Heater_OverHeat_Error           U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Hot_Water_Flow_Block_Error          U32ControlErrorsD.Bit.b6    //E34
#define         Bit7_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b7    //E13
#define         Bit8_Feed_Valve_Error                    U32ControlErrorsD.Bit.b8    //E10
#define         Bit9_Room_Level_Unbalance_Error          U32ControlErrorsD.Bit.b9    //E14
#define         Bit10_Cold_Temp_Open_Short_Error         U32ControlErrorsD.Bit.b10   //E44
#define         Bit11_Amb_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b11   //E43
#define         Bit12_Drain_Pump_Error                   U32ControlErrorsD.Bit.b12   //E60
#define         Bit13_Tray_Micro_SW_Dual_Detect_Error    U32ControlErrorsD.Bit.b13   //E61
#define         Bit14_Tray_Micro_SW_Up_Move_Error        U32ControlErrorsD.Bit.b14   //E62
#define         Bit15_Tray_Micro_SW_Down_Move_Error      U32ControlErrorsD.Bit.b15   //E63
#define         Bit16_Eva_First_Temp_Open_Short_Error    U32ControlErrorsD.Bit.b16   //E63 - noerr
#define         Bit17_Eva_Second_Temp_Open_Short_Error   U32ControlErrorsD.Bit.b17   //E64 - noerr


extern TYPE_BYTE          U8PairingStepB;
#define            u8PairingStep                            U8PairingStepB.byte
#define            Bit0_Pairing_Step0_PrePare               U8PairingStepB.Bit.b0
#define            Bit1_Pairing_Step1_25_Percent            U8PairingStepB.Bit.b1
#define            Bit2_Pairing_Step2_50_Percent            U8PairingStepB.Bit.b2
#define            Bit3_Pairing_Step3_75_Percent            U8PairingStepB.Bit.b3
#define            Bit4_Pairing_Step_FINISH                 U8PairingStepB.Bit.b4
#define            Bit5_Pairing_Exit                        U8PairingStepB.Bit.b5
#define            Bit6_Pairing_Error                       U8PairingStepB.Bit.b6
#define            Bit7_Pairing_Forced_Exit                 U8PairingStepB.Bit.b7


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
extern bit bit_setting_mode_start;
extern U8 gu8_error_popup_enable;


extern bit F_IceOn;
extern bit F_Hot_Enable;
extern bit F_Cold_Enable;
extern bit F_Ice_Lock;
extern bit F_Hot_Lock;
extern U8 gu8HotTemp;
extern U8 gu8ColdTemp;
extern U8 gu8_Room_Water_Level;
extern bit F_DrainStatus;
extern U8 gu8_cup_led_select;
extern U8 gu8Cup_level;
extern LED_STEP gu8_Led_Display_Step;

extern U8 gu8_fnd_water_step;
extern U8 gu8_fnd_continue_step;
extern U8 gu8_fnd_ice_step;
extern U8 gu8_fnd_ice_timer;
extern U8 gu8_Error_Code;

extern bit F_IceFull;
extern bit bit_fast_ice_make;
extern bit F_WaterOut;
extern U8 gu8_cup_led_off_time;
extern U8 gu8_error_flick_timer;
extern U8 gu8_error_flick_cnt;
extern U8 u8Extract_Continue;
extern bit bit_uv_faucet_out;
extern bit bit_uv_ice_tank_out;
extern bit F_All_Lock;
//extern bit F_Save;
//extern bit bit_illumi_State;
extern bit bit_my_cup_setting_start;
extern bit bit_sleep_mode_start;
extern bit bit_my_cup_finish_flick;
extern U8 gu8_my_cup_extract_timer;

extern U8 gu8_default_cup_flick_state;
extern bit bit_default_cup_flick;
extern U8 gu8_durable_test_start;
extern bit F_Wink_500ms;
extern U16 gu16_durable_test_step;

extern bit bit_time_setting_start;

extern bit bit_uv_ice_extraction_out;

extern bit bit_sleep_mode_enable;


extern bit bit_display_last_error;

extern bit bit_display_wifi_error;


extern U8 gu8_rtc_time_Hour;      // 0 ~ 23
extern U8 gu8_rtc_time_Min;       // 0 ~ 59


extern U8 gu8_wifi_time_Hour;
extern U8 gu8_wifi_time_Min;
extern U8 gu8_wifi_time_Sec;

extern bit F_Key_IceExtraction;

extern bit F_Extract_Led_OnOff;

extern U16 gu16_water_select_return_time;

extern U16 gu16_wifi_pairing_30min_timer;
extern bit bit_pairing_5s_display_start;
extern U8 gu8_pairing_finish_timer;
extern U16 gu16_water_return_wifi_time;
#endif

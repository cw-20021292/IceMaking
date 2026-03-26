/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_ICE_EXT_
#define _KEY_INPUT_ICE_EXT_

//extern void power_saving_init(void);
extern void auto_drain_key_off_check(void);
extern void power_saving_init(void);
extern void PCB_Test_Mode_Ice_Key_Short_Input(void);
extern void BuzStep(U8 mu8Step);
extern void start_ice_lock_flick(void);
extern void start_all_lock_flick(void);
extern void stop_button_set_display( void );
extern void finish_filter_alarm(void);
extern void start_breath_steam_clean(void);
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_voice_all_lock_select_103( void );
extern void play_voice_eco_mode_ice_out_101( void );
extern void play_voice_short_ice_out_97( void );
extern void play_voice_ice_lock_ice_out_98( void );
extern void play_voice_ice_off_ice_out_99( void );
extern void play_voice_ice_off_ice_select_99( void );

extern void play_voice_ice_tank_clean_extract_60( void );
extern void play_voice_ice_error_10( void );
extern void play_voice_leakage_error_12( void );
extern void finish_pairing_screen(void);
extern void start_ice_off_flick(void);
extern void off_all_flick(void);



extern TYPE_BYTE          U8LedFlickerStateB;
#define            u8LedFlickerState                           U8LedFlickerStateB.byte
#define            Bit0_Ice_Lock_LED_Flick                U8LedFlickerStateB.Bit.b0
#define            Bit1_Ice_Lock_Extract_LED_Flick                U8LedFlickerStateB.Bit.b1
#define            Bit2_Hot_Water_Lock_LED_Flick                U8LedFlickerStateB.Bit.b2
#define            Bit3_All_Lock_Water_Extract_LED_Flick                U8LedFlickerStateB.Bit.b3





extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

extern TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6

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


extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error__E45            U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error__E49                       U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error__E21                U32ControlErrorsD.Bit.b4    //E21
#define         Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use         U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Main_Water_Flow_Block_Error__E09               U32ControlErrorsD.Bit.b6    //E09
#define         Bit7_BLDC_Communication_Error__E27                  U32ControlErrorsD.Bit.b7    //E27
#define         Bit8_BLDC_Operation_Error_Current_Sensing__E81      U32ControlErrorsD.Bit.b8    //E81
#define         Bit9_BLDC_Operation_Error_Starting_Fail__E82        U32ControlErrorsD.Bit.b9    //E82
#define         Bit10_BLDC_Operation_Error_Over_Current__E83        U32ControlErrorsD.Bit.b10   //E83
#define         Bit11_BLDC_Operation_Error_Overheat__E84            U32ControlErrorsD.Bit.b11   //E84
#define         Bit12_BLDC_Operation_Error_Disconnection_Comm__E85  U32ControlErrorsD.Bit.b12   //E85
#define         Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86    U32ControlErrorsD.Bit.b13   //E86
#define         Bit14_Cold_Temp_Open_Short_Error__E44               U32ControlErrorsD.Bit.b14   //E44
#define         Bit15_Amb_Temp_Open_Short_Error__E43                U32ControlErrorsD.Bit.b15   //E43
#define         Bit16_Drain_Pump_Error__E60                         U32ControlErrorsD.Bit.b16   //E60
#define         Bit17_Tray_Micro_SW_Dual_Detect_Error__E61          U32ControlErrorsD.Bit.b17   //E61
#define         Bit18_Tray_Micro_SW_Up_Move_Error__E62              U32ControlErrorsD.Bit.b18   //E62
#define         Bit19_Tray_Micro_SW_Down_Move_Error__E63            U32ControlErrorsD.Bit.b19   //E63
#define         Bit20_Mixing_Out_Temp_Open_Short_Error__E52         U32ControlErrorsD.Bit.b20   //E52
#define         Bit21_Amb_Side_Temp_Open_Short_Error__E53           U32ControlErrorsD.Bit.b21   //E53
#define         Bit22_Tray_In_Temp_Open_Short_Error__E41_Not_Use    U32ControlErrorsD.Bit.b22   //E56
#define         Bit23_Water_Tank_1_2_UV_Error__E74                  U32ControlErrorsD.Bit.b23   //E74
#define         Bit24_Ice_Tank_1_2_Back_UV_Error__E75               U32ControlErrorsD.Bit.b24   //E75
#define         Bit25_Ice_Tray_1_2_UV_Error__E76                    U32ControlErrorsD.Bit.b25   //E76
#define         Bit26_Ice_Tank_3_Front_UV_Error__E79                U32ControlErrorsD.Bit.b26   //E79
#define         Bit27_Tds_In_Temp_Open_Short_Error__E90             U32ControlErrorsD.Bit.b27   //E90
#define         Bit28_Tds_Out_Temp_Open_Short_Error__E91            U32ControlErrorsD.Bit.b28   //E91
#define         Bit29_Tds_In_Data_Error__E92                        U32ControlErrorsD.Bit.b29   //E92
#define         Bit30_Tds_Out_Data_Error__E93                       U32ControlErrorsD.Bit.b30   //E93






extern bit F_ExtractKeySet;
extern bit F_Ice_Lock;
//extern U8 gu8ICELockLEDFlick;
extern bit F_Ice;
//extern U8 gu8IceOut;
extern bit F_IceOutCCW;
extern bit F_NightNoUseSave;
extern bit F_IceOpen;
extern U8 gu8IceOutCCWInterval;
extern bit F_NoUseSave;
extern U8 gu8IceClose;
extern U16 gu16IceOutOff;
extern bit F_DayNoUseSave;
//extern U16 gu16IceOutTest;
//extern U8 gu8ErrIceMotor;
//extern U16 gu16NoWaterOut;

extern U8 gu8_ice_lock_flick_tmr;
extern U8 gu8_ice_ext_flick_tmr;
extern bit F_FW_Version_Display_Mode;
extern bit F_All_Lock;
extern U8 gu8_all_lock_flick_tmr;
extern bit F_Extraction_LED_Display_Mode;



//extern bit F_Overflow;
extern U8 gu8_Room_Water_Level;
//extern U8 gu8ColdLEV;
//extern bit F_ServiceSet;
extern bit F_CheckIceTray;
extern bit F_IceInit;


extern bit F_auto_drain_off_check;
extern U16 gu16IceDoorCloseResetTimer;
extern U16 gu16StepMotor2;

//extern bit F_IceOn;


extern bit F_WaterOut;
extern bit F_IR;
extern bit F_LineTest;


extern bit bit_ice_out_back_state;
extern bit F_IceOn;
extern bit bit_setting_mode_start;

extern bit bit_wake_up;

extern ICE_STER_MODE gu8_ice_ster_mode;
extern bit bit_ice_tank_ster_start;
extern FLUSHING_STEP gu8_flushing_mode;
extern LED_STEP gu8_Led_Display_Step;
extern U8 gu8_clear_block_error;
extern U8 gu8_fota_start;
extern bit F_Child_Lock;
extern bit bit_time_setting_start;
extern bit bit_filter_all;

extern U8 gu8_durable_test_start;
extern U16 gu16_durable_test_step;

extern bit bit_memento_start;
extern bit bit_sound_setting_start;
extern bit bit_wifi_pairing_start;
extern bit bit_sleep_mode_start;
extern bit bit_altitude_setting_start;
extern bit bit_self_test_start;
extern bit bit_ct_filter_type_start;
extern bit bit_acid_clean_start;
extern bit bit_bldc_operation_error_total;





#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_WATER_EXT_H_
#define _KEY_INPUT_WATER_EXT_H_


extern void PCB_Test_Mode_Extract_Key_Short_Input(void);
extern void auto_drain_key_off_check(void);
//extern void power_saving_init(void);
extern void power_saving_init(void);
extern void BuzStep(U8 mu8Step);
extern void start_all_lock_flick(void);
extern void start_my_cup_setting(void);
extern void halt_my_cup_setting(void);
extern void finish_my_cup_setting(void);
extern void start_low_water_flick(void);
extern void final_compensation_time(void);
extern void Pure_Temp_Compensation_time( void );
extern void calc_mix_water(void);
extern void stop_button_set_display( void );

extern void power_saving_init(void);
extern void SetWifiSystemStatus (E_WIFI_USER_VALUE_T mStatus, U8 mVal );

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


extern TYPE_BYTE          U8TrayPumpONB;
#define            u8TrayPumpON                              U8TrayPumpONB.byte
#define            Bit0_Ice_Tray_Water_Input_State          U8TrayPumpONB.Bit.b0
#define            Bit1_Safty_Ice_Melt_State                U8TrayPumpONB.Bit.b1





/*#define EXTRACT_TIME_CONTINUE                        1200*/

//#define EXTRACT_TIME_CONTINUE                        600
//#define EXTRACT_TIME_CONTINUE                        1800
//#define EXTRACT_TIME_CONTINUE                        1200
//#define EXTRACT_TIME_CONTINUE                        900
/*..hui [20-2-3오전 10:57:20] 퍼센트 계산을 위해 300ms 정도 여유줘야함..*/
#define EXTRACT_TIME_CONTINUE                        903


#define EXTRACT_TIME_CONTINUE_LINE_TEST              6000


//#define EXTRACT_TIME_COLD_DRAIN                      1800
//#define EXTRACT_TIME_COLD_DRAIN                      3000
//#define EXTRACT_TIME_COLD_DRAIN                      3600
/*..hui [20-2-3오전 10:57:20] 퍼센트 계산을 위해 300ms 정도 여유줘야함..*/
//#define EXTRACT_TIME_COLD_DRAIN                      3603


/*..hui [20-5-11오후 4:00:55] 5분으로 변경..*/
#define EXTRACT_TIME_COLD_DRAIN                      3003


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

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

extern TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Eco_Set_Display                 U8SetDisplayB.Bit.b2
#define            Bit3_My_Cup_Set_Display              U8SetDisplayB.Bit.b3
#define            Bit4_My_Cup_Off_Display              U8SetDisplayB.Bit.b4


extern bit F_WaterOut;
//extern bit F_Sterilization;
//extern bit F_SterProhibit;
extern bit F_LineTest;
//extern bit F_NfcTest;
extern bit F_RoomOut;
extern bit F_ColdOut;
extern bit F_HotOut;

extern U8 u8PcbTestEnableFlag;
extern bit F_FW_Version_Display_Mode;

extern bit F_All_Lock;
extern U8 gu8_all_lock_flick_tmr;
extern bit F_auto_drain_off_check;
//extern bit F_ServiceSet;

extern bit F_WaterOut_Disable_State;

extern bit F_Effluent_OK;

extern U8 gu8_Room_Water_Level;
extern U16 gu16_display_effnt_hz;


extern bit F_Tank_Cover_Input;
extern U8 gu8Cup_level;
extern U16 gu16Water_Extract_Timer;
extern U16 gu16_water_select_return_time;
extern bit F_HotWaterInit;

extern U16 gu16IceMakeTime;
extern bit F_IceInit;


extern bit F_Model_Select;
extern U8 gu8_extract_amount;
extern bit bit_setting_mode_start;
extern bit bit_wake_up;
extern U16 gu16_water_out_time;
extern bit bit_my_cup_setting_start;
extern U16 gu16_my_cup_setting_time;
extern bit bit_standby_input;
extern U16 gu16_my_cup_level_pure;
extern U16 gu16_my_cup_level_cold;
extern U16 gu16_my_cup_level_hot;
extern U8 gu8_error_popup_enable;
extern U8 gu8_compensation_time;
extern U8 gu8_durable_test_start;

extern U8 gu8_fota_start;
extern bit bit_self_test_start;

#endif

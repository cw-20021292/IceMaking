/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_CONTROL_H_
#define _DISPLAY_CONTROL_H_



//
extern void BuzStep(U8 mu8Step);

extern void led_display(void);
extern void sleep_mode_decesion(void);
extern void fnd_version(void);

extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2




extern TYPE_BYTE          U8CodyInspectOperationB;
#define            u8CodyInspectOperation                      U8CodyInspectOperationB.byte
#define            Bit0_Cody_Service_Kit_Start                 U8CodyInspectOperationB.Bit.b0
#define            Bit1_Empty_Tank_Start                       U8CodyInspectOperationB.Bit.b1
#define            Bit2_Ice_Tray_Test_Start                    U8CodyInspectOperationB.Bit.b2





extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

extern TYPE_BYTE          U8ButtonSetDisplayB;
#define            u8ButtonSetDisplay                   U8ButtonSetDisplayB.byte
#define            Bit0_Hot_Button_Set_Display          U8ButtonSetDisplayB.Bit.b0
#define            Bit1_Cold_Button_Set_Display         U8ButtonSetDisplayB.Bit.b1
#define            Bit2_Ice_Button_Set_Display          U8ButtonSetDisplayB.Bit.b2
#define            Bit2_cold_Temp_Set_Display           U8ButtonSetDisplayB.Bit.b3


//extern U8 gu8_system_depth;
extern bit bit_ice_tank_uv_start;
extern U8 gu8_uv_depth;
extern U16 gu16CompOffDelay;
extern bit F_Comp_Output;
extern bit F_IceInit;
extern bit F_Tank_Cover_Input;
extern U8 gu8_Room_Water_Level;
extern U8 gu8_elec_usage_proc;
extern bit F_Overflow;
extern U16 gu16ADCds;
extern bit F_Hot_Lock;
extern U8 gu8Cup_level_Default;
extern bit F_Model_Select;
extern bit F_All_Lock;
extern U8 gu8_memento_depth;
extern U8 gu8_product_info_depth;
extern U8 gu8_memento_max_num;
extern U8 u8Memento_Buff[];
extern bit bit_timer_expire;
extern bit F_ErrTrayMotor_DualInital;

extern U8 gu8_time_setting_popup;


extern U8 gu8_Wifi_Pairing_State;

extern bit bit_time_setting_start;

extern bit bit_uv_ice_extraction_out;

extern bit bit_self_test_start;
extern U8 gu8_fota_start;

#if 0
#define PROC_VERSION               0
#define PROC_POWR_OFF              1

#define PROC_NORMAL                2
#define PROC_EXTRACT               3
#define PROC_SETTING               4
#define PROC_CODY_INSPECT          5
#define PROC_DEVELOPER             6
#define PROC_POPUP                 7
#define PROC_DEBUG                 8
#define PROC_WIFI_PAIRING          9
#endif




#define PROC_START                 0
#define PROC_1                     1
#define PROC_2                     2
#define PROC_END                   3








extern bit F_WaterOut;
extern bit F_Ice;
extern bit F_Extract_Led_OnOff;
extern U8 gu8_timer_depth;
extern U8 gu8_report_depth;
//extern U8 gu8_water_using_depth;
//extern U8 gu8_cup_select_time_init;
extern bit F_Save;
extern U8 gu8_configuration_depth;

extern bit bit_date_setting_confirm;
extern bit bit_time_setting_confirm;
extern ICE_STEP gu8IceStep;
extern bit bit_setting_mode_start;
extern U8 gu8_Error_Code;
extern U8 gu8_error_popup_enable;
//extern bit bit_illumi_State;
extern bit bit_debug_mode_start;
extern bit bit_altitude_setting_start;
extern bit bit_memento_start;

extern bit bit_my_cup_setting_start;
extern bit bit_sleep_mode_start;

extern bit bit_wifi_pairing_start;
extern bit bit_sleep_mode_enable;

extern bit bit_9_hour_no_use_start;
extern bit bit_display_sleep_start;

#endif

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
extern void set_duty_percent( U8 mu8_number, U8 mu8_percent );
extern void all_duty_100_percent(void);
extern void fnd_left_front_version(void);
extern void fnd_right_main_version(void);







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

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

extern TYPE_BYTE          U8ButtonSetDisplayB;
#define            u8ButtonSetDisplay                   U8ButtonSetDisplayB.byte
#define            Bit0_Hot_Button_Set_Display          U8ButtonSetDisplayB.Bit.b0
#define            Bit1_Mute_Button_Set_Display         U8ButtonSetDisplayB.Bit.b1
#define            Bit2_Ice_Button_Set_Display          U8ButtonSetDisplayB.Bit.b2
#define            Bit3_Recover_Fast_Ice_Set_Display    U8ButtonSetDisplayB.Bit.b3






//extern U8 gu8_system_depth;
extern bit bit_ice_tank_uv_start;
extern U16 gu16CompOffDelay;
extern bit F_Comp_Output;
extern bit F_IceInit;
extern bit F_Tank_Cover_Input;
extern U8 gu8_Room_Water_Level;
extern U16 gu16ADCds;
extern bit F_Hot_Lock;
extern U8 gu8Cup_level_Default;
extern bit F_Model_Select;
extern bit F_All_Lock;
extern U8 u8Memento_Buff[];
extern bit F_ErrTrayMotor_DualInital;

extern U8 gu8_Wifi_Pairing_State;
extern bit bit_filter_cover;
extern U8 gu8_fota_start;
extern bit bit_ice_disp_pause;

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
extern U8 gu8_memento_display_num;
extern bit bit_setting_mode_start;
extern U8 gu8_Error_Code;
extern U8 gu8_error_popup_enable;
extern bit bit_debug_mode_start;
extern bit bit_ice_tank_ster_start;
extern U8 gu8_uv_popup_enable;
extern bit bit_uv_water_tank_out;
extern bit bit_uv_ice_tray_out;
extern bit bit_uv_ice_tank_out;
extern FLUSHING_STEP gu8_flushing_mode;
extern U8 gu8_filter_alarm_popup_enable;
extern bit bit_time_setting_start;
extern bit bit_filter_all;
extern bit bit_altitude_setting_start;


extern bit bit_sleep_mode_enable;
extern bit bit_sleep_mode_start;
extern bit bit_display_sleep_start;
extern bit bit_9_hour_no_use_start;
extern bit F_Child_Lock;
extern bit bit_hot_preheating_start;
extern U8 gu8_hot_prepare_stage;
extern bit bit_memento_start;
extern bit bit_sound_setting_start;
extern bit bit_wifi_pairing_start;
extern bit bit_self_test_start;
extern bit bit_ct_filter_type_start;
extern bit bit_ice_tray_making_enable;
extern bit bit_acid_clean_start;



#endif

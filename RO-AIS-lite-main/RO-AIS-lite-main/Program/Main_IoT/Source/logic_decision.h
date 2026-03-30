/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _LOGIC_DECISION_H_
#define _LOGIC_DECISION_H_

//
extern void BuzStep(U8 mu8Step);
extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );

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

extern bit F_Hot_Lock;
extern bit F_Cold_Enable;
extern bit F_WaterOut;
extern U8 gu8_Room_Water_Level;
extern bit F_WaterInit;
extern U8 gu8_develop_input_count;
extern U16 gu16_develop_key_clear_time;
extern bit F_HotWaterInit;
extern U8 gu8_user_led_off_time;
extern U8 gu8_cup_led_off_time;
extern U8 gu8_debug_input_count;
extern U16 gu16_debugp_key_clear_time;
extern bit bit_cold_first_op;
extern U8 u8Extract_Continue;
extern bit bit_hot_first_op;
extern bit bit_setting_mode_start;
extern bit bit_altitude_setting_start;
extern bit bit_my_cup_setting_start;
extern bit bit_flow_calc_first_op;

extern bit F_wifi_select_amount_init;
extern bit F_Ice;


#define PRE_WATER_DRAIN_RETURN_TIME    70
#define CUP_LEVEL_RETURN_TIME          70
#define USER_SELECT_RETURN_TIME        70


#define SETTING_MODE_EXIT_TIME         200


#endif

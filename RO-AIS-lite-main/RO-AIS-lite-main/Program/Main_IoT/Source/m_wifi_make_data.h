/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WIFI_MAKE_DATA_H_
#define _WIFI_MAKE_DATA_H_

//
extern void WifiSendData ( E_WIFI_DATA_T mu8Data );
extern void WifiSendDataControl ( E_WIFI_DATA_T mu8Data, U8 mu8IdData );
extern U16 GetUserSystemFunction ( U16 mu16Func );

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

extern TYPE_WORD          U16CompOnW;
#define            u16CompOn                               U16CompOnW.word
#define            u8CompOn_L                              U16CompOnW.byte[0]
#define            u8CompOn_H                              U16CompOnW.byte[1]
#define            Bit0_Cold_Mode_On_State                 U16CompOnW.Bit.b0
#define            Bit1_Ice_Make_On_State                  U16CompOnW.Bit.b1
#define            Bit2_Ice_Init_On_State                  U16CompOnW.Bit.b2
#define            Bit3_test_State                  U16CompOnW.Bit.b3

extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


//#define TEM_FAST_MODE_WATT                      30
///#define TEM_KEEP_MODE_WATT                      5


#define COMP_45HZ_UNDER_WATT                    8
#define COMP_60HZ_UNDER_WATT                    11
#define COMP_60HZ_OOVER_WATT                    12

#if 0
#define COMP_AMB_20_UNDER_ICE_55_WATT           15
#define COMP_AMB_20_UNDER_COLD_50_WATT          14
#define COMP_AMB_20__30_UNDER_ICE_70_WATT       19
#define COMP_AMB_20__30_UNDER_COLD_85_WATT      23
#define COMP_AMB_30_OVER_ICE_80_WATT            22
#define COMP_AMB_30_OVER_COLD_90_WATT           25
#endif

#if 0
#define COMP_AMB_20_UNDER_ICE_55_WATT           13
#define COMP_AMB_20_UNDER_COLD_50_WATT          12
#define COMP_AMB_20__30_UNDER_ICE_70_WATT       17
#define COMP_AMB_20__30_UNDER_COLD_85_WATT      21
#define COMP_AMB_30_OVER_ICE_80_WATT            20
#define COMP_AMB_30_OVER_COLD_90_WATT           23
#endif

#if 0
#define COMP_AMB_20_UNDER_ICE_55_WATT           10
#define COMP_AMB_20_UNDER_COLD_50_WATT          9
#define COMP_AMB_20__30_UNDER_ICE_70_WATT       12
#define COMP_AMB_20__30_UNDER_COLD_85_WATT      15
#define COMP_AMB_30_OVER_ICE_80_WATT            14
#define COMP_AMB_30_OVER_COLD_90_WATT           17
#endif

#if 0
#define COMP_ICE_80_WATT                        15
#define COMP_COLD_90_WATT                       17
#endif

#if 0
//#define COMP_ICE_80_WATT                        18
//#define COMP_COLD_90_WATT                       18
#endif

#define COMP_ICE_80_WATT                        16
#define COMP_COLD_90_WATT                       19





/*#define HOT_HEATER_WATT_FULL                    138*/
/*#define HOT_HEATER_WATT_FULL                    119*/
#define HOT_HEATER_WATT_FULL                      62

/*#define MAX_COMP_WATT                           4000*/
/*#define MAX_COMP_WATT                           8000*/
#define MAX_COMP_WATT                           6000


/*#define MAX_HOT_HEATER_WATT                     42000*/
#define MAX_HOT_HEATER_WATT                     36000
/*#define MAX_TOTAL_WATT                          46000*/
/*#define MAX_TOTAL_WATT                          40000*/
/*#define MAX_TOTAL_WATT                          44000*/
#define MAX_TOTAL_WATT                          42000



#define MAX_ICE_OUT_TIME                        90000




extern bit F_WaterOut;
extern U8 gu8_Error_Code;
extern bit bit_filter_cover;
extern bit F_Ice;
extern bit F_Comp_Output;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;
extern bit bit_9_hour_no_use_start;

extern U8 gu8_bldc_target_hz;
//extern bit bit_uv_water_tank_out;
extern bit bit_uv_ice_tank_out;
//extern bit bit_uv_ice_tray_out;
extern U8 gu8_hot_setting_temperature;
extern U8 gu8_Mixing_Out_Temperature_One_Degree;
extern bit F_Tank_Cover_Input;
//extern bit F_Heater_Output;
extern POWER_SAVING_STATE gu8_smart_operation_mode;
extern bit bit_filter_all;

extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_GasSwitch_Status;
extern bit bit_sleep_mode_start;
extern bit bit_self_test_start;
extern U8 gu8_self_test_manual_step;
extern U8 gu8_component_test_step;
            	/* ◎ */
// test용으로 extern 제거
extern U16 gu16_current_check_timer;
extern bit bit_flushing_water_start;
extern U8 gu8_wait_finish_step;
extern LED_STEP gu8_Led_Display_Step;
extern bit bit_uv_ice_tank_front_out;
 bit bit_ice_tray_making_enable;

 bit bit_uv_water_tank_out;
 bit bit_uv_ice_tray_out;
 extern bit F_Heater_Output;









#endif

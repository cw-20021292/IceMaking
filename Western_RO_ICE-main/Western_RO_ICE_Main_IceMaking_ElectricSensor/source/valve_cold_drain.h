/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _COLD_DRAIN_VALVE_OUTPUT_H_
#define _COLD_DRAIN_VALVE_OUTPUT_H_

//
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







extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3


extern TYPE_BYTE          U8TrayPumpOFFB;
#define            u8TrayPumpOFF                                   U8TrayPumpOFFB.byte
#define            Bit0_Tray_Pump_Low_Water_Off_State              U8TrayPumpOFFB.Bit.b0
#define            Bit1_Tray_Pump_Ster_Drain_Full_Off_State        U8TrayPumpOFFB.Bit.b1






extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3







extern bit F_DrainStatus;
extern bit F_Circul_Drain;
//extern bit F_HardError;

extern U8 gu8_over_ice_melt_proc;

//extern bit F_ErrColdLEV;
//extern bit F_ErrDrain;
extern bit F_Ice_Tray_Down_Move_Reset;
//extern bit F_LeakageError;
extern bit bit_manual_drain_valve_output;
extern bit bit_flushing_tank_start;
extern bit bit_tank_drain_valve_output;
extern FLUSHING_STEP gu8_flushing_mode;
extern bit bit_manual_drain_start;

extern U8 gu8_prepare_ster_step;

extern U8 gu8_hot_spray_step;
extern U16 gu16_hot_spray_timer;

extern U8 gu8_overheat_circul_step;
extern U16 gu16_overheat_circul_timer;

extern U8 gu8_lukewarm_spray_step;
extern U16 gu16_lukewarm_spray_timer;
extern U16 gu16_lukewarm_spray_max_timer;

extern U8 gu8_final_clean_step;
extern U16 gu16_final_clean_timer;
extern U16 gu16_final_clean_max_timer;
extern bit bit_ice_tank_ster_start;
extern ICE_STER_MODE gu8_ice_ster_mode;
extern U8 gu8_melt_ice_step;
extern U16 gu16_melt_ice_timer;
extern U8 gu8_melt_ice_prepare_step;

extern bit bit_tray_pump_output;
extern U8 gu8_ice_tray_clean_step;
extern U16 gu16_ice_tray_clean_timer;
extern bit bit_drain_error_check_enable;
extern U8 gu8_drain_pump_retry_step;

extern bit bit_acid_clean_start;
extern U8 gu8_acid_clean_step;
extern U32 gu32_acid_clean_timer;

extern ACID_CLEAN_STEP gu8_acid_clean_mode;
extern U8 gu8_acid_prepare_step;
extern U8 gu8_acid_change_filter_step;
extern U8 gu8_acid_wait_step;
extern U8 gu8_acid_rinse_step;
extern U8 gu8_acid_finish_step;
extern bit bit_acid_drain_valve_output;



/*#define ICE_STER_COLD_DRAIN_OPEN_TIME            50*/
#define ICE_STER_COLD_DRAIN_OPEN_TIME            70





#endif

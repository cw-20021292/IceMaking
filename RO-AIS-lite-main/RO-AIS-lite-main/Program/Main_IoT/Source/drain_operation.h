/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DRAIN_OP_H_
#define _DRAIN_OP_H_



//

extern void auto_drain_control(void);





extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3


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






extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                     U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State         U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State        U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State             U812VPowerControl.Bit.b2
#define            Bit3_Faucet_UV_12V_Out_State          U812VPowerControl.Bit.b3
#define			   Bit4_Ice_Extraction_UV_12V_Out_State	 U812VPowerControl.Bit.b4
#define			   Bit5_Drain_Pump_12V_Out_State	 	 U812VPowerControl.Bit.b5




extern U16 gu16_AD_Drain_Pump_Current;
//extern bit F_IceOn;
//extern bit F_ErrDrain;

extern bit F_auto_drain_mode_pump_out;
extern bit F_DrainStatus;
extern U8 gu8_room_level;
//extern U8 gu8ColdLEV;
//extern bit F_Overflow;
extern bit F_WaterOut;
extern U8 gu8_Room_Water_Level;
extern bit F_Tank_Cover_Input;
extern bit F_Overflow;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;


extern bit F_IceOn;
extern bit bit_first_drain;
extern bit F_FW_Version_Display_Mode;




//#define DRAIN_WATER_LEVEL_DETECT_TIME    30
#define DRAIN_PUMP_MAX_OP_TIME           30
#define DRAIN_PUMP_OFF_PROC              0
#define DRAIN_PUMP_ON_PROC               1
#define DRAIN_ERROR_PUMP_ON_10_MIN       6000
#define DRAIN_ERROR_PUMP_OFF_1_MIN       600
#define DRAIN_ERROR_PUMP_ON_2_MIN        1200
#define FORCED_DRAIN_ADDITIONAL_TIME     100

/*..hui [18-7-19오후 1:28:38] 드레인펌프 에러 감지 2회째부터 Full Duty 가동..*/
#define DRAIN_PUMP_MAX_OUTPUT_ERROR_COUNT      1


//#define PUMP_OVER_CURRENT_ADC                        250
#define PUMP_OVER_CURRENT_ADC                        100
//#define PUMP_OVER_CURRENT_ADC                        70
//#define PUMP_OVER_CURRENT_DETECT_TIME                50
#define PUMP_OVER_CURRENT_DETECT_TIME                30
//#define PUMP_OVER_CURRENT_DETECT_TIME                120
//#define PUMP_OVER_CURRENT_OFF_TIME                   10
#define PUMP_OVER_CURRENT_OFF_TIME                   20

#endif

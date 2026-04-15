/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _ICE_MAKING_H_
#define _ICE_MAKING_H_


//extern U8 CheckIceTray(void);
extern void down_tray_motor(void);
extern void up_tray_motor(void);
extern void ice_init_operation(void);
extern void GasSwitchIce(void);



extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3

extern TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                 U8MakeModeB.Bit.b1

extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2

extern TYPE_BYTE          U8CodyInspectOperationB;
#define            u8CodyInspectOperation                      U8CodyInspectOperationB.byte
#define            Bit0_Cody_Service_Kit_Start                 U8CodyInspectOperationB.Bit.b0
#define            Bit1_Empty_Tank_Start                       U8CodyInspectOperationB.Bit.b1
#define            Bit2_Ice_Tray_Test_Start                    U8CodyInspectOperationB.Bit.b2

extern TYPE_WORD          U16CompOffW;
#define            u16CompOff                              U16CompOffW.word
#define            u8CompOff_L                             U16CompOffW.byte[0]
#define            u8CompOff_H                             U16CompOffW.byte[1]
#define            Bit0_Restart_5min_Delay_State           U16CompOffW.Bit.b0
#define            Bit1_Max_90min_CutOff_State             U16CompOffW.Bit.b1
#define            Bit2_Safty_Routine_State                U16CompOffW.Bit.b2
#define            Bit3_Ice_Making_Err_State               U16CompOffW.Bit.b3
#define            Bit4_Hot_Water_COMP_Off_State           U16CompOffW.Bit.b4


extern bit F_ErrTrayMotor_DualInital;
extern U8 gu8_Room_Water_Level;
//extern bit F_HardError;
extern U16 gu16_AD_Result_Cold;
//extern bit F_Overflow;
extern bit F_Cold_Enable;
extern U16 gu16_AD_Result_Room;
extern U16 gu16_AD_Result_Eva_First;
extern U16 gu16_AD_Result_Amb;
extern bit F_SoftError;
extern bit F_SelectBar;
//extern bit F_NoSelectBar;
extern bit F_CristalIce;
//extern bit F_IceOn;
extern bit F_Safety_Routine;
extern U8 gu8HeaterOffDelay;
//extern bit F_ErrRoomLowLEV;
extern bit F_Ice;
//extern bit F_LeakageError;
extern bit F_FW_Version_Display_Mode;
//extern U16 gu16IceVVTime1;
//extern U8 gu8ColdWaterLEV;
extern U16 gu16IceOutOff;
//extern U16 gu16IceStopTime;
extern bit F_Ice_Tray_Down_Move_Reset;
extern U8 gu8_over_ice_melt_proc;
extern bit F_Safety_Routine;
//extern bit F_Fast_Ice_Make;
extern bit bit_first_ice_full;
extern U16 gu16CompOffDelay;
extern bit F_IceInit;
extern U16 gu16_Amb_Temperature;
extern U16 gu16_Room_Temperature;
extern bit F_WaterOut;
extern U8 gu8_GasSwitch_Status;
extern bit F_Comp_Output;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8IceTrayLEV;
extern bit F_IR;

extern U32 gu32_wifi_ice_heater_time;

/*..hui [20-10-14���� 4:14:19] �������� ���濡 ���� ����..*/
#define C_ICE_TRAY_FILL_200CC          1010
// #define C_ICE_TRAY_FILL_200CC          810      // 기존대비 80% 감소


#define ICE_MAKE_TIME     899                        /* �ܱ� 25'C, �ü� �µ� 25'C ���� */
#define WORK_ADC_OK_TIME  1800      // 제빙 최소시간 3분 @100ms



/*#define HEAT_TORAL_TIME_10_UNDER       5150*/
/*#define HEAT_TORAL_TIME_15_UNDER       5150*/
/*#define HEAT_TORAL_TIME_15_UNDER       8000*/
/*#define HEAT_TORAL_TIME_20_UNDER       3000*/

#define HEAT_TORAL_TIME_15_UNDER       11000
#define HEAT_TORAL_TIME_20_UNDER       4500
#define HEAT_TORAL_TIME_25_UNDER       3000
#define HEAT_TORAL_TIME_30_UNDER       2700
#define HEAT_TORAL_TIME_35_UNDER       2700
#define HEAT_TORAL_TIME_35_OVER        2700

extern U32 gu32_wifi_ice_make_time;


extern bit bit_self_test_start;

extern U8 Get_IsIceMakeTable(void);
extern U8 Get_IceMakeTableCount(void);
extern U8 Get_IsIceMakeAdc(void);
extern U8 Get_IceMakeAdcCount(void);

#define ICE_MAKE_METHOD_TABLE   1
#define ICE_MAKE_METHOD_ADC     2

extern void Record_IceMakeComplete(U8 mu8Method);
extern U8   Get_IceMakeHistory(U8 mu8Index);





#endif

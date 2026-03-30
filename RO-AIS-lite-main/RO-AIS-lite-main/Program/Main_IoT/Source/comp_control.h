/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _COMP_CONTROL_H_
#define _COMP_CONTROL_H_


//

extern void GasSwitchCold(void);



#define COMP_FIRST_TURN_ON_5MIN_TIME    3000
#define COMP_RESTART_DELAY_5MIN_TIME    3000
#define COMP_MID_TEMP_KEEP_TIME         900
#define COMP_STABLE_TIME                10
#define COMP_MAX_TURN_ON_150MIN_TIME    90000



extern TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                 U8MakeModeB.Bit.b1

extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2





extern U16 gu16IceMakeTime;
extern bit F_Safety_Routine;
extern bit F_ErrTrayMotor_DualInital;
extern bit F_IceInit;
extern U8 gu8_GasSwitch_Status;
extern bit F_WaterOut;
extern U8 gu8InitStep;
extern ICE_STEP gu8IceStep;
extern U8 gu8_Amb_Temperature_One_Degree;







#endif


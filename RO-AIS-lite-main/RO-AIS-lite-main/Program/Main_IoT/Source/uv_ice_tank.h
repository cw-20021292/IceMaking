/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _UV_ICE_TANK_H_
#define _UV_ICE_TANK_H_

//
extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2




extern bit F_Tank_Cover_Input;
extern bit F_Ice;
extern U16 gu16StepMotor2;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;
extern bit F_IceOn;
extern bit bit_self_test_start;


#define UV_MAX_OPERATION_UV_AUTO_OFF        1
#define UV_MAX_OPERATION_UV_AUTO_ON         3

#define UV_TANK_COVER_REED_DETECT_TIME      3


#endif

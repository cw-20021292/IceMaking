/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SWING_BAR_H_
#define _SWING_BAR_H_

//
extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2





extern bit F_ErrTrayMotor_DualInital;
//extern bit F_ColdDIR;
extern U16 gu16IceMakeTime;
extern bit F_Safety_Routine;
extern ICE_STEP gu8IceStep;

extern bit bit_self_test_start;


//#define CRISTAL_ON          6                      // 전자석 ON
//#define CRISTAL_OFF         4                      // 전자석 OFF

//#define CRISTAL_ON            4                      // 전자석 ON
//#define CRISTAL_OFF           2                      // 전자석 OFF

//#define CRISTAL_ON            2                      // 전자석 ON
//#define CRISTAL_OFF           4                      // 전자석 OFF

#define CRISTAL_ON            2                      // 전자석 ON
#define CRISTAL_OFF           6                      // 전자석 OFF



#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WATER_LEVEL_H_
#define _WATER_LEVEL_H_




extern bit F_ErrTrayMotor_DualInital;
//extern bit F_WaterInitSet;
//extern bit F_Overflow;
//extern bit F_ErrTrayMotor_Dual;
extern bit F_Feed;
//extern bit F_ColdVV;
//extern bit F_ColdWaterInit;




extern U8 gu8IceCount;
extern bit F_WaterInit;
//extern bit F_ErrPurify;
//extern bit F_ErrRoomLowLEV;
//extern bit F_ErrRoomLowLEV_D;
//extern U8 gu8DrainErrorRetrayDelay;
//extern bit F_IceWaterExt;
//extern bit F_ErrDrainSet;

//extern U16 gu16IceWaterExt;
//extern bit F_Drain_Retray;
//extern U16 gu16IceWaterExtMax;



//extern U8 gu8IceWaterExtDelay;
//extern bit F_ErrDrain;
//extern bit F_ErrDrain_D;
//extern bit F_ErrDrainSetFix;
//extern U8 gu8IceDrainError_CNT;
//extern bit F_Ext_cold;


/*#define DRAIN_WATER_LEVEL_DETECT_TIME    30*/
#define DRAIN_WATER_LEVEL_DETECT_TIME          20
#define DRAIN_LOW_WATER_LEVEL_CLEAR_TIME       15




#endif

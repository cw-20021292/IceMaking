/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_DEBUG_H_
#define _DISPLAY_DEBUG_H_

//
extern void fnd_out( U8 mu8_direct, U8 mu8_thousand, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  );


extern U16 gu16CompOffDelay;
extern U8 gu8_Flow_1sec;


extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;
extern U8 gu8_Eva_Ice_Temperature_One_Degree;
extern U16 gu16ADCds;
extern U16 gu16ADIceFull;
extern U16 gu16IceMakingADVal;
extern ICE_STEP gu8IceStep;


extern bit F_ErrTrayMotor_DualInital;
extern bit F_Ice_Tray_Up_Move_Reset;
extern bit F_Ice_Tray_Down_Move_Reset;

extern bit F_drain_water_level_low;
extern bit F_drain_water_level_high;




#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _AGING_H_
#define _AGING_H_

//
extern void key_cold_water_select_job(void);
extern void water_extract_key(void);
extern void key_ambient_water_select_job(void);
extern void key_hot_water_select_job(void);
extern void ice_extraction_finish(void);
extern void ice_extraction_start(void);



extern TYPE_BYTE          U8FeedValveONB;
#define            u8FeedValveON                         U8FeedValveONB.byte
#define            Bit0_Low_Water_Filling_State          U8FeedValveONB.Bit.b0
#define            Bit1_Feed_Valve_Flushing_State        U8FeedValveONB.Bit.b1
#define            Bit2_Feed_Valve_Water_Flushing_State  U8FeedValveONB.Bit.b2
#define            Bit3_Feed_Valve_Flushing_Tank_State   U8FeedValveONB.Bit.b3



extern U8 gu8_Error_Code;
extern bit F_FW_Version_Display_Mode;
extern U8 gu8_Room_Water_Level;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern bit F_WaterOut;









#endif

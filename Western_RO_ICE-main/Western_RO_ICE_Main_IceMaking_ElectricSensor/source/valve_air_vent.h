/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _VALVE_AIR_VENT_H_
#define _VALVE_AIR_VENT_H_

//


extern TYPE_BYTE          U8ColdDrainValveONB;
#define            u8ColdDrainValveON                      U8ColdDrainValveONB.byte
#define            Bit0_CD_Flushing_Tank_Drain_On_State    U8ColdDrainValveONB.Bit.b0
#define            Bit1_CD_Circul_Drain_On_State           U8ColdDrainValveONB.Bit.b1
#define            Bit2_CD_Manual_Drain_On_State           U8ColdDrainValveONB.Bit.b2
#define            Bit3_CD_Ice_Ster_On_State               U8ColdDrainValveONB.Bit.b3
#define            Bit4_CD_Drain_Retry_On_State            U8ColdDrainValveONB.Bit.b4
#define            Bit5_CD_Drain_Acid_On_State             U8ColdDrainValveONB.Bit.b5


extern bit bit_feed_output;
extern bit F_WaterOut;

extern U8 gu8_ice_tank_ster_step;
extern bit bit_ice_tank_ster_start;
extern ICE_STER_MODE gu8_ice_ster_mode;
extern U8 gu8_hot_spray_step;
extern U8 gu8_overheat_circul_step;
extern U8 gu8_lukewarm_spray_step;
extern U8 gu8_final_clean_step;
extern bit F_DrainStatus;
extern ICE_STEP gu8IceStep;

extern bit bit_manual_drain_start;

extern FLUSHING_STEP gu8_flushing_mode;
extern bit bit_flushing_start;
extern bit bit_flushing_tank_start;

extern bit bit_flushing_water_start;
extern U8 gu8_water_flushing_step;
extern U8 gu8_melt_ice_step;
extern U32 gu32_feed_overheat_on_timer;

extern bit bit_acid_clean_start;
extern U8 gu8_acid_clean_step;
extern U32 gu32_acid_clean_timer;

extern ACID_CLEAN_STEP gu8_acid_clean_mode;
extern U8 gu8_acid_prepare_step;
extern U8 gu8_acid_change_filter_step;
extern U8 gu8_acid_wait_step;
extern U8 gu8_acid_rinse_step;
extern U8 gu8_acid_finish_step;


#define AIR_VENT_DELAY_TIME             600


#define HIGH_LEVEL_FAULT_CHECK_TIME     132000


#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _FLUSHING_WATER_H_
#define _FLUSHING_WATER_H_

//
extern void run_open_ro_drain(void);
extern void run_close_ro_drain(void);


#define FLUSHING_WATER_DELAY_TIME                  5

#define PRE_WATER_FLUSHING_TIME      1800
#define RO_WATER_FLUSHING_TIME       30

#define NO_INPUT_WATER_6_HOUR        216000
#define NO_WATER_FLUSHING_24_HOUR    864000

extern U8 gu8_ro_drain_status;
extern bit bit_feed_output;

extern FLUSHING_STEP gu8_flushing_mode;
extern bit bit_filter_all;
extern bit bit_ice_tank_ster_start;
extern bit bit_self_test_start;
extern bit bit_acid_clean_start;







#endif

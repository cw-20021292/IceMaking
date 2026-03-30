/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_FND_SLEEP_H_
#define _DISPLAY_FND_SLEEP_H_


#define DISPLAY_SLEEP_TIME         6000

extern void no_use_save_init(void);



//extern bit bit_illumi_State;
extern bit F_WaterOut;
extern bit F_Ice;
extern bit bit_sleep_mode_enable;

extern bit bit_display_sleep_start;
extern U16 gu16_display_sleep_timer;

extern LED_STEP gu8_Led_Display_Step;
extern U16 gu16_current_time_total;
extern U16 gu16_start_time_total;
extern U16 gu16_finish_time_total;

extern U8 gu8_rtc_time_Hour;      // 0 ~ 23
extern U8 gu8_rtc_time_Min;       // 0 ~ 59
extern U8 gu8_rtc_time_Sec;       // 0 ~ 59

extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;

#endif

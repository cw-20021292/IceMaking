/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WIFI_SETTING_DATA_H_
#define _WIFI_SETTING_DATA_H_

//
extern void BuzStep(U8 mu8Step);
extern void water_select_return_timer_control( U8 mu8_flag );

extern void start_drain_pump( U16 u16_data );
extern void stop_drain_pump( void );
extern void start_tray_pump( U16 u16_data );
extern void stop_tray_pump( void );

/* ¡Ý */
extern void start_self_test(void);



#if 1
extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2
#endif

extern bit F_Hot_Lock;
extern bit F_All_Lock;
extern bit bit_child_lock_enable;
extern bit F_Mute_Enable;
extern bit F_Ice_Lock;
extern bit F_Hot_Enable;
extern U8 gu8AltitudeStep;
extern bit bit_fast_ice_make;
extern bit F_IceOn;
extern bit F_Extract_Led_OnOff;


extern U8 gu8_cup_level_order;
extern bit bit_sleep_mode_enable;
extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;
extern U8 gu8Cup_level_Default;
extern U8 gu8_fota_start;
extern U8 gu8_wifi_smart_unused_setting_time;

extern U8 gu8VoiceVolumeLevel;
extern U8 gu8Sound_Type;
extern U8 gu8_voice_language_type;

//extern bit bit_self_test_start;
extern bit bit_self_test_stop;
extern U8 gu8_wifi_self_test_progress;
extern U8 gu8_wifi_self_test_state;
extern U8 gu8_filter_change_type;
extern U8 gu8Cup_level;

extern bit F_Cold_Enable;

extern bit bit_self_test_start;
extern bit bit_self_test_stop;

#endif

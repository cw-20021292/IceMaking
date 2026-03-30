/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _EEPROM_H_
#define _EEPROM_H_

//extern U8 IsRtcBatBackUpMode(void);
extern U8 HAL_RTC_ByteWrite( U8 _dev, U16 _addr , U8 _data );
extern U8 HAL_RTC_PageWrite( U8 _dev, U16 _addr , U8 *_data, U8 _len );
extern U8 HAL_RTC_SeqRead( U8 _dev, U16 _addr , U8 * _data, U8 _len );






#define EEP_ADDR_OFFSET   0x0040




/*#define DEFAULT_SERVICE_MODE_DAY    91*/

#define DEFAULT_SERVICE_MODE_DAY    0



#define MAX_ERROR    100



#define EEPROM_CHECK_A_VALUE              0xAA
#define EEPROM_CHECK_B_VALUE              0x55


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2



extern bit F_SpecialSettingModeSeatDetect;
extern bit F_SpecialSettingModeAutoDrain;


extern U8 u8Memento_Buff[];
extern bit F_SpecialSettingModeEW;        /*..자동배수 설정..*/

extern bit F_FirstTwistMoveCheck;  /*..전원인가 후 원점제어를 할 것인지를 확인하는 플래그..*/
extern bit F_First_Turn_On_Check;
extern bit F_First_Turn_On_Load_Value;

extern bit F_Cold_Enable;
extern bit F_Hot_Enable;
extern bit F_Hot_Lock;

//extern bit F_Save;
extern bit F_Ice_Lock;
//extern bit F_IceOn;


extern U8 gu8AltitudeStep;
extern bit F_Circul_Drain;
extern U8 gu8Cup_level_Default;
//extern bit bit_eeprom_err;
extern bit F_All_Lock;

//extern U32	gu32ServiceTime;

extern U8 gu8_service_timer_1day;

extern bit F_Mute_Enable;

//extern bit F_Fast_Ice_Make;


extern bit F_Auto_UV_Control;
extern bit F_Extract_Led_OnOff;
extern U8 gu8_clock_theme;
extern U8 gu8_screen_bright;
extern U8 gu8_ice_setting;

extern U8 gu8_cold_setting_level;
extern U8 gu8Cup_level;

extern bit bit_fast_ice_make;
extern bit F_IceOn;


extern U16 gu16_my_cup_level_pure;
extern U16 gu16_my_cup_level_cold;
extern U16 gu16_my_cup_level_hot;

extern bit bit_my_cup_enable;
extern bit bit_temporary_no_operation;

extern bit bit_sleep_mode_enable;

extern bit F_Wifi_Power;

extern bit F_Wifi_First_Paring;
extern bit F_Wifi_Fota_MCU;
extern bit F_Wifi_Fota_MODULE;

extern bit F_Wifi_Power_Old;

extern bit F_Wifi_First_Paring_Old;

extern bit F_Wifi_Fota_MODULE_Old;

extern bit F_Wifi_Fota_MCU_Old;

extern U8 gu8_fota_start;

extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;

extern U8 gu8_fota_start;

#endif


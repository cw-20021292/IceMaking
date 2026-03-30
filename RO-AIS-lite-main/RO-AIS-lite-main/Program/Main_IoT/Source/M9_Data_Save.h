/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DATA_SAVE_H_
#define _DATA_SAVE_H_


extern void EepromByteWrite( U16 mu16Addr, U8 mu8Data );
extern void EepromPageWrite(U16 mu16Addr, U8 *pData, U8 mu8len );
extern void ErrorSave(void);
extern void ProcessRtc(void);






extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

extern bit F_Cold_Enable;
extern bit F_Hot_Enable;
extern bit F_Hot_Lock;
//extern bit F_Save;
extern bit F_Ice_Lock;
//extern bit F_IceOn;


extern U8 gu8AltitudeStep;
extern bit F_Circul_Drain;
extern U8 gu8Cup_level_Default;
extern bit bit_eeprom_err;
extern bit F_All_Lock;

//extern U32  gu32ServiceTime;
extern bit F_Extraction_LED_Display_Mode;
extern bit F_Extraction_LED_Display_Mode_Old;

extern bit F_Mute_Enable;
extern bit F_Mute_Enable_Old;

extern bit F_WaterOut_Change_State;

//extern bit F_Fast_Ice_Make_Old;
//extern bit F_Fast_Ice_Make;

extern U8 gu8_eeprom_wbuf[16];
extern U8 gu8_eeprom_rbuf[16];

extern bit F_Auto_UV_Control;

extern bit F_Rtc_Write;
//extern U8 gu8_system_depth;
extern U8 gu8_configuration_depth;

extern U8 gu8_service_timer_1day;
extern U8 gu8_service_timer_1day_old;





extern bit F_FW_Version_Display_Mode;
extern bit F_WaterOut;


extern U8 gu8_cold_setting_level;
extern U8 gu8_cold_setting_level_old;

extern bit bit_fast_ice_make;
extern bit F_IceOn;
extern U16 gu16_my_cup_level_pure;
extern U16 gu16_my_cup_level_cold;
extern U16 gu16_my_cup_level_hot;
extern bit bit_my_cup_enable;
extern bit bit_temporary_no_operation;

extern bit bit_sleep_mode_enable;
extern bit F_Wifi_Fota_MODULE;
extern bit F_Wifi_First_Paring;
extern bit F_Wifi_Fota_MCU;

extern bit bit_sleep_mode_enable;
extern U8 gu8_sleep_mode_start_hour;
extern U8 gu8_sleep_mode_start_minute;
extern U8 gu8_sleep_mode_finish_hour;
extern U8 gu8_sleep_mode_finish_minute;

extern U8 gu8_fota_start;
extern bit bit_first_time_setting;

#endif


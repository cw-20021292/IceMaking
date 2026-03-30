/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/

#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

/***********************************************************************************************************************/
#include    "WIFI_DefUser.h"

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/




#define FALSE   0
#define TRUE    1

#define STX    2     //SONIX2349
#define ETX    3
#define DATA_PACKET_MAX_LENGTH    35
#define PC_DATA_PACKET_MAX_LENGTH    5


#define SETTING_ENABLE     1
#define SETTING_DISABLE    0

#if 0
#define RESET       2
#define WAIT        3
#define START       4
#define RETRY       5
#endif

//#define CONFIG_WATER_AMOUNT_120ML		1
#define CONFIG_SLEEP_SAVING_MODE			1
#define	LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF	0
#define CONFIG_ICE_EFFLUENT_UV_CARE			1
#define CONFIG_WIFI_USE						1
#define CONFIG_TIME_SETTING					1
#define COFIG_EEPROM_AT24C02C_USE			0
#define CONFIG_RTC_EEPROM_ISL12026_USE		1

#define WIFI_PAIRING_START_30_MIN       18000

typedef enum
{
    LED_Display__VERSION = 0,
    LED_Display__MAIN,
    LED_Display__ALL_LOCK,
    LED_Display__WATER_EXTRACT,
    LED_Display__ICE_EXTRACT,
    LED_Display__SETTING,
    LED_Display__SLEEP,
    LED_Display__ERROR,
    LED_Display__DEBUG,
    LED_Display__SETTING_MY_CUP,
    LED_Display__ALTITUDE_SETTING,
    LED_Display__MEMENTO,
#if CONFIG_TIME_SETTING
	LED_Display__TIME_SETTING,
#endif
    LED_Display__BUTTON_SET,

    LED_Display__WIFI_PAIRING,
    LED_Display__FOTA_START,
    LED_Display__SELF_TEST
}LED_STEP;

#define LED_DIMMING_FULL           10


#define PAIRING_PROGRESS_0_PERCENT           0
#define PAIRING_PROGRESS_25_PERCENT          25
#define PAIRING_PROGRESS_50_PERCENT          50
#define PAIRING_PROGRESS_75_PERCENT          75
#define PAIRING_PROGRESS_100_PERCENT         100


typedef enum
{
    ICE_HEATER_CONTROL_OFF = 0,
    ICE_HEATER_CONTROL_15_UNDER,
    ICE_HEATER_CONTROL_20_UNDER,

    ICE_HEATER_CONTROL_25_UNDER,
    ICE_HEATER_CONTROL_30_UNDER,
    ICE_HEATER_CONTROL_35_UNDER,
    ICE_HEATER_CONTROL_35_OVER
}ICE_HEATER_CONTROL;



typedef enum
{
    STATE_0_STANDBY = 0,

    STATE_10_ICE_TRAY_MOVE_UP = 10,
    STATE_11_WAIT_ROOM_WATER_FULL = 11,
    STATE_12_CHECK_DRAIN_LEVEL = 12,

    STATE_20_WATER_IN_ICE_TRAY = 20,
    STATE_21_ICE_SWITCH_MOVE = 21,

    STATE_30_CALC_ICE_MAKING_TIME = 30,
    STATE_31_MAIN_ICE_MAKING = 31,

    STATE_40_ICE_TRAY_MOVE_DOWN = 40,
    STATE_41_ICE_TAKE_OFF = 41,

    STATE_50_ICE_FULL_IR_CHECK = 50,
    STATE_51_FINISH_ICE_MAKE = 51
}ICE_STEP;


typedef enum
{
    TEMP_DISPLAY_0_INIT,
    TEMP_DISPLAY_1_LOW,
    TEMP_DISPLAY_2_MID,
    TEMP_DISPLAY_3_HIGH

}TEMP_DISPLAY;

typedef enum
{
    DISPLAY_NUM_0,
    DISPLAY_NUM_1,
    DISPLAY_NUM_2,
    DISPLAY_NUM_3,
    DISPLAY_NUM_4,
    DISPLAY_NUM_5,
    DISPLAY_NUM_6,
    DISPLAY_NUM_7,
    DISPLAY_NUM_8,
    DISPLAY_NUM_9,

    DISPLAY_NUM_LARGE_A,
    DISPLAY_NUM_LARGE_F,
    DISPLAY_NUM_SMALL_u,
    DISPLAY_NUM_SMALL_n,
    DISPLAY_NUM_SMALL_o,
    DISPLAY_NUM_LARGE_P,
    DISPLAY_NUM_SMALL_r,
    DISPLAY_NUM_SMALL_t,
    DISPLAY_BAR,
    DISPLAY_NUM_LARGE_E,
    DISPLAY_NUM_LARGE_O,
    DISPLAY_NUM_LARGE_C,
    DISPLAY_NUM_LARGE_H,
    DISPLAY_NUM_SMALL_d,
    DISPLAY_NUM_LARGE_K,

    DISPLAY_NUM_CONTINUE_100,
    DISPLAY_NUM_CONTINUE_010,
    DISPLAY_NUM_CONTINUE_001,

    DISPLAY_NUM_SQUARE_UP,
    DISPLAY_NUM_SQUARE_DOWN,

    DISPLAY_OFF
}DISPLAY_DATA;


typedef enum
{
    DISPLAY_THOUSAND_OFF,
    DISPLAY_THOUSAND_UPPER,
    DISPLAY_THOUSAND_LOWER,

    DISPLAY_THOUSAND_NUM_1
}THOUSAND_DISPLAY_DATA;

#define DUTY_EXTRACT_90_PERCENT        9
#define DUTY_EXTRACT_80_PERCENT        8
#define DUTY_EXTRACT_70_PERCENT        7
#define DUTY_EXTRACT_60_PERCENT        6
#define DUTY_EXTRACT_50_PERCENT        5
#define DUTY_EXTRACT_40_PERCENT        4
#define DUTY_EXTRACT_30_PERCENT        3





#define DUTY_100_PERCENT               10
#define DUTY_20_PERCENT                1


#define FIXED_DISPLAY                  0
#define DIRECT_DISPLAY                 1



typedef enum
{
    DUTY_OUT_SET_SELECT,
    DUTY_OUT_ICE_SELECT,
    DUTY_OUT_HOT_SELECT,
    DUTY_OUT_AMBIENT_SELECT,
    DUTY_OUT_COLD_SELECT,
    DUTY_OUT_AMOUNT_SELECT,

    DUTY_OUT_ICE_EXTRACT,
    DUTY_OUT_WATER_EXTRACT,

    DUTY_OUT_SETTING_MENU,
    DUTY_OUT_ETC_ICON,

    DUTY_OUT_HOT_TEMP,
    DUTY_OUT_COLD_TEMP,

    DUTY_OUT_CONT,
    DUTY_OUT_POT,
    DUTY_OUT_2_CUPS,
    DUTY_OUT_1_CUP,
    DUTY_OUT_HALF_CUP,
    DUTY_OUT_MY_CUP,

    DUTY_OUT_SEGMENT_0_0_0_1,
    DUTY_OUT_SEGMENT_0_0_2_0,

    DUTY_OUT_SEGMENT_0_3_0_0,
    DUTY_OUT_SEGMENT_4_0_0_0,
    
    DUTY_OUT_WIFI_WHITE_ICON
    

}DUTY_SET_DATA;



typedef enum
{
    DIMMING__HOT_TEMP,
    DIMMING__COLD_TEMP,
    DIMMING__UV_CART,
    DIMMING__FAUCET,
    DIMMING__ICE_TANK,
    DIMMING__ICE_FAUCET,
    DIMMING__ml,
    
    DIMMING__AM,
    DIMMING__PM,

    DIMMING__PERCENT,
    DIMMING__AUTO_DRAIN,

    DIMMING__LOW_WATER,
    DIMMING__ICON_ICE_LOCK,

    DIMMING__ICON_HOT_LOCK,
    DIMMING__ICON_ALL_LOCK,
#if 0
    DIMMING__SEGMENT_0_0_0_1,
    DIMMING__SEGMENT_0_0_2_0,

    DIMMING__SEGMENT_0_3_0_0,
    DIMMING__SEGMENT_4_0_0_0,
#endif
    DIMMING__ICON_SAVE,
    DIMMING__ICE_FIRST,
    DIMMING__ICE_FULL


}ICON_DIMMING_SET_DATA;


#define ICON_DIIMMING_10_PERCENT_ON                1
#define ICON_DIIMMING_FULL_ON                      0


#define LED_SLEEP_ENTER_TIME       6000
#define LED_SLEEP_WAKEUP_TIME      100

/* sean [24-10-24] 고장진단 추가에 따른 변수 추가*/
#define SELF_TEST_RESULT_DATA_LENGTH       28

typedef union
{
    U8 byte[SELF_TEST_RESULT_DATA_LENGTH * 2];
    U16  word[SELF_TEST_RESULT_DATA_LENGTH];
}TYPE_SELF_TEST_DATA;


typedef enum
{
    DC_LOAD_1__FEED_VALVE,
    DC_LOAD_2__NOS_VALVE,
    DC_LOAD_3__HOT_OUT_VALVE,
    DC_LOAD_4__PURE_OUT_VALVE,
    DC_LOAD_5__COLD_OUT_VALVE,
    DC_LOAD_6__DRAIN_NOS_VALVE,

    DC_LOAD_7__UV_FAUCET,
    DC_LOAD_8__UV_ICE_FAUCET,
    DC_LOAD_9__UV_ICE_TANK,

    DC_LOAD_10__SWING_BAR,

    DC_LOAD_11__ICE_DOOR_MOTOR,
    DC_LOAD_12__GAS_SWITCH_MOTOR,

    DC_LOAD_13__DRAIN_PUMP,
    DC_LOAD_14__ICE_FULL_SENSOR,
    
    DC_LOAD_15__COLD_FAN

}SELF_TEST_NO;

#define WIFI_SELF_TEST_NO_OPERATION     0
#define WIFI_SELF_TEST_START            1
#define WIFI_SELF_TEST_ING              2
#define WIFI_SELF_TEST_FINISH           3
#define WIFI_SELF_TEST_STOP             4
#define WIFI_SELF_TEST_PROHIBIT         5

#define WIFI_SELF_TEST_0_PERCENT        0
#define WIFI_SELF_TEST_10_PERCENT       10
#define WIFI_SELF_TEST_20_PERCENT       20
#define WIFI_SELF_TEST_30_PERCENT       30
#define WIFI_SELF_TEST_40_PERCENT       40
#define WIFI_SELF_TEST_50_PERCENT       50
#define WIFI_SELF_TEST_60_PERCENT       60
#define WIFI_SELF_TEST_70_PERCENT       70
#define WIFI_SELF_TEST_80_PERCENT       80
#define WIFI_SELF_TEST_90_PERCENT       90
#define WIFI_SELF_TEST_100_PERCENT      100



#define SELF_TEST_INITIAL_DATA               0xFFFF
//#define SELF_TEST_SENSOR_ERROR_DATA          130
#define SELF_TEST_SENSOR_ERROR_DATA          255



typedef enum
{
    DEBUG__COMP_DELAY,
    DEBUG__FLOW_HZ,
    DEBUG__COLD_TEMP,
    DEBUG__ROOM_TEMP,
    DEBUG__HOT_TEMP,
    DEBUG__OUT_DOOR_TEMP,
    DEBUG__EVA_COLD_TEMP,
    DEBUG__EVA_ICE_TEMP,
    DEBUG__ICE_FULL_AD,
    DEBUG__LEAK_AD,
    DEBUG__CDS_AD,
    DEBUG__ICE_STEP,
    DEBUG__ICE_TRAY_INPUT,
    DEBUG__ICE_TRAY_ERROR,
    DEBUG__ICE_WATER_LEVEL,
    DEBUG__ICE_DRAIN_LEVEL,
    DEBUG__FEED_NOS_DCFAN,
    DEBUG__ROOM_COLD_HOT,
    DEBUG__COMP_ICEHEATER_HOTHEATER

}DEBUG_STEP;


typedef enum
{
    STEP0_STANDBY,
    STEP1_40MIN_ON,
    STEP2_20MIN_OFF,
    STEP3_40MIN_ON,
    STEP4_120MIN_OFF

}PUMP_RETRY_STEP;

typedef enum
{
GREEN_WEEK, INTENSIVE_WEEK
}POWER_SAVING_STATE;

#define LowByte(data)                   ((U8)((data) & 0xff))
#define HighByte(data)                  ((U8)(((data) >> 8) & 0xff))

#define LowWord(data)                   ((U16)((data) & 0xFFFF))
#define HighWord(data)                  ((U16)(((data) >> 16) & 0xFFFF)

#define BitRead(value, bit)             (((value) >> (bit)) & 0x01)
#define BitSet(value, bit)              ((value) |= (1UL << (bit)))
#define BitClear(value, bit)            ((value) &= ~(1UL << (bit)))
#define BitWrite(value, bit, bitvalue)  (bitvalue ? BitSet(value, bit) : BitClear(value, bit))


#define ON_OFF_DISPLAY_OFF                0
#define ON_OFF_DISPLAY_ICE_SET            1
//#define ON_OFF_DISPLAY_COLD_TEMP_STE      2
#define ON_OFF_DISPLAY_COLD_ENABLE	      2
#define ON_OFF_DISPLAY_ECO_SET            4
#define ON_OFF_DISPLAY_MY_CUP_SET         8
#define ON_OFF_DISPLAY_MY_CUP_OFF         16


/*..hui [24-4-24오후 5:33:54] 추가..*/
#define BUTTON_SET_DISPLAY_OFF                     0
#define BUTTON_SET_HOT_DISPLAY                     1
#define BUTTON_SET_COLD_DISPLAY                    2
#define BUTTON_SET_ICE_DISPLAY                     4
#define BUTTON_SET_COLD_TEMP_DISPLAY			   8


#define BUTTON_SET_DISPLAY_TIME                    30




#if 0
#define C_01_LPM    7
#define C_02_LPM    14
#define C_03_LPM    22
#define C_035_LPM   26
#define C_04_LPM    30
#define C_05_LPM    38
#define C_06_LPM    45
#define C_07_LPM    52
#define C_08_LPM    60
#define C_09_LPM    68
#define C_10_LPM    76
#define C_11_LPM    83
#define C_12_LPM    90
#define C_13_LPM    98
#define C_14_LPM    106
#define C_15_LPM    114
#endif


#define C_02_LPM    10
#define C_025_LPM   13
#define C_03_LPM    16
#define C_035_LPM   19
#define C_04_LPM    22
#define C_05_LPM    28
#define C_055_LPM   31
#define C_057_LPM   32
#define C_06_LPM    34
#define C_07_LPM    40





#define HOT_BLOCKED_FLOW_HZ              5
/*#define HOT_FIRST_BLOCKED_FLOW_HZ        14*/
#define HOT_FIRST_BLOCKED_FLOW_HZ        10




#define BUZZER_OFF                  0
#define BUZZER_POWER_ON             1
#define BUZZER_EFFLUENT             2
#define BUZZER_EFFLUENT_END         3
#define BUZZER_COOL_SETUP           4
#define BUZZER_COOL_CANCEL          5
#define BUZZER_SELECT               6
#define BUZZER_ERROR                7
#define BUZZER_SETUP                8
#define BUZZER_CANCEL               9
#define BUZZER_EFFLUENT_CONTINUE    10
#define BUZZER_STERILIZE_START      11
#define BUZZER_STERILIZE_END        12
#define BUZZER_AP_CONNECT           13
#define BUZZER_SERVER_CONNECT       14
#define BUZZER_MUTE                 15
#define BUZZER_MEMENTO_1            16      /* 메멘토 1 */
#define BUZZER_MEMENTO_2            17      /* 메멘토 2 */
#define BUZZER_MEMENTO_3            18      /* 메멘토 3 */
#define BUZZER_MEMENTO_4            19      /* 메멘토 4 */
#define BUZZER_MEMENTO_5            20      /* 메멘토 5 */
#define BUZZER_SETUP_MUTE           30
#define BUZZER_CANCEL_MUTE          31
#define BUZZER_MEMENTO_1_MUTE       32
#define BUZZER_MEMENTO_5_MUTE       33
#define BUZZER_POWER_ON_MUTE       	34
#define BUZZER_AP_CONNECT_MUTE      35
#define BUZZER_SERVER_CONNECT_MUTE  36


#define USCAN1                   0
#define USCAN2                   1
#define USCAN3                   2
#define USCAN4                   3
#define USCAN5                   4
#define USCAN6                   5
#define USCAN7                   6

#define UControl_Key_Mask                   0x00


#define MODEL_CHPI                0
#define MODEL_CPI                 1






#define ALTITUDE_1_MODE_HIGH      0
#define ALTITUDE_2_MODE_MID       1
#define ALTITUDE_3_MODE_LOW       2
#define ALTITUDE_4_MODE_VERY_LOW  3


#define WIFI_ICE_MAKING_STANDBY             0
#define WIFI_ICE_TRAY_IN_START              1
#define WIFI_ICE_TRAY_IN_ING                2
#define WIFI_ICE_MAKING_START               3
#define WIFI_ICE_MAKING_ING                 4
#define WIFI_ICE_TAKE_OFF_START             5
#define WIFI_ICE_TAKE_OFF_ING               6
#define WIFI_ICE_MAKING_FINISH_START        7
#define WIFI_ICE_MAKING_FINISH_ING          8

#define WIFI_PAIRING_STANDBY             0
#define WIFI_PAIRING_STEP0_PREPARE       1
#define WIFI_PAIRING_STEP1_25_PERCENT    2
#define WIFI_PAIRING_STEP2_50_PERCENT    3
#define WIFI_PAIRING_STEP3_75_PERCENT    4
#define WIFI_PAIRING_STEP_FINISH         5

#define WIFI_UV_OPERATION_OFF           0
#define WIFI_UV_OPERATION_ON            1
#define WIFI_UV_OPERATION_GOING         2


#define WIFI_PAIRING_START                  0
#define WIFI_PAIRING_ING                    1
#define WIFI_PAIRING_FAIL                   2
#define WIFI_PAIRING_SUCESS                 3
#define WIFI_ERROR_DENY__AP3                4
#define WIFI_NO_AP__AP4                     5
#define WIFI_NO_ACK__AP2                    6
#define WIFI_FAIL_PASS__AP1                 7
#define WIFI_NO_SERVER__AP5                 8

//RTC만 별도로 빼서 동작
//#define DEV_ADDR_RTC          0xDE  /* Device RTC - ISL12026 */

/*.. sean [24-10-07] RTC, EEPROM 사용..*/
#if CONFIG_RTC_EEPROM_ISL12026_USE
#define DEV_ADDR_EEP          0xAE  /* Device EEPROM - ISL12026 */
#define DEV_ADDR_RTC          0xDE  /* Device RTC - ISL12026 */


/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_START               0x0040
/////////////////////////////////////////////////////////////////////////////
#define SPECIAL_SETTING_START_ADDR            0x0050
#define SPECIAL_SETTING_LENGTH                7

#define EEPROM_ADDR1_COLD_SETTING             0x50
#define EEPROM_ADDR1_HOT_LOCK                 0x51
#define EEPROM_ADDR1_ALL_LOCK                 0x52
#define EEPROM_ADDR1_MUTE_SETTING             0x53
#define EEPROM_ADDR1_COLD_LEVEL               0x54
#define EEPROM_ADDR1_HOT_ENABLE               0x55
#define EEPROM_ADDR1_ALTITUDE                 0x56


/////////////////////////////////////////////////////////////////////////////
#define ICE_SETTING_START_ADDR                0x0060
#define ICE_SETTING_LENGTH                    4

#define EEPROM_ADDR2_ICE_LOCK                 0x0060
#define EEPROM_ADDR2_ICE_ON_OFF               0x0061
#define EEPROM_ADDR2_ICE_MAKE_PRIORITY        0x0062
#define EEPROM_ADDR2_ICE_TOTAL_SETTING        0x0063


/////////////////////////////////////////////////////////////////////////////
#define FUNCTION_SETTING_START_ADDR           0x0070
#define FUNCTION_SETTING_LENGTH               10

#define EEPROM_ADDR3_OWER_SAVE_SETTING        0x0070
#define EEPROM_ADDR3_CIRCULATION_DRAIN        0x0071
#define EEPROM_ADDR3_AUTO_UV_CONTROL          0x0072
#define EEPROM_ADDR3_EXTRACT_LED_ONOFF        0x0073
#define EEPROM_ADDR3_NO_USE_SAVE              0x0074

#define EEPROM_ADDR3_SLEEP_MODE_ENABLE        0x0075
#define EEPROM_ADDR3_SLEEP_START_HOUR         0x0076
#define EEPROM_ADDR3_SLEEP_START_MINUTE       0x0077
#define EEPROM_ADDR3_SLEEP_FINISH_HOUR        0x0078
#define EEPROM_ADDR3_SLEEP_FINISH_MINUTE      0x0079

/////////////////////////////////////////////////////////////////////////////
#define ETC_SAVE_START_ADDR                   0x0080
#define ETC_SAVE_LENGTH                       2

#define EEPROM_ADDR4_CUP_LEVEL                0x80
#define EEPROM_ADDR4_WATER_SELECT_DEFAULT     0x81

/////////////////////////////////////////////////////////////////////////////
#define MEMENTO_START_ADDR                    0x0090
#define MEMENTO_LENGTH                        5

#define EEPROM_ADDR5_MEMENTO_NUM0             0x90
#define EEPROM_ADDR5_MEMENTO_NUM1             0x91
#define EEPROM_ADDR5_MEMENTO_NUM2             0x92
#define EEPROM_ADDR5_MEMENTO_NUM3             0x93
#define EEPROM_ADDR5_MEMENTO_NUM4             0x94


/////////////////////////////////////////////////////////////////////////////
#define MY_CUP_START_ADDR                     0xA0
#define MY_CYP_SETTING_LENGTH                 7

#define EEPROM_ADDR6_MY_CUP_USING             0xA0

#define EEPROM_ADDR6_MY_CUP_LEVEL_PURE        0xA1
#define EEPROM_ADDR6_MY_CUP_LEVEL_PURE_1      0xA2

#define EEPROM_ADDR6_MY_CUP_LEVEL_COLD        0xA3
#define EEPROM_ADDR6_MY_CUP_LEVEL_COLD_1      0xA4

#define EEPROM_ADDR6_MY_CUP_LEVEL_HOT         0xA5
#define EEPROM_ADDR6_MY_CUP_LEVEL_HOT_1       0xA6


///////////////////////////////////////////////////////////////////////////////
#define IOT_FUNCTION_ADDR                     0x00B0
#define IOT_FUNCTION_LENGTH                   2

#define EEPROM_ADDR6_CUP_LEVEL_SELECT         0x00B0
#define EEPROM_ADDR6_FOTA_START               0x00B1

/////////////////////////////////////////////////////////////////////////////
#define WIFI_DATA_ADDR                        0x00E0
#define WIFI_DATA_LENGTH                      4

//중복으로 wifi_config.h에서 읽어오도록 변경
#if 0
#define EEPROM_ADDR_WIFI_POWER                0x00E0   // WIFI On/Off State
#define EEPROM_ADDR_FIRST_PARING              0x00E1   // WIFI First Paring Check
#define EEPROM_ADDR_FOTA_STATE                0x00E2   // WIFI Module Fota State
#define EEPROM_ADDR_FOTA_MCU                  0x00E3   // WIFI MCU Fota State
#endif


/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_END                  0x01EA
/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_TEST                       0x01EC  // MAIN PBA TEST  //kdh /*48*/
/////////////////////////////////////////////////////////////////////////////////
#endif

//EEPROM만 사용할 경우
#if COFIG_EEPROM_AT24C02C_USE
#define DEV_ADDR_EEP                          0xA0     /* Device EEPROM - AT24C02C */

/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_START               0x40
/////////////////////////////////////////////////////////////////////////////
#define SPECIAL_SETTING_START_ADDR            0x50
#define SPECIAL_SETTING_LENGTH                7

#define EEPROM_ADDR1_COLD_SETTING             0x50
#define EEPROM_ADDR1_HOT_LOCK                 0x51
#define EEPROM_ADDR1_ALL_LOCK                 0x52
#define EEPROM_ADDR1_MUTE_SETTING             0x53
#define EEPROM_ADDR1_COLD_LEVEL               0x54
#define EEPROM_ADDR1_HOT_ENABLE               0x55
#define EEPROM_ADDR1_ALTITUDE                 0x56


/////////////////////////////////////////////////////////////////////////////
#define ICE_SETTING_START_ADDR                0x60
#define ICE_SETTING_LENGTH                    3

#define EEPROM_ADDR2_ICE_LOCK                 0x60
#define EEPROM_ADDR2_ICE_ON_OFF               0x61
#define EEPROM_ADDR2_ICE_MAKE_PRIORITY        0x62
#define EEPROM_ADDR2_ICE_TOTAL_SETTING        0x63



/////////////////////////////////////////////////////////////////////////////
#define FUNCTION_SETTING_START_ADDR           0x70
#define FUNCTION_SETTING_LENGTH               5

#define EEPROM_ADDR3_OWER_SAVE_SETTING        0x70
#define EEPROM_ADDR3_CIRCULATION_DRAIN        0x71
#define EEPROM_ADDR3_AUTO_UV_CONTROL          0x72
#define EEPROM_ADDR3_EXTRACT_LED_ONOFF        0x73
#define EEPROM_ADDR3_NO_USE_SAVE              0x74



/////////////////////////////////////////////////////////////////////////////
#define ETC_SAVE_START_ADDR                   0x80
#define ETC_SAVE_LENGTH                       2

#define EEPROM_ADDR4_CUP_LEVEL                0x80
#define EEPROM_ADDR4_WATER_SELECT_DEFAULT     0x81


/////////////////////////////////////////////////////////////////////////////
#define MEMENTO_START_ADDR                    0x90
#define MEMENTO_LENGTH                        5

#define EEPROM_ADDR6_MEMENTO_NUM0             0x90
#define EEPROM_ADDR6_MEMENTO_NUM1             0x91
#define EEPROM_ADDR6_MEMENTO_NUM2             0x92
#define EEPROM_ADDR6_MEMENTO_NUM3             0x93
#define EEPROM_ADDR6_MEMENTO_NUM4             0x94

/////////////////////////////////////////////////////////////////////////////
#define MY_CUP_START_ADDR                     0xA0
#define MY_CYP_SETTING_LENGTH                 7

#define EEPROM_ADDR7_MY_CUP_USING             0xA0

#define EEPROM_ADDR7_MY_CUP_LEVEL_PURE        0xA1
#define EEPROM_ADDR7_MY_CUP_LEVEL_PURE_1      0xA2

#define EEPROM_ADDR7_MY_CUP_LEVEL_COLD        0xA3
#define EEPROM_ADDR7_MY_CUP_LEVEL_COLD_1      0xA4

#define EEPROM_ADDR7_MY_CUP_LEVEL_HOT         0xA5
#define EEPROM_ADDR7_MY_CUP_LEVEL_HOT_1       0xA6

/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_END                 0xF0
/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_TEST                      0xF8  // MAIN PBA TEST  //kdh /*48*/
/////////////////////////////////////////////////////////////////////////////////
#endif





#define KEY_SETTING_SELECT                 0x8000
#define KEY_ICE                            0x4000
#define KEY_HOT_SELECT                     0x2000
#define KEY_AMBIENT_SELECT                 0x1000
#define KEY_COLD_SELECT                    0x0800
#define KEY_AMOUNT_SELECT                  0x0400
#define KEY_SETTING_ICE_FIRST              0x0200
#define KEY_SETTING_ICE_LOCK               0x0100
#define KEY_SETTING_HOT_LOCK               0x0080
#define KEY_SETTING_ECO_MODE               0x0040
#define KEY_SETTING_COLD_ENABLE            0x0020
#define KEY_SETTING_MY_CUP                 0x0010


#define LONG_KEY_HOT_TEMP_SETTING        (KEY_SETTING_SELECT + KEY_HOT_SELECT)
/*#define LONG_KEY_PCB_TEST_MODE           (KEY_HOT_SELECT + KEY_AMOUNT_SELECT + KEY_AMBIENT_SELECT)*/
#define LONG_KEY_PCB_TEST_MODE           (KEY_SETTING_SELECT + KEY_ICE + KEY_HOT_SELECT + KEY_AMOUNT_SELECT)

#define LONG_KEY_DISPLAY_TEST_MODE_CHPI  (KEY_HOT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_CIRCULATION_DRAIN       (KEY_COLD_SELECT + KEY_SETTING_COLD_ENABLE)
#define LONG_KEY_ALL_LOCK                (KEY_HOT_SELECT + KEY_AMBIENT_SELECT)
#define LONG_KEY_DEBUG_MODE              (KEY_SETTING_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_MEMENTO              (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_COLD_SELECT)
#define LONG_KEY_3S_MUTE_SETTING         (KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)

//#define LONG_KEY_3S_TAKEOFF_ICE          (KEY_SETTING_SELECT + KEY_ICE)
//Western ICE 와 설정 맞춤
#define LONG_KEY_3S_TAKEOFF_ICE          (KEY_ICE + KEY_HOT_SELECT)
#define LONG_KEY_3S_ICE_TRAY_TEST        (KEY_ICE + KEY_AMBIENT_SELECT)
#define LONG_KEY_3S_CANCEL_COMP_DELAY    (KEY_ICE + KEY_AMOUNT_SELECT)

#define LONG_KEY_3S_SETTING_MISS_TOUCH   (KEY_SETTING_SELECT + KEY_SETTING_ICE_FIRST)
#define LONG_KEY_3S_ICE_MISS_TOUCH   (KEY_ICE + KEY_SETTING_ICE_LOCK)
#define LONG_KEY_3S_HOT_MISS_TOUCH   (KEY_HOT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_PURE_MISS_TOUCH   (KEY_AMBIENT_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_COLD_MISS_TOUCH   (KEY_COLD_SELECT + KEY_SETTING_COLD_ENABLE)
#define LONG_KEY_3S_AMOUNT_MISS_TOUCH   (KEY_AMOUNT_SELECT + KEY_SETTING_MY_CUP)



#define LONG_KEY_3S_DURABLE_TEST         (KEY_ICE + KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_MANUAL_FACTORY_TEST      (KEY_SETTING_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_NO_USE_NO_OPERATION    (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)

/*..hui [24-4-24오후 4:32:38] 얼음, 온수, 냉수 OFF 버튼 변경..*/
#if LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF
#define LONG_KEY_3S_HOT_OFF               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_ICE_OFF               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_COLD_OFF              (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#endif

/* sean [24-4-26] 얼음, 온수, 냉수 off 버튼 Miss touch 추가 */
//Hot 기능 Off
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_1               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_2               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_3               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_4               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_5               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_6               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_7               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)

//Ice 기능 Off
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_1               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_2               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_3               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_4               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_5               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_6               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_7               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)

//Cold 기능 Off
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_1               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_COLD_ENABLE)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_2               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_3               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_4               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_COLD_ENABLE + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_5               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_COLD_ENABLE + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_6               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)
#define LONG_KEY_3S_COLD_OFF_MISS_TOUCH_7               (KEY_COLD_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_COLD_ENABLE + KEY_SETTING_ECO_MODE + KEY_SETTING_MY_CUP)

#define LONG_KEY_3S_BLE_FAIRING           (KEY_AMBIENT_SELECT)
#define LONG_KEY_3S_WIFI_FAIRING          (KEY_AMBIENT_SELECT + KEY_COLD_SELECT)
#define LONG_KEY_3S_WIFI_ONOFF            (KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
//잘못 touch 되었을때 눌리도록 추가
#define LONG_KEY_3S_AMBIENT_MISS_TOUCH   (KEY_AMBIENT_SELECT + KEY_SETTING_ECO_MODE)

#define LONG_KEY_3S_COLD_SETTING         				(KEY_SETTING_SELECT + KEY_COLD_SELECT)

//시간 세팅
#if CONFIG_TIME_SETTING
#define LONG_KEY_3S_TIME_SETTING         				(KEY_SETTING_SELECT + KEY_ICE)
#endif

#if 0
#define LONG_KEY_2S_FAUCET_UV           (KEY_SETTING_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_2S_ICE_TANK_UV       (KEY_SETTING_SELECT + KEY_AMBIENT_SELECT)
#define LONG_KEY_2S_ICE_FAUCET_UV       (KEY_SETTING_SELECT + KEY_COLD_SELECT)
#endif
//
#define UKey_Mask                    0x00
#define UWater_Extract_Key           0x02
#define UIce_Extract_Key             0x01

#define UWater_Extract_Long_Key           0x02
#define UIce_Extract_Long_Key             0x01



/*..hui [18-1-30오후 5:04:07] 드레인펌프 출력 전압 변경에 따라 시간 감소..*/
/*..hui [19-12-2오후 2:59:15] 4분 30초..*/
/*#define COLD_DRAIN_TIME    2700*/

/*..hui [19-12-2오후 3:49:41] 탱크가 크니까 5분 30초로.....*/
/*#define COLD_DRAIN_TIME    3300*/
#define COLD_DRAIN_TIME    1200



#define NOW_USE_PHOTO   6000                     // 미사용 절전 밤낮 확정 시간 10(600)->1분(60)
#define NoWaterOutTime  360                     // 미사용 절전 6시간 6 x 60(360)->30분(30)



#define TEMPERATURE_SENSOR_OPEN               1000
#define TEMPERATURE_SENSOR_SHORT              20

#define TEMPERATURE_SENSOR_8BIT_OPEN          250
#define TEMPERATURE_SENSOR_8BIT_SHORT         5

#define TEMPERATURE_SENSOR_ERROR_CHECK_TIME   30

#define RO_DRAIN_MODE_NONE                 0
#define RO_DRAIN_MODE_INIT                 1
#define RO_DRAIN_MODE_CLOSE                2
#define RO_DRAIN_MODE_OPEN                 3

#define RO_DRAIN_STEP_NUM                  4

#define RO_DRAIN_HOLD_STEP                 0    //10
#define RO_DRAIN_OPEN_PULSE                700
#define RO_DRAIN_MAX_CLOSE                 900
#define RO_DRAIN_INIT_ADJUST               0


#define RO_DRAIN_STATUS_CLOSE              0
#define RO_DRAIN_STATUS_OPEN               1



#if 0
#define PUMP_PWM_Free   1699                      // Sterilization.h 에도 정의, 기동 초기 20V
#define DRAIN_PUMP_PWM_OP        1499                      // 16V(1300)->18V(1500) 동작 DUTY
#define DRAIN_PUMP_PWM_MAX    1999                      // 16V(1300)->18V(1500) 동작 DUTY
#endif



#if 0
#define DRAIN_PUMP_PWM_OP        4000                      // 2ms
#define DRAIN_PUMP_PWM_MAX    6000                      // Full(3ms)
#endif


/*#define DRAIN_PUMP_PWM_OP     33600*/                      // 2ms
/*..hui [23-5-31오전 11:33:09] 듀티 변경.. 70%에서 67%로..*/
//#define DRAIN_PUMP_PWM_OP     32160                      // 2ms
#define DRAIN_PUMP_PWM_OP     640                      // 2ms

#define DRAIN_PUMP_PWM_MAX    3200                      // Full(3ms)



#define DRAIN_CURRENT   83                       // 0.4V(82)



#define ICE_TRAY_POSITION_ICE_MAKING    0        /*..얼음받음..*/
#define ICE_TRAY_POSITION_ICE_THROW     1        /*..얼음버림..*/
#define ICE_TRAY_POSITION_MOVING        2        /*..이동중..*/
#define ICE_TRAY_POSITION_ERROR         3        /*..에러..*/



#define CUP_SELECT_LED_OFF_TIME    70


#define STEP_ANGLE1 2000                        // Select Bar 1200->2000


/*..hui [20-3-26오후 7:24:07] ICE Door 1500->1000.. 아이스2.0 사양..*/
/*#define STEP_ANGLE2 1000*/

/*..hui [20-3-26오후 7:24:23] 아이스3.0은 이 값이 적정 사양..*/
/*#define STEP_ANGLE2 670*/


/*..hui [20-3-26오후 7:30:12] 50펄스 정도 더 주는걸로..*/
#define STEP_ANGLE2 750



#define COLDSUPPLY_TIME 7200                    // 냉수공급시간 2시간
#define DRAIN_ON_TIME 580                       // 얼음녹은물 배수시간 50초 Valve Delay 8초
#define DRAIN_MAX_TIME 5987                     // 강제배수시간 10분, 드레인 시작 13초 후 카운트
#define DRAIN_TEST_MAX_TIME 1787                // 테스트모드 강제배수시간 3분, 드레인 시작 13초 후 카운트


// 20160530 Sus EVA 추가 변경 (콤프 재기동 3분->8분)
//#define COMP_START_TIME 480                     // COMP 기동 대기 8분
//#define COMP_START_TIME 4800                     // COMP 기동 대기 8분
/*..hui [19-9-18오후 1:15:38] COMP 기동 대기 7분으로 변경..*/
/*#define COMP_START_TIME        4200*/

/*..hui [19-11-19오후 4:09:12] COMP 기동 대기 6분으로 변경..*/
//#define COMP_START_TIME                      4800
/*..[25-02-13] 냉수 성능 NG로 8분에서 20분으로 변경..*/
//#define COMP_START_TIME                      12000
#define COMP_START_TIME                      6000
#define DEVELOPE_COMP_DELAY_CANCEL_TIME      300


#define ICEVV_TIME_INIT                      300                    // 얼음받이 물주입 시간 30초


#define COLD_TIME                            50                            // 냉수재정수 시간 5초
#define IceWaterDelay                        1440        // 얼음녹은물 24시간 강제 배수 24 x 60




//service
#define WASH_TIME                            500+20                  // 세척시간
#define NEUTRAL_TIME                         600+20                  // 중화시간


#define STANDBY             0                       // 서비스대기
#define WASH                1                       // 세척
#define WASHEND             2                       // 세척종료
#define NEUTRAL             3                       // 중화
#define NEUTRALEND          4                       // 중화종료


/*..hui [19-9-4오후 7:30:26] 연속 추출이 메뉴속으로..*/
/*#define CUP_LEVEL_CONTINUE        8*/
/*..hui [23-2-13오후 7:26:17] 연속빼고 마이컵..*/
/*..sean [24-09-29] 120ml 추가 ..*/
#if 0
#define CUP_LEVEL_HALF            1
#define CUP_LEVEL_ONE             2
#define CUP_LEVEL_TWO             4
#define CUP_LEVEL_MY_CUP          8
#else
#define CUP_LEVEL_HALF            1
#define CUP_LEVEL_ONE             2
#define CUP_LEVEL_TWO             3
#define CUP_LEVEL_FOUR            4
#define CUP_LEVEL_CONTINUE        5
#define CUP_LEVEL_MY_CUP          6
#endif



#define USER_SELECT_NONE     0
#define USER_SELECT_A        1
#define USER_SELECT_B        2
#define USER_SELECT_C        3




#define PURE_WATER_SELECT    1
#define COLD_WATER_SELECT    2
#define HOT_WATER_SELECT     4


#define COLD_FIRST_ICE_MAKE    0
#define ICE_FIRST_ICE_MAKE     1




#define DRAIN_LEVEL_EMPTY    1
#define DRAIN_LEVEL_LOW      2
#define DRAIN_LEVEL_HIGH     4
#define DRAIN_LEVEL_ERROR    8

#define ROOM_LEVEL_LOW     0
#define ROOM_LEVEL_MID     1
#define ROOM_LEVEL_FULL    2
#define ROOM_LEVEL_ERROR   3



#define COLD_WATER_DISABLE    1
#define HOT_WATER_DISABLE     2
#define ICE_MAKE_DISABLE      4



#define SETTING_MAX_YEAR      80
#define SETTING_MIN_YEAR      24


/*..hui [20-1-15오후 7:42:07] 2020년 1월1일 0시0분0초..*/
#define RTC_DEFAULT_YEAR      25
#define RTC_DEFAULT_MONTH     1
#define RTC_DEFAULT_DATE      1
#define RTC_DEFAULT_HOUR      0
#define RTC_DEFAULT_MIN       0
#define RTC_DEFAULT_SEC       0
#define RTC_DEFAULT_DAYWEEK   5
#define RTC_DEFAULT_Y2K       20


#if 0
#define SLEEP_IN    245                         //  진입, 1.2V
#define SLEEP_OUT   450                         //  해제, 2.2V
#endif


//#define SLEEP_IN    385
//#define SLEEP_OUT   810

//#define SLEEP_IN    100
//#define SLEEP_OUT   160


/*..hui [20-1-22오후 2:46:18] PCB, 기구물에 폼 붙여서 다시..*/
/*#define SLEEP_IN    345*/
/*#define SLEEP_OUT   634*/

/*..hui [20-2-18오후 5:17:51] 기구물 수정 후 다시 측정..*/
/*#define SLEEP_IN    381*/
/*#define SLEEP_OUT   754*/

/*#define SLEEP_IN    381*/
/*#define SLEEP_OUT   754*/


//#define SLEEP_IN    560
//#define SLEEP_OUT   881

/*..sean [23-8-28 오전 10:11:22] MYAIS 최종 디자인 사양 적용후 재 측정..*/
//#define SLEEP_IN    460
//#define SLEEP_OUT   830

/*..sean [23-8-28 오전 10:11:22] MYAIS 최종 디자인 사양 적용후 재 측정..*/
//#define SLEEP_IN    520
//#define SLEEP_OUT   855

/*..sean [23-8-28 오전 10:11:22] MYAIS 최종 디자인 사양 적용후 재 측정..*/
#define SLEEP_IN    520
#define SLEEP_OUT   800








/*..hui [20-1-30오후 3:41:34] 추출량 정할때 끝이 0으로 끝나지 않도록 명심~~~..*/
/*..hui [20-1-30오후 3:41:39] LCD 표시 관련..*/
#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       103
#define EXTRACT_TIME_PURE_WATER_ONE        204
#define EXTRACT_TIME_PURE_WATER_TWO        512

#define EXTRACT_TIME_COLD_WATER_HALF       93
#define EXTRACT_TIME_COLD_WATER_ONE        185
#define EXTRACT_TIME_COLD_WATER_TWO        385

#define EXTRACT_TIME_HOT_WATER_HALF        175
#define EXTRACT_TIME_HOT_WATER_ONE         349
#define EXTRACT_TIME_HOT_WATER_TWO         719
#endif

#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       103
#define EXTRACT_TIME_PURE_WATER_ONE        214
#define EXTRACT_TIME_PURE_WATER_TWO        432

#define EXTRACT_TIME_COLD_WATER_HALF       102
#define EXTRACT_TIME_COLD_WATER_ONE        209
#define EXTRACT_TIME_COLD_WATER_TWO        431

#define EXTRACT_TIME_HOT_WATER_HALF        175
#define EXTRACT_TIME_HOT_WATER_ONE         358
#define EXTRACT_TIME_HOT_WATER_TWO         764



#define MY_CUP_SETTING_800mL_PURE          333 //revise
#define MY_CUP_SETTING_800mL_COLD          1000
#define MY_CUP_SETTING_800mL_HOT           1000

/*#define MY_CUP_SETTING_120mL_PURE_MIN      59*/ //revise
/*..hui [23-4-18오후 3:45:53] 최저 유량 120ml로 변경.. 튜닝 필요함..*/
#define MY_CUP_SETTING_120mL_PURE_MIN      47 //revise
#define MY_CUP_SETTING_120mL_COLD_MIN      10
#define MY_CUP_SETTING_120mL_HOT_MIN       10
#endif

#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       93
#define EXTRACT_TIME_PURE_WATER_ONE        164
#define EXTRACT_TIME_PURE_WATER_TWO        372

#define EXTRACT_TIME_COLD_WATER_HALF       94
#define EXTRACT_TIME_COLD_WATER_ONE        185
#define EXTRACT_TIME_COLD_WATER_TWO        379

#define EXTRACT_TIME_HOT_WATER_HALF        153
#define EXTRACT_TIME_HOT_WATER_ONE         309
#define EXTRACT_TIME_HOT_WATER_TWO         633

#define MY_CUP_SETTING_800mL_PURE          304
#define MY_CUP_SETTING_800mL_COLD          1000
#define MY_CUP_SETTING_800mL_HOT           1000

/*#define MY_CUP_SETTING_120mL_PURE_MIN      59*/ //revise
/*..hui [23-4-18오후 3:45:53] 최저 유량 120ml로 변경.. 튜닝 필요함..*/
#define MY_CUP_SETTING_120mL_PURE_MIN      42
#define MY_CUP_SETTING_120mL_COLD_MIN      10
#define MY_CUP_SETTING_120mL_HOT_MIN       10
#endif

#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       97
#define EXTRACT_TIME_PURE_WATER_ONE        191
#define EXTRACT_TIME_PURE_WATER_TWO        372

#define EXTRACT_TIME_COLD_WATER_HALF       96
#define EXTRACT_TIME_COLD_WATER_ONE        192
#define EXTRACT_TIME_COLD_WATER_TWO        379

#define EXTRACT_TIME_HOT_WATER_HALF        158
#define EXTRACT_TIME_HOT_WATER_ONE         322
#define EXTRACT_TIME_HOT_WATER_TWO         653

#define MY_CUP_SETTING_800mL_PURE          304
#define MY_CUP_SETTING_800mL_COLD          1000
#define MY_CUP_SETTING_800mL_HOT           1000
#endif

#define EXTRACT_TIME_PURE_WATER_HALF		49		
#define EXTRACT_TIME_PURE_WATER_ONE			101
#define EXTRACT_TIME_PURE_WATER_TWO			199
#define EXTRACT_TIME_PURE_WATER_FOUR        402

#define EXTRACT_TIME_COLD_WATER_HALF		48
#define EXTRACT_TIME_COLD_WATER_ONE			96
#define EXTRACT_TIME_COLD_WATER_TWO			197
#define EXTRACT_TIME_COLD_WATER_FOUR		392

#define EXTRACT_TIME_HOT_WATER_HALF			79
#define EXTRACT_TIME_HOT_WATER_ONE			161
#define EXTRACT_TIME_HOT_WATER_TWO			333
#define EXTRACT_TIME_HOT_WATER_FOUR			695

#define MY_CUP_SETTING_800mL_PURE          304
#define MY_CUP_SETTING_800mL_COLD          1000
#define MY_CUP_SETTING_800mL_HOT           1000

/*#define MY_CUP_SETTING_120mL_PURE_MIN      59*/ //revise
/*..hui [23-4-18오후 3:45:53] 최저 유량 120ml로 변경.. 튜닝 필요함..*/
#define MY_CUP_SETTING_120mL_PURE_MIN      42
#define MY_CUP_SETTING_120mL_COLD_MIN      10
#define MY_CUP_SETTING_120mL_HOT_MIN       10


//add
#define MY_CUP_MAX_SETTING                 800



#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       45
#define EXTRACT_TIME_PURE_WATER_ONE        93
#define EXTRACT_TIME_PURE_WATER_TWO        183

#define EXTRACT_TIME_COLD_WATER_HALF       42
#define EXTRACT_TIME_COLD_WATER_ONE        83
#define EXTRACT_TIME_COLD_WATER_TWO        166
#endif


#if 0
#define EXTRACT_TIME_PURE_WATER_HALF       44  /*10s*/
#define EXTRACT_TIME_PURE_WATER_ONE        92
#define EXTRACT_TIME_PURE_WATER_TWO        180

#define EXTRACT_TIME_COLD_WATER_HALF       40  /*10s*/
#define EXTRACT_TIME_COLD_WATER_ONE        83
#define EXTRACT_TIME_COLD_WATER_TWO        166
#endif

//#define EXTRACT_TIME_HOT_WATER_HALF        45  /*10s*/
//#define EXTRACT_TIME_HOT_WATER_ONE         100
/*#define EXTRACT_TIME_HOT_WATER_TWO         204*/
//#define EXTRACT_TIME_HOT_WATER_TWO         212

//#define C_CUP_120CC_HOT                    535
//#define C_CUP_250CC_HOT                    1190
//#define C_CUP_500CC_HOT                    2350

//#define C_CUP_120CC_HOT                    390
#define C_CUP_120CC_HOT                    365
#define C_CUP_250CC_HOT                    825
#define C_CUP_500CC_HOT                    1670



#if 0
#define C_CUP_120CC_HOT                    518
#define C_CUP_250CC_HOT                    1190
#define C_CUP_500CC_HOT                    2350
#endif

#define HOT_SETTING_TEMP_COFFEE     0
#define HOT_SETTING_TEMP_TEA        1
#define HOT_SETTING_TEMP_MILK       2

#define Heater_Efficiency           0.95
#define C_Flow_Min_Q                350       // 최소 유량은 0.35LPM (이하에서 스팀)
#define C_FLOW_METER_Hz             14        // 신규 유량센서
//#define C_Heater_Power      2700
#define C_Heater_Power              2720
#define C_Heater_Max_Power          3400
#define C_Heater_Min_Power          1900


//#define C_Heater_Damaged_Power      1500
#define C_Heater_Damaged_Power      1800

#define HOT_TRIAC_OFF_TEMP                    99
#define HOT_TRIAC_OFF_RETURN_TEMP             97


#define HOT_RELAY_TRIAC_OFF_TEMP              100
#define HOT_RELAY_TRIAC_OFF_RETURN_TEMP       97



#define ROOM_OVER_HEAT_TEMP             50
#define ROOM_OVER_HEAT_CLEAR_TEMP       45



//#define STEP_TRIAC                    50        // 트라이악 총 제어 단계 (80단계로 설정)
//#define STEP_TRIAC                    86        // 트라이악 총 제어 단계 (80단계로 설정)
//#define STEP_TRIAC                    114        // 트라이악 총 제어 단계 (80단계로 설정)

//#define STEP_TRIAC                    90        // 트라이악 총 제어 단계 (80단계로 설정)

#define STEP_TRIAC                    110        // 트라이악 총 제어 단계 (80단계로 설정)


#define TRAY_IN_PWM_PWR_UP_TIME       1800


#define GAS_SWITCH_COLD               0
#define GAS_SWITCH_ICE                1

#if 0
#define COLD_TEMP_OFF                 0
#define COLD_TEMP_LOW                 1
#define COLD_TEMP_HIGH                2
#endif

/*#define COLD_TEMP_OFF                 0*/
/*..hui [20-2-24오후 7:44:45] 냉수 ONOFF랑 온도설정 메뉴 분리..*/
#define COLD_TEMP_HIGH                0
#define COLD_TEMP_LOW                 1

//중복으로 주석처리 
/*
#define WIFI_UV_OPERATION_OFF           0
#define WIFI_UV_OPERATION_ON            1
#define WIFI_UV_OPERATION_GOING         2


#define WIFI_PAIRING_START             0
#define WIFI_PAIRING_ING               1
#define WIFI_PAIRING_FAIL              2
#define WIFI_PAIRING_SUCESS            3
#define WIFI_ERROR_DENY                4
#define WIFI_NO_AP                     5
#define WIFI_NO_ACK                    6
#define WIFI_FAIL_PASS                 7
#define WIFI_NO_SERVER                 8
*/

#define PAIRING_STEP_1                 0
#define PAIRING_STEP_2                 1
#define PAIRING_STEP_3                 2
#define PAIRING_STEP_4                 3
#define PAIRING_STEP_5                 4



#define ICE_SETTING_OFF               0
#define ICE_SETTING_ICE_FIRST         1
#define ICE_SETTING_COLD_FIRST        2



#define MAKE_STOP                     0
#define MAKE_COLD                     1
#define MAKE_ICE                      2
#define MAKE_DUAL                     3


/*..hui [19-10-15오후 5:50:08] 물량 적산 최대값은 999.9..*/
#define USER_WATER_MAX_ACC            99999
#define DISPLAY_USER_WATER_MAX_ACC    9999


#define HEATING_PASS_TIME_THREE_MIN             1800


#define SILVER_CARE_TIME_MIN          2880

//#define CODY_CARE_MAX_TIME            65535
/*..hui [21-3-5오전 10:04:59] 최대 9999초.. 아이콘 사양..*/
#define CODY_CARE_MAX_TIME            9999


////////////////////////////////////////////////////////////////////////////////////

#define LCD_RX_BUFFER_SIZE          16
#define LCD_RX_BUFFER_MASK          (LCD_RX_BUFFER_SIZE - 1)
/*#define LCD_TX_BUFFER_SIZE            256*/
#define LCD_TX_BUFFER_SIZE          1024
#define LCD_TX_BUFFER_MASK          (LCD_TX_BUFFER_SIZE - 1)


#if 0
#define MAIN_MENU_TIMER_DEP_1                    1
#define MAIN_MENU_USING_WATER_DEP_1              2
#define MAIN_MENU_REPORT_DEP_1                   4
#define MAIN_MENU_UV_STERERLIZE_DEP_1            8
#define MAIN_MENU_SYSTEM_DEP_1                   16
/*#define MAIN_MENU_CODY_INSPECTION_DEP_1          32*/

#define ELECTRICITY_USAGE_REPORT_DEP_2           1
#define FAULT_DETAILS_REPORT_DEP_2               2

#define UV_AUTO_STERERLIZE_SETTING               1
#define UV_IMMEDIATELY_STER_START                2

#define SYSTEM_GENERAL_SETTING_DEP_2             1
#define SYSTEM_LOCK_SETTING_DEP_2                2
#define SYSTEM_SELF_GUIDE_DEP_2                  4
#define SYSTEM_SCREEN_SETTING_DEP_2              8



#define SYSTEM_GENERAL_DEFAULT_CUP_DEP_3          1
#define SYSTEM_GENERAL_COLD_ENABLE_DEP_3          2
#define SYSTEM_GENERAL_ICE_ENABLE_DEP_3           4
#define SYSTEM_GENERAL_ICE_PRIORITY_DEP_3         8
#define SYSTEM_GENERAL_POWER_SAVING_DEP_3         16


#define SYSTEM_LOCK_HOT_LOCK_DEP_3                1
#define SYSTEM_LOCK_ICE_LOCK_DEP_3                2
#define SYSTEM_LOCK_ALL_LOCK_DEP_3                4

#define SYSTEM_SCREEN__STANDBY_CLOCK_DEP_3        1
#define SYSTEM_SCREEN__SCREEN_BRIGHTNESS_DEP_3    2
#define SYSTEM_SCREEN__SOUND_DEP_3                4
#define SYSTEM_SCREEN__EXTRACT_LED_DEP_3          8
#define SYSTEM_SCREEN__DATE_SETTING_DEP_3         16
#define SYSTEM_SCREEN__TIME_SETTING_DEP_3         32
#endif


#if 0
/*..hui [20-2-21오후 7:29:50] 메인메뉴..*/
#define MAIN_MENU__GENERA_SETTING_DEP__1            1
#define MAIN_MENU__TIMER_DEP__1                     2
#define MAIN_MENU__REPORT_DEP__1                    4
#define MAIN_MENU__LOCK_SETTING_DEP__1              8
#define MAIN_MENU__SCREEN_SOUND_DEP__1              16

/*..hui [20-2-21오후 7:29:44] 기본기능..*/
#define SYSTEM_GENERAL__DEFAULT_CUP_DEP__2          1
#define SYSTEM_GENERAL__ICE_ENABLE_DEP__2           2
#define SYSTEM_GENERAL__COLD_TEMP_DEP__2            4
#define SYSTEM_GENERAL__ICE_PRIORITY_DEP__2         8
#define SYSTEM_GENERAL__UV_STERERLIZE_DEP__2        16
#define SYSTEM_GENERAL__POWER_SAVING_DEP__2         32
#define SYSTEM_GENERAL__COLD_ENABLE_DEP__2          64

/*..hui [20-2-21오후 7:30:13] 기록 셀프진단..*/
#define REPORT__USING_WATER__DEP_2                  1
#define REPORT__SELF_GUIDE_DEP__2                   2
#define REPORT__FAULT_DETAILS_DEP__2                4
#define REPORT__ELECTRICITY_USAGE_REPORT_DEP__2     8

/*..hui [20-2-21오후 7:29:56] 버튼잠금..*/
#define SYSTEM_LOCK__HOT_LOCK_DEP__2                1
#define SYSTEM_LOCK__ICE_LOCK_DEP__2                2
#define SYSTEM_LOCK__ALL_LOCK_DEP__2                4

/*..hui [20-2-21오후 7:30:04] 화면 소리..*/
#define SYSTEM_SCREEN__STANDBY_CLOCK_DEP__2         1
#define SYSTEM_SCREEN__SCREEN_BRIGHTNESS_DEP__2     2
#define SYSTEM_SCREEN__SOUND_DEP__2                 4
#define SYSTEM_SCREEN__EXTRACT_LED_DEP__2           8
#define SYSTEM_SCREEN__DATE_SETTING_DEP__2          16
#define SYSTEM_SCREEN__TIME_SETTING_DEP__2          32
#endif



/*..hui [20-3-30오전 10:06:54] 메인메뉴..*/
#define MAIN_MENU__FUNCTION_SETTING_DEP__1            1
#define MAIN_MENU__SYSTEM_CONFIG_DEP__1               2
#define MAIN_MENU__REPORT_DEP__1                      4
#define MAIN_MENU__TIMER_DEP__1                       8
#define MAIN_MENU__LOCK_SETTING_DEP__1                16


/*..hui [20-3-30오전 10:07:02] 기능설정..*/
#define SYSTEM_GENERAL__DEFAULT_CUP_DEP__2            1
#define SYSTEM_GENERAL__ICE_ENABLE_DEP__2             2
#define SYSTEM_GENERAL__COLD_TEMP_DEP__2              4
#define SYSTEM_GENERAL__POWER_SAVING_DEP__2           8
#define SYSTEM_GENERAL__COLD_ENABLE_DEP__2            16


/*..hui [20-3-30오전 10:07:46] 환경설정..*/
#define SYSTEM_SCREEN__STANDBY_CLOCK_DEP__2           1
#define SYSTEM_SCREEN__SCREEN_BRIGHTNESS_DEP__2       2
#define SYSTEM_SCREEN__SOUND_DEP__2                   4
#define SYSTEM_SCREEN__EXTRACT_LED_DEP__2             8
#define SYSTEM_SCREEN__DATE_TIME_SETTING_DEP__2       16


/*..hui [20-3-30오전 10:08:01] 기록진단..*/
#define REPORT__USING_WATER__DEP_2                    1
#define REPORT__SELF_GUIDE_DEP__2                     2
#define REPORT__FAULT_DETAILS_DEP__2                  4
#define REPORT__ELECTRICITY_USAGE_REPORT_DEP__2       8


/*..hui [20-2-21오후 7:29:56] 버튼잠금..*/
#define SYSTEM_LOCK__HOT_LOCK_DEP__2                  1
#define SYSTEM_LOCK__ICE_LOCK_DEP__2                  2
#define SYSTEM_LOCK__ALL_LOCK_DEP__2                  4




#define WIFI_CONNECT_POPUP                            0
#define ERASE_WATER_POPUP                             1

















/*..hui [20-1-29오후 1:30:49] 탱크 비움 메뉴 삭제..*/
/*..hui [20-4-1오후 7:47:19] UV 설정이 코디닥터 메뉴로..*/
#define CODY_INSPECT__CODY_SERVICE_DEP_1               1
#define CODY_INSPECT__TAKEOFF_ICE_DEP_1                2
#define CODY_INSPECT__ICE_TRAY_INSPECTION_DEP_1        4
#define CODY_INSPECT__UV_SETTING_DEP_1                 8
#define CODY_INSPECT__MEMENTO_DISPLAY_DEP_1            16
#define CODY_INSPECT__PRODUCT_INFO_1                   32




#define DEVELOPER_CANCEL_COMP_DELAY_DEP_1         1
#define DEVELOPER_CANCEL_ICE_INIT_DEP_1           2




#define DEFAULT_CLOCK_THEME             0
#define MAX_NUM_CLOCK_THEME             4

#define SMART_CLOCK_THEME               0
#define MOTION_CLOCK_THEME              1
#define DIGITAL_CLOCK_THEME             2
#define CLASSIC_BLACK_CLOCK_THEME       3
#define CLASSIC_WHITE_CLOCK_THEME       4




/*#define DEFAULT_SCREEN_BRIGHT           2*/

/*..hui [20-2-25오후 3:03:23] 디폴트 값 2단계로 변경..*/
#define DEFAULT_SCREEN_BRIGHT           1



#define LCD_MENU_DEPTH_ONE              0
#define LCD_MENU_DEPTH_TWO              1
#define LCD_MENU_DEPTH_THREE            2
#define LCD_MENU_DEPTH_FOUT             3

#if 0
#define SCREEN_BRIGHT_1STEP             4
#define SCREEN_BRIGHT_2STEP             10
#define SCREEN_BRIGHT_3STEP             15
#define SCREEN_BRIGHT_4STEP             20
#define SCREEN_BRIGHT_5STEP             70
#endif

//#define SCREEN_BRIGHT_1STEP             4
#define SCREEN_BRIGHT_1STEP             1
#define SCREEN_BRIGHT_2STEP             15
#define SCREEN_BRIGHT_3STEP             30
#define SCREEN_BRIGHT_4STEP             50
#define SCREEN_BRIGHT_5STEP             70






#define SETTING_LEFT_KEY                0x01
#define SETTING_RIGHT_KEY               0x02
#define SETTING_REDO_KEY                0x04
#define SETTING_OKAY_KEY                0x08
#define SETTING_OKAY_LONG_KEY           0x10



/*..hui [19-10-17오후 12:34:09] 현재 표시중인 추출 화면..*/
#define NOW_EXTRACT_SCREEN_WATER             0
#define NOW_EXTRACT_SCREEN_ICE               1




#define WIFI_OFF                        0
#define WIFI_CONNECT                    1
#define WIFI_DISCONNECT                 2
#define WIFI_BLINK                      3


/*
#define WIFI_PAIRING_STANDBY            0
#define WIFI_PAIRING_STEP_ONE           1
#define WIFI_PAIRING_STEP_TWO           2
#define WIFI_PAIRING_STEP_THREE         3
#define WIFI_PAIRING_STEP_FOUR          4
#define WIFI_PAIRING_STEP_FIVE          5
#define WIFI_PAIRING_STEP_FINISH        6
*/

#define WIFI_HOT_LOCK_OFF               1
#define WIFI_HOT_LOCK_ON                2


//#define FEEDBACK_SHOW_TIME              15
//#define POPUP_SHOW_TIME                 15
//#define FEEDBACK_SHOW_TIME              17
//#define POPUP_SHOW_TIME                 17

#define FEEDBACK_SHOW_TIME              30
#define POPUP_SHOW_TIME                 30


#define ERROR_POPUP_SHOW_TIME           30



#define NONE_TEST_MODE                  0x00
#define PCB_TEST_MODE                   0x01
#define UART_TEST_MODE                  0x02
#define DISPLAY_TEST_MODE               0x04




#define AT_MODEL_CMD_CHP_671                   0x04
#define AT_MODEL_CMD_CHP_260                   0x01
#define AT_MODEL_CMD_CP_260                    0x02
#define AT_MODEL_CMD_CHP_590                   0x03
#define AT_MODEL_CMD_CHP_7300                  0x13
#define AT_MODEL_CMD_CHP_7300V2                0x17
#define AT_MODEL_CMD_CHP_7300E                 0x18
#define AT_MODEL_CMD_CHP_7510L                 0x22

#define AT_MODEL_CMD_CHP_7520L_MY_AIS          0x36


#define AT_RS232_STX                           0x01
#define AT_RS232_ETX                           0x04
#define AT_RS232_ACK                           0x06
#define AT_RS232_NAK                           0x15


#define AT_UART_No_CMD                         0x0000
#define AT_UART_CMD_START                      0x2000              // Start
#define AT_UART_CMD_SETTINGS                   0x3000              // Settings
#define AT_UART_CMD_WIFI                       0x3010              // WIFI
#define AT_UART_CMD_UV_ICE_FAUCET			   0x3011              // ICE FAUCET UV
#define AT_UART_CMD_SENSOR_FLOW                0x3012              // 유량 센서
#define AT_UART_CMD_CURRENT_CALC               0x3013              // DC 전류


#define AT_UART_CMD_UV_FAUCET                  0x3014              // uv faucet
#define AT_UART_CMD_DRAIN_PUMP                 0x3016              // drain pump
#define AT_UART_CMD_DC_FAN                     0x3018              // fan
#define AT_UART_CMD_CDS_SENSOR                 0x301A              // cds
#define AT_UART_CMD_UV_ICE_TANK                0x301C              // uv ice tank
#define AT_UART_CMD_ICE_FULL_SENSOR            0x301D              // ice full sensor
#define AT_UART_CMD_RTC				           0x301E              // rtc
#define AT_UART_CMD_TRAY_PUMP                  0x301F              // tray pump


#define AT_UART_CMD_SENSOR_TH                  0x3020              // 온도 센서

#define AT_UART_CMD_SENSOR_WATER_LEVEL         0x3030              // 수위 센서

#define AT_UART_CMD_SENSOR_ICE                 0x3040              // 제빙 관련 센서

#define AT_UART_CMD_NO_LOAD                    0x5000              // 전체 부하 OFF
#define AT_UART_CMD_HOT_HEATER_ON              0x5010              // 온수 히터 ON
#define AT_UART_CMD_HOT_HEATER_OFF             0x5011              // 온수 히터 OFF

#define AT_UART_CMD_ICE_HEATER_ON              0x5012              // 탈빙 히터 ON
#define AT_UART_CMD_ICE_HEATER_OFF             0x5013              // 탈빙 히터 OFF

#define AT_UART_CMD_ROOM_VALVE_ON              0x5106
#define AT_UART_CMD_ROOM_VALVE_OFF             0x5107
#define AT_UART_CMD_COLD_VALVE_ON              0x5108
#define AT_UART_CMD_COLD_VALVE_OFF             0x5109
#define AT_UART_CMD_HOT_VALVE_ON               0x510A
#define AT_UART_CMD_HOT_VALVE_OFF              0x510B

#define AT_UART_CMD_FEED_VALVE_ON              0x510E
#define AT_UART_CMD_FEED_VALVE_OFF             0x510F
#define AT_UART_CMD_NOS_VALVE_ON               0x5110
#define AT_UART_CMD_NOS_VALVE_OFF              0x5111

#define AT_UART_CMD_COLD_DRAIN_ON              0x5118
#define AT_UART_CMD_COLD_DRAIN_OFF             0x5119

#define AT_UART_CMD_COOLING_FAN_ON             0x5200
#define AT_UART_CMD_COOLING_FAN_OFF            0x5201

#define AT_UART_CMD_GAS_SWITCH_ON              0x5202
#define AT_UART_CMD_GAS_SWITCH_OFF             0x5203

#define AT_UART_CMD_ICE_TRAY_MOTOR_ON          0x5206
#define AT_UART_CMD_ICE_TRAY_MOTOR_OFF         0x5207
#define AT_UART_CMD_ICE_DOOR_MOTOR_ON          0x5208
#define AT_UART_CMD_ICE_DOOR_MOTOR_OFF         0x5209
#define AT_UART_CMD_ICE_EXTRACT_MOTOR_CW_ON    0x520A
#define AT_UART_CMD_ICE_EXTRACY_MOTOR_CW_OFF   0x520B
#define AT_UART_CMD_ICE_EXTRACT_MOTOR_CCW_ON   0x520C
#define AT_UART_CMD_ICE_EXTRACY_MOTOR_CCW_OFF  0x520D

#define AT_UART_CMD_SWING_BAR_ON               0x5210
#define AT_UART_CMD_SWING_BAR_OFF              0x5211

#define AT_UART_CMD_DRAIN_PUMP_ON              0x5302
#define AT_UART_CMD_DRAIN_PUMP_OFF             0x5303
#define AT_UART_CMD_TRAY_PUMP_ON               0x5304
#define AT_UART_CMD_TRAY_PUMP_OFF              0x5305

#define AT_UART_CMD_COMP_ON                    0x9900
#define AT_UART_CMD_COMP_OFF                   0x9901
#define AT_UART_CMD_ICE_SWITCH_ICE             0x9902
#define AT_UART_CMD_ICE_SWITCH_COLD            0x9903

#define AT_UART_CMD_SYSTEM_COMPLETE            0xFF00              // (검사종료)제품일반모드로 전환



#define NON_UART_TEST                          0x00
#define NOT_INCLUDE_FRONT_UART_TEST            0x01
#define INCLUDE_FRNOT_UART_TEST                0x02
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

/*.. sean [23-08-17 10:58:12 스마트 절전 모드 기능 추가] ..*/
#define TRIP_REST_TIME					84
#define TOTAL_MAXIMUM_REST_TIME			144
#define USE_SAVE_LEARNEND_MODE_TIME		16
/*.. sean [25-02-17 국내향 12시간으로 변경] ..*/
//#define NO_USE_SAVE_MODE_TIME			18
#define NO_USE_SAVE_MODE_TIME			12
//#define DISPLAY_SLEEP_TIME				6000
#define ONE_WEEK_TIME_HOUR				168


#define WIFI_SLEEP_MODE_START_HOUR_DEFAULT          0
#define WIFI_SLEEP_MODE_START_MINUTE_DEFAULT        0

#define WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT         6
#define WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT       0


#if CONFIG_TIME_SETTING

#define HOT_KEY_CONTINUE            1
#define COLD_KEY_CONTINUE           2

typedef enum
{
    SETTING_TIME_HOUR,
    SETTING_TIME_MIN,
    SETTING_TIME_FINISH

}TIME_SETTING;

typedef enum
{
    CURRENT_TIME_SETTING_MODE,
    //CLEAN_RESERVE_TIME_SETTING_MODE

}TIME_SETTING_MODE;
#endif

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif

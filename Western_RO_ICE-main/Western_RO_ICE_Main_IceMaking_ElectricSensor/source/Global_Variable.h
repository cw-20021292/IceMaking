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

// TDS 원수 입수 온도
#define TDS_TEMP0_0             (1024 - 768)    // 0도       256
#define TDS_TEMP1_0             (1024 - 759)    // 1도       265
#define TDS_TEMP2_0             (1024 - 751)    // 2도       273
#define TDS_TEMP3_0             (1024 - 742)    // 3도       282
#define TDS_TEMP4_0             (1024 - 733)    // 4도       291
#define TDS_TEMP5_0             (1024 - 724)    // 5도       300
#define TDS_TEMP6_0             (1024 - 715)    // 6도       309
#define TDS_TEMP7_0             (1024 - 706)    // 7도       318
#define TDS_TEMP7_5             (1024 - 701)    // 7.5도     323
#define TDS_TEMP8_0             (1024 - 696)    // 8도       328
#define TDS_TEMP9_0             (1024 - 687)    // 9도       337
#define TDS_TEMP10_0            (1024 - 677)    // 10도      347
#define TDS_TEMP11_0            (1024 - 668)    // 11도      356
#define TDS_TEMP12_0            (1024 - 658)    // 12도      366
#define TDS_TEMP12_5            (1024 - 653)    // 12.5도    371
#define TDS_TEMP13_0            (1024 - 648)    // 13도      376
#define TDS_TEMP14_0            (1024 - 639)    // 14도      385
#define TDS_TEMP15_0            (1024 - 629)    // 15도      395
#define TDS_TEMP16_0            (1024 - 619)    // 16도      405
#define TDS_TEMP17_0            (1024 - 609)    // 17도      415
#define TDS_TEMP17_5            (1024 - 604)    // 17.5도    420
#define TDS_TEMP18_0            (1024 - 599)    // 18도      425
#define TDS_TEMP19_0            (1024 - 589)    // 19도      435
#define TDS_TEMP20_0            (1024 - 580)    // 20도      444
#define TDS_TEMP21_0            (1024 - 570)    // 21도      454
#define TDS_TEMP22_0            (1024 - 560)    // 22도      464
#define TDS_TEMP22_5            (1024 - 555)    // 22.5도    469
#define TDS_TEMP23_0            (1024 - 550)    // 23도      474
#define TDS_TEMP24_0            (1024 - 540)    // 24도      484
#define TDS_TEMP25_0            (1024 - 530)    // 25도      494
#define TDS_TEMP26_0            (1024 - 521)    // 26도      503
#define TDS_TEMP27_0            (1024 - 511)    // 27도      513
#define TDS_TEMP27_5            (1024 - 506)    // 27.5도    518
#define TDS_TEMP28_0            (1024 - 501)    // 28도      523
#define TDS_TEMP29_0            (1024 - 492)    // 29도      532
#define TDS_TEMP30_0            (1024 - 482)    // 30도      542
#define TDS_TEMP31_0            (1024 - 473)    // 31도      551
#define TDS_TEMP31_5            (1024 - 477)    // 31.5도    547
#define TDS_TEMP32_0            (1024 - 463)    // 32도      561
#define TDS_TEMP32_5            (1024 - 459)    // 32.5도    565
#define TDS_TEMP33_0            (1024 - 454)    // 33도      570
#define TDS_TEMP34_0            (1024 - 445)    // 34도      579
#define TDS_TEMP35_0            (1024 - 436)    // 35도      588
#define TDS_TEMP36_0            (1024 - 427)    // 36도      597
#define TDS_TEMP37_0            (1024 - 418)    // 37도      606
#define TDS_TEMP38_0            (1024 - 409)    // 38도      615
#define TDS_TEMP39_0            (1024 - 401)    // 39도      623
#define TDS_TEMP40_0            (1024 - 392)    // 40도      632
#define TDS_TEMP41_0            (1024 - 384)    // 41도      640
#define TDS_TEMP42_0            (1024 - 375)    // 42도      649
#define TDS_TEMP43_0            (1024 - 367)    // 43도      657
#define TDS_TEMP44_0            (1024 - 359)    // 44도      665
#define TDS_TEMP45_0            (1024 - 351)    // 45도      673
#define TDS_TEMP46_0            (1024 - 343)    // 46도      681
#define TDS_TEMP47_0            (1024 - 335)    // 47도      689
#define TDS_TEMP48_0            (1024 - 328)    // 48도      696
#define TDS_TEMP49_0            (1024 - 320)    // 49도      704
#define TDS_TEMP50_0            (1024 - 313)    // 50도      711
#define TDS_TEMP51_0            (1024 - 306)    // 51도      718
#define TDS_TEMP52_0            (1024 - 299)    // 52도      725
#define TDS_TEMP53_0            (1024 - 292)    // 53도      732
#define TDS_TEMP54_0            (1024 - 285)    // 54도      739
#define TDS_TEMP55_0            (1024 - 279)    // 55도      745
#define TDS_TEMP56_0            (1024 - 272)    // 56도      752
#define TDS_TEMP57_0            (1024 - 266)    // 57도      758
#define TDS_TEMP58_0            (1024 - 260)    // 58도      764
#define TDS_TEMP59_0            (1024 - 253)    // 59도      771
#define TDS_TEMP60_0            (1024 - 247)    // 60도      777
#define TDS_TEMP61_0            (1024 - 242)    // 61도      782
#define TDS_TEMP62_0            (1024 - 236)    // 62도      788
#define TDS_TEMP63_0            (1024 - 230)    // 63도      794
#define TDS_TEMP64_0            (1024 - 225)    // 64도      799
#define TDS_TEMP65_0            (1024 - 219)    // 65도      805
#define TDS_TEMP66_0            (1024 - 214)    // 66도      810
#define TDS_TEMP67_0            (1024 - 209)    // 67도      815
#define TDS_TEMP68_0            (1024 - 204)    // 68도      820
#define TDS_TEMP69_0            (1024 - 199)    // 69도      825
#define TDS_TEMP70_0            (1024 - 194)    // 70도      830
#define TDS_TEMP71_0            (1024 - 190)    // 71도      834
#define TDS_TEMP72_0            (1024 - 185)    // 72도      839
#define TDS_TEMP73_0            (1024 - 181)    // 73도      843
#define TDS_TEMP74_0            (1024 - 176)    // 74도      848
#define TDS_TEMP75_0            (1024 - 172)    // 75도      852
#define TDS_TEMP76_0            (1024 - 168)    // 76도      856
#define TDS_TEMP77_0            (1024 - 164)    // 77도      860
#define TDS_TEMP78_0            (1024 - 160)    // 78도      864
#define TDS_TEMP79_0            (1024 - 156)    // 79도      868
#define TDS_TEMP80_0            (1024 - 152)    // 80도      872
#define TDS_TEMP81_0            (1024 - 149)    // 81도      875
#define TDS_TEMP82_0            (1024 - 145)    // 82도      879
#define TDS_TEMP83_0            (1024 - 142)    // 83도      882
#define TDS_TEMP84_0            (1024 - 138)    // 84도      886
#define TDS_TEMP85_0            (1024 - 135)    // 85도      889
#define TDS_TEMP86_0            (1024 - 132)    // 86도      892
#define TDS_TEMP87_0            (1024 - 129)    // 87도      895
#define TDS_TEMP88_0            (1024 - 126)    // 88도      898
#define TDS_TEMP89_0            (1024 - 123)    // 89도      901
#define TDS_TEMP90_0            (1024 - 120)    // 90도      904
#define TDS_TEMP91_0            (1024 - 117)    // 91도      907
#define TDS_TEMP92_0            (1024 - 114)    // 92도      910
#define TDS_TEMP93_0            (1024 - 111)    // 93도      913
#define TDS_TEMP94_0            (1024 - 109)    // 94도      915
#define TDS_TEMP95_0            (1024 - 106)    // 95도      918
#define TDS_TEMP96_0            (1024 - 104)    // 96도      920
#define TDS_TEMP97_0            (1024 - 101)    // 97도      923
#define TDS_TEMP98_0            (1024 - 99)     // 98도      925
#define TDS_TEMP99_0            (1024 - 97)     // 99도      927
#define TDS_TEMP100_0           (1024 - 94)     // 100도     930


typedef enum
{
    LED_Display__VERSION = 0,
    LED_Display__MAIN,
    LED_Display__ALL_LOCK,
    LED_Display__ALTITUDE_SETTING,
    LED_Display__SOUND_SETTING,
    LED_Display__WATER_EXTRACT,
    LED_Display__ICE_EXTRACT,
    LED_Display__STEAM_CLEAN,
    LED_Display__FLUSHING,
    LED_Display__FILTER_COVER_OPEN,
    LED_Display__FILTER_ALARM,
    LED_Display__TIME_SETTING,
    LED_Display__WIFI_PAIRING,
    LED_Display__CT_FILTER_TYPE,

    LED_Display__SETTING,
    LED_Display__BUTTON_SET,
    LED_Display__SLEEP,
    LED_Display__ERROR,
    LED_Display__UV,
    LED_Display__DEBUG,
    LED_Display__MEMENTO,
    LED_Display__FOTA_START,
    LED_Display__SELF_TEST,
    LED_Display__ACID_CLEAN

}LED_STEP;

//#define LED_DIMMING_FULL           10



typedef enum
{
    ICE_HEATER_CONTROL_OFF = 0,
    ICE_HEATER_CONTROL_10_UNDER,
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

    STATE_5_PREHEAT_HOTGAS_MOVE = 5,
    STATE_6_CALC_PREHEAT_TIME = 6,
    STATE_7_PREHEAT_OPERATION = 7,

    STATE_10_ICE_TRAY_MOVE_UP = 10,
    STATE_11_WAIT_ROOM_WATER_FULL = 11,
    STATE_12_CONT_ICE_SWITCH_MOVE = 12,    /////
    STATE_13_CONT_RPS_SETTING = 13,
    STATE_14_CHECK_ICE_TRAY_HZ = 14,

    STATE_20_WATER_IN_ICE_TRAY = 20,
    STATE_21_ICE_SWITCH_MOVE = 21,

    STATE_30_CALC_ICE_MAKING_TIME = 30,
    STATE_31_MAIN_ICE_MAKING = 31,

    STATE_40_ICE_TRAY_MOVE_DOWN = 40,
    STATE_41_GAS_SWITCH_HOT_GAS = 41,
    STATE_42_CALC_HOT_GAS_TIME = 42,
    STATE_43_ICE_TAKE_OFF = 43,

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
    COOLING_DISPLAY_0_OFF,
    COOLING_DISPLAY_1_ON

}COOLING_DISPLAY;

typedef enum
{
    HEATING_DISPLAY_0_INIT,
    HEATING_DISPLAY_1_OFF,
    HEATING_DISPLAY_2_ON

}HEATING_DISPLAY;



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
    DISPLAY_NUM_LARGE_L,
    DISPLAY_NUM_SMALL_d,
    DISPLAY_NUM_SMALL_b,

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

typedef enum
{
    SETTING_TIME_HOUR,
    SETTING_TIME_MIN,
    SETTING_TIME_FINISH

}TIME_SETTING;

typedef enum
{
    CURRENT_TIME_SETTING_MODE,
    CLEAN_RESERVE_TIME_SETTING_MODE

}TIME_SETTING_MODE;



#define DUTY_100_PERCENT               10
#define DUTY_20_PERCENT                1


#define FIXED_DISPLAY                  0
#define DIRECT_DISPLAY                 1


#if 0
typedef enum
{
    DUTY_OUT_DIMMING_LOW,
    DUTY_OUT_DIMMING_HIGH,
    DUTY_OUT_DIMMING_EXTRACT_LOW,
    DUTY_OUT_DIMMING_EXTRACT_HIGH

}DUTY_SET_DATA;
#endif

#if 0
typedef enum
{
    DIMMING__ON_OFF_SETTING_SELECT,
    DIMMING__ON_OFF_ICE_SELECT,
    DIMMING__ON_OFF_HOT_SELECT,
    DIMMING__ON_OFF_AMBIENT_SELECT,
    DIMMING__ON_OFF_COLD_SELECT,
    DIMMING__ON_OFF_AMOUNT_SELECT,
    DIMMING__ON_OFF_ICE_FIRST_TEXT,
    DIMMING__ON_OFF_ICE_LOCK_ICON,
    DIMMING__ON_OFF_HOT_LOCK_ICON,
    DIMMING__ON_OFF_HOT_TEMP_1_2_3,
    DIMMING__ON_OFF_COLD_TEMP_1_2_3,
    DIMMING__ON_OFF_ICE_FULL_TEXT,
    DIMMING__ON_OFF_ICE_EXTRACT,
    DIMMING__ON_OFF_WATER_EXTRACT,

    DIMMING__ON_OFF_SETTING_ICE_FIRST,
    DIMMING__ON_OFF_SETTING_ICE_LCOK,
    DIMMING__ON_OFF_SETTING_HOT_LOCK,
    DIMMING__ON_OFF_SETTING_TOUCH_LOCK,
    DIMMING__ON_OFF_SETTING_STEAM_OFF,
    DIMMING__ON_OFF_SETTING_ECO_MODE,

    DIMMING__ON_OFF_PREPARING_TEXT,
    DIMMING__ON_OFF_ERROR_TEXT,
    DIMMING__ON_OFF_WATER_USAGE_TEXT,
    DIMMING__ON_OFF_ECCO_ICON,
    DIMMING__ON_OFF_oF_ICON,
    DIMMING__ON_OFF_PERCENT_ICON,
    DIMMING__ON_OFF_oC_ICON,
    DIMMING__ON_OFF_Gal_ICON,

    DIMMING__ON_OFF_STEAM_CLEAN_TEXT,
    DIMMING__ON_OFF_UV_CARE_TEXT,
    DIMMING__ON_OFF_UV_CARE_UNDER_BAR,    ///////
    DIMMING__ON_OFF_WATER_TANK_TEXT,
    DIMMING__ON_OFF_ICE_TRAY_TEXT,
    DIMMING__ON_OFF_ICE_TANK_TEXT,

    DIMMING__ON_OFF_FILTER_LIFE_TEXT,
    DIMMING__ON_OFF_WIFI_ICON,
    DIMMING__ON_OFF_Oz_ICON,
    DIMMING__ON_OFF_Min_ICON,
    DIMMING__ON_OFF_Left_ICON,            ///////
    DIMMING__ON_OFF_ml_ICON,
    DIMMING__ON_OFF_days_ICON,

    DIMMING__ON_OFF_TEMP_BAR_1_1,
    DIMMING__ON_OFF_TEMP_BAR_1_2,
    DIMMING__ON_OFF_TEMP_BAR_1_3,
    DIMMING__ON_OFF_TEMP_BAR_1_4,
    DIMMING__ON_OFF_AMOUNT_BAR_2_1,
    DIMMING__ON_OFF_AMOUNT_BAR_2_2,
    DIMMING__ON_OFF_AMOUNT_BAR_2_3,
    DIMMING__ON_OFF_AMOUNT_BAR_2_4,
    DIMMING__ON_OFF_AMOUNT_BAR_2_5,
    DIMMING__ON_OFF_LEFT_SEGMENT_1_0_0,
    DIMMING__ON_OFF_LEFT_SEGMENT_0_2_0,
    DIMMING__ON_OFF_LEFT_SEGMENT_0_0_3,

    DIMMING__ON_OFF_RIGHT_SEGMENT_1_0_0,
    DIMMING__ON_OFF_RIGHT_SEGMENT_0_2_0,
    DIMMING__ON_OFF_RIGHT_SEGMENT_0_0_3

}DIMMING_ON_OFF_DATA;
#endif

typedef enum
{
    DIMMING__PERCENT_SETTING_SELECT,
    DIMMING__PERCENT_ICE_SELECT,

    DIMMING__PERCENT_HOT_SELECT,
    DIMMING__PERCENT_AMBIENT_SELECT,

    DIMMING__PERCENT_COLD_SELECT,
    DIMMING__PERCENT_AMOUNT_SELECT,

    DIMMING__PERCENT_SETTING_ICE_FIRST,
    DIMMING__PERCENT_SETTING_ICE_LCOK,

    DIMMING__PERCENT_SETTING_HOT_LOCK,
    DIMMING__PERCENT_SETTING_TOUCH_LOCK,

    DIMMING__PERCENT_SETTING_ECO_MODE,

    DIMMING__PERCENT_PREPARING_TEXT,
    DIMMING__PERCENT_CURRENT_TEXT,

    DIMMING__PERCENT_FILTER_FLUSHING_TEXT,
    DIMMING__PERCENT_ECCO_ICON,

    DIMMING__PERCENT_oF_ICON,
    DIMMING__PERCENT_PERCENT_ICON,

    DIMMING__PERCENT_oC_ICON,

    DIMMING__PERCENT_ICE_TANK_CLEAN_TEXT,
    DIMMING__PERCENT_UV_CARE_UNDER_BAR_TEXT,

    DIMMING__PERCENT_WIFI_BLUE_ICON,
    DIMMING__PERCENT_WATER_TANK_TEXT,

    DIMMING__PERCENT_ICE_TRAY_TEXT,
    DIMMING__PERCENT_ICE_TANK_TEXT,

    DIMMING__PERCENT_WIFI_WHITE_ICON,
    DIMMING__PERCENT_Oz_ICON,

    DIMMING__PERCENT_Min_Left_ICON,
    DIMMING__PERCENT_ml_ICON,

    DIMMING__PERCENT_days_Left_ICON,
    DIMMING__PERCENT_ICE_FIRST_TEXT,

    DIMMING__PERCENT_ICE_LOCK_ICON,
    DIMMING__PERCENT_HOT_LOCK_ICON,

    DIMMING__PERCENT_ICE_FULL_TEXT,
    DIMMING__PERCENT_NEW_ICE_MAKING_TEXT,

    DIMMING__PERCENT_NEW_HOT_HEATING_TEXT,
    DIMMING__PERCENT_NEW_COLD_COOLING_TEXT,

    DIMMING__PERCENT_NEW_LOW_WATER_TEXT,
    DIMMING__PERCENT_NEW_REPLACE_FILTER_TEXT,

    DIMMING__PERCENT_NEW_REPLACE_FILTER_1_NUM,
    DIMMING__PERCENT_NEW_REPLACE_FILTER_2_NUM,

    DIMMING__PERCENT_NEW_REPLACE_FILTER_3_NUM,
    DIMMING__PERCENT_AMOUNT_BAR_2_1,

    DIMMING__PERCENT_AMOUNT_BAR_2_2,
    DIMMING__PERCENT_AMOUNT_BAR_2_3,

    DIMMING__PERCENT_AMOUNT_BAR_2_4,
    DIMMING__PERCENT_AMOUNT_BAR_CONTINUE,

    DIMMING__PERCENT_TEMP_BAR_1_1,
    DIMMING__PERCENT_TEMP_BAR_1_2,

    DIMMING__PERCENT_TEMP_BAR_1_3,
    DIMMING__PERCENT_TEMP_BAR_1_4,

    DIMMING__PERCENT_LEFT_SEGMENT_1_0_0,
    DIMMING__PERCENT_LEFT_SEGMENT_0_2_0,

    DIMMING__PERCENT_LEFT_SEGMENT_0_0_3,
    DIMMING__PERCENT_RIGHT_SEGMENT_1_0_0,

    DIMMING__PERCENT_RIGHT_SEGMENT_0_2_0,
    DIMMING__PERCENT_RIGHT_SEGMENT_0_0_3,

    DIMMING__PERCENT_ICE_EXTRACT,
    DIMMING__PERCENT_WATER_EXTRACT


}DIMMING_PERCENT_DATA;






typedef enum
{
    ANIMATION__DIMMING__WATER_OUT,
    ANIMATION__DIMMING__ICE_OUT,
    ANIMATION__DIMMING__FILTER_FLUSHING,
    ANIMATION__DIMMING__CURRENT,
    ANIMATION__DIMMING__PREPARING,
    ANIMATION__DIMMING__ICE_TANK_CLEAN,
    ANIMATION__DIMMING__UV_CARE_UNDERBAR,
    ANIMATION__DIMMING__WATER_TANK,
    ANIMATION__DIMMING__ICE_TRAY,
    ANIMATION__DIMMING__ICE_TANK,
    ANIMATION__DIMMING__LEFT_SEG_1_0_0,
    ANIMATION__DIMMING__LEFT_SEG_0_2_0,
    ANIMATION__DIMMING__LEFT_SEG_0_0_3,
    ANIMATION__DIMMING__RIGHT_SEG_1_0_0,
    ANIMATION__DIMMING__RIGHT_SEG_0_2_0,
    ANIMATION__DIMMING__RIGHT_SEG_0_0_3,

    ANIMATION__DIMMING__oF,
    ANIMATION__DIMMING__PERCENT,
    ANIMATION__DIMMING__oC,
    ANIMATION__DIMMING__Oz,
    ANIMATION__DIMMING__Min_Left,
    ANIMATION__DIMMING__mL,
    ANIMATION__DIMMING__Days_Left,
    //ANIMATION__DIMMING__LEFT_TEMP_BAR,
    //ANIMATION__DIMMING__RIGHT_AMOUNT_BAR,

    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_1,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_2,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_3,
    ANIMATION__DIMMING__LEFT_SETTING_BAR_1_4,

    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_1,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_2,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_3,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_2_4,
    ANIMATION__DIMMING__AMOUNT_SETTING_BAR_CONTINUE,

    ANIMATION__DIMMING__SETTINGS,
    ANIMATION__DIMMING__ICE,
    ANIMATION__DIMMING__HOT,
    ANIMATION__DIMMING__AMBIENT,
    ANIMATION__DIMMING__COLD,
    ANIMATION__DIMMING__AMOUNT,

    ANIMATION__DIMMING__ECO_ICON,
    ANIMATION__DIMMING__WIFI_ICON,
    ANIMATION__DIMMING__ICE_FIRST_TEXT,
    ANIMATION__DIMMING__ICE_FULL_TEXT,
    ANIMATION__DIMMING__ICE_LOCK_ICON,
    ANIMATION__DIMMING__HOT_LOCK_ICON,

    ANIMATION__DIMMING__SETTING_ICE_FIRST,
    ANIMATION__DIMMING__SETTING_ICE_LOCK,
    ANIMATION__DIMMING__SETTING_HOT_LOCK,
    ANIMATION__DIMMING__SETTING_TOUCH_LOCK,
    ANIMATION__DIMMING__SETTING_ECO_MODE,

    ANIMATION__DIMMING__NEW_ICE_MAKING,
    ANIMATION__DIMMING__NEW_HOT_HEATING,
    ANIMATION__DIMMING__NEW_COLD_COOLING,
    ANIMATION__DIMMING__NEW_LOW_WATER,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_TEXT,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_1_NUM,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_2_NUM,
    ANIMATION__DIMMING__NEW_REPLACE_FILTER_3_NUM


}DIMMING_ANIMATION;

#define START_ANIMATION_DIIMMING                      1
#define STOP_ANIMATION_DIIMMING                       0






#define DIIMMING__0_PERCENT                         0

#define DIIMMING__10_PERCENT                        1
#define DIIMMING__20_PERCENT                        2
#define DIIMMING__30_PERCENT                        3
#define DIIMMING__40_PERCENT                        4
#define DIIMMING__50_PERCENT                        5
#define DIIMMING__60_PERCENT                        6
#define DIIMMING__70_PERCENT                        7
#define DIIMMING__80_PERCENT                        8
#define DIIMMING__90_PERCENT                        9
#define DIIMMING__100_PERCENT                       10


#if 0
//1608
#define TOP_ICON__DIMMING__50_PERCENT               7
#define SEGMENT__DIMMING__90_PERCENT                9
#define CENTER_ICON__DIMMING__50_PERCENT            7
#define FUNCTION_ICON__DIMMING__70_PERCENT          7
#define SETTING_TEXT__DIMMING__50_PERCETN           5
#define EXTRACT__DIMMING__40_PERCETN                4
#define ICE_FULL__DIMMING__40_PERCETN               7
#endif

//2012
#define TOP_ICON__DIMMING__50_PERCENT               7
#define SEGMENT__DIMMING__90_PERCENT                8
#define CENTER_ICON__DIMMING__50_PERCENT            7
#define FUNCTION_ICON__DIMMING__70_PERCENT          8
#define SETTING_TEXT__DIMMING__50_PERCETN           7
#define EXTRACT__DIMMING__40_PERCETN                6
#define ICE_FULL__DIMMING__40_PERCETN               7

/*..hui [24-3-27오후 6:01:33] 디자인.. 와이파이 LED 화이트 10%, 블루 10%로 적용 요청..*/
#define WIFI_WHITE_LED_70_PERCENT                   7
#define WIFI_BLUE_LED_100_PERCENT                   10
#define WIFI_BLUE_WITH_WHITE_LED_10_PERCENT         1

#if 0
//mix
#define TOP_ICON__DIMMING__50_PERCENT               10
#define SEGMENT__DIMMING__90_PERCENT                9
#define CENTER_ICON__DIMMING__50_PERCENT            10
#define FUNCTION_ICON__DIMMING__70_PERCENT          9
#define SETTING_TEXT__DIMMING__50_PERCETN           10
#define EXTRACT__DIMMING__40_PERCETN                6
#define ICE_FULL__DIMMING__40_PERCETN               10
#endif


/*#define EXTRACT_TOTAL_STEP                          5*/
#define EXTRACT_TOTAL_STEP                          4


//#define BREATH_ANIMATION_DUTY         40
//#define BREATH_ANIMATION_TIME         150

/*..hui [23-5-24오후 2:08:22] 1초주기 괜찮은거..*/
//#define BREATH_ANIMATION_DUTY         50
//#define BREATH_ANIMATION_TIME         80

/*..hui [23-5-24오후 2:14:41] 1초 주기..*/
//#define BREATH_ANIMATION_DUTY         40
//#define BREATH_ANIMATION_TIME         100

/*..hui [23-5-24오후 2:09:49] 0.5초 주기 괜찮은거..*/
//#define BREATH_ANIMATION_DUTY         50
//#define BREATH_ANIMATION_TIME         40

/*..hui [23-5-24오후 2:14:01] 0.5초 주기..*/
//#define BREATH_ANIMATION_DUTY         40
//#define BREATH_ANIMATION_TIME         50

/*..hui [23-5-31오전 9:24:07] 0.75초 주기..*/
#define BREATH_ANIMATION_DUTY         50
#define BREATH_ANIMATION_TIME         60



/*..hui [23-5-31오전 9:36:09] 6회.. = 0.75 * 6 = 4.5초....*/
//////#define BREATH_FLICKER_COUNT          45

/*..hui [23-5-31오전 9:36:09] 4회.. = 0.75 * 4 = 3초....*/
#define BREATH_FLICKER_COUNT          29




#define LED_SLEEP_ENTER_TIME       6000
#define LED_SLEEP_WAKEUP_TIME      100




typedef enum
{
    DEBUG__COMP_DELAY,
    DEBUG__COLD_TEMP,
    DEBUG__ROOM_TEMP,
    DEBUG__HOT_TEMP,
    DEBUG__MIXING_TEMP,
    DEBUG__OUT_DOOR_FRONT_TEMP,

    DEBUG__OUT_DOOR_SIDE_TEMP,
    DEBUG__OUT_DOOR_FINAL_TEMP,
    /*DEBUG__TRAY_TEMP,*/
    /*DEBUG__TRAY_AVERAGE_TEMP,*/

    DEBUG__EVA_ICE_TEMP,

    DEBUG__FLOW_HZ,
    DEBUG__DRAIN_HZ,

    DEBUG__ICE_FULL_AD,
    DEBUG__LEAK_AD,
    DEBUG__UV_WATER_AD,
    DEBUG__UV_ICE_TANK_AD,
    DEBUG__UV_ICE_TRAY_1_AD,
    DEBUG__UV_ICE_TRAY_2_AD,

    DEBUG__BLDC_TARGET,
    DEBUG__BLDC_OPERATION,
    DEBUG__BLDC_ERROR,
    DEBUG__BLDC_TEMP,

    DEBUG__ICE_STEP,
    DEBUG__ICE_TRAY_INPUT,
    DEBUG__ICE_TRAY_ERROR,
    DEBUG__ICE_WATER_LEVEL,
    DEBUG__ICE_DRAIN_LEVEL,
    DEBUG__FEED_NOS_DCFAN,
    DEBUG__ROOM_COLD_HOT,

    DEBUG__ROOM_FILTER_REED,
    DEBUG__ROOM_TOP_REED,
    DEBUG__COMP_ICEHEATER_HOTHEATER,

    DEBUG__FILTER_CHANGE_TYPE,
    DEBUG__NEO_RESET_DAY,
    DEBUG__RO_RESET_DAY,
    DEBUG__INO_RESET_DAY,
    DEBUG__NEO_WATER_USAGE,
    DEBUG__RO_WATER_USAGE,
    DEBUG__INO_WATER_USAGE,
    DEBUG__STER_LOW_WATER_ERR,
    DEBUG__INO_STER_DRAIN_ERR



}DEBUG_STEP;


typedef enum
{
    FLUSHING_NONE_STATE = 0,

    FLUSHING_STANDBY_STATE,
    FLUSHING_MAIN_STATE,

    FLUSHING_TANK_STATE,

    FLUSHING_FINISH_STATE

}FLUSHING_STEP;


typedef enum
{
    ACID_CLEAN_NONE_STATE = 0,

    ACID_CLEAN_STANDBY,
    ACID_CLEAN_PREPARE,
    ACID_CLEAN_CHANGE_FILTER,
    ACID_CLEAN_WAIT_1_HOUR,
    ACID_CLEAN_RINSE,
    ACID_CLEAN_FINISH
}ACID_CLEAN_STEP;




typedef enum
{
    STER_MODE_NONE_STATE,
    STER_MODE_PREPARE,

    STER_MODE_CIRCULATION_HOT_STATE,

    STER_MODE_HOT_SPRAY_STATE,
    /*STER_MODE_CIRCULATION_STATE,*/
    STER_MODE_LUKEWARM_SPRAY_STATE,
    STER_MODE_FINAL_CLEAN_STATE,

    STER_MODE_ICE_TRAY_CLEAN_PREPARE,
    STER_MODE_ICE_TRAY_CLEAN,

    STER_MODE_MELT_ICE_PREPARE,
    STER_MODE_MELT_ICE,

    STER_MODE_FINISH

}ICE_STER_MODE;

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
    GREEN_WEEK,
    INTENSIVE_WEEK
}POWER_SAVING_STATE;


typedef enum
{
    HOT_STER_TEMP_HIGH_MODE,
    HOT_STER_TEMP_LOW_MODE

}HOT_STER_OP_TEMP;




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
    DC_LOAD_6__HOT_IN_VALVE,
    DC_LOAD_7__AIR_FEED_VALVE,
    DC_LOAD_8__COLD_DRAIN_VALVE,
    DC_LOAD_9__ICE_TRAY_IN_VALVE,
    DC_LOAD_10__FLUSHING_FEED,
    DC_LOAD_11__RO_FLUSHING_MOTOR,
    DC_LOAD_12__HOT_OVERHEAT_VALVE,
    DC_LOAD_13__HOT_STER_LEFT_VALVE,
    DC_LOAD_14__HOT_STER_RIGHT_VALVE,
    DC_LOAD_15__FLUSHING_NOS_VALVE,

    DC_LOAD_16__COLD_FAN,

    SENSOR_17__ICE_TRAY_FLOW_SENSOR,
    SENSOR_18__RO_DRAIN_FLOW_SENSOR,

    DC_LOAD_19__UV_ICE_TANK_1_2_BACK,
    DC_LOAD_20__UV_ICE_TRAY_1_2,
    DC_LOAD_21__UV_COLD_TANK_1_2,
    DC_LOAD_22__UV_ICE_TANK_3_FRONT,

    DC_LOAD_23__SWING_BAR,

    DC_LOAD_24__ICE_DOOR_MOTOR,
    DC_LOAD_25__GAS_SWITCH_MOTOR,

    DC_LOAD_26__DRAIN_PUMP,
    DC_LOAD_27__ICE_TRAY_PUMP,
    DC_LOAD_28__ICE_FULL_SENSOR

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





#define LowByte(data)                   ((U8)((data) & 0xff))
#define HighByte(data)                  ((U8)(((data) >> 8) & 0xff))

#define LowWord(data)                   ((U16)((data) & 0xFFFF))
#define HighWord(data)                  ((U16)(((data) >> 16) & 0xFFFF)

#define BitRead(value, bit)             (((value) >> (bit)) & 0x01)
#define BitSet(value, bit)              ((value) |= (1UL << (bit)))
#define BitClear(value, bit)            ((value) &= ~(1UL << (bit)))
#define BitWrite(value, bit, bitvalue)  (bitvalue ? BitSet(value, bit) : BitClear(value, bit))


#define ON_OFF_DISPLAY_OFF                         0
#define ON_OFF_DISPLAY_ICE_SET                     1
#define ON_OFF_DISPLAY_EXTRA_COLD_STE              2
#define ON_OFF_DISPLAY_STEAM_OFF_SET               4





#define BUTTON_SET_DISPLAY_OFF                     0
#define BUTTON_SET_HOT_DISPLAY                     1
#define BUTTON_SET_MUTE_DISPLAY                    2
#define BUTTON_SET_ICE_OFF_DISPLAY                 4
#define BUTTON_SET_RECOVER_FAST_ICE_DISPLAY        8

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

#if 0
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
#endif

/*..hui [20-10-14오후 4:14:19] 유량센서 변경에 따라 변경..*/
//#define C_ICE_TRAY_FILL_200CC          1010
/*#define C_ICE_TRAY_FILL_200CC            2500*/
/*..hui [24-4-11오전 9:18:41] 트레이 형상 변경. 약 10cc 정도 추가 입수해야함..*/
#define C_ICE_TRAY_FILL_200CC            2680


#define ICE_MAKE_TIME                   899                        /* 외기 25'C, 시수 온도 25'C 기준 */
#define PREHEAT_AMB_TEMP                25

#define HOT_GAS_NOISE_REDUCE_TIME           300


#define HEAT_TORAL_TIME_10_UNDER            5150
#define HEAT_TORAL_TIME_15_UNDER            3600
#define HEAT_TORAL_TIME_20_UNDER            3000
#define HEAT_TORAL_TIME_25_UNDER            2700
#define HEAT_TORAL_TIME_30_UNDER            2700
#define HEAT_TORAL_TIME_35_UNDER            2700
#define HEAT_TORAL_TIME_35_OVER             2700




#define HOT_GAS_TIME_9_UNDER_765S           7650
#define HOT_GAS_TIME_13_UNDER_600S          6000
#define HOT_GAS_TIME_19_UNDER_180S          1800
/*#define HOT_GAS_TIME_24_UNDER_30S           300*/
/*#define HOT_GAS_TIME_29_UNDER_20S           200*/
#define HOT_GAS_TIME_24_UNDER_30S           350
#define HOT_GAS_TIME_29_UNDER_20S           250
#define HOT_GAS_TIME_30_OVER_15S            150



#define PREHEAT_TIME_14_UNDER_600S          6000
#define PREHEAT_TIME_20_UNDER_360S          3600
#define PREHEAT_TIME_25_UNDER_360S          3600



/*#define HOT_BLOCKED_FLOW_HZ              5*/
#define HOT_BLOCKED_FLOW_HZ              10

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


#define ALTITUDE_1_MODE_HIGH           0
#define ALTITUDE_2_MODE_MID            1
#define ALTITUDE_3_MODE_LOW            2
#define ALTITUDE_4_MODE_VERY_LOW       3


/*#define SLEEP_MODE_HEATER_OFF_TEMP                          80*/
/*#define SLEEP_MODE_HEATER_ON_TEMP                           43*/

/*..hui [24-11-15오후 4:46:18] 취침모드/미사용절전모드 고도모드에따른 분리..*/
#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_1              89
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_1               60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_2              89
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_2               60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_3              86
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_3               60

#define SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_4              79
#define SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_4               60




#define ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_OVER         96
#define ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_OVER          88

#define ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER        96
#define ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER         90

/*..hui [24-11-15오후 4:44:06] 고도모드 변경.. 냉동팀..*/
#define ALTITUDE_2_MODE_HEATER_OFF_TEMP                     91
#define ALTITUDE_2_MODE_HEATER_ON_TEMP                      85

#define ALTITUDE_3_MODE_HEATER_OFF_TEMP                     86
#define ALTITUDE_3_MODE_HEATER_ON_TEMP                      80

#define ALTITUDE_4_MODE_HEATER_OFF_TEMP                     79
#define ALTITUDE_4_MODE_HEATER_ON_TEMP                      73


#if 0
#define ALTITUDE_2_MODE_HEATER_OFF_TEMP                     94
#define ALTITUDE_2_MODE_HEATER_ON_TEMP                      86

#define ALTITUDE_3_MODE_HEATER_OFF_TEMP                     91
#define ALTITUDE_3_MODE_HEATER_ON_TEMP                      83

#define ALTITUDE_4_MODE_HEATER_OFF_TEMP                     89
#define ALTITUDE_4_MODE_HEATER_ON_TEMP                      81
#endif

/*#define DEV_ADDR_EEP                          0xA0*/     /* Device EEPROM - AT24C02C */


#define DEV_ADDR_EEP          0xAE  /* Device EEPROM - ISL12026 */
#define DEV_ADDR_RTC          0xDE  /* Device RTC - ISL12026 */


/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_START               0x0040
/////////////////////////////////////////////////////////////////////////////
#define SPECIAL_SETTING_START_ADDR            0x0051
#define SPECIAL_SETTING_LENGTH                15

#define EEPROM_ADDR1_COLD_SETTING             0x0051
#define EEPROM_ADDR1_HOT_LOCK                 0x0052
#define EEPROM_ADDR1_ALL_LOCK                 0x0053
#define EEPROM_ADDR1_MUTE_SETTING             0x0054
#define EEPROM_ADDR1_COLD_LEVEL               0x0055
#define EEPROM_ADDR1_HOT_ENABLE               0x0056
#define EEPROM_ADDR1_INSTALL_FLUSHING         0x0057
#define EEPROM_ADDR1_FILTER_FLUSHING          0x0058
#define EEPROM_ADDR1_FIRST_TIME_SETTING       0x0059
#define EEPROM_ADDR1_SOUND_TYPE               0x005A
#define EEPROM_ADDR1_VOICE_VOLUME             0x005B
#define EEPROM_ADDR1_ALTITUDE                 0x005C
#define EEPROM_ADDR1_LANGUAGE_TYPE            0x005D
#define EEPROM_ADDR1_CT_FORCED_FLUSHING       0x005E
#define EEPROM_ADDR1_CT_REPLACE_FILTER        0x005F


/////////////////////////////////////////////////////////////////////////////
#define ICE_SETTING_START_ADDR                0x0060
#define ICE_SETTING_LENGTH                    5

#define EEPROM_ADDR2_ICE_LOCK                 0x0060
#define EEPROM_ADDR2_ICE_ON_OFF               0x0061
#define EEPROM_ADDR2_ICE_MAKE_PRIORITY        0x0062
#define EEPROM_ADDR2_RECOVER_FAST_ICE         0x0063
#define EEPROM_ADDR2_ACID_CLEAN               0x0064



/////////////////////////////////////////////////////////////////////////////
#define FUNCTION_SETTING_START_ADDR           0x0070
#define FUNCTION_SETTING_LENGTH               15

#define EEPROM_ADDR3_OWER_SAVE_SETTING        0x0070
#define EEPROM_ADDR3_CIRCULATION_DRAIN        0x0071
#define EEPROM_ADDR3_AUTO_UV_CONTROL          0x0072
#define EEPROM_ADDR3_EXTRACT_LED_ONOFF        0x0073

#define EEPROM_ADDR3_SMART_UNUSED_TIME        0x0074
#define EEPROM_ADDR3_NOT_USE                  0x0075
#define EEPROM_ADDR3_NOT_USE_2                0x0076

#define EEPROM_ADDR3_STEAM_OFF                0x0077
#define EEPROM_ADDR3_PERIOD_STER_HOUR         0x0078
#define EEPROM_ADDR3_PERIOD_STER_MINUTE       0x0079

#define EEPROM_ADDR3_SLEEP_MODE_ENABLE        0x007A
#define EEPROM_ADDR3_SLEEP_START_HOUR         0x007B
#define EEPROM_ADDR3_SLEEP_START_MINUTE       0x007C
#define EEPROM_ADDR3_SLEEP_FINISH_HOUR        0x007D
#define EEPROM_ADDR3_SLEEP_FINISH_MINUTE      0x007E



/////////////////////////////////////////////////////////////////////////////
#define ETC_SAVE_START_ADDR                   0x0080
#define ETC_SAVE_LENGTH                       2

#define EEPROM_ADDR4_CUP_LEVEL                0x0080
#define EEPROM_ADDR4_WATER_SELECT_DEFAULT     0x0081


/////////////////////////////////////////////////////////////////////////////
#define MEMENTO_START_ADDR                    0x0090
#define MEMENTO_LENGTH                        5

#define EEPROM_ADDR5_MEMENTO_NUM0             0x0090
#define EEPROM_ADDR5_MEMENTO_NUM1             0x0091
#define EEPROM_ADDR5_MEMENTO_NUM2             0x0092
#define EEPROM_ADDR5_MEMENTO_NUM3             0x0093
#define EEPROM_ADDR5_MEMENTO_NUM4             0x0094

/////////////////////////////////////////////////////////////////////////////
#define IOT_FUNCTION_ADDR                     0x00A0
#define IOT_FUNCTION_LENGTH                   16

#define EEPROM_ADDR6_CUP_LEVEL_SELECT         0x00A0
//#define EEPROM_ADDR6_CUP_LEVEL_SELECT_B       0x00A1
#define EEPROM_ADDR6_CUP_LEVEL_ORDER          0x00A2
#define EEPROM_ADDR6_OC_OF_SELECT             0x00A3
#define EEPROM_ADDR6_OZ_ML_SELECT             0x00A4
#define EEPROM_ADDR6_HOT_TEMP_LEVEL_ORDER     0x00A5
#define EEPROM_ADDR6_HOT_TEMP_DEFAULT         0x00A6
//#define EEPROM_ADDR6_WATER_USAGE_GAL          0x00A7
//#define EEPROM_ADDR6_WATER_USAGE_GAL_B        0x00A8
//#define EEPROM_ADDR6_FILTER_RESET_DAY_NEO     0x00A9
//#define EEPROM_ADDR6_FILTER_RESET_DAY_NEO_B   0x00AA
//#define EEPROM_ADDR6_FILTER_RESET_DAY_RO      0x00AB
//#define EEPROM_ADDR6_FILTER_RESET_DAY_RO_B    0x00AC
#define EEPROM_ADDR6_CHILD_LOCK_ENABLE        0x00AD
#define EEPROM_ADDR6_FOTA_START               0x00AE
#define EEPROM_ADDR6_FILTER_CHANGE_CYCLE      0x00AF

/////////////////////////////////////////////////////////////////////////////
#define WATER_USAGE_ADDR                      0x00B0
#define WATER_USAGE_LENGTH                    13

#define EEPROM_ADDR7_WATER_USAGE__NEO         0x00B0
#define EEPROM_ADDR7_WATER_USAGE__NEO_B       0x00B1
#define EEPROM_ADDR7_WATER_USAGE__RO          0x00B2
#define EEPROM_ADDR7_WATER_USAGE__RO_B        0x00B3
#define EEPROM_ADDR7_WATER_USAGE__INO         0x00B4
#define EEPROM_ADDR7_WATER_USAGE__INO_B       0x00B5

#define EEPROM_ADDR7_FILTER_RESET_DAY__NEO    0x00B6
#define EEPROM_ADDR7_FILTER_RESET_DAY__NEO_B  0x00B7
#define EEPROM_ADDR7_FILTER_RESET_DAY__RO     0x00B8
#define EEPROM_ADDR7_FILTER_RESET_DAY__RO_B   0x00B9
#define EEPROM_ADDR7_FILTER_RESET_DAY__INO    0x00BA
#define EEPROM_ADDR7_FILTER_RESET_DAY__INO_B  0x00BB

#define EEPROM_ADDR7_FILTER_CHANGE_TYPE       0x00BC

/////////////////////////////////////////////////////////////////////////////
#define DEBUG_DATA_ADDR                       0x00C0
#define DEBUG_DATA_LENGTH                     2

#define EEPROM_ADDR8_STER_DRAIN_STOP          0x00C0
#define EEPROM_ADDR8_STER_LOW_WATER_STOP      0x00C1



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#define WIFI_DATA_ADDR                        0x00E0
#define WIFI_DATA_LENGTH                      4

#define EEPROM_ADDR_WIFI_POWER                0x00E0   // WIFI On/Off State
#define EEPROM_ADDR_FIRST_PARING              0x00E1   // WIFI First Paring Check
#define EEPROM_ADDR_FOTA_MODULE               0x00E2   // WIFI Module Fota State
#define EEPROM_ADDR_FOTA_MCU                  0x00E3   // WIFI MCU Fota State

/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_CHECK_END                 0x01EA
/////////////////////////////////////////////////////////////////////////////
#define EEPROM_ADDR_TEST                      0x01EC  // MAIN PBA TEST  //kdh /*48*/
/////////////////////////////////////////////////////////////////////////////////







#define KEY_SETTING_SELECT                 0x8000
#define KEY_ICE                            0x4000
#define KEY_HOT_SELECT                     0x2000
#define KEY_AMBIENT_SELECT                 0x1000
#define KEY_COLD_SELECT                    0x0800
#define KEY_AMOUNT_SELECT                  0x0400
#define KEY_SETTING_ICE_FIRST              0x0200
#define KEY_SETTING_ICE_LOCK               0x0100
#define KEY_SETTING_HOT_LOCK               0x0080
#define KEY_SETTING_TOUCH_LOCK             0x0040
/*#define KEY_SETTING_STEAM_OFF              0x0020*/
/*#define KEY_SETTING_ECO_MODE               0x0010*/
#define KEY_SETTING_ECO_MODE               0x0020



#define LONG_KEY_3S_SETTING_MISS_TOUCH   (KEY_SETTING_SELECT + KEY_SETTING_ICE_FIRST)
#define LONG_KEY_3S_ICE_MISS_TOUCH   (KEY_ICE + KEY_SETTING_ICE_LOCK)
#define LONG_KEY_3S_HOT_MISS_TOUCH   (KEY_HOT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_AMBIENT_MISS_TOUCH   (KEY_AMBIENT_SELECT + KEY_SETTING_TOUCH_LOCK)
/*#define LONG_KEY_3S_COLD_MISS_TOUCH   (KEY_COLD_SELECT + KEY_SETTING_STEAM_OFF)*/
#define LONG_KEY_3S_COLD_MISS_TOUCH   (KEY_COLD_SELECT + KEY_SETTING_ECO_MODE)

/*#define LONG_KEY_3S_AMOUNT_MISS_TOUCH   (KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)*/




#define LONG_KEY_PCB_TEST_MODE           (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_AMOUNT_SELECT + KEY_AMBIENT_SELECT)
#define LONG_KEY_DISPLAY_TEST_MODE_CHPI  (KEY_ICE + KEY_COLD_SELECT)
//#define LONG_KEY_CIRCULATION_DRAIN       (KEY_COLD_SELECT + KEY_SETTING_STEAM_OFF)
#define LONG_KEY_HOT_TEMP_SETTING        (KEY_HOT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_HOT_TEMP_SETTING_MISS_TOUCH_1        (KEY_HOT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK)

//#define LONG_KEY_ALL_LOCK                (KEY_HOT_SELECT + KEY_AMBIENT_SELECT)
#define LONG_KEY_DEBUG_MODE              (KEY_SETTING_SELECT + KEY_COLD_SELECT)

//////////#define LONG_KEY_3S_MEMENTO              (KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_MEMENTO              (KEY_SETTING_SELECT + KEY_AMBIENT_SELECT +  KEY_AMOUNT_SELECT)

#define LONG_KEY_3S_SOUND_SETTING         (KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_SOUND_SETTING_MISS_TOUCH_1         (KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_TOUCH_LOCK)

#define LONG_KEY_3S_TAKEOFF_ICE          (KEY_ICE + KEY_HOT_SELECT)
#define LONG_KEY_3S_ICE_TRAY_TEST        (KEY_ICE + KEY_AMBIENT_SELECT)
#define LONG_KEY_3S_CANCEL_COMP_DELAY    (KEY_ICE + KEY_AMOUNT_SELECT)

#define LONG_KEY_3S_TIME_SETTING         (KEY_SETTING_SELECT + KEY_ICE)
#define LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_1         (KEY_SETTING_SELECT + KEY_ICE + KEY_SETTING_ICE_FIRST)
#define LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_2         (KEY_SETTING_SELECT + KEY_ICE + KEY_SETTING_ICE_LOCK)
#define LONG_KEY_3S_TIME_SETTING_MISS_TOUCH_3         (KEY_SETTING_SELECT + KEY_ICE + KEY_SETTING_ICE_FIRST + KEY_SETTING_ICE_LOCK)



#define LONG_KEY_3S_STER_RESERVE_TIME_SETTING         (KEY_SETTING_SELECT + KEY_HOT_SELECT)
#define LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_1         (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_SETTING_ICE_FIRST)
#define LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_2         (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_STER_RESERVE_TIME_SETTING_MISS_TOUCH_3         (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_SETTING_ICE_FIRST + KEY_SETTING_HOT_LOCK)


#define LONG_KEY_3S_BLE_FAIRING           (KEY_AMBIENT_SELECT)

#define LONG_KEY_3S_WIFI_FAIRING          (KEY_AMBIENT_SELECT + KEY_COLD_SELECT)
#define LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_1          (KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_2          (KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_WIFI_FAIRING_MISS_TOUCH_3          (KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_TOUCH_LOCK + KEY_SETTING_ECO_MODE)


#define LONG_KEY_3S_WIFI_ONOFF            (KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_WIFI_ONOFF_MISS_TOUCH_1            (KEY_COLD_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)

#define LONG_KEY_3S_FORCED_FINISH_FLUSHING       (KEY_SETTING_SELECT + KEY_ICE + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)

#define LONG_KEY_MANUAL_ICE_TANK_STER      (KEY_SETTING_SELECT + KEY_AMOUNT_SELECT)


/*#define LONG_KEY_MANUAL_FACTORY_TEST      (KEY_SETTING_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)*/
#define LONG_KEY_MANUAL_FACTORY_TEST      (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_AMOUNT_SELECT)


#define LONG_KEY_3S_CHANGE_UNIT            (KEY_COLD_SELECT + KEY_SETTING_ICE_FIRST)
#define LONG_KEY_3S_CHANGE_LANGUAGE        (KEY_COLD_SELECT + KEY_SETTING_ICE_LOCK)


#define LONG_KEY_3S_NO_USE_NO_OPERATION    (KEY_SETTING_SELECT + KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_NO_COLD                (KEY_SETTING_SELECT +  KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)

#define LONG_KEY_3S_MANUAL_DRAIN           (KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_1           (KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_2           (KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_MANUAL_DRAIN_MISS_TOUCH_3           (KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_ECO_MODE)


#define LONG_KEY_3S_DURABLE_TEST           (KEY_ICE + KEY_HOT_SELECT + KEY_COLD_SELECT + KEY_AMOUNT_SELECT)

#define LONG_KEY_3S_CT_FORCED_FLUSHING        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT)
#define LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_1        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_2        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_CT_FORCED_FLUSHING_MISS_TOUCH_3        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_TOUCH_LOCK)



/*#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)*/
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_1        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_2        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_3        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_4        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_5        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_6        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_TOUCH_LOCK + KEY_SETTING_ECO_MODE)
#define LONG_KEY_3S_CT_CHANGE_FILTER_ORDER_MISS_TOUCH_7        (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_COLD_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_TOUCH_LOCK + KEY_SETTING_ECO_MODE)





#define LONG_KEY_2S_MOVE_NEXT_STER        (KEY_COLD_SELECT + KEY_SETTING_ICE_FIRST + KEY_SETTING_ICE_LOCK)



#define LONG_KEY_3S_HOT_OFF                            (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_1               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_2               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_HOT_OFF_MISS_TOUCH_3               (KEY_HOT_SELECT + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_HOT_LOCK + KEY_SETTING_TOUCH_LOCK)



#define LONG_KEY_3S_ICE_OFF                            (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_1               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_2               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_TOUCH_LOCK)
#define LONG_KEY_3S_ICE_OFF_MISS_TOUCH_3               (KEY_ICE + KEY_AMBIENT_SELECT + KEY_AMOUNT_SELECT + KEY_SETTING_ICE_LOCK + KEY_SETTING_TOUCH_LOCK)




#define LONG_KEY_3S_RECOVER_FAST_ICE      (KEY_SETTING_SELECT + KEY_ICE + KEY_AMBIENT_SELECT + KEY_COLD_SELECT)



#define LONG_KEY_3S_ACID_CLEAN            (KEY_HOT_SELECT + KEY_COLD_SELECT)




#define HOT_KEY_CONTINUE            1
#define COLD_KEY_CONTINUE           2




//
#define UKey_Mask                    0x00
//#define UWater_Extract_Key           0x01
//#define UIce_Extract_Key             0x02
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



#if 0
#define PUMP_PWM_Free   1699                      // Sterilization.h 에도 정의, 기동 초기 20V
#define PUMP_PWM        1499                      // 16V(1300)->18V(1500) 동작 DUTY
#define PUMP_PWM_MAX    1999                      // 16V(1300)->18V(1500) 동작 DUTY
#endif



#if 0
#define PUMP_PWM        4000                      // 2ms
#define PUMP_PWM_MAX    6000                      // Full(3ms)
#endif


#define PUMP_PWM        33600                      // 2ms
#define PUMP_PWM_MAX    48000                      // Full(3ms)



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



#define TRIP_REST_TIME                      84
#define TOTAL_MAXIMUM_REST_TIME             144

#define USE_SAVE_LEARNEND_MODE_TIME         16

#define USE_SAVE_LEARNEND_MODE_MIN_TIME     1
#define USE_SAVE_LEARNEND_MODE_MAX_TIME     100



//#define DISPLAY_SLEEP_TIME                6000
#define ONE_WEEK_TIME_HOUR                  168
#define WEEK_COUNT                          4

#define DIRECT_CONVERT_COUNT                100
#define ONE_WEEK_INITIAL_HOUR               0xff



// 20160530 Sus EVA 추가 변경 (콤프 재기동 3분->8분)
//#define COMP_START_TIME 480                     // COMP 기동 대기 8분
//#define COMP_START_TIME 4800                     // COMP 기동 대기 8분
/*..hui [19-9-18오후 1:15:38] COMP 기동 대기 7분으로 변경..*/
/*#define COMP_START_TIME        4200*/

/*..hui [19-11-19오후 4:09:12] COMP 기동 대기 6분으로 변경..*/
/*#define COMP_START_TIME                      3600*/
/*..hui [23-4-12오후 2:07:00] 아이콘 아이스는 대기시간 5분..*/
#define COMP_START_TIME                      3000
#define DEVELOPE_COMP_DELAY_CANCEL_TIME      300


#define ICEVV_TIME_INIT                      300                    // 얼음받이 물주입 시간 30초


#define COLD_TIME                            50                            // 냉수재정수 시간 5초
#define IceWaterDelay                        1440        // 얼음녹은물 24시간 강제 배수 24 x 60



#define ICE_INIT_ERROR_CANCEL_TIME           72000



#define STANDBY             0                       // 서비스대기
#define WASH                1                       // 세척
#define WASHEND             2                       // 세척종료
#define NEUTRAL             3                       // 중화
#define NEUTRALEND          4                       // 중화종료

#if 0
#define CUP_LEVEL_HALF            1
#define CUP_LEVEL_ONE             2
#define CUP_LEVEL_TWO             4
#define CUP_LEVEL_MY_CUP          8
#endif


#if 0
#define CUP_LEVEL__4_OZ__120_ML             1
#define CUP_LEVEL__6_OZ__175_ML             2
#define CUP_LEVEL__8_OZ__235_ML             3
#define CUP_LEVEL__10_OZ__295_ML            4
#define CUP_LEVEL__12_OZ__355_ML            5
#define CUP_LEVEL__14_OZ__415_ML            6
#define CUP_LEVEL__16_OZ__475_ML            7
#define CUP_LEVEL__20_OZ__590_ML            8
#define CUP_LEVEL__32_OZ__945_ML            9
#define CUP_LEVEL__CONTINUE                 10

#define CUP_LEVEL__MAX                      10
#endif

#define CUP_LEVEL__4_OZ__120_ML             1
#define CUP_LEVEL__6_OZ__175_ML             2
#define CUP_LEVEL__8_OZ__235_ML             3
#define CUP_LEVEL__10_OZ__295_ML            4
#define CUP_LEVEL__12_OZ__355_ML            5
#define CUP_LEVEL__14_OZ__415_ML            6
#define CUP_LEVEL__16_OZ__475_ML            7
#define CUP_LEVEL__20_OZ__590_ML            8
#define CUP_LEVEL__CONTINUE                 9

#define CUP_LEVEL__MAX                      9




#define CUP_LEVEL_ORDER__UP                 0
#define CUP_LEVEL_ORDER__DOWN               1

/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_16_20             0xD5*/
/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE       0x295*/
/*#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE       0x195*/
#define CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE       0x295




#define ROOM_TEMP_DISPLAY_MID               0
#define ROOM_TEMP_DISPLAY_LOW               1
#define ROOM_TEMP_DISPLAY_HIGH              2



#define Fahrenheit_oF_SELECT                0
#define Celsius_oC_SELECT                   1

#define Oz_SELECT                           0
#define mL_SELECT                           1


#define HOT_TEMP_LEVEL_ORDER__UP            0
#define HOT_TEMP_LEVEL_ORDER__DOWN          1

#define HOT_TEMP_DEFAULT_TEMP               2


#define WIFI_ICE_MAKING_STANDBY             0
#define WIFI_ICE_TRAY_IN_START              1
#define WIFI_ICE_TRAY_IN_ING                2
#define WIFI_ICE_MAKING_START               3
#define WIFI_ICE_MAKING_ING                 4
#define WIFI_ICE_TAKE_OFF_START             5
#define WIFI_ICE_TAKE_OFF_ING               6
#define WIFI_ICE_MAKING_FINISH_START        7
#define WIFI_ICE_MAKING_FINISH_ING          8


#define WIFI_FLUSHING_OFF                   0
#define WIFI_FLUSHING_ON                    1
#define WIFI_FLUSHING_GOING                 2
#define WIFI_FLUSHING_DONE                  3

#define WIFI_SMART_SAVE_GREEN_WEEK_START                   0
#define WIFI_SMART_SAVE_GREEN_WEEK_ING                     1
#define WIFI_SMART_SAVE_INTENSIVE_WEEK_START               2
#define WIFI_SMART_SAVE_INTENSIVE_WEEK_ING                 3


#define WIFI_ICE_STER_OFF                   0
#define WIFI_ICE_STER_ON                    1
#define WIFI_ICE_STER_GOING                 2
#define WIFI_ICE_STER_DONE                  3


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
#define WIFI_ACID_CLEAN_STANDBY__0                                 0

#define WIFI_ACID_CLEAN_START_ACID_WATER__1                        1
#define WIFI_ACID_CLEAN_ACID_WATER_ING__2                          2

#define WIFI_ACID_CLEAN_START_CHANGE_FILTER__3                     3
#define WIFI_ACID_CLEAN_CHANGE_FILTER_ING__4                       4

#define WIFI_ACID_CLEAN_START_WAIT_1_HOUR__5                       5
#define WIFI_ACID_CLEAN_WAIT_1_HOUR_ING__6                         6

#define WIFI_ACID_CLEAN_START_DRAIN_ACID_WATER__7                  7
#define WIFI_ACID_CLEAN_DRAIN_ACID_WATER_ING__8                    8

#define WIFI_ACID_CLEAN_START_1ST_RINSE_FEED_WATER__9              9
#define WIFI_ACID_CLEAN_RINSE_1ST_FEED_WATER_ING__10               10
#define WIFI_ACID_CLEAN_START_1ST_DRAIN_RINSE_WATER__11            11
#define WIFI_ACID_CLEAN_START_1ST_DRAIN_RINSE_WATER_ING__12        12

#define WIFI_ACID_CLEAN_START_2ND_RINSE_FEED_WATER__13             13
#define WIFI_ACID_CLEAN_RINSE_2ND_FEED_WATER_ING__14               14
#define WIFI_ACID_CLEAN_START_2ND_DRAIN_RINSE_WATER__15            15
#define WIFI_ACID_CLEAN_START_2ND_DRAIN_RINSE_WATER_ING__16        16
#define WIFI_ACID_CLEAN_FINISH__17                                 17

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////







/*..hui [23-6-26오후 12:25:38] 디폴트 우선 새벽 1시..*/
#define WIFI_PERIOD_STER_HOUR_DEFAULT       1
#define WIFI_PERIOD_STER_MINUTE_DEFAULT     0


#define WIFI_SLEEP_MODE_START_HOUR_DEFAULT          0
#define WIFI_SLEEP_MODE_START_MINUTE_DEFAULT        0

#define WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT         6
#define WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT       0



#define WIFI_FILTER_CHANGE_CYCLE_DEFAULT            100
#define WIFI_FILTER_CHANGE_CYCLE_MIN                30
#define WIFI_FILTER_CHANGE_CYCLE_MAX                200


#define PURE_WATER_SELECT    1
#define COLD_WATER_SELECT    2
#define HOT_WATER_SELECT     4


#define COLD_FIRST_ICE_MAKE    0
#define ICE_FIRST_ICE_MAKE     1



#define NEW_FAST_ICE           0
#define RECOVER_FAST_ICE       1




#define RGB_OFF              0
#define RGB_COLOR_HOT        1
#define RGB_COLOR_COLD       2


#define TEST_MODE_RGB_OFF                0
#define TEST_MODE_RGB_COLOR_RED          1
#define TEST_MODE_RGB_COLOR_GREEN        2
#define TEST_MODE_RGB_COLOR_BLUE         3


typedef enum
{
    DRAIN_RETRY_INIT,
    DRAIN_RETRY_COLD_DRIN_ON,
    DRAIN_RETRY_PUMP_1MIN_OFF,
    DRAIN_RETRY_PUMP_2MIN_ON

}DRAIN_RETRY;


#define DRAIN_LEVEL_EMPTY    1
#define DRAIN_LEVEL_LOW      2
#define DRAIN_LEVEL_HIGH     4
#define DRAIN_LEVEL_ERROR    8

#define ROOM_LEVEL_LOW       0
#define ROOM_LEVEL_MID       1
#define ROOM_LEVEL_FULL      2
#define ROOM_LEVEL_ERROR     3


#define UV_WATER_TANK_OPERATION_TIME_MIN             120
#define UV_ICE_TRAY_OPERATION_TIME_MIN               60
#define UV_ICE_TANK_OPERATION_TIME_MIN               120

#define UV_ICE_OFF_OPERATION_TIME_MIN                120



#define UV_FAULT_TEST_1MIN_30SEC                     900



#if 0
/*..hui [23-6-8오전 9:40:56] 네오 이노는 1년..*/
#define FILTER_RESET_DAY__NEO_INO                    365
#define FILTER_ALARM_BEFORE_30_DAYS__NEO_INO         30

/*..hui [23-6-8오전 9:41:19] RO는 2년 730일..*/
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO                         730
#endif


#if 0
#define NEO_TOTAL_USAGE_MAX_WATER                    3600
#define RO_TOTAL_USAGE_MAX_WATER                     7200
#define INO_TOTAL_USAGE_MAX_WATER                    3600

#define FILTER_ALARM_REMAIN_240_LITER                240
#endif


#define NEO_TOTAL_USAGE_MAX_WATER                    3785
#define RO_TOTAL_USAGE_MAX_WATER                     7570
#define INO_TOTAL_USAGE_MAX_WATER                    3785

/*#define FILTER_ALARM_REMAIN_240_LITER                240*/
#define FILTER_ALARM_REMAIN_315_LITER                315



#if 0
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO                        456
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO                         912
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO                        456
#endif

#if 0
/*..hui [24-2-23오전 10:04:55] 15개월/30개월..*/
#define FILTER_RESET_DEFAULT_MONTH__NEO                          15
#define FILTER_RESET_DEFAULT_MONTH__RO                           30
#define FILTER_RESET_DEFAULT_MONTH__INO                          15

/*..hui [23-12-18오후 7:38:25] 1시간 단위로 변경..*/
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO          10944
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO           21888
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO          10944


#define FILTER_RESET_MAX_HOUR__NEO                               21888
#define FILTER_RESET_MAX_HOUR__RO                                43776
#define FILTER_RESET_MAX_HOUR__INO                               21888

#define FILTER_ALARM_REMAIN_30_DAYS                              720
#endif

/*..hui [24-2-23오전 10:05:01] 12개월/24개월..*/
#define FILTER_RESET_DEFAULT_MONTH__NEO                          12
#define FILTER_RESET_DEFAULT_MONTH__RO                           24
#define FILTER_RESET_DEFAULT_MONTH__INO                          12

/*..hui [23-12-18오후 7:38:25] 1시간 단위로 변경..*/
/* SSG : 30.4 * 24 * 12 = 8755.2 (반올림) */
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO          8755
#define FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO           17510
#define FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO          8755

#define FILTER_RESET_MAX_HOUR__NEO                               17510
#define FILTER_RESET_MAX_HOUR__RO                                35020
#define FILTER_RESET_MAX_HOUR__INO                               17510

#define FILTER_ALARM_REMAIN_30_DAYS                              720





#define FILTER_CHANGE_TYPE__NEO_INO                  0
#define FILTER_CHANGE_TYPE__NEO_RO_INO_ALL           1


/*#define FILTER_CHANGE_RESET_TIME                     18000*/
#define FILTER_CHANGE_RESET_TIME                     9000



/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               36000*/
/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               18000*/
/*..hui [24-5-28오후 4:34:04] 40분으로 변경..*/
/*#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               24000*/
/*..hui [24-7-22오후 2:00:27] 1시간동안 배수 안되면 드레인펌프 에러..*/
#define ACID_CLEAN_TANK_EMPTY_MAX_TIME               36000




//#define SETTING_MAX_YEAR      35
//#define SETTING_MIN_YEAR      21

#define SETTING_MAX_YEAR      80
#define SETTING_MIN_YEAR      23

#if 0
/*..hui [20-1-15오후 7:42:07] 2020년 1월1일 0시0분0초..*/
#define RTC_DEFAULT_YEAR      23
#define RTC_DEFAULT_MONTH     7
#define RTC_DEFAULT_DATE      1
#define RTC_DEFAULT_HUOR      0
#define RTC_DEFAULT_MIN       0
#define RTC_DEFAULT_SEC       0
#define RTC_DEFAULT_DAYWEEK   6
#define RTC_DEFAULT_Y2K       20
#endif

#if 0
#define RTC_DEFAULT_YEAR      24
#define RTC_DEFAULT_MONTH     4
#define RTC_DEFAULT_DATE      1
#define RTC_DEFAULT_HUOR      0
#define RTC_DEFAULT_MIN       0
#define RTC_DEFAULT_SEC       0
#define RTC_DEFAULT_DAYWEEK   1
#define RTC_DEFAULT_Y2K       20
#endif






#define FILTER_FLUSHING_NONE        0
#define FILTER_FLUSHING_NEO_INO     1
#define FILTER_FLUSHING_RO          2




#define STER_PUMP_STAGE_90_PERCENT         0
#define STER_PUMP_STAGE_80_PERCENT         1
//#define STER_PUMP_STAGE_18V         2



#if 0
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:47] 탱크 세척 온수 제어 온도..*/
#define ALTITUDE__1__ICE_TANK_STER__HEATER_OFF_TEMP                95
#define ALTITUDE__1__ICE_TANK_STER__HEATER_ON_TEMP                 93
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__ICE_TANK_STER__HEATER_OFF_TEMP                92
#define ALTITUDE__2__ICE_TANK_STER__HEATER_ON_TEMP                 90

#define ALTITUDE__3__ICE_TANK_STER__HEATER_OFF_TEMP                89
#define ALTITUDE__3__ICE_TANK_STER__HEATER_ON_TEMP                 87

#define ALTITUDE__4__ICE_TANK_STER__HEATER_OFF_TEMP                87
#define ALTITUDE__4__ICE_TANK_STER__HEATER_ON_TEMP                 85

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:53] 아이스트레이 세척 온수 제어 온도..*/
#define ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               82
#define ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_ON_TEMP                80
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               80
#define ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_ON_TEMP                78

#define ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               77
#define ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_ON_TEMP                75

#define ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               75
#define ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_ON_TEMP                73

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:58] 해빙 온수 제어 온도..*/
#define ALTITUDE__1__MELT_ICE__HEATER_OFF_TEMP                     60
#define ALTITUDE__1__MELT_ICE__HEATER_ON_TEMP                      55
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__MELT_ICE__HEATER_OFF_TEMP                     58
#define ALTITUDE__2__MELT_ICE__HEATER_ON_TEMP                      53

#define ALTITUDE__3__MELT_ICE__HEATER_OFF_TEMP                     55
#define ALTITUDE__3__MELT_ICE__HEATER_ON_TEMP                      50

#define ALTITUDE__4__MELT_ICE__HEATER_OFF_TEMP                     53
#define ALTITUDE__4__MELT_ICE__HEATER_ON_TEMP                      48

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#endif

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:47] 탱크 세척 온수 제어 온도..*/
#define ALTITUDE__1__ICE_TANK_STER__HEATER_OFF_TEMP                95
#define ALTITUDE__1__ICE_TANK_STER__HEATER_ON_TEMP                 93
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__ICE_TANK_STER__HEATER_OFF_TEMP                91
#define ALTITUDE__2__ICE_TANK_STER__HEATER_ON_TEMP                 89

#define ALTITUDE__3__ICE_TANK_STER__HEATER_OFF_TEMP                86
#define ALTITUDE__3__ICE_TANK_STER__HEATER_ON_TEMP                 84

#define ALTITUDE__4__ICE_TANK_STER__HEATER_OFF_TEMP                79
#define ALTITUDE__4__ICE_TANK_STER__HEATER_ON_TEMP                 77

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:53] 아이스트레이 세척 온수 제어 온도..*/
#define ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               82
#define ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_ON_TEMP                80
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               82
#define ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_ON_TEMP                80

#define ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               82
#define ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_ON_TEMP                80

#define ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_OFF_TEMP               79
#define ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_ON_TEMP                77

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*..hui [24-2-22오후 2:50:58] 해빙 온수 제어 온도..*/
#define ALTITUDE__1__MELT_ICE__HEATER_OFF_TEMP                     60
#define ALTITUDE__1__MELT_ICE__HEATER_ON_TEMP                      55
/////////////////////////////////////////////////////////////////////////

#define ALTITUDE__2__MELT_ICE__HEATER_OFF_TEMP                     60
#define ALTITUDE__2__MELT_ICE__HEATER_ON_TEMP                      55

#define ALTITUDE__3__MELT_ICE__HEATER_OFF_TEMP                     60
#define ALTITUDE__3__MELT_ICE__HEATER_ON_TEMP                      55

#define ALTITUDE__4__MELT_ICE__HEATER_OFF_TEMP                     60
#define ALTITUDE__4__MELT_ICE__HEATER_ON_TEMP                      55

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////







/*#define HOT_STER_SAFETY_TIME                          6000*/
/*..hui [24-1-25오후 3:30:33] 안전시간 15분.....*/
#define HOT_STER_SAFETY_TIME                          9000


/////#define MELT_NO_ICE_START_HOT_TEMP                45

/*#define STER_NO_OPERATION_COLD_TEMP                   35*/
/*#define STER_NO_OPERATION_COLD_TEMP                   38*/
/*#define STER_NO_OPERATION_COLD_TEMP                   15*/
/*#define STER_NO_OPERATION_COLD_TEMP                   12*/
#define STER_NO_OPERATION_COLD_TEMP                   10


/*#define HOT_CIRCULATION_MAX_TIME            1800*/
/*#define HOT_CIRCULATION_MAX_TIME            1200*/

/*#define HOT_CIRCULATION_MAX_TIME            1800*/
/*..hui [24-1-31오전 10:10:40] 온도 높이기위해 순환 최소화..*/
/*#define HOT_CIRCULATION_MAX_TIME              100*/
/*..hui [24-1-31오후 2:51:55] 온도 너무 높음.. 20초로 변경..*/
/*#define HOT_CIRCULATION_MAX_TIME              200*/
/*..hui [24-2-1오후 2:05:26] 다시 10초로.. 이정환 부장님..*/
#define HOT_CIRCULATION_MAX_TIME                       100
#define MELT_ICE_HOT_CIRCULATION_MAX_TIME              200


/*#define MELT_ICE_HOT_CIRCULATION_MAX_TIME            1200*/
/*#define ICE_TRAY_HOT_CIRCULATION_MAX_TIME            1200*/



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
/////#define SLEEP_IN    381
/////#define SLEEP_OUT   754






#define PUMP_NO_LOAD_MINIMUM_OPERATION_TIME          450
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   190*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   100*/
/*..hui [24-4-4오후 5:59:35] 70%랑 100%랑 둘다 동일..*/
/*..hui [24-4-4오후 6:00:00] 물 없을때 120정도 나옴.. 정상일때는 240~390..*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   170*/
/*#define DRAIN_NO_WATER_FEEDBACK_AD                   150*/
#define DRAIN_NO_WATER_FEEDBACK_AD                   180


#define PUMP_NO_LOAD_CHECK_TIME                      30


/*..hui [18-1-30오후 5:04:07] 드레인펌프 출력 전압 변경에 따라 시간 감소..*/
//#define COLD_DRAIN_TIME    2700
/*..hui [18-3-14오후 10:45:08] 물 없을때 실제 측정 시 75 ~ 85정도 나옴..*/
/*#define DRAIN_COMPLETE_FEEDBACK     100*/
/*#define DRAIN_COMPLETE_FEEDBACK     190*/
/*#define DRAIN_COMPLETE_FEEDBACK     100*/
/*#define DRAIN_COMPLETE_FEEDBACK     170*/
#define DRAIN_COMPLETE_FEEDBACK     180






/*#define DRAIN_VALVE_OPEN_TIME       450*/
/*..hui [23-8-14오후 3:21:50] 저수위->만수위 차는시간 1분.. 여유있게 1분 30초로..*/
/*#define DRAIN_VALVE_OPEN_TIME       900*/
/*#define DRAIN_VALVE_OPEN_TIME       1100*/
/*#define DRAIN_VALVE_OPEN_TIME       900*/
/*..hui [24-3-26오후 5:25:30] 다시 1분으로 변경.. 탱크 물 넘칠수있음..*/
#define DRAIN_VALVE_OPEN_TIME       600




/*#define MANUAL_DRAIN_MAX_TIME             36000*/
#define MANUAL_DRAIN_MAX_TIME             18000


/*#define MANUAL_DRAIN_FINISH_CHECK_TIME    600*/
/*#define MANUAL_DRAIN_FINISH_CHECK_TIME    900*/
#define MANUAL_DRAIN_FINISH_CHECK_TIME    600





#define FLOW_STEP_NUM                  4
#define FLOW_HOLD_STEP                 0//10

#define MAX_INCREASE_FLOW              1000



#define HOT_PREPARE_STAGE_0_INIT                        0
#define HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON             1
#define HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING        2
#define HOT_PREPARE_STAGE_3_HOT_KEY_SETTING             3
#define HOT_PREPARE_STAGE_4_HOT_EXTRACT                 4
#define HOT_PREPARE_STAGE_5_HOT_EXTRACT_FINISH          5
#define HOT_PREPARE_STAGE_6_PREPARE_FINISH              6


#define MIX_ALL_NORMAL                      0
#define MIX_COLD_TEMP_ABNORMAL_HIGH         1
#define MIX_HOT_TEMP_ABNORMAL_LOW           2



#define TARGET_ROOM_27_TEMP            25
//#define HOT_MIX_START_TIME             10
#define HOT_MIX_START_TIME             5


/*#define TARGET_HOT_85_TEMP             85*/
#define TARGET_HOT_85_TEMP             87

#define TARGET_HOT_77_TEMP             77

#define TARGET_HOT_43_TEMP             43

#define COLD_MIX_START_TIME            10


/*#define PERIODIC__STER_CYCLE         7*/
/*..hui [23-11-8오후 2:31:08] 28일에 한번 하는걸로 변경..*/
#define PERIODIC__STER_CYCLE                        28
#define FIRST_POWER_ON_PERIODIC__STER_CYCLE         21



/*..hui [23-7-13오전 9:55:52] 테스트용..*/
/////////#define PERIODIC__STER_CYCLE         1
///////#define HOT_STER_TEMP_HIGH_MODE         0
////////#define HOT_STER_TEMP_LOW_MODE          1




/*..hui [24-4-5오전 9:49:29] 얼음탱크 3 1개짜리 피드백 100..*/
#define UV_SOLO__ERROR_CHECK_UNDER_AD              41
#define UV_SOLO__ERROR_CHECK_OVER_AD               205

/*..hui [24-4-5오전 9:49:44] 얼음탱크 1,2 두개 165, 1개..*/
/*..hui [24-4-5오전 9:49:55] 아이스트레이 1,2 두개 : 164, 1개 : 100..*/
/*..hui [24-4-5오전 9:50:07] 냉수탱크 1,2 두개 : 182, 1개 : 100..*/
/*#define UV_COUPLE__ERROR_CHECK_UNDER_AD            82*/
#define UV_COUPLE__ERROR_CHECK_UNDER_AD            120
#define UV_COUPLE__ERROR_CHECT_OVER_AD             410



//#define HOT_NOT_USE_TIME                     18000
#define HOT_NOT_USE_TIME                     36000



#define HOT_STOP_COLD_MIX_TIME               70
#define HOT_STOP_COLD_MIX_TIME_2               60

/*..hui [20-1-30오후 3:41:34] 추출량 정할때 끝이 0으로 끝나지 않도록 명심~~~..*/
/*..hui [20-1-30오후 3:41:39] LCD 표시 관련..*/
#if 0
#define EXTRACT_TIME_AMBIENT_WATER_4_OZ         51     //52    //45     //52
#define EXTRACT_TIME_AMBIENT_WATER_6_OZ         71
#define EXTRACT_TIME_AMBIENT_WATER_8_OZ         101    //
#define EXTRACT_TIME_AMBIENT_WATER_10_OZ        113
#define EXTRACT_TIME_AMBIENT_WATER_12_OZ        154    //132    //
#define EXTRACT_TIME_AMBIENT_WATER_14_OZ        154
#define EXTRACT_TIME_AMBIENT_WATER_16_OZ        209     //192    //
#define EXTRACT_TIME_AMBIENT_WATER_20_OZ        259     //238     //227    //
/*#define EXTRACT_TIME_AMBIENT_WATER_32_OZ        372*/


#define EXTRACT_TIME_AMBIENT_WATER_4_OZ__LOW_WATER         10    //62    //
#define EXTRACT_TIME_AMBIENT_WATER_6_OZ__LOW_WATER         10
#define EXTRACT_TIME_AMBIENT_WATER_8_OZ__LOW_WATER         10    //123   //135    //125   //
#define EXTRACT_TIME_AMBIENT_WATER_10_OZ__LOW_WATER        10
#define EXTRACT_TIME_AMBIENT_WATER_12_OZ__LOW_WATER        10    //179   //
#define EXTRACT_TIME_AMBIENT_WATER_14_OZ__LOW_WATER        10
#define EXTRACT_TIME_AMBIENT_WATER_16_OZ__LOW_WATER        10   //
#define EXTRACT_TIME_AMBIENT_WATER_20_OZ__LOW_WATER        10   //
/*#define EXTRACT_TIME_AMBIENT_WATER_32_OZ__LOW_WATER        523*/
#endif


#define EXTRACT_TIME_COLD_WATER_4_OZ_120_ML            56      //51     //
#define EXTRACT_TIME_COLD_WATER_6_OZ_175_ML            77      //73
#define EXTRACT_TIME_COLD_WATER_8_OZ_235_ML            105     //100     //
#define EXTRACT_TIME_COLD_WATER_10_OZ_295_ML           134     //129     //125
#define EXTRACT_TIME_COLD_WATER_12_OZ_355_ML           160     //149    //
#define EXTRACT_TIME_COLD_WATER_14_OZ_415_ML           187     //175
#define EXTRACT_TIME_COLD_WATER_16_OZ_475_ML           214     //204    //
#define EXTRACT_TIME_COLD_WATER_20_OZ_590_ML           268     //255    //
/*#define EXTRACT_TIME_COLD_WATER_32_OZ           372*/


#define EXTRACT_TIME_COLD_WATER_4_OZ_120_ML__LOW_WATER            64     //62    //
#define EXTRACT_TIME_COLD_WATER_6_OZ_175_ML__LOW_WATER            89     //87
#define EXTRACT_TIME_COLD_WATER_8_OZ_235_ML__LOW_WATER            125    //118    //
#define EXTRACT_TIME_COLD_WATER_10_OZ_295_ML__LOW_WATER           159     //151
#define EXTRACT_TIME_COLD_WATER_12_OZ_355_ML__LOW_WATER           189      //180     //
#define EXTRACT_TIME_COLD_WATER_14_OZ_415_ML__LOW_WATER           220      //211
#define EXTRACT_TIME_COLD_WATER_16_OZ_475_ML__LOW_WATER           256      //245     //
#define EXTRACT_TIME_COLD_WATER_20_OZ_590_ML__LOW_WATER           319      //307     //
/*#define EXTRACT_TIME_COLD_WATER_32_OZ__LOW_WATER           523*/


#define EXTRACT_TIME_HOT_WATER_4_OZ_120_ML             86     //90      //80     //86     //
#define EXTRACT_TIME_HOT_WATER_6_OZ_175_ML             132    //128
#define EXTRACT_TIME_HOT_WATER_8_OZ_235_ML             176    //164    //156     //154    //155   //171    //
#define EXTRACT_TIME_HOT_WATER_10_OZ_295_ML            221    //209
#define EXTRACT_TIME_HOT_WATER_12_OZ_355_ML            248    //249     //243     //239    //245   //258     //
#define EXTRACT_TIME_HOT_WATER_14_OZ_415_ML            298    //298
#define EXTRACT_TIME_HOT_WATER_16_OZ_475_ML            348    //329    //318    //316    //320    //345    //
#define EXTRACT_TIME_HOT_WATER_20_OZ_590_ML            439    //421    //432    //
/*#define EXTRACT_TIME_HOT_WATER_32_OZ            698*/

#if 0
#define EXTRACT_TIME_HOT_WATER_4_OZ__LOW_WATER             10
#define EXTRACT_TIME_HOT_WATER_6_OZ__LOW_WATER             10
#define EXTRACT_TIME_HOT_WATER_8_OZ__LOW_WATER             10
#define EXTRACT_TIME_HOT_WATER_10_OZ__LOW_WATER            10
#define EXTRACT_TIME_HOT_WATER_12_OZ__LOW_WATER            10
#define EXTRACT_TIME_HOT_WATER_14_OZ__LOW_WATER            10
#define EXTRACT_TIME_HOT_WATER_16_OZ__LOW_WATER            10
#define EXTRACT_TIME_HOT_WATER_20_OZ__LOW_WATER            10
/*#define EXTRACT_TIME_HOT_WATER_32_OZ__LOW_WATER            698*/
#endif


#define HOT_SET_TEMP_4__200_oF_95_oC          0
#define HOT_SET_TEMP_3__185_oF_85_oC          1
#define HOT_SET_TEMP_2__170_oF_77_oC          2
#define HOT_SET_TEMP_1__110_oF_43_oC          3


/*..hui [23-5-24오후 3:44:04] 온수 선택했을때 PREPARING LED ON 조건..*/
#if 0
#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1             94
#define HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_1             86
#define HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_1             80
#define HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_1             45
#endif

/*#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1             94*/
/*..hui [23-12-15오후 4:06:48] 92도 이하.. 이정환 부장님 요청..*/
/*#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1             93*/
/*#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1             94*/
#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1             92
#define HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_1             87
#define HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_1             79
#define HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_1             45


/*..hui [24-11-25오후 2:30:17] 고도모드에 따른 프리페어링 표시 온도 분리..*/
#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_2             87
#define HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_2             84
#define HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_2             79
#define HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_2             45


#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_3             82
#define HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_3             82
#define HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_3             79
#define HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_3             45


#define HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_4             75
#define HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_4             75
#define HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_4             75
#define HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_4             45


#define HOT_PREPARE_MODE_OFF                  0
#define HOT_PREPARE_MODE_ON                   1


///#define HOT_ON_TEMP                           83
///#define HOT_ON_TEMP                           94

#define COLD__BIG                             0
#define HOT__BIG                              1


#if 0
#define FLOW_MODE_NONE                 0
#define FLOW_MODE_INIT                 1
#define FLOW_MODE_DECREASE             2
#define FLOW_MODE_INCREASE             3

#define HOT_FLOW_MOVING                0
#define HOT_FLOW_MAX_OPEN              1
#define HOT_FLOW_MAX_CLOSE             2

#define HOT_FLOW_INCREASE_MOVING       0
#define HOT_FLOW_INCREASE_FINISH       1
#endif



#define CONVERT_FAHRENHEIT_TO_CELSIUS_50             10
#define CONVERT_FAHRENHEIT_TO_CELSIUS_55             13
#define CONVERT_FAHRENHEIT_TO_CELSIUS_60             16
#define CONVERT_FAHRENHEIT_TO_CELSIUS_65             18
#define CONVERT_FAHRENHEIT_TO_CELSIUS_70             21
#define CONVERT_FAHRENHEIT_TO_CELSIUS_75             24
#define CONVERT_FAHRENHEIT_TO_CELSIUS_80             27
#define CONVERT_FAHRENHEIT_TO_CELSIUS_85             29
#define CONVERT_FAHRENHEIT_TO_CELSIUS_90             32
#define CONVERT_FAHRENHEIT_TO_CELSIUS_95             35
#define CONVERT_FAHRENHEIT_TO_CELSIUS_100            38
#define CONVERT_FAHRENHEIT_TO_CELSIUS_105            41


#define CONVERT_FAHRENHEIT_TO_CELSIUS_110            43
#define CONVERT_FAHRENHEIT_TO_CELSIUS_115            46
#define CONVERT_FAHRENHEIT_TO_CELSIUS_120            49
#define CONVERT_FAHRENHEIT_TO_CELSIUS_125            52
#define CONVERT_FAHRENHEIT_TO_CELSIUS_130            54
#define CONVERT_FAHRENHEIT_TO_CELSIUS_135            57
#define CONVERT_FAHRENHEIT_TO_CELSIUS_140            60
#define CONVERT_FAHRENHEIT_TO_CELSIUS_145            63
#define CONVERT_FAHRENHEIT_TO_CELSIUS_150            66
#define CONVERT_FAHRENHEIT_TO_CELSIUS_155            68
#define CONVERT_FAHRENHEIT_TO_CELSIUS_160            71
#define CONVERT_FAHRENHEIT_TO_CELSIUS_165            74
#define CONVERT_FAHRENHEIT_TO_CELSIUS_170            77
#define CONVERT_FAHRENHEIT_TO_CELSIUS_175            79
#define CONVERT_FAHRENHEIT_TO_CELSIUS_180            82
#define CONVERT_FAHRENHEIT_TO_CELSIUS_185            85
#define CONVERT_FAHRENHEIT_TO_CELSIUS_190            88
#define CONVERT_FAHRENHEIT_TO_CELSIUS_195            91
#define CONVERT_FAHRENHEIT_TO_CELSIUS_200            93




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



//#define FLOW_VALVE_MAX_OPEN            2500
//#define FLOW_VALVE_MAX_OPEN            1100
//#define FLOW_VALVE_MAX_OPEN            3000
#define FLOW_VALVE_MAX_OPEN            1100



//#define FLOW_VALVE_ADJUST              260
#define FLOW_VALVE_ADJUST              300
//#define FLOW_VALVE_ADJUST              0



#if 0
#define TOTAL_USAGE_MAX_WATER               3781626
#define ML_PER_GAL                          378
#define MAX_GAL                             9990
#define SAVE_DIFF_RATE                      10
#endif






/*#define UV_PROGRESS_DISPLAY_TIME            70*/
/*..hui [24-7-22오전 11:05:39] UI 디자인팀 30초로 변경 요청..*/
#define UV_PROGRESS_DISPLAY_TIME            300
#define EERROR_DISPLAY_TIME                 70


//#define STEP_TRIAC                    50        // 트라이악 총 제어 단계 (80단계로 설정)
//#define STEP_TRIAC                    86        // 트라이악 총 제어 단계 (80단계로 설정)
//#define STEP_TRIAC                    114        // 트라이악 총 제어 단계 (80단계로 설정)
//#define STEP_TRIAC                    90        // 트라이악 총 제어 단계 (80단계로 설정)
/////#define STEP_TRIAC                    110        // 트라이악 총 제어 단계 (80단계로 설정)
/////#define TRAY_IN_PWM_PWR_UP_TIME       1800


#define GAS_SWITCH_COLD               0
#define GAS_SWITCH_ICE                1
#define GAS_SWITCH_HOTGAS             2

#if 0
#define COLD_TEMP_OFF                 0
#define COLD_TEMP_LOW                 1
#define COLD_TEMP_HIGH                2
#endif

/*#define COLD_TEMP_OFF                 0*/
/*..hui [20-2-24오후 7:44:45] 냉수 ONOFF랑 온도설정 메뉴 분리..*/
#define COLD_TEMP_HIGH                0
#define COLD_TEMP_LOW                 1

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


#define PAIRING_STEP_1                 0
#define PAIRING_STEP_2                 1
#define PAIRING_STEP_3                 2
#define PAIRING_STEP_4                 3
#define PAIRING_STEP_5                 4


#if 0
#define ICE_SETTING_OFF               0
#define ICE_SETTING_ICE_FIRST         1
#define ICE_SETTING_COLD_FIRST        2
#endif


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

#define ROOM_OVER_HEAT_TEMP             50
#define ROOM_OVER_HEAT_CLEAR_TEMP       45

////////////////////////////////////////////////////////////////////////////////////


#if 0
#define FILTER_NO_CHANGE                              0
#define NEO_INO_FILTER_CHANGE                  1
#define ALL_NEO_INO_RO_FILTER_CHANGE           3
#endif

#define FILTER_NO_CHANGE                       0
#define NEO_INO_FILTER_CHANGE                  5
#define ALL_NEO_INO_RO_FILTER_CHANGE           7



#define BLDC_COMP_OFF_0_HZ           0

#define BLDC_COMP_40Hz               0b00101000
#define BLDC_COMP_41Hz               0b00101001
#define BLDC_COMP_42Hz               0b00101010
#define BLDC_COMP_43Hz               0b00101011
#define BLDC_COMP_44Hz               0b00101100
#define BLDC_COMP_45Hz               0b00101101
#define BLDC_COMP_46Hz               0b00101110
#define BLDC_COMP_47Hz               0b00101111
#define BLDC_COMP_48Hz               0b00110000
#define BLDC_COMP_49Hz               0b00110001
#define BLDC_COMP_50Hz               0b00110010
#define BLDC_COMP_51Hz               0b00110011
#define BLDC_COMP_52Hz               0b00110100
#define BLDC_COMP_53Hz               0b00110101
#define BLDC_COMP_54Hz               0b00110110
#define BLDC_COMP_55Hz               0b00110111
#define BLDC_COMP_56Hz               0b00111000
#define BLDC_COMP_57Hz               0b00111001
#define BLDC_COMP_58Hz               0b00111010
#define BLDC_COMP_59Hz               0b00111011
#define BLDC_COMP_60Hz               0b00111100
#define BLDC_COMP_61Hz               0b00111101
#define BLDC_COMP_62Hz               0b00111110
#define BLDC_COMP_63Hz               0b00111111
#define BLDC_COMP_64Hz               0b01000000
#define BLDC_COMP_65Hz               0b01000001
#define BLDC_COMP_66Hz               0b01000010
#define BLDC_COMP_67Hz               0b01000011
#define BLDC_COMP_68Hz               0b01000100
#define BLDC_COMP_69Hz               0b01000101
#define BLDC_COMP_70Hz               0b01000110
#define BLDC_COMP_71Hz               0b01000111
#define BLDC_COMP_72Hz               0b01001000
#define BLDC_COMP_73Hz               0b01001001
#define BLDC_COMP_74Hz               0b01001010
#define BLDC_COMP_75Hz               0b01001011



#define HOT_GAS_AMB_TEMP_9_DIGREE       9
#define HOT_GAS_AMB_TEMP_13_DIGREE      13
#define HOT_GAS_AMB_TEMP_19_DIGREE      19
#define HOT_GAS_AMB_TEMP_24_DIGREE      24
#define HOT_GAS_AMB_TEMP_29_DIGREE      29




#define WIFI_OFF                        0
#define WIFI_CONNECT                    1
#define WIFI_DISCONNECT                 2
#define WIFI_BLINK                      3



#define WIFI_PAIRING_STANDBY             0
#define WIFI_PAIRING_STEP0_PREPARE       1
#define WIFI_PAIRING_STEP1_25_PERCENT    2
#define WIFI_PAIRING_STEP2_50_PERCENT    3
#define WIFI_PAIRING_STEP3_75_PERCENT    4
#define WIFI_PAIRING_STEP_FINISH         5



#define PAIRING_PROGRESS_0_PERCENT           0
#define PAIRING_PROGRESS_25_PERCENT          25
#define PAIRING_PROGRESS_50_PERCENT          50
#define PAIRING_PROGRESS_75_PERCENT          75
#define PAIRING_PROGRESS_100_PERCENT         100


#define WIFI_CERTIFICATE_NONE              0
#define WIFI_CERTIFICATE_ON                1
#define WIFI_CERTIFICATE_FINISH            2


#define WIFI_HOT_LOCK_OFF               1
#define WIFI_HOT_LOCK_ON                2


#define WIFI_PAIRING_START_30_MIN       18000


#define FEEDBACK_SHOW_TIME              30
#define POPUP_SHOW_TIME                 30


#define ERROR_POPUP_SHOW_TIME           30

#define TEMP_SENSOR_OPEN    970
#define TEMP_SENSOR_SHORT   50
#define GAP                 30
#define AT_PCB_UART_TEST    0xF9


#define NONE_TEST_MODE                  0x00
#define PCB_TEST_MODE                   0x01
#define UART_TEST_MODE                  0x02
#define DISPLAY_TEST_MODE               0x04




//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SOUND_TYPE_VOICE                       0
#define SOUND_TYPE_MELODY                      1
#define SOUND_TYPE_MUTE                        2

#define SOUND_VOLUME_LEVEL_1                   0
#define SOUND_VOLUME_LEVEL_2                   1
#define SOUND_VOLUME_LEVEL_3                   2
#define SOUND_VOLUME_LEVEL_4                   3
#define SOUND_VOLUME_LEVEL_5                   4


#define LANGUAGE_TYPE_KOREA                    0
#define LANGUAGE_TYPE_ENGLISH                  1
#define LANGUAGE_TYPE_SPANISH                  2
#define LANGUAGE_TYPE_CHINESE                  3
#define LANGUAGE_TYPE_FRANCE                   4

#define LANGUAGE_MAX                           4


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*NXD Address*/
#define VOICE_START 0x00
//==============================================================
#define KR          0            // 한국어
#define US        200            // 영어
#define ES        400            // 스페인어
#define CN        600            // 중국어
#define FR        800            // 프랑스어

//==============================================================
#define VOICE_1_SHUTOFF_WATER_FILTER_COVER                       1     // '필터 커버가 열려 물 공급을 차단합니다.'
#define VOICE_2_STOP_ICE_ICETANK_COVER                           2     // '얼음탱크 커버가 열렸습니다. 얼음 생성을 중지합니다.'
#define VOICE_3_SHUTOFF_WATER_SIDE_COVER                         3     // '측면의 필터 커버가 열려 물 공급을 차단합니다. '
#define VOICE_4_SHUTOFF_WATER_TOP_COVER                          4     // '상단의 필터 커버가 열려 물 공급을 차단합니다.'
#define VOICE_5_SHUTOFF_WATER_FRONT_COVER                        5     // '정면의 필터 커버가 열려 물 공급을 차단합니다.'
#define VOICE_6_RESTART_ICE_COVER_OK                             6     // '얼음 탱크 커버가 닫혔습니다. 얼음을 재생성 합니다.'
#define VOICE_7_CALL_AS_COLD_WATER_ERROR                         7     // '냉수 기능에 이상이 감지되었으니 고객센터에 연락해주세요'
#define VOICE_8_CLEAN_DUST_FILTER_COLD_WATER_ERROR               8     // '냉수 기능에 이상이 감지되었으니 제품의 먼지 필터를 세척해주세요.'
#define VOICE_9_CALL_AS_HOT_WATER_ERROR                          9     // '온수 기능에 이상이 감지되었으니 고객센터에 연락해주세요'
#define VOICE_10_CALL_AS_ICE_ERROR                              10     // '얼음 기능에 이상이 감지되었으니 고객센터에 연락해주세요'
#define VOICE_11_CALL_AS_WATER_SUPPLY_ERROR                     11     // '물 공급에 이상이 감지 되었으니, 원수공급 밸브를 확인해주시고 문제가 반복되면 고객센터로 연락해주세요.'
#define VOICE_12_CALL_AS_WATER_LEAKAGE_ERROR                    12     // '"누수가 감지되었으니 원수공급 밸브를 잠궈주시고 문제가 반복되면 고객센터로 연락해주세요."'
#define VOICE_13_REPLACE_ONLY_FILTER_NO1_NO3                    13     // '"1번과 3번 필터만 교체하셔야 합니다.  다시 확인하시고 1번과 3번 필터를 교체해주세요. "'
#define VOICE_14_PRESS_RESET_BUTTON_AFTER_NEW_FILTER            14     // '"필터가 연결되었습니다. 새 필터로 교체하셨으면 리셋버튼을 눌러주세요 "'
#define VOICE_15_REPLACE_ADD_FILTER_NO3_PLEASE                  15     // '"1번과 3번 필터를 교체하셔야 합니다.   3번 필터를 추가로 교체해주세요"'
#define VOICE_16_REPLACE_AFTER_CHECK_FILTER_NO1_NO3             16     // '"1번과 3번 필터를 교체하셔야 합니다.  다시 확인하시고 1번과 3번 필터를 교체해주세요."'
#define VOICE_17_REPLACE_ADD_FILTER_NO1_PLEASE                  17     // '"1번과 3번 필터를 교체하셔야 합니다.  1번 필터를 추가로 교체해주세요 "'
#define VOICE_18_CLOSE_COVER_AFTER_FILTER_NO1_NO3               18     // '1번과 3번 필터를 교체하셨다면, 필터 커버를 닫아주세요'
#define VOICE_19_PRESS_YES_OR_NO_AFTER_FILTER_NO1_NO3           19     // '1번과 3번 필터를 교체하셨다면 필터 리셋을 위해 "출수" 버튼을 눌러주세요. 새 필터로 교체하지 않으셨다면 "냉수" 버튼을 눌러주세요'
#define VOICE_20_REPLACE_AFTER_CHECK_FILTER_NO1_NO3_V2          20     // '"1번과 3번 필터를 교체하셔야 합니다.  다시 확인하시고 1번과 3번 필터를 교체해주세요."' (16번과 영문이다름)
#define VOICE_21_PRESS_YES_OR_NO_AFTER_FILTER_NO1_NO3_WELL      21     // '"1번과 3번 필터를 제대로 교체하셨다면 필터 리셋을 위해 ""출수"" 버튼을 눌러주세요. 새 필터로 교체하지 않으셨다면 ""냉수"" 버튼을 눌러주세요"'
#define VOICE_22_REPLACE_ONLY_FILTER_NO1_NO3_NOT_YET_NO2        22     // '1번과 3번 필터만 교체하셔야 합니다. 2번 필터는 교체 시기가 아니오니 다시 확인해주세요.'(한국어만 다름)
#define VOICE_23_START_FILTER_FLUSHING                          23     // '필터 플러싱을 시작합니다. 플러싱 완료 후 제품 사용이 가능합니다.'
#define VOICE_24_FINISH_FILTER_FLUSHING                         24     // '필터 플러싱이 완료되어 제품 사용이 가능합니다.'
#define VOICE_25_CHECK_FILTER_FLUSHING_MANUAL                   25     // '"필터 플러싱이 선택되지 않았습니다.  필터 교체를 진행하셨다면, 매뉴얼을 참고하여 플러싱을 다시 진행해주세요."'
#define VOICE_26_REPLACE_FILTER_NO1_NO3                         26     // '1번과 3번 필터를 교체해주세요. '(한국어)
#define VOICE_27_INFORM_ACTIVATED_FILTER_NO1_ADD_NO3            27     // '"1번 필터의 리셋 버튼이 활성화 되었습니다. 3번 필터를 추가로 교체해 주세요"'
#define VOICE_28_INFORM_ACTIVATED_FILTER_NO3_ADD_NO1            28     // '"3번 필터의 리셋 버튼이 활성화 되었습니다. 1번 필터를 추가로 교체해 주세요 "'
#define VOICE_29_CLOSE_COVER_FOR_FILTER_FLUSHING                29     // '"필터 교체가 완료되었습니다.  필터 커버를 닫으면 필터 플러싱을 시작합니다."'
#define VOICE_30_START_FILTER_FLUSHING_NO1_NO3                  30     // '1번과 3번 필터의 플러싱을 시작합니다. 플러싱 완료 후 제품 사용이 가능합니다.'(한국어)
#define VOICE_31_PRESS_RESET_BUTTON_AFTER_NEW_FILTER            31     // '필터를 교체 하신 후 리셋버튼을 눌러주세요.'
#define VOICE_32_PRESS_RESET_BUTTON_FILTER_NO1                  32     // '"1번 필터 리셋 버튼이 활성화 되지 않았습니다. 정면의 필터 커버를 열어 1번 필터 리셋버튼을 눌러주세요."'
#define VOICE_33_PRESS_RESET_BUTTON_FILTER_NO3                  33     // '"3번 필터 리셋 버튼이 활성화 되지 않았습니다.  정면의 필터 커버를 열어 3번 필터 리셋버튼을 눌러주세요."'
#define VOICE_34_REPLACE_ADD_FILTER_NO3                         34     // '"1번과 3번 필터를 교체하셔야 합니다.   3번 필터를 추가로 교체해 주시기 바랍니다."' (주세요랑 다름)
#define VOICE_35_REPLACE_ADD_FILTER_NO1                         35     // '"1번과 3번 필터를 교체하셔야 합니다.  1번 필터를 추가로 교체해 주시기 바랍니다. "'(주세요랑 다름)
#define VOICE_36_CANCEL_RESET_FILTER_NO1                        36     // '1번 필터 리셋을 취소합니다.'
#define VOICE_37_CANCEL_RESET_FILTER_NO2                        37     // '2번 필터 리셋을 취소합니다.'
#define VOICE_38_CANCEL_RESET_FILTER_NO3                        38     // '3번 필터 리셋을 취소합니다.'
#define VOICE_39_CANCEL_FILTER_FLUSHING                         39     // '"필터 플러싱이 취소되었습니다. 다시 필터 플러싱을 진행하시려면, 필터를 제거 후 다시 결합하고 리셋버튼을 눌러주세요. ."'
                                                                       // '필터가 연결되었습니다. 새 필터로 교체하셨으면 리셋버튼을 눌러주세요 '(국문)
#define VOICE_40_PRESS_RESET_BUTTON_NO1                         40     // 'If number 1 filter is replaced, please press the reset button.'(영문)
#define VOICE_41_PRESS_RESET_BUTTON_NO2                         41     // 'If number 2 filter is replaced, please press the reset button.'(영문)
#define VOICE_42_PRESS_RESET_BUTTON_NO3                         42     // 'If number 3 filter is replaced, please press the reset button.'(영문)
#define VOICE_43_REPLACE_ADD_FILTER_NO2_NO3_FOR_ALL             43     // '모든 필터를 교체하셔야 하니 2번과 3번 필터를 추가로 교체해주세요'
#define VOICE_44_REPLACE_ADD_FILTER_NO1_NO3_FOR_ALL             44     // '모든 필터를 교체하셔야 하니 1번과 3번 필터를 추가로 교체해주세요'
#define VOICE_45_REPLACE_ADD_FILTER_NO1_NO2_FOR_ALL             45     // '모든 필터를 교체하셔야 하니 1번과 2번 필터를 추가로 교체해주세요'
#define VOICE_46_PRESS_YES_OR_NO_AFTER_ALL_FILTERS              46     // '모든 필터를 교체하셨다면 필터 리셋을 위해 "출수" 버튼을 눌러주세요. 새 필터로 교체하지 않으셨다면 "냉수 버튼을 눌러주세요'
#define VOICE_47_CHECK_REPLACE_ALL_FILTERS                      47     // '모든 필터를 교체하셔야 하니, 다시 확인해주세요.'
#define VOICE_48_NOT_SELECTED_FILTER_FLUSHING                   48     // '필터 플러싱이 선택되지 않았습니다. 바로 제품 사용이 가능합니다.'
#define VOICE_49_REPLACE_FILTER_ALL                             49     // '모든 필터를 교체해주세요.'
#define VOICE_50_INFORM_ACTIVATION_ADD_OTHER_FILTER             50     // '"필터 리셋 버튼이 활성화 되었습니다. 나머지 필터를 추가로 교체해주세요"'

#define VOICE_51_CLOSE_COVER_FOR_FILTER_FLUSHING_V2             51     // '"필터 교체가 완료되었습니다.  필터 커버를 닫으면 필터 플러싱을 시작합니다."' (영문이 다름)

#define VOICE_52_PRESS_RESET_BUTTON_AFTER_REPLACE_FILTER        52     // '필터를 교체하신 후 리셋버튼을 눌러주세요'
#define VOICE_53_PRESS_RESET_BUTTON_DEACTIVATED                 53     // '필터 플러싱을 시작합니다.  플러싱 완료 후 제품 사용이 가능합니다.'
#define VOICE_54_REPLACE_ADD_FILTER_NO3_FOR_ALL                 54     // '"모든 필터를 교체하셔야 합니다.  3번 필터를 추가로 교체해주세요" '
#define VOICE_55_REPLACE_ADD_FILTER_NO1_FOR_ALL                 55     // '"모든 필터를 교체하셔야 합니다.  1번 필터를 추가로 교체해주세요" '
#define VOICE_56_REPLACE_ADD_FILTER_NO2_FOR_ALL                 56     // '"모든 필터를 교체하셔야 합니다.  2번 필터를 추가로 교체해주세요" '

#define VOICE_57_PRESS_DISPENSE_BUTTON_AFTER_WATER_VALVE_OPEN   57     // '"원수 공급 밸브를 확인하시어 공급밸브를 열고 추출버튼을 눌러주세요." '
#define VOICE_58_PRESS_YES_OR_NO_AFTER_FAUCET                   58     // '유로 파우셋을 교체하셨다면 "출수" 버튼을 눌러주세요. 교체하지 않으셨다면 "냉수 버튼을 눌러주세요'
#define VOICE_59_PRESS_YES_OR_NO_AFTER_FILTER_FAUCET            59     // '필터와 유로 파우셋을 교체하셨다면 "출수" 버튼을 눌러주세요. 교체하지 않으셨다면 "냉수 버튼을 눌러주세요'
#define VOICE_60_WAIT_ICE_TANK_CLEANING                         60     // '얼음 탱크 세척 중에는 얼음과 물을 사용하실 수 없습니다'
#define VOICE_61_START_SMART_TESTING_MODE                       61     // '스마트 진단을 시작합니다. 진행 중에는 제품을 사용하실 수 없으니 잠시만 기다려 주세요.'
#define VOICE_62_FINISH_SMART_TESTING_MODE_NO_ERROR             62     // '스마트 진단이 완료 되어 제품을 사용하실 수 있습니다. '
#define VOICE_63_FINISH_SMART_TESTING_MODE_WITH_ERROR           63     // '스마트 진단이 완료 되었습니다.'
#define VOICE_64_INFORM_BLE_MODE_ACTIVATED                      64     // '블루투스 연결 모드가 활성화 되었습니다. '
#define VOICE_65_INFORM_BLE_MODE_DEACTIVATED                    65     // '블루투스 연결 모드가 비활성화 되었습니다.'
#define VOICE_66_INFORM_WIFI_MODE_ACTIVATED                     66     // 'Wi-Fi 연결 모드가 활성화 되었습니다. '
#define VOICE_67_INFORM_WIFI_MODE_DEACTIVATED                   67     // 'Wi-Fi 연결 모드가 비활성화 되었습니다.'
#define VOICE_68_INFORM_WIFI_ON                                 68     // '제품의 Wi-Fi가 켜졌습니다.'
#define VOICE_69_INFORM_WIFI_OFF                                69     // '제품의 Wi-Fi가 꺼졌습니다.'
#define VOICE_70_PRESS_BUTTON_ACCORDING_TO_APP_GUIDE            70     // '"제품 인증을 진행 중입니다. 앱에서 가이드하는 버튼을 눌러 주세요." '
#define VOICE_71_INFORM_APP_PAIRING_SUCCESS                     71     // '제품과 앱이 성공적으로 연결되었습니다.'
#define VOICE_72_INFORM_APP_PAIRING_FAIL                        72     // '제품과 앱의 연결이 실패하였습니다. '
#define VOICE_73_INFORM_APP_DISCONNECTED                        73     // '제품과 앱의 연결이 끊어졌습니다.'
#define VOICE_74_INFORM_WIFI_OFF                                74     // '제품의 Wi-Fi가 꺼졌습니다. '
#define VOICE_75_PRESS_INSTALL_BUTTON                           75     // '정수기 설치를 위해 추출버튼을 눌러주세요'
#define VOICE_76_START_WIFI_AUTOMATIC_CONNECTION                76     // '와이파이 연결을 자동으로 시작합니다.'
#define VOICE_77_WAIT_WATER_PIPE_DRAIN                          77     // '"깨끗한 물 제공을 위해 유로의 물을 비우고 있습니다.   잠시만 기다려주세요"
#define VOICE_78_DISCARD_FIRST_CUP                              78     // '깨끗한 물을 드시기 위해 첫 컵은 버리고 음용해 주세요.
#define VOICE_79_WATCHOUT_HOT_WATER_CUP                         79     // '온수가 뜨거우니 주의하세요.
#define VOICE_80_WATCHOUT_HOT_WATER_CONTINUOUS                  80     // '"온수가 뜨거우니 주의하세요.  추출을 멈추시려면 추출 버튼을 눌러주세요."
#define VOICE_81_SETTING_MODE_CLEAN_CARE                        81     // '클린케어 모드
#define VOICE_82_START_CLEAN_CARE_WATCHOUT_FAUCET               82     // '"클린케어를 진행중에 온수가 튈 수 있으니 파우셋 밑에 알맞은 컵을 놓으시거나 파우셋 추출부를 싱크대로 향하게 해주세요."
#define VOICE_83_PRESS_BUTTON_MANUAL_CLEAN_CARE                 83     // '준비가 완료되었다면 '출수 버튼'을 3초 이상 눌러주세요
#define VOICE_84_START_CLEAN_CARE_WATCHOUT_HOT                  84     // '"클린케어를 시작합니다.  추출부로 뜨거운 물이 추출되니 화상을 입지 않도록 조심하시기 바랍니다."
#define VOICE_85_FINISH_CLEAN_CARE                              85     // '클린케어가 완료되었습니다.
#define VOICE_86_PRESS_BUTTON_MORE_SETTING_MODE                 86     // '설정 버튼을 3초 누르면 정수기의 기능 설정이 가능합니다.
#define VOICE_87_SETTING_MODE                                   87     // '기능 설정 모드
#define VOICE_88_CLOSE_FRONT_COVER                              88     // '전면의 필터 커버를 닫아주세요.
#define VOICE_89_CLOSE_SIDE_COVER                               89     // '측면의 필터 커버를 닫아주세요.
#define VOICE_90_CLOSE_TOP_COVER                                90     // '상단의 커버를 닫아주세요.
#define VOICE_91_CLOSE_FILTER_COVER                             91     // '본체의 필터 커버를 닫아주세요.
#define VOICE_92_PRESS_BUTTON_HOT_LOCK_OFF                      92     // '온수 버튼이 잠겨있으니, '온수 잠금' 버튼을 3초 눌러 해제해주세요
#define VOICE_93_PRESS_SETTING_MODE_HOT_LOCK_OFF                93     // '온수 버튼이 잠겨있으니, 설정 모드의 '온수 잠금' 버튼을 3초 눌러 해제해주세요
#define VOICE_94_PRESS_BUTTON_HOT_FUNCTION_ON                   94     // '온수가 꺼져있으니, 온수버튼을 3초 눌러 ON으로 설정해주세요.
#define VOICE_95_CHECK_SETTING_HOT_FUNCTION                     95     // '온수가 꺼져있으니 설정 모드를 확인해주세요
#define VOICE_96_CHECK_SETTING_COLD_FUNCTION                    96     // '냉수가 꺼져있으니 설정 모드를 확인해주세요
#define VOICE_97_DISPENSE_ICE_WHILE_PRESS                       97     // '얼음 추출 버튼을 누르는 동안 얼음이 추출됩니다.
#define VOICE_98_INFORM_ICE_LOCK_ON                             98     // '얼음 추출 버튼이 잠겨있습니다.
#define VOICE_99_PRESS_BUTTON_ICE_FUNCTION_ON                   99     // '얼음 생성 기능이 꺼져있으니, 얼음 버튼을 3초 눌러 ON으로 설정해주세요.
#define VOICE_100_SET_CLOCK_ECO_MODE                           100     // '에코모드 사용을 위해 wifi를 연결하거나 현재 시간을 설정해주세요.
#define VOICE_101_NO_GUARANTEE_ICE_ECO_MODE                    101     // '에코 모드 상태이므로 얼음이 충분하지 않을 수 있습니다.
#define VOICE_102_PRESS_BUTTON_ALL_LOCK_OFF_A                  102     // '1) 모든 버튼이 잠겨있으니 온수잠금과 정수버튼을 동시에 3초 눌러 해제해주세요
#define VOICE_103_PRESS_SETTING_MODE_ALL_LOCK_OFF              103     // '2) 모든 버튼이 잠겨있으니 설정 모드의 전체잠금 버튼을 눌러 해제해주세요"
#define VOICE_104_PRESS_BUTTON_ALL_LOCK_OFF_B                  104     // '3) 모든 버튼이 잠겨있으니 온수와 정수버튼을 동시에 3초 눌러 해제해주세요
#define VOICE_105_WAIT_CLEAN_CARE                              105     // '"클린케어가 진행중입니다. 클린케어 중에는 정수기를 사용하실 수 없습니다."
#define VOICE_106_SET_APP_AUTO_LOCK_OFF                        106     // '"전체 자동 잠금을 해지하시려면 App 을 통해 기능을 해제해주세요."
#define VOICE_107_NO_GUARANTEE_LOW_WATER                       107     // '"깨끗한 물을 채우는 중입니다.  탱크에 물이 부족할 수 있습니다."
#define VOICE_108_WAIT_LOW_WATER                               108     // '"깨끗한 물을 채우는 중입니다.  잠시만 기다려주세요."
#define VOICE_109_INFORM_NOT_ENOUGH_HOT                        109     // '온수를 가열중이므로, 깜빡이는 온도 선택 시 충분히 뜨겁지 않습니다.
#define VOICE_110_INFORM_DISPENSE_NOT_ENOUGH_HOT               110     // '온수를 가열 중이므로, 현재의 탱크 온도로 출수됩니다 .
#define VOICE_111_INFORM_NOT_ENOUGH_COLD                       111     // '냉수를 냉각 중이므로, 충분히 시원하지 않을 수 있습니다.
#define VOICE_112_INFORM_HOT_LOCK_ON                           112     // '온수 버튼이 잠겼습니다.'
#define VOICE_113_INFORM_HOT_LOCK_OFF                          113     // '온수를 사용하실 수 있습니다. '
#define VOICE_114_SETTING_MODE_JOG_DAIL                        114     // '"설정 모드 입니다. 조그다이얼을 사용하여 기능을 설정하세요."'
#define VOICE_115_SETTING_HOT_TANK_CONTROL_MODE                115     // '온수탱크 온도 제어 모드'
#define VOICE_116_START_HEATING_HOT_TANK                       116     // '설정하신 온도로 가열을 시작합니다.'
#define VOICE_117_START_CONTROL_HOT_TANK                       117     // '설정하신 온도로 제어를 시작합니다. '
#define VOICE_118_INFORM_ENOUGH_HOT                            118     // '탱크의 온도가 설정하신 목표 온도에 도달하였습니다.'
#define VOICE_119_INFORM_TOO_HIGH_HOT                          119     // '온수온도 조절 중이므로, 현재의 탱크 온도로 곧 출수됩니다.'
#define VOICE_120_SETTING_MODE_HOT_TANK                        120     // '온수 탱크 설정 모드'
#define VOICE_121_INFORM_HOT_FUNCTION_ON                       121     // '"온수 기능이 켜졌습니다. 설정하신 온도까지 시간이 다소 소요됩니다."
#define VOICE_122_INFORM_HOT_FUNCTION_OFF                      122     // '"온수 기능이 꺼졌습니다. 온수를 사용하실 수 없습니다."
#define VOICE_123_SETTING_MODE_COLD_TANK                       123     // '냉수 탱크 설정 모드'
#define VOICE_124_INFORM_COLD_FUNCTION_ON                      124     // '"냉수 기능이 켜졌습니다. 설정하신 온도까지 시간이 다소 소요됩니다."
#define VOICE_125_INFORM_COLD_FUNCTION_OFF                     125     // '"냉수 기능이 꺼졌습니다. 냉수를 사용하실 수 없습니다."
#define VOICE_126_SETTING_MODE_ALL_LOCK                        126     // '전체 잠금 설정 모드입니다.
#define VOICE_127_INFORM_ALL_LOCK_ON                           127     // '모든 버튼이 잠겼습니다.
#define VOICE_128_INFORM_ALL_LOCK_OFF                          128     // '전체 버튼 잠금이 해제되었습니다.
#define VOICE_129_VOICE_MODE                                   129     // '음성'
#define VOICE_130_MELODY_MODE                                  130     // '효과음'
#define VOICE_131_MUTE_MODE                                    131     // '무음'
#define VOICE_132_SETTING_MODE_SOUND                           132     // '소리 설정 모드'
#define VOICE_133_MODE_SET_VOICE                               133     // '기능이 설정되었습니다. (음성)
#define VOICE_134_MODE_SET_MELODY                              134     // '기능이 설정되었습니다. (효과음)
#define VOICE_135_MODE_SET_MUTE                                135     // '기능이 설정되었습니다. (무음)
#define VOICE_136_MODE_SET_COLD_ON                             136     // '기능이 설정되었습니다. (냉수 기능 ON)
#define VOICE_137_MODE_SET_COLD_OFF                            137     // '기능이 설정되었습니다. (냉수 기능 OFF)
#define VOICE_138_SETTING_MODE_CLEAN_CARE_TIME                 138     // '클린케어 시간 설정 모드
#define VOICE_139_MODE_SET_CLEAN_CARE_TIME                     139     // '기능이 설정되었습니다. (유로살균 시간 설정완료)
#define VOICE_140_SETTING_MODE_DEFAULT_AMOUNT                  140     // '시작용량 설정 모드
#define VOICE_141_MODE_SET_DEFAULT_AMOUNT                      141     // '기능이 설정되었습니다. (시작 용량 설정완료)
#define VOICE_142_NOT_TIME_REPLACE_FILTER_YET                  142     // '"필터의 교체 시점이 아직 도래하지 않았습니다. 필터의 교체 시점이 도래했을 때 안내드리겠습니다."'
#define VOICE_143_CHECK_TIME_REPLACE_FILTER                    143     // '"필터 교체 정보입니다.필터 별로 필터 교체 시점을 확인해주세요."'
#define VOICE_144_SETTING_MODE_CLOCK                           144     // '시간 설정 모드'
#define VOICE_145_MODE_SET_CLOCK                               145     // '기능이 설정되었습니다. (시작 용량 설정완료)
#define VOICE_146_FINISH_SETTING                               146     // '설정모드를 종료합니다.'
#define VOICE_147_INFORM_ICE_LOCK_ON                           147     // '얼음 추출 버튼이 잠겼습니다.'
#define VOICE_148_INFORM_ICE_LOCK_OFF                          148     // '얼음 추출 버튼을 사용하실 수 있습니다.'
#define VOICE_149_INFORM_ICE_FUNCTION_ON                       149     // '얼음 생성 기능이 켜졌습니다.'
#define VOICE_150_INFORM_ICE_FUNCTION_OFF                      150     // '얼음 생성 기능이 꺼졌습니다.'
#define VOICE_151_SPECIAL_FUNCTION                             151     // '특수모드입니다.' (개발/생산용)
//---------------------------------------------------------------
//                 MELODY
//---------------------------------------------------------------
#define VOICE_192_MELODY_DISPENSE_CONTINUOUS                   192
#define VOICE_193_MELODY_DISPENSE_START                        193
#define VOICE_194_MELODY_DISPENSE_FINISH                       194
#define VOICE_195_MELODY_PLUG_IN                               195
#define VOICE_196_MELODY_SELECT                                196
#define VOICE_197_MELODY_WARNING                               197
#define VOICE_198_MELODY_SET_ON                                198
#define VOICE_199_MELODY_SET_OFF                               199
 //==============================================================


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#define AT_MODEL_CMD_CHP_671                   0x04
#define AT_MODEL_CMD_CHP_260                   0x01
#define AT_MODEL_CMD_CP_260                    0x02
#define AT_MODEL_CMD_CHP_590                   0x03
#define AT_MODEL_CMD_CHP_7300                  0x13
#define AT_MODEL_CMD_CHP_7300V2                0x17
#define AT_MODEL_CMD_CHP_7300E                 0x18
#define AT_MODEL_CMD_CHP_7510L                 0x22

#define AT_MODEL_CMD_CHP_7520L_MY_AIS          0x36
#define AT_MODEL_CMD_CHP_WESTERN_ICE           0x38


#define AT_MODEL_CMD_NATION_US                 0x07


#define AT_RS232_STX                           0x01
#define AT_RS232_ETX                           0x04
#define AT_RS232_ACK                           0x06
#define AT_RS232_NAK                           0x15


#define AT_UART_No_CMD                         0x0000
#define AT_UART_CMD_START                      0x2000              // Start
#define AT_UART_CMD_SETTINGS                   0x3000              // Settings
#define AT_UART_CMD_WIFI                       0x3010              // WIFI
#define AT_UART_CMD_UV_ICE_TANK                0x3011              // ICE TANK UV
#define AT_UART_CMD_SENSOR_FLOW_FILTER         0x3012              // Filter 유량 센서
#define AT_UART_CMD_CURRENT_CALC               0x3013              // DC 전류

#define AT_UART_CMD_UV_WATER_TANK              0x3014              // uv water tank
#define AT_UART_CMD_SENSOR_FLOW_TRAY           0x3015              // tray 유량 센서
#define AT_UART_CMD_DC_FAN                     0x3016              // fan
#define AT_UART_CMD_DRAIN_PUMP                 0x3017              // drain pump

#define AT_UART_CMD_TDS_IN                     0x3018              // TDS IN 센서
#define AT_UART_CMD_TDS_OUT                    0x3019              // TDS OUT 센서

#define AT_UART_CMD_UV_ICE_TRAY_1              0x301B              // uv ice tray = 1
#define AT_UART_CMD_UV_ICE_TRAY_2              0x301C              // uv ice tray = 2

#define AT_UART_CMD_ICE_FULL_SENSOR            0x301D              // ice full sensor
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

#define AT_UART_CMD_TRAY_IN_VALVE_ON           0x5116
#define AT_UART_CMD_TRAY_IN_VALVE_OFF          0x5117

#define AT_UART_CMD_COLD_DRAIN_ON              0x5118
#define AT_UART_CMD_COLD_DRAIN_OFF             0x5119

#define AT_UART_CMD_FLUSHING_FEED_VALVE_ON     0x5122
#define AT_UART_CMD_FLUSHING_FEED_VALVE_OFF    0x5123

#define AT_UART_CMD_FLUSHING_NOS_VALVE_ON      0x5124
#define AT_UART_CMD_FLUSHING_NOS_VALVE_OFF     0x5125

#define AT_UART_CMD_OVERHEATING_NOS_ON         0x512A
#define AT_UART_CMD_OVERHEATING_NOS_OFF        0x512B

#define AT_UART_CMD_AIR_FEED_ON                0x5132
#define AT_UART_CMD_AIR_FEED_OFF               0x5133

#define AT_UART_CMD_HOT_IN_FEED_ON             0x5134
#define AT_UART_CMD_HOT_IN_FEED_OFF            0x5135

#define AT_UART_CMD_ICE_TANK_STER_LEFT_ON      0x513C
#define AT_UART_CMD_ICE_TANK_STER_LEFT_OFF     0x513D

#define AT_UART_CMD_ICE_TANK_STER_RIGHT_ON     0x513E
#define AT_UART_CMD_ICE_TANK_STER_RIGHT_OFF    0x513F


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

#define AT_UART_CMD_MIXING_MOTOR_OPEN          0x5212
#define AT_UART_CMD_MIXING_MOTOR_CLOSE         0x5213

#define AT_UART_CMD_DRAIN_MOTOR_OPEN           0x5218
#define AT_UART_CMD_DRAIN_MOTOR_CLOSE          0x5219

#define AT_UART_CMD_DRAIN_PUMP_ON              0x5302
#define AT_UART_CMD_DRAIN_PUMP_OFF             0x5303
#define AT_UART_CMD_TRAY_PUMP_ON               0x5304
#define AT_UART_CMD_TRAY_PUMP_OFF              0x5305

#define AT_UART_CMD_COMP_ON                    0x9900
#define AT_UART_CMD_COMP_OFF                   0x9901
#define AT_UART_CMD_ICE_SWITCH_ICE             0x9902
#define AT_UART_CMD_ICE_SWITCH_COLD            0x9903
#define AT_UART_CMD_ICE_SWITCH_HOTGAS          0x9904

#define AT_UART_CMD_BLDC_COMP_ERROR            0x9910

#define AT_UART_CMD_SYSTEM_COMPLETE            0xFF00              // (검사종료)제품일반모드로 전환



#define NON_UART_TEST                          0x00
#define NOT_INCLUDE_FRONT_UART_TEST            0x01
#define INCLUDE_FRNOT_UART_TEST                0x02
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////






/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#endif

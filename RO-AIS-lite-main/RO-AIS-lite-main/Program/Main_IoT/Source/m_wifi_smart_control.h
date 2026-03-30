/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _WIFI_SMART_CONTROL_H_
#define _WIFI_SMART_CONTROL_H_

//


extern void WifiSendData ( E_WIFI_DATA_T mu8Data );
extern U16 GetWifiRequestValue ( E_WIFI_RQST_T mType );
extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );
extern U16 get_round( F32 f32_data );




typedef enum
{
    WEATHER_SUNNY = 1,
    WEATHER_BIT_CLOUD,
    WEATHER_LOTS_CLOUD,
    WEATHER_CLOUDY,
    WEATHER_CLOUDY_AND_RAINY,
    WEATHER_CLOUDY_AND_SNOWY,
    WEATHER_SUNNY_AFTER_RAINY,
    WEATHER_SHOWER,
    WEATHER_RAINY_OR_SNOWY,
    WEATHER_SNOWY_OR_RAINY,
    WEATHER_THUNDER,
    WEATHER_FOG
}SMART_WEATHER;


#define SMART_IMAGE_SUNNY_DAY                     0
#define SMART_IMAGE_SUNNY_NIGHT                   1
#define SMART_IMAGE_CLOUDY                        2
#define SMART_IMAGE_CLOUDY_AND_RAINY              3
#define SMART_IMAGE_SHOWER                        4
#define SMART_IMAGE_FOG                           5
#define SMART_IMAGE_CLOUDY_AND_SNOWY              6
#define SMART_IMAGE_RAINY_OR_SNOWY                7
#define SMART_IMAGE_THUNDER                       8
#define SMART_IMAGE_SUNNY_AFTER_RAINY_DAY         9
#define SMART_IMAGE_SUNNY_AFTER_RAINY_NIGHT       10


#define MAX_TEMPERATURE                    50
#define MIN_TEMPATURE                      206


#define WIFI_SERVICE_MODE_VISIT            0xffff

extern TYPE_BYTE          U8PairingStepB;
#define            u8PairingStep                            U8PairingStepB.byte
#define            Bit0_Pairing_Step0_PrePare               U8PairingStepB.Bit.b0
#define            Bit1_Pairing_Step1_25_Percent            U8PairingStepB.Bit.b1
#define            Bit2_Pairing_Step2_50_Percent            U8PairingStepB.Bit.b2
#define            Bit3_Pairing_Step3_75_Percent            U8PairingStepB.Bit.b3
#define            Bit4_Pairing_Step_FINISH                 U8PairingStepB.Bit.b4
#define            Bit5_Pairing_Exit                        U8PairingStepB.Bit.b5
#define            Bit6_Pairing_Error                       U8PairingStepB.Bit.b6
#define            Bit7_Pairing_Forced_Exit                 U8PairingStepB.Bit.b7


extern U8 gu8_rtc_time_Hour;
extern bit bit_wifi_pairing_start;
extern bit bit_display_last_error;





#endif

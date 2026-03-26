#include "WIFI_Common.h"
#include "WIFI_SetFunctionData.h"
#include "WIFI_SetSensorData.h"
#include "WIFI_SetErrorData.h"
#include "WIFI_SetPartData.h"
#include "WIFI_SetAccumulateData.h"
#include "WIFI_SetMonitorData.h"
#include "WIFI_SetSensorData.h"
#include "WIFI_UserInterface.h"

#ifdef MODEL_NO_3

#include "Port_Define.h"
#include "m_wifi_global_data.h"

#define _HOT_TEMP_4STEP_


extern U16 WifiRamWriteCheck_address = 0;
extern U8 WifiSmartCheckResultData = 0;

void SetUserSystemRamWriteStatus ( U16 mu16Address)
{
    WifiRamWriteCheck_address = (U16)mu16Address;
}
U16 GetUserSystemRamWriteStatus ( U16 mu16Address )
{
    if (WifiRamWriteCheck_address == mu16Address)
    {
        return WifiRamWriteCheck_address;
    }
    return CLEAR;
}

void UserWriteEep ( U16 mu8Addr, U8 mu8Val )
{
    if(u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    if( mu8Addr == EEPROM_ADDR_WIFI_POWER )
    {
        F_Wifi_Power = mu8Val;
    }
    else if( mu8Addr == EEPROM_ADDR_FIRST_PARING )
    {
        F_Wifi_First_Paring = mu8Val;
    }
    else if( mu8Addr == EEPROM_ADDR_FOTA_MODULE )
    {
        F_Wifi_Fota_MODULE = mu8Val;
    }
    else if( mu8Addr == EEPROM_ADDR_FOTA_MCU )
    {
        F_Wifi_Fota_MCU = mu8Val;
    }
    else{}
}


U8 UserReadEep ( U16 mu8Addr )
{
    U8 mu8Data = 0U;

    if( mu8Addr == EEPROM_ADDR_WIFI_POWER )
    {
        mu8Data = (U8)F_Wifi_Power;
    }
    else if( mu8Addr == EEPROM_ADDR_FIRST_PARING )
    {
        mu8Data = (U8)F_Wifi_First_Paring;
    }
    else if( mu8Addr == EEPROM_ADDR_FOTA_MODULE )
    {
        mu8Data = (U8)F_Wifi_Fota_MODULE;
    }
    else if( mu8Addr == EEPROM_ADDR_FOTA_MCU )
    {
        mu8Data = (U8)F_Wifi_Fota_MCU;
    }
    else{}

    return mu8Data;
}


void UserBuzzSound ( U8 mu8Buzz )
{
    /*BuzStep(mu8Buzz);*/
    Play_Voice(mu8Buzz);
}

U8 GetUserSystemStatus ( U8 mu8Value )
{
    /*
    mVal = USER_MODEL_TYPE;
    0 : CHP
    1 : CP
    mVal = USER_FACTORY_STATUS;
    0 CLEAR : Normal
    1 SET : Factory/PCB Test mode
    mVal = USER_RX_STATUS;
    0 FALSE : App Control X (??????/???????/EW??????/????????????/??????????/??????????)
    1 TRUE : App Control O
    mVal = USER_SMART_POSSIBLE_STATUS;
    0 FALSE : Smart Check X (??????/???????/EW??????/????????????)
    1 TRUE : Smart Check O
    mVal = USER_ERROR_STATUS;
    0 FALSE : Normal
    1 TRUE : Error
    mVal = USER_FOTA_STATUS;
    0 FALSE : Fota X (??????/???????/EW??????)
    1 TRUE : Fota O
    mVal = USER_SMART_SENSING_STATUS;
    0 FALSE : Normal
    1 TRUE : Smart Checking
    */
    U8 mu8Return = 0U;

    if ( mu8Value == USER_MODEL_TYPE )
    {
        mu8Return = USER_MODEL_CHP;
    }
    else if ( mu8Value == USER_FACTORY_STATUS )
    {
        /* 공장테스트모드 확인 */
        if ( u8FactoryTestMode == PCB_TEST_MODE || u8FactoryTestMode == UART_TEST_MODE) // ????? ??
        {
            mu8Return = SET; // 공장모드
        }
        else
        {
            mu8Return = CLEAR; // 일반모드
        }
    }
    else if ( mu8Value == USER_RX_STATUS )
    {
        /*..hui [24-2-15오전 9:32:24] 일반제어..*/
        /*..hui [24-2-15오전 9:32:40] 추출/커버오픈/설정모드/스마트진단중/플러싱중/얼음세척..*/
        /*..hui [24-7-25오전 10:01:35] 구연산 세척중 추가..*/
        if( (F_WaterOut == SET)
            || (Bit1_Uart_Test_Mode == SET)
            || (Bit0_Pcb_Test_Mode == SET)
            || (bit_filter_all == CLEAR)
            || (gu8_Led_Display_Step == LED_Display__SETTING)
            || (bit_self_test_start == SET)
            || (gu8_flushing_mode != FLUSHING_NONE_STATE)
            || (bit_ice_tank_ster_start == SET)
            || (F_Ice == SET)
            || (bit_acid_clean_start == SET) )
        {
            mu8Return = FALSE; // 제어불가
        }
        else
        {
            mu8Return = TRUE; // 제어가능
        }
    }
    else if ( mu8Value == USER_SMART_POSSIBLE_STATUS )
    {
        /*..hui [24-2-15오전 9:30:40] 스마트진단..*/
        /*..hui [24-2-15오전 9:31:01] 추출/플러싱/얼음세척..*/
        /*..hui [24-7-25오전 10:01:35] 구연산 세척중 추가..*/
        if( (F_WaterOut == SET)
            || (Bit1_Uart_Test_Mode == SET)       // 자동화검사
            || (Bit0_Pcb_Test_Mode == SET)        // PBA 검사
            || (gu8_Led_Display_Step == LED_Display__SETTING)
            || (gu8_flushing_mode != FLUSHING_NONE_STATE)
            || (bit_ice_tank_ster_start == SET)
            || (F_Ice == SET)
            || (bit_acid_clean_start == SET) )
        {
            mu8Return = FALSE; // 정밀진단 불가
        }
        else
        {
            mu8Return = TRUE; // 정밀진단 가능
        }
    }
    else if ( mu8Value == USER_ERROR_STATUS )
    {
        if ( gu8_Error_Code != 0 ) // 에러중(에러표시중)?
        {
            mu8Return = TRUE; // 제어불가
        }
        else
        {
            mu8Return = FALSE; // 제어가능
        }
    }
    else if ( mu8Value == USER_FOTA_POSSIBLE_STATUS ) // FOTA POSSIBLE STATUS (Possible while flushing?)
    {
        if( (F_WaterOut == SET)
            || (gu8_flushing_mode != FLUSHING_NONE_STATE)
            || (bit_ice_tank_ster_start == SET)
            || (bit_acid_clean_start == SET) )
        {
            mu8Return = FALSE; // 포타 불가
        }
        else
        {
            mu8Return = TRUE; //  포타 가능
        }
    }
    else if ( mu8Value == USER_SMART_SENSING_STATUS )
    {
        if( bit_self_test_start == SET )
        {
            mu8Return = TRUE ; // 정밀진단 중
        }
        else
        {
            mu8Return = FALSE; // 일반
        }
    }
    else if ( mu8Value == USER_FACTORY_DIRECTFOTA_STATUS ) // direct fota mode
    {

    }
    else
    {
        mu8Return = 0U;
    }
    return mu8Return;
}


/* User Data Clear */
void ClearUserSystemData ( void )
{
    init_wifi_elec_watt();
    init_water_quantity();
    init_wifi_no_use_time();
    init_wifi_ice_out_time();
}

void SetUserSystemApplyData ( U16 mId )
{

}


/* User Display Setting */
void SetUserSystemDisplay ( U8 mu8Display )
{
    if ( mu8Display == USER_DISPLAY_FOTA ) // FOTA
    {
        /*bit_fota_start = SET;*/
        start_fota();
    }
    else if ( mu8Display == USER_DISPLAY_SELFCHECK ) // Request Selfcheck
    {

    }
    else
    {

    }
}

/* Time Setting */
void SetUserSystemTime ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec, U16 mDay )
{
    get_wifi_time( mYear, mMonth, mDate, mHour, mMin, mSec);
}


/* User Error Data */
U16 GetUserSystemError ( U16 mu16Err )
{
    U16 mu16Data = 0U;

    switch ( mu16Err ) // 0:Normal / 1:Error
    {
        case WIFI_ERROR_0008_COLD_TEMP:

            mu16Data = Bit14_Cold_Temp_Open_Short_Error__E44;

        break;

        case WIFI_ERROR_0009_NATURAL_TEMP:

            mu16Data = Bit15_Amb_Temp_Open_Short_Error__E43;

        break;

        case WIFI_ERROR_000A_TDSIN_TEMP:

            // mu16Data = Bit27_Tds_In_Temp_Open_Short_Error__E90 | Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90;

        break;

        case WIFI_ERROR_000B_TDSOUT_TEMP:

            // mu16Data = Bit28_Tds_Out_Temp_Open_Short_Error__E91 | Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91;

        break;

        case WIFI_ERROR_000C_BLDC_COMP: // BLDC 통신

            mu16Data = Bit7_BLDC_Communication_Error__E27;

        break;

        case WIFI_ERROR_000E_DRAIN_PUMP:

            mu16Data = Bit16_Drain_Pump_Error__E60;

        break;

        case WIFI_ERROR_0011_TDSIN_SENSOR:

            // mu16Data = Bit29_Tds_In_Data_Error__E92 | Bit2_No_Display_Tds_In_Data_Error__E92;

        break;

        case WIFI_ERROR_0012_TDSOUT_SENSOR:

            // mu16Data = Bit30_Tds_Out_Data_Error__E93 | Bit3_No_Display_Tds_Out_Data_Error__E93;

        break;

        case WIFI_ERROR_0016_COLD_LEVEL:

            mu16Data = Bit4_Room_Low_Water_Level_Error__E21;

        break;

        case WIFI_ERROR_0019_STOP_WATER :

            mu16Data = Bit6_Main_Water_Flow_Block_Error__E09;

        break;

        case WIFI_ERROR_001D_LEAK_SENSOR :

            mu16Data = Bit3_Leakage_Sensor_Error__E01;

        break;

        case WIFI_ERROR_0020_ROOM_TEMP :

            mu16Data = Bit2_Room_Temp_Open_Short_Error__E42;

        break;

        case WIFI_ERROR_0021_MICRO_SW_DETECT :

            mu16Data = Bit17_Tray_Micro_SW_Dual_Detect_Error__E61;

        break;

        case WIFI_ERROR_0022_MICRO_SW_MOVE : // 제빙

            // mu16Data = (Bit18_Tray_Micro_SW_Up_Move_Error__E62 | Bit19_Tray_Micro_SW_Down_Move_Error__E63);
            mu16Data = Bit18_Tray_Micro_SW_Up_Move_Error__E62;

        break;

        case WIFI_ERROR_0026_HOT_TANK_TEMP:

            mu16Data = Bit0_Hot_Tank_Temp_Open_Short_Error__E45;

        break;

        case WIFI_ERROR_0029_BLDC_STATUS: // 상태 - 동작에러

            // mu16Data = (Bit7_BLDC_Communication_Error__E27 | bit_bldc_operation_error_total);
            // mu16Data = bit_bldc_operation_error_total;

        break;

        case WIFI_ERROR_0030_TDS_REMOVE: // E99

            // mu16Data = Bit5_No_Display_Tds_Remove_Error__E99;

        break;

        case WIFI_ERROR_0034_UV_COLD_TANK:

            mu16Data = Bit23_Water_Tank_1_2_UV_Error__E74;

        break;

        case WIFI_ERROR_0035_UV_ICE_TANK1:

            mu16Data = Bit24_Ice_Tank_1_2_Back_UV_Error__E75;

        break;

        case WIFI_ERROR_0037_UV_ICE_TRAY:  // 트레이 1

            mu16Data = Bit25_Ice_Tray_1_2_UV_Error__E76;

        break;

        case WIFI_ERROR_003B_MICRO_SW_MOVE2:  // 탈빙

            mu16Data = Bit19_Tray_Micro_SW_Down_Move_Error__E63;

        break;

        case WIFI_ERROR_003C_ROOM_TEMP_OH:

            mu16Data = Bit1_Room_OverHeat_Error__E49;

        break;

        case WIFI_ERROR_003F_NATURAL2_TEMP:

            mu16Data = Bit21_Amb_Side_Temp_Open_Short_Error__E53;

        break;

        case WIFI_ERROR_0045_UV_ICE_TANK3: // 얼음탱크 앞 (#3)

            mu16Data = Bit26_Ice_Tank_3_Front_UV_Error__E79;

        break;

        case WIFI_ERROR_0047_TDS_IN_WATER: // E98

            // mu16Data = Bit4_No_Display_Tds_In_Pollution_Error__E98;

        break;

        case WIFI_ERROR_0049_BLDC_STATUS1:       // COMP 동작 ERROR ( LG : Current Sensing Trip(1), SAMSUNG : Current Sensing Tirp(2) )

            mu16Data = Bit8_BLDC_Operation_Error_Current_Sensing__E81;

        break;

        case WIFI_ERROR_004A_BLDC_STATUS2:       // COMP 동작 ERROR  ( LG : Position sensing error(2), SAMSUNG : Starting Fail(1) )

            mu16Data = Bit9_BLDC_Operation_Error_Starting_Fail__E82;

        break;

        case WIFI_ERROR_004B_BLDC_STATUS3:       // COMP 동작 ERROR ( LG : Over current error(6), SAMSUNG : Over current error(3) )

            mu16Data = Bit10_BLDC_Operation_Error_Over_Current__E83;

        break;

        case WIFI_ERROR_004C_BLDC_STATUS4:       // COMP 동작 ERROR ( LG : IPM Fault(7), SAMSUNG : Overheat of the controller(5) )

            mu16Data = Bit11_BLDC_Operation_Error_Overheat__E84;

        break;

        case WIFI_ERROR_004D_BLDC_STATUS5:       // COMP 동작 ERROR ( LG : Communication error(8), SAMSUNG : Disconnection of Communication(6) )

            mu16Data = Bit12_BLDC_Operation_Error_Disconnection_Comm__E85;

        break;

        case WIFI_ERROR_004E_BLDC_STATUS6:       // COMP 동작 ERROR ( LG : Overload Protection(9), SAMSUNG : Abnormal Voltage(4) )

            mu16Data = Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86;

        break;



        default:
            mu16Data = 0U;
        break;
    }
    return mu16Data;
}




/* User Function Data */
U16 GetUserSystemFunction ( U16 mu16Func )
{
    U16 mu16Data = 0U;
    U16 buf = 0;
    I16 ibuf = 0;
    U8 mu8_default = 0;
    static U8 u8flushingBuf = 0;

    switch ( mu16Func )
    {
        case WIFI_FUNC_0003_HOT_LOCK_SEL :

            if( F_Hot_Lock == SET )
            {
                mu16Data =  WIFI_HOT_LOCK_ON;
            }
            else
            {
                mu16Data =  WIFI_HOT_LOCK_OFF;
            }

        break;

        // case WIFI_FUNC_0004_SAVE_SEL:
            #if 0
            if( F_Save == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }
            #endif

        // break;

        case WIFI_FUNC_0005_LOCK_SEL:

            if( F_All_Lock == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        //case WIFI_FUNC_0006_MUTE_SEL:

            #if 0
            if( F_Mute_Enable == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }
            #endif

        //break;

        case WIFI_FUNC_0008_ICE_SEL:

            if( bit_fast_ice_make == COLD_FIRST_ICE_MAKE )
            {
                /*..hui [23-6-23오후 4:07:01] 냉수우선 - 1..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-6-23오후 4:07:05] 얼음우선 - 3..*/
                mu16Data = 3;
            }

        break;

        case WIFI_FUNC_000B_WATER_SEL :

            if( u8WaterOutState == PURE_WATER_SELECT )
            {
                mu16Data = 1;
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                mu16Data = 2;
            }
            else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
            {
                mu16Data = 3;
            }

        break;

        case WIFI_FUNC_000D_WATER_OUTQUANTITY :

            if( F_WaterOut == SET )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = gu16_wifi_total_quant;

                init_water_quantity();
                // gu8_wifi_water_send_count++;
                /*..hui [24-1-9오후 1:29:37] 1010보내고 1014까지 보내고 난후 초기화하기위해 카운트..*/
                // if( gu8_wifi_water_send_count >= 2 )
                // {
                //     gu8_wifi_water_send_count = 2;
                //     init_water_quantity();
                // }
                // else{}
            }

        break;

        case WIFI_FUNC_0015_TDS_IN :

            /*mu16Data = gu16_recent_tds_in_data;*/

        break;

        case WIFI_FUNC_0016_TDS_OUT :

            /*mu16Data = gu16_recent_tds_out_data;*/

        break;

        case WIFI_FUNC_0018_TDS_INTEMP :

            /*mu16Data = gu8_TDS_In_Temperature_One_Degree;*/

        break;

        case WIFI_FUNC_0019_TDS_OUTTEMP :

            /*mu16Data = gu8_TDS_Out_Temperature_One_Degree;*/

        break;

        case WIFI_FUNC_001C_HOT_SELTEMP:

            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
                {
                    mu16Data = 95;
                }
                else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
                {
                    mu16Data = 85;
                }
                else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
                {
                    mu16Data = 77;
                }
                else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
                {
                    mu16Data = 43;
                }
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0024_HEART_TIME4:

            /*..hui [21-3-17오후 7:56:45] 닫혔을때만 시간 보냄.. 열렸을때는 0으로.. 현민..*/
            if( F_Tank_Cover_Input == SET )
            {
                mu16Data = gu16_cody_care_timer_sec;
            }
            else
            {
                mu16Data = 0;
            }

            /*..hui [21-3-5오후 3:08:57] 커버 닫히면 데이타 보내고 여기서 초기화..*/
            if( F_Tank_Cover_Input == SET )
            {
                gu8_cody_care_timer_msec = 0;
                gu16_cody_care_timer_sec = 0;
            }
            else{}

        break;

        case WIFI_FUNC_002C_SILVER_CARE :

            // 48시간 미사용 (0미경과 1:경과시)
            if( gu16_silver_timer_min >= SILVER_CARE_TIME_MIN )
            {
                if ( u8FirstSilverCare == CLEAR )
                {
                    u8FirstSilverCare = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                u8FirstSilverCare = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0030_ICE_MAKETIME:

            /*..hui [22-9-15오전 9:51:25] 얼음 추출 시간 추가..*/
            if( F_Ice == CLEAR )
            {
                mu16Data = (U16)(gu32_wifi_ice_out_time / 10);

                /*gu32_wifi_ice_out_time = 0;*/

                gu8_wifi_ice_send_count++;

                /*..hui [24-1-9오후 1:29:37] 1010보내고 1014까지 보내고 난후 초기화하기위해 카운트..*/
                if( gu8_wifi_ice_send_count >= 2 )
                {
                    gu8_wifi_ice_send_count = 2;
                    gu32_wifi_ice_out_time = 0;
                }
                else{}
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0031_VOICE_SEL:

            if( gu8Sound_Type == SOUND_TYPE_VOICE )
            {
                mu16Data = 3;
            }
            else if( gu8Sound_Type == SOUND_TYPE_MELODY )
            {
                mu16Data = 2;
            }
            else /*if( gu8Sound_Type == SOUND_TYPE_MUTE )*/
            {
                mu16Data = 1;
            }

        break;


        case WIFI_FUNC_0032_ICELOCK_SEL:

            if( F_Ice_Lock == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0033_VOICE_VOL_SEL:

            if( gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_1 )
            {
                mu16Data = 1;
            }
            else if( gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_2 )
            {
                mu16Data = 2;
            }
            else if( gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_3 )
            {
                mu16Data = 3;
            }
            else if( gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_4 )
            {
                mu16Data = 4;
            }
            else /*if( gu8VoiceVolumeLevel == SOUND_VOLUME_LEVEL_5 )*/
            {
                mu16Data = 5;
            }

        break;

        case WIFI_FUNC_0035_COVER1_OPEN:

            if ( bit_filter_cover == SET )
            {
                /*..hui [21-8-3오후 12:48:23] 닫힘..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-8-3오후 12:48:30] 열림..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0036_COVER2_OPEN:

            if ( F_Tank_Cover_Input == SET )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;


        case WIFI_FUNC_0039_HOT_SEL:

            if( F_Hot_Enable == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_003D_HEIGHT_SEL:

            if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
            {
                mu16Data = 0;
            }
            else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
            {
                mu16Data = 1;
            }
            else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
            {
                mu16Data = 2;
            }
            else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
            {
                mu16Data = 3;
            }

        break;

        case WIFI_FUNC_0040_SMART_CHECK_RQST :

            if( bit_self_test_start == 0 )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }


        break;

        case WIFI_FUNC_0041_SMART_CHECK_STATUS :

            /*mu16Data = gu8_wifi_self_test_state;*/

            if( (F_WaterOut == SET)
                || (Bit1_Uart_Test_Mode == SET)
                || (Bit0_Pcb_Test_Mode == SET)
                || ( gu8_flushing_mode > FLUSHING_NONE_STATE )
                || bit_flushing_water_start == SET
                || bit_ice_tank_ster_start == SET
                || F_Ice == SET )
            {
                mu16Data = WIFI_SELF_TEST_PROHIBIT;
                gu8_wifi_self_test_state = WIFI_SELF_TEST_PROHIBIT;
            }
            else
            {
                mu16Data = gu8_wifi_self_test_state;
            }

        break;

        case WIFI_FUNC_0042_SMART_CHECK_PROGRESS : // 0 ~ 100 %

            mu16Data = gu8_wifi_self_test_progress;

        break;

        case WIFI_FUNC_0043_FILTER_STATUS1 :

            /*..hui [23-10-4오후 1:24:45] 0x43이 NEO 필터..*/
            if( bit_neo_filter_1_reed == SET )
            {
                /*..hui [21-9-13오후 7:30:42] 장착..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-13오후 7:30:49] 분리..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0044_FILTER_STATUS2 :

            /*..hui [23-10-4오후 1:24:53] 0x44는 INO 필터..*/
            if( bit_ino_filter_3_reed == SET )
            {
                /*..hui [21-9-13오후 7:30:42] 장착..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-13오후 7:30:49] 분리..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0045_FILTER_STATUS3 :

            /*..hui [23-10-4오후 1:24:59] 0x45가 RO 필터..*/
            if( bit_ro_filter_2_reed == SET )
            {
                /*..hui [21-9-13오후 7:30:42] 장착..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-13오후 7:30:49] 분리..*/
                mu16Data = 1;
            }

        break;


        case WIFI_FUNC_0049_OUT_BUTTON_LIGHT:

            if( F_Extract_Led_OnOff == CLEAR )
            {
                /*..hui [23-6-23오후 2:32:59] OFF..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [23-6-23오후 2:33:03] ON..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0053_FILTER_RESET1 : // NEO

            /*..hui [23-6-23오후 2:40:38] NEO 필터 리셋..*/
            if( bit_wifi_neo_filter_1_reset == SET )
            {
                mu16Data = 1;
                bit_wifi_neo_filter_1_reset = CLEAR;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0054_FILTER_RESET2 :  // INO

            /*..hui [23-6-23오후 2:40:56] INO 필터 리셋.. NEO, INO 공용임..*/
            /*..hui [23-6-23오후 2:42:30] 어떻게 해야....??????..*/
            if( bit_wifi_ino_filter_3_reset == SET )
            {
                mu16Data = 1;
                bit_wifi_ino_filter_3_reset = CLEAR;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0055_FILTER_RESET3 :  // RO

            if( bit_wifi_ro_filter_2_reset == SET )
            {
                mu16Data = 1;
                bit_wifi_ro_filter_2_reset = CLEAR;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0059_ICE_ONOFF_SEL :

            if( F_IceOn == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_005A_UV_ICE_TANK_STATUS :

            if( bit_uv_ice_tank_out == SET && bit_uv_fault_test_start == CLEAR )
            {
                if( bit_wifi_first_ice_tank_uv == CLEAR )
                {
                    bit_wifi_first_ice_tank_uv = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ice_tank_uv = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_005B_UV_ICE_TRAY_STATUS :

            /*if( bit_uv_ice_tray_out == SET )*/
            /*..hui [24-11-28오전 10:12:38] 전원인가후 고장 테스트중에는 안보냄..*/
            if( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR && bit_uv_fault_test_start == CLEAR )
            {
                if( bit_wifi_first_ice_tray_uv == CLEAR )
                {
                    bit_wifi_first_ice_tray_uv = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ice_tray_uv = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_005C_SMART_CHECK_RESULT :
            // No modification required. It is used for public use.
            mu16Data = WifiSmartCheckResultData;
            WifiSmartCheckResultData = 0U;

        break;

        case WIFI_FUNC_005E_SLEEP_MODE_SEL :

            /*if( bit_child_lock_enable == CLEAR )*/
            if( bit_sleep_mode_enable == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_005F_SLEEP_START_HOUR :

            mu16Data = (U16)gu8_sleep_mode_start_hour;

        break;

        case WIFI_FUNC_0060_SLEEP_START_MIN :

            mu16Data = (U16)gu8_sleep_mode_start_minute;

        break;

        case WIFI_FUNC_0061_SLEEP_END_HOUR :

            mu16Data = (U16)gu8_sleep_mode_finish_hour;

        break;

        case WIFI_FUNC_0062_SLEEP_END_MIN :

            mu16Data = (U16)gu8_sleep_mode_finish_minute;

        break;


        case WIFI_FUNC_0065_DEFAULT_TEMP_SEL :

            if( gu8_hot_default_temp == HOT_SET_TEMP_4__200_oF_95_oC )
            {
                mu16Data = 3;
            }
            else if( gu8_hot_default_temp == HOT_SET_TEMP_3__185_oF_85_oC )
            {
                mu16Data = 2;
            }
            else if( gu8_hot_default_temp == HOT_SET_TEMP_2__170_oF_77_oC )
            {
                mu16Data = 1;
            }
            else /*if( gu8_hot_default_temp == HOT_SET_TEMP_1__110_oF_43_oC )*/
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL :

            if( gu8Cup_level_Default == CUP_LEVEL__4_OZ__120_ML )
            {
                mu16Data = 0;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__6_OZ__175_ML)
            {
                mu16Data = 1;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__8_OZ__235_ML)
            {
                mu16Data = 2;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__10_OZ__295_ML)
            {
                mu16Data = 3;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__12_OZ__355_ML)
            {
                mu16Data = 4;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__14_OZ__415_ML)
            {
                mu16Data = 5;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__16_OZ__475_ML)
            {
                mu16Data = 6;
            }
            else if(gu8Cup_level_Default == CUP_LEVEL__20_OZ__590_ML)
            {
                mu16Data = 7;
            }
            #if 0
            else if(gu8Cup_level_Default == CUP_LEVEL__32_OZ__945_ML)
            {
                mu16Data = 8;
            }
            #endif
            else /*if(gu8Cup_level_Default == CUP_LEVEL__CONTINUE)*/
            {
                /*mu16Data = 9;*/
                mu16Data = 9;
            }

        break;

        case WIFI_FUNC_0067_WATER_QUANTITY_USE_SEL0 :

            if( Bit0_4_Oz_Select__120_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0068_WATER_QUANTITY_USE_SEL1:

            if( Bit1_6_Oz_Select__175_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0069_WATER_QUANTITY_USE_SEL2:

            if( Bit2_8_Oz_Select__235_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_006A_WATER_QUANTITY_USE_SEL3 :

            if( Bit3_10_Oz_Select__295_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_006B_WATER_QUANTITY_USE_SEL4 :

            if( Bit4_12_Oz_Select__355_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_006C_WATER_QUANTITY_USE_SEL5:

            if( Bit5_14_Oz_Select__415_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_006D_WATER_QUANTITY_USE_SEL6:

            if( Bit6_16_Oz_Select__475_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_006E_WATER_QUANTITY_USE_SEL7 :

            if( Bit7_20_Oz_Select__590_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        #if 0
        case WIFI_FUNC_006F_WATER_QUANTITY_USE_SEL8 :

            #if 0
            if( Bit8_32_Oz_Select__945_ml == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }
            #endif

            mu16Data = 0;

        break;
        #endif

        case WIFI_FUNC_0070_WATER_QUANTITY_USE_SEL9 :

            if( Bit9_Continue_Select__Continue == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0072_WATER_QUANTITY_SORT_SEL :

            if( gu8_cup_level_order == CUP_LEVEL_ORDER__UP )
            {
                /*..hui [23-6-23오후 4:13:03] 오름차순..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [23-6-23오후 4:13:07] 내림차순..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0073_WATER_TEMP_SORT_SEL :

            if( gu8_hot_level_order == HOT_TEMP_LEVEL_ORDER__UP )
            {
                /*..hui [23-6-23오후 4:13:03] 오름차순..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [23-6-23오후 4:13:07] 내림차순..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0075_TEMP_UNIT_SEL :

            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                /*..hui [23-6-23오후 4:14:52] 화씨..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [23-6-23오후 4:14:56] 섭씨..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0076_WATER_QUANTITY_UNIT_SEL:

            if( gu8_ml__oz_select == Oz_SELECT )
            {
                /*..hui [23-6-23오후 4:15:35] Oz..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [23-6-23오후 4:15:38] mL..*/
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_0077_HOT_TARGET_TEMP_TIME: // Heater OFF

            /*..hui [23-6-23오후 4:16:04] 온수 목표 온도 도달 시간??..*/
            if( bit_wifi_hot_heater == CLEAR )
            {
                if( bit_wifi_heater_on_time_update == SET )
                {
                    bit_wifi_heater_on_time_update = CLEAR;
                    mu16Data = gu16_hot_target_reach_timer_sec;
                    gu32_hot_target_reach_timer_ms = 0;
                    gu16_hot_target_reach_timer_sec = 0;
                }
                else
                {
                    mu16Data = 0;
                }
            }
            else
            {
                bit_wifi_heater_on_time_update = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0078_COLD_TARGET_TEMP_TIME :// COMP OFF

            /*..hui [23-6-23오후 4:16:22] 냉수 목표 온도 도달 시간..???..*/
            if( bit_wifi_comp == CLEAR )
            {
                if( bit_wifi_comp_on_time_update == SET )
                {
                    bit_wifi_comp_on_time_update = CLEAR;
                    mu16Data = gu16_cold_target_reach_timer_sec;
                    gu32_cold_target_reach_timer_ms = 0;
                    gu16_cold_target_reach_timer_sec = 0;
                }
                else
                {
                    mu16Data = 0;
                }
            }
            else
            {
                bit_wifi_comp_on_time_update = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_007C_COLDTANK_LOW_WATERLEVEL :

            if( bit_wifi_cold_low == SET )
            {
                if( bit_wifi_first_cold_low == CLEAR )
                {
                    bit_wifi_first_cold_low = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_cold_low = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_007D_COLDTANK_HIGH_WATERLEVEL :

            if( bit_wifi_cold_high == SET )
            {
                if( bit_wifi_first_cold_high == CLEAR )
                {
                    bit_wifi_first_cold_high = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_cold_high = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0080_HIGH_TEMP_STL_TIME:

            mu16Data = (U16)gu8_wifi_period_ster_hour;

        break;

        case WIFI_FUNC_0081_HIGH_TEMP_STL_TIME_M:

            mu16Data = (U16)gu8_wifi_period_ster_minute;

        break;

        case WIFI_FUNC_0082_UNUSE_POW_SAVING_STATUS :

            /*..hui [23-6-23오후 4:53:11] 미사용 절전 상태..*/
            if( bit_9_hour_no_use_start == SET )
            {
                if( bit_wifi_first_no_use_save == CLEAR )
                {
                    bit_wifi_first_no_use_save = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_no_use_save = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0083_POWER_SAVING_STATUS: // 취침 절전 상태 0(OFF) / 1(SET) / 2 (ING)

            if( bit_sleep_mode_start == SET )
            {
                if( bit_wifi_first_sleep == CLEAR )
                {
                    bit_wifi_first_sleep = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_sleep = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_008A_COLDTANK_UV_STL_STATUS:

            /*..hui [24-11-28오전 10:12:38] 전원인가후 고장 테스트중에는 안보냄..*/
            if( bit_uv_water_tank_out == SET && bit_uv_fault_test_start == CLEAR )
            {
                if( bit_wifi_first_water_tank_uv == CLEAR )
                {
                    bit_wifi_first_water_tank_uv = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_water_tank_uv = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_008B_HEATER_STATUS:

            if( bit_wifi_hot_heater == SET )
            {
                if( bit_wifi_first_hot_heater == CLEAR )
                {
                    bit_wifi_first_hot_heater = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_hot_heater = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_008C_COMP_STATUS :

            if( F_Comp_Output == SET )
            {
                if( bit_wifi_first_comp == CLEAR )
                {
                    bit_wifi_first_comp = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_comp = CLEAR;
                mu16Data = 0;
            }


        break;

        // ice
        case WIFI_FUNC_008F_ICE_FULL_STATUS :

            if( F_IceFull == SET )
            {
                if( bit_wifi_first_ice_full == CLEAR )
                {
                    bit_wifi_first_ice_full = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ice_full = CLEAR;
                mu16Data = 0;
            }


        break;

        case WIFI_FUNC_0093_ICEMAKING_STAUTS :

            mu16Data = gu8_wifi_ice_make_state;

        break;

        case WIFI_FUNC_0095_ICEMAKING_COMPLET_TIME :

            if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
            {
                mu16Data = (U16)(gu32_wifi_ice_make_time / 10);
                gu32_wifi_ice_make_time = 0;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0096_DEICING_COMPLET_TIME :

            if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
            {
                mu16Data = (U16)(gu32_wifi_hot_gas_time / 10);
                gu32_wifi_hot_gas_time = 0;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0097_TARY_WATER_COMPLET_TIME :

            if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
            {
                mu16Data = (U16)(gu16_wifi_tray_in_time / 10);
                gu16_wifi_tray_in_time = 0;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_0098_TARY_WATER_QUANTITY : // ml

            if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
            {
                mu16Data = gu16_wifi_tray_in_flow;
                gu16_wifi_tray_in_flow = 0;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_009B_DRAINTANK_LOW_WLEVEL :

            if( F_drain_water_level_low == SET )
            {
                if( bit_wifi_first_drain_low == CLEAR )
                {
                    bit_wifi_first_drain_low = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_drain_low = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_009C_DRAINTANK_HIGH_WLEVEL :

            if( F_drain_water_level_high == SET )
            {
                if( bit_wifi_first_drain_high == CLEAR )
                {
                    bit_wifi_first_drain_high = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_drain_high = CLEAR;
                mu16Data = 0;
            }


        break;

        case WIFI_FUNC_009F_ICE_EVA_TEMP :

            mu16Data = gu8_Eva_Cold_Temperature_One_Degree;

        break;

        case WIFI_FUNC_00A0_COLD_TANK_TEMP :

            mu16Data = gu8_Cold_Temperature_One_Degree;

        break;

        case WIFI_FUNC_00A1_HOT_TANK_TEMP :

            mu16Data = gu8_Hot_Tank_Temperature_One_Degree;

        break;

        case WIFI_FUNC_00A2_CHILD_LOCK :

            if( bit_child_lock_enable == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }

        break;

        case WIFI_FUNC_00A9_UNUSED_TIME :

            if( gu8_wifi_no_use_time_send == SET )
            {
                gu8_wifi_no_use_time_send = CLEAR;
                mu16Data = gu16_wifi_no_use_timer_min;

                gu16_wifi_no_use_timer_sec = 0;
                gu16_wifi_no_use_timer_min = 0;
            }
            else
            {
                mu16Data = 0;
            }

        break;

        /*..hui [23-8-30오전 10:31:47] 테스트용? 나중에 확인..*/
        case WIFI_FUNC_00AA_SMART_SAVING_SET_TIME :

            mu16Data = gu8_wifi_smart_unused_setting_time;

        break;

        case WIFI_FUNC_00AB_SAMRT_SAVING_STATE :

            if( bit_smart_first_send == SET )
            {
                bit_smart_first_send = CLEAR;

                if( gu8_smart_operation_mode == GREEN_WEEK )
                {
                    gu8_wifi_smart_save = WIFI_SMART_SAVE_GREEN_WEEK_START;
                }
                else /*if( gu8_smart_operation_mode == INTENSIVE_WEEK )*/
                {
                    gu8_wifi_smart_save = WIFI_SMART_SAVE_INTENSIVE_WEEK_START;
                }
            }
            else
            {
                if( gu8_smart_operation_mode == GREEN_WEEK )
                {
                    gu8_wifi_smart_save = WIFI_SMART_SAVE_GREEN_WEEK_ING;
                }
                else /*if( gu8_smart_operation_mode == INTENSIVE_WEEK )*/
                {
                    gu8_wifi_smart_save = WIFI_SMART_SAVE_INTENSIVE_WEEK_ING;
                }
            }

            mu16Data = (U16)gu8_wifi_smart_save;

        break;

        case WIFI_FUNC_00AC_FILTER1_WATER_USAGE :

            /*..hui [23-8-31오후 3:57:05] 우선 넣어놓고 나중에....*/
            /*..hui [23-8-31오후 3:57:13] 개별로 분리해야함..*/
            /*..hui [23-12-18오후 7:30:13] 개별 분리 완료..*/
            mu16Data = gu16_water_usage_neo_filter;

        break;

        case WIFI_FUNC_00AD_FILTER1_UASGE_DAY :

            mu16Data = gu16_neo_filter_1_remain_day;

        break;

        case WIFI_FUNC_00AE_FILTER2_WATER_USAGE :

            /*..hui [23-12-19오전 9:36:09] 필터2가 INO..*/
            mu16Data = gu16_water_usage_ino_filter;

        break;

        case WIFI_FUNC_00AF_FILTER2_UASGE_DAY :

            mu16Data = gu16_ino_filter_3_remain_day;

        break;

        case WIFI_FUNC_00B0_FILTER3_WATER_USAGE :

            /*..hui [23-12-19오전 9:36:15] 필터3가 RO..*/
            mu16Data = gu16_water_usage_ro_filter;

        break;

        case WIFI_FUNC_00B1_FILTER3_UASGE_DAY :

            mu16Data = gu16_ro_filter_2_remain_day;

        break;

        case WIFI_FUNC_00B2_FILTER_NOTICE1 :

            if( bit_wifi_neo_filter_1_alarm == SET )
            {
                if( bit_wifi_first_neo_alarm == CLEAR )
                {
                    bit_wifi_first_neo_alarm = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_neo_alarm = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_00B3_FILTER_NOTICE2 :

            if( bit_wifi_ino_filter_3_alarm == SET )
            {
                if( bit_wifi_first_ino_alarm == CLEAR )
                {
                    bit_wifi_first_ino_alarm = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ino_alarm = CLEAR;
                mu16Data = 0;
            }

        break;

        case WIFI_FUNC_00B4_FILTER_NOTICE3 :

            if( bit_wifi_ro_filter_2_alarm == SET )
            {
                if( bit_wifi_first_ro_alarm == CLEAR )
                {
                    bit_wifi_first_ro_alarm = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ro_alarm = CLEAR;
                mu16Data = 0;
            }


        break;

        case WIFI_FUNC_00B5_FILTER_FLUSHING :

            // mu16Data = (U16)gu8_wifi_flushing_state;

            if ((gu8_wifi_flushing_state == 1U) || (gu8_wifi_flushing_state == 2U))
            {
                if (u8flushingBuf == 0U )
                {
                    mu16Data = 1U;
                    u8flushingBuf = 1U;
                }
                else
                {
                    mu16Data = 2U;
                }
            }
            else //else if ((gu8_wifi_flushing_state == 3U))
            {
                mu16Data = (U16)gu8_wifi_flushing_state;
                u8flushingBuf = 0;
            }

        break;

        case WIFI_FUNC_00B6_VOICE_LANGUAGE :

            mu16Data = (U16)gu8_voice_language_type;

        break;


        case WIFI_FUNC_00B7_FILTER_SEQ :

            /*..hui [24-1-16오후 3:38:18] 0(1필터 - 15개월), 1(1,3필터 - 15개월), 2(1,3필터 - 30개월)..*/
            /*..hui [24-1-16오후 3:38:33] 3(1,2,3필터 - 30개월), 4(1,2,3필터 - 45개월)..*/
            if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_INO )
            {
                mu16Data = (U16)1;
            }
            else /*if( gu8_filter_change_type == FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )*/
            {
                mu16Data = (U16)3;
            }
        break;

        case WIFI_FUNC_00B8_FILTER1_DDAY:
        // No modification required. It is used for public use.
            mu16Data = GetFilterDayData(WIFI_FUNC_00AD_FILTER1_UASGE_DAY);
        break;

        case WIFI_FUNC_00B9_FILTER2_DDAY:
        // No modification required. It is used for public use.
            mu16Data = GetFilterDayData(WIFI_FUNC_00AF_FILTER2_UASGE_DAY);
        break;

        case WIFI_FUNC_00BA_FILTER3_DDAY:
        // No modification required. It is used for public use.
            mu16Data = GetFilterDayData(WIFI_FUNC_00B1_FILTER3_UASGE_DAY);
        break;

        case WIFI_FUNC_00BD_ICETANK_STL_STATUS :  //고온수 살균 상태( 0:미동작 / 1: 얼음탱크살균(시작) / 2: 얼음탱크살균(동작중) / 3: 얼음탱크살균(완료) )

            mu16Data = (U16)gu8_wifi_ice_ster_state;
        break;

        case WIFI_FUNC_00CB_WATER_EXTRACT_STATUS :

            if( (F_WaterOut == SET) )
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }

        break;

        case WIFI_FUNC_00CC_ICE_EXTRACT_STATUS :

            if( (F_Ice == SET) )
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }

        break;

        case WIFI_FUNC_00CD_SETUP_MODE_STATUS :

            if( (gu8_Led_Display_Step == LED_Display__SETTING))
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }

        break;

        case WIFI_FUNC_00D0_UV_ICE_TANK_STATUS2 :

            /*if( bit_uv_ice_tray_out == SET )*/
            /*..hui [24-11-28오전 10:12:38] 전원인가후 고장 테스트중에는 안보냄..*/
            if( bit_uv_ice_tank_front_out == SET && bit_ice_tray_making_enable == CLEAR && bit_uv_fault_test_start == CLEAR )
            {
                if( bit_wifi_first_ice_tank_front_uv == CLEAR )
                {
                    bit_wifi_first_ice_tank_front_uv = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ice_tank_front_uv = CLEAR;
                mu16Data = 0;
            }


        break;

        case WIFI_FUNC_00D1_ALTITUDE_AUTO :

            mu16Data = 0;

        break;

        case WIFI_FUNC_00FF_CLEANING_STATUS :
        /*
            0 : 미동작(대기)
            1 : 세정수 투입[시작]
            2 : 세정수 투입중
            3 : 세정수 방치[시작]
            4 : 세정수 방치중
            5 : 세정수 배수[시작]
            6 : 세정수 배수중
            7 : 탱크 세척[시작]
            8 : 탱크 세척중
            9 : 세척수 배수[시작]
            10 : 세척수 배수중
            11 : 세척 완료[시작]
        */
            mu16Data = (U16)gu8_wifi_acid_clean_state;

        break;

        case WIFI_FUNC_0100_CLEANING_SW_STATUS : // 0: 분리, 1: 장착

            if( bit_acid_reed == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                /*..hui [24-7-17오후 6:52:59] 닫힘..*/
                /*mu16Data = 0;*/
                /*..hui [24-7-17오후 6:54:35] 장착.. 감지되면 에러임..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                /*..hui [24-7-17오후 6:53:02] 열림..*/
                /*mu16Data = 1;*/
                /*..hui [24-7-17오후 6:55:08] 분리.. 정상..*/
                mu16Data = 0;
            }
        break;

        case WIFI_FUNC_0101_STERILIZE_REMAINING_DAY : // 고온살균 잔여일 (얼음탱크 살균)
            ibuf = (I16)(PERIODIC__STER_CYCLE - (I8)gu8_periodic_ster_count);
            if( (ibuf > 0) && (ibuf <= PERIODIC__STER_CYCLE) )
            {
                /* 00:00 ~ 살균설정시간 사이. 자정부터 미리 -1카운트하여 표시
                (WiFi DATA는 빌트인과 잔여일 표시 동일하게..) */
                if ((gu16_periodic_ster_current_time_total >= 0)
                && (gu16_periodic_ster_current_time_total < gu16_periodic_ster_time_total))
                {
                    mu16Data = (U16)(ibuf-1);
                }
                else
                {
                    mu16Data = (U16)(ibuf);
                }
            }
            else
            {
                mu16Data = 0U;
            }


            break;

        default:
            mu16Data = 0U;
        break;
    }
    return mu16Data;
}

/* User Sensor Data */
I16 GetUserSystemSensor ( U16 mu16Sen )
{
//  I16 buf = 0;
    I16 mi16Data = 0;

    switch ( mu16Sen )
    {
        case WIFI_SENSOR_0001_COLD_TEMP : //  -127 ~ 127

            mi16Data = gu8_Cold_Temperature_One_Degree;

            if ( mi16Data >= 99 )
            {
                mi16Data = 99;
            }
            else{}

        break;

        case WIFI_SENSOR_0002_HOT_TEMP : //  -127 ~ 127

            mi16Data = gu8_Hot_Tank_Temperature_One_Degree;

            if ( mi16Data >= 99 )
            {
                mi16Data = 99;
            }
            else{}

        break;

        case WIFI_SENSOR_0003_WATER_TEMP : //  -127 ~ 127

            mi16Data = gu8_Room_Temperature_One_Degree;

            if ( mi16Data >= 99 )
            {
                mi16Data = 99;
            }
            else{}

        break;

        case WIFI_SENSOR_0004_OUT_TEMP : //  -127 ~ 127

            mi16Data = gu8_Amb_Front_Temperature_One_Degree;

            if ( mi16Data >= 99 )
            {
                mi16Data = 99;
            }
            else{}

        break;

        case WIFI_SENSOR_0006_FILTER1_DATA:  // 사용량 % (잔여사용량 아님)
        // No modification required. It is used for public use.
        /*mi16Data = GetFilterData(WIFI_FUNC_00AC_FILTER1_WATER_USAGE, 3600U);*/
        mi16Data = GetFilterData(WIFI_FUNC_00AC_FILTER1_WATER_USAGE, 3785U);

        break;

        case WIFI_SENSOR_0007_FILTER2_DATA: // 사용량 % (잔여사용량 아님)
        // No modification required. It is used for public use.
        /*mi16Data = GetFilterData(WIFI_FUNC_00AE_FILTER2_WATER_USAGE, 3600U);*/
        mi16Data = GetFilterData(WIFI_FUNC_00AE_FILTER2_WATER_USAGE, 3785U);

        break;

        case WIFI_SENSOR_0008_FILTER3_DATA: // 사용량 % (잔여사용량 아님)
        // No modification required. It is used for public use.
        /*mi16Data = GetFilterData(WIFI_FUNC_00B0_FILTER3_WATER_USAGE, 7200U);*/
        mi16Data = GetFilterData(WIFI_FUNC_00B0_FILTER3_WATER_USAGE, 7570U);

        break;

        case WIFI_SENSOR_000E_WATT_DATA : // 0.01~250.00 (ex -> 1.78 = 178)

            /*mu16Data = gu16_wifi_total_watt;*/

            if( gu16_wifi_total_watt == 0 )
            {
                mi16Data = 1;
            }
            else
            {
                mi16Data = (gu16_wifi_total_watt / 10);
            }

            init_wifi_elec_watt();

        break;

        case WIFI_SENSOR_000F_COMP_DATA:

            if( F_Comp_Output == SET )
            {
                mi16Data = 1;
            }
            else
            {
                mi16Data = 0;
            }

        break;

        case WIFI_SENSOR_0014_HEATER_DATA:

            if( F_Heater_Output == SET )
            {
                mi16Data = 1;
            }
            else
            {
                mi16Data = 0;
            }

        break;

        case WIFI_SENSOR_0015_OUT2_TEMP:

            mi16Data = gu8_Amb_Side_Temperature_One_Degree;

            if ( mi16Data >= 99 )
            {
                mi16Data = 99;
            }

        break;

        case WIFI_SENSOR_0016_BAR_PRESSURE:

            /*..hui [24-7-17오후 5:56:02] 추후 추가..*/
            mi16Data = 0;

        break;



        default:
          mi16Data = 0;
        break;
    }
    return mi16Data;
}

/* User Part Data */        //  ?????? ??????
U16 GetUserSystemPart ( U16 mu16Part )
{
    U16 mu16Data = 9999U;
    U8 mu8_OPENSHORT_Error = 0;
    switch ( mu16Part )
    {
        case WIFI_PART_0000_VALVE_FEED:

            mu16Data = U16_FEED_1_1_DC_Current_PART_0000;
            initial_each_self_data( DC_LOAD_1__FEED_VALVE );

            break;

        case WIFI_PART_0001_VALVE_NOS:

            mu16Data = U16_NOS_1_2_DC_Current_PART_0001;
            initial_each_self_data( DC_LOAD_2__NOS_VALVE );

            break;

        case WIFI_PART_0002_VALVE_HOT_OUT:

            mu16Data = U16_HOT_OUT_3_3_DC_Current_PART_0002;
            initial_each_self_data( DC_LOAD_3__HOT_OUT_VALVE );

            break;

        case WIFI_PART_0003_VALVE_PURE_OUT:

            mu16Data = U16_PURE_OUT_3_2_DC_Current_PART_0003;
            initial_each_self_data( DC_LOAD_4__PURE_OUT_VALVE );

            break;

        case WIFI_PART_0004_VALVE_COLD_OUT:

            mu16Data = U16_COLD_OUT_3_1_DC_Current_PART_0004;
            initial_each_self_data( DC_LOAD_5__COLD_OUT_VALVE );

            break;

        case WIFI_PART_0009_VALVE_HOT_IN:

            mu16Data = U16_HOT_IN_6_2_DC_Current_PART_0009;
            initial_each_self_data( DC_LOAD_6__HOT_IN_VALVE );

            break;

        case WIFI_PART_000B_VALVE_COLD_AIR:

            mu16Data = U16_AIR_FEED_2_DC_Current_PART_000B;
            initial_each_self_data( DC_LOAD_7__AIR_FEED_VALVE );

            break;

        case WIFI_PART_000D_VALVE_COLD_DRAIN:

            mu16Data = U16_COLD_DRAIN_3_4_DC_Current_PART_000D;
            initial_each_self_data( DC_LOAD_8__COLD_DRAIN_VALVE );

            break;

        case WIFI_PART_0015_VALVE_ICE_TRAY_IN:

            mu16Data = U16_ICE_TRAY_IN_6_1_DC_Current_PART_0015;
            initial_each_self_data( DC_LOAD_9__ICE_TRAY_IN_VALVE );

            break;

        case WIFI_PART_0018_VALVE_FLUSHING:

            mu16Data = U16_FLUSHING_FEED_8_2_DC_Current_PART_0018;
            initial_each_self_data( DC_LOAD_10__FLUSHING_FEED );

            break;

        case WIFI_PART_0019_VALVE_RO_FLUSHING:

            mu16Data = U16_RO_FLUSHING_MOTOR_DC_Current_PART_0019;
            initial_each_self_data( DC_LOAD_11__RO_FLUSHING_MOTOR );

            break;

        case WIFI_PART_001A_VALVE_HOT_OVER_HEAT:

            mu16Data = U16_HOT_OVERHEAT_5_3_DC_Current_PART_001A;
            initial_each_self_data( DC_LOAD_12__HOT_OVERHEAT_VALVE );

            break;

        case WIFI_PART_001B_VALVE_HOT_STERILIZE_L:

            mu16Data = U16_HOT_STER_LEFT_DC_Current_PART_001B;
            initial_each_self_data( DC_LOAD_13__HOT_STER_LEFT_VALVE );

            break;

        case WIFI_PART_001C_VALVE_HOT_STERILIZE_R:

            mu16Data = U16_HOT_STER_RIGHT_DC_Current_PART_001C;
            initial_each_self_data( DC_LOAD_14__HOT_STER_RIGHT_VALVE );

            break;

        case WIFI_PART_001F_VALVE_FLUSHING_NOS: // NOS

            mu16Data = U16_FLUSHING_NOS_8_1_DC_Current_PART_001F;
            initial_each_self_data( DC_LOAD_15__FLUSHING_NOS_VALVE );

            break;

        case WIFI_PART_0101_LEVEL_COLD_HIGH:

            if( pLEVEL_PURIFY_HIGH == SET )
            {
                /*..hui [23-12-21오후 8:12:16] 감지..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21오후 8:12:22] 미감지..*/
                mu16Data = 0;
            }

            break;

        case WIFI_PART_0103_LEVEL_COLD_LOW:

            if( pLEVEL_PURIFY_LOW == SET )
            {
                /*..hui [23-12-21오후 8:12:16] 감지..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21오후 8:12:22] 미감지..*/
                mu16Data = 0;
            }

            break;

        case WIFI_PART_010B_LEVEL_DRAIN_HIGH:

            if( pLEVEL_ICE_DRAIN_HIGH == SET )
            {
                /*..hui [23-12-21오후 8:12:16] 감지..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21오후 8:12:22] 미감지..*/
                mu16Data = 0;
            }

            break;

        case WIFI_PART_010D_LEVEL_DRAIN_LOW:

            if( pLEVEL_ICE_DRAIN_LOW == SET )
            {
                /*..hui [23-12-21오후 8:12:16] 감지..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21오후 8:12:22] 미감지..*/
                mu16Data = 0;
            }

            break;

        case WIFI_PART_010F_LEVEL_COLD_ERROR:
            mu16Data = GetUserSystemError(WIFI_ERROR_0016_COLD_LEVEL);

        break;

        case WIFI_PART_0201_COLD_BLDC:

            // if( Bit7_BLDC_Communication_Error__E27 == SET )
            // {
            //     mu16Data = 27;
            // }
            // else if( bit_bldc_operation_error_total == SET )
            // {
            //     mu16Data = (U16)gu8_bldc_error_code;
            // }
            // else
            // {
            //     /*..hui [23-12-21오후 8:13:59] 정상..*/
            //     mu16Data = 0;
            // }

            break;

        case WIFI_PART_0204_COLD_FAN:

            mu16Data = U16_COLD_FAN_DC_Furrent_PART_0204;
            initial_each_self_data( DC_LOAD_16__COLD_FAN );

            break;

        case WIFI_PART_0206_COLD_TEMP_1:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Cold_Temperature_One_Degree;
            }

            break;

        case WIFI_PART_0208_COLD_ROOM_TEMP:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Amb_Front_Temperature_One_Degree;
            }

            break;

        case WIFI_PART_020D_COLD_ROOM_TEMP2:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Amb_Side_Temperature_One_Degree;
            }

            break;

        case WIFI_PART_020E_COLD_STOP_ERROR:
            mu16Data = GetUserSystemError(WIFI_ERROR_0019_STOP_WATER);

        break;

        case WIFI_PART_0210_COLD_BLDC_ERROR:
            mu16Data = GetUserSystemError(WIFI_ERROR_000C_BLDC_COMP);
        break;

        case WIFI_PART_0214_COLD_BLDC1:
            mu16Data = GetUserSystemError(WIFI_ERROR_0049_BLDC_STATUS1);
        break;
        case WIFI_PART_0215_COLD_BLDC2:
            mu16Data = GetUserSystemError(WIFI_ERROR_004A_BLDC_STATUS2);
        break;
        case WIFI_PART_0216_COLD_BLDC3:
            mu16Data = GetUserSystemError(WIFI_ERROR_004B_BLDC_STATUS3);
        break;
        case WIFI_PART_0217_COLD_BLDC4:
            mu16Data = GetUserSystemError(WIFI_ERROR_004C_BLDC_STATUS4);
        break;
        case WIFI_PART_0218_COLD_BLDC5:
            mu16Data = GetUserSystemError(WIFI_ERROR_004D_BLDC_STATUS5);
        break;
        case WIFI_PART_0219_COLD_BLDC6:
            mu16Data = GetUserSystemError(WIFI_ERROR_004E_BLDC_STATUS6);
        break;

        case WIFI_PART_0301_HOT_TEMP:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Hot_Tank_Temperature_One_Degree;
            }

            break;


        case WIFI_PART_0308_HOT_TARGET_TEMP_TIME:

            mu16Data = gu16_wifi_hot_target_time_min;
            /*gu16_wifi_hot_target_time_min = SELF_TEST_INITIAL_DATA;*/
            /*gu16_wifi_hot_target_time_min = 0;*/

        break;

        case WIFI_PART_0309_HOT_BAR_PRESSURE:

            mu16Data = 0;

        break;

        case WIFI_PART_0402_SENSOR_LEAK:

            /*if( gu16ADLeakage >= LEAKAGE_DETECT_AD )*/
            if( Bit3_Leakage_Sensor_Error__E01 == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

            break;

        case WIFI_PART_0403_SENSOR_FLOW:

            mu16Data = U16_ICE_TRAY_FLOW_SENSOR_PART_0403;
            initial_each_self_data( SENSOR_17__ICE_TRAY_FLOW_SENSOR );

            break;

        case WIFI_PART_0405_SENSOR_FILTER_REED:

            if( bit_filter_cover == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                mu16Data = 1;
            }

            break;

        case WIFI_PART_0406_SENSOR_FILTER_SW_1:

            if( bit_neo_filter_1_reed == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                mu16Data = 1;
            }

            break;

        case WIFI_PART_0407_SENSOR_FILTER_SW_2:

            if( bit_ino_filter_3_reed == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                mu16Data = 1;
            }

            break;

        case WIFI_PART_0408_SENSOR_FILTER_SW_3:

            if( bit_ro_filter_2_reed == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                mu16Data = 1;
            }

            break;

        case WIFI_PART_0409_SENSOR_TANK_REED:

            if( F_Tank_Cover_Input == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                mu16Data = 1;
            }

            break;

        case WIFI_PART_040C_SENSOR_BLUE_E_FLOW:

            mu16Data = U16_RO_DRAIN_FLOW_SENSOR_PART_040C;
            initial_each_self_data( SENSOR_18__RO_DRAIN_FLOW_SENSOR );

            break;

        case WIFI_PART_0412_SENSOR_CLEANING_SW:

            if( bit_acid_reed == SET )
            {
                /*..hui [21-9-9오후 8:31:16] 정상..*/
                /*..hui [24-7-17오후 6:52:59] 닫힘..*/
                /*mu16Data = 0;*/
                /*..hui [24-7-17오후 6:54:35] 장착.. 감지되면 에러임..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [21-9-9오후 8:31:30] 에러..*/
                /*..hui [24-7-17오후 6:53:02] 열림..*/
                /*mu16Data = 1;*/
                /*..hui [24-7-17오후 6:55:08] 분리.. 정상..*/
                mu16Data = 0;
            }

            break;


        case WIFI_PART_0503_STER_UV_ICE_TANK1:

            mu16Data = U16_UV_ICE_TANK_1_2_Back_DC_Current_PART_0503;
            initial_each_self_data( DC_LOAD_19__UV_ICE_TANK_1_2_BACK );

            break;

        case WIFI_PART_0504_STER_UV_ICE_TRAY:

            mu16Data = U16_UV_ICE_TRAY_1_2_DC_Current_PART_0504;
            initial_each_self_data( DC_LOAD_20__UV_ICE_TRAY_1_2 );

            break;

        case WIFI_PART_0505_STER_UV_COLD_TANK:

            mu16Data = U16_UV_COLD_TANK_1_2_DC_Current_PART_0505;
            initial_each_self_data( DC_LOAD_21__UV_COLD_TANK_1_2 );

            break;

        // case WIFI_PART_0506_STER_UV_ICE_TRAY2:

        //     mu16Data = U16_UV_ICE_TANK_3_Front_DC_Current_PART_0506;
        //     initial_each_self_data( DC_LOAD_22__UV_ICE_TANK_3_FRONT );

        //     break;

        case WIFI_PART_0508_STER_UV_ICE_TANK2:  // 얼음탱크 (#2) 앞

            mu16Data = U16_UV_ICE_TANK_3_Front_DC_Current_PART_0506;
            initial_each_self_data( DC_LOAD_22__UV_ICE_TANK_3_FRONT );

            break;

        case WIFI_PART_0509_STER_UV_ERROR_E74:

            mu16Data = GetUserSystemError(WIFI_ERROR_0034_UV_COLD_TANK);

        break;

        case WIFI_PART_050B_STER_UV_ERROR_E75:

            mu16Data = GetUserSystemError(WIFI_ERROR_0035_UV_ICE_TANK1);

        break;

        case WIFI_PART_050C_STER_UV_ERROR_E79:

            /*mu16Data = GetUserSystemError(WIFI_ERROR_0036_UV_ICE_TANK2);*/
            mu16Data = GetUserSystemError(WIFI_ERROR_0045_UV_ICE_TANK3);

        break;

        case WIFI_PART_050D_STER_UV_ERROR_E76:

            mu16Data = GetUserSystemError(WIFI_ERROR_0037_UV_ICE_TRAY);

        break;

        case WIFI_PART_0600_TDS_TEMP_IN:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            // if( Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 == SET )
            // {
            //     mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            // }
            // else
            // {
            //     mu16Data = gu8_TDS_In_Temperature_One_Degree;
            // }
            mu16Data = 0U;

            break;

        case WIFI_PART_0601_TDS_TEMP_OUT:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            // if( Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 == SET )
            // {
            //     mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            // }
            // else
            // {
            //     mu16Data = gu8_TDS_Out_Temperature_One_Degree;
            // }
            mu16Data = 0U;

            break;

        case WIFI_PART_0602_TDS_SENSOR_IN:

            /*..hui [21-8-25오후 4:46:57] 우선 가장 최근 측정된 TDS IN 값 보내주는걸로..ppm임..*/
            // mu16Data = gu16_recent_tds_in_data;
            /*..hui [21-8-26오전 9:20:02] 에러상태로 일단 변경..*/
            ///mu16Data = Bit2_No_Display_Tds_In_Data_Error__E92;
            mu16Data = 0U;
            break;

        case WIFI_PART_0603_TDS_SENSOR_OUT:

            /*..hui [21-8-25오후 4:47:10] 마찬가지... 프로토콜은 ad로 되어있음 변경해야 함..*/
            // mu16Data = gu16_recent_tds_out_data;
            /*..hui [21-8-26오전 9:20:02] 에러상태로 일단 변경..*/
            //mu16Data = Bit3_No_Display_Tds_Out_Data_Error__E93;
            mu16Data = 0U;
            break;

        case WIFI_PART_0604_TDS_CLEARANCE:  // 0, 1

            /*..hui [24-7-18오전 9:34:37] 제거율 %가 아닌 에러 상태..*/
            // mu16Data = Bit5_No_Display_Tds_Remove_Error__E99;
            // mu16Data = GetUserSystemError(WIFI_ERROR_0030_TDS_REMOVE);
            mu16Data = 0U;
            break;

        case WIFI_PART_0605_TDS_IN_ERROR_E92:
            // mu16Data = GetUserSystemError(WIFI_ERROR_0011_TDSIN_SENSOR);
            mu16Data = 0U;
            break;

        case WIFI_PART_0606_TDS_OUT_ERROR_E93:
            // mu16Data = GetUserSystemError(WIFI_ERROR_0012_TDSOUT_SENSOR);
            mu16Data = 0U;
            break;

        case WIFI_PART_0607_TDS_IN_WATER_E98:       // E98
            // mu16Data = GetUserSystemError(WIFI_ERROR_0047_TDS_IN_WATER);
            mu16Data = 0U;
            break;

        case WIFI_PART_0800_ICE_PURE_TEMP:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( Bit2_Room_Temp_Open_Short_Error__E42 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Room_Temperature_One_Degree;
            }

            break;

        case WIFI_PART_0801_ICE_FULL_SENSOR:

            mu16Data = U16_ICE_FULL_SENSOR_PART_0801;

            break;

        case WIFI_PART_0802_ICE_SWING_BAR:

            mu16Data = U16_SWING_BAR_DC_Current_PART_0802;
            initial_each_self_data( DC_LOAD_23__SWING_BAR );

            break;

        case WIFI_PART_0805_ICE_TRAY_SENSING_SW:

            if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET )
            {
                mu16Data = 3;
            }
            else if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET )
            {
                mu16Data = 1;
            }
            else if( Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
            {
                mu16Data = 2;
            }
            else
            {
                mu16Data = 0;
            }

            break;

        case WIFI_PART_0807_ICE_DOOR_STEPMOTOR:

            mu16Data = U16_ICE_DOOR_MOTOR_DC_Current_PART_0807;
            initial_each_self_data( DC_LOAD_24__ICE_DOOR_MOTOR );

            break;

        case WIFI_PART_0808_ICE_COURSE_CHANGE_VV:

            mu16Data = U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808;
            initial_each_self_data( DC_LOAD_25__GAS_SWITCH_MOTOR );

            break;

        case WIFI_PART_080A_ICE_DRAIN_PUMP:

            mu16Data = U16_DRAIN_PUMP_DC_Current_PART_080A;
            initial_each_self_data( DC_LOAD_26__DRAIN_PUMP );

            break;

        case WIFI_PART_080B_ICE_TRAY_PUMP:

            mu16Data = U16_ICE_TRAY_PUMP_DC_Current_PART_080B;
            initial_each_self_data( DC_LOAD_27__ICE_TRAY_PUMP );

            break;

        case WIFI_PART_080E_ICE_DRAIN_ERROR_E60:
            mu16Data = GetUserSystemError(WIFI_ERROR_000E_DRAIN_PUMP);

            break;
        case WIFI_PART_080F_ICE_TRAY_ERROR_E61:
            mu16Data = GetUserSystemError(WIFI_ERROR_0021_MICRO_SW_DETECT);

            break;
        case WIFI_PART_0810_ICE_TRAY_ERROR_E62:
            mu16Data = GetUserSystemError(WIFI_ERROR_0022_MICRO_SW_MOVE);

            break;
        case WIFI_PART_0811_ICE_TRAY_ERROR_E63:
            mu16Data = GetUserSystemError(WIFI_ERROR_003B_MICRO_SW_MOVE2);

            break;

        case WIFI_PART_0900_EXTRACT_TEMP:

            /*..hui [21-9-17오후 1:18:06] 온도센서 에러일경우 130으로 보내기로 함..*/
            if( bit_Mixing_Out_Temp_Open_Short_Error__E52 == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Mixing_Out_Temperature_One_Degree;
            }

            break;

        default:
            mu16Data = 0xFFFF;
            break;
    }


    return mu16Data;
}


U32 GetUserSystemAccumulate ( U16 mu16Acc )
{
    U32 mu32Data = 0U;

    return mu32Data;
}



/* App Control -> User Function Data */     //  ?????? ?????????
void SetUserSystemFunction ( U16 mu16Func, U16 mData )
{
    switch ( mu16Func )
    {
        case WIFI_FUNC_0003_HOT_LOCK_SEL :

            wifi_hot_lock( mData );

        break;

        // case WIFI_FUNC_0004_SAVE_SEL:

        // break;

        case WIFI_FUNC_0005_LOCK_SEL:

            wifi_all_lock( mData );

        break;

        //case WIFI_FUNC_0006_MUTE_SEL:

            /*wifi_mute( mData );*/

        //break;

        case WIFI_FUNC_0008_ICE_SEL:

            wifi_ice_first( mData );

        break;

        case WIFI_FUNC_0031_VOICE_SEL:

            wifi_voice( mData );

        break;

        case WIFI_FUNC_0032_ICELOCK_SEL:

            wifi_ice_lock( mData );

        break;

        case WIFI_FUNC_0033_VOICE_VOL_SEL:

            wifi_volume( mData );

        break;

        case WIFI_FUNC_0039_HOT_SEL:

            wifi_hot_enable( mData );

        break;

        case WIFI_FUNC_003D_HEIGHT_SEL:

            wifi_altitude( mData );

        break;

        case WIFI_FUNC_0040_SMART_CHECK_RQST :

            //////////////////////////
            /*..hui [21-8-25오후 5:43:05] 스마트 진단.. 0 - 중지, 1 - 시작..*/
            wifi_self_test( mData );

        break;

        case WIFI_FUNC_0049_OUT_BUTTON_LIGHT:

            wifi_welcome_light( mData );

        break;

        case WIFI_FUNC_0059_ICE_ONOFF_SEL:

            wifi_ice_enable( mData );

        break;

        case WIFI_FUNC_005C_SMART_CHECK_RESULT :
            // No modification required. It is used for public use.
            // Modification required if voice IC.
            WifiSmartCheckResultData = (U8)mData;

            if (WifiSmartCheckResultData == CLEAR)
            {
                SetWifiBuzzSound(WIFI_BUZZER_SMART_CHECK_OK); // OK
            }
            else
            {
                SetWifiBuzzSound(WIFI_BUZZER_SMART_CHECK_ERROR); // NG
            }

        break;

        case WIFI_FUNC_005E_SLEEP_MODE_SEL :

            wifi_sleep_mode_enable( mData );

        break;

        case WIFI_FUNC_005F_SLEEP_START_HOUR :

            wifi_sleep_start_hour( mData );

        break;

        case WIFI_FUNC_0060_SLEEP_START_MIN :

            wifi_sleep_start_minute( mData );

        break;

        case WIFI_FUNC_0061_SLEEP_END_HOUR :

            wifi_sleep_finish_hour( mData );

        break;

        case WIFI_FUNC_0062_SLEEP_END_MIN :

            wifi_sleep_finish_minute( mData );

        break;

        case WIFI_FUNC_0065_DEFAULT_TEMP_SEL :

            wifi_hot_default_temp( mData );

        break;

        case WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL :

            wifi_default_cup( mData );

        break;

        case WIFI_FUNC_0067_WATER_QUANTITY_USE_SEL0 :

            wifi_4_oz_water_using( mData );

        break;

        case WIFI_FUNC_0068_WATER_QUANTITY_USE_SEL1:

            wifi_6_oz_water_using( mData );

        break;

        case WIFI_FUNC_0069_WATER_QUANTITY_USE_SEL2:

            wifi_8_oz_water_using( mData );

        break;

        case WIFI_FUNC_006A_WATER_QUANTITY_USE_SEL3 :

            wifi_10_oz_water_using( mData );

        break;

        case WIFI_FUNC_006B_WATER_QUANTITY_USE_SEL4 :

            wifi_12_oz_water_using( mData );

        break;

        case WIFI_FUNC_006C_WATER_QUANTITY_USE_SEL5:

            wifi_14_oz_water_using( mData );

        break;

        case WIFI_FUNC_006D_WATER_QUANTITY_USE_SEL6:

            wifi_16_oz_water_using( mData );

        break;

        case WIFI_FUNC_006E_WATER_QUANTITY_USE_SEL7 :

            wifi_20_oz_water_using( mData );

        break;

        #if 0
        case WIFI_FUNC_006F_WATER_QUANTITY_USE_SEL8 :

            /*wifi_32_oz_water_using( mData );*/

        break;
        #endif

        case WIFI_FUNC_0070_WATER_QUANTITY_USE_SEL9 :

            /*..hui [23-11-16오전 9:24:52] 연속도 디폴트로..*/
            /*wifi_continue_water_using( mData );*/

        break;

        case WIFI_FUNC_0072_WATER_QUANTITY_SORT_SEL :

            wifi_cup_level_order( mData );

        break;

        case WIFI_FUNC_0073_WATER_TEMP_SORT_SEL :

            wifi_hot_temp_level_order( mData );

        break;

        // case WIFI_FUNC_0074_UNUSE_POWER_SAVING_SEL :

        // break;

        case WIFI_FUNC_0075_TEMP_UNIT_SEL :

            wifi_oF_oC_select( mData );

        break;

        case WIFI_FUNC_0076_WATER_QUANTITY_UNIT_SEL:

            wifi_Oz_mL_select( mData );

        break;

        case WIFI_FUNC_0080_HIGH_TEMP_STL_TIME:

            wifi_period_ster_hour( mData );

        break;

        case WIFI_FUNC_0081_HIGH_TEMP_STL_TIME_M:

            wifi_period_ster_minute( mData );

        break;

        case WIFI_FUNC_00A2_CHILD_LOCK :

            wifi_child_lock( mData );

        break;

        /*..hui [23-8-30오전 10:31:47] 테스트용? 나중에 확인..*/
        case WIFI_FUNC_00AA_SMART_SAVING_SET_TIME :

            wifi_unused_setting_time( mData );

        break;

        case WIFI_FUNC_00B6_VOICE_LANGUAGE :

            wifi_voice_language( mData );

        break;

        case WIFI_FUNC_00B7_FILTER_SEQ :

            wifi_filter_change_type( mData );

        break;

        case WIFI_FUNC_00D1_ALTITUDE_AUTO :

        break;

        default:
        break;
    }
}

U16 GetFilterDayData (U16 mu16Data)
{
    U32 work = 0;
    U16 mu16Datareturn = 0;
    work = (U16)GetUserSystemFunction(mu16Data);
    if (work <= 720U)
    {
        work = (U32)(work)*1000U;
        work = (U32)(work/24U);
        if ((work)%1000U > 0)
        {
            mu16Datareturn = (U16)(work/1000U)+1U;
        }
        else
        {
            mu16Datareturn = (U16)(work/1000U);
        }
    }
    else
    {
        mu16Datareturn = 65535U;
    }
    return mu16Datareturn;
}

I16 GetFilterData (U16 mu16SensorDataFilter, U16 mu16FilterTotalUsage)
{
    U32 work = 0;
    U16 mu16Filter_WaterUsageLiter = 0U;
    U16 mu16Filter_WaterUsagePercent = 0U;
    I16 mi16Data = 0;

    mu16Filter_WaterUsageLiter = (U16)GetUserSystemFunction(mu16SensorDataFilter);
    if (mu16Filter_WaterUsageLiter >= mu16FilterTotalUsage)
    {
        mu16Filter_WaterUsageLiter = mu16FilterTotalUsage;
    }
    work = (U32)((mu16FilterTotalUsage)-(mu16FilterTotalUsage - mu16Filter_WaterUsageLiter)) * 10000U;
    work = (U32)(work / mu16FilterTotalUsage);
    mu16Filter_WaterUsagePercent = (U16)(work/100U);
    // if ((work % 100U) > 0U )
    // {
    //  mu16Filter_WaterUsagePercent = (U16)(work/100U)+1U;
    // }
    // else
    // {
    //  mu16Filter_WaterUsagePercent = (U16)(work/100U);
    // }
    mi16Data = (I16)mu16Filter_WaterUsagePercent;

    return mi16Data;
}

U32 GetUserSystemRamMonitor ( U16 mu16Func, U16 mLen )
{
    U32 mu32Data = 0U;
    __near U8 *mPRamAddress_read; // 1byte
    U16 mu16temp_2byte_value = 0U;
    U32 mu32temp_4byte_value = 0U;

    if ((mu16Func > Z_rammax) || (mu16Func < Z_rammin))
    { // RAM ?? ??
        return mu32Data;
    }

    if ((mLen == 0) && (mLen > 4))
    {
        return mu32Data;
    }
    mPRamAddress_read = (__near U8*)mu16Func;
    mu32Data = *mPRamAddress_read;

    if (mLen > 1)
    {
        mPRamAddress_read++;
        mu16temp_2byte_value = *mPRamAddress_read;
        mu32Data += (U16)((mu16temp_2byte_value & 0x00FF) << 8);

    }
    if (mLen > 2)
    {
        mPRamAddress_read++;
        mu32temp_4byte_value = *mPRamAddress_read;
        mPRamAddress_read++;
        mu16temp_2byte_value = *mPRamAddress_read;
        mu32temp_4byte_value += (U16)((mu16temp_2byte_value & 0x00FF) << 8);
        mu32Data += (U32)((mu32temp_4byte_value & 0x0000FFFF) << 16);
    }
    return mu32Data;
}

void  SetUserSystemRamMonitor (__near U16 mu16address, I8 *mData )
{
    __near U8 *mPRamAddress;
    U16 mLen = 0U;
    U16 mRWMode = 0U;
    U32 mRamWriteData_4byte = 0U;
    U32 mRamWriteData_4byte_buf = 0U;
    U8 mi = 0U;
    U8 mDec = 0U;
    U32 mDEC_Positional_Number = 1U;

    mLen = WIFI_ASCII2HEX(mData[0]) & 0x000F;
    mRWMode = WIFI_ASCII2HEX(mData[1]) & 0x000F;

    if ((mu16address > Z_rammax) || (mu16address < Z_rammin)){
        return;
    }
    if (mRWMode != Write)
    {
        return;
    }
    for (mi=0; mi<(mData[LENGTH_WIFI_RAM_DATA-1]-1); mi++)
    {
        mDEC_Positional_Number *= 10;
    }
    for (mi=0; mi<mData[LENGTH_WIFI_RAM_DATA-1]; mi++)
    {
        mDec = (U8)((mData[2+mi])-0x30);
        mRamWriteData_4byte += mDec * (mDEC_Positional_Number);
        mDEC_Positional_Number /= 10;
    }

    mPRamAddress = (__near U8*)mu16address;
    mRamWriteData_4byte_buf = mRamWriteData_4byte;
    for (mi = 0; mi < mLen; mi++)
    {
        *mPRamAddress = (U8)(mRamWriteData_4byte_buf & 0x000000FF);
        mRamWriteData_4byte_buf = mRamWriteData_4byte_buf  >> 8;
        mPRamAddress++;
    }

    SetUserSystemRamWriteStatus((U16)mu16address);
}

#endif


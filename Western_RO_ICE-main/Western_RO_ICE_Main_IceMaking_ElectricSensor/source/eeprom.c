/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Input.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Eeprom.h"

void EEPROM_PRIMARY(void);
void eeprom_data_load(void);
void load_spetial_setting(void);
void load_ice_setting(void);
void load_function_setting(void);
void load_etc_setting(void);
void load_memento(void);
void load_iot_function(void);
void load_wifi(void);
void load_water_usage(void);
void load_debug_data(void);

void eeprom_initial(void);
void initial_spetial_setting(void);
void initial_ice_setting(void);
void initial_function_setting(void);
void initial_etc_setting(void);
void initial_memento(void);
void initial_iot_function(void);
void initial_wifi(void);
void initial_water_usage(void);
void initial_debug_data(void);

void eeprom_test(void);
void eeprom_write_cycle_time(void);
void EepromByteWrite( U16 mu16Addr, U8 mu8Data );
void EepromPageWrite(U16 mu16Addr, U8 *pData, U8 mu8len );
void EepromPageWriteSub( U16 mu16Addr, U8 *pData, U8 mu8len );
void EepromSeqRead( U16 mu16Addr, U8 *pData, U8 mu16Length );





bit bit_eeprom_err;


U8 gu8_eeprom_wbuf[16];
U8 gu8_eeprom_rbuf[16];

U8 u811111;
U16 gu16_eep_cnt;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void EEPROM_PRIMARY(void)
{
    U8 mu8_eep_checkA = 0;
    U8 mu8_eep_checkB = 0;
/***********************************************************************************************************************/
    EepromSeqRead(EEPROM_ADDR_CHECK_START, &mu8_eep_checkA, 1);
/***********************************************************************************************************************/
    EepromSeqRead(EEPROM_ADDR_CHECK_END, &mu8_eep_checkB, 1);
/***********************************************************************************************************************/
    if((mu8_eep_checkA != EEPROM_CHECK_A_VALUE) || (mu8_eep_checkB != EEPROM_CHECK_B_VALUE))
    {
        eeprom_initial();
    }
    else
    {
        eeprom_data_load();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eeprom_data_load(void)
{
    U8 mu8_Read_Buffer[16];

    load_spetial_setting();
    load_ice_setting();
    load_function_setting();
    load_etc_setting();
    load_memento();
    load_iot_function();

    /*..hui [21-7-15오후 1:04:57] wifi 데이터 불러오는것도 이쪽으로..*/
    load_wifi();

    load_water_usage();

    load_debug_data();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_spetial_setting(void)
{
    EepromSeqRead(SPECIAL_SETTING_START_ADDR, gu8_eeprom_rbuf, SPECIAL_SETTING_LENGTH);

    //=========================================================================================//
    /*.. 냉수 사용 설정..*/
    #if 0
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        F_Cold_Enable = gu8_eeprom_rbuf[0];
    }
    else
    {
        F_Cold_Enable = SET;
        EepromByteWrite(EEPROM_ADDR1_COLD_SETTING, (U8)F_Cold_Enable);
    }
    #endif
    //=========================================================================================//
    /*.. 온수 잠금 설정..*/
    if(gu8_eeprom_rbuf[1] <= 1)
    {
        F_Hot_Lock = gu8_eeprom_rbuf[1];
    }
    else
    {
        F_Hot_Lock = CLEAR;
        EepromByteWrite(EEPROM_ADDR1_HOT_LOCK, (U8)F_Hot_Lock);
    }
    //=========================================================================================//
    /*.. 전체 잠금 설정..*/
    if(gu8_eeprom_rbuf[2] <= 1)
    {
        F_All_Lock = gu8_eeprom_rbuf[2];
    }
    else
    {
        F_All_Lock = CLEAR;
        EepromByteWrite(EEPROM_ADDR1_ALL_LOCK, (U8)F_All_Lock);
    }
    //=========================================================================================//
    /*.. 음소거 모드..*/
    if(gu8_eeprom_rbuf[3] <= 1)
    {
        F_Mute_Enable = gu8_eeprom_rbuf[3];
    }
    else
    {
        F_Mute_Enable = CLEAR;
        EepromByteWrite(EEPROM_ADDR1_MUTE_SETTING, (U8)F_Mute_Enable);
    }
    //=========================================================================================//
    /*..hui [20-1-6오후 7:54:35] 냉수 온도 설정..*/
    if(gu8_eeprom_rbuf[4] <= COLD_TEMP_LOW)
    {
        gu8_cold_setting_level = gu8_eeprom_rbuf[4];
    }
    else
    {
        gu8_cold_setting_level = COLD_TEMP_HIGH;
        EepromByteWrite(EEPROM_ADDR1_COLD_LEVEL, (U8)gu8_cold_setting_level);
    }
    //=========================================================================================//
    /*..hui [23-2-8오후 4:25:29] 온수 ON/OFF..*/
    if(gu8_eeprom_rbuf[5] <= 1)
    {
        F_Hot_Enable = gu8_eeprom_rbuf[5];
    }
    else
    {
        F_Hot_Enable = SET;
        EepromByteWrite(EEPROM_ADDR1_HOT_ENABLE, (U8)F_Hot_Enable);
    }
    //=========================================================================================//
    /*..hui [21-5-28오후 4:38:50] 설치 플러싱 상태..*/
    if(gu8_eeprom_rbuf[6] <= 1)
    {
        bit_install_flushing_state = gu8_eeprom_rbuf[6];
    }
    else
    {
        bit_install_flushing_state = SET;
        EepromByteWrite(EEPROM_ADDR1_INSTALL_FLUSHING, (U8)bit_install_flushing_state);
    }

    //=========================================================================================//
    /*..hui [23-6-1오후 7:06:03] 필터 플러싱 상태..*/
    if(gu8_eeprom_rbuf[7] <= FILTER_FLUSHING_RO)
    {
        gu8_filter_flushing_state = gu8_eeprom_rbuf[7];
    }
    else
    {
        gu8_filter_flushing_state = FILTER_FLUSHING_NONE;
        EepromByteWrite(EEPROM_ADDR1_FILTER_FLUSHING, (U8)gu8_filter_flushing_state);
    }

    //=========================================================================================//
    /*..hui [23-6-29오후 2:37:57] 최초 설정 시간 상태..*/
    if(gu8_eeprom_rbuf[8] <= 1)
    {
        bit_first_time_setting = gu8_eeprom_rbuf[8];
    }
    else
    {
        bit_first_time_setting = CLEAR;
        EepromByteWrite(EEPROM_ADDR1_FIRST_TIME_SETTING, (U8)bit_first_time_setting);
    }

    //=========================================================================================//
    /*.. 음성IC..*/
    if(gu8_eeprom_rbuf[9] <= SOUND_TYPE_MUTE )
    {
        gu8Sound_Type = gu8_eeprom_rbuf[9];
    }
    else
    {
        gu8Sound_Type = SOUND_TYPE_VOICE;
        EepromByteWrite(EEPROM_ADDR1_SOUND_TYPE, gu8Sound_Type);
    }

    //=========================================================================================//
    /*..hui [21-5-12오후 1:52:30] 음성 볼륨..*/
    if(gu8_eeprom_rbuf[10] <= SOUND_VOLUME_LEVEL_5)
    {
        gu8VoiceVolumeLevel = gu8_eeprom_rbuf[10];
    }
    else
    {
        /*gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_2;*/
        gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_3;
        EepromByteWrite(EEPROM_ADDR1_VOICE_VOLUME, gu8VoiceVolumeLevel);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[11] <= ALTITUDE_4_MODE_VERY_LOW)
    {
        gu8AltitudeStep = gu8_eeprom_rbuf[11];
    }
    else
    {
        gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;
        EepromByteWrite(EEPROM_ADDR1_ALTITUDE, gu8AltitudeStep);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[12] <= LANGUAGE_MAX)
    {
        gu8_voice_language_type = gu8_eeprom_rbuf[12];
    }
    else
    {
        gu8_voice_language_type = LANGUAGE_TYPE_ENGLISH;
        EepromByteWrite(EEPROM_ADDR1_LANGUAGE_TYPE, gu8AltitudeStep);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[13] <= 1)
    {
        gu8_ct_forced_flushing_start = gu8_eeprom_rbuf[13];
    }
    else
    {
        gu8_ct_forced_flushing_start = CLEAR;
        EepromByteWrite(EEPROM_ADDR1_CT_FORCED_FLUSHING, gu8_ct_forced_flushing_start);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[14] <= ALL_NEO_INO_RO_FILTER_CHANGE)
    {
        gu8CTFilterReplace = gu8_eeprom_rbuf[14];
    }
    else
    {
        gu8CTFilterReplace = 0;
        EepromByteWrite(EEPROM_ADDR1_CT_REPLACE_FILTER, gu8CTFilterReplace);
    }

    //=========================================================================================//

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_ice_setting(void)
{
    EepromSeqRead(ICE_SETTING_START_ADDR, gu8_eeprom_rbuf, ICE_SETTING_LENGTH);

    //=========================================================================================//
    /*.. 얼음 잠금..*/
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        F_Ice_Lock = gu8_eeprom_rbuf[0];
    }
    else
    {
        F_Ice_Lock = CLEAR;
        EepromByteWrite(EEPROM_ADDR2_ICE_LOCK, (U8)F_Ice_Lock);
    }

    //=========================================================================================//
    /*.. 얼음 켜짐..*/
    if(gu8_eeprom_rbuf[1] <= 1)
    {
        F_IceOn = gu8_eeprom_rbuf[1];
    }
    else
    {
        F_IceOn = SET;
        EepromByteWrite(EEPROM_ADDR2_ICE_ON_OFF, (U8)F_IceOn);
    }
    //=========================================================================================//
    /*..hui [18-2-21오후 8:05:32] 냉수/얼음 우선순위 설정 모드 추가..*/
    if(gu8_eeprom_rbuf[2] <= ICE_FIRST_ICE_MAKE)
    {
        bit_fast_ice_make = gu8_eeprom_rbuf[2];
    }
    else
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        EepromByteWrite(EEPROM_ADDR2_ICE_MAKE_PRIORITY, (U8)bit_fast_ice_make);
    }
    //=========================================================================================//
    /*..hui [24-4-11오후 7:11:04] 얼음우선 원래대로 돌리는거 추가..*/
    if(gu8_eeprom_rbuf[3] <= RECOVER_FAST_ICE)
    {
        gu8_recover_org_fast_ice = gu8_eeprom_rbuf[3];
    }
    else
    {
        gu8_recover_org_fast_ice = NEW_FAST_ICE;
        EepromByteWrite(EEPROM_ADDR2_RECOVER_FAST_ICE, gu8_recover_org_fast_ice);
    }
    //=========================================================================================//
    /*..hui [24-7-26오후 3:09:08] 구연산 정전보상..*/
    if(gu8_eeprom_rbuf[4] <= 14)
    {
        gu8_return_acid_step = gu8_eeprom_rbuf[4];
    }
    else
    {
        gu8_return_acid_step = 0;
        EepromByteWrite(EEPROM_ADDR2_ACID_CLEAN, gu8_return_acid_step);
    }


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_function_setting(void)
{
    EepromSeqRead(FUNCTION_SETTING_START_ADDR, gu8_eeprom_rbuf, FUNCTION_SETTING_LENGTH);

    //=========================================================================================//
    /*.. 야간 절전 설정..*/
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        F_Save = gu8_eeprom_rbuf[0];
    }
    else
    {
        F_Save = SET;
        EepromByteWrite(EEPROM_ADDR3_OWER_SAVE_SETTING, (U8)F_Save);
    }

    //=========================================================================================//
    /*.. 순환 배수 설정..*/
    /*..hui [20-3-26오후 8:22:15] 순환배수 설정 복원..*/
    /*..hui [20-3-26오후 8:22:20] 혹시나 나중에 필요할수있으니..*/
    if(gu8_eeprom_rbuf[1] <= 1)
    {
        F_Circul_Drain = gu8_eeprom_rbuf[1];
    }
    else
    {
        F_Circul_Drain = SET;
        EepromByteWrite(EEPROM_ADDR3_CIRCULATION_DRAIN, (U8)F_Circul_Drain);
    }
    //=========================================================================================//
    /*..hui [19-9-24오전 10:00:06] UV 자동 살균 설정..*/
    if(gu8_eeprom_rbuf[2] <= 1)
    {
        F_Auto_UV_Control = gu8_eeprom_rbuf[2];
    }
    else
    {
        F_Auto_UV_Control = SET;
        EepromByteWrite(EEPROM_ADDR3_AUTO_UV_CONTROL, (U8)F_Auto_UV_Control);
    }
    //=========================================================================================//
    /*..hui [19-9-24오전 10:01:12] 얼음,물추출 LED ONOFF설정..*/
    if(gu8_eeprom_rbuf[3] <= 1)
    {
        F_Extract_Led_OnOff = gu8_eeprom_rbuf[3];
    }
    else
    {
        F_Extract_Led_OnOff = SET;
        EepromByteWrite(EEPROM_ADDR3_EXTRACT_LED_ONOFF, (U8)F_Extract_Led_OnOff);
    }
    //=========================================================================================//
    /*..hui [23-9-4오전 11:46:29] 최소시간은 1시간으로..*/
    if( gu8_eeprom_rbuf[4] >= USE_SAVE_LEARNEND_MODE_MIN_TIME
        && gu8_eeprom_rbuf[4] <= USE_SAVE_LEARNEND_MODE_MAX_TIME )
    {
        gu8_wifi_smart_unused_setting_time = gu8_eeprom_rbuf[4];
    }
    else
    {
        gu8_wifi_smart_unused_setting_time = USE_SAVE_LEARNEND_MODE_TIME;
        EepromByteWrite(EEPROM_ADDR3_SMART_UNUSED_TIME, gu8_wifi_smart_unused_setting_time);
    }
    //=========================================================================================//
    #if 0
    gu16_my_cup_level = (U16)((gu8_eeprom_rbuf[5] * 256) + gu8_eeprom_rbuf[6]);

    /*..hui [23-2-8오후 4:28:55] 나중에 다시..*/
    if( gu16_my_cup_level <= 10 || gu16_my_cup_level >= 1000 )
    {
        gu16_my_cup_level = 100;
        gu8_eeprom_wbuf[0] = (U8)(gu16_my_cup_level / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level % (U16)256);
        EepromPageWrite(EEPROM_ADDR3_MY_CUP_LEVEL, gu8_eeprom_wbuf, 2);
    }
    else{}
    #endif
    //=========================================================================================//
    if(gu8_eeprom_rbuf[7] <= 1)
    {
        bit_periodic_ster_enable = gu8_eeprom_rbuf[7];
    }
    else
    {
        bit_periodic_ster_enable = SET;
        EepromByteWrite(EEPROM_ADDR3_STEAM_OFF, (U8)bit_periodic_ster_enable);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[8] <= 23)
    {
        gu8_wifi_period_ster_hour = gu8_eeprom_rbuf[8];
    }
    else
    {
        gu8_wifi_period_ster_hour = WIFI_PERIOD_STER_HOUR_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_PERIOD_STER_HOUR, gu8_wifi_period_ster_hour);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[9] <= 59)
    {
        gu8_wifi_period_ster_minute = gu8_eeprom_rbuf[9];
    }
    else
    {
        gu8_wifi_period_ster_minute = WIFI_PERIOD_STER_MINUTE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_PERIOD_STER_MINUTE, gu8_wifi_period_ster_minute);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[10] <= 1)
    {
        bit_sleep_mode_enable = gu8_eeprom_rbuf[10];
    }
    else
    {
        /*..hui [23-6-29오후 2:24:16] 취침모드 디폴트는 OFF..*/
        bit_sleep_mode_enable = CLEAR;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_MODE_ENABLE, (U8)bit_sleep_mode_enable);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[11] <= 23)
    {
        gu8_sleep_mode_start_hour = gu8_eeprom_rbuf[11];
    }
    else
    {
        gu8_sleep_mode_start_hour = WIFI_SLEEP_MODE_START_HOUR_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_START_HOUR, gu8_sleep_mode_start_hour);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[12] <= 59)
    {
        gu8_sleep_mode_start_minute = gu8_eeprom_rbuf[12];
    }
    else
    {
        gu8_sleep_mode_start_minute = WIFI_SLEEP_MODE_START_MINUTE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_START_MINUTE, gu8_sleep_mode_start_minute);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[13] <= 23)
    {
        gu8_sleep_mode_finish_hour = gu8_eeprom_rbuf[13];
    }
    else
    {
        gu8_sleep_mode_finish_hour = WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_FINISH_HOUR, gu8_sleep_mode_finish_hour);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[14] <= 59)
    {
        gu8_sleep_mode_finish_minute = gu8_eeprom_rbuf[14];
    }
    else
    {
        gu8_sleep_mode_finish_minute = WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_FINISH_MINUTE, gu8_wifi_period_ster_minute);
    }
    //=========================================================================================//




}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_etc_setting(void)
{
    EepromSeqRead(ETC_SAVE_START_ADDR, gu8_eeprom_rbuf, ETC_SAVE_LENGTH);

    //=========================================================================================//
    /*.. 컵레벨 디폴트 설정..*/
    /*if(gu8_eeprom_rbuf[0] <= CUP_LEVEL__20_OZ__590_ML)*/
    /*if(gu8_eeprom_rbuf[0] <= CUP_LEVEL__32_OZ__945_ML)*/
    if(gu8_eeprom_rbuf[0] <= CUP_LEVEL__MAX)
    {
        gu8Cup_level_Default = gu8_eeprom_rbuf[0];
        gu8Cup_level = gu8Cup_level_Default;
    }
    else
    {
        gu8Cup_level_Default = CUP_LEVEL__4_OZ__120_ML;
        gu8Cup_level = gu8Cup_level_Default;
        EepromByteWrite(EEPROM_ADDR4_CUP_LEVEL, gu8Cup_level_Default);
    }
    //=========================================================================================//
    /*..hui [18-1-10오전 11:06:40] 정수/냉수 선택 상태..*/
    if(gu8_eeprom_rbuf[1] <= HOT_WATER_SELECT)
    {
        u8WaterOutState = gu8_eeprom_rbuf[1];
    }
    else
    {
        u8WaterOutState = PURE_WATER_SELECT;
        EepromByteWrite(EEPROM_ADDR4_WATER_SELECT_DEFAULT, u8WaterOutState);
    }

    //=========================================================================================//
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_memento(void)
{
    EepromSeqRead(MEMENTO_START_ADDR, gu8_eeprom_rbuf, MEMENTO_LENGTH);

    //=========================================================================================//
    /*.. 메멘토 01..*/
    if(gu8_eeprom_rbuf[0] <= MAX_ERROR)
    {
        u8Memento_Buff[0] = gu8_eeprom_rbuf[0];
    }
    else
    {
        u8Memento_Buff[0] = 0;
        EepromByteWrite(EEPROM_ADDR5_MEMENTO_NUM0, u8Memento_Buff[0]);
    }
//=========================================================================================//
    /*.. 메멘토 02..*/
    if(gu8_eeprom_rbuf[1] <= MAX_ERROR)
    {
        u8Memento_Buff[1] = gu8_eeprom_rbuf[1];
    }
    else
    {
        u8Memento_Buff[1] = 0;
        EepromByteWrite(EEPROM_ADDR5_MEMENTO_NUM1, u8Memento_Buff[1]);
    }
//=========================================================================================//
    /*.. 메멘토 03..*/
    if(gu8_eeprom_rbuf[2] <= MAX_ERROR)
    {
        u8Memento_Buff[2] = gu8_eeprom_rbuf[2];
    }
    else
    {
        u8Memento_Buff[2] = 0;
        EepromByteWrite(EEPROM_ADDR5_MEMENTO_NUM2, u8Memento_Buff[2]);
    }

//=========================================================================================//
    /*.. 메멘토 04..*/
    if(gu8_eeprom_rbuf[3] <= MAX_ERROR)
    {
        u8Memento_Buff[3] = gu8_eeprom_rbuf[3];
    }
    else
    {
        u8Memento_Buff[3] = 0;
        EepromByteWrite(EEPROM_ADDR5_MEMENTO_NUM3, u8Memento_Buff[3]);
    }

//=========================================================================================//
    /*.. 메멘토 05..*/
    if(gu8_eeprom_rbuf[4] <= MAX_ERROR)
    {
        u8Memento_Buff[4] = gu8_eeprom_rbuf[4];
    }
    else
    {
        u8Memento_Buff[4] = 0;
        EepromByteWrite(EEPROM_ADDR5_MEMENTO_NUM4, u8Memento_Buff[4]);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_iot_function(void)
{
    EepromSeqRead(IOT_FUNCTION_ADDR, gu8_eeprom_rbuf, IOT_FUNCTION_LENGTH);

    //=========================================================================================//
    u16CupLevelSelect = (U16)((gu8_eeprom_rbuf[0] * 256) + gu8_eeprom_rbuf[1]);

    /*if( u16CupLevelSelect < 1 || u16CupLevelSelect > 496 )*/
    /*if( u16CupLevelSelect < 1 || u16CupLevelSelect > 992 )*/
    /*..hui [23-10-4오후 3:52:46] 최대값으로 설정.. 나중에 갯수 변경됐을때 오류 방지..*/
    /*if( u16CupLevelSelect < 1 || u16CupLevelSelect > 1023 )*/
    /*..hui [23-11-23오전 10:20:13] 연속이 디폴트 선택으로 변경됨..*/
    if( u16CupLevelSelect < 512 || u16CupLevelSelect > 1023 )
    {
        u16CupLevelSelect = CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE;
        gu8_eeprom_wbuf[0] = (U8)(u16CupLevelSelect / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(u16CupLevelSelect % (U16)256);
        EepromPageWrite(EEPROM_ADDR6_CUP_LEVEL_SELECT, gu8_eeprom_wbuf, 2);
    }
    else{}


    //=========================================================================================//
    if(gu8_eeprom_rbuf[2] <= CUP_LEVEL_ORDER__DOWN)
    {
        gu8_cup_level_order = gu8_eeprom_rbuf[2];
    }
    else
    {
        gu8_cup_level_order = CUP_LEVEL_ORDER__UP;
        EepromByteWrite(EEPROM_ADDR6_CUP_LEVEL_ORDER, gu8_cup_level_order);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[3] <= Celsius_oC_SELECT)
    {
        gu8_oF__oC_select = gu8_eeprom_rbuf[3];
    }
    else
    {
        gu8_oF__oC_select = Fahrenheit_oF_SELECT;
        EepromByteWrite(EEPROM_ADDR6_OC_OF_SELECT, gu8_oF__oC_select);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[4] <= mL_SELECT)
    {
        gu8_ml__oz_select = gu8_eeprom_rbuf[4];
    }
    else
    {
        gu8_ml__oz_select = Oz_SELECT;
        EepromByteWrite(EEPROM_ADDR6_OZ_ML_SELECT, gu8_ml__oz_select);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[5] <= HOT_TEMP_LEVEL_ORDER__DOWN)
    {
        gu8_hot_level_order = gu8_eeprom_rbuf[5];
    }
    else
    {
        /*gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__UP;*/
        /*..hui [24-1-9오후 3:43:03] 온수온도 디폴트는 내림차순으로.. 디자인..*/
        gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__DOWN;
        EepromByteWrite(EEPROM_ADDR6_HOT_TEMP_LEVEL_ORDER, gu8_hot_level_order);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[6] <= HOT_SET_TEMP_1__110_oF_43_oC)
    {
        gu8_hot_default_temp = gu8_eeprom_rbuf[6];
    }
    else
    {
        /*gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;*/
        /*..hui [23-6-28오전 10:44:24] 95도 디폴트로 변경..*/
        gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
        EepromByteWrite(EEPROM_ADDR6_HOT_TEMP_DEFAULT, gu8_hot_default_temp);
    }
    //=========================================================================================//
    #if 0
    gu16_total_usage_water_gal_save = (U16)((gu8_eeprom_rbuf[7] * 256) + gu8_eeprom_rbuf[8]);
    u16_display_usage_water_gal = gu16_total_usage_water_gal_save;
    gu32_total_usage_water_ml = (U32)((U32)gu16_total_usage_water_gal_save * (U32)ML_PER_GAL);

    if( gu16_total_usage_water_gal_save > MAX_GAL )
    {
        gu16_total_usage_water_gal_save = 0;
        u16_display_usage_water_gal = 0;
        gu32_total_usage_water_ml = 0;
        gu8_eeprom_wbuf[0] = (U8)(gu16_total_usage_water_gal_save / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(gu16_total_usage_water_gal_save % (U16)256);
        EepromPageWrite(EEPROM_ADDR6_WATER_USAGE_GAL, gu8_eeprom_wbuf, 2);
    }
    else{}
    #endif

    //=========================================================================================//
    #if 0
    gu16_filter_reset_day_neo = (U16)((gu8_eeprom_rbuf[9] * 256) + gu8_eeprom_rbuf[10]);

    if( gu16_filter_reset_day_neo > FILTER_RESET_DAY__NEO_INO )
    {
        gu16_filter_reset_day_neo = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR6_FILTER_RESET_DAY_NEO, gu8_eeprom_wbuf, 2);
    }
    else{}
    #endif
    //=========================================================================================//
    #if 0
    gu16_filter_reset_day_ro = (U16)((gu8_eeprom_rbuf[11] * 256) + gu8_eeprom_rbuf[12]);

    if( gu16_filter_reset_day_ro > FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO )
    {
        gu16_filter_reset_day_ro = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR6_FILTER_RESET_DAY_RO, gu8_eeprom_wbuf, 2);
    }
    else{}
    #endif
    //=========================================================================================//
    if(gu8_eeprom_rbuf[13] <= 1)
    {
        bit_child_lock_enable = gu8_eeprom_rbuf[13];
    }
    else
    {
        bit_child_lock_enable = CLEAR;
        EepromByteWrite(EEPROM_ADDR6_CHILD_LOCK_ENABLE, (U8)bit_child_lock_enable);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[14] <= 1)
    {
        gu8_fota_start = gu8_eeprom_rbuf[14];
    }
    else
    {
        gu8_fota_start = CLEAR;
        EepromByteWrite(EEPROM_ADDR6_FOTA_START, gu8_fota_start);
    }
    //=========================================================================================//
    if( gu8_eeprom_rbuf[15] >= WIFI_FILTER_CHANGE_CYCLE_MIN && gu8_eeprom_rbuf[15] <= WIFI_FILTER_CHANGE_CYCLE_MAX )
    {
        gu8_wifi_filter_cycle_percent = gu8_eeprom_rbuf[15];
    }
    else
    {
        gu8_wifi_filter_cycle_percent = WIFI_FILTER_CHANGE_CYCLE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR6_FILTER_CHANGE_CYCLE, gu8_wifi_filter_cycle_percent);
    }
    //=========================================================================================//





}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_wifi(void)
{
    EepromSeqRead(WIFI_DATA_ADDR, gu8_eeprom_rbuf, WIFI_DATA_LENGTH);

    //=========================================================================================//
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        F_Wifi_Power = gu8_eeprom_rbuf[0];
    }
    else
    {
        F_Wifi_Power = CLEAR;
        EepromByteWrite(EEPROM_ADDR_WIFI_POWER, (U8)F_Wifi_Power);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[1] <= 1)
    {
        F_Wifi_First_Paring = gu8_eeprom_rbuf[1];
    }
    else
    {
        F_Wifi_First_Paring = CLEAR;
        EepromByteWrite(EEPROM_ADDR_FIRST_PARING, (U8)F_Wifi_First_Paring);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[2] <= 1)
    {
        F_Wifi_Fota_MODULE = gu8_eeprom_rbuf[2];
    }
    else
    {
        F_Wifi_Fota_MODULE = CLEAR;
        EepromByteWrite(EEPROM_ADDR_FOTA_MODULE, (U8)F_Wifi_Fota_MODULE);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[3] <= 1)
    {
        F_Wifi_Fota_MCU = gu8_eeprom_rbuf[3];
    }
    else
    {
        F_Wifi_Fota_MCU = CLEAR;
        EepromByteWrite(EEPROM_ADDR_FOTA_MCU, (U8)F_Wifi_Fota_MCU);
    }

    //=========================================================================================//
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_water_usage(void)
{
    U32 mu32_a = 0;
    U32 mu32_b = 0;

    EepromSeqRead(WATER_USAGE_ADDR, gu8_eeprom_rbuf, WATER_USAGE_LENGTH);

    //=========================================================================================//
    gu16_water_usage_neo_filter = (U16)((gu8_eeprom_rbuf[0] * 256) + gu8_eeprom_rbuf[1]);

    if( gu16_water_usage_neo_filter > NEO_TOTAL_USAGE_MAX_WATER )
    {
        gu16_water_usage_neo_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_WATER_USAGE__NEO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    gu16_water_usage_ro_filter = (U16)((gu8_eeprom_rbuf[2] * 256) + gu8_eeprom_rbuf[3]);

    if( gu16_water_usage_ro_filter > RO_TOTAL_USAGE_MAX_WATER )
    {
        gu16_water_usage_ro_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_WATER_USAGE__RO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    gu16_water_usage_ino_filter = (U16)((gu8_eeprom_rbuf[4] * 256) + gu8_eeprom_rbuf[5]);

    if( gu16_water_usage_ino_filter > INO_TOTAL_USAGE_MAX_WATER )
    {
        gu16_water_usage_ino_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_WATER_USAGE__INO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    gu16_reset_hour_neo_filter = (U16)((gu8_eeprom_rbuf[6] * 256) + gu8_eeprom_rbuf[7]);

    /*if( gu16_reset_hour_neo_filter > FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO )*/
    if( gu16_reset_hour_neo_filter > FILTER_RESET_MAX_HOUR__NEO )
    {
        gu16_reset_hour_neo_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_FILTER_RESET_DAY__NEO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    gu16_reset_hour_ro_filter = (U16)((gu8_eeprom_rbuf[8] * 256) + gu8_eeprom_rbuf[9]);

    /*if( gu16_reset_hour_ro_filter > FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO )*/
    if( gu16_reset_hour_ro_filter > FILTER_RESET_MAX_HOUR__RO )
    {
        gu16_reset_hour_ro_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_FILTER_RESET_DAY__RO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    gu16_reset_hour_ino_filter = (U16)((gu8_eeprom_rbuf[10] * 256) + gu8_eeprom_rbuf[11]);

    /*if( gu16_reset_hour_ino_filter > FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO )*/
    if( gu16_reset_hour_ino_filter > FILTER_RESET_MAX_HOUR__INO )
    {
        gu16_reset_hour_ino_filter = 0;
        gu8_eeprom_wbuf[0] = 0;
        gu8_eeprom_wbuf[1] = 0;
        EepromPageWrite(EEPROM_ADDR7_FILTER_RESET_DAY__INO, gu8_eeprom_wbuf, 2);
    }
    else{}

    //=========================================================================================//
    if( gu8_eeprom_rbuf[12] <= FILTER_CHANGE_TYPE__NEO_RO_INO_ALL )
    {
        gu8_filter_change_type = gu8_eeprom_rbuf[12];
    }
    else
    {
        gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;
        EepromByteWrite(EEPROM_ADDR7_FILTER_CHANGE_TYPE, (U8)gu8_filter_change_type);
    }

    //=========================================================================================//
    #if 0
    mu32_a = (U32)(((U32)gu8_eeprom_rbuf[0] * 256) + gu8_eeprom_rbuf[1]);
    mu32_b = (U32)(((U32)gu8_eeprom_rbuf[2] * 256) + gu8_eeprom_rbuf[3]);

    gu32_total_usage_water_ml_save = (U32)((mu32_a * 65536) + mu32_b);

    gu32_total_usage_water_ml = gu32_total_usage_water_ml_save;
    gu16_wifi_total_usage_water = (U16)(gu32_total_usage_water_ml / 1000);

    /*..hui [23-6-7오후 5:32:58] 1이면 0.1gal..*/
    u16_display_usage_water_gal = (U16)(gu32_total_usage_water_ml / ML_PER_GAL);

    if( u16_display_usage_water_gal >= MAX_GAL )
    {
        u16_display_usage_water_gal = MAX_GAL;
    }
    else{}
    #endif
    //=========================================================================================//
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_debug_data(void)
{
    EepromSeqRead(DEBUG_DATA_ADDR, gu8_eeprom_rbuf, DEBUG_DATA_LENGTH);

    //=========================================================================================//
    if(gu8_eeprom_rbuf[0] <= 99)
    {
        gu8_ice_ster_drain_stop_count = gu8_eeprom_rbuf[0];
    }
    else
    {
        gu8_ice_ster_drain_stop_count = 0;
        EepromByteWrite(EEPROM_ADDR8_STER_DRAIN_STOP, gu8_ice_ster_drain_stop_count);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[1] <= 99)
    {
        gu8_ice_ster_low_water_stop_count = gu8_eeprom_rbuf[1];
    }
    else
    {
        gu8_ice_ster_low_water_stop_count = 0;
        EepromByteWrite(EEPROM_ADDR8_STER_LOW_WATER_STOP, gu8_ice_ster_low_water_stop_count);
    }

    //=========================================================================================//
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eeprom_initial(void)
{
    //-----------------------
    /*..                초기화      ..*/
    //-----------------------

    // Check A
    EepromByteWrite(EEPROM_ADDR_CHECK_START,EEPROM_CHECK_A_VALUE);

    initial_spetial_setting();
    initial_ice_setting();
    initial_function_setting();
    initial_etc_setting();
    initial_memento();
    initial_iot_function();
    initial_wifi();
    initial_water_usage();

    initial_debug_data();

    EepromByteWrite(EEPROM_ADDR_CHECK_END,EEPROM_CHECK_B_VALUE);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_spetial_setting(void)
{
    F_Cold_Enable = SET;    /*.. 냉수 사용 설정..*/
    F_Hot_Lock = CLEAR;         /*.. 온수 잠금 설정..*/
    F_All_Lock = CLEAR;    /*.. 전체 잠금 설정..*/
    /*..hui [24-1-5오전 9:15:43] 음소거 모드 미사용..*/
    F_Mute_Enable = CLEAR;  /*..hui [18-1-9오후 7:16:17] 음소거 모드..*/
    /*..hui [20-1-6오후 7:56:30] 냉수 온도 설정..*/
    /*..hui [24-1-5오전 9:15:49] 냉수온도 설정 미사용..*/
    gu8_cold_setting_level = COLD_TEMP_HIGH;
    F_Hot_Enable = SET;

    /*..hui [21-5-28오후 4:41:00] 설치 플러싱 상태..*/
    bit_install_flushing_state = SET;
    gu8_filter_flushing_state = FILTER_FLUSHING_NONE;

    bit_first_time_setting = CLEAR;

    gu8Sound_Type = SOUND_TYPE_VOICE;
    /*gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_2;*/
    gu8VoiceVolumeLevel = SOUND_VOLUME_LEVEL_3;

    gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;

    gu8_voice_language_type = LANGUAGE_TYPE_ENGLISH;
    gu8_ct_forced_flushing_start = CLEAR;
    gu8CTFilterReplace = 0;

    gu8_eeprom_wbuf[0] = (U8)F_Cold_Enable;
    gu8_eeprom_wbuf[1] = (U8)F_Hot_Lock;
    gu8_eeprom_wbuf[2] = (U8)F_All_Lock;
    gu8_eeprom_wbuf[3] = (U8)F_Mute_Enable;
    gu8_eeprom_wbuf[4] = gu8_cold_setting_level;
    gu8_eeprom_wbuf[5] = (U8)F_Hot_Enable;
    gu8_eeprom_wbuf[6] = (U8)bit_install_flushing_state;
    gu8_eeprom_wbuf[7] = gu8_filter_flushing_state;
    gu8_eeprom_wbuf[8] = (U8)bit_first_time_setting;
    gu8_eeprom_wbuf[9] = gu8Sound_Type;
    gu8_eeprom_wbuf[10] = gu8VoiceVolumeLevel;
    gu8_eeprom_wbuf[11] = gu8AltitudeStep;
    gu8_eeprom_wbuf[12] = gu8_voice_language_type;
    gu8_eeprom_wbuf[13] = gu8_ct_forced_flushing_start;
    gu8_eeprom_wbuf[14] = gu8CTFilterReplace;


    EepromPageWrite(SPECIAL_SETTING_START_ADDR, gu8_eeprom_wbuf, SPECIAL_SETTING_LENGTH);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_setting(void)
{
    F_Ice_Lock = CLEAR;          /*.. 얼음 잠금..*/
    F_IceOn = SET;               /*.. 얼음 켜짐..*/
    bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
    gu8_recover_org_fast_ice = NEW_FAST_ICE;
    gu8_return_acid_step = 0;

    gu8_eeprom_wbuf[0] = (U8)F_Ice_Lock;
    gu8_eeprom_wbuf[1] = (U8)F_IceOn;
    gu8_eeprom_wbuf[2] = (U8)bit_fast_ice_make;
    gu8_eeprom_wbuf[3] = gu8_recover_org_fast_ice;
    gu8_eeprom_wbuf[4] = gu8_return_acid_step;

    EepromPageWrite(ICE_SETTING_START_ADDR, gu8_eeprom_wbuf, ICE_SETTING_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_function_setting(void)
{
    F_Save = SET;                /*..야간 절전 설정..*/
    F_Circul_Drain = SET;        /*..순환배수 설정..*/
    F_Auto_UV_Control = SET;     /*..UV 자동살균..*/
    F_Extract_Led_OnOff = SET;   /*..추출 LED ONOFF..*/

    /*bit_my_cup_enable = CLEAR;*/
    /*gu16_my_cup_level = 100;*/
    gu8_wifi_smart_unused_setting_time = USE_SAVE_LEARNEND_MODE_TIME;

    bit_periodic_ster_enable = SET;
    gu8_wifi_period_ster_hour = WIFI_PERIOD_STER_HOUR_DEFAULT;
    gu8_wifi_period_ster_minute = WIFI_PERIOD_STER_MINUTE_DEFAULT;

    /*bit_sleep_mode_enable = SET;*/
    /*..hui [23-6-29오후 2:24:16] 취침모드 디폴트는 OFF..*/
    bit_sleep_mode_enable = CLEAR;
    gu8_sleep_mode_start_hour = WIFI_SLEEP_MODE_START_HOUR_DEFAULT;
    gu8_sleep_mode_start_minute = WIFI_SLEEP_MODE_START_MINUTE_DEFAULT;
    gu8_sleep_mode_finish_hour = WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT;
    gu8_sleep_mode_finish_minute = WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT;

    gu8_eeprom_wbuf[0] = (U8)F_Save;
    gu8_eeprom_wbuf[1] = (U8)F_Circul_Drain;
    gu8_eeprom_wbuf[2] = (U8)F_Auto_UV_Control;
    gu8_eeprom_wbuf[3] = (U8)F_Extract_Led_OnOff;

    gu8_eeprom_wbuf[4] = gu8_wifi_smart_unused_setting_time;
    gu8_eeprom_wbuf[5] = (U8)0;
    gu8_eeprom_wbuf[6] = (U8)0;

    gu8_eeprom_wbuf[7] = (U8)bit_periodic_ster_enable;
    gu8_eeprom_wbuf[8] = gu8_wifi_period_ster_hour;
    gu8_eeprom_wbuf[9] = gu8_wifi_period_ster_minute;

    gu8_eeprom_wbuf[10] = (U8)bit_sleep_mode_enable;
    gu8_eeprom_wbuf[11] = gu8_sleep_mode_start_hour;
    gu8_eeprom_wbuf[12] = gu8_sleep_mode_start_minute;
    gu8_eeprom_wbuf[13] = gu8_sleep_mode_finish_hour;
    gu8_eeprom_wbuf[14] = gu8_sleep_mode_finish_minute;

    EepromPageWrite(FUNCTION_SETTING_START_ADDR, gu8_eeprom_wbuf, FUNCTION_SETTING_LENGTH);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_etc_setting(void)
{
    /*.. cup level default 설정..*/
    gu8Cup_level_Default = CUP_LEVEL__4_OZ__120_ML;
    gu8Cup_level = gu8Cup_level_Default;

    /*..hui [18-1-10오전 11:06:40] 정수/냉수 선택 상태..*/
    u8WaterOutState = PURE_WATER_SELECT;

    gu8_eeprom_wbuf[0] = gu8Cup_level;
    gu8_eeprom_wbuf[1] = u8WaterOutState;

    EepromPageWrite(ETC_SAVE_START_ADDR, gu8_eeprom_wbuf, ETC_SAVE_LENGTH);
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_memento(void)
{
    /*.. 메멘토01..*/
    u8Memento_Buff[0] = 0;

    /*.. 메멘토02..*/
    u8Memento_Buff[1] = 0;

    /*.. 메멘토03..*/
    u8Memento_Buff[2] = 0;

    /*.. 메멘토04..*/
    u8Memento_Buff[3] = 0;

     /*.. 메멘토05..*/
    u8Memento_Buff[4] = 0;

    gu8_eeprom_wbuf[0] = u8Memento_Buff[0];
    gu8_eeprom_wbuf[1] = u8Memento_Buff[1];
    gu8_eeprom_wbuf[2] = u8Memento_Buff[2];
    gu8_eeprom_wbuf[3] = u8Memento_Buff[3];
    gu8_eeprom_wbuf[4] = u8Memento_Buff[4];

    EepromPageWrite(MEMENTO_START_ADDR, gu8_eeprom_wbuf, MEMENTO_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_iot_function(void)
{
    u16CupLevelSelect = CUP_LEVEL_SELECT_DEFAULT_4_8_12_20_CONTINUE;
    gu8_cup_level_order = CUP_LEVEL_ORDER__UP;

    gu8_oF__oC_select = Fahrenheit_oF_SELECT;
    gu8_ml__oz_select = Oz_SELECT;
    /*gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__UP;*/
    /*..hui [24-1-9오후 3:43:03] 온수온도 디폴트는 내림차순으로.. 디자인..*/
    gu8_hot_level_order = HOT_TEMP_LEVEL_ORDER__DOWN;

    /*gu8_hot_default_temp = HOT_SET_TEMP_3__185_oF_85_oC;*/
    /*..hui [23-6-28오전 10:44:24] 95도 디폴트로 변경..*/
    gu8_hot_default_temp = HOT_SET_TEMP_4__200_oF_95_oC;
    /*gu16_total_usage_water_gal_save  = 0;*/
    /*gu16_filter_reset_day_neo = 0;*/
    /*gu16_filter_reset_day_ro = 0;*/

    bit_child_lock_enable = CLEAR;
    gu8_fota_start = CLEAR;
    gu8_wifi_filter_cycle_percent = WIFI_FILTER_CHANGE_CYCLE_DEFAULT;

    gu8_eeprom_wbuf[0] = (U8)(u16CupLevelSelect/(U16)256);
    gu8_eeprom_wbuf[1] = (U8)(u16CupLevelSelect%(U16)256);
    gu8_eeprom_wbuf[2] = (U8)gu8_cup_level_order;
    gu8_eeprom_wbuf[3] = (U8)gu8_oF__oC_select;
    gu8_eeprom_wbuf[4] = (U8)gu8_ml__oz_select;
    gu8_eeprom_wbuf[5] = (U8)gu8_hot_level_order;
    gu8_eeprom_wbuf[6] = (U8)gu8_hot_default_temp;
    /*gu8_eeprom_wbuf[7] = (U8)(gu16_total_usage_water_gal_save/(U16)256);*/
    /*gu8_eeprom_wbuf[8] = (U8)(gu16_total_usage_water_gal_save%(U16)256);*/
    gu8_eeprom_wbuf[7] = (U8)0;
    gu8_eeprom_wbuf[8] = (U8)0;
    /*gu8_eeprom_wbuf[9] = (U8)(gu16_filter_reset_day_neo/(U16)256);*/
    /*gu8_eeprom_wbuf[10] = (U8)(gu16_filter_reset_day_neo%(U16)256);*/
    /*gu8_eeprom_wbuf[11] = (U8)(gu16_filter_reset_day_ro/(U16)256);*/
    /*gu8_eeprom_wbuf[12] = (U8)(gu16_filter_reset_day_ro%(U16)256);*/
    gu8_eeprom_wbuf[9] = (U8)0;
    gu8_eeprom_wbuf[10] = (U8)0;
    gu8_eeprom_wbuf[11] = (U8)0;
    gu8_eeprom_wbuf[12] = (U8)0;
    gu8_eeprom_wbuf[13] = (U8)bit_child_lock_enable;
    gu8_eeprom_wbuf[14] = gu8_fota_start;
    gu8_eeprom_wbuf[15] = gu8_wifi_filter_cycle_percent;

    EepromPageWrite(IOT_FUNCTION_ADDR, gu8_eeprom_wbuf, IOT_FUNCTION_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_wifi(void)
{
    F_Wifi_Power = CLEAR;
    F_Wifi_First_Paring = CLEAR;
    F_Wifi_Fota_MODULE = CLEAR;
    F_Wifi_Fota_MCU = CLEAR;

    gu8_eeprom_wbuf[0] = CLEAR;
    gu8_eeprom_wbuf[1] = CLEAR;
    gu8_eeprom_wbuf[2] = CLEAR;
    gu8_eeprom_wbuf[3] = CLEAR;

    EepromPageWrite(WIFI_DATA_ADDR, gu8_eeprom_wbuf, WIFI_DATA_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_water_usage(void)
{
    #if 0
    gu32_total_usage_water_ml_save = 0;
    gu32_total_usage_water_ml = 0;
    gu16_wifi_total_usage_water = 0;
    u16_display_usage_water_gal = 0;
    #endif

    gu16_water_usage_neo_filter = 0;
    gu16_water_usage_ro_filter = 0;
    gu16_water_usage_ino_filter = 0;

    gu16_reset_hour_neo_filter = 0;
    gu16_reset_hour_ro_filter = 0;
    gu16_reset_hour_ino_filter = 0;

    gu16_temporary_save_usage = 0;

    gu8_filter_change_type = FILTER_CHANGE_TYPE__NEO_INO;

    gu8_eeprom_wbuf[0] = (U8)(gu16_water_usage_neo_filter/(U16)256);
    gu8_eeprom_wbuf[1] = (U8)(gu16_water_usage_neo_filter%(U16)256);

    gu8_eeprom_wbuf[2] = (U8)(gu16_water_usage_ro_filter/(U16)256);
    gu8_eeprom_wbuf[3] = (U8)(gu16_water_usage_ro_filter%(U16)256);

    gu8_eeprom_wbuf[4] = (U8)(gu16_water_usage_ino_filter/(U16)256);
    gu8_eeprom_wbuf[5] = (U8)(gu16_water_usage_ino_filter%(U16)256);

    gu8_eeprom_wbuf[6] = (U8)(gu16_reset_hour_neo_filter/(U16)256);
    gu8_eeprom_wbuf[7] = (U8)(gu16_reset_hour_neo_filter%(U16)256);

    gu8_eeprom_wbuf[8] = (U8)(gu16_reset_hour_ro_filter/(U16)256);
    gu8_eeprom_wbuf[9] = (U8)(gu16_reset_hour_ro_filter%(U16)256);

    gu8_eeprom_wbuf[10] = (U8)(gu16_reset_hour_ino_filter/(U16)256);
    gu8_eeprom_wbuf[11] = (U8)(gu16_reset_hour_ino_filter%(U16)256);

    gu8_eeprom_wbuf[12] = gu8_filter_change_type;

    EepromPageWrite(WATER_USAGE_ADDR, gu8_eeprom_wbuf, WATER_USAGE_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_debug_data(void)
{
    gu8_ice_ster_drain_stop_count = 0;
    gu8_ice_ster_low_water_stop_count = 0;

    gu8_eeprom_wbuf[0] = gu8_ice_ster_drain_stop_count;
    gu8_eeprom_wbuf[1] = gu8_ice_ster_low_water_stop_count;

    EepromPageWrite(DEBUG_DATA_ADDR, gu8_eeprom_wbuf, DEBUG_DATA_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eeprom_test(void)
{
    U8 mu8EEPROM_ReadDataBuffer = 0;

    if(u811111 == SET)
    {
        return;
    }
    else
    {
        u811111 = SET;
    }

    EepromSeqRead(EEPROM_ADDR_TEST, gu8_eeprom_rbuf, 1);

    if(gu8_eeprom_rbuf[0] == EEPROM_CHECK_A_VALUE)
    {
        EepromByteWrite(EEPROM_ADDR_TEST, EEPROM_CHECK_B_VALUE);

        EepromSeqRead(EEPROM_ADDR_TEST, gu8_eeprom_rbuf, 1);

        if(gu8_eeprom_rbuf[0] == EEPROM_CHECK_B_VALUE)
        {
            bit_eeprom_err = CLEAR;
        }
        else
        {
            bit_eeprom_err = 1;
        }
    }
    else
    {
        EepromByteWrite(EEPROM_ADDR_TEST, EEPROM_CHECK_A_VALUE);

        EepromSeqRead(EEPROM_ADDR_TEST, gu8_eeprom_rbuf, 1);

        if(gu8_eeprom_rbuf[0] == EEPROM_CHECK_A_VALUE)
        {
            bit_eeprom_err = CLEAR;
        }
        else
        {
            bit_eeprom_err = 1;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eeprom_write_cycle_time(void)
{
    U16 mu16temp = 0;

    /*..hui [17-12-8오후 1:16:26] 약 5.3ms..*/
    /*..hui [19-10-21오후 1:25:35] 약 16ms, typical 12ms, max 20ms..*/
    for(mu16temp = 0 ; mu16temp < 13000 ; mu16temp++)
    {
       NOP(); NOP(); NOP(); NOP(); NOP();
       NOP(); NOP(); NOP(); NOP(); NOP();
       NOP(); NOP(); NOP(); NOP(); NOP();
       NOP(); NOP(); NOP(); NOP(); NOP();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void EepromByteWrite( U16 mu16Addr, U8 mu8Data )
{
    U8 mu8_temp = 0;

    #if 0
    mu8_temp = IsRtcBatBackUpMode();

    if( mu8_temp == TRUE )
    {
        return;
    }
    else{}
    #endif

    HAL_RTC_ByteWrite( DEV_ADDR_EEP, mu16Addr, mu8Data);

    gu16_eep_cnt++;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void EepromPageWrite(U16 mu16Addr, U8 *pData, U8 mu8len )
{
    U8 i = 0;
    U8 mu8PageNum = 0;

    EepromPageWriteSub( mu16Addr, pData, mu8len );

    gu16_eep_cnt++;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void EepromPageWriteSub( U16 mu16Addr, U8 *pData, U8 mu8len )
{
    U8 mu8_temp = 0;

    #if 0
    mu8_temp = IsRtcBatBackUpMode();

    if( mu8_temp == TRUE )
    {
        return;
    }
    else{}
    #endif

    HAL_RTC_PageWrite( DEV_ADDR_EEP, mu16Addr, pData, mu8len);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void EepromSeqRead( U16 mu16Addr, U8 *pData, U8 mu16Length )
{
    U8 mu8_temp = 0;

    #if 0
    mu8_temp = IsRtcBatBackUpMode();

    if( mu8_temp == TRUE )
    {
        return;
    }
    else{}
    #endif

    HAL_RTC_SeqRead( DEV_ADDR_EEP, mu16Addr, pData, mu16Length );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




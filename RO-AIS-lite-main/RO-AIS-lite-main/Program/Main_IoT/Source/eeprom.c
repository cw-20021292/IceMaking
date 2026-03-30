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
#include	"WIFI_UserCommon.h"

void EEPROM_PRIMARY(void);
void eeprom_data_load(void);
void load_spetial_setting(void);
void load_ice_setting(void);
void load_function_setting(void);
void load_etc_setting(void);
void load_memento(void);
void load_my_cup(void);
void load_wifi(void);
void load_iot_function(void);

void eeprom_initial(void);
void initial_spetial_setting(void);
void initial_ice_setting(void);
void initial_function_setting(void);
void initial_etc_setting(void);
void initial_memento(void);
void initial_my_cup(void);
U8 eeprom_test(void);
void eeprom_write_cycle_time(void);
void EepromByteWrite( U16 mu16Addr, U8 mu8Data );
void EepromPageWrite(U16 mu16Addr, U8 *pData, U8 mu8len );
void EepromPageWriteSub( U16 mu16Addr, U8 *pData, U8 mu8len );
void EepromSeqRead( U16 mu16Addr, U8 *pData, U8 mu16Length );

void initial_wifi(void);
void initial_iot_function(void);



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
    load_my_cup();

    load_iot_function();

	load_wifi();
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
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        F_Cold_Enable = gu8_eeprom_rbuf[0];
    }
    else
    {
        F_Cold_Enable = SET;
        EepromByteWrite(EEPROM_ADDR1_COLD_SETTING, (U8)F_Cold_Enable);
    }
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
    if(gu8_eeprom_rbuf[6] <= ALTITUDE_3_MODE_LOW)
    {
        gu8AltitudeStep = gu8_eeprom_rbuf[6];
    }
    else
    {
        gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;
        EepromByteWrite(EEPROM_ADDR1_ALTITUDE, gu8AltitudeStep);
    }
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
    #if 0
    /*..hui [18-2-21오후 8:05:32] 냉수/얼음 우선순위 설정 모드 추가..*/
    if(gu8_eeprom_rbuf[3] <= ICE_SETTING_COLD_FIRST)
    {
        gu8_ice_setting = gu8_eeprom_rbuf[3];
    }
    else
    {
        gu8_ice_setting = ICE_SETTING_COLD_FIRST;
        EepromByteWrite(EEPROM_ADDR2_ICE_TOTAL_SETTING, gu8_ice_setting);
    }
    #endif
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
        //F_Save = gu8_eeprom_rbuf[0];
        bit_sleep_mode_enable = gu8_eeprom_rbuf[10];
    }
    else
    {
        /*..hui [23-6-29오후 2:24:16] 취침모드 디폴트는 OFF..*/
        bit_sleep_mode_enable = CLEAR;
        EepromByteWrite(EEPROM_ADDR3_OWER_SAVE_SETTING, (U8)bit_sleep_mode_enable);
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
    if(gu8_eeprom_rbuf[4] <= 1)
    {
        bit_temporary_no_operation = gu8_eeprom_rbuf[4];
    }
    else
    {
        bit_temporary_no_operation = CLEAR;
        EepromByteWrite(EEPROM_ADDR3_NO_USE_SAVE, (U8)bit_temporary_no_operation);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[5] <= 1)
    {
        bit_sleep_mode_enable = gu8_eeprom_rbuf[5];
    }
    else
    {
        /*..hui [23-6-29오후 2:24:16] 취침모드 디폴트는 OFF..*/
        bit_sleep_mode_enable = CLEAR;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_MODE_ENABLE, (U8)bit_sleep_mode_enable);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[6] <= 23)
    {
        gu8_sleep_mode_start_hour = gu8_eeprom_rbuf[6];
    }
    else
    {
        gu8_sleep_mode_start_hour = WIFI_SLEEP_MODE_START_HOUR_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_START_HOUR, gu8_sleep_mode_start_hour);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[7] <= 59)
    {
        gu8_sleep_mode_start_minute = gu8_eeprom_rbuf[7];
    }
    else
    {
        gu8_sleep_mode_start_minute = WIFI_SLEEP_MODE_START_MINUTE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_START_MINUTE, gu8_sleep_mode_start_minute);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[8] <= 23)
    {
        gu8_sleep_mode_finish_hour = gu8_eeprom_rbuf[8];
    }
    else
    {
        gu8_sleep_mode_finish_hour = WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_FINISH_HOUR, gu8_sleep_mode_finish_hour);
    }
    //=========================================================================================//
    if(gu8_eeprom_rbuf[9] <= 59)
    {
        gu8_sleep_mode_finish_minute = gu8_eeprom_rbuf[9];
    }
    else
    {
        gu8_sleep_mode_finish_minute = WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT;
        EepromByteWrite(EEPROM_ADDR3_SLEEP_FINISH_MINUTE, gu8_sleep_mode_finish_minute);
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
    /*if(gu8_eeprom_rbuf[0] <= CUP_LEVEL_TWO)*/
    if(gu8_eeprom_rbuf[0] <= CUP_LEVEL_MY_CUP)
    {
        gu8Cup_level_Default = gu8_eeprom_rbuf[0];
        gu8Cup_level = gu8Cup_level_Default;
    }
    else
    {
        gu8Cup_level_Default = CUP_LEVEL_HALF;
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
void load_my_cup(void)
{
    EepromSeqRead(MY_CUP_START_ADDR, gu8_eeprom_rbuf, MY_CYP_SETTING_LENGTH);

    //=========================================================================================//
    if(gu8_eeprom_rbuf[0] <= 1)
    {
        bit_my_cup_enable = gu8_eeprom_rbuf[0];
    }
    else
    {
        bit_my_cup_enable = SET;
        EepromByteWrite(EEPROM_ADDR6_MY_CUP_USING, (U8)bit_my_cup_enable);
    }
    //=========================================================================================//
    gu16_my_cup_level_pure = (U16)((gu8_eeprom_rbuf[1] * 256) + gu8_eeprom_rbuf[2]);

    /*..hui [23-2-8오후 4:28:55] 나중에 다시..*/
    if( gu16_my_cup_level_pure < MY_CUP_SETTING_120mL_PURE_MIN || gu16_my_cup_level_pure > MY_CUP_SETTING_800mL_PURE )
    {
        gu16_my_cup_level_pure = MY_CUP_SETTING_120mL_PURE_MIN;
        gu8_eeprom_wbuf[0] = (U8)(gu16_my_cup_level_pure / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level_pure % (U16)256);
        EepromPageWrite(EEPROM_ADDR6_MY_CUP_LEVEL_PURE, gu8_eeprom_wbuf, 2);
    }
    else{}
    //=========================================================================================//
    gu16_my_cup_level_cold = (U16)((gu8_eeprom_rbuf[3] * 256) + gu8_eeprom_rbuf[4]);

    /*..hui [23-2-8오후 4:28:55] 나중에 다시..*/
    if( gu16_my_cup_level_cold < MY_CUP_SETTING_120mL_COLD_MIN || gu16_my_cup_level_cold > MY_CUP_SETTING_800mL_COLD )
    {
        gu16_my_cup_level_cold = MY_CUP_SETTING_120mL_COLD_MIN;
        gu8_eeprom_wbuf[0] = (U8)(gu16_my_cup_level_cold / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level_cold % (U16)256);
        EepromPageWrite(EEPROM_ADDR6_MY_CUP_LEVEL_COLD, gu8_eeprom_wbuf, 2);
    }
    else{}
    //=========================================================================================//
    gu16_my_cup_level_hot = (U16)((gu8_eeprom_rbuf[5] * 256) + gu8_eeprom_rbuf[6]);

    /*..hui [23-2-8오후 4:28:55] 나중에 다시..*/
    if( gu16_my_cup_level_hot < MY_CUP_SETTING_120mL_HOT_MIN || gu16_my_cup_level_hot > MY_CUP_SETTING_800mL_HOT )
    {
        gu16_my_cup_level_hot = MY_CUP_SETTING_120mL_HOT_MIN;
        gu8_eeprom_wbuf[0] = (U8)(gu16_my_cup_level_hot / (U16)256);
        gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level_hot % (U16)256);
        EepromPageWrite(EEPROM_ADDR6_MY_CUP_LEVEL_HOT, gu8_eeprom_wbuf, 2);
    }
    else{}
    //=========================================================================================//








}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eeprom_initial(void)
{
    U8 mu8_eep_checkA = 0;
    U8 mu8_eep_checkB = 0;
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
    initial_my_cup();
	
    initial_wifi();

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
    F_Mute_Enable = CLEAR;  /*..hui [18-1-9오후 7:16:17] 음소거 모드..*/
    /*..hui [20-1-6오후 7:56:30] 냉수 온도 설정..*/
    gu8_cold_setting_level = COLD_TEMP_HIGH;
    F_Hot_Enable = SET;
    gu8AltitudeStep = ALTITUDE_1_MODE_HIGH;

    gu8_eeprom_wbuf[0] = (U8)F_Cold_Enable;
    gu8_eeprom_wbuf[1] = (U8)F_Hot_Lock;
    gu8_eeprom_wbuf[2] = (U8)F_All_Lock;
    gu8_eeprom_wbuf[3] = (U8)F_Mute_Enable;
    gu8_eeprom_wbuf[4] = gu8_cold_setting_level;
    gu8_eeprom_wbuf[5] = (U8)F_Hot_Enable;
    gu8_eeprom_wbuf[6] = gu8AltitudeStep;

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
    /*gu8_ice_setting = ICE_SETTING_COLD_FIRST;*/

    gu8_eeprom_wbuf[0] = (U8)F_Ice_Lock;
    gu8_eeprom_wbuf[1] = (U8)F_IceOn;
    gu8_eeprom_wbuf[2] = (U8)bit_fast_ice_make;
    gu8_eeprom_wbuf[3] = 0;

    EepromPageWrite(ICE_SETTING_START_ADDR, gu8_eeprom_wbuf, ICE_SETTING_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_function_setting(void)
{
    //F_Save = SET;                /*..야간 절전 설정..*/
    bit_sleep_mode_enable = CLEAR;
    F_Circul_Drain = SET;        /*..순환배수 설정..*/
    F_Auto_UV_Control = SET;     /*..UV 자동살균..*/
    F_Extract_Led_OnOff = SET;   /*..추출 LED ONOFF..*/

    gu8_sleep_mode_start_hour = WIFI_SLEEP_MODE_START_HOUR_DEFAULT;
    gu8_sleep_mode_start_minute = WIFI_SLEEP_MODE_START_MINUTE_DEFAULT;
    gu8_sleep_mode_finish_hour = WIFI_SLEEP_MODE_FINISH_HOUR_DEFAULT;
    gu8_sleep_mode_finish_minute = WIFI_SLEEP_MODE_FINISH_MINUTE_DEFAULT;

    /*..hui [23-8-17오후 3:55:16] 미사용절전 모드 저장.. 테스트 및 대비용..*/
    bit_temporary_no_operation = CLEAR;


    //gu8_eeprom_wbuf[0] = (U8)F_Save;
    gu8_eeprom_wbuf[0] = (U8)0;
    gu8_eeprom_wbuf[1] = (U8)F_Circul_Drain;
    gu8_eeprom_wbuf[2] = (U8)F_Auto_UV_Control;
    gu8_eeprom_wbuf[3] = (U8)F_Extract_Led_OnOff;
    gu8_eeprom_wbuf[4] = (U8)bit_temporary_no_operation;

    gu8_eeprom_wbuf[5] = (U8)bit_sleep_mode_enable;
    gu8_eeprom_wbuf[6] = gu8_sleep_mode_start_hour;
    gu8_eeprom_wbuf[7] = gu8_sleep_mode_start_minute;
    gu8_eeprom_wbuf[8] = gu8_sleep_mode_finish_hour;
    gu8_eeprom_wbuf[9] = gu8_sleep_mode_finish_minute;

    EepromPageWrite(FUNCTION_SETTING_START_ADDR, gu8_eeprom_wbuf, FUNCTION_SETTING_LENGTH);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_etc_setting(void)
{
    /*.. cup level default 설정..*/
    gu8Cup_level_Default = CUP_LEVEL_HALF;
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
void initial_my_cup(void)
{
    bit_my_cup_enable = CLEAR;
    gu16_my_cup_level_pure = MY_CUP_SETTING_120mL_PURE_MIN;
    gu16_my_cup_level_cold = MY_CUP_SETTING_120mL_COLD_MIN;
    gu16_my_cup_level_hot = MY_CUP_SETTING_120mL_HOT_MIN;

    gu8_eeprom_wbuf[0] = (U8)bit_my_cup_enable;
    gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level_pure/(U16)256);
    gu8_eeprom_wbuf[2] = (U8)(gu16_my_cup_level_pure%(U16)256);
    gu8_eeprom_wbuf[3] = (U8)(gu16_my_cup_level_cold/(U16)256);
    gu8_eeprom_wbuf[4] = (U8)(gu16_my_cup_level_cold%(U16)256);
    gu8_eeprom_wbuf[5] = (U8)(gu16_my_cup_level_hot/(U16)256);
    gu8_eeprom_wbuf[6] = (U8)(gu16_my_cup_level_hot%(U16)256);

    EepromPageWrite(MY_CUP_START_ADDR, gu8_eeprom_wbuf, MY_CYP_SETTING_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 eeprom_test(void)
{
    U8 mu8EEPROM_ReadDataBuffer = 0;
    U8 mu8ret = 0;

    if(u811111 == SET)
    {
        return mu8ret;
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

    return mu8ret;

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
void initial_iot_function(void)
{

    gu8_fota_start = CLEAR;

    gu8_eeprom_wbuf[0] = gu8Cup_level;
    gu8_eeprom_wbuf[1] = gu8_fota_start;

    EepromPageWrite(IOT_FUNCTION_ADDR, gu8_eeprom_wbuf, IOT_FUNCTION_LENGTH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void load_iot_function(void)
{
    EepromSeqRead(IOT_FUNCTION_ADDR, gu8_eeprom_rbuf, IOT_FUNCTION_LENGTH);

    //=========================================================================================//
#if 0
    /*..hui [23-10-4오후 3:52:46] 최대값으로 설정.. 나중에 갯수 변경됐을때 오류 방지..*/
    if( gu8Cup_level_Default > 0 )
    {
        gu8Cup_level_Default = gu8_eeprom_rbuf[0];
        EepromPageWrite(EEPROM_ADDR6_CUP_LEVEL_SELECT, gu8_eeprom_wbuf, 2);
    }
    else{}
#endif

    //=========================================================================================//
    if(gu8_eeprom_rbuf[1] <= 1)
    {
        gu8_fota_start = gu8_eeprom_rbuf[1];
    }
    else
    {
        gu8_fota_start = CLEAR;
        EepromByteWrite(EEPROM_ADDR6_FOTA_START, gu8_fota_start);
    }
    //=========================================================================================//




}


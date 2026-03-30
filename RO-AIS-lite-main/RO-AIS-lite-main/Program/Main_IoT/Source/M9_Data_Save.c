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
#include    "M9_Data_Save.h"
#include	"WIFI_Config.h"

void Save_Eeprom_Data(void);
void save_special_setting(void);
void save_ice_setting(void);
void save_function_setting(void);
void save_etc_setting(void);
void water_select_state_save(void);
void my_cup_setting(void);

void apply_before_special_setting(void);
void apply_before_ice_setting(void);
void apply_before_function_setting(void);
void apply_before_etc_setting(void);
void apply_before_my_cup_setting(void);
void apply_wifi_data(void);
void init_before_save_data(void);

void wifi_data_save(void);
void save_iot_function(void);
void apply_before_iot_function_setting(void);


bit F_Cold_Enable_Old;
bit F_Hot_Lock_Old;
bit F_All_Lock_Old;
//bit F_Mute_Enable_Old;
bit F_Ice_Lock_Old;
bit F_IceOn_Old;
bit bit_fast_ice_make_old;
bit F_Save_Old;
bit F_Circul_Drain_Old;
bit F_Auto_UV_Control_Old;
U8 gu8_clock_theme_Old;
U8 gu8_screen_bright_Old;
//bit F_Service_1day_Save;

U8 gu8_cup_level_default_old;
U8 gu8_WaterOutState_Old;

U8 gu8_eeprom_data_save_xmit;


bit F_Wifi_Power;
bit F_Wifi_Power_Old;


bit F_Wifi_First_Paring;
bit F_Wifi_First_Paring_Old;

bit F_Extract_Led_OnOff;
bit F_Extract_Led_OnOff_Old;

U8 gu8_ice_setting;
U8 gu8_ice_setting_old;


bit F_Hot_Enable_Old;
bit bit_my_cup_enable_Old;
U16 gu16_my_cup_level_pure_old;
U16 gu16_my_cup_level_cold_old;
U16 gu16_my_cup_level_hot_old;

U8 gu8AltitudeStep_old;

bit bit_temporary_no_operation_old;

bit F_Wifi_Power;
bit F_Wifi_Power_Old;

bit F_Wifi_First_Paring;
bit F_Wifi_First_Paring_Old;

bit F_Wifi_Fota_MODULE;
bit F_Wifi_Fota_MODULE_Old;

bit F_Wifi_Fota_MCU;
bit F_Wifi_Fota_MCU_Old;

bit bit_sleep_mode_enable_old;

U8 gu8_sleep_mode_start_hour_old;
U8 gu8_sleep_mode_start_minute_old;
U8 gu8_sleep_mode_finish_hour_old;
U8 gu8_sleep_mode_finish_minute_old;

bit bit_first_time_setting_old;

U8 gu8_fota_start_old;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Save_Eeprom_Data(void)
{
    switch(gu8_eeprom_data_save_xmit)
    {
        case 0:

            save_special_setting();
            gu8_eeprom_data_save_xmit++;

            break;

        case 1:

            save_ice_setting();
            gu8_eeprom_data_save_xmit++;

            break;

        case 2:

            save_function_setting();
            gu8_eeprom_data_save_xmit++;

            break;

        case 3:

            save_etc_setting();
            gu8_eeprom_data_save_xmit++;

            break;

        case 4:

            ErrorSave();
            gu8_eeprom_data_save_xmit++;

            break;

        case 5:

            my_cup_setting();
            gu8_eeprom_data_save_xmit++;

            break;

        case 6:


            save_iot_function();
            gu8_eeprom_data_save_xmit++;

            break;

        case 7:

            wifi_data_save();
            gu8_eeprom_data_save_xmit++;

            break;

        case 8:

            gu8_eeprom_data_save_xmit++;

            break;

        case 9:

            gu8_eeprom_data_save_xmit++;

            break;

        case 10:

            ProcessRtc();
            gu8_eeprom_data_save_xmit = 0;

            break;

        default:

            gu8_eeprom_data_save_xmit = 0;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_special_setting(void)
{
    U8 mu8_enable = 0;

    if( F_Cold_Enable_Old != F_Cold_Enable
       || F_Hot_Lock_Old != F_Hot_Lock
       || F_All_Lock_Old != F_All_Lock
       || F_Mute_Enable_Old != F_Mute_Enable
       || gu8_cold_setting_level_old != gu8_cold_setting_level
       || F_Hot_Enable_Old != F_Hot_Enable
       || gu8AltitudeStep_old != gu8AltitudeStep )
    {
        mu8_enable = SET;
    }
    else{}

    if(mu8_enable == SET)
    {
        apply_before_special_setting();

        gu8_eeprom_wbuf[0] = (U8)F_Cold_Enable;
        gu8_eeprom_wbuf[1] = (U8)F_Hot_Lock;
        gu8_eeprom_wbuf[2] = (U8)F_All_Lock;
        gu8_eeprom_wbuf[3] = (U8)F_Mute_Enable;
        gu8_eeprom_wbuf[4] = gu8_cold_setting_level;
        gu8_eeprom_wbuf[5] = (U8)F_Hot_Enable;
        gu8_eeprom_wbuf[6] = gu8AltitudeStep;

        EepromPageWrite(SPECIAL_SETTING_START_ADDR, gu8_eeprom_wbuf, SPECIAL_SETTING_LENGTH);
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_ice_setting(void)
{
    U8 mu8_enable = 0;

    /*..hui [20-3-31오후 4:32:27] 얼음생성이랑 얼음우선이 얼음설정 하나로 통합됨.. 꺼짐,얼음,냉수 순....*/
    if( F_Ice_Lock_Old != F_Ice_Lock
       || F_IceOn_Old != F_IceOn
       || bit_fast_ice_make_old != bit_fast_ice_make )
    {
        mu8_enable = SET;
    }
    else{}

    if(mu8_enable == SET)
    {
        apply_before_ice_setting();

        gu8_eeprom_wbuf[0] = (U8)F_Ice_Lock;
        gu8_eeprom_wbuf[1] = (U8)F_IceOn;
        gu8_eeprom_wbuf[2] = (U8)bit_fast_ice_make;

        EepromPageWrite(ICE_SETTING_START_ADDR, gu8_eeprom_wbuf, ICE_SETTING_LENGTH);
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_function_setting(void)
{
    U8 mu8_enable = 0;

    if( /*F_Save_Old != F_Save
       ||*/ F_Circul_Drain_Old != F_Circul_Drain
       || F_Auto_UV_Control_Old != F_Auto_UV_Control
       || F_Extract_Led_OnOff_Old != F_Extract_Led_OnOff
       || bit_temporary_no_operation_old != bit_temporary_no_operation

       || bit_sleep_mode_enable_old != bit_sleep_mode_enable
       || gu8_sleep_mode_start_hour_old != gu8_sleep_mode_start_hour
       || gu8_sleep_mode_start_minute_old != gu8_sleep_mode_start_minute
       || gu8_sleep_mode_finish_hour_old != gu8_sleep_mode_finish_hour
       || gu8_sleep_mode_finish_minute_old != gu8_sleep_mode_finish_minute

	)
    {
        mu8_enable = SET;
    }
    else{}

    if(mu8_enable == SET)
    {
        apply_before_function_setting();

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
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_etc_setting(void)
{

    if( gu8_cup_level_default_old != gu8Cup_level_Default )
    {
        gu8_cup_level_default_old = gu8Cup_level_Default;

        gu8_eeprom_wbuf[0] = (U8)gu8Cup_level_Default;

        EepromPageWrite(ETC_SAVE_START_ADDR, gu8_eeprom_wbuf, 1);
    }
    else{}

    water_select_state_save();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_select_state_save(void)
{
    /*..hui [18-1-10오전 11:15:29] 온수 선택상태이거나 선택 후 복귀 이전이면 저장안함..*/
    if(u8WaterOutState == HOT_WATER_SELECT || F_WaterOut_Change_State == SET)
    {
        return;
    }
    else{}

    if(gu8_WaterOutState_Old != u8WaterOutState)
    {
        gu8_WaterOutState_Old = u8WaterOutState;

        EepromByteWrite(EEPROM_ADDR4_WATER_SELECT_DEFAULT, u8WaterOutState);
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void my_cup_setting(void)
{
    U8 mu8_enable = 0;

    if( bit_my_cup_enable_Old != bit_my_cup_enable
       || gu16_my_cup_level_pure_old != gu16_my_cup_level_pure
       || gu16_my_cup_level_cold_old != gu16_my_cup_level_cold
       || gu16_my_cup_level_hot_old != gu16_my_cup_level_hot )
    {
        mu8_enable = SET;
    }
    else{}

    if(mu8_enable == SET)
    {
        apply_before_my_cup_setting();

        gu8_eeprom_wbuf[0] = (U8)bit_my_cup_enable;
        gu8_eeprom_wbuf[1] = (U8)(gu16_my_cup_level_pure/(U16)256);
        gu8_eeprom_wbuf[2] = (U8)(gu16_my_cup_level_pure%(U16)256);
        gu8_eeprom_wbuf[3] = (U8)(gu16_my_cup_level_cold/(U16)256);
        gu8_eeprom_wbuf[4] = (U8)(gu16_my_cup_level_cold%(U16)256);
        gu8_eeprom_wbuf[5] = (U8)(gu16_my_cup_level_hot/(U16)256);
        gu8_eeprom_wbuf[6] = (U8)(gu16_my_cup_level_hot%(U16)256);

        EepromPageWrite(MY_CUP_START_ADDR, gu8_eeprom_wbuf, MY_CYP_SETTING_LENGTH);
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_special_setting(void)
{
    F_Cold_Enable_Old = F_Cold_Enable;
    F_Hot_Lock_Old = F_Hot_Lock;
    F_All_Lock_Old = F_All_Lock;
    F_Mute_Enable_Old = F_Mute_Enable;
    gu8_cold_setting_level_old = gu8_cold_setting_level;
    F_Hot_Enable_Old = F_Hot_Enable;
    gu8AltitudeStep_old = gu8AltitudeStep;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_ice_setting(void)
{
    F_Ice_Lock_Old = F_Ice_Lock;
    F_IceOn_Old = F_IceOn;
    bit_fast_ice_make_old = bit_fast_ice_make;
    /*gu8_ice_setting_old = gu8_ice_setting;*/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_function_setting(void)
{
    //F_Save_Old = F_Save;
    F_Circul_Drain_Old = F_Circul_Drain;
    F_Auto_UV_Control_Old = F_Auto_UV_Control;
    F_Extract_Led_OnOff_Old = F_Extract_Led_OnOff;
    bit_temporary_no_operation_old = bit_temporary_no_operation;
	
	//sleep mode 추가 
    bit_sleep_mode_enable_old = bit_sleep_mode_enable;
    gu8_sleep_mode_start_hour_old = gu8_sleep_mode_start_hour;
    gu8_sleep_mode_start_minute_old = gu8_sleep_mode_start_minute;
    gu8_sleep_mode_finish_hour_old = gu8_sleep_mode_finish_hour;
    gu8_sleep_mode_finish_minute_old = gu8_sleep_mode_finish_minute;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_etc_setting(void)
{
    gu8_cup_level_default_old = gu8Cup_level_Default;
    gu8_WaterOutState_Old = u8WaterOutState;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_my_cup_setting(void)
{
    bit_my_cup_enable_Old = bit_my_cup_enable;
    gu16_my_cup_level_pure_old = gu16_my_cup_level_pure;
    gu16_my_cup_level_cold_old = gu16_my_cup_level_cold;
    gu16_my_cup_level_hot_old = gu16_my_cup_level_hot;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_before_save_data(void)
{
    apply_before_special_setting();
    apply_before_ice_setting();
    apply_before_function_setting();
    apply_before_etc_setting();
    apply_before_iot_function_setting();

	apply_wifi_data();
    apply_before_my_cup_setting();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_wifi_data(void)
{
    F_Wifi_First_Paring_Old = F_Wifi_First_Paring;
    F_Wifi_Power_Old = F_Wifi_Power;
    F_Wifi_Fota_MODULE_Old = F_Wifi_Fota_MODULE;
    F_Wifi_Fota_MCU_Old = F_Wifi_Fota_MCU;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_data_save(void)
{
    U8 mu8_enable = 0;

    if( F_Wifi_Power != F_Wifi_Power_Old
       || F_Wifi_First_Paring != F_Wifi_First_Paring_Old
       || F_Wifi_Fota_MODULE != F_Wifi_Fota_MODULE_Old
       || F_Wifi_Fota_MCU != F_Wifi_Fota_MCU_Old )
    {
        mu8_enable = SET;
    }
    else
    {
        mu8_enable = CLEAR;
    }

    if(mu8_enable == SET)
    {
        apply_wifi_data();

        gu8_eeprom_wbuf[0] = (U8)F_Wifi_Power;
        gu8_eeprom_wbuf[1] = (U8)F_Wifi_First_Paring;
        gu8_eeprom_wbuf[2] = (U8)F_Wifi_Fota_MODULE;
        gu8_eeprom_wbuf[3] = (U8)F_Wifi_Fota_MCU;

        EepromPageWrite(WIFI_DATA_ADDR, gu8_eeprom_wbuf, WIFI_DATA_LENGTH);
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_iot_function(void)
{
    U8 mu8_enable = 0;

    if( gu8_fota_start_old != gu8_fota_start )
    {
        mu8_enable = SET;
    }
    else{}

    if(mu8_enable == SET)
    {
        apply_before_iot_function_setting();

        
        gu8_eeprom_wbuf[1] = gu8_fota_start;

        EepromPageWrite(IOT_FUNCTION_ADDR, gu8_eeprom_wbuf, IOT_FUNCTION_LENGTH);
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_before_iot_function_setting(void)
{
    gu8_fota_start_old = gu8_fota_start;
}


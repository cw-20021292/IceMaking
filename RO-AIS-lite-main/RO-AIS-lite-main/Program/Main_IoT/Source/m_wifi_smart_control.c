/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "m_wifi_smart_control.h"
#include    "WIFI_Status.h"

void wifi_smart_control(void);
//void get_wifi_info_data(void);
void get_wifi_connect(void);
void get_wifi_pairing(void);
void get_wifi_error(void);
void get_wifi_power(void);
U8 change_error_number( U8 mu8_error );
void get_wifi_filter_period(void);
void change_filter_period(void);
void get_wifi_cert(void);





U8 gu8_wifi_weather;
U8 gu8_wifi_aqi;

S8 gs8_signed_wifi_temperature;
U8 gu8_unsigned_wifi_temperature;

U8 gu8_wifi_temperature;


U8 gu8_Wifi_Connect_State;

U8 gu8_Wifi_Pairing_State;
U8 gu8_Wifi_Pairing_Error;
U8 gu8_Wifi_Last_Error;


U8 gu8_smart_image;
U8 gu8_smart_text;

U8 gu8_ap_mode;



U8 gu8_smart_standby_mode;

U8 gu8_custom_cup_setting;


U8 gu8_wifi_power_temporary;
U8 gu8_wifi_ap_first_temporary;

U8 gu8_wifi_ap_mode;
U8 gu8_ble_ap_mode;

U8 gu8_wifi_disp_timer;

U16 gu16_wifi_pairing_30min_timer;
U8 gu8_wifi_pairing_5sec_timer;
bit bit_pairing_5s_display_start;

U8 gu8_fota_start;


U8 gu8_wifi_filter_cycle_percent;
bit bit_filter_cycle_change;

U16 gu16_define_filter_period__neo;
U16 gu16_define_filter_period__ro;
U16 gu16_define_filter_period__ino;

U16 gu16_test_cycle;

U8 gu8_Wifi_Cert_State;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_smart_control(void)
{
    get_wifi_connect();
    get_wifi_pairing();
    get_wifi_error();
    get_wifi_power();

    //get_wifi_filter_period();
    /*get_wifi_info_data();*/

    get_wifi_cert();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void get_wifi_info_data(void)
{
    U8 mu8_connect_state = 0;
    U8 mu8_data = 0;
    S8 ms8_temp = 0;
    U8 mu8_temp = 0;

    mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_WEATHER );

    #if 0
    if( mu8_data >= SMART_WEATHER_MIN && mu8_data <= SMART_WEATHER_MAX )
    {
        gu8_wifi_weather = mu8_data;
    }
    else{}
    #endif

    mu8_data  = (U8)GetWifiRequestValue( WIFI_RQST_AQI );

    #if 0
    if( mu8_data >= AQI_GOOD && mu8_data <= AQI_VERY_BAD )
    {
        gu8_wifi_aqi = mu8_data;
    }
    else{}
    #endif

    /*..hui [21-3-24오후 3:33:20] AQI 값으로 필터링..*/
    if( mu8_data != 99 )
    {
        mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_CURRENT_TEMP );

        /*..hui [21-3-24오후 3:33:25] 온도값으로 한번 더 필터링..*/
        if( mu8_data != 99 )
        {
            gu8_unsigned_wifi_temperature = mu8_data;

            if( gu8_unsigned_wifi_temperature >= 128 )
            {
                if( gu8_unsigned_wifi_temperature <= MIN_TEMPATURE )
                {
                    gu8_wifi_temperature = MIN_TEMPATURE;
                }
                else
                {
                    gu8_wifi_temperature = gu8_unsigned_wifi_temperature;
                }
            }
            else
            {
                if( gu8_unsigned_wifi_temperature >= MAX_TEMPERATURE )
                {
                    gu8_wifi_temperature = MAX_TEMPERATURE;
                }
                else
                {
                    gu8_wifi_temperature = gu8_unsigned_wifi_temperature;
                }
            }
        }
        else{}
    }
    else{}
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_connect(void)
{
    U8 mu8_connect_state = 0;

    mu8_connect_state = GetWifiStatusValue( WIFI_STATUS_DISP );

    if( mu8_connect_state == WIFI_DISP_OFF )
    {
        gu8_Wifi_Connect_State = WIFI_OFF;
    }
    else if( mu8_connect_state == WIFI_DISP_CONNECT )
    {
        gu8_Wifi_Connect_State = WIFI_CONNECT;
    }
    else
    {
        gu8_Wifi_Connect_State = WIFI_DISCONNECT;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_pairing(void)
{
    U8 mu8_pairing_state = 0;

    mu8_pairing_state = GetWifiStatusValue( WIFI_STATUS_DISP );

    gu8_wifi_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_MODE );
    gu8_ble_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_BLE );
/*
    if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP_FINISH;
        return;
    }
    else{}
*/
    if( gu8_wifi_ap_mode == SET )
    {
        if( mu8_pairing_state == WIFI_DISP_AP_START )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP0 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP0_PREPARE;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP1 )
        {
            /*..hui [23-12-20오후 1:22:03] 점유인증되면 STEP1이 날라옴.. 그때부터 25%로 화면 표시 시작..*/
            if( gu8_Wifi_Pairing_State != WIFI_PAIRING_STEP1_25_PERCENT )
            {
                gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP1_25_PERCENT;

                if( gu8_Wifi_Pairing_Error == 0 )
                {
                    bit_wifi_pairing_start = SET;
                    bit_display_last_error = CLEAR;
                }
                else{}
            }
            else{}

        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP2 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP2_50_PERCENT;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP3 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP3_75_PERCENT;
        }
        else
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
    }
    else if( gu8_ble_ap_mode == SET )
    {
        if( mu8_pairing_state == WIFI_DISP_BLE_START )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP0 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP0_PREPARE;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP1 )
        {
            /*..hui [23-12-20오후 1:22:03] 점유인증되면 STEP1이 날라옴.. 그때부터 25%로 화면 표시 시작..*/
            if( gu8_Wifi_Pairing_State != WIFI_PAIRING_STEP1_25_PERCENT )
            {
                gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP1_25_PERCENT;

                if( gu8_Wifi_Pairing_Error == 0 )
                {
                    bit_wifi_pairing_start = SET;
                    bit_display_last_error = CLEAR;
                }
                else{}
            }
            else{}
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP2 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP2_50_PERCENT;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP3 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP3_75_PERCENT;
        }
        else
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
    }
    else
    {
        gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        bit_wifi_pairing_start = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_error(void)
{
    U8 mu8_error = 0;

    mu8_error = GetWifiStatusValue(WIFI_STATUS_AP_ERROR);

    gu8_Wifi_Pairing_Error = change_error_number( mu8_error );


    mu8_error = GetWifiStatusValue(WIFI_STATUS_ERROR);

    gu8_Wifi_Last_Error = change_error_number( mu8_error );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_power(void)
{
    /*..hui [21-8-2오후 8:23:11] 전원 상태 및 첫 페어링 상태..*/
    /*..hui [21-8-2오후 8:23:24] 설정에서 현민이 쪽에서 가져다 쓰기위해..*/
    gu8_wifi_power_temporary = GetWifiStatusValue(WIFI_STATUS_POWER);

    gu8_wifi_ap_first_temporary = GetWifiApStatus(STATUS_AP_FIRST);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 change_error_number( U8 mu8_error )
{
    U8 mu8_return = 0;

    if( mu8_error == WIFI_DISP_AP1 )
    {
        /*..hui [21-10-5오후 2:10:03] AP1 - 무선공유기 암호불일치..*/
        mu8_return = WIFI_FAIL_PASS__AP1;
    }
    else if( mu8_error == WIFI_DISP_AP2 )
    {
        /*..hui [21-10-5오후 2:10:13] AP2 - 무선공유기 미검색 1분..*/
        mu8_return = WIFI_NO_ACK__AP2;
    }
    else if( mu8_error == WIFI_DISP_AP3 )
    {
        /*..hui [21-10-5오후 2:10:25] AP3 - 무선공유기 접속거부..*/
        mu8_return = WIFI_ERROR_DENY__AP3;
    }
    else if( mu8_error == WIFI_DISP_AP4 )
    {
        /*..hui [21-10-5오후 2:10:33] AP4 - 무선공유기 응답없음..*/
        mu8_return = WIFI_NO_AP__AP4;
    }
    else if( mu8_error == WIFI_DISP_AP5 )
    {
        /*..hui [21-10-5오후 2:10:41] AP5 - 서버 응답없음..*/
        mu8_return = WIFI_NO_SERVER__AP5;
    }
    else
    {
        mu8_return = 0;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_cert(void)
{
    U8 mu8_connect_state = 0;

    gu8_Wifi_Cert_State = GetWifiStatusValue(WIFI_STATUS_BLE_CERT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



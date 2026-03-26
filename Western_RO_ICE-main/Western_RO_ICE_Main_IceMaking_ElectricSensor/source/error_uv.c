/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "error_uv.h"

void check_error_uv(void);
void check_error_uv_water_tank(void);
void check_error_uv_ice_tank_back(void);
void check_error_uv_ice_tank_front(void);
void check_error_uv_ice_tray(void);

U8 gu8_water_tank_uv_error_check_timer;
U8 gu8_water_tank_uv_error_clear_timer;

U8 gu8_ice_tank_uv_error_check_timer;
U8 gu8_ice_tank_uv_error_clear_timer;

U8 gu8_ice_tray_one_uv_error_check_timer;
U8 gu8_ice_tray_one_uv_error_clear_timer;

U8 gu8_ice_tray_two_uv_error_check_timer;
U8 gu8_ice_tray_two_uv_error_clear_timer;

U8 gu8_ice_tank_front_uv_error_check_timer;
U8 gu8_ice_tank_front_uv_error_clear_timer;

U8 gu8_water_tank_uv_retry_cnt;
bit bit_water_tank_uv_retry_stop;

U8 gu8_ice_tank_uv_retry_cnt;
bit bit_ice_tank_uv_retry_stop;

U8 gu8_ice_tray_uv_retry_cnt;
bit bit_ice_tray_uv_retry_stop;


U16 gu16_water_uv_error_elasped_timer_hour;
U16 gu16_water_uv_error_elasped_timer_day;
U8 gu8_water_uv_error_elasped_day;


U8 gu8_ice_tank_front_uv_retry_cnt;
bit bit_ice_tank_front_uv_retry_stop;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv(void)
{
    /*..hui [24-4-3오후 7:53:47] 냉수탱크 UV 2개..*/
    check_error_uv_water_tank();
    /*..hui [24-4-3오후 7:53:59] 얼음탱크 뒤쪽 UV 2개.. 원래 있던거에 1개추가..*/
    check_error_uv_ice_tank_back();
    /*..hui [24-4-3오후 7:54:08] 얼음탱크 앞쪽 UV 1개.. 신규 추가..*/
    check_error_uv_ice_tank_front();
    /*..hui [24-4-3오후 7:54:21] 아이스 트레이 측면 2개.. 분리돼있던거 2개 합침..*/
    check_error_uv_ice_tray();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv_water_tank(void)
{
    if( bit_uv_water_tank_out == SET && bit_water_tank_uv_retry_stop == CLEAR )
    {
        /*..hui [24-4-4오후 3:05:58] 냉수탱크 UV 2개 연결..*/
        if( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            gu8_water_tank_uv_error_clear_timer = 0;
            gu8_water_tank_uv_error_check_timer++;

            if( gu8_water_tank_uv_error_check_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_water_tank_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;

                gu8_water_tank_uv_retry_cnt++;

                if( gu8_water_tank_uv_retry_cnt >= UV_ERROR_RETRY_COUNT )
                {
                    gu8_water_tank_uv_retry_cnt = UV_ERROR_RETRY_COUNT;
                    gu8_water_tank_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;
                    Bit23_Water_Tank_1_2_UV_Error__E74 = SET;
                }
                else
                {
                    gu8_water_tank_uv_error_check_timer = 0;
                    bit_water_tank_uv_retry_stop = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_water_tank_uv_error_check_timer = 0;
            gu8_water_tank_uv_error_clear_timer++;

            if ( gu8_water_tank_uv_error_clear_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_water_tank_uv_error_clear_timer = UV_SENSOR_ERROR_CHECK_TIME;
                Bit23_Water_Tank_1_2_UV_Error__E74 = CLEAR;
                gu8_water_tank_uv_retry_cnt = 0;
                gu8_water_uv_error_elasped_day = 0;
            }
            else{}
        }
    }
    else
    {
        gu8_water_tank_uv_error_clear_timer = 0;
        gu8_water_tank_uv_error_check_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv_ice_tank_back(void)
{
    if( bit_uv_ice_tank_out == SET && bit_ice_tank_uv_retry_stop == CLEAR )
    {
        /*..hui [24-4-4오후 3:06:11] 얼음 탱크 뒤 UV 2개 연결..*/
        if( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            gu8_ice_tank_uv_error_clear_timer = 0;
            gu8_ice_tank_uv_error_check_timer++;

            if( gu8_ice_tank_uv_error_check_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tank_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;

                gu8_ice_tank_uv_retry_cnt++;

                if( gu8_ice_tank_uv_retry_cnt >= UV_ERROR_RETRY_COUNT )
                {
                    gu8_ice_tank_uv_retry_cnt = UV_ERROR_RETRY_COUNT;
                    gu8_ice_tank_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;
                    Bit24_Ice_Tank_1_2_Back_UV_Error__E75 = SET;
                }
                else
                {
                    gu8_ice_tank_uv_error_check_timer = 0;
                    bit_ice_tank_uv_retry_stop = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_ice_tank_uv_error_check_timer = 0;
            gu8_ice_tank_uv_error_clear_timer++;

            if ( gu8_ice_tank_uv_error_clear_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tank_uv_error_clear_timer = UV_SENSOR_ERROR_CHECK_TIME;
                Bit24_Ice_Tank_1_2_Back_UV_Error__E75 = CLEAR;
                gu8_ice_tank_uv_retry_cnt = 0;
            }
            else{}
        }
    }
    else
    {
        gu8_ice_tank_uv_error_clear_timer = 0;
        gu8_ice_tank_uv_error_check_timer = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv_ice_tank_front(void)
{
    if( bit_uv_ice_tank_front_out == SET && bit_ice_tank_front_uv_retry_stop == CLEAR )
    {
        /*..hui [24-4-4오후 3:06:21] 얼음 탱크 앞 UV 1개 연결..*/
        if( gu16_AD_Result_UV_Ice_Tank_3_Front_Current >= UV_SOLO__ERROR_CHECK_OVER_AD
            || gu16_AD_Result_UV_Ice_Tank_3_Front_Current <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            gu8_ice_tank_front_uv_error_clear_timer = 0;
            gu8_ice_tank_front_uv_error_check_timer++;

            if( gu8_ice_tank_front_uv_error_check_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tank_front_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;

                gu8_ice_tank_front_uv_retry_cnt++;

                if( gu8_ice_tank_front_uv_retry_cnt >= UV_ERROR_RETRY_COUNT )
                {
                    gu8_ice_tank_front_uv_retry_cnt = UV_ERROR_RETRY_COUNT;
                    gu8_ice_tank_front_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;
                    Bit26_Ice_Tank_3_Front_UV_Error__E79 = SET;
                }
                else
                {
                    gu8_ice_tank_front_uv_error_check_timer = 0;
                    bit_ice_tank_front_uv_retry_stop = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_ice_tank_front_uv_error_check_timer = 0;
            gu8_ice_tank_front_uv_error_clear_timer++;

            if ( gu8_ice_tank_front_uv_error_clear_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tank_front_uv_error_clear_timer = UV_SENSOR_ERROR_CHECK_TIME;
                Bit26_Ice_Tank_3_Front_UV_Error__E79 = CLEAR;
                gu8_ice_tank_front_uv_retry_cnt = 0;
            }
            else{}
        }
    }
    else
    {
        gu8_ice_tank_front_uv_error_clear_timer = 0;
        gu8_ice_tank_front_uv_error_check_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv_ice_tray(void)
{
    if( bit_uv_ice_tray_out == SET && bit_ice_tray_uv_retry_stop == CLEAR )
    {
        /*..hui [24-4-4오후 3:06:31] 아이스 트레이 UV 2개 연겨..*/
        if( gu16_AD_Result_UV_Ice_Tray_1_2_Current >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Ice_Tray_1_2_Current <= UV_COUPLE__ERROR_CHECK_UNDER_AD  )
            //////|| gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed >= UV_COUPLE__ERROR_CHECK_UNDER_AD
            ///////|| gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            gu8_ice_tray_one_uv_error_clear_timer = 0;
            gu8_ice_tray_one_uv_error_check_timer++;

            if( gu8_ice_tray_one_uv_error_check_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tray_one_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;

                gu8_ice_tray_uv_retry_cnt++;

                if( gu8_ice_tray_uv_retry_cnt >= UV_ERROR_RETRY_COUNT )
                {
                    gu8_ice_tray_uv_retry_cnt = UV_ERROR_RETRY_COUNT;
                    gu8_ice_tray_one_uv_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;
                    Bit25_Ice_Tray_1_2_UV_Error__E76 = SET;
                }
                else
                {
                    gu8_ice_tray_one_uv_error_check_timer = 0;
                    bit_ice_tray_uv_retry_stop = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_ice_tray_one_uv_error_check_timer = 0;
            gu8_ice_tray_one_uv_error_clear_timer++;

            if ( gu8_ice_tray_one_uv_error_clear_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_ice_tray_one_uv_error_clear_timer = UV_SENSOR_ERROR_CHECK_TIME;
                Bit25_Ice_Tray_1_2_UV_Error__E76 = CLEAR;
                gu8_ice_tray_uv_retry_cnt = 0;
            }
            else{}
        }
    }
    else
    {
        gu8_ice_tray_one_uv_error_clear_timer = 0;
        gu8_ice_tray_one_uv_error_check_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




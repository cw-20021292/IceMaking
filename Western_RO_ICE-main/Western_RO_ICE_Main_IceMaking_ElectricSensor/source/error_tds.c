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
#include    "error_tds.h"

#if 0
void tds_temp_sensor_error_check(void);
void tds_in_temp_sensor_error_check(void);
void tds_out_temp_sensor_error_check(void);

U8 gu8_tds_in_temp_err_clear_timer;
U8 gu8_tds_in_temp_err_check_timer;

U8 gu8_tds_out_temp_err_clear_timer;
U8 gu8_tds_out_temp_error_check_timer;
#endif


#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_temp_sensor_error_check(void)
{
    tds_in_temp_sensor_error_check();
    tds_out_temp_sensor_error_check();

    /*..hui [19-1-25오후 2:21:56] TDS DATA 에러는 측정 완료한 시점에 확인해야하기땜에 위치 이동한다..*/
    /*tds_in_data_error_check();*/
	/*tds_out_data_error_check();*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_in_temp_sensor_error_check(void)
{
    if( gu16_AD_Result_TDS_In_Temp >= TEMPERATURE_SENSOR_OPEN
		|| gu16_AD_Result_TDS_In_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_tds_in_temp_err_clear_timer = 0;
        gu8_tds_in_temp_err_check_timer++;

        if( gu8_tds_in_temp_err_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_tds_in_temp_err_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 = SET;
        }
        else{}
    }
    else
    {
        gu8_tds_in_temp_err_check_timer = 0;
        gu8_tds_in_temp_err_clear_timer++;

        if ( gu8_tds_in_temp_err_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_tds_in_temp_err_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_out_temp_sensor_error_check(void)
{
    if( gu16_AD_Result_TDS_Out_Temp >= TEMPERATURE_SENSOR_OPEN
		|| gu16_AD_Result_TDS_Out_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_tds_out_temp_err_clear_timer = 0;
        gu8_tds_out_temp_error_check_timer++;

        if( gu8_tds_out_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_tds_out_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 = SET;
        }
        else{}
    }
    else
    {
        gu8_tds_out_temp_error_check_timer = 0;
        gu8_tds_out_temp_err_clear_timer++;

        if ( gu8_tds_out_temp_err_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_tds_out_temp_err_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 = CLEAR;
        }
        else{}
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/











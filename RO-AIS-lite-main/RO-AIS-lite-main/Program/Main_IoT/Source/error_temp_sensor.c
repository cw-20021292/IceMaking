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
#include    "error_temp_sensor.h"


void check_error_temp_sensor(void);
void check_error_hot_tank_temp_sensor(void);
/*void check_error_hot_heater_temp_sensor(void);*/
void check_error_cold_temp_sensor_open_short(void);
void check_error_room_temp_sensor_open_short(void);
void check_error_amb_temp_sensor_open_short(void);
void check_error_eva_first_temp_sensor_open_short(void);
void check_error_eva_second_temp_sensor_open_short(void);


U8 gu8_hot_tank_temp_error_check_timer;
U8 gu8_hot_tank_temp_error_clear_timer;

U8 gu8_hot_heater_temp_error_check_timer;
U8 gu8_hot_heater_temp_error_clear_timer;

U8 gu8_cold_temp_error_check_timer;
U8 gu8_cold_temp_error_clear_timer;

U8 gu8_room_temp_error_check_timer;
U8 gu8_room_temp_error_clear_timer;

U8 gu8_amb_temp_error_clear_timer;
U8 gu8_amb_temp_error_check_timer;

U8 gu8_eva_first_temp_error_check_timer;
U8 gu8_eva_first_temp_error_clear_timer;

U8 gu8_eva_second_temp_error_check_timer;
U8 gu8_eva_second_temp_error_clear_timer;

bit bit_cold_read_finish;
bit bit_hot_read_finish;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_temp_sensor(void)
{
    /*..hui [23-2-8오후 5:07:07] 온수탱크 온도센서..*/
    check_error_hot_tank_temp_sensor();

    /*..hui [17-12-29오후 11:39:53] 냉수센서 오픈 쇼트 에러..*/
    check_error_cold_temp_sensor_open_short();

    /*..hui [19-6-26오전 11:16:15] 정수 온도센서..*/
    check_error_room_temp_sensor_open_short();

    /*..hui [19-6-26오전 11:16:19] 주변 온도센서..*/
    check_error_amb_temp_sensor_open_short();

    /*..hui [19-6-26오전 11:16:25] 에바1 온도센서..*/
    /*check_error_eva_first_temp_sensor_open_short();*/

    /*..hui [19-6-26오전 11:16:29] 에바2 온도센서..*/
    /*check_error_eva_second_temp_sensor_open_short();*/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_hot_tank_temp_sensor(void)
{
    /*..hui [23-3-3오후 3:35:49] 온수 OFF이면 에러 해제..*/
    if( F_Hot_Enable != SET )
    {
        Bit0_Hot_Tank_Temp_Open_Short_Error = CLEAR;
        gu8_hot_tank_temp_error_clear_timer = 0;
        gu8_hot_tank_temp_error_check_timer = 0;

        /*..hui [24-4-24오후 7:28:13] 수정.. 온수센서 에러상태 - 온수 OFF - 온수 ON시 다시 에러유무 판단 완료한 후부터 정상으로 표시..*/
        /*bit_hot_read_finish = SET;*/
        bit_hot_read_finish = CLEAR;

    }
    else
    {
        if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
            || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
        {
            gu8_hot_tank_temp_error_clear_timer = 0;
            gu8_hot_tank_temp_error_check_timer++;

            if( gu8_hot_tank_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_hot_tank_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                Bit0_Hot_Tank_Temp_Open_Short_Error = SET;
                bit_hot_read_finish = SET;
            }
            else{}
        }
        else
        {
            gu8_hot_tank_temp_error_check_timer = 0;
            gu8_hot_tank_temp_error_clear_timer++;

            if ( gu8_hot_tank_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_hot_tank_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                Bit0_Hot_Tank_Temp_Open_Short_Error = CLEAR;
                bit_hot_read_finish = SET;
            }
            else{}

        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void check_error_hot_heater_temp_sensor(void)
{
    if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_hot_heater_temp_error_clear_timer = 0;
        gu8_hot_heater_temp_error_check_timer++;

        if( gu8_hot_heater_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_hot_heater_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit1_Room_OverHeat_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_hot_heater_temp_error_check_timer = 0;
        gu8_hot_heater_temp_error_clear_timer++;

        if ( gu8_hot_heater_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_hot_heater_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit1_Room_OverHeat_Error = CLEAR;
        }
        else{}
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_cold_temp_sensor_open_short(void)
{
    /*..hui [23-3-3오후 3:36:03] 냉수 에러이면 에러해제..*/
    if( F_Cold_Enable != SET )
    {
        Bit10_Cold_Temp_Open_Short_Error = CLEAR;
        gu8_cold_temp_error_clear_timer = 0;
        gu8_cold_temp_error_check_timer = 0;

        /*bit_cold_read_finish = SET;*/
        /*..hui [24-4-24오후 7:28:13] 수정.. 온수센서 에러상태 - 온수 OFF - 온수 ON시 다시 에러유무 판단 완료한 후부터 정상으로 표시..*/
        bit_cold_read_finish = CLEAR;
    }
    else
    {
        /*..hui [19-12-19오후 4:46:31] 파워 인가중에만 에러 감지..*/
        /*if( pCOLD_TH_POWER == SET )*/
        if( bit_adc_cold_start == SET )
        {
            if( gu16_AD_Result_Cold >= TEMPERATURE_SENSOR_OPEN
                || gu16_AD_Result_Cold <= TEMPERATURE_SENSOR_SHORT )
            {
                gu8_cold_temp_error_clear_timer = 0;
                gu8_cold_temp_error_check_timer++;

                if( gu8_cold_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
                {
                    gu8_cold_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                    Bit10_Cold_Temp_Open_Short_Error = SET;
                    bit_cold_read_finish = SET;
                }
                else{}
            }
            else
            {
                gu8_cold_temp_error_check_timer = 0;
                gu8_cold_temp_error_clear_timer++;

                if ( gu8_cold_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
                {
                    gu8_cold_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                    Bit10_Cold_Temp_Open_Short_Error = CLEAR;
                    bit_cold_read_finish = SET;
                }
                else{}

            }
        }
        else
        {
            gu8_cold_temp_error_clear_timer = 0;
            gu8_cold_temp_error_check_timer = 0;
        }

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_temp_sensor_open_short(void)
{
    /*..hui [19-12-19오후 4:46:31] 파워 인가중에만 에러 감지..*/
    /*if( pROOM_TH_POWER == SET )*/
    if( bit_adc_room_start == SET )
    {
        if( gu16_AD_Result_Room >= TEMPERATURE_SENSOR_OPEN
            || gu16_AD_Result_Room <= TEMPERATURE_SENSOR_SHORT )
        {
            gu8_room_temp_error_clear_timer = 0;
            gu8_room_temp_error_check_timer++;

            if( gu8_room_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_room_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                Bit2_Room_Temp_Open_Short_Error = SET;
            }
            else{}
        }
        else
        {
            gu8_room_temp_error_check_timer = 0;
            gu8_room_temp_error_clear_timer++;

            if ( gu8_room_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
            {
                gu8_room_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
                Bit2_Room_Temp_Open_Short_Error = CLEAR;
            }
            else{}
        }
    }
    else
    {
        gu8_room_temp_error_clear_timer = 0;
        gu8_room_temp_error_check_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_amb_temp_sensor_open_short(void)
{

    if( gu16_AD_Result_Amb >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Amb <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_amb_temp_error_clear_timer = 0;
        gu8_amb_temp_error_check_timer++;

        if( gu8_amb_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_amb_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit11_Amb_Temp_Open_Short_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_amb_temp_error_check_timer = 0;
        gu8_amb_temp_error_clear_timer++;

        if ( gu8_amb_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_amb_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit11_Amb_Temp_Open_Short_Error = CLEAR;
        }
        else{}

    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_eva_first_temp_sensor_open_short(void)
{

    if( gu16_AD_Result_Eva_First >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_First <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_eva_first_temp_error_clear_timer = 0;
        gu8_eva_first_temp_error_check_timer++;

        if( gu8_eva_first_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_eva_first_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit16_Eva_First_Temp_Open_Short_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_eva_first_temp_error_check_timer = 0;
        gu8_eva_first_temp_error_clear_timer++;

        if ( gu8_eva_first_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_eva_first_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit16_Eva_First_Temp_Open_Short_Error = CLEAR;
        }
        else{}

    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_eva_second_temp_sensor_open_short(void)
{

    if( gu16_AD_Result_Eva_Second >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_Second <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_eva_second_temp_error_clear_timer = 0;
        gu8_eva_second_temp_error_check_timer++;

        if( gu8_eva_second_temp_error_check_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_eva_second_temp_error_check_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit17_Eva_Second_Temp_Open_Short_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_eva_second_temp_error_check_timer = 0;
        gu8_eva_second_temp_error_clear_timer++;

        if ( gu8_eva_second_temp_error_clear_timer >= TEMPERATURE_SENSOR_ERROR_CHECK_TIME )
        {
            gu8_eva_second_temp_error_clear_timer = TEMPERATURE_SENSOR_ERROR_CHECK_TIME;
            Bit17_Eva_Second_Temp_Open_Short_Error = CLEAR;
        }
        else{}

    }

}


















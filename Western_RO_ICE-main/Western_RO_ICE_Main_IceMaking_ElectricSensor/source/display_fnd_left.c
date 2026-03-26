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
#include    "display_fnd_left.h"

void fnd_left_normal_state(void);
void normal_state_pure_temp(void);
void normal_state_cold_temp(void);
void normal_state_hot_temp(void);
void normal_state_hot_extract(void);
//void normal_state_hot_preheat(void);
void fnd_left_front_version(void);
void fnd_left_pba_test(void);
void fnd_left_uart_test(void);



//void fnd_left_water_out(void);
//void fnd_left_water_out_normal(void);
//void fnd_left_water_out_continue(void);
void fnd_left_ice_out(void);
void fnd_left_setting(void);
void fnd_left_button_set(void);
void fnd_left_error(void);
void fnd_left_uv(void);
void fnd_left_all_lock(void);
void fnd_left_display_test(void);




TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Steam_Off_Set_Display           U8SetDisplayB.Bit.b2






U8 gu8_fnd_left_ice_step;
U8 gu8_fnd_left_ice_timer;

U8 gu8_fnd_water_step;
U8 gu8_fnd_water_timer;
U16 gu16_extract_display_timer;

U8 gu8_extract_amount;
U8 gu8_extract_display_cnt;




U8 gu8_temp_hundred;
U8 gu8_temp_ten;
U8 gu8_temp_one;


U8 gu8_Fahrenheit_temp_old;
U8 gu8_Celcius_temp_old;

bit bit_temp_old_update;

bit bit_uv_display_finish;
bit bit_error_display_finish;

U8 gu8_cold_temp_old;
U8 gu8_cold_temp_update_timer;

U8 gu8_current_room_temp_mode;

U8 gu8_Fahrenheit_temp;
U8 gu8_Celcius_temp;


bit bit_hot_current_temp_on;
U8 gu8_hot_last_current_temp;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_normal_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;

    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        ///clear_hot_preheat_breath();
        normal_state_pure_temp();
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        ///clear_hot_preheat_breath();
        normal_state_cold_temp();
    }
    else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
    {
        if( F_WaterOut == SET )
        {
            if( bit_hot_current_temp_on == SET )
            {
                normal_state_hot_extract();
            }
            else
            {
                normal_state_hot_temp();
            }
        }
        else
        {
            normal_state_hot_temp();

            /*if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_ON )*/
            /*..hui [24-2-20오후 1:42:23] 히팅 & 프리페어 둘 다 ON일 경우에만 current랑 현재온도 표시..*/
            /*if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_ON && gu8_heating_display_mode == HEATING_DISPLAY_2_ON )*/
            if( gu8_hot_prepare_mode == HOT_PREPARE_MODE_ON )
            {
                /*..hui [24-2-20오후 4:45:27] 에러 걸렸을때, 온수 OFF했을때 커런트랑 현재온도 표시 안함.. 제호님..*/
                /*if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                    || Bit3_Leakage_Sensor_Error__E01 == SET
                    || Bit4_Room_Low_Water_Level_Error__E21 == SET
                    || Bit1_Room_OverHeat_Error__E49 == SET
                    || F_Hot_Enable == CLEAR )*/
                /*..hui [24-2-21오전 10:09:19] 온수센서 에러만 OFF하고 나머지에러는 Preparing 조건에 맞춰 표시하도록..제호....*/
                if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                    || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
                    || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT ) )
                {
                    bit_hot_current_temp_on = CLEAR;
                }
                else
                {
                    bit_hot_current_temp_on = SET;
                }
            }
            else
            {
                bit_hot_current_temp_on = CLEAR;
            }

            gu8_hot_last_current_temp = 0;
        }
    }

    mu8_temporary_hundred = gu8_temp_hundred;
    mu8_temporary_ten = gu8_temp_ten;
    mu8_temporary_one = gu8_temp_one;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_state_pure_temp(void)
{
    #if 0
    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        gu8_temp_hundred = DISPLAY_OFF;
        gu8_temp_ten = DISPLAY_NUM_8;
        gu8_temp_one = DISPLAY_NUM_0;
    }
    else
    {
        gu8_temp_hundred = DISPLAY_OFF;
        gu8_temp_ten = DISPLAY_NUM_2;
        gu8_temp_one = DISPLAY_NUM_7;
    }
    #endif

    if( gu8_Hot_Tank_Temperature_One_Degree >= 85 )
    {
        if( gu8_Cold_Temperature_One_Degree <= 10 )
        {
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_MID;
        }
        else
        {
            /*gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_HIGH;*/
            /*..hui [24-11-26오후 4:14:57] 25도로 변경.. RO CT와 표시사양 통일..*/
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_MID;
        }
    }
    else if( gu8_Hot_Tank_Temperature_One_Degree >= 60 )
    {
        if( gu8_Cold_Temperature_One_Degree <= 10 )
        {
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_LOW;
        }
        else
        {
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_MID;
        }
    }
    else
    {
        if( gu8_Cold_Temperature_One_Degree <= 10 )
        {
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_MID;
        }
        else
        {
            gu8_current_room_temp_mode = ROOM_TEMP_DISPLAY_HIGH;
        }
    }


    if( gu8_current_room_temp_mode == ROOM_TEMP_DISPLAY_MID )
    {
        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_7;
        }
        else
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_2;
            gu8_temp_one = DISPLAY_NUM_5;
        }
    }
    else if( gu8_current_room_temp_mode == ROOM_TEMP_DISPLAY_LOW )
    {
        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_3;
        }
        else
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_2;
            gu8_temp_one = DISPLAY_NUM_3;
        }
    }
    else /*if( gu8_current_room_temp_mode == ROOM_TEMP_DISPLAY_HIGH )*/
    {
        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_8;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_2;
            gu8_temp_one = DISPLAY_NUM_7;
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_state_cold_temp(void)
{
    U8 mu8_Fahrenheit_temp = 0;
    U8 mu8_Celcius_temp = 0;

    #if 0
    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        gu8_temp_hundred = DISPLAY_OFF;
        gu8_temp_ten = DISPLAY_NUM_4;
        gu8_temp_one = DISPLAY_NUM_3;
    }
    else
    {
        gu8_temp_hundred = DISPLAY_OFF;
        gu8_temp_ten = DISPLAY_OFF;
        gu8_temp_one = DISPLAY_NUM_6;
    }
    #endif

    /*mu8_Fahrenheit_temp = get_Fahrenheit( gu8_Cold_Temperature_One_Degree );*/
    //*mu8_Celcius_temp = gu8_Cold_Temperature_One_Degree;*/

    /*..hui [23-11-16오후 2:03:52] 물 추출할때는 이전값 유지..*/
    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    if( gu8_cold_temp_old != gu8_Cold_Temperature_One_Degree )
    {
        gu8_cold_temp_old = gu8_Cold_Temperature_One_Degree;
        gu8_cold_temp_update_timer = 0;
    }
    else
    {
        gu8_cold_temp_update_timer++;

        if( gu8_cold_temp_update_timer >= 20 )
        {
            gu8_cold_temp_update_timer = 20;

            gu8_Fahrenheit_temp = get_Fahrenheit( gu8_Cold_Temperature_One_Degree );
            gu8_Celcius_temp = gu8_Cold_Temperature_One_Degree;
        }
        else{}
    }

    /*if( gu8_Cold_Temperature_One_Degree <= 6 )*/
    /*..hui [24-1-12오후 3:36:51] Cooling LED OFF된 상태에서는 무조건 6도로 표시.. 에러 포함..*/
    if( gu8_cooling_display_mode == COOLING_DISPLAY_0_OFF )
    {
        gu8_Fahrenheit_temp = 43;
        gu8_Celcius_temp = 6;
    }
    else if( gu8_cold_temp_old == 0 )
    {
        gu8_Fahrenheit_temp = get_Fahrenheit( gu8_Cold_Temperature_One_Degree );
        gu8_Celcius_temp = gu8_Cold_Temperature_One_Degree;
    }
    else if( gu8_Fahrenheit_temp == 0 && gu8_Celcius_temp == 0 )
    {
        gu8_Fahrenheit_temp = get_Fahrenheit( gu8_Cold_Temperature_One_Degree );
        gu8_Celcius_temp = gu8_Cold_Temperature_One_Degree;
    }
    else{}

    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        if( gu8_Fahrenheit_temp < 10 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_OFF;
            gu8_temp_one = gu8_Fahrenheit_temp;
        }
        else if( gu8_Fahrenheit_temp < 100 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = (gu8_Fahrenheit_temp / 10);
            gu8_temp_one = (gu8_Fahrenheit_temp % 10);
        }
        else
        {
            gu8_temp_hundred = (U8)((gu8_Fahrenheit_temp / 100) % 10);
            gu8_temp_ten = (U8)((gu8_Fahrenheit_temp / 10) % 10);
            gu8_temp_one = (U8)(gu8_Fahrenheit_temp % 10);
        }
    }
    else
    {
        /*..hui [24-1-31오전 9:14:53] 10미만일때는 왼쪽 2개 OFF후 표시..*/
        if( gu8_Celcius_temp < 10 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_OFF;
            gu8_temp_one = gu8_Celcius_temp;
        }
        else if( gu8_Celcius_temp < 100 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = (gu8_Celcius_temp / 10);
            gu8_temp_one = (gu8_Celcius_temp % 10);
        }
        else
        {
            gu8_temp_hundred = (U8)((gu8_Celcius_temp / 100) % 10);
            gu8_temp_ten = (U8)((gu8_Celcius_temp / 10) % 10);
            gu8_temp_one = (U8)(gu8_Celcius_temp % 10);
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_state_hot_temp(void)
{
    /*..hui [24-11-21오후 2:43:24] 고도모드 설정에 따라 최대값 초과할수 없도록 변경하여 표시..*/
    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            /*..hui [24-11-21오후 2:50:14] 95도는 2단계 - 90도, 3단계 - 85도, 4단계 - 77도..*/
            if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
            {
                gu8_temp_hundred = DISPLAY_NUM_2;
                gu8_temp_ten = DISPLAY_NUM_0;
                gu8_temp_one = DISPLAY_NUM_0;
            }
            else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_9;
                gu8_temp_one = DISPLAY_NUM_4;
            }
            else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_0;
            }
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            /*..hui [24-11-21오후 2:49:19] 85도는 4단계만 77도..*/
            if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_0;
            }
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            /*..hui [24-11-21오후 2:49:31] 77도는 전부 77도..*/
            gu8_temp_hundred = DISPLAY_NUM_1;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            /*..hui [24-11-21오후 2:49:39] 43도는 전부 43도..*/
            gu8_temp_hundred = DISPLAY_NUM_1;
            gu8_temp_ten = DISPLAY_NUM_1;
            gu8_temp_one = DISPLAY_NUM_0;
        }
    }
    else
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            /*..hui [24-11-21오후 2:50:14] 95도는 2단계 - 90도, 3단계 - 85도, 4단계 - 77도..*/
            if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_9;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_9;
                gu8_temp_one = DISPLAY_NUM_0;
            }
            else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_7;
            }
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            /*..hui [24-11-21오후 2:49:19] 85도는 4단계만 77도..*/
            if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_5;
            }
            else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_7;
            }
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            /*..hui [24-11-21오후 2:49:31] 77도는 전부 77도..*/
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_7;
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            /*..hui [24-11-21오후 2:49:39] 43도는 전부 43도..*/
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_4;
            gu8_temp_one = DISPLAY_NUM_3;
        }
    }







    #if 0
    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            gu8_temp_hundred = DISPLAY_NUM_2;
            gu8_temp_ten = DISPLAY_NUM_0;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            gu8_temp_hundred = DISPLAY_NUM_1;
            gu8_temp_ten = DISPLAY_NUM_8;
            gu8_temp_one = DISPLAY_NUM_5;
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            gu8_temp_hundred = DISPLAY_NUM_1;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            gu8_temp_hundred = DISPLAY_NUM_1;
            gu8_temp_ten = DISPLAY_NUM_1;
            gu8_temp_one = DISPLAY_NUM_0;
        }
    }
    else
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_9;
            gu8_temp_one = DISPLAY_NUM_5;
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_8;
            gu8_temp_one = DISPLAY_NUM_5;
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_7;
            gu8_temp_one = DISPLAY_NUM_7;
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_4;
            gu8_temp_one = DISPLAY_NUM_3;
        }
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_state_hot_extract(void)
{
    U8 mu8_Fahrenheit_temp = 0;
    U8 mu8_Celcius_temp = 0;

    #if 0
    /*..hui [23-5-30오후 2:30:54] 가열하다가 물 추출할때는 추출하기 전 마지막 온도 기준으로 표시..*/
    if( F_WaterOut == SET )
    {
        return;
    }
    else{}
    #endif

    if( gu8_hot_last_current_temp == 0 )
    {
        gu8_hot_last_current_temp = gu8_Hot_Tank_Temperature_One_Degree;
    }
    else{}

    /*mu8_Fahrenheit_temp = get_Fahrenheit( gu8_Hot_Tank_Temperature_One_Degree );
    mu8_Celcius_temp = gu8_Hot_Tank_Temperature_One_Degree;*/

    mu8_Fahrenheit_temp = get_Fahrenheit( gu8_hot_last_current_temp );
    mu8_Celcius_temp = gu8_hot_last_current_temp;

    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        if( mu8_Fahrenheit_temp < 10 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_OFF;
            gu8_temp_one = mu8_Fahrenheit_temp;
        }
        else if( mu8_Fahrenheit_temp < 100 )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = (mu8_Fahrenheit_temp / 10);
            gu8_temp_one = (mu8_Fahrenheit_temp % 10);
        }
        else
        {
            gu8_temp_hundred = (U8)((mu8_Fahrenheit_temp / 100) % 10);
            gu8_temp_ten = (U8)((mu8_Fahrenheit_temp / 10) % 10);
            gu8_temp_one = (U8)(mu8_Fahrenheit_temp % 10);
        }
    }
    else
    {
         if( mu8_Celcius_temp < 10 )
         {
             gu8_temp_hundred = DISPLAY_OFF;
             gu8_temp_ten = DISPLAY_OFF;
             gu8_temp_one = mu8_Celcius_temp;
         }
         else if( mu8_Celcius_temp < 100 )
         {
             gu8_temp_hundred = DISPLAY_OFF;
             gu8_temp_ten = (mu8_Celcius_temp / 10);
             gu8_temp_one = (mu8_Celcius_temp % 10);
         }
         else
         {
             gu8_temp_hundred = (U8)((mu8_Celcius_temp / 100) % 10);
             gu8_temp_ten = (U8)((mu8_Celcius_temp / 10) % 10);
             gu8_temp_one = (U8)(mu8_Celcius_temp % 10);
         }
    }

    /*..hui [23-7-17오전 9:39:29] 추출 불가이므로.. 표시된 온도보다 높더라도 낮게 표시..*/
    /*..hui [23-7-17오전 9:39:47] 설정온도보다 높은데 추출 안되면 그게 더 이상..*/
    if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
    {
        if( gu8_hot_last_current_temp >= 93 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                //gu8_temp_hundred = DISPLAY_NUM_2;
                //gu8_temp_ten = DISPLAY_NUM_0;
                //gu8_temp_one = DISPLAY_NUM_0;

                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_9;
                gu8_temp_one = DISPLAY_NUM_9;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_9;
                /*gu8_temp_one = DISPLAY_NUM_5;*/
                gu8_temp_one = DISPLAY_NUM_3;
            }
        }
        else{}
    }
    else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
    {
        if( gu8_hot_last_current_temp >= 84 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_3;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_4;
            }
        }
        else{}

    }
    else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
    {
        if( gu8_hot_last_current_temp >= 76 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_6;
                gu8_temp_one = DISPLAY_NUM_8;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_6;
            }
        }
        else{}

    }
    else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
    {
        if( gu8_hot_last_current_temp >= 42 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_0;
                gu8_temp_one = DISPLAY_NUM_7;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_4;
                gu8_temp_one = DISPLAY_NUM_2;
            }
        }
        else{}

    }

    if( gu8_hot_last_current_temp <= CONVERT_FAHRENHEIT_TO_CELSIUS_50 )
    {
        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_5;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_1;
            gu8_temp_one = DISPLAY_NUM_0;
        }
    }
    else{}








}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void normal_state_hot_preheat(void)
{
    U8 mu8_Fahrenheit_temp = 0;
    U8 mu8_Celcius_temp = 0;

    /*..hui [23-5-30오후 2:30:54] 가열하다가 물 추출할때는 추출하기 전 마지막 온도 기준으로 표시..*/
    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    mu8_Fahrenheit_temp = get_Fahrenheit( gu8_Hot_Tank_Temperature_One_Degree );
    mu8_Celcius_temp = gu8_Hot_Tank_Temperature_One_Degree;


    if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
    {
        gu8_Celcius_temp_old = 0;

        /*..hui [23-6-16오후 1:09:02] 2도 이상 올랐을때만 표시..*/
        /*..hui [23-6-16오후 1:10:18] 만약 2도..*/
        /*if( (mu8_Fahrenheit_temp >= (gu8_Fahrenheit_temp_old + PREHEAT_DISPLAY_FAHRENHEIT_TEMP_DIFF))
            || (mu8_Fahrenheit_temp == FAHRENHEIT_0_DEGREE) )*/
        if( (mu8_Fahrenheit_temp >= gu8_Fahrenheit_temp_old)
            || (mu8_Fahrenheit_temp == FAHRENHEIT_0_DEGREE) )
        {
            gu8_Fahrenheit_temp_old = mu8_Fahrenheit_temp;

            if( mu8_Fahrenheit_temp < 100 )
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = (mu8_Fahrenheit_temp / 10);
                gu8_temp_one = (mu8_Fahrenheit_temp % 10);
            }
            else
            {
                gu8_temp_hundred = (U8)((mu8_Fahrenheit_temp / 100) % 10);
                gu8_temp_ten = (U8)((mu8_Fahrenheit_temp / 10) % 10);
                gu8_temp_one = (U8)(mu8_Fahrenheit_temp % 10);
            }
        }
        else
        {
            /*..hui [23-6-16오후 1:14:16] 혹시몰라....*/
            /*..hui [23-6-16오후 1:14:51] 이전값이 1도 이상이고(안전장치), 현재값이 이전값보다 3도 더 내려가면 값 업데이트..*/
            /*..hui [23-6-16오후 1:42:56] 걍 10도 이하면 그냥 계속 업데이트..*/
            /*..hui [23-7-24오후 2:58:32] 10도로 변경..*/
            if( (( mu8_Fahrenheit_temp < (gu8_Fahrenheit_temp_old - PREHEAT_DISPLAY_FAHRENHEIT_TEMP_LOW) )
                && ( gu8_Fahrenheit_temp_old >= FAHRENHEIT_0_DEGREE ) )
                || (mu8_Fahrenheit_temp <= FAHRENHEIT_10_DEGREE) )
            {
                gu8_Fahrenheit_temp_old = mu8_Fahrenheit_temp;

                if( mu8_Fahrenheit_temp < 100 )
                {
                    gu8_temp_hundred = DISPLAY_OFF;
                    gu8_temp_ten = (mu8_Fahrenheit_temp / 10);
                    gu8_temp_one = (mu8_Fahrenheit_temp % 10);
                }
                else
                {
                    gu8_temp_hundred = (U8)((mu8_Fahrenheit_temp / 100) % 10);
                    gu8_temp_ten = (U8)((mu8_Fahrenheit_temp / 10) % 10);
                    gu8_temp_one = (U8)(mu8_Fahrenheit_temp % 10);
                }
            }
            else
            {
                /*..hui [23-7-27오후 3:11:32] 잠깐 다른화면 다녀온 사이에 마지막 최종 값 보여줘야 함..*/
                /*..hui [23-7-27오후 3:12:04] 예열화면 -> 냉수 선택 -> 그 사이에 온도 낮아짐 -> 다시 예열화면으로 돌아오면..*/
                /*..hui [23-7-27오후 3:12:13] 이쪽으로 들어와서 값 표시가 안됨..*/
                /*..hui [23-7-27오후 3:12:31] 그럴땐 마지막으로 갖고있는 old값으로 표시..*/
                if( gu8_Fahrenheit_temp_old < 100 )
                {
                    gu8_temp_hundred = DISPLAY_OFF;
                    gu8_temp_ten = (gu8_Fahrenheit_temp_old / 10);
                    gu8_temp_one = (gu8_Fahrenheit_temp_old % 10);
                }
                else
                {
                    gu8_temp_hundred = (U8)((gu8_Fahrenheit_temp_old / 100) % 10);
                    gu8_temp_ten = (U8)((gu8_Fahrenheit_temp_old / 10) % 10);
                    gu8_temp_one = (U8)(gu8_Fahrenheit_temp_old % 10);
                }
            }
        }
    }
    else
    {
         gu8_Fahrenheit_temp_old = 0;

         /*if( (mu8_Celcius_temp >= (gu8_Celcius_temp_old + PREHEAT_DISPLAY_CELCIUS_TEMP_DIFF))
             || (mu8_Celcius_temp == CELCIUS_0_DEGREE) )*/
         /*..hui [23-7-24오후 3:55:11] 1도 단위..*/
         if( (mu8_Celcius_temp >= gu8_Celcius_temp_old)
             || (mu8_Celcius_temp == CELCIUS_0_DEGREE) )
         {
             gu8_Celcius_temp_old = mu8_Celcius_temp;

             if( mu8_Celcius_temp < 100 )
             {
                 gu8_temp_hundred = DISPLAY_OFF;
                 gu8_temp_ten = (mu8_Celcius_temp / 10);
                 gu8_temp_one = (mu8_Celcius_temp % 10);
             }
             else
             {
                 gu8_temp_hundred = (U8)((mu8_Celcius_temp / 100) % 10);
                 gu8_temp_ten = (U8)((mu8_Celcius_temp / 10) % 10);
                 gu8_temp_one = (U8)(mu8_Celcius_temp % 10);
             }
         }
         else
         {
             /*..hui [23-6-16오후 1:14:16] 혹시몰라....*/
             /*..hui [23-6-16오후 1:14:51] 이전값이 1도 이상이고(안전장치), 현재값이 이전값보다 3도 더 내려가면 값 업데이트..*/
             /*..hui [23-6-16오후 1:42:56] 걍 10도 이하면 그냥 계속 업데이트..*/
             if( ( ( mu8_Celcius_temp < (gu8_Celcius_temp_old - PREHEAT_DISPLAY_CELCIUS_TEMP_LOW) )
                 && ( gu8_Celcius_temp_old >= PREHEAT_DISPLAY_CELCIUS_TEMP_LOW ) )
                 || (mu8_Celcius_temp <= CELCIUS_10_DEGREE) )
             {
                 gu8_Celcius_temp_old = mu8_Celcius_temp;

                 if( mu8_Celcius_temp < 100 )
                 {
                     gu8_temp_hundred = DISPLAY_OFF;
                     gu8_temp_ten = (mu8_Celcius_temp / 10);
                     gu8_temp_one = (mu8_Celcius_temp % 10);
                 }
                 else
                 {
                     gu8_temp_hundred = (U8)((mu8_Celcius_temp / 100) % 10);
                     gu8_temp_ten = (U8)((mu8_Celcius_temp / 10) % 10);
                     gu8_temp_one = (U8)(mu8_Celcius_temp % 10);
                 }
             }
             else
             {
                 /*..hui [23-7-27오후 3:12:56] 섭씨도 마찬가지..*/
                 if( gu8_Celcius_temp_old < 100 )
                 {
                     gu8_temp_hundred = DISPLAY_OFF;
                     gu8_temp_ten = (gu8_Celcius_temp_old / 10);
                     gu8_temp_one = (gu8_Celcius_temp_old % 10);
                 }
                 else
                 {
                     gu8_temp_hundred = (U8)((gu8_Celcius_temp_old / 100) % 10);
                     gu8_temp_ten = (U8)((gu8_Celcius_temp_old / 10) % 10);
                     gu8_temp_one = (U8)(gu8_Celcius_temp_old % 10);
                 }
             }
         }


    }


    /*..hui [23-7-17오전 9:39:29] 추출 불가이므로.. 표시된 온도보다 높더라도 낮게 표시..*/
    /*..hui [23-7-17오전 9:39:47] 설정온도보다 높은데 추출 안되면 그게 더 이상..*/
    if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 94 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_2;
                gu8_temp_ten = DISPLAY_NUM_0;
                gu8_temp_one = DISPLAY_NUM_0;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_9;
                gu8_temp_one = DISPLAY_NUM_5;
            }
        }
        else{}
    }
    else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 84 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_3;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_8;
                gu8_temp_one = DISPLAY_NUM_4;
            }
        }
        else{}

    }
    else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 76 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_6;
                gu8_temp_one = DISPLAY_NUM_8;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_7;
                gu8_temp_one = DISPLAY_NUM_6;
            }
        }
        else{}

    }
    else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 42 )
        {
            if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
            {
                gu8_temp_hundred = DISPLAY_NUM_1;
                gu8_temp_ten = DISPLAY_NUM_0;
                gu8_temp_one = DISPLAY_NUM_7;
            }
            else
            {
                gu8_temp_hundred = DISPLAY_OFF;
                gu8_temp_ten = DISPLAY_NUM_4;
                gu8_temp_one = DISPLAY_NUM_2;
            }
        }
        else{}

    }

    if( gu8_Hot_Tank_Temperature_One_Degree <= CONVERT_FAHRENHEIT_TO_CELSIUS_50 )
    {
        if( gu8_oF__oC_select == Fahrenheit_oF_SELECT )
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_5;
            gu8_temp_one = DISPLAY_NUM_0;
        }
        else
        {
            gu8_temp_hundred = DISPLAY_OFF;
            gu8_temp_ten = DISPLAY_NUM_1;
            gu8_temp_one = DISPLAY_NUM_0;
        }
    }
    else{}

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_ice_out(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( F_WaterOut == SET )
    {
        if( gu8_fnd_left_ice_step >= 5 )
        {
            gu8_fnd_left_ice_timer = 0;
            gu8_fnd_left_ice_step = 1;
        }
        else{}
    }
    else{}

    switch( gu8_fnd_left_ice_step )
    {
        case 0 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 1 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}


        break;

        case 2 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 3 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}


        break;

        case 4 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;

                if( F_WaterOut == SET )
                {
                    gu8_fnd_left_ice_step = 1;
                }
                else
                {
                    gu8_fnd_left_ice_step++;
                }
            }
            else{}

        break;

        case 5 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 6 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 7 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 8 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 9 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 10 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step++;
            }
            else{}

        break;

        case 11 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_left_ice_timer++;

            if( gu8_fnd_left_ice_timer >= 5 )
            {
                gu8_fnd_left_ice_timer = 0;
                gu8_fnd_left_ice_step = 1;
            }
            else{}

        break;



        default :

            gu8_fnd_left_ice_step = 0;
            gu8_fnd_left_ice_timer = 0;

        break;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_setting(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;


    /*..hui [23-2-7오후 7:55:29] ICE OFF, Cold Temp, Eco Mode..*/
    switch( u8SetDisplay )
    {
        case ON_OFF_DISPLAY_OFF:

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
            gu8_on_off_flick_cnt = 0;
            gu16_on_off_flick_timer = 0;

        break;

        case ON_OFF_DISPLAY_STEAM_OFF_SET:

            /*mu8_flick_state = on_off_flick_timer(5, 5);*/
            mu8_flick_state = on_off_flick_timer(30, 0);

            if( mu8_flick_state == SET )
            {
                if( bit_periodic_ster_enable == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;

        default:

            u8SetDisplay = ON_OFF_DISPLAY_OFF;
            gu8_on_off_flick_cnt = 0;
            gu16_on_off_flick_timer = 0;

        break;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_button_set(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    switch( u8ButtonSetDisplay )
    {
        case BUTTON_SET_DISPLAY_OFF:

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case BUTTON_SET_HOT_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                if( F_Hot_Enable == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;

        case BUTTON_SET_MUTE_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                /*if( F_Mute_Enable == SET )*/

                /*..hui [23-7-26오후 7:15:45] 소리가 나는게 ON임.. UI 확인받았음.. 내가한게 맞았네..*/
                if( F_Mute_Enable == CLEAR )
                {
                    /*..hui [23-5-12오후 2:01:32] 소리 OFF이므로 ON표시..*/
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }


        break;

        case BUTTON_SET_ICE_OFF_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                if( F_IceOn == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;

        case BUTTON_SET_RECOVER_FAST_ICE_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                /*..hui [24-4-11오후 7:27:17] 얼음우선 예전 사양으로..*/
                if( gu8_recover_org_fast_ice == RECOVER_FAST_ICE )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;


        default:

            u8ButtonSetDisplay = BUTTON_SET_DISPLAY_OFF;
            gu16_button_set_display_timer = 0;

        break;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_error(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( bit_error_display_finish == SET )
    {
        bit_error_display_finish = CLEAR;
        /*gu8_error_flick_timer = UV_PROGRESS_DISPLAY_TIME;*/
        gu8_error_flick_timer = EERROR_DISPLAY_TIME;
    }
    else{}

    /*mu8_flick_state = error_flick_timer(5, 5);*/
    mu8_flick_state = error_flick_timer(EERROR_DISPLAY_TIME, 5);

    if( mu8_flick_state == SET )
    {
        /*mu8_temporary_hundred = DISPLAY_OFF;*/
        /*..hui [23-11-24오후 2:30:48] 에러 아이콘 빠지면서 Exx로 표시..*/
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (gu8_Error_Code / 10);
        mu8_temporary_one = (gu8_Error_Code % 10);
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_uv(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( bit_uv_display_finish == SET )
    {
        /*bit_uv_display_finish = CLEAR;*/
        gu16_uv_percent_flick_timer = UV_PROGRESS_DISPLAY_TIME;
    }
    else{}

    /*mu8_flick_state = error_flick_timer(5, 5);*/
    mu8_flick_state = uv_percent_display_timer(UV_PROGRESS_DISPLAY_TIME);

    if( mu8_flick_state == SET )
    {
        if( gu8_display_uv_elapsed_percent < 100 )
        {
            if( gu8_display_uv_elapsed_percent == 0 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = (gu8_display_uv_elapsed_percent / 10);
                mu8_temporary_one = (gu8_display_uv_elapsed_percent % 10);
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_NUM_1;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_all_lock(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_front_version(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8DataBuffer_1 = 0;
    U8 mu8DataBuffer_2 = 0;

    mu8DataBuffer_1 = gu8_front_version >> 4;

    if( mu8DataBuffer_1 == 0x01 )
    {
        mu8DataBuffer_1 = 1;
    }
    else if( mu8DataBuffer_1 == 0x02 )
    {
        mu8DataBuffer_1 = 2;
    }
    else if( mu8DataBuffer_1 == 0x03 )
    {
        mu8DataBuffer_1 = 10;
    }
    else if( mu8DataBuffer_1 == 0x04 )
    {
        mu8DataBuffer_1 = 20;
    }

    mu8DataBuffer_2 = (U8)(gu8_front_version & 0x0F);


    mu8_temporary_hundred = (U8)((mu8DataBuffer_1 / 10) % 10);
    mu8_temporary_ten = (U8)(mu8DataBuffer_1 % 10);
    mu8_temporary_one = mu8DataBuffer_2;


    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_display_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;


    if( bit_display_test_filter_reed_error == SET)
    {
        if( gu8_display_reed_test_step == 0 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_reed_test_step == 1 )
        {
            mu8_temporary_hundred = DISPLAY_BAR;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_reed_test_step == 2 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_BAR;
            mu8_temporary_one = DISPLAY_BAR;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_reed_test_step == 3 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_BAR;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_reed_test_step == 4 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_NUM_8;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
    }
    else
    {
        if( gu8_display_test_error == 1 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 2 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_H;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 3 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_A;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 4 )
        {
            #if 0
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_O;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;
            #endif

            /*..hui [24-8-5오후 5:56:35] TDS 센서랑 중복으로 EAO로 변경..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_A;
            mu8_temporary_one = DISPLAY_NUM_0;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 5 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_r;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 6 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_L;
            mu8_temporary_one = DISPLAY_NUM_LARGE_L;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 7 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_H;
            mu8_temporary_one = DISPLAY_NUM_LARGE_L;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 8 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_L;
            mu8_temporary_one = DISPLAY_NUM_SMALL_d;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 9 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_H;
            mu8_temporary_one = DISPLAY_NUM_SMALL_d;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 10 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_d;
            mu8_temporary_one = DISPLAY_NUM_SMALL_d;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 11 )
        {
            #if 0
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
            mu8_temporary_one = DISPLAY_NUM_SMALL_d;
            #endif

            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_t;
            mu8_temporary_one = DISPLAY_NUM_LARGE_O;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 12 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_r;
            mu8_temporary_one = DISPLAY_NUM_LARGE_O;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 13 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
            mu8_temporary_one = DISPLAY_NUM_SMALL_d;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 14 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_1;
            mu8_temporary_one = DISPLAY_NUM_LARGE_O;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 15 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
            mu8_temporary_one = DISPLAY_NUM_LARGE_O;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 16 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_C;
            mu8_temporary_one = DISPLAY_NUM_5;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 17 )
        {
            /*..hui [24-7-25오전 11:04:27] TDS 입수 온도센서..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_1;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 18 )
        {
            /*..hui [24-7-25오전 11:04:32] TDS 출수 온도센서..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_SMALL_t;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 19 )
        {
            /*..hui [24-7-25오전 11:05:40] TDS 입수 센서 - EIS..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_1;
            mu8_temporary_one = DISPLAY_NUM_5;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else if( gu8_display_test_error == 20 )
        {
            /*..hui [24-7-25오전 11:05:50] TDS 출수 센서 - EOS..*/
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = DISPLAY_NUM_0;
            mu8_temporary_one = DISPLAY_NUM_5;

            fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }
        else
        {
            if( gu8_ice_ext_test_input == 0 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_8;
                mu8_temporary_ten = DISPLAY_NUM_8;
                mu8_temporary_one = DISPLAY_NUM_8;

                fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
                gu8_left_fnd_off_timer = 0;
            }
            else
            {
                gu8_left_fnd_off_timer++;

                if( gu8_left_fnd_off_timer <= 2 )
                {
                    mu8_temporary_hundred = 0x5F;
                    mu8_temporary_ten = 0x5F;
                    mu8_temporary_one = 0x5F;
                }
                else if( gu8_left_fnd_off_timer <= 4 )
                {
                    mu8_temporary_hundred = 0x5E;
                    mu8_temporary_ten = 0x5E;
                    mu8_temporary_one = 0x5E;
                }
                else if( gu8_left_fnd_off_timer <= 6 )
                {
                    mu8_temporary_hundred = 0x5C;
                    mu8_temporary_ten = 0x5C;
                    mu8_temporary_one = 0x5C;
                }
                else if( gu8_left_fnd_off_timer <= 8 )
                {
                    mu8_temporary_hundred = 0x58;
                    mu8_temporary_ten = 0x58;
                    mu8_temporary_one = 0x58;
                }
                else if( gu8_left_fnd_off_timer <= 10 )
                {
                    mu8_temporary_hundred = 0x50;
                    mu8_temporary_ten = 0x50;
                    mu8_temporary_one = 0x50;
                }
                else if( gu8_left_fnd_off_timer <= 12 )
                {
                    mu8_temporary_hundred = 0x40;
                    mu8_temporary_ten = 0x40;
                    mu8_temporary_one = 0x40;
                }
                else
                {
                    gu8_left_fnd_off_timer = 13;

                    if( F_cds_detect == SET && F_Wink_500ms == SET )
                    {
                        mu8_temporary_hundred = 0x7F;
                        mu8_temporary_ten = 0x7F;
                        mu8_temporary_one = 0x7F;
                    }
                    else
                    {
                        mu8_temporary_hundred = 0x00;
                        mu8_temporary_ten = 0x00;
                        mu8_temporary_one = 0x00;
                    }
                }

                fnd_left_out( DIRECT_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_pba_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_hundred = DISPLAY_NUM_8;
    mu8_temporary_ten = DISPLAY_NUM_8;
    mu8_temporary_one = DISPLAY_NUM_8;

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_left_uart_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
    {
        mu8_temporary_hundred = (U8)((gu8_Tray_Flow_1sec / 100) % 10);
        mu8_temporary_ten = (U8)((gu8_Tray_Flow_1sec / 10) % 10);
        mu8_temporary_one = (U8)(gu8_Tray_Flow_1sec % 10);
    }
    else
    {
        if( gu8_factory_test_step == 1 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_t;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_E;
            mu8_temporary_one = DISPLAY_NUM_1;
        }
        else if( gu8_factory_test_step == 2 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_SMALL_t;
            mu8_temporary_ten = DISPLAY_NUM_LARGE_E;
            mu8_temporary_one = DISPLAY_NUM_2;
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }

    fnd_left_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


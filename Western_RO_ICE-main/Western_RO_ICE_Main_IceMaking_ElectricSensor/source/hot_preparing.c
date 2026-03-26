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
#include    "hot_preparing.h"

//void start_hot_preheating(void);
//void stop_hot_preheating(void);

void hot_prepare(void);
//void hot_preheating_control(void);
//void return_hot_water_select(void);
//void hot_prepare_stage(void);
//void hot_prepare_return_timer_init(void);
//void hot_extract_return(void);

U8 gu8_hot_prepare_mode;

bit bit_hot_preheating_start;
U8 gu8_preheating_set_temp;

U8 gu8_hot_prepare_stage;

U8 gu8_hot_prepare_no_select_timer;

U8 gu8_95_degree_preparing_temp;
U8 gu8_85_degree_preparing_temp;
U8 gu8_77_degree_preparing_temp;
U8 gu8_43_degree_preparing_temp;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void start_hot_preheating(void)
{
    ///#if 0
    /*BuzStep(BUZZER_SETUP);*/
    BuzStep(BUZZER_SELECT);

    /*BuzStep(BUZZER_ERROR);*/
    bit_hot_preheating_start = SET;
    gu8_preheating_set_temp = gu8_hot_setting_temperature;
    gu8_Fahrenheit_temp_old = 0;
    gu8_Celcius_temp_old = 0;
    ///#endif

    gu8_hot_prepare_stage = HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON;
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void stop_hot_preheating(void)
{
    ///#if 0
    bit_hot_preheating_start = CLEAR;
    /*gu8_preheating_set_temp = 0;*/
    gu8_Fahrenheit_temp_old = 0;
    gu8_Celcius_temp_old = 0;
    ///#endif

    /*gu8_hot_prepare_stage = HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON;*/
    gu8_hot_prepare_stage = HOT_PREPARE_STAGE_0_INIT;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_prepare(void)
{
    /*..hui [24-11-25오후 2:35:40] 고도모드에 따른 프리페어링 LED 표시 온도 변경..*/
    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        gu8_95_degree_preparing_temp = HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1;
        gu8_85_degree_preparing_temp = HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_1;
        gu8_77_degree_preparing_temp = HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_1;
        gu8_43_degree_preparing_temp = HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_1;
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        gu8_95_degree_preparing_temp = HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_2;
        gu8_85_degree_preparing_temp = HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_2;
        gu8_77_degree_preparing_temp = HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_2;
        gu8_43_degree_preparing_temp = HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_2;
    }
    else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
    {
        gu8_95_degree_preparing_temp = HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_3;
        gu8_85_degree_preparing_temp = HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_3;
        gu8_77_degree_preparing_temp = HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_3;
        gu8_43_degree_preparing_temp = HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_3;
    }
    else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
    {
        gu8_95_degree_preparing_temp = HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_4;
        gu8_85_degree_preparing_temp = HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_4;
        gu8_77_degree_preparing_temp = HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_4;
        gu8_43_degree_preparing_temp = HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_4;
    }

    if( u8WaterOutState == HOT_WATER_SELECT )/////|| bit_hot_preheating_start == SET )
    {
        if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
            || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
            || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT ) )
        {
            /*..hui [24-2-20오후 4:53:35] 온수 온도센서 에러 발생했을때는 프리페어링 무조건 ON..*/
            /*..hui [24-2-20오후 4:53:49] 나머지 에러, 온수 OFF등은 온도 조건에 따라....*/
            gu8_hot_prepare_mode = HOT_PREPARE_MODE_ON;
        }
        else
        {
            if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
            {
                if( gu8_Hot_Tank_Temperature_One_Degree < gu8_95_degree_preparing_temp )
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_ON;
                }
                else
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_OFF;
                }
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
            {
                if( gu8_Hot_Tank_Temperature_One_Degree < gu8_85_degree_preparing_temp )
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_ON;
                }
                else
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_OFF;
                }

            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
            {
                if( gu8_Hot_Tank_Temperature_One_Degree < gu8_77_degree_preparing_temp )
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_ON;
                }
                else
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_OFF;
                }
            }
            else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
            {
                if( gu8_Hot_Tank_Temperature_One_Degree < gu8_43_degree_preparing_temp )
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_ON;
                }
                else
                {
                    gu8_hot_prepare_mode = HOT_PREPARE_MODE_OFF;
                }
            }
        }
    }
    else
    {
        gu8_hot_prepare_mode = HOT_PREPARE_MODE_OFF;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_preheating_control(void)
{
    U8 mu8_finish = 0;

    if( bit_hot_preheating_start == SET )
    {
        if( gu8_preheating_set_temp == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_PREPARING_TEMP_200_oF_95_oC__ALTITUDE_1 )
            {
                mu8_finish = SET;
            }
            else{}
        }
        else if( gu8_preheating_set_temp == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_PREPARING_TEMP_185_oF_85_oC__ALTITUDE_1 )
            {
                mu8_finish = SET;
            }
            else{}
        }
        else if( gu8_preheating_set_temp == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_PREPARING_TEMP_170_oF_77_oC__ALTITUDE_1 )
            {
                mu8_finish = SET;
            }
            else{}
        }
        else /*if( gu8_preheating_set_temp == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
            if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_PREPARING_TEMP_110_oF_43_oC__ALTITUDE_1 )
            {
                mu8_finish = SET;
            }
            else{}
        }

        if( mu8_finish == SET )
        {
            BuzStep(BUZZER_SETUP);
            stop_hot_preheating();
        }
        else{}
    }
    else
    {
        /*gu8_preheating_set_temp = 0;*/
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void return_hot_water_select(void)
{
    if( F_All_Lock == SET && F_Child_Lock == SET )
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    /*..hui [19-10-7오후 3:24:23] 팝업 노출 순위 뒤로..*/
    if(F_Hot_Lock == SET)
    {
        start_hot_lock_flick();
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    gu16_water_select_return_time = 0;

    if(u8WaterOutState != HOT_WATER_SELECT)
    {
        u8WaterOutState = HOT_WATER_SELECT;

        /*..hui [23-7-27오후 3:39:23] 온수로 자동으로 돌아가고 0.5초 동안 추출 금지 추가..*/
        F_WaterOut_Disable_State = SET;
    }
    else{}

    /*..hui [23-5-30오후 2:44:23] 프리히팅한 온도로 복귀..*/
    gu8_hot_setting_temperature = gu8_preheating_set_temp;
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_prepare_stage(void)
{
    if( bit_hot_preheating_start == CLEAR )
    {
        gu8_hot_prepare_no_select_timer = 0;
        return;
    }
    else{}

    if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON
        || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING
        || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_3_HOT_KEY_SETTING
        || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_4_HOT_EXTRACT )
    {
        gu16_water_select_return_time = 0;
    }
    else
    {
        if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_5_HOT_EXTRACT_FINISH )
        {
            if( u8WaterOutState != HOT_WATER_SELECT )
            {
                stop_hot_preheating();
            }
            else{}
        }
        else{}
    }

    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON
            || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_3_HOT_KEY_SETTING  )
        {
            gu8_hot_prepare_no_select_timer++;

            if( gu8_hot_prepare_no_select_timer >= 70 )
            {
                gu8_hot_prepare_no_select_timer = 0;
                gu8_hot_prepare_stage = HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING;

                /*..hui [23-7-24오전 11:12:07] 다시 프리히팅 하던 온도로 복귀..*/
                gu8_hot_setting_temperature = gu8_preheating_set_temp;
            }
            else{}
        }
        else if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING  )
        {
            gu8_hot_prepare_no_select_timer = 0;
            hot_preheating_control();
        }
        else
        {
            gu8_hot_prepare_no_select_timer = 0;
        }
    }
    else
    {
        if( F_WaterOut == CLEAR )
        {
            if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_1_CURRENT_TEMP_ON
                || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING
                || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_3_HOT_KEY_SETTING
                || gu8_hot_prepare_stage == HOT_PREPARE_STAGE_4_HOT_EXTRACT )
            {
                gu8_hot_prepare_no_select_timer++;

                if( gu8_hot_prepare_no_select_timer >= 70 )
                {
                    gu8_hot_prepare_no_select_timer = 0;
                    gu8_hot_prepare_stage = HOT_PREPARE_STAGE_2_CURRENT_TEMP_DIMMING;

                    return_hot_water_select();
                }
                else{}
            }
            else
            {
                gu8_hot_prepare_no_select_timer = 0;
            }
        }
        else
        {
            gu8_hot_prepare_stage = HOT_PREPARE_STAGE_6_PREPARE_FINISH;
            gu8_hot_prepare_no_select_timer = 0;
        }

        /*..hui [23-7-26오후 1:53:30] 예열 -> 냉/정버튼 -> 추출 -> 추출종료 -> 이후 알람음 울려줘야함....*/
        if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_6_PREPARE_FINISH  )
        {
            hot_preheating_control();
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_prepare_return_timer_init(void)
{

    gu8_hot_prepare_no_select_timer = 0;


}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_extract_return(void)
{
    if( gu8_hot_prepare_stage == HOT_PREPARE_STAGE_4_HOT_EXTRACT )
    {
        gu8_hot_prepare_stage = HOT_PREPARE_STAGE_5_HOT_EXTRACT_FINISH;
    }
    else{}
}
#endif



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


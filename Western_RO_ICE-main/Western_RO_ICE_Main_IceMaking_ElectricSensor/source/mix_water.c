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
#include    "mix_water.h"

void calc_mix_water(void);
void calc_hot_85_degree_mix_water(void);
void calc_hot_77_degree_mix_water(void);
void open_cold_valve(void);
void calc_room_mix_water(void);
void open_hot_valve(void);
void Pure_Temp_Compensation_time_Cold_Big( void );
void Pure_Temp_Compensation_time_Hot_Big( void );

void Hot_Temp_Compensation_time( void );
void Hot_Temp_45_Degree_Compensation_time_Hot_Big( void );
void Hot_Temp_45_Degree_Compensation_time_Cold_Big( void );

void calc_hot_43_degree_mix_water( void );
void check_hot_not_use(void);
void check_hot_95_temp_use(void);
void check_hot_85_95_temp_use(void);
void check_hot_fast_dec(void);





U16 gu16_water_out_time;
U16 gu16_hot_mix_time;
bit bit_open_hot_valve;
bit bit_first_room_open;
U8 gu8_room_open_timer;
U16 gu16_hot_open_timer;
U16 g16_extract_decrease_time;
U16 g16_extract_increase_time;

U8 g8_aaaa;

U16 gu16_cold_mix_time;
bit bit_open_cold_valve;
U16 gu16_cold_open_timer;

bit bit_first_open_room_valve_pure;
bit bit_first_open_room_valve_hot;


bit bit_big_mode;


U8 gu8_room_mix_abnormal_mode;


U16 gu16_devide_extract_timer;

U16 gu16_devide_total_time;
U16 gu16_devide_mix_time;
U8 gu8_devide_odd_time;
U8 gu8_devide_count;


U8 gu8_test_test;
U8 gu8_test_conv;

U16 gu16_cold_devide_extract_timer;
U16 gu16_cold_devide_total_time;
U16 gu16_cold_devide_mix_time;
U8 gu8_cold_devide_count;

U8 gu8_cold_mix_start_time;

bit bit_hot_long_not_use_state;
U16 gu16_hot_not_use_timer;


bit bit_95_degree_use_state;
U16 gu16_95_degree_use_timer;
U8 gu8_95_degree_extract_timer;

bit bit_85_95_degree_use_state;
U16 gu16_85_95_degree_use_timer;
U8 gu8_85_95_degree_extract_timer;

U16 gu16_hot_fast_dec_timer;
bit bit_hot_fast_dec;
U8 gu8_hot_temp_before;
U8 gu8_hot_temp_before_2;
U8 gu8_hot_dec_clear_cnt;
U16 gu16_dec_finish_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_mix_water(void)
{
    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            calc_hot_85_degree_mix_water();
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
        {
            calc_hot_77_degree_mix_water();
        }
        else if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )
        {
            calc_hot_43_degree_mix_water();
        }
    }
    else if( u8WaterOutState == PURE_WATER_SELECT )
    {
        calc_room_mix_water();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_hot_85_degree_mix_water(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_time = 0;
    U16 mu16_max_time = 0;

    /*..hui [24-11-25오후 3:21:26] 고도모드 3단, 4단 설정 시 믹싱 제어 안함..*/
    /*..hui [24-11-25오후 3:22:01] 3단 설정시 설정온도 86/80이므로 85도 제어할 필요없음..*/
    if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    /*..hui [24-11-25오후 3:22:25] 4단 설정시 설정온도 79/73이므로 77도 제어할 필요없음..*/
    if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_HOT_85_TEMP - 3) )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    /*if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_85_TEMP + 3) )*/
    if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_85_TEMP + 1) )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 83 )
        {
            /*..hui [24-3-29오전 11:07:37] 고온 추출 후 85도 추출할때 강제로 0.3초 냉수 섞음..*/
            /*..hui [24-3-29오전 11:07:53] 온수 95도 240ml -> 120ml -> 85도 추출하면 89~이상나옴..*/
            /*..hui [24-3-29오전 11:08:07] 온수탱크에 냉수 층이 생겨서 발생하는 문제.....*/
            if( bit_95_degree_use_state == SET )
            {
                gu16_cold_mix_time = 3;
            }
            else
            {
                gu16_cold_mix_time = 0;
            }
        }
        else
        {
            gu16_cold_mix_time = 0;
        }

        return;
    }
    else{}

    mu8_b = TARGET_HOT_85_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_a = gu8_Hot_Tank_Temperature_One_Degree - TARGET_HOT_85_TEMP;

    f32_c = (F32)((F32)mu8_b / mu8_a);
    /*f32_c = (F32)(f32_c * 2.0f);*/
    /*2_c = (F32)(f32_c * 1.6f);*/

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        /*f32_c = (F32)(f32_c * 1.6f);*/
        /*f32_c = (F32)(f32_c * 1.8f);*/
        f32_c = (F32)(f32_c * 1.7f);

        /*..hui [23-11-27오전 9:30:14] 1시간 방치 조건 추가..*/
        if( bit_hot_long_not_use_state == SET )
        {
            /*..hui [24-3-29오전 9:32:40] 곱하는 숫자 커질수록 냉수 적게 섞음..*/
            /*..hui [24-3-29오전 9:32:55] 1시간 방치후에는 냉수 최대한 적게..*/
            f32_c = (F32)(f32_c * 1.6f);
        }
        else if( bit_95_degree_use_state == SET )
        {
            /*..hui [24-3-29오전 11:37:29] 직전에 온수 95도 추출했을때.. 냉수 더 넣어줘야함.. 층이생김..*/
            f32_c = (F32)(f32_c / 1.7f);
        }
        else if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            /*f32_c = (F32)(f32_c * 1.4f);*/
            f32_c = (F32)(f32_c * 1.5f);
        }
        /*else if( gu8_Mixing_Out_Temperature_One_Degree <= 70 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )*/
        else if( gu8_Mixing_Out_Temperature_One_Degree <= 60 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            /*f32_c = (F32)(f32_c * 1.3f);*/
            f32_c = (F32)(f32_c * 1.1f);
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        f32_c = (F32)(f32_c * 1.6f);
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        f32_c = (F32)(f32_c * 1.6f);
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        f32_c = (F32)(f32_c * 2.0f);
    }
    else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
    {
        f32_c = (F32)(f32_c * 2.0f);
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        /*f32_c = (F32)(f32_c * 2.0f);*/
        /*f32_c = 0;*/
        f32_c = (F32)(f32_c * 2.5f);
    }
    else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
    {
        /*f32_c = (F32)(f32_c * 2.0f);*/
        /*f32_c = 0;*/
        f32_c = (F32)(f32_c * 3.0f);
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        /*f32_c = (F32)(f32_c * 2.0f);*/
        /*f32_c = 0;*/
        f32_c = (F32)(f32_c * 3.5f);
    }
    else
    {
        f32_c = (F32)(f32_c * 1.6f);
    }

    if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
    {
        f32_c = (F32)(f32_c * 1.5f);
    }
    else{}

    if( f32_c < 1.0f )
    {
        f32_c = 1.0f;
    }
    else{}

    f32_time = (F32)((F32)gu16_water_out_time / f32_c);

    gu16_cold_mix_time = (U16)f32_time;

    mu16_max_time = gu16_water_out_time;

    if( gu16_cold_mix_time >= mu16_max_time )
    {
        gu16_cold_mix_time = mu16_max_time;
    }
    else{}

    if( gu16_cold_mix_time <= 2 )
    {
        gu16_cold_mix_time = 0;
    }
    else
    {
        if(u8Extract_Continue != SET)
        {
            Hot_Temp_Compensation_time();
        }
        else{}
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_hot_77_degree_mix_water(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_time = 0;
    U16 mu16_max_time = 0;

    /*..hui [24-11-25오후 3:22:25] 4단 설정시 설정온도 79/73이므로 77도 제어할 필요없음..*/
    if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_HOT_77_TEMP - 3) )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    /*if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_77_TEMP + 3) )*/
    if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_77_TEMP + 1) )
    {
        /*gu16_cold_mix_time = 0;*/

        if( gu8_Hot_Tank_Temperature_One_Degree >= 73 )
        {
            /*..hui [24-3-29오전 11:07:37] 고온 추출 후 85도 추출할때 강제로 0.3초 냉수 섞음..*/
            /*..hui [24-3-29오전 11:07:53] 온수 95도 240ml -> 120ml -> 85도 추출하면 89~이상나옴..*/
            /*..hui [24-3-29오전 11:08:07] 온수탱크에 냉수 층이 생겨서 발생하는 문제.....*/
            if( bit_85_95_degree_use_state == SET || bit_hot_fast_dec == SET )
            {
                gu16_cold_mix_time = 5;
            }
            else
            {
                gu16_cold_mix_time = 0;
            }
        }
        else
        {
            gu16_cold_mix_time = 0;
        }

        return;
    }
    else{}

    mu8_b = TARGET_HOT_77_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_a = gu8_Hot_Tank_Temperature_One_Degree - TARGET_HOT_77_TEMP;

    f32_c = (F32)((F32)mu8_b / mu8_a);

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        /*f32_c = (F32)(f32_c * 1.9f);*/
        /*f32_c = (F32)(f32_c * 2.0f);*/
        /*f32_c = (F32)(f32_c * 2.1f);*/
        /*..hui [24-3-8오후 2:04:20] 작게할수록 냉수 많이섞음..*/
        /*f32_c = (F32)(f32_c * 2.1f);*/
        /*..hui [24-3-14오전 9:03:01] 실험결과 수정.. 양선웅님..*/
        f32_c = (F32)(f32_c * 1.9f);

        /*..hui [23-11-27오전 9:35:01] 온수 1시간 방치 조건 추가..*/
        if( bit_hot_long_not_use_state == SET )
        {
            f32_c = (F32)(f32_c * 1.4f);
        }
        else if( gu8_Cold_Temperature_One_Degree  >= 25 )
        {
            f32_c = (F32)(f32_c * 1.3f);
        }
        else if( gu8_Cold_Temperature_One_Degree  >= 15 )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else if( bit_85_95_degree_use_state == SET || bit_hot_fast_dec == SET )
        {
            /*..hui [24-3-29오전 11:37:29] 직전에 온수 95도 추출했을때.. 냉수 더 넣어줘야함.. 층이생김..*/
            f32_c = (F32)(f32_c / 1.3f);
        }
        else if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        f32_c = (F32)(f32_c * 1.9f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.4f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        f32_c = (F32)(f32_c * 2.2f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        f32_c = (F32)(f32_c * 2.5f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
    {
        f32_c = (F32)(f32_c * 2.7f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        f32_c = (F32)(f32_c * 2.9f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }
    else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
    {
        f32_c = (F32)(f32_c * 2.9f);
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        f32_c = (F32)(f32_c * 2.9f);
    }
    else
    {
        f32_c = (F32)(f32_c * 1.9f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 40 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }


    #if 0
    if( gu8_Mixing_Out_Temperature_One_Degree <= 25 )
    {
        f32_c = (F32)(f32_c * 1.7f);
    }
    else
    {
        f32_c = (F32)(f32_c * 1.9f);
    }
    #endif

    #if 0
    if( gu8_Mixing_Out_Temperature_One_Degree <= 40 )
    {
        f32_c = (F32)(f32_c * 1.4f);
    }
    else{}
    #endif

    if( f32_c < 1.0f )
    {
        f32_c = 1.0f;
    }
    else{}


    f32_time = (F32)((F32)gu16_water_out_time / f32_c);

    gu16_cold_mix_time = (U16)f32_time;

    mu16_max_time = gu16_water_out_time;

    if( gu16_cold_mix_time >= mu16_max_time )
    {
        gu16_cold_mix_time = mu16_max_time;
    }
    else{}

    if( gu16_cold_mix_time <= 2 )
    {
        gu16_cold_mix_time = 0;
    }
    else
    {
        if(u8Extract_Continue != SET)
        {
            Hot_Temp_Compensation_time();
        }
        else{}
    }

    /*Hot_Temp_Compensation_time();*/

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void open_cold_valve(void)
{
    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
        || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
        || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
        || Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
        /////|| gu16_cold_mix_time <= 2 )
    {
        bit_open_cold_valve = CLEAR;
        bit_first_open_room_valve_hot = CLEAR;
        gu16_cold_mix_time = 0;

        gu16_cold_devide_extract_timer = 0;
        gu16_cold_devide_total_time = 0;
        gu16_cold_devide_mix_time = 0;
        gu8_cold_devide_count = 0;
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC
                || gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC
                || gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )
            {
                if( gu8Cup_level == CUP_LEVEL__CONTINUE )
                {
                    gu16_cold_devide_total_time = u16Efluent_Time / 5;
                    gu16_cold_devide_mix_time = gu16_cold_mix_time / 5;

                    if( gu16_cold_mix_time >= 20 && gu16_cold_mix_time <= u16Efluent_Time - 30 )
                    {
                        gu16_cold_devide_extract_timer++;

                        if( gu16Water_Extract_Timer >= COLD_MIX_START_TIME )
                        {
                            gu16_cold_open_timer++;

                            /*if( gu16_hot_open_timer >= gu16_hot_mix_time )*/
                            /*..hui [23-10-19오후 5:06:53] 믹싱타임이 홀수인경우 1 더해줌..*/
                            if( gu16_cold_open_timer >= gu16_cold_devide_mix_time )
                            {
                                gu16_cold_open_timer = gu16_cold_devide_mix_time;
                                bit_open_cold_valve = CLEAR;
                            }
                            else
                            {
                                bit_open_cold_valve = SET;
                            }

                            /*if( gu16Water_Extract_Timer >= gu16_cold_devide_total_time )*/
                            if( gu16_cold_devide_extract_timer >= gu16_cold_devide_total_time )
                            {
                                gu16_cold_devide_extract_timer = 0;

                                gu8_cold_devide_count++;

                                if( gu8_cold_devide_count <= 1 )
                                {
                                    gu16_cold_open_timer = 0;
                                }
                                else if( gu8_cold_devide_count == 2 )
                                {
                                    gu16_cold_open_timer = 0;
                                }
                                else if( gu8_cold_devide_count == 3 )
                                {
                                    gu16_cold_open_timer = 0;
                                }
                                else if( gu8_cold_devide_count == 4 )
                                {
                                    gu16_cold_open_timer = 0;
                                }
                                else
                                {
                                    gu8_cold_devide_count = 5;
                                }
                            }
                            else{}
                        }
                        else{}
                    }

                }
                else
                {
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC
                        && gu8_Cold_Temperature_One_Degree >= 15
                        && gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
                    {
                        gu8_cold_mix_start_time = 5;
                    }
                    else
                    {
                        gu8_cold_mix_start_time = COLD_MIX_START_TIME;
                    }


                    /*if( gu16Water_Extract_Timer >= COLD_MIX_START_TIME )*/
                    if( gu16Water_Extract_Timer >= gu8_cold_mix_start_time )
                    {
                        gu16_cold_open_timer++;

                        if( gu16_cold_open_timer >= gu16_cold_mix_time )
                        {
                            gu16_cold_open_timer = gu16_cold_mix_time;
                            bit_open_cold_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_cold_valve = SET;
                        }
                    }
                    else{}
                }
            }
            else
            {
                bit_open_cold_valve = CLEAR;
                gu16_cold_open_timer = 0;

                gu16_cold_devide_extract_timer = 0;
                gu16_cold_devide_total_time = 0;
                gu16_cold_devide_mix_time = 0;
                gu8_cold_devide_count = 0;
            }


            /*..hui [23-7-17오전 10:19:59] 첫 온수 추출할때 정수쪽 에어뺴기..*/
            if( bit_first_room_open == CLEAR )
            {
                if( gu16Water_Extract_Timer >= 20 )
                {
                    gu8_room_open_timer++;

                    if( gu8_room_open_timer >= 10 )
                    {
                        gu8_room_open_timer = 10;
                        bit_first_open_room_valve_hot = CLEAR;
                        bit_first_room_open = SET;
                    }
                    else
                    {
                        bit_first_open_room_valve_hot = SET;
                    }
                }
                else
                {
                    bit_first_open_room_valve_hot = CLEAR;
                    gu8_room_open_timer = 0;
                }
            }
            else
            {
                bit_first_open_room_valve_hot = CLEAR;
            }
        }
        else
        {
            bit_open_cold_valve = CLEAR;
            bit_first_open_room_valve_hot = CLEAR;
            gu16_cold_open_timer = 0;

            gu16_cold_devide_extract_timer = 0;
            gu16_cold_devide_total_time = 0;
            gu16_cold_devide_mix_time = 0;
            gu8_cold_devide_count = 0;
        }
    }
    else
    {
        bit_open_cold_valve = CLEAR;
        bit_first_open_room_valve_hot = CLEAR;
        gu16_cold_open_timer = 0;

        gu16_cold_devide_extract_timer = 0;
        gu16_cold_devide_total_time = 0;
        gu16_cold_devide_mix_time = 0;
        gu8_cold_devide_count = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_room_mix_water(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_time = 0;
    U16 mu16_max_time = 0;
    U8 mu8_conv = 0;

    if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_ROOM_27_TEMP - 3) )
    {
        gu16_hot_mix_time = 0;
        gu8_room_mix_abnormal_mode = MIX_COLD_TEMP_ABNORMAL_HIGH;
        return;
    }
    else{}

    if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_ROOM_27_TEMP + 3) )
    {
        gu16_hot_mix_time = 0;
        /*..hui [23-10-16오후 1:52:17] 온수로만 추출할때는 온수 추출시간으로 변경..*/
        /*..hui [24-1-12오후 5:15:13] 연속 선택 후 추출하면 4oz 추출되는 현상.. 큰일날뻔~~~..*/
        if(u8Extract_Continue != SET)
        {
            effluent_time_hot_normal();
        }
        else{}
        gu8_room_mix_abnormal_mode = MIX_HOT_TEMP_ABNORMAL_LOW;
        return;
    }
    else{}

    gu8_room_mix_abnormal_mode = MIX_ALL_NORMAL;

    /*..hui [23-7-11오후 3:15:47] 정수온도 기준은 25~30도임..*/
    mu8_a = TARGET_ROOM_27_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_b = gu8_Hot_Tank_Temperature_One_Degree - TARGET_ROOM_27_TEMP;

    //if( mu8_a <= mu8_b && mu8_a + 7 <= mu8_b )

    if( mu8_a <= mu8_b && mu8_a + 15 >= mu8_b )
    {
        mu8_conv = 1;
        gu8_test_conv = 1;
    }
    else
    {
        gu8_test_conv = 0;
    }

    if( mu8_a <= mu8_b && mu8_conv == 0 )
    {
        bit_big_mode = COLD__BIG;

        f32_c = (F32)((F32)mu8_b / mu8_a);

        if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 60 )
            {
                //f32_c = (F32)(f32_c / 2.3f);
                //f32_c = (F32)(f32_c / 2.1f);
                f32_c = (F32)(f32_c / 2.4f);
            }
            else if( gu8_Cold_Temperature_One_Degree >= 15 )
            {
                //f32_c = (F32)(f32_c / 2.3f);
                //f32_c = (F32)(f32_c / 2.1f);
                f32_c = (F32)(f32_c / 2.5f);
            }
            else if( gu8_Cold_Temperature_One_Degree >= 10 && gu8_Hot_Tank_Temperature_One_Degree >= 80 )
            {
                f32_c = (F32)(f32_c / 2.3f);
            }
            else if( gu8_Mixing_Out_Temperature_One_Degree >= 70 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
            {
                f32_c = (F32)(f32_c / 1.8f);
            }
            else
            {
                //f32_c = (F32)(f32_c / 2.1f);
                f32_c = (F32)(f32_c / 2.0f);
            }

            /*..hui [23-11-29오전 11:27:35] 1시간 이상 미사용시..*/
            /*..hui [23-12-1오후 5:12:47] 온수를 더 넣어줘야함?..*/
            if( bit_hot_long_not_use_state == SET )
            {
                f32_c = (F32)(f32_c / 1.1f);
            }
            else if( bit_hot_fast_dec == SET )
            {
                f32_c = (F32)(f32_c * 1.1f);
            }
            else{}
        }
        else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
        {
            /*f32_c = (F32)(f32_c / 2.1f);*/
            f32_c = (F32)(f32_c / 2.0f);
        }
        else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
        {
            /*f32_c = (F32)(f32_c / 2.0f);*/
            f32_c = (F32)(f32_c / 1.9f);
        }
        else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
        {
            /*f32_c = (F32)(f32_c / 1.9f);*/
            /*..hui [24-2-28오전 11:13:50] 높아질수록 온도 올라감..*/
            f32_c = (F32)(f32_c / 2.0f);
        }
        else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
        {
            /*f32_c = (F32)(f32_c / 1.8f);*/
            f32_c = (F32)(f32_c / 1.9f);
        }
        else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
        {
            /*f32_c = (F32)(f32_c / 1.8f);*/
            f32_c = (F32)(f32_c / 1.9f);
        }
        else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
        {
            /*f32_c = (F32)(f32_c / 1.7f);*/
            f32_c = (F32)(f32_c / 1.8f);
        }
        else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
        {
            f32_c = (F32)(f32_c / 1.7f);
        }
        else if( gu8Cup_level == CUP_LEVEL__CONTINUE )
        {
            /*f32_c = (F32)(f32_c / 1.7f);*/
            f32_c = (F32)(f32_c / 1.9f);
        }
    }
    else
    {
        /*..hui [24-3-29오후 5:23:47] 온수를 계속열고 냉수를 조절..*/
        bit_big_mode = HOT__BIG;
        f32_c = (F32)((F32)mu8_a / mu8_b);

        if( gu8_test_conv == 0 )
        {
            ///f32_c = (F32)(f32_c * 2.5f);
            //f32_c = (F32)(f32_c * 2.8f);
            //f32_c = (F32)(f32_c * 2.7f);
            /*f32_c = (F32)(f32_c * 2.7f);*/
            f32_c = (F32)(f32_c * 2.5f);
        }
        else
        {
            /*f32_c = (F32)(f32_c * 3.3f);*/
            f32_c = (F32)(f32_c * 3.2f);
        }

        if( bit_hot_fast_dec == SET )
        {
            f32_c = (F32)(f32_c / 1.2f);
        }
        else{}

        if(u8Extract_Continue != SET)
        {
            effluent_time_hot_normal();
            gu16_water_out_time = u16Efluent_Time;
        }
        else{}
    }

    if( f32_c < 1.0f )
    {
        f32_c = 1.0f;
    }
    else{}

    if( bit_big_mode == COLD__BIG )
    {
        f32_time = (F32)((F32)gu16_water_out_time / f32_c);

        gu16_hot_mix_time = (U16)f32_time;

        mu16_max_time = gu16_water_out_time;

        if( gu16_hot_mix_time >= mu16_max_time )
        {
            gu16_hot_mix_time = mu16_max_time;
        }
        else{}

        if(u8Extract_Continue != SET)
        {
            Pure_Temp_Compensation_time_Cold_Big();
        }
        else{}
    }
    else /*if( bit_big_mode == HOT__BIG )*/
    {
        f32_time = (F32)((F32)gu16_water_out_time / f32_c);

        gu16_hot_mix_time = (U16)f32_time;

        mu16_max_time = gu16_water_out_time;

        if( gu16_hot_mix_time >= mu16_max_time )
        {
            gu16_hot_mix_time = mu16_max_time;
        }
        else{}

        if(u8Extract_Continue != SET)
        {
            Pure_Temp_Compensation_time_Hot_Big();
        }
        else{}
    }

}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void open_hot_valve(void)
{
    U8 mu8_odd = 0;
    U8 mu8_devide_max = 0;

    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
        || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
        || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
        || Bit14_Cold_Temp_Open_Short_Error__E44 == SET
        || gu16_hot_mix_time <= 4 )
    {
        bit_open_hot_valve = CLEAR;
        bit_first_open_room_valve_pure = CLEAR;
        gu16_hot_open_timer = 0;
        gu8_devide_count = 0;
        gu8_devide_odd_time = 0;
        gu16_devide_extract_timer = 0;
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        if( u8WaterOutState == PURE_WATER_SELECT )
        {
            /*..hui [23-10-19오후 4:14:17] 정수 475미리, 590미리만 우선 나눠서 추출..*/
            if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML
                || gu8Cup_level == CUP_LEVEL__10_OZ__295_ML
                || gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
                /*|| gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )*/
            {
                gu16_devide_total_time = u16Efluent_Time / 2;
                gu16_devide_mix_time = gu16_hot_mix_time / 2;

                /////mu8_odd

                if( gu16_hot_mix_time >= 20 && gu16_hot_mix_time <= u16Efluent_Time - 30 )
                {
                    if( gu16_hot_mix_time % 2 == 1 )
                    {
                        mu8_odd = 1;
                    }
                    else{}

                    if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
                    {
                        gu16_hot_open_timer++;

                        /*if( gu16_hot_open_timer >= gu16_hot_mix_time )*/
                        /*..hui [23-10-19오후 5:06:53] 믹싱타임이 홀수인경우 1 더해줌..*/
                        if( gu16_hot_open_timer >= gu16_devide_mix_time + gu8_devide_odd_time )
                        {
                            gu16_hot_open_timer = gu16_devide_mix_time + gu8_devide_odd_time;
                            bit_open_hot_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_hot_valve = SET;
                        }

                        if( gu16Water_Extract_Timer >= gu16_devide_total_time )
                        {
                            gu8_devide_count++;

                            if( gu8_devide_count <= 1 )
                            {
                                gu16_hot_open_timer = 0;
                                gu8_devide_odd_time = mu8_odd;
                            }
                            else
                            {
                                gu8_devide_count = 2;
                            }
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
                    {
                        gu16_hot_open_timer++;

                        if( gu16_hot_open_timer >= gu16_hot_mix_time )
                        {
                            gu16_hot_open_timer = gu16_hot_mix_time;
                            bit_open_hot_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_hot_valve = SET;
                        }
                    }
                    else{}
                }
            }
            else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML
                     || gu8Cup_level == CUP_LEVEL__16_OZ__475_ML
                     || gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
            {
                /*..hui [24-2-28오후 1:52:39] 415도 3번 나누는걸로..*/
                gu16_devide_total_time = u16Efluent_Time / 3;
                gu16_devide_mix_time = gu16_hot_mix_time / 3;

                /////mu8_odd

                if( gu16_hot_mix_time >= 20 && gu16_hot_mix_time <= u16Efluent_Time - 30 )
                {
                    if( gu16_hot_mix_time % 3 == 1 )
                    {
                        mu8_odd = 1;
                    }
                    else if( gu16_hot_mix_time % 3 == 2 )
                    {
                        mu8_odd = 2;
                    }
                    else{}

                    gu16_devide_extract_timer++;

                    if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
                    {
                        gu16_hot_open_timer++;

                        /*if( gu16_hot_open_timer >= gu16_hot_mix_time )*/
                        /*..hui [23-10-19오후 5:06:53] 믹싱타임이 홀수인경우 1 더해줌..*/
                        if( gu16_hot_open_timer >= gu16_devide_mix_time + gu8_devide_odd_time )
                        {
                            gu16_hot_open_timer = gu16_devide_mix_time + gu8_devide_odd_time;
                            bit_open_hot_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_hot_valve = SET;
                        }

                        /*if( gu16Water_Extract_Timer >= gu16_devide_total_time )*/
                        if( gu16_devide_extract_timer >= gu16_devide_total_time )
                        {
                            gu16_devide_extract_timer = 0;

                            gu8_devide_count++;

                            if( gu8_devide_count <= 1 )
                            {
                                gu16_hot_open_timer = 0;
                                gu8_devide_odd_time = 0;
                            }
                            else if( gu8_devide_count == 2 )
                            {
                                gu16_hot_open_timer = 0;
                                gu8_devide_odd_time = mu8_odd;
                            }
                            else
                            {
                                gu8_devide_count = 3;
                            }
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
                    {
                        gu16_hot_open_timer++;

                        if( gu16_hot_open_timer >= gu16_hot_mix_time )
                        {
                            gu16_hot_open_timer = gu16_hot_mix_time;
                            bit_open_hot_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_hot_valve = SET;
                        }
                    }
                    else{}
                }
            }
            else if( gu8Cup_level == CUP_LEVEL__CONTINUE )
            {
                /*gu16_devide_total_time = u16Efluent_Time / 5;*/
                /*gu16_devide_mix_time = gu16_hot_mix_time / 5;*/

                /*..hui [24-2-28오후 3:41:48] 온수 믹싱 총 시간이 10초 이하이면 5회 분할..*/
                /*..hui [24-2-28오후 3:41:54] 10초 초과이면 10회 분할..*/
                /*..hui [24-2-28오후 3:43:42] 6초 이하이면 3회 분할..*/
                if( gu16_hot_mix_time <= 60 )
                {
                    gu16_devide_total_time = u16Efluent_Time / 3;
                    gu16_devide_mix_time = gu16_hot_mix_time / 3;
                    mu8_devide_max = 0;
                }
                else if( gu16_hot_mix_time <= 120 )
                {
                    gu16_devide_total_time = u16Efluent_Time / 5;
                    gu16_devide_mix_time = gu16_hot_mix_time / 5;
                    mu8_devide_max = 1;
                }
                else
                {
                    gu16_devide_total_time = u16Efluent_Time / 10;
                    gu16_devide_mix_time = gu16_hot_mix_time / 10;
                    mu8_devide_max = 2;
                }

                /////mu8_odd

                /*if( gu16_hot_mix_time >= 20 && gu16_hot_mix_time <= u16Efluent_Time - 30 )*/
                if( gu16_hot_mix_time >= 30 && gu16_hot_mix_time <= u16Efluent_Time - 30 )
                {
                    gu16_devide_extract_timer++;

                    /*if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )*/
                    /*..hui [24-2-28오후 3:58:46] 냉수 2초 먼저 넣어주고나서부터 시작..*/
                    if( gu16Water_Extract_Timer >= 20 )
                    {
                        gu16_hot_open_timer++;

                        /*if( gu16_hot_open_timer >= gu16_hot_mix_time )*/
                        /*..hui [23-10-19오후 5:06:53] 믹싱타임이 홀수인경우 1 더해줌..*/
                        if( gu16_hot_open_timer >= gu16_devide_mix_time )
                        {
                            gu16_hot_open_timer = gu16_devide_mix_time;
                            bit_open_hot_valve = CLEAR;
                        }
                        else
                        {
                            bit_open_hot_valve = SET;
                        }

                        /*if( gu16Water_Extract_Timer >= gu16_devide_total_time )*/
                        if( gu16_devide_extract_timer >= gu16_devide_total_time )
                        {
                            gu16_devide_extract_timer = 0;

                            gu8_devide_count++;

                            if( gu8_devide_count <= 1 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 2 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 3 )
                            {
                                if( mu8_devide_max == 0 )
                                {
                                    gu8_devide_count = 3;
                                }
                                else
                                {
                                    gu16_hot_open_timer = 0;
                                }
                            }
                            else if( gu8_devide_count == 4 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 5 )
                            {
                                if( mu8_devide_max == 1 )
                                {
                                    gu8_devide_count = 5;
                                }
                                else
                                {
                                    gu16_hot_open_timer = 0;
                                }
                            }
                            else if( gu8_devide_count == 6 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 7 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 8 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else if( gu8_devide_count == 9 )
                            {
                                gu16_hot_open_timer = 0;
                            }
                            else
                            {
                                gu8_devide_count = 10;
                            }
                        }
                        else{}
                    }
                    else{}
                }
            }
            else
            {
                if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
                {
                    gu16_hot_open_timer++;

                    if( gu16_hot_open_timer >= gu16_hot_mix_time )
                    {
                        gu16_hot_open_timer = gu16_hot_mix_time;
                        bit_open_hot_valve = CLEAR;
                    }
                    else
                    {
                        bit_open_hot_valve = SET;
                    }
                }
                else{}
            }

            if( bit_first_room_open == CLEAR )
            {
                if( gu16Water_Extract_Timer >= 20 )
                {
                    gu8_room_open_timer++;

                    if( gu8_room_open_timer >= 10 )
                    {
                        gu8_room_open_timer = 10;
                        bit_first_open_room_valve_pure = CLEAR;
                        bit_first_room_open = SET;
                    }
                    else
                    {
                        bit_first_open_room_valve_pure = SET;
                    }
                }
                else
                {
                    bit_first_open_room_valve_pure = CLEAR;
                    gu8_room_open_timer = 0;
                }
            }
            else
            {
                bit_first_open_room_valve_pure = CLEAR;
            }
        }
        else
        {
            bit_open_hot_valve = CLEAR;
            bit_first_open_room_valve_pure = CLEAR;
            gu16_hot_open_timer = 0;
            gu8_devide_count = 0;
            gu8_devide_odd_time = 0;
            gu16_devide_extract_timer = 0;
        }
    }
    else
    {
        bit_open_hot_valve = CLEAR;
        bit_first_open_room_valve_pure = CLEAR;
        gu16_hot_open_timer = 0;
        gu8_devide_count = 0;
        gu8_devide_odd_time = 0;
        gu16_devide_extract_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pure_Temp_Compensation_time_Cold_Big( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;


    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        return;
    }
    else{}

    mu16_a = gu16_hot_mix_time / 10;

    mu16_final = mu16_a * 2;

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree <= 60 )
        {
            if( mu16_final >= 2 )
            {
                mu16_final = mu16_final - 2;
            }
            else{}
        }
        else
        {
            mu16_final = mu16_final + 2;
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        mu16_final = mu16_final + 2;
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        /*mu16_final = mu16_final + 5;*/
        mu16_final = mu16_final + 9;
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        mu16_final = mu16_final + 9;
    }
    else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
    {
        mu16_final = mu16_final + 12;
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        mu16_final = mu16_final + 10;
    }
    else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
    {
        mu16_final = mu16_final + 20;
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        mu16_final = mu16_final + 20;
    }
    else{}


    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    /*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    /*..hui [23-5-23오후 5:58:04] 최종.. 2초당 전체 추출시간의 1.5 percent 빼준다..*/
    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pure_Temp_Compensation_time_Hot_Big( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;


    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        return;
    }
    else{}

    /*mu16_a = gu16_hot_mix_time / 10;*/

    /*mu16_final = mu16_a * 2;*/

    if( gu8_test_conv == 0 )
    {
        /*mu16_a = (U16)(((U32)gu16_hot_mix_time * (U32)140) / 100 );*/
        /*mu16_a = (U16)(((U32)gu16_hot_mix_time * (U32)130) / 100 );*/
        mu16_a = (U16)(((U32)gu16_hot_mix_time * (U32)110) / 100 );
    }
    else
    {
        mu16_a = (U16)(((U32)gu16_hot_mix_time * (U32)120) / 100 );
    }

    mu16_final = mu16_a;

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    /*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);*/

    if( gu8_test_conv == 0 )
    {
        mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);
    }
    else
    {
        /*mu16_limit = (U16)(((U32)u16Efluent_Time * 50) / 100);*/
        mu16_limit = (U16)(((U32)u16Efluent_Time * 45) / 100);
    }

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    /*..hui [23-5-23오후 5:58:04] 최종.. 2초당 전체 추출시간의 1.5 percent 빼준다..*/
    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Hot_Temp_Compensation_time( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;


    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != HOT_WATER_SELECT )
    {
        return;
    }
    else{}

    if( gu8_hot_setting_temperature != HOT_SET_TEMP_1__110_oF_43_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_2__170_oF_77_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_3__185_oF_85_oC )
    {
        return;
    }
    else{}

    /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)140) / 100 );*/
    /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)135) / 100 );*/
    mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)130) / 100 );

    mu16_final = mu16_a;

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    /*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Hot_Temp_45_Degree_Compensation_time_Hot_Big( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;


    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != HOT_WATER_SELECT )
    {
        return;
    }
    else{}

    if( gu8_hot_setting_temperature != HOT_SET_TEMP_1__110_oF_43_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_2__170_oF_77_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_3__185_oF_85_oC )
    {
        return;
    }
    else{}


    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 90 )
        {
            /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)95) / 100 );*/
            /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)100) / 100 );*/
            /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)105) / 100 );*/
            /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)95) / 100 );*/
            /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)85) / 100 );*/
            mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)90) / 100 );
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)100) / 100 );*/
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)105) / 100 );*/
                //mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)110) / 100 );
                ///mu16_a = mu16_a + 3;
                mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)90) / 100 );

                //if( gu8_Cold_Temperature_One_Degree >= 25 )
                if( gu8_Cold_Temperature_One_Degree >= 10 )
                {
                    mu16_a = mu16_a - 2;
                }
                else{}
            }
            else
            {
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)110) / 100 );*/
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)115) / 100 );*/
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)120) / 100 );*/
                /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)110) / 100 );*/
                //mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)90) / 100 );
                mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)85) / 100 );

                if( gu8_Cold_Temperature_One_Degree >= 25 )
                {
                    if( mu16_a > 3 )
                    {
                        mu16_a = mu16_a - 3;
                    }
                    else{}
                }
                else{}
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree <= 80 )
        {
            mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)130) / 100 );
        }
        else
        {
            //mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)140) / 100 );
            //mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)130) / 100 );
            mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)120) / 100 );
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)120) / 100 );
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)130) / 100 );
    }
    else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)120) / 100 );
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)140) / 100 );
    }
    else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)130) / 100 );
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)140) / 100 );
    }
    else
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)110) / 100 );
    }


    mu16_final = mu16_a;

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    /*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);*/
    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 50) / 100);*/
    if( gu8_Hot_Tank_Temperature_One_Degree >= 90 )
    {
        if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
            && gu8_Cold_Temperature_One_Degree >= 25
            && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME )
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 45) / 100);
        }
        else if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
                 && gu8_Cold_Temperature_One_Degree >= 20
                 && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME_2 )
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 45) / 100);
        }
        else
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 50) / 100);
        }
    }
    else
    {
        if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
            && gu8_Cold_Temperature_One_Degree >= 25
            && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME )
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 45) / 100);
        }
        else if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
                 && gu8_Cold_Temperature_One_Degree >= 20
                 && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME_2 )
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 45) / 100);
        }
        else if( gu8_Cold_Temperature_One_Degree >= 15 && gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 48) / 100);
        }
        else
        {
            mu16_limit = (U16)(((U32)u16Efluent_Time * 55) / 100);
        }
    }
    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 60) / 100);*/

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Hot_Temp_45_Degree_Compensation_time_Cold_Big( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;

    #if 0
    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != HOT_WATER_SELECT )
    {
        return;
    }
    else{}

    if( gu8_hot_setting_temperature != HOT_SET_TEMP_1__110_oF_43_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_2__170_oF_77_oC
        && gu8_hot_setting_temperature != HOT_SET_TEMP_3__185_oF_85_oC )
    {
        return;
    }
    else{}

    /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)140) / 100 );*/
    /*mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)70) / 100 );*/

    #if 0
    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)78) / 100 );
    }
    else
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)70) / 100 );
    }
    #endif

    #if 0
    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        //mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)75) / 100 );
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)90) / 100 );
    }
    else
    {
        mu16_a = (U16)(((U32)gu16_cold_mix_time * (U32)75) / 100 );
    }
    #endif


    mu16_final = mu16_a;


    mu16_a = gu16_hot_mix_time / 10;

    mu16_final = mu16_a * 2;

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    /*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);*/
    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 50) / 100);*/
    mu16_limit = (U16)(((U32)u16Efluent_Time * 55) / 100);
    /*mu16_limit = (U16)(((U32)u16Efluent_Time * 60) / 100);*/

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_hot_43_degree_mix_water( void )
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_time = 0;
    U16 mu16_max_time = 0;

    if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_HOT_43_TEMP - 3) )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_43_TEMP + 3) )
    {
        gu16_cold_mix_time = 0;
        return;
    }
    else{}

    mu8_b = TARGET_HOT_43_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_a = gu8_Hot_Tank_Temperature_One_Degree - TARGET_HOT_43_TEMP;



////////////////////////////////////////////////////////////////////////////////////////
    /*bit_big_mode = HOT__BIG;*/

    #if 0
    if( gu8_Cold_Temperature_One_Degree >= 25 )
    {
        bit_big_mode = COLD__BIG;

    }
    else
    {
        bit_big_mode = HOT__BIG;

    }
    #endif

    bit_big_mode = HOT__BIG;

    f32_c = (F32)((F32)mu8_b / mu8_a);

    if( f32_c < 1.0f )
    {
        gu8_test_test = 1;
    }
    else
    {
        gu8_test_test = 2;
    }


    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        /*f32_c = (F32)(f32_c * 1.7f);*/
        if( f32_c < 1.0f )
        {
            /*f32_c = (F32)(f32_c * 2.9f);*/
            /*f32_c = (F32)(f32_c * 3.0f);*/
            /*f32_c = (F32)(f32_c * 2.8f);*/
            /*f32_c = (F32)(f32_c * 2.9f);*/
            /*f32_c = (F32)(f32_c * 3.0f);*/
            if( gu8_Hot_Tank_Temperature_One_Degree >= 94 )
            {
                //f32_c = (F32)(f32_c * 3.2f);
                //f32_c = (F32)(f32_c * 3.3f);
                //f32_c = (F32)(f32_c * 3.4f);
                //f32_c = (F32)(f32_c * 3.3f);
                //f32_c = (F32)(f32_c * 3.2f);

                if( gu8_Cold_Temperature_One_Degree < 15 )
                {
                    f32_c = (F32)(f32_c * 3.2f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 25 )
                {
                    f32_c = (F32)(f32_c * 3.3f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 30 )
                {
                    f32_c = (F32)(f32_c * 3.4f);
                }
                else
                {
                    f32_c = (F32)(f32_c * 3.2f);
                }
            }
            else if( gu8_Hot_Tank_Temperature_One_Degree >= 80 )
            {
                //f32_c = (F32)(f32_c * 3.1f);
                //f32_c = (F32)(f32_c * 3.2f);
                //f32_c = (F32)(f32_c * 3.1f);
                //f32_c = (F32)(f32_c * 3.0f);
                //f32_c = (F32)(f32_c * 2.9f);
                if( gu8_Cold_Temperature_One_Degree < 10 )
                {
                    f32_c = (F32)(f32_c * 2.7f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 15 )
                {
                    f32_c = (F32)(f32_c * 2.9f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 25 )
                {
                    f32_c = (F32)(f32_c * 3.1f);
                }
                else
                {
                    f32_c = (F32)(f32_c * 3.2f);
                }
            }
            else
            {
                /*f32_c = (F32)(f32_c * 3.0f);*/
                /*f32_c = (F32)(f32_c * 2.9f);*/
                //f32_c = (F32)(f32_c * 3.0f);
                //f32_c = (F32)(f32_c * 2.9f);
                //f32_c = (F32)(f32_c * 2.8f);
                //f32_c = (F32)(f32_c * 2.7f);

                if( gu8_Cold_Temperature_One_Degree < 15 )
                {
                    //f32_c = (F32)(f32_c * 2.7f);
                    f32_c = (F32)(f32_c * 2.5f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 25 )
                {
                    f32_c = (F32)(f32_c * 2.9f);
                }
                else
                {
                    f32_c = (F32)(f32_c * 2.9f);
                }
            }
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 60 )
            {
                ////f32_c = (F32)(f32_c * 2.1f);
                f32_c = (F32)(f32_c * 1.8f);
            }
            else if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                //f32_c = (F32)(f32_c * 2.2f);
                /*f32_c = (F32)(f32_c * 2.3f);*/
                /*f32_c = (F32)(f32_c * 2.4f);*/
                /*f32_c = (F32)(f32_c * 2.5f);*/
                /*f32_c = (F32)(f32_c * 2.4f);*/
                //f32_c = (F32)(f32_c * 2.3f);
                //f32_c = (F32)(f32_c * 2.2f);

                if( gu8_Cold_Temperature_One_Degree < 15 )
                {
                    /////f32_c = (F32)(f32_c * 2.2f);
                    f32_c = (F32)(f32_c * 2.0f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 25 )
                {
                    ///f32_c = (F32)(f32_c * 2.5f);
                    f32_c = (F32)(f32_c * 2.3f);
                }
                else
                {
                    /////f32_c = (F32)(f32_c * 2.7f);
                    f32_c = (F32)(f32_c * 2.5f);
                }


            }
            else
            {
                /*f32_c = (F32)(f32_c * 2.5f);*/
                /*f32_c = (F32)(f32_c * 2.7f);*/
                //f32_c = (F32)(f32_c * 2.7f);
                /*f32_c = (F32)(f32_c * 2.2f);*/
                //f32_c = (F32)(f32_c * 2.5f);
                if( gu8_Cold_Temperature_One_Degree < 15 )
                {
                    ////f32_c = (F32)(f32_c * 2.6f);
                    f32_c = (F32)(f32_c * 2.4f);
                }
                else if( gu8_Cold_Temperature_One_Degree < 25 )
                {
                    /////f32_c = (F32)(f32_c * 2.9f);
                    f32_c = (F32)(f32_c * 2.7f);
                }
                else
                {
                    /////f32_c = (F32)(f32_c * 3.1f);
                    f32_c = (F32)(f32_c * 2.9f);
                }
            }
        }

        /*..hui [23-11-24오후 2:24:06] 43도 첫 잔 추출시 53도 나오는 현상.. 삭제..*/
        /*if( gu8_Mixing_Out_Temperature_One_Degree <= 30 )*/
        if( bit_hot_long_not_use_state == SET )
        {
            f32_c = (F32)(f32_c * 1.1f);
        }
        else if( gu8_Mixing_Out_Temperature_One_Degree <= 30 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            /*f32_c = (F32)(f32_c * 1.7f);*/
            /*f32_c = (F32)(f32_c * 1.1f);*/
            f32_c = (F32)(f32_c * 1.1f);
        }
        else if( gu8_Mixing_Out_Temperature_One_Degree >= 80 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            /*..hui [23-11-30오후 4:27:58] 고온 추출후에 43도 추출했을때..*/
            f32_c = (F32)(f32_c / 1.1f);
        }
        else{}

    }
    else if( gu8Cup_level == CUP_LEVEL__6_OZ__175_ML )
    {
        ///////f32_c = (F32)(f32_c * 4.0f);

        if( f32_c < 1.0f )
        {
            if( gu8_Cold_Temperature_One_Degree >= 15 )
            {
                f32_c = (F32)(f32_c * 3.5f);
            }
            else if( gu8_Hot_Tank_Temperature_One_Degree >= 90 )
            {
                ///f32_c = (F32)(f32_c * 3.5f);
                ///f32_c = (F32)(f32_c * 3.3f);
                ///f32_c = (F32)(f32_c * 3.4f);
                ///f32_c = (F32)(f32_c * 3.5f);
                f32_c = (F32)(f32_c * 3.6f);
            }
            else
            {
                //f32_c = (F32)(f32_c * 4.0f);
                //f32_c = (F32)(f32_c * 3.7f);
                //f32_c = (F32)(f32_c * 3.6f);
                //f32_c = (F32)(f32_c * 3.5f);
                f32_c = (F32)(f32_c * 3.2f);
            }
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 60 )
            {
                f32_c = (F32)(f32_c * 2.0f);
            }
            else if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.2f);
            }
            else
            {
                ////f32_c = (F32)(f32_c * 3.0f);
                ////f32_c = (F32)(f32_c * 2.6f);
                f32_c = (F32)(f32_c * 2.7f);
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__8_OZ__235_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.6f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.2f);
            }
            else
            {
                if( gu16_user_water_out_count >= 8 )
                {
                    f32_c = (F32)(f32_c * 2.2f);
                }
                else
                {
                    f32_c = (F32)(f32_c * 2.5f);
                }
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__10_OZ__295_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.7f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.4f);
            }
            else
            {
                f32_c = (F32)(f32_c * 2.8f);
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__12_OZ__355_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.7f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.4f);
            }
            else
            {
                f32_c = (F32)(f32_c * 2.8f);
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__14_OZ__415_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.7f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.4f);
            }
            else
            {
                f32_c = (F32)(f32_c * 2.8f);
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__16_OZ__475_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.7f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 3.0f);
            }
            else
            {
                f32_c = (F32)(f32_c * 3.0f);
            }
        }
    }
    else if( gu8Cup_level == CUP_LEVEL__20_OZ__590_ML )
    {
        if( f32_c < 1.0f )
        {
            f32_c = (F32)(f32_c * 3.7f);
        }
        else
        {
            if( gu8_Hot_Tank_Temperature_One_Degree <= 70 )
            {
                f32_c = (F32)(f32_c * 2.7f);
            }
            else
            {
                f32_c = (F32)(f32_c * 3.0f);
            }
        }

    }
    else
    {
        f32_c = (F32)(f32_c * 1.9f);

        if( gu8_Mixing_Out_Temperature_One_Degree <= 30 && bit_Mixing_Out_Temp_Open_Short_Error__E52 == CLEAR )
        {
            f32_c = (F32)(f32_c * 1.2f);
        }
        else{}
    }

    #if 0
    /*..hui [23-11-29오전 11:27:35] 1시간 이상 미사용시..*/
    if( bit_hot_long_not_use_state == SET )
    {
        f32_c = (F32)(f32_c * 1.1f);
    }
    else{}
    #endif

    if( f32_c < 1.0f )
    {
        f32_c = 1.0f;
    }
    else{}

    f32_time = (F32)((F32)gu16_water_out_time / f32_c);

    gu16_cold_mix_time = (U16)f32_time;

    mu16_max_time = gu16_water_out_time;

    if( gu16_cold_mix_time >= mu16_max_time )
    {
        gu16_cold_mix_time = mu16_max_time;
    }
    else{}

    if( gu16_cold_mix_time <= 2 )
    {
        gu16_cold_mix_time = 0;
    }
    else
    {
        /*Hot_Temp_Compensation_time();*/
        if(u8Extract_Continue != SET)
        {
            Hot_Temp_45_Degree_Compensation_time_Hot_Big();
        }
        else{}
    }


////////////////////////////////////////////////////////////////////////////////////////

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_hot_not_use(void)
{
    if( F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT )
    {
        bit_hot_long_not_use_state = CLEAR;
        gu16_hot_not_use_timer = 0;
    }
    else
    {
        gu16_hot_not_use_timer++;

        if( gu16_hot_not_use_timer >= HOT_NOT_USE_TIME )
        {
            gu16_hot_not_use_timer = HOT_NOT_USE_TIME;
            bit_hot_long_not_use_state = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_hot_95_temp_use(void)
{
    /*..hui [24-11-25오후 3:38:06] 고도모드 1단계에서만 동작..*/
    if( gu8AltitudeStep == ALTITUDE_2_MODE_MID
        || gu8AltitudeStep == ALTITUDE_3_MODE_LOW
        || gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )
    {
        gu8_95_degree_extract_timer = 0;
        bit_95_degree_use_state = CLEAR;
        gu16_95_degree_use_timer = 0;
        return;
    }
    else{}

    if( F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
        {
            gu8_95_degree_extract_timer++;

            if( gu8_95_degree_extract_timer >= 30 )
            {
                gu8_95_degree_extract_timer = 30;
                bit_95_degree_use_state = SET;
                gu16_95_degree_use_timer = 0;
            }
            else{}
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
             gu8_95_degree_extract_timer++;

             if( gu8_95_degree_extract_timer >= 30 )
             {
                 gu8_95_degree_extract_timer = 30;
                 bit_95_degree_use_state = CLEAR;
                 gu16_95_degree_use_timer = 0;
             }
             else{}
        }

    }
    else
    {
        if( bit_95_degree_use_state == SET )
        {
            gu16_95_degree_use_timer++;

            /*..hui [24-3-29오전 11:04:25] 2분동안만..*/
            if( gu16_95_degree_use_timer >= 1600 )
            {
                gu16_95_degree_use_timer = 1600;
                bit_95_degree_use_state = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_95_degree_use_timer = 0;
        }

        gu8_95_degree_extract_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_hot_85_95_temp_use(void)
{
    /*..hui [24-11-25오후 3:38:06] 고도모드 1,2,3단계에서만 동작..*/
    if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )
    {
        gu8_85_95_degree_extract_timer = 0;
        bit_85_95_degree_use_state = CLEAR;
        gu16_85_95_degree_use_timer = 0;
        return;
    }
    else{}


    if( F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC
            || gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
        {
            gu8_85_95_degree_extract_timer++;

            if( gu8_85_95_degree_extract_timer >= 30 )
            {
                gu8_85_95_degree_extract_timer = 30;
                bit_85_95_degree_use_state = SET;
                gu16_85_95_degree_use_timer = 0;
            }
            else{}
        }
        else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
        {
             gu8_85_95_degree_extract_timer++;

             if( gu8_85_95_degree_extract_timer >= 30 )
             {
                 gu8_85_95_degree_extract_timer = 30;
                 bit_85_95_degree_use_state = CLEAR;
                 gu16_85_95_degree_use_timer = 0;
             }
             else{}
        }

    }
    else
    {
        if( bit_85_95_degree_use_state == SET )
        {
            gu16_85_95_degree_use_timer++;

            /*..hui [24-3-29오전 11:04:25] 2분동안만..*/
            if( gu16_85_95_degree_use_timer >= 1600 )
            {
                gu16_85_95_degree_use_timer = 1600;
                bit_85_95_degree_use_state = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_85_95_degree_use_timer = 0;
        }

        gu8_85_95_degree_extract_timer = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_hot_fast_dec(void)
{
    if( gu8_Hot_Tank_Temperature_One_Degree <= 30
        || gu8_Hot_Tank_Temperature_One_Degree >= 92
        || gu8_hot_temp_before == 0
        || gu8_hot_temp_before_2 == 0 )
    {
        gu8_hot_temp_before = gu8_Hot_Tank_Temperature_One_Degree;
        gu16_hot_fast_dec_timer = 0;
        bit_hot_fast_dec = CLEAR;
        gu8_hot_temp_before_2 = gu8_Hot_Tank_Temperature_One_Degree;
        gu8_hot_dec_clear_cnt = 0;
        gu16_dec_finish_timer = 0;
        return;
    }
    else{}

    gu16_hot_fast_dec_timer++;

    /*if( gu16_hot_fast_dec_timer >= 600 )*/
    /*if( gu16_hot_fast_dec_timer >= 300 )*/
    if( gu16_hot_fast_dec_timer >= 100 )
    {
        gu16_hot_fast_dec_timer = 0;

        /*..hui [24-3-29오후 3:22:51] 1분안에 10도 이상 떨어졌을떄..*/
        /*if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_temp_before - 5 )*/
        if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_hot_temp_before - 3 )
        {
            bit_hot_fast_dec = SET;
            /*gu8_hot_temp_before = gu8_Hot_Tank_Temperature_One_Degree;*/
        }
        else{}

        gu8_hot_temp_before = gu8_Hot_Tank_Temperature_One_Degree;

    }
    else{}


    if( bit_hot_fast_dec == SET )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree != gu8_hot_temp_before_2 )
        {
            if( gu8_Hot_Tank_Temperature_One_Degree > gu8_hot_temp_before_2 )
            {
                gu8_hot_dec_clear_cnt++;
            }
            else{}

            //if( gu8_hot_dec_clear_cnt >= 3 )
            if( gu8_hot_dec_clear_cnt >= 5 )
            {
                bit_hot_fast_dec = CLEAR;
            }
            else{}

            gu8_hot_temp_before_2 = gu8_Hot_Tank_Temperature_One_Degree;
        }
        else{}

        gu16_dec_finish_timer++;

        if( gu16_dec_finish_timer >= 1800 )
        {
            gu8_hot_dec_clear_cnt = 0;
            gu16_dec_finish_timer = 0;
            bit_hot_fast_dec = CLEAR;
        }
        else{}
    }
    else
    {
        gu8_hot_temp_before_2 = gu8_Hot_Tank_Temperature_One_Degree;
        gu8_hot_dec_clear_cnt = 0;
        gu16_dec_finish_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



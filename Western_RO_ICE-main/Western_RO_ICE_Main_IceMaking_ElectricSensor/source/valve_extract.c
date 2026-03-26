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
#include    "valve_extract.h"



void output_valve_extract(void);





U8 gu8LockLEDFlick;

bit F_LineTest;                   // 라인 테스트
bit F_LineTest2;                  // 라인 테스트2
//bit F_PartTest;                   // 파트 테스트
//bit F_PBATest;                    // PBA TEST
//bit F_NfcTest;

//===================================== Part Test
bit F_PartHeater;
bit F_PartComp;
bit F_PartIceHeater;
bit F_PartTrayVV;
bit F_PartColdVV;
bit F_PartTrayCW;
bit F_PartDrainPump;
bit F_PartCristal;
bit F_PartIR;
bit F_PartIce;


U8 gu8_hot_close_delay_timer;

bit bit_temporary_hot_stop;
U16 gu16_temporary_hot_stop_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : Water Output
// 개요       : 추출 밸브
//----------------------------------------------------------------------------
// 기능       : 추출 밸브 동작

//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void output_valve_extract(void)
{
    /*calc_mix_water();*/
    open_hot_valve();
    open_cold_valve();

    check_hot_not_use();
    check_hot_95_temp_use();
    check_hot_85_95_temp_use();
    check_hot_fast_dec();

    if( F_WaterOut == SET )
    {
        if( u8WaterOutState == PURE_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;

            if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
                || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
                || Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
            {
                /*..hui [23-8-25오후 2:56:17] 온수 온도센서 or 냉수 온도센서 고장 시 냉수 추출하면 무조건 냉수밸브만.. 필차장님 제호..*/
                pVALVE_COLD_OUT = SET;
                pVALVE_ROOM_OUT = CLEAR;
                pVALVE_HOT_OUT = CLEAR;
            }
            //////else if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_ROOM_27_TEMP - 3) )
            else if( gu8_room_mix_abnormal_mode == MIX_COLD_TEMP_ABNORMAL_HIGH  )
            {
                if( bit_first_open_room_valve_pure == SET )
                {
                    pVALVE_ROOM_OUT = SET;
                }
                else
                {
                    pVALVE_ROOM_OUT = CLEAR;
                }

                pVALVE_COLD_OUT = SET;
                pVALVE_HOT_OUT = CLEAR;
            }
            ///////else if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_ROOM_27_TEMP + 3) )
            else if( gu8_room_mix_abnormal_mode == MIX_HOT_TEMP_ABNORMAL_LOW  )
            {
                if( bit_first_open_room_valve_pure == SET )
                {
                    pVALVE_ROOM_OUT = SET;
                }
                else
                {
                    pVALVE_ROOM_OUT = CLEAR;
                }

                pVALVE_COLD_OUT = CLEAR;
                pVALVE_HOT_OUT = SET;
            }
            else
            {
                if( bit_first_open_room_valve_pure == SET )
                {
                    pVALVE_ROOM_OUT = SET;
                }
                else
                {
                    pVALVE_ROOM_OUT = CLEAR;
                }

                if( bit_big_mode == COLD__BIG )
                {
                    pVALVE_COLD_OUT = SET;

                    /*..hui [23-7-14오후 3:44:30] DPP 끝나고 저수위감지됐을경우 테스트 해봐야함..*/
                    /*if( bit_open_hot_valve == SET && bit_first_open_room_valve_pure == CLEAR)*/
                    if( bit_open_hot_valve == SET )
                    {
                        pVALVE_HOT_OUT = SET;
                    }
                    else
                    {
                        pVALVE_HOT_OUT = CLEAR;
                    }
                }
                else /*if( bit_big_mode == HOT__BIG )*/
                {
                    pVALVE_HOT_OUT = SET;

                    /*..hui [23-7-14오후 3:44:30] DPP 끝나고 저수위감지됐을경우 테스트 해봐야함..*/
                    /*if( bit_open_hot_valve == SET && bit_first_open_room_valve_pure == CLEAR)*/
                    if( bit_open_hot_valve == SET )
                    {
                        pVALVE_COLD_OUT = SET;
                    }
                    else
                    {
                        pVALVE_COLD_OUT = CLEAR;
                    }
                }
            }
        }
        else if( u8WaterOutState == COLD_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;
            pVALVE_COLD_OUT = SET;
            pVALVE_ROOM_OUT = CLEAR;
            pVALVE_HOT_OUT = CLEAR;
        }
        else if( u8WaterOutState == HOT_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;

            if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
                || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN )
                || ( F_Hot_Enable == CLEAR && gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
                || Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
            {
                /*..hui [23-8-25오후 3:19:33] 95, 85는 센서 불량이더라도 온수밸브만 ON..*/
                if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC
                   || gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
                {
                    pVALVE_COLD_OUT = CLEAR;
                    pVALVE_ROOM_OUT = CLEAR;
                    pVALVE_HOT_OUT = SET;
                }
                else
                {
                    /*..hui [23-8-25오후 2:56:17] 온수 온도센서 or 냉수 온도센서 고장 시 온수 추출하면 무조건 온수+냉수밸브.. 필차장님 제호..*/
                    /*..hui [23-8-25오후 3:20:06] 77도, 43도는 둘 중 하나 고장이면 냉수+온수밸브 ON..*/
                    pVALVE_COLD_OUT = SET;
                    pVALVE_ROOM_OUT = CLEAR;
                    pVALVE_HOT_OUT = SET;
                }
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC )
            {
                if( bit_first_open_room_valve_hot == SET )
                {
                    pVALVE_COLD_OUT = CLEAR;
                    pVALVE_ROOM_OUT = SET;
                    pVALVE_HOT_OUT = SET;
                }
                else
                {
                    /*..hui [23-6-16오후 3:09:14] 200도는 온수밸브만 OPEN..*/
                    pVALVE_COLD_OUT = CLEAR;
                    pVALVE_ROOM_OUT = CLEAR;
                    pVALVE_HOT_OUT = SET;
                }
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__185_oF_85_oC )
            {
                /*..hui [23-10-6오후 5:37:50] 추출중에 온수 온도 떨어지는 경우 대비.. 이쪽에도 추가..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_85_TEMP + 3) )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_85_TEMP + 1) )
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_HOT_OUT = SET;
                    pVALVE_COLD_OUT = CLEAR;
                }
                else
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_HOT_OUT = SET;

                    if( bit_open_cold_valve == SET )
                    {
                        pVALVE_COLD_OUT = SET;
                    }
                    else
                    {
                        pVALVE_COLD_OUT = CLEAR;
                    }
                }
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__170_oF_77_oC )
            {
                /*..hui [23-10-6오후 5:37:50] 추출중에 온수 온도 떨어지는 경우 대비.. 이쪽에도 추가..*/
                /*if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_77_TEMP + 3) )*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_77_TEMP + 1) )
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_HOT_OUT = SET;
                    pVALVE_COLD_OUT = CLEAR;
                }
                else
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_HOT_OUT = SET;

                    if( bit_open_cold_valve == SET )
                    {
                        pVALVE_COLD_OUT = SET;
                    }
                    else
                    {
                        pVALVE_COLD_OUT = CLEAR;
                    }
                }
            }
            else /*if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )*/
            {
                /*..hui [23-10-6오후 5:37:50] 추출중에 온수 온도 떨어지는 경우 대비.. 이쪽에도 추가..*/
                if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_HOT_43_TEMP + 3) )
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_HOT_OUT = SET;
                    pVALVE_COLD_OUT = CLEAR;
                }
                else if( gu8_Cold_Temperature_One_Degree >= (U8)(TARGET_HOT_43_TEMP - 3) )
                {
                    /*..hui [23-10-6오후 5:42:49] 냉수 온도가 40도 이상일 경우....는 없지만 추가..*/
                    if( bit_first_open_room_valve_pure == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    pVALVE_COLD_OUT = SET;
                    pVALVE_HOT_OUT = CLEAR;
                }
                else
                {
                    if( bit_first_open_room_valve_hot == SET )
                    {
                        pVALVE_ROOM_OUT = SET;
                    }
                    else
                    {
                        pVALVE_ROOM_OUT = CLEAR;
                    }

                    /*..hui [23-11-30오후 3:06:26] 히터 OFF온도가 98~99도로 높아짐..*/
                    /*..hui [23-11-30오후 3:06:43] 냉수 25도 이상일떄 full로 냉수+온수밸브 열어줘야 하는데..*/
                    /*..hui [23-11-30오후 3:06:58] 온도가 높아짐에따라 50도까지 올라가게됨....*/
                    /*..hui [23-11-30오후 3:07:24] 그럴경우에는 추출 종료 전에 온수밸브만 꺼주는 제어 추가..*/
                    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
                        && gu8_Cold_Temperature_One_Degree >= 30
                        && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME )
                    {
                        /*bit_temporary_hot_stop = SET;*/

                        gu16_temporary_hot_stop_timer++;

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time - 18 )
                        {
                            bit_temporary_hot_stop = SET;
                        }
                        else
                        {
                            bit_temporary_hot_stop = CLEAR;
                        }

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time )
                        {
                            gu16_temporary_hot_stop_timer = u16Efluent_Time;
                        }
                        else{}
                    }
                    else if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
                        && gu8_Cold_Temperature_One_Degree >= 25
                        && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME )
                    {
                        /*bit_temporary_hot_stop = SET;*/

                        gu16_temporary_hot_stop_timer++;

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time - 15 )
                        {
                            bit_temporary_hot_stop = SET;
                        }
                        else
                        {
                            bit_temporary_hot_stop = CLEAR;
                        }

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time )
                        {
                            gu16_temporary_hot_stop_timer = u16Efluent_Time;
                        }
                        else{}
                    }
                    else if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML
                        && gu8_Cold_Temperature_One_Degree >= 20
                        && gu16_cold_mix_time >= HOT_STOP_COLD_MIX_TIME_2 )
                    {
                        /*bit_temporary_hot_stop = SET;*/

                        gu16_temporary_hot_stop_timer++;

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time - 10 )
                        {
                            bit_temporary_hot_stop = SET;
                        }
                        else
                        {
                            bit_temporary_hot_stop = CLEAR;
                        }

                        if( gu16_temporary_hot_stop_timer >= u16Efluent_Time )
                        {
                            gu16_temporary_hot_stop_timer = u16Efluent_Time;
                        }
                        else{}
                    }
                    else
                    {
                        bit_temporary_hot_stop = CLEAR;
                        gu16_temporary_hot_stop_timer = 0;
                    }

                    if( bit_big_mode == HOT__BIG )
                    {
                        if( bit_temporary_hot_stop == SET )
                        {
                            pVALVE_HOT_OUT = CLEAR;
                        }
                        else
                        {
                            pVALVE_HOT_OUT = SET;
                        }

                        if( bit_open_cold_valve == SET )
                        {
                            pVALVE_COLD_OUT = SET;
                        }
                        else
                        {
                            pVALVE_COLD_OUT = CLEAR;
                        }
                    }
                    else /*if( bit_big_mode == COLD__BIG )*/
                    {
                        pVALVE_COLD_OUT = SET;

                        if( bit_open_cold_valve == SET )
                        {
                            pVALVE_HOT_OUT = SET;
                        }
                        else
                        {
                            pVALVE_HOT_OUT = CLEAR;
                        }
                    }
                }
            }
        }
        else
        {
            if( bit_cold_drain_output == SET )
            {
                pVALVE_24V_POWER = SET;
            }
            else
            {
                pVALVE_24V_POWER = CLEAR;
            }

            pVALVE_ROOM_OUT = CLEAR;
            pVALVE_COLD_OUT = CLEAR;
            pVALVE_HOT_OUT = CLEAR;
        }
    }
    else
    {
        if( bit_cold_drain_output == SET )
        {
            pVALVE_24V_POWER = SET;
        }
        else
        {
            pVALVE_24V_POWER = CLEAR;
        }

        pVALVE_ROOM_OUT = CLEAR;
        pVALVE_COLD_OUT = CLEAR;
        pVALVE_HOT_OUT = CLEAR;

        bit_temporary_hot_stop = CLEAR;
        gu16_temporary_hot_stop_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/







/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





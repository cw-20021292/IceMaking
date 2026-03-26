/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "AD_Conversion.h"
#include    "Temp_Table.h"

/***********************************************************************************************************************/

void AD_Conversion(void);
U16 get_adc_value( U8 ad_channel, U8 resolution);
void filtering_dc_current_24V_adc( U16 mu16ad_result );
void filtering_dc_current_12V_adc( U16 mu16ad_result );
void filtering_drain_pump_current_adc( U16 mu16ad_result );
void filtering_hot_tank_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_HotTankWater(U16 mu16Adc);
void filtering_hot_pump_current_adc( U16 mu16ad_result );
void filtering_uv_water_tank_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_tank_back_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_tray_one_current_feed_adc( U16 mu16ad_result );
void filtering_ice_full_adc( U16 mu16ad_result );
void filtering_leakage_adc( U16 mu16ad_result );
void filtering_eva_1_temp_adc( U16 mu16ad_result );
//void filtering_eva_2_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_Eva(U16 mu16Adc);
void filtering_cold_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_ColdWater(U16 mu16Adc);
void filtering_room_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_RoomWater(U16 mu16Adc);
void filtering_mixing_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_MixingOutWater(U16 mu16Adc);
void filtering_amb_temp_adc( U16 mu16ad_result );
void filtering_amb_side_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_Ambient(U16 mu16Adc);
void filtering_fan_current_adc( U16 mu16ad_result );
//void filtering_uv_ice_tray_two_current_feed_adc( U16 mu16ad_result );
//void filtering_tray_temp_adc( U16 mu16ad_result );
//U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc);

//void filtering_tds_in_temp_adc( U16 mu16ad_result );
//U16 ConvAdc2Temp_TDS_In_Water(U16 mu16Adc);
void filtering_uv_ice_tank_3_front_current_adc( U16 mu16ad_result );

//void filtering_cds_adc( U16 mu16ad_result );
//U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value );

//U16 ConvAdc2Temp_TDS_Out_Water(U16 mu16Adc);
//void filtering_tds_out_temp_adc( U16 mu16ad_result );
//void filtering_tds_out_data_adc( U16 mu16ad_result );
//U16 ConvAdc2Temp_HotInWater(U16 mu16Adc);

void ADC_Start(void);
void ADC_Stop(void);




/***********************************************************************************************************************/
/*..hui [17-11-24오후 1:47:00] 드레인펌프 피드백 전류..*/
U16 gu16_AD_Result_Cold;
U16 gu16ADIceFull;
U16 gu16ADCds;
U16 gu16ADLeakage;
//U8 gu8_AD_Result_Eva_First;
U16 gu16_AD_Result_Amb;
U16 gu16_AD_Result_Room;

U16 gu16AD_EWD_Old;
U16 gu16AD_Hot_Old;
U16 gu16AD_Cold_Old;
U16 gu16AD_IceFull_Old;
U16 gu16AD_Cds_Old;
U16 gu16AD_Leakage_Old;
U8 gu8AD_Eva_Old;
U8 gu8AD_Amb_Old;
U8 gu8AD_Room_Old;

U16 gu16AD_EWD_Now;
U16 gu16AD_Hot_Now;
U16 gu16AD_Cold_Now;
U16 gu16AD_IceFull_Now;
U16 gu16AD_Cds_Now;
U16 gu16AD_Leakage_Now;
U8 gu8AD_Eva_Now;
U8 gu8AD_Amb_Now;
U8 gu8AD_Room_Now;


U8 u8AdCount;

U16 gu16_AD_Drain_Pump_Current;
U16 u16Max_Drain_Pump_Current_AD;
U16 u16Min_Drain_Pump_Current_AD;
U32 u32AD_Drain_Pump_Current_Sum;
U8 u8Cnt_Drain_Pump_Current;




U16 gu16_AD_Tray_Pump_Current;
U16 u16Max_Hot_Pump_Current_AD;
U16 u16Min_Hot_Pump_Current_AD;
U32 u32AD_Hot_Pump_Current_Sum;
U8 u8Cnt_Hot_Pump_Current;


U16 u16Max_Cold_Temp_AD;
U16 u16Min_Cold_Temp_AD;
U32 u32AD_Cold_Temp_Sum;
U8 u8Cnt_Cold_Temp;
U16 gu16_Cold_Temperature;
U8 gu8_Cold_Temperature_One_Degree;


U16 u16Max_Amb_Temp_AD;
U16 u16Min_Amb_Temp_AD;
U32 u32AD_Amb_Temp_Sum;
U8 u8Cnt_Amb_Temp;
U16 gu16_Amb_Front_Temperature;
U8 gu8_Amb_Front_Temperature_One_Degree;

U8 gu8_Amb_Temperature_One_Degree;


U16 gu16_AD_Result_Eva_First;
U16 u16Max_Eva_1_Temp_AD;
U16 u16Min_Eva_1_Temp_AD;
U32 u32AD_Eva_1_Temp_Sum;
U8 u8Cnt_Eva_1_Temp;
U16 gu16_Eva_First_Temperature;
U8 gu8_Eva_Cold_Temperature_One_Degree;


U16 gu16_AD_Result_Eva_Second;
U16 u16Max_Eva_2_Temp_AD;
U16 u16Min_Eva_2_Temp_AD;
U32 u32AD_Eva_2_Temp_Sum;
U8 u8Cnt_Eva_2_Temp;
U16 gu16_Eva_Second_Temperature;
U8 gu8_Eva_Ice_Temperature_One_Degree;



U16 u16Max_Room_Temp_AD;
U16 u16Min_Room_Temp_AD;
U32 u32AD_Room_Temp_Sum;
U8 u8Cnt_Room_Temp;
U16 gu16_Room_Temperature;
U8 gu8_Room_Temperature_One_Degree;


U16 u16Max_Hot_Temp_AD;
U16 u16Min_Hot_Temp_AD;
U32 u32AD_Hot_Temp_Sum;
U8 u8Cnt_Hot_Temp;

U16 u16Max_Ice_Full_Temp_AD;
U16 u16Min_Ice_Full_Temp_AD;
U32 u32AD_Ice_Full_Temp_Sum;
U8 u8Cnt_Ice_Full_Temp;

U16 u16Max_Leakage_AD;
U16 u16Min_Leakage_AD;
U32 u32AD_Leakage_Sum;
U8 u8Cnt_Leakage;

U16 u16Max_CDS_AD;
U16 u16Min_CDS_AD;
U32 u32AD_CDS_Sum;
U8 u8Cnt_CDS;


U16 gu16_AD_Result_TDS_In_Temp;
U16 gu16Max_TDS_In_Temp_AD;
U16 gu16Min_TDS_In_Temp_AD;
U16 gu16AD_TDS_In_Temp_Sum;
U8 u8Cnt_TDS_In_Temp;

U16 gu16_AD_Result_TDS_In_Org_Temp;
U16 gu16_TDS_In_Temperature;
U8 gu8_TDS_In_Temperature_One_Degree;


U16 gu16_AD_Result_Fan_Current;
U16 gu16Max_Fan_Current_Data_AD;
U16 u16Min_Fan_Current_Data_AD;
U32 u32AD_Fan_Current_Sum;
U8 u8Cnt_Fan_Current_Data;

U16 gu16_AD_Result_TDS_Out_Temp;
U16 gu16Max_TDS_Out_Temp_AD;
U16 gu16Min_TDS_Out_Temp_AD;
U32 gu32AD_TDS_Out_Temp_Sum;
U8 u8Cnt_TDS_Out_Temp;

U16 gu16_AD_Result_UV_Ice_Tray_1_2_Current;
U16 gu16Max_UV_Ice_Tray_One_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tray_One_Current_Feed_AD;
U32 u32AD_UV_Ice_Tray_One_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tray_One_Current_Feed;

U16 gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
U16 gu16Max_UV_Ice_Tank_Back_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tank_Back_Current_Feed_AD;
U32 u32AD_UV_Ice_Tank_Back_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tank_Back_Current_Feed;

U16 gu16_AD_Result_Hot_Tank_Temp;
U16 u16Max_Hot_Tank_Temp_AD;
U16 u16Min_Hot_Tank_Temp_AD;
U32 u32AD_Hot_Tank_Temp_Sum;
U8 u8Cnt_Hot_Tank_Temp;
U8 gu8_Hot_Tank_Temperature_One_Degree;
U16 gu16_Hot_Tank_Temperature;

U16 gu16_AD_Result_DC_Current_24V;
U16 gu16Max_DC_Current_24V_AD;
U16 gu16Min_DC_Current_24V_AD;
U32 gu32AD_DC_Current_24V_Sum;
U8 u8Cnt_DC_Current_24V;

U16 gu16_AD_Result_DC_Current_12V;
U16 gu16Max_DC_Current_12V_AD;
U16 u16Min_DC_Current_12V_AD;
U32 u32AD_DC_Current_12V_Sum;
U8 u8Cnt_DC_Current_12V;

U16 gu16_Mixing_Out_Temperature;
U8 gu8_Mixing_Out_Temperature_One_Degree;
U16 gu16_AD_Result_Mixing_Out;
U16 u16Max_Mixing_Temp_AD;
U16 u16Min_Mixing_Temp_AD;
U32 u32AD_Mixing_Temp_Sum;
U8 u8Cnt_Mixing_Temp;

#if 0
U16 gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed;
U16 gu16Max_UV_Ice_Tray_Two_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tray_Two_Current_Feed_AD;
U32 u32AD_UV_Ice_Tray_Two_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tray_Two_Current_Feed;
#endif

U16 gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
U16 gu16Max_UV_Water_Tank_Current_Feed_AD;
U16 gu16Min_UV_Water_Tank_Current_Feed_AD;
U32 u32AD_UV_Water_Tank_Current_Feed_Sum;
U8 u8Cnt_UV_Water_Tank_Current_Feed;

U16 gu16_AD_Result_Amb_Side;
U16 u16Max_Amb_Side_Temp_AD;
U16 u16Min_Amb_Side_Temp_AD;
U32 u32AD_Amb_Side_Temp_Sum;
U8 u8Cnt_Amb_Side_Temp;
U16 gu16_Amb_Side_Temperature;
U8 gu8_Amb_Side_Temperature_One_Degree;


U16 gu16_AD_Result_Tray_Temp;
U16 u16Max_Tray_Temp_AD;
U16 u16Min_Tray_Temp_AD;
U32 u32AD_Tray_Temp_Sum;
U8 u8Cnt_Tray_Temp;
U16 gu16_Tray_Temperature;
U8 gu8_Tray_Temperature_One_Degree;

U16 gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
U16 gu16Max_UV_Ice_Tank_Front_Current_AD;
U16 gu16Min_UV_Ice_Tank_Front_Current_AD;
U32 u32AD_UV_Ice_Tank_Front_Current_Sum;
U8 u8Cnt_UV_Ice_Tank_Front_Current;

#if 0
U16 gu16_TDS_Out_Temperature;
U8 gu8_TDS_Out_Temperature_One_Degree;
U16 gu16_AD_Result_TDS_Out_Org_Temp;

U16 gu16_AD_Result_TDS_Out_Data;
U16 gu16Max_TDS_Out_Data_AD;
U16 u16Min_TDS_Out_Data_AD;
U16 u16AD_TDS_Out_Data_Sum;
U8 u8Cnt_TDS_Out_Data;
U16 gu16AD_TDS_Out_Temp_Sum;
#endif

U16 gu16_tds_ad_test;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void AD_Conversion(void)
{
    U16 ad_result = 0;
    U8 mu8_ad_channel;

    u8AdCount++;

    switch(u8AdCount)
    {
        case AD_Count_1:

               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_24V,
                                           AD_CONV_10BIT);

               filtering_dc_current_24V_adc(ad_result);


               break;

        case AD_Count_2:

               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_12V,
                                           AD_CONV_10BIT);

               filtering_dc_current_12V_adc(ad_result);

               break;

        case AD_Count_3:

               ad_result = get_adc_value( (U8)AD_Channel_Drain_Pump_Current,
                                           AD_CONV_10BIT );

               filtering_drain_pump_current_adc(ad_result);

               break;

        case AD_Count_4:

               ad_result = get_adc_value( (U8)AD_Channel_Hot_Heater_Temp,
                                           AD_CONV_10BIT);

               filtering_hot_tank_temp_adc(ad_result);

               gu16_Hot_Tank_Temperature = ConvAdc2Temp_HotTankWater(gu16_AD_Result_Hot_Tank_Temp);
               gu8_Hot_Tank_Temperature_One_Degree = (U8)((gu16_Hot_Tank_Temperature + 5) / 10);

               break;

        case AD_Count_5:

               ad_result = get_adc_value( (U8)AD_Channel_Hot_Pump_Current,
                                           AD_CONV_10BIT );

               filtering_hot_pump_current_adc(ad_result);

               break;

        case AD_Count_6:

               /*..hui [23-2-16오후 5:47:49] UV Water Tank 전류 피드백..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Water_Tank_Current,
                                           AD_CONV_10BIT);

               filtering_uv_water_tank_current_feed_adc(ad_result);


               break;

        case AD_Count_7:

               /*..hui [23-2-16오후 5:48:07] UV 얼음 탱크 1 전류 피드백..*/
               /*..hui [24-4-4오전 9:58:27] UV 얼음 탱크 뒤쪽 2개 피드백..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tank_Current,
                                           AD_CONV_10BIT);

               /*..hui [24-2-2오후 1:59:43] UV 얼음탱크 뒷쪽.. 위, 아래 2개 피드백..*/
               filtering_uv_ice_tank_back_current_feed_adc(ad_result);


               break;

        case AD_Count_8:

               /*..hui [23-2-16오후 5:48:25] UV 아이스 트레이 전류 피드백..*/
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tray_1_2_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_tray_one_current_feed_adc(ad_result);


               break;

        case AD_Count_9:

               /*..hui [17-11-24오후 2:38:10] 만빙 수신..*/
               ad_result = get_adc_value( (U8)AD_Channel_Ice_Full_Receive,
                                           AD_CONV_10BIT);

               filtering_ice_full_adc(ad_result);

               break;

        case AD_Count_10:

               /*..hui [17-11-24오후 2:38:16] 누수..*/
               ad_result = get_adc_value( (U8)AD_Channel_Water_Leakage,
                                           AD_CONV_10BIT);

               filtering_leakage_adc(ad_result);

               break;

        case AD_Count_11:

               /*..hui [17-11-24오후 2:37:56] 에바 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_EVA_1_TEMP,
                                           AD_CONV_10BIT );

               filtering_eva_1_temp_adc(ad_result);

               /*..hui [23-6-30오후 5:45:47] 웨스턴은 EVA 온도 1개.. 얼음임..*/
               gu16_Eva_First_Temperature = ConvAdc2Temp_Eva(gu16_AD_Result_Eva_First);
               gu8_Eva_Cold_Temperature_One_Degree = (U8)((gu16_Eva_First_Temperature + 5) / 10);

               break;

        case AD_Count_12:

               /*..hui [17-11-24오후 2:37:41] 냉수 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Cold_Temp,
                                           AD_CONV_10BIT );

               if( bit_adc_cold_start == SET && pCOLD_TH_POWER == SET )
               {
                   filtering_cold_temp_adc(ad_result);

                   gu16_Cold_Temperature = ConvAdc2Temp_ColdWater(gu16_AD_Result_Cold);
                   gu8_Cold_Temperature_One_Degree = (U8)((gu16_Cold_Temperature + 5) / 10);
               }
               else{}

               break;

        case AD_Count_13:

               /*..hui [17-11-24오후 2:38:01] 정수 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Room_Temp,
                                           AD_CONV_10BIT );

               if( bit_adc_room_start == SET && pROOM_TH_POWER == SET)
               {
                   filtering_room_temp_adc(ad_result);

                   gu16_Room_Temperature = ConvAdc2Temp_RoomWater(gu16_AD_Result_Room);
                   gu8_Room_Temperature_One_Degree = (U8)((gu16_Room_Temperature + 5) / 10);
               }
               else{}

               break;

        case AD_Count_14:

               /*..hui [23-2-16오후 5:57:44] 믹싱온도센서.... 순간온수 추출온도센서랑 동일..*/
               ad_result = get_adc_value( (U8)AD_Channel_Cold_Mixing_Temp,
                                           AD_CONV_10BIT );

               filtering_mixing_temp_adc(ad_result);

               gu16_Mixing_Out_Temperature = ConvAdc2Temp_MixingOutWater(gu16_AD_Result_Mixing_Out);
               gu8_Mixing_Out_Temperature_One_Degree = (U8)((gu16_Mixing_Out_Temperature + 5) / 10);

               break;

        case AD_Count_15:

               /*..hui [17-11-24오후 2:37:48] 외기 온도센서..*/
               ad_result = get_adc_value( (U8)AD_Channel_Amb_Temp,
                                           AD_CONV_10BIT );


               filtering_amb_temp_adc(ad_result);

               gu16_Amb_Front_Temperature = ConvAdc2Temp_Ambient(gu16_AD_Result_Amb);
               gu8_Amb_Front_Temperature_One_Degree = (U8)((gu16_Amb_Front_Temperature + 5) / 10);

               break;

        case AD_Count_16:


               ad_result = get_adc_value( (U8)AD_Channel_FAN_Current,
                                           AD_CONV_10BIT );

               filtering_fan_current_adc(ad_result);

               break;

        case AD_Count_17:

               /*..hui [23-9-18오후 4:25:47] 좌측 하단 외기온도센서 1개 추가..*/
               ad_result = get_adc_value( (U8)AD_Channel_Amb_Temp_Side,
                                           AD_CONV_10BIT );

               filtering_amb_side_temp_adc(ad_result);

               gu16_Amb_Side_Temperature = ConvAdc2Temp_Ambient(gu16_AD_Result_Amb_Side);
               gu8_Amb_Side_Temperature_One_Degree = (U8)((gu16_Amb_Side_Temperature + 5) / 10);


               break;

        case AD_Count_18:

               /*..hui [24-4-4오전 10:03:34] 온수 바이메탈 온도센서로 변경..*/
               /*..hui [24-4-4오후 12:12:56] 우선 바이메탈 온도센서 삭제.. ..*/
               /*..hui [24-4-4오후 12:13:10] 나중에 바꿀때 AD입력으로 변경해줘야 함.. 지금은 out..*/
               #if 0
               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tray_Two_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_tray_two_current_feed_adc(ad_result);
               #endif

               break;

        case AD_Count_19:

               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tank_Front_Current,
                                           AD_CONV_10BIT);

               /*..hui [24-2-2오후 2:00:05] UV 얼음탱크 정면에서 앞쪽(도어쪽) UV 피드백..*/
               filtering_uv_ice_tank_3_front_current_adc(ad_result);

               u8AdCount = 0;

               break;

        #if 0
        case AD_Count_20:

               ad_result = get_adc_value( (U8)AD_Channel_TDS_IN_Temp,
                                           AD_CONV_10BIT);

               filtering_tds_in_temp_adc(ad_result);

               gu16_TDS_In_Temperature = ConvAdc2Temp_TDS_In_Water(gu16_AD_Result_TDS_In_Org_Temp);
               gu8_TDS_In_Temperature_One_Degree = (U8)((gu16_TDS_In_Temperature + 5) / 10);

               break;

        case AD_Count_21:

               ad_result = get_adc_value( (U8)AD_Channel_TDS_OUT_Temp,
                                           AD_CONV_10BIT);

               filtering_tds_out_temp_adc(ad_result);

               gu16_TDS_Out_Temperature = ConvAdc2Temp_TDS_Out_Water(gu16_AD_Result_TDS_Out_Org_Temp);
               gu8_TDS_Out_Temperature_One_Degree = (U8)((gu16_TDS_Out_Temperature + 5) / 10);

               break;

        case AD_Count_22:

               if(gu16TDS_OUT_Pulse_Time == 14 || gu16TDS_OUT_Pulse_Time == 13 || gu16TDS_OUT_Pulse_Time == 12)
               {
                   ad_result = get_adc_value( (U8)AD_Channel_TDS_OUT_Data,
                                               AD_CONV_10BIT);

                   filtering_tds_out_data_adc(ad_result);

                   gu16_tds_ad_test++;

                   if( gu16_tds_ad_test >= 10000 )
                   {
                       gu16_tds_ad_test = 10000;
                   }
                   else{}
               }
               else{}

               u8AdCount = 0;

               break;
        #endif

        default:

               ADS = AD_Channel_DC_Current_24V;
               u8AdCount = 0;

               break;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 get_adc_value( U8 ad_channel, U8 resolution)
{
    U16 mu16_ad_result = 0;
    U16 mu16_final_ad_value = 0;

    ADC_Stop();

    ADS = ad_channel;
    ADCE = 1U;  /* enable AD comparator */

    ADC_Start();

    while(ADIF != SET){}

    ADC_Stop();
    ADCE = 0U;  /* disable AD comparator */

    mu16_ad_result = (U16)(ADCR >> resolution);

    /*..hui [17-11-24오후 2:11:20] ACD값 필터링....*/
    /*mu16_final_ad_value = filtering_adc_value( ad_old_value,
                                          mu16_ad_result );  */

    /*return mu16_final_ad_value;*/

    return mu16_ad_result;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_dc_current_24V_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_DC_Current_24V_AD)    //Max Save
    {
        gu16Max_DC_Current_24V_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_DC_Current_24V_AD)  //Min   Save
    {
        gu16Min_DC_Current_24V_AD = mu16ad_result;
    }

    gu32AD_DC_Current_24V_Sum += mu16ad_result;

    if(++u8Cnt_DC_Current_24V >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_DC_Current_24V = 0;
        gu16_AD_Result_DC_Current_24V
            = (U16)(gu32AD_DC_Current_24V_Sum - gu16Max_DC_Current_24V_AD - gu16Min_DC_Current_24V_AD) / 10;

        gu32AD_DC_Current_24V_Sum  = 0;
        gu16Max_DC_Current_24V_AD = 0;
        gu16Min_DC_Current_24V_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_dc_current_12V_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_DC_Current_12V_AD)    //Max Save
    {
        gu16Max_DC_Current_12V_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_DC_Current_12V_AD)  //Min   Save
    {
        u16Min_DC_Current_12V_AD = mu16ad_result;
    }

    u32AD_DC_Current_12V_Sum += mu16ad_result;

    if(++u8Cnt_DC_Current_12V >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_DC_Current_12V = 0;
        gu16_AD_Result_DC_Current_12V
            = (U16)(u32AD_DC_Current_12V_Sum - gu16Max_DC_Current_12V_AD - u16Min_DC_Current_12V_AD) / 10;

        /*gu16_AD_Result_DC_Current_12V = 1024 - gu16_AD_Result_DC_Current_12V;*/

        u32AD_DC_Current_12V_Sum  = 0;
        gu16Max_DC_Current_12V_AD = 0;
        u16Min_DC_Current_12V_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_drain_pump_current_adc( U16 mu16ad_result )
{

    if(mu16ad_result > u16Max_Drain_Pump_Current_AD)    //Max Save
    {
        u16Max_Drain_Pump_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Drain_Pump_Current_AD)  //Min   Save
    {
        u16Min_Drain_Pump_Current_AD = mu16ad_result;
    }

    u32AD_Drain_Pump_Current_Sum += mu16ad_result;

    if(++u8Cnt_Drain_Pump_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Drain_Pump_Current = 0;
        gu16_AD_Drain_Pump_Current = (U16)(u32AD_Drain_Pump_Current_Sum - u16Max_Drain_Pump_Current_AD - u16Min_Drain_Pump_Current_AD) / 50;

        u32AD_Drain_Pump_Current_Sum  = 0;
        u16Max_Drain_Pump_Current_AD = 0;
        u16Min_Drain_Pump_Current_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_tank_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Hot_Tank_Temp_AD)    //Max Save
    {
        u16Max_Hot_Tank_Temp_AD = (U16)mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Tank_Temp_AD)  //Min   Save
    {
        u16Min_Hot_Tank_Temp_AD = (U16)mu16ad_result;
    }

    u32AD_Hot_Tank_Temp_Sum += (U16)mu16ad_result;

    if(++u8Cnt_Hot_Tank_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Tank_Temp = 0;
        gu16_AD_Result_Hot_Tank_Temp = (U16)(u32AD_Hot_Tank_Temp_Sum - u16Max_Hot_Tank_Temp_AD - u16Min_Hot_Tank_Temp_AD) / 50;
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Hot_Tank_Temp = 1024 - gu16_AD_Result_Hot_Tank_Temp;

        u32AD_Hot_Tank_Temp_Sum  = 0;
        u16Max_Hot_Tank_Temp_AD = 0;
        u16Min_Hot_Tank_Temp_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_HotTankWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_WATER )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_WATER )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_WATER;
    return temp_hot_tank_water_table[ mu16Index ];
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_hot_pump_current_adc( U16 mu16ad_result )
{

    if(mu16ad_result > u16Max_Hot_Pump_Current_AD)    //Max Save
    {
        u16Max_Hot_Pump_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Pump_Current_AD)  //Min   Save
    {
        u16Min_Hot_Pump_Current_AD = mu16ad_result;
    }

    u32AD_Hot_Pump_Current_Sum += mu16ad_result;

    if(++u8Cnt_Hot_Pump_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Pump_Current = 0;
        gu16_AD_Tray_Pump_Current = (U16)(u32AD_Hot_Pump_Current_Sum - u16Max_Hot_Pump_Current_AD - u16Min_Hot_Pump_Current_AD) / 50;

        u32AD_Hot_Pump_Current_Sum  = 0;
        u16Max_Hot_Pump_Current_AD = 0;
        u16Min_Hot_Pump_Current_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_water_tank_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Water_Tank_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Water_Tank_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Water_Tank_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Water_Tank_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Water_Tank_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Water_Tank_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Water_Tank_Current_Feed = 0;
        gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed
            = (U16)(u32AD_UV_Water_Tank_Current_Feed_Sum - gu16Max_UV_Water_Tank_Current_Feed_AD - gu16Min_UV_Water_Tank_Current_Feed_AD) / 50;

        u32AD_UV_Water_Tank_Current_Feed_Sum  = 0;
        gu16Max_UV_Water_Tank_Current_Feed_AD = 0;
        gu16Min_UV_Water_Tank_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_tank_back_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tank_Back_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tank_Back_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tank_Back_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tank_Back_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tank_Back_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tank_Back_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tank_Back_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current
            = (U16)(u32AD_UV_Ice_Tank_Back_Current_Feed_Sum - gu16Max_UV_Ice_Tank_Back_Current_Feed_AD - gu16Min_UV_Ice_Tank_Back_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Tank_Back_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tank_Back_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tank_Back_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_tray_one_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tray_One_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tray_One_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tray_One_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tray_One_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tray_One_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tray_One_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tray_One_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Tray_1_2_Current
            = (U16)(u32AD_UV_Ice_Tray_One_Current_Feed_Sum - gu16Max_UV_Ice_Tray_One_Current_Feed_AD - gu16Min_UV_Ice_Tray_One_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Tray_One_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tray_One_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tray_One_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_ice_full_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Ice_Full_Temp_AD)    //Max Save
    {
        u16Max_Ice_Full_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Ice_Full_Temp_AD)  //Min   Save
    {
        u16Min_Ice_Full_Temp_AD = mu16ad_result;
    }

    u32AD_Ice_Full_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Ice_Full_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Ice_Full_Temp = 0;
        gu16ADIceFull = (U16)(u32AD_Ice_Full_Temp_Sum - u16Max_Ice_Full_Temp_AD - u16Min_Ice_Full_Temp_AD) / 50;

        u32AD_Ice_Full_Temp_Sum  = 0;
        u16Max_Ice_Full_Temp_AD = 0;
        u16Min_Ice_Full_Temp_AD = 1024;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_leakage_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Leakage_AD)    //Max Save
    {
        u16Max_Leakage_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Leakage_AD)  //Min   Save
    {
        u16Min_Leakage_AD = mu16ad_result;
    }

    u32AD_Leakage_Sum += mu16ad_result;

    if(++u8Cnt_Leakage >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Leakage = 0;
        gu16ADLeakage = (U16)((u32AD_Leakage_Sum - u16Max_Leakage_AD - u16Min_Leakage_AD) / 50);

        u32AD_Leakage_Sum  = 0;
        u16Max_Leakage_AD = 0;
        u16Min_Leakage_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_eva_1_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Eva_1_Temp_AD)    //Max Save
    {
        u16Max_Eva_1_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Eva_1_Temp_AD)  //Min   Save
    {
        u16Min_Eva_1_Temp_AD = mu16ad_result;
    }

    u32AD_Eva_1_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Eva_1_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Eva_1_Temp = 0;
        gu16_AD_Result_Eva_First = (U16)((u32AD_Eva_1_Temp_Sum - u16Max_Eva_1_Temp_AD - u16Min_Eva_1_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Eva_First = 1024 - gu16_AD_Result_Eva_First;

        u32AD_Eva_1_Temp_Sum  = 0;
        u16Max_Eva_1_Temp_AD = 0;
        u16Min_Eva_1_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_eva_2_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Eva_2_Temp_AD)    //Max Save
    {
        u16Max_Eva_2_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Eva_2_Temp_AD)  //Min   Save
    {
        u16Min_Eva_2_Temp_AD = mu16ad_result;
    }

    u32AD_Eva_2_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Eva_2_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Eva_2_Temp = 0;
        gu16_AD_Result_Eva_Second = (U16)((u32AD_Eva_2_Temp_Sum - u16Max_Eva_2_Temp_AD - u16Min_Eva_2_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Eva_Second = 1024 - gu16_AD_Result_Eva_Second;

        u32AD_Eva_2_Temp_Sum  = 0;
        u16Max_Eva_2_Temp_AD = 0;
        u16Min_Eva_2_Temp_AD = 1024;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_Eva(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_EVA_TEMP )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_EVA_TEMP )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_EVA_TEMP;
    return temp_eva_table[ mu16Index ];
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_cold_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Cold_Temp_AD)    //Max Save
    {
        u16Max_Cold_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Cold_Temp_AD)  //Min   Save
    {
        u16Min_Cold_Temp_AD = mu16ad_result;
    }

    u32AD_Cold_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Cold_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Cold_Temp = 0;
        gu16_AD_Result_Cold = (U16)((u32AD_Cold_Temp_Sum - u16Max_Cold_Temp_AD - u16Min_Cold_Temp_AD) / 50);

        u32AD_Cold_Temp_Sum  = 0;
        u16Max_Cold_Temp_AD = 0;
        u16Min_Cold_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_ColdWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_COLD_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_COLD_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_COLD_WATER;
    return temp_cold_water_table[ mu16Index ];
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_room_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Room_Temp_AD)    //Max Save
    {
        u16Max_Room_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Room_Temp_AD)  //Min   Save
    {
        u16Min_Room_Temp_AD = mu16ad_result;
    }

    u32AD_Room_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Room_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Room_Temp = 0;
        gu16_AD_Result_Room = (U16)((u32AD_Room_Temp_Sum - u16Max_Room_Temp_AD - u16Min_Room_Temp_AD) / 50);

        u32AD_Room_Temp_Sum  = 0;
        u16Max_Room_Temp_AD = 0;
        u16Min_Room_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_RoomWater(U16 mu16Adc)
{
    return ConvAdc2Temp_ColdWater( mu16Adc );
    /*..hui [23-4-13오전 9:40:23] 정수온도 -> 배관형 온수입수온도 센서로..*/
    /////////return ConvAdc2Temp_HotInWater( mu16Adc );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 1
U16 ConvAdc2Temp_HotInWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_IN_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_IN_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_IN_WATER;
    return temp_hot_in_water_table[ mu16Index ];
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_mixing_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Mixing_Temp_AD)    //Max Save
    {
        u16Max_Mixing_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Mixing_Temp_AD)  //Min   Save
    {
        u16Min_Mixing_Temp_AD = mu16ad_result;
    }

    u32AD_Mixing_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Mixing_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Mixing_Temp = 0;
        gu16_AD_Result_Mixing_Out = (U16)((u32AD_Mixing_Temp_Sum - u16Max_Mixing_Temp_AD - u16Min_Mixing_Temp_AD) / 20);

        u32AD_Mixing_Temp_Sum  = 0;
        u16Max_Mixing_Temp_AD = 0;
        u16Min_Mixing_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_MixingOutWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_OUT_WATER )
    {
        return 1200;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_OUT_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_OUT_WATER;
    return temp_hot_out_water_table[ mu16Index ];
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_amb_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Amb_Temp_AD)    //Max Save
    {
        u16Max_Amb_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Amb_Temp_AD)  //Min   Save
    {
        u16Min_Amb_Temp_AD = mu16ad_result;
    }

    u32AD_Amb_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Amb_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Amb_Temp = 0;
        gu16_AD_Result_Amb = (U16)((u32AD_Amb_Temp_Sum - u16Max_Amb_Temp_AD - u16Min_Amb_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Amb = 1024 - gu16_AD_Result_Amb;

        u32AD_Amb_Temp_Sum  = 0;
        u16Max_Amb_Temp_AD = 0;
        u16Min_Amb_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_amb_side_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Amb_Side_Temp_AD)    //Max Save
    {
        u16Max_Amb_Side_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Amb_Side_Temp_AD)  //Min   Save
    {
        u16Min_Amb_Side_Temp_AD = mu16ad_result;
    }

    u32AD_Amb_Side_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Amb_Side_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Amb_Side_Temp = 0;
        gu16_AD_Result_Amb_Side = (U16)((u32AD_Amb_Side_Temp_Sum - u16Max_Amb_Side_Temp_AD - u16Min_Amb_Side_Temp_AD) / 50);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        gu16_AD_Result_Amb_Side = 1024 - gu16_AD_Result_Amb_Side;

        u32AD_Amb_Side_Temp_Sum  = 0;
        u16Max_Amb_Side_Temp_AD = 0;
        u16Min_Amb_Side_Temp_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_Ambient(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_AMBIENT_TEMP )
    {
        return 0;  // min temperture..
    }

    if( mu16Adc > MAX_ADC_AMBIENT_TEMP )
    {
        return 1000;  // max temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_AMBIENT_TEMP;
    return temp_ambient_table[ mu16Index ];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_fan_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_Fan_Current_Data_AD)    //Max Save
    {
        gu16Max_Fan_Current_Data_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Fan_Current_Data_AD)  //Min   Save
    {
        u16Min_Fan_Current_Data_AD = mu16ad_result;
    }

    u32AD_Fan_Current_Sum += mu16ad_result;

    if(++u8Cnt_Fan_Current_Data >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Fan_Current_Data = 0;
        gu16_AD_Result_Fan_Current = (U16)(u32AD_Fan_Current_Sum - gu16Max_Fan_Current_Data_AD - u16Min_Fan_Current_Data_AD) / 20;

        u32AD_Fan_Current_Sum  = 0;
        gu16Max_Fan_Current_Data_AD = 0;
        u16Min_Fan_Current_Data_AD = 1024;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_uv_ice_tray_two_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tray_Two_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tray_Two_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tray_Two_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tray_Two_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tray_Two_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tray_Two_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tray_Two_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed
            = (U16)(u32AD_UV_Ice_Tray_Two_Current_Feed_Sum - gu16Max_UV_Ice_Tray_Two_Current_Feed_AD - gu16Min_UV_Ice_Tray_Two_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Tray_Two_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tray_Two_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tray_Two_Current_Feed_AD = 1024;
    }
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0

void filtering_cds_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_CDS_AD)    //Max Save
    {
        u16Max_CDS_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_CDS_AD)  //Min   Save
    {
        u16Min_CDS_AD = mu16ad_result;
    }

    u32AD_CDS_Sum += mu16ad_result;

    if(++u8Cnt_CDS >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_CDS = 0;
        gu16ADCds = (U16)((u32AD_CDS_Sum - u16Max_CDS_AD - u16Min_CDS_AD) / 50);

        u32AD_CDS_Sum  = 0;
        u16Max_CDS_AD = 0;
        u16Min_CDS_AD = 1024;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_tray_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Tray_Temp_AD)    //Max Save
    {
        u16Max_Tray_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Tray_Temp_AD)  //Min   Save
    {
        u16Min_Tray_Temp_AD = mu16ad_result;
    }

    u32AD_Tray_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Tray_Temp >= 22)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Tray_Temp = 0;
        gu16_AD_Result_Tray_Temp = (U16)((u32AD_Tray_Temp_Sum - u16Max_Tray_Temp_AD - u16Min_Tray_Temp_AD) / 20);
        /*..hui [23-2-8오후 4:07:44] 풀다운을 풀업으로 변경...*/
        /*gu16_AD_Result_Tray_Temp = 1024 - gu16_AD_Result_Tray_Temp;*/

        u32AD_Tray_Temp_Sum  = 0;
        u16Max_Tray_Temp_AD = 0;
        u16Min_Tray_Temp_AD = 1024;
    }

}


#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 ConvAdc2Temp_HotOutWater(U16 mu16Adc)
{
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_HOT_OUT_WATER )
    {
        return 1200;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_HOT_OUT_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_HOT_OUT_WATER;
    return temp_hot_out_water_table[ mu16Index ];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_in_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_In_Temp_AD)    //Max Save
    {
        gu16Max_TDS_In_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_TDS_In_Temp_AD)  //Min   Save
    {
        gu16Min_TDS_In_Temp_AD = mu16ad_result;
    }

    gu16AD_TDS_In_Temp_Sum += mu16ad_result;

    if(++u8Cnt_TDS_In_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_In_Temp = 0;
        gu16_AD_Result_TDS_In_Temp
            = (gu16AD_TDS_In_Temp_Sum - gu16Max_TDS_In_Temp_AD - gu16Min_TDS_In_Temp_AD) / 50;


        gu16_AD_Result_TDS_In_Org_Temp = gu16_AD_Result_TDS_In_Temp;
        // 센서의 전압에 따른 AD값이 온도가 커질수록 작아지므로,
        // 프로그램 가독성이 좋도록 값이 증가하도록 연산처리
        gu16_AD_Result_TDS_In_Temp = 1024 - gu16_AD_Result_TDS_In_Temp;  // 10bit AD -> 최대값 1024

        gu16AD_TDS_In_Temp_Sum  = 0;
        gu16Max_TDS_In_Temp_AD = 0;
        gu16Min_TDS_In_Temp_AD = 1024;
    }

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_TDS_In_Water(U16 mu16Adc)
{
    return ConvAdc2Temp_HotInWater( mu16Adc );
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_ice_tank_3_front_current_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tank_Front_Current_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tank_Front_Current_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tank_Front_Current_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tank_Front_Current_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tank_Front_Current_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tank_Front_Current >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tank_Front_Current = 0;
        gu16_AD_Result_UV_Ice_Tank_3_Front_Current
            = (U16)(u32AD_UV_Ice_Tank_Front_Current_Sum - gu16Max_UV_Ice_Tank_Front_Current_AD - gu16Min_UV_Ice_Tank_Front_Current_AD) / 50;

        u32AD_UV_Ice_Tank_Front_Current_Sum  = 0;
        gu16Max_UV_Ice_Tank_Front_Current_AD = 0;
        gu16Min_UV_Ice_Tank_Front_Current_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value )
{
    U16 mu16_filted_adc_value;

    /*..hui [17-11-24오후 2:11:22] ACD값 필터링....*/
    mu16_filted_adc_value = (U16)(ad_old_value - (U16)(ad_old_value / 2) + (U16)(ad_now_value / 2));

    return mu16_filted_adc_value;



}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ADC_Start(void)
{
    ADIF = 0;  /* clear INTAD interrupt flag */
    //ADMK = 0;  /* enable INTAD interrupt */
    ADCS = 1;  /* enable AD conversion */
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ADC_Stop(void)
{
    ADCS = 0;  /* disable AD conversion */
    //ADMK = 1;  /* disable INTAD interrupt */
    ADIF = 0;  /* clear INTAD interrupt flag */
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_out_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_Out_Temp_AD)    //Max Save
    {
        gu16Max_TDS_Out_Temp_AD = (U16)mu16ad_result;
    }

    if(mu16ad_result < gu16Min_TDS_Out_Temp_AD)  //Min   Save
    {
        gu16Min_TDS_Out_Temp_AD = (U16)mu16ad_result;
    }

    gu16AD_TDS_Out_Temp_Sum += (U16)mu16ad_result;

    if(++u8Cnt_TDS_Out_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_Out_Temp = 0;
        gu16_AD_Result_TDS_Out_Temp = (gu16AD_TDS_Out_Temp_Sum - gu16Max_TDS_Out_Temp_AD - gu16Min_TDS_Out_Temp_AD) / 50;

        gu16_AD_Result_TDS_Out_Org_Temp = gu16_AD_Result_TDS_Out_Temp;
        // 센서의 전압에 따른 AD값이 온도가 커질수록 작아지므로,
        // 프로그램 가독성이 좋도록 값이 증가하도록 연산처리
        gu16_AD_Result_TDS_Out_Temp = 1024 - gu16_AD_Result_TDS_Out_Temp;  // 10bit AD -> 최대값 1024

        gu16AD_TDS_Out_Temp_Sum  = 0;
        gu16Max_TDS_Out_Temp_AD = 0;
        gu16Min_TDS_Out_Temp_AD = 1024;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U16 ConvAdc2Temp_TDS_Out_Water(U16 mu16Adc)
{
    return ConvAdc2Temp_HotInWater( mu16Adc );
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void filtering_tds_out_data_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_TDS_Out_Data_AD)    //Max Save
    {
        gu16Max_TDS_Out_Data_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_TDS_Out_Data_AD)  //Min   Save
    {
        u16Min_TDS_Out_Data_AD = mu16ad_result;
    }

    u16AD_TDS_Out_Data_Sum += mu16ad_result;

    if(++u8Cnt_TDS_Out_Data >= 12)                   // Sum = count +   Max +   Min
    {
        u8Cnt_TDS_Out_Data = 0;
        gu16_AD_Result_TDS_Out_Data = (U16)(u16AD_TDS_Out_Data_Sum - gu16Max_TDS_Out_Data_AD - u16Min_TDS_Out_Data_AD) / 10;
        gu16_AD_Result_TDS_Out_Data = 1024 - gu16_AD_Result_TDS_Out_Data;

        u16AD_TDS_Out_Data_Sum  = 0;
        gu16Max_TDS_Out_Data_AD = 0;
        u16Min_TDS_Out_Data_AD = 1024;
    }

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



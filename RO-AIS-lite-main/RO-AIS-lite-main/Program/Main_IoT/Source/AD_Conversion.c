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
void filtering_fan_current_adc( U16 mu16ad_result );
void filtering_drain_pump_current_adc( U16 mu16ad_result );
void filtering_hot_pump_current_adc( U16 mu16ad_result );
void filtering_eva_1_temp_adc( U16 mu8ad_result );
void filtering_eva_2_temp_adc( U16 mu8ad_result );
void filtering_ice_full_adc( U16 mu16ad_result );
void filtering_amb_temp_adc( U16 mu8ad_result );
void filtering_cold_temp_adc( U16 mu16ad_result );
void filtering_room_temp_adc( U16 mu8ad_result );
void filtering_leakage_adc( U16 mu16ad_result );
void filtering_uv_faucet_current_feed_adc( U16 mu16ad_result );
void filtering_uv_ice_tank_current_feed_adc( U16 mu16ad_result );
void filtering_cds_adc( U16 mu16ad_result );
void filtering_hot_tank_temp_adc( U16 mu16ad_result );
U16 ConvAdc2Temp_HotTankWater(U16 mu16Adc);
U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value );
U16 ConvAdc2Temp_RoomWater(U16 mu16Adc);
U16 ConvAdc2Temp_ColdWater(U16 mu16Adc);
U16 ConvAdc2Temp_Ambient(U16 mu16Adc);
U16 ConvAdc2Temp_Eva(U16 mu16Adc);

void filtering_dc_current_24V_adc( U16 mu16ad_result );
void filtering_dc_current_12V_adc( U16 mu16ad_result );

void ADC_Start(void);
void ADC_Stop(void);




/***********************************************************************************************************************/
/*..hui [17-11-24���� 1:47:00] �巹������ �ǵ�� ����..*/
U16 gu16_AD_Result_Cold;
U16 gu16ADIceFull;
U16 gu16ADCds;
U16 gu16IceMakingADVal;
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




U16 gu16_AD_Hot_Pump_Current;
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
U16 gu16_Amb_Temperature;
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
U32 gu32AD_TDS_In_Temp_Sum;
U8 u8Cnt_TDS_In_Temp;

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

U16 gu16_AD_Result_UV_Faucet_Current;
U16 gu16Max_UV_Faucet_Current_Feed_AD;
U16 gu16Min_UV_Faucet_Current_Feed_AD;
U32 u32AD_UV_Faucet_Current_Feed_Sum;
U8 u8Cnt_UV_Faucet_Current_Feed;

U16 gu16_AD_Result_UV_Ice_Tank_Current;
U16 gu16Max_UV_Ice_Tank_Current_Feed_AD;
U16 gu16Min_UV_Ice_Tank_Current_Feed_AD;
U32 u32AD_UV_Ice_Tank_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Tank_Current_Feed;

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

               ad_result = get_adc_value( (U8)AD_Channel_Hot_Heater_Temp,
                                           AD_CONV_10BIT);

               filtering_hot_tank_temp_adc(ad_result);

               gu16_Hot_Tank_Temperature = ConvAdc2Temp_HotTankWater(gu16_AD_Result_Hot_Tank_Temp);
               gu8_Hot_Tank_Temperature_One_Degree = (U8)((gu16_Hot_Tank_Temperature + 5) / 10);

               break;

        case AD_Count_2:

               /*..hui [17-11-24���� 2:37:41] �ü� �µ�����..*/
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

        case AD_Count_3:

               /*..hui [17-11-24���� 2:38:01] ���� �µ�����..*/
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

        case AD_Count_4:

               /*..hui [17-11-24���� 2:38:10] ���� ����..*/
               ad_result = get_adc_value( (U8)AD_Channel_Ice_Full_Receive,
                                           AD_CONV_10BIT);

               filtering_ice_full_adc(ad_result);

               break;

        case AD_Count_5:

               /*..hui [17-11-24���� 2:37:48] �ܱ� �µ�����..*/
               ad_result = get_adc_value( (U8)AD_Channel_Amb_Temp,
                                           AD_CONV_10BIT );


               filtering_amb_temp_adc(ad_result);

               gu16_Amb_Temperature = ConvAdc2Temp_Ambient(gu16_AD_Result_Amb);
               gu8_Amb_Temperature_One_Degree = (U8)((gu16_Amb_Temperature + 5) / 10);

               break;

        case AD_Count_6:

               /*..hui [17-11-24���� 2:37:56] ���� �µ�����..*/
               ad_result = get_adc_value( (U8)AD_Channel_EVA_1_TEMP,
                                           AD_CONV_10BIT );

               filtering_eva_1_temp_adc(ad_result);

               gu16_Eva_First_Temperature = ConvAdc2Temp_Eva(gu16_AD_Result_Eva_First);
               gu8_Eva_Cold_Temperature_One_Degree = (U8)((gu16_Eva_First_Temperature + 5) / 10);

               break;

        case AD_Count_7:

               ad_result = get_adc_value( (U8)AD_Channel_EVA_2_TEMP,
                                           AD_CONV_10BIT );

               filtering_eva_2_temp_adc(ad_result);

               gu16_Eva_Second_Temperature = ConvAdc2Temp_Eva(gu16_AD_Result_Eva_Second);
               gu8_Eva_Ice_Temperature_One_Degree = (U8)((gu16_Eva_Second_Temperature + 5) / 10);

               break;

        case AD_Count_8:

               /*..hui [17-11-24���� 2:38:16] ����..*/
               ad_result = get_adc_value( (U8)AD_Channel_Water_Leakage,
                                           AD_CONV_10BIT);

               filtering_leakage_adc(ad_result);


               break;

        case AD_Count_9:


               ad_result = get_adc_value( (U8)AD_Channel_UV_Faucet_Led_Current,
                                           AD_CONV_10BIT);

               filtering_uv_faucet_current_feed_adc(ad_result);


               break;

        case AD_Count_10:

               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Tank_Led_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_tank_current_feed_adc(ad_result);

               break;

        case AD_Count_11:

               ad_result = get_adc_value( (U8)AD_Channel_FAN_Current,
                                           AD_CONV_10BIT );

               filtering_fan_current_adc(ad_result);


               break;

        case AD_Count_12:


               ad_result = get_adc_value( (U8)AD_Channel_Photo_TR,
                                           AD_CONV_10BIT);

               filtering_cds_adc(ad_result);

               break;

        case AD_Count_13:

               ad_result = get_adc_value( (U8)AD_Channel_Hot_Pump_Current,
                                           AD_CONV_10BIT );

               filtering_hot_pump_current_adc(ad_result);

               break;

        case AD_Count_14:

               ad_result = get_adc_value( (U8)AD_Channel_Drain_Pump_Current,
                                           AD_CONV_10BIT );

               filtering_drain_pump_current_adc(ad_result);
			   
               break;

        case AD_Count_15:

               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_24V,
                                           AD_CONV_10BIT);

               filtering_dc_current_24V_adc(ad_result);

               break;

        case AD_Count_16: //ANI20

               ad_result = get_adc_value( (U8)AD_Channel_DC_Current_12V,
                                           AD_CONV_10BIT);

               filtering_dc_current_12V_adc(ad_result);


               u8AdCount = 0;

               break;

        default:

               ADS = AD_Channel_Hot_Heater_Temp;
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

    /*..hui [17-11-24���� 2:11:20] ACD�� ���͸�....*/
    /*mu16_final_ad_value = filtering_adc_value( ad_old_value,
                                          mu16_ad_result );  */

    /*return mu16_final_ad_value;*/

    return mu16_ad_result;
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
        gu16_AD_Hot_Pump_Current = (U16)(u32AD_Hot_Pump_Current_Sum - u16Max_Hot_Pump_Current_AD - u16Min_Hot_Pump_Current_AD) / 50;

        u32AD_Hot_Pump_Current_Sum  = 0;
        u16Max_Hot_Pump_Current_AD = 0;
        u16Min_Hot_Pump_Current_AD = 1024;
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
        /*..hui [23-2-8���� 4:07:44] Ǯ�ٿ��� Ǯ������ ����...*/
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
        /*..hui [23-2-8���� 4:07:44] Ǯ�ٿ��� Ǯ������ ����...*/
        gu16_AD_Result_Eva_Second = 1024 - gu16_AD_Result_Eva_Second;

        u32AD_Eva_2_Temp_Sum  = 0;
        u16Max_Eva_2_Temp_AD = 0;
        u16Min_Eva_2_Temp_AD = 1024;
    }

}

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
        /*..hui [23-2-8���� 4:07:44] Ǯ�ٿ��� Ǯ������ ����...*/
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
    U16 mu16Index;

    if(  mu16Adc < MIN_ADC_ROOM_WATER )
    {
        return 900;  // max temperture..
    }

    if( mu16Adc > MAX_ADC_ROOM_WATER )
    {
        return 0;  // min temperture..
    }

    mu16Index = mu16Adc - MIN_ADC_ROOM_WATER;
    return temp_room_water_table[ mu16Index ];
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
        gu16IceMakingADVal = (U16)((u32AD_Leakage_Sum - u16Max_Leakage_AD - u16Min_Leakage_AD) / 50);

        u32AD_Leakage_Sum  = 0;
        u16Max_Leakage_AD = 0;
        u16Min_Leakage_AD = 1024;
    }

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filtering_uv_faucet_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Faucet_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Faucet_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Faucet_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Faucet_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Faucet_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Faucet_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Faucet_Current_Feed = 0;
        gu16_AD_Result_UV_Faucet_Current
            = (U16)(u32AD_UV_Faucet_Current_Feed_Sum - gu16Max_UV_Faucet_Current_Feed_AD - gu16Min_UV_Faucet_Current_Feed_AD) / 50;

        u32AD_UV_Faucet_Current_Feed_Sum  = 0;
        gu16Max_UV_Faucet_Current_Feed_AD = 0;
        gu16Min_UV_Faucet_Current_Feed_AD = 1024;
    }

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
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
void filtering_hot_tank_temp_adc( U16 mu16ad_result )
{
    if(mu16ad_result > u16Max_Hot_Tank_Temp_AD)    //Max Save
    {
        u16Max_Hot_Tank_Temp_AD = mu16ad_result;
    }

    if(mu16ad_result < u16Min_Hot_Tank_Temp_AD)  //Min   Save
    {
        u16Min_Hot_Tank_Temp_AD = mu16ad_result;
    }

    u32AD_Hot_Tank_Temp_Sum += mu16ad_result;

    if(++u8Cnt_Hot_Tank_Temp >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_Hot_Tank_Temp = 0;
        gu16_AD_Result_Hot_Tank_Temp = (U16)(u32AD_Hot_Tank_Temp_Sum - u16Max_Hot_Tank_Temp_AD - u16Min_Hot_Tank_Temp_AD) / 50;
        /*..hui [23-2-8���� 4:07:44] Ǯ�ٿ��� Ǯ������ ����...*/
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
void filtering_uv_ice_tank_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Tank_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Tank_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Tank_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Tank_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Tank_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Tank_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Tank_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Tank_Current
            = (U16)(u32AD_UV_Ice_Tank_Current_Feed_Sum - gu16Max_UV_Ice_Tank_Current_Feed_AD - gu16Min_UV_Ice_Tank_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Tank_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Tank_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Tank_Current_Feed_AD = 1024;
    }

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
U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value )
{
    U16 mu16_filted_adc_value;

    /*..hui [17-11-24���� 2:11:22] ACD�� ���͸�....*/
    mu16_filted_adc_value = (U16)(ad_old_value - (U16)(ad_old_value / 2) + (U16)(ad_now_value / 2));

    return mu16_filted_adc_value;



}

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



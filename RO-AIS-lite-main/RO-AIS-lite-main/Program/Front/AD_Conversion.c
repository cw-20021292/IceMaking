/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "AD_Conversion.h"

/***********************************************************************************************************************/

void AD_Conversion(void);
U16 get_adc_value( U8 ad_channel, U8 resolution);
void filtering_uv_ice_extraction_current_feed_adc( U16 mu16ad_result );

void ADC_Start(void);
void ADC_Stop(void);




/***********************************************************************************************************************/
/*..hui [17-11-24오후 1:47:00] 드레인펌프 피드백 전류..*/
U16 gu16_AD_Result_Cold;
U16 gu16ADIceFull;
U16 gu16ADCds;
U16 gu16ADLeakage;

U8 u8AdCount;

U16 gu16_AD_Result_UV_Ice_Extraction_Current;
U16 gu16Max_UV_Ice_Extraction_Current_Feed_AD;
U16 gu16Min_UV_Ice_Extraction_Current_Feed_AD;
U32 u32AD_UV_Ice_Extraction_Current_Feed_Sum;
U8 u8Cnt_UV_Ice_Extraction_Current_Feed;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void AD_Conversion(void)
{
    U16 ad_result = 0;
    U8 mu8_ad_channel;

    //u8AdCount++;

    switch(u8AdCount)
    {
			   
        case AD_Count_1:

               ad_result = get_adc_value( (U8)AD_Channel_UV_Ice_Extraction_Led_Current,
                                           AD_CONV_10BIT);

               filtering_uv_ice_extraction_current_feed_adc(ad_result);
               break;

			   
        default:

               ADS = AD_Channel_UV_Ice_Extraction_Led_Current;
               u8AdCount = 1;

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
void filtering_uv_ice_extraction_current_feed_adc( U16 mu16ad_result )
{
    if(mu16ad_result > gu16Max_UV_Ice_Extraction_Current_Feed_AD)    //Max Save
    {
        gu16Max_UV_Ice_Extraction_Current_Feed_AD = mu16ad_result;
    }

    if(mu16ad_result < gu16Min_UV_Ice_Extraction_Current_Feed_AD)  //Min   Save
    {
        gu16Min_UV_Ice_Extraction_Current_Feed_AD = mu16ad_result;
    }

    u32AD_UV_Ice_Extraction_Current_Feed_Sum += mu16ad_result;

    if(++u8Cnt_UV_Ice_Extraction_Current_Feed >= 52)                   // Sum = count +   Max +   Min
    {
        u8Cnt_UV_Ice_Extraction_Current_Feed = 0;
        gu16_AD_Result_UV_Ice_Extraction_Current
            = (U16)(u32AD_UV_Ice_Extraction_Current_Feed_Sum - gu16Max_UV_Ice_Extraction_Current_Feed_AD - gu16Min_UV_Ice_Extraction_Current_Feed_AD) / 50;

        u32AD_UV_Ice_Extraction_Current_Feed_Sum  = 0;
        gu16Max_UV_Ice_Extraction_Current_Feed_AD = 0;
        gu16Min_UV_Ice_Extraction_Current_Feed_AD = 1024;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 filtering_adc_value( U16 ad_old_value, U16 ad_now_value )
{
    U16 mu16_filted_adc_value;

    /*..hui [17-11-24오후 2:11:22] ACD값 필터링....*/
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



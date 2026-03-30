/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _AD_CONVERSION_H_
#define _AD_CONVERSION_H_

#define AD_Count_1                         1
#define AD_Count_2                         2
#define AD_Count_3                         3
#define AD_Count_4                         4
#define AD_Count_5                         5
#define AD_Count_6                         6
#define AD_Count_7                         7
#define AD_Count_8                         8
#define AD_Count_9                         9
#define AD_Count_10                        10
#define AD_Count_11                        11
#define AD_Count_12                        12
#define AD_Count_13                        13
#define AD_Count_14                        14
#define AD_Count_15                        15
#define AD_Count_16                        16
#define AD_Count_17                        17






//#define AD_Channel_Hot_Heater_Temp                  0
//#define AD_Channel_Cold_Temp                        1
//#define AD_Channel_Room_Temp                        2
//#define AD_Channel_Ice_Full_Receive                 3
//#define AD_Channel_Amb_Temp                         4
//#define AD_Channel_EVA_1_TEMP                       5
//#define AD_Channel_EVA_2_TEMP                       6
///#define AD_Channel_Water_Leakage                    7
//#define AD_Channel_UV_Faucet_Led_Current            8
//#define AD_Channel_FAN_Current                      10
//#define AD_Channel_Photo_TR                         11
//#define AD_Channel_Hot_Pump_Current                 12
//#define AD_Channel_Drain_Pump_Current               13

//ANI0으로 옮기기전 AD Conversion용 정의 
#define AD_Channel_UV_Ice_Extraction_Led_Current	  0




#define AD_CONV_10BIT                      6
#define AD_CONV_8BIT                       8



extern void R_ADC_Start(void);
extern void R_ADC_Stop(void);


extern bit bit_adc_cold_start;
extern bit bit_adc_room_start;




#endif


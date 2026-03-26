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
#define AD_Count_18                        18
#define AD_Count_19                        19
#define	AD_Count_20						   20
#define	AD_Count_21						   21
#define	AD_Count_22						   22





#define AD_Channel_DC_Current_24V                   0
#define AD_Channel_DC_Current_12V                   1
#define AD_Channel_Drain_Pump_Current               2
#define AD_Channel_Hot_Heater_Temp                  3
#define AD_Channel_Hot_Pump_Current                 4
#define AD_Channel_UV_Water_Tank_Current            5
#define AD_Channel_UV_Ice_Tank_Current              6
#define AD_Channel_UV_Ice_Tray_1_2_Current          7
#define AD_Channel_Ice_Full_Receive                 8
#define AD_Channel_Water_Leakage                    9
#define AD_Channel_EVA_1_TEMP                       10
#define AD_Channel_Cold_Temp                        11
#define AD_Channel_Room_Temp                        12
#define AD_Channel_Cold_Mixing_Temp                 13
#define AD_Channel_Amb_Temp                         14
#define AD_Channel_FAN_Current                      18
#define AD_Channel_Amb_Temp_Side                    19
/*#define AD_Channel_UV_Ice_Tray_Two_Current          21*/
#define AD_Channel_UV_Ice_Tank_Front_Current        22

#if 0
#define AD_Channel_TDS_IN_Temp				        23
#define AD_Channel_TDS_OUT_Temp				        24
#define AD_Channel_TDS_OUT_Data				        25
#endif




extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2





#define AD_CONV_10BIT                      6
#define AD_CONV_8BIT                       8



extern void R_ADC_Start(void);
extern void R_ADC_Stop(void);


extern bit bit_adc_cold_start;
extern bit bit_adc_room_start;


extern U16 gu16TDS_OUT_Pulse_Time;


#endif


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
#include    "tds_out_calculation.h"
#include    "math.h"

#if 0
void tds_out_control(void);
void TDS_Out_Pulse_Control(void);
void TDSOutTEMP_Calculation(void);
void TDSOut_Calculation(void);
void compensate_tds_out(void);
#endif

// 정수
U8 gu8TDS_CheckTimeCnt;          // TDS를 체크하는 시간 카운터
U16 gu16TDS_OUT_Pulse_Time;       // 원수 TDS 펄스 출력 체크하는 Timer
U16 gu16TDS_Out_Temp_Final;
U8 gu8TDS_OUT_AVR_Count;          // 정수 TDS 평균을 위한 적산을 카운트
U32 gu32TDS_OUT_Sum;               // 정수 TDS 평균을 위한 적산
U16 gu16TDS_OUT_Max;               // 정수 TDS 평균을 위한 최고값
U16 gu16TDS_OUT_Min;               // 정수 TDS 평균을 위한 최저값
U16 gu16TDS_OUT_Data;              // 정수 TDS 결과 Data
U16 gu16TDS_OUT_Final;             // 정수 TDS 최종 Data
U16 gu16TDS_OUT_Middle;            // 정수 TDS 중간 Data
U8  gu8TDS_TurnOn_Time;
//add
U16 gu16TDS_OUT_Final_temp;

bit F_TDS_Interim_Check;

//add
U16 gu16_tds_out_before;

#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tds_out_control(void)
{
    TDSOutTEMP_Calculation();
    TDSOut_Calculation();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//
/* Function Information--------------------------------------------------------
※ 함수명: OUTPUT TDS
※ 설  명: TDS_IN (환기연)
           TDS_OUT(기술연)
※ 작성자: Phil
※ 작성일: 2016.4.11
※ 사용처: Int_interval()
※ 주  기: 1ms
------------------------------------------------------------------------------*/
//------------------------------------------------------------------------------
//                      Output TDS Pulse Control (Per 0.5ms)
//------------------------------------------------------------------------------
void TDS_Out_Pulse_Control(void)
{
    #if 0
    /*..hui [24-7-19오전 11:00:07] 디스플레이 테스트모드에서는 패스..*/
    if( u8FactoryTestMode == DISPLAY_TEST_MODE )
    {
        return;
    }
    else{}
    #endif

    if(F_TDS_ON == SET)
    {
        if (gu16TDS_OUT_Pulse_Time-- == 0)
        {
            gu16TDS_OUT_Pulse_Time = 50;
        }
        else{}

        // 50ms * 50 = 250ms 중 25ms 씩 반복 출력하는군
        // 20 ~ 16
        if(gu16TDS_OUT_Pulse_Time == 20 || gu16TDS_OUT_Pulse_Time == 19 ||
           gu16TDS_OUT_Pulse_Time == 18 || gu16TDS_OUT_Pulse_Time == 17 ||
           gu16TDS_OUT_Pulse_Time == 16)
        {
            pTDS_OUT_Power1 = 1;
            pTDS_OUT_Power2 = 0;
        }
        else if(gu16TDS_OUT_Pulse_Time == 15 || gu16TDS_OUT_Pulse_Time == 14
               || gu16TDS_OUT_Pulse_Time == 13 || gu16TDS_OUT_Pulse_Time == 12
               || gu16TDS_OUT_Pulse_Time == 11)
        {
            pTDS_OUT_Power1 = 0;
            pTDS_OUT_Power2 = 1;
        }
        else
        {
            pTDS_OUT_Power1 = 0;
            pTDS_OUT_Power2 = 0;
        }
    }
    else
    {
        gu16TDS_OUT_Pulse_Time = 50;
        pTDS_OUT_Power1 = 0;
        pTDS_OUT_Power2 = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      Output TDS 온도 계산 (Per 100ms)
//------------------------------------------------------------------------------
void TDSOutTEMP_Calculation(void)   // per 100ms
{
    D64 md64TDSOutTemp1_Voltage = 0;
    D64 md64TDSOutTemp2_Voltage = 0;
    D64 md64TDSOutTemp_Resistance = 0;

    md64TDSOutTemp1_Voltage   = (1024 - gu16_AD_Result_TDS_Out_Temp) * 0.0048828125;
    md64TDSOutTemp2_Voltage   = gu16_AD_Result_TDS_Out_Temp * 0.0048828125;
    md64TDSOutTemp_Resistance = (md64TDSOutTemp1_Voltage / (md64TDSOutTemp2_Voltage / 10000));
    gu16TDS_Out_Temp_Final    = (U16)(fabs((((1 / (pow((md64TDSOutTemp_Resistance / 1000.0), 0.09305))) * 369.8154) - 273.15) * 10));

    if(gu16_AD_Result_TDS_Out_Temp < 5)
    {
        gu16TDS_Out_Temp_Final = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      Output TDS 보정 확정 (Per 100ms)
//------------------------------------------------------------------------------
void TDSOut_Calculation(void)
{
    D64 md64TDSOut1_Voltage = 0;
    D64 md64TDSOut2_Voltage = 0;
    D64 md64TDSOut_Resistance = 0;

    if(F_TDS_ON == SET)
    {
        md64TDSOut1_Voltage = gu16_AD_Result_TDS_Out_Data * 0.0048828125;
        md64TDSOut2_Voltage = (1024 - gu16_AD_Result_TDS_Out_Data) * 0.0048828125;
        md64TDSOut_Resistance = (md64TDSOut2_Voltage / (md64TDSOut1_Voltage / 1088));
        gu16TDS_OUT_Data = (U16)(fabs((((((1 / ((-16.3984575 + md64TDSOut_Resistance) * (-0.0000150134 + 0.0000000592714 * ((gu16TDS_Out_Temp_Final / 10) + 273.15)))) + 0.694408181818182) * 0.798594) / 1.36198))));  // Plate Type

        if (gu16_AD_Result_TDS_Out_Data < 8)
        {
            gu16TDS_OUT_Data = 0;     // gu16AdTDS_OutData와는 다름
        }
        else{}

        gu32TDS_OUT_Sum += gu16TDS_OUT_Data;

        if(gu16TDS_OUT_Data > gu16TDS_OUT_Max)
        {
            gu16TDS_OUT_Max = gu16TDS_OUT_Data;      // 최대값 저장
        }
        else{}

        if(gu16TDS_OUT_Data < gu16TDS_OUT_Min)
        {
            gu16TDS_OUT_Min = gu16TDS_OUT_Data;      // 최소값 저장
        }
        else{}

        if(++gu8TDS_OUT_AVR_Count >= 5)
        {
            gu16TDS_OUT_Data = (U16)((gu32TDS_OUT_Sum - (gu16TDS_OUT_Max + gu16TDS_OUT_Min)) / 3);

            /*gu16TDS_OUT_Final = gu16TDS_OUT_Data;*/

            /*..hui [23-3-7오후 1:43:26] 출수 TDS 보상 추가..*/
			gu16_tds_out_before = gu16TDS_OUT_Data;
            compensate_tds_out();
			gu16TDS_OUT_Final_temp = gu16TDS_OUT_Final;


            gu8TDS_OUT_AVR_Count = 0;
            gu32TDS_OUT_Sum = 0;
            gu16TDS_OUT_Max = 0;
            gu16TDS_OUT_Min = 1024;
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void compensate_tds_out(void)
{
    /*..sean TDS 추가 보상 */
    if((TDS_TEMP10_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP20_0))
    {
	    if( gu16TDS_OUT_Data >= 200 )
	    {
        	gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.88);
	    }
		else {}
    }
    else if((TDS_TEMP20_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP30_0))
    {
	    if( gu16TDS_OUT_Data >= 200 )
	    {
        	gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.87);
	    }
		else {}
    }
    else if(gu16_AD_Result_TDS_Out_Temp >= TDS_TEMP30_0)
    {
	    if( gu16TDS_OUT_Data >= 400 )
	    {
        	gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.90);
	    }
		else {}
    }
    else{}

    /*..hui [23-3-7오후 1:52:46] TDS 출수 보상..*/
/*
    if((TDS_TEMP7_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP8_0))
    {
        gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.80);
    }
    else if((TDS_TEMP8_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP9_0))
    {
        gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.81);
    }
    else if((TDS_TEMP9_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP10_0))
    {
        gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.82);
    }
    else if((TDS_TEMP10_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP11_0))
    {
        gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.83);
    }
    else if((TDS_TEMP11_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP12_0))
    {
        gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.85);
    }
    else if((TDS_TEMP12_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP13_0))
    {
       gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.89);
    }
    else if((TDS_TEMP13_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP14_0))
    {
       gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.93);
    }
    else if((TDS_TEMP15_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP15_0))
    {
       gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.97);
    }
    else if((TDS_TEMP16_0 <= gu16_AD_Result_TDS_Out_Temp) && (gu16_AD_Result_TDS_Out_Temp < TDS_TEMP17_0))
    {
       gu16TDS_OUT_Data = (U16)(gu16TDS_OUT_Data * 0.98);
    }
    else{}
*/
    gu16TDS_OUT_Final = gu16TDS_OUT_Data;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



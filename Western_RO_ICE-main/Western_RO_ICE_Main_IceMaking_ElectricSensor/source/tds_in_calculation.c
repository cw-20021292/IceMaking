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
#include    "tds_in_calculation.h"

#if 0
void TDS_In_Control(void);
void TDS_In_FACTOR(void);
void INTP4_TDS_Input(void);
#endif

bit F_TDS_ON;                     // 원수/정수 TDS 측정 Start
bit F_TDS_IN_Check;               // 원수 주파수 측정 지시
bit F_TDS_Decide;                 // 원수 TDS 보정 및 변환


U16  gu16Cnt100ms_TDS;             // 원수 TDS 측정 주파수를 위한 카운트
U16  gu16TDS_IN_Pulse;             // 원수 TDS 측정 주파수
U16  gu16Factor_Temp_1;            // 원수 TDS 변환 버퍼
U8   gu8TDS_IN_AVR_Count;          // 원수 TDS 평균을 위한 적산을 카운트
U32  gu32TDS_IN_Sum;               // 원수 TDS 평균을 위한 적산
U16  gu16TDS_IN_Max;               // 원수 TDS 평균을 위한 최고값
U16  gu16TDS_IN_Min;               // 원수 TDS 평균을 위한 최저값
U16  gu16TDS_IN_Data;              // 원수 TDS 결과 Data
U16  gu16TDS_IN_Final;             // 원수 TDS 최종 Data

U16 gu16TDS_IN_CON;



U8 gu8TDS_IN_Level;

#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/* Function Information--------------------------------------------------------
※ 함수명: INPUT TDS
※ 설  명: TDS_IN (환기연)
           TDS_OUT(기술연)
※ 작성자: Phil
※ 작성일: 2016.4.11
※ 사용처: Int_interval()
※ 주  기: 1ms
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//                      INPUT TDS Control
//------------------------------------------------------------------------------
void TDS_In_Control(void)   // per 1ms
{
    if(F_TDS_ON == SET)
    {

        pTDS_IN_Power = 0;                // Power ON
        F_TDS_IN_Check = 1;               // Enable Interrupt Count

        if(++gu16Cnt100ms_TDS >= 100)     // 100ms후에 (1초 너무 길어 사전판단)
        {
            gu16Cnt100ms_TDS = 0;
            F_TDS_Decide = 1;               // TDS 계산 및 판단
        }
        else{}
    }
    else
    {
        pTDS_IN_Power = 1;                // Power OFF
        gu16Cnt100ms_TDS = 0;
        F_TDS_IN_Check = 0;               // Disable Interrupt Count
        F_TDS_Decide = 0;

        gu16TDS_IN_Pulse = 0;
    }

    // 입력 TDS 보정 및 판단
    if(F_TDS_Decide == SET)
    {
        F_TDS_Decide = 0;

        gu16TDS_IN_CON = gu16TDS_IN_Pulse * 10;     // 입수 주파수(초당 Pulse 갯수)
        TDS_In_FACTOR();                   // TDS 보정

        if( u8FactoryTestMode != NONE_TEST_MODE )
        {
            gu16_uart_test_pulse = gu16TDS_IN_Pulse;
        }
        else{}

        gu16TDS_IN_Pulse = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//------------------------------------------------------------------------------
//                      TDS FACTOR (TDS 보정)
//------------------------------------------------------------------------------
void TDS_In_FACTOR(void)
{
    gu16Factor_Temp_1 = gu16TDS_IN_Pulse * 10;      // 100ms동안 입력된 Signal로 1초 데이터 추정 연산

// 전장팀 2017년 2월 9일 안
// 입수 온도 6도 미만   : y = 2E-08x3 + 0.0001x2 + 0.4091x + 0.2205
// 입수 온도 6 ~ 9도    : y = 2E-08x3 + 1E-04x2 + 0.3832x + 0.1762
// 입수 온도 9 ~ 11도   : y = 2E-08x3 + 8E-05x2 + 0.3462x + 0.1615
// 입수 온도 11 ~ 14도  : y = 3E-08x3 + 6E-05x2 + 0.3284x - 0.6361
// 입수 온도 14 ~ 16도  : y = 4E-08x3 + 3E-05x2 + 0.3131x - 1.4181
// 입수 온도 16 ~ 19도  : y = 3E-08x3 + 5E-05x2 + 0.2899x - 0.8228
// 입수 온도 19 ~ 21도  : y = 2E-08x3 + 6E-05x2 + 0.2683x - 0.155
// 입수 온도 21 ~ 24도  : y = 2E-08x3 + 5E-05x2 + 0.2532x - 0.1544
// 입수 온도 24 ~ 26도  : y = 2E-08x3 + 5E-05x2 + 0.2398x - 0.1511
// 입수 온도 26 ~ 29도  : y = 2E-08x3 + 4E-05x2 + 0.2235x + 0.0222
// 입수 온도 29 ~ 31도  : y = 2E-08x3 + 4E-05x2 + 0.2095x + 0.1505
// 입수 온도 31 ~ 34도  : y = 3E-08x3 + 1E-05x2 + 0.2118x - 3.0446
// 입수 온도 34도 이상  : y = 3E-08x3 - 9E-06x2 + 0.2217x - 6.3495

    // 전도도 계산(?)
    if (gu16_AD_Result_TDS_In_Temp < TDS_TEMP6_0)
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.0001 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.4091 * (D64)(gu16Factor_Temp_1)) + 0.2205);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP6_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP9_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.0001 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.3832 * (D64)(gu16Factor_Temp_1)) + 0.1762);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP9_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP11_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00008 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.3462 * (D64)(gu16Factor_Temp_1)) + 0.1615);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP11_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP14_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000003 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00006 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.3284 * (D64)(gu16Factor_Temp_1)) - 0.6361);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP14_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP16_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000004 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00003 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.3131 * (D64)(gu16Factor_Temp_1)) - 1.4181);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP16_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP19_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000003 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00005 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2899 * (D64)(gu16Factor_Temp_1)) - 0.8228);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP19_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP21_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00006 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2683 * (D64)(gu16Factor_Temp_1)) - 0.155);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP21_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP24_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00005 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2532 * (D64)(gu16Factor_Temp_1)) - 0.1544);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP24_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP26_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00005 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2398 * (D64)(gu16Factor_Temp_1)) - 0.1511);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP26_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP29_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00004 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2235 * (D64)(gu16Factor_Temp_1)) + 0.0222);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP29_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP31_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000002 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00004 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2095 * (D64)(gu16Factor_Temp_1)) + 0.1505);
    }
    else if ((gu16_AD_Result_TDS_In_Temp >= TDS_TEMP31_0) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP34_0))
    {
        gu16TDS_IN_Data = (U16)((0.00000003 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.00001 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2118 * (D64)(gu16Factor_Temp_1)) - 3.0446);
    }
    else if (gu16_AD_Result_TDS_In_Temp >= TDS_TEMP34_0)
    {
        gu16TDS_IN_Data = (U16)((0.00000003 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) - (0.000009 * ((D64)(gu16Factor_Temp_1) * (D64)(gu16Factor_Temp_1))) + (0.2217 * (D64)(gu16Factor_Temp_1)) - 6.3495);
    }
    else{}


    // 온도에 따른 TDS값 보정
    if((TDS_TEMP6_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP7_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.83);
    }
    else if((TDS_TEMP7_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP8_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.82);
    }
    else if((TDS_TEMP8_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP9_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.80);
    }
    else if((TDS_TEMP9_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP10_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.87);
    }
    else if((TDS_TEMP10_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP11_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP11_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP12_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP12_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP13_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP13_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP14_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.80);
    }
    else if((TDS_TEMP14_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP15_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP15_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP16_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.82);
    }
    else if((TDS_TEMP16_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP17_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP17_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP18_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.82);
    }
    else if((TDS_TEMP18_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP19_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.80);
    }
    else if((TDS_TEMP19_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP20_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP20_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP21_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP21_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP22_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP22_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP23_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP23_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP24_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.82);
    }
    else if((TDS_TEMP24_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP25_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP25_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP26_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.82);
    }
    else if((TDS_TEMP26_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP27_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP27_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP28_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP28_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP29_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.83);
    }
    else if((TDS_TEMP29_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP30_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP30_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP31_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP31_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP32_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.90);
    }
    else if((TDS_TEMP32_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP33_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.85);
    }
    else if((TDS_TEMP33_0 <= gu16_AD_Result_TDS_In_Temp) && (gu16_AD_Result_TDS_In_Temp < TDS_TEMP34_0))
    {
      gu16TDS_IN_Data = (U16)(gu16TDS_IN_Data * 0.83);
    }

    if (!gu16TDS_IN_Pulse)
    {
        gu16TDS_IN_Data = 0;
    }
    else{}

    // 평균값 구하기
    gu32TDS_IN_Sum += gu16TDS_IN_Data;

    if (gu16TDS_IN_Data > gu16TDS_IN_Max)
    {
        gu16TDS_IN_Max = gu16TDS_IN_Data;      // 최대값 저장
    }
    else{}

    if (gu16TDS_IN_Data < gu16TDS_IN_Min)
    {
      gu16TDS_IN_Min = gu16TDS_IN_Data;      // 최소값 저장
    }
    else{}

    if (++gu8TDS_IN_AVR_Count >= 10)
    {
        gu16TDS_IN_Data = (U16)((gu32TDS_IN_Sum - (gu16TDS_IN_Max + gu16TDS_IN_Min)) / 8);

        //gu16TDS_IN_Data = 550;     // TEST

        gu16TDS_IN_Final = gu16TDS_IN_Data;

        if(gu16TDS_IN_Final <= 160)
        {
            gu8TDS_IN_Level = 0;
        }
        else if(gu16TDS_IN_Final > 160 && gu16TDS_IN_Final <= 200)
        {
            gu8TDS_IN_Level = 1;
        }
        else if(gu16TDS_IN_Final > 200 && gu16TDS_IN_Final <= 250)
        {
            gu8TDS_IN_Level = 2;
        }
        else if(gu16TDS_IN_Final > 250 && gu16TDS_IN_Final < 350)
        {
            gu8TDS_IN_Level = 3;
        }
        else if(gu16TDS_IN_Final > 350 && gu16TDS_IN_Final < 500)
        {
            gu8TDS_IN_Level = 4;
        }
        else if(gu16TDS_IN_Final > 500)
        {
            gu8TDS_IN_Level = 5;
        }
        else{}

        gu8TDS_IN_AVR_Count = 0;
        gu32TDS_IN_Sum = 0;
        gu16TDS_IN_Max = 0;
        gu16TDS_IN_Min = 1024;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void INTP4_TDS_Input(void)
{
    if(F_TDS_IN_Check == SET)
    {
        if(gu16TDS_IN_Pulse < 6000)
        {
            ++gu16TDS_IN_Pulse;
        }
        else{}
    }
    else{}
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


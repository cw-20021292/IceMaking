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
#include    "uv_ice_extraction.h"



U8 uv_ice_extraction_control(void);
U8 ice_extraction_uv_standby(void);
void output_ice_extraction_uv(void);
void ice_extraction_uv_operation_timer(void);
void start_ice_extraction_uv(void);
void initial_ice_extraction_uv_timer(void);
U8 uv_ice_extraction_standby_timer(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8IceExtractionUvONB;
#define            u8IceExtractionUvON                         U8IceExtractionUvONB.byte
#define            Bit0_Ice_Extraction_UV_On_State             U8IceExtractionUvONB.Bit.b0




TYPE_BYTE          U8IceExtractionUvOFFB;
#define            u8IceExtractionUvOFF                        U8IceExtractionUvOFFB.byte
#define            Bit0_Extraction_Open_UV_Off_State           U8IceExtractionUvOFFB.Bit.b0
#define            Bit1_Ice_Extract_UV_Off_State         U8IceExtractionUvOFFB.Bit.b1
#define            Bit2_Auto_UV_Off_State                U8IceExtractionUvOFFB.Bit.b2
#define            Bit3_Ice_Error_UV_Off_State           U8IceExtractionUvOFFB.Bit.b3



extern TYPE_BYTE          U812VPowerControl;
#define            u8PowerControl12V                     U812VPowerControl.byte
#define            Bit0_Gas_Switch_12V_Out_State         U812VPowerControl.Bit.b0
#define            Bit1_Ice_Tank_UV_12V_Out_State        U812VPowerControl.Bit.b1
#define            Bit2_Uart_Test_Mode_State             U812VPowerControl.Bit.b2
#define            Bit3_Faucet_UV_12V_Out_State          U812VPowerControl.Bit.b3
#define			   Bit4_Ice_Extraction_UV_12V_Out_State	 U812VPowerControl.Bit.b4
#define			   Bit5_Drain_Pump_12V_Out_State	 	 U812VPowerControl.Bit.b5




/***********************************************************************************************************************/

U8 gu8_uv_ice_extraction_step;
U16 gu16_ice_extraction_uv_operation_timer_sec;
U16 gu16_ice_extraction_uv_operation_timer_min;
U16 gu16_ice_extraction_uv_operation_timer_hour;

U16 gu16_ice_extraction_uv_standby_timer_sec;
U16 gu16_ice_extraction_uv_standby_timer_min;
U16 gu16_ice_extraction_uv_standby_timer_hour;

bit bit_ice_extraction_uv_start;

bit bit_uv_ice_extraction_out;

bit F_IceExtractUVSet;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_ice_extraction_uv(void)
{
    Bit0_Ice_Extraction_UV_On_State = uv_ice_extraction_control();

    if( F_Ice == SET )
    {
        Bit1_Ice_Extract_UV_Off_State = F_Ice;
    }
    else
    {
        if( gu16StepMotor2 == 0 )
        {
            Bit1_Ice_Extract_UV_Off_State = CLEAR;
        }
        else{}
    }

/***********************************************************************************************/
    if( u8IceExtractionUvOFF > 0 )
    {
        //pUV_LED_ICE_EXTRACT = CLEAR;                  /*off*/
        bit_uv_ice_extraction_out = CLEAR;
        Bit4_Ice_Extraction_UV_12V_Out_State = CLEAR;
    }
    else
    {
        if( u8IceExtractionUvON > 0 )
        {
            //pUV_LED_ICE_EXTRACT = SET;                 /*on*/
            bit_uv_ice_extraction_out = SET;
        	Bit4_Ice_Extraction_UV_12V_Out_State = SET;
        }
        else
        {
            //pUV_LED_ICE_EXTRACT = CLEAR;              /*off*/
            bit_uv_ice_extraction_out = CLEAR;
        	Bit4_Ice_Extraction_UV_12V_Out_State = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_ice_extraction_control(void)
{
    U8 mu8_return = 0;
    U8 UV_ice_extraction_start;
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}
/*
    if( F_IceOn == CLEAR )
    {
        initial_ice_extraction_uv_timer();
        gu8_uv_ice_extraction_step = 0;
        bit_ice_extraction_uv_start = CLEAR;
        return CLEAR;
    }
    else{}
*/
    switch( gu8_uv_ice_extraction_step )
    {
        case 0 :

            UV_ice_extraction_start = uv_ice_extraction_standby_timer();

            if(UV_ice_extraction_start == SET)
            {
                gu8_uv_ice_extraction_step++;
                start_ice_extraction_uv();
            }
            else{}

        break;

        case 1 :

            /*..hui [19-10-24���� 8:34:49] 10�� ����..*/
            if(bit_ice_extraction_uv_start == SET)
            {
                // ���� ���� �Ǵ� �Ѳ������� ��쿡��?����..
                if( F_IceOn == SET )
                {
                    ice_extraction_uv_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu8_uv_ice_extraction_step = 0;
            }

        break;

        default :

            gu8_uv_ice_extraction_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_extraction_uv(void)
{
    bit_ice_extraction_uv_start = SET;
	initial_ice_extraction_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_ice_extraction_uv(void)
{
    bit_ice_extraction_uv_start = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_uv_operation_timer(void)
{
    gu16_ice_extraction_uv_operation_timer_sec++;

    if(gu16_ice_extraction_uv_operation_timer_sec >= 600)
    {
        gu16_ice_extraction_uv_operation_timer_sec = 0;
        gu16_ice_extraction_uv_operation_timer_min++;
    }
    else{}

    /*..hui [23-2-10���� 10:56:02] �Ŀ��?UV�� 30�и� ����..*/
	/*..sean [23-7-14 ���� 3:52:12 ] 30�� �������� 1�ð� �������� ����  ..*/
    //if(gu16_faucet_uv_operation_timer_min >= 30)
    if(gu16_ice_extraction_uv_operation_timer_min >= 15)
    {
        bit_ice_extraction_uv_start = CLEAR;
        initial_ice_extraction_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_extraction_uv_timer(void)
{
    gu16_ice_extraction_uv_operation_timer_sec = 0;
    gu16_ice_extraction_uv_operation_timer_min = 0;
    gu16_ice_extraction_uv_operation_timer_hour = 0;
	
    gu16_ice_extraction_uv_standby_timer_sec = 0;
    gu16_ice_extraction_uv_standby_timer_min = 0;
    gu16_ice_extraction_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_ice_extraction_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_ice_extraction_uv_standby_timer_sec++;

    if(gu16_ice_extraction_uv_standby_timer_sec >= 600)
    {
        gu16_ice_extraction_uv_standby_timer_sec = 0;
        gu16_ice_extraction_uv_standby_timer_min++;
    }
    else{}

    if(gu16_ice_extraction_uv_standby_timer_min >= 60)
    {
        gu16_ice_extraction_uv_standby_timer_min = 0;
        gu16_ice_extraction_uv_standby_timer_hour++;
    }
    else{}

	if( gu16_ice_extraction_uv_standby_timer_hour >= 5)
    {
	    if(gu16_ice_extraction_uv_standby_timer_min >= 45)
	    {
	        initial_ice_extraction_uv_timer();
	        mu8_return = SET;
	    }
    }
    else{}

	//for test
	/*
	if( gu16_ice_extraction_uv_standby_timer_hour >= 0)
    {
	    if(gu16_ice_extraction_uv_standby_timer_min >= 1)
	    {
	        initial_ice_extraction_uv_timer();
	        mu8_return = SET;
	    }
    }
    else{}
*/
    return mu8_return;
}


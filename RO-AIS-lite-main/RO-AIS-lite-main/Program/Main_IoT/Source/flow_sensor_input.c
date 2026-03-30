/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "flow_sensor_input.h"

void flow_sensor_start(void);
void flow_sensor_stop(void);
void INTP7_Flow_Sensor_Input(void);
void flow_input_count(void);
void calculate_flow_input(void);
U8 conv_hz_to_flow( U8 mu8_flow_hz );
U16 conv_hot_hz( U8 mu8_flow_hz );



bit F_Flow_Meter;
U8 gu8CntFlowMeter;


U8 gu8_Flow_1sec;


U8 gu8Flow10_J;
U8 gu8Flow10_I;
U8 gu8Flow10_H;
U8 gu8Flow10_G;
U8 gu8Flow10_F;
U8 gu8Flow10_E;
U8 gu8Flow10_D;
U8 gu8Flow10_C;
U8 gu8Flow10_B;
U8 gu8Flow10_A;

U16 gu16Effluent_Hz;

U8 gu8_Hot_Flow_Rate;

U8 gu8_Tray_Flow_1sec;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_sensor_start(void)
{
    R_INTC7_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_sensor_stop(void)
{
    R_INTC7_Stop();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void INTP7_Flow_Sensor_Input(void)
{
    F_Flow_Meter = SET;

    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        if(u8WaterOutState == HOT_WATER_SELECT && F_WaterOut == SET)
        {
            //
        }
        else
        {
            /*if(pVALVE_ICE_TRAY_IN == SET)*/
            if( bit_tray_pump_output == SET )
            {
                if(gu16_Ice_Tray_Fill_Hz > 0)
                {
                    gu16_Ice_Tray_Fill_Hz--;
                }
                else{}
            }
            else{}
        }
    }
    else{}

    flow_sensor_stop();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_input_count(void)
{
    if(F_Flow_Meter == SET)
    {
        F_Flow_Meter = CLEAR;
        gu8CntFlowMeter++;

        flow_sensor_start();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calculate_flow_input(void)
{
    gu8Flow10_A = gu8CntFlowMeter;
    gu8CntFlowMeter = 0;
    gu8_Flow_1sec = (gu8Flow10_J + gu8Flow10_I + gu8Flow10_H + gu8Flow10_G + gu8Flow10_F
                          + gu8Flow10_E + gu8Flow10_D + gu8Flow10_C + gu8Flow10_B + gu8Flow10_A);

    gu8Flow10_J = gu8Flow10_I;
    gu8Flow10_I = gu8Flow10_H;
    gu8Flow10_H = gu8Flow10_G;
    gu8Flow10_G = gu8Flow10_F;
    gu8Flow10_F = gu8Flow10_E;
    gu8Flow10_E = gu8Flow10_D;
    gu8Flow10_D = gu8Flow10_C;
    gu8Flow10_C = gu8Flow10_B;
    gu8Flow10_B = gu8Flow10_A;

    gu8_Hot_Flow_Rate = conv_hz_to_flow( gu8_Flow_1sec );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 conv_hz_to_flow( U8 mu8_flow_hz )
{
    U8 mu8_return = 0;

    if(mu8_flow_hz < 5)
    {
        mu8_return = 0;
    }
    else if(mu8_flow_hz >= 5 && mu8_flow_hz < 10)    // 0.1LPM
    {
        mu8_return = 1;
    }
    else if(mu8_flow_hz >= 10 && mu8_flow_hz < 16)   // 0.2LPM
    {
        mu8_return = 2;
    }
    else if(mu8_flow_hz >= 16 && mu8_flow_hz < 22)   // 0.3LPM
    {
        mu8_return = 3;
    }
    else if(mu8_flow_hz >= 22 && mu8_flow_hz < 28)   // 22hz, 0.4LPM
    {
        mu8_return = 4;
    }
    else if(mu8_flow_hz >= 28 && mu8_flow_hz < 34)   // 28hz, 0.5LPM
    {
        mu8_return = 5;
    }
    else if(mu8_flow_hz >= 34 && mu8_flow_hz < 40)    // 34hz, 0.6LPM
    {
        mu8_return = 6;
    }
    else if(mu8_flow_hz >= 40 && mu8_flow_hz < 46)   // 40hz, 0.7LPM
    {
        mu8_return = 7;
    }
    else if(mu8_flow_hz >= 46 && mu8_flow_hz < 52)   // 46hz, 0.8LPM
    {
        mu8_return = 8;
    }
    else if(mu8_flow_hz >= 52 && mu8_flow_hz < 58)   // 52hz, 0.9LPM
    {
        mu8_return = 9;
    }
    else if(mu8_flow_hz >= 58 && mu8_flow_hz < 64)   // 58hz, 1.0LPM
    {
        mu8_return = 10;
    }
    else if(mu8_flow_hz >= 64 && mu8_flow_hz < 70)   // 64hz, 1.1LPM
    {
        mu8_return = 11;
    }
    else if(mu8_flow_hz >= 70 && mu8_flow_hz < 76)   // 70hz, 1.2LPM
    {
        mu8_return = 12;
    }
    else if(mu8_flow_hz >= 76 && mu8_flow_hz < 82)   // 76hz, 1.3LPM
    {
        mu8_return = 13;
    }
    else if(mu8_flow_hz >= 82 && mu8_flow_hz < 88)   // 82hz, 1.4LPM
    {
        mu8_return = 14;
    }
    else if(mu8_flow_hz >= 88 && mu8_flow_hz < 94)   // 88hz, 1.5LPM
    {
        mu8_return = 15;
    }
    else if(mu8_flow_hz >= 94 && mu8_flow_hz < 100)  // 94hz, 1.6LPM
    {
        mu8_return = 16;
    }
    else if(mu8_flow_hz >= 100 && mu8_flow_hz < 106) // 100hz, 1.7LPM
    {
        mu8_return = 17;
    }
    else if(mu8_flow_hz >= 106 && mu8_flow_hz < 112) // 106hz, 1.8LPM
    {
        mu8_return = 18;
    }
    else if(mu8_flow_hz >= 112 && mu8_flow_hz < 118) // 112hz, 1.9LPM
    {
        mu8_return = 19;
    }
    else if(mu8_flow_hz >= 118)                         // 118hz, 2.0LPM
    {
        mu8_return = 20;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 conv_hot_hz( U8 mu8_flow_hz )
{
    U16 mu16_return = 0;

    if(mu8_flow_hz < 5)
    {
        mu16_return = 0;
    }
    else if(mu8_flow_hz >= 5 && mu8_flow_hz < 10)    // 0.1LPM
    {
        mu16_return = 100;
    }
    else if(mu8_flow_hz >= 10 && mu8_flow_hz < 16)   // 0.2LPM
    {
        mu16_return = 200;
    }
    else if(mu8_flow_hz == 16)   // 0.3LPM
    {
        mu16_return = 300;
    }
    else if(mu8_flow_hz == 17)
    {
        mu16_return = 320;
    }
    else if(mu8_flow_hz == 18)
    {
        mu16_return = 340;
    }
    else if(mu8_flow_hz == 19)
    {
        mu16_return = 360;
    }
    else if(mu8_flow_hz == 20)
    {
        mu16_return = 380;
    }
    else if(mu8_flow_hz == 21)
    {
        mu16_return = 390;
    }
    else if(mu8_flow_hz == 22)   // 22hz, 0.4LPM
    {
        mu16_return = 400;
    }
    else if(mu8_flow_hz == 23)
    {
        mu16_return = 420;
    }
    else if(mu8_flow_hz == 24)
    {
        mu16_return = 440;
    }
    else if(mu8_flow_hz == 25)
    {
        mu16_return = 460;
    }
    else if(mu8_flow_hz == 26)
    {
        mu16_return = 480;
    }
    else if(mu8_flow_hz == 27)
    {
        mu16_return = 490;
    }
    else if(mu8_flow_hz == 28)   // 28hz, 0.5LPM
    {
        mu16_return = 500;
    }
    else if(mu8_flow_hz == 29)
    {
        mu16_return = 520;
    }
    else if(mu8_flow_hz == 30)
    {
        mu16_return = 540;
    }
    else if(mu8_flow_hz == 31)
    {
        mu16_return = 560;
    }
    else if(mu8_flow_hz == 32)
    {
        mu16_return = 580;
    }
    else if(mu8_flow_hz == 33)
    {
        mu16_return = 590;
    }
    else if(mu8_flow_hz == 34)
    {
        mu16_return = 600;
    }
    else if(mu8_flow_hz == 35)
    {
        mu16_return = 620;
    }
    else if(mu8_flow_hz == 36)
    {
        mu16_return = 640;
    }
    else if(mu8_flow_hz == 37)
    {
        mu16_return = 660;
    }
    else if(mu8_flow_hz == 38)
    {
        mu16_return = 680;
    }
    else if(mu8_flow_hz == 39)
    {
        mu16_return = 690;
    }
    else if(mu8_flow_hz >= 40 && mu8_flow_hz < 46)   // 40hz, 0.7LPM
    {
        mu16_return = 700;
    }
    else if(mu8_flow_hz >= 46 && mu8_flow_hz < 52)   // 46hz, 0.8LPM
    {
        mu16_return = 800;
    }
    else if(mu8_flow_hz >= 52 && mu8_flow_hz < 58)   // 52hz, 0.9LPM
    {
        mu16_return = 900;
    }
    else if(mu8_flow_hz >= 58 && mu8_flow_hz < 64)   // 58hz, 1.0LPM
    {
        mu16_return = 1000;
    }
    else if(mu8_flow_hz >= 64 && mu8_flow_hz < 70)   // 64hz, 1.1LPM
    {
        mu16_return = 1100;
    }
    else if(mu8_flow_hz >= 70 && mu8_flow_hz < 76)   // 70hz, 1.2LPM
    {
        mu16_return = 1200;
    }
    else if(mu8_flow_hz >= 76 && mu8_flow_hz < 82)   // 76hz, 1.3LPM
    {
        mu16_return = 1300;
    }
    else if(mu8_flow_hz >= 82 && mu8_flow_hz < 88)   // 82hz, 1.4LPM
    {
        mu16_return = 1400;
    }
    else if(mu8_flow_hz >= 88 && mu8_flow_hz < 94)   // 88hz, 1.5LPM
    {
        mu16_return = 1500;
    }
    else if(mu8_flow_hz >= 94 && mu8_flow_hz < 100)  // 94hz, 1.6LPM
    {
        mu16_return = 1600;
    }
    else if(mu8_flow_hz >= 100 && mu8_flow_hz < 106) // 100hz, 1.7LPM
    {
        mu16_return = 1700;
    }
    else if(mu8_flow_hz >= 106 && mu8_flow_hz < 112) // 106hz, 1.8LPM
    {
        mu16_return = 1800;
    }
    else if(mu8_flow_hz >= 112 && mu8_flow_hz < 118) // 112hz, 1.9LPM
    {
        mu16_return = 1900;
    }
    else if(mu8_flow_hz >= 118)                         // 118hz, 2.0LPM
    {
        mu16_return = 2000;
    }

    return mu16_return;
}



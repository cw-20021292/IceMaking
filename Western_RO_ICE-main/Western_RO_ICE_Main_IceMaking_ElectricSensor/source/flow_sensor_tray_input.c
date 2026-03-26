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
#include    "flow_sensor_tray_input.h"

void tray_flow_sensor_start(void);
void tray_flow_sensor_stop(void);
void INTP11_Tray_Flow_Sensor_Input(void);
void tray_flow_input_count(void);
void calculate_tray_flow_input(void);
U8 conv_hz_to_flow( U8 mu8_flow_hz );



bit F_Tray_Flow_Meter;
U8 gu8_Cnt_Tray_Flow_Meter;


U8 gu8_Tray_Flow_1sec;


U8 gu8TrayFlow10_J;
U8 gu8TrayFlow10_I;
U8 gu8TrayFlow10_H;
U8 gu8TrayFlow10_G;
U8 gu8TrayFlow10_F;
U8 gu8TrayFlow10_E;
U8 gu8TrayFlow10_D;
U8 gu8TrayFlow10_C;
U8 gu8TrayFlow10_B;
U8 gu8TrayFlow10_A;


U8 gu8_Hot_Flow_Rate;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tray_flow_sensor_start(void)
{
    R_INTC11_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tray_flow_sensor_stop(void)
{
    R_INTC11_Stop();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void INTP11_Tray_Flow_Sensor_Input(void)
{
    F_Tray_Flow_Meter = SET;

    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
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
    else{}

    #if 0
    /*..hui [23-2-28¿ÀÈÄ 7:29:57] ¿Â¼öÅÊÅ© »ì±ÕÇÒ¶§..*/
    if( bit_ice_tank_ster_start == SET && gu8_ice_tank_ster_step == 3 )
    {
        if( F_WaterOut == SET )
        {
            //
        }
        else
        {
            if( bit_tray_pump_output == SET )
            {
                if( gu16_Ice_Tank_Ster_Hz > 0 )
                {
                    gu16_Ice_Tank_Ster_Hz--;
                }
                else{}
            }
            else{}
        }
    }
    else{}
    #endif



    tray_flow_sensor_stop();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tray_flow_input_count(void)
{
    if(F_Tray_Flow_Meter == SET)
    {
        F_Tray_Flow_Meter = CLEAR;
        gu8_Cnt_Tray_Flow_Meter++;

        tray_flow_sensor_start();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calculate_tray_flow_input(void)
{
    gu8TrayFlow10_A = gu8_Cnt_Tray_Flow_Meter;
    gu8_Cnt_Tray_Flow_Meter = 0;
    gu8_Tray_Flow_1sec = (gu8TrayFlow10_J + gu8TrayFlow10_I + gu8TrayFlow10_H + gu8TrayFlow10_G + gu8TrayFlow10_F
                          + gu8TrayFlow10_E + gu8TrayFlow10_D + gu8TrayFlow10_C + gu8TrayFlow10_B + gu8TrayFlow10_A);

    gu8TrayFlow10_J = gu8TrayFlow10_I;
    gu8TrayFlow10_I = gu8TrayFlow10_H;
    gu8TrayFlow10_H = gu8TrayFlow10_G;
    gu8TrayFlow10_G = gu8TrayFlow10_F;
    gu8TrayFlow10_F = gu8TrayFlow10_E;
    gu8TrayFlow10_E = gu8TrayFlow10_D;
    gu8TrayFlow10_D = gu8TrayFlow10_C;
    gu8TrayFlow10_C = gu8TrayFlow10_B;
    gu8TrayFlow10_B = gu8TrayFlow10_A;

    gu8_Hot_Flow_Rate = conv_hz_to_flow( gu8_Tray_Flow_1sec );

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



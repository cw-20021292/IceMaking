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
#include    "flow_sensor_filter.h"

void filter_flow_sensor_start(void);
void filter_flow_sensor_stop(void);
void INTP7_Filter_Flow_Sensor_Input(void);
void filter_flow_input_count(void);
void calculate_filter_flow_input(void);


bit F_Filter_Flow_Meter;
U8 gu8CntFilterFlowMeter;


U8 gu8_Filter_Flow_1sec;


U8 gu8Flow10_J_Filter;
U8 gu8Flow10_I_Filter;
U8 gu8Flow10_H_Filter;
U8 gu8Flow10_G_Filter;
U8 gu8Flow10_F_Filter;
U8 gu8Flow10_E_Filter;
U8 gu8Flow10_D_Filter;
U8 gu8Flow10_C_Filter;
U8 gu8Flow10_B_Filter;
U8 gu8Flow10_A_Filter;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_flow_sensor_start(void)
{
    R_INTC7_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_flow_sensor_stop(void)
{
    R_INTC7_Stop();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void INTP7_Filter_Flow_Sensor_Input(void)
{
    F_Filter_Flow_Meter = SET;

    filter_flow_sensor_stop();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_flow_input_count(void)
{
    if(F_Filter_Flow_Meter == SET)
    {
        F_Filter_Flow_Meter = CLEAR;
        gu8CntFilterFlowMeter++;

        filter_flow_sensor_start();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calculate_filter_flow_input(void)
{
    gu8Flow10_A_Filter = gu8CntFilterFlowMeter;
    gu8CntFilterFlowMeter = 0;
    gu8_Filter_Flow_1sec = (gu8Flow10_J_Filter + gu8Flow10_I_Filter + gu8Flow10_H_Filter + gu8Flow10_G_Filter + gu8Flow10_F_Filter
                          + gu8Flow10_E_Filter + gu8Flow10_D_Filter + gu8Flow10_C_Filter + gu8Flow10_B_Filter + gu8Flow10_A_Filter);

    gu8Flow10_J_Filter = gu8Flow10_I_Filter;
    gu8Flow10_I_Filter = gu8Flow10_H_Filter;
    gu8Flow10_H_Filter = gu8Flow10_G_Filter;
    gu8Flow10_G_Filter = gu8Flow10_F_Filter;
    gu8Flow10_F_Filter = gu8Flow10_E_Filter;
    gu8Flow10_E_Filter = gu8Flow10_D_Filter;
    gu8Flow10_D_Filter = gu8Flow10_C_Filter;
    gu8Flow10_C_Filter = gu8Flow10_B_Filter;
    gu8Flow10_B_Filter = gu8Flow10_A_Filter;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


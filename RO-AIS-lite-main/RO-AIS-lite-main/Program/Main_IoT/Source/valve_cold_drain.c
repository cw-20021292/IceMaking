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
#include    "valve_cold_drain.h"

void output_cold_drain_valve(void);
bit F_auto_drain_mode_cold_water_valve_out;


//bit F_over_ice_melt_mode_cold_water_valve_out;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_cold_drain_valve(void)
{
    /*..hui [18-1-14오후 5:44:23] 순환배수 기능 OFF이거나 드레인 상태 아니면 OFF..*/
    /*if(F_HardError == SET)*/
    /*if(Bit2_Ice_Operation_Disable_State == SET)*/
    /*..hui [18-2-20오전 11:21:48] 굳이 모든 에러에 다 막을 필요ㅗ는 없음..*/
    if(Bit12_Drain_Pump_Error == SET || Bit3_Leakage_Sensor_Error == SET)
    {
        pVALVE_COLD_DRAIN = CLEAR;
    }
    else if(Bit2_Ice_Operation_Disable_State == SET)
    {
        pVALVE_COLD_DRAIN = CLEAR;
    }
    else if( (F_DrainStatus == CLEAR || F_Circul_Drain == CLEAR) )
    {
        pVALVE_COLD_DRAIN = CLEAR;
    }
    else
    {
        if(F_auto_drain_mode_cold_water_valve_out == SET)
        {
            pVALVE_COLD_DRAIN = SET;
        }
        else
        {
            pVALVE_COLD_DRAIN = CLEAR;
        }
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




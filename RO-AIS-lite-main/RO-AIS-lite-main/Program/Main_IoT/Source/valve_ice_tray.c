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
#include    "valve_ice_tray.h"

void output_valve_ice_tray(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8IceTrayValveONB;
#define            u8IceTrayValveON                         U8IceTrayValveONB.byte
#define            Bit0_Ice_Make_Input_State          U8IceTrayValveONB.Bit.b0
#define            Bit1_Over_Ice_Melt_Input_State          U8IceTrayValveONB.Bit.b1




TYPE_BYTE          U8IceTrayValveOFFB;
#define            u8IceTrayValveOFF                         U8IceTrayValveOFFB.byte
#define            Bit0_Tray_Drain_Error_Off_State           U8IceTrayValveOFFB.Bit.b0
#define            Bit1_Tray_Leakage_Error_Off_State         U8IceTrayValveOFFB.Bit.b1
#define            Bit2_Tray_Ice_Error_Off_State             U8IceTrayValveOFFB.Bit.b2
#define            Bit3_Tray_Hot_Out_Off_State               U8IceTrayValveOFFB.Bit.b3
#define            Bit4_Tray_Low_Level_Off_State             U8IceTrayValveOFFB.Bit.b4
#define            Bit5_Tray_Hot_Cooling_Off_State           U8IceTrayValveOFFB.Bit.b5
#define            Bit6_Tray_Hot_Filling_Off_State           U8IceTrayValveOFFB.Bit.b6
#define            Bit7_Tray_Hot_Steam_Off_State             U8IceTrayValveOFFB.Bit.b7



/***********************************************************************************************************************/


U8 u8_room_low_detect;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_ice_tray(void)
{

    #if 0
    /***********************************************************************************************/
    /***********************************************************************************************/

    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        /*..hui [19-12-13오후 3:08:52] 트레이 입수중 저수위 미만 감지되어 정지시..*/
        /*..hui [19-12-13오후 3:08:59] 만수위까지 채운 후 재 시작하도록 변경..*/
        if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
        {
            u8_room_low_detect = SET;
        }
        else
        {
            if(u8_room_low_detect == SET)
            {
                if( gu8_Room_Water_Level == ROOM_LEVEL_FULL)
                {
                    u8_room_low_detect = CLEAR;
                }
                else{}
            }
            else{}
        }

        if(u8_room_low_detect == SET)
        {
            Bit0_Ice_Make_Input_State = CLEAR;
        }
        else
        {
            Bit0_Ice_Make_Input_State = SET;
        }
    }
    else
    {
        u8_room_low_detect = CLEAR;
        Bit0_Ice_Make_Input_State = CLEAR;
    }

    /***********************************************************************************************/

    if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)
    {
        if( u8WaterOutState == HOT_WATER_SELECT
            && F_WaterOut == SET )
        {
            Bit1_Over_Ice_Melt_Input_State = CLEAR;
        }
        else
        {
            Bit1_Over_Ice_Melt_Input_State = (F_Safety_Routine & F_Ice_Tray_Down_Move_Reset & F_IceVV);
        }
    }
    else
    {
        Bit1_Over_Ice_Melt_Input_State = CLEAR;
    }

    /***********************************************************************************************/
    /***********************************************************************************************/
    /***********************************************************************************************/


    Bit0_Tray_Drain_Error_Off_State = Bit12_Drain_Pump_Error;

    Bit1_Tray_Leakage_Error_Off_State = Bit3_Leakage_Sensor_Error;

    Bit2_Tray_Ice_Error_Off_State = (Bit2_Ice_Operation_Disable_State | F_ErrTrayMotor_DualInital);

    /***********************************************************************************************/


    /*..hui [19-8-27오후 3:44:11] 트레이 입수 중 온수 추출 시 트레이 밸브 OFF..*/
    /*..hui [19-8-27오후 3:44:17] 온수 추출로 전환..*/

    /*..hui [19-8-27오후 7:24:57] 온수 추출 뿐만아니라 정수/냉수 추출중에도 트레이 입수는 잠시 대기..*/
    /*..hui [19-8-28오후 2:44:21] 트레이 입수 안될경우 재시도 대기 시간동안 OFF 추가..*/
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        Bit3_Tray_Hot_Out_Off_State = F_WaterOut;  /* | F_Tray_In_Error_Temporary;*/
    }
    else
    {
        Bit3_Tray_Hot_Out_Off_State = CLEAR;
    }

    /***********************************************************************************************/
    /*..hui [19-12-13오후 3:09:53] 그 외 조건일 경우 저수위 미만일때만 닫음..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
    {
        Bit4_Tray_Low_Level_Off_State = SET;
    }
    else
    {
        Bit4_Tray_Low_Level_Off_State = CLEAR;
    }
    /***********************************************************************************************/
    /***********************************************************************************************/

    if (u8IceTrayValveOFF > 0)
    {
        pVALVE_ICE_TRAY_IN = CLEAR;      /*off*/
    }
    else
    {
        if (u8IceTrayValveON > 0)
        {
            pVALVE_ICE_TRAY_IN = SET;    /*on*/
        }
        else
        {
            pVALVE_ICE_TRAY_IN = CLEAR;  /*off*/
        }
    }
    /***********************************************************************************************/
    /***********************************************************************************************/
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



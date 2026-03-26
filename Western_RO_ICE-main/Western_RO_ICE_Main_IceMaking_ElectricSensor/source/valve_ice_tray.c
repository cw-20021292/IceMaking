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
#define            Bit0_Ice_Make_Input_State                U8IceTrayValveONB.Bit.b0
#define            Bit1_Over_Ice_Melt_Input_State           U8IceTrayValveONB.Bit.b1
#define            Bit2_Tray_Flushing_State                 U8IceTrayValveONB.Bit.b2
#define            Bit3_Tray_Clean_State                    U8IceTrayValveONB.Bit.b3




TYPE_BYTE          U8IceTrayValveOFFB;
#define            u8IceTrayValveOFF                         U8IceTrayValveOFFB.byte
#define            Bit0_Tray_Drain_Error_Off_State           U8IceTrayValveOFFB.Bit.b0
#define            Bit1_Tray_Leakage_Error_Off_State         U8IceTrayValveOFFB.Bit.b1
#define            Bit2_Tray_Ice_Error_Off_State             U8IceTrayValveOFFB.Bit.b2
#define            Bit3_Tray_Hot_Out_Off_State               U8IceTrayValveOFFB.Bit.b3
#define            Bit4_Tray_Low_Level_Off_State             U8IceTrayValveOFFB.Bit.b4
#define            Bit5_Tray_Ice_Tank_Ster_Off_State         U8IceTrayValveOFFB.Bit.b5



/***********************************************************************************************************************/


U8 u8_room_low_detect;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_ice_tray(void)
{
    /***********************************************************************************************/
    /***********************************************************************************************/
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        /*..hui [23-4-13오전 11:02:49] 트레이 입수중에는 그냥 항상 열고있도록..*/
        /*..hui [23-4-13오전 11:02:52] 펌프쪽에서 제어..*/
        Bit0_Ice_Make_Input_State = SET;

        #if 0
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
        #endif
    }
    else
    {
        u8_room_low_detect = CLEAR;
        Bit0_Ice_Make_Input_State = CLEAR;
    }

    /***********************************************************************************************/
    /*if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)*/
    /*if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 6)*/
    if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)
    {
        Bit1_Over_Ice_Melt_Input_State = (F_Safety_Routine & F_Ice_Tray_Down_Move_Reset & F_IceVV);
    }
    else
    {
        Bit1_Over_Ice_Melt_Input_State = CLEAR;
    }


    /*..hui [23-8-16오후 1:24:20] 탱크 플러싱할때..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        /*if( gu8_flushing_tank_step >= 6 && gu8_flushing_tank_step <= 8 )*/
        /*if( gu8_flushing_tank_step >= 11 && gu8_flushing_tank_step <= 13 )*/
        if( gu8_flushing_tank_step >= 6 && gu8_flushing_tank_step <= 8 )
        {
            Bit2_Tray_Flushing_State = bit_flushing_tank_start;
        }
        else
        {
            Bit2_Tray_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit2_Tray_Flushing_State = CLEAR;
    }



    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step >= 15 && gu8_ice_tray_clean_step <= 17 )
            {
                Bit3_Tray_Clean_State = SET;
            }
            else
            {
                Bit3_Tray_Clean_State = CLEAR;
            }
        }
        else
        {
            Bit3_Tray_Clean_State = CLEAR;
        }
    }
    else
    {
        Bit3_Tray_Clean_State = CLEAR;
    }







    /***********************************************************************************************/
    /***********************************************************************************************/
    /***********************************************************************************************/


    Bit0_Tray_Drain_Error_Off_State = Bit16_Drain_Pump_Error__E60;

    Bit1_Tray_Leakage_Error_Off_State = Bit3_Leakage_Sensor_Error__E01;


    /*..hui [24-1-25오전 11:18:27] 온수 세척 중에는 가동해야함.. 정수센서 에러등은 온수세척과 관계가 없기 때문에..*/
    if( bit_ice_tank_ster_start == SET )
    {
        Bit2_Tray_Ice_Error_Off_State = CLEAR;
    }
    else if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        /*..hui [24-1-25오전 11:21:05] 설치플러싱.. 탱크 플러싱할때도 트레이 세척해야함.. 플러싱은 얼음에러랑은 상관없음..*/
        Bit2_Tray_Ice_Error_Off_State = CLEAR;
    }
    else
    {
        Bit2_Tray_Ice_Error_Off_State = (Bit2_Ice_Operation_Disable_State | F_ErrTrayMotor_DualInital);
    }

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
    /*..hui [23-2-28오후 7:12:43] 얼음 탱크 살균할때 정지..*/
    if( bit_ice_tank_ster_start == SET )
    {
        /*if( gu8_ice_ster_mode >= STER_MODE_HOT_SPRAY_STATE )*/
        /*..hui [24-1-25오전 11:09:41] 아이스트레이 세척할떄는 켜야함..*/
        if( gu8_ice_ster_mode != STER_MODE_ICE_TRAY_CLEAN )
        {
            Bit5_Tray_Ice_Tank_Ster_Off_State = SET;
        }
        else
        {
            Bit5_Tray_Ice_Tank_Ster_Off_State = CLEAR;
        }
    }
    else
    {
        Bit5_Tray_Ice_Tank_Ster_Off_State = CLEAR;
    }


    /***********************************************************************************************/
    /***********************************************************************************************/

    if (u8IceTrayValveOFF > 0)
    {
        pVALVE_ICE_TRAY_IN_FEED = CLEAR;      /*off*/
    }
    else
    {
        if (u8IceTrayValveON > 0)
        {
            pVALVE_ICE_TRAY_IN_FEED = SET;    /*on*/
        }
        else
        {
            pVALVE_ICE_TRAY_IN_FEED = CLEAR;  /*off*/
        }
    }
    /***********************************************************************************************/
    /***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



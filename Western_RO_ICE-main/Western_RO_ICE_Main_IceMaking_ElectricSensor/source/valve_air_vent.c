/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "valve_air_vent.h"


void output_valve_air_vent(void);





TYPE_WORD          U16AirValveOnW;
#define            u16AirValveON                                 U16AirValveOnW.word
#define            u8AirValveOn_L                                U16AirValveOnW.byte[0]
#define            u8AirValveOn_H                                U16AirValveOnW.byte[1]
#define            Bit0_Air_Valve_Feed_On_State                  U16AirValveOnW.Bit.b0
#define            Bit1_Air_Valve_Extract_On_State               U16AirValveOnW.Bit.b1
#define            Bit2_Air_Valve_Ice_Tray_Input_On_State        U16AirValveOnW.Bit.b2
#define            Bit3_Air_Valve_Hot_Ster_On_State              U16AirValveOnW.Bit.b3
#define            Bit4_Air_Valve_Auto_Drain_On_State            U16AirValveOnW.Bit.b4
#define            Bit5_Air_Valve_Manual_Drain_On_State          U16AirValveOnW.Bit.b5
#define            Bit6_Air_Valve_Install_Flushing_On_State      U16AirValveOnW.Bit.b6
#define            Bit7_Air_Valve_Water_lushing_On_State         U16AirValveOnW.Bit.b7
#define            Bit8_Air_Valve_Acid_Clean_On_State            U16AirValveOnW.Bit.b8






TYPE_BYTE          U8AirValveOFFB;
#define            u8AirValveOFF                                 U8AirValveOFFB.byte
#define            Bit0_Air_Valve_Off_State                      U8AirValveOFFB.Bit.b0

bit bit_air_vent_valve_output;
U16 gu16_air_vent_delay_timer;
bit bit_air_vent_close_delay;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_air_vent(void)
{

    /*..hui [23-7-28오후 2:38:43] 재정수할때는 닫는다(소음문제)..*/
    /*Bit0_Air_Valve_Feed_On_State = bit_feed_output;*/


    /*..hui [24-3-5오후 2:25:30] 피드밸브 ON 시간 3시간 40분 경과 시 20분동안 에어밸브 ON..*/
    /*..hui [24-3-5오후 2:25:47] 혹시나 만수위센서 불량이면 바디로 물 떨어져서 누수에러 걸리게하기 위함..*/
    if( bit_feed_output == SET )
    {
        if( gu32_feed_overheat_on_timer >= HIGH_LEVEL_FAULT_CHECK_TIME )
        {
            Bit0_Air_Valve_Feed_On_State = bit_feed_output;
        }
        else
        {
            Bit0_Air_Valve_Feed_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Air_Valve_Feed_On_State = CLEAR;
    }




    Bit1_Air_Valve_Extract_On_State = F_WaterOut;


    if( gu8IceStep >= STATE_14_CHECK_ICE_TRAY_HZ && gu8IceStep <= STATE_20_WATER_IN_ICE_TRAY )
    {
        Bit2_Air_Valve_Ice_Tray_Input_On_State = SET;
    }
    else
    {
        Bit2_Air_Valve_Ice_Tray_Input_On_State = CLEAR;
    }


    if( bit_ice_tank_ster_start == SET )
    {
        /*if( gu8_ice_ster_mode >= STER_MODE_HOT_SPRAY_STATE )*/
        /*if( gu8_ice_ster_mode >= STER_MODE_CIRCULATION_HOT_STATE )*/
        /*..hui [23-10-12오후 5:29:26] 준비 단계에서 드레인 탱크에 물 넣는 기능 추가됐기 때문에..*/
        if( gu8_ice_ster_mode >= STER_MODE_PREPARE )
        {
            Bit3_Air_Valve_Hot_Ster_On_State = SET;
        }
        else
        {
            Bit3_Air_Valve_Hot_Ster_On_State = CLEAR;
        }
    }
    else
    {
        Bit3_Air_Valve_Hot_Ster_On_State = CLEAR;
    }


    Bit4_Air_Valve_Auto_Drain_On_State = F_DrainStatus;

    /*..hui [23-8-14오후 1:25:44] 수동배수시..*/
    Bit5_Air_Valve_Manual_Drain_On_State = bit_manual_drain_start;


    /*..hui [23-8-25오전 9:51:01] 플러싱할때.. 항상 켜줌..*/
    /*..hui [23-8-25오전 10:04:07] 탱크 배수도 해야하고.. 유로전환밸브 고착에 효과있음? 이정환 부장님....*/
    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        Bit6_Air_Valve_Install_Flushing_On_State = bit_flushing_start;
    }
    else if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        Bit6_Air_Valve_Install_Flushing_On_State = bit_flushing_tank_start;
    }
    else
    {
        Bit6_Air_Valve_Install_Flushing_On_State = CLEAR;
    }

    /*..hui [23-9-4오후 4:25:30] 워터 플러싱할때.. 이정환부장님.. 우선 필드테스트는 ON하는걸로..*/
    /*..hui [23-9-4오후 4:25:37] 나중에 FEED-NOS로 변경되면 빼도됨..*/
    if( bit_flushing_water_start == SET )
    {
        if( gu8_water_flushing_step >= 1 && gu8_water_flushing_step <= 9 )
        {
            Bit7_Air_Valve_Water_lushing_On_State = SET;
        }
        else
        {
            Bit7_Air_Valve_Water_lushing_On_State = CLEAR;
        }
    }
    else
    {
        Bit7_Air_Valve_Water_lushing_On_State = CLEAR;
    }

    /*..hui [24-5-23오후 7:05:42] 구연산 세정할때..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode > ACID_CLEAN_NONE_STATE )
        {
            Bit8_Air_Valve_Acid_Clean_On_State = Bit5_CD_Drain_Acid_On_State;
        }
        else
        {
            Bit8_Air_Valve_Acid_Clean_On_State = CLEAR;
        }
    }
    else
    {
        Bit8_Air_Valve_Acid_Clean_On_State = CLEAR;
    }

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

    Bit0_Air_Valve_Off_State = CLEAR;


/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
    if (u8AirValveOFF > 0)
    {
        pVALVE_AIR_VENT = CLEAR;      /*off*/
        bit_air_vent_valve_output = CLEAR;
    }
    else
    {
        /*if (u8AirValveON > 0)*/
        if (u16AirValveON > 0)
        {
            pVALVE_AIR_VENT = SET;    /*on*/
            bit_air_vent_valve_output = SET;
            gu16_air_vent_delay_timer = 0;

            /*..hui [23-8-25오전 9:56:48] 물 추출하고 나서만 1분 지연 후 OFF하도록..*/
            if( Bit1_Air_Valve_Extract_On_State == SET )
            {
                bit_air_vent_close_delay = SET;
            }
            else{}
        }
        else
        {
            if( bit_air_vent_close_delay == SET )
            {
                gu16_air_vent_delay_timer++;

                /*..hui [23-6-15오후 12:00:42] 에어밸브는 피드 닫히고 1분후 닫는걸로.. 소음문제..*/
                if( gu16_air_vent_delay_timer >= AIR_VENT_DELAY_TIME )
                {
                    pVALVE_AIR_VENT = CLEAR;  /*off*/
                    bit_air_vent_valve_output = CLEAR;
                    gu16_air_vent_delay_timer = 0;

                    bit_air_vent_close_delay = CLEAR;
                }
                else{}
            }
            else
            {
                pVALVE_AIR_VENT = CLEAR;  /*off*/
                bit_air_vent_valve_output = CLEAR;
                gu16_air_vent_delay_timer = 0;
            }
        }
    }


    #if 0
    if (u8AirValveOFF > 0)
    {
        pVALVE_AIR_VENT = CLEAR;      /*off*/
    }
    else
    {
        if (u8AirValveON > 0)
        {
            pVALVE_AIR_VENT = SET;    /*on*/
        }
        else
        {
            pVALVE_AIR_VENT = CLEAR;  /*off*/
        }
    }
    #endif
/***********************************************************************************************/
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





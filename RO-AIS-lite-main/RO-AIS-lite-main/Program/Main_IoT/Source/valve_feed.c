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
#include    "valve_feed.h"

void output_valve_feed(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8FeedValveONB;
#define            u8FeedValveON                         U8FeedValveONB.byte
#define            Bit0_Low_Water_Filling_State          U8FeedValveONB.Bit.b0




TYPE_BYTE          U8FeedValveOFFB;
#define            u8FeedValveOFF                         U8FeedValveOFFB.byte
#define            Bit0_Water_Level_Error_Off_State       U8FeedValveOFFB.Bit.b0
#define            Bit1_FV_Hot_Cooling_Off_State          U8FeedValveOFFB.Bit.b1
#define            Bit2_Overflow_Off_State                U8FeedValveOFFB.Bit.b2
#define            Bit3_Feed_Valve_OverHeat_State         U8FeedValveOFFB.Bit.b3
#define            Bit4_System_Init_State                 U8FeedValveOFFB.Bit.b4
#define            Bit5_Hot_Drain_Off_State               U8FeedValveOFFB.Bit.b5
#define            Bit6_Drain_Operation_Off_State         U8FeedValveOFFB.Bit.b6
#define            Bit7_Hot_Filling_Off_State             U8FeedValveOFFB.Bit.b7



U16 gu16_feed_drain_full_time;


bit F_filling_add_op;
U16 gu16_filling_add_op_timer;


bit bit_feed_output;

U32 gu32_feed_overheat_on_timer;
U16 gu16_feed_overheat_off_timer;

/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_feed(void)
{
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW
        || gu8_Room_Water_Level == ROOM_LEVEL_MID )
    {
        Bit0_Low_Water_Filling_State = SET;
    }
    else
    {
        Bit0_Low_Water_Filling_State = CLEAR;
    }

    /***********************************************************************************************/
    /***********************************************************************************************/

    if( Bit3_Leakage_Sensor_Error == SET
        || Bit7_Room_High_Water_Level_Error == SET
        || Bit8_Feed_Valve_Error  == SET
        || Bit9_Room_Level_Unbalance_Error == SET
        || Bit4_Room_Low_Water_Level_Error == SET )
    {
        Bit0_Water_Level_Error_Off_State = SET;
    }
    else
    {
        Bit0_Water_Level_Error_Off_State = CLEAR;
    }


    Bit2_Overflow_Off_State = F_Err_OVF_Check;

    /*..hui [19-10-23오전 11:03:01] 드레인펌프 가동중에는 피드밸브 닫기..*/
    Bit6_Drain_Operation_Off_State = F_Drain_Pump_Output;

    #if 0
    /*..hui [23-6-9오전 9:34:04] 외장펌프 미연결됐을때만..*/
    if( bit_boost_pump_connect == CLEAR )
    {
        if( bit_feed_output == SET )
        {
            gu16_feed_overheat_off_timer = 0;
            gu32_feed_overheat_on_timer++;

            /*..hui [23-6-9오전 9:34:19] 피드밸브가 150분 이상 ON시 강제 OFF..*/
            if( gu32_feed_overheat_on_timer >= FEED_OVER_HEAT_PREVENT_TIME )
            {
                Bit3_Feed_Valve_OverHeat_State = SET;
            }
            else{}
        }
        else
        {
            gu32_feed_overheat_on_timer = 0;

            if( Bit3_Feed_Valve_OverHeat_State == SET )
            {
                gu16_feed_overheat_off_timer++;

                /*..hui [23-6-9오전 9:34:37] 강제 OFF 후 30분동안 OFF 상태 유지..*/
                if( gu16_feed_overheat_off_timer >= FEED_OVER_HEAT_RETURN_TIME )
                {
                    gu16_feed_overheat_off_timer = 0;
                    Bit3_Feed_Valve_OverHeat_State = CLEAR;
                }
                else{}
            }
            else
            {
                gu16_feed_overheat_off_timer = 0;
            }
        }
    }
    else
    {
        gu16_feed_overheat_off_timer = 0;
        gu32_feed_overheat_on_timer = 0;
        Bit3_Feed_Valve_OverHeat_State = CLEAR;
    }
    #endif

    if( bit_feed_output == SET )
    {
        gu16_feed_overheat_off_timer = 0;
        gu32_feed_overheat_on_timer++;

        /*..hui [23-6-9오전 9:34:19] 피드밸브가 150분 이상 ON시 강제 OFF..*/
        /*..hui [23-6-12오전 10:19:28] 240분으로 변경..*/
        if( gu32_feed_overheat_on_timer >= FEED_OVER_HEAT_PREVENT_TIME )
        {
            gu32_feed_overheat_on_timer = FEED_OVER_HEAT_PREVENT_TIME;
            Bit3_Feed_Valve_OverHeat_State = SET;
        }
        else{}
    }
    else
    {
        gu32_feed_overheat_on_timer = 0;

        if( Bit3_Feed_Valve_OverHeat_State == SET )
        {
            gu16_feed_overheat_off_timer++;

            /*..hui [23-6-9오전 9:34:37] 강제 OFF 후 30분동안 OFF 상태 유지..*/
            if( gu16_feed_overheat_off_timer >= FEED_OVER_HEAT_RETURN_TIME )
            {
                gu16_feed_overheat_off_timer = 0;
                Bit3_Feed_Valve_OverHeat_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_feed_overheat_off_timer = 0;
        }
    }

/***********************************************************************************************/
    if (u8FeedValveOFF > 0)
    {
        pVALVE_FEED = CLEAR;      /*off*/
        bit_feed_output = CLEAR;
    }
    else
    {
        if (u8FeedValveON > 0)
        {
            pVALVE_FEED = SET;    /*on*/
            bit_feed_output = SET;
        }
        else
        {
            pVALVE_FEED = CLEAR;  /*off*/
            bit_feed_output = CLEAR;
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




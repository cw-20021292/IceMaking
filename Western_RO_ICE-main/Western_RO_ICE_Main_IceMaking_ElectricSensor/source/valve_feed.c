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
#define            Bit1_Feed_Valve_Flushing_State        U8FeedValveONB.Bit.b1
#define            Bit2_Feed_Valve_Water_Flushing_State  U8FeedValveONB.Bit.b2
#define            Bit3_Feed_Valve_Flushing_Tank_State   U8FeedValveONB.Bit.b3
#define            Bit4_Feed_Valve_Acid_Clean_State      U8FeedValveONB.Bit.b4




TYPE_BYTE          U8FeedValveOFFB;
#define            u8FeedValveOFF                         U8FeedValveOFFB.byte
#define            Bit0_Water_Level_Error_Off_State       U8FeedValveOFFB.Bit.b0
#define            Bit1_FV_Water_Flushing_Off_State       U8FeedValveOFFB.Bit.b1
#define            Bit2_FV_Ice_Tank_Ster_Off_State        U8FeedValveOFFB.Bit.b2
#define            Bit3_Feed_Valve_OverHeat_State         U8FeedValveOFFB.Bit.b3
#define            Bit4_Auto_Drain_Off_State              U8FeedValveOFFB.Bit.b4
#define            Bit5_Manual_Drain_Off_State            U8FeedValveOFFB.Bit.b5
#define            Bit6_Drain_Operation_Off_State         U8FeedValveOFFB.Bit.b6
#define            Bit7_FV_Reed_Off_State                 U8FeedValveOFFB.Bit.b7



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
    pre_water_flushing( u8FeedValveOFF, u8FeedValveON );


    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW
        || gu8_Room_Water_Level == ROOM_LEVEL_MID )
    {
        /*..hui [23-6-14오후 3:18:26] 플러싱모드에서는 피드 OFF..*/
        /*..hui [24-5-24오후 5:20:56] 구연산 세정할때도 따로 제어..*/
        if( gu8_flushing_mode == FLUSHING_NONE_STATE && bit_acid_clean_start == CLEAR )
        {
            Bit0_Low_Water_Filling_State = SET;
        }
        else
        {
            Bit0_Low_Water_Filling_State = CLEAR;
        }

        gu16_filling_add_op_timer = 0;
    }
    else
    {
        /*Bit0_Low_Water_Filling_State = CLEAR;*/

        /*..hui [24-1-23오후 5:45:52] 피드밸브 30초 지연 후 OFF 하도록 수정..*/
        if( Bit0_Low_Water_Filling_State == SET )
        {
            if( pVALVE_FEED == SET )
            {
                gu16_filling_add_op_timer++;
            }
            else{}

            if( gu16_filling_add_op_timer >= FEED_FILLING_ADD_TIME
                || Bit0_Water_Level_Error_Off_State == SET
                || Bit2_Feed_Valve_Water_Flushing_State == SET )
            {
                gu16_filling_add_op_timer = 0;
                Bit0_Low_Water_Filling_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_filling_add_op_timer = 0;
        }
    }

    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        /*if( gu8_flushing_step == 4 || gu8_flushing_step == 7 || gu8_flushing_step == 8 )*/
        if( gu8_flushing_step == 4 || gu8_flushing_step == 7 || gu8_flushing_step == 8 || gu8_flushing_step == 12 )
        {
            Bit1_Feed_Valve_Flushing_State = bit_flushing_start;
        }
        else
        {
            Bit1_Feed_Valve_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit1_Feed_Valve_Flushing_State = CLEAR;
    }

    /*..hui [23-8-16오후 1:24:20] 탱크 플러싱할때..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        /*..hui [23-8-23오전 9:17:57] 만수위 아닐경우만 조건 추가..*/
        if( gu8_Room_Water_Level != ROOM_LEVEL_FULL )
        {
            if( gu8_flushing_tank_step >= 1 && gu8_flushing_tank_step <= 3 )
            {
                Bit3_Feed_Valve_Flushing_Tank_State = bit_flushing_tank_start;
            }
            else
            {
                Bit3_Feed_Valve_Flushing_Tank_State = CLEAR;
            }
        }
        else
        {
            Bit3_Feed_Valve_Flushing_Tank_State = CLEAR;
        }
    }
    else
    {
        Bit3_Feed_Valve_Flushing_Tank_State = CLEAR;
    }



    /*..hui [23-6-16오후 2:51:06] 급수 플러싱할때..*/
    if( bit_flushing_water_start == SET )
    {
        if( gu8_water_flushing_step >= 2 && gu8_water_flushing_step <= 5 )
        {
            Bit2_Feed_Valve_Water_Flushing_State = SET;
        }
        else
        {
            Bit2_Feed_Valve_Water_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit2_Feed_Valve_Water_Flushing_State = CLEAR;
    }



    /*..hui [24-5-23오후 7:05:42] 구연산 세정할때..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_NONE_STATE )
        {
            Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_STANDBY )
        {
            Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE )
        {
            if( gu8_acid_prepare_step == 3 || gu8_acid_prepare_step == 4 )
            {
                Bit4_Feed_Valve_Acid_Clean_State = SET;
            }
            else
            {
                Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
            }
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
        {
            Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR )
        {
            Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
        {
            if( gu8_acid_rinse_step == 4 || gu8_acid_rinse_step == 5
                || gu8_acid_rinse_step == 8 || gu8_acid_rinse_step == 11 )
            {
                Bit4_Feed_Valve_Acid_Clean_State = SET;
            }
            else
            {
                Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
            }
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )
        {
            if( gu8_acid_finish_step == 1 )
            {
                Bit4_Feed_Valve_Acid_Clean_State = SET;
            }
            else
            {
                Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
            }
        }
        else
        {
            Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
        }

    }
    else
    {
        Bit4_Feed_Valve_Acid_Clean_State = CLEAR;
    }


    /***********************************************************************************************/
    /***********************************************************************************************/
    if( Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        Bit0_Water_Level_Error_Off_State = SET;
    }
    else
    {
        Bit0_Water_Level_Error_Off_State = CLEAR;
    }

    #if 0
    if( u8PreWaterFlushing > 0 )
    {
        Bit1_FV_Water_Flushing_Off_State = SET;
    }
    else
    {
        Bit1_FV_Water_Flushing_Off_State = CLEAR;
    }
    #endif

    /*..hui [23-8-14오후 1:26:31] 순환배수시 feed 닫도록.. 온수 냉수탱크로 역류될수있음.. 이정환부장님..*/
    Bit4_Auto_Drain_Off_State = F_DrainStatus;

    /*..hui [23-8-14오후 1:26:35] 수동배수할때..*/
    Bit5_Manual_Drain_Off_State = bit_manual_drain_start;



    /*..hui [19-10-23오전 11:03:01] 드레인펌프 가동중에는 피드밸브 닫기..*/
    Bit6_Drain_Operation_Off_State = F_Drain_Pump_Output;


    /*..hui [23-10-12오후 5:12:04] 온수세척 중에는 피드 닫기.. 소음 때문에..*/
    /*..hui [23-10-12오후 5:12:16] 나중에 재정수하는 조건에서는 열리도록 수정해야함..*/
    /*Bit2_FV_Ice_Tank_Ster_Off_State = bit_ice_tank_ster_start;*/

    if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-10-17오후 2:30:14] 해빙작업 재정수할때 제외하고 OFF.. 소음문제..*/
        /*..hui [24-1-25오전 9:17:17] 아이스트레이 준비할떄도.. 재정수 해야함..*/
        if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
        {
            Bit2_FV_Ice_Tank_Ster_Off_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
        {
            Bit2_FV_Ice_Tank_Ster_Off_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINISH )
        {
            Bit2_FV_Ice_Tank_Ster_Off_State = CLEAR;
        }
        else
        {
            Bit2_FV_Ice_Tank_Ster_Off_State = SET;
        }
    }
    else
    {
        Bit2_FV_Ice_Tank_Ster_Off_State = CLEAR;
    }


    if( bit_feed_output == SET )
    {
        gu16_feed_overheat_off_timer = 0;
        gu32_feed_overheat_on_timer++;

        /*..hui [23-6-9오전 9:34:19] 피드밸브가 150분 이상 ON시 강제 OFF..*/
        /*..hui [23-6-12오전 10:19:28] 240분으로 변경..*/
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


    /*..hui [23-6-16오후 2:52:45] 급수 플러싱할때는 닫기..*/
    if( bit_flushing_water_start == SET )
    {
        /*Bit1_FV_Water_Flushing_Off_State = SET;*/
        /*..hui [23-6-16오후 2:55:51] 급수플러싱할때 FEED 켜는 조건에서는 켜도록..*/
        Bit1_FV_Water_Flushing_Off_State = ~Bit2_Feed_Valve_Water_Flushing_State;
    }
    else
    {
        Bit1_FV_Water_Flushing_Off_State = CLEAR;
    }

    Bit7_FV_Reed_Off_State = ~bit_filter_all;

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




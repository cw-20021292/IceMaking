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
#include    "error_feed.h"


void check_error_feed_valve(void);

TYPE_BYTE          U8FeedErrorCheckB;
#define            u8FeedErrorCheck                       U8FeedErrorCheckB.byte
#define            Bit0_Feed_Error_Ice_Full_State         U8FeedErrorCheckB.Bit.b0
#define            Bit1_Feed_Error_Ice_Step_State         U8FeedErrorCheckB.Bit.b1
#define            Bit2_Feed_Error_Room_Level_State       U8FeedErrorCheckB.Bit.b2
#define            Bit3_Feed_Error_Drain_Tank_State       U8FeedErrorCheckB.Bit.b3



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_feed_valve(void)
{

#if 0
    if( F_IceOn == SET )
    {
        Bit0_Feed_Error_Ice_Full_State = F_IceFull;
    }
    else
    {
        Bit0_Feed_Error_Ice_Full_State = SET;
    }

    if( gu8IceStep == STATE_0_STANDBY )
    {
        Bit1_Feed_Error_Ice_Step_State = SET;
    }
    else
    {
        Bit1_Feed_Error_Ice_Step_State = CLEAR;
    }

    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
    {
        Bit2_Feed_Error_Room_Level_State = SET;
    }
    else
    {
        Bit2_Feed_Error_Room_Level_State = CLEAR;
    }


    //Bit3_Feed_Error_Drain_Tank_State


    if( u8FeedErrorCheck == 0x07 )
    {
        if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)

    }
    else
    {

    }

#endif

}



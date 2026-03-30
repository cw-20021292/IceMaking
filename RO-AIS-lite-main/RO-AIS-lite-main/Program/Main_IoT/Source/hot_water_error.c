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
#include    "hot_water_error.h"



void hot_water_error_check(void);
void check_error_hot_overheat(void);
void check_error_room_overheat(void);

U8 gu8_hot_overheat_on_timer;
U8 gu8_hot_overheat_off_timer;


U16 gu16_hot_flow_block_err_chk_timer;
U16 gu16_hot_flow_block_err_clr_timer;

U16 gu16_hot_overheat_err_chk_timer;
U16 gu16_hot_overheat_err_clr_timer;


bit F_Hot_Temp_Much_Difference_State;

U8 gu8_room_overheat_on_timer;
U8 gu8_room_overheat_off_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_water_error_check(void)
{
    /*..hui [23-5-17오후 7:47:06] 온수 과열 에러 삭제..*/
    /*check_error_hot_overheat();*/
    check_error_room_overheat();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_hot_overheat(void)
{
    U8 u8_check_enable = CLEAR;

    if( Bit0_Hot_Tank_Temp_Open_Short_Error == SET )
    {
        Bit5_Hot_Heater_OverHeat_Error = CLEAR;
        gu8_hot_overheat_off_timer = 0;
        gu8_hot_overheat_on_timer = 0;
        return;
    }
    else{}

    if( gu8_Hot_Tank_Temperature_One_Degree >= 99 )
    {
        gu8_hot_overheat_off_timer = 0;
        gu8_hot_overheat_on_timer++;

        if( gu8_hot_overheat_on_timer >= HOT_OVERHEAT_ERROR_CHECK_TIME )
        {
            gu8_hot_overheat_on_timer = 30;
            Bit5_Hot_Heater_OverHeat_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_hot_overheat_on_timer = 0;

        if( gu8_Hot_Tank_Temperature_One_Degree <= 97 )
        {
            gu8_hot_overheat_off_timer++;

            if( gu8_hot_overheat_off_timer >= 30 )
            {
                gu8_hot_overheat_off_timer = 30;
                Bit5_Hot_Heater_OverHeat_Error = CLEAR;
            }
            else{}
        }
        else
        {
            gu8_hot_overheat_off_timer = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_overheat(void)
{
    if( Bit2_Room_Temp_Open_Short_Error == SET )
    {
        Bit1_Room_OverHeat_Error = CLEAR;
        gu8_room_overheat_off_timer = 0;
        gu8_room_overheat_on_timer = 0;
        return;
    }
    else{}

    if( gu8_Room_Temperature_One_Degree >= ROOM_OVERHEAT_ERROR_TEMP )
    {
        gu8_room_overheat_off_timer = 0;
        gu8_room_overheat_on_timer++;

        if( gu8_room_overheat_on_timer >= ROOM_OVERHEAT_ERROR_CHECK_TIME )
        {
            gu8_room_overheat_on_timer = ROOM_OVERHEAT_ERROR_CHECK_TIME;
            Bit1_Room_OverHeat_Error = SET;
        }
        else{}
    }
    else
    {
        gu8_room_overheat_on_timer = 0;

        if( gu8_Room_Temperature_One_Degree <= ROOM_OVERHEAT_CLEAR_TEMP )
        {
            gu8_room_overheat_off_timer++;

            if( gu8_room_overheat_off_timer >= ROOM_OVERHEAT_ERROR_CHECK_TIME )
            {
                gu8_room_overheat_off_timer = ROOM_OVERHEAT_ERROR_CHECK_TIME;
                Bit1_Room_OverHeat_Error = CLEAR;
            }
            else{}
        }
        else
        {
            gu8_room_overheat_off_timer = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


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
#include    "valve_extract.h"



void output_valve_extract(void);





U8 gu8LockLEDFlick;

bit F_LineTest;                   // 라인 테스트
bit F_LineTest2;                  // 라인 테스트2
//bit F_PartTest;                   // 파트 테스트
//bit F_PBATest;                    // PBA TEST
//bit F_NfcTest;

//===================================== Part Test
bit F_PartHeater;
bit F_PartComp;
bit F_PartIceHeater;
bit F_PartTrayVV;
bit F_PartColdVV;
bit F_PartTrayCW;
bit F_PartDrainPump;
bit F_PartCristal;
bit F_PartIR;
bit F_PartIce;


U8 gu8_hot_close_delay_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : Water Output
// 개요       : 추출 밸브
//----------------------------------------------------------------------------
// 기능       : 추출 밸브 동작

//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void output_valve_extract(void)
{
    /*calc_mix_water();*/
    open_hot_valve();

    if( F_WaterOut == SET )
    {
        /*..hui [23-3-22오후 5:38:51] 마이컵 세팅할때 물 추출은 무조건 정수로 고정..*/
        if( bit_my_cup_setting_start == SET )
        {
            pVALVE_24V_POWER = SET;
            pVALVE_ROOM_OUT = SET;
            pVALVE_COLD_OUT = CLEAR;
            pVALVE_HOT_OUT = CLEAR;
        }
        else if( u8WaterOutState == PURE_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;
            pVALVE_ROOM_OUT = SET;
            pVALVE_COLD_OUT = CLEAR;
            /*pVALVE_HOT_OUT = CLEAR;*/

            /*..hui [23-4-3오후 1:08:49] 정수탱크 저수위 감지되면 온수 추출도 정지..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                pVALVE_HOT_OUT = CLEAR;
            }
            else
            {
                if( bit_open_hot_valve == SET )
                {
                    pVALVE_HOT_OUT = SET;
                }
                else
                {
                    pVALVE_HOT_OUT = CLEAR;
                }
            }
        }
        else if( u8WaterOutState == COLD_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;
            pVALVE_COLD_OUT = SET;
            pVALVE_ROOM_OUT = CLEAR;
            pVALVE_HOT_OUT = CLEAR;
        }
        else if( u8WaterOutState == HOT_WATER_SELECT )
        {
            pVALVE_24V_POWER = SET;
            pVALVE_COLD_OUT = CLEAR;
            pVALVE_ROOM_OUT = CLEAR;
            pVALVE_HOT_OUT = SET;
        }
        else
        {
            pVALVE_24V_POWER = CLEAR;
            pVALVE_ROOM_OUT = CLEAR;
            pVALVE_COLD_OUT = CLEAR;
            pVALVE_HOT_OUT = CLEAR;
        }
    }
    else
    {
        //pVALVE_24V_POWER = CLEAR;
        
        if( pVALVE_COLD_DRAIN == SET )
        {
            pVALVE_24V_POWER = SET;
        }
        else
        {
            pVALVE_24V_POWER = CLEAR;
        }

        
        pVALVE_ROOM_OUT = CLEAR;
        pVALVE_COLD_OUT = CLEAR;
        pVALVE_HOT_OUT = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/







/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





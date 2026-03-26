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
#include    "valve_flushing.h"

void output_valve_flushing_feed(void);
void output_valve_flushing_nos(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8FlushingFeedValveONB;
#define            u8FlushingFeedValveON                        U8FlushingFeedValveONB.byte
#define            Bit0_Flushing__Feed_On_State                 U8FlushingFeedValveONB.Bit.b0
#define            Bit1_Water_Flushing__Feed_On_State           U8FlushingFeedValveONB.Bit.b1
#define            Bit2_FF_Acid_Clean__Feed_On_State            U8FlushingFeedValveONB.Bit.b2




TYPE_BYTE          U8FlushingFeedValveOFFB;
#define            u8FlushingFeedValveOFF                       U8FlushingFeedValveOFFB.byte
#define            Bit0_Flushing__Feed_Off_State                U8FlushingFeedValveOFFB.Bit.b0



/***********************************************************************************************************************/
TYPE_BYTE          U8FlushingNosValveONB;
#define            u8FlushingNosValveON                         U8FlushingNosValveONB.byte
#define            Bit0_Flushing__Nos_On_State                  U8FlushingNosValveONB.Bit.b0
#define            Bit1_Water_Flushing__Nos_On_State            U8FlushingNosValveONB.Bit.b1
#define            Bit2_FN_Acid_Clean__Nos_On_State             U8FlushingNosValveONB.Bit.b2




TYPE_BYTE          U8FlushingNosValveOFFB;
#define            u8FlushingNosValveOFF                        U8FlushingNosValveOFFB.byte
#define            Bit0_Flushing__Nos_Off_State                 U8FlushingNosValveOFFB.Bit.b0




/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_flushing_feed(void)
{
/***********************************************************************************************/
    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        /*if( gu8_flushing_step >= 1 && gu8_flushing_step <= 9 )*/
        if( gu8_flushing_step >= 1 && gu8_flushing_step <= 15 )
        {
            Bit0_Flushing__Feed_On_State = bit_flushing_start;
        }
        else
        {
            Bit0_Flushing__Feed_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Flushing__Feed_On_State = CLEAR;
    }

/***********************************************************************************************/

    /*..hui [23-6-16오후 2:51:06] 급수 플러싱할때..*/
    if( bit_flushing_water_start == SET )
    {
        /*if( gu8_water_flushing_step >= 1 && gu8_water_flushing_step <= 7 )*/
        if( gu8_water_flushing_step >= 1 && gu8_water_flushing_step <= 6 )
        {
            Bit1_Water_Flushing__Feed_On_State = SET;
        }
        else
        {
            Bit1_Water_Flushing__Feed_On_State = CLEAR;
        }
    }
    else
    {
        Bit1_Water_Flushing__Feed_On_State = CLEAR;
    }

    /*..hui [24-5-23오후 7:05:42] 구연산 세정할때..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
        {
            if( gu8_acid_rinse_step >= 2 && gu8_acid_rinse_step <= 6 )
            {
                Bit2_FF_Acid_Clean__Feed_On_State = SET;
            }
            else
            {
                Bit2_FF_Acid_Clean__Feed_On_State = CLEAR;
            }
        }
        else
        {
            Bit2_FF_Acid_Clean__Feed_On_State = CLEAR;
        }
    }
    else
    {
        Bit2_FF_Acid_Clean__Feed_On_State = CLEAR;
    }



/***********************************************************************************************/
    if (u8FlushingFeedValveOFF > 0)
    {
        pVALVE_FLUSHING_FEED = CLEAR;      /*off*/
    }
    else
    {
        if (u8FlushingFeedValveON > 0)
        {
            pVALVE_FLUSHING_FEED = SET;    /*on*/
        }
        else
        {
            pVALVE_FLUSHING_FEED = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_flushing_nos(void)
{
/***********************************************************************************************/
    if( gu8_flushing_mode == FLUSHING_MAIN_STATE )
    {
        /*if( gu8_flushing_step >= 1 && gu8_flushing_step <= 9 )*/
        /*..hui [23-9-20오전 9:49:09] 피드 열고 노스 닫고..*/
        /*..hui [23-9-20오전 9:49:35] 노스 열고 피드 닫고..*/
        /*if( gu8_flushing_step >= 2 && gu8_flushing_step <= 8 )*/
        if( gu8_flushing_step >= 2 && gu8_flushing_step <= 14 )
        {
            Bit0_Flushing__Nos_On_State = bit_flushing_start;
        }
        else
        {
            Bit0_Flushing__Nos_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Flushing__Nos_On_State = CLEAR;
    }

/***********************************************************************************************/

    /*..hui [23-6-16오후 2:51:06] 급수 플러싱할때..*/
    if( bit_flushing_water_start == SET )
    {
        /*if( gu8_water_flushing_step >= 1 && gu8_water_flushing_step <= 6 )*/
        if( gu8_water_flushing_step >= 2 && gu8_water_flushing_step <= 6 )
        {
            Bit1_Water_Flushing__Nos_On_State = SET;
        }
        else
        {
            Bit1_Water_Flushing__Nos_On_State = CLEAR;
        }
    }
    else
    {
        Bit1_Water_Flushing__Nos_On_State = CLEAR;
    }

    /*..hui [24-5-23오후 7:05:42] 구연산 세정할때..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
        {
            if( gu8_acid_rinse_step >= 3 && gu8_acid_rinse_step <= 6 )
            {
                Bit2_FN_Acid_Clean__Nos_On_State = SET;
            }
            else
            {
                Bit2_FN_Acid_Clean__Nos_On_State = CLEAR;
            }
        }
        else
        {
            Bit2_FN_Acid_Clean__Nos_On_State = CLEAR;
        }
    }
    else
    {
        Bit2_FN_Acid_Clean__Nos_On_State = CLEAR;
    }

/***********************************************************************************************/
    if (u8FlushingNosValveOFF > 0)
    {
        pVALVE_FLUSHING_NOS = CLEAR;      /*off*/
    }
    else
    {
        if (u8FlushingNosValveON > 0)
        {
            pVALVE_FLUSHING_NOS = SET;    /*on*/
        }
        else
        {
            pVALVE_FLUSHING_NOS = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





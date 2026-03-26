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
#include    "valve_ster_out.h"

void output_valve_ster_out_right(void);
void output_valve_ster_out_left(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8SterOutRightValveONB;
#define            u8SterOutRightValveON                         U8SterOutRightValveONB.byte
#define            Bit0_Ster_Out_Right_Hot_Ster_On_State         U8SterOutRightValveONB.Bit.b0
#define            Bit1_Ster_Out_Right_Flushing_Feed_On_State    U8SterOutRightValveONB.Bit.b1




TYPE_BYTE          U8SterOutRightValveOFFB;
#define            u8SterOutRightValveOFF                        U8SterOutRightValveOFFB.byte
#define            Bit0_Ster_Out_Right_Valve_Off_State           U8SterOutRightValveOFFB.Bit.b0



/***********************************************************************************************************************/
TYPE_BYTE          U8SterOutLeftValveONB;
#define            u8SterOutLeftValveON                          U8SterOutLeftValveONB.byte
#define            Bit0_Ster_Out_Left_Hot_Ster_On_State          U8SterOutLeftValveONB.Bit.b0
#define            Bit1_Ster_Out_Left_Flushing_Feed_On_State     U8SterOutLeftValveONB.Bit.b1




TYPE_BYTE          U8SterOutLeftValveOFFB;
#define            u8SterOutLeftValveOFF                          U8SterOutLeftValveOFFB.byte
#define            Bit0_Ster_Out_Left_Valve_Off_State            U8SterOutLeftValveOFFB.Bit.b0


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_ster_out_right(void)
{

    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            /*if( gu8_hot_spray_step >= 6 && gu8_hot_spray_step <= 8 )*/
            if( gu8_hot_spray_step >= 8 && gu8_hot_spray_step <= 10 )
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            /*if( gu8_lukewarm_spray_step >= 4 && gu8_lukewarm_spray_step <= 6 )*/
            /*if( gu8_lukewarm_spray_step >= 6 && gu8_lukewarm_spray_step <= 8 )*/
            if( gu8_lukewarm_spray_step >= 10 && gu8_lukewarm_spray_step <= 12 )
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            /*if( gu8_final_clean_step >= 4 && gu8_final_clean_step <= 6 )*/
            /*if( gu8_final_clean_step >= 6 && gu8_final_clean_step <= 8 )*/
            if( gu8_final_clean_step >= 10 && gu8_final_clean_step <= 12 )
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            if( gu8_melt_ice_step >= 10 && gu8_melt_ice_step <= 12 )
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = SET;
            }
            else if( gu8_melt_ice_step >= 18 && gu8_melt_ice_step <= 20 )
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
            }
        }
        else
        {
            Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Ster_Out_Right_Hot_Ster_On_State = CLEAR;
    }


    #if 0
     /*..hui [24-1-4오전 11:14:35] 탱크 플러싱할때.. 오버히팅NOS 차압때문에 온수탱크 에어 차는 현상..*/
     /*..hui [24-1-4오전 11:15:06] 탱크 L,R 2개 같이 켜주면 압이 줄어서 에어빼는데 도움이된다.. 이정환 부장님..*/
     if( gu8_flushing_mode == FLUSHING_TANK_STATE )
     {
         /*..hui [23-8-23오전 9:17:57] 만수위 아닐경우만 조건 추가..*/
         /*..hui [24-1-4오전 11:15:34] 피드밸브 열리는 조건에서만 같이 연다..*/
         if( gu8_Room_Water_Level != ROOM_LEVEL_FULL )
         {
             if( gu8_flushing_tank_step >= 1 && gu8_flushing_tank_step <= 3 )
             {
                 Bit1_Ster_Out_Right_Flushing_Feed_On_State = bit_flushing_tank_start;
             }
             else
             {
                 Bit1_Ster_Out_Right_Flushing_Feed_On_State = CLEAR;
             }
         }
         else
         {
             Bit1_Ster_Out_Right_Flushing_Feed_On_State = CLEAR;
         }
     }
     else
     {
         Bit1_Ster_Out_Right_Flushing_Feed_On_State = CLEAR;
     }
    #endif

    /*..hui [24-1-19오전 11:20:45] 원인이 이게 아니었음.. 삭제..*/
    Bit1_Ster_Out_Right_Flushing_Feed_On_State = CLEAR;

/***********************************************************************************************/




/***********************************************************************************************/
    if (u8SterOutRightValveOFF > 0)
    {
        pVALVE_ICE_TANK_STER_FEED_RIGHT = CLEAR;      /*off*/
    }
    else
    {
        if (u8SterOutRightValveON > 0)
        {
            pVALVE_ICE_TANK_STER_FEED_RIGHT = SET;    /*on*/
        }
        else
        {
            pVALVE_ICE_TANK_STER_FEED_RIGHT = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_ster_out_left(void)
{

    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_SPRAY_STATE )
        {
            if( gu8_hot_spray_step >= 3 && gu8_hot_spray_step <= 5 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            /*if( gu8_lukewarm_spray_step >= 1 && gu8_lukewarm_spray_step <= 3 )*/
            if( gu8_lukewarm_spray_step >= 5 && gu8_lukewarm_spray_step <= 7 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_FINAL_CLEAN_STATE )
        {
            /*if( gu8_final_clean_step >= 1 && gu8_final_clean_step <= 3 )*/
            if( gu8_final_clean_step >= 5 && gu8_final_clean_step <= 7 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step >= 6 && gu8_ice_tray_clean_step <= 10 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE )
        {
            if( gu8_melt_ice_step >= 6 && gu8_melt_ice_step <= 8 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else if( gu8_melt_ice_step >= 14 && gu8_melt_ice_step <= 16 )
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = SET;
            }
            else
            {
                Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
            }
        }
        else
        {
            Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Ster_Out_Left_Hot_Ster_On_State = CLEAR;
    }


    #if 0
    /*..hui [24-1-4오전 11:14:35] 탱크 플러싱할때.. 오버히팅NOS 차압때문에 온수탱크 에어 차는 현상..*/
    /*..hui [24-1-4오전 11:15:06] 탱크 L,R 2개 같이 켜주면 압이 줄어서 에어빼는데 도움이된다.. 이정환 부장님..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        /*..hui [23-8-23오전 9:17:57] 만수위 아닐경우만 조건 추가..*/
        /*..hui [24-1-4오전 11:15:34] 피드밸브 열리는 조건에서만 같이 연다..*/
        if( gu8_Room_Water_Level != ROOM_LEVEL_FULL )
        {
            if( gu8_flushing_tank_step >= 1 && gu8_flushing_tank_step <= 3 )
            {
                Bit1_Ster_Out_Left_Flushing_Feed_On_State = bit_flushing_tank_start;
            }
            else
            {
                Bit1_Ster_Out_Left_Flushing_Feed_On_State = CLEAR;
            }
        }
        else
        {
            Bit1_Ster_Out_Left_Flushing_Feed_On_State = CLEAR;
        }
    }
    else
    {
        Bit1_Ster_Out_Left_Flushing_Feed_On_State = CLEAR;
    }
    #endif

    /*..hui [24-1-19오전 11:20:45] 원인이 이게 아니었음.. 삭제..*/
    Bit1_Ster_Out_Left_Flushing_Feed_On_State = CLEAR;
/***********************************************************************************************/




/***********************************************************************************************/
    if (u8SterOutLeftValveOFF > 0)
    {
        pVALVE_ICE_TANK_STER_FEED_LEFT = CLEAR;      /*off*/
    }
    else
    {
        if (u8SterOutLeftValveON > 0)
        {
            pVALVE_ICE_TANK_STER_FEED_LEFT = SET;    /*on*/
        }
        else
        {
            pVALVE_ICE_TANK_STER_FEED_LEFT = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





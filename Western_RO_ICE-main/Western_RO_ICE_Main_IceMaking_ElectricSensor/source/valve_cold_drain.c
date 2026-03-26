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
#include    "valve_cold_drain.h"

void output_cold_drain_valve(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8ColdDrainValveONB;
#define            u8ColdDrainValveON                      U8ColdDrainValveONB.byte
#define            Bit0_CD_Flushing_Tank_Drain_On_State    U8ColdDrainValveONB.Bit.b0
#define            Bit1_CD_Circul_Drain_On_State           U8ColdDrainValveONB.Bit.b1
#define            Bit2_CD_Manual_Drain_On_State           U8ColdDrainValveONB.Bit.b2
#define            Bit3_CD_Ice_Ster_On_State               U8ColdDrainValveONB.Bit.b3
#define            Bit4_CD_Drain_Retry_On_State            U8ColdDrainValveONB.Bit.b4
#define            Bit5_CD_Drain_Acid_On_State             U8ColdDrainValveONB.Bit.b5




TYPE_BYTE          U8ColdDrainValveOFFB;
#define            u8ColdDrainValveOFF                     U8ColdDrainValveOFFB.byte
#define            Bit0_CD_Error_Off_State                 U8ColdDrainValveOFFB.Bit.b0



/***********************************************************************************************************************/
bit F_auto_drain_mode_cold_water_valve_out;

bit bit_cold_drain_output;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_cold_drain_valve(void)
{
    /***********************************************************************************************/
    /*..hui [23-8-25오후 1:22:05] 플러싱 동작중.. 탱크 비우기 할때..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE )
    {
        if( bit_flushing_tank_start == SET )
        {
            if( bit_tank_drain_valve_output == SET )
            {
                Bit0_CD_Flushing_Tank_Drain_On_State = SET;
            }
            else
            {
                Bit0_CD_Flushing_Tank_Drain_On_State = CLEAR;
            }
        }
        else
        {
            Bit0_CD_Flushing_Tank_Drain_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_CD_Flushing_Tank_Drain_On_State = CLEAR;
    }

    /*..hui [23-8-25오후 1:19:11] 순환배수 설정 ON..*/
    if( F_Circul_Drain == SET )
    {
        if( F_DrainStatus == SET )
        {
            /*..hui [23-8-25오후 1:19:18] 순환배수 진행 중..*/
            if(F_auto_drain_mode_cold_water_valve_out == SET)
            {
                Bit1_CD_Circul_Drain_On_State = SET;
            }
            else
            {
                Bit1_CD_Circul_Drain_On_State = CLEAR;
            }
        }
        else
        {
            Bit1_CD_Circul_Drain_On_State = CLEAR;
        }
    }
    else
    {
        Bit1_CD_Circul_Drain_On_State = CLEAR;
    }

    /*..hui [23-8-25오후 1:21:54] 수동 배수 동작 중..*/
    if( bit_manual_drain_start == SET )
    {
        if(bit_manual_drain_valve_output == SET)
        {
            Bit2_CD_Manual_Drain_On_State = SET;
        }
        else
        {
            Bit2_CD_Manual_Drain_On_State = CLEAR;
        }
    }
    else
    {
        Bit2_CD_Manual_Drain_On_State = CLEAR;
    }


    /*..hui [23-8-25오후 1:34:34] 온수 세척 중 드레인 탱크 습기에 의한 센서 감지 방지하기 위해..*/
    if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-10-12오후 5:26:31] 45도 조건일 경우 준비모드에서 냉수 10초 넣어놓고 시작..*/
        if( gu8_ice_ster_mode ==  STER_MODE_PREPARE )
        {
            Bit3_CD_Ice_Ster_On_State = CLEAR;
        }
        else if( gu8_ice_ster_mode ==  STER_MODE_HOT_SPRAY_STATE )
        {
            /*Bit3_CD_Ice_Ster_On_State = CLEAR;*/

            if( gu8_hot_spray_step == 4 || gu8_hot_spray_step == 9 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [24-1-29오후 1:05:12] 1차 세척때는 7.5초로..*/
                        if( gu16_hot_spray_timer <= 120 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else
            {
                Bit3_CD_Ice_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode ==  STER_MODE_LUKEWARM_SPRAY_STATE )
        {
            if( gu8_lukewarm_spray_step == 6 || gu8_lukewarm_spray_step == 11 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        /*if( gu16_lukewarm_spray_timer <= ICE_STER_COLD_DRAIN_OPEN_TIME )*/
                        /*if( gu16_lukewarm_spray_timer <= 100 )*/
                        if( gu16_lukewarm_spray_timer <= 120 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else
            {
                Bit3_CD_Ice_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode ==  STER_MODE_FINAL_CLEAN_STATE )
        {
            if( gu8_final_clean_step == 6 || gu8_final_clean_step == 11)
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        /*if( gu16_final_clean_timer <= ICE_STER_COLD_DRAIN_OPEN_TIME )*/
                        if( gu16_final_clean_timer <= 120 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else
            {
                Bit3_CD_Ice_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode ==  STER_MODE_ICE_TRAY_CLEAN )
        {
            if( gu8_ice_tray_clean_step == 9 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        if( gu16_ice_tray_clean_timer <= 80 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else if( gu16_ice_tray_clean_timer > 300
                                 && gu16_ice_tray_clean_timer <= 380 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else if( gu16_ice_tray_clean_timer > 600
                                 && gu16_ice_tray_clean_timer <= 680 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else if( gu16_ice_tray_clean_timer > 900
                                 && gu16_ice_tray_clean_timer <= 980 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else if( gu16_ice_tray_clean_timer > 1200
                                 && gu16_ice_tray_clean_timer <= 1280 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else if( gu16_ice_tray_clean_timer > 1500
                                 && gu16_ice_tray_clean_timer <= 1600 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }


                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else if( gu8_ice_tray_clean_step == 14 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    /*if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )*/
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        /*if( gu16_ice_tray_clean_timer <= ICE_STER_COLD_DRAIN_OPEN_TIME )*/
                        /*if( gu16_ice_tray_clean_timer <= 150 )*/
                        /*if( gu16_ice_tray_clean_timer <= 200 )*/
                        /*if( gu16_ice_tray_clean_timer <= 250 )*/
                        if( gu16_ice_tray_clean_timer <= 100 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else if( gu8_ice_tray_clean_step == 16 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        /*if( gu16_ice_tray_clean_timer <= ICE_STER_COLD_DRAIN_OPEN_TIME )*/
                        /*if( gu16_ice_tray_clean_timer <= 50 )*/
                        /*if( gu16_ice_tray_clean_timer <= 80 )*/
                        if( gu16_ice_tray_clean_timer <= 100 )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else
            {
                Bit3_CD_Ice_Ster_On_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode ==  STER_MODE_MELT_ICE )
        {
            /*..hui [23-10-17오후 2:43:05] 얼음 해빙작업 할때도 5초동안 넣어준다..*/
            if( gu8_melt_ice_step == 7 || gu8_melt_ice_step == 11 || gu8_melt_ice_step == 15 || gu8_melt_ice_step == 19 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    if( Bit1_Tray_Pump_Ster_Drain_Full_Off_State == CLEAR && bit_tray_pump_output == SET )
                    {
                        /*..hui [23-8-25오후 1:31:30] 우선 5초동안 중탕..*/
                        /*..hui [24-2-7오후 4:41:36] 7초로 변경..*/
                        if( gu16_melt_ice_timer <= ICE_STER_COLD_DRAIN_OPEN_TIME )
                        {
                            Bit3_CD_Ice_Ster_On_State = SET;
                        }
                        else
                        {
                            Bit3_CD_Ice_Ster_On_State = CLEAR;
                        }
                    }
                    else
                    {
                        Bit3_CD_Ice_Ster_On_State = CLEAR;
                    }
                }
                else
                {
                    Bit3_CD_Ice_Ster_On_State = CLEAR;
                }
            }
            else
            {
                Bit3_CD_Ice_Ster_On_State = CLEAR;
            }
        }
        else
        {
            Bit3_CD_Ice_Ster_On_State = CLEAR;
        }
    }
    else
    {
        Bit3_CD_Ice_Ster_On_State = CLEAR;
    }



    /*..hui [24-3-28오후 2:38:31] 저수위 일시적 오감지일때 씻어주기..*/
    if( bit_drain_error_check_enable == SET )
    {
        /*..hui [24-3-28오후 2:37:17] 드레인탱크 저수위 감지 상태일 경우에만..*/
        /*..hui [24-3-28오후 2:37:27] 혹시몰라 비어있는 상태도 추가..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
        {
            if( gu8_drain_pump_retry_step == DRAIN_RETRY_COLD_DRIN_ON )
            {
                Bit4_CD_Drain_Retry_On_State = SET;
            }
            else
            {
                Bit4_CD_Drain_Retry_On_State = CLEAR;
            }
        }
        else
        {
            Bit4_CD_Drain_Retry_On_State = CLEAR;
        }
    }
    else
    {
        Bit4_CD_Drain_Retry_On_State = CLEAR;
    }


    /*..hui [24-5-23오후 5:40:22] 구연산 세척할때..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_NONE_STATE )
        {
            Bit5_CD_Drain_Acid_On_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_STANDBY )
        {
            Bit5_CD_Drain_Acid_On_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE )
        {
            if( gu8_acid_prepare_step == 1 )
            {
                if( bit_acid_drain_valve_output == SET )
                {
                    Bit5_CD_Drain_Acid_On_State = SET;
                }
                else
                {
                    Bit5_CD_Drain_Acid_On_State = CLEAR;
                }
            }
            else if( gu8_acid_prepare_step == 4 )
            {
                /*..hui [24-7-22오후 3:00:06] 구연산 재정수하면서 저수위 이상 차면.. 드레인탱크에 구연산 입수..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    Bit5_CD_Drain_Acid_On_State = SET;
                }
                else
                {
                    Bit5_CD_Drain_Acid_On_State = CLEAR;
                }
            }
            else
            {
                Bit5_CD_Drain_Acid_On_State = CLEAR;
            }
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
        {
            Bit5_CD_Drain_Acid_On_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR )
        {
            Bit5_CD_Drain_Acid_On_State = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
        {
            if( gu8_acid_rinse_step == 1|| gu8_acid_rinse_step == 10 || gu8_acid_rinse_step == 13 )
            {
                if( bit_acid_drain_valve_output == SET )
                {
                    Bit5_CD_Drain_Acid_On_State = SET;
                }
                else
                {
                    Bit5_CD_Drain_Acid_On_State = CLEAR;
                }
            }
            else
            {
                Bit5_CD_Drain_Acid_On_State = CLEAR;
            }
        }
        else /*if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )*/
        {
            Bit5_CD_Drain_Acid_On_State = CLEAR;
        }
    }
    else
    {
        Bit5_CD_Drain_Acid_On_State = CLEAR;
    }




///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-8-25오후 1:10:25] 드레인 펌프 에러, 누수 에러일 경우 무조건 OFF..*/
    if( Bit16_Drain_Pump_Error__E60 == SET || Bit3_Leakage_Sensor_Error__E01 == SET )
    {
        Bit0_CD_Error_Off_State = SET;
    }
    else
    {
        Bit0_CD_Error_Off_State = CLEAR;
    }



/***********************************************************************************************/
    if (u8ColdDrainValveOFF > 0)
    {
        pVALVE_COLD_DRAIN = CLEAR;      /*off*/
        bit_cold_drain_output = CLEAR;
    }
    else
    {
        if (u8ColdDrainValveON > 0)
        {
            pVALVE_COLD_DRAIN = SET;    /*on*/
            bit_cold_drain_output = SET;
        }
        else
        {
            pVALVE_COLD_DRAIN = CLEAR;  /*off*/
            bit_cold_drain_output = CLEAR;
        }
    }
/***********************************************************************************************/

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




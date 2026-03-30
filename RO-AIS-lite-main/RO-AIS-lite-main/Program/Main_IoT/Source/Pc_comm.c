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
#include    "pc_comm.h"

void Pc_Communication(void);

void Uart_ISR3_PC_Rx(void);
void PC_Rx_Process(void);
void PC_Rx_Data_Read(void);
void PC_Tx_Process(void);
void PC_Tx_Data_Read(void);
void Uart_ISR3_PC_Tx( void );


U8  u8RxCount;
U8  u8RxData[PC_DATA_PACKET_MAX_LENGTH];
U8  u8RxLength;
U8  u8RxFinish;
U8  u8PCCommStart;

U8  u8TxCount;
U8  u8TxData[DATA_PACKET_MAX_LENGTH];
U8  u8TxLength;
U8  u8TxFinish;

U8  u8TxEnable;
//U8 Err_Num;

U8  debug_temp_room;
U8  debug_temp_ambi;
I8  debug_temp_eva;
I8  debug_temp_cold;
I8  debug_temp_hot;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pc_Communication(void)
{
    PC_Rx_Process();
    PC_Tx_Process();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR3_PC_Rx(void)
{
    U8 RxBuffer = RXD3;

    if(u8RxCount == 0)
    {
        if(RxBuffer == 0x7f)
        {
            u8RxData[u8RxCount] = RxBuffer;
            u8RxCount++;
        }
        else
        {
            u8RxCount = 0;
        }
    }
    else if(u8RxCount == 1)
    {
        if(RxBuffer == STX)
        {
            u8RxData[u8RxCount] = RxBuffer;
            u8RxCount++;
        }
        else
        {
            u8RxCount = 0;
        }
    }
    else if(u8RxCount >= 2)
    {
        u8RxData[u8RxCount] = RxBuffer;
        u8RxCount++;

        if(u8RxCount > PC_DATA_PACKET_MAX_LENGTH - 1)
        {
            if(u8RxData[PC_DATA_PACKET_MAX_LENGTH - 1] == ETX)
            {
                u8RxFinish = SET;
                u8RxCount = 0;
            }
            else
            {
                u8RxCount = 0;
            }
        }
    }
    else
    {

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PC_Rx_Process(void)
{
    if(u8RxFinish == SET)
    {
        PC_Rx_Data_Read();
        u8RxFinish = CLEAR;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PC_Rx_Data_Read(void)
{
    U8 PCRxCount;
    U8 PCRX_SUM = 0;

    if(u8RxData[2] == 1)// (PCRX_SUM == u8RxData[u8RxLength-1] && u8RxData[3] == 1)
    {
        u8PCCommStart = SET;
        u8TxCount = 0;
    }
    else
    {
        u8PCCommStart = CLEAR;

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PC_Tx_Process(void)
{
    //u8PCCommStart = SET;
    if(u8PCCommStart == SET)
    {
        PC_Tx_Data_Read();
        /*Uart_ISR3_PC_Tx();*/

        TXD3 = u8TxData[0];
        u8TxCount = 1;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//
void PC_Tx_Data_Read(void)
{
    U8 TxCount;
    U8 PCTX_SUM = 0;
    U16 tempComm = 0;
    //U8 Err_Num = 0;
    U8 mu8_ice_make = 0;

    //u8TxLength = 20;
    for(TxCount = 0; TxCount < DATA_PACKET_MAX_LENGTH; TxCount++)
    {
        u8TxData[TxCount] = 0;
    }

    u8TxData[0] = STX;
    u8TxData[1] = 0x7F;
    u8TxData[2] = 35;
    u8TxData[3] = gu8_Hot_Flow_Rate;
    u8TxData[4] = gu8_Flow_1sec;

    #if 0
    if( gu8_ice_setting == ICE_SETTING_ICE_FIRST )
    {
        mu8_ice_make = 1;
    }
    else
    {
        mu8_ice_make = 0;
    }
    #endif

    if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
    {
        mu8_ice_make = 1;
    }
    else
    {
        mu8_ice_make = 0;
    }

    u8TxData[5] = (((gu8_GasSwitch_Status & 0x01) << 7) & 0x80) |
                   (((mu8_ice_make & 0x01) << 6) & 0x40) |
                   ((Bit0_Cold_Make_Go << 5) & 0x20) |
                   ((Bit1_Ice_Make_Go << 4) & 0x10) |
                   ((0 << 3) & 0x08) |
                   ((0 << 2) & 0x04) |
                   ((0 << 1) & 0x02) |
                   (0);


    u8TxData[6] = ((pVALVE_FEED << 7) & 0x80) |        /*feed valve*/
                   ((pDC_FAN << 6) & 0x40) |         /*fan*/
                   ((pVALVE_NOS << 5) & 0x20) |         /* nos..*/
                   //((pVALVE_ICE_TRAY_IN << 4) & 0x10) |    /* 냉수입수*/
                   ((pVALVE_ROOM_OUT << 3) & 0x08) |    /*정수추출*/
                   ((pVALVE_HOT_OUT << 2) & 0x04) |    /* 온수추출*/
                   ((pVALVE_COLD_OUT << 1) & 0x02) |    /* 냉수추출*/
                   (pVALVE_24V_POWER);                 /*추출밸브 전원공급*/


    u8TxData[7] = /*((~pLEVEL_PURIFY_LOW << 7) & 0x80) |*/        /*정수탱크 저수위*/
                   ((pLEVEL_PURIFY_LOW << 7) & 0x80) |
                   ((pLEVEL_PURIFY_HIGH << 6) & 0x40) |   /*정수탱크 만수위*/
                   ((~pICE_MICRO_SW_HIGH << 5) & 0x20) |    /* 얼음받이 마이크로스위치..*/
                   ((~pICE_MICRO_SW_LOW << 4) & 0x10) |    /* 얼음받이 마이크로스위치*/
                   //((pHEATER_HOT_TRIAC_L << 3) & 0x08) |    /*냉수탱크 만수위*/
                   ((pLEVEL_ICE_DRAIN_LOW << 2) & 0x04) |    /*드레인탱크 저수위*/
                   ((pLEVEL_ICE_DRAIN_HIGH << 1) & 0x02) |    /*드레인탱크 만수위*/
                   (pCOMP);                                      /*COMP*/


    u8TxData[8] = ((pHEATER_ICE << 7) & 0x80) |        /*탈빙히터*/
                   ((pHEATER_HOT << 6) & 0x40) |         /*온수히터*/
                   ((pIR_POWER << 5) & 0x20) |       /*만빙발신..*/
                   ((pVALVE_COLD_DRAIN << 4) & 0x10) |    /*냉수 배수밸브*/
                   ((pMOTOR_ICE_OUT_CW << 3) & 0x08) |           /*얼음토출모터 CW*/
                   ((pMOTOR_ICE_OUT_CCW << 2) & 0x04) |          /*얼음토출모터 CCW*/
                   ((pMOTOR_ICE_TRAY_CW << 1) & 0x02) |                   /*얼음받이모터 CW*/
                   (pMOTOR_ICE_TRAY_CCW);                                    /* 얼음받이모터 CCW*/

    u8TxData[9] = ((pSWING_BAR << 7) & 0x80) |        /*스윙바*/
                   ((bit_tray_pump_output << 6) & 0x40) |
                   ((F_Drain_Pump_Output << 5) & 0x20) |
                   ((0 << 4) & 0x10) |
                   ((pUV_LED_ICE_TANK << 3) & 0x08) |
                   ((pUV_LED_WATER_FAUCET << 2) & 0x04) |
                   ((0 << 1) & 0x02) |
                   (0);

    u8TxData[10] = gu8_Error_Code;
    u8TxData[11] = (U8)(gu16CompOffDelay / 20);
    u8TxData[12] = gu8IceStep;
    u8TxData[13] = gu8IceTrayLEV ;

    u8TxData[14] = (U8)(gu16StepMotor2/(U16)256);
    u8TxData[15] = (U8)(gu16StepMotor2%(U16)256);

    u8TxData[16] = (U8)gs16_sm_info_current;
    u8TxData[17] = (U8)0;

    u8TxData[18] = (U8)(gu16IceHeaterTime/(U16)256);
    u8TxData[19] = (U8)(gu16IceHeaterTime%(U16)256);

    u8TxData[20] = (U8)(gu16IceMakeTime/(U16)256);
    u8TxData[21] = (U8)(gu16IceMakeTime%(U16)256);

    u8TxData[22] = (U8)gu8_Hot_Tank_Temperature_One_Degree;      //19
    u8TxData[23] = (U8)0;//u8Delta_Power_Level; //gu8_Eva_Cold_Temperature_One_Degree;

    u8TxData[24] = (U8)0;//u8Target_Hz_Hot;//gu8_Eva_Ice_Temperature_One_Degree;
    u8TxData[25] = (U8)gu8_Amb_Temperature_One_Degree;
    u8TxData[26] = (U8)gu8_Cold_Temperature_One_Degree;
    u8TxData[27] = (U8)gu8_Room_Temperature_One_Degree;
    u8TxData[28] = (U8)gu8_Hot_Tank_Temperature_One_Degree;

    u8TxData[29] = u8DrainWaterLevel;
    u8TxData[30] = gu8_room_level;
    u8TxData[31] = gu8InitStep;
    u8TxData[32] = ((F_IceInit << 7) & 0x80) |
                   ((0 << 6) & 0x40) |
                   ((F_Safety_Routine << 5) & 0x20) |
                   ((F_Ice_Tray_Up_Move_Reset << 4) & 0x10) |
                   ((F_Ice_Tray_Down_Move_Reset << 3) & 0x08) |
                   //((pVALVE_HOT_DRAIN << 2) & 0x04) |
                   ((F_TrayMotorCW << 1) & 0x02) |
                   (F_TrayMotorCCW);
    u8TxData[33] = (U8)0;
    u8TxData[34] = ETX;

    #if 0
    for (TxCount = 1; TxCount <= u8TxLength -2; TxCount ++)
    {
        PCTX_SUM = PCTX_SUM + u8TxData[TxCount];
    }
    u8TxData[10] = PCTX_SUM;
    u8TxData[11] = 0x9F;
    #endif

    //for(TxCount = 0; TxCount < DATA_PACKET_MAX_LENGTH; TxCount++)
    //{
    //    u8TxData[TxCount] = 0;
    //}
    //u16intempComm = (U16)(f32InHot_Temperature * 10);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR3_PC_Tx( void )
{
    #if 0
    for(u8TxCount = 0; u8TxCount < DATA_PACKET_MAX_LENGTH; u8TxCount++)
    {
        TXD3 = u8TxData[u8TxCount];
        while ( !STIF3 );
        STIF3 = 0;
    }
    #endif

    if( u8TxCount < DATA_PACKET_MAX_LENGTH )
    {
        TXD3 = u8TxData[u8TxCount];
        u8TxCount++;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



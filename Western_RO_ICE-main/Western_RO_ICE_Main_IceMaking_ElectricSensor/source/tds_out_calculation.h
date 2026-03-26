/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TDS_OUT_CALCULATION_H_
#define _TDS_OUT_CALCULATION_H_

//
extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


extern bit F_TDS_ON;
extern U16 gu16_AD_Result_TDS_Out_Temp;
extern U16 gu16_AD_Result_TDS_Out_Data;
extern U16 gu16_display_tds_out_sensor;



#endif

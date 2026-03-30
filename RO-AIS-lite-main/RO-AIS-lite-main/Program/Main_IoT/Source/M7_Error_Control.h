/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _ERROR_CONTROL_H_
#define _ERROR_CONTROL_H_


extern void ErrorSaveStart( U8 mu8_err_code );
extern void ErrorSave(void);
extern void check_error_temp_sensor(void);
extern void check_flow_error(void);
extern void check_error_water_level(void);
extern void hot_water_error_check(void);
extern void down_tray_motor(void);
extern void BuzStep(U8 mu8Step);

extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2

extern TYPE_BYTE          U8ErrorPopupEnableB;
#define            u8ErrorPopupEnable              U8ErrorPopupEnableB.byte
#define            Bit0_Now_Error_Occur_State      U8ErrorPopupEnableB.Bit.b0
#define            Bit1_Hot_Error_Repeat_State     U8ErrorPopupEnableB.Bit.b1




#define COLD_OPEN   1023-20        // �ü���̽��� ���� = 4.9V
#define COLD_SHORT  20             // �ü���̽��� ��Ʈ = 0.1V
#define HOT_OPEN    1023-20        // �¼���̽��� ���� = 4.9V
#define HOT_SHORT   20             // �¼���̽��� ��Ʈ = 0.1V
#define ROOM_OPEN   255-5          // ������̽��� ���� = 4.9V
#define ROOM_SHORT  5              // ������̽��� ��Ʈ = 0.1V
#define EVA_OPEN    255-5          // ���߱��̽��� ���� = 4.9V
#define EVA_SHORT   5              // ���߱��̽��� ��Ʈ = 0.1V
#define AMB_OPEN    255-5          // �����µ���̽��� ���� = 4.9V
#define AMB_SHORT   5              // �����µ���̽��� ��Ʈ = 0.1V

#define MAX_ERROR_NUM          32


extern bit F_Hot_Enable;
extern U8 gu8_Room_Water_Level;
extern U16 gu16_AD_Result_Cold;
extern bit F_Cold_Enable;

//extern bit F_ColdWaterInit;
//extern U8 gu8ColdWaterLEV;
extern U16 gu16_AD_Result_Room;
extern U16 gu16_AD_Result_Eva_First;
extern U16 gu16_AD_Result_Amb;
extern U16 gu16IceMakingADVal;

extern bit F_WaterOut;
extern U16 gu16_water_select_return_time;
extern U8 u8Extract_Continue;
extern bit F_Tray_In_Error_Temporary;

extern bit F_Model_Select;

extern bit F_IceInit;
extern U8 gu8IceTrayLEV;
//extern bit F_Memento;
extern bit F_IR;
extern ICE_STEP gu8IceStep;

extern U8 gu8_rtc_time_Year;
extern U8 gu8_rtc_time_Month;
extern U8 gu8_rtc_time_Date;

extern bit F_FW_Version_Display_Mode;

extern bit bit_self_test_start;


#endif

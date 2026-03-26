/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TDS_CONTROL_H_
#define _TDS_CONTROL_H_




//
//extern void tds_out_control(void);
//extern void test_tds(void);


extern TYPE_BYTE          U8TDS_ErrorB;
#define            gu8_TDS_Error                                             U8TDS_ErrorB.byte
#define            Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90         U8TDS_ErrorB.Bit.b0
#define            Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91        U8TDS_ErrorB.Bit.b1
#define            Bit2_No_Display_Tds_In_Data_Error__E92                    U8TDS_ErrorB.Bit.b2
#define            Bit3_No_Display_Tds_Out_Data_Error__E93                   U8TDS_ErrorB.Bit.b3
#define            Bit4_No_Display_Tds_In_Pollution_Error__E98               U8TDS_ErrorB.Bit.b4
#define            Bit5_No_Display_Tds_Remove_Error__E99                     U8TDS_ErrorB.Bit.b5


extern TYPE_BYTE          U8FeedValveONB;
#define            u8FeedValveON                         U8FeedValveONB.byte
#define            Bit0_Low_Water_Filling_State          U8FeedValveONB.Bit.b0
#define            Bit1_Feed_Valve_Flushing_State        U8FeedValveONB.Bit.b1
#define            Bit2_Feed_Valve_Water_Flushing_State  U8FeedValveONB.Bit.b2
#define            Bit3_Feed_Valve_Flushing_Tank_State   U8FeedValveONB.Bit.b3

extern bit F_TDS_ON;
extern U16 gu16TDS_IN_Final;
//extern U16 gu16TDS_OUT_Final;
//extern U16 gu16TDS_OUT_Pulse_Time;
//extern U32 gu32_total_water_flow_acc;

extern bit F_WaterOut;
//extern U8 gu8_Flow_1sec;

//extern U8 gu8_water_input_step;
//extern U8 gu8_Tank_Water_Level;
extern U8 gu8_wifi_tds_update;
extern U8 gu8_Room_Water_Level;
extern bit bit_feed_output;
extern U16 gu16TDS_OUT_Final;
extern bit bit_flushing_water_start;
extern bit bit_ice_tank_ster_start;
extern ICE_STEP gu8IceStep;
extern U16 gu16TDS_OUT_Pulse_Time;

extern FLUSHING_STEP gu8_flushing_mode;
extern bit bit_acid_clean_start;



#define TDS_STABLE_TIME                       30
#define TDS_CHEAK_TIME                        60

/*#define TDS_CHECK_LIMIT_ONE_DAY               3*/
#define TDS_CHECK_LIMIT_ONE_DAY               1


/*#define TDS_DATA_ERROR_COUNT                5*/
/*#define TDS_DATA_ERROR_COUNT                  10*/
#define TDS_DATA_ERROR_COUNT                  5

/*..hui [24-8-13오전 10:47:12] 원수 오염에러 3회..*/
#define TDS_POLLUTION_ERROR_COUNT             3


/*#define TDS_REMOVE_ERROR_RATIO                60*/
/*..hui [24-8-6오후 2:04:12] 제거율 70퍼센트로 변경..*/
#define TDS_REMOVE_ERROR_RATIO                70

/*#define TDS_REMOVE_ERROR_COUNT              3*/
/*#define TDS_REMOVE_ERROR_COUNT                10*/
/*..hui [24-8-13오전 10:42:57] 다시 3회로 변경..*/
#define TDS_REMOVE_ERROR_COUNT                3


/*#define TDS_CHECK_WATER_IN_TIME               4200*/
/*#define TDS_CHECK_WATER_IN_TIME               2400*/
/*#define TDS_CHECK_WATER_IN_TIME               1800*/
#define TDS_CHECK_WATER_IN_TIME               800







#endif

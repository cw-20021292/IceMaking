/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MODE_DECISION_H_
#define _MODE_DECISION_H_

//
extern TYPE_BYTE          U8OperationB;
#define            u8Operation                             U8OperationB.byte
#define            Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define            Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define            Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2

extern TYPE_BYTE          U8CodyInspectOperationB;
#define            u8CodyInspectOperation                      U8CodyInspectOperationB.byte
#define            Bit0_Cody_Service_Kit_Start                 U8CodyInspectOperationB.Bit.b0
#define            Bit1_Empty_Tank_Start                       U8CodyInspectOperationB.Bit.b1
#define            Bit2_Ice_Tray_Test_Start                    U8CodyInspectOperationB.Bit.b2


#define COLD_ON_TEMP_NORMAL         68
#define COLD_ON_TEMP_SAVING         100

#define COLD_OFF_REF_TEMP_AMB       300
#define COLD_OFF_TEMP_4_DEGREE      40
#define COLD_OFF_TEMP_5_DEGREE      50
#define PROTECT_COLD_TEMP           20

#define DUAL_OP_TEMP_AMB_20_DEGREE     200

#define COLD_ADD_OPERATION_TIME     18000





/*#define ICE_MAKE_GOGOGO       0x3F*/

/*#define ICE_MAKE_GOGOGO        0x1FF*/
/*#define COLD_MAKE_GOGOGO       0x7F*/

#define ICE_MAKE_GOGOGO        0x3FF
#define COLD_MAKE_GOGOGO       0xFF


//extern bit F_IceOn;
extern bit F_Cold_Enable;
//extern bit F_Fast_Ice_Make;
extern U16 gu16_Cold_Temperature;
extern U16 gu16_Amb_Temperature;
extern U8 gu8_Room_Water_Level;
extern bit F_IceInit;
extern bit F_IceStop;
extern U8 gu8_GasSwitch_Status;
extern bit F_FW_Version_Display_Mode;
extern bit F_Safety_Routine;
extern bit F_ColdConty;
extern U8 gu8_cold_setting_level;
//extern bit F_Sleep;
extern bit F_IceFull;
extern ICE_STEP gu8IceStep;


extern U8 gu8_Amb_Temperature_One_Degree;
extern bit bit_first_ice_full;
extern bit bit_fast_ice_make;
extern bit F_IceOn;
extern bit bit_9_hour_no_use_start;
extern bit bit_sleep_mode_start;

#endif

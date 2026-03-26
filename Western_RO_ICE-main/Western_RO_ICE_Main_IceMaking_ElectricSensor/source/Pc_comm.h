/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _PCCOMM_H_
#define _PCCOMM_H_

const I8 Temp_Eva_Debug[] =
{
    -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
    -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
    -30, -30, -30, -29, -28, -28, -27, -26, -26, -25,
    -24, -24, -23, -22, -22, -21, -21, -20, -20, -19,
    -19, -18, -18, -17, -17, -16, -16, -15, -15, -14,
    -14, -13, -13, -13, -12, -12, -11, -11, -11, -10,
    -10, -9, -9, -9, -8, -8, -7, -7, -7, -6,
    -6, -6, -5, -5, -5, -4, -4, -3, -3, -3,
    -2, -2, -2, -1, -1, -1, 0, 0, 0, 1,
    1, 1, 2, 2, 2, 3, 3, 3, 4, 4,
    4, 5, 5, 5, 6, 6, 6, 7, 7, 7,
    8, 8, 8, 9, 9, 9, 9, 10, 10, 10,
    11, 11, 11, 12, 12, 12, 13, 13, 13, 14,
    14, 14, 15, 15, 15, 16, 16, 16, 17, 17,
    17, 18, 18, 18, 19, 19, 19, 20, 20, 21,
    21, 21, 22, 22, 22, 23, 23, 23, 24, 24,
    25, 25, 25, 26, 26, 26, 27, 27, 28, 28,
    28, 29, 29, 30, 30, 30, 31, 31, 32, 32,
    33, 33, 34, 34, 34, 35, 35, 36, 36, 37,
    37, 38, 38, 39, 39, 40, 40, 41, 42, 42,
    43, 43, 44, 44, 45, 46, 46, 47, 48, 48,
    49, 50, 50, 51, 52, 53, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
    68, 69, 70, 71, 73, 75, 77, 79, 80, 80,
    80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
    80, 80, 80, 80, 80, 80
};

/*
 * 냉수 온도
 * 온도 범위 : 40'C ~ -20'C  / 162 ~ 795
 * 변환 : ADC to Temperture
 */
const U16 Temp_Cold_Debug[] =
{
    795, 785, 774, 763, 752, 741, 729, 717, 705, 693,   // 0 ~ 9
    680, 668, 655, 642, 629, 616, 603, 590, 577, 564,   // 10 ~ 19
    551, 538, 525, 512, 499, 487, 474, 462, 449, 437,   // 20 ~ 29
    425, 413, 401, 390, 378, 367, 356, 346, 335, 325,   // 30 ~ 39
    315, 305, 296, 286, 277, 268, 260, 251, 243, 235,   // 40 ~ 49
    228, 220, 213, 206, 199, 192, 186, 180, 174, 168,   // 50 ~ 59
    162,                                                // 60
};

/*
 * 온수 온도
 * 온도 범위 : -20'C ~ 100'C  / 25ADC ~ 854 ADC
 * 변환 : ADC to Temperture
 */
const U16 Temp_Hot_Debug[] =
{
    25, 26, 28, 29, 31, 33, 35, 37, 39, 41,             // 0 ~ 9
    44, 46, 49, 52, 54, 57, 61, 64, 67, 71,             // 10 ~ 19
    74, 78, 82, 86, 91, 95, 100, 105, 109, 115,         // 20 ~ 29
    120, 126, 131, 137, 143, 149, 156, 163, 169, 176,   // 30 ~ 39
    184, 191, 198, 206, 214, 222, 231, 239, 248, 256,   // 40 ~ 49
    265, 274, 283, 293, 302, 312, 322, 331, 341, 351,   // 50 ~ 59
    361, 371, 382, 392, 402, 413, 423, 433, 444, 454,   // 60 ~ 69
    465, 475, 485, 496, 506, 516, 526, 536, 546, 556,   // 70 ~ 79
    566, 576, 586, 595, 605, 614, 623, 632, 641, 650,   // 80 ~ 89
    659, 668, 676, 684, 693, 701, 708, 716, 724, 731,   // 90 ~ 99
    738, 746, 753, 759, 766, 773, 779, 785, 791, 797,   // 100 ~ 109
    803, 809, 814, 820, 825, 830, 835, 840, 845, 850,   // 110 ~ 119
    854                                                 // 120
};

// 주위온도
const U8 Temp_Amb_Debug[] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  //  0 ~ 9
                            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 10 ~ 19
                            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 20 ~ 29
                            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 30 ~ 39
                            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 40 ~ 49
                            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 50 ~ 59
                            0,  1,  1,  2,  2,  2,  3,  3,  3,  4,  // 60 ~ 69
                            4,  4,  5,  5,  6,  6,  7,  7,  7,  8,  // 70 ~ 79
                            8,  8,  9,  9, 10, 10, 10, 11, 11, 11,  // 80 ~ 89
                           12, 12, 12, 13, 13, 13, 14, 14, 15, 15,  // 90 ~ 99
                           15, 16, 16, 16, 17, 17, 17, 18, 18, 18,  //100 ~ 109
                           19, 19, 19, 20, 20, 20, 21, 21, 21, 22,  //110 ~ 119
                           22, 23, 23, 23, 24, 24, 24, 25, 25, 25,  //120 ~ 129
                           26, 26, 26, 27, 27, 27, 28, 28, 29, 29,  //130 ~ 139
                           29, 30, 30, 30, 31, 31, 32, 32, 32, 33,  //140 ~ 149
                           33, 33, 34, 34, 35, 35, 35, 36, 36, 37,  //150 ~ 159
                           37, 37, 38, 38, 39, 39, 39, 40, 40, 41,  //160 ~ 169
                           41, 42, 42, 43, 43, 43, 44, 44, 45, 45,  //170 ~ 179
                           46, 46, 47, 47, 48, 48, 49, 49, 50, 50,  //180 ~ 189
                           51, 51, 52, 53, 53, 54, 54, 55, 56, 56,  //190 ~ 199
                           57, 57, 58, 59, 59, 60, 61, 62, 62, 63,  //200 ~ 209
                           64, 65, 65, 66, 67, 68, 69, 70, 71, 72,  //210 ~ 219
                           73, 74, 75, 76, 77, 78, 79, 80, 80, 80,  //220 ~ 229
                           80, 80, 80, 80, 80, 80, 80, 80, 80, 80,  //230 ~ 239
                           80, 80, 80, 80, 80, 80, 80, 80, 80, 80,  //240 ~ 249
                           80, 80, 80, 80, 80, 80};                 //250 ~ 255
// 정수온도
const U8 Temp_Room_Debug[] = { 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, // 0 ~ 9
                            60, 60, 60, 60, 60, 60, 60, 60, 60, 60, // 10 ~ 19
                            60, 59, 58, 57, 56, 54, 53, 52, 51, 50, // 20 ~ 29
                            49, 48, 47, 46, 46, 45, 44, 43, 42, 42, // 30 ~ 39
                            41, 40, 40, 39, 38, 38, 37, 36, 36, 35, // 40 ~ 49
                            34, 34, 33, 33, 32, 32, 31, 31, 30, 30, // 50 ~ 59
                            29, 29, 28, 28, 27, 27, 26, 26, 25, 25, // 60 ~ 69
                            24, 24, 23, 23, 22, 22, 22, 21, 21, 20, // 70 ~ 79
                            20, 20, 19, 19, 18, 18, 18, 17, 17, 16, // 80 ~ 89
                            16, 16, 15, 15, 15, 14, 14, 14, 13, 13, // 90 ~ 99
                            12, 12, 12, 11, 11, 11, 10, 10, 10,  9, // 100 ~ 109
                             9,  9,  8,  8,  8,  7,  7,  7,  6,  6, // 110 ~ 119
                             6,  5,  5,  5,  4,  4,  4,  3,  3,  3, // 120 ~ 129
                             2,  2,  2,  1,  1,  1,  0,  0,  0,  0, // 130 ~ 139
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 140 ~ 149
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 150 ~ 159
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 160 ~ 169
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 170 ~ 179
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 180 ~ 189
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 190 ~ 199
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 200 ~ 209
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 210 ~ 219
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 220 ~ 229
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 230 ~ 239
                             0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 240 ~ 249
                             0,  0,  0,  0,  0,  0};                 // 250 ~ 255

extern void debug_get_lcd_rx(void);



extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3



extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error__E45            U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error__E49                       U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error__E21                U32ControlErrorsD.Bit.b4    //E21
#define         Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use         U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Main_Water_Flow_Block_Error__E09               U32ControlErrorsD.Bit.b6    //E09
#define         Bit7_BLDC_Communication_Error__E27                  U32ControlErrorsD.Bit.b7    //E27
#define         Bit8_BLDC_Operation_Error_Current_Sensing__E81      U32ControlErrorsD.Bit.b8    //E81
#define         Bit9_BLDC_Operation_Error_Starting_Fail__E82        U32ControlErrorsD.Bit.b9    //E82
#define         Bit10_BLDC_Operation_Error_Over_Current__E83        U32ControlErrorsD.Bit.b10   //E83
#define         Bit11_BLDC_Operation_Error_Overheat__E84            U32ControlErrorsD.Bit.b11   //E84
#define         Bit12_BLDC_Operation_Error_Disconnection_Comm__E85  U32ControlErrorsD.Bit.b12   //E85
#define         Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86    U32ControlErrorsD.Bit.b13   //E86
#define         Bit14_Cold_Temp_Open_Short_Error__E44               U32ControlErrorsD.Bit.b14   //E44
#define         Bit15_Amb_Temp_Open_Short_Error__E43                U32ControlErrorsD.Bit.b15   //E43
#define         Bit16_Drain_Pump_Error__E60                         U32ControlErrorsD.Bit.b16   //E60
#define         Bit17_Tray_Micro_SW_Dual_Detect_Error__E61          U32ControlErrorsD.Bit.b17   //E61
#define         Bit18_Tray_Micro_SW_Up_Move_Error__E62              U32ControlErrorsD.Bit.b18   //E62
#define         Bit19_Tray_Micro_SW_Down_Move_Error__E63            U32ControlErrorsD.Bit.b19   //E63
#define         Bit20_Mixing_Out_Temp_Open_Short_Error__E52         U32ControlErrorsD.Bit.b20   //E52
#define         Bit21_Amb_Side_Temp_Open_Short_Error__E53           U32ControlErrorsD.Bit.b21   //E53
#define         Bit22_Tray_In_Temp_Open_Short_Error__E41_Not_Use    U32ControlErrorsD.Bit.b22   //E56
#define         Bit23_Water_Tank_1_2_UV_Error__E74                  U32ControlErrorsD.Bit.b23   //E74
#define         Bit24_Ice_Tank_1_2_Back_UV_Error__E75               U32ControlErrorsD.Bit.b24   //E75
#define         Bit25_Ice_Tray_1_2_UV_Error__E76                    U32ControlErrorsD.Bit.b25   //E76
#define         Bit26_Ice_Tank_3_Front_UV_Error__E79                U32ControlErrorsD.Bit.b26   //E79
#define         Bit27_Tds_In_Temp_Open_Short_Error__E90             U32ControlErrorsD.Bit.b27   //E90
#define         Bit28_Tds_Out_Temp_Open_Short_Error__E91            U32ControlErrorsD.Bit.b28   //E91
#define         Bit29_Tds_In_Data_Error__E92                        U32ControlErrorsD.Bit.b29   //E92
#define         Bit30_Tds_Out_Data_Error__E93                       U32ControlErrorsD.Bit.b30   //E93













extern TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                 U8MakeModeB.Bit.b1

extern TYPE_WORD          U16ColdOperationW;
#define            u16ColdOperation                            U16ColdOperationW.word
#define            u8ColdOperation_L                           U16ColdOperationW.byte[0]
#define            u8ColdOperation_H                           U16ColdOperationW.byte[1]
#define            Bit0_Cold_Setting                           U16ColdOperationW.Bit.b0
#define            Bit1_Cold_Low_Water                              U16ColdOperationW.Bit.b1
#define            Bit2_Cold_Temp_Protect                      U16ColdOperationW.Bit.b2
#define            Bit3_Cold_Temp_Control                      U16ColdOperationW.Bit.b3


extern TYPE_WORD          U16IceOperationW;
#define            u16IceOperation                            U16IceOperationW.word
#define            u8IceOperation_L                           U16IceOperationW.byte[0]
#define            u8IceOperation_H                           U16IceOperationW.byte[1]
#define            Bit0_Ice_Setting                           U16IceOperationW.Bit.b0
#define            Bit1_Ice_Low_Water                         U16IceOperationW.Bit.b1
#define            Bit2_Ice_Temp_Protect                      U16IceOperationW.Bit.b2
#define            Bit3_Ice_Full                              U16IceOperationW.Bit.b3
#define            Bit4_Ice_Stop_Six_Hour                     U16IceOperationW.Bit.b4
#define            Bit5_Ice_Init_Ice_Stop                     U16IceOperationW.Bit.b5
#define            Bit6_Ice_Stop_Safty_Routine                U16IceOperationW.Bit.b6
#define            Bit7_Ice_Error                             U16IceOperationW.Bit.b7
#define            Bit8_Clean_Ice_Tank                        U16IceOperationW.Bit.b8
#define            Bit9_Cody_Service_Ice_Off                  U16IceOperationW.Bit.b9
#define            Bit10_Fast_Ice_Make_Limit                  U16IceOperationW.Bit.b10




//extern U8 gu8_room_level;
//extern bit Bit14_Cold_Temp_Open_Short_Error__E44;
//extern bit F_ErrRoomTH;
extern bit F_ErrOVHRoom;
//extern bit F_ErrTrayMotor_Dual;
//extern bit F_ErrTrayMotor_Move;
//extern bit F_ErrOVFeed;
//extern bit F_ErrDrain;
//extern bit F_ErrOVRoomLEV;
//extern bit F_ErrOVLEV;
//extern bit F_ErrRoomLowLEV;
extern bit F_ErrEvaTH;
//extern bit F_ErrAmbTH;
extern bit F_ErrHotTH;
//extern bit F_ErrOVHot;
//extern bit F_ErrColdLEV;
extern bit F_ErrEWDrain;
//extern bit F_ErrBar;


//extern U16 gu16StepMotor1;
extern U16 gu16StepMotor2;
extern U16 gu16_AD_Result_Cold;
extern U16 gu16_AD_Result_Hot_Tank_Temp;
extern U8 gu8AmbTemp;
extern U16 gu16_AD_Result_Eva_First;
extern U16 gu16_AD_Result_Room;

extern U16 gu16CompOffDelay;
extern U8 gu8IceTrayLEV;
//extern bit F_Overflow;
//extern bit F_SelectBar;


extern U16 gu16_AD_Result_Amb;

extern U16 gu16IceHeaterTime;
extern U16 gu16IceMakeTime;
extern bit F_IceInit;
//extern bit F_IceMakeGo;
extern bit F_Safety_Routine;
extern bit F_Ice_Tray_Up_Move_Reset;
extern bit F_Ice_Tray_Down_Move_Reset;
//extern bit F_ColdDIR;
extern bit F_TrayMotorUP;
extern bit F_TrayMotorDOWN;
extern bit F_ice_make_one_more_time;
extern bit bit_tray_pump_output;
extern U8 gu8_Tray_Flow_1sec;
extern U8 gu8_GasSwitch_Status;
extern S16 gs16_sm_info_current;
//extern bit F_Fast_Ice_Make;
extern bit F_Drain_Pump_Output;
extern U8 gu8_Hot_Flow_Rate;
extern U8 gu8_Error_Code;

extern U8 gu8_Hot_Tank_Temperature_One_Degree;
extern U8 gu8_Eva_Cold_Temperature_One_Degree;
extern U8 gu8_Eva_Ice_Temperature_One_Degree;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Cold_Temperature_One_Degree;
extern U8 gu8_Room_Temperature_One_Degree;
extern U8 gu8_Hot_Tank_Temperature_One_Degree;

extern U8 gu8InitStep;
extern ICE_STEP gu8IceStep;

extern bit bit_fast_ice_make;
extern U8 gu8_bldc_target_hz;
extern U8 gu8_bldc_opration_hz;
extern U8 gu8_Mixing_Out_Temperature_One_Degree;
extern U8 gu8_ro_drain_status;
extern U8 gu8_Amb_Temperature_One_Degree;
extern U8 gu8_Amb_Side_Temperature_One_Degree;
extern U8 gu8_Amb_Front_Temperature_One_Degree;
extern U8 gu8_Room_Water_Level;




#endif

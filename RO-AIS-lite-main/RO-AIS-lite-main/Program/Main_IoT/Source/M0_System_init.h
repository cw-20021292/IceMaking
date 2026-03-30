/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SYSTEM_INIT_H_
#define _SYSTEM_INIT_H_


extern void EEPROM_PRIMARY(void);
extern void Pcb_Test_Init_Check(void);
extern void TestUartStart(void);
extern void InitRtc(void);
extern void InitGasSwitch(void);
extern void init_before_save_data(void);
extern void BuzStep(U8 mu8Step);
extern void Delay_MS( U16 ms );
extern void R_TAU0_Channel0_Start(void);
extern void R_TAU0_Channel2_Start(void);
extern void R_TAU0_Channel4_Start(void);
extern void R_TAU1_Channel1_Start(void);
extern void R_TAU1_Channel2_Start(void);
extern void R_UART0_Start(void);
extern void R_UART1_Start(void);
extern void R_UART2_Start(void);
extern void R_UART3_Start(void);
extern void R_INTC7_Start(void);

extern void R_Systeminit(void);

extern void initial_self_data(void);
extern void init_self_test_auto(void);


extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2


extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2






//extern U16 gu16StepMotor1;
extern U16 gu16StepMotor2;
extern U16 gu16IceVVTime;
//extern U16 gu16IceWaterExt;
//extern U16 gu16IceWaterExtMax;
extern U16 gu16CompOffDelay;
extern U16 gu16IniStepDelay;
//extern U16 gu16NoWaterOut;
//extern U16 gu16IceWaterExtDelay;
//extern U8 gu8ErrRTHDelay;
//extern U8 gu8ErrCTHDelay;

//extern U8 gu8ErrHTHDelay;
//extern U8 gu8ErrETHDelay;
//extern U8 gu8ErrATHDelay;
//extern U8 gu8ErrOVCDelay;
//extern U8 gu8ErrOVHDelay;
//extern U8 gu8ErrBar;
extern U8 gu8ErrDoor;
//extern U16 gu16ErrPuriDelay;
//extern U16 gu16ErrOVHRoomTime;
//extern U16 gu16ErrColdLEVDelay;
//extern U16 ucErrOvice_Valve;
extern U16 ucErrOVice_Heater;
extern U16 ucTime_10min_cycle;
extern U16 ucErrOvice_Time;
extern bit F_Safety_Routine;
extern U8 gu8_IceHeaterControl;

//extern bit F_Room;
extern bit F_TrayMotorCW;
extern bit F_TrayMotorCCW;
extern bit F_WaterOut;
extern bit F_IceInit;
extern bit F_IR;
//extern bit F_Hotgas_Time;
//extern U16 Select_Delay;

extern U16 gu16_water_select_return_time;


extern bit F_HotOut;
extern bit F_RoomOut;
extern bit F_ColdOut;

//extern U8 gu8_test_mode_timeout;

//extern bit F_ColdIn;
extern bit F_ColdIce;
//extern U16 gu16TestTime;
extern bit F_FW_Version_Display_Mode;

extern bit F_Front_Tx_Request;
extern bit F_Extract_Led_OnOff;
extern bit F_Cold_Enable;

extern U8 gu8_rtc_time_Y2K;       // 19 or 20
extern U8 gu8_rtc_time_DayWeek;   // 0 ~ 6
extern U8 gu8_rtc_time_Year;      // 0 ~ 99
extern U8 gu8_rtc_time_Month;     // 1 ~ 12
extern U8 gu8_rtc_time_Date;      // 1 ~ 31
extern U8 gu8_rtc_time_Hour;      // 0 ~ 23
extern U8 gu8_rtc_time_Min;       // 0 ~ 59
extern U8 gu8_rtc_time_Sec;       // 0 ~ 59

extern U8 gu8_test_mode_timeout;
extern bit F_Circul_Drain;




extern U8 gu8_wifi_weather;
extern U8 gu8_wifi_aqi;
extern U8 gu8_wifi_temperature;

extern U8 gu8_smart_image;
extern U8 gu8_smart_text;
extern bit F_Circul_Drain;
extern U8 gu8_uart_test_mode;
extern bit bit_first_drain;
extern U8 gu8_durable_test_start;
extern bit bit_fan_first;


extern U8 gu8_total_no_use_timer_hour;
extern bit f_initial_smart_saving;
extern U16 gu16_uart_ir_power_on_ad;
extern U16 gu16_uart_ir_power_off_ad;

extern U8 gu8_fota_start;

extern U16 gu16_water_return_standard_time;
extern bit bit_first_time_setting;

#endif


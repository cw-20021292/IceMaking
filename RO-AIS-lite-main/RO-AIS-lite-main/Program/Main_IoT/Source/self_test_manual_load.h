/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SELF_TEST_MANUAL_COMPONENT_H_
#define _SELF_TEST_MANUAL_COMPONENT_H_

//
extern U16 calculate_dc_current( U16 mu16_ad );
extern U16 calculate_fan_current( U16 mu16_ad );
extern U16 calculate_uv_current( U16 mu16_ad );
extern U16 calculate_pump_current( U16 mu16_ad );



extern void initial_each_self_data( U8 mu8_num );

extern void start_drain_pump( U16 u16_data );
extern void stop_drain_pump( void );
extern void start_tray_pump( U16 u16_data );
extern void stop_tray_pump( void );

extern void run_open_ro_drain(void);
extern void run_close_ro_drain(void);
extern void GasSwitchInit(void);



extern TYPE_SELF_TEST_DATA             SELF_Test_Result_Data;
#define U16_FEED_1_1_DC_Current_PART_0000                        SELF_Test_Result_Data.word[0]
#define U16_NOS_1_2_DC_Current_PART_0001                         SELF_Test_Result_Data.word[1]
#define U16_HOT_OUT_3_3_DC_Current_PART_0002                     SELF_Test_Result_Data.word[2]
#define U16_PURE_OUT_3_2_DC_Current_PART_0003                    SELF_Test_Result_Data.word[3]
#define U16_COLD_OUT_3_1_DC_Current_PART_0004                    SELF_Test_Result_Data.word[4]
#define U16_ICE_TRAY_FLOW_SENSOR_PART_0403                       SELF_Test_Result_Data.word[5]
#define U16_UV_FAUCET_DC_Current_PART_0501						 SELF_Test_Result_Data.word[6]
#define U16_UV_ICE_FAUCET_DC_Current_PART_0502					 SELF_Test_Result_Data.word[7]
#define U16_UV_ICE_TANK_DC_Current_PART_0503            		 SELF_Test_Result_Data.word[8]
#define U16_SWING_BAR_DC_Current_PART_0802                       SELF_Test_Result_Data.word[9]
#define U16_ICE_DOOR_MOTOR_DC_Current_PART_0807                  SELF_Test_Result_Data.word[10]
#define U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808                SELF_Test_Result_Data.word[11]
#define U16_DRAIN_PUMP_DC_Current_PART_080A                      SELF_Test_Result_Data.word[12]
#define U16_ICE_FULL_SENSOR_PART_0801                            SELF_Test_Result_Data.word[13]

extern TYPE_BYTE          U8FrontExtractUVLEDB;
#define            gu8_front_extract_uv_led                    U8FrontExtractUVLEDB.byte
#define            Bit0_Front_Led_UV_Sterilization             U8FrontExtractUVLEDB.Bit.b0
#define            Bit1_Front_Led_Faucet                       U8FrontExtractUVLEDB.Bit.b1
#define            Bit2_Front_Led_Ice_Tank                     U8FrontExtractUVLEDB.Bit.b2
#define            Bit3_Front_Led_Ice_Extract                  U8FrontExtractUVLEDB.Bit.b3
#define            Bit4_Front_Led_Water_Extract                U8FrontExtractUVLEDB.Bit.b4
//#define            Bit5_Front_Led_Icon_All_Lock                U8FrontExtractUVLEDB.Bit.b5
#define            Bit5_Front_Led_Icon_ice_faucet			   U8FrontExtractUVLEDB.Bit.b5
#define            Bit6_Front_Led_Icon_Save                    U8FrontExtractUVLEDB.Bit.b6
#define            Bit7_Front_Led_Icon_Ice_First               U8FrontExtractUVLEDB.Bit.b7




extern U16 gu16_AD_Result_Fan_Current;
extern bit F_IceDoorClose;

extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;
extern U16 gu16_AD_Result_DC_Current_12V;
extern U16 gu16_AD_Result_DC_Current_24V;
extern U16 gu16_AD_Drain_Pump_Current;
extern U16 gu16_AD_Tray_Pump_Current;

extern U8 gu8_Tray_Flow_1sec;
extern U16 gu16ADIceFull;

extern U16 gu16_AD_Result_UV_Faucet_Current;
extern U8 gu8_front_uv_ice_faucet_current;
extern U16 gu16_AD_Result_UV_Ice_Tank_Current;

/*#define DC_CURRENT_STABLE_TIME              10*/
#define DC_CURRENT_STABLE_TIME              45
#define CURRENT_DELAY_TIME                  5


#define SELF_MANUAL_FLOW_TEST_TIME          40


#define HEATER_TEST_PROHIBIT_TEMP           85



extern U16 gu16_AD_Result_DC_Current_24V;




#endif

/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "M3_Led_Output.h"
#include	"uv_ice_extraction_output.h"

void Led_Output(void);
void fnd_output(void);
void extract_uv_led_output(void);
void etc_led_output(void);
void select_led_output(void);
void temp_led_output(void);
void setting_led_output(void);
void time_led_output(void);
void wifi_led_output(void);





TYPE_BYTE          U8FrontThousandB;
#define            gu8_front_fnd_thousand                      U8FrontThousandB.byte
#define            Bit0_Front_Fnd_Thousand_1                   U8FrontThousandB.Bit.b0
#define            Bit1_Front_Fnd_Thousand_2                   U8FrontThousandB.Bit.b1

TYPE_BYTE          U8FrontHundredB;
#define            gu8_front_fnd_hundred                       U8FrontHundredB.byte
#define            Bit0_Front_Fnd_Hundred_1                    U8FrontHundredB.Bit.b0
#define            Bit1_Front_Fnd_Hundred_2                    U8FrontHundredB.Bit.b1
#define            Bit2_Front_Fnd_Hundred_3                    U8FrontHundredB.Bit.b2
#define            Bit3_Front_Fnd_Hundred_4                    U8FrontHundredB.Bit.b3
#define            Bit4_Front_Fnd_Hundred_5                    U8FrontHundredB.Bit.b4
#define            Bit5_Front_Fnd_Hundred_6                    U8FrontHundredB.Bit.b5
#define            Bit6_Front_Fnd_Hundred_7                    U8FrontHundredB.Bit.b6

TYPE_BYTE          U8FrontTenB;
#define            gu8_front_fnd_ten                           U8FrontTenB.byte
#define            Bit0_Front_Fnd_Ten_1                        U8FrontTenB.Bit.b0
#define            Bit1_Front_Fnd_Ten_2                        U8FrontTenB.Bit.b1
#define            Bit2_Front_Fnd_Ten_3                        U8FrontTenB.Bit.b2
#define            Bit3_Front_Fnd_Ten_4                        U8FrontTenB.Bit.b3
#define            Bit4_Front_Fnd_Ten_5                        U8FrontTenB.Bit.b4
#define            Bit5_Front_Fnd_Ten_6                        U8FrontTenB.Bit.b5
#define            Bit6_Front_Fnd_Ten_7                        U8FrontTenB.Bit.b6

TYPE_BYTE          U8FrontOneB;
#define            gu8_front_fnd_one                           U8FrontOneB.byte
#define            Bit0_Front_Fnd_One_1                        U8FrontOneB.Bit.b0
#define            Bit1_Front_Fnd_One_2                        U8FrontOneB.Bit.b1
#define            Bit2_Front_Fnd_One_3                        U8FrontOneB.Bit.b2
#define            Bit3_Front_Fnd_One_4                        U8FrontOneB.Bit.b3
#define            Bit4_Front_Fnd_One_5                        U8FrontOneB.Bit.b4
#define            Bit5_Front_Fnd_One_6                        U8FrontOneB.Bit.b5
#define            Bit6_Front_Fnd_One_7                        U8FrontOneB.Bit.b6

TYPE_BYTE          U8FrontExtractUVLEDB;
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



TYPE_BYTE          U8FrontETCLEDB;
#define            gu8_front_etc_led                           U8FrontETCLEDB.byte
#define            Bit0_Front_Led_Cont                         U8FrontETCLEDB.Bit.b0
#define            Bit1_Front_Led_Pot                          U8FrontETCLEDB.Bit.b1
#define            Bit2_Front_Led_2_Cups                       U8FrontETCLEDB.Bit.b2
#define            Bit3_Front_Led_1_Cup                        U8FrontETCLEDB.Bit.b3
#define            Bit4_Front_Led_ml                           U8FrontETCLEDB.Bit.b4
#define            Bit5_Front_Led_Percent                      U8FrontETCLEDB.Bit.b5
//#define            Bit6_Front_Led_Auto_Drain                   U8FrontETCLEDB.Bit.b6
#define            Bit6_Front_Led_half_Cup					   U8FrontETCLEDB.Bit.b6 // Revised
#define            Bit7_Front_Led_Low_Water                    U8FrontETCLEDB.Bit.b7

TYPE_BYTE          U8FrontSelectLEDB;
#define            gu8_front_select_led                        U8FrontSelectLEDB.byte
#define            Bit0_Front_Led_Set_Select                   U8FrontSelectLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Select                   U8FrontSelectLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Select                   U8FrontSelectLEDB.Bit.b2
#define            Bit3_Front_Led_Ambient_Select               U8FrontSelectLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Select                  U8FrontSelectLEDB.Bit.b4
#define            Bit5_Front_Led_Amount_Select                U8FrontSelectLEDB.Bit.b5
#define            Bit6_Front_Led_Icon_Ice_Lock                U8FrontSelectLEDB.Bit.b6
#define            Bit7_Front_Led_Icon_Hot_Lock                U8FrontSelectLEDB.Bit.b7

TYPE_BYTE          U8FrontTempLEDB;
#define            gu8_front_temp_led                          U8FrontTempLEDB.byte
#define            Bit0_Front_Led_Hot_Temp_1                   U8FrontTempLEDB.Bit.b0
#define            Bit1_Front_Led_Hot_Temp_2                   U8FrontTempLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Temp_3                   U8FrontTempLEDB.Bit.b2
#define            Bit3_Front_Led_Cold_Temp_1                  U8FrontTempLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp_2                  U8FrontTempLEDB.Bit.b4
#define            Bit5_Front_Led_Cold_Temp_3                  U8FrontTempLEDB.Bit.b5
#define            Bit5_Front_Led_Ice_Full                     U8FrontTempLEDB.Bit.b6

TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Lock                     U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Eco_Mode                     U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp                    U8FrontSettingLEDB.Bit.b4
#define            Bit5_Front_Led_My_Cup                       U8FrontSettingLEDB.Bit.b5

//revised
TYPE_BYTE          U8TimeNWifiSettingLEDB;
#define            gu8_time_wifi_setting_led				   U8TimeNWifiSettingLEDB.byte
#define            Bit0_Time_Led_AM							   U8TimeNWifiSettingLEDB.Bit.b0
#define            Bit1_Time_Led_PM							   U8TimeNWifiSettingLEDB.Bit.b1
#define            Bit2_Time_Led_Colon						   U8TimeNWifiSettingLEDB.Bit.b2
#define            Bit3_Led_Wifi_Icon_White					   U8TimeNWifiSettingLEDB.Bit.b3
#define            Bit4_Led_Wifi_Icon_Blue					   U8TimeNWifiSettingLEDB.Bit.b4



TYPE_DIMMING       U8DimmingNo1;
#define            gu8_dimming_set_ice_first                   U8DimmingNo1.byte
#define            bit_0_3_dimming_set_select                  U8DimmingNo1.nibble.b0_3
#define            bit_4_7_dimming_ice_select                  U8DimmingNo1.nibble.b4_7

TYPE_DIMMING       U8DimmingNo2;
#define            gu8_dimming_hot_ambient                     U8DimmingNo2.byte
#define            bit_0_3_dimming_hot_select                  U8DimmingNo2.nibble.b0_3
#define            bit_4_7_dimming_ambient_select              U8DimmingNo2.nibble.b4_7

TYPE_DIMMING       U8DimmingNo3;
#define            gu8_dimming_cold_amount                     U8DimmingNo3.byte
#define            bit_0_3_dimming_cold_select                 U8DimmingNo3.nibble.b0_3
#define            bit_4_7_dimming_amount_select               U8DimmingNo3.nibble.b4_7

TYPE_DIMMING       U8DimmingNo4;
#define            gu8_dimming_extract                         U8DimmingNo4.byte
#define            bit_0_3_dimming_ice_extract                 U8DimmingNo4.nibble.b0_3
#define            bit_4_7_dimming_water_extract               U8DimmingNo4.nibble.b4_7

TYPE_DIMMING       U8DimmingNo5;
#define            gu8_dimming_setting_etc                     U8DimmingNo5.byte
#define            bit_0_3_dimming_setting_menu                U8DimmingNo5.nibble.b0_3
#define            bit_4_7_dimming_etc_icon                    U8DimmingNo5.nibble.b4_7


TYPE_DIMMING       U8DimmingNo6;
#define            gu8_dimming_temp                            U8DimmingNo6.byte
#define            bit_0_3_dimming_hot_temp                    U8DimmingNo6.nibble.b0_3
#define            bit_4_7_dimming_cold_temp                   U8DimmingNo6.nibble.b4_7

TYPE_DIMMING       U8DimmingNo7;
#define            gu8_dimming_cont_pot                        U8DimmingNo7.byte
#define            bit_0_3_dimming_cont                        U8DimmingNo7.nibble.b0_3
#define            bit_4_7_dimming_pot                         U8DimmingNo7.nibble.b4_7

TYPE_DIMMING       U8DimmingNo8;
#define            gu8_dimming_2cups_1cup                      U8DimmingNo8.byte
#define            bit_0_3_dimming_2cups                       U8DimmingNo8.nibble.b0_3
#define            bit_4_7_dimming_1cup                        U8DimmingNo8.nibble.b4_7

TYPE_DIMMING       U8DimmingNo9;
#define            gu8_dimming_half_cups_colon					U8DimmingNo9.byte
#define            bit_0_3_dimming_half_cup						U8DimmingNo9.nibble.b0_3
#define            bit_4_7_dimming_colon						U8DimmingNo9.nibble.b4_7

TYPE_DIMMING       U8DimmingNo10;
#define            gu8_dimming_Am_Pm							U8DimmingNo10.byte
#define            bit_0_3_dimming_Am							U8DimmingNo10.nibble.b0_3
#define            bit_4_7_dimming_Pm							U8DimmingNo10.nibble.b4_7

TYPE_DIMMING       U8DimmingNo11;
#define            gu8_dimming_Wifi								U8DimmingNo11.byte
#define            bit_0_3_dimming_White						U8DimmingNo10.nibble.b0_3
//#define            bit_4_7_dimming_Blue							U8DimmingNo10.nibble.b4_7

TYPE_DIMMING       U8DimmingNo12;
#define            gu8_dimming_fnd_2_1							U8DimmingNo12.byte
#define            bit_0_3_fnd_0_0_0_1							U8DimmingNo12.nibble.b0_3
#define            bit_4_7_fnd_0_0_2_0							U8DimmingNo12.nibble.b4_7

TYPE_DIMMING       U8DimmingNo13;
#define            gu8_dimming_fnd_4_3							U8DimmingNo13.byte
#define            bit_0_3_fnd_0_3_0_0							U8DimmingNo13.nibble.b0_3
#define            bit_4_7_fnd_4_0_0_0							U8DimmingNo13.nibble.b4_7


TYPE_WORD          U16ETCDimmingSelW;
#define            u16ETCDimmingSel                            U16ETCDimmingSelW.word
#define            u8ETCDimmingSel_L                           U16ETCDimmingSelW.byte[0]
#define            u8ETCDimmingSel_H                           U16ETCDimmingSelW.byte[1]
#define            Bit0_Hot_Temp_1_2_3_Dimming_State           U16ETCDimmingSelW.Bit.b0
#define            Bit1_Cold_Temp_1_2_3_Dimming_State          U16ETCDimmingSelW.Bit.b1
#define            Bit2_UV_Care_Dimming_State                  U16ETCDimmingSelW.Bit.b2
#define            Bit3_Faucet_Dimming_State                   U16ETCDimmingSelW.Bit.b3
#define            Bit4_Ice_Tank_Dimming_State                 U16ETCDimmingSelW.Bit.b4
#define            Bit5_ml_Dimming_State                       U16ETCDimmingSelW.Bit.b5
#define            Bit6_Percent_Dimming_State                  U16ETCDimmingSelW.Bit.b6
#define            Bit7_Auto_Drain_Dimming_State               U16ETCDimmingSelW.Bit.b7
#define            Bit8_Low_Water_Dimming_State                U16ETCDimmingSelW.Bit.b8
#define            Bit9_Icon_Ice_Lock_Dimming_State            U16ETCDimmingSelW.Bit.b9
#define            Bit10_Icon_Hot_Lock_Dimming_State           U16ETCDimmingSelW.Bit.b10
#define            Bit11_Icon_All_Lock_Dimming_State           U16ETCDimmingSelW.Bit.b11
#define            Bit12_Icon_Save_Dimming_State               U16ETCDimmingSelW.Bit.b12
#define            Bit13_Ice_First_Dimming_State               U16ETCDimmingSelW.Bit.b13
#define            Bit14_Ice_Full_Dimming_State                U16ETCDimmingSelW.Bit.b14
#define            Bit15_Ice_faucet_Dimming_State              U16ETCDimmingSelW.Bit.b15

TYPE_BYTE          U8FNDDimmingselB;
#define            gu8_Dimming_seg							   U8FNDDimmingselB.byte
#define            Bit0_Seg_0_0_0_1_state					   U8FNDDimmingselB.Bit.b0
#define            Bit1_Seg_0_0_2_0_state					   U8FNDDimmingselB.Bit.b1
#define            Bit2_Seg_0_3_0_0_state					   U8FNDDimmingselB.Bit.b2
#define            Bit3_Seg_4_0_0_0_state					   U8FNDDimmingselB.Bit.b3



U8 gu8_etc_1;
U8 gu8_etc_2;



U8 gu8_hot_led_dimming;
U8 gu8_hot_lock_dimming;
U8 gu8_room_dimming;
U8 gu8_cold_dimming;
U8 gu8_cup_dimming;
U8 gu8_extract_dimming;
U8 gu8_welcome_dimming;
U8 gu8_etc;



U8 gu8_RGB_Control_PWM_Count;
U8 gu8_Red_On_Time;
U8 gu8_Green_On_Time;
U8 gu8_Blue_On_Time;

U8 gu8_led_dimming;
U8 gu8_ext_led_dimming_percent;

U8 gu8_selected_led_dimming;
U8 gu8_unselected_led_dimming;

U8 gu8_ota_start;
U16 gu16_ota_timer;

/*..hui [23-2-10오후 2:39:54] 회로 확정되면 변경..*/
//U8 pLED_ICON_ALL_LOCK;
//U8 pLED_ICON_SAVE;
//U8 pLED_ICON_ICE_FIRST;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Led_Output(void)
{
    gu8_led_dimming++;

    if(gu8_led_dimming > 10)
    {
        gu8_led_dimming = 1;
    }
    else{}

	/*.. sean [24-11-20] ice extraction uv on/off ..*/
	//output_ice_extraction_uv();
	
    fnd_output();
    extract_uv_led_output();
    etc_led_output();
    select_led_output();
    temp_led_output();
    setting_led_output();
	time_led_output();
	wifi_led_output();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_output(void)
{
#if 0
    pFND_SEG_2_1_B = Bit0_Front_Fnd_Thousand_1;
    pFND_SEG_2_1_C =  Bit1_Front_Fnd_Thousand_2;

    pFND_SEG_1_1_A = Bit0_Front_Fnd_Hundred_1;
    pFND_SEG_1_1_B = Bit1_Front_Fnd_Hundred_2;
    pFND_SEG_1_1_C = Bit2_Front_Fnd_Hundred_3;
    pFND_SEG_1_1_D = Bit3_Front_Fnd_Hundred_4;
    pFND_SEG_1_1_E = Bit4_Front_Fnd_Hundred_5;
    pFND_SEG_1_1_F = Bit5_Front_Fnd_Hundred_6;
    pFND_SEG_1_1_G = Bit6_Front_Fnd_Hundred_7;

    pFND_SEG_1_2_A = Bit0_Front_Fnd_Ten_1;
    pFND_SEG_1_2_B = Bit1_Front_Fnd_Ten_2;
    pFND_SEG_1_2_C = Bit2_Front_Fnd_Ten_3;
    pFND_SEG_1_2_D = Bit3_Front_Fnd_Ten_4;
    pFND_SEG_1_2_E = Bit4_Front_Fnd_Ten_5;
    pFND_SEG_1_2_F = Bit5_Front_Fnd_Ten_6;
    pFND_SEG_1_2_G = Bit6_Front_Fnd_Ten_7;

    pFND_SEG_1_3_A = Bit0_Front_Fnd_One_1;
    pFND_SEG_1_3_B = Bit1_Front_Fnd_One_2;
    pFND_SEG_1_3_C = Bit2_Front_Fnd_One_3;
    pFND_SEG_1_3_D = Bit3_Front_Fnd_One_4;
    pFND_SEG_1_3_E = Bit4_Front_Fnd_One_5;
    pFND_SEG_1_3_F = Bit5_Front_Fnd_One_6;
    pFND_SEG_1_3_G = Bit6_Front_Fnd_One_7;
#endif
	if(gu8_front_fnd_thousand > 0)
	{
		if(Bit3_Seg_4_0_0_0_state = SET)
		{
			if(gu8_led_dimming <= bit_4_7_fnd_4_0_0_0)
			{
				pFND_SEG_2_1_B = Bit0_Front_Fnd_Thousand_1;
				pFND_SEG_2_1_C =  Bit1_Front_Fnd_Thousand_2;				
			}
			else
			{
				pFND_SEG_2_1_B = CLEAR;
				pFND_SEG_2_1_C =  CLEAR;				
			}
		}
		else
		{
			pFND_SEG_2_1_B = CLEAR;
			pFND_SEG_2_1_C =  CLEAR;				
		}
	}
	else
	{
		pFND_SEG_2_1_B = CLEAR;
		pFND_SEG_2_1_C =  CLEAR;				
	}
	
	if(gu8_front_fnd_hundred > 0)
	{
		if(Bit2_Seg_0_3_0_0_state = SET)
		{
			if(gu8_led_dimming <= bit_0_3_fnd_0_3_0_0)
			{
			    pFND_SEG_1_1_A = Bit0_Front_Fnd_Hundred_1;
			    pFND_SEG_1_1_B = Bit1_Front_Fnd_Hundred_2;
			    pFND_SEG_1_1_C = Bit2_Front_Fnd_Hundred_3;
			    pFND_SEG_1_1_D = Bit3_Front_Fnd_Hundred_4;
			    pFND_SEG_1_1_E = Bit4_Front_Fnd_Hundred_5;
			    pFND_SEG_1_1_F = Bit5_Front_Fnd_Hundred_6;
			    pFND_SEG_1_1_G = Bit6_Front_Fnd_Hundred_7;			
			}
			else
			{
			    pFND_SEG_1_1_A = CLEAR;
			    pFND_SEG_1_1_B = CLEAR;
			    pFND_SEG_1_1_C = CLEAR;
			    pFND_SEG_1_1_D = CLEAR;
			    pFND_SEG_1_1_E = CLEAR;
			    pFND_SEG_1_1_F = CLEAR;
			    pFND_SEG_1_1_G = CLEAR;						
			}
		}
		else
		{
		    pFND_SEG_1_1_A = CLEAR;
		    pFND_SEG_1_1_B = CLEAR;
		    pFND_SEG_1_1_C = CLEAR;
		    pFND_SEG_1_1_D = CLEAR;
		    pFND_SEG_1_1_E = CLEAR;
		    pFND_SEG_1_1_F = CLEAR;
		    pFND_SEG_1_1_G = CLEAR;						
		}
	}
	else
	{
	    pFND_SEG_1_1_A = CLEAR;
	    pFND_SEG_1_1_B = CLEAR;
	    pFND_SEG_1_1_C = CLEAR;
	    pFND_SEG_1_1_D = CLEAR;
	    pFND_SEG_1_1_E = CLEAR;
	    pFND_SEG_1_1_F = CLEAR;
	    pFND_SEG_1_1_G = CLEAR;					
	}
	
	if(gu8_front_fnd_ten > 0)
	{
		if(Bit1_Seg_0_0_2_0_state = SET)
		{
			if(gu8_led_dimming <= bit_0_3_fnd_0_3_0_0)
			{
			    pFND_SEG_1_2_A = Bit0_Front_Fnd_Ten_1;
			    pFND_SEG_1_2_B = Bit1_Front_Fnd_Ten_2;
			    pFND_SEG_1_2_C = Bit2_Front_Fnd_Ten_3;
			    pFND_SEG_1_2_D = Bit3_Front_Fnd_Ten_4;
			    pFND_SEG_1_2_E = Bit4_Front_Fnd_Ten_5;
			    pFND_SEG_1_2_F = Bit5_Front_Fnd_Ten_6;
			    pFND_SEG_1_2_G = Bit6_Front_Fnd_Ten_7;		
			}
			else
			{
			    pFND_SEG_1_2_A = CLEAR;
			    pFND_SEG_1_2_B = CLEAR;
			    pFND_SEG_1_2_C = CLEAR;
			    pFND_SEG_1_2_D = CLEAR;
			    pFND_SEG_1_2_E = CLEAR;
			    pFND_SEG_1_2_F = CLEAR;
			    pFND_SEG_1_2_G = CLEAR;					
			}
		}
		else
		{
		    pFND_SEG_1_2_A = CLEAR;
		    pFND_SEG_1_2_B = CLEAR;
		    pFND_SEG_1_2_C = CLEAR;
		    pFND_SEG_1_2_D = CLEAR;
		    pFND_SEG_1_2_E = CLEAR;
		    pFND_SEG_1_2_F = CLEAR;
		    pFND_SEG_1_2_G = CLEAR;						
		}
	}
	else
	{
	    pFND_SEG_1_2_A = CLEAR;
	    pFND_SEG_1_2_B = CLEAR;
	    pFND_SEG_1_2_C = CLEAR;
	    pFND_SEG_1_2_D = CLEAR;
	    pFND_SEG_1_2_E = CLEAR;
	    pFND_SEG_1_2_F = CLEAR;
	    pFND_SEG_1_2_G = CLEAR;					
	}
	
	if(gu8_front_fnd_one > 0)
	{
		if(Bit2_Seg_0_3_0_0_state = SET)
		{
			if(gu8_led_dimming <= bit_0_3_fnd_0_3_0_0)
			{
			    pFND_SEG_1_3_A = Bit0_Front_Fnd_One_1;
			    pFND_SEG_1_3_B = Bit1_Front_Fnd_One_2;
			    pFND_SEG_1_3_C = Bit2_Front_Fnd_One_3;
			    pFND_SEG_1_3_D = Bit3_Front_Fnd_One_4;
			    pFND_SEG_1_3_E = Bit4_Front_Fnd_One_5;
			    pFND_SEG_1_3_F = Bit5_Front_Fnd_One_6;
			    pFND_SEG_1_3_G = Bit6_Front_Fnd_One_7;		
			}
			else
			{
			    pFND_SEG_1_3_A = CLEAR;
			    pFND_SEG_1_3_B = CLEAR;
			    pFND_SEG_1_3_C = CLEAR;
			    pFND_SEG_1_3_D = CLEAR;
			    pFND_SEG_1_3_E = CLEAR;
			    pFND_SEG_1_3_F = CLEAR;
			    pFND_SEG_1_3_G = CLEAR;					
			}
		}
		else
		{
		    pFND_SEG_1_3_A = CLEAR;
		    pFND_SEG_1_3_B = CLEAR;
		    pFND_SEG_1_3_C = CLEAR;
		    pFND_SEG_1_3_D = CLEAR;
		    pFND_SEG_1_3_E = CLEAR;
		    pFND_SEG_1_3_F = CLEAR;
		    pFND_SEG_1_3_G = CLEAR;					
		}
	}
	else
	{
	    pFND_SEG_1_3_A = CLEAR;
	    pFND_SEG_1_3_B = CLEAR;
	    pFND_SEG_1_3_C = CLEAR;
	    pFND_SEG_1_3_D = CLEAR;
	    pFND_SEG_1_3_E = CLEAR;
	    pFND_SEG_1_3_F = CLEAR;
	    pFND_SEG_1_3_G = CLEAR;					
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void extract_uv_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:30:56] UV Sterilization LED..*/
    if( Bit0_Front_Led_UV_Sterilization == SET )
    {
        if( Bit2_UV_Care_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_UV_STERILIZATION = Bit0_Front_Led_UV_Sterilization;
            }
            else
            {
                pLED_UV_STERILIZATION = CLEAR;
            }
        }
        else
        {
            pLED_UV_STERILIZATION = SET;
        }
    }
    else
    {
        pLED_UV_STERILIZATION = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:02] Faucet LED..*/
    if( Bit1_Front_Led_Faucet == SET )
    {
        if( Bit3_Faucet_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_FAUCET_STERILIZION = Bit1_Front_Led_Faucet;
            }
            else
            {
                pLED_FAUCET_STERILIZION = CLEAR;
            }
        }
        else
        {
            pLED_FAUCET_STERILIZION = SET;
        }
    }
    else
    {
        pLED_FAUCET_STERILIZION = CLEAR;
    }
	
	///////////////////////////////////////////////////////////////////////////////////
/*..hui [23-2-2오후 5:31:02] ice Faucet LED..*/
    if( Bit5_Front_Led_Icon_ice_faucet == SET )
    {
        if( Bit15_Ice_faucet_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                //pLED_UV_STERILIZATION = Bit5_Front_Led_Icon_ice_faucet;
		        pLED_UV_ICE_FAUCET = SET;                  /*on*/
		        pUV_ON_OFF = SET;
            }
            else
            {
                //pLED_UV_STERILIZATION = CLEAR;
		        pLED_UV_ICE_FAUCET = CLEAR;                  /*off*/
		        pUV_ON_OFF = CLEAR;
            }
        }
        else
        {
            //pLED_UV_STERILIZATION = SET;
	        pLED_UV_ICE_FAUCET = SET;                  /*off*/
	        pUV_ON_OFF = SET;
        }
    }
    else
    {
        //pLED_UV_STERILIZATION = CLEAR;
        pLED_UV_ICE_FAUCET = CLEAR;                  /*off*/
        pUV_ON_OFF = CLEAR;
    }
////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:10] Ice Tank LED..*/
    if( Bit2_Front_Led_Ice_Tank == SET )
    {
        if( Bit4_Ice_Tank_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICE_TANK_STERILIZION = Bit2_Front_Led_Ice_Tank;
            }
            else
            {
                pLED_ICE_TANK_STERILIZION = CLEAR;
            }
        }
        else
        {
            pLED_ICE_TANK_STERILIZION = SET;
        }
    }
    else
    {
        pLED_ICE_TANK_STERILIZION = CLEAR;
    }
	
	/*..hui [23-2-2오후 5:31:10] Ice extraction UV LED..*/
		if( Bit2_Front_Led_Ice_Tank == SET )
		{
			if( Bit4_Ice_Tank_Dimming_State == SET )
			{
				if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
				{
					pLED_ICE_TANK_STERILIZION = Bit2_Front_Led_Ice_Tank;
				}
				else
				{
					pLED_ICE_TANK_STERILIZION = CLEAR;
				}
			}
			else
			{
				pLED_ICE_TANK_STERILIZION = SET;
			}
		}
		else
		{
			pLED_ICE_TANK_STERILIZION = CLEAR;
		}

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:16] 얼음 추출 LED..*/
    if( Bit3_Front_Led_Ice_Extract == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_ice_extract)
        {
            pLED_ICE_EXTRACT_1 = Bit3_Front_Led_Ice_Extract;
            //pLED_ICE_EXTRACT_2 = Bit3_Front_Led_Ice_Extract;
        }
        else
        {
            pLED_ICE_EXTRACT_1 = CLEAR;
            //pLED_ICE_EXTRACT_2 = CLEAR;
        }
    }
    else
    {
        pLED_ICE_EXTRACT_1 = CLEAR;
        //pLED_ICE_EXTRACT_2 = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:23] 물 추출 LED..*/
    if( Bit4_Front_Led_Water_Extract == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_water_extract)
        {
            pLED_WATER_EXTRACT_1 = Bit4_Front_Led_Water_Extract;
            //pLED_WATER_EXTRACT_2 = Bit4_Front_Led_Water_Extract;
        }
        else
        {
            pLED_WATER_EXTRACT_1 = CLEAR;
            //pLED_WATER_EXTRACT_2 = CLEAR;
        }
    }
    else
    {
        pLED_WATER_EXTRACT_1 = CLEAR;
        //pLED_WATER_EXTRACT_2 = CLEAR;
    }


    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-10오후 2:37:30] 절전 아이콘 추가..*/
    if( Bit6_Front_Led_Icon_Save == SET )
    {
        if( Bit12_Icon_Save_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICON_SAVE = Bit6_Front_Led_Icon_Save;
            }
            else
            {
                pLED_ICON_SAVE = CLEAR;
            }
        }
        else
        {
            pLED_ICON_SAVE = SET;
        }
    }
    else
    {
        pLED_ICON_SAVE = CLEAR;
    }


    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-10오후 2:37:38] 얼음우선 아이콘 추가..*/
    if( Bit7_Front_Led_Icon_Ice_First == SET )
    {
        if( Bit13_Ice_First_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICON_ICE_FIRST = Bit7_Front_Led_Icon_Ice_First;
            }
            else
            {
                pLED_ICON_ICE_FIRST = CLEAR;
            }
        }
        else
        {
            pLED_ICON_ICE_FIRST = SET;
        }
    }
    else
    {
        pLED_ICON_ICE_FIRST = CLEAR;
    }


    ////////////////////////////////////////////////////////////////////////////////////















}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void etc_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:29] Cont LED..*/
    if( Bit0_Front_Led_Cont == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_cont)
        {
            pLED_CONT = Bit0_Front_Led_Cont;
        }
        else
        {
            pLED_CONT = CLEAR;
        }
    }
    else
    {
        pLED_CONT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:34] Pot LED..*/
    if( Bit1_Front_Led_Pot == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_pot)
        {
            pLED_POT = Bit1_Front_Led_Pot;
        }
        else
        {
            pLED_POT = CLEAR;
        }
    }
    else
    {
        pLED_POT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:43] 2Cups LED..*/
    if( Bit2_Front_Led_2_Cups == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_2cups)
        {
            pLED_2_CUP = Bit2_Front_Led_2_Cups;
        }
        else
        {
            pLED_2_CUP = CLEAR;
        }
    }
    else
    {
        pLED_2_CUP = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:49] 1Cup LED..*/
    if( Bit3_Front_Led_1_Cup == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_1cup)
        {
            pLED_1_CUP = Bit3_Front_Led_1_Cup;
        }
        else
        {
            pLED_1_CUP = CLEAR;
        }
    }
    else
    {
        pLED_1_CUP = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:31:49] half Cup LED..*/
    if( Bit6_Front_Led_half_Cup == SET )
    {
    
        if(gu8_led_dimming <= bit_0_3_dimming_half_cup)
        {
            pLED_HALF_CUP = Bit6_Front_Led_half_Cup;
        }
        else
        {
            pLED_HALF_CUP = CLEAR;
        }
    
    }
    else
    {
        pLED_HALF_CUP = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:07] ml LED..*/
    if( Bit4_Front_Led_ml == SET )
    {
        if( Bit5_ml_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_mL = Bit4_Front_Led_ml;
            }
            else
            {
                pLED_mL = CLEAR;
            }
        }
        else
        {
            pLED_mL = SET;
        }
    }
    else
    {
        pLED_mL = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:13] Percent LED..*/
    if( Bit5_Front_Led_Percent == SET )
    {
        if( Bit6_Percent_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_PERCENT = Bit5_Front_Led_Percent;
            }
            else
            {
                pLED_PERCENT = CLEAR;
            }
        }
        else
        {
            pLED_PERCENT = SET;
        }
    }
    else
    {
        pLED_PERCENT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:19] Auto Drain LED..*/
#if 0
    if( Bit6_Front_Led_Auto_Drain == SET )
    {
        if( Bit7_Auto_Drain_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_AUTO_DRAIN_OPERATION = Bit6_Front_Led_Auto_Drain;
            }
            else
            {
                pLED_AUTO_DRAIN_OPERATION = CLEAR;
            }
        }
        else
        {
            pLED_AUTO_DRAIN_OPERATION = SET;
        }
    }
    else
    {
        pLED_AUTO_DRAIN_OPERATION = CLEAR;
    }
#endif
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:26] Low Water LED..*/
    if( Bit7_Front_Led_Low_Water == SET )
    {
        if( Bit8_Low_Water_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_LOW_WATER = Bit7_Front_Led_Low_Water;
            }
            else
            {
                pLED_LOW_WATER = CLEAR;
            }
        }
        else
        {
            pLED_LOW_WATER = SET;
        }
    }
    else
    {
        pLED_LOW_WATER = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void select_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:33] Set 선택 LED..*/
    if( Bit0_Front_Led_Set_Select == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_set_select)
        {
            pLED_SETTING_START = Bit0_Front_Led_Set_Select;
        }
        else
        {
            pLED_SETTING_START = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_START = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:42] Ice First 선택 LED..*/
    if( Bit1_Front_Led_Ice_Select == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_ice_select)
        {
            pLED_ICE = Bit1_Front_Led_Ice_Select;
        }
        else
        {
            pLED_ICE = CLEAR;
        }
    }
    else
    {
        pLED_ICE = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:49] Hot 선택 LED..*/
    if( Bit2_Front_Led_Hot_Select == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_hot_select)
        {
            pLED_HOT = Bit2_Front_Led_Hot_Select;
        }
        else
        {
            pLED_HOT = CLEAR;
        }
    }
    else
    {
        pLED_HOT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:32:57] Ambient 선택 LED..*/
    if( Bit3_Front_Led_Ambient_Select == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_ambient_select)
        {
            pLED_AMBIENT = Bit3_Front_Led_Ambient_Select;
        }
        else
        {
            pLED_AMBIENT = CLEAR;
        }
    }
    else
    {
        pLED_AMBIENT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:03] Cold 선택 LED..*/
    if( Bit4_Front_Led_Cold_Select == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_cold_select)
        {
            pLED_COLD = Bit4_Front_Led_Cold_Select;
        }
        else
        {
            pLED_COLD = CLEAR;
        }
    }
    else
    {
        pLED_COLD = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:11] Amount 선택 LED..*/
    if( Bit5_Front_Led_Amount_Select == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_amount_select)
        {
            pLED_AMOUNT = Bit5_Front_Led_Amount_Select;
        }
        else
        {
            pLED_AMOUNT = CLEAR;
        }
    }
    else
    {
        pLED_AMOUNT = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:19] 얼음 잠금 아이콘 LED..*/
    if( Bit6_Front_Led_Icon_Ice_Lock == SET )
    {
        if( Bit9_Icon_Ice_Lock_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICON_ICE_LOCK = Bit6_Front_Led_Icon_Ice_Lock;
            }
            else
            {
                pLED_ICON_ICE_LOCK = CLEAR;
            }
        }
        else
        {
            pLED_ICON_ICE_LOCK = SET;
        }
    }
    else
    {
        pLED_ICON_ICE_LOCK = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:26] 온수 잠금 아이콘 LED..*/
    if( Bit7_Front_Led_Icon_Hot_Lock == SET )
    {
        if( Bit10_Icon_Hot_Lock_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICON_HOT_LOCK = Bit7_Front_Led_Icon_Hot_Lock;
            }
            else
            {
                pLED_ICON_HOT_LOCK = CLEAR;
            }
        }
        else
        {
            pLED_ICON_HOT_LOCK = SET;
        }
    }
    else
    {
        pLED_ICON_HOT_LOCK = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void temp_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:36] 온수 온도 1 LED..*/
    #if 0
    if( Bit0_Front_Led_Hot_Temp_1 == SET )
    {
        /*if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)*/
        if( Bit0_Hot_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
            {
                pLED_HOT_TEMP_1 = Bit0_Front_Led_Hot_Temp_1;
            }
            else
            {
                pLED_HOT_TEMP_1 = CLEAR;
            }
        }
        else
        {
            pLED_HOT_TEMP_1 = SET;
        }
    }
    else
    {
        pLED_HOT_TEMP_1 = CLEAR;
    }
    #endif

    if( Bit0_Front_Led_Hot_Temp_1 == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
        {
            pLED_HOT_TEMP_1 = Bit0_Front_Led_Hot_Temp_1;
        }
        else
        {
            pLED_HOT_TEMP_1 = CLEAR;
        }
    }
    else
    {
        pLED_HOT_TEMP_1 = CLEAR;
    }



    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:43] 온수 온도2 LED..*/
    #if 0
    if( Bit1_Front_Led_Hot_Temp_2 == SET )
    {
        /*if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)*/
        if( Bit0_Hot_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
            {
                pLED_HOT_TEMP_2 = Bit1_Front_Led_Hot_Temp_2;
            }
            else
            {
                pLED_HOT_TEMP_2 = CLEAR;
            }
        }
        else
        {
            pLED_HOT_TEMP_2 = SET;
        }
    }
    else
    {
        pLED_HOT_TEMP_2 = CLEAR;
    }
    #endif

    if( Bit1_Front_Led_Hot_Temp_2 == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
        {
            pLED_HOT_TEMP_2 = Bit1_Front_Led_Hot_Temp_2;
        }
        else
        {
            pLED_HOT_TEMP_2 = CLEAR;
        }
    }
    else
    {
        pLED_HOT_TEMP_2 = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:48] 온수 온도3 LED..*/
    #if 0
    if( Bit2_Front_Led_Hot_Temp_3 == SET )
    {
        /*if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)*/
        if( Bit0_Hot_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
            {
                pLED_HOT_TEMP_3 = Bit2_Front_Led_Hot_Temp_3;
            }
            else
            {
                pLED_HOT_TEMP_3 = CLEAR;
            }
        }
        else
        {
            pLED_HOT_TEMP_3 = SET;
        }
    }
    else
    {
        pLED_HOT_TEMP_3 = CLEAR;
    }
    #endif

    if( Bit2_Front_Led_Hot_Temp_3 == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_hot_temp)
        {
            pLED_HOT_TEMP_3 = Bit2_Front_Led_Hot_Temp_3;
        }
        else
        {
            pLED_HOT_TEMP_3 = CLEAR;
        }
    }
    else
    {
        pLED_HOT_TEMP_3 = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:33:55] 냉수 온도1 LED..*/
    #if 0
    if( Bit3_Front_Led_Cold_Temp_1 == SET )
    {
        /*if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)*/
        if( Bit1_Cold_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
            {
                pLED_COLD_TEMP_1 = Bit3_Front_Led_Cold_Temp_1;
            }
            else
            {
                pLED_COLD_TEMP_1 = CLEAR;
            }
        }
        else
        {
            pLED_COLD_TEMP_1 = SET;
        }
    }
    else
    {
        pLED_COLD_TEMP_1 = CLEAR;
    }
    #endif

    if( Bit3_Front_Led_Cold_Temp_1 == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
        {
            pLED_COLD_TEMP_1 = Bit3_Front_Led_Cold_Temp_1;
        }
        else
        {
            pLED_COLD_TEMP_1 = CLEAR;
        }
    }
    else
    {
        pLED_COLD_TEMP_1 = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:34:00] 냉수 온도2 LED..*/
    #if 0
    if( Bit4_Front_Led_Cold_Temp_2 == SET )
    {
        /*if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)*/
        if( Bit1_Cold_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
            {
                pLED_COLD_TEMP_2 = Bit4_Front_Led_Cold_Temp_2;
            }
            else
            {
                pLED_COLD_TEMP_2 = CLEAR;
            }
        }
        else
        {
            pLED_COLD_TEMP_2 = SET;
        }
    }
    else
    {
        pLED_COLD_TEMP_2 = CLEAR;
    }
    #endif

    if( Bit4_Front_Led_Cold_Temp_2 == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
        {
            pLED_COLD_TEMP_2 = Bit4_Front_Led_Cold_Temp_2;
        }
        else
        {
            pLED_COLD_TEMP_2 = CLEAR;
        }
    }
    else
    {
        pLED_COLD_TEMP_2 = CLEAR;
    }


    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:34:05] 냉수 온도3 LED..*/
    #if 0
    if( Bit5_Front_Led_Cold_Temp_3 == SET )
    {
        /*if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)*/
        if( Bit1_Cold_Temp_1_2_3_Dimming_State == SET )
        {
            /*if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)*/
            if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
            {
                pLED_COLD_TEMP_3 = Bit5_Front_Led_Cold_Temp_3;
            }
            else
            {
                pLED_COLD_TEMP_3 = CLEAR;
            }
        }
        else
        {
            pLED_COLD_TEMP_3 = SET;
        }
    }
    else
    {
        pLED_COLD_TEMP_3 = CLEAR;
    }
    #endif

    if( Bit5_Front_Led_Cold_Temp_3 == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_cold_temp)
        {
            pLED_COLD_TEMP_3 = Bit5_Front_Led_Cold_Temp_3;
        }
        else
        {
            pLED_COLD_TEMP_3 = CLEAR;
        }
    }
    else
    {
        pLED_COLD_TEMP_3 = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:34:39] 얼음 가득 LED..*/
    if( Bit5_Front_Led_Ice_Full == SET )
    {
        if( Bit14_Ice_Full_Dimming_State == SET )
        {
            if(gu8_led_dimming <= bit_4_7_dimming_etc_icon)
            {
                pLED_ICE_FULL = Bit5_Front_Led_Ice_Full;
            }
            else
            {
                pLED_ICE_FULL = CLEAR;
            }
        }
        else
        {
            pLED_ICE_FULL = SET;
        }
    }
    else
    {
        pLED_ICE_FULL = CLEAR;
    }
    ////////////////////////////////////////////////////////////////////////////////////
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:34:49] 설정 Ice Off LED..*/
    if( Bit0_Front_Led_Ice_First == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_ICE_FIRST = Bit0_Front_Led_Ice_First;
        }
        else
        {
            pLED_SETTING_ICE_FIRST = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_ICE_FIRST = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:34:56] 설정 Ice Lock LED..*/
    if( Bit1_Front_Led_Ice_Lock == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_ICE_LOCK = Bit1_Front_Led_Ice_Lock;
        }
        else
        {
            pLED_SETTING_ICE_LOCK = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_ICE_LOCK = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:35:02] 설정 Hot Lock LED..*/
    if( Bit2_Front_Led_Hot_Lock == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_HOT_LOCK = Bit2_Front_Led_Hot_Lock;
        }
        else
        {
            pLED_SETTING_HOT_LOCK = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_HOT_LOCK = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:35:09] 설정 Auto Drain LED..*/
    if( Bit3_Front_Led_Eco_Mode == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_ECO_MODE = Bit3_Front_Led_Eco_Mode;
        }
        else
        {
            pLED_SETTING_ECO_MODE = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_ECO_MODE = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:35:20] 설정 Cold Temp LED..*/
    if( Bit4_Front_Led_Cold_Temp == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_COLD_OFF = Bit4_Front_Led_Cold_Temp;
        }
        else
        {
            pLED_SETTING_COLD_OFF = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_COLD_OFF = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:35:27] 설정 Eco Mode LED..*/
    if( Bit5_Front_Led_My_Cup == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_setting_menu)
        {
            pLED_SETTING_MY_CUP = Bit5_Front_Led_My_Cup;
        }
        else
        {
            pLED_SETTING_MY_CUP = CLEAR;
        }
    }
    else
    {
        pLED_SETTING_MY_CUP = CLEAR;
    }
    ////////////////////////////////////////////////////////////////////////////////////
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void time_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    /*..sean [24-11-14] AM LED..*/
    if( Bit0_Time_Led_AM == SET )
    {
        if(gu8_led_dimming <= bit_0_3_dimming_Am)
        {
            pLED_AM = Bit0_Time_Led_AM;
        }
        else
        {
            pLED_AM = CLEAR;
        }
    }
    else
    {
        pLED_AM = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..sean [24-11-14] PM LED..*/
    if( Bit1_Time_Led_PM == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_Pm)
        {
            pLED_PM = Bit1_Time_Led_PM;
        }
        else
        {
            pLED_PM = CLEAR;
        }
    }
    else
    {
        pLED_PM = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-2-2오후 5:35:02] Colon LED..*/
    if( Bit2_Time_Led_Colon == SET )
    {
        if(gu8_led_dimming <= bit_4_7_dimming_colon)
        {
            pLED_COLON = Bit2_Time_Led_Colon;
        }
        else
        {
            pLED_COLON = CLEAR;
        }
    }
    else
    {
        pLED_COLON = CLEAR;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_led_output(void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    if( Bit3_Led_Wifi_Icon_White == SET )
    {
        if( gu8_ota_start == SET )
        {
            gu16_ota_timer++;

            /*..hui [23-7-5오전 9:56:51] OTA시 흰색 LED 1초 ON - 4초 OFF 점멸..*/
            /*..hui [23-7-24오후 1:45:21] 1초 ON - 3초 OFF 점멸임....*/
            if( gu16_ota_timer <= 3000 )
            {
                pLED_WiFi_White = SET;
            }
            else
            {
                pLED_WiFi_White = CLEAR;
            }

            #if 0
            if( gu16_ota_timer >= 20000 )
            {
                gu16_ota_timer = 0;
            }
            else{}
            #endif

            if( gu16_ota_timer >= 4000 )
            {
                gu16_ota_timer = 0;
            }
            else{}
        }
		/*
        else if( Bit1_Animation_Dimming_Wifi_State == SET )
        {
            if(gu8_led_breathe_dimming <= gu8_led_breathe_dimming_time)
            {
                pLED_WiFi_White = SET;
            }
            else
            {
                pLED_WiFi_White = CLEAR;
            }
        }
		*/
        else
        {
            if(gu8_led_dimming <= bit_0_3_dimming_White)
            {
                pLED_WiFi_White = SET;
            }
            else
            {
                pLED_WiFi_White = CLEAR;
            }
        }
    }
    else
    {
        pLED_WiFi_White = CLEAR;
        gu16_ota_timer = 0;
    }
}


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
#include    "M6_Display_Control.h"



void Display_Control(void);
void led_control_mode_decesion(void);
void display_version( void );
void led_blink_timer(void);
void on_all_control_led( void );
void off_all_control_led( void );








//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////




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
#define            Bit6_Front_Led_Ice_Full                     U8FrontTempLEDB.Bit.b6

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


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


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
#define            bit_4_7_dimming_Blue							U8DimmingNo10.nibble.b4_7

TYPE_DIMMING       U8DimmingNo12;
#define            gu8_dimming_fnd_2_1							U8DimmingNo12.byte
#define            bit_0_3_fnd_0_0_0_1							U8DimmingNo12.nibble.b0_3
#define            bit_4_7_fnd_0_0_2_0							U8DimmingNo12.nibble.b4_7

TYPE_DIMMING       U8DimmingNo13;
#define            gu8_dimming_fnd_4_3							U8DimmingNo13.byte
#define            bit_0_3_fnd_0_3_0_0							U8DimmingNo13.nibble.b0_3
#define            bit_4_7_fnd_4_0_0_0							U8DimmingNo13.nibble.b4_7



//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

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














U8 gu8T300ms;
bit F_Wink_300ms;

U8 gu8T500ms;
bit F_Wink_500ms;

U8 gu8T1000ms;
bit F_Wink_1000ms;

U8 gu8T2000ms;
bit F_Wink_2000ms;

U16 gu16T3000ms;
bit F_Wink_3000ms;


LED_STEP gu8_Led_Display_Step;



U8 gu8_led_version_step;
U8 gu8_version_display_Timer;
U8 gu8_version_display_count;
bit F_FW_Version_Display_Mode;


bit f_ice_extraction_out;

U8 gu8_cup_led_select;
U8 gu8_cup_led_off_time;


U8 gu8_user_led_select;
U8 gu8_user_led_off_time;

U8 gu8_main_move_delay_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Control(void)
{
    led_blink_timer();
    led_control_mode_decesion();

    sleep_mode_decesion();

    led_display();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_control_mode_decesion(void)
{
    if( F_FW_Version_Display_Mode != SET )
    {
        gu8_Led_Display_Step = LED_Display__VERSION;
    }
    else if( bit_debug_mode_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__DEBUG;
    }
	/*..sean [25-02-27] 잠금 상태에서 고장진단 내려질 경우 표시해야함..*/
    else if( bit_self_test_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__SELF_TEST;
    }
    else if( F_All_Lock == SET )
    {
        gu8_Led_Display_Step = LED_Display__ALL_LOCK;
    }
    else if( bit_altitude_setting_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__ALTITUDE_SETTING;
    }
	/*
    else if( bit_self_test_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__SELF_TEST;
    }
	*/
    else if( gu8_fota_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__FOTA_START;
    }
    else if( bit_memento_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__MEMENTO;
    }
    #if 0
    else if( bit_my_cup_setting_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__SETTING_MY_CUP;
    }
    #endif
    else if( bit_setting_mode_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__SETTING;
    }
    else if( F_WaterOut == SET )
    {
        gu8_Led_Display_Step = LED_Display__WATER_EXTRACT;
    }
    else if( F_Ice == SET )
    {
        gu8_Led_Display_Step = LED_Display__ICE_EXTRACT;
    }
    /*else if( bit_illumi_State == SET )*/
    //else if( bit_sleep_mode_start == SET )
    else if( bit_display_sleep_start == SET || bit_9_hour_no_use_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__SLEEP;
    }
    else if( gu8_Error_Code > 0 && gu8_error_popup_enable == SET )
    {
        gu8_Led_Display_Step = LED_Display__ERROR;
    }
    else if( u8ButtonSetDisplay > BUTTON_SET_DISPLAY_OFF )
    {
        gu8_Led_Display_Step = LED_Display__BUTTON_SET;
    }
	else if( bit_time_setting_start == TRUE)
	{
		gu8_Led_Display_Step = LED_Display__TIME_SETTING;
	}
    else if( bit_wifi_pairing_start == SET )
    {
        gu8_Led_Display_Step = LED_Display__WIFI_PAIRING;
    }
    else
    {
        gu8_Led_Display_Step = LED_Display__MAIN;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_version( void )
{
    switch(gu8_led_version_step)
    {
        case PROC_START:

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_version_display_Timer = 0;

                gu8_version_display_count++;

                if((BIT)(gu8_version_display_count & 1) == (BIT)0)
                {
                    on_all_control_led();
                }
                else
                {
                    off_all_control_led();
                }

                /*if(gu8_version_display_count > 6)*/
                /*..hui [23-3-22오후 12:50:58] 검사시 너무 느림.. 2번 점멸로 변경..*/
                if(gu8_version_display_count > 4)
                {
                    /*..hui [21-11-4오전 9:13:03] 일반모드에서는 버전 표시하지 않도록..*/
                    if( u8FactoryTestMode == NONE_TEST_MODE )
                    {
                        gu8_led_version_step = PROC_END;
                        gu8_version_display_count = 0;
                        gu8_version_display_Timer = 0;
                    }
                    else
                    {
                        gu8_led_version_step++;
                        gu8_version_display_count = 0;
                        gu8_version_display_Timer = 0;
                    }
                }
                else{}
            }
            else{}

            break;

        case PROC_1:

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_version_display_Timer = 0;
                gu8_led_version_step++;
            }
            else{}

            break;

        case PROC_2:

            ///Bit0_Front_Led_Set_Select = SET;
			/*..sean [23-9-14 오후 17:59 알아보기 쉽게 하기위해서 ice점등으로 변경]..*/
			/*Bit1_Front_Led_Ice_Select = SET;*/
			/*Bit2_Front_Led_Hot_Select = SET;*/
			/*..hui [24-4-24오후 5:27:14] 정수..*/
			Bit3_Front_Led_Ambient_Select = SET;
            fnd_version();


            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 10)
            {
                gu8_led_version_step++;
                gu8_version_display_Timer = 0;
            }
            else{}

            break;

        case PROC_END:

            /*..hui [17-4-4오후 2:20:26] 마지막으로 500ms OFF하고 종료..*/
            off_all_control_led();

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_led_version_step = 0;
                gu8_version_display_Timer = 0;
                F_FW_Version_Display_Mode = SET;
            }
            else{}

            break;

        default:
            break;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_blink_timer(void)
{
    gu8T300ms++;

    if(gu8T300ms >= 3)
    {
        gu8T300ms = 0;
        F_Wink_300ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T500ms++;

    if(gu8T500ms >= 5)
    {
        gu8T500ms = 0;
        F_Wink_500ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T1000ms++;

    if(gu8T1000ms >= 10)
    {
        gu8T1000ms = 0;
        F_Wink_1000ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T2000ms++;

    if(gu8T2000ms >= 20)
    {
        gu8T2000ms = 0;
        F_Wink_2000ms ^= SET;          // 300msec Wink
    }
    else{}

    gu16T3000ms++;

    if(gu16T3000ms >= 30)
    {
        gu16T3000ms = 0;
        F_Wink_3000ms ^= SET;          // 300msec Wink
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void on_all_control_led( void )
{
    gu8_front_fnd_thousand = 0x03;
    gu8_front_fnd_hundred = 0x7f;
    gu8_front_fnd_ten = 0x7f;
    gu8_front_fnd_one = 0x7f;

    gu8_front_extract_uv_led = 0xff;
    gu8_front_etc_led = 0xff;
    gu8_front_select_led = 0xff;
    gu8_front_temp_led = 0x7f;
    gu8_front_setting_led = 0x3f;

	gu8_time_wifi_setting_led = 0x1f;

	gu8_dimming_fnd_4_3 = 0xff;
	gu8_dimming_fnd_2_1 = 0xff;
	
	/*.. sean [24-12-05] Front UV 사용해야하기 때문에 추가..*/	
	//bit_uv_ice_extraction_out = SET;
	//f_ice_extraction_out = SET;
	
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    bit_0_3_dimming_set_select = LED_DIMMING_FULL;
    bit_4_7_dimming_ice_select = LED_DIMMING_FULL;

    bit_0_3_dimming_hot_select = LED_DIMMING_FULL;
    bit_4_7_dimming_ambient_select = LED_DIMMING_FULL;

    bit_0_3_dimming_cold_select = LED_DIMMING_FULL;
    bit_4_7_dimming_amount_select = LED_DIMMING_FULL;

    bit_0_3_dimming_ice_extract = LED_DIMMING_FULL;
    bit_4_7_dimming_water_extract = LED_DIMMING_FULL;

    bit_0_3_dimming_setting_menu = LED_DIMMING_FULL;
    bit_4_7_dimming_etc_icon = LED_DIMMING_FULL;

    bit_0_3_dimming_hot_temp = LED_DIMMING_FULL;
    bit_4_7_dimming_cold_temp = LED_DIMMING_FULL;

    bit_0_3_dimming_cont = LED_DIMMING_FULL;
    bit_4_7_dimming_pot = LED_DIMMING_FULL;

    bit_0_3_dimming_2cups = LED_DIMMING_FULL;
    bit_4_7_dimming_1cup = LED_DIMMING_FULL;

    bit_0_3_dimming_half_cup = LED_DIMMING_FULL;
    bit_4_7_dimming_colon = LED_DIMMING_FULL;

    bit_0_3_dimming_Am = LED_DIMMING_FULL;
    bit_4_7_dimming_Pm = LED_DIMMING_FULL;

    bit_0_3_dimming_White = LED_DIMMING_FULL;
    //bit_4_7_dimming_Blue = LED_DIMMING_FULL;

	/*.. sean [25-02-10] FND Dimming 추가..*/
	gu8_Dimming_seg = LED_DIMMING_FULL;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void off_all_control_led( void )
{
    gu8_front_fnd_thousand = 0;
    gu8_front_fnd_hundred = 0;
    gu8_front_fnd_ten = 0;
    gu8_front_fnd_one = 0;

    gu8_front_extract_uv_led = 0;
    gu8_front_etc_led = 0;
    gu8_front_select_led = 0;
    gu8_front_temp_led = 0;
    gu8_front_setting_led = 0;

	gu8_time_wifi_setting_led = 0;
	
	gu8_dimming_fnd_4_3 = 0;
	gu8_dimming_fnd_2_1 = 0;

	/*.. sean [24-12-05] Front UV 사용해야하기 때문에 추가..*/	
	//bit_uv_ice_extraction_out = CLEAR;
	//f_ice_extraction_out = CLEAR;

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    bit_0_3_dimming_set_select = LED_DIMMING_FULL;
    bit_4_7_dimming_ice_select = LED_DIMMING_FULL;

    bit_0_3_dimming_hot_select = LED_DIMMING_FULL;
    bit_4_7_dimming_ambient_select = LED_DIMMING_FULL;

    bit_0_3_dimming_cold_select = LED_DIMMING_FULL;
    bit_4_7_dimming_amount_select = LED_DIMMING_FULL;

    bit_0_3_dimming_ice_extract = LED_DIMMING_FULL;
    bit_4_7_dimming_water_extract = LED_DIMMING_FULL;

    bit_0_3_dimming_setting_menu = LED_DIMMING_FULL;
    bit_4_7_dimming_etc_icon = LED_DIMMING_FULL;

    bit_0_3_dimming_hot_temp = LED_DIMMING_FULL;
    bit_4_7_dimming_cold_temp = LED_DIMMING_FULL;

    bit_0_3_dimming_cont = LED_DIMMING_FULL;
    bit_4_7_dimming_pot = LED_DIMMING_FULL;

    bit_0_3_dimming_2cups = LED_DIMMING_FULL;
    bit_4_7_dimming_1cup = LED_DIMMING_FULL;

    bit_0_3_dimming_half_cup = LED_DIMMING_FULL;
    bit_4_7_dimming_colon = LED_DIMMING_FULL;

    bit_0_3_dimming_Am = LED_DIMMING_FULL;
    bit_4_7_dimming_Pm = LED_DIMMING_FULL;

    bit_0_3_dimming_White = LED_DIMMING_FULL;
    //bit_4_7_dimming_Blue = LED_DIMMING_FULL;
	
	/*.. sean [25-02-10] FND Dimming 추가..*/
	gu8_Dimming_seg = LED_DIMMING_FULL;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



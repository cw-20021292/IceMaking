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
#include    "test_display_factory.h"

void diplay_test_start(void);
void Display_Test_Main(void);
void display_test_factory_input(void);
void display_test_factory_job(void);
void initial_all_data(void);


bit F_cds_detect;
U8 gu8_user_lcd_output;
U8 gu8_hot_lcd_output;
U8 gu8_room_lcd_output;
U8 gu8_cold_lcd_output;
U8 gu8_cup_lcd_output;

U8 gu8_initial_all_data;
U8 u8_water_select_testmode;

bit F_UV_faucet_current;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void diplay_test_start(void)
{
    gu8_test_mode_timeout = 0;
    BuzStep(BUZZER_SELECT);

    off_all_control_led();
    UARTest_NO_LOAD_Set();
    F_TrayMotorCW = 0;
    F_TrayMotorCCW = 0;

    /*..hui [17-12-28오후 10:54:12] 버전만 표시..*/
    F_FW_Version_Display_Mode = CLEAR;
    gu8_led_version_step = 2;
    gu8_version_display_Timer = 0;

    u8FactoryTestMode = DISPLAY_TEST_MODE;

    /*..hui [19-11-5오후 5:57:28] EEPROM / RTC 시간 초기화..*/
    gu8_initial_all_data = 1;

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14오후 8:15:16] 12V 전원 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    bit_sleep_mode_start = CLEAR;

    bit_setting_test_finish = CLEAR;
    bit_ice_test_finish = CLEAR;
    bit_hot_test_finish = CLEAR;
    bit_ambient_test_finish = CLEAR;
    bit_cold_tst_finish = CLEAR;
    bit_amount_test_finish = CLEAR;
    bit_ice_first_test_finish = CLEAR;
    bit_ice_lock_test_finish = CLEAR;
    bit_hot_lock_test_finish = CLEAR;
    bit_eco_test_finish = CLEAR;
    bit_cold_temp_test_finish = CLEAR;
    bit_my_cup_test_finish = CLEAR;

    bit_water_extract_test_finish = CLEAR;
    bit_ice_extract_test_finish = CLEAR;

    bit_manual_test_start = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Test_Main(void)
{
    if(F_FW_Version_Display_Mode != SET)
    {
        display_version();
    }
    else
    {
        display_test_factory_input();
        display_test_factory_job();

        fnd_front_test_mode_();

        /*..hui [23-6-30오후 1:22:01] 디스플레이 검사할때도 DC FAN은 항시 ON하도록..*/
        pDC_FAN = SET;
    }

    initial_all_data();
    initial_ice_tray();
    uart_service_sw();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_input(void)
{
    /*..hui [19-11-18오전 11:28:17] 프론트 LED 다 꺼진 상태에서 조도센서 입력..*/
    /*..hui [19-11-18오후 12:55:19] 트레이 다 올리고나서부터 감지..*/
    /*..hui [20-2-11오후 5:55:02] 탱크 리드스위치 입력 추가.. 닫혔을 경우에만..*/
    /*..hui [20-2-17오후 3:24:39] 트레이도 제빙쪽으로 다 올라갔을 경우에만 완료되도록..*/
    if( F_UV_faucet_current == SET

        && gu8_front_fnd_thousand == 0
        && gu8_front_fnd_hundred == 0
        && gu8_front_fnd_ten == 0
        && gu8_front_fnd_one == 0

        && gu8_front_extract_uv_led == 0
        && gu8_front_etc_led == 0
        && gu8_front_select_led == 0
        && gu8_front_temp_led == 0
        && gu8_front_setting_led == 0
        && gu8_time_wifi_setting_led == 0

        && gu8_service_reed_uart == SET
        && gu8_uart_tray_initial_step == 3 )
    {
        F_cds_detect = 1;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_job(void)
{
    led_blink_timer();

	if(gu8_front_uv_ice_faucet_current > 30)
	{
		F_UV_faucet_current = SET;
	}
	else {}
	
    if(gu8_setting_test_input == 1)
    {
        Bit0_Front_Led_Set_Select = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Led_ml = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Led_Percent = F_cds_detect & F_Wink_500ms;
        //Bit6_Front_Led_Auto_Drain = F_cds_detect & F_Wink_500ms;
        Bit7_Front_Led_Low_Water = F_cds_detect & F_Wink_500ms;
        Bit4_Led_Wifi_Icon_Blue = F_cds_detect & F_Wink_500ms;
		//Bit3_Front_Led_Eco_Mode = F_cds_detect & F_Wink_500ms;

        bit_setting_test_finish = SET;
    }
    else
    {
        if( bit_setting_test_finish == CLEAR )
        {
            Bit0_Front_Led_Set_Select = SET;
            Bit4_Front_Led_ml = SET;
            Bit5_Front_Led_Percent = SET;
            //Bit6_Front_Led_Auto_Drain = SET;
            Bit7_Front_Led_Low_Water = SET;
            Bit4_Led_Wifi_Icon_Blue = SET;
			//Bit3_Front_Led_Eco_Mode = SET;
        }
        else
        {
            gu8_setting_test_input = 1;
        }
    }

    if(gu8_ice_test_input == 1)
    {
        Bit1_Front_Led_Ice_Select = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Led_Ice_Full = F_cds_detect & F_Wink_500ms;
        Bit3_Led_Wifi_Icon_White = F_cds_detect & F_Wink_500ms;
        bit_ice_test_finish = SET;
    }
    else
    {
        if( bit_ice_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = SET;
            Bit6_Front_Led_Ice_Full = SET;
        	Bit3_Led_Wifi_Icon_White = SET;
        }
        else
        {
            gu8_ice_test_input = 1;
        }
    }

    if(gu8_hot_test_input == 1)
    {
        Bit2_Front_Led_Hot_Select = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Led_Hot_Temp_1 = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Led_Hot_Temp_2 = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Led_Hot_Temp_3 = F_cds_detect & F_Wink_500ms;
        bit_hot_test_finish = SET;
    }
    else
    {
        if( bit_hot_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Select = SET;
            Bit0_Front_Led_Hot_Temp_1 = SET;
            Bit1_Front_Led_Hot_Temp_2 = SET;
            Bit2_Front_Led_Hot_Temp_3 = SET;
        }
        else
        {
            gu8_hot_test_input = 1;
        }
    }

    if(gu8_ambient_test_input == 1)
    {
        Bit3_Front_Led_Ambient_Select = F_cds_detect & F_Wink_500ms;

        Bit0_Front_Led_UV_Sterilization = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Led_Faucet = F_cds_detect & F_Wink_500ms;
        //Bit2_Front_Led_Ice_Tank = F_cds_detect & F_Wink_500ms;
		Bit5_Front_Led_Icon_ice_faucet = F_cds_detect & F_Wink_500ms;
		/*.. [24-12-26] 향지 구분하기 위해서 얼음 탱크 기존에도 점멸 ..*/
        Bit2_Front_Led_Ice_Tank = F_Wink_500ms;
		
        bit_ambient_test_finish = SET;
    }
    else
    {
        if( bit_ambient_test_finish == CLEAR )
        {
            Bit3_Front_Led_Ambient_Select = SET;

            Bit0_Front_Led_UV_Sterilization = SET;
            Bit1_Front_Led_Faucet = SET;
            Bit2_Front_Led_Ice_Tank = SET;
			Bit5_Front_Led_Icon_ice_faucet = SET;
        }
        else
        {
            gu8_ambient_test_input = 1;
        }
    }

    if(gu8_cold_test_input == 1)
    {
        Bit4_Front_Led_Cold_Select = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Led_Cold_Temp_1 = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Led_Cold_Temp_2 = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Led_Cold_Temp_3 = F_cds_detect & F_Wink_500ms;

        bit_cold_tst_finish = SET;
    }
    else
    {
        if( bit_cold_tst_finish == CLEAR )
        {
            Bit4_Front_Led_Cold_Select = SET;
            Bit3_Front_Led_Cold_Temp_1 = SET;
            Bit4_Front_Led_Cold_Temp_2 = SET;
            Bit5_Front_Led_Cold_Temp_3 = SET;
        }
        else
        {
            gu8_cold_test_input = 1;
        }
    }

    if(gu8_amount_test_input == 1)
    {
        Bit5_Front_Led_Amount_Select = F_cds_detect & F_Wink_500ms;
        //Bit5_Front_Led_Icon_All_Lock = F_cds_detect & F_Wink_500ms;
        Bit2_Time_Led_Colon = F_cds_detect & F_Wink_500ms;
        Bit0_Time_Led_AM = F_cds_detect & F_Wink_500ms;
        Bit1_Time_Led_PM = F_cds_detect & F_Wink_500ms;

        bit_amount_test_finish = SET;
    }
    else
    {
        if( bit_amount_test_finish == CLEAR )
        {
            Bit5_Front_Led_Amount_Select = SET;
            //Bit5_Front_Led_Icon_All_Lock = SET;
            Bit2_Time_Led_Colon = SET;
	        Bit0_Time_Led_AM = SET;
	        Bit1_Time_Led_PM = SET;
        }
        else
        {

            gu8_amount_test_input = 1;
        }
    }

    if(gu8_setting_ice_first_test_input == 1)
    {
        Bit0_Front_Led_Ice_First = F_cds_detect & F_Wink_500ms;
        Bit7_Front_Led_Icon_Ice_First = F_cds_detect & F_Wink_500ms;

        bit_ice_first_test_finish = SET;
    }
    else
    {
        if( bit_ice_first_test_finish == CLEAR )
        {
            Bit0_Front_Led_Ice_First = SET;
            Bit7_Front_Led_Icon_Ice_First = SET;
        }
        else
        {
            gu8_setting_ice_first_test_input = 1;
        }
    }

    if(gu8_setting_ice_lock_test_input == 1)
    {
        Bit1_Front_Led_Ice_Lock = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Led_Icon_Ice_Lock = F_cds_detect & F_Wink_500ms;

        bit_ice_lock_test_finish = SET;
    }
    else
    {
        if( bit_ice_lock_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Lock = SET;
            Bit6_Front_Led_Icon_Ice_Lock = SET;
        }
        else
        {
            gu8_setting_ice_lock_test_input = 1;
        }
    }

    if(gu8_setting_hot_lock_test_input == 1)
    {
        Bit2_Front_Led_Hot_Lock = F_cds_detect & F_Wink_500ms;
        Bit7_Front_Led_Icon_Hot_Lock = F_cds_detect & F_Wink_500ms;

        bit_hot_lock_test_finish = SET;
    }
    else
    {
        if( bit_hot_lock_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Lock = SET;
            Bit7_Front_Led_Icon_Hot_Lock = SET;
        }
        else
        {
            gu8_setting_hot_lock_test_input = 1;
        }
    }

    if(gu8_setting_eco_mode_test_input == 1)
    {
        Bit3_Front_Led_Eco_Mode = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Led_Icon_Save = F_cds_detect & F_Wink_500ms;

        bit_eco_test_finish = SET;
    }
    else
    {
        if( bit_eco_test_finish == CLEAR )
        {
            Bit3_Front_Led_Eco_Mode = SET;
            Bit6_Front_Led_Icon_Save = SET;
        }
        else
        {
            gu8_setting_eco_mode_test_input = 1;
        }
    }

    if(gu8_setting_cold_temp_test_input == 1)
    {
        Bit4_Front_Led_Cold_Temp = F_cds_detect & F_Wink_500ms;

        bit_cold_temp_test_finish = SET;
    }
    else
    {
        if( bit_cold_temp_test_finish == CLEAR )
        {
            Bit4_Front_Led_Cold_Temp = SET;
        }
        else
        {
            gu8_setting_cold_temp_test_input = 1;
        }
    }

    if(gu8_setting_my_cup_test_input == 1)
    {
        Bit5_Front_Led_My_Cup = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Led_Cont = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Led_Pot = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Led_2_Cups = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Led_1_Cup = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Led_half_Cup = F_cds_detect & F_Wink_500ms;

        bit_my_cup_test_finish = SET;
    }
    else
    {
        if( bit_my_cup_test_finish == CLEAR )
        {
            Bit5_Front_Led_My_Cup = SET;
            Bit0_Front_Led_Cont = SET;
            Bit1_Front_Led_Pot = SET;
            Bit2_Front_Led_2_Cups = SET;
            Bit3_Front_Led_1_Cup = SET;
        	Bit6_Front_Led_half_Cup = SET;
        }
        else
        {
            gu8_setting_my_cup_test_input = 1;
        }
    }


    if(gu8_water_ext_test_input == 1)
    {
        Bit4_Front_Led_Water_Extract = F_cds_detect & F_Wink_500ms;

        bit_water_extract_test_finish = SET;
    }
    else
    {
        if( bit_water_extract_test_finish == CLEAR )
        {
            Bit4_Front_Led_Water_Extract = SET;
        }
        else
        {
            gu8_water_ext_test_input = 1;
        }
    }

    if(gu8_ice_ext_test_input == 1)
    {
        Bit3_Front_Led_Ice_Extract = F_cds_detect & F_Wink_500ms;

        bit_ice_extract_test_finish = SET;
    }
    else
    {
        if( bit_ice_extract_test_finish == CLEAR )
        {
            Bit3_Front_Led_Ice_Extract = SET;
        }
        else
        {
            gu8_ice_ext_test_input = 1;
        }
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_all_data(void)
{
    if(gu8_initial_all_data == 1)
    {
        eeprom_initial();
        gu8_initial_all_data = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



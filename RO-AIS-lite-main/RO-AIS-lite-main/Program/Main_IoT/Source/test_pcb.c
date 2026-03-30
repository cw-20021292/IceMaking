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
#include    "test_pcb.h"



void Pcb_Test_Init_Check(void);
void Main_PBA_Test_Mode_Start(void);
void Pcb_Test_Main(void);
void pcb_test_job(void);
void thermistor_test(void);
void hot_out_temp(void);
void cold_temp(void);
void outdoor_temp(void);
void room_temp(void);
void eva1_temp(void);
void eva2_temp(void);
void sensor_test(void);
void watertank_low_water(void);
void watertank_high_water(void);
void draintank_low_water(void);
void draintank_high_water(void);
void ovf_water(void);
void ice_full(void);
void water_leak(void);
void boost_in(void);
void switch_test(void);
void output_test(void);
void heater_output(void);
void comp_fan_output(void);
void step_motor_teest_output(void);
void ac_motor_output(void);
void valve_output_one(void);
void valve_output_two(void);
void uv_output(void);
void pump_output(void);
void flow_sensor(void);
void uart_test(void);
void pcb_test_mode_uart_test(void);
void uart_error_display(void);
void PCB_Test_Mode_Key_Short_Input( U16 u16key_input_value);
void PCB_Test_Mode_Extract_Key_Short_Input(void);
void PCB_Test_Mode_Ice_Key_Short_Input(void);
void test_mode_eeprom_initial(void);
void wifi_test(void);

void fault_ad_test(void);


TYPE_BYTE          U8FrontTestLEDOneB;
#define            u8FrontTestLEDOne                    U8FrontTestLEDOneB.byte
#define            Bit0_P10                             U8FrontTestLEDOneB.Bit.b0
#define            Bit1_P11                             U8FrontTestLEDOneB.Bit.b1
#define            Bit2_P12                             U8FrontTestLEDOneB.Bit.b2
#define            Bit3_P13                             U8FrontTestLEDOneB.Bit.b3
#define            Bit4_P14                             U8FrontTestLEDOneB.Bit.b4
#define            Bit5_P15                             U8FrontTestLEDOneB.Bit.b5
#define            Bit6_P16                             U8FrontTestLEDOneB.Bit.b6
#define            Bit7_P17                             U8FrontTestLEDOneB.Bit.b7


TYPE_BYTE          U8FrontTestLEDTwoB;
#define            u8FrontTestLEDTwo                    U8FrontTestLEDTwoB.byte
#define            Bit0_P55                             U8FrontTestLEDTwoB.Bit.b0
#define            Bit1_P30                             U8FrontTestLEDTwoB.Bit.b1
#define            Bit2_P05                             U8FrontTestLEDTwoB.Bit.b2
#define            Bit3_P76                             U8FrontTestLEDTwoB.Bit.b3
#define            Bit4_P120                            U8FrontTestLEDTwoB.Bit.b4
#define            Bit5_P43                             U8FrontTestLEDTwoB.Bit.b5
#define            Bit6_P130                            U8FrontTestLEDTwoB.Bit.b6
#define            Bit7_P24                             U8FrontTestLEDTwoB.Bit.b7




U8 gu8_setting_test_input;
U8 gu8_ice_test_input;
U8 gu8_hot_test_input;
U8 gu8_ambient_test_input;
U8 gu8_cold_test_input;
U8 gu8_amount_test_input;
U8 gu8_setting_ice_first_test_input;
U8 gu8_setting_ice_lock_test_input;
U8 gu8_setting_hot_lock_test_input;
U8 gu8_setting_eco_mode_test_input;
U8 gu8_setting_cold_temp_test_input;
U8 gu8_setting_my_cup_test_input;


bit bit_setting_test_finish;
bit bit_ice_test_finish;
bit bit_hot_test_finish;
bit bit_ambient_test_finish;
bit bit_cold_tst_finish;
bit bit_amount_test_finish;
bit bit_ice_first_test_finish;
bit bit_ice_lock_test_finish;
bit bit_hot_lock_test_finish;
bit bit_eco_test_finish;
bit bit_cold_temp_test_finish;
bit bit_my_cup_test_finish;

bit bit_water_extract_test_finish;
bit bit_ice_extract_test_finish;





U8 gu8_water_ext_test_input;
U8 gu8_ice_ext_test_input;

U8 gu8_eeprom_initial_test_input;

U8 gu8_eeprom_initial_step;


U8 u8PcbTestEnableFlag;
U8 u8PcbTestEnableTimer;
bit F_PcbTestStart;
U16 u16TestModeEnableTimer;
U8 u8leakcnt;

bit F_step_test1;
bit F_step_test2;


U8 gu8_EAD_Pcb_Test_On_Time;
U8 gu8_EAD_Pcb_Test_Off_Time;

U8 gu8UARTest_Mode;


U8 gu8_fix_direction;
U8 gu8_EAD_Off;

bit F_Pcb_Test_Ice_Click;

U8 u8icefullcnt;
U8 u8leakcnt;
bit F_water_ext_step_motor_out_state;

U8 u8_drain_cnt;
U8 u8_hot_p_cnt;

bit F_flow_detect;
bit F_mc_sw1;
bit F_mc_sw2;

U8 gu8_hot_heater_on_timer;
U8 gu8_ice_heater_on_timer;


//U8 u8_rtc_test_proc;
//U8 u8_rtc_test_timer;
//U8 u8_rtc_test_fail;

U8 gu8_valve_timer_one;
U8 gu8_valve_timer_two;
U8 gu8_valve_timer_three;

U8 gu8_flow_test_timer;


U8 gu8_user_acc1;
U8 gu8_user_acc2;
U8 gu8_user_acc3;
U8 gu8_user_acc4;

bit F_dbg_Start;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pcb_Test_Init_Check(void)
{
#if 0
    u8PcbTestEnableFlag = CLEAR;


    while(u8PcbTestEnableFlag != SET)
    {
        if(ICE_EXTRACT_KEY != SET && EXTRACT != SET)
        {
            u16TestModeEnableTimer++;

            if(u16TestModeEnableTimer >= TEST_MODE_START_CHECK_TIME)
            {
                u16TestModeEnableTimer = TEST_MODE_START_CHECK_TIME;
                Main_PBA_Test_Mode_Start();
                u8PcbTestEnableFlag = SET;

            }
            else{}
        }
        else
        {
            u16TestModeEnableTimer = 0;
            u8PcbTestEnableFlag = SET;
        }
    }

    //F_PcbTestStart = SET;
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Main_PBA_Test_Mode_Start(void)
{
    /*F_PcbTestStart = SET;*/
    gu8_test_mode_timeout = 0;
    off_all_control_led();
    BuzStep(BUZZER_COOL_SETUP);
    u8FactoryTestMode = PCB_TEST_MODE;
    UARTest_NO_LOAD_Set();
    F_FW_Version_Display_Mode = CLEAR;

    gu8_eeprom_initial_test_input = 1;

    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14���� 8:15:16] 12V ���� ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    /*..hui [21-2-18���� 5:08:19] WIFI ���� �˻� �߰�..*/
    //WifiKey(WIFI_KEY_TEST);
    /*..sean [24-12-24] WIFI �ڵ� ����ȭ�� ���� TEST��� ����..*/
	SetWifiSystemStatus(WIFI_FACTORY_STATUS, SET);
	
    gu8_flow_test_timer = 0;
    bit_sleep_mode_start = CLEAR;
    bit_manual_test_start = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pcb_Test_Main(void)
{
    led_blink_timer();

    /*..hui [19-7-22���� 7:36:53] ��������..*/
    calculate_flow_input();

    if(F_FW_Version_Display_Mode != SET)
    {
        display_version();
    }
    else
    {
        pcb_test_job();
        fnd_pba_test_mode_();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pcb_test_job(void)
{
    eeprom_test();
    thermistor_test();

    sensor_test();
    switch_test();
    flow_sensor();

    output_test();
    fault_ad_test();
	
    /*..hui [18-2-21���� 11:15:24] �ڵ��˻� uart ȸ�� �˻� ��� �߰�..*/
    uart_test();

    wifi_test();

    test_mode_eeprom_initial();

    if(bit_eeprom_err == 0)
    {
        Bit0_Front_Led_Set_Select = SET;
    }
    else
    {
        Bit0_Front_Led_Set_Select = CLEAR;
    }

	/*..sean [25-01-07] FCT Jig������ ff���� 7f�� ���� ..*/
    if( gu8_front_extract_uv_led == 0xff
        && gu8_front_etc_led == 0xff
        && gu8_front_select_led == 0xff
        && gu8_front_temp_led == 0x7f
        && Bit1_Front_Led_Ice_Lock == SET
        && Bit2_Front_Led_Hot_Lock == SET
        && Bit3_Front_Led_Eco_Mode == SET
        && Bit4_Front_Led_Cold_Temp == SET
        && Bit5_Front_Led_My_Cup == SET )
    {
        Bit0_Front_Led_Ice_First ^= SET;
    }
    else
    {
        /*Bit0_Front_Led_Ice_First = CLEAR;*/
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void thermistor_test(void)
{
    hot_out_temp();
    cold_temp();
    outdoor_temp();
    room_temp();
    eva1_temp();
    eva2_temp();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_out_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit2_Front_Led_Hot_Select = SET;
        Bit0_Front_Led_Hot_Temp_1 = SET;
        Bit1_Front_Led_Hot_Temp_2 = SET;
        Bit2_Front_Led_Hot_Temp_3 = SET;
        Bit7_Front_Led_Icon_Hot_Lock = SET;
		return;
	}
	else {}
	
    if(gu16_AD_Result_Hot_Tank_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Tank_Temp >= TEMP_SENSOR_OPEN)
    {
        //����
        Bit2_Front_Led_Hot_Select = CLEAR;
        Bit0_Front_Led_Hot_Temp_1 = CLEAR;
        Bit1_Front_Led_Hot_Temp_2 = CLEAR;
        Bit2_Front_Led_Hot_Temp_3 = CLEAR;
        Bit7_Front_Led_Icon_Hot_Lock = CLEAR;
    }
    /*else if(gu16_AD_Result_Hot_Tank_Temp >= (328 - GAP) && gu16_AD_Result_Hot_Tank_Temp <= (328 + GAP))*/ //3.18k
    else if(gu16_AD_Result_Hot_Tank_Temp >= (512 - GAP) && gu16_AD_Result_Hot_Tank_Temp <= (512 + GAP)) //3.18k
    {
        //1��
        Bit2_Front_Led_Hot_Select = SET;
        Bit0_Front_Led_Hot_Temp_1 = SET;
        Bit1_Front_Led_Hot_Temp_2 = SET;
        Bit2_Front_Led_Hot_Temp_3 = SET;
        Bit7_Front_Led_Icon_Hot_Lock = SET;
    }
    else
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
        Bit0_Front_Led_Hot_Temp_1 = CLEAR;
        Bit1_Front_Led_Hot_Temp_2 = CLEAR;
        Bit2_Front_Led_Hot_Temp_3 = CLEAR;
        Bit7_Front_Led_Icon_Hot_Lock = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit4_Front_Led_Cold_Select = SET;
        Bit3_Front_Led_Cold_Temp_1 = SET;
        Bit4_Front_Led_Cold_Temp_2 = SET;
        Bit5_Front_Led_Cold_Temp_3 = SET;
		return;
	}
	else {}
	
    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)
    {
        //����
        Bit4_Front_Led_Cold_Select = CLEAR;
        Bit3_Front_Led_Cold_Temp_1 = CLEAR;
        Bit4_Front_Led_Cold_Temp_2 = CLEAR;
        Bit5_Front_Led_Cold_Temp_3 = CLEAR;

    }
    else if(gu16_AD_Result_Cold >= (524 - GAP) && gu16_AD_Result_Cold <= (524 + GAP)) //133.54k
    {
        //1��
        Bit4_Front_Led_Cold_Select = SET;
        Bit3_Front_Led_Cold_Temp_1 = SET;
        Bit4_Front_Led_Cold_Temp_2 = SET;
        Bit5_Front_Led_Cold_Temp_3 = SET;

    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
        Bit3_Front_Led_Cold_Temp_1 = CLEAR;
        Bit4_Front_Led_Cold_Temp_2 = CLEAR;
        Bit5_Front_Led_Cold_Temp_3 = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void outdoor_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit1_Front_Led_Ice_Select = SET;
		return;
	}
	else {}
	
    if(gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN)
    {
        //����
        Bit1_Front_Led_Ice_Select = CLEAR;
        /*Bit6_Front_Led_Icon_Ice_Lock = CLEAR;*/
    }
    //else if(gu16_AD_Result_Amb >= (684 - GAP) && gu16_AD_Result_Amb <= (684 + GAP)) //9.42k
    //{
        //1��
    //    Bit3_Status_Low_Level_Test_Mode = SET;
    //}
    else
    {
        Bit1_Front_Led_Ice_Select = SET;
        /*Bit6_Front_Led_Icon_Ice_Lock = SET;*/
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void room_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit3_Front_Led_Ambient_Select = SET;
		return;
	}
	else {}
	
    if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)
    {
        //����
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }         
    else if(gu16_AD_Result_Room >= (524 - GAP) && gu16_AD_Result_Room <= (524 + GAP)) //133.54k
    {
        //ǥ�þ���
        Bit3_Front_Led_Ambient_Select = SET;
    }
    else
    {
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eva1_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit0_Front_Led_Ice_First = SET;
		Bit7_Front_Led_Icon_Ice_First = SET;
		return;
	}
	else {}
	
    if( gu16_AD_Result_Eva_First <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_First >= TEMP_SENSOR_OPEN )
    {
        //����
        Bit0_Front_Led_Ice_First = CLEAR;
		Bit7_Front_Led_Icon_Ice_First = CLEAR;
    }
    else if(gu16_AD_Result_Eva_First >= (512 - GAP) && gu16_AD_Result_Eva_First <= (512 + GAP))
    {
        //ǥ�þ���
        Bit0_Front_Led_Ice_First = SET;
		Bit7_Front_Led_Icon_Ice_First = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_First = CLEAR;
		Bit7_Front_Led_Icon_Ice_First = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eva2_temp(void)
{
	if(F_dbg_Start == SET)
	{
        Bit1_Front_Led_Ice_Lock = SET;
		return;
	}
	else {}
	
    if(gu16_AD_Result_Eva_Second <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_Second >= TEMP_SENSOR_OPEN)
    {
        //����
        Bit1_Front_Led_Ice_Lock = CLEAR;
    }
    else if(gu16_AD_Result_Eva_Second >= (512 - GAP) && gu16_AD_Result_Eva_Second <= (512 + GAP))
    {
        //1��
        Bit1_Front_Led_Ice_Lock = SET;
    }
    else
    {
        Bit1_Front_Led_Ice_Lock = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sensor_test(void)
{
    watertank_low_water();
    watertank_high_water();

    draintank_low_water();
    draintank_high_water();

    /*..hui [20-1-23���� 10:05:12] �����÷ο� ���� �߰�..*/
    ovf_water();

    ice_full();

    water_leak();

    boost_in();
	/*
    if(gu16ADCds < 700)
    {
        Bit3_Front_Led_Eco_Mode = 1;
    }
    else{}
	*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_low_water(void)
{
	if(F_dbg_Start == SET)
	{
        Bit0_Front_Led_Cont = SET;
		return;
	}
	else {}
	
    if(pLEVEL_PURIFY_LOW == SET)
    {
        Bit0_Front_Led_Cont = SET;
		//Bit0_Time_Led_AM = SET;
    }
    else
    {
        Bit0_Front_Led_Cont = CLEAR;
		//Bit0_Time_Led_AM = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_high_water(void)
{
	if(F_dbg_Start == SET)
	{
        Bit1_Front_Led_Pot = SET;
		return;
	}
	else {}
	
    if(pLEVEL_PURIFY_HIGH == SET)
    {
        Bit1_Front_Led_Pot = SET;
		//Bit1_Time_Led_PM = SET;
    }
    else
    {
        Bit1_Front_Led_Pot = CLEAR;
		//Bit1_Time_Led_PM = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void draintank_low_water(void)
{
	if(F_dbg_Start == SET)
	{
        Bit2_Front_Led_2_Cups = SET;
		Bit2_Front_Led_Hot_Lock = SET;
		return;
	}
	else {}
	
    if(pLEVEL_ICE_DRAIN_LOW == SET)
    {
        Bit2_Front_Led_2_Cups = SET;
		Bit2_Front_Led_Hot_Lock = SET;
    }
    else
    {
        Bit2_Front_Led_2_Cups = CLEAR;
		Bit2_Front_Led_Hot_Lock = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void draintank_high_water(void)
{
	if(F_dbg_Start == SET)
	{
        Bit3_Front_Led_1_Cup = SET;
		Bit6_Front_Led_Icon_Save = SET;
		return;
	}
	else {}
	
    if(pLEVEL_ICE_DRAIN_HIGH == SET)
    {
        Bit3_Front_Led_1_Cup = SET;
		Bit6_Front_Led_Icon_Save = SET;
    }
    else
    {
        Bit3_Front_Led_1_Cup = CLEAR;
		Bit6_Front_Led_Icon_Save = CLEAR;		
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ovf_water(void)
{
	if(F_dbg_Start == SET)
	{
        Bit2_Time_Led_Colon = SET;
		return;
	}
	else {}
	
    if(pLEVEL_OVERFLOW == SET)
    {
        //Bit4_Front_Led_ml = SET;
        Bit2_Time_Led_Colon = SET;
    }
    else
    {
        //Bit4_Front_Led_ml = CLEAR;
		Bit2_Time_Led_Colon = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full(void)
{
	if(F_dbg_Start == SET)
	{
		Bit5_Front_Led_My_Cup = SET;
        Bit6_Front_Led_Ice_Full = SET;
		return;
	}
	else {}
	
    /*ICE_IR_POW = 1;*/ /*�������� �߽ź�*/
    pIR_POWER = SET;

    if (gu16ADIceFull >= 230)
    {
        u8icefullcnt++;

        if(u8icefullcnt >= 3)
        {
            u8icefullcnt = 3;
			Bit5_Front_Led_My_Cup = SET;
            Bit6_Front_Led_Ice_Full = SET;
        }
        else{}

    }
    else
    {
        u8icefullcnt = CLEAR;
		Bit5_Front_Led_My_Cup = CLEAR;
        Bit6_Front_Led_Ice_Full = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_leak(void)
{
	if(F_dbg_Start == SET)
	{
        Bit6_Front_Led_half_Cup = SET;
		Bit4_Front_Led_Cold_Temp = SET;
		return;
	}
	else {}
	
    pLEAKAGE_ON = CLEAR;

    if (gu16IceMakingADVal > 750)
    {
        u8leakcnt++;

        if(u8leakcnt >= 3)
        {
            //Bit7_Front_Led_Low_Water = SET;
            Bit6_Front_Led_half_Cup = SET;
			//extra cold�� ���� ���� Ȯ��
			Bit4_Front_Led_Cold_Temp = SET;
        }
        else{}
    }
    else
    {
        u8leakcnt = 0;
        //Bit7_Front_Led_Low_Water = CLEAR;
        Bit6_Front_Led_half_Cup = CLEAR;
		//extra cold�� ���� ���� Ȯ��
		Bit4_Front_Led_Cold_Temp = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void boost_in(void)
{
	if(F_dbg_Start == SET)
	{
        Bit6_Front_Led_Icon_Ice_Lock = SET;
		return;
	}
	else {}
	
    if(pOUT_PUMP_IN == CLEAR)
    {
        Bit6_Front_Led_Icon_Ice_Lock = SET;
    }
    else
    {
        Bit6_Front_Led_Icon_Ice_Lock = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void switch_test(void)
{
	if(F_dbg_Start == SET)
	{
        Bit7_Front_Led_Low_Water = SET;
        Bit5_Front_Led_Percent = SET;
        Bit4_Front_Led_ml = SET;
		return;
	}
	else {}
	
    if(pREED_TANK_COVER == CLEAR)
    {
        Bit7_Front_Led_Low_Water = SET;
    }
    else
    {
        Bit7_Front_Led_Low_Water = CLEAR;
    }

    if(pICE_MICRO_SW_LOW == CLEAR)
    {
        Bit5_Front_Led_Percent = SET;
    }
    else
    {
        Bit5_Front_Led_Percent = CLEAR;
    }
	
    if(pICE_MICRO_SW_HIGH == CLEAR)
    {
        Bit4_Front_Led_ml = SET;
    }
    else
    {
        Bit4_Front_Led_ml = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_test(void)
{
    pVALVE_24V_POWER = SET;

    heater_output();
    comp_fan_output();
    step_motor_teest_output();
    ac_motor_output();

    valve_output_one();
    valve_output_two();

    uv_output();
    pump_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void heater_output(void)
{
    if( gu8_setting_test_input == 1 )
    {
        gu8_hot_heater_on_timer++;

        /*..hui [20-2-26���� 8:25:38] ��ǰ���ε� �׽�Ʈ�Ҽ��ֵ��� 3�ʷ� ����..*/
        if( gu8_hot_heater_on_timer >= 20 )
        {
            gu8_hot_heater_on_timer = 20;
            pHEATER_HOT = 0;
        }
        else
        {
            pHEATER_HOT = 1;
        }
    }
    else
    {
        gu8_hot_heater_on_timer = 0;
        pHEATER_HOT = 0;
    }


    if(gu8_ice_test_input == 1)
    {
        gu8_ice_heater_on_timer++;

        /*..hui [20-2-26���� 8:25:38] ��ǰ���ε� �׽�Ʈ�Ҽ��ֵ��� 3�ʷ� ����..*/
        if( gu8_ice_heater_on_timer >= 30 )
        {
            gu8_ice_heater_on_timer = 30;
            pHEATER_ICE = 0;
        }
        else
        {
            pHEATER_ICE = 1;
        }
    }
    else
    {
        gu8_ice_heater_on_timer = 0;
        pHEATER_ICE = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_fan_output(void)
{
    if(gu8_hot_test_input == 1)
    {
        pCOMP = 1;
        pDC_FAN = 1;
    }
    else
    {
        pCOMP = 0;
        pDC_FAN = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void step_motor_teest_output(void)
{
    F_IceInit = CLEAR;

    ControlGasSwitch();

    if(gu8_ambient_test_input == 0)
    {
        F_IceOpen = 0;
        F_water_ext_step_motor_out_state = CLEAR;

    }
    else
    {
        if(F_water_ext_step_motor_out_state == CLEAR)
        {
            F_water_ext_step_motor_out_state = SET;
            F_IceOpen = 1;

            F_GasSwitch_Initial = CLEAR;
            GasSwitchInit();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ac_motor_output(void)
{
    if(gu8_cold_test_input == 1)
    {
        pMOTOR_ICE_TRAY_CW = SET;
        pMOTOR_ICE_TRAY_CCW = CLEAR;
    }
    else if(gu8_cold_test_input == 2)
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = SET;
    }
    else
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;
    }


    if(gu8_amount_test_input == 1)
    {
        pMOTOR_ICE_OUT_CW = SET;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if(gu8_amount_test_input == 2)
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = SET;
    }
    else
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void valve_output_one(void)
{
    if(gu8_setting_ice_first_test_input == 0)
    {
        pVALVE_NOS = 0;
        pVALVE_FEED = 0;
        gu8_valve_timer_one = 0;
    }
    else
    {
        gu8_valve_timer_one++;

        if( gu8_valve_timer_one >= 5 )
        {
            gu8_valve_timer_one = 5;
            pVALVE_NOS = 1;
            pVALVE_FEED = 1;
        }
        else
        {
            pVALVE_NOS = 0;
            pVALVE_FEED = 1;
        }
    }


    if(gu8_setting_ice_lock_test_input == 1)
    {
        pVALVE_COLD_DRAIN = 1;
    }
    else
    {
        pVALVE_COLD_DRAIN = 0;
    }


    if(gu8_setting_hot_lock_test_input == 1)
    {
        pSWING_BAR = 1;
    }
    else
    {
        pSWING_BAR = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void valve_output_two(void)
{
    if(gu8_setting_eco_mode_test_input == 1)
    {
        pVALVE_HOT_OUT = 1;
    }
    else
    {
        pVALVE_HOT_OUT = 0;
    }


    if(gu8_setting_cold_temp_test_input == 1)
    {
        pVALVE_ROOM_OUT = 1;
        pVALVE_COLD_OUT = 1;
    }
    else
    {
        pVALVE_ROOM_OUT = 0;
        pVALVE_COLD_OUT = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_output(void)
{
	if(F_dbg_Start == SET)
	{
		Bit5_Front_Led_Icon_ice_faucet = SET;
        Bit1_Ice_Tank_UV_12V_Out_State = SET;
        Bit2_Front_Led_Ice_Tank = SET;
        Bit1_Front_Led_Faucet = SET;
        Bit0_Front_Led_UV_Sterilization = SET;
		return;
	}
	else {}
	
    if(gu8_setting_my_cup_test_input == 0)
    {
        pUV_LED_ICE_TANK = CLEAR;
        pUV_LED_WATER_FAUCET = CLEAR;
		Bit5_Front_Led_Icon_ice_faucet = CLEAR;
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
    }
    else
    {
        pUV_LED_ICE_TANK = SET;
        pUV_LED_WATER_FAUCET = SET;
		Bit5_Front_Led_Icon_ice_faucet = SET;
        Bit1_Ice_Tank_UV_12V_Out_State = SET;
    }

    if(gu8_setting_my_cup_test_input != 0)
    {
        /*if(gu16_AD_Result_UV_Faucet_Current >= 10)*/
        /*if(gu16_AD_Result_UV_Faucet_Current >= 200)*/
        /*if(gu16_AD_Result_UV_Faucet_Current >= 40)*/
        if(gu16_AD_Result_UV_Faucet_Current >= 10)
        {
            Bit1_Front_Led_Faucet = SET;
        }
        else
        {
            Bit1_Front_Led_Faucet = CLEAR;
        }
    }
    else
    {
        Bit1_Front_Led_Faucet = CLEAR;
    }
#if 0
if(gu8_ambient_test_input != 0)
    {
        /*if(gu16_AD_Result_UV_Faucet_Current >= 10)*/
        /*if(gu16_AD_Result_UV_Faucet_Current >= 200)*/
        /*if(gu16_AD_Result_UV_Faucet_Current >= 40)*/
        if(gu8_front_uv_ice_faucet_current >= 10)
        {
            Bit5_Front_Led_Icon_ice_faucet = SET;
        }
        else
        {
            Bit5_Front_Led_Icon_ice_faucet = CLEAR;
        }
    }
    else
    {
        Bit5_Front_Led_Icon_ice_faucet = CLEAR;
    }
#endif
	if(gu8_setting_my_cup_test_input != 0)
    {
        if(gu16_AD_Result_UV_Ice_Tank_Current >= 40)
        {
            Bit2_Front_Led_Ice_Tank = SET;
        }
        else
        {
            Bit2_Front_Led_Ice_Tank = CLEAR;
        }
    }
    else
    {
        Bit2_Front_Led_Ice_Tank = CLEAR;
    }

    if( gu8_hot_test_input != 0 )
    {
        if( gu16_AD_Result_Fan_Current >= 10 )
        {
            Bit0_Front_Led_UV_Sterilization = SET;
        }
        else
        {
            Bit0_Front_Led_UV_Sterilization = CLEAR;
        }
    }
    else
    {
        Bit0_Front_Led_UV_Sterilization = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pump_output(void)
{
	if(F_dbg_Start == SET)
	{
        Bit4_Front_Led_Water_Extract = SET;
		
		Bit5_Front_Led_Amount_Select = SET;
        Bit3_Front_Led_Ice_Extract = SET;

		return;
	}
	else {}
	
    if(gu8_water_ext_test_input == 0)
    {
        stop_drain_pump();
        Bit4_Front_Led_Water_Extract = CLEAR;

        pBOOST_PUMP_ON = CLEAR;
    }
    else
    {
        start_drain_pump( DRAIN_PUMP_PWM_MAX );
        Bit4_Front_Led_Water_Extract = SET;

        pBOOST_PUMP_ON = SET;
    }

    if(gu8_water_ext_test_input != 0)
    {
        //������� IAD
        if(gu16_AD_Drain_Pump_Current >= 5 && gu16_AD_Drain_Pump_Current <= 900) //795
        {
            u8_drain_cnt = 0;
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            u8_drain_cnt++;
            if(u8_drain_cnt >= 10)
            {
                u8_drain_cnt = 10;
                 Bit5_Front_Led_Amount_Select = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_drain_cnt = 0;
        Bit5_Front_Led_Amount_Select = CLEAR;
    }


    if(gu8_ice_ext_test_input == 0)
    {
        stop_tray_pump();
        Bit3_Front_Led_Ice_Extract = CLEAR;
    }
    else
    {
        start_tray_pump( DRAIN_PUMP_PWM_MAX );
        Bit3_Front_Led_Ice_Extract = SET;
    }

    if(gu8_ice_ext_test_input != 0)
    {
        if(gu16_AD_Hot_Pump_Current >= 5 && gu16_AD_Hot_Pump_Current <= 900) //795
        {
            u8_hot_p_cnt = 0;
            //Bit4_Front_Led_Cold_Temp = SET;
        }
        else
        {
            u8_hot_p_cnt++;
            if(u8_hot_p_cnt >= 10)
            {
                u8_hot_p_cnt = 10;
                //Bit4_Front_Led_Cold_Temp = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_hot_p_cnt = 0;
        //Bit4_Front_Led_Cold_Temp = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_sensor(void)
{
	if(F_dbg_Start == SET)
	{
        Bit3_Front_Led_Eco_Mode = SET;

		return;
	}
	else {}
    //if(gu8_Flow_1sec >= 10  && gu8_Flow_1sec <= 50)
    //if(gu8_Flow_1sec >= 10)
    //if(gu8_Flow_1sec >= 10  && gu8_Flow_1sec <= 50)
    if(gu8_Flow_1sec >= 10  && gu8_Flow_1sec <= 50)
    {
        gu8_flow_test_timer++;

        if( gu8_flow_test_timer >= 10 )
        {
            gu8_flow_test_timer = 10;
            //Bit6_Front_Led_Auto_Drain = SET;
            Bit3_Front_Led_Eco_Mode = SET;
        }
        else{}
    }
    else
    {
        gu8_flow_test_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_test(void)
{
    pcb_test_mode_uart_test();
    uart_error_display();

    AT_UART_Communication();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_test(void)
{
    if(GetWifiStatusValue(WIFI_STATUS_TEST) == SET)
    {
        Bit3_Led_Wifi_Icon_White = SET;
        //Bit4_Led_Wifi_Icon_Blue = SET;
    }
    else
    {
        //Bit3_Led_Wifi_Icon_White = CLEAR;
        Bit3_Led_Wifi_Icon_White ^= SET;
        //Bit4_Led_Wifi_Icon_Blue ^= SET;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pcb_test_mode_uart_test(void)
{
    if( gu8UARTest_Mode == 0 )
    {
         gu8UARTData[1]= AT_PCB_UART_TEST;

         gu8UART_DataLength = 1;
         AT_F_TxStart = 1;

         gu8UARTest_Mode++;
    }
    else if( gu8UARTest_Mode == 1 )
    {
        //if(AT_F_RxComplete == SET)
        //{

            gu8UARTest_Mode = 0;
        //}
        //else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_error_display(void)
{
	if(F_dbg_Start == SET)
	{
        Bit5_Front_Led_My_Cup = SET;
		return;
	}
	else {}
	
    //Bit8_Status_UV_Ster_Status_Test_Mode = AT_F_RxComplete;

    if( AT_gu8TX_ERROR >= 2)
    {
        //Bit8_Status_UV_Ster_Status_Test_Mode ^= 1;
        //Bit8_Status_UV_Ster_Status_Test_Mode = 1;
        Bit5_Front_Led_My_Cup ^= SET;
    }
    else
    {
        //Bit8_Status_UV_Ster_Status_Test_Mode = AT_F_RxComplete;
        Bit5_Front_Led_My_Cup = AT_F_RxComplete;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PCB_Test_Mode_Key_Short_Input( U16 u16key_input_value)
{
    U8 mu8_return = 0;

    BuzStep(BUZZER_SELECT);

    switch(u16key_input_value)
    {
        case KEY_SETTING_SELECT:
            //
            if( bit_manual_test_start == SET )
            {
                if( gu8_GasSwitch_Mode == 0x00 )
                {
                    gu8_setting_test_input++;
                }
                else
                {
                    BuzStep(BUZZER_ERROR);
                }
            }
            else
            {
                gu8_setting_test_input++;
            }

            if(gu8_setting_test_input >= 2)
            {
                gu8_setting_test_input = 0;
            }
            else{}

        break;

        case KEY_ICE:
            //
            gu8_ice_test_input++;

            if(gu8_ice_test_input >= 2)
            {
                gu8_ice_test_input = 0;
            }
            else{}


        break;

        case KEY_HOT_SELECT:
            //
            gu8_hot_test_input++;

            if(gu8_hot_test_input >= 2)
            {
                gu8_hot_test_input = 0;
            }
            else{}


        break;

        case KEY_AMBIENT_SELECT:
            //
            gu8_ambient_test_input++;

            if(gu8_ambient_test_input >= 2)
            {
                gu8_ambient_test_input = 0;
            }
            else{}


        break;

        case KEY_COLD_SELECT:
            //
            gu8_cold_test_input++;

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                if(gu8_cold_test_input >= 3)
                {
                    gu8_cold_test_input = 0;
                }
                else{}
            }
            else
            {
                if(gu8_cold_test_input >= 2)
                {
                    gu8_cold_test_input = 0;
                }
                else{}
            }


        break;

        case KEY_AMOUNT_SELECT:
            //
            gu8_amount_test_input++;

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                if(gu8_amount_test_input >= 3)
                {
                    gu8_amount_test_input = 0;
                }
                else{}
            }
            else
            {
                if(gu8_amount_test_input >= 2)
                {
                    gu8_amount_test_input = 0;
                }
                else{}
            }


        break;


        case KEY_SETTING_ICE_FIRST:
            //
            gu8_setting_ice_first_test_input++;

            if(gu8_setting_ice_first_test_input >= 2)
            {
                gu8_setting_ice_first_test_input = 0;
            }
            else{}


        break;


        case KEY_SETTING_ICE_LOCK:
            //
            gu8_setting_ice_lock_test_input++;

            if(gu8_setting_ice_lock_test_input >= 2)
            {
                gu8_setting_ice_lock_test_input = 0;
            }
            else{}


        break;

        case KEY_SETTING_HOT_LOCK:
            //
            gu8_setting_hot_lock_test_input++;

            if(gu8_setting_hot_lock_test_input >= 2)
            {
                gu8_setting_hot_lock_test_input = 0;
            }
            else{}


        break;

        case KEY_SETTING_ECO_MODE:
            //
            gu8_setting_eco_mode_test_input++;

            if(gu8_setting_eco_mode_test_input >= 2)
            {
                gu8_setting_eco_mode_test_input = 0;
            }
            else{}


        break;

        case KEY_SETTING_COLD_ENABLE:
            //
            gu8_setting_cold_temp_test_input++;

            if(gu8_setting_cold_temp_test_input >= 2)
            {
                gu8_setting_cold_temp_test_input = 0;
            }
            else{}

        break;

        case KEY_SETTING_MY_CUP:
            //
            gu8_setting_my_cup_test_input++;

            if(gu8_setting_my_cup_test_input >= 2)
            {
                gu8_setting_my_cup_test_input = 0;
            }
            else{}

        break;

        default:
            NOP();
        break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PCB_Test_Mode_Extract_Key_Short_Input(void)
{
     BuzStep(BUZZER_SELECT);

     gu8_water_ext_test_input++;

     if(gu8_water_ext_test_input >= 2)
     {
         gu8_water_ext_test_input = 0;
     }
     else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PCB_Test_Mode_Ice_Key_Short_Input(void)
{
    if(F_Key_IceExtraction == SET)
    {
        if(F_Pcb_Test_Ice_Click != SET)
        {
            F_Pcb_Test_Ice_Click = SET;
            BuzStep(BUZZER_SELECT);

            gu8_ice_ext_test_input++;

            if(gu8_ice_ext_test_input >= 2)
            {
                gu8_ice_ext_test_input = 0;
            }
            else{}
        }
        else{}
    }
    else
    {
        F_Pcb_Test_Ice_Click = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_mode_eeprom_initial(void)
{
    /*..hui [19-10-31���� 11:05:54] �˻� �Ϸ���Ŀ� ���� �����ϵ���..*/
    if(gu8_eeprom_initial_test_input == 1)
    {
        eeprom_initial();
        gu8_eeprom_initial_test_input = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fault_ad_test(void)
{
	if(F_dbg_Start == SET)
	{
        Bit0_Time_Led_AM = SET;
        Bit1_Time_Led_PM = SET;
		return;
	}
	else {}
	
    if( gu16_AD_Result_DC_Current_12V >= 15 )
    {
        //Bit0_Front_Under_Txt_Led_Ice_First = SET;
        Bit0_Time_Led_AM = SET;
    }
    else
    {
        ///////Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
    }

    if( gu16_AD_Result_DC_Current_24V >= 15 )
    {
        //Bit1_Front_Led_Ice_Lock = SET;
        Bit1_Time_Led_PM = SET;
    }
    else
    {
        ///////Bit1_Front_Led_Ice_Lock = CLEAR;
    }
}



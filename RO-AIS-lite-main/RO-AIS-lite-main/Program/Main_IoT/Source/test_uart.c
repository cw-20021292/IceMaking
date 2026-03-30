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
#include    "test_uart.h"

void TestUartStart(void);
void Uart_Test_Main(void);
void motor_test(void);
void test_uart_input(void);
void input_uart_thermistor(void);
void uart_service_sw(void);
void input_uart_flow(void);
void input_uart_level(void);
void input_uart_water_level(void);
void input_uart_drain_level(void);
void input_uart_leakage(void);
void input_uart_ice_sensor(void);
void input_ice_full(void);
void input_drain_pump_ad(void);
void input_hot_pump_ad(void);
void test_uart_ice_tray(void);
void test_ice_heater(void);
void input_uart_uv(void);
void test_uart_gas_switch(void);
void test_ice_system(void);
void initial_ice_tray(void);
void input_manual_test(void);
void manual_test(void);
void test_hot_heater(void);
void uart_mode_display_test(void);
void manual_test_start(void);
void comp_manual_test(void);



TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

U8 gu8R_LEV_H;
U8 gu8R_LEV_L;
U8 gu8Drain_LEV_H;
U8 gu8Drain_LEV_L;
U8 gu8Ovf_LEV;


U8 gu8_test_mode_timeout;
U8 gu8_factory_test_step;

U8 gu8_uart_test_start;


U8 gu8_service_reed_uart_timer;
U8 gu8_service_reed_uart;



U8 gu8_uart_hot_out_temp;
U8 gu8_uart_hot_heater_temp;
U8 gu8_uart_eva_first_temp;
U8 gu8_uart_eva_second_temp;
U8 gu8_uart_amb_temp;
U8 gu8_uart_cold_temp;
U8 gu8_uart_room_temp;

U8 gu8_uart_leakage;

U16 gu16_uart_ir_power_on_ad;
U16 gu16_uart_ir_power_off_ad;

U8 gu8_uart_ir_check_timer;
U8 gu8_uart_ir_off_check_timer;

U16 gu16_uart_dpump_ad;
U8 gu8_uart_dpump_check_timer;

U16 gu16_uart_hpump_ad;
U8 gu8_uart_hpump_check_timer;

U8 gu8_uart_ir_check_timer;


U8 gu8_uart_ice_tray_up;
U8 gu8_uart_ice_trray_down;
U8 gu8_uart_ice_tray_test_step;
U16 gu16_uart_ice_tray_test_timer;

U16 gu16_uart_faucet_uv_ad;
U8 gu8_uart_faucet_uv_check_timer;

U16 gu16_uart_ice_tank_uv_ad;
U8 gu8_uart_ice_tank_uv_check_timer;




U8 gu8_uart_ice_heater;
U8 gu8_uart_ice_heater_timer;
U8 gu8_uart_ice_heater_finish;

U8 gu8_uart_hot_heater;
U8 gu8_uart_hot_heater_timer;
U8 gu8_uart_hot_heater_finish;




U8 gu8AT_Flow_1sec;
U8 gu8_flow_check_start;


U8 gu8_uart_comm_start;

U8 gu8_uart_ice_test_start;
U8 gu8_uart_ice_test_step;
U8 gu8_uart_ice_test_timer;
U8 gu8_uart_ice_result;
U8 gu8_uart_cold_result;
U8 gu8_start_temp_eva_cold;
U8 gu8_start_temp_eva_ice;


U8 gu8_uart_tray_initial;
U8 gu8_uart_tray_initial_step;
U16 gu16_uart_tray_initial_timer;
U8 gu8_uart_tray_finish;

U8 gu8_uart_rtc_initial;

U8 gu8_manual_test_low_level_on_cnt;
U8 gu8_manual_test_low_level_off_cnt;

U8 gu8_manual_test_start;


U16 gu16_uart_dc_fan_ad;

bit bit_flow_detect;
U8 gu8_flow_detect_timer;
bit bit_display_test_finish;
U8 gu8_display_test_delay_timer;

U8 gu8_ice_motor_test_timer;
bit bit_flow_buzzer;


bit bit_testets;

U8 gu8_uart_start_timer;

bit bit_manual_test_start;


U16 gu16_manaul_comp_delay_timer;

bit bit_manual_test_first;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//
void uart_test_mode_decision(void)
{
    /*..hui [17-12-28���� 10:45:49] PCB �׽�Ʈ ��� ���� ���¿����� ���� �Ұ�..*/
    if(gu8_test_mode_timeout == 0 || u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    gu8_uart_start_timer++;

    if( gu8_uart_start_timer >= 30 )
    {
        gu8_uart_start_timer = 30;
    }
    else
    {
        return;
    }

    uart_service_sw();

    /*..hui [23-3-14���� 4:47:45] ������� �����ϱ⶧���� ..*/
    AT_UART_Communication();
    /*UARTest_RUN();*/

    /*..hui [19-11-7���� 9:47:43] �� ���� �Ϸ�� �� ���� �����ϵ��� ����..*/
    /*..hui [20-1-20���� 8:58:56] ���� �д½ð� ����, ���� ���÷��� �Ϸ�� �� ����..*/
    if( /*pLEVEL_PURIFY_LOW != SET //�� Ǯ����� *******
        &&*/ gu8_service_reed_uart == CLEAR
        && gu16IceMakingADVal >= 750
        && F_FW_Version_Display_Mode == SET
        && (gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST || gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST) )
    {
        gu8_uart_test_start = SET;
        TestUartStart();
    }
    else
    {
        gu8_uart_test_start = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void TestUartStart(void)
{
    BuzStep(BUZZER_SELECT);

    UARTest_NO_LOAD_Set();
    AT_gu8TX_ERROR = 0;
    AT_F_Rx_NG = 0;
    gu8_test_mode_timeout = 0;
    gu8_factory_test_step = 0;
    u8FactoryTestMode = UART_TEST_MODE;

    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [19-11-5���� 5:57:28] EEPROM / RTC �ð� �ʱ�ȭ..*/
    gu8_initial_all_data = 1;

    /*..hui [20-1-14���� 8:15:16] 12V ���� ON..*/
    Bit2_Uart_Test_Mode_State = SET;
    bit_sleep_mode_start = CLEAR;

    gu8_uart_ice_heater = CLEAR;
    gu8_uart_ice_heater_finish = CLEAR;
    gu8_uart_hot_heater = CLEAR;
    gu8_uart_hot_heater_finish = CLEAR;

    bit_flow_detect = CLEAR;

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

    gu8_uart_ice_tray_test_step = 0;
    gu16_uart_ice_tray_test_timer = 0;

    F_ErrTrayMotor_DualInital = CLEAR;

	// ���� rtc�� Ȯ��
	gu8_diff_second_prev = gu8_rtc_time_Sec;
	gu8_diff_min_prev = gu8_rtc_time_Min;
	
    /*..hui [23-7-3���� 2:20:40] ���� ��а˻���..*/
    if( bit_manual_test_start == SET )
    {
        gu8_uart_test_mode = INCLUDE_FRNOT_UART_TEST;
        gu8_factory_test_step = 2;
        off_all_control_led();

        GasSwitchInit();

        /*..hui [23-7-6���� 12:34:20] ó���� ���� �ٷ� �����ǰ�..*/
        gu16_manaul_comp_delay_timer = COMP_START_TIME;

        gu8_setting_test_input = 0;
        gu8_ice_test_input = 0;
        gu8_cold_test_input = 0;
        gu8_hot_test_input = 0;

        bit_manual_test_first = SET;
    }
    else{}

    gu16_uart_ir_power_off_ad = 1024;

	//wifi test��� �߰�
	
    /*..hui [21-2-18���� 5:08:19] WIFI ���� �˻� �߰�..*/
    //WifiKey(WIFI_KEY_TEST);
    /*..sean [24-12-24] WIFI �ڵ� ����ȭ�� ���� TEST��� ����..*/
	SetWifiSystemStatus(WIFI_FACTORY_STATUS, SET);
	
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_Test_Main(void)
{
    if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST )
    {
        if( gu8_factory_test_step == 0 )
        {
            uart_mode_display_test();
        }
        else if( gu8_factory_test_step == 1 )
        {
            /*..hui [23-3-15���� 2:28:58] ��� �׽�Ʈ �����ϸ� FND, LED ��ü �� �Ѵ°ɷ�..*/
            /*on_all_control_led();*/
            Bit6_Front_Led_Ice_Full ^= SET;
        }
        else
        {
            if( bit_manual_test_start == CLEAR )
            {
                off_all_control_led();
                Bit6_Front_Led_Ice_Full = SET;
            }
            else
            {
                if( bit_manual_test_first == SET )
                {
                    off_all_control_led();
                    bit_manual_test_first = CLEAR;
                }
                else{}
            }
        }
    }
    else
    {
        off_all_control_led();
        bit_display_test_finish = SET;
    }

    /*..hui [23-3-14���� 5:47:23] ������ �Է�..*/
    test_uart_input();

    /*..hui [23-3-14���� 5:47:39] �˻� �����ϸ� ���̽�Ʈ���� �÷ȴ� ����..*/
    test_uart_ice_tray();

    /*..hui [23-3-14���� 5:47:58] Ż������ ON Ŀ�ǵ� ������� 1ȸ ���� �ִ� 7�ʸ� ON..*/
    test_ice_heater();

    /*..hui [23-3-14���� 5:47:58] �¼����� ON Ŀ�ǵ� ������� 1ȸ ���� �ִ� 7�ʸ� ON..*/
    test_hot_heater();

    /*..hui [23-3-14���� 5:48:41] ���� �� �ð� �׽�Ʈ�� �׺������� �ϴ°ɷ� ����..*/
    /*test_ice_system();*/
    ControlGasSwitch();

    /*..hui [23-3-14���� 5:48:46] EEPROM ����Ÿ �ʱ�ȭ..*/
    initial_all_data();

    /*..hui [22-8-17���� 10:49:14] ��õ���� �����˻��� �߰�..*/
    /*..hui [23-3-22���� 1:35:05] �����˻� ��� ����.. �������.. ������ ���� ������ �ǵ� OPEN��..*/
    /*input_manual_test();*/

	/*.. sean [24-12-23] RTC �˻� �߰� ..*/
	ProcessRtc();
	
    switch(gu8_factory_test_step)
    {
        case 0:

            motor_test();

            /*..hui [22-8-17���� 10:49:14] ��õ���� �����˻��� �߰�..*/
            /*..hui [23-3-22���� 1:35:05] �����˻� ��� ����.. �������.. ������ ���� ������ �ǵ� OPEN��..*/
            /*if( gu8_manual_test_start == SET )
            {
                UARTest_NO_LOAD_Set();
                gu8_factory_test_step = 2;
            }
            else*/

            if(gu8_service_reed_uart == SET && bit_flow_detect == SET && bit_display_test_finish == SET )
            {
                /*..hui [23-3-14���� 5:54:57] ���彺��ġ ���� & �������� 10hz �̻� ����..*/
                BuzStep(BUZZER_SELECT);
                UARTest_NO_LOAD_Set();
                gu8_factory_test_step++;

                F_GasSwitch_Initial = CLEAR;
                GasSwitchInit();

                off_all_control_led();
            }
            else{}

            break;


        case 1:

            AT_UART_Communication();
            UARTest_RUN();

            if(F_Uart_Final == SET)
            {
                UARTest_NO_LOAD_Set();
                gu8_factory_test_step++;
            }
            else{}

            break;

        case 2:

            // ���
            manual_test();
            comp_manual_test();
            fnd_manual_test_mode_();

            break;

        default:

            gu8_factory_test_step = 0;

            break;
    }

    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void motor_test(void)
{
    /*..hui [19-10-28���� 9:23:38] ��� ���� �������� ���� �׽�Ʈ..*/
    if(gu8_uart_comm_start == 1)
    {
        return;
    }
    else{}


    gu8_ice_motor_test_timer++;

    if( gu8_ice_motor_test_timer <= 20 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = SET;
    }
    else if( gu8_ice_motor_test_timer <= 25 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if( gu8_ice_motor_test_timer <= 45 )
    {
        pMOTOR_ICE_OUT_CW = SET;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if( gu8_ice_motor_test_timer <= 50 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else
    {
        gu8_ice_motor_test_timer = 0;
    }

    if( gu16StepMotor2 == 0 )
    {
        F_IceOpen = 1;
    }
    else if (gu16StepMotor2 == STEP_ANGLE2)
    {
        F_IceOpen = 0;
    }
    else{}

    /*..hui [23-3-15���� 2:19:52] ���� ���� �׽�Ʈ�Ҷ� �ð��ҵ� ����..*/
    pDC_FAN = SET;

    if( gu16_AD_Result_Fan_Current > gu16_uart_dc_fan_ad )
    {
        gu16_uart_dc_fan_ad = gu16_AD_Result_Fan_Current;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_input(void)
{
    /*..hui [19-10-23���� 7:56:31] ��ũ Ŀ�� ���彺��ġ ..*/
    /*service_reed_sw_input();*/
    uart_service_sw();

    /*..hui [19-10-28���� 1:13:01] �µ����� �Է�..*/
    /*..hui [23-3-14���� 5:51:17] test_uart_run���� ���� �����°ɷ� ����..*/
    /*input_uart_thermistor();*/

    /*..hui [19-7-22���� 7:36:53] ��������..*/
    calculate_flow_input();
    input_uart_flow();

    input_uart_level();

    /*..hui [19-10-28���� 2:17:55] ���� ���� ����..*/
    input_uart_ice_sensor();

    input_uart_uv();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_thermistor(void)
{
    /*..hui [19-10-28���� 12:21:11] �¼��µ�����..*/
    if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_hot_out_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_hot_out_temp = gu8_Hot_Tank_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:21] �¼� ���� �µ�����..*/
    if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_hot_heater_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_hot_heater_temp = gu8_Hot_Tank_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:28] ����1 �µ�����..*/
    if( gu16_AD_Result_Eva_First >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_First <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_eva_first_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_eva_first_temp = gu8_Eva_Cold_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:33] ����2 �µ�����..*/
    if( gu16_AD_Result_Eva_Second >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_Second <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_eva_second_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_eva_second_temp = gu8_Eva_Ice_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:38] ���� �µ�����..*/
    if( gu16_AD_Result_Amb >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Amb <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_amb_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_amb_temp = gu8_Amb_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:43] �ü� �µ�����..*/
    if( gu16_AD_Result_Cold >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Cold <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_cold_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_cold_temp = gu8_Cold_Temperature_One_Degree;
    }

    /*..hui [19-10-28���� 12:21:48] ���� �µ�����..*/
    if( gu16_AD_Result_Room >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Room <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_room_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_room_temp = gu8_Room_Temperature_One_Degree;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_service_sw(void)
{
    if(pREED_TANK_COVER == CLEAR)
    {
        gu8_service_reed_uart_timer++;

        if(gu8_service_reed_uart_timer >= 2)
        {
            gu8_service_reed_uart_timer = 2;
            /*..hui [19-10-28���� 11:08:54] Ŀ�� ����..*/
            gu8_service_reed_uart = SET;
        }
        else{}
    }
    else
    {
        if(gu8_service_reed_uart_timer > 0)
        {
            gu8_service_reed_uart_timer--;
        }
        else
        {
            gu8_service_reed_uart = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_flow(void)
{
    #if 0
    /*..hui [23-3-14���� 5:52:50] ���� ������ ���Ұ˻� �ϸ鼭 �������� �˻� Ȯ�� ����?..*/
    if(gu8_flow_check_start == 0)
    {
        return;
    }
    else{}
    #endif

    if( gu8_Flow_1sec > gu8AT_Flow_1sec )
    {
        gu8AT_Flow_1sec = gu8_Flow_1sec;
    }
    else{}

    #if 0
    if( gu8_Flow_1sec >= 10 )
    {
        gu8_flow_detect_timer++;

        if( gu8_flow_detect_timer >= 10 )
        {
            gu8_flow_detect_timer = 10;
            bit_flow_detect = SET;
        }
        else{}
    }
    else
    {
        gu8_flow_detect_timer = 0;
    }
    #endif

    if( gu8_Flow_1sec >= 5 )
    {
        gu8_flow_detect_timer++;

        if( gu8_flow_detect_timer >= 5 )
        {
            gu8_flow_detect_timer = 5;
            bit_flow_detect = SET;

            if( bit_flow_buzzer == CLEAR )
            {
                bit_flow_buzzer = SET;
                BuzStep(BUZZER_ERROR);
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_flow_detect_timer = 0;
        bit_flow_buzzer = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_level(void)
{
    /*..hui [19-6-26���� 1:54:08] �������� �Է�..*/
    /*input_water_level();*/
    input_uart_water_level();
    input_uart_drain_level();
    /*..hui [19-10-28���� 1:16:52] �������� �Է�..*/
    input_uart_leakage();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_water_level(void)
{
    if(pLEVEL_PURIFY_HIGH == SET)
    {
        gu8R_LEV_H = 0;
    }
    else
    {
        gu8R_LEV_H = 1;
    }


    if(pLEVEL_PURIFY_LOW == SET)
    {
        gu8R_LEV_L = 0;
    }
    else
    {
        gu8R_LEV_L = 1;
    }

    if( pLEVEL_OVERFLOW == SET )
    {
        gu8Ovf_LEV = 0;
    }
    else
    {
        gu8Ovf_LEV = 1;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_drain_level(void)
{
    if( pLEVEL_ICE_DRAIN_HIGH == SET )
    {
        gu8Drain_LEV_H = 0;
    }
    else
    {
        gu8Drain_LEV_H = 1;
    }

    if( pLEVEL_ICE_DRAIN_LOW == SET )
    {
        gu8Drain_LEV_L = 0;
    }
    else
    {
        gu8Drain_LEV_L = 1;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_leakage(void)
{
    /* 5. ���� ���� - Ŀ���� Short �˻� */
    if( gu16IceMakingADVal < 50 )
    {
        gu8_uart_leakage = 0x00;  // ����
    }
    else
    {
        gu8_uart_leakage = 0x01;  // Short
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_ice_sensor(void)
{
    input_ice_full();
    input_drain_pump_ad();
    input_hot_pump_ad();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_full(void)
{
    #if 0
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*983 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ��Ʈ / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ��Ʈ*/
    /*on / off*/
    /*1023/ 1023*/
    #endif


    //----------------- �������� IR ����------------------------------------
    gu8_uart_ir_check_timer++;

    if(gu8_uart_ir_check_timer >= 70)
    {
        pIR_POWER = CLEAR;
        /*gu8_uart_ir_check_timer = 70;*/

        if( gu8_uart_ir_check_timer >= 90 )
        {
            gu8_uart_ir_check_timer = 90;

            /*..hui [23-11-15���� 1:38:56] �����߽� OFF�ϰ� AD�� üũ(��ƮȮ��)..*/
            gu8_uart_ir_off_check_timer++;

            if( gu8_uart_ir_off_check_timer < 30 )
            {
                /*if( gu16ADIceFull < gu16_uart_ir_power_off_ad )*/
                /*if( gu16ADIceFull > gu16_uart_ir_power_off_ad )*/
                if( gu16ADIceFull < gu16_uart_ir_power_off_ad )
                {
                    gu16_uart_ir_power_off_ad = gu16ADIceFull;
                }
                else{}
            }
            else
            {
                gu8_uart_ir_off_check_timer = 30;
            }
        }
        else
        {
            gu8_uart_ir_off_check_timer = 0;
        }

        return;
    }
    else{}

    pIR_POWER = SET;

    if( gu16ADIceFull > gu16_uart_ir_power_on_ad )
    {
        gu16_uart_ir_power_on_ad = gu16ADIceFull;
    }
    else{}

    gu16_uart_ir_power_off_ad = 1024;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_drain_pump_ad(void)
{
    /*..hui [23-3-24���� 12:15:07] 1��忡���� ��� �����ϴ°ɷ� ����.. ���� ����� ��û..*/
    if(gu8_factory_test_step != 0)
    {
        return;
    }
    else{}

    start_drain_pump( DRAIN_PUMP_PWM_MAX );

    if( gu16_AD_Drain_Pump_Current > gu16_uart_dpump_ad )
    {
        gu16_uart_dpump_ad = gu16_AD_Drain_Pump_Current;
    }
    else{}

    #if 0
    if(gu8_uart_dpump_check_timer >= 50)
    {
        return;
    }
    else{}

    gu8_uart_dpump_check_timer++;

    if(gu8_uart_dpump_check_timer >= 50)
    {
        gu8_uart_dpump_check_timer = 50;
        stop_drain_pump();
    }
    else
    {
        start_drain_pump( DRAIN_PUMP_PWM_MAX );
    }

    if( gu16_AD_Drain_Pump_Current > gu16_uart_dpump_ad )
    {
        gu16_uart_dpump_ad = gu16_AD_Drain_Pump_Current;
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_hot_pump_ad(void)
{
    /*..hui [23-3-24���� 12:15:07] 1��忡���� ��� �����ϴ°ɷ� ����.. ���� ����� ��û..*/
    if(gu8_factory_test_step != 0)
    {
        return;
    }
    else{}

    start_tray_pump( DRAIN_PUMP_PWM_MAX );

    if( gu16_AD_Hot_Pump_Current > gu16_uart_hpump_ad )
    {
        gu16_uart_hpump_ad = gu16_AD_Hot_Pump_Current;
    }
    else{}


    #if 0
    if(gu8_uart_hpump_check_timer >= 50)
    {
        return;
    }
    else{}

    gu8_uart_hpump_check_timer++;

    if(gu8_uart_hpump_check_timer >= 50)
    {
        gu8_uart_hpump_check_timer = 50;
        stop_tray_pump();
    }
    else
    {
        start_tray_pump( DRAIN_PUMP_PWM_MAX );
    }

    if( gu16_AD_Hot_Pump_Current > gu16_uart_hpump_ad )
    {
        gu16_uart_hpump_ad = gu16_AD_Hot_Pump_Current;
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_ice_tray(void)
{
    input_ice_tray_micro_sw();

    if( bit_manual_test_start == SET )
    {
        return;
    }
    else{}

    if( gu8_uart_ice_tray_test_step >= 4 )
    {
        /*..hui [19-11-8���� 5:12:28] Ʈ���� �˻� �Ϸ� �� ���� �˻��Ҷ� Ʈ���� ������������ �̵�..*/
        return;
    }
    else{}

    /*..hui [19-10-28���� 3:06:51] ����ũ�ν���ġ ���� ������ ����..*/
    /*..hui [19-10-28���� 3:08:17] Ʈ���� �˻� �Ϸ�ÿ��� ����..*/
    if( F_ErrTrayMotor_DualInital == SET )
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;
        return;
    }
    else{}

    if( gu8_uart_ice_tray_test_step > 0 )
    {
        gu16_uart_ice_tray_test_timer++;

        /*..hui [19-11-5���� 12:26:04] �ִ� 35�� ����..*/
        if(gu16_uart_ice_tray_test_timer >= 500)
        {
            gu16_uart_ice_tray_test_timer = 0;
            pMOTOR_ICE_TRAY_CW = CLEAR;
            pMOTOR_ICE_TRAY_CCW = CLEAR;
            gu8_uart_ice_tray_test_step = 4;
        }
        else{}
    }
    else{}

    /*..hui [18-2-9���� 1:09:49] CW CCW ���� ���� �� 5�� ��� �� ��ȯ..*/
    inverse_direction_time_check();

    check_error_micro_sw_movement();

    switch( gu8_uart_ice_tray_test_step )
    {
        case 0:

            gu16_uart_ice_tray_test_timer = 0;
            gu8_uart_ice_tray_test_step++;

            break;

        case 1:

            up_tray_motor();
            gu8_uart_ice_tray_test_step++;

            break;

        case 2:

            if(F_TrayMotorCW != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_ice_tray_up = SET;
                down_tray_motor();
                gu8_uart_ice_tray_test_step++;
            }
            else{}

            break;

        case 3:

            if(F_TrayMotorCCW != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            {
                gu8_uart_ice_trray_down = SET;
                gu8_uart_ice_tray_test_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [19-10-28���� 2:40:33] ���⼭ ���..*/
            F_TrayMotorCW = 0;
            F_TrayMotorCCW = 0;

            break;

        default:

            gu8_uart_ice_tray_test_step = 0;

            break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_ice_heater(void)
{
    /*..hui [20-5-11���� 5:38:35] �ѹ��� �����ϵ��� ����..*/
    if(gu8_uart_ice_heater == SET && gu8_uart_ice_heater_finish != SET)
    {
        gu8_uart_ice_heater_timer++;

        if(gu8_uart_ice_heater_timer >= 70)
        {
            pHEATER_ICE = 0;
            gu8_uart_ice_heater_timer = 0;
            gu8_uart_ice_heater = CLEAR;
            gu8_uart_ice_heater_finish = SET;
        }
        else
        {
            pHEATER_ICE = 1;
        }
    }
    else
    {
        pHEATER_ICE = 0;
        gu8_uart_ice_heater_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_uv(void)
{
    if( gu8_factory_test_step != 1 )
    {
        gu8_uart_faucet_uv_check_timer = 0;
        pUV_LED_ICE_TANK = CLEAR;   /*off*/
        pUV_LED_WATER_FAUCET = CLEAR;
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;

        return;
    }
    else{}

    gu8_uart_faucet_uv_check_timer++;

    /*..hui [19-10-28���� 3:13:29] UV������ 3�ʸ�..*/
    if(gu8_uart_faucet_uv_check_timer >= 30)
    {
        gu8_uart_faucet_uv_check_timer = 30;
        pUV_LED_ICE_TANK = CLEAR;   /*off*/
        pUV_LED_WATER_FAUCET = CLEAR;
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
    }
    else
    {
        pUV_LED_ICE_TANK = SET;     /*on*/
        pUV_LED_WATER_FAUCET = SET;
        Bit1_Ice_Tank_UV_12V_Out_State = SET;
    }

    if( gu16_AD_Result_UV_Faucet_Current > gu16_uart_faucet_uv_ad )
    {
        gu16_uart_faucet_uv_ad = gu16_AD_Result_UV_Faucet_Current;
    }
    else{}

    if( gu16_AD_Result_UV_Ice_Tank_Current > gu16_uart_ice_tank_uv_ad )
    {
        gu16_uart_ice_tank_uv_ad = gu16_AD_Result_UV_Ice_Tank_Current;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_gas_switch(void)
{
    if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
    {
        GasSwitchIce();
    }
    else
    {
        GasSwitchInit();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_ice_system(void)
{
    U8 mu8_eva_diff = 0;

    ControlGasSwitch();

    if(gu8_uart_ice_test_start != SET)
    {
        gu8_uart_ice_test_step = 0;
        return;
    }
    else{}


    //gu8_Eva_Cold_Temperature_One_Degree �ü�
    //gu8_Eva_Ice_Temperature_One_Degree ���̽�


    switch( gu8_uart_ice_test_step )
    {
        case 0 :

            if(gu8_GasSwitch_Mode == 0)
            {
                gu8_uart_ice_result = 0;
                gu8_uart_cold_result = 0;
                /*GasSwitchCold();*/
                GasSwitchIce();

                gu8_start_temp_eva_ice = gu8_Eva_Ice_Temperature_One_Degree;
                gu8_uart_ice_test_step++;
            }
            else{}

        break;

        case 1 :

            if(gu8_start_temp_eva_ice > gu8_Eva_Ice_Temperature_One_Degree)
            {
                mu8_eva_diff
                    = (U8)(gu8_start_temp_eva_ice - gu8_Eva_Ice_Temperature_One_Degree);
            }
            else{}

            /*if( mu8_eva_diff >= 2)*/
            if( mu8_eva_diff >= 3)
            {
                gu8_uart_ice_result = 1;
                gu8_uart_ice_test_step++;
            }
            else{}


        break;

        case 2 :

            /*GasSwitchIce();*/
            GasSwitchCold();
            gu8_start_temp_eva_cold = gu8_Eva_Cold_Temperature_One_Degree;
            gu8_uart_ice_test_step++;


        break;

        case 3 :

            if(gu8_start_temp_eva_cold > gu8_Eva_Cold_Temperature_One_Degree)
            {
                mu8_eva_diff
                    = (U8)(gu8_start_temp_eva_cold - gu8_Eva_Cold_Temperature_One_Degree);
            }
            else{}

            /*if( mu8_eva_diff >= 2)*/
            if( mu8_eva_diff >= 3)
            {
                gu8_uart_cold_result = 1;
                gu8_uart_ice_test_step++;
            }
            else{}


        break;

        case 4 :

            //���� �������� COMP ���� �����ϸ� ���
            /*..hui [20-1-17���� 7:27:14] 5�� �߰� ���� �� ���� ����..*/
            gu8_uart_ice_test_timer++;

            if(gu8_uart_ice_test_timer >= 50)
            {
                gu8_uart_ice_test_timer = 0;
                /*..hui [20-3-11���� 4:04:45] ������ ����ñ��� ON ���� ����..*/
                /*pCOMP = 0;*/
                gu8_uart_ice_test_step++;
            }
            else{}

        case 5 :

            //���


        break;

        default :

             gu8_uart_ice_test_step = 0;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tray(void)
{
    input_ice_tray_micro_sw();

    /*..hui [19-11-8���� 4:58:12] ���̽�Ʈ���� �˻� �Ϸ�ñ��� ���..*/
    if( gu8_uart_tray_initial_step >= 3 )
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;

        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
        return;
    }
    else{}

    /*..hui [20-6-10���� 8:23:21] Ʈ���� �ö󰡴� ���� ������� ��ȸ�� ���� �˻� �߰�..*/
    /*pMOTOR_ICE_OUT_CW = SET;*/
    /*pMOTOR_ICE_OUT_CCW = CLEAR;*/

    /*..hui [23-7-3���� 9:07:03] ���÷��� �˻��Ҷ� ��ȸ������ �ٽ� ����.. �������..*/
    pMOTOR_ICE_OUT_CW = CLEAR;
    pMOTOR_ICE_OUT_CCW = SET;



    if( gu8_uart_tray_initial_step > 0 )
    {
        gu16_uart_tray_initial_timer++;

        if(gu16_uart_tray_initial_timer >= 900)
        {
            gu16_uart_tray_initial_timer = 0;
            pMOTOR_ICE_TRAY_CW = CLEAR;
            pMOTOR_ICE_TRAY_CCW = CLEAR;
            gu8_uart_tray_initial_step = 3;
        }
        else{}
    }
    else{}

    /*..hui [18-2-9���� 1:09:49] CW CCW ���� ���� �� 5�� ��� �� ��ȯ..*/
    inverse_direction_time_check();

    check_error_micro_sw_movement();

    switch( gu8_uart_tray_initial_step )
    {
        case 0:

            gu16_uart_tray_initial_timer++;

            if(gu16_uart_tray_initial_timer >= 10)
            {
                gu16_uart_tray_initial_timer = 0;
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 1:

            up_tray_motor();
            gu8_uart_tray_initial_step++;

            break;

        case 2:

            if(F_TrayMotorCW != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [19-10-28���� 2:40:33] ���⼭ ���..*/
            F_TrayMotorCW = 0;
            F_TrayMotorCCW = 0;
            gu8_uart_tray_initial = 0;
            //gu8_uart_tray_finish = 1;

            break;

        default:

            gu8_uart_tray_initial_step = 0;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_manual_test(void)
{
    /*..hui [22-8-17���� 10:49:14] ��õ���� �����˻��� �߰�..*/
    if(pLEVEL_PURIFY_LOW == SET)
    {
        gu8_manual_test_low_level_off_cnt = 0;
        gu8_manual_test_low_level_on_cnt++;

        if( gu8_manual_test_low_level_on_cnt >= 10 )
        {
            gu8_manual_test_low_level_on_cnt = 10;

            if( gu8_manual_test_start  != SET )
            {
                gu8_manual_test_start = SET;
                BuzStep(BUZZER_STERILIZE_END);
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_manual_test_low_level_on_cnt = 0;
        gu8_manual_test_low_level_off_cnt++;

        if( gu8_manual_test_low_level_off_cnt >= 10 )
        {
            gu8_manual_test_low_level_off_cnt = 10;
        }
        else{}
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_test(void)
{
    /*..hui [22-8-18���� 10:44:09] �޴����׽�Ʈ or ��Ű˻� ���� �� FAN ���� ����..*/
    pDC_FAN = SET;

    /*..hui [22-8-19���� 1:32:16] �Լ� �ǵ���� FAN�� �Ѵ°ɷ� ����..*/
    pVALVE_FEED = 1;

    /*..hui [23-3-15���� 4:28:35] NOS ��� ON ���� ���� �߰�..*/
    /*pVALVE_NOS = 1;*/

    #if 0
    pVALVE_ICE_TRAY_IN = 1;

    if( F_Model_Select == MODEL_CHPI )
    {
        pVALVE_HOT_DRAIN = 1;
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_hot_heater(void)
{
    /*..hui [20-5-11���� 5:38:35] �ѹ��� �����ϵ��� ����..*/
    if(gu8_uart_hot_heater == SET && gu8_uart_hot_heater_finish != SET)
    {
        gu8_uart_hot_heater_timer++;

        if(gu8_uart_hot_heater_timer >= 70)
        {
            pHEATER_HOT = 0;
            gu8_uart_hot_heater_timer = 0;
            gu8_uart_hot_heater = CLEAR;
            gu8_uart_hot_heater_finish = SET;
        }
        else
        {
            pHEATER_HOT = 1;
        }
    }
    else
    {
        pHEATER_HOT = 0;
        gu8_uart_hot_heater_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_mode_display_test(void)
{
    led_blink_timer();

    if(gu8_setting_test_input == 1)
    {
        Bit0_Front_Led_Set_Select = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Led_ml = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Led_Percent = F_cds_detect & F_Wink_500ms;
        //Bit6_Front_Led_Auto_Drain = F_cds_detect & F_Wink_500ms;
        Bit7_Front_Led_Low_Water = F_cds_detect & F_Wink_500ms;

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
        bit_ice_test_finish = SET;
    }
    else
    {
        if( bit_ice_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = SET;
            Bit6_Front_Led_Ice_Full = SET;
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
        Bit2_Front_Led_Ice_Tank = F_cds_detect & F_Wink_500ms;

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

        bit_amount_test_finish = SET;
    }
    else
    {
        if( bit_amount_test_finish == CLEAR )
        {
            Bit5_Front_Led_Amount_Select = SET;
            //Bit5_Front_Led_Icon_All_Lock = SET;
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

    fnd_uart_test_mode_();

    /*..hui [19-11-18���� 11:28:17] ����Ʈ LED �� ���� ���¿��� �������� �Է�..*/
    /*..hui [19-11-18���� 12:55:19] Ʈ���� �� �ø����������� ����..*/
    /*..hui [20-2-11���� 5:55:02] ��ũ ���彺��ġ �Է� �߰�.. ������ ��쿡��..*/
    /*..hui [20-2-17���� 3:24:39] Ʈ���̵� ���������� �� �ö��� ��쿡�� �Ϸ�ǵ���..*/
    if( /*gu16ADCds < 780

        &&*/ gu8_front_fnd_thousand == 0
        && gu8_front_fnd_hundred == 0
        && gu8_front_fnd_ten == 0
        && gu8_front_fnd_one == 0

        && gu8_front_extract_uv_led == 0
        && gu8_front_etc_led == 0
        && gu8_front_select_led == 0
        && gu8_front_temp_led == 0
        && gu8_front_setting_led == 0
        && gu8_time_wifi_setting_led == 0

        && gu8_service_reed_uart == SET )
    {
        F_cds_detect = 1;

        gu8_display_test_delay_timer++;

        /*..hui [23-3-15���� 11:02:39] ������������ �˻��ϰ� ��ü 2ȸ ���� �� ��Ű˻� ����..*/
        if( gu8_display_test_delay_timer >= 2 )
        {
            gu8_display_test_delay_timer = 2;
            bit_display_test_finish = SET;
        }
        else{}
    }
    else{}




}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_test_start(void)
{
    if(gu8_test_mode_timeout == 0 || u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    bit_manual_test_start = SET;
    TestUartStart();
    gu16_manaul_comp_delay_timer = COMP_START_TIME;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_manual_test(void)
{
    U8 mu8_test_rps = 0;

    if( bit_manual_test_start == CLEAR )
    {
        return;
    }
    else{}

    initial_ice_tray();

    if( gu8_setting_test_input == 1 && gu16_manaul_comp_delay_timer >= COMP_START_TIME )
    {
        gu16_manaul_comp_delay_timer = COMP_START_TIME;
        Bit0_Front_Led_Set_Select ^= SET;
        pCOMP = SET;
    }
    else
    {
        if( gu8_setting_test_input == 1 )
        {
            gu8_setting_test_input = 0;
            BuzStep(BUZZER_ERROR);
        }
        else{}

        Bit0_Front_Led_Set_Select = CLEAR;

        if( pCOMP == SET )
        {
            gu16_manaul_comp_delay_timer = 0;
            pCOMP = CLEAR;
        }
        else{}

        gu16_manaul_comp_delay_timer++;

        if( gu16_manaul_comp_delay_timer >= COMP_START_TIME )
        {
            gu16_manaul_comp_delay_timer = COMP_START_TIME;
        }
        else{}
    }

    if( gs16_sm_info_target == gs16_sm_info_current )
    {
        if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
        {
            Bit1_Front_Led_Ice_Select = SET;
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )*/
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
            Bit4_Front_Led_Cold_Select = SET;
        }
    }
    else
    {
        Bit1_Front_Led_Ice_Select ^= SET;
        Bit4_Front_Led_Cold_Select ^= SET;
    }



    if( gu8_ice_test_input == 1 )
    {
        GasSwitchIce();
        gu8_ice_test_input = 0;
        gu8_cold_test_input = 0;
        gu8_hot_test_input = 0;
    }
    else{}

    if( gu8_cold_test_input == 1 )
    {
        GasSwitchCold();
        gu8_ice_test_input = 0;
        gu8_cold_test_input = 0;
        gu8_hot_test_input = 0;
    }
    else{}

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





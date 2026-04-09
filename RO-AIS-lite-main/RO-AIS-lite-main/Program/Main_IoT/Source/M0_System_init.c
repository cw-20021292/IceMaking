/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M0_System_init.h"
#include	"WIFI_Config.h"
#include    "api_uart.h"
#include    "api_debug.h"

void System_ini(void);
void Ram_Init(void);
void Variable_Init(void);
void system_reset(void);


bit F_PowerOn;

bit F_System_Init_Finish;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void System_ini(void)
{
    DI();

    R_Systeminit(); // FOTA Projext

    Ram_Init();

    //ADC_Start();

    R_TAU0_Channel0_Start();   /* timer 250us */

    R_TAU0_Channel2_Start();   /* timer 500us */

    R_TAU0_Channel4_Start();   /* masetr pwm - drain pump */

    R_TAU1_Channel2_Start();   /* master pwm - hot pump */

    R_UART0_Start();           /* Hermes */
    R_UART1_Start();           /* Wifi */
    R_UART2_Start();           /* Front */
    R_UART3_Start();           /* Line Test, Pc */

    R_INTC7_Start();           /* Flow Sensor */

    EI();

    Variable_Init();

    Uart_Init();

    dlog(SYSMOD, INFO, ("CLI - System Start \r\n") );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ram_Init(void)
{
    /* ram initialize */
    U32 ram_addr = 0;
    __near U8 *p_ram_addr = 0;

    //for(ram_addr = 0xFCF00; ram_addr < 0xFFE20; ram_addr++)
    // for(ram_addr = 0xFCF00; ram_addr < 0xFFE00; ram_addr++)
    for(ram_addr = 0xFBF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (__near U8 *)ram_addr;
        *p_ram_addr = 0;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Variable_Init(void)
{
    //Delay_MS( 500 );

	/*.. sean [24-10-07] rtc ����ȭ ���� �ð� ����  delay 500 -> 1000..*/
	Delay_MS( 1000 );

    InitRtc();
	
	/*.. sean [24-10-07] rtc ����ȭ ���� �ð� ����  ..*/
	Delay_MS( 50 );

    WifiControlProcess(WIFI_TIME_INI);      ////////////////////////////////

    EEPROM_PRIMARY();

    WifiControlProcess(WIFI_TIME_SET);      ////////////////////////////////



    gu16StepMotor2 = STEP_ANGLE2;                     // Ice Door ���۰��� �ʱ�ȭ
    gu16CompOffDelay = COMP_START_TIME;                 // ���� ��⵿��� 10��

    F_Safety_Routine = 0;
    gu8_IceHeaterControl = 0;
    F_TrayMotorCW = 0;                                // Tray ����
    F_TrayMotorCCW = 0;                               //
    F_IceInit = 1;                                    // ���� �������� ������
    F_IR = 1;                                       // �������� ����

    /*..hui [17-12-27���� 4:35:10] ������ �����Ͼ��� �׳� �׻� ������ ����..*/
    pLEAKAGE_ON = CLEAR;

    InitGasSwitch();

    /*..hui [19-8-1���� 8:49:18] ����Ʈ ��� ����..*/
    F_Front_Tx_Request = SET;

    /*gu8_test_mode_timeout = 30;*/
    gu8_test_mode_timeout = 60;
    u8FactoryTestMode = NONE_TEST_MODE;

    init_before_save_data();
	
    /*..hui [21-9-8���� 3:18:10] ��Ÿ ������ ������ �ȳ���..*/
    if( gu8_fota_start == SET )
    {
        gu8_fota_start = CLEAR;

        /*..hui [24-1-18���� 5:30:03] FOTA �Ϸ� �� BLE Ȱ��ȭ..*/
    }
    else
    {
    	if(F_Mute_Enable == CLEAR)
    	{
			BuzStep(BUZZER_POWER_ON);
    	}
		else
		{
			BuzStep(BUZZER_POWER_ON_MUTE);
		}
    }
	
    initial_self_data();
    init_self_test_auto();

    F_Circul_Drain = SET;
    gu8_uart_test_mode = NON_UART_TEST;

    bit_first_drain = SET;
    gu8_durable_test_start = CLEAR;

    bit_fan_first = CLEAR;

	f_initial_smart_saving = SET;

	/*..hui [23-11-15���� 4:48:49] V13 üũ�� �ȹٲ��� �ʱ�ȭ �߰�..*/
	gu16_uart_ir_power_on_ad = 0;
	gu16_uart_ir_power_off_ad = 0;

    bit_first_time_setting = CLEAR;

	/*..sean [25-03-04] wifi���� �Ǿ��� ���� ���� ǥ�õǵǷ� �ϱ����ؼ� ����..*/
	//gu16_water_return_wifi_time = 70;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void system_reset(void)
{
    DI();

    while(1)
    {
        ;
    }
}




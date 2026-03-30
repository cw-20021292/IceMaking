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

	/*.. sean [24-10-07] rtc 안정화 위한 시간 증가  delay 500 -> 1000..*/
	Delay_MS( 1000 );

    InitRtc();
	
	/*.. sean [24-10-07] rtc 안정화 위한 시간 증가  ..*/
	Delay_MS( 50 );

    WifiControlProcess(WIFI_TIME_INI);      ////////////////////////////////

    EEPROM_PRIMARY();

    WifiControlProcess(WIFI_TIME_SET);      ////////////////////////////////



    gu16StepMotor2 = STEP_ANGLE2;                     // Ice Door 동작각도 초기화
    gu16CompOffDelay = COMP_START_TIME;                 // 컴프 재기동대기 10분

    F_Safety_Routine = 0;
    gu8_IceHeaterControl = 0;
    F_TrayMotorCW = 0;                                // Tray 정지
    F_TrayMotorCCW = 0;                               //
    F_IceInit = 1;                                    // 최초 얼음받이 물공급
    F_IR = 1;                                       // 만빙센서 동작

    /*..hui [17-12-27오후 4:35:10] 스케일 생길일없음 그냥 항상 감지로 변경..*/
    pLEAKAGE_ON = CLEAR;

    InitGasSwitch();

    /*..hui [19-8-1오후 8:49:18] 프론트 통신 시작..*/
    F_Front_Tx_Request = SET;

    /*gu8_test_mode_timeout = 30;*/
    gu8_test_mode_timeout = 60;
    u8FactoryTestMode = NONE_TEST_MODE;

    init_before_save_data();
	
    /*..hui [21-9-8오후 3:18:10] 포타 진행중 부팅음 안나게..*/
    if( gu8_fota_start == SET )
    {
        gu8_fota_start = CLEAR;

        /*..hui [24-1-18오후 5:30:03] FOTA 완료 후 BLE 활성화..*/
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

	/*..hui [23-11-15오후 4:48:49] V13 체크섬 안바껴서 초기화 추가..*/
	gu16_uart_ir_power_on_ad = 0;
	gu16_uart_ir_power_off_ad = 0;

    bit_first_time_setting = CLEAR;

	/*..sean [25-03-04] wifi연결 되었을 때에 물량 표시되되록 하기위해서 변경..*/
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




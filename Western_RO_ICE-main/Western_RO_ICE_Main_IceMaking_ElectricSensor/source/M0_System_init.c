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
#include "Wifi/WifiUser/Western_ICE/WIFI_MonitorFixRAM.h"


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

    /*..hui [21-9-8오후 1:57:51] FOTA 관련.. 이쪽으로 이동..*/
    R_Systeminit();

    Ram_Init();

    //ADC_Start();

    R_TAU0_Channel0_Start();   /* timer 250us */

    R_TAU0_Channel2_Start();   /* timer 500us */

    R_TAU1_Channel0_Start();   /* multi masetr pwm - drain / hot pump */

    R_UART0_Start();           /* Front */
    R_UART1_Start();           /* Wifi */
    R_UART2_Start();           /* BLDC Comp */
    R_UART3_Start();           /* Line Test, Pc */

    /*..hui [24-11-13오후 4:36:12] TDS 삭제..*/
    /*R_INTC4_Start();*/           /* TDS In */
    R_INTC7_Start();           /* Flow Sensor - Filter */
    R_INTC11_Start();          /* Flow Sensor - Tray */

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
    U8 *p_ram_addr = 0;

    #if 0
    for(ram_addr = 0xFCF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }
    #endif

    #if 0
    /*..hui [24-7-17오후 7:51:49] 100SH..*/
    for(ram_addr = 0xFBF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }
    #endif

    for(ram_addr = 0xFAF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Variable_Init(void)
{
    /*Delay_MS( 500 );*/
    /*EEPROM_PRIMARY();*/

    /*Delay_MS( 500 );*/

    Delay_MS( 1000 );

    InitRtc();

    Delay_MS( 50 );

    WifiControlProcess(WIFI_TIME_INI);      ////////////////////////////////

    EEPROM_PRIMARY();

    WifiControlProcess(WIFI_TIME_SET);      ////////////////////////////////

    #if 0
    if( gu8_fota_start == CLEAR )
    {
        BuzStep(BUZZER_POWER_ON);
    }
    else{}
    #endif

    /*gu8_fota_start = CLEAR;*/
    /*Voice_Initialize();*/

    gu16StepMotor2 = STEP_ANGLE2;                     // Ice Door 동작각도 초기화
    gu16CompOffDelay = COMP_START_TIME;                 // 컴프 재기동대기 8분

    F_Safety_Routine = 0;
    gu8_IceHeaterControl = 0;
    F_TrayMotorUP = 0;                                // Tray 정지
    F_TrayMotorDOWN = 0;                               //
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

    off_all_control_led();

    init_before_save_data();

    /*run_init_flow();*/

    /*..hui [23-2-15오전 11:10:25] 순환배수는 디폴트 ON..*/
    F_Circul_Drain = SET;

    /*..hui [23-2-24오후 2:39:34] 냉수 무조건 ON - OFF 기능 없음..*/
    F_Cold_Enable = SET;

    bit_first_drain = SET;
    bit_hot_first_op = CLEAR;

    run_init_ro_drain();


    gu8_animation_time = BREATH_ANIMATION_TIME;
    gu8_animation_duty = BREATH_ANIMATION_DUTY;
    all_breath_stop();
    all_duty_100_percent();

    u32ControlErrors = 0;

    gu8_altutude_setting_timeout = 30;

    gu8_uart_test_mode = NON_UART_TEST;
    bit_manual_test_start = CLEAR;

    /*gu8_fota_start = CLEAR;*/

    /*gu8_periodic_ster_count = PERIODIC__STER_CYCLE;*/
    /*..hui [23-11-8오후 2:33:09] 처음 전원켰을땐 7일후에 하도록..*/
    gu8_periodic_ster_count = FIRST_POWER_ON_PERIODIC__STER_CYCLE;

    bit_temporary_no_operation = CLEAR;

    gu8_wifi_water_select = u8WaterOutState;

    /////gu8_smart_total_no_use_timer_hour = ONE_WEEK_INITIAL_HOUR;
    /*gu8_hot_ster_temp_mode = HOT_STER_TEMP_LOW_MODE;*/

    gu8_durable_test_start = CLEAR;

    /*..hui [23-11-8오후 3:48:54] 얼음 세척은 OFF기능 없음..*/
    bit_periodic_ster_enable = SET;


    bit_self_test_start = CLEAR;

    initial_self_data();
    init_self_test_auto();
    /*gu16_wifi_hot_target_time_min = SELF_TEST_INITIAL_DATA;*/
    gu16_wifi_hot_target_time_min = 0;

    Voice_Initialize();

    /*..hui [24-2-16오전 9:14:20] 필터 주기 적용..*/
    change_filter_period();


    init_acid_clean();
    bit_acid_power_off_check = CLEAR;

    /*..hui [24-11-13오후 4:44:41] TDS 삭제..*/
    /*u16Min_TDS_Out_Data_AD = 1024;*/

    /*..hui [24-11-28오전 9:47:30] UV 고장 테스트 시작..*/
    bit_uv_fault_test_start = SET;

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




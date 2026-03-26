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
void input_tray_pump_ad(void);
void test_uart_ice_tray(void);
void test_ice_heater(void);
void input_uart_uv(void);
void test_uart_gas_switch(void);
void test_ice_system(void);
void initial_ice_tray(void);
void input_manual_test(void);
void manual_test(void);
void test_hot_heater(void);
void input_reed_sw(void);
void test_comp_control(void);
void uart_mode_display_test(void);

void manual_test_start(void);
void comp_manual_test(void);
void check_off_ad(void);
/*void test_tds(void);*/


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

/*U16 gu16_uart_ir_ad;*/
U16 gu16_uart_ir_power_on_ad;
U16 gu16_uart_ir_power_off_ad;

U8 gu8_uart_ir_check_timer;
U8 gu8_uart_ir_off_check_timer;

U16 gu16_uart_drain_pump_on_ad;
U16 gu16_uart_drain_pump_off_ad;

U8 gu8_uart_dpump_check_timer;

U16 gu16_uart_tray_pump_on_ad;
U16 gu16_uart_tray_pump_off_ad;

U8 gu8_uart_hpump_check_timer;

U8 gu8_uart_ir_check_timer;


U8 gu8_uart_ice_tray_up;
U8 gu8_uart_ice_trray_down;
U8 gu8_uart_ice_tray_test_step;
U16 gu16_uart_ice_tray_test_timer;

U8 gu8_uart_uv_check_timer;

U16 gu16_uart_ice_tank_1_2_uv_on_ad;
U16 gu16_uart_water_tank_1_2_uv_on_ad;
U16 gu16_uart_ice_tray_1_2_uv_on_ad;
U16 gu16_uart_ice_tank_3_front_uv_on_ad;

U16 gu16_uart_ice_tank_1_2_uv_off_ad;
U16 gu16_uart_water_tank_1_2_uv_off_ad;
U16 gu16_uart_ice_tray_1_2_uv_off_ad;
U16 gu16_uart_ice_tank_3_front_uv_off_ad;



U8 gu8_uart_ice_heater;
U8 gu8_uart_ice_heater_timer;
U8 gu8_uart_ice_heater_finish;

U8 gu8_uart_hot_heater;
U8 gu8_uart_hot_heater_timer;
U8 gu8_uart_hot_heater_finish;




U8 gu8AT_Tray_Flow_1sec;
U8 gu8AT_Filter_Flow_1sec;

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


U16 gu16_uart_dc_fan_on_ad;
U16 gu16_uart_dc_fan_off_ad;

bit bit_flow_detect;
U8 gu8_flow_detect_timer;
bit bit_display_test_finish;
U8 gu8_display_test_delay_timer;

U8 gu8_ice_motor_test_timer;
bit bit_flow_buzzer;


bit bit_testets;

U8 gu8_uart_start_timer;


bit bit_tank_cover_old;
bit bit_ro_filter_old;
bit bit_filter_cover_old;
bit bit_acid_old;

bit bit_uart_tank_cover_reed;
bit bit_uart_ro_filter_reed;
bit bit_uart_filter_cover_reed;

bit bit_uart_acid_reed_1;
bit bit_uart_acid_reed_final;

bit bit_manual_test_start;


U16 gu16_manaul_comp_delay_timer;

bit bit_manual_test_first;

U8 gu8_check_off_ad_timer;

U8 gu8_eeprom_test_timer;


U16 gu16_uart_test_pulse;

/////U16 gu16_uart_tds_in_max;
/////U16 gu16_uart_tds_out_max;
U8 gu8_uart_bldc_comm_error;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//
void uart_test_mode_decision(void)
{
    /*..hui [17-12-28오후 10:45:49] PCB 테스트 모드 진입 상태에서는 진입 불가..*/
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

    /*..hui [23-3-14오후 4:47:45] 통신으로 시작하기때문에 ..*/
    AT_UART_Communication();

    /*..hui [20-1-20오후 8:58:56] 센서 읽는시간 고려, 버전 디스플레이 완료된 후 진입..*/
    if( gu16ADLeakage >= 750
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
    /*play_melody_select_196();*/
    play_voice_test_mode_151();

    UARTest_NO_LOAD_Set();
    AT_gu8TX_ERROR = 0;
    AT_F_Rx_NG = 0;
    gu8_test_mode_timeout = 0;
    gu8_factory_test_step = 0;
    u8FactoryTestMode = UART_TEST_MODE;

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [19-11-5오후 5:57:28] EEPROM / RTC 시간 초기화..*/
    gu8_initial_all_data = 1;

    /*..hui [20-1-14오후 8:15:16] 12V 전원 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

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
    bit_touch_lock_test_finish = CLEAR;
    bit_steam_off_test_finish = CLEAR;
    bit_eco_test_finish = CLEAR;

    bit_water_extract_test_finish = CLEAR;
    bit_ice_extract_test_finish = CLEAR;


    gu8_uart_ice_tray_test_step = 0;
    gu16_uart_ice_tray_test_timer = 0;
    gu8_eeprom_test_timer = 0;

    F_ErrTrayMotor_DualInital = CLEAR;

    /*..hui [21-2-18오후 5:08:19] WIFI 공장 검사 추가..*/
    WifiKey(WIFI_KEY_TEST);

    gu8_uart_comp_start = 0;
    gu8_uart_comp_rps = 0;

    all_breath_stop();

    /*..hui [23-7-3오후 2:20:40] 수동 기밀검사모드..*/
    if( bit_manual_test_start == SET )
    {
        gu8_uart_test_mode = INCLUDE_FRNOT_UART_TEST;
        gu8_factory_test_step = 2;
        off_all_control_led();

        GasSwitchInit();

        /*..hui [23-7-6오후 12:34:20] 처음엔 컴프 바로 가동되게..*/
        gu16_manaul_comp_delay_timer = COMP_START_TIME;

        gu8_setting_test_input = 0;
        gu8_ice_test_input = 0;
        gu8_cold_test_input = 0;
        gu8_hot_test_input = 0;

        bit_manual_test_first = SET;
    }
    else{}

    gu16_uart_ir_power_off_ad = 1024;

    gu16_uart_ice_tank_1_2_uv_off_ad = 1024;
    gu16_uart_water_tank_1_2_uv_off_ad = 1024;
    gu16_uart_ice_tray_1_2_uv_off_ad = 1024;
    gu16_uart_ice_tank_3_front_uv_off_ad = 1024;

    gu16_uart_drain_pump_off_ad = 1024;
    gu16_uart_tray_pump_off_ad = 1024;
    gu16_uart_dc_fan_off_ad = 1024;

    gu8AT_Tray_Flow_1sec = 0;

    #if 0
    /*..hui [24-11-13오후 4:00:55] 드레인 전압 삭제..*/
    /*..hui [24-7-26오후 5:39:25] 드레인 수위센서 전원 항상 킴..*/
    pPower_Drain_Level = CLEAR;
    bit_drain_level_power_output = SET;
    #endif

    gu8_uart_bldc_comm_error = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_Test_Main(void)
{
    all_breath_stop();
    //all_dimming_full_on();
    all_duty_100_percent();

    if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST )
    {
        if( gu8_factory_test_step == 0 )
        {
            uart_mode_display_test();
        }
        else if( gu8_factory_test_step == 1 )
        {
            /*..hui [23-3-15오후 2:28:58] 통신 테스트 시작하면 FND, LED 전체 다 켜는걸로..*/
            /*on_all_control_led();*/
            Bit5_Front_Under_Led_Ice_Full ^= SET;
            fnd_left_uart_test();
            fnd_right_uart_test();
        }
        else
        {
            if( bit_manual_test_start == CLEAR )
            {
                off_all_control_led();
                Bit5_Front_Under_Led_Ice_Full = SET;
                fnd_left_uart_test();
                fnd_right_uart_test();
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
        /*off_all_control_led();*/
        fnd_left_uart_test();
        fnd_right_uart_test();
        bit_display_test_finish = SET;
    }

    /*..hui [23-3-14오후 5:47:23] 센서류 입력..*/
    test_uart_input();

    /*..hui [23-3-14오후 5:47:39] 검사 시작하면 아이스트레이 올렸다 내림..*/
    test_uart_ice_tray();

    /*..hui [23-3-14오후 5:47:58] 탈빙히터 ON 커맨드 날라오면 1회 한전 최대 7초만 ON..*/
    //////test_ice_heater();

    /*..hui [23-3-14오후 5:47:58] 온수히터 ON 커맨드 날라오면 1회 한전 최대 7초만 ON..*/
    test_hot_heater();

    /*..hui [23-3-14오후 5:48:41] 제빙 및 냉각 테스트는 테블릿에서 하는걸로 변경..*/
    /*test_ice_system();*/
    ControlGasSwitch();

    /*..hui [23-3-14오후 5:48:46] EEPROM 데이타 초기화..*/
    initial_all_data();

    /*..hui [22-8-17오전 10:49:14] 인천공장 수동검사모드 추가..*/
    /*..hui [23-3-22오후 1:35:05] 수동검사 모드 삭제.. 설차장님.. 어차피 전원 켜지면 피드 OPEN됨..*/
    /*input_manual_test();*/

    gu8_eeprom_test_timer++;

    if( gu8_eeprom_test_timer >= 20 )
    {
        gu8_eeprom_test_timer = 20;
        eeprom_test();
    }
    else{}

    /*..hui [19-7-22오후 7:36:53] 유량센서..*/
    calculate_tray_flow_input();
    calculate_filter_flow_input();
    input_uart_flow();

    ControlRoDrain();
    /*ControlMixFlow();*/

    test_comp_control();

    /*..hui [24-11-13오후 4:09:51] TDS 삭제..*/
    /*test_tds();*/

    switch(gu8_factory_test_step)
    {
        case 0:

            motor_test();

            /*..hui [23-6-30오후 3:35:13] 탱크커버, RO필터 OFF->ON되고 디스플레이 검사 완료..*/
            /*..hui [23-11-16오전 9:14:28] 누수센서 조건 추가.. 누수 커넥터 연결된채로 생산될수있음..*/
            /*if( bit_uart_tank_cover_reed == SET && bit_uart_ro_filter_reed == SET
                && bit_display_test_finish == SET && gu16ADLeakage < 50)*/
            /*..hui [23-12-8오후 4:29:23] RO필터는 디스플레이 검사에서 확인.. 탑커버, 누수센서 미감지 두개만 봄..*/
            /*..hui [23-12-11오전 10:54:07] 트레이 입수 유량센서도 추가..*/
            /*if( bit_uart_tank_cover_reed == SET && bit_display_test_finish == SET && gu16ADLeakage < 50 && bit_flow_detect == SET )*/
            /*..hui [24-7-18오후 3:55:20] 구연산 리드 상태 추가..*/
            /*..hui [24-7-18오후 3:55:34] 미감지 -> 감지 -> 미감지로 돼야함..*/
            /*if( bit_uart_tank_cover_reed == SET && bit_display_test_finish == SET
                && gu16ADLeakage < 50 && bit_flow_detect == SET && bit_uart_acid_reed_final == SET && pREED_ACID == SET )*/
            /*..hui [24-8-12오후 2:30:21] 유량 감지 조건 삭제.. 검사기술팀 요청..*/
            if( bit_uart_tank_cover_reed == SET && bit_display_test_finish == SET
                && gu16ADLeakage < 50 && bit_uart_acid_reed_final == SET && pREED_ACID == SET )
            {
                play_melody_select_196();
                UARTest_NO_LOAD_Set();
                gu8_factory_test_step++;

                F_GasSwitch_Initial = CLEAR;
                GasSwitchInit();

                off_all_control_led();
                gu8_check_off_ad_timer = 0;
            }
            else{}

            break;


        case 1:

            check_off_ad();
            AT_UART_Communication();
            UARTest_RUN();

            if(F_Uart_Final == SET)
            {
                UARTest_NO_LOAD_Set();
                off_all_control_led();
                gu8_factory_test_step++;
            }
            else{}

            break;

        case 2:

            // 대기
            manual_test();
            comp_manual_test();
            fnd_left_uart_test();
            fnd_right_uart_test();

            break;

        default:

            gu8_factory_test_step = 0;

            break;
    }

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void motor_test(void)
{
    /*..hui [19-10-28오후 9:23:38] 통신 시작 전까지만 육안 테스트..*/
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

    /*..hui [23-12-15오전 9:30:33] 1모드에서 트레이 입수밸브 ON 추가.. 설희석 차장님 요청..*/
    pVALVE_ICE_TRAY_IN_FEED = SET;


    /*..hui [23-3-15오후 2:19:52] 모터 육안 테스트할때 냉각팬도 가동..*/
    pDC_FAN = SET;

    if( gu16_AD_Result_Fan_Current > gu16_uart_dc_fan_on_ad )
    {
        gu16_uart_dc_fan_on_ad = gu16_AD_Result_Fan_Current;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_input(void)
{
    /*..hui [19-10-23오후 7:56:31] 탱크 커버 리드스위치 ..*/
    uart_service_sw();

    input_uart_level();

    /*..hui [19-10-28오후 2:17:55] 제빙 관련 센서..*/
    input_uart_ice_sensor();

    input_uart_uv();

    input_reed_sw();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_thermistor(void)
{
    #if 0
    /*..hui [19-10-28오후 12:21:11] 온수온도센서..*/
    if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_hot_out_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_hot_out_temp = gu8_Hot_Tank_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:21] 온수 히터 온도센서..*/
    if( gu16_AD_Result_Hot_Tank_Temp >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Hot_Tank_Temp <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_hot_heater_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_hot_heater_temp = gu8_Hot_Tank_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:28] 에바1 온도센서..*/
    if( gu16_AD_Result_Eva_First >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_First <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_eva_first_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_eva_first_temp = gu8_Eva_Cold_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:33] 에바2 온도센서..*/
    if( gu16_AD_Result_Eva_Second >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Eva_Second <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_eva_second_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_eva_second_temp = gu8_Eva_Ice_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:38] 주위 온도센서..*/
    if( gu16_AD_Result_Amb >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Amb <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_amb_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_amb_temp = gu8_Amb_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:43] 냉수 온도센서..*/
    if( gu16_AD_Result_Cold >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Cold <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_cold_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_cold_temp = gu8_Cold_Temperature_One_Degree;
    }

    /*..hui [19-10-28오후 12:21:48] 정수 온도센서..*/
    if( gu16_AD_Result_Room >= TEMPERATURE_SENSOR_OPEN
        || gu16_AD_Result_Room <= TEMPERATURE_SENSOR_SHORT )
    {
        gu8_uart_room_temp = UART_TEMP_SENSOR_ERROR;
    }
    else
    {
        gu8_uart_room_temp = gu8_Room_Temperature_One_Degree;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_service_sw(void)
{
    if( pREED_TANK_COVER == CLEAR )
    {
        gu8_service_reed_uart_timer++;

        if(gu8_service_reed_uart_timer >= 2)
        {
            gu8_service_reed_uart_timer = 2;
            /*..hui [19-10-28오전 11:08:54] 커버 닫힘..*/
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
    if( gu8_factory_test_step != 1 )
    {
        return;
    }
    else{}
    #endif

    /*..hui [23-12-8오후 4:37:31] 1모드, 2모드 모두 확인.. 설희석 차장님..*/
    if( gu8_factory_test_step == 2 )
    {
        return;
    }
    else{}

    if( gu8_Tray_Flow_1sec > gu8AT_Tray_Flow_1sec )
    {
        gu8AT_Tray_Flow_1sec = gu8_Tray_Flow_1sec;
    }
    else{}

    if( gu8_Filter_Flow_1sec > gu8AT_Filter_Flow_1sec )
    {
        gu8AT_Filter_Flow_1sec = gu8_Filter_Flow_1sec;
    }
    else{}


    /*if( gu8_Tray_Flow_1sec >= 5 )*/
    if( gu8AT_Tray_Flow_1sec >= 5 )
    {
        gu8_flow_detect_timer++;

        if( gu8_flow_detect_timer >= 1 )
        {
            gu8_flow_detect_timer = 1;
            bit_flow_detect = SET;

            if( bit_flow_buzzer == CLEAR )
            {
                bit_flow_buzzer = SET;
                play_melody_warning_197();
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
    /*..hui [19-6-26오후 1:54:08] 수위센서 입력..*/
    /*input_water_level();*/
    input_uart_water_level();
    input_uart_drain_level();
    /*..hui [19-10-28오후 1:16:52] 누수센서 입력..*/
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
    /* 5. 누수 센서 - 커넥터 Short 검사 */
    if( gu16ADLeakage < 50 )
    {
        gu8_uart_leakage = 0x00;  // 정상
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
    input_tray_pump_ad();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_full(void)
{
    #if 0
    /*발신 정상 / 수신 정상*/
    /*on / off*/
    /*983 / 0*/
    /*발신 오픈 / 수신 정상*/
    /*on / off*/
    /*0 / 0*/
    /*발신 쇼트 / 수신 정상*/
    /*on / off*/
    /*0 / 0*/
    /*발신 정상 / 수신 오픈*/
    /*on / off*/
    /*0 / 0*/
    /*발신 정상 / 수신 쇼트*/
    /*on / off*/
    /*1023/ 1023*/
    #endif


    //----------------- 만빙센서 IR 동작------------------------------------
    gu8_uart_ir_check_timer++;

    if(gu8_uart_ir_check_timer >= 70)
    {
        pIR_POWER = CLEAR;
        /*gu8_uart_ir_check_timer = 70;*/

        if( gu8_uart_ir_check_timer >= 90 )
        {
            gu8_uart_ir_check_timer = 90;

            /*..hui [23-11-15오후 1:38:56] 만빙발신 OFF하고 AD값 체크(쇼트확인)..*/
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
    /*..hui [23-3-24오후 12:15:07] 1모드에서는 계속 가동하는걸로 변경.. 설희석 차장님 요청..*/
    if(gu8_factory_test_step != 0)
    {
        return;
    }
    else{}

    start_drain_pump( PUMP_PWM_MAX );

    if( gu16_AD_Drain_Pump_Current > gu16_uart_drain_pump_on_ad )
    {
        gu16_uart_drain_pump_on_ad = gu16_AD_Drain_Pump_Current;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_tray_pump_ad(void)
{
    /*..hui [23-3-24오후 12:15:07] 1모드에서는 계속 가동하는걸로 변경.. 설희석 차장님 요청..*/
    if(gu8_factory_test_step != 0)
    {
        return;
    }
    else{}

    start_tray_pump( PUMP_PWM_MAX );

    if( gu16_AD_Tray_Pump_Current > gu16_uart_tray_pump_on_ad )
    {
        gu16_uart_tray_pump_on_ad = gu16_AD_Tray_Pump_Current;
    }
    else{}


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
        /*..hui [19-11-8오후 5:12:28] 트레이 검사 완료 후 제빙 검사할때 트레이 제빙방향으로 이동..*/
        return;
    }
    else{}

    /*..hui [19-10-28오후 3:06:51] 마이크로스위치 동시 감지시 정지..*/
    /*..hui [19-10-28오후 3:08:17] 트레이 검사 완료시에도 정지..*/
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

        /*..hui [19-11-5오후 12:26:04] 최대 35초 제한..*/
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

    /*..hui [18-2-9오후 1:09:49] CW CCW 방향 변경 시 5초 대기 후 전환..*/
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

            if(F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_ice_tray_up = SET;
                down_tray_motor();
                gu8_uart_ice_tray_test_step++;
            }
            else{}

            break;

        case 3:

            if(F_TrayMotorDOWN != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            {
                gu8_uart_ice_trray_down = SET;
                gu8_uart_ice_tray_test_step++;
            }
            else{}

            break;

        case 4:

            /*..hui [19-10-28오후 2:40:33] 여기서 대기..*/
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;

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
    #if 0
    /*..hui [20-5-11오후 5:38:35] 한번만 동작하도록 개선..*/
    if(gu8_uart_ice_heater == SET && gu8_uart_ice_heater_finish != SET)
    {
        gu8_uart_ice_heater_timer++;

        if(gu8_uart_ice_heater_timer >= 70)
        {
            //pHEATER_ICE = 0;
            gu8_uart_ice_heater_timer = 0;
            gu8_uart_ice_heater = CLEAR;
            gu8_uart_ice_heater_finish = SET;
        }
        else
        {
            //pHEATER_ICE = 1;
        }
    }
    else
    {
        //pHEATER_ICE = 0;
        gu8_uart_ice_heater_timer = 0;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_uv(void)
{
    if( gu8_factory_test_step == 0 || gu8_factory_test_step == 2 )
    {
        gu8_uart_uv_check_timer = 0;
        pUV_LED_ICE_TANK_1_2_BACK = CLEAR;
        pUV_LED_WATER_TANK_1_2 = CLEAR;
        pUV_LED_ICE_TRAY_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3_FRONT = CLEAR;
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;

        /*..hui [23-12-8오후 5:44:40] 1모드에서 UV류 OFF했을때 AD값 저장..*/
        if( gu8_factory_test_step == 0 )
        {
            if( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current < gu16_uart_ice_tank_1_2_uv_off_ad )
            {
                gu16_uart_ice_tank_1_2_uv_off_ad = gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
            }
            else{}

            if( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed < gu16_uart_water_tank_1_2_uv_off_ad )
            {
                gu16_uart_water_tank_1_2_uv_off_ad = gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
            }
            else{}

            if( gu16_AD_Result_UV_Ice_Tray_1_2_Current < gu16_uart_ice_tray_1_2_uv_off_ad )
            {
                gu16_uart_ice_tray_1_2_uv_off_ad = gu16_AD_Result_UV_Ice_Tray_1_2_Current;
            }
            else{}

            if( gu16_AD_Result_UV_Ice_Tank_3_Front_Current < gu16_uart_ice_tank_3_front_uv_off_ad )
            {
                gu16_uart_ice_tank_3_front_uv_off_ad = gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
            }
            else{}
        }
        else{}

        return;
    }
    else{}

    gu8_uart_uv_check_timer++;

    /*..hui [19-10-28오후 3:13:29] UV센서는 3초만..*/
    if(gu8_uart_uv_check_timer >= 30)
    {
        gu8_uart_uv_check_timer = 30;
        pUV_LED_ICE_TANK_1_2_BACK = CLEAR;
        pUV_LED_WATER_TANK_1_2 = CLEAR;
        pUV_LED_ICE_TRAY_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3_FRONT = CLEAR;
        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;
    }
    else
    {
        pUV_LED_ICE_TANK_1_2_BACK = SET;
        pUV_LED_WATER_TANK_1_2 = SET;
        pUV_LED_ICE_TRAY_1_2 = SET;
        pUV_LED_ICE_TANK_3_FRONT = SET;
        Bit1_Ice_Tank_UV_12V_Out_State = SET;
    }

    if( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current > gu16_uart_ice_tank_1_2_uv_on_ad )
    {
        gu16_uart_ice_tank_1_2_uv_on_ad = gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current;
    }
    else{}

    if( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed > gu16_uart_water_tank_1_2_uv_on_ad )
    {
        gu16_uart_water_tank_1_2_uv_on_ad = gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed;
    }
    else{}

    if( gu16_AD_Result_UV_Ice_Tray_1_2_Current > gu16_uart_ice_tray_1_2_uv_on_ad )
    {
        gu16_uart_ice_tray_1_2_uv_on_ad = gu16_AD_Result_UV_Ice_Tray_1_2_Current;
    }
    else{}

    if( gu16_AD_Result_UV_Ice_Tank_3_Front_Current > gu16_uart_ice_tank_3_front_uv_on_ad )
    {
        gu16_uart_ice_tank_3_front_uv_on_ad = gu16_AD_Result_UV_Ice_Tank_3_Front_Current;
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

    #if 0
    ControlGasSwitch();

    if(gu8_uart_ice_test_start != SET)
    {
        gu8_uart_ice_test_step = 0;
        return;
    }
    else{}


    //gu8_Eva_Cold_Temperature_One_Degree 냉수
    //gu8_Eva_Ice_Temperature_One_Degree 아이스


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

            //제빙 방향으로 COMP 지속 가동하며 대기
            /*..hui [20-1-17오후 7:27:14] 5초 추가 가동 후 컴프 종료..*/
            gu8_uart_ice_test_timer++;

            if(gu8_uart_ice_test_timer >= 50)
            {
                gu8_uart_ice_test_timer = 0;
                /*..hui [20-3-11오후 4:04:45] 컴프는 종료시까지 ON 상태 유지..*/
                /*pCOMP = 0;*/
                gu8_uart_ice_test_step++;
            }
            else{}

        case 5 :

            //대기


        break;

        default :

             gu8_uart_ice_test_step = 0;

        break;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tray(void)
{
    input_ice_tray_micro_sw();

    /*..hui [19-11-8오후 4:58:12] 아이스트레이 검사 완료시까지 대기..*/
    if( gu8_uart_tray_initial_step >= 3 )
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;

        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
        return;
    }
    else{}

    /*..hui [20-6-10오후 8:23:21] 트레이 올라가는 동안 추출모터 역회전 육안 검사 추가..*/
    /*pMOTOR_ICE_OUT_CW = SET;*/
    /*pMOTOR_ICE_OUT_CCW = CLEAR;*/

    /*..hui [23-6-30오전 11:10:15] 역회전 -> 정회전으로 변경.. 설차장님..*/
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

    /*..hui [18-2-9오후 1:09:49] CW CCW 방향 변경 시 5초 대기 후 전환..*/
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

            if(F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [19-10-28오후 2:40:33] 여기서 대기..*/
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
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
    /*..hui [22-8-17오전 10:49:14] 인천공장 수동검사모드 추가..*/
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
                //////BuzStep(BUZZER_STERILIZE_END);
                play_melody_setting_on_198();
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
    pVALVE_24V_POWER = SET;

    /*..hui [22-8-18오전 10:44:09] 메뉴얼테스트 or 통신검사 종료 후 FAN 지속 가동..*/
    pDC_FAN = SET;

//////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-12-8오후 4:59:18] 입수 FEED 개방..*/
    pVALVE_FEED = SET;
    /*..hui [23-12-8오후 5:00:08] 오버히팅 NOS 차단..*/
    pVALVE_OVERHEATING_NOS = SET;
    /*..hui [23-12-8오후 5:00:19] 고온세척 입수 개방..*/
    pVALVE_HOT_IN_FEED = SET;
    /*..hui [23-12-8오후 5:00:30] 트레이 입수 개방..*/
    pVALVE_ICE_TRAY_IN_FEED = SET;

//////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-12-8오후 4:59:12] 입수 NOS 개방..*/
    pVALVE_NOS = CLEAR;
    /*..hui [23-12-8오후 5:00:51] 냉수 추출 차단..*/
    pVALVE_COLD_OUT = CLEAR;
    /*..hui [23-12-8오후 5:00:55] 온수 추출 차단..*/
    pVALVE_HOT_OUT = CLEAR;
    /*..hui [23-12-8오후 5:01:08] 냉수 배수밸브 차단..*/
    pVALVE_COLD_DRAIN = CLEAR;
    /*..hui [23-12-8오후 5:01:16] 얼음살균L 차단..*/
    pVALVE_ICE_TANK_STER_FEED_LEFT = CLEAR;
    /*..hui [23-12-8오후 5:01:21] 얼음살균R 차단..*/
    pVALVE_ICE_TANK_STER_FEED_RIGHT = CLEAR;
    /*..hui [23-12-8오후 5:01:29] 에어밸브 차단..*/
    pVALVE_AIR_VENT = CLEAR;
    /*..hui [23-12-8오후 5:01:34] 미온수추출 차단..*/
    pVALVE_ROOM_OUT = CLEAR;

//////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-6-30오후 3:49:45] 유로전환밸브 = 드레인방향..*/
    /*..hui [23-12-8오후 5:05:16] 유로전환 FEED 개방..*/
    pVALVE_FLUSHING_FEED = SET;
    /*..hui [23-12-8오후 5:05:06] 유로전환 NOS 차단..*/
    pVALVE_FLUSHING_NOS = SET;

    /*..hui [23-6-30오후 4:08:47] RO 드레인 모터 풀 개방..*/
    if( gu8_ro_drain_status == RO_DRAIN_STATUS_CLOSE )
    {
        run_open_ro_drain();
    }
    else{}

    /*..hui [23-9-18오후 5:28:13] 냉수 믹싱 모터 삭제..*/
    #if 0
    /*..hui [23-6-30오후 4:08:54] 믹싱모터 풀 개방..*/
    if( gu8_hot_flow_status != HOT_FLOW_MAX_OPEN )
    {
        run_increase_flow(MAX_INCREASE_FLOW);
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
    /*..hui [20-5-11오후 5:38:35] 한번만 동작하도록 개선..*/
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
void input_reed_sw(void)
{
    if( gu8_factory_test_step != 0 )
    {
        return;
    }
    else{}

    /*..hui [21-10-6오후 7:48:43] 감지..*/
    if( pREED_TANK_COVER == CLEAR )
    {
        if( bit_tank_cover_old == SET )
        {
            bit_tank_cover_old = CLEAR;

            /*..hui [21-10-6오후 7:50:14] 미감지 -> 감지로 변경된 경우에만 정상..*/
            bit_uart_tank_cover_reed = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_tank_cover_old == CLEAR )
        {
            bit_tank_cover_old = SET;
            play_melody_warning_197();
        }
        else{}
    }

    /*..hui [21-10-6오후 7:48:43] 감지..*/
    if( pREED_ACID == CLEAR )
    {
        if( bit_acid_old == SET )
        {
            bit_acid_old = CLEAR;

            /*..hui [24-7-18오후 3:53:52] 미감지 -> 감지로 상태 변화..*/
            bit_uart_acid_reed_1 = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_acid_old == CLEAR )
        {
            bit_acid_old = SET;
            play_melody_warning_197();

            if( bit_uart_acid_reed_1 == SET )
            {
                /*..hui [24-7-18오후 3:54:34] 감지 됐다가 다시 미감지로 돼야함..*/
                bit_uart_acid_reed_final = SET;
            }
            else{}
        }
        else{}
    }


    /*..hui [21-10-6오후 7:48:43] 감지..*/
    if( pREED_RO_2_FILTER == CLEAR )
    {
        if( bit_ro_filter_old == SET )
        {
            bit_ro_filter_old = CLEAR;

            /*..hui [21-10-6오후 7:50:14] 미감지 -> 감지로 변경된 경우에만 정상..*/
            bit_uart_ro_filter_reed = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_ro_filter_old == CLEAR )
        {
            bit_ro_filter_old = SET;
            play_melody_warning_197();
        }
        else{}
    }

    /*..hui [21-10-6오후 7:48:43] 감지..*/
    if( pREED_FILTER_COVER == CLEAR )
    {
        if( bit_filter_cover_old == SET )
        {
            bit_filter_cover_old = CLEAR;

            /*..hui [21-10-6오후 7:50:14] 미감지 -> 감지로 변경된 경우에만 정상..*/
            bit_uart_filter_cover_reed = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_filter_cover_old == CLEAR )
        {
            bit_filter_cover_old = SET;
            play_melody_warning_197();
        }
        else{}
    }





}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_comp_control(void)
{
    gu8_bldc_target_hz = gu8_uart_comp_rps;

    if( gu8_bldc_target_hz == 0 )
    {
        comp_off();
    }
    else
    {
        comp_on();
    }

    if( pCOMP == SET )
    {
        Bldc_Comp_Communication();
    }
    else
    {
        clear_bldc_buffer();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_mode_display_test(void)
{
    led_blink_timer();

    display_test_error();

    fnd_left_display_test();
    fnd_right_display_test();

    if( gu8_display_test_error != 0 )
    {
        gu8_front_select_led = 0;
        gu8_front_new_text_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_under_icon_led = 0;
        gu8_front_uv_care_txt_led = 0;

        gu8_front_left_led = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        return;
    }
    else{}

    if(gu8_setting_test_input == 1)
    {
        Bit0_Front_Led_Set_Select = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Left_Led_Preparing_Text = F_cds_detect & F_Wink_500ms;
        bit_setting_test_finish = SET;
    }
    else
    {
        if( bit_setting_test_finish == CLEAR )
        {
            Bit0_Front_Led_Set_Select = SET;
            Bit0_Front_Left_Led_Preparing_Text = SET;
        }
        else
        {
            gu8_setting_test_input = 1;
        }
    }


    if(gu8_ice_test_input == 1)
    {
        Bit1_Front_Led_Ice_Select = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Left_Led_Filter_Flushing_Text = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Left_Led_Celcius_oC_Icon = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = F_cds_detect & F_Wink_500ms;
        bit_ice_test_finish = SET;
    }
    else
    {
        if( bit_ice_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = SET;
            Bit2_Front_Left_Led_Filter_Flushing_Text = SET;
            Bit6_Front_Left_Led_Celcius_oC_Icon = SET;
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = SET;
        }
        else
        {
            gu8_ice_test_input = 1;
        }
    }


    if(gu8_hot_test_input == 1)
    {
        Bit2_Front_Led_Hot_Select = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Left_Led_Current_Text = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Left_Led_Percent_Icon = F_cds_detect & F_Wink_500ms;

        bit_hot_test_finish = SET;
    }
    else
    {
        if( bit_hot_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Select = SET;
            Bit1_Front_Left_Led_Current_Text = SET;
            Bit5_Front_Left_Led_Percent_Icon = SET;
        }
        else
        {
            gu8_hot_test_input = 1;
        }
    }


    if(gu8_ambient_test_input == 1)
    {
        Bit3_Front_Led_Ambient_Select = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Led_Ice_Tank_Clean_Text = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Led_Water_Tank_Text = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Led_Ice_Tank_Text = F_cds_detect & F_Wink_500ms;
        Bit5_Front_New_Led_Replace_Filter_1_Num = F_cds_detect & F_Wink_500ms;

        bit_ambient_test_finish = SET;
    }
    else
    {
        if( bit_ambient_test_finish == CLEAR )
        {
            Bit3_Front_Led_Ambient_Select = SET;
            Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
            Bit2_Front_Led_Water_Tank_Text = SET;
            Bit4_Front_Led_Ice_Tank_Text = SET;
            Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
        }
        else
        {
            gu8_ambient_test_input = 1;
        }
    }


    if(gu8_cold_test_input == 1)
    {
        Bit4_Front_Led_Cold_Select = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Led_UV_Care_Txt_Under_bar = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Led_Ice_Tray_Text = F_cds_detect & F_Wink_500ms;
        Bit6_Front_New_Led_Replace_Filter_2_Num = F_cds_detect & F_Wink_500ms;

        bit_cold_tst_finish = SET;
    }
    else
    {
        if( bit_cold_tst_finish == CLEAR )
        {
            Bit4_Front_Led_Cold_Select = SET;
            Bit1_Front_Led_UV_Care_Txt_Under_bar = SET;
            Bit3_Front_Led_Ice_Tray_Text = SET;
            Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
        }
        else
        {
            gu8_cold_test_input = 1;
        }
    }


    if(gu8_amount_test_input == 1)
    {
        Bit5_Front_Led_Amount_Select = F_cds_detect & F_Wink_500ms;
        Bit4_Front_New_Led_Replace_Filter_Text = F_cds_detect & F_Wink_500ms;
        Bit7_Front_New_Led_Replace_Filter_3_Num = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Right_Led_ml_Text = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Right_Led_OZ_Text = F_cds_detect & F_Wink_500ms;

        bit_amount_test_finish = SET;
    }
    else
    {
        if( bit_amount_test_finish == CLEAR )
        {
            Bit5_Front_Led_Amount_Select = SET;
            Bit4_Front_New_Led_Replace_Filter_Text = SET;
            Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
            Bit5_Front_Right_Led_ml_Text = SET;
            Bit3_Front_Right_Led_OZ_Text = SET;
        }
        else
        {

            gu8_amount_test_input = 1;
        }
    }


    if(gu8_setting_ice_first_test_input == 1)
    {
        Bit0_Front_Led_Ice_First = F_cds_detect & F_Wink_500ms;
        Bit0_Front_Under_Txt_Led_Ice_First = F_cds_detect & F_Wink_500ms;
        Bit6_Front_Right_Led_Days_Left_Text = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Right_Led_Wifi_Icon_White = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = SET;

        bit_ice_first_test_finish = SET;
    }
    else
    {
        if( bit_ice_first_test_finish == CLEAR )
        {
            Bit0_Front_Led_Ice_First = SET;
            Bit0_Front_Under_Txt_Led_Ice_First = SET;
            Bit6_Front_Right_Led_Days_Left_Text = SET;
            Bit1_Front_Right_Led_Wifi_Icon_White = SET;
            Bit2_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
        }
        else
        {
            gu8_setting_ice_first_test_input = 1;
        }
    }


    if(gu8_setting_ice_lock_test_input == 1)
    {
        Bit1_Front_Led_Ice_Lock = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Under_Icon_Led_Ice_Lock = F_cds_detect & F_Wink_500ms;
        Bit1_Front_Right_Led_Wifi_Icon_White = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = F_cds_detect & F_Wink_500ms;
        Bit0_Front_New_Led_Ice_Making_Text = F_cds_detect & F_Wink_500ms;

        bit_ice_lock_test_finish = SET;
    }
    else
    {
        if( bit_ice_lock_test_finish == CLEAR )
        {
            Bit1_Front_Led_Ice_Lock = SET;
            Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
            Bit0_Front_New_Led_Ice_Making_Text = SET;
        }
        else
        {
            gu8_setting_ice_lock_test_input = 1;
            Bit2_Front_Right_Led_Wifi_Icon_Blue = F_cds_detect & F_Wink_500ms;
        }
    }


    if(gu8_setting_hot_lock_test_input == 1)
    {
        Bit2_Front_Led_Hot_Lock = F_cds_detect & F_Wink_500ms;
        Bit2_Front_Under_Icon_Led_Hot_Lock = F_cds_detect & F_Wink_500ms;
        Bit4_Front_Right_Led_Min_Left_Text = F_cds_detect & F_Wink_500ms;
        Bit1_Front_New_Led_Hot_Heating_Text = F_cds_detect & F_Wink_500ms;

        bit_hot_lock_test_finish = SET;
    }
    else
    {
        if( bit_hot_lock_test_finish == CLEAR )
        {
            Bit2_Front_Led_Hot_Lock = SET;
            Bit2_Front_Under_Icon_Led_Hot_Lock = SET;
            Bit4_Front_Right_Led_Min_Left_Text = SET;
            Bit1_Front_New_Led_Hot_Heating_Text = SET;
        }
        else
        {
            gu8_setting_hot_lock_test_input = 1;
        }
    }



    if(gu8_setting_touch_lock_test_input == 1)
    {
        Bit3_Front_Led_Touch_Lock = F_cds_detect & F_Wink_500ms;
        Bit5_Front_Under_Led_Ice_Full = F_cds_detect & F_Wink_500ms;
        Bit2_Front_New_Led_Cold_Cooling_Text = F_cds_detect & F_Wink_500ms;

        gu8_hot_temp_off_timer++;

        if( gu8_hot_temp_off_timer <= 3 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else if( gu8_hot_temp_off_timer <= 6 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else if( gu8_hot_temp_off_timer <= 9 )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else
        {
            gu8_hot_temp_off_timer = 10;
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = F_cds_detect & F_Wink_500ms;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = F_cds_detect & F_Wink_500ms;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = F_cds_detect & F_Wink_500ms;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = F_cds_detect & F_Wink_500ms;
        }

        bit_touch_lock_test_finish = SET;
    }
    else
    {
        if( bit_touch_lock_test_finish == CLEAR )
        {
            Bit3_Front_Led_Touch_Lock = SET;
            Bit5_Front_Under_Led_Ice_Full = SET;
            Bit2_Front_New_Led_Cold_Cooling_Text = SET;

            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            gu8_hot_temp_off_timer = 0;
        }
        else
        {
            gu8_setting_touch_lock_test_input = 1;
        }
    }


    if(gu8_setting_eco_mode_test_input == 1)
    {
        Bit4_Front_Led_Eco_Mode = F_cds_detect & F_Wink_500ms;
        Bit3_Front_Left_Led_Eco_Icon = F_cds_detect & F_Wink_500ms;
        Bit3_Front_New_Led_Low_Water_Text = F_cds_detect & F_Wink_500ms;

        gu8_cup_level_off_timer++;

        if( gu8_cup_level_off_timer <= 3 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 6 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 9 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else if( gu8_cup_level_off_timer <= 12 )
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

        }
        else
        {
            gu8_cup_level_off_timer = 13;
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = F_cds_detect & F_Wink_500ms;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = F_cds_detect & F_Wink_500ms;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = F_cds_detect & F_Wink_500ms;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = F_cds_detect & F_Wink_500ms;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = F_cds_detect & F_Wink_500ms;
        }

        bit_eco_test_finish = SET;
    }
    else
    {
        if( bit_eco_test_finish == CLEAR )
        {
            Bit4_Front_Led_Eco_Mode = SET;
            Bit3_Front_Left_Led_Eco_Icon = SET;
            Bit3_Front_New_Led_Low_Water_Text = SET;

            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

            gu8_cup_level_off_timer = 0;

        }
        else
        {
            gu8_setting_eco_mode_test_input = 1;
        }
    }


    #if 0
    if(gu8_water_ext_test_input == 1)
    {
        Bit4_Front_Under_Led_Water_Extract = SET;
        make_rgb_color( RGB_COLOR_HOT );
        set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
    }
    else if(gu8_water_ext_test_input == 2)
    {
        Bit4_Front_Under_Led_Water_Extract = SET;
        make_rgb_color( RGB_COLOR_COLD );
        set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
    }
    else if(gu8_water_ext_test_input == 3)
    {
        Bit4_Front_Under_Led_Water_Extract = F_cds_detect & F_Wink_500ms;
        make_rgb_color( RGB_OFF );
        set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__100_PERCENT );
        bit_water_extract_test_finish = SET;
    }
    else
    {
        if( bit_water_extract_test_finish == CLEAR )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_rgb_color( RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__100_PERCENT );
        }
        else
        {
            gu8_water_ext_test_input = 3;
        }
    }
    #endif

    if(gu8_water_ext_test_input == 1)
    {
        gu8_water_color_change_timer++;

        if( gu8_water_color_change_timer <= 5 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else if( gu8_water_color_change_timer <= 10 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else if( gu8_water_color_change_timer <= 15 )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
        }
        else
        {
            gu8_water_color_change_timer = 16;
            Bit4_Front_Under_Led_Water_Extract = F_cds_detect & F_Wink_500ms;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__100_PERCENT );
            bit_water_extract_test_finish = SET;
        }
    }
    else
    {
        if( bit_water_extract_test_finish == CLEAR )
        {
            Bit4_Front_Under_Led_Water_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__100_PERCENT );
        }
        else
        {
            gu8_water_ext_test_input = 1;
        }
    }

    if(gu8_ice_ext_test_input == 1)
    {
        Bit3_Front_Under_Led_Ice_Extract = F_cds_detect & F_Wink_500ms;

        bit_ice_extract_test_finish = SET;
    }
    else
    {
        if( bit_ice_extract_test_finish == CLEAR )
        {
            Bit3_Front_Under_Led_Ice_Extract = SET;
        }
        else
        {
            gu8_ice_ext_test_input = 1;
        }
    }

    /*..hui [19-11-18오전 11:28:17] 프론트 LED 다 꺼진 상태에서 조도센서 입력..*/
    /*..hui [19-11-18오후 12:55:19] 트레이 다 올리고나서부터 감지..*/
    /*..hui [20-2-11오후 5:55:02] 탱크 리드스위치 입력 추가.. 닫혔을 경우에만..*/
    /*..hui [20-2-17오후 3:24:39] 트레이도 제빙쪽으로 다 올라갔을 경우에만 완료되도록..*/

    if( gu8_front_temp_fnd_hundred == 0
        && gu8_front_temp_fnd_ten == 0
        && gu8_front_temp_fnd_one == 0
        && gu8_front_amount_fnd_hundred == 0
        && gu8_front_amount_fnd_ten == 0
        && gu8_front_amount_fnd_one == 0
        && gu8_front_select_led == 0
        && gu8_front_new_text_led == 0
        && gu8_front_setting_led == 0
        && gu8_front_under_icon_led == 0
        && gu8_front_uv_care_txt_led == 0
        && gu8_front_left_led == 0
        && gu8_front_right_led == 0
        && gu8_front_temp_setting_bar_led == 0
        && gu8_front_amount_setting_bar_led == 0

        && gu8_service_reed_uart == SET
        && gu8_display_test_error == 0 )
    {
        F_cds_detect = 1;

        gu8_display_test_delay_timer++;

        /*..hui [23-3-15오전 11:02:39] 조도센서까지 검사하고 전체 2회 점멸 후 통신검사 시작..*/
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

        if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
        {
            mu8_test_rps = get_ice_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
        else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
        {
            mu8_test_rps = get_cold_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
        {
            mu8_test_rps = get_hotgas_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
    }
    else
    {
        if( gu8_setting_test_input == 1 )
        {
            gu8_setting_test_input = 0;
            play_melody_warning_197();
        }
        else{}

        Bit0_Front_Led_Set_Select = CLEAR;

        if( gu8_uart_comp_rps > 0 )
        {
            gu16_manaul_comp_delay_timer = 0;
            gu8_uart_comp_rps = 0;
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
            Bit2_Front_Led_Hot_Select = CLEAR;
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
        else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
            Bit2_Front_Led_Hot_Select = CLEAR;
            Bit4_Front_Led_Cold_Select = SET;
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
            Bit2_Front_Led_Hot_Select = SET;
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
    }
    else
    {
        Bit1_Front_Led_Ice_Select ^= SET;
        Bit2_Front_Led_Hot_Select ^= SET;
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

    if( gu8_hot_test_input == 1 )
    {
        GasSwitchHotGas();
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
void check_off_ad(void)
{
    gu8_check_off_ad_timer++;

    if( gu8_check_off_ad_timer >= 50 )
    {
        gu8_check_off_ad_timer = 50;
        return;
    }
    else{}

    if( pDC_FAN == CLEAR )
    {
        if( gu16_AD_Result_Fan_Current < gu16_uart_dc_fan_off_ad )
        {
            gu16_uart_dc_fan_off_ad = gu16_AD_Result_Fan_Current;
        }
        else{}
    }
    else{}

    if( gu16_drain_pwm_out == 0 )
    {
        if( gu16_AD_Drain_Pump_Current < gu16_uart_drain_pump_off_ad )
        {
            gu16_uart_drain_pump_off_ad = gu16_AD_Drain_Pump_Current;
        }
        else{}
    }
    else{}

    if( gu16_current_tray_pwm == 0 )
    {
        if( gu16_AD_Tray_Pump_Current < gu16_uart_tray_pump_off_ad )
        {
            gu16_uart_tray_pump_off_ad = gu16_AD_Tray_Pump_Current;
        }
        else{}
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void test_tds(void)
{
    if( gu8_factory_test_step != 0 )
    {
        F_TDS_ON = CLEAR;
        return;
    }
    else{}

    F_TDS_ON = SET;

    if( gu16_uart_test_pulse > gu16_uart_tds_in_max )
    {
        gu16_uart_tds_in_max = gu16_uart_test_pulse;
    }
    else{}

    if( gu16_AD_Result_TDS_Out_Data > gu16_uart_tds_out_max )
    {
        gu16_uart_tds_out_max = gu16_AD_Result_TDS_Out_Data;

        if( gu16_uart_tds_out_max >= 1024 )
        {
            gu16_uart_tds_out_max = 1024;
        }
        else{}
    }
    else{}
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



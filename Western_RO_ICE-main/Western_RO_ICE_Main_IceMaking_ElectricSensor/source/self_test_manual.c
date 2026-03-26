/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "self_test_manual.h"


void self_test(void);
void self_test_manual(void);

void self_tesr_proc(void);
void initial_self_data(void);
U8 off_all_test_load(void);
void finish_self_test(void);
void start_self_test(void);
void initial_each_self_data( U8 mu8_num );
void self_max_limit_timer(void);


TYPE_SELF_TEST_DATA             SELF_Test_Result_Data;
#define U16_FEED_1_1_DC_Current_PART_0000                        SELF_Test_Result_Data.word[0]
#define U16_NOS_1_2_DC_Current_PART_0001                         SELF_Test_Result_Data.word[1]
#define U16_HOT_OUT_3_3_DC_Current_PART_0002                     SELF_Test_Result_Data.word[2]
#define U16_PURE_OUT_3_2_DC_Current_PART_0003                    SELF_Test_Result_Data.word[3]
#define U16_COLD_OUT_3_1_DC_Current_PART_0004                    SELF_Test_Result_Data.word[4]
#define U16_HOT_IN_6_2_DC_Current_PART_0009                      SELF_Test_Result_Data.word[5]
#define U16_AIR_FEED_2_DC_Current_PART_000B                      SELF_Test_Result_Data.word[6]
#define U16_COLD_DRAIN_3_4_DC_Current_PART_000D                  SELF_Test_Result_Data.word[7]
#define U16_ICE_TRAY_IN_6_1_DC_Current_PART_0015                 SELF_Test_Result_Data.word[8]
#define U16_FLUSHING_FEED_8_2_DC_Current_PART_0018               SELF_Test_Result_Data.word[9]
#define U16_RO_FLUSHING_MOTOR_DC_Current_PART_0019               SELF_Test_Result_Data.word[10]
#define U16_HOT_OVERHEAT_5_3_DC_Current_PART_001A                SELF_Test_Result_Data.word[11]
#define U16_HOT_STER_LEFT_DC_Current_PART_001B                   SELF_Test_Result_Data.word[12]
#define U16_HOT_STER_RIGHT_DC_Current_PART_001C                  SELF_Test_Result_Data.word[13]
#define U16_FLUSHING_NOS_8_1_DC_Current_PART_001F                SELF_Test_Result_Data.word[14]
#define U16_COLD_FAN_DC_Furrent_PART_0204                        SELF_Test_Result_Data.word[15]
#define U16_ICE_TRAY_FLOW_SENSOR_PART_0403                       SELF_Test_Result_Data.word[16]
#define U16_RO_DRAIN_FLOW_SENSOR_PART_040C                       SELF_Test_Result_Data.word[17]
#define U16_UV_ICE_TANK_1_2_Back_DC_Current_PART_0503            SELF_Test_Result_Data.word[18]
#define U16_UV_ICE_TRAY_1_2_DC_Current_PART_0504                 SELF_Test_Result_Data.word[19]
#define U16_UV_COLD_TANK_1_2_DC_Current_PART_0505                SELF_Test_Result_Data.word[20]
#define U16_UV_ICE_TANK_3_Front_DC_Current_PART_0506             SELF_Test_Result_Data.word[21]
#define U16_SWING_BAR_DC_Current_PART_0802                       SELF_Test_Result_Data.word[22]
#define U16_ICE_DOOR_MOTOR_DC_Current_PART_0807                  SELF_Test_Result_Data.word[23]
#define U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808                SELF_Test_Result_Data.word[24]
#define U16_DRAIN_PUMP_DC_Current_PART_080A                      SELF_Test_Result_Data.word[25]
#define U16_ICE_TRAY_PUMP_DC_Current_PART_080B                   SELF_Test_Result_Data.word[26]
#define U16_ICE_FULL_SENSOR_PART_0801                            SELF_Test_Result_Data.word[27]







bit bit_self_test_start;
bit bit_self_test_stop;

U8 gu8_self_test_manual_step;
U16 gu16_self_test_manual_timer;

U8 gu8_self_test_no_load_max_timer;



U8 gu8_selfselfself;

bit bit_current_check_disable;


U16 gu16_self_max_lilit_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void self_test(void)
{
    self_test_manual();
    periodic_self_test();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void self_test_manual(void)
{
    #if 0
    if( gu8_selfselfself == 1 )
    {
        gu8_selfselfself = 0;
        start_self_test();
    }
    else{}
    #endif

    if( bit_self_test_start == SET )
    {
        self_max_limit_timer();

        if( bit_self_test_stop == SET )
        {
            finish_self_test();
        }
        else
        {
            self_tesr_proc();
        }
    }
    else
    {
        gu8_self_test_manual_step = 0;
        gu16_self_test_manual_timer = 0;
        gu16_self_max_lilit_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void self_max_limit_timer(void)
{
    gu16_self_max_lilit_timer++;

    if( gu16_self_max_lilit_timer >= 6000 )
    {
        gu16_self_max_lilit_timer = 6000;
        bit_self_test_stop = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void self_tesr_proc(void)
{
    U16 mu16_val = 0;
    U8 mu8_decision = 0;
    U8 mu8_ok = 0;
    U8 mu8_return = 0;

    switch( gu8_self_test_manual_step )
    {
        case 0 :

            gu8_component_test_step = 0;
            gu8_current_check_step = 0;
            gu8_self_flow_test_step = 0;
            gu8_self_test_no_load_max_timer = 0;

            gu16_self_test_manual_timer = 0;
            gu8_self_test_manual_step++;

            ///////////gu8_Lcd_Display_Step = LCD_Display__SELF_TEST;

        break;

        case 1 :

            F_WaterOut = CLEAR;
            /*..hui [20-10-30오전 9:50:06] 시작하기 전에 이전 데이타 초기ㅗ하..*/
            initial_self_data();

            /*..hui [23-12-22오후 4:41:59] 얼음 만드는중이었으면 완료될때까지 대기..*/
            if( gu8IceStep == STATE_0_STANDBY )
            {
                gu8_self_test_manual_step++;
            }
            else{}

        break;

        case 2 :

            mu8_return = off_all_test_load();

            if( mu8_return == SET )
            {
                gu16_self_test_manual_timer++;

                /*..hui [20-10-28오후 7:53:40] 전류 피드백 10 이하로 안정 or 최대 2초 이내..*/
                if( gu16_AD_Result_DC_Current_24V <= 20
                     || gu16_self_test_manual_timer >= 20 )
                {
                    gu16_self_test_manual_timer = 0;
                    gu8_self_test_no_load_max_timer = 0;
                    gu8_self_test_manual_step++;
                }
                else{}
            }
            else
            {
                gu16_self_test_manual_timer = 0;

                gu8_self_test_no_load_max_timer++;

                if( gu8_self_test_no_load_max_timer >= 20 )
                {
                    gu16_self_test_manual_timer = 0;
                    gu8_self_test_no_load_max_timer = 0;
                    gu8_self_test_manual_step++;
                }
                else{}
            }

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 3 :

            /*..hui [21-8-25오후 2:44:37] 유량 테스트 더 먼저..*/
            /*..hui [23-12-21오전 11:34:13] 트레이 입수 유량센서, RO 드레인 유량센서 유량 측정..*/
            mu8_return = manual_test_flow();

            if( mu8_return == SET )
            {
                off_all_test_load();
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step++;
            }
            else{}

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 4 :

            /*..hui [20-10-29오전 11:38:05] DC 및 AC 부하 전류 테스트..*/
            /*..hui [23-12-21오전 11:43:29] DC 부하 테스트..*/
            mu8_return = manual_test_load();

            if( mu8_return == SET )
            {
                off_all_test_load();
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step++;
            }
            else{}

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 5 :

            gu16_self_test_manual_timer++;

            if( gu16_self_test_manual_timer >= 10 )
            {
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step = 0;

                finish_self_test();
            }
            else{}

        break;


        default :

            gu8_self_test_manual_step = 0;
            gu16_self_test_manual_timer = 0;

        break;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_self_data(void)
{
    U8 mu8_i = 0;

    for(mu8_i = 0; mu8_i < SELF_TEST_RESULT_DATA_LENGTH; mu8_i++)
    {
        SELF_Test_Result_Data.word[ mu8_i ] = SELF_TEST_INITIAL_DATA;
    }

    /*gu16_wifi_hot_target_time_min = SELF_TEST_INITIAL_DATA;*/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_each_self_data( U8 mu8_num )
{
    U8 mu8_i = 0;

    SELF_Test_Result_Data.word[ mu8_num ] = SELF_TEST_INITIAL_DATA;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 off_all_test_load(void)
{
    U8 mu8_return = 0;

    /*p12V_POWER = CLEAR;*/
    /*pVALVE_24V_POWER = CLEAR;*/
    pVALVE_24V_POWER = SET;

    if( pUV_LED_ICE_TRAY_1_2 == CLEAR
        && pUV_LED_ICE_TANK_3_FRONT == CLEAR
        && pUV_LED_ICE_TANK_1_2_BACK == CLEAR
        && pUV_LED_WATER_TANK_1_2 == CLEAR

        && pMOTOR_ICE_TRAY_CW == CLEAR
        && pMOTOR_ICE_TRAY_CCW == CLEAR

        && pMOTOR_ICE_OUT_CW == CLEAR
        && pMOTOR_ICE_OUT_CCW == CLEAR
        && pCOMP == CLEAR
        && pHEATER_HOT == CLEAR

        && pSWING_BAR == CLEAR
        && pDC_FAN == CLEAR
        && pIR_POWER == CLEAR

        /*&& pVALVE_24V_POWER == CLEAR*/
        && pVALVE_NOS == CLEAR
        && pVALVE_FEED == CLEAR
        && pVALVE_AIR_VENT == CLEAR
        && pVALVE_HOT_OUT == CLEAR
        && pVALVE_COLD_OUT == CLEAR
        && pVALVE_ROOM_OUT == CLEAR
        && pVALVE_COLD_DRAIN == CLEAR
        && pVALVE_ICE_TANK_STER_FEED_LEFT == CLEAR
        && pVALVE_ICE_TANK_STER_FEED_RIGHT == CLEAR
        && pVALVE_OVERHEATING_NOS == CLEAR
        && pVALVE_ICE_TRAY_IN_FEED == CLEAR
        && pVALVE_HOT_IN_FEED == CLEAR
        && pVALVE_FLUSHING_FEED == CLEAR
        && pVALVE_FLUSHING_NOS == CLEAR

        /*&& pTDS_IN_Power == SET*/
        && pLEAKAGE_ON == CLEAR
        && TDR11 == 0
        && TDR12 == 0 )
    {
        mu8_return = SET;
    }
    else
    {
        pUV_LED_ICE_TRAY_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3_FRONT = CLEAR;
        pUV_LED_ICE_TANK_1_2_BACK = CLEAR;
        pUV_LED_WATER_TANK_1_2 = CLEAR;

        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;

        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
        pCOMP = CLEAR;
        pHEATER_HOT = CLEAR;

        pSWING_BAR = CLEAR;
        pDC_FAN = CLEAR;
        pIR_POWER = CLEAR;

        /*pVALVE_24V_POWER = CLEAR;*/
        pVALVE_NOS = CLEAR;
        pVALVE_FEED = CLEAR;
        pVALVE_AIR_VENT = CLEAR;
        pVALVE_HOT_OUT = CLEAR;
        pVALVE_COLD_OUT = CLEAR;
        pVALVE_ROOM_OUT = CLEAR;
        pVALVE_COLD_DRAIN = CLEAR;
        pVALVE_ICE_TANK_STER_FEED_LEFT = CLEAR;
        pVALVE_ICE_TANK_STER_FEED_RIGHT = CLEAR;
        pVALVE_OVERHEATING_NOS = CLEAR;
        pVALVE_ICE_TRAY_IN_FEED = CLEAR;
        pVALVE_HOT_IN_FEED = CLEAR;
        pVALVE_FLUSHING_FEED = CLEAR;
        pVALVE_FLUSHING_NOS = CLEAR;

        /*pTDS_IN_Power = SET;*/
        pLEAKAGE_ON = CLEAR;

        stop_drain_pump();
        stop_tray_pump();
    }

    return mu8_return;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void finish_self_test(void)
{
    /*..hui [24-1-9오후 1:46:00] 중간에 중단할경우 설정음.. 선국과장..*/
    if( bit_self_test_stop == SET )
    {
        play_melody_setting_on_198();
    }
    else{}

    bit_self_test_start = CLEAR;
    bit_self_test_stop = CLEAR;

    off_all_test_load();

    gu8_self_test_manual_step = 0;
    gu8_component_test_step = 0;
    gu16_self_test_manual_timer = 0;

    gu16_gas_switch_current_max = 0;

    /*..hui [24-1-9오후 12:07:50] WIFI쪽에서 자동 출력..*/
    /*play_voice_finish_self_no_error_test_62();*/

    Bit2_Uart_Test_Mode_State = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_self_test(void)
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

    bit_self_test_start = SET;

    off_all_test_load();

    /*..hui [23-12-22오후 5:11:58] 제빙중이었으면 정지..*/
    stop_ice_cody_mode();

    gu8_self_test_manual_step = 0;

    Bit2_Uart_Test_Mode_State = SET;

    play_voice_start_self_test_61();

    gu16_gas_switch_current_max = 0;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/






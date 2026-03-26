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



void Main_PBA_Test_Mode_Start(void);
void Pcb_Test_Main(void);
void pcb_test_job(void);
void thermistor_test(void);
void hot_out_temp(void);
void hot_heater_temp(void);
void cold_temp(void);
void outdoor_1_temp(void);
void outdoor_2_temp(void);

void room_temp(void);
void mixing_temp(void);
void eva1_temp(void);
/////void tds_in_temp(void);
/////void tds_out_temp(void);

void sensor_test(void);
void watertank_low_water(void);
void watertank_high_water(void);
void draintank_low_water(void);
void draintank_high_water(void);
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
/////void tds_sensor(void);

void fault_ad_test(void);

void uart_test(void);
void bldc_comm_test(void);

void pcb_test_mode_uart_test(void);
void uart_error_display(void);
void PCB_Test_Mode_Key_Short_Input( U16 u16key_input_value);
void PCB_Test_Mode_Extract_Key_Short_Input(void);
void PCB_Test_Mode_Ice_Key_Short_Input(void);
void test_mode_eeprom_initial(void);
void wifi_test(void);




U8 gu8_redo_test_input;
U8 gu8_left_test_input;

U8 gu8_user_test_input;
U8 gu8_hot_test_input;
U8 gu8_room_test_input;
U8 gu8_cold_test_input;
U8 gu8_cup_test_input;



U8 gu8_user_test_input_led;
U8 gu8_hot_test_input_led;
U8 gu8_room_test_input_led;
U8 gu8_cold_test_input_led;
U8 gu8_cup_test_input_led;





U8 gu8_right_test_input;



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


bit bit_step_out_state;


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
U8 gu8_filter_flow_test_timer;


U8 gu8_user_acc1;
U8 gu8_user_acc2;
U8 gu8_user_acc3;
U8 gu8_user_acc4;



U8 gu8_setting_test_input;
U8 gu8_ice_test_input;
U8 gu8_hot_test_input;
U8 gu8_ambient_test_input;
U8 gu8_cold_test_input;
U8 gu8_amount_test_input;
U8 gu8_setting_ice_first_test_input;
U8 gu8_setting_ice_lock_test_input;
U8 gu8_setting_hot_lock_test_input;
U8 gu8_setting_touch_lock_test_input;
U8 gu8_setting_steam_off_test_input;
U8 gu8_setting_eco_mode_test_input;

U8 gu8_water_ext_test_input;
U8 gu8_ice_ext_test_input;


bit bit_setting_test_finish;
bit bit_ice_test_finish;
bit bit_hot_test_finish;
bit bit_ambient_test_finish;
bit bit_cold_tst_finish;
bit bit_amount_test_finish;
bit bit_ice_first_test_finish;
bit bit_ice_lock_test_finish;
bit bit_hot_lock_test_finish;
bit bit_touch_lock_test_finish;
bit bit_steam_off_test_finish;
bit bit_eco_test_finish;

bit bit_water_extract_test_finish;
bit bit_ice_extract_test_finish;

bit bit_bldc_rx_pba_test_ok;

bit bit_comp_test;

bit bit_pcb_test_finish;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Main_PBA_Test_Mode_Start(void)
{
    /*F_PcbTestStart = SET;*/
    gu8_test_mode_timeout = 0;
    off_all_control_led();
    /*BuzStep(BUZZER_COOL_SETUP);*/
    /*play_melody_setting_on_198();*/
    play_voice_test_mode_151();

    u8FactoryTestMode = PCB_TEST_MODE;
    UARTest_NO_LOAD_Set();
    F_FW_Version_Display_Mode = CLEAR;

    /*..hui [19-12-19오후 1:26:46] 정수 온도센서 전원 ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19오후 1:27:21] 냉수 온도센서 전원 ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;


    /*..hui [20-1-14오후 8:15:16] 12V 전원 ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    gu8_flow_test_timer = 0;
    gu8_filter_flow_test_timer = 0;
    bit_bldc_rx_pba_test_ok = CLEAR;

    /*..hui [21-2-18오후 5:08:19] WIFI 공장 검사 추가..*/
    WifiKey(WIFI_KEY_TEST);

    gu8_eeprom_initial_test_input = 1;

    bit_manual_test_start = CLEAR;

    all_breath_stop();

    bit_pcb_test_finish = CLEAR;

    #if 0
    /*..hui [24-11-13오후 4:00:55] 드레인 전압 삭제..*/
    /*..hui [24-7-26오후 5:39:25] 드레인 수위센서 전원 항상 킴..*/
    pPower_Drain_Level = CLEAR;
    bit_drain_level_power_output = SET;
    #endif

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pcb_Test_Main(void)
{
    all_breath_stop();
    //all_dimming_full_on();
    all_duty_100_percent();

    led_blink_timer();

    /*..hui [19-7-22오후 7:36:53] 유량센서..*/
    calculate_tray_flow_input();
    calculate_filter_flow_input();

    if(F_FW_Version_Display_Mode != SET)
    {
        display_version();
    }
    else
    {
        pcb_test_job();
        fnd_left_pba_test();
        fnd_right_pba_test();
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
    /*..hui [24-11-13오후 4:28:36] TDS 삭제..*/
    /*tds_sensor();*/

    output_test();
    fault_ad_test();

    /*..hui [18-2-21오전 11:15:24] 자동검사 uart 회로 검사 기능 추가..*/
    uart_test();
    bldc_comm_test();

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


    if( gu8_front_temp_fnd_hundred == 0x7f
        && gu8_front_temp_fnd_ten == 0x7f
        && gu8_front_temp_fnd_one == 0x7f

        && gu8_front_amount_fnd_hundred == 0x7f
        && gu8_front_amount_fnd_ten == 0x7f
        && gu8_front_amount_fnd_one == 0x7f

        && gu8_front_select_led == 0x3f
        && gu8_front_new_text_led == 0xff
        /*&& gu8_front_setting_led == 0x1f*/
        && gu8_front_setting_led == 0x0f
        && gu8_front_under_icon_led == 0x3f
        && gu8_front_uv_care_txt_led == 0x1f

        && gu8_front_left_led == 0x7f
        && gu8_front_right_led == 0x7e
        && gu8_front_temp_setting_bar_led == 0x0f
        && gu8_front_amount_setting_bar_led == 0x1f )
    {
        /*Bit4_Front_Led_Eco_Mode ^= SET;*/
        //Bit7_Front_Left_Led_Gal_Icon ^= SET;

        bit_pcb_test_finish = SET;
    }
    else
    {
        /*Bit5_Front_Led_Eco_Mode = CLEAR;*/
    }

    if( bit_pcb_test_finish == SET )
    {
        Bit4_Front_Led_Eco_Mode ^= SET;
    }
    else
    {
        Bit4_Front_Led_Eco_Mode = CLEAR;
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
    outdoor_1_temp();
    outdoor_2_temp();

    room_temp();
    mixing_temp();
    eva1_temp();

    /*..hui [24-11-13오후 4:14:14] TDS 삭제..*/
    /*tds_in_temp();*/
    /*tds_out_temp();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_out_temp(void)
{
    if(gu16_AD_Result_Hot_Tank_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Tank_Temp >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit2_Front_Led_Hot_Select = CLEAR;
    }
    else if(gu16_AD_Result_Hot_Tank_Temp >= (512 - GAP) && gu16_AD_Result_Hot_Tank_Temp <= (512 + GAP))
    {
        //1단
        Bit2_Front_Led_Hot_Select = SET;
    }
    else
    {
        Bit2_Front_Led_Hot_Select = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp(void)
{
    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit4_Front_Led_Cold_Select = CLEAR;
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
    }
    else if(gu16_AD_Result_Cold >= (512 - GAP) && gu16_AD_Result_Cold <= (512 + GAP))
    {
        //1단
        Bit4_Front_Led_Cold_Select = SET;
        Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
        Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
    }
    else
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void outdoor_1_temp(void)
{
    if(gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit1_Front_Led_Ice_Select = CLEAR;
    }
    else if(gu16_AD_Result_Amb >= (512 - GAP) && gu16_AD_Result_Amb <= (512 + GAP))
    {
        //1단
        Bit1_Front_Led_Ice_Select = SET;
    }
    else
    {
        Bit1_Front_Led_Ice_Select = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void outdoor_2_temp(void)
{
    if(gu16_AD_Result_Amb_Side <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb_Side >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
        ///Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
        Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
    }
    else if(gu16_AD_Result_Amb_Side >= (512 - GAP) && gu16_AD_Result_Amb_Side <= (512 + GAP))
    {
        //1단
        Bit5_Front_New_Led_Replace_Filter_1_Num = SET;
        ///Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
        Bit7_Front_New_Led_Replace_Filter_3_Num = SET;
    }
    else
    {
        Bit5_Front_New_Led_Replace_Filter_1_Num = CLEAR;
        ///Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
        Bit7_Front_New_Led_Replace_Filter_3_Num = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void room_temp(void)
{
    if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }
    else if(gu16_AD_Result_Room >= (512 - GAP) && gu16_AD_Result_Room <= (512 + GAP))
    {
        //표시없음
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
void mixing_temp(void)
{
    if( gu16_AD_Result_Mixing_Out <= TEMP_SENSOR_SHORT || gu16_AD_Result_Mixing_Out >= TEMP_SENSOR_OPEN )
    {
        //에러
        Bit5_Front_Led_Amount_Select = CLEAR;
    }
    else if(gu16_AD_Result_Mixing_Out >= (512 - GAP) && gu16_AD_Result_Mixing_Out <= (512 + GAP))
    {
        //표시없음
        Bit5_Front_Led_Amount_Select = SET;
    }
    else
    {
        Bit5_Front_Led_Amount_Select = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void eva1_temp(void)
{
    if( gu16_AD_Result_Eva_First <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_First >= TEMP_SENSOR_OPEN )
    {
        //에러
        Bit0_Front_Led_Ice_First = CLEAR;
    }
    else if(gu16_AD_Result_Eva_First >= (512 - GAP) && gu16_AD_Result_Eva_First <= (512 + GAP))
    {
        //표시없음
        Bit0_Front_Led_Ice_First = SET;
    }
    else
    {
        Bit0_Front_Led_Ice_First = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void tds_in_temp(void)
{
    if(gu16_AD_Result_TDS_In_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_TDS_In_Temp >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
    }
    else if(gu16_AD_Result_TDS_In_Temp >= (512 - GAP) && gu16_AD_Result_TDS_In_Temp <= (512 + GAP)) //10k
    {
        //1단
        Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
    }
    else
    {
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
    }

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void tds_out_temp(void)
{
    if(gu16_AD_Result_TDS_Out_Temp <= TEMP_SENSOR_SHORT || gu16_AD_Result_TDS_Out_Temp >= TEMP_SENSOR_OPEN)
    {
        //에러
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
    }
    else if(gu16_AD_Result_TDS_Out_Temp >= (512 - GAP) && gu16_AD_Result_TDS_Out_Temp <= (512 + GAP)) //10k
    {
        //1단
        Bit6_Front_New_Led_Replace_Filter_2_Num = SET;
    }
    else
    {
        Bit6_Front_New_Led_Replace_Filter_2_Num = CLEAR;
    }

}
#endif
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

    ice_full();

    water_leak();

    /*boost_in();*/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_low_water(void)
{
    if(pLEVEL_PURIFY_LOW == SET)
    {
        Bit0_Front_Left_Led_Preparing_Text = SET;
    }
    else
    {
        Bit0_Front_Left_Led_Preparing_Text = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_high_water(void)
{
    if(pLEVEL_PURIFY_HIGH == SET)
    {
        Bit1_Front_Left_Led_Current_Text = SET;
    }
    else
    {
        Bit1_Front_Left_Led_Current_Text = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void draintank_low_water(void)
{
    if(pLEVEL_ICE_DRAIN_LOW == SET)
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = SET;
    }
    else
    {
        Bit2_Front_Left_Led_Filter_Flushing_Text = CLEAR;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void draintank_high_water(void)
{
    if(pLEVEL_ICE_DRAIN_HIGH == SET)
    {
        Bit3_Front_Left_Led_Eco_Icon = SET;
    }
    else
    {
        Bit3_Front_Left_Led_Eco_Icon = CLEAR;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full(void)
{
    /*ICE_IR_POW = 1;*/ /*만빙센서 발신부*/
    pIR_POWER = SET;

    if (gu16ADIceFull >= 230)
    {
        u8icefullcnt++;

        if(u8icefullcnt >= 3)
        {
            u8icefullcnt = 3;
            Bit4_Front_Left_Led_Fahrenheit_oF_Icon = SET;
        }
        else{}

    }
    else
    {
        u8icefullcnt = CLEAR;
        Bit4_Front_Left_Led_Fahrenheit_oF_Icon = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_leak(void)
{
    pLEAKAGE_ON = CLEAR;

    if (gu16ADLeakage > 750)
    {
        u8leakcnt++;

        if(u8leakcnt >= 3)
        {
            Bit5_Front_Left_Led_Percent_Icon = SET;
            Bit6_Front_Left_Led_Celcius_oC_Icon = SET;
        }
        else{}
    }
    else
    {
        u8leakcnt = 0;
        Bit5_Front_Left_Led_Percent_Icon = CLEAR;
        Bit6_Front_Left_Led_Celcius_oC_Icon = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void boost_in(void)
{
    #if 0
    if(pOUT_PUMP_IN == CLEAR)
    {
        Bit1_Front_Under_Icon_Led_Ice_Lock = SET;
    }
    else
    {
        Bit1_Front_Under_Icon_Led_Ice_Lock = CLEAR;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void switch_test(void)
{
    if(pREED_TANK_COVER == CLEAR)
    {
        Bit2_Front_Under_Icon_Led_Hot_Lock = SET;
    }
    else
    {
        Bit2_Front_Under_Icon_Led_Hot_Lock = CLEAR;
    }

    if(pREED_NEO_1_FILTER == CLEAR)
    {
        Bit0_Front_New_Led_Ice_Making_Text = SET;
    }
    else
    {
        Bit0_Front_New_Led_Ice_Making_Text = CLEAR;
    }


    if(pREED_RO_2_FILTER == CLEAR)
    {
        Bit6_Front_Right_Led_Days_Left_Text = SET;
    }
    else
    {
        Bit6_Front_Right_Led_Days_Left_Text = CLEAR;
    }

    if(pREED_INO_3_FILTER == CLEAR)
    {
        Bit1_Front_New_Led_Hot_Heating_Text = SET;
    }
    else
    {
        Bit1_Front_New_Led_Hot_Heating_Text = CLEAR;
    }

    if( pREED_ACID == CLEAR )
    {
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
    }
    else
    {
        Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
        Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }


    if( pREED_FILTER_COVER == CLEAR )
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
        ////Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
        /*Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;*/
        /*Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;*/
    }
    else
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
        /////Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
        Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
        /*Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;*/
        /*Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;*/
    }

    if(pICE_MICRO_SW_LOW == CLEAR)
    {
        Bit4_Front_Right_Led_Min_Left_Text = SET;
        Bit2_Front_New_Led_Cold_Cooling_Text = SET;
    }
    else
    {
        Bit4_Front_Right_Led_Min_Left_Text = CLEAR;
        Bit2_Front_New_Led_Cold_Cooling_Text = CLEAR;
    }

    if(pICE_MICRO_SW_HIGH == CLEAR)
    {
        Bit5_Front_Right_Led_ml_Text = SET;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
    }
    else
    {
        Bit5_Front_Right_Led_ml_Text = CLEAR;
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
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

        /*..hui [20-2-26오후 8:25:38] 제품으로도 테스트할수있도록 3초로 제한..*/
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

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_fan_output(void)
{


    if(gu8_ice_test_input == 1)
    {
        pCOMP = 1;
        pDC_FAN = 1;
        pSWING_BAR = 1;

    }
    else
    {
        pCOMP = 0;
        pDC_FAN = 0;
        pSWING_BAR = 0;
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

    if(gu8_hot_test_input == 0)
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


    ControlRoDrain();
    /*ControlMixFlow();*/

    if(gu8_ambient_test_input == 0)
    {
        bit_step_out_state = CLEAR;
    }
    else
    {
        if(bit_step_out_state == CLEAR)
        {
            bit_step_out_state = SET;

            /*run_init_flow();*/
            run_init_ro_drain();
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

        pUV_LED_ICE_TRAY_1_2 = 0;
        pUV_LED_ICE_TANK_3_FRONT = 0;
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

            pUV_LED_ICE_TRAY_1_2 = 1;
            pUV_LED_ICE_TANK_3_FRONT = 1;
        }
        else
        {
            pVALVE_NOS = 0;
            pVALVE_FEED = 1;

            pUV_LED_ICE_TRAY_1_2 = 1;
            pUV_LED_ICE_TANK_3_FRONT = 0;
        }
    }


    if(gu8_setting_ice_lock_test_input == 1)
    {
        pVALVE_AIR_VENT = 1;
        pUV_LED_ICE_TANK_1_2_BACK = 1;
        pUV_LED_WATER_TANK_1_2 = 1;
        pVALVE_FLUSHING_NOS = 1;
    }
    else
    {
        pVALVE_AIR_VENT = 0;
        pUV_LED_ICE_TANK_1_2_BACK = 0;
        pUV_LED_WATER_TANK_1_2 = 0;
        pVALVE_FLUSHING_NOS = 0;
    }


    if(gu8_setting_hot_lock_test_input == 1)
    {
        pVALVE_HOT_OUT = 1;
        pVALVE_COLD_OUT = 1;
        pVALVE_ROOM_OUT = 1;
        Bit2_Front_Led_Hot_Lock = SET;
    }
    else
    {
        pVALVE_HOT_OUT = 0;
        pVALVE_COLD_OUT = 0;
        pVALVE_ROOM_OUT = 0;
        Bit2_Front_Led_Hot_Lock = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void valve_output_two(void)
{
    if(gu8_setting_touch_lock_test_input == 1)
    {
        pVALVE_COLD_DRAIN = 1;
        Bit3_Front_Led_Touch_Lock = SET;
        pVALVE_ICE_TANK_STER_FEED_LEFT = 1;
        pVALVE_ICE_TANK_STER_FEED_RIGHT = 1;
        pVALVE_OVERHEATING_NOS = 1;
    }
    else
    {
        pVALVE_COLD_DRAIN = 0;
        Bit3_Front_Led_Touch_Lock = CLEAR;
        pVALVE_ICE_TANK_STER_FEED_LEFT = 0;
        pVALVE_ICE_TANK_STER_FEED_RIGHT = 0;
        pVALVE_OVERHEATING_NOS = 0;
    }

    #if 0
    if(gu8_setting_steam_off_test_input == 1)
    {
        pVALVE_ICE_TANK_STER_FEED_LEFT = 1;
        pVALVE_ICE_TANK_STER_FEED_RIGHT = 1;
        pVALVE_OVERHEATING_NOS = 1;

    }
    else
    {
        pVALVE_ICE_TANK_STER_FEED_LEFT = 0;
        pVALVE_ICE_TANK_STER_FEED_RIGHT = 0;
        pVALVE_OVERHEATING_NOS = 0;
    }
    #endif

    if(gu8_setting_eco_mode_test_input == 1)
    {
        pVALVE_ICE_TRAY_IN_FEED = 1;
        pVALVE_HOT_IN_FEED = 1;
        pVALVE_FLUSHING_FEED = 1;

    }
    else
    {
        pVALVE_ICE_TRAY_IN_FEED = 0;
        pVALVE_HOT_IN_FEED = 0;
        pVALVE_FLUSHING_FEED = 0;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_output(void)
{
    if(gu8_setting_ice_first_test_input != 0)
    {
        if( gu16_AD_Result_UV_Ice_Tray_1_2_Current >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Ice_Tray_1_2_Current <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        }
        else
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
        }

        //if(gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed >= 10)//40)
        //if( gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed >= UV_COUPLE__ERROR_CHECK_UNDER_AD
        //    || gu16_AD_Result_UV_Ice_Tray_Two_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        if( gu16_AD_Result_UV_Ice_Tank_3_Front_Current >= UV_SOLO__ERROR_CHECK_OVER_AD
            || gu16_AD_Result_UV_Ice_Tank_3_Front_Current <= UV_SOLO__ERROR_CHECK_UNDER_AD )
        {
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        }
        else
        {
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
        }
    }
    else
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        //Bit4_Front_Led_Temp_Fnd_Point = CLEAR;
    }

    if(gu8_setting_ice_lock_test_input != 0)
    {
        //if(gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current >= 10)//40)
        if( gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Ice_Tank_1_2_Back_Current <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            Bit4_Front_Led_Ice_Tank_Text = CLEAR;
        }
        else
        {
            Bit4_Front_Led_Ice_Tank_Text = SET;
        }

        //if(gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed >= 10)//40)
        if( gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed >= UV_COUPLE__ERROR_CHECT_OVER_AD
            || gu16_AD_Result_UV_Water_Tank_1_2_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            Bit2_Front_Led_Water_Tank_Text = CLEAR;
        }
        else
        {
            Bit2_Front_Led_Water_Tank_Text = SET;
        }
    }
    else
    {
        Bit2_Front_Led_Water_Tank_Text = CLEAR;
        Bit4_Front_Led_Ice_Tank_Text = CLEAR;

    }


    if( gu8_ice_test_input != 0 )
    {
        if( gu16_AD_Result_Fan_Current >= 10 )
        {
            Bit3_Front_Led_Ice_Tray_Text = SET;
        }
        else
        {
            Bit3_Front_Led_Ice_Tray_Text = CLEAR;
        }
    }
    else
    {
        Bit3_Front_Led_Ice_Tray_Text = CLEAR;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pump_output(void)
{
    if(gu8_water_ext_test_input == 0)
    {
        stop_drain_pump();
        Bit4_Front_Under_Led_Water_Extract = CLEAR;

        bit_comp_test = CLEAR;
    }
    else
    {
        start_drain_pump( PUMP_PWM_MAX );
        Bit4_Front_Under_Led_Water_Extract = SET;

        bit_comp_test = SET;
    }

    if(gu8_water_ext_test_input != 0)
    {
        //배수펌프 IAD
        if(gu16_AD_Drain_Pump_Current >= 5 && gu16_AD_Drain_Pump_Current <= 900) //795
        {
            u8_drain_cnt = 0;
            Bit4_Front_New_Led_Replace_Filter_Text = SET;
        }
        else
        {
            u8_drain_cnt++;
            if(u8_drain_cnt >= 10)
            {
                u8_drain_cnt = 10;
                 Bit4_Front_New_Led_Replace_Filter_Text = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_drain_cnt = 0;
        Bit4_Front_New_Led_Replace_Filter_Text = CLEAR;
    }


    if(gu8_ice_ext_test_input == 0)
    {
        stop_tray_pump();
        Bit3_Front_Under_Led_Ice_Extract = CLEAR;

        /*..hui [24-11-13오후 4:00:55] 드레인 전압 삭제..*/
        /*..hui [24-7-30오후 2:11:51] 드레인 수위센서 ON..*/
        /*pPower_Drain_Level = CLEAR;*/
    }
    else
    {
        start_tray_pump( PUMP_PWM_MAX );
        Bit3_Front_Under_Led_Ice_Extract = SET;

        /*..hui [24-11-13오후 4:00:55] 드레인 전압 삭제..*/
        /*..hui [24-7-30오후 2:11:44] 드레인 수위센서 OFF..*/
        /*pPower_Drain_Level = SET;*/
    }

    if(gu8_ice_ext_test_input != 0)
    {
        if(gu16_AD_Tray_Pump_Current >= 5 && gu16_AD_Tray_Pump_Current <= 900) //795
        {
            u8_hot_p_cnt = 0;
            Bit3_Front_Right_Led_OZ_Text = SET;
        }
        else
        {
            u8_hot_p_cnt++;
            if(u8_hot_p_cnt >= 10)
            {
                u8_hot_p_cnt = 10;
                Bit3_Front_Right_Led_OZ_Text = CLEAR;
            }
            else{}
        }
    }
    else
    {
        u8_hot_p_cnt = 0;
        Bit3_Front_Right_Led_OZ_Text = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_sensor(void)
{
    #if 0
    if(gu8_Tray_Flow_1sec > 5)
    {
        F_flow_detect = SET;
    }
    else{}
    #endif

    /*..hui [23-6-28오후 5:28:06] 트레이 유량센서..*/
    if(gu8_Tray_Flow_1sec >= 30  && gu8_Tray_Flow_1sec <= 70)
    {
        gu8_flow_test_timer++;

        if( gu8_flow_test_timer >= 10 )
        {
            gu8_flow_test_timer = 10;
            Bit0_Front_Led_Ice_Tank_Clean_Text = SET;
        }
        else{}
    }
    else
    {
        gu8_flow_test_timer = 0;
    }

    /*..hui [23-6-28오후 5:28:01] 필터 유량센서..*/
    if(gu8_Filter_Flow_1sec >= 30  && gu8_Filter_Flow_1sec <= 70)
    {
        gu8_filter_flow_test_timer++;

        if( gu8_filter_flow_test_timer >= 10 )
        {
            gu8_filter_flow_test_timer = 10;
            Bit1_Front_Led_UV_Care_Txt_Under_bar = SET;
        }
        else{}
    }
    else
    {
        gu8_filter_flow_test_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void tds_sensor(void)
{
    F_TDS_ON = SET;

    if(gu16_uart_test_pulse >= 5 && gu16_uart_test_pulse <= 100)
    {
        Bit2_Front_New_Led_Cold_Cooling_Text = SET;
    }
    else
    {
        Bit2_Front_New_Led_Cold_Cooling_Text = CLEAR;
    }

    if(gu16_AD_Result_TDS_Out_Data >= 5 && gu16_AD_Result_TDS_Out_Data <= 100)
    {
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
    }
    else
    {
        Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fault_ad_test(void)
{
    if( gu16_AD_Result_DC_Current_12V >= 15 )
    {
        Bit0_Front_Under_Txt_Led_Ice_First = SET;
    }
    else
    {
        ///////Bit0_Front_Under_Txt_Led_Ice_First = CLEAR;
    }

    if( gu16_AD_Result_DC_Current_24V >= 15 )
    {
        Bit1_Front_Led_Ice_Lock = SET;
    }
    else
    {
        ///////Bit1_Front_Led_Ice_Lock = CLEAR;
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
void bldc_comm_test(void)
{
    /*Bldc_Comp_Communication();*/

    if( bit_comp_test == SET )
    {
        gu8_bldc_target_hz = BLDC_COMP_65Hz;
    }
    else
    {
        gu8_bldc_target_hz = 0;
        bit_bldc_rx_pba_test_ok = CLEAR;
    }

    //////Bldc_Comp_Communication();

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

    if( bit_bldc_rx_pba_test_ok == SET )
    {
        Bit3_Front_New_Led_Low_Water_Text ^= SET;
    }
    else
    {
        Bit3_Front_New_Led_Low_Water_Text = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_test(void)
{
    if(GetWifiStatusValue(WIFI_STATUS_TEST) == SET)
    {
        Bit1_Front_Right_Led_Wifi_Icon_White = SET;
        Bit2_Front_Right_Led_Wifi_Icon_Blue = SET;
    }
    else
    {
        Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;
        Bit2_Front_Right_Led_Wifi_Icon_Blue ^= SET;
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
    //Bit8_Status_UV_Ster_Status_Test_Mode = AT_F_RxComplete;

    if( AT_gu8TX_ERROR >= 2)
    {
        //Bit8_Status_UV_Ster_Status_Test_Mode ^= 1;
        //Bit8_Status_UV_Ster_Status_Test_Mode = 1;
        Bit5_Front_Under_Led_Ice_Full ^= SET;
    }
    else
    {
        //Bit8_Status_UV_Ster_Status_Test_Mode = AT_F_RxComplete;
        Bit5_Front_Under_Led_Ice_Full = AT_F_RxComplete;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void PCB_Test_Mode_Key_Short_Input( U16 u16key_input_value)
{
    U8 mu8_return = 0;

    if(u8FactoryTestMode == DISPLAY_TEST_MODE)
    {
        if( bit_display_test_filter_reed_error == SET )
        {
            play_melody_warning_197();
            return;
        }
        else
        {
            if( gu8_display_test_error == 0 )
            {
                /*play_melody_select_196();*/
                play_voice_test_mode_151();
            }
            else
            {
                play_melody_warning_197();
                return;
            }
        }
    }
    else
    {
        /*play_melody_select_196();*/
        play_voice_test_mode_151();
    }

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
                    play_melody_warning_197();
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
            if( u8FactoryTestMode == PCB_TEST_MODE )
            {
                gu8_setting_ice_lock_test_input++;

                if(gu8_setting_ice_lock_test_input >= 2)
                {
                    gu8_setting_ice_lock_test_input = 0;
                }
                else{}
            }
            else
            {
                /*..hui [23-12-20오전 9:57:15] 디스플레이 테스트모드에서 wifi 화이트 -> 블루 순서로 검사해야 함..*/
                /*..hui [23-12-20오전 9:57:40] ice lock 부터 누르면 led가 off되기때문에 ice first가 눌린 상태에서만 눌리도록.....*/
                if( gu8_setting_ice_first_test_input == 1 )
                {
                    gu8_setting_ice_lock_test_input++;

                    if(gu8_setting_ice_lock_test_input >= 2)
                    {
                        gu8_setting_ice_lock_test_input = 0;
                    }
                    else{}
                }
                else
                {
                    play_melody_warning_197();
                }
            }

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

        case KEY_SETTING_TOUCH_LOCK:
            //
            gu8_setting_touch_lock_test_input++;

            if(gu8_setting_touch_lock_test_input >= 2)
            {
                gu8_setting_touch_lock_test_input = 0;
            }
            else{}

        break;

        #if 0
        case KEY_SETTING_STEAM_OFF:
            //
            gu8_setting_steam_off_test_input++;

            if(gu8_setting_steam_off_test_input >= 2)
            {
                gu8_setting_steam_off_test_input = 0;
            }
            else{}

        break;
        #endif

        case KEY_SETTING_ECO_MODE:
            //
            gu8_setting_eco_mode_test_input++;

            if(gu8_setting_eco_mode_test_input >= 2)
            {
                gu8_setting_eco_mode_test_input = 0;
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

     if(u8FactoryTestMode == DISPLAY_TEST_MODE)
     {
         if( bit_display_test_filter_reed_error == SET )
         {
             play_melody_warning_197();
             return;
         }
         else
         {
             if( gu8_display_test_error == 0 )
             {
                 /*play_melody_select_196();*/
                 play_voice_test_mode_151();
             }
             else
             {
                 play_melody_warning_197();
                 return;
             }

         }

     }
     else
     {
         /*play_melody_select_196();*/
         play_voice_test_mode_151();
     }


     gu8_water_ext_test_input++;

     /*if(gu8_water_ext_test_input >= 2)*/
     /*if(gu8_water_ext_test_input >= 4)*/
     /*if(gu8_water_ext_test_input >= 5)*/
     /*..hui [23-12-11오전 11:11:15] 추출버튼 한번 누르면 자동으로 변경되는걸로....*/
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


            if(u8FactoryTestMode == DISPLAY_TEST_MODE)
            {
                if( bit_display_test_filter_reed_error == SET )
                {
                    play_melody_warning_197();
                    return;
                }
                else
                {
                    if( gu8_display_test_error == 0 )
                    {
                        /*play_melody_select_196();*/
                        play_voice_test_mode_151();
                    }
                    else
                    {
                        play_melody_warning_197();
                        return;
                    }

                }

            }
            else
            {
                /*play_melody_select_196();*/
                play_voice_test_mode_151();
            }



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
    /*..hui [19-10-31오전 11:05:54] 검사 완료된후에 진입 가능하도록..*/
    if(gu8_eeprom_initial_test_input == 1)
    {
        eeprom_initial();
        gu8_eeprom_initial_test_input = 0;
        /*FactoryResetRtc();*/
        InitRtcTime();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



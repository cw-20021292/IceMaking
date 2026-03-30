/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "display_led.h"



void led_display(void);
void display_normal_state(void);
void ice_full_led_output(void);
void funcition_led_output(void);
void icon_led_out(void);
void ice_lock_icon_output(void);
void hot_lock_icon_output(void);
//void all_lock_icon_output(void);
void save_icon_output(void);
void ice_first_icon_output(void);
void temp_led_out(void);
void hot_temp_led_out(void);
void cold_temp_led_out(void);
void low_water_led_out(void);
//void auto_drain_led_out(void);
void am_pm_led_out(void);
void cup_level_led_out(void);
void extract_led_out(void);
void uv_led_out(void);
void percent_ml_led_out(void);
void setting_led_out(void);
void set_led_duty( U8 mu8_number, U8 mu8_duty );
void set_icon_duty( U8 mu8_number, U8 mu8_on_off );

void led_time_setting_state(void);

TYPE_BYTE          U8ButtonIndicatorB;
#define            gu8_bitton_indicator                        U8ButtonIndicatorB.byte
#define            Bit0_Ice_Lock_Indicator                     U8ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U8ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U8ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U8ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U8ButtonIndicatorB.Bit.b4
#define            Bit5_Low_Water_Indicator                    U8ButtonIndicatorB.Bit.b5
#define            Bit6_Ice_Off_Indicator                      U8ButtonIndicatorB.Bit.b6


U16 gu16_my_cup_level_pure;
U16 gu16_my_cup_level_cold;
U16 gu16_my_cup_level_hot;

bit bit_my_cup_enable;
bit bit_my_cup_first_display;

U8 gu8_my_cup_flick_timer;
U8 gu8_test_pwm;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_display(void)
{
    U8 mu8_return = 0;
    static LED_STEP before_display;

    switch( gu8_Led_Display_Step )
    {
        case LED_Display__VERSION:

            if( before_display == LED_Display__VERSION
                || before_display > LED_Display__VERSION )
            {
                before_display = LED_Display__VERSION;
            }
            else{}

            display_version();

            break;

        case LED_Display__ALL_LOCK:

            if( before_display != LED_Display__ALL_LOCK )
            {
                before_display = LED_Display__ALL_LOCK;
                off_all_control_led();
            }
            else{}

            display_all_lock();
            fnd_all_lock();

            break;

        case LED_Display__FOTA_START:

            if( before_display != LED_Display__FOTA_START )
            {
                before_display = LED_Display__FOTA_START;
                off_all_control_led();
            }
            else{}

            off_all_control_led();
			
            Bit3_Led_Wifi_Icon_White = SET;

            break;

        case LED_Display__SELF_TEST:

            if( before_display != LED_Display__SELF_TEST )
            {
                before_display = LED_Display__SELF_TEST;
                off_all_control_led();
				
            }
            else{}
			
			fnd_self_test_state();
            led_self_test_state();

            break;

        case LED_Display__ALTITUDE_SETTING:

            if( before_display != LED_Display__ALTITUDE_SETTING )
            {
                before_display = LED_Display__ALTITUDE_SETTING;
                off_all_control_led();
            }
            else{}

            display_altitude_setting();
            fnd_altitude_setting();

            break;

        case LED_Display__MEMENTO:

            if( before_display != LED_Display__ALTITUDE_SETTING )
            {
                before_display = LED_Display__ALTITUDE_SETTING;
            }
            else{}

            display_normal_state();
            fnd_memento();

            break;

        #if 0
        case LED_Display__SETTING_MY_CUP:

            if( before_display != LED_Display__SETTING_MY_CUP )
            {
                before_display = LED_Display__SETTING_MY_CUP;
                off_all_control_led();
            }
            else{}

            display_my_cup_setting();
            fnd_my_cup_setting_state();

            break;
        #endif

        case LED_Display__WATER_EXTRACT:

            if( before_display != LED_Display__WATER_EXTRACT )
            {
                before_display = LED_Display__WATER_EXTRACT;
                gu8_fnd_water_step = 0;
                gu8_fnd_continue_step = 0;
                gu8_my_cup_extract_timer = 0;
            }
            else{}

            display_normal_state();
            fnd_water_out();

            break;


        case LED_Display__ICE_EXTRACT:

            if( before_display != LED_Display__ICE_EXTRACT )
            {
                before_display = LED_Display__ICE_EXTRACT;
                gu8_fnd_ice_step = 0;
                gu8_fnd_ice_timer = 0;
            }
            else{}

            display_normal_state();
            fnd_ice_out();

            break;

        case LED_Display__SETTING:

            if( before_display != LED_Display__SETTING )
            {
                before_display = LED_Display__SETTING;
                off_all_control_led();
            }
            else{}

            display_setting();
            fnd_setting();

            break;

        case LED_Display__SLEEP:

            if( before_display != LED_Display__SLEEP )
            {
                before_display = LED_Display__SLEEP;
                off_all_control_led();
            }
            else{}

            display_sleep();
            fnd_sleep();

            break;

        case LED_Display__ERROR:

            if( before_display != LED_Display__ERROR )
            {
                before_display = LED_Display__ERROR;
                gu8_error_flick_timer = 0;
                gu8_error_flick_cnt = 0;
            }
            else{}

            display_normal_state();
            fnd_error();

            break;

        case LED_Display__DEBUG:

            if( before_display != LED_Display__DEBUG )
            {
                before_display = LED_Display__DEBUG;
            }
            else{}

            display_normal_state();
            fnd_debug();

            break;

        case LED_Display__BUTTON_SET:

            if( before_display != LED_Display__BUTTON_SET )
            {
                before_display = LED_Display__BUTTON_SET;
                off_all_control_led();
            }
            else{}

            /*display_normal_state();*/
            /*..hui [24-4-24오후 7:09:37] 추가..*/
            led_button_set();
            fnd_button_set();

            break;
#if CONFIG_TIME_SETTING
        case LED_Display__TIME_SETTING:

            if( before_display != LED_Display__TIME_SETTING )
            {
                before_display = LED_Display__TIME_SETTING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_time_set();
            fnd_time_set();

            break;
#endif

        case LED_Display__WIFI_PAIRING:
		

            if( before_display != LED_Display__WIFI_PAIRING )
            {
                before_display = LED_Display__WIFI_PAIRING;
                off_all_control_led();
                //all_dimming_full_on();
                
	            u8PairingStep = 0;
	            gu8_pairing_finish_timer = 0;

	            bit_display_wifi_error = CLEAR;
            }
            else{}

            led_wifi_pairing();
            fnd_wifi_set();

            break;
#if 0
        case LED_Display__WIFI_CONNECTED:

            if( before_display != LED_Display__WIFI_PAIRING )
            {
                before_display = LED_Display__WIFI_PAIRING;
                off_all_control_led();
                //all_dimming_full_on();
            }
            else{}

            led_wifi_pairing();
            fnd_wifi_set();

            break;
#endif
        case LED_Display__MAIN:

            if( before_display != LED_Display__MAIN )
            {
                before_display = LED_Display__MAIN;
                bit_default_cup_flick = CLEAR;
            }
            else{}

            display_normal_state();
            fnd_normal_state();

			//추출 종료 후 30분 후부터 표시되도록 변경 
			if(gu8_Led_Display_Step == LED_Display__WATER_EXTRACT)
			{
		        if( gu16_wifi_pairing_30min_timer >= WIFI_PAIRING_START_30_MIN )
		        {
		            /*..hui [24-8-6오전 10:52:13] 30분 경과후부터 추출 종료후 5초 동안 표시..*/
		            bit_pairing_5s_display_start = SET;
		        }
		        else{}
			}

            break;

        default:

            gu8_Led_Display_Step = LED_Display__VERSION;

            break;
    }


    /*..hui [23-2-8오후 1:58:51] 에러 발생상태일 경우 얼음추출, 물 추출 후 에러 화면 표시..*/
    if( gu8_Led_Display_Step == LED_Display__WATER_EXTRACT
        || gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        if( gu8_Error_Code > 0 )
        {
            gu8_error_popup_enable = SET;
        }
        else{}
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_normal_state(void)
{
    funcition_led_output();
    temp_led_out();
    cup_level_led_out();
    extract_led_out();
    setting_led_out();


    /*..hui [23-2-10오후 2:45:03] 기타 아이콘들 흐리게 켜질떄 PWM..*/
    set_led_duty( DUTY_OUT_ETC_ICON, DUTY_100_PERCENT);

    ice_full_led_output();
    icon_led_out();
    low_water_led_out();
    //auto_drain_led_out();
    am_pm_led_out();
    uv_led_out();
    percent_ml_led_out();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full_led_output(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        set_icon_duty( DIMMING__ICE_FULL, ICON_DIIMMING_FULL_ON );
    }
    else
    {
        set_icon_duty( DIMMING__ICE_FULL, ICON_DIIMMING_10_PERCENT_ON );
    }

    if( F_IceFull == SET )
    {
        Bit6_Front_Led_Ice_Full = SET;
    }
    else
    {
        Bit6_Front_Led_Ice_Full = CLEAR;
    }
	#if 0
	/*sean [25-03-21] 얼음 기능이 꺼져있을 때에는 표시안함 */
    if( F_IceOn == SET )
    {
        Bit6_Front_Led_Ice_Full = SET;
    }
    else
    {
        Bit6_Front_Led_Ice_Full = CLEAR;
    }
	#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void funcition_led_output(void)
{
    U8 mu8_flick_state = 0;
    U8 mu8_cold_flick_state = 0;
    U8 mu8_hot_flick_state = 0;

    if( Bit0_Ice_Lock_Indicator == SET )
    {
        mu8_flick_state = indicator_flick_timer(5, 5);

        if( mu8_flick_state == SET )
        {
            Bit0_Front_Led_Set_Select = SET;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            Bit0_Front_Led_Set_Select = CLEAR;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        }
    }
    else if( Bit1_Hot_Lock_Indicator == SET )
    {
        mu8_flick_state = indicator_flick_timer(5, 5);

        if( mu8_flick_state == SET )
        {
            Bit0_Front_Led_Set_Select = SET;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            Bit0_Front_Led_Set_Select = CLEAR;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        }
    }
    else
    {
        /*..hui [23-3-23오전 9:08:37] 마이컵 추출할때는 표시하지 않는걸로.. 디자인팀..*/
		/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    //if( bit_illumi_State == SET )
	    if(bit_sleep_mode_start == SET)
        {
            Bit0_Front_Led_Set_Select = SET;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_20_PERCENT);
        }
        else
        {
            /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
            Bit0_Front_Led_Set_Select = CLEAR;
            set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_IceOn == SET )
    {
        Bit1_Front_Led_Ice_Select = SET;
        set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_100_PERCENT);
    }
    else
    {
        /*Bit1_Front_Led_Ice_Select = CLEAR;*/
        set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_100_PERCENT);

        /*..hui [24-4-24오후 6:55:05] 얼음 OFF일때 얼음버튼 누르면 LED 점멸 추가..*/
        if( Bit6_Ice_Off_Indicator == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
        }
        else
        {
            mu8_hot_flick_state = ice_off_flickering_timer(5, 5);

            if( mu8_hot_flick_state == SET )
            {
                Bit1_Front_Led_Ice_Select = SET;

            }
            else
            {
                Bit1_Front_Led_Ice_Select = CLEAR;
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    //if( F_Hot_Lock == SET )
    if( F_Hot_Enable == SET )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            Bit2_Front_Led_Hot_Select = SET;
            set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            #if 0
            Bit2_Front_Led_Hot_Select = SET;
            set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_20_PERCENT);
            #endif
			
			/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
			//if( bit_illumi_State == SET )
			if(bit_sleep_mode_start == SET)

            {
                Bit2_Front_Led_Hot_Select = SET;
                set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_20_PERCENT);
            }
            else
            {
                /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
                Bit2_Front_Led_Hot_Select = CLEAR;
                set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
            }
        }
    }
    else
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( Bit3_Hot_Off_Indicator == CLEAR )
            {
                Bit2_Front_Led_Hot_Select = SET;
                set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
            }
            else
            {
                mu8_hot_flick_state = hot_off_flickering_timer(5, 5);

                if( mu8_hot_flick_state == SET )
                {
                    Bit2_Front_Led_Hot_Select = SET;
                    set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);

                }
                else
                {
                    Bit2_Front_Led_Hot_Select = CLEAR;
                    set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
                }
            }
        }
        else
        {
            /*Bit2_Front_Led_Hot_Select = CLEAR;*/
            /*set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);*/

            /*..hui [23-2-24오전 10:34:45] 야간모드에서는 흐리게..*/
            /*..hui [23-2-24오전 10:35:08] AIS3.5가 온수 꺼져있어도 흐리게 켜져있음 야간에는....*/
			/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
		    //if( bit_illumi_State == SET )
			    if(bit_sleep_mode_start == SET)
            {
                Bit2_Front_Led_Hot_Select = SET;
                set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_20_PERCENT);
            }
            else
            {
                /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
                Bit2_Front_Led_Hot_Select = CLEAR;
                set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        Bit3_Front_Led_Ambient_Select = SET;
        set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_100_PERCENT);
    }
    else
    {
        #if 0
        Bit3_Front_Led_Ambient_Select = SET;
        set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_20_PERCENT);
        #endif

		/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    //if( bit_illumi_State == SET )
	    if(bit_sleep_mode_start == SET)

        {
            Bit3_Front_Led_Ambient_Select = SET;
            set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_20_PERCENT);
        }
        else
        {
            /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
            Bit3_Front_Led_Ambient_Select = CLEAR;
            set_led_duty( DUTY_OUT_AMBIENT_SELECT, DUTY_100_PERCENT);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( F_Cold_Enable == SET )
    {
        if( u8WaterOutState == COLD_WATER_SELECT )
        {
            Bit4_Front_Led_Cold_Select = SET;
            set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            #if 0
            Bit4_Front_Led_Cold_Select = SET;
            set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_20_PERCENT);
            #endif
			
			/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
			//if( bit_illumi_State == SET )
			if(bit_sleep_mode_start == SET)

            {
                Bit4_Front_Led_Cold_Select = SET;
                set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_20_PERCENT);
            }
            else
            {
                /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
                Bit4_Front_Led_Cold_Select = CLEAR;
                set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
            }
        }
    }
    else
    {
        if( u8WaterOutState == COLD_WATER_SELECT )
        {
            if( Bit2_Cold_Off_Indicator == CLEAR )
            {
                Bit4_Front_Led_Cold_Select = SET;
                set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
            }
            else
            {
                mu8_cold_flick_state = cold_off_flickering_timer(5, 5);

                if( mu8_cold_flick_state == SET )
                {
                    Bit4_Front_Led_Cold_Select = SET;
                    set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
                }
                else
                {
                    Bit4_Front_Led_Cold_Select = CLEAR;
                    set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
                }
            }
        }
        else
        {
            /*Bit4_Front_Led_Cold_Select = CLEAR;*/
            /*set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);*/
			
			/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
			//if( bit_illumi_State == SET )
			if(bit_sleep_mode_start == SET)

            {
                Bit4_Front_Led_Cold_Select = SET;
                set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_20_PERCENT);
            }
            else
            {
                /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
                Bit4_Front_Led_Cold_Select = CLEAR;
                set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    if( gu8_cup_led_select == SET )
    {
        /*..hui [20-1-7오전 10:01:44] 물 추출하면 즉시 OFF..*/
        if( F_WaterOut == SET )
        {
            gu8_cup_led_select = CLEAR;
        }
        else{}

        gu8_cup_led_off_time++;

        /*..hui [20-1-7오전 10:01:54] 선택하고 7초 후 OFF..*/
        if( gu8_cup_led_off_time < CUP_SELECT_LED_OFF_TIME )
        {
            Bit5_Front_Led_Amount_Select = SET;
            set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_100_PERCENT);
        }
        else
        {
            gu8_cup_led_select = CLEAR;
        }
    }
    else
    {
        gu8_cup_led_off_time = 0;

        #if 0
        Bit5_Front_Led_Amount_Select = SET;
        set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_20_PERCENT);
        #endif

		/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    //if( bit_illumi_State == SET )
	    if(bit_sleep_mode_start == SET)

        {
            Bit5_Front_Led_Amount_Select = SET;
            set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_20_PERCENT);
        }
        else
        {
            /*..hui [23-2-22오후 1:30:55] 주간모드에서는 끄고있는걸로..*/
            Bit5_Front_Led_Amount_Select = CLEAR;
            set_led_duty( DUTY_OUT_AMOUNT_SELECT, DUTY_100_PERCENT);
        }
    }

	//time setting LED 표시 추가
    if( bit_time_setting_start == SET )
    {
    	//표시부 미확정
        //Bit1_Front_Led_Ice_Select = SET;
        //set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_100_PERCENT);

	    Bit0_Front_Led_Set_Select = SET;
	    Bit2_Front_Led_Hot_Select = SET;
	    Bit4_Front_Led_Cold_Select = SET;
		
        set_led_duty( DUTY_OUT_SET_SELECT, DUTY_100_PERCENT);
        set_led_duty( DUTY_OUT_HOT_SELECT, DUTY_100_PERCENT);
        set_led_duty( DUTY_OUT_COLD_SELECT, DUTY_100_PERCENT);
    }
    else
    {
		//UI 디자인 사양 미확정
#if 0
        /*Bit1_Front_Led_Ice_Select = CLEAR;*/
        set_led_duty( DUTY_OUT_ICE_SELECT, DUTY_100_PERCENT);

        /*..hui [24-4-24오후 6:55:05] 얼음 OFF일때 얼음버튼 누르면 LED 점멸 추가..*/
        if( Bit6_Ice_Off_Indicator == CLEAR )
        {
            Bit1_Front_Led_Ice_Select = CLEAR;
        }
        else
        {
            mu8_hot_flick_state = ice_off_flickering_timer(5, 5);

            if( mu8_hot_flick_state == SET )
            {
                Bit1_Front_Led_Ice_Select = SET;

            }
            else
            {
                Bit1_Front_Led_Ice_Select = CLEAR;
            }
        }
#endif
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void icon_led_out(void)
{
    ice_lock_icon_output();
    hot_lock_icon_output();
    //all_lock_icon_output();
    save_icon_output();
    ice_first_icon_output();
	
    wifi_icon_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_lock_icon_output(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        set_icon_duty( DIMMING__ICON_ICE_LOCK, ICON_DIIMMING_FULL_ON );
    }
    else
    {
        set_icon_duty( DIMMING__ICON_ICE_LOCK, ICON_DIIMMING_10_PERCENT_ON  );
    }

    if( F_Ice_Lock == SET )
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
void hot_lock_icon_output(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        set_icon_duty( DIMMING__ICON_HOT_LOCK, ICON_DIIMMING_FULL_ON );
    }
    else
    {
        set_icon_duty( DIMMING__ICON_HOT_LOCK, ICON_DIIMMING_10_PERCENT_ON  );
    }

    if( F_Hot_Lock == SET )
    {
        Bit7_Front_Led_Icon_Hot_Lock = SET;
    }
    else
    {
        Bit7_Front_Led_Icon_Hot_Lock = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_lock_icon_output(void)
{
#if 0
    set_icon_duty( DIMMING__ICON_ALL_LOCK, ICON_DIIMMING_FULL_ON );

    if( F_All_Lock == SET )
    {
        Bit5_Front_Led_Icon_All_Lock = SET;
    }
    else
    {
        Bit5_Front_Led_Icon_All_Lock = CLEAR;
    }
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void save_icon_output(void)
{
    set_icon_duty( DIMMING__ICON_SAVE, ICON_DIIMMING_FULL_ON );

    /*if( F_Save == SET )*/
    if( bit_sleep_mode_enable == SET )
    {
        Bit6_Front_Led_Icon_Save = SET;
    }
    else
    {
        Bit6_Front_Led_Icon_Save = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_first_icon_output(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        set_icon_duty( DIMMING__ICE_FIRST, ICON_DIIMMING_FULL_ON );
    }
    else
    {
        set_icon_duty( DIMMING__ICE_FIRST, ICON_DIIMMING_10_PERCENT_ON );
    }

	/*sean [25-03-21] 얼음 기능이 꺼져있을 때에는 표시안함 */
    #if 1
    /*..hui [23-5-17오후 1:16:14] 얼음 켜져있을때만 ice first 아이콘 점등.. 꺼져있을땐 소등.. DR 내용..*/
    if( F_IceOn == SET )
    {
        if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
        {
            Bit7_Front_Led_Icon_Ice_First = SET;
        }
        else
        {
            Bit7_Front_Led_Icon_Ice_First = CLEAR;
        }
    }
    else
    {
        Bit7_Front_Led_Icon_Ice_First = CLEAR;
    }
    #endif
#if 0
    /*..hui [23-6-19오전 9:12:49] 원복.. 설정 들어갔을때 얼음우선 LED 꺼짐..*/
    if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
    {
        Bit7_Front_Led_Icon_Ice_First = SET;
    }
    else
    {
        Bit7_Front_Led_Icon_Ice_First = CLEAR;
    }
#endif
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void temp_led_out(void)
{
    hot_temp_led_out();
    cold_temp_led_out();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_temp_led_out(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        /*set_icon_duty( DIMMING__HOT_TEMP, ICON_DIIMMING_FULL_ON );*/
    	/*.. sean [25-3-18 사양 정리] Ro Lite 디자인 최종 사양 ..*/
        set_led_duty( DUTY_OUT_HOT_TEMP, DUTY_EXTRACT_40_PERCENT);
    }
    else
    {
    	/*.. sean [25-3-18 사양 정리] Ro Lite 디자인 최종 사양 ..*/
        /*set_icon_duty( DIMMING__HOT_TEMP, ICON_DIIMMING_10_PERCENT_ON );*/
        set_led_duty( DUTY_OUT_HOT_TEMP, DUTY_20_PERCENT);
    }

    if( F_Hot_Enable == SET )
    {
        switch( gu8HotTemp )
        {
            case TEMP_DISPLAY_0_INIT:
            case TEMP_DISPLAY_1_LOW:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = CLEAR;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_2_MID:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = SET;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_3_HIGH:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = SET;
                Bit2_Front_Led_Hot_Temp_3 = SET;
                break;

            default:

                Bit0_Front_Led_Hot_Temp_1 = SET;
                Bit1_Front_Led_Hot_Temp_2 = CLEAR;
                Bit2_Front_Led_Hot_Temp_3 = CLEAR;
                break;
        }
    }
    else
    {
        Bit0_Front_Led_Hot_Temp_1 = CLEAR;
        Bit1_Front_Led_Hot_Temp_2 = CLEAR;
        Bit2_Front_Led_Hot_Temp_3 = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp_led_out(void)
{
    if( bit_sleep_mode_start == CLEAR )
    {
        /*set_icon_duty( DIMMING__COLD_TEMP, ICON_DIIMMING_FULL_ON );*/
    	/*.. sean [25-3-18 사양 정리] Ro Lite 디자인 최종 사양 ..*/
        set_led_duty( DUTY_OUT_COLD_TEMP, DUTY_EXTRACT_40_PERCENT);
    }
    else
    {
        /*set_icon_duty( DIMMING__COLD_TEMP, ICON_DIIMMING_10_PERCENT_ON );*/
        set_led_duty( DUTY_OUT_COLD_TEMP, DUTY_20_PERCENT);
    }

    if( F_Cold_Enable == SET )
    {
        switch( gu8ColdTemp )
        {
            case TEMP_DISPLAY_0_INIT:
            case TEMP_DISPLAY_1_LOW:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = CLEAR;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_2_MID:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = SET;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;

            case TEMP_DISPLAY_3_HIGH:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = SET;
                Bit5_Front_Led_Cold_Temp_3 = SET;
                break;

            default:

                Bit3_Front_Led_Cold_Temp_1 = SET;
                Bit4_Front_Led_Cold_Temp_2 = CLEAR;
                Bit5_Front_Led_Cold_Temp_3 = CLEAR;
                break;
        }
    }
    else
    {
        Bit3_Front_Led_Cold_Temp_1 = CLEAR;
        Bit4_Front_Led_Cold_Temp_2 = CLEAR;
        Bit5_Front_Led_Cold_Temp_3 = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void low_water_led_out(void)
{
    U8 mu8_low_water_flick_state = 0;

    set_icon_duty( DIMMING__LOW_WATER, ICON_DIIMMING_FULL_ON );

    #if 0
    if(gu8_Room_Water_Level != ROOM_LEVEL_LOW)
    {
        Bit7_Front_Led_Low_Water = CLEAR;
    }
    else
    {
        Bit7_Front_Led_Low_Water = SET;
    }
    #endif

    if(gu8_Room_Water_Level != ROOM_LEVEL_LOW)
    {
        Bit7_Front_Led_Low_Water = CLEAR;
    }
    else
    {
        /*Bit7_Front_Led_Low_Water = SET;*/

        if( Bit5_Low_Water_Indicator == CLEAR )
        {
            Bit7_Front_Led_Low_Water = SET;
        }
        else
        {
            mu8_low_water_flick_state = low_water_flick_timer(3, 5);

            if( mu8_low_water_flick_state == SET )
            {
                Bit7_Front_Led_Low_Water = SET;
            }
            else
            {
                Bit7_Front_Led_Low_Water = CLEAR;
            }
        }

    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void am_pm_led_out(void)
{
	
    set_icon_duty( DIMMING__AM, ICON_DIIMMING_FULL_ON );
    set_icon_duty( DIMMING__PM, ICON_DIIMMING_FULL_ON );

	// WIFI 연결 후 정상적으로 시간 받아왔을 때에, 
    //if( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) /* && ( gu8_wifi_time_Hour != 0 ) && ( gu8_wifi_time_Min != 0 ) */)
	if( (GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && (GetWifiStatusValue(WIFI_STATUS_PAIRING) == CLEAR ) 
		/*&& ( gu8_cup_led_select == CLEAR ) */&& ( gu16_water_return_wifi_time == 0 )  )
    {
		if(gu8_rtc_time_Hour >= 12)
		{
			Bit0_Time_Led_AM = CLEAR;
	        Bit1_Time_Led_PM = SET;
			Bit2_Time_Led_Colon = SET;
		}
		else 
		{
			Bit0_Time_Led_AM = SET;
	        Bit1_Time_Led_PM = CLEAR;
			Bit2_Time_Led_Colon = SET;
		}
		
		if( (gu8_cup_led_select == SET) || (F_WaterOut == SET) || (F_Key_IceExtraction == SET) ) //if
		{
	        Bit0_Time_Led_AM = CLEAR;
	        Bit1_Time_Led_PM = CLEAR;
			Bit2_Time_Led_Colon = CLEAR;
		}
		else {}
    }
    else
    {
        Bit0_Time_Led_AM = CLEAR;
        Bit1_Time_Led_PM = CLEAR;
		Bit2_Time_Led_Colon = CLEAR;
    }

	//error일 경우에는 colon 표시 삭제
	if( gu8_Led_Display_Step == LED_Display__ERROR )
	{
		if(u32ControlErrors > 0 )
			Bit2_Time_Led_Colon = CLEAR;
		else {}
	}
}

#if 0
void auto_drain_led_out(void)
{
	/*
    set_icon_duty( DIMMING__AUTO_DRAIN, ICON_DIIMMING_FULL_ON );

    if( F_DrainStatus == SET )
    {
        Bit6_Front_Led_Auto_Drain = SET;
    }
    else
    {
        Bit6_Front_Led_Auto_Drain = CLEAR;
    }
	*/
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_led_out(void)
{
    if( bit_my_cup_setting_start == SET )
    {
        Bit6_Front_Led_half_Cup = CLEAR;
        set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
		
        Bit3_Front_Led_1_Cup = CLEAR;
        set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

        Bit2_Front_Led_2_Cups = CLEAR;
        set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

        Bit1_Front_Led_Pot = CLEAR;
        set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

        /*..hui [23-3-3오후 4:51:56] 설정중에는 마이컵 점등, 추출버튼 점멸로.. 고차장님..*/
        /*..hui [23-3-3오후 4:52:06] 둘 다 깜빡거리면 이상함..*/
        Bit0_Front_Led_Cont = SET;
        set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);

        return;
    }
    else
    {
        gu8_my_cup_flick_timer = 0;
    }

    if( gu8_cup_led_select == SET )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_20_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_20_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
        }
        else if(gu8Cup_level == CUP_LEVEL_ONE)
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_20_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_20_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }

        }
        else if(gu8Cup_level == CUP_LEVEL_TWO)
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_20_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_20_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
        }
        else if(gu8Cup_level == CUP_LEVEL_FOUR)
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_20_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_20_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_20_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);
			
			Bit0_Front_Led_Cont = SET;
			set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
        }
        else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_20_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_20_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_20_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_20_PERCENT);
			
			Bit0_Front_Led_Cont = SET;
			set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
        }
        else /*if(gu8Cup_level == CUP_LEVEL_MY_CUP)*/
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_20_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_20_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_20_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_20_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_20_PERCENT);
            }
        }
    }
    else
    {
    	/*..일반 모드에서는  시계 표시하면서  LED 꺼지도록 변경  ..*/
		//if( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR )		
	    if( (GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && (GetWifiStatusValue(WIFI_STATUS_PAIRING) == CLEAR )
			/*&& ( gu8_cup_led_select == CLEAR )*/ && ( gu16_water_return_wifi_time == 0 )  )
		{
            Bit6_Front_Led_half_Cup = CLEAR;
            Bit3_Front_Led_1_Cup = CLEAR;
            Bit2_Front_Led_2_Cups = CLEAR;
            Bit1_Front_Led_Pot = CLEAR;
            Bit0_Front_Led_Cont = CLEAR;
			return;
		}
		else {}
		
		if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            Bit6_Front_Led_half_Cup = SET;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = CLEAR;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = CLEAR;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = CLEAR;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

            Bit0_Front_Led_Cont = CLEAR;
            set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
        }
        else if(gu8Cup_level == CUP_LEVEL_ONE)
        {
            Bit6_Front_Led_half_Cup = CLEAR;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = SET;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = CLEAR;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = CLEAR;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

            Bit0_Front_Led_Cont = CLEAR;
            set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
        }
        else if(gu8Cup_level == CUP_LEVEL_TWO)
        {
            Bit6_Front_Led_half_Cup = CLEAR;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = CLEAR;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = SET;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = CLEAR;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

            Bit0_Front_Led_Cont = CLEAR;
            set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);

        }
        else if(gu8Cup_level == CUP_LEVEL_FOUR)
        {
            Bit6_Front_Led_half_Cup = CLEAR;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = CLEAR;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = CLEAR;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = SET;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

            Bit0_Front_Led_Cont = CLEAR;
            set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);

        }
        else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
        {
            Bit6_Front_Led_half_Cup = CLEAR;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = CLEAR;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = CLEAR;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = CLEAR;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);
			
			Bit0_Front_Led_Cont = CLEAR;
			set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);

            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
            }
        }
        else /*if(gu8Cup_level == CUP_LEVEL_MY_CUP)*/
        {
            Bit6_Front_Led_half_Cup = CLEAR;
            set_led_duty( DUTY_OUT_HALF_CUP, DUTY_100_PERCENT);
			
            Bit3_Front_Led_1_Cup = CLEAR;
            set_led_duty( DUTY_OUT_1_CUP, DUTY_100_PERCENT);

            Bit2_Front_Led_2_Cups = CLEAR;
            set_led_duty( DUTY_OUT_2_CUPS, DUTY_100_PERCENT);

            Bit1_Front_Led_Pot = CLEAR;
            set_led_duty( DUTY_OUT_POT, DUTY_100_PERCENT);

            /*..hui [23-2-13오후 7:48:03] 이 조건은 성립할수가 없음.. 혹시나..*/
            if( bit_my_cup_enable == SET )
            {
                Bit0_Front_Led_Cont = SET;
                set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
            }
            else
            {
                Bit0_Front_Led_Cont = CLEAR;
                set_led_duty( DUTY_OUT_CONT, DUTY_100_PERCENT);
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 gu8_dbg_duty;
void extract_led_out(void)
{
    if( bit_setting_mode_start == SET )
    {
        /*..hui [23-2-23오후 7:15:15] 마이컵 설정 중 추출 LED 점멸..*/
        if( bit_my_cup_setting_start == SET || Bit3_My_Cup_Set_Display == SET )
        {
            Bit3_Front_Led_Ice_Extract = CLEAR;
            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
            //set_led_duty( DUTY_OUT_ICE_EXTRACT, gu8_dbg_duty);

            /*Bit4_Front_Led_Water_Extract = Bit0_Front_Led_Cont;*/
            /*set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_100_PERCENT);*/

            /*..hui [23-3-22오후 5:21:51] 세팅 완료되고 End 표시하는 동안은 꺼져있어야 함..*/
            if( bit_my_cup_finish_flick == CLEAR )
            {
                gu8_my_cup_flick_timer++;

                if( gu8_my_cup_flick_timer <= 5 )
                {
                    Bit4_Front_Led_Water_Extract = SET;
		            set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
		            //set_led_duty( DUTY_OUT_WATER_EXTRACT, gu8_dbg_duty);
                }
                else if( gu8_my_cup_flick_timer <= 10 )
                {
                    Bit4_Front_Led_Water_Extract = CLEAR;
		            set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
		            //set_led_duty( DUTY_OUT_WATER_EXTRACT, gu8_dbg_duty);
                }
                else
                {
                    gu8_my_cup_flick_timer = 0;
                }
            }
            else
            {
                Bit4_Front_Led_Water_Extract = CLEAR;
	            set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
	            //set_led_duty( DUTY_OUT_WATER_EXTRACT, gu8_dbg_duty);
            }
        }
        else
        {
        }

        return;
    }
    //else{}	
	/*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	//if( bit_illumi_State == SET )
	else if(bit_sleep_mode_start == SET)
    {
        if( gu8_durable_test_start == SET )
        {
            Bit3_Front_Led_Ice_Extract = F_Wink_500ms;
            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_20_PERCENT);
        }
        else
        {
            Bit3_Front_Led_Ice_Extract = SET;
            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_20_PERCENT);
        }

        Bit4_Front_Led_Water_Extract = SET;
        set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_20_PERCENT);		
    }
    else
    {
        if( gu8_durable_test_start == SET )
        {
            if( gu16_durable_test_step == 10 || gu8_Error_Code != 0 )
            {
                Bit3_Front_Led_Ice_Extract ^= SET;
            }
            else
            {
                Bit3_Front_Led_Ice_Extract = F_Wink_500ms;
            }

            //set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_100_PERCENT);
            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
            //t_led_duty( DUTY_OUT_ICE_EXTRACT, gu8_dbg_duty);
        }
        else
        {
        	if(F_Extract_Led_OnOff == SET)
       		{
	            Bit3_Front_Led_Ice_Extract = SET;
	            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
	            Bit4_Front_Led_Water_Extract = SET;   		
	            set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
       		}
			else
			{
	            Bit3_Front_Led_Ice_Extract = CLEAR;
	            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
	            //t_led_duty( DUTY_OUT_ICE_EXTRACT, gu8_dbg_duty);

	            Bit4_Front_Led_Water_Extract = CLEAR;
	            set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
	            //t_led_duty( DUTY_OUT_WATER_EXTRACT, gu8_dbg_duty);
	            gu8_my_cup_flick_timer = 0;
			}
			/*
            Bit3_Front_Led_Ice_Extract = SET;
            //set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_100_PERCENT);
            set_led_duty( DUTY_OUT_ICE_EXTRACT, DUTY_EXTRACT_70_PERCENT);
			
	        Bit4_Front_Led_Water_Extract = SET;
	        //set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_100_PERCENT);
	        set_led_duty( DUTY_OUT_WATER_EXTRACT, DUTY_EXTRACT_70_PERCENT);
	        */
        }

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_led_out(void)
{
    /*..hui [23-2-10오후 3:13:16] UV Care 아이콘은 항상 밝게 점등..*/
    set_icon_duty( DIMMING__UV_CART, ICON_DIIMMING_FULL_ON );

    if( bit_uv_faucet_out == SET || bit_uv_ice_tank_out == SET || bit_uv_ice_extraction_out == SET )
    {
        Bit0_Front_Led_UV_Sterilization = SET;
    }
    else
    {
        Bit0_Front_Led_UV_Sterilization = CLEAR;
    }

    if( Bit0_Front_Led_UV_Sterilization == SET )
    {
        if( bit_uv_faucet_out == SET )
        {
            Bit1_Front_Led_Faucet = SET;
            set_icon_duty( DIMMING__FAUCET, ICON_DIIMMING_FULL_ON );
        }
        else
        {
            /*..hui [23-3-8오후 4:24:27] 현재 동작중이지 않은 모드는 끄는걸로.. 디자인..*/
            Bit1_Front_Led_Faucet = CLEAR;
            set_icon_duty( DIMMING__FAUCET, ICON_DIIMMING_FULL_ON );
        }

        if( bit_uv_ice_tank_out == SET )
        {
            Bit2_Front_Led_Ice_Tank = SET;
            set_icon_duty( DIMMING__ICE_TANK, ICON_DIIMMING_FULL_ON );
        }
        else
        {
            /*..hui [23-3-8오후 4:24:27] 현재 동작중이지 않은 모드는 끄는걸로.. 디자인..*/
            Bit2_Front_Led_Ice_Tank = CLEAR;
            set_icon_duty( DIMMING__ICE_TANK, ICON_DIIMMING_FULL_ON );
        }

        if( bit_uv_ice_extraction_out  == SET )
        {
            Bit5_Front_Led_Icon_ice_faucet = SET;
            set_icon_duty( DIMMING__ICE_FAUCET, ICON_DIIMMING_FULL_ON );
        }
        else
        {
            /*..hui [23-3-8오후 4:24:27] 현재 동작중이지 않은 모드는 끄는걸로.. 디자인..*/
            Bit5_Front_Led_Icon_ice_faucet = CLEAR;
            set_icon_duty( DIMMING__ICE_FAUCET, ICON_DIIMMING_FULL_ON );
        }
    }
    else
    {
        Bit1_Front_Led_Faucet = CLEAR;
        Bit2_Front_Led_Ice_Tank = CLEAR;
		Bit5_Front_Led_Icon_ice_faucet = CLEAR;
        //ice_faucet에 대한 uv 켜줘야함 
        //Bit3_Front_Led_Ice_Extract = CLEAR;
        set_icon_duty( DIMMING__FAUCET, ICON_DIIMMING_FULL_ON );
        set_icon_duty( DIMMING__ICE_FAUCET, ICON_DIIMMING_FULL_ON );
        set_icon_duty( DIMMING__ICE_TANK, ICON_DIIMMING_FULL_ON );
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void percent_ml_led_out(void)
{
    set_icon_duty( DIMMING__ml, ICON_DIIMMING_FULL_ON );
    set_icon_duty( DIMMING__PERCENT, ICON_DIIMMING_FULL_ON );

    if( gu8_Led_Display_Step == LED_Display__WATER_EXTRACT )
    {
#if 0
        if( u8Extract_Continue == SET )
        {
            Bit5_Front_Led_Percent = CLEAR;
            Bit4_Front_Led_ml = CLEAR;
        }
        else
        {
            Bit5_Front_Led_Percent = SET;
            Bit4_Front_Led_ml = CLEAR;
        }
#endif
        #if 1
        if( (u8Extract_Continue == SET) || gu8Cup_level == CUP_LEVEL_CONTINUE )
        {
            Bit5_Front_Led_Percent = CLEAR;
            Bit4_Front_Led_ml = CLEAR;
        }
        else if( bit_my_cup_enable == SET && gu8Cup_level == CUP_LEVEL_MY_CUP )
        {
            /*..hui [23-3-23오후 2:34:29] 마이컵 추출할때도 퍼센트 OFF..*/
            Bit5_Front_Led_Percent = SET;
            Bit4_Front_Led_ml = CLEAR;
        }
        else
        {
            Bit5_Front_Led_Percent = SET;
            Bit4_Front_Led_ml = CLEAR;
        }
        #endif
    }
    else if( gu8_Led_Display_Step == LED_Display__ICE_EXTRACT )
    {
        Bit5_Front_Led_Percent = CLEAR;
        Bit4_Front_Led_ml = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__ERROR )
    {
        Bit5_Front_Led_Percent = CLEAR;
        Bit4_Front_Led_ml = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__SELF_TEST )
    {
        Bit5_Front_Led_Percent = SET;
        Bit4_Front_Led_ml = CLEAR;
    }
	/*.. sean [25-01-06] wifi paring 시에는 % 표시하도록 수정 ..*/
    else if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        if( bit_display_wifi_error == SET || bit_display_last_error == SET )
        {
        	Bit5_Front_Led_Percent = CLEAR;
        }
        else
        {
            /*..hui [23-12-4오후 2:14:01] 페어링 단계 표시화면에서는 퍼센트만 표시..*/
        	Bit5_Front_Led_Percent = SET;
        }
    }
    else
    {
        /*..hui [23-3-23오후 4:41:21] FND와 LED 싱크를 위해서 이쪽으로 이동..*/
        if( bit_default_cup_flick == SET )
        {
            /*mu8_flick_state = default_cup_set_flick_timer(5, 5);*/
            gu8_default_cup_flick_state = default_cup_set_flick_timer(5, 5);
        }
        else
        {
            gu8_default_cup_flick_state = SET;
        }

        /*..hui [23-2-23오후 7:43:45] 마이컵 선택시에는 둘 다 표시안함..*/
        if ( (gu8Cup_level == CUP_LEVEL_MY_CUP) || (gu8Cup_level == CUP_LEVEL_CONTINUE ) )
        {
            Bit5_Front_Led_Percent = CLEAR;
            Bit4_Front_Led_ml = CLEAR;
        }
        else
        {
            Bit5_Front_Led_Percent = CLEAR;
            /*..hui [23-3-23오후 4:10:09] 디폴트 컵 설정시 ml도 같이 점멸..*/
            if( bit_default_cup_flick == SET )
            {
                if( gu8_default_cup_flick_state == SET )
                {
                    Bit4_Front_Led_ml = SET;
                }
                else
                {
                    Bit4_Front_Led_ml = CLEAR;
                }
            }
            else
            {
                Bit4_Front_Led_ml = SET;
            }
			//if( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR )		
	    	if( (GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && (GetWifiStatusValue(WIFI_STATUS_PAIRING) == CLEAR )
			/*&& ( gu8_cup_led_select == CLEAR )*/ && ( gu16_water_return_wifi_time == 0 )  )
			{
				if(gu8_cup_led_select == SET)
					Bit4_Front_Led_ml = SET;
				else
					Bit4_Front_Led_ml = CLEAR;
			}
			else {}
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_led_out(void)
{
    U8 mu8_flick_state = 0;

    if( bit_setting_mode_start == SET )
    {
        /*..hui [23-3-22오후 5:35:54] 마이컵 세팅.. 물 추출하고 End 끝날때까지 아래쪽 Mycup LED만 켜놓는다..*/
        if( bit_my_cup_setting_start == SET
            && (F_WaterOut == SET || bit_my_cup_finish_flick == SET) )
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = CLEAR;
            Bit2_Front_Led_Hot_Lock = CLEAR;
            Bit3_Front_Led_Eco_Mode = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_My_Cup = SET;
        }
        else
        {
            Bit0_Front_Led_Ice_First = SET;
            Bit1_Front_Led_Ice_Lock = SET;
            Bit2_Front_Led_Hot_Lock = SET;
            Bit3_Front_Led_Eco_Mode = SET;
            Bit4_Front_Led_Cold_Temp = SET;
            Bit5_Front_Led_My_Cup = SET;
        }

        set_led_duty( DUTY_OUT_SETTING_MENU, DUTY_100_PERCENT);
    }
    else
    {
        if( Bit0_Ice_Lock_Indicator == SET )
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = Bit0_Front_Led_Set_Select;
            Bit2_Front_Led_Hot_Lock = CLEAR;
            Bit3_Front_Led_Eco_Mode = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_My_Cup = CLEAR;
            set_led_duty( DUTY_OUT_SETTING_MENU, DUTY_100_PERCENT);
        }
        else if( Bit1_Hot_Lock_Indicator == SET )
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = CLEAR;
            Bit2_Front_Led_Hot_Lock = Bit0_Front_Led_Set_Select;
            Bit3_Front_Led_Eco_Mode = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_My_Cup = CLEAR;
            set_led_duty( DUTY_OUT_SETTING_MENU, DUTY_100_PERCENT);
        }
        else
        {
            Bit0_Front_Led_Ice_First = CLEAR;
            Bit1_Front_Led_Ice_Lock = CLEAR;
            Bit2_Front_Led_Hot_Lock = CLEAR;
            Bit3_Front_Led_Eco_Mode = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;

            #if 0
            /*..hui [23-3-22오후 5:57:10] 마이컵 설정, 선택, 추출시 설정쪽 마이컵 LED 점등..*/
            if( F_WaterOut == SET && bit_my_cup_enable == SET && gu8Cup_level == CUP_LEVEL_MY_CUP )
            {
                Bit5_Front_Led_My_Cup = SET;
            }
            else
            {
                Bit5_Front_Led_My_Cup = CLEAR;
            }
            #endif

            /*..hui [23-3-23오전 9:09:30] 마이컵 선택 후 추출할때는 표시하지않음.. 설정이라 헷갈림..디자인..*/
            Bit5_Front_Led_My_Cup = CLEAR;

            set_led_duty( DUTY_OUT_SETTING_MENU, DUTY_100_PERCENT);
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void set_led_duty( U8 mu8_number, U8 mu8_duty )
{
    U8 mu8_final_duty = 0;

    if( mu8_duty >= 10 )
    {
        mu8_final_duty = 10;
    }
    else
    {
        mu8_final_duty = mu8_duty;
    }


    switch( mu8_number )
    {
        case DUTY_OUT_SET_SELECT:

            bit_0_3_dimming_set_select = mu8_final_duty;

        break;

        case DUTY_OUT_ICE_SELECT:

            bit_4_7_dimming_ice_select = mu8_final_duty;

        break;



        case DUTY_OUT_HOT_SELECT:

            bit_0_3_dimming_hot_select = mu8_final_duty;

        break;

        case DUTY_OUT_AMBIENT_SELECT:

            bit_4_7_dimming_ambient_select = mu8_final_duty;

        break;


        case DUTY_OUT_COLD_SELECT:

            bit_0_3_dimming_cold_select = mu8_final_duty;

        break;


        case DUTY_OUT_AMOUNT_SELECT:

            bit_4_7_dimming_amount_select = mu8_final_duty;

        break;

        case DUTY_OUT_ICE_EXTRACT:

            bit_0_3_dimming_ice_extract = mu8_final_duty;

        break;


        case DUTY_OUT_WATER_EXTRACT:

            bit_4_7_dimming_water_extract = mu8_final_duty;

        break;


        case DUTY_OUT_SETTING_MENU:

            bit_0_3_dimming_setting_menu = mu8_final_duty;

        break;

        case DUTY_OUT_ETC_ICON:

            bit_4_7_dimming_etc_icon = mu8_final_duty;

        break;

        case DUTY_OUT_HOT_TEMP:

            bit_0_3_dimming_hot_temp = mu8_final_duty;

        break;

        case DUTY_OUT_COLD_TEMP:

            bit_4_7_dimming_cold_temp = mu8_final_duty;

        break;

        case DUTY_OUT_CONT:

            bit_0_3_dimming_cont = mu8_final_duty;

        break;

        case DUTY_OUT_POT:

            bit_4_7_dimming_pot = mu8_final_duty;

        break;

        case DUTY_OUT_2_CUPS:

            bit_0_3_dimming_2cups = mu8_final_duty;

        break;


        case DUTY_OUT_1_CUP:

            bit_4_7_dimming_1cup = mu8_final_duty;

        break;


        case DUTY_OUT_HALF_CUP:

            bit_0_3_dimming_half_cup = mu8_final_duty;

        break;


        case DUTY_OUT_MY_CUP:

            bit_4_7_dimming_colon = mu8_final_duty;

        break;


        case DUTY_OUT_SEGMENT_0_0_0_1:

            bit_0_3_fnd_0_0_0_1 = mu8_final_duty;

        break;


        case DUTY_OUT_SEGMENT_0_0_2_0:

            bit_4_7_fnd_0_0_2_0 = mu8_final_duty;

        break;


        case DUTY_OUT_SEGMENT_0_3_0_0:

            bit_0_3_fnd_0_3_0_0 = mu8_final_duty;

        break;


        case DUTY_OUT_SEGMENT_4_0_0_0:

            bit_4_7_fnd_4_0_0_0 = mu8_final_duty;

        break;


        case DUTY_OUT_WIFI_WHITE_ICON:

            bit_4_7_dimming_colon = mu8_final_duty;

        break;


        default:

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void set_icon_duty( U8 mu8_number, U8 mu8_on_off )
{
    if(  mu8_number > DIMMING__ICE_FULL || mu8_on_off > ICON_DIIMMING_10_PERCENT_ON )
    {
        return;
    }
    else{}

    switch( mu8_number )
    {
        case DIMMING__HOT_TEMP:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit0_Hot_Temp_1_2_3_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit0_Hot_Temp_1_2_3_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__COLD_TEMP:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit1_Cold_Temp_1_2_3_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit1_Cold_Temp_1_2_3_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__UV_CART:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit2_UV_Care_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit2_UV_Care_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__FAUCET:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit3_Faucet_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit3_Faucet_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICE_TANK:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit4_Ice_Tank_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit4_Ice_Tank_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ml:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit5_ml_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit5_ml_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__PERCENT:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit6_Percent_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit6_Percent_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__AUTO_DRAIN:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit8_Low_Water_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit8_Low_Water_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICON_ICE_LOCK:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit9_Icon_Ice_Lock_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit9_Icon_Ice_Lock_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICON_HOT_LOCK:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit10_Icon_Hot_Lock_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit10_Icon_Hot_Lock_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICON_ALL_LOCK:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit11_Icon_All_Lock_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit11_Icon_All_Lock_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICON_SAVE:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit12_Icon_Save_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit12_Icon_Save_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICE_FIRST:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit13_Ice_First_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit13_Ice_First_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICE_FULL:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit14_Ice_Full_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit14_Ice_Full_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__ICE_FAUCET:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit15_Ice_faucet_Dimming_State = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit15_Ice_faucet_Dimming_State = CLEAR;
            }

        break;

        case DIMMING__AM:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit0_Time_Led_AM = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit0_Time_Led_AM = CLEAR;
            }

        break;

        case DIMMING__PM:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit1_Time_Led_PM = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit1_Time_Led_PM = CLEAR;
            }

        break;
#if 0
case DIMMING__SEGMENT_0_0_0_1:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit0_Seg_0_0_0_1_state = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit0_Seg_0_0_0_1_state = CLEAR;
            }

        break;

        case DIMMING__SEGMENT_0_0_2_0:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit1_Seg_0_0_2_0_state = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit1_Seg_0_0_2_0_state = CLEAR;
            }

        break;

        case DIMMING__SEGMENT_0_3_0_0:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit2_Seg_0_3_0_0_state = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit2_Seg_0_3_0_0_state = CLEAR;
            }

        break;

        case DIMMING__SEGMENT_4_0_0_0:

            if( mu8_on_off == ICON_DIIMMING_10_PERCENT_ON)
            {
                Bit3_Seg_4_0_0_0_state = SET;
            }
            else /*if( mu8_on_off == ICON_DIIMMING_FULL_ON)*/
            {
                Bit3_Seg_4_0_0_0_state = CLEAR;
            }

        break;
#endif
		default:

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_time_setting_state(void)
{
    Bit0_Front_Led_Set_Select = SET;
    Bit2_Front_Led_Hot_Select = SET;
    Bit4_Front_Led_Cold_Select = SET;
}


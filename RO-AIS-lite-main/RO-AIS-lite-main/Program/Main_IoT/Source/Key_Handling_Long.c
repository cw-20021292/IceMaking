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
#include    "Key_Handling_Long.h"

#include "WIFI_A101x_FunctionList.h"


void setting_mode_start(void);
void cold_water_enable_setting_job( U8 mu8_mode );
void hot_water_enable_setting_job( U8 mu8_mode);
void all_lock_setting_job( U8 mu8_mode );
void ice_on_off_setting_job(void);
void ice_on_setting_job(void);
void ice_off_setting_job(void);
void cody_inspection_select_job(void);
void debug_mode_select_job(void);
void key_altitude_setting_job(void);
void memento_select_job(void);
void memento_delete_job(void);
void memento_finish_job(void);
void default_cup_setting_job(void);
void mute_setting_job(void);
void calcel_comp_delay(void);
void Cold_temp_setting_job(void);

#if CONFIG_TIME_SETTING
void key_time_setting_job(void);
void key_time_setting_hot_long_select_job(void);
void key_time_setting_cold_long_select_job(void);
#endif
bit bit_setting_mode_start;

bit bit_altitude_setting_start;
bit bit_memento_start;
U8 gu8_memento_display_num;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_mode_start(void)
{
    /*..hui [17-12-28오후 1:03:15] 추출중에는 변경못하도록 변경..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if(F_All_Lock == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    #if 0
    if( bit_my_cup_setting_start == SET )
    {
        ///bit_my_cup_setting_start = CLEAR;
        BuzStep(BUZZER_CANCEL);
        halt_my_cup_setting();

        ///bit_my_cup_enable = CLEAR;
        return;
    }
    else{}
    #endif

    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_setting_mode_start == CLEAR )
    {
        bit_setting_mode_start = SET;
        BuzStep(BUZZER_SELECT);
        /////bit_my_cup_first_display = CLEAR;

        bit_my_cup_first_display = CLEAR;
        bit_my_cup_finish_flick = CLEAR;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_water_enable_setting_job( U8 mu8_mode )
{
    if(F_All_Lock == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}


    if(F_WaterOut == SET)
    {
        return;
    }
    else{}

    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_Cold_Enable != SET)
        {
            F_Cold_Enable = SET;
            water_select_return_timer_control(0);

            if(F_Mute_Enable == CLEAR)
            {
                BuzStep(BUZZER_SETUP);
            }
            else
            {
                /*BuzStep(BUZZER_SETUP_MUTE);*/
            }

            /*..hui [24-4-24오후 5:48:35] 냉수 ON, OFF 시 표시..*/
            start_button_set_display( BUTTON_SET_COLD_DISPLAY );
        }
        else{}
    }
    else
    {
        /*if(F_Cold_Enable == SET && F_Cold_Water_VeryLongKey_Disable == CLEAR)*/
        if( F_Cold_Enable == SET )
        {
            F_Cold_Enable = CLEAR;
            water_select_return_timer_control(1);

            /*..hui [20-1-6오후 8:06:19] 냉수 버튼으로 냉수 끄면 냉수 설정도 OFF로 변경..*/
            /*..hui [20-2-24오후 7:44:02] 냉수 ONOFF랑 냉수온도 설정 메뉴 분리..*/
            /*gu8_cold_setting_level = COLD_TEMP_OFF;*/

            if(F_Mute_Enable == CLEAR)
            {
                BuzStep(BUZZER_CANCEL);
            }
            else
            {
                /*BuzStep(BUZZER_CANCEL_MUTE);*/
            }

            /*..hui [24-4-24오후 5:48:35] 냉수 ON, OFF 시 표시..*/
            start_button_set_display( BUTTON_SET_COLD_DISPLAY );
        }
        else{}
    }
}


void hot_water_enable_setting_job( U8 mu8_mode)
{
//
    if(F_All_Lock == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}


    #if 0
    if( F_Hot_Lock == SET )
    {
        return;
    }
    else{}
    #endif

    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_Hot_Enable != SET)
        {
            F_Hot_Enable = SET;
            water_select_return_timer_control(0);

            if(F_Mute_Enable == CLEAR)
            {
                BuzStep(BUZZER_SETUP);
            }
            else
            {
                /*BuzStep(BUZZER_SETUP_MUTE);*/
            }

            /*..hui [24-4-24오후 5:46:42] 온수 설정시 ON, OFF 표시..*/
            start_button_set_display( BUTTON_SET_HOT_DISPLAY );
        }
        else{}
    }
    else
    {
        /*if(F_Hot_Enable == SET && F_Hot_Water_VeryLongKey_Disable == CLEAR)*/
        if(F_Hot_Enable == SET)
        {
            F_Hot_Enable = CLEAR;
            water_select_return_timer_control(1);

            if(F_Mute_Enable == CLEAR)
            {
                BuzStep(BUZZER_CANCEL);
            }
            else
            {
                /*BuzStep(BUZZER_CANCEL_MUTE);*/
            }

            /*..hui [24-4-24오후 5:46:42] 온수 설정시 ON, OFF 표시..*/
            start_button_set_display( BUTTON_SET_HOT_DISPLAY );
        }
        else{}
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_lock_setting_job( U8 mu8_mode )
{
    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 추출중에는 변경못하도록 변경..*/
    if(F_WaterOut == SET || F_Ice == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}


    if(mu8_mode == SETTING_ENABLE)
    {
        if(F_All_Lock != SET)
        {
            F_All_Lock = SET;
            BuzStep(BUZZER_SETUP);
        }
        else{}
    }
    else
    {
        if(F_All_Lock == SET)
        {
            F_All_Lock = CLEAR;
            BuzStep(BUZZER_CANCEL);
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_on_off_setting_job(void)
{
    if(F_All_Lock == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    F_IceOn = ~F_IceOn;
    setting_buzzer( (U8)F_IceOn );

    if(F_IceOn == SET)
    {
        F_IR = SET;               // 만빙감지
    }
    else
    {
        F_IceDoorClose = SET;
    }

    /*start_set_flick( ON_OFF_DISPLAY_ICE_SET );*/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_on_setting_job(void)
{
    if(F_All_Lock == SET)
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    /*..hui [24-4-3오후 4:04:48] 얼음 ON돼있을경우 PASS..*/
    if( F_IceOn == SET )
    {
        return;
    }
    else{}

    F_IceOn = SET;
    setting_buzzer( (U8)F_IceOn );

    if( F_IceOn == SET )
    {
        F_IR = SET;               // 만빙감지
    }
    else
    {
        F_IceDoorClose = SET;
    }

    /*..hui [24-4-24오후 5:41:27] 얼음 설정 ON 표시..*/
    start_button_set_display( BUTTON_SET_ICE_DISPLAY );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_off_setting_job(void)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-28오후 1:03:15] 얼음 추출중에는 변경못하도록 변경..*/
    if( F_Ice == SET )
    {
        return;
    }
    else{}

    /*..hui [24-4-3오후 4:04:48] 얼음 OFF돼있을경우 PASS..*/
    if( F_IceOn == CLEAR )
    {
        return;
    }
    else{}

    F_IceOn = CLEAR;
    setting_buzzer( (U8)F_IceOn );

    if(F_IceOn == SET)
    {
        F_IR = SET;               // 만빙감지
    }
    else
    {
        F_IceDoorClose = SET;
    }

    /*..hui [24-4-24오후 5:41:27] 얼음 설정 OFF 표시..*/
    start_button_set_display( BUTTON_SET_ICE_DISPLAY );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_inspection_select_job(void)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut != SET && F_Ice != SET )
    {
        //gu8_memento_depth = LCD_MENU_DEPTH_ONE;
        //gu8_product_info_depth = LCD_MENU_DEPTH_ONE;
        //show_cody_inspect_menu();
        BuzStep(BUZZER_SETUP);
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void debug_mode_select_job(void)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:33:24] 메인 표시 상태에서만 진입..*/
    if(gu8_Led_Display_Step != LED_Display__MAIN)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut != SET && F_Ice != SET )
    {
        /*..hui [20-3-13오후 3:06:31] 즉시 디버그 모드 진입..*/
        bit_debug_mode_start = SET;
        BuzStep(BUZZER_SETUP);
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_altitude_setting_job(void)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_altitude_setting_start != SET )
    {
        bit_altitude_setting_start = SET;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        bit_altitude_setting_start = CLEAR;
        BuzStep(BUZZER_CANCEL);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_select_job(void)
{
    /*..hui [19-10-18오후 1:33:24] 메인 표시 상태에서만 진입..*/
    if(gu8_Led_Display_Step != LED_Display__MAIN )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut == SET || F_Ice == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /*..hui [19-10-18오후 1:34:57] 물 추출, 얼음 추출이 아닐때..*/
    if( F_WaterOut != SET )
    {
        bit_memento_start = SET;
        gu8_memento_display_num = 0;
        BuzStep(BUZZER_SETUP);
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_finish_job(void)
{
    bit_memento_start = CLEAR;
    gu8_memento_display_num = 0;
    BuzStep(BUZZER_CANCEL);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void memento_delete_job(void)
{
    F_ErrorSave = 1;

    u8Memento_Buff[0] = 0;
    u8Memento_Buff[1] = 0;
    u8Memento_Buff[2] = 0;
    u8Memento_Buff[3] = 0;
    u8Memento_Buff[4] = 0;

    BuzStep(BUZZER_SETUP);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void default_cup_setting_job(void)
{
    /*..hui [17-12-19오후 2:25:35] 현재 디폴트 상태랑 동일한 키 입력시 패스....*/
    if( gu8Cup_level == gu8Cup_level_Default )
    {
        //
    }
    else
    {
    	if(gu8Cup_level == CUP_LEVEL_CONTINUE)
    	{
        	BuzStep(BUZZER_ERROR);
    	}
		else
		{
	        gu8Cup_level_Default = gu8Cup_level;
	        BuzStep(BUZZER_SETUP);

	        /*..hui [23-3-22오후 4:16:20] Main 화면에서만 FND 점멸 표시..*/
	        if( gu8_Led_Display_Step == LED_Display__MAIN )
	        {
	            start_defualt_cup_set_flick();
	        }
	        else{}

	        gu8_cup_level_time_init = SET;
			
	    	send_wifi_each_data_control( WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL );
		}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void mute_setting_job(void)
{
    #if 0
    if(F_Mute_Enable != SET)
    {
        F_Mute_Enable = SET;
        /*BuzStep(BUZZER_SETUP_MUTE);*/
        BuzStep(BUZZER_CANCEL_MUTE);
    }
    else
    {
        F_Mute_Enable = CLEAR;
        /*BuzStep(BUZZER_CANCEL_MUTE);*/
        /*BuzStep(BUZZER_SETUP_MUTE);*/
        BuzStep(BUZZER_SETUP);
    }
    #endif
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if(F_Mute_Enable != SET)
    {
        F_Mute_Enable = SET;
        /*BuzStep(BUZZER_SETUP_MUTE);*/
        BuzStep(BUZZER_MUTE);
    }
    else
    {
        F_Mute_Enable = CLEAR;
        BuzStep(BUZZER_CANCEL);
    }

    /*BuzStep(BUZZER_MUTE);*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calcel_comp_delay(void)
{
    /*..hui [19-10-25오전 9:21:25] 여기서 한번 더 필터링..*/
    if(F_Comp_Output == CLEAR && gu16CompOffDelay > 0)
    {
        /*..hui [19-10-25오전 9:22:56] 냉매전환밸브 초기화시간 고려..*/
        gu16CompOffDelay = DEVELOPE_COMP_DELAY_CANCEL_TIME;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if CONFIG_TIME_SETTING
void key_time_setting_job(void)
{
#if 1
    if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        return;
    }
    else{}
#endif

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET )
    {
        //start_all_lock_flick();
        return;
    }
    else{}

    if( F_WaterOut == SET || F_Ice == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}
	
    if( bit_altitude_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /*..hui [23-9-14오후 3:38:14] 현재시간, 설정시간 설정시에는 진입못하게..*/
    if( bit_time_setting_start == SET )
    {
    	bit_time_setting_start = CLEAR;
        /*play_melody_warning_197();*/
        return;
    }
    else
	{
		bit_time_setting_start = CLEAR;
	}

    if( bit_setting_mode_start != SET )
    {
        start_time_setting_mode( CURRENT_TIME_SETTING_MODE );
    }
    else
    {
        //play_melody_warning_197();
        //error 부저 넣을 수 있도록 수정
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_hot_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit0_Hot_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_cold_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit1_Cold_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_cold_temp(void)
{

    /*..hui [20-1-6오후 1:32:06] 냉수온도 설정 기능 추가..*/
    if(gu8_cold_setting_level == COLD_TEMP_HIGH)
    {
        gu8_cold_setting_level = COLD_TEMP_LOW;
        BuzStep(BUZZER_CANCEL);
    }
    else
    {
        gu8_cold_setting_level = COLD_TEMP_HIGH;
        BuzStep(BUZZER_SETUP);
    }

    //start_set_flick( ON_OFF_DISPLAY_COLD_TEMP_STE );
    /*..hui [24-4-24오후 5:41:27] extra cold 설정 ON/OFF 표시..*/
    start_button_set_display( BUTTON_SET_COLD_TEMP_DISPLAY );

    /*..hui [23-4-3오후 12:50:04] 마이컵 설정중 extra cold 버튼 누를경우 마이컵 첫 표시 플래그 초기화..*/
    bit_my_cup_first_display = CLEAR;

}


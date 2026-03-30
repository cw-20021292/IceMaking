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
#include    "Key_Handling.h"
#include	"WIFI_Config.h"

void key_setting_select_job(void);
void key_ice_select_job(void);
void key_hot_water_select_job(void);
void key_ambient_water_select_job(void);
void key_cold_water_select_job(void);
void key_amount_select_job(void);
void key_setting_ice_first(void);
void key_setting_ice_lock(void);
void key_setting_hot_lock(void);
void key_setting_auto_drain(void);
void key_setting_eco_mode(void);
//void key_setting_cold_temp(void);
void key_setting_cold_enable(void);
void key_setting_my_cup(void);
void setting_buzzer( U8 mu8_setting );


//================================== Key Flag
bit F_KeySet;
bit F_ExtractKeySet;
bit F_TestKeySet;
bit F_LongKeySet;
bit F_IceKeySet;
bit F_Cold_Enable;
bit F_ColdOut;
bit F_ColdOn;
bit F_ColdOff;
bit F_Hot_Enable;
bit F_HotOut;
bit F_HotOn;
bit F_HotOff;
bit F_Room;
bit F_RoomOut;
//bit F_Save;
bit F_Conty;
bit F_ContyGo;
bit F_Hot_Lock;
bit F_All_Lock;
bit F_Ice;
bit F_BeIce;
bit F_IceOn;
bit F_Ice_Lock;
bit F_IceOut;
bit F_IceOutStop;
bit F_LEDOff;
bit F_ColdSet;
bit F_HotSet;
bit F_IcemakeSet;
bit F_SaveSet;
bit F_KeySetBuz;
bit F_SterAuto;
bit F_SterLED;
bit Be_COMP;
bit Be_EW_POW;
bit Be_F_EWDrainPump;
//================================== S/W 센서
bit F_Out;
bit F_BeOut;
bit F_OutSet;
bit F_WaterOut;

U8 gu8LockFlick;
bit F_Mute_Enable;
bit F_Mute_Enable_Old;



bit F_Hot_Temp_Setting;
bit F_Circul_Drain;


bit F_Extraction_LED_Display_Mode;
bit F_Extraction_LED_Display_Mode_Old;




bit bit_fast_ice_make;

bit F_Ice_Make_Priority_Setting_Mode;

U8 gu8_ice_make_priority_settiong_time;


U8 gu8_direction_continue_timer;
U8 gu8_direction_continue_max;

bit F_wifi_select_amount_init;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_select_job(void)
{
    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}
	
    /*.. sean [25-03-24] wifi가 연결된 상태면 물양 보여주고 물양 누를 시 바로 올라갈 수 있도록 해야함 ..*/
	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
	{
		F_wifi_select_amount_init = SET;
	}
	else {}

    if( bit_memento_start == SET )
    {
        gu8_memento_display_num++;

        if( gu8_memento_display_num > 4 )
        {
            gu8_memento_display_num = 0;
        }
        else{}
    }
    else{}


    if( bit_debug_mode_start == SET
        && gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        gu8_fnd_debug_step++;

        if( gu8_fnd_debug_step > DEBUG__COMP_ICEHEATER_HOTHEATER)
        {
            gu8_fnd_debug_step = DEBUG__COMP_DELAY;
        }
        else{}

        gu8_debug_timer = 0;
        /*BuzStep(BUZZER_SELECT);*/
    }
    else{}


    if( bit_my_cup_setting_start == SET || bit_my_cup_finish_flick == SET )
    {
        /*..hui [23-4-3오전 11:36:43] Settings LED OFF하므로 부저음 불가음은 삭제..*/
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        Bit2_Settings_Switch_Indicator = SET;
        return;
    }
    else{}

    if( bit_setting_mode_start == SET )
    {
        bit_setting_mode_start = CLEAR;
        BuzStep(BUZZER_CANCEL);

        /*..hui [23-4-3오전 10:49:47] 화면 표시중이던 내용 전부 삭제..*/
        start_set_flick( ON_OFF_DISPLAY_OFF );
    }
    else
    {
        if( F_WaterOut == SET || F_Ice == SET )
        {
            BuzStep(BUZZER_ERROR);
        }
        else
        {
            BuzStep(BUZZER_SELECT);
        }

    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ice_select_job(void)
{
    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}
/*
    if( F_IceOn == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else {}
*/
    /*.. sean [25-03-24] wifi가 연결된 상태면 물양 보여주고 물양 누를 시 바로 올라갈 수 있도록 해야함 ..*/
	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
	{
		F_wifi_select_amount_init = SET;
	}
	else {}
	
    if( bit_debug_mode_start == SET
        && gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        if( gu8_fnd_debug_step <= DEBUG__COMP_DELAY)
        {
            gu8_fnd_debug_step = DEBUG__COMP_ICEHEATER_HOTHEATER;
        }
        else
        {
            gu8_fnd_debug_step--;
        }

        gu8_debug_timer = 0;
        /*BuzStep(BUZZER_SELECT);*/
    }
    else
    {
        if( F_WaterOut == SET || F_Ice == SET )
        {
            BuzStep(BUZZER_ERROR);
        }
        else
        {
            /*BuzStep(BUZZER_SELECT);*/
            /*..hui [24-4-24오후 5:38:30] 변경.. 얼음OFF->얼음누르면 띠링띠링..*/
            if( F_IceOn == CLEAR )
            {
                start_ice_off_flick();
                /*..hui [24-4-3오후 4:29:57] 얼음 OFF 상태에서 얼음 버튼 선택시 OFF 표시..*/
                start_button_set_display( BUTTON_SET_ICE_DISPLAY );
                /*..hui [24-4-24오후 5:40:19] 불가음..*/
                BuzStep(BUZZER_ERROR);
            }
            else
            {
                BuzStep(BUZZER_SELECT);
            }
        }

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_hot_water_select_job(void)
{
    if( bit_altitude_setting_start == SET )
    {
        gu8AltitudeStep++;

        if( gu8AltitudeStep > ALTITUDE_3_MODE_LOW )
        {
            gu8AltitudeStep = 0;
        }
        else{}

        gu8_altitude_return_time = 0;

        BuzStep(BUZZER_SELECT);

        return;
    }
    else{}


    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}


    gu8_cup_level_time_init = SET;


    /*..hui [19-10-7오후 3:24:23] 팝업 노출 순위 뒤로..*/
    if(F_Hot_Lock == SET)
    {
        /*Bit1_Hot_Lock_Indicator = SET;*/
        start_hot_lock_flick();
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    /*..hui [23-2-23오후 7:25:42] 탱크식이기때문에 에러났어도 그냥 물 추출은 가능..*/
    #if 0
    if( Bit1_Hot_Operation_Disable_State == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}
    #endif

    if( F_WaterOut == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        Bit0_Hot_Minus_Indicator = SET;
        return;
    }
    else{}
	
    /*.. sean [25-03-24] wifi가 연결된 상태면 물양 보여주고 물양 누를 시 바로 올라갈 수 있도록 해야함 ..*/
	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
	{
		F_wifi_select_amount_init = SET;
	}
	else {}


    if(F_Hot_Enable == CLEAR)
    {
        start_hot_off_flick();
        /*..hui [24-4-24오후 5:44:41] 온수 OFF 상태에서 온수 선택시 OFF 표시..*/
        start_button_set_display( BUTTON_SET_HOT_DISPLAY );
        BuzStep(BUZZER_ERROR);
    }
    else
    {
        BuzStep(BUZZER_SELECT);
    }

    u8WaterOutState = HOT_WATER_SELECT;
    gu16_water_select_return_time = 0;

    /*BuzStep(BUZZER_SELECT);*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ambient_water_select_job(void)
{
    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if(F_WaterOut == SET)
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}
	
    /*.. sean [25-03-24] wifi가 연결된 상태면 물양 보여주고 물양 누를 시 바로 올라갈 수 있도록 해야함 ..*/
	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
	{
		F_wifi_select_amount_init = SET;
	}
	else {}

    u8WaterOutState = PURE_WATER_SELECT;
    gu16_water_select_return_time = 0;

    BuzStep(BUZZER_SELECT);
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cold_water_select_job(void)
{
    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if(F_WaterOut == SET)
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        Bit1_Cold_Plus_Indicator = SET;
        return;
    }
    else{}
	
    /*.. sean [25-03-24] wifi가 연결된 상태면 물양 보여주고 물양 누를 시 바로 올라갈 수 있도록 해야함 ..*/
	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
	{
		F_wifi_select_amount_init = SET;
	}
	else {}

    if(F_Cold_Enable == CLEAR)
    {
        start_cold_off_flick();
        /*..hui [24-4-24오후 5:44:41] 냉수 OFF 상태에서 냉수 선택시 OFF 표시..*/
        start_button_set_display( BUTTON_SET_COLD_DISPLAY );
        BuzStep(BUZZER_ERROR);
    }
    else
    {
        BuzStep(BUZZER_SELECT);
    }

    u8WaterOutState = COLD_WATER_SELECT;
    gu16_water_select_return_time = 0;

    /*BuzStep(BUZZER_SELECT);*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_amount_select_job(void)
{
    if(F_All_Lock == SET)
    {
        BuzStep(BUZZER_ERROR);
        start_all_lock_flick();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;
    /*..hui [19-8-22오후 2:45:46] 온수 선택 중 사용자/물량 버튼 눌릴 경우 복귀 시간 초기화..캐럿 사양..*/
    gu8_hot_select_time_init = SET;

    if(F_WaterOut != SET)
    {
    	/*.. sean [25-02-13] wifi가 연결된 상태면 현재상태 보여주고 올라갈 수 있도록 해야함 ..*/
    	if ( ( GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( F_wifi_select_amount_init == CLEAR ) )
    	{
    		F_wifi_select_amount_init = SET;
    		gu8Cup_level--;
    	}
		else {}
		
        if( bit_my_cup_enable == SET )
        {
            if(gu8Cup_level == CUP_LEVEL_HALF)
            {
                gu8Cup_level = CUP_LEVEL_ONE;
            }
            else if(gu8Cup_level == CUP_LEVEL_ONE)
            {
                gu8Cup_level = CUP_LEVEL_TWO;
            }
            else if(gu8Cup_level == CUP_LEVEL_TWO)
            {
                gu8Cup_level = CUP_LEVEL_FOUR;
            }
            else if(gu8Cup_level == CUP_LEVEL_FOUR)
            {
                gu8Cup_level = CUP_LEVEL_CONTINUE;
            }
            else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
            {
                gu8Cup_level = CUP_LEVEL_MY_CUP;
            }
            else
            {
                gu8Cup_level = CUP_LEVEL_HALF;
            }
        }
        else
        {
            if(gu8Cup_level == CUP_LEVEL_HALF)
            {
                gu8Cup_level = CUP_LEVEL_ONE;
            }
            else if(gu8Cup_level == CUP_LEVEL_ONE)
            {
                gu8Cup_level = CUP_LEVEL_TWO;
            }
            else if(gu8Cup_level == CUP_LEVEL_TWO)
            {
                gu8Cup_level = CUP_LEVEL_FOUR;
            }
            else if(gu8Cup_level == CUP_LEVEL_FOUR)
            {
                gu8Cup_level = CUP_LEVEL_CONTINUE;
            }
            else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
            {
                gu8Cup_level = CUP_LEVEL_HALF;
            }
            else /*if(gu8Cup_level == CUP_LEVEL_TWO)*/
            {
                gu8Cup_level = CUP_LEVEL_HALF;
            }
        }

        /*..hui [20-1-7오전 9:56:14] 물량 선택 LED 표시용..*/
        gu8_cup_led_select = SET;

        BuzStep(BUZZER_SELECT);
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

void key_setting_ice_first(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    if( bit_fast_ice_make == COLD_FIRST_ICE_MAKE )
    {
        bit_fast_ice_make = ICE_FIRST_ICE_MAKE;
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        BuzStep(BUZZER_CANCEL);
    }

    send_wifi_each_data_control( WIFI_FUNC_0008_ICE_SEL );


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_ice_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    F_Ice_Lock = ~F_Ice_Lock;

    setting_buzzer( (U8)F_Ice_Lock );


    send_wifi_each_data_control( WIFI_FUNC_0032_ICELOCK_SEL );

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_hot_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}


    F_Hot_Lock = ~F_Hot_Lock;
    setting_buzzer( (U8)F_Hot_Lock );


    send_wifi_each_data_control( WIFI_FUNC_0003_HOT_LOCK_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_auto_drain(void)
{
    #if 0
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}

    F_Circul_Drain = ~F_Circul_Drain;
    setting_buzzer( (U8)F_Circul_Drain );
    #endif


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void key_setting_eco_mode(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}
	
    /*..hui [23-12-15오전 11:05:52] 에코모드 설정된 상태에서 시간 설정 지워지면 해제는 가능하도록..*/
    if( bit_sleep_mode_enable == SET )
    {
        bit_sleep_mode_enable = !bit_sleep_mode_enable;
        BuzStep(BUZZER_CANCEL);
        return;
    }
    else{}
	
    if( bit_first_time_setting == CLEAR )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    bit_sleep_mode_enable = !bit_sleep_mode_enable;
	
	BuzStep(BUZZER_SETUP);

	
#if 0
    F_Save = !F_Save;

    setting_buzzer( (U8)F_Save );
#endif
    /*start_set_flick( ON_OFF_DISPLAY_ECO_SET );*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void key_setting_cold_temp(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}

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

    start_set_flick( ON_OFF_DISPLAY_COLD_TEMP_STE );

    /*..hui [23-4-3오후 12:50:04] 마이컵 설정중 extra cold 버튼 누를경우 마이컵 첫 표시 플래그 초기화..*/
    bit_my_cup_first_display = CLEAR;

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_cold_enable(void)
{
    if( bit_setting_mode_start == CLEAR )
    {
        return;
    }
    else{}

    /*..hui [20-1-6오후 1:32:06] 냉수온도 설정 기능 추가..*/
    if(F_Cold_Enable == SET)
    {
    	F_Cold_Enable = CLEAR;
	/*..sean [25-03-07] 냉수 ON, OFF 시 표시..*/
        //cold_water_enable_setting_job(SETTING_DISABLE);
        BuzStep(BUZZER_CANCEL);
    }
    else
    {
    	F_Cold_Enable = SET;
        //cold_water_enable_setting_job(SETTING_ENABLE);
        BuzStep(BUZZER_SETUP);
    }
    start_set_flick( ON_OFF_DISPLAY_COLD_ENABLE );
	

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_my_cup(void)
{
    if( bit_debug_mode_start == SET || bit_altitude_setting_start == SET || bit_memento_start == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( bit_my_cup_finish_flick == SET )
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}

    /*..hui [23-2-23오후 6:34:07] 물 추출, 얼음 추출중에는 설정 안되게..*/
    if( F_Ice == SET || F_WaterOut == SET )
    {
        /*BuzStep(BUZZER_ERROR);*/
        return;
    }
    else{}


    if( bit_my_cup_first_display == CLEAR )
    {
        bit_my_cup_first_display = SET;
        BuzStep(BUZZER_SELECT);

        if( bit_my_cup_enable == SET )
        {
            start_set_flick( ON_OFF_DISPLAY_MY_CUP_SET );
        }
        else
        {
            start_set_flick( ON_OFF_DISPLAY_MY_CUP_OFF );
        }
    }
    else
    {
        if( Bit3_My_Cup_Set_Display == SET )
        {
            BuzStep(BUZZER_CANCEL);
            finish_my_cup_setting();
            start_set_flick( ON_OFF_DISPLAY_MY_CUP_OFF );

            /*..hui [23-2-22오후 4:20:25] 마이컵 해제시 디폴트 물량이 마이컵이었으면 반컵으로..*/
            if( gu8Cup_level_Default == CUP_LEVEL_MY_CUP )
            {
                gu8Cup_level_Default = CUP_LEVEL_HALF;
                gu8Cup_level = gu8Cup_level_Default;
            }
            else{}

            if( gu8Cup_level == CUP_LEVEL_MY_CUP )
            {
                gu8Cup_level = gu8Cup_level_Default;
            }
            else{}
        }
        else if( Bit4_My_Cup_Off_Display == SET )
        {
            BuzStep(BUZZER_SETUP);
            start_set_flick( ON_OFF_DISPLAY_MY_CUP_SET );
        }
        else{}

    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_buzzer( U8 mu8_setting )
{
    if(mu8_setting == SET)
    {
        BuzStep(BUZZER_SETUP);
    }
    else
    {
        BuzStep(BUZZER_CANCEL);
    }
}




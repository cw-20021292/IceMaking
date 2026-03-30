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
#include    "Key_Input.h"
#include	"WIFI_Config.h"

void Scan_Port_Select( U8 Scan_value );
void Led_Port_Clear(void);
void Key_Input_Check(U8 u8key_state, U8 u8key_num);
void Key_Matrix_Input( U8 Scan_value );
void Key_Input_Sampling( U16 u16key_input_value);
void Key_Management( U16 u16key_input_value);
void Key_Short_Input( U16 u16key_input_value);
void Key_Long_Input( U16 u16key_input_value);
void Key_Very_Long_Input( U16 u16key_input_value);
U8 key_short_enable_check( U16 u16key_input_value );
void Key_Normal_Long_Input( U16 u16key_input_value);
void Key_Middle_Input( U16 u16key_input_value);


//void Extract_KeyInput(void);




U8  u8Scan_Value;


U32  u32Fix_Key_Input_Value;


U16  gu16_Key_Input;

//U16  u16Key_Input;
U16  u16Key_Buffer;

U16  u16Key_Sampling_Counter;
bit F_Key_Short_Push_State;
bit F_Key_Middle_Push_State;
bit F_Key_Long_Push_State;
bit F_Key_Very_Long_Push_State;
bit F_Key_Normal_Long_Push_State;

U8  u8Key_Input_Value;

U16  u16Key_Long_Counter;
U16  u16Key_Short_Counter;
U16 u16LedOutValue;






bit F_CoverOpenSet;


U16 gu16ExtrKeyDelay;




bit F_SterReady;
bit F_SterProhibit;
bit F_SterComplete;
bit F_SterWashCancel;



U16 gu16IceOutOff;
U8 gu8ICELockLEDFlick;


//U16 gu16KeyTime;


bit F_Cold_Water_VeryLongKey_Disable;
bit F_Hot_Water_VeryLongKey_Disable;

U8 gu8_develop_input_count;
U16 gu16_develop_key_clear_time;

U8 gu8_debug_input_count;
U16 gu16_debugp_key_clear_time;


TYPE_BYTE          U8LedFlickerStateB;
#define            u8LedFlickerState                           U8LedFlickerStateB.byte
#define            Bit0_Ice_Lock_LED_Flick                     U8LedFlickerStateB.Bit.b0
#define            Bit1_Ice_Lock_Extract_LED_Flick             U8LedFlickerStateB.Bit.b1
#define            Bit2_Hot_Water_Lock_LED_Flick               U8LedFlickerStateB.Bit.b2
#define            Bit3_All_Lock_Water_Extract_LED_Flick       U8LedFlickerStateB.Bit.b3


TYPE_BYTE          U8DirectionLongKeyB;
#define            u8DirectionLongKey                          U8DirectionLongKeyB.byte
#define            Bit0_Right_Continue                         U8DirectionLongKeyB.Bit.b0
#define            Bit1_Left_Continue                          U8DirectionLongKeyB.Bit.b1


bit bit_setting_start;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input(void)
{
    /*..hui [19-11-7���� 9:55:18] �ʱ� Ű ����..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    Key_Input_Sampling(gu16_Key_Input);
    Key_Management(gu16_Key_Input);

    key_input_ice_extract();
    key_input_water_extract();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input_Sampling( U16 u16key_input_value)
{
    U8 mu8_filter = 0;

    mu8_filter = 1;

    if(u16key_input_value == u16Key_Buffer)
    {
        if(u16Key_Buffer == UControl_Key_Mask)
        {
            u16Key_Sampling_Counter = 0;
            F_Key_Short_Push_State = CLEAR;
            F_Key_Middle_Push_State = CLEAR;
            F_Key_Long_Push_State = CLEAR;
            F_Key_Very_Long_Push_State = CLEAR;
            F_Key_Normal_Long_Push_State = CLEAR;

            //u8DirectionLongKey = 0;
            u8TimeSettingLongKey = 0;
        }
        else
        {
            u16Key_Sampling_Counter++;
        }

        if(u16Key_Sampling_Counter >= mu8_filter)
        {
            u16Key_Short_Counter = u16Key_Sampling_Counter;
            u16Key_Long_Counter++;
        }
        else{}
    }
    else
    {
        u16Key_Buffer = u16key_input_value;
        u16Key_Sampling_Counter = 0;
        u16Key_Long_Counter = 0;
        u16Key_Short_Counter = 0;

        //F_Key_Short_Push_State = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Management( U16 u16key_input_value)
{
    if(F_Key_Short_Push_State == CLEAR)
    {
        if( (u16Key_Short_Counter >= 1) && (u16Key_Short_Counter < 1000) )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                Key_Short_Input( u16key_input_value );
            }
            else
            {
                PCB_Test_Mode_Key_Short_Input( u16key_input_value );
            }

            F_Key_Short_Push_State = SET;
            u16Key_Short_Counter = 0;
        }
        else{}
    }
    else
    {
        if(F_Key_Middle_Push_State == CLEAR)
        {
            if( (u16Key_Long_Counter >= 1000 && u16Key_Long_Counter < 2000) )
            {
                F_Key_Middle_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    Key_Middle_Input( u16key_input_value );
                }
                else{}
            }
            else{}
        }
        else
        {
            if(F_Key_Long_Push_State == CLEAR)
            {
                if( (u16Key_Long_Counter >= 2000 && u16Key_Long_Counter < 3000) )
                {
                    F_Key_Long_Push_State = SET;

                    if(u8FactoryTestMode == NONE_TEST_MODE)
                    {
                        Key_Long_Input( u16key_input_value );
                    }
                    else{}
                }
                else{}
            }
            else
            {
                if(F_Key_Normal_Long_Push_State == CLEAR)
                {
                    if( (u16Key_Long_Counter >= 3000 && u16Key_Long_Counter < 5000) )
                    {
                        F_Key_Normal_Long_Push_State = SET;

                        if(u8FactoryTestMode == NONE_TEST_MODE)
                        {
                            Key_Normal_Long_Input( u16key_input_value );
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    if(F_Key_Very_Long_Push_State == CLEAR)
                    {
                        if( u16Key_Long_Counter >= 7000 )
                        {
                            F_Key_Very_Long_Push_State = SET;
                            u16Key_Long_Counter = 0;

                            if(u8FactoryTestMode == NONE_TEST_MODE)
                            {
                                Key_Very_Long_Input( u16key_input_value );
                            }
                            else{}
                        }
                        else{}
                    }
                    else{}
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Short_Input( U16 u16key_input_value )
{
    U8 mu8_return = 0;
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}
	
	/*.. sean [25-03-13] �¼�/����/�ü� ��ư�� ���õ����� 20�ʵ��� �뷮 ǥ�� ..*/
	if(GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR )
	{
		//F_wifi_change_time_state = SET;
		
		gu16_water_return_wifi_time = 200;
	}
	else {}
	
    /*..hui [20-1-14���� 2:26:40] �ٽ� ����..��� ��ư ���� ��� ������� ����..*/
    ///F_lcd_standby_input = SET;
	/*.. sean [24-10-07] �ٽ� ���� ���, �ð� ������..*/
    gu8_time_setting_return_time = 0;

    ///F_lcd_setting_input = SET;
    bit_setting_mode_time_init = SET;

    bit_standby_input = SET;

    auto_drain_key_off_check();
    power_saving_init();


    if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        //bit_wifi_pairing_start = CLEAR;
        finish_pairing_screen();
    }
    else{}


    #if 0
    /*..hui [24-4-24���� 5:43:33] ǥ���� ��ư������ �ٷ� ����..*/
    if( u8ButtonSetDisplay > BUTTON_SET_DISPLAY_OFF )
    {
        /*..hui [23-5-31���� 2:18:04] �¼���ư ������ ����ǥ�� ����. ..*/
        stop_button_set_display();
    }
    else{}
    #endif

    /*..hui [24-4-24���� 5:43:33] ǥ���� ��ư������ �ٷ� ����..*/
    /*..hui [23-5-31���� 2:18:04] �¼���ư ������ ����ǥ�� ����. ..*/
    stop_button_set_display();

    switch(u16key_input_value)
    {
        case KEY_SETTING_SELECT:
        case LONG_KEY_3S_SETTING_MISS_TOUCH:
            //
            key_setting_select_job();

        break;

        case KEY_ICE:
        case LONG_KEY_3S_ICE_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_ice_select_job();
            }
            else{}

        break;

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
			if (bit_time_setting_start == TRUE)
			{
            	key_time_setting_hot_long_select_job();
			}
            else if( bit_setting_mode_start == CLEAR )
            {
                key_hot_water_select_job();
            }
            else{}

        break;

        case KEY_AMBIENT_SELECT:
        case LONG_KEY_3S_PURE_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                key_ambient_water_select_job();
            }
            else{}

        break;

        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
			if (bit_time_setting_start == TRUE)
			{
            	key_time_setting_cold_long_select_job();
			}
            else if( bit_setting_mode_start == CLEAR )
            {
                key_cold_water_select_job();
            }
            else{}

            gu8_debug_input_count++;

        break;

        case KEY_AMOUNT_SELECT:
        case LONG_KEY_3S_AMOUNT_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR
                && bit_my_cup_setting_start == CLEAR )
            {
                key_amount_select_job();
            }
            else{}

        break;


        case KEY_SETTING_ICE_FIRST:
            //
            if( Bit0_Front_Led_Ice_First == SET )
            {
                key_setting_ice_first();
            }
            else{}

        break;


        case KEY_SETTING_ICE_LOCK:
            //
            if( Bit1_Front_Led_Ice_Lock == SET )
            {
                key_setting_ice_lock();
            }
            else{}

        break;

        case KEY_SETTING_HOT_LOCK:
            //
            if( Bit2_Front_Led_Hot_Lock == SET )
            {
                key_setting_hot_lock();
            }
            else{}

        break;

        case KEY_SETTING_ECO_MODE:
            //
            if( Bit3_Front_Led_Eco_Mode == SET )
            {
                /*key_setting_auto_drain();*/
                key_setting_eco_mode();
            }
            else{}

        break;

        case KEY_SETTING_COLD_ENABLE:
            //
            if( Bit4_Front_Led_Cold_Temp == SET )
            {
                key_setting_cold_enable();
            }
            else{}

        break;

        case KEY_SETTING_MY_CUP:
            //
            if( Bit5_Front_Led_My_Cup == SET )
            {
                key_setting_my_cup();
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
void Key_Middle_Input( U16 u16key_input_value)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    switch(u16key_input_value)
    {
        case KEY_COLD_SELECT:
            //

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
void Key_Long_Input( U16 u16key_input_value)
{
    //power_saving_init();

    switch(u16key_input_value)
    {
        case LONG_KEY_PCB_TEST_MODE:
            //
            /*..hui [17-12-28���� 10:45:49] Uart �׽�Ʈ ��� ���� ���¿����� ���� �Ұ�..*/
            /*..hui [19-10-30���� 9:25:44] LCD MAINȭ������ ���� �Ϸ� �ĺ��� ���� ����..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0 )
            {
                Main_PBA_Test_Mode_Start();
            }
            else{}

        break;

        case LONG_KEY_DISPLAY_TEST_MODE_CHPI:
            //
            /*..hui [17-12-28���� 10:45:49] Uart �׽�Ʈ ��� ���� ���¿����� ���� �Ұ�..*/
            /*..hui [19-10-30���� 9:25:44] LCD MAINȭ������ ���� �Ϸ� �ĺ��� ���� ����..*/
            /*..hui [19-11-4���� 8:08:43] �� ���� �Ϸ�� �ĺ���..*/
            /*..hui [19-11-7���� 10:02:43] �������� ��Ʈ ���¸� ���÷��� �׽�Ʈ ������..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE
                && gu16IceMakingADVal <= 200
                && pLEVEL_ICE_DRAIN_LOW == CLEAR && pLEVEL_ICE_DRAIN_HIGH == CLEAR
                && gu8_room_level == ROOM_LEVEL_LOW
                && F_Overflow == CLEAR ) 
            {
                diplay_test_start();
            }
            else{}

        break;

        case LONG_KEY_MANUAL_FACTORY_TEST:
            //
            manual_test_start();

        break;

        case LONG_KEY_3S_BLE_FAIRING:
        case LONG_KEY_3S_AMBIENT_MISS_TOUCH:
            if( gu8_Led_Display_Step == LED_Display__MEMENTO
                && bit_memento_start == SET )
            {
                /*..hui [23-9-26���� 6:25:52] �޸��� ��忡���� �޸��� ���� ������..*/
                memento_delete_job();
            }
            else
            {
                WifiKey(WIFI_KEY_BLE);

                if( gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    if( gu8_wifi_ap_mode == CLEAR && gu8_ble_ap_mode == CLEAR )
                    {
                        if( GetWifiStatusValue( WIFI_STATUS_DISP ) == WIFI_DISP_OFF )
                        {
                            /*gu8_Lcd_Display_Step = LCD_Display__WIFI_PAIRING;*/
                        }
                        else
                        {
                            /*bit_wifi_pairing_start = SET;*/

                            if( gu8_Wifi_Last_Error != 0 )
                            {
                                bit_display_last_error = SET;
                                bit_wifi_pairing_start = SET;
                            }
                            else
                            {
                                bit_display_last_error = CLEAR;
                            }
                        }
                    }
                    else
                    {
                        bit_wifi_pairing_start = CLEAR;
                    }
                }
                else
                {
                    bit_wifi_pairing_start = CLEAR;
                }
            }
			break;

        case LONG_KEY_3S_WIFI_FAIRING:
            if( F_All_Lock == SET )
            {

            }
            else
            {
                WifiKey(WIFI_KEY_AP);

                if( gu8_Led_Display_Step == LED_Display__MAIN )
                {
                    if( gu8_wifi_ap_mode == CLEAR && gu8_ble_ap_mode == CLEAR )
                    {
                        if( GetWifiStatusValue( WIFI_STATUS_DISP ) == WIFI_DISP_OFF )
                        {
                            /*gu8_Lcd_Display_Step = LCD_Display__WIFI_PAIRING;*/
                        }
                        else
                        {
                            /*bit_wifi_pairing_start = SET;*/

                            if( gu8_Wifi_Last_Error != 0 )
                            {
                                bit_display_last_error = SET;
                                bit_wifi_pairing_start = SET;
                            }
                            else
                            {
                                bit_display_last_error = CLEAR;
                            }
                        }
                    }
                    else
                    {
                        bit_wifi_pairing_start = CLEAR;
                    }
                }
                else
                {
                    bit_wifi_pairing_start = CLEAR;
                }
            }
			break;

        case LONG_KEY_3S_WIFI_ONOFF:
            //
            if( F_All_Lock == SET )
            {

            }
            else
            {
                WifiKey(WIFI_KEY_ONOFF);
            }
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
void Key_Normal_Long_Input( U16 u16key_input_value)
{
    switch(u16key_input_value)
    {
        case LONG_KEY_3S_DURABLE_TEST:

            if( F_All_Lock == CLEAR
                && F_FW_Version_Display_Mode == SET
                && u8FactoryTestMode == NONE_TEST_MODE
                && gu8_test_mode_timeout > 0
                && gu8_Led_Display_Step == LED_Display__MAIN )
            {
                if( gu8_durable_test_start == CLEAR )
                {
                    gu8_durable_test_start = SET;
                    BuzStep(BUZZER_SETUP);
                }
                else{}
            }
            else{}

        break;

        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                cold_water_enable_setting_job(SETTING_ENABLE);
            }
            else{}

        break;
		
#if LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF
        /*..hui [24-4-24���� 4:41:25] �߰�..*/
        case LONG_KEY_3S_COLD_OFF:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_1:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_2:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_3:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_4:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_5:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_6:
		case LONG_KEY_3S_COLD_OFF_MISS_TOUCH_7:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                cold_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}

        break;
#endif

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_ENABLE);
            }
            else{}

        break;

#if LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF
		/*..hui [24-4-24���� 4:34:54] �߰�..*/
        case LONG_KEY_3S_HOT_OFF:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_1:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_2:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_3:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_4:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_5:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_6:
		case LONG_KEY_3S_HOT_OFF_MISS_TOUCH_7:
            //
            /*..hui [24-4-2���� 5:42:03] �¼� OFF ��ư�.. ����Ű��.. �¼�+����+���� 3��..*/
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}

        break;
#endif

		     
		case KEY_ICE:
        case LONG_KEY_3S_ICE_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                /*..hui [24-11-21 ] ���� ON/OFF �Լ� ������..*/
                //ice_on_off_setting_job();
                /*..hui [24-4-24���� 4:40:44] ���� ON/OFF �Լ� �и�..*/
                ice_on_setting_job();
            }
            else{}

        break;
		
#if LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF
        case LONG_KEY_3S_ICE_OFF:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_1:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_2:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_3:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_4:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_5:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_6:
		case LONG_KEY_3S_ICE_OFF_MISS_TOUCH_7:
            //
            /*..hui [24-4-3���� 4:07:19] ���� OFF ��ư�.. ����Ű��.. ����+����+���� 3��..*/
            if( bit_setting_mode_start == CLEAR )
            {
                ice_off_setting_job();
            }
            else{}

        break;
#endif

        case KEY_AMOUNT_SELECT:
        case LONG_KEY_3S_AMOUNT_MISS_TOUCH:
            //
            /*..hui [23-2-22���� 4:15:04] ����Ʈ ���� ������ �����ŵ� ����..*/
            if( bit_setting_mode_start == CLEAR )
            {
                default_cup_setting_job();
            }
            else{}

        break;

        /*..hui [23-5-10���� 10:13:44] ������ư�̶� ICE FIRST ������ư�� ������� �ΰ� ������쿡�� ������� �����ϵ���..*/
        case KEY_SETTING_SELECT:
        case LONG_KEY_3S_SETTING_MISS_TOUCH:
            //
            setting_mode_start();

        break;

        case LONG_KEY_ALL_LOCK:
            //
            if(F_All_Lock != SET)
            {
                all_lock_setting_job(SETTING_ENABLE);
            }
            else
            {
                all_lock_setting_job(SETTING_DISABLE);
            }

        break;

        case LONG_KEY_HOT_TEMP_SETTING:

            key_altitude_setting_job();

        break;

        case LONG_KEY_3S_MUTE_SETTING:

            mute_setting_job();

        break;

        case LONG_KEY_DEBUG_MODE:
            //
            if(gu8_debug_input_count == 3)
            {
                debug_mode_select_job();
            }
            else{}

        break;

        case LONG_KEY_3S_MEMENTO:
            //
            if( F_All_Lock == CLEAR
                && F_FW_Version_Display_Mode == SET
                && u8FactoryTestMode == NONE_TEST_MODE
                && gu8_test_mode_timeout > 0
                && gu8_Led_Display_Step == LED_Display__MAIN )
            {
                gu8_test_mode_timeout = 0;
                memento_select_job();
            }
            else if( gu8_Led_Display_Step == LED_Display__MEMENTO
                     && bit_memento_start == SET )
            {
                memento_finish_job();
            }
            else{}

        break;

        case KEY_AMBIENT_SELECT:
            //
            if( gu8_Led_Display_Step == LED_Display__MEMENTO
                && bit_memento_start == SET )
            {
                memento_delete_job();
            }
            else{}

        break;

        case LONG_KEY_3S_TAKEOFF_ICE:
            //
            start_cody_takeoff_ice();

        break;

        case LONG_KEY_3S_ICE_TRAY_TEST:
            //
            start_ice_tray_test();

        break;

        case LONG_KEY_3S_CANCEL_COMP_DELAY:
            //
            calcel_comp_delay();

        break;

        case LONG_KEY_3S_NO_USE_NO_OPERATION:
            //
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == NONE_TEST_MODE )
            {
                key_no_use_no_operation();
            }
            else{}
        break;
			
        case LONG_KEY_3S_COLD_SETTING:
		
			key_setting_cold_temp();

        break;
		
#if	CONFIG_TIME_SETTING
        case LONG_KEY_3S_TIME_SETTING:
		
			key_time_setting_job();

        break;
#endif
        default:

            NOP();

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Very_Long_Input( U16 u16key_input_value)
{
    switch(u16key_input_value)
    {
#if LONG_KEY_3S_ICE_HOT_COLD_MIX_OFF
		//mix Ű�� ���۵Ǳ� ������ ����
#else
        case KEY_COLD_SELECT:
        case LONG_KEY_3S_COLD_MISS_TOUCH:
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                cold_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}

        break;

        case KEY_HOT_SELECT:
        case LONG_KEY_3S_HOT_MISS_TOUCH:
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                hot_water_enable_setting_job(SETTING_DISABLE);
            }
            else{}

        break;
			
        case KEY_ICE:
        case LONG_KEY_3S_ICE_MISS_TOUCH:
            //
            /*..hui [23-2-9���� 6:28:05] ���ø�忡���� �ȴ���..*/
            if( bit_setting_mode_start == CLEAR )
            {
                /*..hui [24-11-21 ] ���� ON/OFF �Լ� ������..*/
                //ice_on_off_setting_job();
    			/*.. sean [25-3-18 ��� ����] 3�� ��� on / 7�� ��� off ǥ��ȭ ���� ..*/
                ice_off_setting_job();
            }
            else{}
        break;
#endif

        default:
            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



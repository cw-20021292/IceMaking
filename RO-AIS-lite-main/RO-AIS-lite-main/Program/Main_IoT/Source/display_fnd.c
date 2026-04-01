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
#include    "display_fnd.h"
/*.. sean [24-12-26] �ð� ǥ�� ���ؼ� Wifi ������� �߰�..*/
#include	"WIFI_Status.h"

void fnd_normal_state(void);
void fnd_water_out(void);
void fnd_water_out_normal(void);
void fnd_water_out_my_cup(void);
void fnd_water_out_continue(void);
void fnd_ice_out(void);
void fnd_setting(void);
void fnd_error(void);
void fnd_out( U8 mu8_direct, U8 mu8_thousand, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  );
void fnd_sleep(void);
void fnd_all_lock(void);
void fnd_altitude_setting(void);
void fnd_memento(void);
void fnd_my_cup_setting_state(void);
void fnd_version(void);
void fnd_front_test_mode_(void);
void fnd_pba_test_mode_(void);
void fnd_uart_test_mode_(void);
void fnd_manual_test_mode_(void);
void fnd_button_set(void);
void fnd_time_set(void);



const U8 Fnd_Display_Data[]
= { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,                                 /*..0 ~ 9..*/
    0x77, 0x71, 0x1C, 0x54, 0x5C, 0x73, 0x50, 0x78, 0x40, 0x79, 0x3F, 0x39, 0x76, 0x5E, 0x7A, /*..A, F, u, n, o, P, r, t, -, E, O, C, H, d, F ..*/
    0x39, 0x09, 0x0f, 0x63, 0x5C,                                                               /*..continue..square up, square down*/
    0x00 };


TYPE_BYTE          U8SetDisplayB;
#define            u8SetDisplay                         U8SetDisplayB.byte
#define            Bit0_Ice_Set_Display                 U8SetDisplayB.Bit.b0
#define            Bit1_Cold_Temp_Set_Display           U8SetDisplayB.Bit.b1
#define            Bit2_Eco_Set_Display                 U8SetDisplayB.Bit.b2
#define            Bit3_My_Cup_Set_Display              U8SetDisplayB.Bit.b3
#define            Bit4_My_Cup_Off_Display              U8SetDisplayB.Bit.b4




U8 gu8_temporary_thousand;
U8 gu8_temporary_hundred;
U8 gu8_temporary_ten;
U8 gu8_temporary_one;

U8 gu8_fnd_ice_step;
U8 gu8_fnd_ice_timer;

U8 gu8_fnd_water_step;
U8 gu8_fnd_water_timer;
U16 gu16_extract_display_timer;

U8 gu8_extract_amount;
U8 gu8_extract_display_cnt;

U8 gu8_fnd_continue_step;


U8 gu8_my_cup_setting_step;
U8 gu8_my_cup_setting_timer;

bit bit_my_cup_finish_flick;
U8 gu8_my_cup_finish_step;
U8 gu8_my_cup_finish_timer;


U8 gu8_my_cup_extract_timer;

U8 gu8_hour_setting_blink_timer;
bit bit_hour_blink_500ms;
U8 gu8_min_setting_blink_timer;
bit bit_min_blink_500ms;

extern bit F_Safety_Routine;
extern U16 gu16IceMakingADVal;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_normal_state(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

	U8 mu8_temp_hour = 0;
	U8 mu8_temp_min = 0;
    if( bit_default_cup_flick == SET )
    {
        if( gu8_default_cup_flick_state == SET )
        {
            if( gu8Cup_level == CUP_LEVEL_HALF )
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_NUM_1;
                mu8_temporary_ten = DISPLAY_NUM_2;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if(gu8Cup_level == CUP_LEVEL_ONE)
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_NUM_2;
                mu8_temporary_ten = DISPLAY_NUM_5;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if(gu8Cup_level == CUP_LEVEL_TWO)
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_NUM_5;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else if(gu8Cup_level == CUP_LEVEL_FOUR)
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
                mu8_temporary_hundred = DISPLAY_NUM_0;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
		    else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
		    {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
		        mu8_temporary_hundred = DISPLAY_NUM_CONTINUE_100;
		        mu8_temporary_ten = DISPLAY_NUM_CONTINUE_010;
		        mu8_temporary_one = DISPLAY_NUM_CONTINUE_001;
		    }
            else /*if(gu8Cup_level == CUP_LEVEL_MY_CUP)*/
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                mu8_temporary_one = DISPLAY_OFF;
            }
        }
        else
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else if( gu8_durable_test_start == SET )
    {
        if( gu16_aging_count < 10000 )
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = (U8)((gu16_aging_count / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16_aging_count / 100) % 10);
            mu8_temporary_one = (U8)((gu16_aging_count / 10) % 10);
        }
        else
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            mu8_temporary_hundred = (U8)((gu16_aging_count / 1000) % 10);
            mu8_temporary_ten = (U8)((gu16_aging_count / 100) % 10);
            mu8_temporary_one = (U8)((gu16_aging_count / 10) % 10);
        }
    }
    else
    {
		/*.. sean [24-12-26] wifi�� ����Ǿ��� ��� �ð� ǥ�� ..*/
	    //else if( ( GetWifiApStatus(STATUS_AP_WIFI) != CLEAR ) || ( GetWifiApStatus(STATUS_AP_BLE) != CLEAR ) )
	    //if( (GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) && ( gu8_cup_led_select == CLEAR )  )
	    if( (GetWifiStatusValue(WIFI_STATUS_SERVER_CON) != CLEAR ) &&  (GetWifiStatusValue(WIFI_STATUS_PAIRING) == CLEAR ) 
			/*&& ( gu8_cup_led_select == CLEAR )*/ && ( gu16_water_return_wifi_time == 0 )  )
	    {
	    	mu8_temp_hour = gu8_rtc_time_Hour;
			
	    	if( gu8_rtc_time_Hour > 12 )
	    	{
	    		mu8_temp_hour = gu8_rtc_time_Hour % 12 ;
	    	}
			else {}
			mu8_temp_min = gu8_rtc_time_Min;
			
			if( mu8_temp_hour >= 10 )
				mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
			else
				mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;		
			
	        mu8_temporary_hundred = (U8)( mu8_temp_hour  % 10 );
			
	        mu8_temporary_ten = (U8)(mu8_temp_min / 10);
	        mu8_temporary_one = (U8)(mu8_temp_min % 10);
	    }
		else
		{
	        // if( gu8Cup_level == CUP_LEVEL_HALF )
	        // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
	        //     mu8_temporary_hundred = DISPLAY_NUM_1;
	        //     mu8_temporary_ten = DISPLAY_NUM_2;
	        //     mu8_temporary_one = DISPLAY_NUM_0;
	        // }
	        // else if( gu8Cup_level == CUP_LEVEL_ONE )
	        // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
	        //     mu8_temporary_hundred = DISPLAY_NUM_2;
	        //     mu8_temporary_ten = DISPLAY_NUM_5;
	        //     mu8_temporary_one = DISPLAY_NUM_0;
	        // }
	        // else if(gu8Cup_level == CUP_LEVEL_TWO)
	        // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
	        //     mu8_temporary_hundred = DISPLAY_NUM_5;
	        //     mu8_temporary_ten = DISPLAY_NUM_0;
	        //     mu8_temporary_one = DISPLAY_NUM_0;
	        // }
	        // else if(gu8Cup_level == CUP_LEVEL_FOUR)
	        // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
	        //     mu8_temporary_hundred = DISPLAY_NUM_0;
	        //     mu8_temporary_ten = DISPLAY_NUM_0;
	        //     mu8_temporary_one = DISPLAY_NUM_0;
	        // }
		    // else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
		    // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
		    //     mu8_temporary_hundred = DISPLAY_NUM_CONTINUE_100;
		    //     mu8_temporary_ten = DISPLAY_NUM_CONTINUE_010;
		    //     mu8_temporary_one = DISPLAY_NUM_CONTINUE_001;
		    // }
	        // else /*if(gu8Cup_level == CUP_LEVEL_MY_CUP)*/
	        // {
	        //     mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
	        //     mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
	        //     mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
	        //     mu8_temporary_one = DISPLAY_OFF;
	        // }

            // 디버깅 표시
            if(F_Safety_Routine == SET)
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            }
            else
            {
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            }

            mu8_temporary_hundred = (gu16IceMakingADVal / 100);
            mu8_temporary_ten = ((gu16IceMakingADVal % 100) / 10);
            mu8_temporary_one = (gu16IceMakingADVal % 10);
		}
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_water_out(void)
{
	/*.. ���� ���� �� 3�� ��ư ������ �ְ� �����ؼ� fnd �߰��ؾ���..*/
    //if( u8Extract_Continue == SET )
    if( ( u8Extract_Continue == SET ) || ( gu8Cup_level == CUP_LEVEL_CONTINUE ) )
    {
        fnd_water_out_continue();
    }
    else
    {
        #if 0
        /*..hui [23-3-22���� 5:54:53] ������ ��� �����ϰ� ������ ����� �� ������� ����..*/
        if( bit_my_cup_enable == SET && gu8Cup_level == CUP_LEVEL_MY_CUP )
        {
            fnd_water_out_my_cup();
        }
        else
        {
            fnd_water_out_normal();
        }
        #endif

        fnd_water_out_normal();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_water_out_normal(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U16 mu16_out_time = 0;

    switch( gu8_fnd_water_step )
    {
        case 0:

            #if 0
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
            #endif

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;

            gu8_fnd_water_timer = 0;
            gu8_fnd_water_step++;

            gu16_extract_display_timer = 0;
            gu8_extract_display_cnt = 0;

        break;

        case 1:

            #if 0
            /*..hui [23-2-9���� 12:28:00] ml ǥ�ÿ�.. �����̽��� %�� ǥ��..*/
            gu16_extract_display_timer = (U16)( (u16Efluent_Time) / gu8_extract_amount );

            if( 0 >= gu16Water_Extract_Timer % gu16_extract_display_timer )
            {
                gu8_extract_display_cnt++;

                if(gu8_extract_display_cnt >= gu8_extract_amount)
                {
                    gu8_extract_display_cnt = gu8_extract_amount;
                }
                else{}
            }
            else{}
            #endif

            mu16_out_time = u16Efluent_Time - 4;

            //gu16_extract_display_timer = (U16)( (u16Efluent_Time) / 10 );
            gu16_extract_display_timer = (U16)( (mu16_out_time) / 10 );

            if( 0 >= gu16Water_Extract_Timer % gu16_extract_display_timer )
            {
                gu8_extract_display_cnt++;

                if(gu8_extract_display_cnt >= 10)
                {
                    gu8_extract_display_cnt = 10;
                }
                else{}
            }
            else{}

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

            if( gu8_extract_display_cnt >= 10 )
            {
                mu8_temporary_hundred = DISPLAY_NUM_1;
                mu8_temporary_ten = DISPLAY_NUM_0;
                mu8_temporary_one = DISPLAY_NUM_0;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;

                if( gu8_extract_display_cnt > 0 )
                {
                    mu8_temporary_ten = gu8_extract_display_cnt;
                }
                else
                {
                    mu8_temporary_ten = DISPLAY_OFF;
                }

                mu8_temporary_one = DISPLAY_NUM_0;
            }

        break;


        default :

            gu8_fnd_water_timer = 0;
            gu8_fnd_water_step = 0;

        break;


    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_water_out_my_cup(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    gu8_my_cup_extract_timer++;

    #if 0
    if( gu8_my_cup_extract_timer <= 10 )
    {
        mu8_temporary_hundred = 56;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 14;
    }
    else if( gu8_my_cup_extract_timer <= 20 )
    {
        mu8_temporary_hundred = 120;
        mu8_temporary_ten = 72;
        mu8_temporary_one = 78;
    }
    else if( gu8_my_cup_extract_timer <= 30 )
    {
        mu8_temporary_hundred = 57;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else
    {
        gu8_my_cup_extract_timer = 1;
        mu8_temporary_hundred = 56;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 14;
    }
    #endif

    if( gu8_my_cup_extract_timer <= 5 )
    {
        mu8_temporary_hundred = 48;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_my_cup_extract_timer <= 10 )
    {
        mu8_temporary_hundred = 33;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_my_cup_extract_timer <= 15 )
    {
        mu8_temporary_hundred = 1;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 0;
    }
    else if( gu8_my_cup_extract_timer <= 20 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 1;
    }
    else if( gu8_my_cup_extract_timer <= 25 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 3;
    }
    else if( gu8_my_cup_extract_timer <= 30 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 6;
    }
    else if( gu8_my_cup_extract_timer <= 35 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 12;
    }
    else if( gu8_my_cup_extract_timer <= 40 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 8;
    }
    else if( gu8_my_cup_extract_timer <= 45 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 0;
    }
    else if( gu8_my_cup_extract_timer <= 50 )
    {
        mu8_temporary_hundred = 24;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else
    {
        gu8_my_cup_extract_timer = 1;
        mu8_temporary_hundred = 48;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }

    fnd_out( DIRECT_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_water_out_continue(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

    gu8_fnd_continue_step++;

    if( gu8_fnd_continue_step <= 3 )
    {
        mu8_temporary_hundred = 16;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 6 )
    {
        mu8_temporary_hundred = 48;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 9 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 12 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 15 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 1;
    }
    else if( gu8_fnd_continue_step <= 18 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 3;
    }
    else if( gu8_fnd_continue_step <= 21 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 7;
    }
    else if( gu8_fnd_continue_step <= 24 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 27 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 30 )
    {
        mu8_temporary_hundred = 57;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 33 )
    {
        mu8_temporary_hundred = 41;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 36 )
    {
        mu8_temporary_hundred = 9;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 39 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 42 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_step <= 45 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 14;
    }
    else if( gu8_fnd_continue_step <= 48 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 12;
    }
    else if( gu8_fnd_continue_step <= 51 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 8;
    }
    else if( gu8_fnd_continue_step <= 54 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 57 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_step <= 60 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
        gu8_fnd_continue_step = 0;
    }
    else
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
        gu8_fnd_continue_step = 0;
    }

    fnd_out( DIRECT_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_ice_out(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    switch( gu8_fnd_ice_step )
    {
        case 0 :

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_ice_timer++;

            if( gu8_fnd_ice_timer >= 5 )
            {
                gu8_fnd_ice_timer = 0;
                gu8_fnd_ice_step++;
            }
            else{}

        break;

        case 1 :

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_ice_timer++;

            if( gu8_fnd_ice_timer >= 5 )
            {
                gu8_fnd_ice_timer = 0;
                gu8_fnd_ice_step++;
            }
            else{}


        break;

        case 2 :

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_OFF;

            gu8_fnd_ice_timer++;

            if( gu8_fnd_ice_timer >= 5 )
            {
                gu8_fnd_ice_timer = 0;
                gu8_fnd_ice_step++;
            }
            else{}

        break;

        case 3 :

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

            gu8_fnd_ice_timer++;

            if( gu8_fnd_ice_timer >= 5 )
            {
                gu8_fnd_ice_timer = 0;
                gu8_fnd_ice_step++;
            }
            else{}


        break;

        case 4 :

            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

            gu8_fnd_ice_timer++;

            if( gu8_fnd_ice_timer >= 5 )
            {
                gu8_fnd_ice_timer = 0;
                gu8_fnd_ice_step = 1;
            }
            else{}

        break;

        default :

            gu8_fnd_ice_step = 0;
            gu8_fnd_ice_timer = 0;

        break;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_setting(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;


    if( bit_my_cup_setting_start == SET )
    {
        if( F_WaterOut == SET )
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

            gu8_my_cup_setting_step++;

            if( gu8_my_cup_setting_step <= 5 )
            {
                mu8_temporary_hundred = 48;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 0;
            }
            else if( gu8_my_cup_setting_step <= 10 )
            {
                mu8_temporary_hundred = 33;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 0;
            }
            else if( gu8_my_cup_setting_step <= 15 )
            {
                mu8_temporary_hundred = 1;
                mu8_temporary_ten = 1;
                mu8_temporary_one = 0;
            }
            else if( gu8_my_cup_setting_step <= 20 )
            {
                mu8_temporary_hundred = 0;
                mu8_temporary_ten = 1;
                mu8_temporary_one = 1;
            }
            else if( gu8_my_cup_setting_step <= 25 )
            {
                mu8_temporary_hundred = 0;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 3;
            }
            else if( gu8_my_cup_setting_step <= 30 )
            {
                mu8_temporary_hundred = 0;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 6;
            }
            else if( gu8_my_cup_setting_step <= 35 )
            {
                mu8_temporary_hundred = 0;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 12;
            }
            else if( gu8_my_cup_setting_step <= 40 )
            {
                mu8_temporary_hundred = 0;
                mu8_temporary_ten = 8;
                mu8_temporary_one = 8;
            }
            else if( gu8_my_cup_setting_step <= 45 )
            {
                mu8_temporary_hundred = 8;
                mu8_temporary_ten = 8;
                mu8_temporary_one = 0;
            }
            else if( gu8_my_cup_setting_step <= 50 )
            {
                mu8_temporary_hundred = 24;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 0;
            }
            else
            {
                gu8_my_cup_setting_step = 1;
                mu8_temporary_hundred = 48;
                mu8_temporary_ten = 0;
                mu8_temporary_one = 0;
            }

            fnd_out( DIRECT_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

            return;
        }
        else
        {
            if( bit_my_cup_finish_flick == SET )
            {
                /*mu8_flick_state = on_off_flick_timer(5, 5);*/
                mu8_flick_state = my_cup_end_flick_timer(5, 5);

                if( mu8_flick_state == SET )
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_NUM_SMALL_d;
                }
                else
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = DISPLAY_OFF;
                }
            }
            else
            {
                gu8_my_cup_finish_step = 0;
                /*..hui [23-2-23���� 7:19:04] ������ ���� �� FND���� SEt ǥ��..*/
                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_NUM_5;
                mu8_temporary_ten = DISPLAY_NUM_LARGE_E;
                mu8_temporary_one = DISPLAY_NUM_SMALL_t;
            }
        }
    }
    else
    {
        gu8_my_cup_setting_step = 0;
        bit_my_cup_finish_flick = 0;

        /*..hui [23-2-7���� 7:55:29] ICE OFF, Cold Temp, Eco Mode..*/
        switch( u8SetDisplay )
        {
            case ON_OFF_DISPLAY_OFF:

                mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
                gu8_on_off_flick_cnt = 0;
                gu16_on_off_flick_timer = 0;

            break;
#if 0
            case ON_OFF_DISPLAY_COLD_TEMP_STE:

                /*mu8_flick_state = on_off_flick_timer(5, 5);*/
                mu8_flick_state = on_off_flick_timer(20, 0);

                if( mu8_flick_state == SET )
                {
                    if( gu8_cold_setting_level == COLD_TEMP_HIGH )
                    {
                        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                        mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                        mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                        mu8_temporary_one = DISPLAY_OFF;
                    }
                    else /*if( gu8_cold_setting_level == COLD_TEMP_LOW )*/
                    {
                        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                        mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                        mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                        mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                    }
                }
                else
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = DISPLAY_OFF;
                }

            break;
#endif
            case ON_OFF_DISPLAY_COLD_ENABLE:

                /*mu8_flick_state = on_off_flick_timer(5, 5);*/
                mu8_flick_state = on_off_flick_timer(20, 0);

                if( mu8_flick_state == SET )
                {
                    if( F_Cold_Enable == SET )
                    {
                        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                        mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                        mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                        mu8_temporary_one = DISPLAY_OFF;
                    }
                    else /*if( F_Cold_Enable == CLEAR )*/
                    {
                        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                        mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                        mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                        mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                    }
                }
                else
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = DISPLAY_OFF;
                }

            break;
            case ON_OFF_DISPLAY_MY_CUP_SET:

                /*mu8_flick_state = on_off_flick_timer(70, 0);*/
                mu8_flick_state = on_off_flick_timer(100, 0);

                if( mu8_flick_state == SET )
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_NUM_5;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_E;
                    mu8_temporary_one = DISPLAY_NUM_SMALL_t;
                }
                else
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = DISPLAY_OFF;
                }

            break;

            case ON_OFF_DISPLAY_MY_CUP_OFF:

                /*mu8_flick_state = on_off_flick_timer(5, 5);*/
                mu8_flick_state = on_off_flick_timer(20, 0);

                if( mu8_flick_state == SET )
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
                else
                {
                    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
                    mu8_temporary_hundred = DISPLAY_OFF;
                    mu8_temporary_ten = DISPLAY_OFF;
                    mu8_temporary_one = DISPLAY_OFF;
                }

            break;

            default:

                u8SetDisplay = ON_OFF_DISPLAY_OFF;
                gu8_on_off_flick_cnt = 0;
                gu16_on_off_flick_timer = 0;

            break;
        }
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_error(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_flick_state = error_flick_timer(5, 5);

    if( mu8_flick_state == SET )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (gu8_Error_Code / 10);
        mu8_temporary_one = (gu8_Error_Code % 10);
    }
    else
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 gu8TestDuty;
bit F_dutyTest;
void fnd_out( U8 mu8_direct, U8 mu8_thousand, U8 mu8_hundred, U8 mu8_ten, U8 mu8_one  )
{
    if( mu8_direct == DIRECT_DISPLAY )
    {
        gu8_front_fnd_thousand = mu8_thousand;
        gu8_front_fnd_hundred = mu8_hundred;
        gu8_front_fnd_ten = mu8_ten;
        gu8_front_fnd_one = mu8_one;
    }
    else
    {
        gu8_front_fnd_thousand = mu8_thousand;
        gu8_front_fnd_hundred = Fnd_Display_Data[ mu8_hundred ];
        gu8_front_fnd_ten = Fnd_Display_Data[ mu8_ten ];
        gu8_front_fnd_one = Fnd_Display_Data[ mu8_one ];
    }
	
	/*..sean [25-02-10]fnd �ֵ� �����Ͽ� ������ �� �ֵ��� ����..*/
	if( F_dutyTest == CLEAR )
	{
		set_led_duty( DUTY_OUT_SEGMENT_0_0_0_1, DUTY_EXTRACT_70_PERCENT );
		set_led_duty( DUTY_OUT_SEGMENT_0_0_2_0, DUTY_EXTRACT_70_PERCENT );
		set_led_duty( DUTY_OUT_SEGMENT_0_3_0_0, DUTY_EXTRACT_70_PERCENT );
		set_led_duty( DUTY_OUT_SEGMENT_4_0_0_0, DUTY_EXTRACT_70_PERCENT );
	}
	else
	{
		set_led_duty( DUTY_OUT_SEGMENT_0_0_0_1, gu8TestDuty );
		set_led_duty( DUTY_OUT_SEGMENT_0_0_2_0, gu8TestDuty );
		set_led_duty( DUTY_OUT_SEGMENT_0_3_0_0, gu8TestDuty );
		set_led_duty( DUTY_OUT_SEGMENT_4_0_0_0, gu8TestDuty );
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_sleep(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_all_lock(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_altitude_setting(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    /*mu8_temporary_one = gu8AltitudeStep;*/

    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        mu8_temporary_one = DISPLAY_NUM_1;
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        mu8_temporary_one = DISPLAY_NUM_2;
    }
    else /*if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )*/
    {
        mu8_temporary_one = DISPLAY_NUM_3;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_memento(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( gu8_memento_display_num == 0 )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (U8)(u8Memento_Buff[0] / 10);
        mu8_temporary_one = (U8)(u8Memento_Buff[0] % 10);
    }
    else if( gu8_memento_display_num == 1 )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_UPPER;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (U8)(u8Memento_Buff[1] / 10);
        mu8_temporary_one = (U8)(u8Memento_Buff[1] % 10);
    }
    else if( gu8_memento_display_num == 2 )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_LOWER;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (U8)(u8Memento_Buff[2] / 10);
        mu8_temporary_one = (U8)(u8Memento_Buff[2] % 10);
    }
    else if( gu8_memento_display_num == 3 )
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (U8)(u8Memento_Buff[3] / 10);
        mu8_temporary_one = (U8)(u8Memento_Buff[3] % 10);
    }
    else /*if( gu8_memento_display_num == 4 )*/
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_UPPER;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
        mu8_temporary_ten = (U8)(u8Memento_Buff[4] / 10);
        mu8_temporary_one = (U8)(u8Memento_Buff[4] % 10);
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_my_cup_setting_state(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    /*..hui [23-2-23���� 7:19:04] ������ ���� �� FND���� SEt ǥ��..*/
    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
    mu8_temporary_hundred = DISPLAY_NUM_5;
    mu8_temporary_ten = DISPLAY_NUM_LARGE_E;
    mu8_temporary_one = DISPLAY_NUM_SMALL_t;

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_version(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
    mu8_temporary_hundred = DISPLAY_NUM_SMALL_u;
    mu8_temporary_ten = Main_FW_Version_Main;
    mu8_temporary_one = Main_FW_Version_Sub;

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_front_test_mode_(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8_service_reed_uart == 1 )
    {
        if( F_cds_detect == SET && F_Wink_500ms == SET )
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_NUM_8;
        }
        else
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else
    {
#if 0
        mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
        mu8_temporary_hundred = DISPLAY_NUM_8;
        mu8_temporary_ten = DISPLAY_NUM_8;
        mu8_temporary_one = DISPLAY_NUM_8;
#endif
    	/*.. sean [24-12-26]���� �����ϱ����� ���� ǥ�� ..*/
        mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        mu8_temporary_hundred = DISPLAY_NUM_LARGE_K;
        mu8_temporary_ten = DISPLAY_NUM_SMALL_o;
        mu8_temporary_one = DISPLAY_NUM_SMALL_r;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_uart_test_mode_(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    /*if( gu8_water_ext_test_input == 1 )*/
    if( gu8_service_reed_uart == 1 )
    {
        if( F_cds_detect == SET && F_Wink_500ms == SET )
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_NUM_8;
        }
        else
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }
    else
    {
        mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
        mu8_temporary_hundred = DISPLAY_NUM_8;
        mu8_temporary_ten = DISPLAY_NUM_8;
        mu8_temporary_one = DISPLAY_NUM_8;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_pba_test_mode_(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
    mu8_temporary_hundred = DISPLAY_NUM_8;
    mu8_temporary_ten = DISPLAY_NUM_8;
    mu8_temporary_one = DISPLAY_NUM_8;

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_manual_test_mode_(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;


    if( bit_manual_test_start == SET )
    {
        if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
            mu8_temporary_ten = (U8)((gu8_Eva_Ice_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Eva_Ice_Temperature_One_Degree % 10);
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )*/
        {
            mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
            mu8_temporary_ten = (U8)((gu8_Eva_Cold_Temperature_One_Degree / 10) % 10);
            mu8_temporary_one = (U8)(gu8_Eva_Cold_Temperature_One_Degree % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_button_set(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;

    switch( u8ButtonSetDisplay )
    {
        case BUTTON_SET_DISPLAY_OFF:

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case BUTTON_SET_HOT_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                if( F_Hot_Enable == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;

        case BUTTON_SET_COLD_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                if( F_Cold_Enable == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }


        break;

        case BUTTON_SET_ICE_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );

            if( mu8_flick_state == SET )
            {
                if( F_IceOn == SET )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;

        case BUTTON_SET_COLD_TEMP_DISPLAY:

            mu8_flick_state = button_set_display_timer( BUTTON_SET_DISPLAY_TIME );
			
            if( mu8_flick_state == SET )
            {
                if( gu8_cold_setting_level == COLD_TEMP_HIGH )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_SMALL_n;
                    mu8_temporary_one = DISPLAY_OFF;
                }
                else // ( gu8_cold_setting_level == COLD_TEMP_LOW )
                {
                    mu8_temporary_hundred = DISPLAY_NUM_LARGE_O;
                    mu8_temporary_ten = DISPLAY_NUM_LARGE_F;
                    mu8_temporary_one = DISPLAY_NUM_LARGE_F;
                }
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = DISPLAY_OFF;
            }

        break;


        default:

            u8ButtonSetDisplay = BUTTON_SET_DISPLAY_OFF;
            gu16_button_set_display_timer = 0;

        break;
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_time_set(void)
{
	U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8_time_setting_step == SETTING_TIME_HOUR )
    {
        gu8_hour_setting_blink_timer++;

        if( gu8_hour_setting_blink_timer >= 5 )
        {
            if( u8TimeSettingLongKey > 0 )
            {
                gu8_hour_setting_blink_timer = 0;
                bit_hour_blink_500ms = CLEAR;
            }
            else
            {
                gu8_hour_setting_blink_timer = 0;
                bit_hour_blink_500ms ^= SET;
            }
        }
        else{}

        if( bit_hour_blink_500ms == CLEAR )
        {
            //mu8_temporary_hundred = DISPLAY_OFF;
            //mu8_temporary_ten = (U8)((gu8_temporary_Hour / 10) % 10);
            //mu8_temporary_one = (U8)(gu8_temporary_Hour % 10);
            if( ( gu8_temporary_Hour / 10 ) > 0)
            {
				mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            	mu8_temporary_hundred = gu8_temporary_Hour % 10;
            }
			else
			{				
				mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            	mu8_temporary_hundred = gu8_temporary_Hour;
			}
        }
        else // ( bit_hour_blink_500ms == SET )
        {
            mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            mu8_temporary_hundred = DISPLAY_OFF;
        }
        mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
    }
    else if( gu8_time_setting_step == SETTING_TIME_MIN )
    {
        gu8_min_setting_blink_timer++;

        if( gu8_min_setting_blink_timer >= 5 )
        {
            if( u8TimeSettingLongKey > 0 )
            {
                gu8_min_setting_blink_timer = 0;
                bit_min_blink_500ms = CLEAR;
            }
            else
            {
                gu8_min_setting_blink_timer = 0;
                bit_min_blink_500ms ^= SET;
            }
        }
        else{}

        if( bit_min_blink_500ms == CLEAR )
        {
            if( ( gu8_temporary_Hour / 10 ) > 0)
            {
				mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            	mu8_temporary_hundred = gu8_temporary_Hour % 10;
            }
			else
			{
				mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            	mu8_temporary_hundred = gu8_temporary_Hour;
			}
            mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
            mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
        }
        else
        {
            if( ( gu8_temporary_Hour / 10 ) > 0)
            {
				mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
            	mu8_temporary_hundred = gu8_temporary_Hour % 10;
            }
			else
			{
				mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
            	mu8_temporary_hundred = gu8_temporary_Hour;
			}
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }  
    else //if( gu8_time_setting_step == SETTING_TIME_FINISH )
    {
        if( ( gu8_temporary_Hour / 10 ) > 0)
        {
			mu8_temporary_thousand = DISPLAY_THOUSAND_NUM_1;
        	mu8_temporary_hundred = gu8_temporary_Hour % 10;
        }
		else
		{
			mu8_temporary_thousand = DISPLAY_THOUSAND_OFF;
        	mu8_temporary_hundred = gu8_temporary_Hour;
		}
        mu8_temporary_ten = (U8)((gu8_temporary_Min / 10) % 10);
        mu8_temporary_one = (U8)(gu8_temporary_Min % 10);
    }

    fnd_out( FIXED_DISPLAY, mu8_temporary_thousand, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


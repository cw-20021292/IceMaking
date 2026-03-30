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
#include    "display_led_wifi.h"

void led_wifi_pairing(void);
void wifi_icon_output(void);
void wifi_pairing_display(void);


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_wifi_pairing(void)
{
    /*..hui [23-12-4오후 2:14:16] 페어링 화면에서는 wifi 아이콘이랑 퍼센트만 표시..*/
    wifi_icon_output();
	
    percent_ml_led_out();
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_icon_output(void)
{
    if( gu8_Wifi_Connect_State == WIFI_OFF )
    {
        Bit3_Led_Wifi_Icon_White = CLEAR;
        //Bit4_Led_Wifi_Icon_Blue = CLEAR;
        gu8_wifi_disp_timer = 0;
        gu16_wifi_pairing_30min_timer = 0;
        gu8_wifi_pairing_5sec_timer = 0;
        bit_pairing_5s_display_start = CLEAR;
    }
    else if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        Bit3_Led_Wifi_Icon_White = SET;
        //Bit4_Led_Wifi_Icon_Blue = CLEAR;
        gu8_wifi_disp_timer = 0;
        gu16_wifi_pairing_30min_timer = 0;
        gu8_wifi_pairing_5sec_timer = 0;
        bit_pairing_5s_display_start = CLEAR;
    }
    else /*if( gu8_Wifi_Connect_State == WIFI_DISCONNECT )*/
    {
        gu8_wifi_disp_timer++;

        if( gu8_wifi_disp_timer >= 10 )
        {
            gu8_wifi_disp_timer = 0;
        }
        else{}

        if( gu8_wifi_ap_mode == SET || gu8_ble_ap_mode == SET )
        {
            gu16_wifi_pairing_30min_timer++;

            if( gu16_wifi_pairing_30min_timer >= WIFI_PAIRING_START_30_MIN )
            {
                /*..hui [24-8-6오전 9:50:14] 정상모드에서 30분동안 표시 후 OFF 표시..*/
                gu16_wifi_pairing_30min_timer  = WIFI_PAIRING_START_30_MIN;

                if( bit_pairing_5s_display_start == SET && gu8_Led_Display_Step != LED_Display__WATER_EXTRACT )
                {
                    gu8_wifi_pairing_5sec_timer++;

                    /*..hui [24-8-6오전 9:58:42] 물 추출 종료되고 5초 동안 표시..*/
                    if( gu8_wifi_pairing_5sec_timer >= 50 )
                    {
                        gu8_wifi_pairing_5sec_timer = 0;
                        bit_pairing_5s_display_start = CLEAR;
                    }
                    else{}

                    wifi_pairing_display();
                }
                else
                {
                    Bit3_Led_Wifi_Icon_White = CLEAR;
                    //Bit4_Led_Wifi_Icon_Blue = CLEAR;
                    gu8_wifi_disp_timer = 0;
                    gu8_wifi_pairing_5sec_timer = 0;
                }
            }
            else
            {
                gu8_wifi_pairing_5sec_timer = 0;
                bit_pairing_5s_display_start = CLEAR;
                wifi_pairing_display();
            }
        }
        else
        {
            gu16_wifi_pairing_30min_timer = 0;
            gu8_wifi_pairing_5sec_timer = 0;
            bit_pairing_5s_display_start = CLEAR;

            if( gu8_wifi_disp_timer >= 5 )
            {
                Bit3_Led_Wifi_Icon_White = SET;
                //Bit4_Led_Wifi_Icon_Blue = CLEAR;
            }
            else
            {
                Bit3_Led_Wifi_Icon_White = CLEAR;
                //Bit4_Led_Wifi_Icon_Blue = CLEAR;
            }
        }
    }

    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_led_duty( DUTY_OUT_WIFI_WHITE_ICON, DUTY_20_PERCENT );
    }
    else
    {
		set_led_duty( DUTY_OUT_WIFI_WHITE_ICON, DUTY_EXTRACT_70_PERCENT );
    }


}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_pairing_display(void)
{
    /*..hui [23-6-14오전 9:34:53] BLE일 경우 BLUE..*/
    if( gu8_ble_ap_mode == SET )
    {
        /*Bit1_Front_Right_Led_Wifi_Icon_White = CLEAR;*/

        if( gu8_wifi_disp_timer == 0 )
        {
            /*..hui [24-3-27오후 7:31:20] 블루 켤떄 화이트 10%로 같이 켜줌..디자ㅣㄴ..*/
            Bit4_Led_Wifi_Icon_Blue = SET;
            Bit3_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            Bit4_Led_Wifi_Icon_Blue = CLEAR;
            Bit3_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            /*..hui [24-3-27오후 7:31:20] 블루 켤떄 화이트 10%로 같이 켜줌..디자ㅣㄴ..*/
            Bit4_Led_Wifi_Icon_Blue = SET;
            Bit3_Led_Wifi_Icon_White = SET;
        }
        else
        {
            Bit4_Led_Wifi_Icon_Blue = CLEAR;
            Bit3_Led_Wifi_Icon_White = CLEAR;
        }
    }
    else
    {
        Bit4_Led_Wifi_Icon_Blue = CLEAR;

        if( gu8_wifi_disp_timer == 0 )
        {
            Bit3_Led_Wifi_Icon_White = SET;
        }
        else if( gu8_wifi_disp_timer == 1 )
        {
            Bit3_Led_Wifi_Icon_White = CLEAR;
        }
        else if( gu8_wifi_disp_timer == 2 )
        {
            Bit3_Led_Wifi_Icon_White = SET;
        }
        else
        {
            Bit3_Led_Wifi_Icon_White = CLEAR;
        }
    }
}






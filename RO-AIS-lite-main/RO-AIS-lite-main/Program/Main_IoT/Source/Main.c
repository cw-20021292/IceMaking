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
#include    "Main.h"
#include	"WIFI_Config.h"

void main(void);
void Sync_50MS(void);
void Sync_100MS(void);
void check_adc(void);
/*.. sean [24-10-02] Ais Lite WiFi �߰��� ���� ��� �߰�.. */
void wifi(void);

U8 u8_wifi_timer;

U8 aa;

U8 u8_wifi_timer_1sec;
U16 u16_wifi_timer_1min;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void main(void)
{

    System_ini();

    while(1)
    {
        WDTE = (U8)0xAC;

        if(u8FactoryTestMode > 0)
        {
            Sync_100MS();

            if(u8FactoryTestMode == PCB_TEST_MODE)
            {
                Front_Communication();
                Pcb_Test_Main();
            	wifi();
				
            }
            else if(u8FactoryTestMode == DISPLAY_TEST_MODE)
            {
                Front_Communication();		
                Display_Test_Main();
            }
            else /*if(u8FactoryTestMode == UART_TEST_MODE)*/
            {
                /*..hui [23-3-15���� 2:16:43] 2���.. ����Ʈ �˻� ������ �˻���..*/
                if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST )
                {
                    Front_Communication();
                }
                else{}

                Uart_Test_Main();
                wifi();
            }
        }
        else
        {
            Sync_50MS();
            Front_Communication();

            Sync_100MS();
            Input();
            Mode_Control();
            Ice_Make_Process();
            Make_Mode_Decision();
            Heating_Control();
            Output();
            Error_Control();
            Display_Control();
            Front_Communication();
            self_test();
			
            Save_Eeprom_Data();
            wifi();

            #if CONFIG_MMI
                Pc_Communication();
            #endif
        }
    }
}/* --- End of main() --- */

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Sync_50MS(void)
{
    while(u8CountSync < 50)
    {
        check_adc();
        WifiControlProcess(WIFI_TIME_WHILE);
    }

    /*u8CountSync = CLEAR;*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Sync_100MS(void)
{
    while(u8CountSync < 100)
    {
        check_adc();
        WifiControlProcess(WIFI_TIME_WHILE);
    }

    u8CountSync = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_adc(void)
{
    if( F_ADC_Check == SET )
    {
        F_ADC_Check = CLEAR;
        AD_Conversion();
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi(void)
{
    // u8_wifi_timer_1sec++;

    WifiControlProcess(WIFI_TIME_100MS);

    // if( u8_wifi_timer_1sec >= 10 )
    // {
    //     u8_wifi_timer_1sec = 0;
    //     WifiControlProcess(WIFI_TIME_1SEC);
    // }
    // else{}

    // u16_wifi_timer_1min++;

    // if( u16_wifi_timer_1min >= 600 )
    // {
    //     u16_wifi_timer_1min = 0;
    //     WifiControlProcess(WIFI_TIME_1MIN);
    // }
    // else{}
}





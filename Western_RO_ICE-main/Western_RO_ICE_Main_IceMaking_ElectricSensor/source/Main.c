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

void main(void);
void Sync_50MS(void);
void Sync_100MS(void);
void wifi(void);
void check_adc(void);

U8 u8_wifi_timer_1sec;
U16 u16_wifi_timer_1min;

U8 aa;
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
                ProcessVoice_Main();
                wifi();
            }
            else if(u8FactoryTestMode == DISPLAY_TEST_MODE)
            {
                Front_Communication();
                Display_Test_Main();
                ProcessVoice_Main();
            }
            else /*if(u8FactoryTestMode == UART_TEST_MODE)*/
            {
                /*..hui [23-3-15오후 2:16:43] 2모드.. 프론트 검사 포함한 검사모드..*/
                /*..hui [24-4-26오후 5:26:41] 1모드에서 유량값 표시 추가..*/
                if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST
                    || gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
                {
                    Front_Communication();
                }
                else{}

                Uart_Test_Main();
                ProcessVoice_Main();
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
            flushing_main();
            Output();
            Error_Control();
            Display_Control();
            Front_Communication();
            ProcessVoice_Main();
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
void wifi(void)
{
    u8_wifi_timer_1sec++;

    WifiControlProcess(WIFI_TIME_100MS);

    if( u8_wifi_timer_1sec >= 10 )
    {
        u8_wifi_timer_1sec = 0;
        WifiControlProcess(WIFI_TIME_1SEC);
    }
    else{}

    u16_wifi_timer_1min++;

    if( u16_wifi_timer_1min >= 600 )
    {
        u16_wifi_timer_1min = 0;
        WifiControlProcess(WIFI_TIME_1MIN);
    }
    else{}
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
        /*..hui [23-9-19오전 11:27:38] 외기 센서 1개 추가에 따라 최종 적용 값 결정..*/
        get_final_small_amb_temp();
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





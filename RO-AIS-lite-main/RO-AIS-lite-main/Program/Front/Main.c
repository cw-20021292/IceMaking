/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "Main.h"

void main(void);
void Sync(void);
void check_adc(void);


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

        if(F_10ms == SET)
        {
            F_10ms = CLEAR;
            Front_Communication();
        }
        else{}

        if(F_100ms == SET)
        {
            F_100ms = CLEAR;
        	check_adc();
            /*Led_Output();*/
        }
        else{}
        
        Sync();
        //Led_Output();
        //service_check_input();
        //Front_Communication();
    }


}/* --- End of main() --- */

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 
***********************************************************************************************************************/
void Sync(void)
{
    while(u8CountSync < 100)
    {
        //;
        check_adc();
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



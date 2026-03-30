/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "M0_System_init.h"


void System_ini(void);
void Ram_Init(void);
void Variable_Init(void);
void system_reset(void);


bit F_PowerOn;

bit F_System_Init_Finish;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void System_ini(void)
{
    DI();

    Ram_Init();

    R_TAU0_Channel0_Start();   /* timer 250us */

    R_UART2_Start();           /* front panel comm */

    EI();

    Variable_Init();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ram_Init(void)
{
    /* ram initialize */
    U32 ram_addr = 0;
    U8 *p_ram_addr = 0;

    //for(ram_addr = 0xFCF00; ram_addr < 0xFFE20; ram_addr++)
    for(ram_addr = 0xFCF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Variable_Init(void)
{

    gu8_ota_start = CLEAR;


    F_PowerOn = 1;
    F_Service_Check_Input = SET;
    //
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void system_reset(void)
{
    DI();

    while(1)
    {
        ;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



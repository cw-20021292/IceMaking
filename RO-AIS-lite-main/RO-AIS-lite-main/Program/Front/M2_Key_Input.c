/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Input.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "M2_Key_Input.h"




void Key_Input(void);
void key_input_check(void);
void key_input_processing(U8 u8key_state, U8 u8key_num);
void key_input_sampling( U16 u16key_input_value);

U16 gu16_Key_Input;
U16 gu16_Key_Buffer;
U16 gu16_Key_Sampling_Counter;
U16 gu16_Key_Input_Final;
U16 gu16_Key_Input_Final_Old;





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input(void)
{
    key_input_check();
    key_input_sampling(gu16_Key_Input);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_check(void)
{
    key_input_processing( (U8)pKEY_SETTING_START, 15);
    key_input_processing( (U8)pKEY_ICE, 14);
    key_input_processing( (U8)pKEY_HOT, 13);
    key_input_processing( (U8)pKEY_AMBIENT, 12);
    key_input_processing( (U8)pKEY_COLD, 11);
    key_input_processing( (U8)pKEY_AMOUNT, 10);
    key_input_processing( (U8)pKEY_SETTING_ICE_FIRST, 9);
    key_input_processing( (U8)pKEY_SETTING_ICE_LOCK, 8);
    key_input_processing( (U8)pKEY_SETTING_HOT_LOCK, 7);
    key_input_processing( (U8)pKEY_SETTING_ECO_MODE, 6);
    key_input_processing( (U8)pKEY_SETTING_COLD_TEMP, 5);
    key_input_processing( (U8)pKEY_SETTING_MY_CUP, 4);

    key_input_processing( (U8)pKEY_ICE_EXTRACT, 3);
    key_input_processing( (U8)pKEY_WATER_EXTRACT, 2);

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_processing(U8 u8key_state, U8 u8key_num)
{
    U16 u16KeyMask = 0x01;

    if( u8key_state == SET)
    {
        gu16_Key_Input &= ~(U16)(u16KeyMask << (U16)u8key_num);
    }
    else
    {
        gu16_Key_Input |= (U16)(u16KeyMask << (U16)u8key_num);
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_sampling( U16 u16key_input_value)
{
    if(u16key_input_value == gu16_Key_Buffer)
    {
        if(gu16_Key_Buffer == UControl_Key_Mask)
        {
            gu16_Key_Sampling_Counter = 0;
            gu16_Key_Input_Final = 0;
        }
        else
        {
            gu16_Key_Sampling_Counter++;
        }

        if(gu16_Key_Sampling_Counter >= 70)
        {
            gu16_Key_Sampling_Counter = 70;
            gu16_Key_Input_Final = gu16_Key_Buffer;
        }
        else{}
    }
    else
    {
        gu16_Key_Buffer = u16key_input_value;
        gu16_Key_Sampling_Counter = 0;

        //F_Key_Short_Push_State = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "uv_faucet.h"


void output_faucet_uv(void);
U8 uv_faucet_control(void);
void uv_faucet_operation_timer(void);
U8 uv_faucet_standby_timer(void);
void start_faucet_uv(void);
void initial_faucet_uv_timer(void);



/***********************************************************************************************************************/
TYPE_BYTE          U8FaucetUVONB;
#define            gu8FaucetUVOn                          U8FaucetUVONB.byte
#define            Bit0_Faucet_UV_On_State                U8FaucetUVONB.Bit.b0


TYPE_BYTE          U8FaucetUVOFFB;
#define            u8FaucetUvOFF                          U8FaucetUVOFFB.byte
#define            Bit0_Water_Out_Faucet_UV_Off_State     U8FaucetUVOFFB.Bit.b0

/***********************************************************************************************************************/
bit bit_faucet_uv_start;

U16 gu16_faucet_uv_operation_timer_sec;
U16 gu16_faucet_uv_operation_timer_min;
U16 gu16_faucet_uv_operation_timer_hour;

U16 gu16_faucet_uv_standby_timer_sec;
U16 gu16_faucet_uv_standby_timer_min;
U16 gu16_faucet_uv_standby_timer_hour;

U8 gu8_uv_faucet_step;


bit bit_uv_faucet_out;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_faucet_uv(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}
	
    Bit0_Faucet_UV_On_State = uv_faucet_control();

    /***********************************************************************************************/
    /*..hui [19-10-24ï¿½ï¿½ï¿½ï¿½ 8:04:54] ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½..*/
    if( F_WaterOut == SET )
    {
        Bit0_Water_Out_Faucet_UV_Off_State = SET;
    }
    else
    {
        Bit0_Water_Out_Faucet_UV_Off_State = CLEAR;
    }
/***********************************************************************************************/
    if( u8FaucetUvOFF > 0 )
    {
        pUV_LED_WATER_FAUCET = CLEAR;                  /*off*/
        Bit3_Faucet_UV_12V_Out_State = CLEAR;
        bit_uv_faucet_out = CLEAR;
    }
    else
    {
        if( gu8FaucetUVOn > 0 )
        {
            pUV_LED_WATER_FAUCET = SET;                 /*on*/
            Bit3_Faucet_UV_12V_Out_State = SET;
            bit_uv_faucet_out = SET;
        }
        else
        {
            pUV_LED_WATER_FAUCET = CLEAR;              /*off*/
            Bit3_Faucet_UV_12V_Out_State = CLEAR;
            bit_uv_faucet_out = CLEAR;
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_faucet_control(void)
{
    U8 mu8_return = 0;
    U8 mu8_finish = 0;

/********************************************************************************************/
    switch( gu8_uv_faucet_step )
    {
        case 0 :

            /*..hui [19-10-24¿ÀÈÄ 8:34:44] 6½Ã°£ ´ë±â..*/
			/*..sean [23-07-14¿ÀÈÄ 16:00:00] 5½Ã°£ ´ë±â..*/
            mu8_finish = uv_faucet_standby_timer();

            if(mu8_finish == SET)
            {
                gu8_uv_faucet_step = 1;
                start_faucet_uv();
            }
            else{}

        break;

        case 1 :

            /*..hui [23-2-10¿ÀÀü 10:55:28] ÆÄ¿ì¼Â UV´Â 30ºÐ¸¸ °¡µ¿..*/
            if(bit_faucet_uv_start == SET)
            {
                /*..hui [23-2-10¿ÀÀü 10:55:38] ¹° ÃßÃâÁß¿¡´Â Á¤Áö..*/
                if( u8FaucetUvOFF == 0 )
                {
                    uv_faucet_operation_timer();
                    mu8_return = SET;
                }
                else{}
            }
            else
            {
                gu8_uv_faucet_step = 0;
            }

        break;

        default :

            gu8_uv_faucet_step = 0;

        break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uv_faucet_operation_timer(void)
{
    gu16_faucet_uv_operation_timer_sec++;

    if(gu16_faucet_uv_operation_timer_sec >= 600)
    {
        gu16_faucet_uv_operation_timer_sec = 0;
        gu16_faucet_uv_operation_timer_min++;
    }
    else{}

    /*..hui [23-2-10¿ÀÀü 10:56:02] ÆÄ¿ì¼Â UV´Â 30ºÐ¸¸ °¡µ¿..*/
	/*..sean [23-7-14 ¿ÀÈÄ 3:52:12 ] 30ºÐ °¡µ¿¿¡¼­ 1½Ã°£ °¡µ¿À¸·Î º¯°æ  ..*/
    //if(gu16_faucet_uv_operation_timer_min >= 30)
    if(gu16_faucet_uv_operation_timer_min >= 30)
    {
        bit_faucet_uv_start = CLEAR;
        initial_faucet_uv_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 uv_faucet_standby_timer(void)
{
    U8 mu8_return = 0;

    gu16_faucet_uv_standby_timer_sec++;

    if(gu16_faucet_uv_standby_timer_sec >= 600)
    {
        gu16_faucet_uv_standby_timer_sec = 0;
        gu16_faucet_uv_standby_timer_min++;
    }
    else{}

    if(gu16_faucet_uv_standby_timer_min >= 60)
    {
        gu16_faucet_uv_standby_timer_min = 0;
        gu16_faucet_uv_standby_timer_hour++;
    }
    else{}

    /*..hui [19-10-24¿ÀÈÄ 9:29:57] 6½Ã°£ ´ë±â Áß Áï½Ã»ì±Õ ¼±ÅÃ ½Ã Áï½Ã »ì±Õ ½ÃÀÛ..*/
    /*..hui [20-3-6¿ÀÈÄ 4:58:21] ¼öµ¿ »ì±Õ »èÁ¦..*/
    /*if( gu16_faucet_uv_standby_timer_hour >= 6 )*/
    /*..hui [23-4-4¿ÀÈÄ 4:52:54] ÆÄ¿ì¼Â UV´Â 5½Ã°£ 30ºÐ ´ë±â - 30ºÐ °¡µ¿À¸·Î.. ÃÖÀÎ½Ä´Ô..*/
    /*..hui [23-4-4¿ÀÈÄ 4:53:00] 30ºÐ °¡µ¿ÀÌ 6½Ã°£¾È¿¡ Æ÷ÇÔµÊ..*/
	/*..sean [23-7-14 ¿ÀÈÄ 3:52:12 ] 30ºÐ °¡µ¿¿¡¼­ 1½Ã°£ °¡µ¿À¸·Î º¯°æ  ..*/
    //if( gu16_faucet_uv_standby_timer_hour >= 5 && gu16_faucet_uv_standby_timer_min >= 30 )
	//if( gu16_faucet_uv_standby_timer_hour >= 5)	
    if( gu16_faucet_uv_standby_timer_hour >= 3 && gu16_faucet_uv_standby_timer_min >= 30 )
    {
        initial_faucet_uv_timer();
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_faucet_uv(void)
{
    bit_faucet_uv_start = SET;
    initial_faucet_uv_timer();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_faucet_uv_timer(void)
{
    gu16_faucet_uv_operation_timer_sec = 0;
    gu16_faucet_uv_operation_timer_min = 0;
    gu16_faucet_uv_operation_timer_hour = 0;

    gu16_faucet_uv_standby_timer_sec = 0;
    gu16_faucet_uv_standby_timer_min = 0;
    gu16_faucet_uv_standby_timer_hour = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



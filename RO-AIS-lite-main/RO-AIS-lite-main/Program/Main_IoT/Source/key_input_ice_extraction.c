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
#include    "key_input_ice_extraction.h"

void key_input_ice_extract(void);

void input_ice_extract_key(void);
void ice_ext_button_operation(void);
void ice_extraction_start(void);
void ice_extraction_finish(void);

U8 u8ice_ext_on_decision_cnt;
U8 u8ice_ext_off_decision_cnt;


U8 gu8_Key_Ice_Extract;
bit F_Key_IceExtraction;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_ice_extract(void)
{
    input_ice_extract_key();

    if(u8FactoryTestMode == NONE_TEST_MODE)
    {
        ice_ext_button_operation();
    }
    else
    {
        PCB_Test_Mode_Ice_Key_Short_Input();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_extract_key(void)
{
    if(gu8_Key_Ice_Extract != SET)
    {
        u8ice_ext_on_decision_cnt = 0;
        u8ice_ext_off_decision_cnt++;

        if( u8ice_ext_off_decision_cnt >= 100 )
        {
            u8ice_ext_off_decision_cnt = 100;
            F_Key_IceExtraction = CLEAR;
        }
        else{}
    }
    else
    {
        u8ice_ext_off_decision_cnt = 0;
        u8ice_ext_on_decision_cnt++;

        if ( u8ice_ext_on_decision_cnt >= 100 )
        {
            u8ice_ext_on_decision_cnt = 100;
            F_Key_IceExtraction = SET;
            auto_drain_key_off_check();
            power_saving_init();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_ext_button_operation(void)
{
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    /*..hui [23-2-9오후 2:03:49] 세팅모드에서는 부저음없이 추출안됨..*/
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    if(F_Key_IceExtraction == SET)
    {
        if(F_ExtractKeySet == CLEAR)
        {
            if(F_All_Lock == SET)
            {
                BuzStep(BUZZER_ERROR);
                start_all_lock_flick();
            }
            else
            {
                ice_extraction_start();
            }

            F_ExtractKeySet = SET;
        }
        else{}

        bit_standby_input = SET;
    }
    else
    {
        if( gu8_durable_test_start == CLEAR )
        {
            ice_extraction_finish();
            F_ExtractKeySet = CLEAR;
			/*.. sean [24-09-30] 얼음 추출구 UV 추가 ..*/
			F_IceExtractUVSet = SET;
        }
        else
        {
#if 0
			if( gu16_durable_test_step != 8 )
    		{
    		    ice_extraction_finish();
    		    F_ExtractKeySet = CLEAR;
    		}
    		else{}
#endif
		}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_start(void)
{
    /*..hui [24-4-24오후 5:43:33] 표시중 버튼눌리면 바로 종료..*/
    /*..hui [23-5-31오후 2:18:04] 온수버튼 눌려도 상태표시 중지. ..*/
    stop_button_set_display();
	
    if( gu8_fota_start == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}
	
    if(F_Ice_Lock == SET)
    {
        /*..hui [19-10-7오후 3:30:31] 얼음잠금 팝업출력..*/
        /*..hui [19-12-10오전 9:41:41] 물 추출중이 아닐 경우에만 표시하도록 ..*/
        if(F_WaterOut == CLEAR)
        {
            /*Bit4_IcE_Lock_Popup_State = SET;*/

        }
        else{}

        F_Ice = CLEAR;
        F_IceOutCCW = CLEAR;

        /*Bit0_Ice_Lock_Indicator = SET;*/
        start_ice_lock_flick();
        BuzStep(BUZZER_ERROR);
        return;
    }
    else{}

    /*if( gu8_ice_setting == ICE_SETTING_OFF )*/
    if(F_IceOn == CLEAR)
    {
        /*..hui [19-12-10오전 9:41:41] 물 추출중이 아닐 경우에만 표시하도록 ..*/
        if(F_WaterOut == CLEAR)
        {

        }
        else{}
    }
    else{}

    if(F_Ice != SET)
    {
        F_Ice = SET;

        if(F_Ice == SET)
        {
            BuzStep(BUZZER_SETUP);

            /*..hui [24-4-24오후 6:57:38] 추가..*/
            if( F_IceOn == CLEAR )
            {
                /*..hui [24-4-3오후 5:45:48] 얼음 OFF돼있으면 얼음 추출할때도 얼음버튼 점멸 추가..*/
                start_ice_off_flick();
            }
            else{}
        }
        else
        {
            BuzStep(BUZZER_CANCEL);
        }

        if(F_Ice == SET)
        {
            F_IceOpen = SET;
            F_IceOutCCW = SET;
            gu8IceOutCCWInterval = 30;

            /*..hui [20-4-16오전 10:39:30] 역회전 동작중이었으면 취소..*/
            bit_ice_out_back_state = CLEAR;

            /* 아이스 도어 강제 닫힘 기능값 겹치는 경우 FULL OPEN */
            if( gu16IceDoorCloseResetTimer  != 0 )
            {
                gu16StepMotor2  = 0;
            }
            else{}
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_finish(void)
{
	/*.. wifi 연결시 이상동작 막기위해서 예외처리 제외..*/
    /* if(F_Ice_Lock == SET || F_All_Lock == SET)        // 얼음잠금 시 닫힘완료음 없음
    {
        F_ExtractKeySet = CLEAR;
    }
    else */if(F_Ice == SET && F_LineTest != SET)
    {
        F_Ice = CLEAR;

        /*..hui [20-4-22오전 10:44:03] 역회전 조건 만족하지 않을경우 즉시 만빙 감지..*/
        /*..hui [20-4-22오전 10:44:15] 역회전 조건이면 역회전 완료하고 만빙 감지..*/
        if( bit_ice_out_back_state == CLEAR )
        {
            F_IR = SET;
        }
        else{}

        F_IceOutCCW = CLEAR;
        gu8IceClose = 30;         // 얼음도어 닫힘지연 3초
        F_ExtractKeySet = CLEAR;

        /*..hui [19-8-22오전 9:39:28] 얼음 추출 종료음은 안나도록.. 캐럿 기준..*/
        BuzStep(BUZZER_CANCEL);
    }
    else if(F_ExtractKeySet == SET)
    {
        F_ExtractKeySet = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


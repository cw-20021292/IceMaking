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
#include    "extract_control.h"


void water_extract_control(void);





U8 gu8_effluent_control_timer;
bit F_Effluent_OK;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_control(void)
{
    if(F_WaterOut == SET)
    {
        gu16Water_Extract_Timer++;

        if( gu16Water_Extract_Timer >= u16Efluent_Time )
        {
            F_WaterOut = CLEAR;
            gu16Water_Extract_Timer = 0;
            u16Efluent_Time = 0;

            /*BuzStep(BUZZER_EFFLUENT_END);*/

            if( bit_my_cup_setting_start == SET )
            {
                BuzStep(BUZZER_SETUP);
            }
            else
            {
                BuzStep(BUZZER_EFFLUENT_END);
            }

            /*..hui [18-1-11오후 11:12:11] 연속추출 정지..*/
            u8Extract_Continue = CLEAR;

            /*..hui [18-3-14오후 3:50:40] 정량추출 종료..*/
            F_WaterOut_Disable_State = SET;
        }
        else
        {
            if( bit_my_cup_setting_start == SET )
            {
                if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
                {
                    BuzStep(BUZZER_ERROR);
                    /*..hui [23-3-23오후 1:51:31] 마이컵 설정 종료. 다시 Set 표시 화면으로..*/
                    halt_my_cup_setting();
                    start_low_water_flick();

                    F_WaterOut = CLEAR;
                    gu16Water_Extract_Timer = 0;
                    u16Efluent_Time = 0;
                }
                else{}
            }
            else{}

            /*..hui [23-5-9오전 11:46:25] 온수 추출중 저수위일 경우 정지..*/
            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
                {
                    BuzStep(BUZZER_ERROR);

                    F_WaterOut = CLEAR;
                    gu16Water_Extract_Timer = 0;
                    u16Efluent_Time = 0;

                    /*..hui [18-1-11오후 11:12:11] 연속추출 정지..*/
                    u8Extract_Continue = CLEAR;

                    /*..hui [18-3-14오후 3:50:40] 정량추출 종료..*/
                    F_WaterOut_Disable_State = SET;
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        gu16Water_Extract_Timer = 0;

        /*..hui [18-1-22오후 5:37:49] 냉수 탱크 청소모드 해제..*/
        /*..hui [20-1-30오전 10:13:58] 피드밸브 동작 유지, 냉각/제빙 동작은 코디닥터 점검기능에서 한다..*/
        F_ColdConty = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



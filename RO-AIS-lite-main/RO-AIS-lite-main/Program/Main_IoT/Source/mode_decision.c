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
#include    "mode_decision.h"

void Make_Mode_Decision(void);
void cold_mode_decision(void);
void ice_mode_decision(void);
U8 cold_mode_comp_control(void);
void final_mode_decision(void);
U8 cold_comp_test(void);
void cold_priority_decision(void);
void ice_priority_decision(void);
void check_dual_mode(void);




TYPE_WORD          U16ColdOperationW;
#define            u16ColdOperation                            U16ColdOperationW.word
#define            u8ColdOperation_L                           U16ColdOperationW.byte[0]
#define            u8ColdOperation_H                           U16ColdOperationW.byte[1]
#define            Bit0_Cold_Setting                           U16ColdOperationW.Bit.b0
#define            Bit1_Cold_Low_Water                         U16ColdOperationW.Bit.b1
#define            Bit2_Cold_Temp_Protect                      U16ColdOperationW.Bit.b2
#define            Bit3_Cold_Temp_Control                      U16ColdOperationW.Bit.b3
#define            Bit4_Ice_Init_Cold_Stop                     U16ColdOperationW.Bit.b4
#define            Bit5_Cold_Error                             U16ColdOperationW.Bit.b5
#define            Bit6_Clean_Cold_Tank                        U16ColdOperationW.Bit.b6
#define            Bit7_Cody_Service_Cold_Off                  U16ColdOperationW.Bit.b7


TYPE_WORD          U16IceOperationW;
#define            u16IceOperation                            U16IceOperationW.word
#define            u8IceOperation_L                           U16IceOperationW.byte[0]
#define            u8IceOperation_H                           U16IceOperationW.byte[1]
#define            Bit0_Ice_Setting                           U16IceOperationW.Bit.b0
#define            Bit1_Ice_Low_Water                         U16IceOperationW.Bit.b1
#define            Bit2_Ice_Temp_Protect                      U16IceOperationW.Bit.b2
#define            Bit3_Ice_Full                              U16IceOperationW.Bit.b3
#define            Bit4_Ice_Stop_Six_Hour                     U16IceOperationW.Bit.b4
#define            Bit5_Ice_Init_Ice_Stop                     U16IceOperationW.Bit.b5
#define            Bit6_Ice_Stop_Safty_Routine                U16IceOperationW.Bit.b6
#define            Bit7_Ice_Error                             U16IceOperationW.Bit.b7
#define            Bit8_Clean_Ice_Tank                        U16IceOperationW.Bit.b8
#define            Bit9_Cody_Service_Ice_Off                  U16IceOperationW.Bit.b9


TYPE_BYTE          U8ColdTempControlB;
#define            gu8_Cold_Temp_Control                     U8ColdTempControlB.byte
#define            Bit0_Temp_Control                         U8ColdTempControlB.Bit.b0
#define            Bit1_Temp_Add_Control                     U8ColdTempControlB.Bit.b1



TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                             U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                         U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                          U8MakeModeB.Bit.b1


U16 mu16_cold_on_temp;
U16 mu16_cold_off_temp;

bit F_Cold_Make_Mode;
bit F_Ice_Make_Mode;

bit F_cold_add_op;
U16 gu16_cold_add_op_timer;

U8 gu8_dual_temp_check_timer;
bit F_Dual_Mode_Disable;

/*..hui [20-1-29오후 1:42:16] 냉수 센서 ON/OFF 추가로 감지 타이머 추가.. 혹시몰라..*/
U8 gu8_cold_on_timer;
U16 gu16_cold_off_timer;
U8 gu8_cold_protect_timer;

bit bit_cold_first_op;

bit bit_ice_one_more;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Make_Mode_Decision(void)
{
    /*..hui [19-10-23오후 10:17:47] 처음 전원 ON시 만빙검사 완료 후 진입하기 위해..*/
    if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

    cold_mode_decision();
    ice_mode_decision();

    final_mode_decision();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_mode_decision(void)
{
    //F_Cold_Enable=0;


    Bit0_Cold_Setting = F_Cold_Enable;


    /*..hui [20-3-17오후 5:36:44] 냉수는 전원 ON 후 정수탱크 저수위 이상 채우고나서 가동 시작..*/
    /*..hui [20-3-17오후 5:36:55] 그 이후부터는 수위는 보지않고 그냥 주구장창 가동한다..*/
    /*..hui [20-3-17오후 5:37:05] 위원님 & 노차장님 의견..*/
    Bit1_Cold_Low_Water = bit_cold_first_op;

    #if 0
    if(gu8_Room_Water_Level != ROOM_LEVEL_LOW)
    {
        Bit1_Cold_Low_Water = SET;
    }
    else
    {
        Bit1_Cold_Low_Water = CLEAR;
    }
    #endif

    if(gu16_Cold_Temperature > PROTECT_COLD_TEMP)
    {
        Bit2_Cold_Temp_Protect = SET;
    }
    else
    {
        /*Bit2_Cold_Temp_Protect = CLEAR;*/
        /*..hui [20-1-29오후 2:02:15] cold_comp_test 함수에서 처리..*/
        Bit2_Cold_Temp_Protect = SET;
    }

    /*Bit3_Cold_Temp_Control = cold_mode_comp_control();*/

    Bit3_Cold_Temp_Control = cold_comp_test();


    Bit4_Ice_Init_Cold_Stop = ~F_IceInit;

    /*..hui [19-8-2오후 7:28:42] 냉수 관련 에러 발생 시 냉수측 냉각 정지..*/
    /*..hui [19-8-2오후 7:28:56] 냉수 에러 발생해도 제빙측은 정상 동작해야하기 때문에 이쪽으로 이동..*/
    Bit5_Cold_Error = ~Bit0_Cold_Operation_Disable_State;

    /*..hui [19-12-18오후 8:39:09] 냉수탱크 청소모드 진입시 냉각 정지..*/
    /*Bit6_Clean_Cold_Tank = ~F_ColdConty;*/
    /*..hui [20-3-20오후 3:46:03] 냉수탱크 청소모드에도 냉각은 계속 진행..*/
    /*..hui [20-3-20오후 3:46:16] 어차피 청소하기위해 코디 서비스모드 들어가면 냉각제빙 멈춤..*/
    Bit6_Clean_Cold_Tank = SET;

    /*..hui [20-1-20오후 10:26:55] 코디 서비스 모드 진행 중 냉각 정지..*/
    /*if( u8CodyInspectOperation == 0 )*/

    /*..hui [20-2-26오후 9:35:29] 트레이 테스트는 냉각 정상 진행, 코디서비스만 냉각 정지..*/
    #if 0
    if( Bit0_Cody_Service_Kit_Start == CLEAR )
    {
        Bit7_Cody_Service_Cold_Off = SET;
    }
    else
    {
        Bit7_Cody_Service_Cold_Off = CLEAR;
    }
    #endif

    Bit7_Cody_Service_Cold_Off = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_mode_decision(void)
{
    /*Bit0_Ice_Setting = F_IceOn;*/

    #if 0
    if( gu8_ice_setting == ICE_SETTING_OFF )
    {
        Bit0_Ice_Setting = CLEAR;
    }
    else
    {
        Bit0_Ice_Setting = SET;
    }
    #endif

    Bit0_Ice_Setting = F_IceOn;

    if(gu8_Room_Water_Level != ROOM_LEVEL_LOW)
    {
        Bit1_Ice_Low_Water = SET;
    }
    else
    {
        Bit1_Ice_Low_Water = CLEAR;
    }

    if(gu16_Cold_Temperature > PROTECT_COLD_TEMP)
    {
        Bit2_Ice_Temp_Protect = SET;
    }
    else
    {
        /*Bit2_Ice_Temp_Protect = CLEAR;*/
        /*..hui [19-11-7오후 3:36:57] 제빙은 삭제..*/
        Bit2_Ice_Temp_Protect = SET;
    }

    /*Bit3_Ice_Full = ~F_IceFull;*/

    if( F_IceFull == SET )
    {
        if( bit_ice_one_more == SET )
        {
            /*bit_ice_one_more = CLEAR;*/
            Bit3_Ice_Full = SET;

        #if 0
            if( gu8_Make_Mode == MAKE_ICE
                && gu8IceStep > STATE_0_STANDBY
                && gu8IceStep < STATE_31_MAIN_ICE_MAKING)
            {
                bit_ice_one_more = CLEAR;
            }
            else{}
        #endif
        }
        else
        {
            Bit3_Ice_Full = CLEAR;
        }
    }
    else
    {
        bit_ice_one_more = bit_first_ice_full;
        Bit3_Ice_Full = SET;
    }

    /*Bit4_Ice_Stop_Six_Hour = ~F_IceStop;*/
    /*..sean [25-01-02] 미사용절전모드는 제빙하고는 상관없음..*/
    /*..sean [25-01-02] 취침모드는 만빙까지 채우지않고 진입 즉시 하던거까지만 하고 제빙 멈춤.. 최인식..*/
    Bit4_Ice_Stop_Six_Hour = ~bit_sleep_mode_start;

    Bit5_Ice_Init_Ice_Stop = ~F_IceInit;

    /*..hui [19-12-18오후 1:49:10] 트레이 이동에러 재시도 진입중에는 제빙 정지 후 냉각 전환..*/
    Bit6_Ice_Stop_Safty_Routine = ~F_Safety_Routine;

    /*..hui [19-12-18오후 8:03:47] 제빙 불가 에러..*/
    Bit7_Ice_Error = ~Bit2_Ice_Operation_Disable_State;

    /*..hui [19-12-18오후 8:39:09] 냉수탱크 청소모드 진입시 냉각 정지..*/
    /*Bit8_Clean_Ice_Tank = ~F_ColdConty;*/
    /*..hui [20-3-20오후 3:46:03] 냉수탱크 청소모드에도 제빙은 계속 진행..*/
    /*..hui [20-3-20오후 3:46:16] 어차피 청소하기위해 코디 서비스모드 들어가면 냉각제빙 멈춤..*/
    Bit8_Clean_Ice_Tank = SET;

    /*..hui [20-1-20오후 10:26:55] 코디 서비스 모드 진행 중 제빙 정지..*/
    if( u8CodyInspectOperation == 0 )
    {
        Bit9_Cody_Service_Ice_Off = SET;
    }
    else
    {
        Bit9_Cody_Service_Ice_Off = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 cold_mode_comp_control(void)
{

/*..hui [20-1-29오후 2:00:42] 냉각 지연시간 있는 버전.. 혹시 나중에 변경될수있으니 남겨두는걸로..*/
#if 0
    U16 mu16_cold_on_temp = 0;
    U16 mu16_cold_off_temp = 0;

    if(F_Sleep == SET)
    {
        mu16_cold_on_temp = COLD_ON_TEMP_SAVING;
    }
    else
    {
        mu16_cold_on_temp = COLD_ON_TEMP_NORMAL;
    }
    //gu16_Amb_Temperature=333;

    /*..hui [19-7-25오후 8:45:00] 30도 이상이었다가 30분 추가 냉각중 30도 미만으로 다시 내려오면..??????..*/
    if(gu16_Amb_Temperature < COLD_OFF_REF_TEMP_AMB)
    {
        mu16_cold_off_temp = COLD_OFF_TEMP_4_DEGREE;
    }
    else
    {
        mu16_cold_off_temp = COLD_OFF_TEMP_5_DEGREE;
    }

    if(gu16_Cold_Temperature >= mu16_cold_on_temp)
    {
        Bit0_Temp_Control = SET;

        /*..hui [19-7-25오후 5:37:11] 30분 추가 기동 중 다시 가동조건 됐을때 초기화..*/
        Bit1_Temp_Add_Control = CLEAR;
        F_cold_add_op = CLEAR;
        gu16_cold_add_op_timer = 0;
    }
    else
    {
        if(Bit0_Temp_Control == SET)
        {
            if(gu16_Cold_Temperature <= mu16_cold_off_temp)
            {
                if(mu16_cold_off_temp == COLD_OFF_TEMP_5_DEGREE)
                {
                    Bit0_Temp_Control = CLEAR;
                    Bit1_Temp_Add_Control = SET;
                    gu16_cold_add_op_timer = 0;
                }
                else
                {
                    Bit0_Temp_Control = CLEAR;
                }
            }
            else{}
        }
        else{}
    }


    if(Bit1_Temp_Add_Control == SET)
    {
        /*..hui [19-7-26오후 7:32:20] 분할냉각..*/
        if(gu8_GasSwitch_Status == GAS_SWITCH_COLD)
        {
            gu16_cold_add_op_timer++;
        }
        else{}

        /*..hui [19-7-25오후 5:33:28] 30분 추가 기동 후 종료..*/
        if(gu16_cold_add_op_timer >= COLD_ADD_OPERATION_TIME)
        {
            Bit1_Temp_Add_Control = CLEAR;
        }
        else
        {
            Bit1_Temp_Add_Control = SET;
        }
    }
    else
    {
        Bit1_Temp_Add_Control = CLEAR;
        gu16_cold_add_op_timer = 0;
    }

    /*..hui [19-7-25오후 5:40:39] 2도 이하 프로텍트 OFF 위치이동..*/
    if(gu16_Cold_Temperature <= PROTECT_COLD_TEMP)
    {
        gu8_Cold_Temp_Control = 0;
    }
    else{}

    if(gu8_Cold_Temp_Control > 0)
    {
        return SET;
    }
    else
    {
        return CLEAR;
    }
#endif

    return CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 cold_comp_test(void)
{
    //U16 mu16_cold_on_temp = 0;
    //U16 mu16_cold_off_temp = 0;
    U16 mu16_cold_delay_time = 0;

    /*..hui [23-8-17오후 4:55:42] 미사용 절전 모드가 최우선..*/
    if( bit_9_hour_no_use_start == SET )
    {
        /*..hui [23-8-17오후 5:25:08] 미사용 절전모드 == 냉수 강일때는 10도, 약일때는 14도 == 절전모드랑 동일..*/
        if( gu8_cold_setting_level == COLD_TEMP_HIGH )
        {
            mu16_cold_on_temp = 100;
        }
        else
        {
            mu16_cold_on_temp = 140;
        }
    }
    //else if(F_Sleep == SET)
    /*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
    else if(bit_sleep_mode_start == SET)
    {
        /*..hui [23-8-17오전 10:49:23] 절전모드 == 냉수 강일때는 10도, 약일때는 14도..*/
        if( gu8_cold_setting_level == COLD_TEMP_HIGH )
        {
            mu16_cold_on_temp = 100;
        }
        else
        {
            mu16_cold_on_temp = 140;
        }
    }
    else if( gu8_cold_setting_level == COLD_TEMP_LOW )
    {
        /*..hui [23-2-22오전 10:37:17] 냉수 <약> 설정시 14도..*/
        mu16_cold_on_temp = 140;
    }
    else
    {
    	/*.. sean [24-11-21] 냉수 성능 불충족으로 제어 사양 변경 ..*/
        //mu16_cold_on_temp = 85;
        mu16_cold_on_temp = 80;
    }

    /*..hui [20-11-30오후 12:54:49] 냉수 <약> 설정일때 OFF 온도 7도로 변경..*/
    /*..hui [20-11-30오후 12:55:11] 필드에서 <약> 설정했는데 물이 넘 차갑다는 클레임..*/
    /*..hui [20-11-30오후 12:55:52] 온도 표시도 강이 6도 이하에 표시하기 때문에 <약> 설정시 냉수온도 강을 표시할 가능성 낮아짐..*/
    if( gu8_cold_setting_level == COLD_TEMP_LOW )
    {
        mu16_cold_off_temp = 100;
        mu16_cold_delay_time = 20;
    }
    else
    {
        if( gu8_Amb_Temperature_One_Degree < 30 )
        {
            /*..hui [23-3-8오전 10:21:22] 30도 미만, 6도..*/
    		/*.. sean [24-11-21] 냉수 성능 불충족으로 제어 사양 변경 ..*/
            //mu16_cold_off_temp = 60;
			if( (bit_sleep_mode_start == SET) || (bit_9_hour_no_use_start == SET) )
			{
	            mu16_cold_off_temp = 60;
	            mu16_cold_delay_time = 20;
			}
			else
			{
	            mu16_cold_off_temp = 50;
	            mu16_cold_delay_time = 20;
			}
        }
        else
        {
            /*..hui [23-3-8오전 10:21:13] 30도 이상, 7도 / 15분..*/
            //mu16_cold_off_temp = 70;
            //mu16_cold_delay_time = 9000;
            /*..sean [25-02-10] 절전모드일 때, 30도 이상, 6도 / 10분..*/
			if( (bit_sleep_mode_start == SET) || (bit_9_hour_no_use_start == SET) )
			{
	            mu16_cold_off_temp = 70;
	            mu16_cold_delay_time = 9000;
			}
			else
			{		
	            /*..sean [25-02-10] 30도 이상, 6도 / 10분..*/
	            mu16_cold_off_temp = 60;
	            mu16_cold_delay_time = 6000;
			}
        }
    }



    if(gu16_Cold_Temperature >= mu16_cold_on_temp)
    {
        gu8_cold_on_timer++;

        if( gu8_cold_on_timer >= 20 )
        {
            gu8_cold_on_timer = 20;
            Bit0_Temp_Control = SET;
        }
        else{}

        gu16_cold_off_timer = 0;
    }
    else
    {
        gu8_cold_on_timer = 0;

        if(Bit0_Temp_Control == SET)
        {
            if(gu16_Cold_Temperature <= mu16_cold_off_temp)
            {
                gu16_cold_off_timer++;

                if( gu16_cold_off_timer >= mu16_cold_delay_time )
                {
                    gu16_cold_off_timer = 0;
                    Bit0_Temp_Control = CLEAR;
                }
                else{}
            }
            else
            {
                gu16_cold_off_timer = 0;
            }
        }
        else
        {
            gu16_cold_off_timer = 0;
        }
    }

    /*..hui [19-7-25오후 5:40:39] 2도 이하 프로텍트 OFF 위치이동..*/
    if(gu16_Cold_Temperature <= PROTECT_COLD_TEMP)
    {
        gu8_cold_protect_timer++;

        if( gu8_cold_protect_timer >= 20 )
        {
            gu8_cold_protect_timer = 20;
            gu8_Cold_Temp_Control = 0;
        }
        else{}
    }
    else
    {
        gu8_cold_protect_timer = 0;
    }

    if(gu8_Cold_Temp_Control > 0)
    {
        return SET;
    }
    else
    {
        return CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void final_mode_decision(void)
{
    /*if( gu8_ice_setting == ICE_SETTING_COLD_FIRST )*/
    if(bit_fast_ice_make == COLD_FIRST_ICE_MAKE)
    {
        cold_priority_decision();
    }
    else
    {
        ice_priority_decision();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            if(u16ColdOperation == COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_COLD;
            }
            else
            {
                if(u16IceOperation == ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_ICE;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            /*..hui [19-7-25오후 4:21:53] 냉각 중 냉각 조건 종료 시 제빙/냉각 조건 재 확인..*/
            if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-7-25오후 4:22:10] 제빙 중 제빙 완료 시 제빙/냉각 조건 재 확인..*/
            /*if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)*/
            if(gu8IceStep == STATE_0_STANDBY)
            {
                /*..hui [20-1-21오전 11:15:35] 제빙 모드 중 대기 상태에서 냉각 조건 발생 시..*/
                if(u16ColdOperation == COLD_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else if(u16IceOperation != ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else{}
            }
            else{}

        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            /*..hui [19-7-26오후 8:09:21] 제빙 우선이므로 만빙될때까지 제빙 먼저..*/
            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_ICE;
            }
            else
            {
                /*..hui [19-7-26오후 8:09:34] 제빙 조건 아닐때만 냉각 동작..*/
                if(u16ColdOperation == COLD_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_COLD;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                /*..hui [19-11-6오후 1:57:36] 냉각 중 제빙 조건 발생 시..*/
                gu8_Make_Mode = MAKE_STOP;
            }
            else if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                /*..hui [19-11-6오후 1:57:57] 냉각 중 냉각 조건 해제 시..*/
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-11-6오후 1:59:36] 제빙 중 제빙 완료 시 제빙/냉각 조건 재 확인..*/
            /*if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)*/
            if(gu8IceStep == STATE_0_STANDBY)
            {
                /*..hui [19-12-18오후 4:06:39] 얼음 모드중 대기 상태에서 얼음 모드 해지조건 발생 시..*/
                if(u16IceOperation != ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
                else{}
            }
            else{}


        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void final_mode_decision(void)
{
    if(F_Fast_Ice_Make == CLEAR)
    {
        cold_priority_decision();
    }
    else
    {
        ice_priority_decision();
    }

    ///////////////////////////////////////////////////////////////////////////
    /*..hui [19-7-26오후 8:28:42] 주위온도가 20도 미만으로 10초 이상 감지 시 듀얼 제빙 금지..*/
    check_dual_mode();
    ////////////////////////////////////////////////////////////////////////////
}



void cold_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            if(u16ColdOperation == COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_COLD;
            }
            else
            {
                if(u16IceOperation == ICE_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_ICE;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            /*..hui [19-7-25오후 4:21:53] 냉각 중 냉각 조건 종료 시 제빙/냉각 조건 재 확인..*/
            if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-7-25오후 4:22:10] 제빙 중 제빙 완료 시 제빙/냉각 조건 재 확인..*/
            if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)
            {
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_DUAL:

            if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                Bit0_Cold_Make_Go = CLEAR;
            }
            else{}

            if(gu8IceStep == STATE_31_MAIN_ICE_MAKING)
            {
                /*..hui [19-11-6오후 3:28:28] 듀얼 냉각 제빙 중 제빙우선 기능 끈 경우 냉수 냉각 종료..*/
                Bit0_Cold_Make_Go = CLEAR;
            }
            else{}

            if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)
            {
                /*..hui [19-11-6오후 3:34:37] 제빙 끝날때까지 기다렸다 제빙은 무조건 종료..*/
                Bit1_Ice_Make_Go = CLEAR;
            }
            else{}

        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}






void ice_priority_decision(void)
{
    switch(gu8_Make_Mode)
    {
        case MAKE_STOP:

            /*..hui [19-7-26오후 8:09:21] 제빙 우선이므로 만빙될때까지 제빙 먼저..*/
            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                gu8_Make_Mode = MAKE_ICE;
            }
            else
            {
                /*..hui [19-7-26오후 8:09:34] 제빙 조건 아닐때만 냉각 동작..*/
                if(u16ColdOperation == COLD_MAKE_GOGOGO)
                {
                    gu8_Make_Mode = MAKE_COLD;
                }
                else
                {
                    gu8_Make_Mode = MAKE_STOP;
                }
            }

        break;

        case MAKE_COLD:

            if(u16IceOperation == ICE_MAKE_GOGOGO)
            {
                /*..hui [19-11-6오후 1:57:36] 냉각 중 제빙 조건 발생 시..*/
                gu8_Make_Mode = MAKE_ICE;
            }
            else if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                /*..hui [19-11-6오후 1:57:57] 냉각 중 냉각 조건 해제 시..*/
                gu8_Make_Mode = MAKE_STOP;
            }
            else{}

        break;

        case MAKE_ICE:

            /*..hui [19-11-6오후 1:59:36] 제빙 중 제빙 완료 시 제빙/냉각 조건 재 확인..*/
            if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)
            {
                gu8_Make_Mode = MAKE_STOP;
            }
            else
            {
                /*..hui [19-7-26오후 7:56:52] 제빙도 하고 냉각도 하고,, 단 냉매밸브는 냉각으로..*/
                /*..hui [19-7-26오후 8:30:12] 외기온도 20도 미만일경우 그냥 제빙만 계속 진행..*/
                /*..hui [19-7-26오후 8:30:24] 복잡하다.. 디버깅 많이많이..*/
                if(gu8IceStep != STATE_31_MAIN_ICE_MAKING)
                {
                    if( F_Dual_Mode_Disable == CLEAR )
                    {
                        if(u16ColdOperation == COLD_MAKE_GOGOGO)
                        {
                            Bit0_Cold_Make_Go = SET;
                        }
                        else{}
                    }
                    else{}
                }
                else{}
            }

        break;

        case MAKE_DUAL:

            /*..hui [19-11-6오후 2:17:50] 냉매 전환밸브는 이미 얼음쪽으로 돌아가있는 상태..*/
            if(u16ColdOperation != COLD_MAKE_GOGOGO)
            {
                Bit0_Cold_Make_Go = CLEAR;
            }
            else{}

            if(gu8IceStep == STATE_31_MAIN_ICE_MAKING)
            {
                /*..hui [19-11-6오후 2:20:03] 듀얼 냉각 중 제빙 시작 시 냉수 냉각 종료..*/
                Bit0_Cold_Make_Go = CLEAR;
            }
            else{}

            if(gu8IceStep == STATE_51_FINISH_ICE_MAKE)
            {
                if(u16IceOperation != ICE_MAKE_GOGOGO)
                {
                    /*..hui [19-11-6오후 2:51:38] 듀얼 제빙 중 제빙 완료하고 만빙 검사 완료하고 제빙조건 재 검색..*/
                    Bit1_Ice_Make_Go = CLEAR;
                }
                else{}
            }
            else{}

        break;

        default:

            gu8_Make_Mode = MAKE_STOP;

        break;
    }
}



void check_dual_mode(void)
{
    /*..hui [19-7-26오후 8:28:42] 주위온도가 20도 미만으로 10초 이상 감지 시 듀얼 제빙 금지..*/
    if(gu16_Amb_Temperature < DUAL_OP_TEMP_AMB_20_DEGREE)
    {
        gu8_dual_temp_check_timer++;

        /*..hui [19-7-26오후 8:26:23] 20도 미만으로 10초 이상 감지시..*/
        if(gu8_dual_temp_check_timer >= 100)
        {
            gu8_dual_temp_check_timer = 100;
            F_Dual_Mode_Disable = SET;
        }
        else{}
    }
    else
    {
        /*..hui [19-7-26오후 8:29:03] 20도 이상일 경우 즉시 해제 및 듀얼 제빙 가능..*/
        gu8_dual_temp_check_timer = 0;
        F_Dual_Mode_Disable = CLEAR;
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




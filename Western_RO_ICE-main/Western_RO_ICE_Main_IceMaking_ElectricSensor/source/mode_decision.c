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
//void check_dual_mode(void);
void count_ice_make(void);




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
#define            Bit10_Fast_Ice_Make_Limit                  U16IceOperationW.Bit.b10


TYPE_BYTE          U8ColdTempControlB;
#define            gu8_Cold_Temp_Control                     U8ColdTempControlB.byte
#define            Bit0_Temp_Control                         U8ColdTempControlB.Bit.b0
#define            Bit1_Temp_Add_Control                     U8ColdTempControlB.Bit.b1



TYPE_BYTE          U8MakeModeB;
#define            gu8_Make_Mode                             U8MakeModeB.byte
#define            Bit0_Cold_Make_Go                         U8MakeModeB.Bit.b0
#define            Bit1_Ice_Make_Go                          U8MakeModeB.Bit.b1





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


bit bit_drain_full_ice_stop;
U16 gu16_drain_full_timer;


U16 gu16_fast_ice_make_timer;
U8 gu8_fast_ice_make_count;
bit bit_count_ice_make;
U16 gu16_fast_ice_cold_max_timer;

U16 gu16_test_cold_on_temp;
U16 gu16_test_cold_off_temp;

bit bit_set_temp_change;
U8 gu8_recover_org_fast_ice;



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


    /*..hui [23-9-4오후 4:17:26] 트레이 에러 걸렸을때 냉각은 정상 동작하기위해..*/
    /*..hui [23-9-4오후 4:17:42] 트레이 에러 걸렸을때 F_IceInit이 SET된 상태로 끝날수잇음..*/
    if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
        || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
        || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
    {
        Bit4_Ice_Init_Cold_Stop = SET;
    }
    else
    {
        Bit4_Ice_Init_Cold_Stop = ~F_IceInit;
    }

    /*..hui [19-8-2오후 7:28:42] 냉수 관련 에러 발생 시 냉수측 냉각 정지..*/
    /*..hui [19-8-2오후 7:28:56] 냉수 에러 발생해도 제빙측은 정상 동작해야하기 때문에 이쪽으로 이동..*/
    Bit5_Cold_Error = ~Bit0_Cold_Operation_Disable_State;

    /*..hui [19-12-18오후 8:39:09] 냉수탱크 청소모드 진입시 냉각 정지..*/
    /*Bit6_Clean_Cold_Tank = ~F_ColdConty;*/
    /*..hui [20-3-20오후 3:46:03] 냉수탱크 청소모드에도 냉각은 계속 진행..*/
    /*..hui [20-3-20오후 3:46:16] 어차피 청소하기위해 코디 서비스모드 들어가면 냉각제빙 멈춤..*/
    /*..hui [23-9-4오후 2:07:02] 탈빙방향 트레이 불량일때 냉각도 정지.. 해빙동작할때 핫가스 탈빙해야하기때문..*/
    /*..hui [23-9-4오후 2:09:34] 에러 걸렸을때는 냉각 정상 가동..*/
    #if 0
    if( Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
    {
        Bit6_Clean_Cold_Tank = SET;
    }
    else
    {
        if( F_Safety_Routine == SET && F_Ice_Tray_Down_Move_Reset == SET )
        {
            Bit6_Clean_Cold_Tank = CLEAR;
        }
        else
        {
            Bit6_Clean_Cold_Tank = SET;
        }
    }
    #endif

    #if 0
    /*..hui [23-10-17오전 9:47:48] 세척시 냉수끈다..*/
    if( bit_ice_tank_ster_start == SET )
    {
        Bit6_Clean_Cold_Tank = CLEAR;
    }
    else
    {
        Bit6_Clean_Cold_Tank = SET;
    }
    #endif



    if( bit_ice_tank_ster_start == SET )
    {
        /*if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE
           || gu8_ice_ster_mode == STER_MODE_MELT_ICE
           || gu8_ice_ster_mode == STER_MODE_FINISH )*/
        /*..hui [24-1-25오전 9:18:56] 아이스트레이 세척 준비, 세척중에도 냉각은 동작..*/
        if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE
           || gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN
           || gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE
           || gu8_ice_ster_mode == STER_MODE_MELT_ICE
           || gu8_ice_ster_mode == STER_MODE_FINISH )
        {
            /*..hui [23-10-23오후 1:44:46] 얼음세척할때도 해빙 준비작업 이후로는 냉각 가동..*/
            /*..hui [23-10-23오후 1:45:10] 18도 OFF, 22도 ON 조건으로 냉각 진행..*/
            Bit6_Clean_Cold_Tank = SET;
        }
        else
        {
            Bit6_Clean_Cold_Tank = CLEAR;
        }
    }
    else
    {
        Bit6_Clean_Cold_Tank = SET;
    }


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

    /*..hui [24-7-29오후 2:57:56] 구연산 세척 중 냉각 정지..*/
    if( bit_self_test_start == CLEAR && bit_acid_clean_start == CLEAR )
    {
        Bit7_Cody_Service_Cold_Off = SET;
    }
    else
    {
        Bit7_Cody_Service_Cold_Off = CLEAR;
    }

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

    /*if( gu8_Room_Water_Level != ROOM_LEVEL_LOW )*/
    if( gu8_Room_Water_Level != ROOM_LEVEL_LOW )
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
        Bit3_Ice_Full = CLEAR;
    }
    else
    {
        Bit3_Ice_Full = SET;
    }

    /*Bit4_Ice_Stop_Six_Hour = ~F_IceStop;*/
    /*..hui [23-6-29오후 5:20:21] 미사용절전모드는 제빙하고는 상관없음..*/
    /*..hui [23-6-29오후 5:20:47] 취침모드는 만빙까지 채우지않고 진입 즉시 하던거까지만 하고 제빙 멈춤.. 최인식..*/
    Bit4_Ice_Stop_Six_Hour = ~bit_sleep_mode_start;

    Bit5_Ice_Init_Ice_Stop = ~F_IceInit;

    /*..hui [19-12-18오후 1:49:10] 트레이 이동에러 재시도 진입중에는 제빙 정지 후 냉각 전환..*/
    Bit6_Ice_Stop_Safty_Routine = ~F_Safety_Routine;

    /*..hui [19-12-18오후 8:03:47] 제빙 불가 에러..*/
    Bit7_Ice_Error = ~Bit2_Ice_Operation_Disable_State;

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-4-2오후 7:42:15] 드레인 탱크 만수위 상태가 5분 이상 지속시 제빙 진입 금지..*/
    /*..hui [24-4-2오후 7:42:31] 배수 막혀서 얼음 탱크 물 넘칠수있음..*/
    if( u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
    {
        gu16_drain_full_timer++;

        /*..hui [24-4-5오후 4:09:04] 5분 -> 10분으로 변경..*/
        if( gu16_drain_full_timer >= DRAIN_FULL_ICE_STOP_TIME )
        {
            gu16_drain_full_timer = DRAIN_FULL_ICE_STOP_TIME;
            bit_drain_full_ice_stop = SET;
        }
        else
        {
            bit_drain_full_ice_stop = CLEAR;
        }
    }
    else
    {
        gu16_drain_full_timer = 0;
        bit_drain_full_ice_stop = CLEAR;
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-18오후 8:39:09] 냉수탱크 청소모드 진입시 냉각 정지..*/
    /*Bit8_Clean_Ice_Tank = ~F_ColdConty;*/
    /*..hui [20-3-20오후 3:46:03] 냉수탱크 청소모드에도 제빙은 계속 진행..*/
    /*..hui [20-3-20오후 3:46:16] 어차피 청소하기위해 코디 서비스모드 들어가면 냉각제빙 멈춤..*/

    /*..hui [23-6-29오후 6:41:03] 얼음탱크 살균중에 제빙 정지..*/
    /*..hui [23-7-7오후 4:29:03] 정기 살균 1시간 전부터 제빙 정지..*/
    /*..hui [23-7-28오후 4:00:26] 플러싱 대기 화면에서도 제빙 안하도록 수정..*/
    /*if( bit_ice_tank_ster_start == SET || bit_extract_stop_before_ster_start == SET
        || gu8_Led_Display_Step == LED_Display__FLUSHING || gu8_Led_Display_Step == LED_Display__STEAM_CLEAN )*/
    /*..hui [23-8-25오전 10:08:19] 세척 1시간 전에 얼음 안만드는건 삭제.. 제품 사용에 영향이 생겨선안됨.. 이정환 부장님..*/
    /*..hui [24-4-2오후 7:42:15] 드레인 탱크 만수위 상태가 5분 이상 지속시 제빙 진입 금지..*/
    /*..hui [24-7-29오후 2:49:43] 구연산 세정 중 제빙 정지..*/
    if( bit_ice_tank_ster_start == SET
        || gu8_Led_Display_Step == LED_Display__FLUSHING
        || gu8_Led_Display_Step == LED_Display__STEAM_CLEAN
        || bit_drain_full_ice_stop == SET
        || bit_acid_clean_start == SET )
    {
        Bit8_Clean_Ice_Tank = CLEAR;
    }
    else
    {
        Bit8_Clean_Ice_Tank = SET;
    }

    /*..hui [20-1-20오후 10:26:55] 코디 서비스 모드 진행 중 제빙 정지..*/
    /*..hui [23-12-20오후 5:14:23] 고장진단중일때는 정지..*/
    if( u8CodyInspectOperation == 0 && bit_self_test_start == CLEAR )
    {
        Bit9_Cody_Service_Ice_Off = SET;
    }
    else
    {
        Bit9_Cody_Service_Ice_Off = CLEAR;
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [24-4-11오후 7:08:35] 혹시몰라.. 이전 모드 변경 특수모드 추가..*/
    if( gu8_recover_org_fast_ice == NEW_FAST_ICE )
    {
        /*..hui [24-4-11오후 3:53:13] 얼음우선일때.. 제빙 횟수 체크..*/
        count_ice_make();

        if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
        {
            if( F_IceOn == CLEAR )
            {
                /*..hui [24-4-11오후 3:57:33] 얼음 OFF -> ON 시 횟수 초기화..*/
                gu8_fast_ice_make_count = 0;
            }
            else{}

            if( bit_ice_tank_ster_start == SET )
            {
                /*..hui [24-4-12오후 12:12:59] 얼음 세척시 횟수 초기화..*/
                gu8_fast_ice_make_count = 0;
            }
            else{}

            if( bit_sleep_mode_start == SET )
            {
                /*..hui [24-4-12오후 12:14:40] 취침모드 진입시 횟수 초기화..*/
                gu8_fast_ice_make_count = 0;
            }
            else{}

            /*..hui [24-4-11오후 3:11:27] 얼음우선 / 제빙 4회 하고 나서..*/
            if( gu8_fast_ice_make_count >= FAST_ICE_MAKE_COUNT )
            {
                /*..hui [24-4-11오후 3:11:34] 냉각 가동 조건이면 냉각으로 이동..*/
                if( u16ColdOperation == COLD_MAKE_GOGOGO )
                {
                    Bit10_Fast_Ice_Make_Limit = CLEAR;

                    /*..hui [24-4-11오후 4:04:28] 냉각 모드로 가동중인 조건에서 확인..*/
                    if( Bit0_Cold_Mode_On_State == SET && F_Comp_Output == SET )
                    {
                        gu16_fast_ice_cold_max_timer++;

                        /*..hui [24-4-11오후 4:02:20] 냉각 가동시간 최대 1시간 경과시 다시 제빙해야함..*/
                        if( gu16_fast_ice_cold_max_timer >= FAST_ICE_COLD_MAX_OP_TIME )
                        {
                            gu16_fast_ice_cold_max_timer = 0;
                            gu8_fast_ice_make_count = 0;
                        }
                        else{}
                    }
                    else{}


                    /*..hui [24-4-12오전 11:43:09] 실제 냉각 제어하는곳에서 초기화해야함.. 이미 초기화되서 이쪽으로 안들어옴..*/
                    #if 0
                    /*..hui [24-4-11오후 7:49:32] 냉각 OFF 온도 도달시(7.5도 도달시) 4회 카운트 초기화..*/
                    /*..hui [24-4-11오후 7:49:41] 다시 얼음 무조건 4번 만든다..*/
                    /*..hui [24-4-12오전 11:25:31] 이쪽으로 와야함.. 4회 제빙하고.. 냉각 진행하고 냉각 완료되면 초기화..*/
                    if( Bit3_Cold_Temp_Control == CLEAR )
                    {
                        gu8_fast_ice_make_count = 0;
                    }
                    else{}
                    #endif
                }
                else
                {
                    Bit10_Fast_Ice_Make_Limit = SET;
                    gu16_fast_ice_cold_max_timer = 0;
                    /*..hui [24-4-11오후 3:15:38] 냉각 미가동 조건일경우 카운트 초기화하고 다시 4회 제빙..*/
                    /*..hui [24-4-11오후 7:39:40] 여기서는 초기화하면안됨..*/
                    /*..hui [24-4-11오후 7:39:53] 4번이후 한번 제빙하고 계속 냉각조건 확인해야하기 때문..*/
                    /*gu8_fast_ice_make_count = 0;*/
                }
            }
            else
            {
                Bit10_Fast_Ice_Make_Limit = SET;
                gu16_fast_ice_cold_max_timer = 0;
            }
        }
        else
        {
            Bit10_Fast_Ice_Make_Limit = SET;
            gu16_fast_ice_cold_max_timer = 0;
            /*..hui [24-4-11오후 3:15:38] 냉각 미가동 조건일경우 카운트 초기화하고 다시 4회 제빙..*/
            gu8_fast_ice_make_count = 0;
        }
    }
    else
    {
        bit_count_ice_make = CLEAR;

        Bit10_Fast_Ice_Make_Limit = SET;
        gu16_fast_ice_cold_max_timer = 0;
        /*..hui [24-4-11오후 3:15:38] 냉각 미가동 조건일경우 카운트 초기화하고 다시 4회 제빙..*/
        gu8_fast_ice_make_count = 0;
    }
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void count_ice_make(void)
{
    if( bit_fast_ice_make == ICE_FIRST_ICE_MAKE )
    {
        if( gu8IceStep == STATE_43_ICE_TAKE_OFF )
        {
            if( bit_count_ice_make == CLEAR )
            {
                bit_count_ice_make = SET;

                gu8_fast_ice_make_count++;

                if( gu8_fast_ice_make_count >= FAST_ICE_MAKE_COUNT )
                {
                    gu8_fast_ice_make_count = FAST_ICE_MAKE_COUNT;
                }
                else{}
            }
            else{}
        }
        else
        {
            bit_count_ice_make = CLEAR;
        }

    }
    else
    {
        bit_count_ice_make = CLEAR;
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
    //gu16_Amb_Front_Temperature=333;

    /*..hui [19-7-25오후 8:45:00] 30도 이상이었다가 30분 추가 냉각중 30도 미만으로 다시 내려오면..??????..*/
    if(gu16_Amb_Front_Temperature < COLD_OFF_REF_TEMP_AMB)
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
    U16 mu16_cold_on_temp = 0;
    U16 mu16_cold_off_temp = 0;
    U16 mu16_cold_delay_time = 0;

    #if 0
    mu16_cold_on_temp = 75;
    mu16_cold_off_temp = 58;
    mu16_cold_delay_time = 20;
    #endif

    /*if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET
        || Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )*/
    /*..hui [23-9-20오전 9:23:37] 둘 다 고장일 경우..*/

    if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-10-23오후 1:48:18] 얼음세척할때 제어온도.. 각 단계별로 할지말지는 mode decision에서 결정..*/
        /*..hui [24-1-29오전 11:53:13] 얼음 세척할때는 10도, 6도로 통일..*/
        mu16_cold_on_temp = 100;
        mu16_cold_off_temp = 60;
        mu16_cold_delay_time = 20;

        bit_set_temp_change = CLEAR;
    }
    else if( ( gu8_recover_org_fast_ice == NEW_FAST_ICE
               && bit_fast_ice_make == ICE_FIRST_ICE_MAKE
               && u16IceOperation == FAST_ICE_MAKE_ENABLE )
             || ( gu8_recover_org_fast_ice == NEW_FAST_ICE
               && bit_fast_ice_make == ICE_FIRST_ICE_MAKE
               && u16IceOperation == ICE_MAKE_GOGOGO ) )
    {
        /*..hui [24-4-11오후 2:37:22] 얼음 우선 설정돼있을때.. 냉각 온도 15도, 7.5도..*/
        mu16_cold_on_temp = 150;
        mu16_cold_off_temp = 75;
        mu16_cold_delay_time = 20;

        /*..hui [24-4-11오후 5:08:34] 얼음우선 제빙 조건 아닌 경우 -> 제빙 조건으로 변경될때..*/
        /*..hui [24-4-11오후 5:08:39] 냉각 가동 조건 다시 확인하기 위해..*/
        /*..hui [24-4-11오후 5:09:15] 더미탈빙 -> 냉각 가동조건 8도 -> 냉각 가동조건 set -> 더미탈빙 종료..*/
        /*..hui [24-4-11오후 5:09:39] 제빙 -> 4회 진행 -> 가동조건 set돼있기 때문에 냉각 가동으로 넘어감..*/
        /*..hui [24-4-11오후 5:10:00] 제빙 가동 조건되면 냉각 조건은 다시 15도로 확인하도록..*/
        if( bit_set_temp_change == CLEAR )
        {
            bit_set_temp_change = SET;
            Bit0_Temp_Control = CLEAR;
        }
        else{}
    }
    else if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET
            && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        /*..hui [23-7-10오후 1:24:43] 외기센서 에러일때는 미사용절전/취침모드 전부 동일하게.. 청래..*/
        mu16_cold_on_temp = 80;
        mu16_cold_off_temp = 60;
        mu16_cold_delay_time = 20;

        bit_set_temp_change = CLEAR;
    }
    else
    {
        bit_set_temp_change = CLEAR;

        if( gu8_Amb_Temperature_One_Degree <= 10 )
        {
            if( bit_9_hour_no_use_start == SET || bit_sleep_mode_start  == SET )
            {
                /*..hui [23-4-7오전 11:15:58] 10도 이하..*/
                /*mu16_cold_on_temp = 100;*/
                /*..hui [23-8-23오후 2:21:58] 미사용절전 첫잔 높아서 1도 내림.. 청래..*/
                mu16_cold_on_temp = 90;
                mu16_cold_off_temp = 60;
                mu16_cold_delay_time = 20;
            }
            else
            {
                /*..hui [23-4-7오전 11:15:58] 10도 이하..*/
                mu16_cold_on_temp = 80;
                mu16_cold_off_temp = 60;
                mu16_cold_delay_time = 20;
            }
        }
        else if( gu8_Amb_Temperature_One_Degree <= 20 )
        {
            if( bit_9_hour_no_use_start == SET || bit_sleep_mode_start  == SET )
            {
                /*..hui [23-4-7오전 11:16:02] 20도 이하..*/
                /*mu16_cold_on_temp = 100;*/
                mu16_cold_on_temp = 90;
                mu16_cold_off_temp = 60;
                mu16_cold_delay_time = 20;
            }
            else
            {
                /*..hui [23-4-7오전 11:16:02] 20도 이하..*/
                mu16_cold_on_temp = 80;
                mu16_cold_off_temp = 60;
                mu16_cold_delay_time = 20;
            }
        }
        else if( gu8_Amb_Temperature_One_Degree <= 30 )
        {
            if( bit_9_hour_no_use_start == SET || bit_sleep_mode_start  == SET )
            {
                /*..hui [23-4-7오전 11:16:10] 30도 이하..*/
                /*mu16_cold_on_temp = 100;*/
                mu16_cold_on_temp = 90;
                mu16_cold_off_temp = 60;
                /*mu16_cold_delay_time = 3000;*/
                mu16_cold_delay_time = 6000;
            }
            else
            {
                /*..hui [23-4-7오전 11:16:10] 30도 이하..*/
                mu16_cold_on_temp = 80;
                mu16_cold_off_temp = 60;
                /*mu16_cold_delay_time = 3000;*/
                mu16_cold_delay_time = 6000;
            }
        }
        else
        {
            if( bit_9_hour_no_use_start == SET || bit_sleep_mode_start  == SET )
            {
                /*..hui [23-4-7오전 11:16:14] 30도 초과..*/
                /*mu16_cold_on_temp = 100;*/
                mu16_cold_on_temp = 90;
                mu16_cold_off_temp = 60;
                /*mu16_cold_delay_time = 6000;*/
                mu16_cold_delay_time = 12000;
            }
            else
            {
                /*..hui [23-4-7오전 11:16:14] 30도 초과..*/
                mu16_cold_on_temp = 80;
                mu16_cold_off_temp = 60;
                /*mu16_cold_delay_time = 6000;*/
                mu16_cold_delay_time = 12000;
            }
        }
    }

    /*..hui [24-4-11오후 4:22:44] 디버깅.. 확인용..*/
    gu16_test_cold_on_temp = mu16_cold_on_temp;
    gu16_test_cold_off_temp = mu16_cold_off_temp;

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

                    /*..hui [24-4-12오전 11:43:45] 냉각 완료시 제빙 횟수 초기화 이쪽에서..*/
                    gu8_fast_ice_make_count = 0;
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
    if(gu16_Amb_Front_Temperature < DUAL_OP_TEMP_AMB_20_DEGREE)
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




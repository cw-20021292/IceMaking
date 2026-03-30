/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M7_Error_Control.h"


void Error_Control(void);
void error_check(void);
void search_error_code(void);
void error_management(void);



TYPE_BYTE       U8OperationB;
#define         u8Operation                             U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State       U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State        U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State        U8OperationB.Bit.b2






TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Hot_Tank_Temp_Open_Short_Error      U32ControlErrorsD.Bit.b0    //E45
#define         Bit1_Room_OverHeat_Error                 U32ControlErrorsD.Bit.b1    //E49
#define         Bit2_Room_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Room_Low_Water_Level_Error          U32ControlErrorsD.Bit.b4    //E11
#define         Bit5_Hot_Heater_OverHeat_Error           U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Hot_Water_Flow_Block_Error          U32ControlErrorsD.Bit.b6    //E34
#define         Bit7_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b7    //E13
#define         Bit8_Feed_Valve_Error                    U32ControlErrorsD.Bit.b8    //E10
#define         Bit9_Room_Level_Unbalance_Error          U32ControlErrorsD.Bit.b9    //E14
#define         Bit10_Cold_Temp_Open_Short_Error         U32ControlErrorsD.Bit.b10   //E44
#define         Bit11_Amb_Temp_Open_Short_Error          U32ControlErrorsD.Bit.b11   //E43
#define         Bit12_Drain_Pump_Error                   U32ControlErrorsD.Bit.b12   //E60
#define         Bit13_Tray_Micro_SW_Dual_Detect_Error    U32ControlErrorsD.Bit.b13   //E61
#define         Bit14_Tray_Micro_SW_Up_Move_Error        U32ControlErrorsD.Bit.b14   //E62
#define         Bit15_Tray_Micro_SW_Down_Move_Error      U32ControlErrorsD.Bit.b15   //E63
#define         Bit16_Eva_First_Temp_Open_Short_Error    U32ControlErrorsD.Bit.b16   //E63 - noerr
#define         Bit17_Eva_Second_Temp_Open_Short_Error   U32ControlErrorsD.Bit.b17   //E64 - noerr


/*..hui [19-11-28오전 10:53:48] E10 피드밸브 에러..*/


/*const U8 gu8_error_code[16] = {47, 48, 44, 42, 43, 63, 64, 1, 11, 60, 61, 62, 40, 34, 13, 65};*/

/*..hui [19-12-11오후 8:45:58] 온수히터온도센서 임시로.. 입수로..*/
/*const U8 gu8_error_code[18] = {47, 46, 44, 42, 43, 63, 64, 1, 11, 60, 61, 62, 40, 34, 13, 65, 10, 14};*/



/*..hui [20-1-3오전 9:25:01] 에러 표시 우선순위 순서 변경..*/
/*const U8 gu8_error_code[18] = {47, 48, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 65, 63, 63};*/
/*const U8 gu8_error_code[18] = {45, 48, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 65, 63, 63};*/
/*const U8 gu8_error_code[18] = {45, 48, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 63, 63, 63};*/
const U8 gu8_error_code[18] = {45, 49, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 63, 63, 63};




bit F_ErrAll;                     // 전체에러
//bit F_HardError;                  // 중 에러
bit F_SoftError;                  // 경 에러
bit F_ErrOVHRoom;                  // 정수과온 에러
//bit F_ErrPurify;                  // 재정수시간 초과
//bit F_ErrColdLEVSet;              // 냉수수위센서 에러셋
bit F_ErrEEPROM;                  // EEPROM 에러
bit F_ErrIceVV;                   // 냉수공급밸브 에러
bit F_ErrIceTraySet;              // 아이스트레이 에러 감지
bit F_ErrIceTrayChk;              // 아이스트레이 연속감지
//bit F_ErrDrainSet;
//bit F_ErrOVIce;
bit F_ErrHotGas;
bit F_ErrSter;

bit F_ErrIceTray;                 // 얼음받이 감지 에러
//bit F_ErrOVCold;                  // 과냉 에러
//bit F_ErrOVF;                     // 물넘침 에러

//----------------------------------
//bit F_ErrOVFeed;                  // 물넘침 피드VV 에러
//bit F_ErrOVRoomLEV;               // 물넘침 만수위센서 에러
//bit F_ErrOVLEV;                                     // 물넘침 수위센서 에러
//bit F_ErrRoomLowLEV;              // 정수 수위센서 에러
//bit F_ErrColdLEV;                 // 냉수 수위센서 에러
//----------------------------------
//bit Bit10_Cold_Temp_Open_Short_Error;                  // 냉수 TH 에러
bit F_ErrHotTH;                   // 온수 TH 에러
//bit F_ErrRoomTH;                  // 정수 TH 에러
bit F_ErrEvaTH;                   // 증발기 TH 에러
//bit F_ErrAmbTH;                   // 주위온도 TH 에러
//bit F_ErrOVHot;                   // 과온 에러
//bit F_ErrTrayMotor_Dual;          // 얼음받이 모터  M/S Error
//bit F_ErrTrayMotor_Move;          // 얼음받이 모터 이동 에러
//bit F_ErrDrain;                   // 드레인펌프,수위센서 에러
//bit F_ErrDrainSetFix;



U8 gu8ErrorCode;
U8 gu8ErrorStep;

//-----------------------------------------------------// ERROR
U8 gu8ErrCds;
U8 gu8ErrEEP;
U8 gu8ErrIceMotor;
U8 gu8ErrIceMotorClear;
U8 gu8ErrRTHDelay;
U8 gu8ErrCTHDelay;
U8 gu8ErrHTHDelay;
U8 gu8ErrETHDelay;
U8 gu8ErrATHDelay;
U8 gu8IceDrainError_CNT;
U8 gu8ErrOVCDelay;
U8 gu8ErrOVHDelay;
U16 gu16ErrOVHRoomTime;
U8 gu8ErrI2C;
U8 gu8ErrKey;
U8 gu8ErrIceTray;
//U8 gu8ErrBar;
U8 gu8ErrDoor;
U16 gu16ErrIceOut;
U8 gu8ErrDoorClear;
U8 gu8ErrColdBarCnt;
U8 gu8ErrIceBarCnt;
U16 gu16ErrOVIce;
U16 gu16ErrColdLEVDelay;
U8 gu8ErrHotgas;
U8 gu8ErrHotgasSum;

U8 gu8LeakageCheckCount;
U8 gu8LeakageCheckCount2;
// 20140117 살균 시 냉수 입수 밸브 삭제 및 트레이 입수 이용
// 20170706 일반배수에러 개선 - 10분 에러 만수 미 해제 시 1분 정지/2분 가동 10회 추가(만수해제 & 저전류 감지 정상)
bit F_COLD_VV_In;
bit F_Drain_Retray;


U8 gu8DrainErrorRetrayDelay;                  // 얼음 잔수 배수
U16 gu16IceWaterExtMax;

U16 gu16IceWaterExt;

U8 gu8_Cold_level_err_1s_cnt;


U32 gu32_error_state;
U32 gu32_error_state_old;

U8 gu8_Error_Code;
U8 gu8_Err_Code_Old;



U8 u8_re_ice_init_error;

U8 gu8_hot_water_error_code_old;

U8 gu8_hot_water_error_code;
U8 gu8_hot_water_error_year;
U8 gu8_hot_water_error_month;
U8 gu8_hot_water_error_date;



U8 gu8_now_error_occur_year;
U8 gu8_now_error_occur_month;
U8 gu8_now_error_occur_day;

U8 gu8_error_popup_enable;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Error_Control(void)
{
    error_check();

    search_error_code();

    error_management();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_check(void)
{
    /*..hui [17-12-26오전 9:51:20] 버전 표시 완료 후 시작..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}
	
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /*..hui [19-6-26오전 11:19:16] 온도센서 오픈/쇼트 에러..*/
    check_error_temp_sensor();

    /*..hui [19-6-26오전 11:36:25] 누수 관련 에러..*/
    check_flow_error();

    /*..hui [19-6-26오전 11:41:48] 수위 관련 에러..*/
    check_error_water_level();

    /*..hui [19-7-26오후 2:50:02] 온수 관련 에러..*/
    hot_water_error_check();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void search_error_code(void)
{
    U8 mu8_error_count = 0;
    U8 mu8_detect_error = 0;
    /*U8 temp_error_code = 0;*/

    ////////////////////////////////////////////////////////////////////////////
    /*..hui [19-8-2오후 3:47:56] 에러 47 ; 온수 출수 온도센서..*/
    /*..hui [19-8-2오후 3:48:00] 에러 48 ; 온수 히터 온도센서..*/
    /*..hui [19-8-2오후 3:48:05] 에러 44 ; 냉수 온도센서..*/
    /*..hui [19-8-2오후 3:48:10] 에러 42 ; 정수 온도센서..*/
    /*..hui [19-8-2오후 3:48:16] 에러 43 ; 주위 온도센서..*/
    /*..hui [19-8-2오후 3:48:21] 에러 63 ; EVA1 온도센서..*/
    /*..hui [19-8-2오후 3:48:26] 에러 64 ; EVA2 온도센서..*/
    /*..hui [19-8-2오후 3:48:31] 에러 01 ; 누수 센서..*/
    /*..hui [19-8-2오후 3:48:38] 에러 11 ; 저수위..*/
    /*..hui [19-8-2오후 3:48:45] 에러 60 ; 드레인 펌프 에러..*/
    /*..hui [19-8-2오후 3:49:08] 에러 61 ; 마이크로 스위치 동시 감지 에러..*/
    /*..hui [19-8-2오후 3:50:18] 에러 62 ; 마이크로 스위치 이동 에러..*/
    /*..hui [19-8-2오후 3:50:23] 에러 40 ; 온수온도 과열..*/
    /*..hui [19-8-2오후 3:50:27] 에러 34 ; 온수 배수막힘 및 온수 단수..*/
    ////////////////////////////////////////////////////////////////////////////

    if(u32ControlErrors > 0)
    {
        for(mu8_error_count = 0; mu8_error_count < MAX_ERROR_NUM; mu8_error_count++)
        {
            mu8_detect_error = (U8)(((U32)(u32ControlErrors) >> mu8_error_count) & 0x01);

            if(mu8_detect_error == 0x01)
            {
                gu8_Error_Code = gu8_error_code[mu8_error_count];
                return;
            }
            else{}
        }
    }
    else
    {
        gu8_Error_Code = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_management(void)
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-8-2오후 6:51:28] 에러 발생 시 냉각 정지..*/
    /*..hui [19-8-2오후 6:51:32] 냉수 온도센서 에러..*/
    /*..hui [19-12-18오후 10:41:07] 피드밸브/수위 언발란스 에러 추가..*/
    if( Bit10_Cold_Temp_Open_Short_Error == SET
        || Bit3_Leakage_Sensor_Error == SET
        || Bit4_Room_Low_Water_Level_Error == SET
        || Bit7_Room_High_Water_Level_Error == SET
        || Bit8_Feed_Valve_Error == SET
        || Bit9_Room_Level_Unbalance_Error == SET )
    {
        Bit0_Cold_Operation_Disable_State = SET;
    }
    else
    {
        Bit0_Cold_Operation_Disable_State = CLEAR;
    }


    /*..hui [23-2-23오후 7:30:54] 탱크식 삭제..*/
    #if 0
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-8-2오후 6:54:12] 에러 발생 시 온수 정지..*/
    /*..hui [19-8-2오후 6:54:19] 온수 출수 온도센서 에러..*/
    /*..hui [19-8-2오후 6:54:25] 온수 히터 온도센서 에러..*/
    /*..hui [19-8-2오후 6:54:29] 정수 온도센서 에러..*/
    /*..hui [19-8-2오후 6:54:32] 누수센서 에러..*/
    /*..hui [19-8-2오후 6:54:38] 정수 수위센서 에러..*/
    /*..hui [19-8-2오후 6:54:42] 온수온도 과열..*/
    /*..hui [19-8-2오후 6:55:05] 온수 배수막힘 및 단수..*/
    /*..hui [19-8-27오후 7:48:12] 만수위센서 에러 추가..*/
    /*..hui [19-12-18오후 10:41:07] 피드밸브/수위 언발란스 에러 추가..*/
    /*..hui [20-4-16오후 2:15:20] 얼음 트레이 입수 에러 추가.. 유량센서랑 히터 사이 누수 발생시..*/
    if(   Bit0_Hot_Tank_Temp_Open_Short_Error == SET
       || Bit1_Room_OverHeat_Error == SET
       || Bit2_Room_Temp_Open_Short_Error == SET
       || Bit3_Leakage_Sensor_Error == SET
       || Bit4_Room_Low_Water_Level_Error == SET
       || Bit5_Hot_Heater_OverHeat_Error == SET
       || Bit6_Hot_Water_Flow_Block_Error == SET
       || Bit7_Room_High_Water_Level_Error == SET
       || Bit8_Feed_Valve_Error == SET
       || Bit9_Room_Level_Unbalance_Error == SET )
       /*|| Bit15_Tray_Micro_SW_Down_Move_Error == SET )*/
    {
        Bit1_Hot_Operation_Disable_State = SET;

        /*..hui [19-8-2오후 7:16:33] 온수 사용중이라면 즉시 추출 정지하고 이전 모드로 복귀..*/
        /*if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)*/
        /*..hui [20-3-12오후 1:47:43] 온수 선택 상태에서(미추출상태) 온수불가 에러 발생시 냉정으로 복귀..*/
        /*..hui [20-3-12오후 1:47:49] 추출때는 추출 멈추고 복귀..*/
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            gu16_water_select_return_time = 70;

            if( F_WaterOut == SET )
            {
                F_WaterOut = CLEAR;
                u8Extract_Continue = CLEAR;
            }
            else{}
        }
        else{}
    }
    else
    {
        Bit1_Hot_Operation_Disable_State = CLEAR;

        #if 0
        gu8_hot_water_error_code = 0;
        gu8_hot_water_error_code_old = 0xff;
        gu8_hot_water_error_year = 0;
        gu8_hot_water_error_month = 0;
        gu8_hot_water_error_date = 0;
        #endif
    }
    #endif

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [18-2-8오후 2:58:50] 에러 발생 시 제빙 정지..*/
    /*..hui [19-8-2오후 6:50:09] 정수 온도센서..*/
    /*..hui [19-8-2오후 6:50:23] 마이크로 스위치 동시 감지 에러..*/
    /*..hui [19-8-2오후 6:50:28] 마이크로 스위치 이동 에러..*/
    /*..hui [19-8-2오후 6:50:33] 드레인 펌프 에러..*/
    /*..hui [19-8-2오후 6:50:38] 정수 저수위 에러..*/
    /*..hui [19-8-2오후 6:50:49] 주위 온도센서 에러..*/
    /*..hui [19-8-2오후 6:50:52] 누수센서 에러..*/
    /*..hui [19-8-27오후 7:48:12] 만수위센서 에러 추가..*/
    /*..hui [19-8-28오후 2:26:50] 트레이 입수 에러 추가..*/
    /*..hui [19-12-18오후 10:41:07] 피드밸브/수위 언발란스 에러 추가..*/
    if(   Bit2_Room_Temp_Open_Short_Error == SET
       || Bit1_Room_OverHeat_Error == SET
       || Bit13_Tray_Micro_SW_Dual_Detect_Error == SET
       || Bit14_Tray_Micro_SW_Up_Move_Error == SET
       || Bit15_Tray_Micro_SW_Down_Move_Error == SET

       || Bit12_Drain_Pump_Error == SET
       || Bit4_Room_Low_Water_Level_Error == SET
       || Bit11_Amb_Temp_Open_Short_Error == SET
       || Bit3_Leakage_Sensor_Error == SET
       || Bit7_Room_High_Water_Level_Error == SET
       /*|| F_Tray_In_Error_Temporary == SET*/
       || Bit8_Feed_Valve_Error == SET
       || Bit9_Room_Level_Unbalance_Error == SET )
    {
        Bit2_Ice_Operation_Disable_State = SET;

        /*..hui [19-12-18오후 7:50:28] 에러 해제되고 더미탈빙 진행하는 에러들..*/
        /*..hui [19-12-18오후 10:41:07] 피드밸브/수위 언발란스 에러 추가..*/
        /*..hui [19-12-18오후 10:44:09] 피드밸브/수위 언발란스는 자동해제가 아니기때문에 의미없음..*/
        /*..hui [19-12-18오후 10:44:30] 만수위센서 에러도 마찬가지..*/
        /*..hui [19-12-19오후 1:00:22] 정수온도센서는 제빙 전에 에러감지하기 때문에 삭제..*/
        if(   Bit4_Room_Low_Water_Level_Error == SET
           || Bit2_Room_Temp_Open_Short_Error == SET
           || Bit11_Amb_Temp_Open_Short_Error == SET
           || Bit3_Leakage_Sensor_Error == SET
           || Bit1_Room_OverHeat_Error == SET )
        {
            if( gu8IceStep >= STATE_31_MAIN_ICE_MAKING
                && gu8IceStep <= STATE_41_ICE_TAKE_OFF )
            {
                /*..hui [19-12-18오후 10:43:42] 제빙중에 에러 걸렸을때만 해제됐을때 더미탈빙 진행..*/
                u8_re_ice_init_error = SET;
            }
            else{}
        }
        else{}

        /*..hui [20-2-13오후 5:42:54] 에러 발생 시 트레이 내림.. 트레이에 물 고여있는 상황 발생할 수 있음..*/
        /*..hui [20-2-14오전 11:20:25] 단, 트레이 관련 에러는 그냥 현위치대로 남겨둠.. 서비스 용이하도록..*/
        if( Bit13_Tray_Micro_SW_Dual_Detect_Error != SET
            && Bit14_Tray_Micro_SW_Up_Move_Error != SET
            && Bit15_Tray_Micro_SW_Down_Move_Error != SET )
        {
            if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP )
            {
                if( gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )
                {
                    down_tray_motor();
                }
                else{}
            }
            else{}
        }
        else{}
    }
    else
    {
        Bit2_Ice_Operation_Disable_State = CLEAR;

        if(u8_re_ice_init_error == SET)
        {
            u8_re_ice_init_error = CLEAR;
            F_IceInit = SET;
        }
        else{}
    }

    /*..hui [23-5-9오전 11:58:26] 정수 과열 시 추출중이면 추출 정지..*/
    if( Bit1_Room_OverHeat_Error == SET )
    {
        if( F_WaterOut == SET && u8WaterOutState == PURE_WATER_SELECT )
        {
            F_WaterOut = CLEAR;
            u8Extract_Continue = CLEAR;
            BuzStep(BUZZER_ERROR);
        }
        else{}
    }
    else{}

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( gu8_Error_Code != 0 )
    {
        /*..hui [18-1-10오후 9:05:35] 우선순위 관계없이 신규 에러 추가될떄마다 부저음 울리기 위해 변경..*/
        /*if(gu32_error_state != gu32_error_state_old)*/
        /*..hui [18-1-10오후 9:07:20] 에러 걸릴때만 부저음 울려야함.. 해제될때는 울리면안된다....*/
        /*if(u32ControlErrors > gu32_error_state_old)*/
        if(u32ControlErrors > gu32_error_state_old)
        {
            /*..hui [19-3-26오전 11:22:16] 에러 걸렸을때 부저음 출력은 안하는걸로..*/
            /*..hui [19-8-2오후 6:40:37] LCD 완성되기전에 에러 발생한지 확인하기위해.....*/
            /*BuzStep(BUZZER_ERROR);*/
            /*gu8_error_popup_enable = SET;*/
        }
        else{}

        if( gu8_Err_Code_Old != gu8_Error_Code )
        {
            #if 0
            /*..hui [20-1-20오후 8:15:50] 우선순위 높은 에러로 변경됐을때만 팝업 표시..*/
            /*..hui [20-1-20오후 8:20:52] 에러 걸린 상태에서 우선순위 낮은 에러 걸릴경우 추가 표시 안한다..*/
            gu8_error_popup_enable = SET;

            gu8_now_error_occur_year = gu8_rtc_time_Year;
            gu8_now_error_occur_month = gu8_rtc_time_Month;
            gu8_now_error_occur_day = gu8_rtc_time_Date;
            #endif

            gu8_error_popup_enable = SET;
        }
        else{}

        gu32_error_state_old = u32ControlErrors;
        gu8_Err_Code_Old = gu8_Error_Code;
    }
    else
    {
        gu32_error_state_old = 0;
        gu8_Err_Code_Old = 0;
        //gu8_error_popup_enable = CLEAR;
    }

    ErrorSaveStart( gu8_Error_Code );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



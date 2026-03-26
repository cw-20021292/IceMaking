/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Input.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M4_Input.h"


void Input(void);
//void input_select_bar(void);
//void input_cds(void);

//void input_overflow(void);
void check_ice_full(void);
//void power_saving_init(void);

//void LeverInput(void);

//bit F_Bar;
//bit F_BeBar;
//bit F_BarSet;
//bit F_SelectBar;
//U8 gu8Bar;


bit F_NoUseSave;
bit F_DayNoUseSave;
bit F_NightNoUseSave;             // 낮 해제를 위해

//----------------------------------------------------// IR
U8 gu8IRTime, gu8IRCount;
U16 gu16IRInterval;



bit F_IceFull;                        // 만빙
bit F_IR;                             // 만빙 검사



/*..hui [18-3-8오후 5:25:49] 처음 전원 ON시 만빙 체크..*/
bit bit_first_ice_full;

U8 gu8ContyCancel;
U8 gu8Out;
U16 gu16Conty;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Input(void)
{
    /*..hui [19-6-26오후 1:54:08] 수위센서 입력..*/
    input_water_level();

    /*..hui [19-6-26오후 1:12:26] 트레이 마이크로스위치 입력..*/
    input_ice_tray_micro_sw();

    /*..hui [19-6-26오후 1:54:12] 만빙 입력..*/
    check_ice_full();

    /*..hui [19-7-22오후 7:36:53] 유량센서..*/
    calculate_tray_flow_input();

    /*..hui [23-6-9오후 2:20:05] 필터 유량센서..*/
    calculate_filter_flow_input();

    /*..hui [19-7-25오후 8:25:00] 조도센서 다시 추가됨..*/
    /*..hui [23-2-28오후 3:34:11] 조도센서 없음..*/
    /*input_cds();*/

    /*detect_front_cds();*/

    /*..hui [19-10-23오후 7:56:31] 탱크 커버 리드스위치 ..*/
    service_reed_sw_input();

    /*..hui [20-2-19오후 5:57:55] UV 차단용 탱크 커버 리드스위치 따로 분리..*/
    /*..hui [20-2-19오후 5:58:13] 탱크 커버 열었을때 즉시 UV 차단하기 위해 분리함..*/
    uv_tank_reed_sw_input();

    /*..hui [21-8-25오후 5:29:54] 펄터 개별 리드스위치..*/
    input_filter_reed_sw();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_ice_full(void)
{
    if(gu8IRTime > 0)
    {
        gu8IRTime--;                             // 만빙검사 10초
    }
    else{}

    //==================================================================
    if(F_IR != SET && F_LineTest != SET)
    {
        return;
    }
    else{}
//
    if(pIR_POWER != SET)                                         // IR 출력 없을경우
    {
        pIR_POWER = SET;

        if(F_LineTest == SET)
        {
            gu8IRTime = 30;
        }
        else
        {
            gu8IRTime = 100;
        }
    }
    else{}

    if(gu16ADIceFull >= ICEFULL_LEV)
    {
        gu8IRCount++;
    }
    else{}

    if(gu8IRTime == 0)
    {
        if(F_LineTest == SET)
        {
            if(gu8IRCount >= 10)
            {
                F_IceFull = CLEAR;
            }
            else
            {
                F_IceFull = SET;
            }
        }
        else
        {
            if(gu8IRCount >= 50)
            {
                F_IceFull = CLEAR;
            }
            else
            {
                F_IceFull = SET;
            }
        }

        gu8IRCount = 0;
        pIR_POWER = CLEAR;
        F_IR = CLEAR;

        if(F_LineTest == SET)
        {
            gu16IRInterval = 0;
        }
        else
        {
            gu16IRInterval = IR_INTERVAL;
        }
    }

    /////////F_IceFull = CLEAR;
    //F_Cold_Enable = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



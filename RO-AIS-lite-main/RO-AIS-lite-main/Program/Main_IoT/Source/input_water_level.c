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
#include    "input_water_level.h"



void input_water_level(void);
void input_room_water_level(void);
void input_drain_tank_level(void);
void drain_tank_low_water_level_input(void);
void drain_tank_high_water_level_input(void);
void drain_tank_water_level_confirm(void);
void input_overflow(void);




//U16 gu16_ice_level_delay;
U16 gu16ColdVVOnTime;
// 20140318 제빙 중 만수해제 시점 1L(50초 누적) 추출 시 급수 시작 , 제빙 외 구간에서 즉시 공급
//U16 gu16IceVVTime1;

U16 gu16IceWaterExtDelay;



U8 gu8IceDrainLEV;
U8 gu8BeIceDrainLEV;
U8 gu8IceDrainSenLEV;
U8 gu8IceDrainLEVDelay;

//U8 gu8NFC_Feed_Check;

bit F_Low;                        // 최초저수위
bit F_Feed;                       // 피드밸브

//----------------------------------------------------// 물넘침센서
U8 gu8OVF;
bit F_OVF;
bit F_BeOVF;
bit F_OVFSet;
bit F_Overflow;


//----------------------------------------------------// 정수 수위센서
U8 gu8_Room_Water_Level;
U8 gu8BeRoomWaterLEV;
U8 gu8_room_level;
U8 gu8_be_room_level;
U8 gu8_room_level_delay;

//----------------------------------------------------// 냉수 수위센서
//U8 gu8ColdWaterLEV;
//U8 gu8BeColdWaterLEV;
//U8 gu8ColdLEV;
//U8 gu8BeColdLEV;
//U8 gu8ColdLEVDelay;

//----------------------------------------------------// 배수 수위센서
U8 gu8DrainWaterLEV;
U8 gu8BeDrainWaterLEV;
U8 gu8DrainLEV;
U8 gu8BeDrainLEV;
U8 gu8DrainLEVDelay;


U8 u8drain_low_level_on_decision_cnt;
U8 u8drain_low_level_off_decision_cnt;

U8 u8drain_high_level_on_decision_cnt;
U8 u8drain_high_level_off_decision_cnt;

bit F_drain_water_level_low;
bit F_drain_water_level_high;

bit F_room_water_level_low;
bit F_room_water_level_high;

TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_water_level(void)
{
    /*..hui [19-6-26오후 1:12:15] 정수탱크 수위센서 입력..*/
    input_room_water_level();

    /*..hui [17-12-15오후 10:09:46] 드레인 탱크 수위 감지..*/
    input_drain_tank_level();

    /*..hui [19-12-18오후 9:30:18] 물넘침 센서 추가..*/
    input_overflow();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : Room Water Level
// 개요         : 정수 수위센서
//----------------------------------------------------------------------------
// 기능       :  1.수위감지 3초간 지연
//               2.저수위시 재정수
//               3.만수위시 추출시간 리셋(120초)
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void input_room_water_level(void)
{
    if(gu8_room_level_delay > 0)
    {
        gu8_room_level_delay--;              // 정수레벨 감지 딜레이
    }
    else{}


    //============================================================Room Water Level
    // 20160819 정수,냉수 만수위 출력 변경
    /*..hui [17-12-8오전 11:07:39] 미감지,미감지..*/
    /*..hui [17-12-27오전 10:57:14] 정수 저수위 센서 active high로 변경..*/
    /*if(pLEVEL_PURIFY_HIGH != SET && pLEVEL_PURIFY_LOW == SET) */
    if(pLEVEL_PURIFY_HIGH != SET && pLEVEL_PURIFY_LOW != SET)
    {
        gu8_room_level = ROOM_LEVEL_LOW;            // Low
    }
    /*..hui [17-12-8오전 11:07:44] 미감지,감지..*/
    /*else if(pLEVEL_PURIFY_HIGH != SET && pLEVEL_PURIFY_LOW != SET) */
    else if(pLEVEL_PURIFY_HIGH != SET && pLEVEL_PURIFY_LOW == SET)
    {
        gu8_room_level = ROOM_LEVEL_MID;      // Mid
    }
    /*..hui [17-12-8오전 11:07:53] 감지,감지..*/
    /*else if(pLEVEL_PURIFY_HIGH == SET && pLEVEL_PURIFY_LOW != SET)*/
    else if(pLEVEL_PURIFY_HIGH == SET && pLEVEL_PURIFY_LOW == SET)
    {
        gu8_room_level = ROOM_LEVEL_FULL;     // Full
    }
    /*..hui [17-12-8오전 11:08:02] 감지,미감지..*/
    /*else if(pLEVEL_PURIFY_HIGH == SET && pLEVEL_PURIFY_LOW == SET) */
    else if(pLEVEL_PURIFY_HIGH == SET && pLEVEL_PURIFY_LOW != SET)
    {
        gu8_room_level = ROOM_LEVEL_ERROR;      // Water Level Error
    }
    else{}

    if(gu8_room_level != gu8_be_room_level)
    {
        gu8_be_room_level = gu8_room_level;
        gu8_room_level_delay = 30;           // 수위시간딜레이

        return;
    }
    else{}
#if 0
	if( F_room_water_level_high == SET )
	{
		F_room_water_level_high = CLEAR;
		send_wifi_system_function();
	}
	else{}
	
	if( F_room_water_level_low == SET )
	{
		F_room_water_level_low = CLEAR;
		send_wifi_system_function();
	}
	else{}
#endif
    if(gu8_room_level_delay > 0)
    {
        return;
    }
    else{}

    gu8_Room_Water_Level = gu8_room_level;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_drain_tank_level(void)
{
    /*..hui [17-12-15오후 10:08:42] 드레인탱크 저수위 입력..*/
    drain_tank_low_water_level_input();
    /*..hui [17-12-15오후 10:08:48] 드레인탱크 고수위 입력..*/
    drain_tank_high_water_level_input();
    /*..hui [17-12-15오후 10:08:55] 드레인탱크 최종 수위 결정..*/
    drain_tank_water_level_confirm();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_tank_low_water_level_input(void)
{
    if(pLEVEL_ICE_DRAIN_LOW == CLEAR)
    {
        u8drain_low_level_on_decision_cnt = 0;
        u8drain_low_level_off_decision_cnt++;

        #if 0
        if( u8drain_low_level_off_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
        {
            u8drain_low_level_off_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;
            F_drain_water_level_low = CLEAR;
        }
        else{}
        #endif

        if( u8drain_low_level_off_decision_cnt >= DRAIN_LOW_WATER_LEVEL_CLEAR_TIME )
        {
            u8drain_low_level_off_decision_cnt = DRAIN_LOW_WATER_LEVEL_CLEAR_TIME;
            F_drain_water_level_low = CLEAR;
        }
        else{}
    }
    else
    {
        if( pLEVEL_ICE_DRAIN_LOW == SET )
        {
            u8drain_low_level_off_decision_cnt = 0;
            u8drain_low_level_on_decision_cnt++;

            if ( u8drain_low_level_on_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
            {
                u8drain_low_level_on_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;
                F_drain_water_level_low = SET;
            }
            else{}
        }
        else{}
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_tank_high_water_level_input(void)
{

    if(pLEVEL_ICE_DRAIN_HIGH == CLEAR)
    {
        u8drain_high_level_on_decision_cnt = 0;
        u8drain_high_level_off_decision_cnt++;

        if( u8drain_high_level_off_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
        {
            u8drain_high_level_off_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;
            F_drain_water_level_high = CLEAR;
        }
        else{}
    }
    else
    {
        if( pLEVEL_ICE_DRAIN_HIGH == SET )
        {
            u8drain_high_level_off_decision_cnt = 0;
            u8drain_high_level_on_decision_cnt++;

            if ( u8drain_high_level_on_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
            {
                u8drain_high_level_on_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;
                F_drain_water_level_high = SET;
            }
            else{}
        }
        else{}

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_tank_water_level_confirm(void)
{
    U8 gu8water_levle_temp = 0;

    gu8water_levle_temp |= (U8)(F_drain_water_level_low);
    gu8water_levle_temp |= (U8)(F_drain_water_level_high << 1);


    switch(gu8water_levle_temp)
    {
        case 0 :

            u8DrainWaterLevel = DRAIN_LEVEL_EMPTY;

            break;


        case 1 :

            u8DrainWaterLevel = DRAIN_LEVEL_LOW;

            break;

        case 2 :

            u8DrainWaterLevel = DRAIN_LEVEL_ERROR;

            break;


        case 3 :

            u8DrainWaterLevel = DRAIN_LEVEL_HIGH;

            break;

        default :
             //
            break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_overflow(void)
{
    if( gu8OVF > 0 )
    {
        gu8OVF--;                            // Overflow 인식딜레이
    }
    else{}

    F_OVF = pLEVEL_OVERFLOW;

    if(F_BeOVF != F_OVF)
    {
        F_BeOVF = F_OVF;
        F_OVFSet = 1;
        gu8OVF = 10;                                   // 감지 1sec

        return;
    }
    else{}

    if(gu8OVF != 0)
    {
        return;
    }
    else{}

    if(F_OVFSet != SET)
    {
        return;
    }
    else{}

    F_OVFSet = 0;
    F_Overflow = F_OVF;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



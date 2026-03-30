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
#include    "error_water_level.h"


void check_error_water_level(void);
void check_error_room_low_level(void);
void check_error_room_high_level(void);
void check_error_over_flow(void);


U16 u16_water_in_check_timer_sec;
U16 u16_water_in_check_timer_min;

bit F_Err_OVF_Check;
U8 gu8ErrOVFeedCnt;
U8 gu8ErrOVRoomLEVCnt;
U8 gu8ErrOVLEVCnt;

U8 gu8OVFOnDelay;
U8 gu8OVFOffDelay;

bit bit_ovf_clear;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_water_level(void)
{
    check_error_room_low_level();

    /*..hui [19-8-27오후 7:41:18] 만수위센서 에러 추가..*/
    /*..hui [19-12-18오후 9:38:32] 물넘침 센서 추가로 삭제..*/
    /*check_error_room_high_level();*/

    /*..hui [19-12-18오후 10:13:29] 물넘침센서 관련 에러 추가..*/
    check_error_over_flow();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_low_level(void)
{
    /*..hui [19-6-26오후 12:59:28] 저수위 미감지 / 만수위 감지 시 에러 발생..*/
    if(gu8_Room_Water_Level == ROOM_LEVEL_ERROR)
    {
        Bit4_Room_Low_Water_Level_Error = SET;
    }
    else
    {
        Bit4_Room_Low_Water_Level_Error = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_over_flow(void)
{
    /*..hui [20-2-11오후 5:29:15] 버전 표시 완료후부터 동작하도록..*/
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        return;
    }
    else{}

    if(gu8OVFOffDelay > 0)
    {
        gu8OVFOffDelay--;            // 누수해제 대기시간
    }
    else{}

    if(gu8OVFOnDelay > 0)
    {
        gu8OVFOnDelay--;              // 누수감지 대기시간
    }
    else{}


#if 0
    if(F_Overflow != SET)                          // 물넘침 해제
    {
        gu8OVFOnDelay = OVF_DELAY;
    }
    else if(gu8InitStep == 3 || gu8IceStep == 3)  // 얼음물 급수 중 물넘침 지연
    {
        gu8OVFOnDelay = OVF_DELAY;
    }
    else                                          // 물넘침 감지
    {
        gu8OVFOffDelay = OVF_DELAY;
    }
#endif

    if(F_Overflow != SET)                          // 물넘침 해제
    {
        gu8OVFOnDelay = OVF_DELAY;
    }
    else                                          // 물넘침 감지
    {
        gu8OVFOffDelay = OVF_DELAY;
    }

    if(F_Overflow == SET && gu8OVFOnDelay == 0 && F_Err_OVF_Check != SET)
    {
        if(gu8_Room_Water_Level == ROOM_LEVEL_FULL)
        {
            /*..hui [20-2-11오후 5:36:41] 피드 밸브 에러..*/
            gu8ErrOVFeedCnt++;
        }
        else if(gu8_Room_Water_Level == ROOM_LEVEL_MID)
        {
            /*..hui [20-2-11오후 5:36:52] 만수위 센서 에러..*/
            gu8ErrOVRoomLEVCnt++;
        }
        else
        {
            /*..hui [20-2-11오후 5:37:02] 수위 센서 언발란스 에러..*/
            gu8ErrOVLEVCnt++;
        }

        F_Err_OVF_Check = SET;                 //오버플로우 셋
    }
    else if( F_Overflow != SET
             && gu8OVFOffDelay == 0
             && ( gu8_Room_Water_Level == ROOM_LEVEL_LOW
                  || gu8_Room_Water_Level == ROOM_LEVEL_MID ) )
    {
        F_Err_OVF_Check = CLEAR;
    }
    else{}

    if(gu8_Room_Water_Level == ROOM_LEVEL_FULL)
    {
        /*..hui [20-2-11오후 5:36:08] 만수위 센서 에러..*/
        gu8ErrOVRoomLEVCnt = 0;
        /*..hui [20-2-11오후 5:36:29] 수위 센서 언발란스 에러..*/
        gu8ErrOVLEVCnt = 0;
    }
    else{}

    if(gu8ErrOVFeedCnt >= 3)
    {
        /*..hui [19-12-18오후 10:25:10] 피드밸브 에러..*/
        Bit8_Feed_Valve_Error = SET;
    }
    else{}

    if(gu8ErrOVRoomLEVCnt >= 3)
    {
        /*..hui [19-12-18오후 10:25:15] 만수위 센서 에러..*/
        Bit7_Room_High_Water_Level_Error = SET;
    }
    else{}

    //if(gu8ErrOVLEVCnt>=3)
    if(gu8ErrOVLEVCnt >= 10)
    {
        /*..hui [19-12-18오후 10:25:21] 수위센서 언발란스 에러..*/
        Bit9_Room_Level_Unbalance_Error = SET;
    }
    else{}

    /*..hui [20-2-11오후 5:19:55] 탱크 커버 열림..*/
    /*..hui [20-2-11오후 5:22:27] 탱크 커버 열렸다 닫히면 수위 센서 관련 카운트 전부 초기화..*/
    if( F_Tank_Cover_Input == CLEAR )
    {
        bit_ovf_clear = SET;
    }
    else
    {
        if( bit_ovf_clear == SET )
        {
            bit_ovf_clear = CLEAR;
            gu8ErrOVFeedCnt = 0;
            gu8ErrOVRoomLEVCnt = 0;
            gu8ErrOVLEVCnt = 0;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_high_level(void)
{
    /*..hui [19-8-27오후 7:43:39] FEED 밸브 열린 상태에서 ..*/
    /*..hui [19-8-27오후 7:44:28] 약 30분?? 정도 지난후에도 정수탱크가 만수위까지 감지되지 않을경우..*/
    /*..hui [19-8-27오후 7:45:01] 당연히 NOS는 열려있는 상태..*/
    /*..hui [19-10-17오전 10:38:12] 물 추출하면 시간 초기화.. 에러 발생 최소화하기 위해~~..*/
    if(pVALVE_FEED == SET && pVALVE_NOS == CLEAR && F_WaterOut == CLEAR)
    {
        u16_water_in_check_timer_sec++;

        if(u16_water_in_check_timer_sec >= 600)
        {
            u16_water_in_check_timer_sec = 0;
            u16_water_in_check_timer_min++;
        }
        else{}

        if(u16_water_in_check_timer_min >= HIGH_LEVEL_ERR_CHECK_TIME)
        {
            u16_water_in_check_timer_min = HIGH_LEVEL_ERR_CHECK_TIME;
            Bit7_Room_High_Water_Level_Error = SET;
        }
        else{}
    }
    else
    {
        u16_water_in_check_timer_sec = 0;
        u16_water_in_check_timer_min = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




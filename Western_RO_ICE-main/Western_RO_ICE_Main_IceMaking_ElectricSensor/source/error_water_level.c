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
    /*..hui [23-2-28오후 3:39:51] 물넘침 센서 없음..*/
    /*check_error_over_flow();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_low_level(void)
{
    /*..hui [19-6-26오후 12:59:28] 저수위 미감지 / 만수위 감지 시 에러 발생..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_ERROR )
    {
        Bit4_Room_Low_Water_Level_Error__E21 = SET;
    }
    else
    {
        Bit4_Room_Low_Water_Level_Error__E21 = CLEAR;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




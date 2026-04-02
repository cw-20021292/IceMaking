
#include    "Packet_Match.h"

#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>

#include    "Global_Variable.h"
#if 0
/* @TODO : 유저용) 외부 전역변수 참조 및 헤더 참조 */

#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M8_Ice_Making.h"
#include    "M9_Front_Communication.h"

extern uint8_t get_cold_mode_comp_rps(void);
extern uint8_t get_ice_mode_comp_rps(void);
extern uint8_t gu8BLDCErrorNum;
extern bit F_Cold_Operation_Init;
extern uint16_t gu16_Ice_Tray_Fill_Hz;
extern uint8_t gu8_Cold_Temperature_One_Degree;
extern uint8_t gu8_Hot_Heater_Temperature_One_Degree;
extern uint8_t gu8_Hot_Out_Temperature_One_Degree;
extern bit bit_nos_output;
extern uint8_t u8RoomInValveON;
extern bit F_Drain_Pump_Output;
extern bit F_Tank_Cover_Input;
extern uint16_t gu16IceMakeTime;
extern uint16_t gu16CompOffDelay;
extern uint8_t gu8_bldc_target_hz;
extern uint16_t gu16_test_cold_on_temp;
extern uint16_t gu16_test_cold_off_temp;
extern uint16_t gu16_test_cold_delay_time;
extern uint8_t gu8_cristal_timer;
extern bit F_Safety_Routine;
extern uint8_t gu8IceLEV;
extern bit bit_cold_first_op;
extern bit F_IceInit;
extern bit bit_filter_reed;
extern bit bit_filter_cover;
extern uint8_t gu8_Amb_Front_Temperature_One_Degree;
extern uint8_t gu8_Room_Temperature_One_Degree;
extern uint8_t gu8_Amb_Temperature_One_Degree;
extern uint8_t gu8_GasSwitch_Status;
extern bit F_Comp_Output;
#endif

/* 프로토콜 데이터 구조체 */
/* F0Data : 공통 시스템 프로토콜 데이터 */
F0_COMMON_SYSTEM_DATA_FIELD F0Data = {0, };
/* F1Data : 냉각 시스템 프로토콜 데이터 */
F1_COLD_SYSTEM_DATA_FIELD F1Data = {0, };
/* F2Data : 히팅 시스템 프로토콜 데이터 */
F2_HEATING_SYSTEM_DATA_FIELD F2Data = {0, };
/* B1Data : 냉각 디버깅 데이터 */
B1_COLD_TABLE_DATA_FIELD B1Data = {0, };
/* B2Data : 제빙 디버깅 데이터 */
B2_ICE_MAKE_TABLE_DATA_FIELD B2Data = {0, };
/* B4Data : 보냉 디버깅 데이터 */
B4_ICE_STORAGE_TABLE_DATA_FIELD B4Data = {0, };
/* FreezingTable : 제빙 시간 테이블 */
Freezing_Table_T FreezingTable;

// @How to use : Parse_로 시작하는 함수에서 프로토콜 문서에 맞게 사용자의 프로젝트에서 사용중인 변수를 넣어야 함
/***************************************************************************************/
/**
* @brief 커맨드 F0의 프로토콜 데이터필드
* @details 커맨드 F0의 프로토콜 데이터필드를 사용자의 변수를 채우는 함수
*/
void Parse_F0_Protocol(void)
{
    /* 센서류 (DATAFIELD 1-13) */
    // Data 1 : 외기온도 1 (0.1℃ 단위)
    F0Data.u8AmbTemp1 = 0;
    // Data 2 : 입수온도 (0.1℃ 단위)
    F0Data.u8InletWaterTemp = 0;
    // Data 3 : 정수온도 (0.1℃ 단위)
    F0Data.u8PurifiedWaterTemp = 0;
    // Data 4 : 외기온도 2 (0.1℃ 단위)
    F0Data.u8AmbTemp2 = 0;
    // Data 5 : 냉수온도 (0.1℃ 단위)
    F0Data.u8ColdWaterTemp = 0;
    // Data 6 : 히터 내부온도 (0.1℃ 단위)
    F0Data.u8HeaterInternalTemp = 0;
    // Data 7 : 온수 출수온도 (0.1℃ 단위)
    F0Data.u8HotWaterOutletTemp = 0;

    /* 밸브 상태 (DATAFIELD 14-38) */
    // NOS 밸브: 1=CLOSE, 0=OPEN
    F0Data.u8ValveNOS1 = 0;
    F0Data.u8ValveNOS2 = 0;
    F0Data.u8ValveNOS3 = 0;
    F0Data.u8ValveNOS4 = 0;
    F0Data.u8ValveNOS5 = 0;

    // FEED 밸브: 1=OPEN, 0=CLOSE
    F0Data.u8ValveFEED1 = 0;
    F0Data.u8ValveFEED2 = 0;
    F0Data.u8ValveFEED3 = 0;
    F0Data.u8ValveFEED4 = 0;
    F0Data.u8ValveFEED5 = 0;
    F0Data.u8ValveFEED6 = 0;
    F0Data.u8ValveFEED7 = 0;
    F0Data.u8ValveFEED8 = 0;
    F0Data.u8ValveFEED9 = 0;
    F0Data.u8ValveFEED10 = 0;
    F0Data.u8ValveFEED11 = 0;
    F0Data.u8ValveFEED12 = 0;
    F0Data.u8ValveFEED13 = 0;
    F0Data.u8ValveFEED14 = 0;
    F0Data.u8ValveFEED15 = 0;

    // 리드스위치 (1 : 감지, 0 : 미감지)
    F0Data.u8FilterReed = 0;
    F0Data.u8FrontReed = 0;
}

/***************************************************************************************/
/**
* @brief 커맨드 F1의 프로토콜 데이터필드
* @details 커맨드 F1의 프로토콜 데이터필드를 사용자의 변수를 채우는 함수
*/
void Parse_F1_Protocol(void)
{
    /* 공조시스템 (DATAFIELD 1-13) */
    // Data 1 : 냉매전환밸브 1 현재위치 (0:핫가스, 1:냉각, 2:제빙, 3:보냉)
    F1Data.u8RefValve1Pos = 0;
    // Data 2 : 냉매전환밸브 2 현재위치 (병렬 구조)
    F1Data.u8RefValve2Pos = 0;
    // Data 3 : 압축기 출력상태 (1:가동, 0:정지)
    F1Data.u8CompOutputStatus = 0;
    // Data 4 : 압축기 안정시간 [HIGH] (초 단위)
    F1Data.u8CompStableTimeHigh = HIGH_BYTE(0);
    // Data 5 : 압축기 안정시간 [LOW] (초 단위)
    F1Data.u8CompStableTimeLow = LOW_BYTE(0);
    // Data 6 : 압축기 현재 RPS (37-75)
    F1Data.u8CompCurrentRPS = 0;
    // Data 7 : 압축기 에러코드 (E81~E88)
    F1Data.u8CompErrorCode = 0;
    // Data 8 : 압축기 팬 출력상태 (1:가동, 0:정지)
    F1Data.u8CompFanOutput = 0;
    // Data 9 : 얼음탱크 팬 출력상태 (1:가동, 0:정지)
    F1Data.u8IceTankFanOutput = 0;

    /* 냉각 데이터 (DATAFIELD 14-26) */
    // Data 1 : 운전상태 (1:운전, 0:정지)
    F1Data.u8CoolingOpStatus = 0;
    // Data 2 : 초기 기동여부 (1:초기기동, 0:일반기동)
    F1Data.u8CoolingInitStart = 0;
    // Data 3 : 냉각용 목표 RPS (37-75)
    F1Data.u8CoolingTargetRPS = (GetB1ColdTargetRPS() > 0) ? GetB1ColdTargetRPS() : 0;
    // Data 4 : ON 온도 (0.1℃ 단위)
    F1Data.u8CoolingOnTemp = (GetB1ColdOnTemp() > 0) ? GetB1ColdOnTemp() : 0;
    // Data 5 : OFF 온도 (0.1℃ 단위)
    F1Data.u8CoolingOffTemp = (GetB1ColdOffTemp() > 0) ? GetB1ColdOffTemp() : 0;
    // Data 6 : 추가 기동시간 [HIGH] (ms)
    F1Data.u8CoolingAddStartTime_H = (GetB1ColdDelayTime() > 0) ? HIGH_BYTE(GetB1ColdDelayTime()) : HIGH_BYTE(0);
    // Data 7 : 추가 기동시간 [LOW] (ms)
    F1Data.u8CoolingAddStartTime_L = (GetB1ColdDelayTime() > 0) ? LOW_BYTE(GetB1ColdDelayTime()) : LOW_BYTE(0);

    /* 제빙 데이터 (DATAFIELD 27-47) */
    // Data 1 : 제빙 STEP (255:더미탈빙, 1~:제빙STEP)
    F1Data.u8IceMakingStep = 255;
    
    // Data 2 : 제빙용 목표 RPS (37-75)
    F1Data.u8IceMakingTargetRPS = 0;
    // Data 3 : 제빙시간 [HIGH] (초 단위)
    F1Data.u8IceMakingTimeHigh = HIGH_BYTE(0);
    // Data 4 : 제빙시간 [LOW] (초 단위)
    F1Data.u8IceMakingTimeLow = LOW_BYTE(0);
    // Data 5 : 입수 용량 [HIGH] (Hz)
    F1Data.u8InletWaterCapHigh = (GetB2TrayIn_Hz() > 0) ? HIGH_BYTE(GetB2TrayIn_Hz()) : HIGH_BYTE(0);
    // Data 6 : 입수 용량 [LOW] (Hz)
    F1Data.u8InletWaterCapLow = (GetB2TrayIn_Hz() > 0) ? LOW_BYTE(GetB2TrayIn_Hz()) : LOW_BYTE(0);
    // Data 7 : 스윙바 ON 시간 (0.1초)
    F1Data.u8SwingBarOnTime = (GetB2SwingbarOn() > 0) ? GetB2SwingbarOn() : 0;
    // Data 8 : 스윙바 OFF 시간 (0.1초)
    F1Data.u8SwingBarOffTime = (GetB2SwingbarOff() > 0) ? GetB2SwingbarOff() : 0;                                     // CMD 47: 스윙바 OFF 시간
    F1Data.u8IceTrayPosition = 0;
    // Data 9 : 얼음걸림 상태 (0:없음, 1:걸림)
    F1Data.u8IceJamStatus = 0;

    /* 보냉 데이터 (DATAFIELD 48-62) */
    // Data 1 : 보냉 STEP (255:더미탈빙, 1~:보냉STEP)
    F1Data.u8KeepColdStep = (GetB4IceStorageTargetRPS() > 0) ? GetB4IceStorageTargetRPS() : 0;
    // Data 2 : 보냉용 목표 RPS (37-75)
    F1Data.u8KeepColdTargetRPS = (GetB4IceStorageTargetRPS() > 0) ? GetB4IceStorageTargetRPS() : 0;
    // Data 3 : 보냉 목표온도 (0.1℃ 단위)
    F1Data.u8KeepColdTargetTemp = (GetB4TargetTemp() > 0) ? GetB4TargetTemp() : 0;
    // Data 4 : 보냉 첫 목표온도 (0.1℃ 단위)
    F1Data.u8KeepColdFirstTargetTemp = (GetB4TargetTempFirst() > 0) ? GetB4TargetTempFirst() : 0;
    // Data 5 : 보냉 트레이 위치 (0:제빙, 1:중간, 2:탈빙)
    F1Data.u8KeepColdTrayPosition = (GetB4TrayPosition() > 0) ? GetB4TrayPosition() : 0;

    /* 드레인 탱크 (DATAFIELD 63-71) */
    // Data 1 : 드레인탱크 저수위 (1:감지, 0:미감지)
    F1Data.u8DrainTankLowLevel = 0;
    // Data 2 : 드레인탱크 만수위 (1:감지, 0:미감지)
    F1Data.u8DrainTankFullLevel = 0;
    // Data 3 : 수위 상태 (0:없음, 1:저수위, 2:중수위, 3:만수위, 4:에러)
    F1Data.u8DrainWaterLevelStatus = 0;
    // Data 4 : 드레인 펌프 출력상태 (1:가동, 0:정지)
    F1Data.u8DrainPumpOutput = 0;

    /* 기타 (DATAFIELD 72-74) */
    // Data 1 : 얼음탱크 커버 (1:열림, 0:닫힘)
    F1Data.u8IceTankCover = 0;
 }

void Parse_F2_Protocol(void)
{

}

/***************************************************************************************/
/**
* @brief 커맨드 B1 (냉각 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B1_Protocol(uint8_t *buf)
{
    memcpy((void*)&B1Data, (void*)&buf[4], sizeof(B1Data));
}

/***************************************************************************************/
/**
* @brief 커맨드 B2 (제빙 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B2_Protocol(uint8_t *buf)
{
    memcpy((void*)&B2Data, (void*)&buf[4], sizeof(B2Data));
}

/***************************************************************************************/
/**
* @brief 커맨드 B4 (보냉 디버깅 데이터)의 프로토콜 데이터필드
* @details PC → 제품 방향으로 고정값을 받아서 쓰는 함수
*/
void Parse_B4_Protocol(uint8_t *buf)
{
    memcpy((void*)&B4Data, (void*)&buf[4], sizeof(B4Data));
}


/* F0Data를 바이트 배열로 복사하는 함수 241212 */
void Get_F0_Data_Bytes(uint8_t *dest_buf, uint8_t length)
{
    uint8_t u8Index = 0;
    // uint8_t copy_length = (length < PROTOCOL_F0_LENGTH) ? length : PROTOCOL_F0_LENGTH;

    for(u8Index = 0; u8Index < length; u8Index++)
    {
        dest_buf[u8Index] = ((U8*)&F0Data)[u8Index];
    }
}

/* F1Data를 바이트 배열로 복사하는 함수 241212 */
void Get_F1_Data_Bytes(uint8_t *dest_buf, uint8_t length)
{
    uint8_t u8Index = 0;
    // uint8_t copy_length = (length < PROTOCOL_F1_LENGTH) ? length : PROTOCOL_F1_LENGTH;

    for(u8Index = 0; u8Index < length; u8Index++)
    {
        dest_buf[u8Index] = ((U8*)&F1Data)[u8Index];
    }
}

/***********************************************************************************************************************
* Function Name: FreezingTable_Init
* Description  : 제빙 시간 테이블 초기화
***********************************************************************************************************************/
void FreezingTable_Init(void)
{
    uint8_t i;
    SetUsedFreezingTable(CLEAR);

    for(i = 0; i < 46; i++)
    {
        FreezingTable.MakeTime[i] = 0;
    }
}

/***********************************************************************************************************************
* Function Name: SetFreezingTable
* Description  : 제빙 시간 테이블에 제빙 시간을 설정
* Input        : DataBuffer : 제빙 시간 데이터 버퍼 (92바이트: 46개의 uint16_t 값)
* Output       : 제빙 시간 데이터 버퍼
* Return       : 제빙 시간 데이터 버퍼
***********************************************************************************************************************/
void SetFreezingTable(uint8_t *DataBuffer)
{
    uint8_t i;
    uint8_t dataIndex = 0;

    // DATAFIELD의 데이터를 2BYTE씩 받아서 FreezingTable.MakeTime[0]~[45]에 저장
    // 상위1BYTE, 하위1BYTE를 조합하여 uint16_t 값 생성
    for(i = 0; i < 46; i++)
    {
        FreezingTable.MakeTime[i] = (U16)((U16)DataBuffer[dataIndex] << 8) | DataBuffer[dataIndex + 1];
        dataIndex += 2;
    }
}

/***********************************************************************************************************************
* Function Name: GetUsedFreezingTable
* Description  : 제빙 시간 테이블 사용 여부를 가져옴
***********************************************************************************************************************/
uint8_t GetUsedFreezingTable(void)
{
    return FreezingTable.Used;
}

/***********************************************************************************************************************
* Function Name: SetUsedFreezingTable
* Description  : 제빙 시간 테이블 사용 여부를 설정
* Input        : Used : 사용 여부
***********************************************************************************************************************/
void SetUsedFreezingTable(uint8_t Used)
{
    FreezingTable.Used = Used;
}

/*****************************************************************************
* Function Name: GetFreezingTime
* Description  : 제빙 시간 테이블에서 제빙 시간을 가져옴
* Input        : RoomInTemp : 입수온도
* Output       : 제빙 시간
* Return       : 제빙 시간
******************************************************************************/
uint16_t GetFreezingTime(uint8_t AmbTemp)
{
    return FreezingTable.MakeTime[AmbTemp];
}

uint8_t GetB1ColdTargetRPS(void)
{
    return B1Data.u8ColdTargetRPS;
}

void SetB1ColdTargetRPS(uint8_t *u8ColdTargetRPS)
{
    *u8ColdTargetRPS = B1Data.u8ColdTargetRPS;
}

uint8_t GetB1ColdOnTemp(void)
{
    return B1Data.u8ColdOnTemp;
}

void SetB1ColdOnTemp(uint8_t *u8ColdOnTemp)
{
    *u8ColdOnTemp = B1Data.u8ColdOnTemp;
}

uint8_t GetB1ColdOffTemp(void)
{
    return B1Data.u8ColdOffTemp;
}

void SetB1ColdOffTemp(uint8_t *u8ColdOffTemp)
{
    *u8ColdOffTemp = B1Data.u8ColdOffTemp;
}

uint16_t GetB1ColdDelayTime(void)
{
    return (U16)((U16)B1Data.ColdDelayTime_H << 8 | B1Data.ColdDelayTime_L);
}

void SetB1ColdDelayTime(uint16_t *u16ColdDelayTime)
{
    *u16ColdDelayTime = (U16)((U16)B1Data.ColdDelayTime_H << 8 | B1Data.ColdDelayTime_L);
}

void SetB2IceMakeTargetRPS(uint8_t *u8IceMakeTargetRPS)
{
    *u8IceMakeTargetRPS = B2Data.u8IceMakeTargetRPS;
}

uint8_t GetB2IceMakeTargetRPS(void)
{
    return B2Data.u8IceMakeTargetRPS;
}

void SetB2TrayIn_Hz(uint16_t *u16TrayIn_Hz)
{
    *u16TrayIn_Hz = (U16)((U16)B2Data.TrayInHz_H << 8 | B2Data.TrayInHz_L);
}

uint16_t GetB2TrayIn_Hz(void)
{
    return (U16)((U16)B2Data.TrayInHz_H << 8 | B2Data.TrayInHz_L);
}

void SetB2SwingbarOn(uint8_t *u8SwingbarOn)
{
    *u8SwingbarOn = B2Data.u8SwingbarOn;
}

uint8_t GetB2SwingbarOn(void)
{
    return B2Data.u8SwingbarOn;
}

void SetB2SwingbarOff(uint8_t *u8SwingbarOff)
{
    *u8SwingbarOff = B2Data.u8SwingbarOff;
}

uint8_t GetB2SwingbarOff(void)
{
    return B2Data.u8SwingbarOff;
}

void SetB4IceStorageTargetRPS(uint8_t *u8IceStorageTargetRPS)
{
    *u8IceStorageTargetRPS = B4Data.u8IceStorageTargetRPS;
}

uint8_t GetB4IceStorageTargetRPS(void)
{
    return B4Data.u8IceStorageTargetRPS;
}

void SetB4TargetTemp(uint8_t *u8TargetTemp)
{
    *u8TargetTemp = B4Data.u8TargetTemp;
}

uint8_t GetB4TargetTemp(void)
{
    return B4Data.u8TargetTemp;
}

void SetB4TargetTempFirst(uint8_t *u8TargetTempFirst)
{
    *u8TargetTempFirst = B4Data.u8TargetTempFirst;
}

uint8_t GetB4TargetTempFirst(void)
{
    return B4Data.u8TargetTempFirst;
}

void SetB4TrayPosition(uint8_t *u8TrayPosition)
{
    *u8TrayPosition = B4Data.u8TrayPosition;
}

uint8_t GetB4TrayPosition(void)
{
    return B4Data.u8TrayPosition;
}

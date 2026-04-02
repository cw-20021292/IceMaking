#ifndef __PACKET_MATCH_H__
#define __PACKET_MATCH_H__

#include "api_uart.h"

#define HIGH_BYTE(val)       (U8)(((val)&0xFF00) >> 8)
#define LOW_BYTE(val)        (U8)((val)&0x00FF)

/* 공통 시스템 프로토콜 (응답) */
typedef enum
{
    PROTOCOL_F0_CMD = 0xF0,
    PROTOCOL_F0_LENGTH = 40,
} PROTOCOL_F0_COMMON_SYSTEM;

/* 냉각 시스템 프로토콜 (응답) */
typedef enum
{
    PROTOCOL_F1_CMD = 0xF1,
    PROTOCOL_F1_LENGTH = 76,
} PROTOCOL_F1_COLD_SYSTEM;

/* 히팅 시스템 프로토콜 (응답) */
typedef enum
{
    PROTOCOL_F2_CMD = 0xF2,
    PROTOCOL_F2_LENGTH = 0,
} PROTOCOL_F2_HEATING_SYSTEM;

typedef enum
{
    PROTOCOL_B3_CMD = 0xB3,
    PROTOCOL_B3_LENGTH = 0,
} PROTOCOL_B3_FREEZING_TABLE;

typedef enum
{
    PROTOCOL_B1_CMD = 0xB1,
    PROTOCOL_B1_LENGTH = 5,
} PROTOCOL_B1_COLD_TABLE;

typedef enum
{
    PROTOCOL_B2_CMD = 0xB2,
    PROTOCOL_B2_LENGTH = 0,
} PROTOCOL_B2_ICE_MAKE_TABLE;

typedef enum
{
    PROTOCOL_B4_CMD = 0xB4,
    PROTOCOL_B4_LENGTH = 0,
} PROTOCOL_B4_ICE_STORAGE_TABLE;

/* 통신 데이터 F0 구조체 */
typedef struct
{
    /* 센서류 (CMD 1-13) */
    uint8_t u8AmbTemp1;              // CMD 1: 외기온도 1 (0.1℃ 단위)
    uint8_t u8InletWaterTemp;        // CMD 2: 입수온도 (0.1℃ 단위)
    uint8_t u8PurifiedWaterTemp;     // CMD 3: 정수온도 (0.1℃ 단위)
    uint8_t u8AmbTemp2;              // CMD 4: 외기온도 2 (0.1℃ 단위)
    uint8_t u8ColdWaterTemp;         // CMD 5: 냉수온도 (0.1℃ 단위)
    uint8_t u8HeaterInternalTemp;    // CMD 6: 히터 내부온도 (0.1℃ 단위)
    uint8_t u8HotWaterOutletTemp;    // CMD 7: 온수 출수온도 (0.1℃ 단위)
    uint8_t u8Reserved_8;             // CMD 8: Reserved
    uint8_t u8Reserved_9;             // CMD 9: Reserved
    uint8_t u8Reserved_10;            // CMD 10: Reserved
    uint8_t u8Reserved_11;            // CMD 11: Reserved
    uint8_t u8Reserved_12;            // CMD 12: Reserved
    uint8_t u8Reserved_13;            // CMD 13: Reserved

    /* 밸브 상태 (CMD 75-99) */
    uint8_t u8ValveNOS1;             // CMD 75: 밸브 NOS 1 상태 (1:CLOSE, 0:OPEN)
    uint8_t u8ValveNOS2;             // CMD 76: 밸브 NOS 2 상태 (1:CLOSE, 0:OPEN)
    uint8_t u8ValveNOS3;             // CMD 77: 밸브 NOS 3 상태 (1:CLOSE, 0:OPEN)
    uint8_t u8ValveNOS4;             // CMD 78: 밸브 NOS 4 상태 (1:CLOSE, 0:OPEN)
    uint8_t u8ValveNOS5;             // CMD 79: 밸브 NOS 5 상태 (1:CLOSE, 0:OPEN)
    uint8_t u8ValveFEED1;            // CMD 80: 밸브 FEED 1 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED2;            // CMD 81: 밸브 FEED 2 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED3;            // CMD 82: 밸브 FEED 3 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED4;            // CMD 83: 밸브 FEED 4 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED5;            // CMD 84: 밸브 FEED 5 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED6;            // CMD 85: 밸브 FEED 6 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED7;            // CMD 86: 밸브 FEED 7 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED8;            // CMD 87: 밸브 FEED 8 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED9;            // CMD 88: 밸브 FEED 9 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED10;           // CMD 89: 밸브 FEED 10 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED11;           // CMD 90: 밸브 FEED 11 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED12;           // CMD 91: 밸브 FEED 12 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED13;           // CMD 92: 밸브 FEED 13 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED14;           // CMD 93: 밸브 FEED 14 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8ValveFEED15;           // CMD 94: 밸브 FEED 15 상태 (1:OPEN, 0:CLOSE)
    uint8_t u8Reserved_95;           // CMD 95: Reserved
    uint8_t u8Reserved_96;           // CMD 96: Reserved
    uint8_t u8Reserved_97;           // CMD 97: Reserved
    uint8_t u8Reserved_98;           // CMD 98: Reserved
    uint8_t u8Reserved_99;           // CMD 99: Reserved

    uint8_t u8FilterReed;
    uint8_t u8FrontReed;
} F0_COMMON_SYSTEM_DATA_FIELD;

/* 통신 데이터 F1 구조체 */
typedef struct
{
    /* 공조시스템 (DATAFIELD 14-15) */
    uint8_t u8RefValve1Pos;          // CMD 14: 냉매전환밸브 1 현재위치 (0:핫가스, 1:냉각, 2:제빙, 3:보냉)
    uint8_t u8RefValve2Pos;          // CMD 15: 냉매전환밸브 2 현재위치 (병렬 구조)
    uint8_t u8CompOutputStatus;     // CMD 16: 압축기 출력상태 (1:가동, 0:정지)
    uint8_t u8CompStableTimeHigh;   // CMD 17: 압축기 안정시간 [HIGH] (초 단위)
    uint8_t u8CompStableTimeLow;    // CMD 18: 압축기 안정시간 [LOW] (초 단위)
    uint8_t u8CompCurrentRPS;       // CMD 19: 압축기 현재 RPS (37-75)
    uint8_t u8CompErrorCode;        // CMD 20: 압축기 에러코드 (E81~E88)
    uint8_t u8CompFanOutput;        // CMD 21: 압축기 팬 출력상태 (1:가동, 0:정지)
    uint8_t u8IceTankFanOutput;     // CMD 22: 얼음탱크 팬 출력상태 (1:가동, 0:정지)
    uint8_t u8Reserved_1;
    uint8_t u8Reserved_2;
    uint8_t u8Reserved_3;
    uint8_t u8Reserved_4;
    uint8_t u8Reserved_5;
    uint8_t u8Reserved_6;

    /* 냉각 데이터 (DATAFIELD 16-26) */
    uint8_t u8CoolingOpStatus;       // CMD 29: 운전상태 (1:운전, 0:정지)
    uint8_t u8CoolingInitStart;      // CMD 30: 초기 기동여부 (1:초기기동, 0:일반기동)
    uint8_t u8CoolingTargetRPS;      // CMD 31: 냉각용 목표 RPS (37-75)
    uint8_t u8CoolingOnTemp;         // CMD 32: ON 온도 (0.1℃ 단위)
    uint8_t u8CoolingOffTemp;        // CMD 33: OFF 온도 (0.1℃ 단위)
    uint8_t u8CoolingAddStartTime_H;   // CMD 34: 추가 기동시간 HIGH (ms)
    uint8_t u8CoolingAddStartTime_L;   // CMD 35: 추가 기동시간 LOW (ms)
    uint8_t u8Reserved_7;
    uint8_t u8Reserved_8;
    uint8_t u8Reserved_9;
    uint8_t u8Reserved_10;

    /* 제빙 데이터 (DATAFIELD 27-47) */
    uint8_t u8IceMakingStep;         // CMD 40: 제빙 STEP (0:더미탈빙, 1~:제빙STEP)
    uint8_t u8IceMakingTargetRPS;   // CMD 41: 제빙용 목표 RPS (37-75)
    uint8_t u8IceMakingTimeHigh;    // CMD 42: 제빙시간 [HIGH] (초 단위)
    uint8_t u8IceMakingTimeLow;     // CMD 43: 제빙시간 [LOW] (초 단위)
    uint8_t u8InletWaterCapHigh;    // CMD 44: 입수 용량 [HIGH] (Hz)
    uint8_t u8InletWaterCapLow;      // CMD 45: 입수 용량 [LOW] (Hz)
    uint8_t u8SwingBarOnTime;        // CMD 46: 스윙바 ON 시간 (0.1초)
    uint8_t u8SwingBarOffTime;       // CMD 47: 스윙바 OFF 시간 (0.1초)
    uint8_t u8IceTrayPosition;       // CMD 48: 제빙 트레이 위치 (0:제빙, 1:중간, 2:탈빙)
    uint8_t u8IceJamStatus;          // CMD 49: 얼음걸림 상태 (0:없음, 1:걸림)
    uint8_t u8Reserved_11;
    uint8_t u8Reserved_12;
    uint8_t u8Reserved_13;
    uint8_t u8Reserved_14;
    uint8_t u8Reserved_15;
    uint8_t u8Reserved_16;
    uint8_t u8Reserved_17;
    uint8_t u8Reserved_18;
    uint8_t u8Reserved_19;
    uint8_t u8Reserved_20;

    /* 보냉 데이터 (DATAFIELD 47-61) */
    uint8_t u8KeepColdStep;          // CMD 60: 보냉 STEP
    uint8_t u8KeepColdTargetRPS;     // CMD 61: 보냉용 목표 RPS (37-75)
    uint8_t u8KeepColdTargetTemp;    // CMD 62: 보냉 목표온도 (0.1℃ 단위)
    uint8_t u8KeepColdFirstTargetTemp; // CMD 63: 보냉 첫 목표온도 (0.1℃ 단위)
    uint8_t u8KeepColdTrayPosition;  // CMD 64: 보냉 트레이 위치 (0:제빙, 1:중간, 2:탈빙)
    uint8_t u8Reserved_21;
    uint8_t u8Reserved_22;
    uint8_t u8Reserved_23;
    uint8_t u8Reserved_24;
    uint8_t u8Reserved_25;
    uint8_t u8Reserved_26;
    uint8_t u8Reserved_27;
    uint8_t u8Reserved_28;
    uint8_t u8Reserved_29;
    uint8_t u8Reserved_30;

    /* 드레인 탱크 (DATAFIELD 62-70) */
    uint8_t u8DrainTankLowLevel;     // CMD 100: 드레인탱크 저수위 (1:감지, 0:미감지)
    uint8_t u8DrainTankFullLevel;   // CMD 101: 드레인탱크 만수위 (1:감지, 0:미감지)
    uint8_t u8DrainWaterLevelStatus;  // CMD 102: 수위 상태 (0:없음, 1:저수위, 2:중수위, 3:만수위, 4:에러)
    uint8_t u8DrainPumpOutput;       // CMD 103: 드레인 펌프 출력상태 (1:가동, 0:정지)
    uint8_t u8Reserved_31;
    uint8_t u8Reserved_32;
    uint8_t u8Reserved_33;
    uint8_t u8Reserved_34;
    uint8_t u8Reserved_35;

    /* 기타 (DATAFIELD 71-74) */
    uint8_t u8IceTankCover;          // DATA 71: 얼음탱크 커버 (1:열림, 0:닫힘)
    uint8_t u8Reserved_36;
    uint8_t u8Reserved_37;
    uint8_t u8Reserved_38;
    uint8_t u8Reserved_39;
    uint8_t u8Reserved_40;
} F1_COLD_SYSTEM_DATA_FIELD;

/* 통신 데이터 F2 구조체 */
typedef struct
{
    uint8_t u8HeatingOpStatus;
} F2_HEATING_SYSTEM_DATA_FIELD;

typedef struct
{
    uint8_t u8ColdTargetRPS;     // 냉각 목표 RPS
    uint8_t u8ColdOnTemp;        // 냉각 ON 온도
    uint8_t u8ColdOffTemp;       // 냉각 OFF 온도
    uint8_t ColdDelayTime_H;     // 냉각 추가기동 시간 [HIGH]
    uint8_t ColdDelayTime_L;     // 냉각 추가기동 시간 [LOW]
} B1_COLD_TABLE_DATA_FIELD;

typedef struct
{
    uint8_t u8IceMakeTargetRPS;  // 제빙 목표 RPS
    uint8_t TrayInHz_H;           // 입수용량 [HIGH]
    uint8_t TrayInHz_L;           // 입수용량 [LOW]
    uint8_t u8SwingbarOn;        // 스윙바 ON 시간
    uint8_t u8SwingbarOff;       // 스윙바 OFF 시간
} B2_ICE_MAKE_TABLE_DATA_FIELD;

typedef struct
{
    uint8_t u8IceStorageTargetRPS;  // 보냉 목표 RPS
    uint8_t u8TargetTemp;           // 보냉 목표온도
    uint8_t u8TargetTempFirst;      // 보냉 첫 목표온도
    uint8_t u8TrayPosition;         // 보냉 트레이 위치
} B4_ICE_STORAGE_TABLE_DATA_FIELD;

// 외기온도 [0`C ~ 45`C] 까지의 제빙 시간 테이블
// 제빙을 시작하기 직전의 외기온도, 입수온도에 따라 제빙 시간을 결정하기 위해 사용
// 제빙 직전의 시점에 제품에서 PC로 현재 외기온도와 입수온도, 제빙 Step을 보내주면 해당 외기온도, 입수온도, 제빙 Step에 따른 제빙 시간을 보냄
// Index는 제빙테이블에서 외기온도를 의미
typedef struct
{
    uint8_t  Used;
    uint16_t MakeTime[46];
} Freezing_Table_T;

void Get_F0_Data_Bytes(uint8_t *dest_buf, uint8_t length);
void Get_F1_Data_Bytes(uint8_t *dest_buf, uint8_t length);

void Parse_F0_Protocol(void);
void Parse_F1_Protocol(void);
void Parse_F2_Protocol(void);
void Parse_B1_Protocol(uint8_t *buf);
void Parse_B2_Protocol(uint8_t *buf);
void Parse_B4_Protocol(uint8_t *buf);

void FreezingTable_Init(void);
void SetFreezingTable(uint8_t *DataBuffer);
uint16_t GetFreezingTime(uint8_t RoomInTemp);
uint8_t GetIceStep(void);
void SetUsedFreezingTable(uint8_t Used);
uint8_t GetUsedFreezingTable(void);

uint8_t GetB1ColdTargetRPS(void);
void SetB1ColdTargetRPS(uint8_t *u8ColdTargetRPS);
uint8_t GetB1ColdOnTemp(void);
void SetB1ColdOnTemp(uint8_t *u8ColdOnTemp);
uint8_t GetB1ColdOffTemp(void);
void SetB1ColdOffTemp(uint8_t *u8ColdOffTemp);
uint16_t GetB1ColdDelayTime(void);
void SetB1ColdDelayTime(uint16_t *u16ColdDelayTime);

uint8_t GetB2IceMakeTargetRPS(void);
void SetB2IceMakeTargetRPS(uint8_t *u8IceMakeTargetRPS);
uint16_t GetB2TrayIn_Hz(void);
void SetB2TrayIn_Hz(uint16_t *u16TrayIn_Hz);
uint8_t GetB2SwingbarOn(void);
void SetB2SwingbarOn(uint8_t *u8SwingbarOn);
uint8_t GetB2SwingbarOff(void);
void SetB2SwingbarOff(uint8_t *u8SwingbarOff);

uint8_t GetB4IceStorageTargetRPS(void);
void SetB4IceStorageTargetRPS(uint8_t *u8IceStorageTargetRPS);
uint8_t GetB4TargetTemp(void);
void SetB4TargetTemp(uint8_t *u8TargetTemp);
uint8_t GetB4TargetTempFirst(void);
void SetB4TargetTempFirst(uint8_t *u8TargetTempFirst);
uint8_t GetB4TrayPosition(void);
void SetB4TrayPosition(uint8_t *u8TrayPosition);
#endif /*__PACKET_MATCH_H__*/

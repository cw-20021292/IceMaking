# CHPI All In One - 통신 모듈 (CodeModule_MV_Origin)

## 1. 개요

본 프로젝트는 정수기 제품과 PC 간의 시리얼 통신을 위한 임베디드 통신 모듈입니다.  
Renesas MCU 기반으로 UART 통신을 통해 냉각/제빙/보냉 시스템의 센서 데이터 수집, 제어 파라미터 설정 및 디버깅 기능을 제공합니다.

### 주요 기능
- **UART 기반 시리얼 통신**: PC와 제품 간 양방향 데이터 송수신
- **프로토콜 기반 통신**: STX/ETX 및 CRC 검증을 통한 안정적인 데이터 전송
- **시스템 모니터링**: 온도 센서, 밸브 상태, 압축기 상태 등 실시간 모니터링
- **파라미터 설정**: 냉각/제빙/보냉 모드의 목표값 및 동작 파라미터 설정
- **제빙 시간 테이블**: 외기온도별 제빙 시간 테이블 관리 (0°C ~ 45°C)

### 계층 구조
```
APP (Application Layer)
 ├─ App_Comm: 통신 상태 관리 및 패킷 핸들러
 ├─ App_Comm_Protocol: 프로토콜 파싱 및 ACK 패킷 생성
 ├─ Packet_Match: 프로토콜 데이터 매칭 및 구조체 관리
 └─ App_Comm_CLI: CLI 명령어 처리 (선택)
    ↓
API (Interface Layer)
 ├─ api_uart: UART 송수신 버퍼 및 API
 ├─ api_queue: 데이터 큐 관리
 └─ api_debug: 디버그 메시지 출력
    ↓
HAL (Hardware Abstraction Layer)
 └─ hal_serial: Renesas MCU UART 하드웨어 제어
```

---

## 2. 프로토콜 데이터

### 2.1 프로토콜 구조
모든 패킷은 다음과 같은 공통 구조를 가집니다:

```
┌─────┬────┬─────┬────────┬──────────┬─────────┬─────┐
│ STX │ ID │ CMD │ LENGTH │   DATA   │ CRC(2B) │ ETX │
├─────┼────┼─────┼────────┼──────────┼─────────┼─────┤
│0x02 │ 1B │ 1B  │  1B    │  0~nB    │  2B     │0x03 │
└─────┴────┴─────┴────────┴──────────┴─────────┴─────┘
```

- **STX**: 시작 바이트 (0x02)
- **ID**: 송신자 ID
  - `0x01`: PC
  - `0x02`: Main Board (제품)
  - `0x03`: Front Board
- **CMD**: 명령어 코드
- **LENGTH**: DATA 필드 길이 (바이트)
- **DATA**: 프로토콜별 데이터 필드
- **CRC**: CRC-16 체크섬 (Polynomial: 0x1021)
- **ETX**: 종료 바이트 (0x03)

### 2.2 지원 프로토콜

#### 2.2.1 F0 프로토콜 (공통 시스템 데이터)
**CMD**: `0xF0`  
**LENGTH**: 40 바이트  
**방향**: PC → 제품 (요청) / 제품 → PC (응답)

**데이터 필드 구성**:

| DATAFIELD | 항목 | 설명 | 단위 |
|-----------|------|------|------|
| 1 | 외기온도 1 | 외부 온도 센서 1 | 0.1°C |
| 2 | 입수온도 | 물 입수 온도 | 0.1°C |
| 3 | 정수온도 | 정수된 물 온도 | 0.1°C |
| 4 | 외기온도 2 | 외부 온도 센서 2 | 0.1°C |
| 5 | 냉수온도 | 냉수 출수 온도 | 0.1°C |
| 6 | 히터 내부온도 | 히터 내부 온도 | 0.1°C |
| 7 | 온수 출수온도 | 온수 출수 온도 | 0.1°C |
| 8~13 | Reserved | 예약 영역 | - |
| 14~18 | NOS 밸브 1~5 | NOS 밸브 상태 (1:CLOSE, 0:OPEN) | - |
| 19~33 | FEED 밸브 1~15 | FEED 밸브 상태 (1:OPEN, 0:CLOSE) | - |
| 34~38 | Reserved | 예약 영역 | - |
| 39 | 필터 리드스위치 | 필터 감지 (1:감지, 0:미감지) | - |
| 40 | 전면 리드스위치 | 전면 커버 감지 (1:감지, 0:미감지) | - |

---

#### 2.2.2 F1 프로토콜 (냉각 시스템 데이터)
**CMD**: `0xF1`  
**LENGTH**: 76 바이트  
**방향**: PC → 제품 (요청) / 제품 → PC (응답)

**데이터 필드 구성**:

##### 공조 시스템 (DATAFIELD 1-15)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 1 | 냉매전환밸브 1 위치 | 0:핫가스, 1:냉각, 2:제빙, 3:보냉 | 0~3 |
| 2 | 냉매전환밸브 2 위치 | 병렬 구조 | 0~3 |
| 3 | 압축기 출력상태 | 1:가동, 0:정지 | 0/1 |
| 4~5 | 압축기 안정시간 | HIGH/LOW 바이트 | 초 단위 |
| 6 | 압축기 현재 RPS | 현재 회전수 | 37~75 |
| 7 | 압축기 에러코드 | E81~E88 | - |
| 8 | 압축기 팬 출력 | 1:가동, 0:정지 | 0/1 |
| 9 | 얼음탱크 팬 출력 | 1:가동, 0:정지 | 0/1 |
| 10~15 | Reserved | 예약 영역 | - |

##### 냉각 데이터 (DATAFIELD 16-26)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 16 | 운전상태 | 1:운전, 0:정지 | 0/1 |
| 17 | 초기 기동여부 | 1:초기기동, 0:일반기동 | 0/1 |
| 18 | 냉각 목표 RPS | 목표 회전수 | 37~75 |
| 19 | 냉각 ON 온도 | 압축기 가동 온도 | 0.1°C |
| 20 | 냉각 OFF 온도 | 압축기 정지 온도 | 0.1°C |
| 21~22 | 추가 기동시간 | HIGH/LOW 바이트 | ms |
| 23~26 | Reserved | 예약 영역 | - |

##### 제빙 데이터 (DATAFIELD 27-47)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 27 | 제빙 STEP | 255:더미탈빙, 1~:제빙STEP | - |
| 28 | 제빙 목표 RPS | 목표 회전수 | 37~75 |
| 29~30 | 제빙시간 | HIGH/LOW 바이트 | 초 |
| 31~32 | 입수 용량 | HIGH/LOW 바이트 | Hz |
| 33 | 스윙바 ON 시간 | 스윙바 동작 시간 | 0.1초 |
| 34 | 스윙바 OFF 시간 | 스윙바 대기 시간 | 0.1초 |
| 35 | 제빙 트레이 위치 | 0:제빙, 1:중간, 2:탈빙 | 0~2 |
| 36 | 얼음걸림 상태 | 0:없음, 1:걸림 | 0/1 |
| 37~47 | Reserved | 예약 영역 | - |

##### 보냉 데이터 (DATAFIELD 48-62)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 48 | 보냉 STEP | 보냉 단계 | - |
| 49 | 보냉 목표 RPS | 목표 회전수 | 37~75 |
| 50 | 보냉 목표온도 | 유지 온도 | 0.1°C |
| 51 | 보냉 첫 목표온도 | 초기 목표 온도 | 0.1°C |
| 52 | 보냉 트레이 위치 | 0:제빙, 1:중간, 2:탈빙 | 0~2 |
| 53~62 | Reserved | 예약 영역 | - |

##### 드레인 탱크 (DATAFIELD 63-71)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 63 | 드레인탱크 저수위 | 1:감지, 0:미감지 | 0/1 |
| 64 | 드레인탱크 만수위 | 1:감지, 0:미감지 | 0/1 |
| 65 | 수위 상태 | 0:없음, 1:저수위, 2:중수위, 3:만수위, 4:에러 | 0~4 |
| 66 | 드레인 펌프 출력 | 1:가동, 0:정지 | 0/1 |
| 67~71 | Reserved | 예약 영역 | - |

##### 기타 (DATAFIELD 72-76)
| DATAFIELD | 항목 | 설명 | 값 범위 |
|-----------|------|------|---------|
| 72 | 얼음탱크 커버 | 1:열림, 0:닫힘 | 0/1 |
| 73~76 | Reserved | 예약 영역 | - |

---

#### 2.2.3 F2 프로토콜 (히팅 시스템 데이터)
**CMD**: `0xF2`  
**LENGTH**: 가변  
**방향**: PC → 제품 (요청) / 제품 → PC (응답)  
*(현재 구현 예정)*

---

#### 2.2.4 B1 프로토콜 (냉각 파라미터 설정)
**CMD**: `0xB1`  
**LENGTH**: 5 바이트  
**방향**: PC → 제품 (설정)

**데이터 필드**:
| Byte | 항목 | 설명 | 값 범위 |
|------|------|------|---------|
| 0 | 냉각 목표 RPS | 압축기 목표 회전수 | 37~75 |
| 1 | 냉각 ON 온도 | 압축기 가동 온도 | 0.1°C |
| 2 | 냉각 OFF 온도 | 압축기 정지 온도 | 0.1°C |
| 3~4 | 냉각 추가기동 시간 | HIGH/LOW 바이트 | ms |

---

#### 2.2.5 B2 프로토콜 (제빙 파라미터 설정)
**CMD**: `0xB2`  
**LENGTH**: 5 바이트  
**방향**: PC → 제품 (설정)

**데이터 필드**:
| Byte | 항목 | 설명 | 값 범위 |
|------|------|------|---------|
| 0 | 제빙 목표 RPS | 압축기 목표 회전수 | 37~75 |
| 1~2 | 입수용량 | HIGH/LOW 바이트 | Hz |
| 3 | 스윙바 ON 시간 | 스윙바 동작 시간 | 0.1초 |
| 4 | 스윙바 OFF 시간 | 스윙바 대기 시간 | 0.1초 |

---

#### 2.2.6 B3 프로토콜 (제빙 시간 테이블 설정)
**CMD**: `0xB3`  
**LENGTH**: 92 바이트  
**방향**: PC → 제품 (설정)

**데이터 필드**:
- 외기온도 0°C ~ 45°C에 대응하는 46개의 제빙 시간 값 (각 2바이트, U16)
- Index 0 = 0°C의 제빙 시간 (초)
- Index 1 = 1°C의 제빙 시간 (초)
- ...
- Index 45 = 45°C의 제빙 시간 (초)

**사용 예시**:
```c
// 외기온도 25°C일 때 제빙 시간 조회
U16 makingTime = GetFreezingTime(25);
```

---

#### 2.2.7 B4 프로토콜 (보냉 파라미터 설정)
**CMD**: `0xB4`  
**LENGTH**: 4 바이트  
**방향**: PC → 제품 (설정)

**데이터 필드**:
| Byte | 항목 | 설명 | 값 범위 |
|------|------|------|---------|
| 0 | 보냉 목표 RPS | 압축기 목표 회전수 | 37~75 |
| 1 | 보냉 목표온도 | 유지 온도 | 0.1°C |
| 2 | 보냉 첫 목표온도 | 초기 목표 온도 | 0.1°C |
| 3 | 보냉 트레이 위치 | 0:제빙, 1:중간, 2:탈빙 | 0~2 |

---

## 3. 사용방법

### 3.1 사용할 UART 채널 설정

#### 📁 파일 위치
- `HAL\hal_serial.h`
- `HAL\hal_serial.c`

#### 설정 방법

1. **`hal_serial.h` 파일 수정**

UART 채널을 선택하려면 다음과 같이 매크로를 주석 처리하거나 활성화합니다:

```c
// UART0 사용 시
#define USE_UART0_MODULE

// UART3 사용 시 (기본값)
#define USE_UART3_MODULE
```

> ⚠️ **주의**: 한 번에 하나의 채널만 활성화해야 합니다.

2. **UART 초기화**

`api_uart.c`의 `Uart_Init()` 함수에서 UART를 초기화합니다:

```c
void Uart_Init(void)
{
    // UART3 초기화 (hal_serial.h에서 USE_UART3_MODULE 정의 필요)
    HAL_Uart_Init(UART_CHANNEL_3, uart3_recv_callback, uart3_send_callback);
}
```

3. **하드웨어 설정 확인**
   - 보레이트(Baud Rate): **9600bps** (고정)
   - 인터럽트: 송신(`INTST3`), 수신(`INTSR3`) 인터럽트 자동 연결

---

### 3.2 프로토콜 매칭

#### 📁 파일 위치
- `APP\Packet_Match.h`
- `APP\Packet_Match.c`

#### 설정 방법

프로토콜 데이터와 실제 MCU의 센서/제어 변수를 매칭하려면 `Parse_F0_Protocol()` 및 `Parse_F1_Protocol()` 함수를 수정합니다.

---

#### 3.2.1 F0 프로토콜 매칭 (공통 시스템 데이터)

**예제**: 온도 센서 값 매핑

`Packet_Match.c` 파일에서 `Parse_F0_Protocol()` 함수를 수정합니다:

```c
void Parse_F0_Protocol(void)
{
    /* 센서류 (DATAFIELD 1-13) */
    // Data 1 : 외기온도 1 (0.1℃ 단위)
    F0Data.u8AmbTemp1 = gu8_Amb_Temperature_One_Degree;  // 실제 외기온도 변수 연결
    
    // Data 2 : 입수온도 (0.1℃ 단위)
    F0Data.u8InletWaterTemp = gu8_Room_Temperature_One_Degree;  // 실제 입수온도 변수 연결
    
    // Data 3 : 정수온도 (0.1℃ 단위)
    F0Data.u8PurifiedWaterTemp = 0;  // 값이 없으면 0으로 설정
    
    // Data 5 : 냉수온도 (0.1℃ 단위)
    F0Data.u8ColdWaterTemp = gu8_Cold_Temperature_One_Degree;  // 실제 냉수온도 변수 연결
    
    // Data 6 : 히터 내부온도 (0.1℃ 단위)
    F0Data.u8HeaterInternalTemp = gu8_Hot_Heater_Temperature_One_Degree;  // 실제 히터온도 변수 연결
    
    // Data 7 : 온수 출수온도 (0.1℃ 단위)
    F0Data.u8HotWaterOutletTemp = gu8_Hot_Out_Temperature_One_Degree;  // 실제 온수온도 변수 연결

    /* 밸브 상태 (DATAFIELD 14-38) */
    // NOS 밸브: 1=CLOSE, 0=OPEN
    F0Data.u8ValveNOS1 = bit_nos_output;  // 실제 밸브 출력 변수 연결
    
    // FEED 밸브: 1=OPEN, 0=CLOSE
    F0Data.u8ValveFEED1 = u8RoomInValveON;  // 실제 밸브 ON 변수 연결
    F0Data.u8ValveFEED2 = 0;
    // ... (필요한 밸브만 매핑)

    // 리드스위치 (1 : 감지, 0 : 미감지)
    F0Data.u8FilterReed = bit_filter_reed;  // 필터 리드스위치 변수 연결
    F0Data.u8FrontReed = bit_filter_cover;  // 전면 리드스위치 변수 연결
}
```

---

#### 3.2.2 F1 프로토콜 매칭 (냉각 시스템 데이터)

**예제**: 압축기 및 냉각 데이터 매핑

`Packet_Match.c` 파일에서 `Parse_F1_Protocol()` 함수를 수정합니다:

```c
void Parse_F1_Protocol(void)
{
    /* 공조시스템 (DATAFIELD 1-15) */
    // Data 1 : 냉매전환밸브 1 현재위치 (0:핫가스, 1:냉각, 2:제빙, 3:보냉)
    F1Data.u8RefValve1Pos = gu8_GasSwitch_Status;  // 실제 가스밸브 상태 변수 연결
    
    // Data 3 : 압축기 출력상태 (1:가동, 0:정지)
    F1Data.u8CompOutputStatus = F_Comp_Output;  // 실제 압축기 출력 플래그 연결
    
    // Data 4~5 : 압축기 안정시간 [HIGH/LOW] (초 단위)
    F1Data.u8CompStableTimeHigh = HIGH_BYTE(gu16CompOffDelay);  // 실제 압축기 딜레이 변수 연결
    F1Data.u8CompStableTimeLow = LOW_BYTE(gu16CompOffDelay);
    
    // Data 6 : 압축기 현재 RPS (37-75)
    F1Data.u8CompCurrentRPS = gu8_bldc_target_hz;  // 실제 압축기 RPS 변수 연결
    
    // Data 7 : 압축기 에러코드 (E81~E88)
    F1Data.u8CompErrorCode = gu8BLDCErrorNum;  // 실제 에러 코드 변수 연결

    /* 냉각 데이터 (DATAFIELD 14-26) */
    // Data 1 : 운전상태 (1:운전, 0:정지)
    F1Data.u8CoolingOpStatus = F_Safety_Routine;  // 실제 운전 상태 플래그 연결
    
    // Data 2 : 초기 기동여부 (1:초기기동, 0:일반기동)
    F1Data.u8CoolingInitStart = F_Cold_Operation_Init;  // 실제 초기 기동 플래그 연결
    
    // Data 3~7 : B1 프로토콜에서 설정된 값 사용
    F1Data.u8CoolingTargetRPS = (GetB1ColdTargetRPS() > 0) ? GetB1ColdTargetRPS() : get_cold_mode_comp_rps();
    F1Data.u8CoolingOnTemp = (GetB1ColdOnTemp() > 0) ? GetB1ColdOnTemp() : gu16_test_cold_on_temp;
    F1Data.u8CoolingOffTemp = (GetB1ColdOffTemp() > 0) ? GetB1ColdOffTemp() : gu16_test_cold_off_temp;
    // ... (나머지 항목도 동일하게 매핑)

    /* 제빙 데이터 (DATAFIELD 27-47) */
    // Data 1 : 제빙 STEP (255:더미탈빙, 1~:제빙STEP)
    F1Data.u8IceMakingStep = GetIceStep();  // 실제 제빙 STEP 함수 호출
    
    // Data 2 : 제빙용 목표 RPS (37-75)
    F1Data.u8IceMakingTargetRPS = get_ice_mode_comp_rps();  // 실제 제빙 RPS 함수 호출
    
    // Data 3~4 : 제빙시간 [HIGH/LOW] (초 단위)
    F1Data.u8IceMakingTimeHigh = HIGH_BYTE(gu16IceMakeTime);  // 실제 제빙 시간 변수 연결
    F1Data.u8IceMakingTimeLow = LOW_BYTE(gu16IceMakeTime);

    /* 드레인 탱크 (DATAFIELD 63-71) */
    // Data 4 : 드레인 펌프 출력상태 (1:가동, 0:정지)
    F1Data.u8DrainPumpOutput = F_Drain_Pump_Output;  // 실제 펌프 출력 플래그 연결

    /* 기타 (DATAFIELD 72-76) */
    // Data 1 : 얼음탱크 커버 (1:열림, 0:닫힘)
    F1Data.u8IceTankCover = F_Tank_Cover_Input;  // 실제 탱크 커버 입력 플래그 연결
}
```

---

#### 3.2.3 B1/B2/B4 프로토콜 수신 처리

B1, B2, B4 프로토콜은 PC에서 제품으로 파라미터를 설정하는 프로토콜입니다.  
수신된 데이터는 자동으로 구조체에 저장되며, `Get` 함수를 통해 값을 읽을 수 있습니다.

**사용 예제**:

```c
// 메인 루프에서 B1 프로토콜로 수신된 냉각 파라미터 사용
void main_loop(void)
{
    U8 targetRPS = GetB1ColdTargetRPS();      // 냉각 목표 RPS 읽기
    U8 onTemp = GetB1ColdOnTemp();            // 냉각 ON 온도 읽기
    U8 offTemp = GetB1ColdOffTemp();          // 냉각 OFF 온도 읽기
    U16 delayTime = GetB1ColdDelayTime();     // 냉각 추가 기동시간 읽기
    
    if(targetRPS > 0)  // PC에서 설정값이 들어왔다면
    {
        set_compressor_target_rps(targetRPS);
    }
}

// B2 프로토콜로 수신된 제빙 파라미터 사용
void ice_making_control(void)
{
    U8 iceMakeRPS = GetB2IceMakeTargetRPS();   // 제빙 목표 RPS
    U16 trayInHz = GetB2TrayIn_Hz();           // 입수용량
    U8 swingOnTime = GetB2SwingbarOn();        // 스윙바 ON 시간
    U8 swingOffTime = GetB2SwingbarOff();      // 스윙바 OFF 시간
}

// B3 프로토콜로 수신된 제빙 시간 테이블 사용
void get_ice_making_time(void)
{
    U8 ambTemp = 25;  // 현재 외기온도 25°C
    
    if(GetUsedFreezingTable())  // 제빙 테이블이 설정되었는지 확인
    {
        U16 makingTime = GetFreezingTime(ambTemp);  // 해당 온도의 제빙 시간 조회
        start_ice_making(makingTime);
    }
}

// B4 프로토콜로 수신된 보냉 파라미터 사용
void ice_storage_control(void)
{
    U8 storageRPS = GetB4IceStorageTargetRPS();  // 보냉 목표 RPS
    U8 targetTemp = GetB4TargetTemp();            // 보냉 목표온도
    U8 firstTemp = GetB4TargetTempFirst();        // 보냉 첫 목표온도
    U8 trayPos = GetB4TrayPosition();             // 보냉 트레이 위치
}
```

---

### 3.3 통신 흐름

#### 송수신 흐름도

```
PC                          제품(MCU)
 │                              │
 ├─── F0 요청 (STX+ID+CMD...) ─>│
 │                              ├─ Parse_F0_Protocol() 호출
 │                              ├─ 센서 값을 F0Data 구조체에 채움
 │<── F0 응답 (센서 데이터) ────┤
 │                              │
 ├─── F1 요청 (STX+ID+CMD...) ─>│
 │                              ├─ Parse_F1_Protocol() 호출
 │                              ├─ 냉각 시스템 값을 F1Data 구조체에 채움
 │<── F1 응답 (냉각 데이터) ────┤
 │                              │
 ├─── B1 설정 (냉각 파라미터) ─>│
 │                              ├─ Parse_B1_Protocol() 호출
 │                              ├─ B1Data 구조체에 저장
 │<── B1 응답 (Echo) ───────────┤
 │                              │
 ├─── B3 설정 (제빙 테이블) ───>│
 │                              ├─ SetFreezingTable() 호출
 │                              ├─ FreezingTable에 저장
 │                              ├─ Parse_F1_Protocol() 호출 (응답용)
 │<── F1 응답 (제빙 데이터) ────┤
 │                              │
```

---

### 3.4 패킷 검증 및 처리

#### 수신 패킷 검증
`App_Comm_Protocol.c`의 `Protocol_isValidPacket()` 함수가 자동으로 다음을 검증합니다:
- STX/ETX 확인
- ID 확인 (PC ID: 0x01)
- 패킷 길이 확인
- CRC-16 체크섬 확인

#### 패킷 처리 흐름
```c
// App_Comm.c의 Comm_Packet_Handler() 함수에서 자동 처리
void Comm_Packet_Handler(void)
{
    if(GetCommState() == COMM_STATE_RECEIVING)
    {
        if(Protocol_isValidPacket(comm_info.comm_rx_buffer))  // 패킷 검증
        {
            // ACK 패킷 생성 및 송신
            U8 tx_length = Protocol_Make_Ack_Packet(comm_info.comm_rx_buffer, 
                                                     comm_info.comm_tx_buffer);
            Uart_Send_Buffer(UART_CHANNEL_3, (const char*)comm_info.comm_tx_buffer, tx_length);
        }
        SetCommState(COMM_STATE_IDLE);
    }
}
```

---

## 4. 디버깅 및 트러블슈팅

### 4.1 디버그 메시지 출력

`api_debug.h`를 사용하여 UART로 디버그 메시지를 출력할 수 있습니다:

```c
#include "api_debug.h"

// 문자열 출력
Debug_Print("System Init OK\r\n");

// 16진수 값 출력
Debug_PrintHex8(temperature);     // 1바이트
Debug_PrintHex16(pressure);       // 2바이트
```

### 4.2 일반적인 문제 해결

#### 문제 1: 통신이 안 됨
- `hal_serial.h`에서 UART 채널 정의 확인 (`USE_UART3_MODULE`)
- 보레이트 확인 (9600bps)
- UART 핀 연결 확인

#### 문제 2: CRC 에러 발생
- 패킷 데이터 손상 확인
- 노이즈 대책 확인 (GND 연결, 차폐선 사용)

#### 문제 3: 센서 값이 0으로 표시됨
- `Parse_F0_Protocol()` 또는 `Parse_F1_Protocol()` 함수에서 실제 변수 연결 확인
- 외부 변수 선언(`extern`) 확인

---

## 5. 참고 사항

### 5.1 메모리 사용량
- UART 수신 버퍼: 256 바이트
- UART 송신 버퍼: 256 바이트
- F0 데이터 구조체: 40 바이트
- F1 데이터 구조체: 76 바이트
- 제빙 테이블: 93 바이트 (46 × 2 + 1)

### 5.2 제약사항
- 최대 패킷 크기: 256 바이트
- 지원 UART 채널: UART0, UART3 (Renesas MCU 종속)
- 보레이트: 9600bps 고정

### 5.3 확장 방법
- 새로운 프로토콜 추가 시:
  1. `Packet_Match.h`에 프로토콜 enum 및 구조체 정의
  2. `Packet_Match.c`에 `Parse_XXX_Protocol()` 함수 구현
  3. `App_Comm_Protocol.c`의 `Protocol_Make_Ack_Data()` 함수에 case 추가

---

## 6. 라이선스 및 연락처

**프로젝트**: CHPI All In One - 통신 모듈  
**대상 MCU**: Renesas RL78 시리즈  
**작성자**: CHPI 개발팀  
**버전**: 1.0 (2025)

---

**End of Document**

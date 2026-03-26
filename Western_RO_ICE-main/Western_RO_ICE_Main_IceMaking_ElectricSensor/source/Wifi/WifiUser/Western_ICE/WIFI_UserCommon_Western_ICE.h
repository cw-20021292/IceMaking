
#ifndef _WIFI_COMMON_MAX_H_
#define _WIFI_COMMON_MAX_H_

#ifdef Western_AIS

/***** User headers ****************************************************************/
/*#include "r_cg_macrodriver.h"*/
/*#include "r_cg_serial.h"*/
/*#include "WIFI_DefUser.h"*/
#include    "Macrodriver.h"
#include    "Global_Variable.h"


/***** Type Define *****************************************************************/
#if 0
typedef unsigned char       U8;
typedef signed char         I8;
typedef unsigned int        U16;
typedef signed int          I16;
typedef const signed char   CI8;
typedef const signed int    CI16;
typedef unsigned long int   U32;
typedef float               F32;
typedef double              D64;
#endif
/***** library headers ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/********** Western_ICE **********/
// #define MODEL_NO_1     // Western RO
// #define MODEL_NO_2  // Western Built IN
#define MODEL_NO_3  // Western AIS
// #define MODEL_NO_4  // WesternNT

#define WIFI_VERSION    "V1.0.0.1"	// WiFi Version
#define MODEL_NAME_CHP  "CHPI-1500L"
#define MODEL_NAME_CP   "CHPI-1500L"

#define MODEL_NAME_CHP_BLESSID  "CHPI1500LCW"
#define MODEL_NAME_CP_BLESSID   "CHPI1500LCW"

// USER WIFI Port & Register
#define R_TXD           TXD1
#define R_RXD           RXD1
#define R_STIF          STIF1
#define P_WIFI_ON       P0.4
#define P_WIFI_RSTN     P0.1

// USER Define (Number of User Data)
#if 0
#define USER_DATA_MAX_NUM   58  // The number of data (Total)
//#define USER_DATA_MAX_NUM_1BYTE   48  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_1BYTE   45  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_3BYTE   13  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_5BYTE   20  // The number of data (DATA Size)
#endif

#define USER_DATA_MAX_NUM   104  // The number of data (Total)
//#define USER_DATA_MAX_NUM_1BYTE   48  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_1BYTE   64  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_3BYTE   10  // The number of data (DATA Size)
#define USER_DATA_MAX_NUM_5BYTE   30  // The number of data (DATA Size)


#define USER_INFO_MAX_NUM   10  // The number of info
//#define USER_USE_ACCUMULATE     // A10A0 used / unused
//#define USER_USE_WEATHER        // A2010 Weather used / unused
#define USER_USE_ACK            // WiFi Ack used / unused

// #define FOTA_SIZE_128K
// #define FOTA_SIZE_192K
#define FOTA_SIZE_256K

// USER Define (RomSize/ProductNum)
#define FOTA            1           // 0:Unused / 1:Used Fota

#ifdef FOTA_SIZE_128K
#define FOTA_SIZE       "513"       // FotaSize = Rom Size * 4 + 1
#endif

#ifdef FOTA_SIZE_192K
#define FOTA_SIZE       "769"       // FotaSize = Rom Size * 4 + 1
#endif

#ifdef FOTA_SIZE_256K
#define FOTA_SIZE       "1025"       // FotaSize = Rom Size * 4 + 1
#endif


#define FOTA_TYPE_CHP   "113713"    // Product Code Number // 02FOB
#define FOTA_TYPE_CP    "113713"    // Product Code Number

// USER Define (EEPROM Address)
#if 0
#define EEPROM_ADDR_WIFI_POWER      0x17   // WIFI On/Off Status
#define EEPROM_ADDR_FIRST_PARING    0x18   // WIFI First Paring Status
#define EEPROM_ADDR_FOTA_MODULE     0x19   // WIFI Module Fota Status
#define EEPROM_ADDR_FOTA_MCU        0x1A   // WIFI MCU Fota Status
#endif

#define Z_rammax		(0xFEDF)        //(0xFEDF)				//	MCU RAM Range_MAX ~ less than SFR
#define Z_rammin		(0xBF00)		//	MCU RAM Range_MIN* 192K

// USER Define (Buzzer)

// #define	WIFI_BUZZER_SELECT          0x01  // 페어링 (선택음 "띵")
// #define	WIFI_BUZZER_AP_CONNECT      0x02  // AP연결 (진입음 "띠리링" / 와이파이 연결을 시작합니다)
// #define	WIFI_BUZZER_SETUP           0x03  // WIFI ON (설정음 "띵동↗" / 와이파이 연결을 시작합니다)
// #define	WIFI_BUZZER_SERVER_CONNECT  0x04  // 서버연결 (연결음 "띠리링↗" / 와이파이 연결이 완료되었습니다)
// #define	WIFI_BUZZER_AP_FAIL         0x05  // 페어링30분 경과 (해제음 "동띵" / 와이파이 연결이 실패되었습니다. 인터넷 공유기를 확인해주세요. 문제가 반복되면 콜센터에 연락주세요.)
// #define	WIFI_BUZZER_CANCEL          0x06  // WIFI OFF (해제음 "동띵" / 와이파이 연결이 해제되었습니다. 다시 연결하시려면 제품 설정 모드에서 와이파이를 켜주세요.)
// #define WIFI_BUZZER_AP_START         0x07  // AP시작음 (설정음 "띵동 ↗")
// #define	WIFI_BUZZER_ERROR           0x08  // 불가음 (에러음 "띵깡띵깡")
// #define WIFI_BUZZER_SERVER_FIRST     0x09  // 서버연결 (연결음 "띠리링↗" / 와이파이 연결이 완료되었습니다. 이제부터 아이오케어 앱을 통해 스마트한 관리를 받으실 수 있습니다.)
// #define	WIFI_BUZZER_BLE_OFF         0x0A  // 블루투스 패어링 해제음(동띵)

#if 0
#define WIFI_BUZZER_SELECT          0x68 // 페어링 (선택음 "띵")
#define	WIFI_BUZZER_AP_CONNECT      0x40 // AP연결 (진입음 "띠리링" / 와이파이 연결을 시작합니다)
//#define	WIFI_BUZZER_SETUP           0x40 // WIFI ON (설정음 "띵동↗" / 와이파이 연결을 시작합니다)
#define	WIFI_BUZZER_SETUP           0x38 // WIFI ON (설정음 "띵동↗" / 와이파이 연결을 시작합니다)
#define	WIFI_BUZZER_SERVER_CONNECT  0x44 // 서버연결 (연결음 "띠리링↗" / 와이파이 연결이 완료되었습니다)
#define	WIFI_BUZZER_AP_FAIL         0x42 // 페어링30분 경과 (해제음 "동띵" / 와이파이 연결이 실패되었습니다. 인터넷 공유기를 확인해주세요. 문제가 반복되면 콜센터에 연락주세요.)
#define	WIFI_BUZZER_CANCEL          0x7F // WIFI OFF (해제음 "동띵" / 와이파이 연결이 해제되었습니다. 다시 연결하시려면 제품 설정 모드에서 와이파이를 켜주세요.)
#define WIFI_BUZZER_AP_START        0x6A // AP시작음 (설정음 "띵동 ↗")
#define WIFI_BUZZER_ERROR           0x69 // 불가음 (에러음 "띵깡띵깡")
#define WIFI_BUZZER_SERVER_FIRST    0x41 // 서버연결 (연결음 "띠리링↗" / 와이파이 연결이 완료되었습니다. 이제부터 아이오케어 앱을 통해 스마트한 관리를 받으실 수 있습니다.)
#define WIFI_BUZZER_BLE_OFF	        0x6B // 블루투스 패어링 해제음(동띵)
#endif

#if 0
#define	WIFI_BUZZER_SELECT          (BUZZER_SELECT)     // 페어링 (선택음 "띵")
#define WIFI_BUZZER_AP_START        (BUZZER_SETUP)      // AP시작음 (설정음 "띵동 ↗")
#define	WIFI_BUZZER_ERROR           (BUZZER_ERROR)      // 불가음 (에러음 "띵깡띵깡")

#define	WIFI_BUZZER_AP_CONNECT      (BUZZER_AP_CONNECT)     // AP연결 (진입음 "띠리링" / Wi-Fi 연결모드가 활성화 되었습니다.) (웨스턴 추가)
#define	WIFI_BUZZER_BLE_CONNECT     (BUZZER_AP_CONNECT)     // AP연결 (진입음 "띠리링" / BLE연결모드가 활성화 되었습니다.) (웨스턴 추가)
#define	WIFI_BUZZER_SETUP           (BUZZER_SETUP)          // WIFI ON (설정음 "띵동↗" / 제품의 Wi-Fi가 켜졌습니다.)
#define	WIFI_BUZZER_SERVER_CONNECT  (BUZZER_SERVER_CONNECT) // 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.)
#define	WIFI_BUZZER_AP_FAIL         (BUZZER_CANCEL)         // 페어링30분 경과 (해제음 "동띵" / 제품과 앱의 연결이 실패하였습니다.)
#define	WIFI_BUZZER_CANCEL          (BUZZER_CANCEL)         // WIFI OFF (해제음 "동띵" / 제품의 Wi-Fi가 꺼졌습니다.)
#define	WIFI_BUZZER_SERVER_FIRST    (BUZZER_SERVER_CONNECT) // 최초 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.) (웨스턴은 최초연결과 그 이후 연결과 음성 동일)
#define WIFI_BUZZER_WiFi_OFF        (BUZZER_CANCEL)         // Wi-Fi 페어링 해제음(동띵) / Wi-Fi 연결 모드가 비활성화 되었습니다. (웨스턴 추가)
#define	WIFI_BUZZER_BLE_OFF         (BUZZER_CANCEL)         // 블루투스 페어링 해제음(동띵) / 블루투스 연결 모드가 비활성화 되었습니다. (웨스턴 추가)
#define WIFI_BUZZER_BLE_CERT        (BUZZER_SELECT)         // (선택음 "띵") / 블루투스 점유인증 활성화 상태 / 제품인증을 진행 중입니다. 앱에서 가이드하는 버튼을 눌러주세요. (웨스턴 추가)

#define WIFI_BUZZER_SMART_CHECK_OK          (BUZZER_CANCEL) // (설정음 "띵동 ↗") / 스마트 진단이 완료 되어 제품을 사용하실 수 있습니다. (웨스턴 추가 x005C)
#define WIFI_BUZZER_SMART_CHECK_ERROR       (BUZZER_ERROR)  // 불가음 (에러음 "띵깡띵깡") / 스마트 진단이 완료 되었습니다. (웨스턴 추가 x005C)
#endif

#define	WIFI_BUZZER_SELECT          (VOICE_196_MELODY_SELECT)     // 페어링 (선택음 "띵")
#define WIFI_BUZZER_AP_START        (VOICE_198_MELODY_SET_ON)      // AP시작음 (설정음 "띵동 ↗")
#define	WIFI_BUZZER_ERROR           (VOICE_197_MELODY_WARNING)      // 불가음 (에러음 "띵깡띵깡")

#define	WIFI_BUZZER_AP_CONNECT      (VOICE_66_INFORM_WIFI_MODE_ACTIVATED)     // AP연결 (진입음 "띠리링" / Wi-Fi 연결모드가 활성화 되었습니다.) (웨스턴 추가)
#define	WIFI_BUZZER_BLE_CONNECT     (VOICE_64_INFORM_BLE_MODE_ACTIVATED)     // AP연결 (진입음 "띠리링" / BLE연결모드가 활성화 되었습니다.) (웨스턴 추가)
#define	WIFI_BUZZER_SETUP           (VOICE_68_INFORM_WIFI_ON)          // WIFI ON (설정음 "띵동↗" / 제품의 Wi-Fi가 켜졌습니다.)
#define	WIFI_BUZZER_SERVER_CONNECT  (VOICE_71_INFORM_APP_PAIRING_SUCCESS) // 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.)
#define	WIFI_BUZZER_AP_FAIL         (VOICE_72_INFORM_APP_PAIRING_FAIL)         // 페어링30분 경과 (해제음 "동띵" / 제품과 앱의 연결이 실패하였습니다.)
#define	WIFI_BUZZER_CANCEL          (VOICE_74_INFORM_WIFI_OFF)         // WIFI OFF (해제음 "동띵" / 제품의 Wi-Fi가 꺼졌습니다.)
#define	WIFI_BUZZER_SERVER_FIRST    (VOICE_71_INFORM_APP_PAIRING_SUCCESS) // 최초 서버연결 (연결음 "띠리링↗" / 제품과 앱이 성공적으로 연결되었습니다.) (웨스턴은 최초연결과 그 이후 연결과 음성 동일)
#define WIFI_BUZZER_WiFi_OFF        (VOICE_67_INFORM_WIFI_MODE_DEACTIVATED)         // Wi-Fi 페어링 해제음(동띵) / Wi-Fi 연결 모드가 비활성화 되었습니다. (웨스턴 추가)
#define	WIFI_BUZZER_BLE_OFF         (VOICE_65_INFORM_BLE_MODE_DEACTIVATED)         // 블루투스 페어링 해제음(동띵) / 블루투스 연결 모드가 비활성화 되었습니다. (웨스턴 추가)
#define WIFI_BUZZER_BLE_CERT        (VOICE_70_PRESS_BUTTON_ACCORDING_TO_APP_GUIDE)         // (선택음 "띵") / 블루투스 점유인증 활성화 상태 / 제품인증을 진행 중입니다. 앱에서 가이드하는 버튼을 눌러주세요. (웨스턴 추가)

#define WIFI_BUZZER_SMART_CHECK_OK          (VOICE_62_FINISH_SMART_TESTING_MODE_NO_ERROR) // (설정음 "띵동 ↗") / 스마트 진단이 완료 되어 제품을 사용하실 수 있습니다. (웨스턴 추가 x005C)
#define WIFI_BUZZER_SMART_CHECK_ERROR       (VOICE_63_FINISH_SMART_TESTING_MODE_WITH_ERROR)  // 불가음 (에러음 "띵깡띵깡") / 스마트 진단이 완료 되었습니다. (웨스턴 추가 x005C)



#endif

#endif


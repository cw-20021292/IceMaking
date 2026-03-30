#include "WIFI_cJSON.h"

#ifndef _WIFI_UserInterface_MAX_H_
#define _WIFI_UserInterface_MAX_H_

// Define structures for parsed JSON data

// // SAP ���� CODE
// #define F1000  0U  //SAP001 ����
// #define S1000  1U
// #define E9000  2U

// typedef enum{  // Json KEY
//     WIFI_JSON_UV_FAUCET_LD = 0,
//     WIFI_JSON_UV_FAUCET_ND,
//     WIFI_JSON_SUPPLY_FILTER_SEQ ,
//     WIFI_JSON_SUPPLY_FILTER_MT ,
//     WIFI_JSON_SUPPLY_FILTER_LD ,
//     WIFI_JSON_SUPPLY_FILTER_ND ,
//     WIFI_JSON_SUPPLY_FILTER_FR ,
//     WIFI_JSON_SUPPLY_FLOWMODULE_SEQ,
//     WIFI_JSON_SUPPLY_FLOWMODULE_MT,
//     WIFI_JSON_SUPPLY_FLOWMODULE_LD,
//     WIFI_JSON_SUPPLY_FLOWMODULE_ND,
//     WIFI_JSON_SUPPLY_FLOWMODULE_FR,
//     WIFI_JSON_ENVIRONMENT_SPB,
//     WIFI_JSON_ENVIRONMENT_SCS,
//     WIFI_JSON_ENVIRONMENT_MCT,

//     WIFI_JSON_KEY_MAX
// }E_WIFI_JSON_KEY_T;

// enum{  // Json UV DAY
//     WIFI_JSON_UV_LASTDAY = 0,
//     WIFI_JSON_UV_NEXTDAY,

//     WIFI_JSON_UV_DAY_MAX
// };

// enum{  // Json Supply KEY
//     WIFI_JSON_ARRAY_FILTER = 0,
//     WIFI_JSON_ARRAY_FLOWMODULE,

//     WIFI_JSON_SUPPLY_KEY_MAX
// };

// enum{  // JSON SUPPLY 
//     WIFI_JSON_SUPPLY_LASTDAY= 0,
//     WIFI_JSON_SUPPLY_NEXTDAY,
//     WIFI_JSON_SEQ,
//     WIFI_JSON_MEMBERSHIP,
//     WIFI_JSON_REMAIN,

//     WIFI_JSON_SUPPLY_VALUE_MAX
// };

// enum{ // JSON ENVIRONMENT
//     WIFI_JSON_SAVED_PLASTIC_BOTTLES = 0,
//     WIFI_JSON_CARBON_SAVINGS,
//     WIFI_JSON_MATURE_CARBON_TREES,

//     WIFI_JSON_ENVIRONMENT_MAX
// };

// typedef enum{
//     WIFI_JSON_T1_YEAR = 0,
//     WIFI_JSON_T1_MONTH,
//     WIFI_JSON_T1_DAY,
//     WIFI_JSON_T1_HOUR,
//     WIFI_JSON_T1_MIN,

//     WIFI_JSON_DATE_YMDHM_MAX
// }E_WIFI_JSON_DATE_YMDHM_T;

// typedef enum{
//     WIFI_JSON_T2_YEAR = 0,
//     WIFI_JSON_T2_MONTH,
//     WIFI_JSON_T2_DAY,

//     WIFI_JSON_DATE_YMD_MAX
// }E_WIFI_JSON_DATE_YMD_T;

// // JSON Value Def
// typedef struct{
// 	U8 u8JsonDateLD[WIFI_JSON_DATE_YMDHM_MAX]; // YY MM DD HH MM
// 	U8 u8JsonDateND[WIFI_JSON_DATE_YMDHM_MAX]; // YY MM DD HH MM
// } WIFI_JSON_DATE_YMDHM_T;
// typedef struct{
// 	U8 u8JsonDateLD[WIFI_JSON_DATE_YMD_MAX]; // YY MM DD HH MM
// 	U8 u8JsonDateND[WIFI_JSON_DATE_YMD_MAX]; // YY MM DD HH MM
// } WIFI_JSON_DATE_YMD_T;

// typedef struct{
// 	WIFI_JSON_DATE_YMD_T 	Date_YMD;

// 	I16 i16JsonSEQ;
// 	I16 i16JsonMembership;
// 	I16 i16JsonRemain;
// } WIFI_JSON_SUPPLY_T;

// typedef struct{
// 	I16 i16JsonSavedPlasticBottles;
// 	I16 i16JsonCarbonSavings;
// 	I16 i16JsonMatureCarbonTrees;
// } WIFI_JSON_ENVIRONMENT_T;
// typedef struct
// {
//     WIFI_JSON_DATE_YMDHM_T  UV_Faucet;
// 	WIFI_JSON_SUPPLY_T		Supply[WIFI_JSON_SUPPLY_KEY_MAX];
// 	WIFI_JSON_ENVIRONMENT_T Environment;

// } WIFI_JSON_VALUE_T;

// typedef struct
// {
//     E_WIFI_JSON_KEY_T		Id;
// 	I16						*i16data;

// } WIFI_JSON_TABLE_T;

// // JSON Struct
// JSONObject JsonObjectDepth_1; 
// JSONObject JsonObjectDepth_2;
// JSONArray JsonArray; 
// JSONOArrayValue JsonArrayValue;

#if (USER_USE_A2021_SAPINFO == 1)


#endif

//Event Check
// #define EventCheckSize  (2)  // Func, Err
enum{ 
    WIFI_EVENT_CHECK_FUNC = 0,
    WIFI_EVENT_CHECK_ERR,

    WIFI_EVENT_CHECK_MAX
};


void UserWriteEep ( U16 mu8Addr, U8 mu8Val );
U8 UserReadEep ( U16 mu8Addr );
void UserBuzzSound ( U16 mu16Buzz );

U8 GetUserSystemStatus ( U8 mu8StatusType );
void SetUserSystemStatus ( U8 mu8StatusType, U8 mu8Value );

U16 GetUserSystemError ( U16 mu16Err );
U16 GetUserSystemFunction ( U16 mu16Func );
U32 GetUserSystemRamMonitor ( U16 mu16Func, U16 mLen);
I16 GetUserSystemSensor ( U16 mu16Sen );
U16 GetUserSystemPart ( U16 mu16Part );
U16 GetUserSystemPara ( U16 mu16Para );
U32 GetUserSystemAccumulate ( U16 mu16Acc );

void SetUserSystemFunction ( U16 mu16Func, U16 mData );
void SetUserSystemDiagnosis ( U16 mu16DR, I16 mData );
void SetUserSystemRamMonitor (__near U16 mu16Func, I8 *mData );

void SetUserSystemStatusData ( U8 mu8StatusType );

void ClearUserSystemData ( void );
void ClearUserSystemDataA1010 ( void );
void ClearUserSystemDataA1020 ( void );
void SetUserSystemDisplay ( U8 mu8Display );
// void SetUserSystemFOTA ( void );

void SetUserSystemTime ( U16 mYear, U16 mMonth, U16 mDate, U16 mHour, U16 mMin, U16 mSec, U16 mDay );

void SetUserSystemJson (U8 mu8JsonKey);
void SetUserSystemJsonObject (  U16 mu16Info, I8 *pBuf );

U16 GetFilterDayData (U16 mu16Data);
I16 GetFilterData (U16 mu16SensorDataFilter, U16 mu16FilterTotalUsage);

void SetUserSystemRamWriteStatus ( U16 mu16Address );
U16 GetUserSystemRamWriteStatus ( U16 mu16Address );

void SystemFunctionEventCheck(void);

#endif


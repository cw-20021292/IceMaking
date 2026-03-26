
/*******************************************************************************
&Description :
    A1030 ~ A103x
    Error Table

&Histiry :
    ShinHM 2021.04.13 update
    SSG 2023.05.24 update
*******************************************************************************/


/******************************************************************************/
/***** Header *****************************************************************/
/******************************************************************************/
#include "WIFI_Common.h"
#include "WIFI_DefUser.h"
#include "WIFI_SetCommon.h"
#include "WIFI_TxForm.h"
#include "WIFI_SetErrorData.h"


/******************************************************************************/
/***** Static Function ********************************************************/
/******************************************************************************/
static void EvtWifiErr ( U16 mId, I8 *pBuf );


/******************************************************************************/
/***** Table ******************************************************************/
/******************************************************************************/
#ifdef MODEL_NO_1
static const WifiTxFuncList_T WifiErrorList[] =
{   /*  ID                                  Function                */
    // {   WIFI_ERROR_0001_LOW_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0002_HIGH_LEVEL,         NULL,           NULL    },
    // {   WIFI_ERROR_0003_COMPLEX_LEVEL,      NULL,           NULL    },
    // {   WIFI_ERROR_0004_FEED_VALVE,         NULL,           NULL    },
    // {   WIFI_ERROR_0005_LEAK_WATER,         NULL,           NULL    },
    // {   WIFI_ERROR_0006_HOTIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_0007_HOTOUT_TEMP,        NULL,           NULL    },
    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0009_NATURAL_TEMP,       NULL,           NULL    },
    // {   WIFI_ERROR_000A_TDSIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000B_TDSOUT_TEMP,        NULL,           NULL    },
    // {   WIFI_ERROR_000C_BLDC_COMP,          NULL,           NULL    },
    // {   WIFI_ERROR_000D_STERILIZE_TRAY,     NULL,           NULL    },
    // {   WIFI_ERROR_000E_DRAIN_PUMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000F_STERILIZE_STATE,    NULL,           NULL    },
    // {   WIFI_ERROR_0010_HOTDRAIN_CLOSE,     NULL,           NULL    },
    // {   WIFI_ERROR_0011_TDSIN_SENSOR,       NULL,           NULL    },
    // {   WIFI_ERROR_0012_TDSOUT_SENSOR,      NULL,           NULL    },
    // {   WIFI_ERROR_0013_EVA_TEMP,           NULL,           NULL    },
    // {   WIFI_ERROR_0014_ICE_MOTOR,          NULL,           NULL    },
    // {   WIFI_ERROR_0015_COLD_PUMP,          NULL,           NULL    },
    {   WIFI_ERROR_0016_COLD_LEVEL,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0017_SPARKLING_PUMP,     NULL,           NULL    },
    // {   WIFI_ERROR_0018_TEM_TEMP,           NULL,           NULL    },
    {   WIFI_ERROR_0019_STOP_WATER,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001A_TEM_OPERATION,      NULL,           NULL    },
    // {   WIFI_ERROR_001B_STOP_HOTWATER,      NULL,           NULL    },
    // {   WIFI_ERROR_001C_LEAK_FLOW,          NULL,           NULL    },
    {   WIFI_ERROR_001D_LEAK_SENSOR,        EvtWifiErr,     NULL    },
    {   WIFI_ERROR_001E_HOT_OVER,           EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001F_HEATER_SENSOR,      NULL,           NULL    },
    {   WIFI_ERROR_0020_ROOM_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0021_MICRO_SW_DETECT,    NULL,           NULL    },
    // {   WIFI_ERROR_0022_MICRO_SW_MOVE,      NULL,           NULL    },
    // {   WIFI_ERROR_0023_ICE_TRAY_IN,        NULL,           NULL    },
    // {   WIFI_ERROR_0024_COLD_TEMP_UP,       NULL,           NULL    },
    // {   WIFI_ERROR_0025_COLD_TEMP_DOWN,     NULL,           NULL    },
    {   WIFI_ERROR_0026_HOT_TANK_TEMP,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0027_HOT_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0028_ICE_SHAFT_LEVEL,    NULL,           NULL    },
    // {   WIFI_ERROR_0029_BLDC_STATUS,        NULL,           NULL    },
    // {   WIFI_ERROR_002A_STIRRING_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002B_COMP_OUT_TEMP,      NULL,           NULL    },
    // {   WIFI_ERROR_002C_STERILIZE_MODULE,   NULL,           NULL    },
    // {   WIFI_ERROR_002D_UV_OPERATION,       NULL,           NULL    },
    // {   WIFI_ERROR_002E_OUT_TRAY_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002F_PRESSURE_SENSOR,    NULL,           NULL    }
    {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0035_UV_ICE_TANK1,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0036_UV_ICE_TANK2,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0037_UV_ICE_TRAY,        EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0038_UV_EXTRACT,         NULL,           NULL    },
    // {   WIFI_ERROR_0039_UV_ICE_EXTRACT,     NULL,           NULL    },

};

static const WifiTxFuncList_T WifiErrorListCp[] =
{   /*  ID                                  Function                */

    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },

};
#endif

#ifdef MODEL_NO_2
static const WifiTxFuncList_T WifiErrorList[] =
{   /*  ID                                  Function                */
    // {   WIFI_ERROR_0001_LOW_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0002_HIGH_LEVEL,         NULL,           NULL    },
    // {   WIFI_ERROR_0003_COMPLEX_LEVEL,      NULL,           NULL    },
    // {   WIFI_ERROR_0004_FEED_VALVE,         NULL,           NULL    },
    // {   WIFI_ERROR_0005_LEAK_WATER,         NULL,           NULL    },
    // {   WIFI_ERROR_0006_HOTIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_0007_HOTOUT_TEMP,        NULL,           NULL    },
    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0009_NATURAL_TEMP,       NULL,           NULL    },
    // {   WIFI_ERROR_000A_TDSIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000B_TDSOUT_TEMP,        NULL,           NULL    },
    // {   WIFI_ERROR_000C_BLDC_COMP,          NULL,           NULL    },
    // {   WIFI_ERROR_000D_STERILIZE_TRAY,     NULL,           NULL    },
    // {   WIFI_ERROR_000E_DRAIN_PUMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000F_STERILIZE_STATE,    NULL,           NULL    },
    // {   WIFI_ERROR_0010_HOTDRAIN_CLOSE,     NULL,           NULL    },
    // {   WIFI_ERROR_0011_TDSIN_SENSOR,       NULL,           NULL    },
    // {   WIFI_ERROR_0012_TDSOUT_SENSOR,      NULL,           NULL    },
    // {   WIFI_ERROR_0013_EVA_TEMP,           NULL,           NULL    },
    // {   WIFI_ERROR_0014_ICE_MOTOR,          NULL,           NULL    },
    // {   WIFI_ERROR_0015_COLD_PUMP,          NULL,           NULL    },
    // {   WIFI_ERROR_0016_COLD_LEVEL,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0017_SPARKLING_PUMP,     NULL,           NULL    },
    // {   WIFI_ERROR_0018_TEM_TEMP,           NULL,           NULL    },
    // {   WIFI_ERROR_0019_STOP_WATER,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001A_TEM_OPERATION,      NULL,           NULL    },
    // {   WIFI_ERROR_001B_STOP_HOTWATER,      NULL,           NULL    },
    // {   WIFI_ERROR_001C_LEAK_FLOW,          NULL,           NULL    },
    // {   WIFI_ERROR_001D_LEAK_SENSOR,        EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001E_HOT_OVER,           EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001F_HEATER_SENSOR,      NULL,           NULL    },
    // {   WIFI_ERROR_0020_ROOM_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0021_MICRO_SW_DETECT,    NULL,           NULL    },
    // {   WIFI_ERROR_0022_MICRO_SW_MOVE,      NULL,           NULL    },
    // {   WIFI_ERROR_0023_ICE_TRAY_IN,        NULL,           NULL    },
    // {   WIFI_ERROR_0024_COLD_TEMP_UP,       NULL,           NULL    },
    // {   WIFI_ERROR_0025_COLD_TEMP_DOWN,     NULL,           NULL    },
    // {   WIFI_ERROR_0026_HOT_TANK_TEMP,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0027_HOT_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0028_ICE_SHAFT_LEVEL,    NULL,           NULL    },
    // {   WIFI_ERROR_0029_BLDC_STATUS,        NULL,           NULL    },
    // {   WIFI_ERROR_002A_STIRRING_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002B_COMP_OUT_TEMP,      NULL,           NULL    },
    // {   WIFI_ERROR_002C_STERILIZE_MODULE,   NULL,           NULL    },
    // {   WIFI_ERROR_002D_UV_OPERATION,       NULL,           NULL    },
    // {   WIFI_ERROR_002E_OUT_TRAY_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002F_PRESSURE_SENSOR,    NULL,           NULL    }
    // {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0035_UV_ICE_TANK1,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0036_UV_ICE_TANK2,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0037_UV_ICE_TRAY,        EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0038_UV_EXTRACT,         NULL,           NULL    },
    // {   WIFI_ERROR_0039_UV_ICE_EXTRACT,     NULL,           NULL    },
};

static const WifiTxFuncList_T WifiErrorListCp[] =
{   /*  ID                                  Function                */

    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },

};
#endif

#ifdef MODEL_NO_3
static const WifiTxFuncList_T WifiErrorList[] =
{   /*  ID                                  Function                */
    // {   WIFI_ERROR_0001_LOW_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0002_HIGH_LEVEL,         NULL,           NULL    },
    // {   WIFI_ERROR_0003_COMPLEX_LEVEL,      NULL,           NULL    },
    // {   WIFI_ERROR_0004_FEED_VALVE,         NULL,           NULL    },
    // {   WIFI_ERROR_0005_LEAK_WATER,         NULL,           NULL    },
    // {   WIFI_ERROR_0006_HOTIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_0007_HOTOUT_TEMP,        NULL,           NULL    },
    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0009_NATURAL_TEMP,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_000A_TDSIN_TEMP,         EvtWifiErr,     NULL    },
    {   WIFI_ERROR_000B_TDSOUT_TEMP,        EvtWifiErr,     NULL    },
    {   WIFI_ERROR_000C_BLDC_COMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_000D_STERILIZE_TRAY,     NULL,           NULL    },
    {   WIFI_ERROR_000E_DRAIN_PUMP,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_000F_STERILIZE_STATE,    NULL,           NULL    },
    // {   WIFI_ERROR_0010_HOTDRAIN_CLOSE,     NULL,           NULL    },
    {   WIFI_ERROR_0011_TDSIN_SENSOR,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0012_TDSOUT_SENSOR,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0013_EVA_TEMP,           NULL,           NULL    },
    // {   WIFI_ERROR_0014_ICE_MOTOR,          NULL,           NULL    },
    // {   WIFI_ERROR_0015_COLD_PUMP,          NULL,           NULL    },
    {   WIFI_ERROR_0016_COLD_LEVEL,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0017_SPARKLING_PUMP,     NULL,           NULL    },
    // {   WIFI_ERROR_0018_TEM_TEMP,           NULL,           NULL    },
    {   WIFI_ERROR_0019_STOP_WATER,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001A_TEM_OPERATION,      NULL,           NULL    },
    // {   WIFI_ERROR_001B_STOP_HOTWATER,      NULL,           NULL    },
    // {   WIFI_ERROR_001C_LEAK_FLOW,          NULL,           NULL    },
    {   WIFI_ERROR_001D_LEAK_SENSOR,        EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001E_HOT_OVER,           EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001F_HEATER_SENSOR,      NULL,           NULL    },
    {   WIFI_ERROR_0020_ROOM_TEMP,          EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0021_MICRO_SW_DETECT,    EvtWifiErr,     NULL    }, // ??им?
    {   WIFI_ERROR_0022_MICRO_SW_MOVE,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0023_ICE_TRAY_IN,        NULL,           NULL    },
    // {   WIFI_ERROR_0024_COLD_TEMP_UP,       NULL,           NULL    },
    // {   WIFI_ERROR_0025_COLD_TEMP_DOWN,     NULL,           NULL    },
    {   WIFI_ERROR_0026_HOT_TANK_TEMP,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0027_HOT_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0028_ICE_SHAFT_LEVEL,    NULL,           NULL    },
    // {   WIFI_ERROR_0029_BLDC_STATUS,        EvtWifiErr,     NULL    }, // ?вп??
    // {   WIFI_ERROR_002A_STIRRING_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002B_COMP_OUT_TEMP,      NULL,           NULL    },
    // {   WIFI_ERROR_002C_STERILIZE_MODULE,   NULL,           NULL    },
    // {   WIFI_ERROR_002D_UV_OPERATION,       NULL,           NULL    },
    // {   WIFI_ERROR_002E_OUT_TRAY_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002F_PRESSURE_SENSOR,    NULL,           NULL    },
    {   WIFI_ERROR_0030_TDS_REMOVE,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0033_UV_ROOM_TANK,       NULL,           NULL    },
    {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0035_UV_ICE_TANK1,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0036_UV_ICE_TANK2,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0037_UV_ICE_TRAY,        EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0038_UV_EXTRACT,         NULL,           NULL    },
    // {   WIFI_ERROR_0039_UV_ICE_EXTRACT,     NULL,           NULL    },
    // {   WIFI_ERROR_003A_UV_ICE_TRAY2,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_003B_MICRO_SW_MOVE2,     EvtWifiErr,     NULL    },
    {   WIFI_ERROR_003C_ROOM_TEMP_OH,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_003F_NATURAL2_TEMP,       EvtWifiErr,     NULL    },
    //{   WIFI_ERROR_0040_TRAY_IN_TEMP,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0045_UV_ICE_TANK3,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0046_DARIN_CLOSE,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0047_TDS_IN_WATER,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0048_COLD_TEMP_OC,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_0049_BLDC_STATUS1,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_004A_BLDC_STATUS2,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_004B_BLDC_STATUS3,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_004C_BLDC_STATUS4,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_004D_BLDC_STATUS5,       EvtWifiErr,     NULL    },
    {   WIFI_ERROR_004E_BLDC_STATUS6,       EvtWifiErr,     NULL    },

};

static const WifiTxFuncList_T WifiErrorListCp[] =
{   /*  ID                                  Function                */

    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },

};
#endif

#ifdef MODEL_NO_4
static const WifiTxFuncList_T WifiErrorList[] =
{   /*  ID                                  Function                */
    // {   WIFI_ERROR_0001_LOW_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0002_HIGH_LEVEL,         NULL,           NULL    },
    // {   WIFI_ERROR_0003_COMPLEX_LEVEL,      NULL,           NULL    },
    // {   WIFI_ERROR_0004_FEED_VALVE,         NULL,           NULL    },
    // {   WIFI_ERROR_0005_LEAK_WATER,         NULL,           NULL    },
    // {   WIFI_ERROR_0006_HOTIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_0007_HOTOUT_TEMP,        NULL,           NULL    },
    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0009_NATURAL_TEMP,       NULL,           NULL    },
    // {   WIFI_ERROR_000A_TDSIN_TEMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000B_TDSOUT_TEMP,        NULL,           NULL    },
    // {   WIFI_ERROR_000C_BLDC_COMP,          NULL,           NULL    },
    // {   WIFI_ERROR_000D_STERILIZE_TRAY,     NULL,           NULL    },
    // {   WIFI_ERROR_000E_DRAIN_PUMP,         NULL,           NULL    },
    // {   WIFI_ERROR_000F_STERILIZE_STATE,    NULL,           NULL    },
    // {   WIFI_ERROR_0010_HOTDRAIN_CLOSE,     NULL,           NULL    },
    // {   WIFI_ERROR_0011_TDSIN_SENSOR,       NULL,           NULL    },
    // {   WIFI_ERROR_0012_TDSOUT_SENSOR,      NULL,           NULL    },
    // {   WIFI_ERROR_0013_EVA_TEMP,           NULL,           NULL    },
    // {   WIFI_ERROR_0014_ICE_MOTOR,          NULL,           NULL    },
    // {   WIFI_ERROR_0015_COLD_PUMP,          NULL,           NULL    },
    {   WIFI_ERROR_0016_COLD_LEVEL,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0017_SPARKLING_PUMP,     NULL,           NULL    },
    // {   WIFI_ERROR_0018_TEM_TEMP,           NULL,           NULL    },
    {   WIFI_ERROR_0019_STOP_WATER,         EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001A_TEM_OPERATION,      NULL,           NULL    },
    // {   WIFI_ERROR_001B_STOP_HOTWATER,      NULL,           NULL    },
    // {   WIFI_ERROR_001C_LEAK_FLOW,          NULL,           NULL    },
    {   WIFI_ERROR_001D_LEAK_SENSOR,        EvtWifiErr,     NULL    },
    {   WIFI_ERROR_001E_HOT_OVER,           EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_001F_HEATER_SENSOR,      NULL,           NULL    },
    {   WIFI_ERROR_0020_ROOM_TEMP,          EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0021_MICRO_SW_DETECT,    NULL,           NULL    },
    // {   WIFI_ERROR_0022_MICRO_SW_MOVE,      NULL,           NULL    },
    // {   WIFI_ERROR_0023_ICE_TRAY_IN,        NULL,           NULL    },
    // {   WIFI_ERROR_0024_COLD_TEMP_UP,       NULL,           NULL    },
    // {   WIFI_ERROR_0025_COLD_TEMP_DOWN,     NULL,           NULL    },
    {   WIFI_ERROR_0026_HOT_TANK_TEMP,      EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0027_HOT_LEVEL,          NULL,           NULL    },
    // {   WIFI_ERROR_0028_ICE_SHAFT_LEVEL,    NULL,           NULL    },
    // {   WIFI_ERROR_0029_BLDC_STATUS,        NULL,           NULL    },
    // {   WIFI_ERROR_002A_STIRRING_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002B_COMP_OUT_TEMP,      NULL,           NULL    },
    // {   WIFI_ERROR_002C_STERILIZE_MODULE,   NULL,           NULL    },
    // {   WIFI_ERROR_002D_UV_OPERATION,       NULL,           NULL    },
    // {   WIFI_ERROR_002E_OUT_TRAY_MOTOR,     NULL,           NULL    },
    // {   WIFI_ERROR_002F_PRESSURE_SENSOR,    NULL,           NULL    }
    {   WIFI_ERROR_0034_UV_COLD_TANK,       EvtWifiErr,     NULL    },
    // {   WIFI_ERROR_0035_UV_ICE_TANK,        NULL,           NULL    },
    // {   WIFI_ERROR_0036_UV_ICE_TRAY,        NULL,           NULL    },
    // {   WIFI_ERROR_0037_UV_EXTRACT,         NULL,           NULL    },
    // {   WIFI_ERROR_0038_UV_ICE_EXTRACT,     NULL,           NULL    },
};

static const WifiTxFuncList_T WifiErrorListCp[] =
{   /*  ID                                  Function                */

    {   WIFI_ERROR_0008_COLD_TEMP,          EvtWifiErr,     NULL    },

};

#endif

#define SZ_ER_LIST ( sizeof(WifiErrorList) / sizeof(WifiTxFuncList_T) )


/******************************************************************************/
/***** Global Function ********************************************************/
/******************************************************************************/
void* GetWifiErrorEventList ( void )
{
    if ( IsUserModelCHP() == TRUE )
    {
        return WifiErrorList;
    }
    else
    {
        return WifiErrorListCp;
    }
}

U16 GetWifiErrorListSize ( void )
{
    return SZ_ER_LIST;
}


/******************************************************************************/
/***** Local Function *********************************************************/
/******************************************************************************/
static void EvtWifiErr ( U16 mId, I8 *pBuf )
{
    static I8 mai8Buf[LENGTH_WIFI_DATA_ONE];

    _MEMSET_( (void __FAR*) mai8Buf, '\0', sizeof(mai8Buf) );

    ConvertDataHexToAscii( TYPE_ERROR_CMD, mId, mai8Buf );

    far_sprintf_s( pBuf, 0, mai8Buf );
}



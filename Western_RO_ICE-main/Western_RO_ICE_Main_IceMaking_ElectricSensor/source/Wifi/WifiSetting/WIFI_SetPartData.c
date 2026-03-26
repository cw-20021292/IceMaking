
/*******************************************************************************
&Description :
    A1080 ~ A108x
    A1090 ~ A109x
    Part Table

&Histiry :
    ShinHM 2021.04.14 update
    SSG 2023.05.24 update
*******************************************************************************/


/******************************************************************************/
/***** Header *****************************************************************/
/******************************************************************************/
#include "WIFI_Common.h"
#include "WIFI_DefUser.h"
#include "WIFI_SetCommon.h"
#include "WIFI_TxForm.h"
#include "WIFI_SetPartData.h"


/******************************************************************************/
/***** Static Function ********************************************************/
/******************************************************************************/
static void EvtWifiTxPart ( U16 mId, I8 *pBuf );


/******************************************************************************/
/***** Table ******************************************************************/
/******************************************************************************/


#ifdef MODEL_NO_3
static const WifiTxFuncList_T WifiPartList[] =
{
    {   WIFI_PART_0000_VALVE_FEED,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0001_VALVE_NOS,                       EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0002_VALVE_HOT_OUT,                   EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0003_VALVE_PURE_OUT,                  EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0004_VALVE_COLD_OUT,                  EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0005_VALVE_CP_OUT,                    NULL,               NULL    },
    // {   WIFI_PART_0006_VALVE_CHP_OUT,                   NULL,               NULL    },
    // {   WIFI_PART_0007_VALVE_PURE_IN,                   NULL,               NULL    },
    // {   WIFI_PART_0008_VALVE_HOT_AIR,                   NULL,               NULL    },
    {   WIFI_PART_0009_VALVE_HOT_IN,                    EvtWifiTxPart,               NULL    },
    // {   WIFI_PART_000A_VALVE_HOT_DRAIN,                 NULL,               NULL    },
    {   WIFI_PART_000B_VALVE_COLD_AIR,                  EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_000C_VALVE_COLD_IN,                   NULL,               NULL    },
    {   WIFI_PART_000D_VALVE_COLD_DRAIN,                EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_000E_VALVE_ICE_STORAGE_IN,            NULL,               NULL    },
    // {   WIFI_PART_000F_VALVE_PRESSURE_IN,               NULL,               NULL    },
    // {   WIFI_PART_0010_VALVE_PRESSURE_DRAIN,            NULL,               NULL    },
    // {   WIFI_PART_0011_VALVE_STERILIZE,                 NULL,               NULL    },
    // {   WIFI_PART_0012_VALVE_DRAIN_NOS,                 NULL,               NULL    },
    // {   WIFI_PART_0013_VALVE_ION_CHANGE,                NULL,               NULL    },
    // {   WIFI_PART_0014_VALVE_INNO_CENCE,                NULL,               NULL    },
    {   WIFI_PART_0015_VALVE_ICE_TRAY_IN,               EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0016_VALVE_COLD_ROTATE,               NULL,               NULL    },
    // {   WIFI_PART_0017_VALVE_EW_IN,                     NULL,               NULL    },
    {   WIFI_PART_0018_VALVE_FLUSHING,                  EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0019_VALVE_RO_FLUSHING,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_001A_VALVE_HOT_OVER_HEAT,             EvtWifiTxPart,      NULL    },
    {   WIFI_PART_001B_VALVE_HOT_STERILIZE_L,           EvtWifiTxPart,      NULL    },
    {   WIFI_PART_001C_VALVE_HOT_STERILIZE_R,           EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_001D_VALVE_BLUE_E,                    NULL,               NULL    },
    // {   WIFI_PART_001E_VALVE_TANK_DRAIN,                NULL,               NULL    },
    {   WIFI_PART_001F_VALVE_FLUSHING_NOS,              EvtWifiTxPart,      NULL    },

    // {   WIFI_PART_0100_LEVEL_COLD_OVER,                 NULL,               NULL    },
    {   WIFI_PART_0101_LEVEL_COLD_HIGH,                 EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0102_LEVEL_COLD_MID,                  NULL,               NULL    },
    {   WIFI_PART_0103_LEVEL_COLD_LOW,                  EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0104_LEVEL_ICE_STORAGE_HIGH,          NULL,               NULL    },
    // {   WIFI_PART_0105_LEVEL_PURE_OVER,                 NULL,               NULL    },
    // {   WIFI_PART_0106_LEVEL_PURE_HIGH,                 NULL,               NULL    },
    // {   WIFI_PART_0107_LEVEL_PURE_MID,                  NULL,               NULL    },
    // {   WIFI_PART_0108_LEVEL_PURE_LOW,                  NULL,               NULL    },
    // {   WIFI_PART_0109_LEVEL_HOT_HIGH,                  NULL,               NULL    },
    // {   WIFI_PART_010A_LEVEL_DRAIN_OVER,                NULL,               NULL    },
    {   WIFI_PART_010B_LEVEL_DRAIN_HIGH,                EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_010C_LEVEL_DRAIN_MID,                 NULL,               NULL    },
    {   WIFI_PART_010D_LEVEL_DRAIN_LOW,                 EvtWifiTxPart,      NULL    },
    {   WIFI_PART_010F_LEVEL_COLD_ERROR,                 EvtWifiTxPart,      NULL    },

    // {   WIFI_PART_0200_COLD_COMP,                       EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0201_COLD_BLDC,                       EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0202_COLD_TEM,                        NULL,               NULL    },
    // {   WIFI_PART_0203_COLD_TEM_TEMP,                   NULL,               NULL    },
    {   WIFI_PART_0204_COLD_FAN,                        EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0205_COLD_STIRRING_MOTOR,             NULL,               NULL    },
    {   WIFI_PART_0206_COLD_TEMP_1,                     EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0207_COLD_TEMP_2,                     NULL,               NULL    },
    {   WIFI_PART_0208_COLD_ROOM_TEMP,                  EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0209_COLD_ROTATE_PUMP,                NULL,               NULL    },
    // {   WIFI_PART_020A_COLD_FLOW_MOTOR,                 NULL,               NULL    },
    // {   WIFI_PART_020B_COLD_TARGET_TEMP_TIME,           NULL,               NULL    },
    // {   WIFI_PART_020C_COLD_TANK_DRAIN_PUMP,            NULL,               NULL    },
    {   WIFI_PART_020D_COLD_ROOM_TEMP2,                 EvtWifiTxPart,      NULL    },
    {   WIFI_PART_020E_COLD_STOP_ERROR,                 EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0210_COLD_BLDC_ERROR,                 EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0211_COLD_DRAIN_CLOSE,                EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0214_COLD_BLDC1,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0215_COLD_BLDC2,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0216_COLD_BLDC3,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0217_COLD_BLDC4,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0218_COLD_BLDC5,                      EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0219_COLD_BLDC6,                      EvtWifiTxPart,      NULL    },

    // {   WIFI_PART_0300_HOT_TANK_HEATER,                 EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0301_HOT_TEMP,                        EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0302_HOT_INSTANT_HEATER_1,            NULL,               NULL    },
    // {   WIFI_PART_0303_HOT_INSTANT_HEATER_2,            NULL,               NULL    },
    // {   WIFI_PART_0304_HOT_FLOW_MOTOR,                  NULL,               NULL    },
    // {   WIFI_PART_0305_HOT_TEMP_IN,                     NULL,               NULL    },
    // {   WIFI_PART_0306_HOT_TEMP_OUT,                    NULL,               NULL    },
    // {   WIFI_PART_0307_HOT_HEATER_TEMP,                 NULL,               NULL    },
    {   WIFI_PART_0308_HOT_TARGET_TEMP_TIME,            EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0309_HOT_BAR_PRESSURE,                EvtWifiTxPart,      NULL    },

    // {   WIFI_PART_0400_SENSOR_PRESSURE_1,               NULL,               NULL    },
    // {   WIFI_PART_0401_SENSOR_PRESSURE_2,               NULL,               NULL    },
    {   WIFI_PART_0402_SENSOR_LEAK,                     EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0403_SENSOR_FLOW,                     EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0404_SENSOR_FLOW_REED,                NULL,               NULL    },
    {   WIFI_PART_0405_SENSOR_FILTER_REED,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0406_SENSOR_FILTER_SW_1,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0407_SENSOR_FILTER_SW_2,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0408_SENSOR_FILTER_SW_3,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0409_SENSOR_TANK_REED,                EvtWifiTxPart,      NULL    },

    {   WIFI_PART_040C_SENSOR_BLUE_E_FLOW,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0412_SENSOR_CLEANING_SW,              EvtWifiTxPart,      NULL    },

    // {   WIFI_PART_0500_STER_CSI_MODULE,                 NULL,               NULL    },
    // {   WIFI_PART_0501_STER_UV_FAUCET,                  NULL,               NULL    },
    // {   WIFI_PART_0502_STER_UV_FAUCET_ICE,              NULL,               NULL    },
    {   WIFI_PART_0503_STER_UV_ICE_TANK1,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0504_STER_UV_ICE_TRAY,                EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0505_STER_UV_COLD_TANK,               EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0506_STER_UV_ICE_TRAY2,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0508_STER_UV_ICE_TANK2,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0509_STER_UV_ERROR_E74,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_050B_STER_UV_ERROR_E75,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_050C_STER_UV_ERROR_E79,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_050D_STER_UV_ERROR_E76,               EvtWifiTxPart,      NULL    },

    {   WIFI_PART_0600_TDS_TEMP_IN,                     EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0601_TDS_TEMP_OUT,                    EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0602_TDS_SENSOR_IN,                   EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0603_TDS_SENSOR_OUT,                  EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0604_TDS_CLEARANCE,                   EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0605_TDS_IN_ERROR_E92,                EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0606_TDS_OUT_ERROR_E93,               EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0607_TDS_IN_WATER_E98,                EvtWifiTxPart,      NULL    },
    
    // {   WIFI_PART_0700_FAUCET_REED_1,                   NULL,               NULL    },
    // {   WIFI_PART_0701_FAUCET_REED_2,                   NULL,               NULL    },
    // {   WIFI_PART_0702_FAUCET_CUP_SENSOR,               NULL,               NULL    },
    // {   WIFI_PART_0703_FAUCET_MOTOR,                    NULL,               NULL    },

    {   WIFI_PART_0800_ICE_PURE_TEMP,                   EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0801_ICE_FULL_SENSOR,                 EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0802_ICE_SWING_BAR,                   EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0803_ICE_TRAY_AC,                     NULL,               NULL    },
    // {   WIFI_PART_0804_ICE_TRAY_STEPMOTOR,              NULL,               NULL    },
    {   WIFI_PART_0805_ICE_TRAY_SENSING_SW,             EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0806_ICE_MOTOR_OUT,                   EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0807_ICE_DOOR_STEPMOTOR,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0808_ICE_COURSE_CHANGE_VV,            EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0809_ICE_HOT_GAS_VV,                  NULL,               NULL    },
    {   WIFI_PART_080A_ICE_DRAIN_PUMP,                  EvtWifiTxPart,      NULL    },
    {   WIFI_PART_080B_ICE_TRAY_PUMP,                   EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_080C_ICE_EVA_TEMP,                    NULL,      NULL    },
    // {   WIFI_PART_080D_ICE_TRAY_IN_TEMP,             EvtWifiTxPart,      NULL    },
    {   WIFI_PART_080E_ICE_DRAIN_ERROR_E60,             EvtWifiTxPart,      NULL    },
    {   WIFI_PART_080F_ICE_TRAY_ERROR_E61,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0810_ICE_TRAY_ERROR_E62,              EvtWifiTxPart,      NULL    },
    {   WIFI_PART_0811_ICE_TRAY_ERROR_E63,              EvtWifiTxPart,      NULL    },

    {   WIFI_PART_0900_EXTRACT_TEMP,                    EvtWifiTxPart,      NULL    },
    // {   WIFI_PART_0901_EXTRACT_BOOST_PUMP,              NULL,      NULL    }
};

static const WifiTxFuncList_T WifiPartListCp[] =
{   /* PART LIST ID                                     Tx Function         Rx Function */
    {   WIFI_PART_0000_VALVE_FEED,                      NULL,               NULL    },

};
#endif


#define SZ_PT_LIST ( sizeof(WifiPartList) / sizeof(WifiTxFuncList_T) )


/******************************************************************************/
/***** Global Function ********************************************************/
/******************************************************************************/
void* GetWifiPartEventList ( void )
{
    if ( IsUserModelCHP() == TRUE )
    {
        return WifiPartList;
    }
    else
    {
        return WifiPartListCp;
    }
}

U16 GetWifiPartListSize ( void )
{
    return SZ_PT_LIST;
}


/******************************************************************************/
/***** Local Function *********************************************************/
/******************************************************************************/
static void EvtWifiTxPart ( U16 mId, I8 *pBuf )
{
    static I8 mai8Buf[LENGTH_WIFI_DATA_ONE];

    _MEMSET_( (void __FAR*) mai8Buf, '\0', sizeof(mai8Buf));

    ConvertDataHexToAscii( TYPE_PART_CMD, mId, mai8Buf );

    far_sprintf_s( pBuf, 0, mai8Buf );
}



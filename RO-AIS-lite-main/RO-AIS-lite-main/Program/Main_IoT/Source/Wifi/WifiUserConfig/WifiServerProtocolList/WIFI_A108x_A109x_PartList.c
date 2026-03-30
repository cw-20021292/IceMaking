    
/*******************************************************************************
&Description :
    A1080 ~ A108x
    A1090 ~ A109x
    Part Table

*******************************************************************************/

/******************************************************************************/
/***** Header *****************************************************************/
/******************************************************************************/
#include "WIFI_A108x_A109x_PartList.h"

/******************************************************************************/
/***** User Header ************************************************************/
/******************************************************************************/
#include "Global_Variable.h"
#include "m_wifi_global_data.h"
#include "port_define.h"
/******************************************************************************/
/***** User Function **********************************************************/
/******************************************************************************/

/******************************************************************************/
/***** Table ******************************************************************/
/******************************************************************************/
/* Protocol List */
static const WifiNormalList_T WifiPartProtocolList[] =
{   /*  API ID        */
    {   WIFI_PART_0000_VALVE_FEED,              TYPE_UNSIGNED   },
    {   WIFI_PART_0001_VALVE_NOS,               TYPE_UNSIGNED   },
    {   WIFI_PART_0002_VALVE_HOT_OUT,           TYPE_UNSIGNED   },
    {   WIFI_PART_0003_VALVE_PURE_OUT,          TYPE_UNSIGNED   },
    {   WIFI_PART_0004_VALVE_COLD_OUT,          TYPE_UNSIGNED   },
    //{   WIFI_PART_000C_VALVE_COLD_IN,           TYPE_UNSIGNED   },
    //{   WIFI_PART_000D_VALVE_COLD_DRAIN,        TYPE_UNSIGNED   },
    //{   WIFI_PART_0012_VALVE_DRAIN_NOS,         TYPE_UNSIGNED   },
    //{   WIFI_PART_0015_VALVE_ICE_TRAY_IN,       TYPE_UNSIGNED   },

    {   WIFI_PART_0105_LEVEL_PURE_OVER,         TYPE_UNSIGNED   },
    {   WIFI_PART_0106_LEVEL_PURE_HIGH,         TYPE_UNSIGNED   },
    {   WIFI_PART_0108_LEVEL_PURE_LOW,          TYPE_UNSIGNED   },
    {   WIFI_PART_010B_LEVEL_DRAIN_HIGH,        TYPE_UNSIGNED   },
    {   WIFI_PART_010D_LEVEL_DRAIN_LOW,         TYPE_UNSIGNED   },
    {   WIFI_PART_0112_LEVEL_LOW_ERROR,         TYPE_UNSIGNED   },
    {   WIFI_PART_0113_LEVEL_HIGH_ERROR,        TYPE_UNSIGNED   },
    {   WIFI_PART_0114_LEVEL_LOGIC_ERROR,       TYPE_UNSIGNED   },
    {   WIFI_PART_0115_LEVEL_FEED_ERROR,        TYPE_UNSIGNED   },

    {   WIFI_PART_0206_COLD_TEMP_1,             TYPE_UNSIGNED   },
    {   WIFI_PART_0208_COLD_ROOM_TEMP,          TYPE_UNSIGNED   },
    {   WIFI_PART_020B_COLD_TARGET_TEMP_TIME,   TYPE_UNSIGNED   },

    {   WIFI_PART_0301_HOT_TEMP,                TYPE_UNSIGNED   },
    {   WIFI_PART_0308_HOT_TARGET_TEMP_TIME,    TYPE_UNSIGNED   },

    {   WIFI_PART_0402_SENSOR_LEAK,             TYPE_UNSIGNED   },
    {   WIFI_PART_0409_SENSOR_TANK_REED,        TYPE_UNSIGNED   },

    {   WIFI_PART_0501_STER_UV_FAUCET,          TYPE_UNSIGNED   },
    {   WIFI_PART_0502_STER_UV_FAUCET_ICE,      TYPE_UNSIGNED   },
    {   WIFI_PART_0503_STER_UV_ICE_TANK1,       TYPE_UNSIGNED   },

    {   WIFI_PART_0800_ICE_PURE_TEMP,           TYPE_UNSIGNED   },
    {   WIFI_PART_0801_ICE_FULL_SENSOR,         TYPE_UNSIGNED   },
    {   WIFI_PART_0802_ICE_SWING_BAR,           TYPE_UNSIGNED   },
    {   WIFI_PART_0805_ICE_TRAY_SENSING_SW,     TYPE_UNSIGNED   },
    {   WIFI_PART_0807_ICE_DOOR_STEPMOTOR,      TYPE_UNSIGNED   },
    {   WIFI_PART_0808_ICE_COURSE_CHANGE_VV,    TYPE_UNSIGNED   },
    {   WIFI_PART_080A_ICE_DRAIN_PUMP,          TYPE_UNSIGNED   },
    {   WIFI_PART_080E_ICE_DRAIN_ERROR_E60,     TYPE_UNSIGNED   },
    {   WIFI_PART_080F_ICE_TRAY_ERROR_E61,      TYPE_UNSIGNED   },
    {   WIFI_PART_0810_ICE_TRAY_ERROR_E62,      TYPE_UNSIGNED   },
    {   WIFI_PART_0811_ICE_TRAY_ERROR_E63,      TYPE_UNSIGNED   }
};

#define SZ_PART_EVENT_LIST    (sizeof(WifiPartProtocolList)/sizeof(WifiNormalList_T))

void* GetWifiPartDataEventList ( void )
{
    if (IsUserModelType() == Model_0)
    {
        return WifiPartProtocolList;
    }
    else
    {

    }
}

U16 GetWifiPartEventListSize ( void )
{
    if (IsUserModelType() == Model_0)
    {
        return SZ_PART_EVENT_LIST;
    }
    else
    {

    }
}

/* [User Part Data] Product -> Server */
U16 GetUserSystemPart ( U16 mu16Part )
{
    U16 mu16Data = 9999U;
    switch ( mu16Part )
    {
        case WIFI_PART_0000_VALVE_FEED :       /* ID */
            mu16Data = U16_FEED_1_1_DC_Current_PART_0000;
            initial_each_self_data( DC_LOAD_1__FEED_VALVE );
        break;

        case WIFI_PART_0001_VALVE_NOS : 

            mu16Data = U16_NOS_1_2_DC_Current_PART_0001;
            initial_each_self_data( DC_LOAD_2__NOS_VALVE );

        break;
        case WIFI_PART_0002_VALVE_HOT_OUT : 

            mu16Data = U16_HOT_OUT_3_3_DC_Current_PART_0002;
            initial_each_self_data( DC_LOAD_3__HOT_OUT_VALVE );

        break;
        case WIFI_PART_0003_VALVE_PURE_OUT : 

            mu16Data = U16_PURE_OUT_3_2_DC_Current_PART_0003;
            initial_each_self_data( DC_LOAD_4__PURE_OUT_VALVE );

        break;
        case WIFI_PART_0004_VALVE_COLD_OUT : 

            mu16Data = U16_COLD_OUT_3_1_DC_Current_PART_0004;
            initial_each_self_data( DC_LOAD_5__COLD_OUT_VALVE );

        break;
#if 0
        case WIFI_PART_000C_VALVE_COLD_IN : 

            mu16Data = U16_COLD_IN_6_2_DC_Current_PART_000C;
            initial_each_self_data( DC_LOAD_6__COLD_IN_VALVE );

        break;
        case WIFI_PART_000D_VALVE_COLD_DRAIN : 

            mu16Data = U16_COLD_DRAIN_3_4_DC_Current_PART_000D;
            initial_each_self_data( DC_LOAD_7__COLD_DRAIN_VALVE );

        break;
		case WIFI_PART_0012_VALVE_DRAIN_NOS : 

            mu16Data = U16_DRAIN_NOS_DC_Current_PART_0012;
            initial_each_self_data( DC_LOAD_8__DRAIN_NOS_VALVE );

        break;
        case WIFI_PART_0015_VALVE_ICE_TRAY_IN : 

            mu16Data = U16_ICE_TRAY_IN_6_1_DC_Current_PART_0015;
            initial_each_self_data( DC_LOAD_9__ICE_TRAY_IN_VALVE );

        break;
#endif
        case WIFI_PART_0105_LEVEL_PURE_OVER : 

            if( pLEVEL_OVERFLOW == SET )
            {
                /*..hui [23-12-21���� 8:12:16] ����..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21���� 8:12:22] �̰���..*/
                mu16Data = 0;
            }

        break;
        case WIFI_PART_0106_LEVEL_PURE_HIGH : 

            if( pLEVEL_PURIFY_HIGH == SET )
            {
                /*..hui [23-12-21���� 8:12:16] ����..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21���� 8:12:22] �̰���..*/
                mu16Data = 0;
            }

        break;
        case WIFI_PART_0108_LEVEL_PURE_LOW : 

            if( pLEVEL_PURIFY_LOW == SET )
            {
                /*..hui [23-12-21���� 8:12:16] ����..*/
                mu16Data = 1;
                //for test
                //mu16Data = 0;
				
            }
            else
            {
                /*..hui [23-12-21���� 8:12:22] �̰���..*/
                mu16Data = 0;
            }

        break;
        case WIFI_PART_010B_LEVEL_DRAIN_HIGH : 

            if( pLEVEL_ICE_DRAIN_HIGH == SET )
            {
                /*..hui [23-12-21���� 8:12:16] ����..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21���� 8:12:22] �̰���..*/
                mu16Data = 0;
            }

        break;
        case WIFI_PART_010D_LEVEL_DRAIN_LOW : 

            if( pLEVEL_ICE_DRAIN_LOW == SET )
            {
                /*..hui [23-12-21���� 8:12:16] ����..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-12-21���� 8:12:22] �̰���..*/
                mu16Data = 0;
            }

        break;
        case WIFI_PART_0112_LEVEL_LOW_ERROR : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0001_LOW_LEVEL);

        break;
        case WIFI_PART_0113_LEVEL_HIGH_ERROR : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0002_HIGH_LEVEL);

        break;
        case WIFI_PART_0114_LEVEL_LOGIC_ERROR : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0003_COMPLEX_LEVEL);

        break;
        case WIFI_PART_0115_LEVEL_FEED_ERROR : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0004_FEED_VALVE);

        break;

        case WIFI_PART_0206_COLD_TEMP_1 : 

            /*..hui [21-9-17���� 1:18:06] �µ����� �����ϰ�� 130���� ������� ��..*/
            if( Bit10_Cold_Temp_Open_Short_Error == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Cold_Temperature_One_Degree;
            }

            break;

        break;
        case WIFI_PART_0208_COLD_ROOM_TEMP : 

            /*..hui [21-9-17���� 1:18:06] �µ����� �����ϰ�� 130���� ������� ��..*/
            if( Bit11_Amb_Temp_Open_Short_Error == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Amb_Temperature_One_Degree;
            }

        break;
        case WIFI_PART_020B_COLD_TARGET_TEMP_TIME : 

            mu16Data = gu16_wifi_cold_target_time_min;

        break;

        case WIFI_PART_0301_HOT_TEMP : 

            /*..hui [21-9-17���� 1:18:06] �µ����� �����ϰ�� 130���� ������� ��..*/
            if( Bit0_Hot_Tank_Temp_Open_Short_Error == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Hot_Tank_Temperature_One_Degree;
            }

        break;
        case WIFI_PART_0308_HOT_TARGET_TEMP_TIME : 

            mu16Data = gu16_wifi_hot_target_time_min;

        break;
        case WIFI_PART_0402_SENSOR_LEAK : 

            /*if( gu16IceMakingADVal >= LEAKAGE_DETECT_AD )*/
            if( Bit3_Leakage_Sensor_Error == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }

        break;
        case WIFI_PART_0409_SENSOR_TANK_REED : 

            if( F_Tank_Cover_Input == SET )
            {
                /*..hui [21-9-9���� 8:31:16] ����..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-9-9���� 8:31:30] ����..*/
                mu16Data = 1;
            }

        break;

        case WIFI_PART_0501_STER_UV_FAUCET : 

            mu16Data = U16_UV_FAUCET_DC_Current_PART_0501;
            initial_each_self_data( DC_LOAD_7__UV_FAUCET );

        break;
        case WIFI_PART_0502_STER_UV_FAUCET_ICE : 

            mu16Data = U16_UV_ICE_FAUCET_DC_Current_PART_0502;
            initial_each_self_data( DC_LOAD_8__UV_ICE_FAUCET );

        break;
        case WIFI_PART_0503_STER_UV_ICE_TANK1 : 

            mu16Data = U16_UV_ICE_TANK_DC_Current_PART_0503;
            initial_each_self_data( DC_LOAD_9__UV_ICE_TANK );

        break;

        case WIFI_PART_0800_ICE_PURE_TEMP : 

            /*..hui [21-9-17���� 1:18:06] �µ����� �����ϰ�� 130���� ������� ��..*/
            if( Bit2_Room_Temp_Open_Short_Error == SET )
            {
                mu16Data = SELF_TEST_SENSOR_ERROR_DATA;
            }
            else
            {
                mu16Data = gu8_Room_Temperature_One_Degree;
            }

        break;
        case WIFI_PART_0801_ICE_FULL_SENSOR : 

            mu16Data = U16_ICE_FULL_SENSOR_PART_0801;

        break;
        case WIFI_PART_0802_ICE_SWING_BAR : 

            mu16Data = U16_SWING_BAR_DC_Current_PART_0802;
            initial_each_self_data( DC_LOAD_10__SWING_BAR );

        break;
        case WIFI_PART_0805_ICE_TRAY_SENSING_SW : 

            if( Bit13_Tray_Micro_SW_Dual_Detect_Error == SET )
            {
                mu16Data = 3;
            }
            else if( Bit14_Tray_Micro_SW_Up_Move_Error == SET )
            {
                mu16Data = 1;
            }
            else if( Bit15_Tray_Micro_SW_Down_Move_Error == SET )
            {
                mu16Data = 2;
            }
            else
            {
                mu16Data = 0;
            }

        break;
        case WIFI_PART_0807_ICE_DOOR_STEPMOTOR : 

            mu16Data = U16_ICE_DOOR_MOTOR_DC_Current_PART_0807;
            initial_each_self_data( DC_LOAD_11__ICE_DOOR_MOTOR );

        break;
        case WIFI_PART_0808_ICE_COURSE_CHANGE_VV : 

            mu16Data = U16_GAS_SWITCH_MOTOR_DC_Current_PART_0808;
            initial_each_self_data( DC_LOAD_12__GAS_SWITCH_MOTOR );

        break;
        case WIFI_PART_080A_ICE_DRAIN_PUMP : 

            mu16Data = U16_DRAIN_PUMP_DC_Current_PART_080A;
            initial_each_self_data( DC_LOAD_13__DRAIN_PUMP );

        break;
        case WIFI_PART_080E_ICE_DRAIN_ERROR_E60 : 
            mu16Data = GetUserSystemError(WIFI_ERROR_000E_DRAIN_PUMP);

        break;
        case WIFI_PART_080F_ICE_TRAY_ERROR_E61 : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0021_MICRO_SW_DETECT);

        break;
        case WIFI_PART_0810_ICE_TRAY_ERROR_E62 : 
            mu16Data = GetUserSystemError(WIFI_ERROR_0022_MICRO_SW_MOVE);

        break;
        case WIFI_PART_0811_ICE_TRAY_ERROR_E63 : 
            mu16Data = GetUserSystemError(WIFI_ERROR_003B_MICRO_SW_MOVE2);

        break;


        default:
		mu16Data = 0xFFFF;
        break;
    }

    return mu16Data;
}

/* [A1091] [Diagnosis Result]  Server -> Product */
/* SetWifiSendStatus( TX_DATA, WIFI_TX_RQST_INFO_DRR );  A2010.0029 DiagnosisResultRequest  */ 
void SetUserSystemDiagnosis ( U16 mu16DR, I16 mData ) // [1]: Error ����, [-100] : �̻�1
{
	#define DiagnosisError 	 (1)
	#define DiagnosisAbnormal1 (-100)
	#define DiagnosisAbnormal2 (-200)

	switch ( mu16DR )
    {
		// case 0x0001:
		// 	if (mData == DiagnosisError)
		// 	{

		// 	}
        // 	else if (mData == DiagnosisAbnormal1)
		// 	{

		// 	}
		// 	break;


		default:

        break;
	}
}


/*******************************************************************************
&Description :
    A1010 ~ A101x
    Function Table

*******************************************************************************/

#include "WIFI_A101x_FunctionList.h"
#include "WIFI_UserInterface.h"
/******************************************************************************/
/***** User Header ************************************************************/
/******************************************************************************/
// #include "include/_type_define.h"
// #include "_fix_ram.h"
// #include "cold.h"
#include "m_wifi_global_data.h"
//#include "m_wifi_setting_data.h"
/******************************************************************************/
/***** User Function **********************************************************/
/******************************************************************************/


/******************************************************************************/
/***** Table ******************************************************************/
/******************************************************************************/
/* Event List */
U16 WifiFuncEventPreVal[USER_DATA_MAX_SIZE] = {0};

static const WifiTxFuncEventList_T WifiFuncEventList[] = 
{   /*  API ID                                  DATA_TYPE                                 PreVal(Initial)                         EnventForm     */
    {   WIFI_FUNC_0002_COLD_SEL,                TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0003_HOT_LOCK_SEL,            TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },   
    {   WIFI_FUNC_0005_LOCK_SEL,                TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },   
    {   WIFI_FUNC_0006_MUTE_SEL,                TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0008_ICE_SEL,                 TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_000B_WATER_SEL,               TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED        },
    {   WIFI_FUNC_000D_WATER_OUTQUANTITY,       TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   // 0 -> ??
    // {   WIFI_FUNC_001A_HOT_INTEMP,              TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED },   
    // {   WIFI_FUNC_001B_HOT_MEANTEMP,            TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED },   
    // {   WIFI_FUNC_001C_HOT_SELTEMP,             TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED },   
    {   WIFI_FUNC_0024_HEART_TIME4,             TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   // 0 -> ?? 
    {   WIFI_FUNC_002C_SILVER_CARE,             TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_0030_ICE_MAKETIME,            TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   // 0 -> ??
    // {   WIFI_FUNC_0031_VOICE_SEL,               TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },   // 0 -> ??
    {   WIFI_FUNC_0032_ICELOCK_SEL,             TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_0033_VOICE_VOL_SEL,           TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0035_COVER1_OPEN,             TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0039_HOT_SEL,                 TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_003B_HOT_TEMP_SEL,            TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_003C_COLD_STRENGTH_SEL,       TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_003E_WATER_COURSE_STATUS,     TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_003F_WATER_COURSE_RESET,      TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },
    {   WIFI_FUNC_0040_SMART_CHECK_RQST,        TYPE_SMART_DIAGNOSIS_CONTROL,        (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0041_SMART_CHECK_STATUS,      TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0042_SMART_CHECK_PROGRESS,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_0043_FILTER_STATUS1,          TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_0047_WATER_QUANTITY_SEL,      TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0049_OUT_BUTTON_LIGHT,        TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0050_UV_STERILIZE_STATUS,     TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    // {   WIFI_FUNC_0051_QUANTITY_USE_SEL,        TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0059_ICE_ONOFF_SEL,           TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_005A_UV_ICE_TANK_STATUS,      TYPE_UNUSED,                          (U16*)(&WifiFuncEventPreVal),        EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_005C_SMART_CHECK_RESULT,      TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED        },
    {   WIFI_FUNC_005D_UV_ICE_FAUCET_STATUS,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_005E_SLEEP_MODE_SEL,          TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_005F_SLEEP_START_HOUR,        TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0060_SLEEP_START_MIN,         TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0061_SLEEP_END_HOUR,          TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0062_SLEEP_END_MIN,           TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL,    TYPE_A1014,                          (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_0077_HOT_TARGET_TEMP_TIME,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   //0 -> ??
    {   WIFI_FUNC_0078_COLD_TARGET_TEMP_TIME,   TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   //0 -> ??
    // {   WIFI_FUNC_007F_DEFAULT_TEMP_SET,        TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   
    {   WIFI_FUNC_008B_HEATER_STATUS,           TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_008C_COMP_STATUS,             TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_008F_ICE_FULL_STATUS,         TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_0093_ICEMAKING_STAUTS,        TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_SPECIFIC_CONDITION   },
    {   WIFI_FUNC_0095_ICEMAKING_COMPLET_TIME,  TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   //0 -> ??
    {   WIFI_FUNC_0096_DEICING_COMPLET_TIME,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_OTHER },   //0 -> ??
    {   WIFI_FUNC_009B_DRAINTANK_LOW_WLEVEL,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_009C_DRAINTANK_HIGH_WLEVEL,   TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_00A0_COLD_TANK_TEMP,          TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED        },
    {   WIFI_FUNC_00A1_HOT_TANK_TEMP,           TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED        },
    {   WIFI_FUNC_00A6_PURETANK_LOW_W_LEVEL,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_00A7_PURETANK_HIGH_W_LEVEL,   TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    // {   WIFI_FUNC_00AC_FILTER1_WATER_USAGE,     TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_UNUSED        },
    // {   WIFI_FUNC_00AD_FILTER1_UASGE_DAY,       TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    // {   WIFI_FUNC_00B5_FILTER_FLUSHING,         TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_ZERO_TO_ONE   },
    {   WIFI_FUNC_00CB_WATER_EXTRACT_STATUS,    TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_00CC_ICE_EXTRACT_STATUS,      TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },
    {   WIFI_FUNC_00CD_SETUP_MODE_STATUS,       TYPE_UNUSED,                         (U16*)(&WifiFuncEventPreVal),         EVENT_STATUS_CHANGE },

};

#define SZ_FUNC_EVENT_LIST    (sizeof(WifiFuncEventList)/sizeof(WifiTxFuncEventList_T))

void* GetWifiFuncDataEventList ( void )
{
    if (IsUserModelType() == Model_0)
    {
        return WifiFuncEventList;
    }
    else
    {

    }

}
U16 GetWifiFuncEventListSize ( void )
{
    if (IsUserModelType() == Model_0)
    {
        return SZ_FUNC_EVENT_LIST;
    }
    else
    {

    }
}

U16 WifiSmartCheckResultData = 0U;
/* [User Function Data] Product -> Server */
U16 GetUserSystemFunction ( U16 mu16Func )
{
    U16 mu16Data = 0U;
    U16 buf = 0;

    switch ( mu16Func )
    {
        case WIFI_FUNC_0002_COLD_SEL :       /* ID */

            if( F_Cold_Enable == SET )
            {
                mu16Data =  SET;
            }
            else
            {
                mu16Data =  CLEAR;
            }
        break;
			
        case WIFI_FUNC_0003_HOT_LOCK_SEL : 

            if( F_Hot_Lock == SET )
            {
                mu16Data =  WIFI_HOT_LOCK_ON;
            }
            else
            {
                mu16Data =  WIFI_HOT_LOCK_OFF;
            }
        break;
			
        case WIFI_FUNC_0005_LOCK_SEL : 

            if( F_All_Lock == SET )
            {
                mu16Data =  SET;
            }
            else
            {
                mu16Data =  CLEAR;
            }            
        break;
			
        case WIFI_FUNC_0006_MUTE_SEL : 
			
            if( F_Mute_Enable == SET )
            {
                mu16Data = 1;
            }
            else
            {
                mu16Data = 0;
            }            
        break;
			
        case WIFI_FUNC_0008_ICE_SEL : 

            if( bit_fast_ice_make == COLD_FIRST_ICE_MAKE )
            {
                /*..hui [23-6-23오후 4:07:01] 냉수우선 - 1..*/
                mu16Data = 1;
            }
            else
            {
                /*..hui [23-6-23오후 4:07:05] 얼음우선 - 3..*/
                mu16Data = 3;
            }            
        break;
			
        case WIFI_FUNC_000B_WATER_SEL : 

            if( u8WaterOutState == PURE_WATER_SELECT )
            {
                mu16Data = 1;
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                mu16Data = 2;
            }
            else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
            {
                mu16Data = 3;
            }
            
        break;
        case WIFI_FUNC_000D_WATER_OUTQUANTITY : 

            if( F_WaterOut == SET )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = gu16_wifi_total_quant;

                init_water_quantity();
            }
        break;
		
        case WIFI_FUNC_0024_HEART_TIME4 : 

            /*..hui [21-3-17오후 7:56:45] 닫혔을때만 시간 보냄.. 열렸을때는 0으로.. 현민..*/
            if( F_Tank_Cover_Input == SET )
            {
                mu16Data = gu16_cody_care_timer_sec;
            }
            else
            {
                mu16Data = 0;
            }

            /*..hui [21-3-5오후 3:08:57] 커버 닫히면 데이타 보내고 여기서 초기화..*/
            if( F_Tank_Cover_Input == SET )
            {
                gu8_cody_care_timer_msec = 0;
                gu16_cody_care_timer_sec = 0;
            }
            else{}            
        break;
        case WIFI_FUNC_002C_SILVER_CARE : 
            // 48시간 미사용 (0미경과 1:경과시)
            if( gu16_silver_timer_min >= SILVER_CARE_TIME_MIN )
            {
                if ( u8FirstSilverCare == CLEAR )
                {
                    u8FirstSilverCare = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                u8FirstSilverCare = CLEAR;
                mu16Data = 0;
            }
        break;
			
        case WIFI_FUNC_0030_ICE_MAKETIME : 

            if( F_Ice == CLEAR )
            {
                mu16Data = (U16)(gu32_wifi_ice_out_time / 10);
                gu8_wifi_ice_send_count++;

                /*..hui [24-1-9오후 1:29:37] 1010보내고 1014까지 보내고 난후 초기화하기위해 카운트..*/
                if( gu8_wifi_ice_send_count >= 2 )
                {
                    gu8_wifi_ice_send_count = 2;
                    gu32_wifi_ice_out_time = 0;
                }
                else{}
            }
            else
            {
                mu16Data = 0;
            }            
        break;
			
        case WIFI_FUNC_0032_ICELOCK_SEL : 
            if( F_Ice_Lock == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }            
        break;
			
        case WIFI_FUNC_0035_COVER1_OPEN : 

        if (F_Tank_Cover_Input == SET)
        {
            mu16Data = 0;
        }
        else
        {
            mu16Data = 1;
        } 
        break;
#if 0
            if ( bit_filter_cover == SET )
            {
                /*..hui [21-8-3오후 12:48:23] 닫힘..*/
                mu16Data = 0;
            }
            else
            {
                /*..hui [21-8-3오후 12:48:30] 열림..*/
                mu16Data = 1;
            }            
        break;
#endif			
        case WIFI_FUNC_0039_HOT_SEL : 

            if( F_Hot_Enable == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }            
        break;
			
        case WIFI_FUNC_0040_SMART_CHECK_RQST : 

            if( bit_self_test_start == 0 )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }


        break;
            
        case WIFI_FUNC_0041_SMART_CHECK_STATUS : 

            if( (F_WaterOut == SET)
                || (Bit1_Uart_Test_Mode == SET)
                || (Bit0_Pcb_Test_Mode == SET)
                || F_Ice == SET )
            {
                mu16Data = WIFI_SELF_TEST_PROHIBIT;
                gu8_wifi_self_test_state = WIFI_SELF_TEST_PROHIBIT;
            }
            else
            {
                mu16Data = gu8_wifi_self_test_state;
            }            
        break;
			
        case WIFI_FUNC_0042_SMART_CHECK_PROGRESS : 

            mu16Data = gu8_wifi_self_test_progress;            
        break;
		
		
        case WIFI_FUNC_0049_OUT_BUTTON_LIGHT : 		
			if( F_Extract_Led_OnOff == CLEAR )
			{
				/*..hui [23-6-23오후 2:32:59] OFF..*/
				mu16Data = 0;
			}
			else
			{
				/*..hui [23-6-23오후 2:33:03] ON..*/
				mu16Data = 1;
			}            
        break;
			
        case WIFI_FUNC_0050_UV_STERILIZE_STATUS : 
            // if( ( gu8FaucetUVOn == SET ) || ( u8IceTankUvON == SET ) || ( u8IceExtractionUvON == SET ) )
            if(gu8FaucetUVOn > 0)
        	{
				/*..sean [24-12-30] ON..*/
				mu16Data = 1;
        	}
			else
			{
				/*..sean [24-12-30] OFF..*/
				mu16Data = 0;
        	}
        break;
			
			
        case WIFI_FUNC_0059_ICE_ONOFF_SEL : 
            if( F_IceOn == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }            
        break;
        case WIFI_FUNC_005A_UV_ICE_TANK_STATUS : 
            if(u8IceTankUvON == SET)
        	{
				/*..sean [24-12-30] ON..*/
				mu16Data = 1;
        	}
			else
			{
				/*..sean [24-12-30] OFF..*/
				mu16Data = 0;
        	}
        break;
			
        case WIFI_FUNC_005C_SMART_CHECK_RESULT : 
            // No modification required. It is used for public use.
            mu16Data = WifiSmartCheckResultData;
            WifiSmartCheckResultData = 0U;            
        break;
		
        case WIFI_FUNC_005D_UV_ICE_FAUCET_STATUS : 
            if( u8IceExtractionUvON == SET )
        	{
				/*..sean [24-12-30] ON..*/
				mu16Data = 1;
        	}
			else
			{
				/*..sean [24-12-30] OFF..*/
				mu16Data = 0;
        	}
        break;
			
        case WIFI_FUNC_005E_SLEEP_MODE_SEL : 
	
            if( bit_sleep_mode_enable == CLEAR )
            {
                mu16Data = 0;
            }
            else
            {
                mu16Data = 1;
            }          
            
        break;
		
        case WIFI_FUNC_005F_SLEEP_START_HOUR : 
            mu16Data = (U16)gu8_sleep_mode_start_hour;          
        break;
		
        case WIFI_FUNC_0060_SLEEP_START_MIN : 
            mu16Data = (U16)gu8_sleep_mode_start_minute;         
        break;
		
        case WIFI_FUNC_0061_SLEEP_END_HOUR : 
            mu16Data = (U16)gu8_sleep_mode_finish_hour;   
        break;
		
        case WIFI_FUNC_0062_SLEEP_END_MIN : 
            mu16Data = (U16)gu8_sleep_mode_finish_minute;         
        break;
		
        case WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL : 
			if(gu8Cup_level_Default == CUP_LEVEL_HALF)
			{
            	mu16Data = 0;
			}
			else if(gu8Cup_level_Default == CUP_LEVEL_ONE)
			{
            	mu16Data = 1;
			}
			else if(gu8Cup_level_Default == CUP_LEVEL_TWO)
			{
            	mu16Data = 2;
			}
			else if(gu8Cup_level_Default == CUP_LEVEL_FOUR)
			{
            	mu16Data = 3;
			}/*
			else if(gu8Cup_level_Default == CUP_LEVEL_CONTINUE)
			{
            	mu16Data = 4;
			}
			else if(gu8Cup_level_Default == CUP_LEVEL_MY_CUP)
			{
            	mu16Data = 5;
			}
			*/
			else if(gu8Cup_level_Default == CUP_LEVEL_MY_CUP)
			{
            	mu16Data = 4;
			}
			else {}
        break;
			
        case WIFI_FUNC_0077_HOT_TARGET_TEMP_TIME : 		
		
		/*..hui [23-6-23오후 4:16:04] 온수 목표 온도 도달 시간??..*/
		if( bit_wifi_hot_heater == CLEAR )
		{
			if( bit_wifi_heater_on_time_update == SET )
			{
				bit_wifi_heater_on_time_update = CLEAR;
				mu16Data = gu16_hot_target_reach_timer_sec;
				gu32_hot_target_reach_timer_ms = 0;
				gu16_hot_target_reach_timer_sec = 0;
			}
			else
			{
				mu16Data = 0;
			}
		}
		else
		{
			bit_wifi_heater_on_time_update = CLEAR;
			mu16Data = 0;
		}            
        break;
		
        case WIFI_FUNC_0078_COLD_TARGET_TEMP_TIME : 

            /*..hui [23-6-23오후 4:16:22] 냉수 목표 온도 도달 시간..???..*/
            if( bit_wifi_comp == CLEAR )
            {
                if( bit_wifi_comp_on_time_update == SET )
                {
                    bit_wifi_comp_on_time_update = CLEAR;
                    mu16Data = gu16_cold_target_reach_timer_sec;
                    gu32_cold_target_reach_timer_ms = 0;
                    gu16_cold_target_reach_timer_sec = 0;
                }
                else
                {
                    mu16Data = 0;
                }
            }
            else
            {
                bit_wifi_comp_on_time_update = CLEAR;
                mu16Data = 0;
            }            
        break;
			
        case WIFI_FUNC_008B_HEATER_STATUS : 

            if( bit_wifi_hot_heater == SET )
            {
                if( bit_wifi_first_hot_heater == CLEAR )
                {
                    bit_wifi_first_hot_heater = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_hot_heater = CLEAR;
                mu16Data = 0;
            }
            
        break;
        case WIFI_FUNC_008C_COMP_STATUS : 

            if( F_Comp_Output == SET )
            {
                if( bit_wifi_first_comp == CLEAR )
                {
                    bit_wifi_first_comp = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_comp = CLEAR;
                mu16Data = 0;
            }            
        break;
        case WIFI_FUNC_008F_ICE_FULL_STATUS : // 占쏙옙占쏙옙占쏙옙占쏙옙

            if( F_IceFull == SET )
            {
                if( bit_wifi_first_ice_full == CLEAR )
                {
                    bit_wifi_first_ice_full = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_ice_full = CLEAR;
                mu16Data = 0;
            }


        break;
			
        case WIFI_FUNC_0093_ICEMAKING_STAUTS : 

            mu16Data = gu8_wifi_ice_make_state;
        break;
		
        case WIFI_FUNC_0095_ICEMAKING_COMPLET_TIME : 	
		
		if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
		{
			mu16Data = (U16)(gu32_wifi_ice_make_time / 10);
			gu32_wifi_ice_make_time = 0;
		}
		else
		{
			mu16Data = 0;
		}            
        break;
		
        case WIFI_FUNC_0096_DEICING_COMPLET_TIME : 

            if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
            {
                mu16Data = (U16)(gu32_wifi_ice_heater_time / 10);
                gu32_wifi_ice_heater_time = 0;
            }
            else
            {
                mu16Data = 0;
            }
        break;
			
        case WIFI_FUNC_009B_DRAINTANK_LOW_WLEVEL : 

            if( F_drain_water_level_low == SET )
            {
                if( bit_wifi_first_drain_low == CLEAR )
                {
                    bit_wifi_first_drain_low = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_drain_low = CLEAR;
                mu16Data = 0;
            }
            
        break;
        case WIFI_FUNC_009C_DRAINTANK_HIGH_WLEVEL : 

            if( F_drain_water_level_high == SET )
            {
                if( bit_wifi_first_drain_high == CLEAR )
                {
                    bit_wifi_first_drain_high = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_drain_high = CLEAR;
                mu16Data = 0;
            }
            
        break;
        case WIFI_FUNC_00A0_COLD_TANK_TEMP : 

            mu16Data = gu8_Cold_Temperature_One_Degree;            
        break;
		
        case WIFI_FUNC_00A1_HOT_TANK_TEMP : 

            mu16Data = gu8_Hot_Tank_Temperature_One_Degree;            
        break;
		
        case WIFI_FUNC_00A6_PURETANK_LOW_W_LEVEL : 

            if( bit_wifi_cold_low == SET )
            {
                if( bit_wifi_first_cold_low == CLEAR )
                {
                    bit_wifi_first_cold_low = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_cold_high = CLEAR;
                mu16Data = 0;
            }

     
        break;
        case WIFI_FUNC_00A7_PURETANK_HIGH_W_LEVEL : 

            if( bit_wifi_cold_high == SET )
            {
                if( bit_wifi_first_cold_high == CLEAR )
                {
                    bit_wifi_first_cold_high = SET;
                    mu16Data = 1;
                }
                else
                {
                    mu16Data = 2;
                }
            }
            else
            {
                bit_wifi_first_cold_high = CLEAR;
                mu16Data = 0;
            }
     
        break;
		
        case WIFI_FUNC_00B5_FILTER_FLUSHING : 
            //useless
        break;
			
        case WIFI_FUNC_00CB_WATER_EXTRACT_STATUS : 

            if( (F_WaterOut == SET) )
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }            
        break;
			
        case WIFI_FUNC_00CC_ICE_EXTRACT_STATUS : 

            if( (F_Ice == SET) )
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }            
        break;
			
        case WIFI_FUNC_00CD_SETUP_MODE_STATUS : 

            if( (gu8_Led_Display_Step == LED_Display__SETTING))
            {
                mu16Data = 1U;
            }
            else
            {
                mu16Data = 0U;
            }            
        break;
			

        default:
            mu16Data = 0U;
        break;
    }
    return mu16Data;
}


/* [Set User Function Data] App Control(Server) -> Product */
void SetUserSystemFunction ( U16 mu16Func, U16 mData )
{
    switch ( mu16Func )
    {
        case WIFI_FUNC_0002_COLD_SEL :
			wifi_cold_enable( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);				
        break;
		
        case WIFI_FUNC_0003_HOT_LOCK_SEL :
			wifi_hot_lock( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;
		
        case WIFI_FUNC_0005_LOCK_SEL :
            wifi_all_lock( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0006_MUTE_SEL :
            wifi_mute( mData );
			if(mData == SET)
				//BuzStep(BUZZER_SETUP);
            	BuzStep(BUZZER_SETUP_MUTE);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0008_ICE_SEL :
            wifi_ice_first( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0032_ICELOCK_SEL :
            wifi_ice_lock( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0039_HOT_SEL :
            wifi_hot_enable( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0040_SMART_CHECK_RQST :
            wifi_self_test( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0047_WATER_QUANTITY_SEL :
			//useless
        break;

        case WIFI_FUNC_0049_OUT_BUTTON_LIGHT :
            wifi_welcome_light( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0051_QUANTITY_USE_SEL :
			//useless
        break;

        case WIFI_FUNC_0059_ICE_ONOFF_SEL :	
			wifi_ice_enable( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

		case WIFI_FUNC_005C_SMART_CHECK_RESULT :
			
            WifiSmartCheckResultData = (U8)mData;

            if (WifiSmartCheckResultData == CLEAR)
            {
                SetWifiBuzzSound(WIFI_BUZZER_SMART_CHECK_OK); // OK
            }
            else
            {
                SetWifiBuzzSound(WIFI_BUZZER_SMART_CHECK_ERROR); // NG
            }
			
        break;

		case WIFI_FUNC_005E_SLEEP_MODE_SEL :
            wifi_sleep_mode_enable( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_005F_SLEEP_START_HOUR :
            wifi_sleep_start_hour( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0060_SLEEP_START_MIN :
            wifi_sleep_start_minute( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0061_SLEEP_END_HOUR :
            wifi_sleep_finish_hour( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0062_SLEEP_END_MIN :
            wifi_sleep_finish_minute( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;

        case WIFI_FUNC_0066_DEFAULT_QUANTITY_SEL :
            wifi_default_cup( mData );
			if(mData == SET)
				BuzStep(BUZZER_SETUP);
			else
				BuzStep(BUZZER_CANCEL);	
        break;


        default:
        break;
    }
}

/* User Data Clear (Called when wifi is not connected) */
void ClearUserSystemDataA1010 ( void )
{
    
}

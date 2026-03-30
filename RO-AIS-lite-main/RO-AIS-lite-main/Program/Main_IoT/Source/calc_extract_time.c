/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "calc_extract_time.h"

void calc_waterout_time(void);
void clac_effluent_water_acc(void);
void calc_ice_tray_input_water(void);
void acc_user_water( U16 mu16_water_acc );
void calc_flow_rate(void);
void calc_feed_water(void);
void dec_user_water( U16 mu16_water_acc );
void final_compensation_time(void);
void Pure_Temp_Compensation_time( void );

U16 u16_user_effluent_time;
U16 u16_user_effluent_total_time;
U16 u16_user_effluent_cup_size;


U16 gu16_total_tank_water;

bit bit_tray_water_acc;

U16 gu16_feed_timer;

U8 gu8_compensation_time;
U8 gu8_ro_flow_rate;
bit bit_flow_start_1;
bit bit_flow_start_2;
U16 gu16_ro_flow_timer;

bit bit_flow_calc_first_op;

U16 g16_extract_decrease_time;  // 정상확인후에 Local로 변경 예정

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_waterout_time(void)
{
    /*..hui [23-5-10오전 9:58:52] 처음 만수위 도달하고나서 시작..*/
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        bit_flow_start_1 = CLEAR;
        bit_flow_start_2 = CLEAR;
        gu16_ro_flow_timer = 0;

        gu16_feed_timer = 0;
        gu16_total_tank_water = 0;

        gu8_compensation_time = 0;
        bit_flow_calc_first_op = CLEAR;
        return;
    }
    else{}

    /*..hui [23-5-15오후 1:04:41] 최초 전원 ON 시 저수위 or 만수위일 경우 알고리즘 동작 시작..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW || gu8_Room_Water_Level == ROOM_LEVEL_FULL )
    {
        bit_flow_calc_first_op = SET;
    }
    else{}

    if( bit_flow_calc_first_op == CLEAR )
    {
        bit_flow_start_1 = CLEAR;
        bit_flow_start_2 = CLEAR;
        gu16_ro_flow_timer = 0;

        gu16_feed_timer = 0;
        gu16_total_tank_water = 0;

        gu8_compensation_time = 0;
        return;
    }
    else{}



    /*..hui [23-5-10오전 9:54:16] 추출 유량 계산..*/
    clac_effluent_water_acc();
    /*..hui [23-5-10오전 9:54:44] 트레이 입수 유량 계산..*/
    /*..sean [25-3-18 사양 정리] 트레이 입수 유량 물 추출량에 포함시키지 않음..*/
    //calc_ice_tray_input_water();

    /*..hui [23-5-10오전 9:52:45] 입수 유량 계산..*/
    calc_flow_rate();
    /*..hui [23-5-10오전 9:54:04] 계산된 유량으로 추출된 전체 유량에서 재정수 유량 빼줌..*/
    calc_feed_water();
    /*..hui [23-5-9오후 4:37:08] 최종 보정시간 확인..추출쪽으로 이동..*/
    /*final_compensation_time();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void clac_effluent_water_acc(void)
{
    U16 mu16_water_acc = 0;
	U16 mu16_mycup_size;

    if( F_WaterOut == SET )
    {
        u16_user_effluent_time++;
		if(gu8Cup_level == CUP_LEVEL_MY_CUP)
		{
            if( u8WaterOutState == PURE_WATER_SELECT )
            {
        		u16_user_effluent_total_time = gu16_my_cup_level_pure;
            }
           	else if( u8WaterOutState == HOT_WATER_SELECT )
            {
        		u16_user_effluent_total_time = gu16_my_cup_level_hot;
            }
           	else// if( u8WaterOutState == COLD_WATER_SELECT )
            {
        		u16_user_effluent_total_time = gu16_my_cup_level_cold;
            }
		}
		else
			u16_user_effluent_total_time = u16Efluent_Time;

        if(u8Extract_Continue == SET)
        {
            /*..hui [19-8-23오후 1:33:33] 연속추출 했을때 물 양.. 나중에 계산해서 변경해야 함..*/
            /*u16_user_effluent_cup_size = 1500;*/

            if( u8WaterOutState == PURE_WATER_SELECT )
            {
                u16_user_effluent_cup_size = 2100;
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                u16_user_effluent_cup_size = 2200;
            }
            else /*if(u8WaterOutState == HOT_WATER_SELECT)*/
            {
                u16_user_effluent_cup_size = 1300;
            }
        }
        else
        {
            if(gu8Cup_level == CUP_LEVEL_HALF)
            {
                u16_user_effluent_cup_size = 120;
            }
            else if(gu8Cup_level == CUP_LEVEL_ONE)
            {
                u16_user_effluent_cup_size = 250;
            }
            else if(gu8Cup_level == CUP_LEVEL_TWO)
            {
                u16_user_effluent_cup_size = 500;
            }
            else if(gu8Cup_level == CUP_LEVEL_FOUR)
            {
                u16_user_effluent_cup_size = 1000;
            }
			//mycup은 maximum값 기준으로 계싼
            else if(gu8Cup_level == CUP_LEVEL_MY_CUP)
            {
                u16_user_effluent_cup_size = 800 * ((u16_user_effluent_total_time * 10 ) / MY_CUP_SETTING_800mL_PURE ) ;
				u16_user_effluent_cup_size = u16_user_effluent_cup_size + 80 * ((u16_user_effluent_total_time * 10 ) / MY_CUP_SETTING_800mL_PURE ) ;
            }
            else if(gu8Cup_level == CUP_LEVEL_CONTINUE)
            {
	            if( u8WaterOutState == PURE_WATER_SELECT )
	            {
	                u16_user_effluent_cup_size = 2100;
	            }
	            else if( u8WaterOutState == COLD_WATER_SELECT )
	            {
	                u16_user_effluent_cup_size = 2200;
	            }
	            else /*if(u8WaterOutState == HOT_WATER_SELECT)*/
	            {
	                u16_user_effluent_cup_size = 1300;
	            }
            }
            else // (gu8Cup_level == CUP_LEVEL_HALF)
            {
                u16_user_effluent_cup_size = 1000;
            }
        }
    }
    else
    {
        if(u16_user_effluent_time != 0)
        {
            u16_user_effluent_time = u16_user_effluent_time + 1;
			if(gu8Cup_level == CUP_LEVEL_MY_CUP)
			{
				u16_user_effluent_cup_size = u16_user_effluent_cup_size / 10;
				mu16_water_acc =
					(U16)((((U32)u16_user_effluent_time * (U32)u16_user_effluent_cup_size) / u16_user_effluent_total_time) / 10);
			}
			else
				mu16_water_acc =
					(U16)((((U32)u16_user_effluent_time * (U32)u16_user_effluent_cup_size) / u16_user_effluent_total_time) / 10);

            mu16_water_acc = mu16_water_acc * 10;
            acc_user_water( mu16_water_acc );

            /*..hui [21-8-3오후 3:53:17] 와이파이 적산용 물량..*/
            gu16_wifi_water_acc = mu16_water_acc;

            u16_user_effluent_time = 0;
        }
        else
        {
            u16_user_effluent_time = 0;
            u16_user_effluent_total_time = 0;
            u16_user_effluent_cup_size = 0;
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_ice_tray_input_water(void)
{
    U16 mu16_water_acc = 0;

    if( gu8IceStep >= STATE_21_ICE_SWITCH_MOVE )
    {
        if( bit_tray_water_acc == CLEAR )
        {
            bit_tray_water_acc = SET;
            /*..hui [23-5-9오후 2:45:56] 아이스트레이 입수 용량 300cc..*/
            mu16_water_acc = ICE_TRAY_INPUT_WATER;
            acc_user_water( mu16_water_acc );

            /*..hui [21-8-3오후 3:53:17] 와이파이 적산용 물량..*/
            gu16_wifi_water_acc = mu16_water_acc;
        }
        else{}
    }
    else
    {
        bit_tray_water_acc = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void acc_user_water( U16 mu16_water_acc )
{
    gu16_total_tank_water += mu16_water_acc;

    if(gu16_total_tank_water >= TOTAL_TANK_MAX_WATER)
    {
        gu16_total_tank_water = TOTAL_TANK_MAX_WATER;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_flow_rate(void)
{
    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
    {
        /*..hui [23-5-10오전 9:46:24] 만수위 상태에서 반컵 추출할때..*/
        /*..hui [23-5-10오전 10:02:55] 제빙중 물 빠질 수 있으니 제빙 대기중일때만..*/
        if( F_WaterOut == SET && gu8Cup_level == CUP_LEVEL_HALF && gu8IceStep == STATE_0_STANDBY )
        {
            bit_flow_start_1 = SET;
        }
        else{}
    }
    else{}

    if( bit_flow_start_1 == SET )
    {
        /*..hui [23-5-10오전 9:48:08] 추출 완료되고 추출된 물량이 250ml 이면..*/
        if( F_WaterOut == CLEAR )
        {
            if( gu16_total_tank_water == 250 )
            {
                bit_flow_start_1 = CLEAR;
                bit_flow_start_2 = SET;
            }
            else
            {
                bit_flow_start_1 = CLEAR;
                bit_flow_start_2 = CLEAR;
            }
        }
        else{}
    }
    else{}

    if( bit_flow_start_2 == SET )
    {
        /*..hui [23-5-9오후 2:52:26] FEED 열려있고 NOS 닫혀있는 상태..*/
        if( bit_feed_output == SET )
        {
            gu16_ro_flow_timer++;

            /*..hui [23-5-10오전 9:49:47] 최대 시간 20분..*/
            if( gu16_ro_flow_timer >= 12000 )
            {
                gu16_ro_flow_timer = 12000;
            }
            else{}
        }
        else
        {
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
            {
                gu16_ro_flow_timer = gu16_ro_flow_timer / 10;
                //gu8_ro_flow_rate = (U8)(250 / gu16_ro_flow_timer);
                //250ml 차는 시간 확인 후, 분단위로 변환 후, 분당 유량cc 확인
                gu8_ro_flow_rate = (U8)( ( 250 * 60 ) / gu16_ro_flow_timer );

                bit_flow_start_1 = CLEAR;
                bit_flow_start_2 = CLEAR;
                gu16_ro_flow_timer = 0;
            }
            else{}
        }

        /*..hui [23-5-10오전 9:52:18] 계산중에 물 추출하거나 NOS 닫히면 취소하고 전부 초기화..*/
        if( F_WaterOut == SET || bit_nos_output == SET )
        {
            bit_flow_start_1 = CLEAR;
            bit_flow_start_2 = CLEAR;
            gu16_ro_flow_timer = 0;
        }
        else{}

        if( gu8IceStep >= STATE_20_WATER_IN_ICE_TRAY )
        {
            bit_flow_start_1 = CLEAR;
            bit_flow_start_2 = CLEAR;
            gu16_ro_flow_timer = 0;
        }
        else{}
    }
    else
    {
        gu16_ro_flow_timer = 0;
    }

    if( gu8_ro_flow_rate <= 30
        || gu8_ro_flow_rate >= 200 )
    {
        gu8_ro_flow_rate = FEED_TIME_1_MIN_PER_60ML;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_feed_water(void)
{
    /*..hui [23-5-9오후 2:58:51] 만수위 이거나 수위센서 에러상태일 경우 초기화..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL || gu8_Room_Water_Level == ROOM_LEVEL_ERROR )
    {
        gu16_feed_timer = 0;
        gu16_total_tank_water = 0;
        return;
    }
    else if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        /*..hui [23-5-12오전 9:27:12] 저수위 미감지 시점에서 최대값으로 고정해줌..*/
        gu16_feed_timer = 0;
        gu16_total_tank_water = TOTAL_TANK_MAX_WATER;
        return;
    }
    else{}

    /*..hui [23-5-9오후 2:52:26] FEED 열려있고 NOS 닫혀있는 상태..*/
    if( bit_feed_output == SET && bit_nos_output == CLEAR )
    {
        gu16_feed_timer++;

        if( gu16_feed_timer >= FEED_WATER_TIME_1_MIN )
        {
            gu16_feed_timer = 0;
            /*..hui [23-5-9오후 2:56:27] 1분당 100ml씩 삭제..*/
            /*dec_user_water( FEED_TIME_1_MIN_PER_60ML );*/
            dec_user_water( gu8_ro_flow_rate );
        }
        else{}
    }
    else
    {
        gu16_feed_timer = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void dec_user_water( U16 mu16_water_acc )
{
    if( gu16_total_tank_water > mu16_water_acc )
    {
        gu16_total_tank_water = gu16_total_tank_water - mu16_water_acc;
    }
    else
    {
        gu16_total_tank_water = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void final_compensation_time(void)
{
    U16 mu16_calc_a = 0;
    U16 mu16_basic_time = 0;
    U8 mu8_max_time = 0;
    U16 mu16_tank_water = 0;

    if( gu16_total_tank_water == 0 )
    {
        gu8_compensation_time = 0;
        return;
    }
    else{}

    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_ONE) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_HALF_TIME_TANK_1000ML - ROOM_WATER_HALF_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_ONE);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_HALF_TIME_TANK_1500ML - ROOM_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_ONE);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_HALF_TIME_TANK_1500ML - ROOM_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_ONE);
            }
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_TWO) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_ONE_TIME_TANK_1000ML - ROOM_WATER_ONE_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_TWO);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_ONE_TIME_TANK_1500ML - ROOM_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_TWO);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_ONE_TIME_TANK_1500ML - ROOM_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_TWO);
            }

        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_FOUR) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_TWO_TIME_TANK_1000ML - ROOM_WATER_TWO_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_PURE_WATER_FOUR);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_TWO_TIME_TANK_1500ML - ROOM_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_FOUR);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(ROOM_WATER_TWO_TIME_TANK_1500ML - ROOM_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(ROOM_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_PURE_WATER_FOUR);
            }
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {

        }
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_ONE) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_HALF_TIME_TANK_1000ML - COLD_WATER_HALF_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_ONE);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_HALF_TIME_TANK_1500ML - COLD_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_ONE);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(COLD_WATER_HALF_TIME_TANK_1500ML - COLD_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_ONE);
            }
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_TWO) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_ONE_TIME_TANK_1000ML - COLD_WATER_ONE_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_TWO);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_ONE_TIME_TANK_1500ML - COLD_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_TWO);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(COLD_WATER_ONE_TIME_TANK_1500ML - COLD_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_TWO);
            }

        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_FOUR) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_TWO_TIME_TANK_1000ML - COLD_WATER_TWO_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_COLD_WATER_FOUR);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(COLD_WATER_TWO_TIME_TANK_1500ML - COLD_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_FOUR);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(COLD_WATER_TWO_TIME_TANK_1500ML - COLD_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(COLD_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_COLD_WATER_FOUR);
            }
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {

        }

    }
    else /*if(u8WaterOutState == HOT_WATER_SELECT)*/
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_ONE) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_HALF_TIME_TANK_1000ML - HOT_WATER_HALF_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_HALF_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_ONE);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_HALF_TIME_TANK_1500ML - HOT_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_ONE);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(HOT_WATER_HALF_TIME_TANK_1500ML - HOT_WATER_HALF_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_HALF_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_ONE);
            }
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_TWO) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_ONE_TIME_TANK_1000ML - HOT_WATER_ONE_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_ONE_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_TWO);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_ONE_TIME_TANK_1500ML - HOT_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_TWO);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(HOT_WATER_ONE_TIME_TANK_1500ML - HOT_WATER_ONE_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_ONE_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_TWO);
            }

        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            if( gu16_total_tank_water <= 500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_FOUR) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = 0;
            }
            else if( gu16_total_tank_water <= 1000 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_TWO_TIME_TANK_1000ML - HOT_WATER_TWO_TIME_TANK_500ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_TWO_TIME_TANK_500ML - EXTRACT_TIME_HOT_WATER_FOUR);
            }
            else if( gu16_total_tank_water <= 1500 )
            {
                mu16_calc_a = (U16)(((F32)(HOT_WATER_TWO_TIME_TANK_1500ML - HOT_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_FOUR);
            }
            else
            {
                /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
                mu16_calc_a = (U16)(((F32)(HOT_WATER_TWO_TIME_TANK_1500ML - HOT_WATER_TWO_TIME_TANK_1000ML) / TIME_PER_ML_DEIVDE) * 100);
                mu16_basic_time = (U16)(HOT_WATER_TWO_TIME_TANK_1000ML - EXTRACT_TIME_HOT_WATER_FOUR);
            }
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {

        }

    }

    if( gu16_total_tank_water <= 500 )
    {
        mu16_tank_water = (U8)(gu16_total_tank_water / 10);
    }
    else if( gu16_total_tank_water <= 1000 )
    {
        mu16_tank_water = (U8)((gu16_total_tank_water - 500) / 10);
    }
    else if( gu16_total_tank_water <= 1500 )
    {
        mu16_tank_water = (U8)((gu16_total_tank_water - 1000) / 10);
    }
    else
    {
        /*..hui [23-5-9오후 3:44:43] 1500CC 이상일 경우 1500CC로 적용..*/
        /*mu16_tank_water = 1;*/
        mu16_tank_water = (U8)((1500 - 1000) / 10);
    }


    gu8_compensation_time = (U8)((U8)( (mu16_calc_a * mu16_tank_water) / 100 ) + (U8)mu16_basic_time);


    /*..hui [23-5-10오후 2:04:32] 혹시몰라 최대 제한 시간 추가..*/
    /*..hui [23-5-10오후 2:04:40] 계산 잘못됐을경우 대비..*/
    if( u8WaterOutState == PURE_WATER_SELECT )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            mu8_max_time = ROOM_WATER_HALF_TIME_TANK_1500ML - EXTRACT_TIME_PURE_WATER_ONE;
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            mu8_max_time = ROOM_WATER_ONE_TIME_TANK_1500ML - EXTRACT_TIME_PURE_WATER_TWO;
        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            mu8_max_time = ROOM_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_PURE_WATER_FOUR;
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {
            mu8_max_time = ROOM_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_PURE_WATER_FOUR;
        }
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            mu8_max_time = COLD_WATER_HALF_TIME_TANK_1500ML - EXTRACT_TIME_COLD_WATER_ONE;
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            mu8_max_time = COLD_WATER_ONE_TIME_TANK_1500ML - EXTRACT_TIME_COLD_WATER_TWO;
        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            mu8_max_time = COLD_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_COLD_WATER_FOUR;
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {
            mu8_max_time = COLD_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_COLD_WATER_FOUR;
        }

    }
    else /*if(u8WaterOutState == HOT_WATER_SELECT)*/
    {
        if( gu8Cup_level == CUP_LEVEL_HALF )
        {
            mu8_max_time = HOT_WATER_HALF_TIME_TANK_1500ML - EXTRACT_TIME_HOT_WATER_ONE;
        }
        else if( gu8Cup_level == CUP_LEVEL_ONE )
        {
            mu8_max_time = HOT_WATER_ONE_TIME_TANK_1500ML - EXTRACT_TIME_HOT_WATER_TWO;
        }
        else if( gu8Cup_level == CUP_LEVEL_TWO )
        {
            mu8_max_time = HOT_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_HOT_WATER_FOUR;
        }
        else /*if( gu8Cup_level == CUP_LEVEL_MY_CUP )*/
        {
            mu8_max_time = HOT_WATER_TWO_TIME_TANK_1500ML - EXTRACT_TIME_HOT_WATER_FOUR;
        }
    }

    /*..hui [23-5-10오전 10:12:07] 온수 최대 보상시간 이상일 경우 제한..*/
    if( gu8_compensation_time >= mu8_max_time )
    {
        gu8_compensation_time = mu8_max_time;
    }
    else{}

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pure_Temp_Compensation_time( void )
{
    U16 mu16_a = 0;
    U32 mu32_b = 0;
    U32 mu32_c = 0;
    U16 mu16_final = 0;
    U16 mu16_limit = 0;

    #if 0
    if (gu16_total_tank_water > 1500)
    {
        g16_extract_decrease_time = FIXED_TIME_1500ML_COMPENSATION;
    }
    else
    {
        g16_extract_decrease_time = gu16_hot_mix_time / 20;
    }
    //변수 깨지는지 확인
    u16Efluent_Time = ( u16Efluent_Time * (100 - ( (  g16_extract_decrease_time * 3 ) / 2) ) ) / 100;
    //local로 변경 후 삭제_감소시간 초기화
    g16_extract_decrease_time = 0;
    #endif

    #if 0
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        g16_extract_decrease_time = FIXED_TIME_1500ML_COMPENSATION;
    }
    else
    {
        g16_extract_decrease_time = (gu16_hot_mix_time / 20);
    }
    #endif

    #if 0
    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        return;
    }
    else{}

    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        /*..hui [23-5-23오후 5:48:32] 3 percent 고정..*/
        mu32_b = 300;
    }
    else
    {
        mu32_a = (U32)(gu16_hot_mix_time / 10);
        mu32_b = (U32)(mu32_a * 75);
    }

    mu32_c = (U32)((U32)u16Efluent_Time * mu32_b);
    mu16_final = (U16)(mu32_c / 10000);

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
    mu16_limit = (U16)(((U32)u16Efluent_Time * 80) / 100);

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    /*..hui [23-5-23오후 5:58:04] 최종.. 2초당 전체 추출시간의 1.5 percent 빼준다..*/
    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time);
    #endif

    /*..hui [23-5-23오후 7:04:38] 정수가 아닐때는 패스..*/
    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        return;
    }
    else{}

    mu16_a = gu16_hot_mix_time / 10;

	mu16_final = mu16_a * 2;

    /*..hui [23-5-23오후 5:54:03] 최대 추출시간의 80%로 제한..*/
	/*..sean [23-5-24] 최대 추출시간의 70%로 제한..*/

    mu16_limit = (U16)(((U32)u16Efluent_Time * 40) / 100);

    if( mu16_final >= mu16_limit )
    {
        g16_extract_decrease_time = mu16_limit;
    }
    else
    {
        g16_extract_decrease_time = mu16_final;
    }

    /*..hui [23-5-23오후 5:58:04] 최종.. 2초당 전체 추출시간의 1.5 percent 빼준다..*/
    u16Efluent_Time = (u16Efluent_Time - g16_extract_decrease_time );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



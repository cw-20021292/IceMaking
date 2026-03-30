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
#include    "mix_water.h"

void calc_mix_water(void);
void open_hot_valve(void);


U16 gu16_water_out_time;
U16	gu16_contiune_water_out_time;
U16	gu16_contiune_water_out_standard;
U16 gu16_hot_mix_time;
bit bit_open_hot_valve;
U16 gu16_hot_open_timer;

U16 gu16_contiune_extract_count;
U16 gu16_hot_mix_first_time;
U16 gu16_hot_mix_second_time;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_mix_water(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_time = 0;
    U16 mu16_max_time = 0;

    /*if( gu8_Room_Temperature_One_Degree >= 20 )*/
    if( gu8_Room_Temperature_One_Degree >= 22 )
    {
        gu16_hot_mix_time = 0;
        return;
    }
    else{}

    /*..hui [23-5-25오전 10:24:27] 정수온도 29도 이상일경우 안섞음..*/
    if( gu8_Room_Temperature_One_Degree >= (U8)(TARGET_ROOM_TEMP - 1) )
    {
        gu16_hot_mix_time = 0;
        return;
    }
    else{}

    /*..hui [23-5-25오전 10:24:09] 온수온도 35도 이하일경우 안섞음..*/
    if( gu8_Hot_Tank_Temperature_One_Degree <= (U8)(TARGET_ROOM_TEMP + 5) )
    {
        gu16_hot_mix_time = 0;
        return;
    }
    else{}

    mu8_a = TARGET_ROOM_TEMP - gu8_Room_Temperature_One_Degree;
    mu8_b = gu8_Hot_Tank_Temperature_One_Degree - TARGET_ROOM_TEMP;

    f32_c = (F32)((F32)mu8_b / mu8_a);
	/*..sean [23-7-13 오전 10:12:09] 연속 추출일 경우에도 정수 온도범위로 진행 ..*/
	/* 30초 동안의 정수 추출량을 기준으로 3번 나눠서 하기위해 세팅. 저유량 센서때문에 온수 추출은 2번만 진행 ..*/
	if( u8Extract_Continue == SET ) 
	{
		gu16_contiune_extract_count = 0;
		gu16_contiune_water_out_time = gu16Water_Extract_Timer ;
		gu16_contiune_water_out_standard = EXTRACT_TIME_CONTINUE / 3 ;
		
	    f32_time = (F32)((F32)gu16_contiune_water_out_standard / f32_c);

	    /*gu16_hot_mix_time = gu16_water_out_time - mu16_time;*/
	    gu16_hot_mix_time = (U16)f32_time;

	    /*mu16_max_time = ((gu16_water_out_time * 8) / 10);*/
	    /*..hui [23-5-25오전 11:50:52] 최대 70percent로 제한..*/
	    mu16_max_time = ((gu16_contiune_water_out_standard * 7) / 10);

	    if( gu16_hot_mix_time >= mu16_max_time )
	    {
	        gu16_hot_mix_time = mu16_max_time;
	    }
	    else{}

	    //add
	    /*23-05-02 sean 최대 온수 조합 시간이 추출시간을 넘지 않도록 제한 */
	    if( gu16_hot_mix_time >= u16Efluent_Time )
	    {
	        gu16_hot_mix_time = u16Efluent_Time;
	    }
	    else {}
	}
	else //( u8Extract_Continue != SET ) 
	{	
	    f32_time = (F32)((F32)gu16_water_out_time / f32_c);

	    /*gu16_hot_mix_time = gu16_water_out_time - mu16_time;*/
	    gu16_hot_mix_time = (U16)f32_time;

	    /*mu16_max_time = ((gu16_water_out_time * 8) / 10);*/
	    /*..hui [23-5-25오전 11:50:52] 최대 70percent로 제한..*/
	    mu16_max_time = ((gu16_water_out_time * 7) / 10);

	    if( gu16_hot_mix_time >= mu16_max_time )
	    {
	        gu16_hot_mix_time = mu16_max_time;
	    }
	    else{}

	    //add
	    /*23-05-02 sean 최대 온수 조합 시간이 추출시간을 넘지 않도록 제한 */
	    if( gu16_hot_mix_time >= u16Efluent_Time )
	    {
	        gu16_hot_mix_time = u16Efluent_Time;
	    }
	    else {}
	}
	
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void open_hot_valve(void)
{
    U16 mu16_max_time = 0;

    /////U16 gu16_hot_mix_half_time = 0;

    /*..hui [23-5-25오전 11:41:13] 온수추출밸브 열리는 시간 0.4초 이하일경우 open 안함..*/
    if( Bit0_Hot_Tank_Temp_Open_Short_Error == SET
        || Bit2_Room_Temp_Open_Short_Error == SET
        || gu16_hot_mix_time <= 4 )
    {
        bit_open_hot_valve = CLEAR;
        gu16_hot_open_timer = 0;
        return;
    }
    else{}
#if 0
    /*..hui [23-5-25오전 10:35:43] 연속추출일때는 안섞는다..*/
	/*..sean [23-7-10오전 08:28:42] 연속추출일때에는 3회에 걸쳐서 섞는다..*/
	
    if( F_WaterOut == SET && u8WaterOutState == PURE_WATER_SELECT )
    {
    	if( u8Extract_Continue == CLEAR )
    	{
            if( gu16Water_Extract_Timer >= HOT_MIX_START_TIME )
            {
                gu16_hot_open_timer++;

                if( gu16_hot_open_timer >= gu16_hot_mix_time )
                {
                    gu16_hot_open_timer = gu16_hot_mix_time;
                    bit_open_hot_valve = CLEAR;
                }
                else
                {
                    bit_open_hot_valve = SET;
                }
            }
    	}
       else //( u8Extract_Continue == SET )
	   {
	   		if( gu16_contiune_extract_count <= 2 )
	   		{
				gu16_contiune_water_out_time++;
	            if( gu16_contiune_water_out_time >= HOT_MIX_START_TIME )
	            {
	                gu16_hot_open_timer++;

	                if( gu16_hot_open_timer >= gu16_hot_mix_time )
	                {
	                    gu16_hot_open_timer = gu16_hot_mix_time;
	                    bit_open_hot_valve = CLEAR;
	                }
	                else
	                {
	                    bit_open_hot_valve = SET;
	                }
					if( gu16_contiune_water_out_time > gu16_contiune_water_out_standard)
					{
						gu16_contiune_water_out_time = 0;
						gu16_contiune_extract_count++;
	           			gu16_hot_open_timer = 0;		
					}
					else {}
	        	}	
				else {}
			}
			else
			{
	            bit_open_hot_valve = CLEAR;
	            gu16_hot_open_timer = 0;
				gu16_contiune_extract_count = 0;
				gu16_hot_mix_time = 0;
			}
	   }
    }
    else
    {
        bit_open_hot_valve = CLEAR;
        gu16_hot_open_timer = 0;
    }
#endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



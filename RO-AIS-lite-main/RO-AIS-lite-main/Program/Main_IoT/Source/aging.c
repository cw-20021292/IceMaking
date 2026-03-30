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
#include    "aging.h"


U16 gu16_durable_test_init_timer;
U16 gu16_durable_test_timer;
U16 gu16_durable_test_step;
U8 gu8_durable_test_start;

U16 gu16_aging_count;

U8 gu8_ice_test_step;
U8 gu8_repeat_count;
U32 gu32_ice_test_timer;


U16 gu16_durable_test_timer;

U16 gu8_durable_test_step;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_durable_test(void)
{
	if( gu8_durable_test_start == CLEAR )
	{
		gu8_ice_test_step = 0;
		gu32_ice_test_timer = 0;
		return;
	}
	else{}

	switch(gu8_ice_test_step)
	{
		case 0:

			 gu32_ice_test_timer++;

			 if(gu32_ice_test_timer >= 10)
			 {
				 gu32_ice_test_timer = 0;
				 gu8_ice_test_step++;				 
			 }
			 else{}

		 break;
		
		case 1:

			//key_ambient_water_select_job();
			gu8_ice_test_step++;

			break;


		case 2:

			gu32_ice_test_timer++;

			if(gu32_ice_test_timer >= 10)
			{
				gu32_ice_test_timer = 0;
				//water_extract_key();
				gu8_ice_test_step++;
			}
			 
			 break;

			 
		 break;

		 case 3:
		 	if( F_IceFull == SET )
		 	{
				gu8_ice_test_step++;
		 	}
			else {}			  
		  break;

		 case 4:

			 gu32_ice_test_timer++;

			 if(gu32_ice_test_timer >= 300)
			 {
				 ice_extraction_finish();
				 gu32_ice_test_timer = 0;
				 gu8_ice_test_step++;
			 }
			 else
			 {
				 ice_extraction_start();
			 }
    	    			  
		  break;
			
		case 5:
    			gu32_ice_test_timer++;
    
			if(gu32_ice_test_timer >= 18000)
			{
				gu32_ice_test_timer = 0;
				gu8_ice_test_step = 0;
			}
    		else {}
			 
		 break;

		default:

			 gu8_ice_test_step = 0;
			 gu32_ice_test_timer = 0;

		 break;
	}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_durable_test(void)
{
	if( gu8_durable_test_start == CLEAR )
	{
		gu16_durable_test_init_timer = 0;
		gu8_durable_test_step = 0;
		gu16_durable_test_timer = 0;
		return;
	}
	else{}
	
	if(gu8_Error_Code != 0)
	{
		return;
	}
	else{}

	if( F_FW_Version_Display_Mode == CLEAR )
	{
		gu8_durable_test_step = 0;
		gu16_durable_test_timer = 0;

		return;
	}
	else{}

	switch(gu8_durable_test_step)
	{
		case 0:

			gu16_durable_test_timer++;

			if(gu16_durable_test_timer >= 10)
			{
				gu16_durable_test_timer = 0;
				gu8_durable_test_step++;
			}
			else{}

			break;
		
		case 1:

			key_cold_water_select_job();
			gu8_durable_test_step++;

			break;

		case 2:

			gu16_durable_test_timer++;

			if(gu16_durable_test_timer >= 10)
			{
				gu16_durable_test_timer = 0;
				//u16Efluent_Time = 72;
				water_extract_key();
				gu8_durable_test_step++;
			}
			else{}

			break;

		case 3:

            if( F_WaterOut == CLEAR )
            {
    			gu16_durable_test_timer++;
    
    			if(gu16_durable_test_timer >= 10)
    			{
    				gu16_durable_test_timer = 0;
    				gu8_durable_test_step++;
    			}
    			else{}
    	    }
    	    else
    	    {
				gu16_durable_test_timer = 0;
    	    }

			break;

		case 4:

			gu16_durable_test_timer++;

			if(gu16_durable_test_timer >= 36000)
			{
				gu16_durable_test_timer = 0;
				gu8_durable_test_step = 0;
			}
			else{}
			
			break;


		default:

			gu8_durable_test_step = 0;
			gu16_durable_test_timer = 0;

			break;
	}
}


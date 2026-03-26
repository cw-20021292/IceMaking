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

void water_durable_test(void);

U16 gu16_durable_test_init_timer;
U16 gu16_durable_test_timer;
U16 gu16_durable_test_step;
U8 gu8_durable_test_start;

U16 gu16_aging_count;

U16 gu16_durable_test_step_old;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_durable_test(void)
{
    if( gu8_durable_test_start == CLEAR )
    {
        gu16_durable_test_init_timer = 0;
        gu16_durable_test_step = 0;
        gu16_durable_test_timer = 0;
        gu16_aging_count = 0;
        gu16_durable_test_step_old = 0;
        return;
    }
    else{}

    if(gu8_Error_Code != 0)
    {
        gu16_durable_test_step = 0;
        gu16_durable_test_timer = 0;
        gu16_durable_test_step_old = 0;
        return;
    }
    else{}

    if( F_FW_Version_Display_Mode == CLEAR )
    {
        gu16_durable_test_step = 0;
        gu16_durable_test_timer = 0;
        gu16_durable_test_step_old = 0;
        return;
    }
    else{}

    /*..hui [23-6-7오전 10:43:54] 저수위 or 냉수 10도이상 or 온수 70도 이하..*/
    if( ( gu8_Room_Water_Level == ROOM_LEVEL_LOW
          /*|| gu8_Cold_Temperature_One_Degree >= 10
          || gu8_Hot_Tank_Temperature_One_Degree <= 70 )*/
        || gu8_Cold_Temperature_One_Degree >= 13
        || gu8_Hot_Tank_Temperature_One_Degree <= 60 )
        && ( gu16_durable_test_step != 10 ) )
    {
        if( gu16_durable_test_step == 0
            || gu16_durable_test_step == 1
            || gu16_durable_test_step == 2 )
        {
            gu16_durable_test_step_old = 0;
        }
        else if( gu16_durable_test_step == 3
            || gu16_durable_test_step == 4 )
        {
            gu16_durable_test_step_old = 3;
        }
        else if( gu16_durable_test_step == 5
            || gu16_durable_test_step == 6 )
        {
            gu16_durable_test_step_old = 5;
        }
        else if( gu16_durable_test_step == 7
            || gu16_durable_test_step == 8 )
        {
            gu16_durable_test_step_old = 7;
        }
        else if( gu16_durable_test_step == 9 )
        {
            gu16_durable_test_step_old = 9;
        }

        gu16_durable_test_step = 10;
    }
    else{}


    switch( gu16_durable_test_step )
    {
        case 0:

            gu16_durable_test_timer++;

            if(gu16_durable_test_timer >= 10)
            {
                gu16_durable_test_timer = 0;
                gu16_durable_test_step++;
            }
            else{}

            break;

        case 1:

            key_cold_water_select_job();
            gu16_durable_test_step++;

            break;

        case 2:

            gu16_durable_test_timer++;

            if(gu16_durable_test_timer >= 10)
            {
                gu16_durable_test_timer = 0;
                water_extract_key();
                gu16_durable_test_step++;
            }
            else{}

            break;

        case 3:

            if( F_WaterOut == CLEAR )
            {
                gu16_durable_test_timer++;

                if(gu16_durable_test_timer >= 6000)
                {
                    gu16_durable_test_timer = 0;
                    key_ambient_water_select_job();
                    gu16_durable_test_step++;
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

            if(gu16_durable_test_timer >= 10)
            {
                gu16_durable_test_timer = 0;
                water_extract_key();

                gu16_durable_test_step++;
            }
            else{}

            break;

        case 5:

            if( F_WaterOut == CLEAR )
            {
                gu16_durable_test_timer++;

                if(gu16_durable_test_timer >= 6000)
                {
                    gu16_durable_test_timer = 0;
                    key_hot_water_select_job();
                    gu16_durable_test_step++;
                }
                else{}
            }
            else
            {
                gu16_durable_test_timer = 0;
            }

            break;

        case 6:

            gu16_durable_test_timer++;

            if(gu16_durable_test_timer >= 10)
            {
                gu16_durable_test_timer = 0;
                water_extract_key();

                gu16_durable_test_step++;
            }
            else{}

            break;

        case 7:

            if( F_WaterOut == CLEAR )
            {
                gu16_durable_test_timer++;

                if(gu16_durable_test_timer >= 6000)
                {
                    gu16_durable_test_timer = 0;
                    gu16_durable_test_step++;
                    gu16_aging_count++;

                    if( gu16_aging_count >= 19990 )
                    {
                        gu16_aging_count = 19990;
                    }
                    else{}
                }
                else{}
            }
            else
            {
                gu16_durable_test_timer = 0;
            }

            break;

        case 8:

            gu16_durable_test_timer++;

            if( gu16_durable_test_timer >= 100 )
            {
                ice_extraction_finish();
                gu16_durable_test_timer = 0;
                gu16_durable_test_step++;
            }
            else
            {
                ice_extraction_start();
            }

            break;

        case 9:

            gu16_durable_test_timer++;

            if(gu16_durable_test_timer >= 6000)
            {
                gu16_durable_test_timer = 0;
                gu16_durable_test_step = 0;
            }
            else{}

            break;

        case 10:

            /*if( gu8_Room_Water_Level == ROOM_LEVEL_FULL
               && gu8_Cold_Temperature_One_Degree < 10
               && gu8_Hot_Tank_Temperature_One_Degree > 70 )*/

            /*..hui [24-1-24오후 3:14:38] 30초 추가입수 완료 조건 추가..*/
            if( gu8_Room_Water_Level == ROOM_LEVEL_FULL
               && Bit0_Low_Water_Filling_State == CLEAR
               && gu8_Cold_Temperature_One_Degree <= 7
               && gu8_Hot_Tank_Temperature_One_Degree >= 80 )
            {
                gu16_durable_test_timer = 0;
                /*gu16_durable_test_step = 0;*/

                gu16_durable_test_step = gu16_durable_test_step_old;
            }
            else{}

            break;


        default:

            gu16_durable_test_step = 0;
            gu16_durable_test_timer = 0;

            break;
    }
}






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





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
#include    "display_fnd_right.h"


void fnd_right_normal_state(void);
void fnd_right_aging_count(void);
void fnd_right_display_oz(void);
void fnd_right_display_ml(void);

void fnd_right_error(void);
void fnd_right_uv(void);

void fnd_right_setting(void);
void fnd_right_button_set(void);

void fnd_right_all_lock(void);
void fnd_right_water_out(void);
void fnd_right_water_out_continue(void);
void fnd_right_ice_out(void);
void fnd_right_main_version(void);
void fnd_right_display_test(void);
void fnd_right_pba_test(void);
void fnd_right_uart_test(void);

U8 gu8_fnd_continue_timer;

U8 gu8_fnd_right_ice_step;
U8 gu8_fnd_right_ice_timer;
bit bit_return_ice;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_normal_state(void)
{
    if( gu8_durable_test_start == SET )
    {
        fnd_right_aging_count();
    }
    else
    {
        if( gu8_ml__oz_select == Oz_SELECT )
        {
            fnd_right_display_oz();
        }
        else /*if( gu8_ml__oz_select == mL_SELECT )*/
        {
            fnd_right_display_ml();
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_aging_count(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu16_aging_count < 10000 )
    {
        mu8_temporary_hundred = (U8)((gu16_aging_count / 1000) % 10);
        mu8_temporary_ten = (U8)((gu16_aging_count / 100) % 10);
        mu8_temporary_one = (U8)((gu16_aging_count / 10) % 10);
    }
    else
    {
        if( F_Wink_500ms == SET )
        {
            mu8_temporary_hundred = (U8)((gu16_aging_count / 1000) % 10);
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
        }

        mu8_temporary_ten = (U8)((gu16_aging_count / 100) % 10);
        mu8_temporary_one = (U8)((gu16_aging_count / 10) % 10);
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_display_oz(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_NUM_4;
    }
    else if(gu8Cup_level == CUP_LEVEL__6_OZ__175_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_NUM_6;
    }
    else if(gu8Cup_level == CUP_LEVEL__8_OZ__235_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_NUM_8;
    }
    else if(gu8Cup_level == CUP_LEVEL__10_OZ__295_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_1;
        mu8_temporary_one = DISPLAY_NUM_0;
    }
    else if(gu8Cup_level == CUP_LEVEL__12_OZ__355_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_1;
        mu8_temporary_one = DISPLAY_NUM_2;
    }
    else if(gu8Cup_level == CUP_LEVEL__14_OZ__415_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_1;
        mu8_temporary_one = DISPLAY_NUM_4;
    }
    else if(gu8Cup_level == CUP_LEVEL__16_OZ__475_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_1;
        mu8_temporary_one = DISPLAY_NUM_6;
    }
    else if(gu8Cup_level == CUP_LEVEL__20_OZ__590_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_2;
        mu8_temporary_one = DISPLAY_NUM_0;
    }
    #if 0
    else if(gu8Cup_level == CUP_LEVEL__32_OZ__945_ML)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_NUM_3;
        mu8_temporary_one = DISPLAY_NUM_2;
    }
    #endif
    else /*if(gu8Cup_level == CUP_LEVEL__CONTINUE)*/
    {
        mu8_temporary_hundred = DISPLAY_NUM_CONTINUE_100;
        mu8_temporary_ten = DISPLAY_NUM_CONTINUE_010;
        mu8_temporary_one = DISPLAY_NUM_CONTINUE_001;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_display_ml(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( gu8Cup_level == CUP_LEVEL__4_OZ__120_ML )
    {
        mu8_temporary_hundred = DISPLAY_NUM_1;
        mu8_temporary_ten = DISPLAY_NUM_2;
        mu8_temporary_one = DISPLAY_NUM_0;
    }
    else if(gu8Cup_level == CUP_LEVEL__6_OZ__175_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_1;
        mu8_temporary_ten = DISPLAY_NUM_7;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__8_OZ__235_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_2;
        mu8_temporary_ten = DISPLAY_NUM_3;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__10_OZ__295_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_2;
        mu8_temporary_ten = DISPLAY_NUM_9;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__12_OZ__355_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_3;
        mu8_temporary_ten = DISPLAY_NUM_5;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__14_OZ__415_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_4;
        mu8_temporary_ten = DISPLAY_NUM_1;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__16_OZ__475_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_4;
        mu8_temporary_ten = DISPLAY_NUM_7;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    else if(gu8Cup_level == CUP_LEVEL__20_OZ__590_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_5;
        mu8_temporary_ten = DISPLAY_NUM_9;
        mu8_temporary_one = DISPLAY_NUM_0;
    }
    #if 0
    else if(gu8Cup_level == CUP_LEVEL__32_OZ__945_ML)
    {
        mu8_temporary_hundred = DISPLAY_NUM_9;
        mu8_temporary_ten = DISPLAY_NUM_4;
        mu8_temporary_one = DISPLAY_NUM_5;
    }
    #endif
    else /*if(gu8Cup_level == CUP_LEVEL__CONTINUE)*/
    {
        mu8_temporary_hundred = DISPLAY_NUM_CONTINUE_100;
        mu8_temporary_ten = DISPLAY_NUM_CONTINUE_010;
        mu8_temporary_one = DISPLAY_NUM_CONTINUE_001;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_error(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_uv(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( bit_uv_display_finish == SET )
    {
        bit_uv_display_finish = CLEAR;
        gu16_uv_time_flick_timer = UV_PROGRESS_DISPLAY_TIME;
    }
    else{}

    mu8_flick_state = uv_time_display_timer(UV_PROGRESS_DISPLAY_TIME);

    if( mu8_flick_state == SET )
    {
        if( gu8_display_uv_reamin_minute < 100 )
        {
            if( gu8_display_uv_reamin_minute < 10 )
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = DISPLAY_OFF;
                mu8_temporary_one = gu8_display_uv_reamin_minute;
            }
            else
            {
                mu8_temporary_hundred = DISPLAY_OFF;
                mu8_temporary_ten = (gu8_display_uv_reamin_minute / 10);
                mu8_temporary_one = (gu8_display_uv_reamin_minute % 10);
            }
        }
        else
        {
            mu8_temporary_hundred = (U8)((gu8_display_uv_reamin_minute / 100) % 10);
            mu8_temporary_ten = (U8)((gu8_display_uv_reamin_minute / 10) % 10);
            mu8_temporary_one = (U8)(gu8_display_uv_reamin_minute % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        mu8_temporary_one = DISPLAY_OFF;
    }


    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_setting(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_button_set(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_all_lock(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_water_out(void)
{
    if( u8Extract_Continue == SET )
    {
        fnd_right_water_out_continue();
    }
    else
    {
        fnd_right_normal_state();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_water_out_continue(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    gu8_fnd_continue_timer++;

    if( gu8_fnd_continue_timer <= 3 )
    {
        mu8_temporary_hundred = 16;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 6 )
    {
        mu8_temporary_hundred = 48;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 9 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 12 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 15 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 1;
    }
    else if( gu8_fnd_continue_timer <= 18 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 3;
    }
    else if( gu8_fnd_continue_timer <= 21 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 7;
    }
    else if( gu8_fnd_continue_timer <= 24 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 1;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 27 )
    {
        mu8_temporary_hundred = 49;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 30 )
    {
        mu8_temporary_hundred = 57;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 33 )
    {
        mu8_temporary_hundred = 41;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 36 )
    {
        mu8_temporary_hundred = 9;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 39 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 9;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 42 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 15;
    }
    else if( gu8_fnd_continue_timer <= 45 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 14;
    }
    else if( gu8_fnd_continue_timer <= 48 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 12;
    }
    else if( gu8_fnd_continue_timer <= 51 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 8;
    }
    else if( gu8_fnd_continue_timer <= 54 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 8;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 57 )
    {
        mu8_temporary_hundred = 8;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
    }
    else if( gu8_fnd_continue_timer <= 60 )
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
        gu8_fnd_continue_timer = 0;
    }
    else
    {
        mu8_temporary_hundred = 0;
        mu8_temporary_ten = 0;
        mu8_temporary_one = 0;
        gu8_fnd_continue_timer = 0;
    }

    fnd_right_out( DIRECT_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_ice_out(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( bit_return_ice == SET )
    {
        /*..hui [23-5-11오후 2:52:00] 물 추출 후 얼음추출 화면으로 돌아갈때 자연스럽게 돌아가기위해..*/
        if( gu8_fnd_left_ice_timer == 0 )
        {
            bit_return_ice = CLEAR;
        }
        else{}

        /*..hui [23-5-12오후 12:31:31] FND 끈 상태로 대기..*/
        gu8_fnd_right_ice_step = 0;
    }
    else
    {
        gu8_fnd_right_ice_step = gu8_fnd_left_ice_step;
    }

    //gu8_fnd_right_ice_step = gu8_fnd_left_ice_step;

    switch( gu8_fnd_right_ice_step )
    {
        case 0 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 1 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 2 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 3 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 4 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 5 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_OFF;

        break;

        case 6 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

        break;

        case 7 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

        break;

        case 8 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

        break;

        case 9 :

            mu8_temporary_hundred = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_UP;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

        break;

        case 10 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_NUM_SQUARE_DOWN;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_UP;

        break;

        case 11 :

            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_SQUARE_DOWN;

        break;



        default :

            gu8_fnd_left_ice_step = 0;
            gu8_fnd_left_ice_timer = 0;

        break;
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_main_version(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    mu8_temporary_hundred = (U8)((Main_FW_Version_Main / 10) % 10);
    mu8_temporary_ten = (U8)(Main_FW_Version_Main % 10);
    mu8_temporary_one = (U8)Main_FW_Version_Sub;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_display_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;

    if( bit_display_test_filter_reed_error == SET)
    {
        mu8_temporary_hundred = DISPLAY_OFF;
        mu8_temporary_ten = DISPLAY_OFF;
        /*mu8_temporary_one = DISPLAY_OFF;*/
        mu8_temporary_one = gu8_display_reed_test_step;

        fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

    }
    else
    {

        if( gu8_display_test_error != 0 )
        {
             mu8_temporary_hundred = DISPLAY_OFF;
             mu8_temporary_ten = DISPLAY_OFF;
             mu8_temporary_one = DISPLAY_OFF;

             fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
             return;
        }
        else{}

        if( gu8_water_ext_test_input == 0 )
        {
            mu8_temporary_hundred = DISPLAY_NUM_8;
            mu8_temporary_ten = DISPLAY_NUM_8;
            mu8_temporary_one = DISPLAY_NUM_8;

            fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
            gu8_right_fnd_off_timer = 0;
        }
        else
        {
            gu8_right_fnd_off_timer++;

            if( gu8_right_fnd_off_timer <= 2 )
            {
                mu8_temporary_hundred = 0x5F;
                mu8_temporary_ten = 0x5F;
                mu8_temporary_one = 0x5F;
            }
            else if( gu8_right_fnd_off_timer <= 4 )
            {
                mu8_temporary_hundred = 0x5E;
                mu8_temporary_ten = 0x5E;
                mu8_temporary_one = 0x5E;
            }
            else if( gu8_right_fnd_off_timer <= 6 )
            {
                mu8_temporary_hundred = 0x5C;
                mu8_temporary_ten = 0x5C;
                mu8_temporary_one = 0x5C;
            }
            else if( gu8_right_fnd_off_timer <= 8 )
            {
                mu8_temporary_hundred = 0x58;
                mu8_temporary_ten = 0x58;
                mu8_temporary_one = 0x58;
            }
            else if( gu8_right_fnd_off_timer <= 10 )
            {
                mu8_temporary_hundred = 0x50;
                mu8_temporary_ten = 0x50;
                mu8_temporary_one = 0x50;
            }
            else if( gu8_right_fnd_off_timer <= 12 )
            {
                mu8_temporary_hundred = 0x40;
                mu8_temporary_ten = 0x40;
                mu8_temporary_one = 0x40;
            }
            else
            {
                gu8_right_fnd_off_timer = 13;

                if( F_cds_detect == SET && F_Wink_500ms == SET )
                {
                    mu8_temporary_hundred = 0x7F;
                    mu8_temporary_ten = 0x7F;
                    mu8_temporary_one = 0x7F;
                }
                else
                {
                    mu8_temporary_hundred = 0x00;
                    mu8_temporary_ten = 0x00;
                    mu8_temporary_one = 0x00;
                }

            }

            fnd_right_out( DIRECT_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
        }

    }



}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_pba_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    mu8_temporary_hundred = DISPLAY_NUM_8;
    mu8_temporary_ten = DISPLAY_NUM_8;
    mu8_temporary_one = DISPLAY_NUM_8;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_uart_test(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
    {
        mu8_temporary_hundred = (U8)((gu8_Filter_Flow_1sec / 100) % 10);
        mu8_temporary_ten = (U8)((gu8_Filter_Flow_1sec / 10) % 10);
        mu8_temporary_one = (U8)(gu8_Filter_Flow_1sec % 10);
    }
    else
    {
        if( bit_manual_test_start == SET )
        {
            if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
            {
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_E;
                mu8_temporary_ten = (U8)((gu8_Eva_Cold_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Eva_Cold_Temperature_One_Degree % 10);
            }
            else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
            {
                mu8_temporary_hundred = DISPLAY_NUM_LARGE_C;
                mu8_temporary_ten = (U8)((gu8_Cold_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Cold_Temperature_One_Degree % 10);
            }
            else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
            {
                mu8_temporary_hundred = DISPLAY_NUM_SMALL_o;
                mu8_temporary_ten = (U8)((gu8_Amb_Temperature_One_Degree / 10) % 10);
                mu8_temporary_one = (U8)(gu8_Amb_Temperature_One_Degree % 10);
            }
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_OFF;
        }
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/






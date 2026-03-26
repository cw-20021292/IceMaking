/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "extract_control.h"

void water_extract_control(void);
void user_water_out(void);
void plus_user_water( U16 mu16_water_acc );
void plus_user_low_water( U16 mu16_water_acc );
void calc_feed_water(void);
void minus_user_water( void );
void water_out_compensation( void );
void water_out_compensation_normal( void );
void water_out_compensation_low_water( void );






U8 gu8_effluent_control_timer;
bit F_Effluent_OK;

U16 gu16_user_water_out_count;
U16 gu16_feed_timer;
U16 gu16_compensation_time;

U16 gu16_user_low_water_out_count;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_control(void)
{
    if(F_WaterOut == SET)
    {
        gu16Water_Extract_Timer++;

        if(gu16Water_Extract_Timer >= u16Efluent_Time)
        {
            F_WaterOut = CLEAR;
            gu16Water_Extract_Timer = 0;
            u16Efluent_Time = 0;

            /*BuzStep(BUZZER_EFFLUENT_END);*/
            play_melody_extract_complete_194();

            /*..hui [18-1-11오후 11:12:11] 연속추출 정지..*/
            u8Extract_Continue = CLEAR;

            /*..hui [18-3-14오후 3:50:40] 정량추출 종료..*/
            F_WaterOut_Disable_State = SET;

            user_water_out();

            /*hot_extract_return();*/
        }
        else
        {
            /*..hui [23-5-9오전 11:46:25] 온수 추출중 저수위일 경우 정지..*/
            /*..hui [23-9-1오후 4:31:21] 온수, 정수도 추출중에 저수위되면 추출 정지..*/
            if( u8WaterOutState == HOT_WATER_SELECT || u8WaterOutState == PURE_WATER_SELECT )
            {
                if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
                {
                    play_melody_warning_197();

                    F_WaterOut = CLEAR;
                    gu16Water_Extract_Timer = 0;
                    u16Efluent_Time = 0;

                    /*..hui [18-1-11오후 11:12:11] 연속추출 정지..*/
                    u8Extract_Continue = CLEAR;

                    /*..hui [18-3-14오후 3:50:40] 정량추출 종료..*/
                    F_WaterOut_Disable_State = SET;

                    /*hot_extract_return();*/
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        gu16Water_Extract_Timer = 0;

        /*..hui [18-1-22오후 5:37:49] 냉수 탱크 청소모드 해제..*/
        /*..hui [20-1-30오전 10:13:58] 피드밸브 동작 유지, 냉각/제빙 동작은 코디닥터 점검기능에서 한다..*/
        F_ColdConty = CLEAR;
    }

    calc_feed_water();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void user_water_out(void)
{
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        switch(gu8Cup_level)
        {
            case CUP_LEVEL__4_OZ__120_ML:

                plus_user_low_water( 1 );

                break;

            case CUP_LEVEL__6_OZ__175_ML:

                plus_user_low_water( 1 );

                break;

            case CUP_LEVEL__8_OZ__235_ML:

                plus_user_low_water( 2 );

                break;

            case CUP_LEVEL__10_OZ__295_ML:

                plus_user_low_water( 2 );

                break;

            case CUP_LEVEL__12_OZ__355_ML:

                plus_user_low_water( 3 );

                break;

            case CUP_LEVEL__14_OZ__415_ML:

                plus_user_low_water( 3 );

                break;

            case CUP_LEVEL__16_OZ__475_ML:

                plus_user_low_water( 4 );

                break;

            case CUP_LEVEL__20_OZ__590_ML:

                plus_user_low_water( 5 );

                break;

            #if 0
            case CUP_LEVEL__32_OZ__945_ML:

                plus_user_low_water( 7 );

                break;
            #endif

            default:


                break;
        }


    }
    else
    {
        switch(gu8Cup_level)
        {
            case CUP_LEVEL__4_OZ__120_ML:

                plus_user_water( 1 );

                break;

            case CUP_LEVEL__6_OZ__175_ML:

                plus_user_water( 1 );

                break;

            case CUP_LEVEL__8_OZ__235_ML:

                plus_user_water( 2 );

                break;

            case CUP_LEVEL__10_OZ__295_ML:

                plus_user_water( 2 );

                break;

            case CUP_LEVEL__12_OZ__355_ML:

                plus_user_water( 3 );

                break;

            case CUP_LEVEL__14_OZ__415_ML:

                plus_user_water( 3 );

                break;

            case CUP_LEVEL__16_OZ__475_ML:

                plus_user_water( 4 );

                break;

            case CUP_LEVEL__20_OZ__590_ML:

                plus_user_water( 5 );

                break;

            #if 0
            case CUP_LEVEL__32_OZ__945_ML:

                plus_user_water( 7 );

                break;
            #endif

            default:


                break;
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void plus_user_water( U16 mu16_water_acc )
{
    /*..hui [23-7-12오후 7:21:04] 냉수탱크 용량 3.4리터..*/
    gu16_user_water_out_count += mu16_water_acc;

    if(gu16_user_water_out_count >= USER_WATER_MAX_COUNT)
    {
        gu16_user_water_out_count = USER_WATER_MAX_COUNT;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void plus_user_low_water( U16 mu16_water_acc )
{
    /*..hui [23-7-12오후 7:21:04] 냉수탱크 용량 3.4리터..*/
    gu16_user_low_water_out_count += mu16_water_acc;

    if(gu16_user_low_water_out_count >= USER_LOW_WATER_MAX_COUNT)
    {
        gu16_user_low_water_out_count = USER_LOW_WATER_MAX_COUNT;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_feed_water(void)
{
    /*..hui [23-7-14오전 11:38:00] 초기 수위센서 감지전에 저수위 감지되어 맥스값으로 저장되는현상떔에....*/
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        gu16_feed_timer = 0;
        gu16_user_water_out_count = 0;
        gu16_user_low_water_out_count = 0;
        return;
    }
    else{}


    /*..hui [23-5-9오후 2:58:51] 만수위 이거나 수위센서 에러상태일 경우 초기화..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL || gu8_Room_Water_Level == ROOM_LEVEL_ERROR )
    {
        gu16_feed_timer = 0;
        gu16_user_water_out_count = 0;
        gu16_user_low_water_out_count = 0;
        return;
    }
    else if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        /*..hui [23-5-12오전 9:27:12] 저수위 미감지 시점에서 최대값으로 고정해줌..*/
        /*gu16_feed_timer = 0;*/
        gu16_user_water_out_count = USER_WATER_MAX_COUNT;
        /*return;*/
    }
    else{}

    /*..hui [23-5-9오후 2:52:26] FEED 열려있고 NOS 닫혀있는 상태..*/
    if( bit_feed_output == SET && bit_nos_output == CLEAR )
    {
        gu16_feed_timer++;

        if( gu16_feed_timer >= FEED_WATER_TIME_1_MIN )
        {
            gu16_feed_timer = 0;
            /*..hui [23-5-9오후 2:56:27] 1분당 120ml씩 삭제..*/
            minus_user_water();
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
void minus_user_water( void )
{
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        if( gu16_user_low_water_out_count > 0 )
        {
            gu16_user_low_water_out_count = gu16_user_low_water_out_count - 1;
        }
        else
        {
            gu16_user_low_water_out_count = 0;
        }

    }
    else
    {
        if( gu16_user_water_out_count > 0 )
        {
            gu16_user_water_out_count = gu16_user_water_out_count - 1;
        }
        else
        {
            gu16_user_water_out_count = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_out_compensation( void )
{
    /*..hui [23-10-27오후 3:03:09] 43도는 미적용 물량때문에 온도 편차가 너무 큼..*/
    if( u8WaterOutState == HOT_WATER_SELECT
        && gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )
    {
        return;
    }
    else{}



    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        water_out_compensation_low_water();
    }
    else
    {
        water_out_compensation_normal();
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_out_compensation_normal( void )
{
    U8 mu8_max_time = 0;
    U16 mu16_calc_a = 0;

    /*..hui [23-7-13오후 12:11:55] 저수위 미만일때는 따로..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        return;
    }
    else{}


    if( gu16_user_water_out_count <= 4 )
    {
        /*..hui [23-7-12오후 7:37:34] 5프로 추가..*/
        /*mu16_calc_a = (U16)((u16Efluent_Time * 5) / 100);*/
    }
    else if( gu16_user_water_out_count <= 8 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 4;
    }
    else if( gu16_user_water_out_count <= 12 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 7;
    }
    else if( gu16_user_water_out_count <= 15 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 10;
    }
    else /*if( gu16_user_water_out_count <= USER_WATER_MAX_COUNT )*/
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 11;
    }

    gu16_compensation_time = mu16_calc_a;

    mu8_max_time = 30;

    /*..hui [23-5-10오전 10:12:07] 최대 보상시간 이상일 경우 제한..*/
    if( gu16_compensation_time >= mu8_max_time )
    {
        gu16_compensation_time = mu8_max_time;
    }
    else{}

    u16Efluent_Time = u16Efluent_Time + gu16_compensation_time;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_out_compensation_low_water( void )
{
    U8 mu8_max_time = 0;
    U16 mu16_calc_a = 0;


    if( gu16_user_low_water_out_count <= 3 )
    {
        /*..hui [23-7-12오후 7:37:34] 5프로 추가..*/
        /*mu16_calc_a = (U16)((u16Efluent_Time * 5) / 100);*/
    }
    else if( gu16_user_low_water_out_count <= 6 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 4;
    }
    else if( gu16_user_low_water_out_count <= 9 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        mu16_calc_a = 7;
    }
    else if( gu16_user_low_water_out_count <= 12 )
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        //mu16_calc_a = 11;
        mu16_calc_a = 12;
    }
    else /*if( gu16_user_low_water_out_count <= USER_LOW_WATER_MAX_COUNT )*/
    {
        //mu16_calc_a = (U16)((u16Efluent_Time * 10) / 100);
        //mu16_calc_a = 15;
        mu16_calc_a = 16;
    }

    gu16_compensation_time = mu16_calc_a;

    mu8_max_time = 30;

    /*..hui [23-5-10오전 10:12:07] 최대 보상시간 이상일 경우 제한..*/
    if( gu16_compensation_time >= mu8_max_time )
    {
        gu16_compensation_time = mu8_max_time;
    }
    else{}

    u16Efluent_Time = u16Efluent_Time + gu16_compensation_time;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



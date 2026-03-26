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
#include    "hot_control.h"





void hot_control(void);
//void init_flow_valve(void);
//void mix_motor_control(void);
//void control_flow_valve(void);
//void pure_water_flow_control(void);
//void hot_water_85_degree_control(void);
//void prepare_85_degree(void);
//void mainheating_85_degree(void);

//void hot_water_77_degree_control(void);
//void prepare_77_degree(void);
//void mainheating_77_degree(void);
//void hot_water_43_degree_control(void);
//void prepare_43_degree(void);
//void mainheating_43_degree(void);

bit bit_init_flow_valve;

U8 gu8_Hot_Target_Temp;
U8 gu8_Hot_Preheat_Temp;

bit bit_first_adjust;
bit bit_prepare_finish;


bit bit_direct_pure_water;
U8 gu8_flow_control_timer;


U8 gu8_hot_45_moving_finish;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_control(void)
{
    if( F_FW_Version_Display_Mode == CLEAR )
    {
        return;
    }
    else{}

    /*..hui [23-6-19오후 2:06:04] 온수 예열 관련 디스플레이 제어..*/
    hot_prepare();
    /*hot_preheating_control();*/
    /*hot_prepare_stage();*/

    /*..hui [23-6-19오후 2:07:14] 믹싱 스텝모터 제어..*/
    /*mix_motor_control();*/
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void init_flow_valve(void)
{
    if( u8WaterOutState == HOT_WATER_SELECT )
    {
        if( F_WaterOut == SET )
        {
            bit_init_flow_valve = SET;
        }
        else{}
    }
    else
    {
        if( bit_init_flow_valve == SET )
        {
            bit_init_flow_valve = CLEAR;
            /*run_init_flow();*/
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void mix_motor_control(void)
{
    /*init_flow_valve();*/
    /*control_flow_valve();*/

    /*ControlMixFlow();*/
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void control_flow_valve(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;

    if( F_WaterOut == SET )
    {
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            if( gu8_hot_setting_temperature == HOT_SET_TEMP_1__110_oF_43_oC )
            {
                hot_water_43_degree_control();
            }
            else
            {
                bit_first_adjust = SET;
                gu8_hot_45_moving_finish = CLEAR;
            }
        }
        else
        {
            bit_first_adjust = SET;
            gu8_hot_45_moving_finish = CLEAR;
        }
    }
    else
    {
        bit_first_adjust = CLEAR;
        bit_direct_pure_water = 0;
        gu8_flow_control_timer = 0;
        gu8_hot_45_moving_finish = CLEAR;
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void pure_water_flow_control(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_adjust = 0;
    U16 mu16_adjust = 0;

    if( bit_first_adjust == SET )
    {
        return;
    }
    else{}

    #if 0
    if( gu8_Cold_Temperature_One_Degree >= 23 )
    {
        /*..hui [23-6-16오후 5:30:37] 냉수온도 25도 이상에서는 냉수로 그냥 추출..*/
        bit_direct_pure_water = SET;
        bit_first_adjust = SET;
    }
    else{}
    #endif

    #if 0
    mu8_a = TARGET_ROOM_27_TEMP - gu8_Cold_Temperature_One_Degree;
    mu8_b = gu8_Hot_Tank_Temperature_One_Degree - TARGET_ROOM_27_TEMP;

    f32_c = (F32)((F32)mu8_b / mu8_a);

    f32_adjust = (F32)((F32)MAX_INCREASE_FLOW / f32_c);
    mu16_adjust = (U16)f32_adjust;

    if( bit_first_adjust == CLEAR )
    {
        bit_first_adjust = SET;
        run_target_flow( mu16_adjust );
    }
    else{}
    #endif

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_water_85_degree_control(void)
{
    if( bit_first_adjust == CLEAR )
    {
        prepare_85_degree();
    }
    else
    {
        //if( pVALVE_ROOM_OUT ==  1 )
        if( bit_prepare_finish == SET )
        {
            mainheating_85_degree();
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void prepare_85_degree(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if( bit_first_adjust == SET )
    {
        return;
    }
    else{}

    mu16_adjust = 850;

    run_increase_flow( mu16_adjust );

    bit_first_adjust = SET;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void mainheating_85_degree(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_adjust = 0;
    U16 mu16_max_time = 0;
    U8 mu8_stable_timr = 0;
    U16 mu16_adjust = 0;

    gu8_Hot_Target_Temp = 77;

    mu8_a = gu8_Hot_Target_Temp - gu8_Cold_Temperature_One_Degree;
    mu8_b = gu8_Hot_Tank_Temperature_One_Degree - gu8_Hot_Target_Temp;

    f32_c = (F32)((F32)mu8_b / mu8_a);

    f32_adjust = (F32)((F32)MAX_INCREASE_FLOW / f32_c);
    mu16_adjust = (U16)f32_adjust;

    ///////gu8_Mixing_Out_Temperature_One_Degree

    mu8_stable_timr = 5;

    if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
    {
        gu8_flow_control_timer++;

        if( gu8_flow_control_timer >= mu8_stable_timr )
        {
            gu8_flow_control_timer = 0;
        }
        else
        {
            return;
        }
    }
    else
    {
        gu8_flow_control_timer = 0;
        return;
    }

    run_target_flow( mu16_adjust );
}
#endif




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_water_77_degree_control(void)
{
    if( bit_first_adjust == CLEAR )
    {
        prepare_77_degree();
    }
    else
    {
        if( pVALVE_ROOM_OUT ==  1 )
        {
            mainheating_77_degree();
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void prepare_77_degree(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if( bit_first_adjust == SET )
    {
        return;
    }
    else{}

    mu16_adjust = 850;

    run_increase_flow( mu16_adjust );

    bit_first_adjust = SET;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void mainheating_77_degree(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_adjust = 0;
    U16 mu16_max_time = 0;
    U8 mu8_stable_timr = 0;
    U16 mu16_adjust = 0;

    gu8_Hot_Target_Temp = 77;

    mu8_a = gu8_Hot_Target_Temp - gu8_Cold_Temperature_One_Degree;
    mu8_b = gu8_Hot_Tank_Temperature_One_Degree - gu8_Hot_Target_Temp;

    f32_c = (F32)((F32)mu8_b / mu8_a);

    f32_adjust = (F32)((F32)MAX_INCREASE_FLOW / f32_c);
    mu16_adjust = (U16)f32_adjust;

    ///////gu8_Mixing_Out_Temperature_One_Degree

    mu8_stable_timr = 5;

    if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
    {
        gu8_flow_control_timer++;

        if( gu8_flow_control_timer >= mu8_stable_timr )
        {
            gu8_flow_control_timer = 0;
        }
        else
        {
            return;
        }
    }
    else
    {
        gu8_flow_control_timer = 0;
        return;
    }

    run_target_flow( mu16_adjust );
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void hot_water_43_degree_control(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if( bit_first_adjust == CLEAR )
    {
        prepare_43_degree();
    }
    else
    {
        if( pVALVE_ROOM_OUT == SET )
        {
            mainheating_43_degree();
        }
        else{}
    }
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void prepare_43_degree(void)
{
    U16 mu16_adjust = 0;
    U8 mu8_target = 0;
    U8 mu8_stable_timr = 0;

    if( bit_first_adjust == SET )
    {
        return;
    }
    else{}

    /*..hui [23-7-12오후 5:39:27] 초기화중이었다면 리턴..*/
    if( gu8_hot_flow_mode == FLOW_MODE_INIT )
    {
        return;
    }
    else{}

    if( gu8_Hot_Tank_Temperature_One_Degree >= 70 )
    {
        mu16_adjust = 500;
    }
    else if( gu8_Hot_Tank_Temperature_One_Degree >= 60 )
    {
        mu16_adjust = 310;
    }
    else if( gu8_Hot_Tank_Temperature_One_Degree >= 50 )
    {
        mu16_adjust = 220;
    }
    else
    {
        if( gu8_Hot_Tank_Temperature_One_Degree <= 47 )
        {
            mu16_adjust = 0;
        }
        else
        {
            mu16_adjust = 160;
        }
    }

    /*run_target_flow( mu16_adjust );*/

    bit_first_adjust = SET;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void mainheating_43_degree(void)
{
    U8 mu8_a = 0;
    U8 mu8_b = 0;
    F32 f32_c = 0;
    F32 f32_adjust = 0;
    U16 mu16_max_time = 0;
    U8 mu8_stable_timr = 0;
    U16 mu16_adjust = 0;

    gu8_Hot_Target_Temp = 43;

    if( gu8_Mixing_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp + 7
       || gu8_Mixing_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 7)
    {
        mu16_adjust = 40;
    }
    else if( gu8_Mixing_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp + 5
       || gu8_Mixing_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 5)
    {
        mu16_adjust = 30;
    }
    else if( gu8_Mixing_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp + 3
       || gu8_Mixing_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 3)
    {
        mu16_adjust = 20;
    }
    else
    {
        mu16_adjust = 10;
    }

    mu8_stable_timr = 4;

    if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
    {
        gu8_flow_control_timer++;

        if( gu8_flow_control_timer >= mu8_stable_timr )
        {
            gu8_flow_control_timer = 0;
        }
        else
        {
            return;
        }
    }
    else
    {
        gu8_flow_control_timer = 0;
        return;
    }

    if( gu8_Mixing_Out_Temperature_One_Degree >= gu8_Hot_Target_Temp + 2 )
    {
        /*run_increase_flow( mu16_adjust );*/
    }
    else if( gu8_Mixing_Out_Temperature_One_Degree <= gu8_Hot_Target_Temp - 2 )
    {
        /*run_decrease_flow( mu16_adjust );*/
    }
    else{}
}
#endif


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


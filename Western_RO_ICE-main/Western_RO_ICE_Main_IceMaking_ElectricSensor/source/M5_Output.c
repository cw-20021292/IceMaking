/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Output.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M5_Output.h"

void Output(void);
//void output_swing_bar(void);
//void IceWaterExtrate(void);
//void output_feed_valve(void);
void output_valve_ice_tray(void) ;
//void CyclePump(void);
//void start_drain_pump( U16 u16_data );
//void stop_drain_pump( void );
void output_valve(void);
void output_pump(void);








bit F_IceWaterExt;
U8 gu8IceWaterExtDelay;
bit F_IceWaterExt_Set;


bit F_LineTestEnd;


U8 u8_system_init_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Output(void)
{
    output_swing_bar();

    output_ac_motor();

    output_comp_control();

    output_fan();

    output_pump();

    output_valve();

    ControlGasSwitch();

    /*..hui [23-4-25오후 5:22:21] 스케일 제거용 RO 드레인 스텝모터..*/
    ControlRoDrain();

    /*..hui [19-10-24오후 7:59:26] UV 센서 기능 추가..*/
    output_ice_tank_uv();
    output_water_tank_uv();
    output_ice_tray_uv();
    /*..hui [24-2-14오후 3:49:08] 얼음탱크 앞쪽 UV 추가..*/
    output_ice_tank_front_uv();

    /*..hui [23-6-1오후 3:10:46] 디스플레이 남은시간 표시용..*/
    calc_uv_remain_time();

    /*..hui [19-12-19오후 2:15:31] 정수/냉수 센서 전원 ON/OFF 기능 추가..*/
    output_temp_power();

    /*..hui [23-3-24오전 11:26:27] 부스트 펌프 기능 추가..*/
    /*output_boost_pump();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_pump(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    output_drain_pump();

    /*..hui [23-2-6오전 11:00:45] 트레이 펌프.. 온수 저탕식으로 변경..*/
    output_tray_pump();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve(void)
{
    /*..hui [19-7-18오후 5:01:36] 센서 다 읽을때까지 기다린다..*/
    #if 0
    if(u8_system_init_timer < 50)
    {
        u8_system_init_timer++;
        return;
    }
    else
    {
        u8_system_init_timer = 50;
    }
    #endif

    if(u8_system_init_timer < 30)
    {
        u8_system_init_timer++;
        return;
    }
    else
    {
        u8_system_init_timer = 30;
    }

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /*..hui [23-2-28오전 9:39:51] 에어벤트 밸브.. 소음 이슈로 래치밸브 -> 피드밸브로 교체..*/
    output_valve_air_vent();

    /*..hui [19-6-21오후 4:38:48] 피드밸브 출력..*/
    output_valve_feed();
    /*..hui [19-6-21오후 4:38:53] 노스밸브 출력..*/
    output_valve_nos();
    /*..hui [19-6-21오후 4:39:01] 정/냉/온수 추출 밸브 출력..*/
    output_valve_extract();
    /*..hui [19-6-21오후 4:39:09] 아이스 트레이 입수밸브 출력..*/
    output_valve_ice_tray();

    output_cold_drain_valve();

    /*..hui [23-2-28오후 5:45:26] 플러싱 유로전환 밸브..*/
    /*..hui [23-9-20오전 9:44:51] 유로전환 밸브 -> FEED 밸브로 변경..*/
    output_valve_flushing_feed();

    /*..hui [23-9-20오전 9:44:58] 유로전환 NOS밸브 추가..*/
    output_valve_flushing_nos();

    /*..hui [23-2-28오후 5:45:39] 얼음 살균 온수 입수 밸브..*/
    output_valve_hot_in();

    /*..hui [23-2-28오후 5:45:52] 온수 오버히팅 NOS 밸브..*/
    output_valve_overheat_nos();

    /*..hui [23-2-28오후 5:46:09] 얼음 살균 밸브 Right..*/
    output_valve_ster_out_right();

    /*..hui [23-5-22오후 2:39:12] 얼음 살균 밸브 Left..*/
    output_valve_ster_out_left();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



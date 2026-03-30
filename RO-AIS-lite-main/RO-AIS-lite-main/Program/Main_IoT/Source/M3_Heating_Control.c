/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Display.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M3_Heating_Control.h"

void Heating_Control(void);
void Ice_Heater_Control(void);
void tank_water_heater_control(void);




U16 gu16HeaterOffTemp;
U16 gu16HeaterOnTemp;
U16 gu16HeaterSaveOnTemp;
U16 gu16HeaterNoUseOnTemp;
U8 gu8HeaterOffDelay;


U8 gu8HeaterControlCnt;


TYPE_BYTE          U8IceHeaterONB;
#define            u8IceHeaterON                         U8IceHeaterONB.byte
#define            Bit0_Ice_Making_Heater_On_State       U8IceHeaterONB.Bit.b0
#define            Bit1_Over_Ice_Melt_State              U8IceHeaterONB.Bit.b1
#define            Bit2_Ice_Make_Init_On_State           U8IceHeaterONB.Bit.b2



TYPE_BYTE          U8IceHeaterOFFB;
#define            u8IceHeaterOFF                        U8IceHeaterOFFB.byte
#define            Bit0_Ice_Disable_Error_Off_State      U8IceHeaterOFFB.Bit.b0
#define            Bit1_Tray_Dual_Error_Check_State      U8IceHeaterOFFB.Bit.b1
#define            Bit2_Tray_Move_Error_State            U8IceHeaterOFFB.Bit.b2
#define            Bit3_Non_Ice_Make_State               U8IceHeaterOFFB.Bit.b3



TYPE_WORD          U16HotHeaterOnW;
#define            u16HotHeaterOn                            U16HotHeaterOnW.word
#define            u16HotHeater_L                            U16HotHeaterOnW.byte[0]
#define            u16HotHeater_H                            U16HotHeaterOnW.byte[1]
#define            Bit0_Hot_Heating_State                    U16HotHeaterOnW.Bit.b0





TYPE_WORD          U16HotHeaterOffW;
#define            u16HotHeaterOff                           U16HotHeaterOffW.word
#define            u16HotHeaterOff_L                         U16HotHeaterOffW.byte[0]
#define            u16HotHeaterOff_H                         U16HotHeaterOffW.byte[1]
#define            Bit0_First_Low_Water_State                U16HotHeaterOffW.Bit.b0
#define            Bit1_Hot_Setting_Off_State                U16HotHeaterOffW.Bit.b1
#define            Bit2_Hot_Error_State                      U16HotHeaterOffW.Bit.b2
#define            Bit3_Low_Water_Error_State                U16HotHeaterOffW.Bit.b3
#define            Bit4_Room_Over_Heat_State                 U16HotHeaterOffW.Bit.b4
#define            Bit5_Hot_Safety_State                     U16HotHeaterOffW.Bit.b5


U8 gu8_Hot_Target_Temp;
U8 gu8_Hot_Preheat_Temp;


U16 u16Heater_Power_Save;
U8 u8Heater_1stepWatt;


U16 Target_Flow_Q;
U8 u8Target_Hz_Hot;     //목표 유량

U8 gu8HeaterWatt_CheckTime;
U16 u16Heater_Power;

S16 gs16_heater_compensation;

U8 gu8_heater_increase_cnt;

F32 eeee;
F32 ffff;
F32 gggg;
F32 hhhh;
F32 iiii;

U16 gu16_flow_decrease_timer;
U16 gu16_heater_compensation_timer;

U16 u16Heater_Power_Save_Org;


U8 gu8_damaged_heater_cnt;
U8 gu8_damaged_heater_timer;
bit bit_check_damage;
bit bit_damaged_heater_error_fixed;
bit bit_damaged_heater_error_once;

//U8 gu8_adjust_heater_power_up;
//U8 gu8_adjust_heater_power_down;

S8 gs8_adjust_heater_power;
U8 gu8_adjust_heater_timer;

U8 gu8_heater_full_timer;

U8 gu8_min_power;

U16 gu16_flow_inc_timer;
U16 gu16_flow_dec_timer;

S8 gs8_flow_inc;

U16 u16TargetHeaterPower;       // 계산된 적정 히터 전력

U8 gu8_low_flow_timer;

U8 gu8_heater_off_temp;
U8 gu8_heater_on_temp;
U8 gu8_heater_save_on_temp;

bit bit_hot_first_op;

U8 gu8_room_overheat_timer;
U8 gu8_hot_safety_timer;


U8 gu8_hot_heater_re_timer;

bit F_Heater_Output;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Heating_Control(void)
{
    Ice_Heater_Control();
    tank_water_heater_control();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ice_Heater_Control(void)
{
//******************************************************************************************************//

    if(F_IceInit == SET)
    {
        if(gu8InitStep >= 6 && gu8InitStep <= 7)
        {
            Bit2_Ice_Make_Init_On_State = F_IceHeater;
        }
        else
        {
            Bit2_Ice_Make_Init_On_State = CLEAR;
        }

        Bit0_Ice_Making_Heater_On_State = CLEAR;
    }
    else
    {
        Bit2_Ice_Make_Init_On_State = CLEAR;

        /*if(gu8IceStep >= STATE_40_ICE_TRAY_MOVE_DOWN && gu8IceStep <= STATE_41_ICE_TAKE_OFF)*/
        if(gu8IceStep == STATE_41_ICE_TAKE_OFF)
        {
            Bit0_Ice_Making_Heater_On_State = F_IceHeater;
        }
        else
        {
            Bit0_Ice_Making_Heater_On_State = CLEAR;
        }
    }


    if(F_Safety_Routine == SET)
    {
        if(F_Ice_Tray_Down_Move_Reset == SET)
        {
            if(gu8_over_ice_melt_proc == 2)
            {
                Bit1_Over_Ice_Melt_State = F_Over_Ice_Heater_State;
            }
            else
            {
                Bit1_Over_Ice_Melt_State = CLEAR;
            }
        }
        else
        {
            Bit1_Over_Ice_Melt_State = CLEAR;
        }
    }
    else
    {
        Bit1_Over_Ice_Melt_State = CLEAR;
    }



//******************************************************************************************************//

    /*..hui [18-2-20오전 10:51:36] 제빙 정지 에러 발생했더라도 과제빙 해제 동작시에는 동작하도록....*/
    Bit0_Ice_Disable_Error_Off_State = Bit2_Ice_Operation_Disable_State & ~Bit1_Over_Ice_Melt_State;

    Bit1_Tray_Dual_Error_Check_State = F_ErrTrayMotor_DualInital;

    Bit2_Tray_Move_Error_State = Bit14_Tray_Micro_SW_Up_Move_Error | Bit15_Tray_Micro_SW_Down_Move_Error;

//******************************************************************************************************//

    if (u8IceHeaterOFF > 0)
    {
        pHEATER_ICE = CLEAR;
    }
    else
    {
        if (u8IceHeaterON > 0)
        {
            pHEATER_ICE = SET;
        }
        else
        {
            pHEATER_ICE = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tank_water_heater_control(void)
{
    if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

    //gu8_heater_off_temp = 99;
    //gu8_heater_on_temp = 90;
    //gu8_heater_off_temp = 92;
    //gu8_heater_on_temp = 85;

    //----------------------------------------------------------- 온도설정
    if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
    {
        gu8_heater_off_temp = 93;

        /*..hui [23-8-17오후 4:33:40] 미사용 절전이 최우선 조건..*/
        if( bit_9_hour_no_use_start == SET )
        {
            gu8_heater_on_temp = 65;
        }
        //else if( F_Sleep == SET )
	    /*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    /*.. sean [25-02-24] 온수 첫잔 NG로 히팅 시작온도 2도 up..*/
	    else if(bit_sleep_mode_start == SET)
        {
            gu8_heater_on_temp = 80;
        }
        else
        {
            gu8_heater_on_temp = 88;
        }

        /*gu8_heater_save_on_temp = 80;*/
    }
    else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
    {
        gu8_heater_off_temp = 90;

        if( bit_9_hour_no_use_start == SET )
        {
            gu8_heater_on_temp = 65;
        }
        //else if( F_Sleep == SET )
	    /*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    /*.. sean [25-02-24] 온수 첫잔 NG로 히팅 시작온도 2도 up..*/
	    else if(bit_sleep_mode_start == SET)
        {
            gu8_heater_on_temp = 77;
        }
        else
        {
            gu8_heater_on_temp = 85;
        }

        /*gu8_heater_save_on_temp = 77;*/
    }
    else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
    {
        gu8_heater_off_temp = 86;

        if( bit_9_hour_no_use_start == SET )
        {
            gu8_heater_on_temp = 65;
        }
        //else if( F_Sleep == SET )
	    /*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    /*.. sean [25-02-24] 온수 첫잔 NG로 히팅 시작온도 2도 up..*/
	    else if(bit_sleep_mode_start == SET)
        {
            gu8_heater_on_temp = 75;
        }
        else
        {
            gu8_heater_on_temp = 81;
        }

        /*gu8_heater_save_on_temp = 75;*/
    }
    else
    {
        gu8_heater_off_temp = 93;

        if( bit_9_hour_no_use_start == SET )
        {
            gu8_heater_on_temp = 65;
        }
        //else if( F_Sleep == SET )
	    /*.. sean [25-01-02] 절전모드 대신 취침모드 추가..*/
	    /*.. sean [25-02-24] 온수 첫잔 NG로 히팅 시작온도 2도 up..*/
	    else if(bit_sleep_mode_start == SET)
        {
            gu8_heater_on_temp = 80;
        }
        else
        {
            gu8_heater_on_temp = 88;
        }

        /*gu8_heater_save_on_temp = 80;*/
    }


    if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_heater_off_temp )
    {
        Bit0_Hot_Heating_State = CLEAR;
    }
    else
    {
        if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_heater_on_temp )
        {
            Bit0_Hot_Heating_State = SET;
        }
    }

///////////////////////////////////////////////////////////////////////////////////
    Bit0_First_Low_Water_State = ~bit_hot_first_op;

    Bit1_Hot_Setting_Off_State = ~F_Hot_Enable;


    if( Bit0_Hot_Tank_Temp_Open_Short_Error == SET
        || Bit3_Leakage_Sensor_Error == SET
        || Bit4_Room_Low_Water_Level_Error == SET
        || Bit5_Hot_Heater_OverHeat_Error == SET
        || Bit7_Room_High_Water_Level_Error == SET
        || Bit8_Feed_Valve_Error == SET
        || Bit9_Room_Level_Unbalance_Error == SET )
    {
        Bit2_Hot_Error_State = SET;
    }
    else
    {
        Bit2_Hot_Error_State = CLEAR;
    }

    #if 0
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        Bit3_Low_Water_Error_State = SET;
    }
    else
    {
        Bit3_Low_Water_Error_State = CLEAR;
    }
    #endif

    /*..hui [23-5-26오후 1:35:19] 저수위에서 해제되고 다시 감지되면 10초 후 부터 히터 가동..*/
    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        gu8_hot_heater_re_timer = 0;
        Bit3_Low_Water_Error_State = SET;
    }
    else
    {
        if( Bit3_Low_Water_Error_State == SET )
        {
            gu8_hot_heater_re_timer++;

            if( gu8_hot_heater_re_timer >= 100 )
            {
                gu8_hot_heater_re_timer = 0;
                Bit3_Low_Water_Error_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu8_hot_heater_re_timer = 0;
            Bit3_Low_Water_Error_State = CLEAR;
        }
    }

    /*..hui [23-3-24오후 12:22:05] 정수온도 50도 이상일 경우 온수히터 OFF..*/
    /*..hui [23-3-24오후 12:22:20] 온수 온도센서 고장시.. 바이메탈이 안떨어짐. QS파트..*/
    if( Bit2_Room_Temp_Open_Short_Error == CLEAR )
    {
        if( gu8_Room_Temperature_One_Degree >= ROOM_OVER_HEAT_TEMP )
        {
            gu8_room_overheat_timer++;

            if( gu8_room_overheat_timer >= 30 )
            {
                gu8_room_overheat_timer = 30;
                Bit4_Room_Over_Heat_State = SET;
            }
            else{}
        }
        else
        {
            if( Bit4_Room_Over_Heat_State == SET )
            {
                if( gu8_Room_Temperature_One_Degree <= ROOM_OVER_HEAT_CLEAR_TEMP )
                {
                    Bit4_Room_Over_Heat_State = CLEAR;
                }
                else{}
            }
            else
            {
                gu8_room_overheat_timer = 0;
            }
        }
    }
    else
    {
        Bit4_Room_Over_Heat_State = CLEAR;
        gu8_room_overheat_timer = 0;
    }



    if( gu8_Hot_Tank_Temperature_One_Degree >= HOT_SAFETY_TEMP )
    {
        #if 0
        gu8_hot_safety_timer++;

        if( gu8_hot_safety_timer >= HOT_SAFETY_DETECT_TIMNE )
        {
            gu8_hot_safety_timer = HOT_SAFETY_DETECT_TIMNE;
            Bit5_Hot_Safety_State = SET;
        }
        else{}
        #endif

        Bit5_Hot_Safety_State = SET;
    }
    else
    {
        gu8_hot_safety_timer = 0;
        Bit5_Hot_Safety_State = CLEAR;
    }


    /*****************************************************************************************************************/
    if (u16HotHeaterOff > 0)
    {
        pHEATER_HOT = CLEAR;              /*off*/
        F_Heater_Output = CLEAR;
    }
    else
    {
        if (u16HotHeaterOn > 0)               /*on*/
        {
            if( gu8_Comp_Stable_State == SET )
            {
                pHEATER_HOT = SET;
        		F_Heater_Output = SET;
            }
            else{}
        }
        else
        {
            pHEATER_HOT = CLEAR;          /*off*/
        	F_Heater_Output = CLEAR;
        }
    }



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



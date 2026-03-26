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
#define            Bit6_Hot_Ster_State                       U16HotHeaterOffW.Bit.b6




//U16 u16Heater_Power_Save;
//U8 u8Heater_1stepWatt;


//U16 Target_Flow_Q;
//U8 u8Target_Hz_Hot;     //목표 유량

//U8 gu8HeaterWatt_CheckTime;
//U16 u16Heater_Power;

//S16 gs16_heater_compensation;

//U8 gu8_heater_increase_cnt;

//F32 eeee;
//F32 ffff;
//F32 gggg;
//F32 hhhh;
//F32 iiii;

//U16 gu16_flow_decrease_timer;
//U16 gu16_heater_compensation_timer;

//U16 u16Heater_Power_Save_Org;


//U8 gu8_damaged_heater_cnt;
//U8 gu8_damaged_heater_timer;
//bit bit_check_damage;
//bit bit_damaged_heater_error_fixed;
//bit bit_damaged_heater_error_once;

//U8 gu8_adjust_heater_power_up;
//U8 gu8_adjust_heater_power_down;

//S8 gs8_adjust_heater_power;
//U8 gu8_adjust_heater_timer;

//U8 gu8_heater_full_timer;

//U8 gu8_min_power;

//U16 gu16_flow_inc_timer;
//U16 gu16_flow_dec_timer;

//S8 gs8_flow_inc;

//U16 u16TargetHeaterPower;       // 계산된 적정 히터 전력

//U8 gu8_low_flow_timer;

U8 gu8_heater_off_temp;
U8 gu8_heater_on_temp;
U8 gu8_heater_save_on_temp;

bit bit_hot_first_op;


U8 gu8_hot_setting_temperature;
U8 gu8_room_overheat_timer;

U8 gu8_hot_safety_timer;
U16 gu16_hot_heater_re_timer;

bit bit_heater_low_water_state;
bit F_Heater_Output;


U8 gu8_triac_timer;

bit bit_heater_first_check;
U8 gu8_heater_on_first_hot_temp;
U8 gu8_heater_on_first_amb_temp;

U16 gu16_heater_off_delay_timer;


U8 gu8_display_heater_on_temp;
U8 gu8_display_heater_off_temp;

bit bit_first_reach_on_target_1;
bit bit_first_fall_off_target_2;


U8 gu8_heater_on_timer;
U16 gu16_heater_off_add_timer;
bit bit_heater_add_operation;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Heating_Control(void)
{
    /*Ice_Heater_Control();*/
    tank_water_heater_control();

    /*mix_motor_control();*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ice_Heater_Control(void)
{
//******************************************************************************************************//
#if 0
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

        /*if(gu8IceStep >= STATE_40_ICE_TRAY_MOVE_DOWN && gu8IceStep <= STATE_43_ICE_TAKE_OFF)*/
        if(gu8IceStep == STATE_43_ICE_TAKE_OFF)
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

    Bit2_Tray_Move_Error_State = Bit18_Tray_Micro_SW_Up_Move_Error__E62 | Bit19_Tray_Micro_SW_Down_Move_Error__E63;

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
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tank_water_heater_control(void)
{
    U16 mu16_dalay_time = 0;

    if(F_FW_Version_Display_Mode == CLEAR)
    {
        gu8_heater_on_first_hot_temp = gu8_Hot_Tank_Temperature_One_Degree;
        gu8_heater_on_first_amb_temp = gu8_Amb_Temperature_One_Degree;
        bit_first_reach_on_target_1 = CLEAR;
        bit_first_fall_off_target_2 = CLEAR;
        bit_heater_first_check = CLEAR;
        return;
    }
    else{}

    /*..hui [23-11-28오후 4:31:31] 온수 OFF -> ON 시 다시 재시작..*/
    if( F_Hot_Enable == CLEAR )
    {
        bit_first_reach_on_target_1 = CLEAR;
        bit_first_fall_off_target_2  = CLEAR;

        bit_heater_first_check = CLEAR;
    }
    else{}

    //----------------------------------------------------------- 온도설정
    /*..hui [24-2-7오전 10:12:33] 얼음탱크 세척중.. 종료 준비 제외..*/
    if( bit_ice_tank_ster_start == SET && gu8_ice_ster_mode < STER_MODE_FINISH )
    {
        if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
        {
            if( gu8_ice_ster_mode == STER_MODE_PREPARE )
            {
                /*..hui [23-11-17오후 4:42:29] 이정환부장님..11월17일 변경 요청..*/
                gu8_heater_off_temp = ALTITUDE__1__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__1__ICE_TANK_STER__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
            {
                /*..hui [24-1-25오전 9:20:26] 아이스트레이 세척시 온도..*/
                gu8_heater_off_temp = ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__1__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__1__MELT_ICE__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__1__MELT_ICE__HEATER_ON_TEMP;
            }
            else
            {
                gu8_heater_off_temp = ALTITUDE__1__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__1__ICE_TANK_STER__HEATER_ON_TEMP;
            }
        }
        else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
        {
            if( gu8_ice_ster_mode == STER_MODE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__2__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__2__ICE_TANK_STER__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
            {
                /*..hui [24-1-25오전 9:20:26] 아이스트레이 세척시 온도..*/
                gu8_heater_off_temp = ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__2__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__2__MELT_ICE__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__2__MELT_ICE__HEATER_ON_TEMP;
            }
            else
            {
                gu8_heater_off_temp = ALTITUDE__2__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__2__ICE_TANK_STER__HEATER_ON_TEMP;
            }
        }
        else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
        {
            if( gu8_ice_ster_mode == STER_MODE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__3__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__3__ICE_TANK_STER__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
            {
                /*..hui [24-1-25오전 9:20:26] 아이스트레이 세척시 온도..*/
                gu8_heater_off_temp = ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__3__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__3__MELT_ICE__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__3__MELT_ICE__HEATER_ON_TEMP;
            }
            else
            {
                gu8_heater_off_temp = ALTITUDE__3__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__3__ICE_TANK_STER__HEATER_ON_TEMP;
            }
        }
        else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
        {
            if( gu8_ice_ster_mode == STER_MODE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__4__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__4__ICE_TANK_STER__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
            {
                /*..hui [24-1-25오전 9:20:26] 아이스트레이 세척시 온도..*/
                gu8_heater_off_temp = ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__4__ICE_TRAY_CLEAN__HEATER_ON_TEMP;
            }
            else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
            {
                gu8_heater_off_temp = ALTITUDE__4__MELT_ICE__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__4__MELT_ICE__HEATER_ON_TEMP;
            }
            else
            {
                gu8_heater_off_temp = ALTITUDE__4__ICE_TANK_STER__HEATER_OFF_TEMP;
                gu8_heater_on_temp = ALTITUDE__4__ICE_TANK_STER__HEATER_ON_TEMP;
            }
        }
    }
    else if( bit_9_hour_no_use_start == SET || bit_sleep_mode_start  == SET )
    {
        if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
        {
            gu8_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_1;
            gu8_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_1;

            gu8_display_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_1;
            gu8_display_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_1;
        }
        else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
        {
            gu8_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_2;
            gu8_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_2;

            gu8_display_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_2;
            gu8_display_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_2;
        }
        else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
        {
            gu8_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_3;
            gu8_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_3;

            gu8_display_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_3;
            gu8_display_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_3;
        }
        else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
        {
            gu8_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_4;
            gu8_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_4;

            gu8_display_heater_off_temp = SLEEP_MODE_HEATER_OFF_TEMP__ALTITUDE_4;
            gu8_display_heater_on_temp = SLEEP_MODE_HEATER_ON_TEMP__ALTITUDE_4;
        }

    }
    else
    {
        if( gu8AltitudeStep == ALTITUDE_1_MODE_HIGH )
        {
            /*if( gu8_heater_on_first_hot_temp < 25 )*/
            /*..hui [23-12-15오후 2:55:53] 50도로 변경.. 청래..*/
            if( gu8_heater_on_first_hot_temp < 50 )
            {
                /*..hui [23-11-28오후 5:04:17] 첫 기동 25도 미만 조건은 외기 온도 상관없이 통일..*/
                gu8_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER;
                gu8_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER;
                /*mu16_dalay_time = 600;*/
                mu16_dalay_time = 500;

                gu8_display_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER;
                gu8_display_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER;
            }
            else
            {
                /*if( gu8_heater_on_first_amb_temp < 20 )*/
                if( gu8_heater_on_first_amb_temp < 30 )
                {
                    gu8_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER;
                    gu8_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER;
                    /*..hui [24-2-19오후 4:10:08] 지연시간 삭제..*/
                    /*mu16_dalay_time = 200;*/

                    gu8_display_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_UNDER;
                    gu8_display_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_UNDER;
                }
                else
                {
                    gu8_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_OVER;
                    gu8_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_OVER;

                    gu8_display_heater_off_temp = ALTITUDE_1_MODE_HEATER_OFF_TEMP_AMB_30_OVER;
                    gu8_display_heater_on_temp = ALTITUDE_1_MODE_HEATER_ON_TEMP_AMB_30_OVER;
                }
            }
        }
        else if( gu8AltitudeStep == ALTITUDE_2_MODE_MID )
        {
            gu8_heater_off_temp = ALTITUDE_2_MODE_HEATER_OFF_TEMP;
            gu8_heater_on_temp = ALTITUDE_2_MODE_HEATER_ON_TEMP;

            gu8_display_heater_off_temp = ALTITUDE_2_MODE_HEATER_OFF_TEMP;
            gu8_display_heater_on_temp = ALTITUDE_2_MODE_HEATER_ON_TEMP;
        }
        else if( gu8AltitudeStep == ALTITUDE_3_MODE_LOW )
        {
            gu8_heater_off_temp = ALTITUDE_3_MODE_HEATER_OFF_TEMP;
            gu8_heater_on_temp = ALTITUDE_3_MODE_HEATER_ON_TEMP;

            gu8_display_heater_off_temp = ALTITUDE_3_MODE_HEATER_OFF_TEMP;
            gu8_display_heater_on_temp = ALTITUDE_3_MODE_HEATER_ON_TEMP;
        }
        else /*if( gu8AltitudeStep == ALTITUDE_4_MODE_VERY_LOW )*/
        {
            gu8_heater_off_temp = ALTITUDE_4_MODE_HEATER_OFF_TEMP;
            gu8_heater_on_temp = ALTITUDE_4_MODE_HEATER_ON_TEMP;

            gu8_display_heater_off_temp = ALTITUDE_4_MODE_HEATER_OFF_TEMP;
            gu8_display_heater_on_temp = ALTITUDE_4_MODE_HEATER_ON_TEMP;
        }
    }


    if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_heater_off_temp )
    {
        if( gu8_Hot_Tank_Temperature_One_Degree >= 99 )
        {
            gu16_heater_off_delay_timer = mu16_dalay_time;
            bit_heater_add_operation = CLEAR;
        }
        else{}

        gu16_heater_off_delay_timer++;

        if( gu16_heater_off_delay_timer >= mu16_dalay_time )
        {
            gu16_heater_off_delay_timer = mu16_dalay_time;
            /*Bit0_Hot_Heating_State = CLEAR;*/

            if( u8WaterOutState == HOT_WATER_SELECT
                && gu8AltitudeStep == ALTITUDE_1_MODE_HIGH
                && gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC
                /*&& gu8_Hot_Tank_Temperature_One_Degree <= gu8_heater_off_temp*/
                && gu8_Hot_Tank_Temperature_One_Degree <= 98
                && F_WaterOut == SET )
                /*&& bit_first_fall_off_target_2 == CLEAR )*/
            {
                Bit0_Hot_Heating_State = SET;

                gu8_heater_on_timer++;

                if( gu8_heater_on_timer >= 50 )
                {
                    gu8_heater_on_timer = 50;
                    bit_heater_add_operation = SET;
                }
                else
                {
                    /*..hui [24-2-14오전 9:20:43] 10초 지연 가동 중.. 추출했는데 5초 미만일 경우에는 지연 가동 취소..*/
                    bit_heater_add_operation = CLEAR;
                }

                gu16_heater_off_add_timer = 0;
            }
            else
            {
                gu8_heater_on_timer = 0;

                if( bit_heater_add_operation == SET )
                {
                    gu16_heater_off_add_timer++;

                    if( gu16_heater_off_add_timer >= HEATER_ADD_OPERATION_TIME )
                    {
                        /////gu8_heater_on_timer = 0;
                        gu16_heater_off_add_timer = 0;
                        bit_heater_add_operation = CLEAR;
                        Bit0_Hot_Heating_State = CLEAR;
                    }
                    else{}
                }
                else
                {
                    /////gu8_heater_on_timer = 0;
                    gu16_heater_off_add_timer = 0;
                    bit_heater_add_operation = CLEAR;
                    Bit0_Hot_Heating_State = CLEAR;
                }

                /*bit_first_reach_on_target_1 = SET;*/
            }
        }
        else{}
    }
    else
    {
        gu16_heater_off_delay_timer = 0;

        gu8_heater_on_timer = 0;
        gu16_heater_off_add_timer = 0;
        bit_heater_add_operation = CLEAR;

        /*..hui [23-6-28오전 10:41:28] 초고온수가 디폴트로 변경..*/
        if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_heater_on_temp )
        {
            Bit0_Hot_Heating_State = SET;

            #if 0
            /*..hui [23-11-28오전 10:47:19] 타겟 도달 후 떨어진 경우에만..*/
            if( bit_first_reach_on_target_1 == SET )
            {
                bit_first_fall_off_target_2 = SET;
            }
            else{}
            #endif
        }
        else
        {
            /*..hui [23-11-8오후 1:53:14] 경민과장 요청..*/
            /*..hui [23-11-28오전 10:38:45] 첫 타겟 OFF 온도 초과 후 재 기동온도까지 떨어지면 그 다음부터는 안함..*/
            /*..hui [23-11-28오후 4:32:20] 설정온도 미만이면 항시 동작하도록.. 경민과장..*/
            if( u8WaterOutState == HOT_WATER_SELECT
                && gu8AltitudeStep == ALTITUDE_1_MODE_HIGH
                && gu8_hot_setting_temperature == HOT_SET_TEMP_4__200_oF_95_oC
                && F_WaterOut == SET )
            {
                Bit0_Hot_Heating_State = SET;
            }
            else{}
        }
    }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

    Bit0_First_Low_Water_State = ~bit_hot_first_op;

    /*Bit1_Hot_Setting_Off_State = ~F_Hot_Enable;*/

    if( F_Hot_Enable == CLEAR && bit_ice_tank_ster_start == SET && gu8_ice_ster_mode == STER_MODE_PREPARE )
    {
        /*..hui [23-11-8오후 3:23:05] 온수 꺼져있을때 온수세척 준비중 켠다..*/
        Bit1_Hot_Setting_Off_State = CLEAR;
    }
    else if( F_Hot_Enable == CLEAR && bit_ice_tank_ster_start == SET && gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
    {
        /*..hui [24-1-25오전 9:21:15] 온수 꺼져있을때 아이스트레이 세척 준비중 켠다..*/
        Bit1_Hot_Setting_Off_State = CLEAR;
    }
    else if( F_Hot_Enable == CLEAR && bit_ice_tank_ster_start == SET && gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE )
    {
        /*..hui [23-11-8오후 3:23:29] 온수 꺼져있을때 해빙작업 준비중 켠다..*/
        Bit1_Hot_Setting_Off_State = CLEAR;
    }
    else
    {
        Bit1_Hot_Setting_Off_State = ~F_Hot_Enable;
    }




    #if 0
    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
        || Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET
        /*|| Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use == SET*/
        /*|| Bit7_Room_High_Water_Level_Error__E13_Not_Use == SET*/
        /*|| Bit8_Feed_Valve_Error__E10_Not_Use == SET*/
        /*|| Bit9_Room_Level_Unbalance_Error__E14_Not_Use == SET*/ )
    {
        Bit2_Hot_Error_State = SET;
    }
    else
    {
        Bit2_Hot_Error_State = CLEAR;
    }
    #endif

    /*..hui [23-7-27오후 2:30:41] 에러 컨트롤 부분에서 처리 후 공용사용..*/
    Bit2_Hot_Error_State = Bit1_Hot_Operation_Disable_State;

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
        gu16_hot_heater_re_timer = 0;
        Bit3_Low_Water_Error_State = SET;
    }
    else
    {
        if( Bit3_Low_Water_Error_State == SET )
        {
            gu16_hot_heater_re_timer++;

            /*if( gu16_hot_heater_re_timer >= 100 )*/
            /*..hui [24-3-18오전 9:08:24] 1분으로 변경.. 임재한 부장님 요청. 이게 표준사양..*/
            if( gu16_hot_heater_re_timer >= 600 )
            {
                gu16_hot_heater_re_timer = 0;
                Bit3_Low_Water_Error_State = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_hot_heater_re_timer = 0;
            Bit3_Low_Water_Error_State = CLEAR;
        }
    }

    bit_heater_low_water_state = Bit3_Low_Water_Error_State;

    /*..hui [23-3-24오후 12:22:05] 정수온도 50도 이상일 경우 온수히터 OFF..*/
    /*..hui [23-3-24오후 12:22:20] 온수 온도센서 고장시.. 바이메탈이 안떨어짐. QS파트..*/
    /*..hui [23-10-20오후 3:31:20] 얼음 세척할때도 확인하지 않는다. 에러는 확인..*/
    /*..hui [23-10-20오후 3:31:34] 이정환 부장님 요청.. 세척시 정수온도가 50도까지 올라갈수있음..*/
    /*if( Bit2_Room_Temp_Open_Short_Error__E42 == CLEAR && bit_ice_tank_ster_start == CLEAR )*/
    /*..hui [23-10-20오후 4:07:56] 다시 원복.. 안전장치는 있어야함..*/
    if( Bit2_Room_Temp_Open_Short_Error__E42 == CLEAR )
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

    /*..hui [23-8-24오후 3:07:14] 온수 세척할때는 히터 끄는걸로.. 온도가 너무 높으면안됨..*/
    /*Bit6_Hot_Ster_State = bit_ice_tank_ster_start;*/

    if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-10-17오후 2:34:41] 해빙작업 준비할때 제외하고 세척할때는 끈다..*/
        /*..hui [23-10-27오전 11:51:09] 해빙 끝나고 냉각할때 온수도 같이.....*/
        /*..hui [23-11-8오후 3:28:51] 세척 준비중에도 켠다..*/
        if( gu8_ice_ster_mode == STER_MODE_PREPARE )
        {
            Bit6_Hot_Ster_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_ICE_TRAY_CLEAN_PREPARE )
        {
            /*..hui [24-1-25오전 9:22:49] 아이스 트레이 세척 준비 중 켠다..*/
            Bit6_Hot_Ster_State = CLEAR;
        }
        else if( gu8_ice_ster_mode == STER_MODE_MELT_ICE_PREPARE
            || gu8_ice_ster_mode == STER_MODE_FINISH )
        {
            Bit6_Hot_Ster_State = CLEAR;
        }
        else
        {
            Bit6_Hot_Ster_State = SET;
        }
    }
    else
    {
        Bit6_Hot_Ster_State = CLEAR;
    }

    /*****************************************************************************************************************/
    if (u16HotHeaterOff > 0)
    {
        pHEATER_HOT = CLEAR;              /*off*/
        F_Heater_Output = CLEAR;
        /*..hui [23-5-30오후 3:42:52] 온수히터 OFF 조건 발생 시 예열 진행중인거 취소..*/
        gu8_triac_timer = 0;
        bit_heater_first_check = CLEAR;
    }
    else
    {
        if (u16HotHeaterOn > 0)               /*on*/
        {
            if( gu8_Comp_Stable_State == SET )
            {
                pHEATER_HOT = SET;
                F_Heater_Output = SET;

                if( bit_heater_first_check == CLEAR )
                {
                    bit_heater_first_check = SET;

                    if( gu8_Hot_Tank_Temperature_One_Degree <= gu8_heater_on_temp )
                    {
                        gu8_heater_on_first_hot_temp = gu8_Hot_Tank_Temperature_One_Degree;
                        gu8_heater_on_first_amb_temp = gu8_Amb_Temperature_One_Degree;
                    }
                    else
                    {
                        if( gu8_heater_on_first_hot_temp == 0 )
                        {
                            gu8_heater_on_first_hot_temp = gu8_Hot_Tank_Temperature_One_Degree;
                            gu8_heater_on_first_amb_temp = gu8_Amb_Temperature_One_Degree;
                        }
                        else{}
                    }
                }
                else{}
            }
            else{}
        }
        else
        {
            pHEATER_HOT = CLEAR;          /*off*/
            F_Heater_Output = CLEAR;
            gu8_triac_timer = 0;
            bit_heater_first_check = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



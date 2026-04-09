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
#include    "M8_Ice_making.h"
#include    "Temp_Table.h"
#include    "Ice_Make_Time_Table.h"
#include    "api_debug.h"

void Ice_Make_Process(void);
//void ice_init_operation(void);
void normal_mode_ice_init_operation(void);
//void line_test_ice_init_operation(void);

U16 calc_ice_make_time(U8 mu8AmbTemp, U8 mu8RoomTemp);
U16 calc_ice_heater_time(void);
U8 Ice_Tray_Sensing(void);
//void IceMakeOrder(void);
//void ice_make_timer(void);
//void ice_make_100ms_timer(void);
//void ice_make_1sec_timer(void);
void ice_make_operation(void);
//void forced_take_off_ice(void);
void ice_init_select_bar_test(void);
U8 ice_heater_operation(void);
void recovery_ice_tray(void);


bit F_IceHeater;
bit F_Hotgas_Time;

bit F_CyclePump;
//bit F_IceMakeGo;                    // ���� ������ ����
U8 gu8InitStep;


ICE_STEP gu8IceStep;

bit F_IceVV;
//bit F_IceInit;
//bit F_ReIceInit;
//bit F_SBTest;



//U16 Select_Delay;

//----------------------------------------------------// ICE Heater
U16 gu16IceHeaterTime;                                // Ż�� Heater ���� �ð�
bit F_ColdWaterInit;
bit F_WaterInit;                      // ���� �����Ϸ�
bit F_HotWaterInit;                   // ���� �����Ϸ� - �¼�
bit F_WaterInitSet;
bit F_ColdVV;

bit F_TrayMotorCW;
bit F_TrayMotorPreCW;
bit F_TrayMotorCCW;
bit F_TrayMotorPreCCW;

//bit F_ColdIn;
//bit F_ColdDIR;               // �ü��� ��������
bit F_IceOpen;
U8 gu8IceOut;
bit F_IceOutCCW;
U8 gu8IceOutCCWInterval;
U16 gu16IceOutTest;
//U16 gu16StepMotor1;
U8 gu8IceClose;
U8 gu8SBTest;                // SB Error ����
bit F_NoColdBar;
bit F_NoIceBar;
//U16 gu16CompOffDelay;
U16 gu16IceMakeTime;
U8 gu8_IceHeaterControl;
U16 gu16IceVVTimeSetDelay;
U16 gu16ErrPuriDelay;



U16 gu16IceVVTime;
//U8 gu8IceCount;
U8 gu8ICETrayRoomDelay;
//U8 Tray_Comp_Delay;

/*..hui [18-3-8���� 11:23:33] ���� �� 50�� ���� ���� �� �ü� Ż�� ����..*/
bit F_Ext_cold;

U8 gu8AmbTemp;
U8 gu8RoomTemp;

bit F_CompOn;                     // �ü� ���� ����
bit F_IceCompOn;                  // ���� ���� ����
bit F_CompHeater;                 // ����,���� ���ñ⵿����


U8 gu8_ice_make_1sec_timer;
bit F_ice_make_one_more_time;

U8 gu8_ice_tray_reovery_time;



U16 gu16_Ice_Tray_Fill_Hz;

U16 gu16_cody_ice_make_time;


U16 U16TESTTTTT;

extern U16 gu16IceMakingADVal;
U16 gu16DetectTimer = 0;
U8 gu8IsAdcDown = 0;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ice_Make_Process(void)
{
    /*..hui [17-12-26���� 9:51:20] ���� ǥ�� �Ϸ� �� ����..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    /*..hui [17-12-19���� 7:07:33] �����϶� ���� �� ���� ���� �߰�....*/
    /*..hui [17-12-19���� 7:07:54] ���߿� �ü� �Լ���� OFF��Ű�°͵� �߰��ؾ���....*/
    if( Bit2_Ice_Operation_Disable_State == SET
       || F_Safety_Routine == SET
       || F_ErrTrayMotor_DualInital == SET )
       /*|| u8CodyInspectOperation > 0)*/
    {
        F_IceHeater = CLEAR;
        gu8InitStep = 0;
        gu8IceStep = STATE_0_STANDBY;
        return;
    }
    else{}


    //=======================================================//�������� �ʱ�ȭ
    if(F_IceInit == SET)
    {
        ice_init_operation();
        return;
    }
    else
    {
        gu8InitStep = 0;
    }

    //======================================================// ���� �ʱ�, �ü�, ���� �����ƴϸ� return
    if((gu8IceStep == STATE_0_STANDBY) && (F_WaterInit != SET))
    {
        return;
    }
    else{}

    //======================================================// ���������
    if(Bit1_Ice_Make_Go != SET)
    {
        gu8IceStep = STATE_0_STANDBY;
        F_IceHeater = 0;
        /*F_IceVV = 0;*/
        return;
    }
    else{}

	
	/*..sean [25-03-12] ����Ʈ �������� �߿��� ���� ���� �Ϸ� �� Ż�� ����..*/
	if(bit_self_test_start == SET)
	{
		return;
	}
    //=======================================================// ���� ������
    ice_make_operation();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_operation(void)
{
    U8 mu8_return_value;


    //=======================================================// ���� ������
    switch(gu8IceStep)
    {
        //----------------------------------------------// �������� ����ȸ��
        case STATE_0_STANDBY :

            if(gu16CompOffDelay == 0 || F_Comp_Output == SET)
            {
                /*..hui [19-10-23���� 12:47:20] ���� �����߿��� Ʈ���� �ø��� �ʵ���..*/
                /*..hui [19-10-23���� 12:47:34] �����߿� ������ �з��� Ʈ���̰� �ɸ���..*/
                /*..hui [19-10-23���� 12:47:46] �ⱸ������ ������ �ʟG��..*/
                if(F_Ice != SET)
                {
                    gu8IceStep = STATE_10_ICE_TRAY_MOVE_UP;
                }
                else{}
            }
            else{}

            break;

        //----------------------------------------------// �������� ����ȸ��
        case STATE_10_ICE_TRAY_MOVE_UP :

            if(F_TrayMotorCCW != SET)
            {
                up_tray_motor();
                gu8IceStep = STATE_11_WAIT_ROOM_WATER_FULL;

                F_CristalIce = SET;
            }
            else{}

            break;

        //----------------------------------------------// ����ȸ���� ������VV ON
        case STATE_11_WAIT_ROOM_WATER_FULL :

            if(F_TrayMotorCW != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                F_TrayMotorCW = CLEAR;

                if(gu8_Room_Water_Level >= ROOM_LEVEL_MID)   // ���� �϶���
                {
                    gu8IceStep = STATE_12_CHECK_DRAIN_LEVEL;
                }
                else{}
            }
            else
            {
                /*..hui [18-3-20���� 7:21:54] ������ũ ������ ä����߿� Ʈ���� ������ ���� ������..*/
                if(F_TrayMotorCW != SET)
                {
                    gu8IceStep = STATE_10_ICE_TRAY_MOVE_UP;
                }
                else{}
            }

            break;


        //----------------------------------------------// ����ȸ���� ������VV ON
        case STATE_12_CHECK_DRAIN_LEVEL :

            /*..hui [19-7-23���� 2:08:21] Ʈ�����Լ� ����� ���濡 ���� ��� ����(�������� �Ĵ�)..*/
            /*..hui [19-7-23���� 2:08:26] �¼� ����߿��� Ʈ���� �Լ� ����..*/
            /*if(u8WaterOutState == HOT_WATER_SELECT && F_WaterOut == SET)*/
            /*..hui [19-8-28���� 9:54:48] �¼� �Ӹ��ƴ϶� �� �����߿��� Ʈ���� �Լ� ���..*/
            if(F_WaterOut == SET)
            {
                //���
            }
            else
            {
                gu16_Ice_Tray_Fill_Hz = C_ICE_TRAY_FILL_200CC;

                gu8IceStep = STATE_20_WATER_IN_ICE_TRAY;
            }

            break;

        //-----------------------------------------------// ������VV Off
        case STATE_20_WATER_IN_ICE_TRAY :

            if(gu16_Ice_Tray_Fill_Hz <= 0)
            {
                gu8IceStep = STATE_21_ICE_SWITCH_MOVE;
            }
            else{}

            break;

        //-----------------------------------------------// ������VV Off
        case STATE_21_ICE_SWITCH_MOVE :

            GasSwitchIce();

            gu8IceStep = STATE_30_CALC_ICE_MAKING_TIME;

            break;

        //-----------------------------------------------// ���� ����
        case STATE_30_CALC_ICE_MAKING_TIME :

            /*..hui [19-7-24���� 4:35:37] �ø���ȯ��� �̵� �Ϸ� ��..*/
            if(gu8_GasSwitch_Status == GAS_SWITCH_ICE)
            {
                if(gu16CompOffDelay == 0 ||  F_Comp_Output == SET)
                {
                    gu16IceMakeTime
                        = (U16)calc_ice_make_time( gu8_Amb_Temperature_One_Degree, gu8_Room_Temperature_One_Degree);

                    ///gu16_wifi_ice_make_time = gu16IceMakeTime;

                    /* 제빙시간 3배로 진행 */
                    gu16IceMakeTime = (U16)(gu16IceMakeTime  * 30);

                    /*..hui [20-2-19���� 3:32:11] �ڵ� ��� ���� Ż���� 3�� ���Ŀ��� �����ϱ����� �߰�..*/
                    gu16_cody_ice_make_time  = gu16IceMakeTime;

                    gu8IceStep = STATE_31_MAIN_ICE_MAKING;
                    gu16DetectTimer = 0;
                    gu8IsAdcDown = 0;
                    gu8_ice_tray_reovery_time = 0;
                    dlog(SYSMOD, INFO, ("CLI Test - Ice Make Start \r\n") );

                    #if 0
                    /*..hui [20-2-12���� 4:43:37] �¼� ������̸� �¼� ��� �����ϰ� 2�� �� ����..*/
                    /*..hui [20-2-12���� 4:51:24] �¼�����, COMP ���� ������ ��ũ ���������� ���ܱ� ������ �� ����..*/
                    if( (F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
                        || Bit4_Hot_Water_COMP_Off_State == SET )
                    {
                        //
                    }
                    else
                    {
                        gu8IceStep = STATE_31_MAIN_ICE_MAKING;
                        gu8_ice_tray_reovery_time = 0;
                    }
                    #endif
                }
                else{}
            }
            else
            {
                GasSwitchIce();
            }

            break;
        //-----------------------------------------------// �����Ϸ��� ����ȸ��
        case STATE_31_MAIN_ICE_MAKING :

            if(gu16IceMakeTime > 0 && pCOMP == SET)
            {
                gu16IceMakeTime--;    // ���� 13��

                gu32_wifi_ice_make_time++;
            }
            else{}

            /* ADC 990을 한번 찍은 이후 떨어지는 구간 체크를 위해 Flag Set */
            if(gu16IceMakeTime == 0)
            {
                dlog(SYSMOD, INFO, ("CLI Test - Ice is Not Detected.. T.T => %d \r\n", gu16IceMakingADVal) );
                gu16IceHeaterTime = calc_ice_heater_time();
                down_tray_motor();
                F_CristalIce = CLEAR;

                gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;
            }
            else
            {
                recovery_ice_tray();
            }

            if(gu16IceMakingADVal >= 990)
            {
                gu16DetectTimer++;
                gu8IsAdcDown = 1;
                
                // 6분 연속으로 감지되면 ok
                // if(gu16DetectTimer >= WORK_ADC_OK_TIME)
                // {
                //     gu16DetectTimer = WORK_ADC_OK_TIME;
                //     dlog(SYSMOD, INFO, ("CLI Test - Ice Complete : %d \r\n", 2) );
                // }
            }
            else
            {
                /* Adc가 올라간 후, Adc가 300이하로 감지되면 제빙완료로 판단 */
                if(gu16IceMakingADVal <= 620)
                {
                    if(gu8IsAdcDown == TRUE)
                    {
                        dlog(SYSMOD, INFO, ("CLI Test - Ice Detected! :) => %d \r\n", gu16IceMakingADVal) );
                        // dlog(SYSMOD, INFO, ("CLI - Ice Detected! => %d \r\n" ), gu16IceMakingADVal);
                        gu8IsAdcDown = FALSE;

                        gu16IceHeaterTime = calc_ice_heater_time();

                        /*F_IceHeater = SET;*/                      // Ice Heater On

                        down_tray_motor();

                        gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;

                        F_CristalIce = CLEAR;
                    }
                }

                gu16DetectTimer = 0;
                recovery_ice_tray();
            }

            break;

        //-----------------------------------------------// ����ȸ���Ϸ�
        case STATE_40_ICE_TRAY_MOVE_DOWN :

            if(F_TrayMotorCCW != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            {
                F_TrayMotorCCW = 0;
                /*F_IceHeater = SET;*/                      // Ice Heater On
                gu8IceStep = STATE_41_ICE_TAKE_OFF;
            }
            else{}

            break;

        case STATE_41_ICE_TAKE_OFF :

            mu8_return_value = ice_heater_operation();

            if(mu8_return_value == SET)
            {
                F_IR = SET;              // �������� ����
                F_IceHeater = CLEAR;
                gu8IceStep = STATE_50_ICE_FULL_IR_CHECK;
            }
            else{}

            break;
        //-------------------------------------------------// SB �ü� ȸ���Ϸ�
        case STATE_50_ICE_FULL_IR_CHECK :

            if(F_IR != SET)
            {
                gu8IceStep = STATE_51_FINISH_ICE_MAKE;
            }
            else{}

            break;

        case STATE_51_FINISH_ICE_MAKE :

            //F_IceMakeGo = CLEAR;
            gu8IceStep = STATE_0_STANDBY;

            break;

        default :

            //F_IceMakeGo = CLEAR;
            gu8IceStep = STATE_0_STANDBY;
            gu8InitStep = 0;
            F_IceHeater = CLEAR;
            /*F_IceVV = CLEAR;*/
            F_IceInit = SET;

            break;
      }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 calc_ice_make_time(U8 mu8AmbTemp, U8 mu8RoomTemp)
{
    U8 mu8_amb_temp = 0;
    U8 mu8_room_temp = 0;

    if(mu8AmbTemp >= 45)
    {
        mu8_amb_temp = 45;
    }
    else
    {
        mu8_amb_temp = mu8AmbTemp;
    }

    if(mu8RoomTemp >= 45)
    {
        mu8_room_temp = 45;
    }
    else
    {
        mu8_room_temp = mu8RoomTemp;
    }

    return Temp_MakeTime[ mu8_room_temp ][ mu8_amb_temp ];

    #if 0
    if(mu8AmbTemp > 45)
    {
        return ICE_MAKE_TIME;
    }
    else{}

    if(mu8RoomTemp > 45)
    {
        return ICE_MAKE_TIME;
    }
    else{}

    return Temp_MakeTime[ mu8RoomTemp ][ mu8AmbTemp ];
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 calc_ice_heater_time(void)     // 20120820 Ż�� �ð� �ν�ǰ ����.
{
    #if 0
    if(gu8_Amb_Temperature_One_Degree <= 10)
    {
        /*..hui [20-3-17���� 2:32:30] 10�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_10_UNDER;
        return HEAT_TORAL_TIME_10_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 15)
    {
        /*..hui [20-3-17���� 2:32:45] 10�� �ʰ� ~ 15�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_15_UNDER;
        return HEAT_TORAL_TIME_15_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 20)
    {
        /*..hui [20-3-17���� 2:32:55] 15�� �ʰ� ~ 20�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_20_UNDER;
        return HEAT_TORAL_TIME_20_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 25)
    {
        /*..hui [20-3-17���� 2:33:11] 20�� �ʰ� ~ 25�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_25_UNDER;
        return HEAT_TORAL_TIME_25_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 30)
    {
        /*..hui [20-3-10���� 11:17:35] 25�� �ʰ� ~ 30�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_30_UNDER;
        return HEAT_TORAL_TIME_30_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 35)
    {
        /*..hui [20-3-10���� 11:17:42] 30�� �ʰ� ~ 35�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_35_UNDER;
        return HEAT_TORAL_TIME_35_UNDER;
    }
    else
    {
        /*..hui [20-3-10���� 11:17:05] 35�� �ʰ�..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_35_OVER;
        return HEAT_TORAL_TIME_35_OVER;
    }
    #endif

    if(gu8_Amb_Temperature_One_Degree <= 15)
    {
        /*..hui [23-3-8���� 12:23:25] 15�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_15_UNDER;
        return HEAT_TORAL_TIME_15_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 20)
    {
        /*..hui [20-3-17���� 2:32:55] 15�� �ʰ� ~ 20�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_20_UNDER;
        return HEAT_TORAL_TIME_20_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 25)
    {
        /*..hui [20-3-17���� 2:33:11] 20�� �ʰ� ~ 25�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_25_UNDER;
        return HEAT_TORAL_TIME_25_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 30)
    {
        /*..hui [20-3-10���� 11:17:35] 25�� �ʰ� ~ 30�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_30_UNDER;
        return HEAT_TORAL_TIME_30_UNDER;
    }
    else if(gu8_Amb_Temperature_One_Degree <= 35)
    {
        /*..hui [20-3-10���� 11:17:42] 30�� �ʰ� ~ 35�� ����..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_35_UNDER;
        return HEAT_TORAL_TIME_35_UNDER;
    }
    else
    {
        /*..hui [20-3-10���� 11:17:05] 35�� �ʰ�..*/
        gu8_IceHeaterControl = ICE_HEATER_CONTROL_35_OVER;
        return HEAT_TORAL_TIME_35_OVER;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_heater_operation(void)
{
    U8 mu8_return_value = 0;

    if(gu16IceHeaterTime > 0)
    {
        gu16IceHeaterTime--;
		gu32_wifi_ice_heater_time++;
    }
    else{}

    if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_15_UNDER)
    {
        /*..hui [23-3-8���� 12:25:50] 15�� ����..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_15_UNDER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 10800) && (gu16IceHeaterTime < 11000))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 10450) && (gu16IceHeaterTime < 10800))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 10250) && (gu16IceHeaterTime < 10450))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 9850) && (gu16IceHeaterTime < 10250))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 9650) && (gu16IceHeaterTime < 9850))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 9250) && (gu16IceHeaterTime < 9650))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 9050) && (gu16IceHeaterTime < 9250))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 8650) && (gu16IceHeaterTime < 9050))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 8450) && (gu16IceHeaterTime < 8650))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 8050) && (gu16IceHeaterTime < 8450))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 7900) && (gu16IceHeaterTime < 8050))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 7500) && (gu16IceHeaterTime < 7900))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 7400) && (gu16IceHeaterTime < 7500))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 7000) && (gu16IceHeaterTime < 7400))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 6900) && (gu16IceHeaterTime < 7000))
        {
            F_IceHeater = SET;
        }
        else{}


        if((gu16IceHeaterTime >= 6500) && (gu16IceHeaterTime < 6900))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 6400) && (gu16IceHeaterTime < 6500))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 6000) && (gu16IceHeaterTime < 6400))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 5900) && (gu16IceHeaterTime < 6000))
        {
            F_IceHeater = SET;
        }
        else{}

        if(gu16IceHeaterTime < 5900)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_20_UNDER)
    {
        /*..hui [20-3-17���� 3:06:59] 20�� ����..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_20_UNDER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 4300) && (gu16IceHeaterTime < 4500))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 3950) && (gu16IceHeaterTime < 4300))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 3750) && (gu16IceHeaterTime < 3950))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 3400) && (gu16IceHeaterTime < 3750))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 3250) && (gu16IceHeaterTime < 3400))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2900) && (gu16IceHeaterTime < 3250))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2750) && (gu16IceHeaterTime < 2900))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2350) && (gu16IceHeaterTime < 2750))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2200) && (gu16IceHeaterTime < 2350))
        {
            F_IceHeater = SET;
        }
        else{}

        if(gu16IceHeaterTime < 2200)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_25_UNDER)
    {
        /*..hui [20-1-20���� 11:35:55] 15�� �ʰ�, 25�� ����..*/
        /*..hui [20-3-17���� 3:09:18] 25�� ����..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_25_UNDER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2800) && (gu16IceHeaterTime < 3000))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2500) && (gu16IceHeaterTime < 2800))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2350) && (gu16IceHeaterTime < 2500))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2050) && (gu16IceHeaterTime < 2350))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 1900) && (gu16IceHeaterTime < 2050))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 1600) && (gu16IceHeaterTime < 1900))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 1500) && (gu16IceHeaterTime < 1600))
        {
            F_IceHeater = SET;
        }
        else{}

        if(gu16IceHeaterTime < 1500)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_30_UNDER)
    {
        /*..hui [20-3-10���� 11:37:19] 25�� �ʰ�, 30�� ����.. ����ȭ..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_30_UNDER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2550) && (gu16IceHeaterTime < 2700))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2250) && (gu16IceHeaterTime < 2550))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2100) && (gu16IceHeaterTime < 2250))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 1800) && (gu16IceHeaterTime < 2100))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 1650) && (gu16IceHeaterTime < 1800))
        {
            F_IceHeater = SET;
        }
        else{}

        if(gu16IceHeaterTime < 1650)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)             //off
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_35_UNDER)
    {
        /*..hui [20-3-10���� 11:41:38] 30�� �ʰ� ~ 35�� ����.. ����ȭ..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_35_UNDER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2550) && (gu16IceHeaterTime < 2700))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2250) && (gu16IceHeaterTime < 2550))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2100) && (gu16IceHeaterTime < 2250))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 1800) && (gu16IceHeaterTime < 2100))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 1700) && (gu16IceHeaterTime < 1800))
        {
            F_IceHeater = SET;
        }
        else{}

        if(gu16IceHeaterTime < 1700)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)             //off
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl == ICE_HEATER_CONTROL_35_OVER)
    {
        /*..hui [20-1-20���� 11:36:11] 35�� �ʰ�..*/
        if(gu16IceHeaterTime >= HEAT_TORAL_TIME_35_OVER)
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2550) && (gu16IceHeaterTime < 2700))
        {
            F_IceHeater = SET;
        }
        else{}

        if((gu16IceHeaterTime >= 2250) && (gu16IceHeaterTime < 2550))
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if((gu16IceHeaterTime >= 2150) && (gu16IceHeaterTime < 2250))
        {
            F_IceHeater = SET;
        }
        else{}

        if( gu16IceHeaterTime < 2150 )
        {
            F_IceHeater = CLEAR;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = CLEAR;
            mu8_return_value = SET;
        }
        else{}
    }
    else
    {
        F_IceHeater = CLEAR;
        mu8_return_value = SET;
    }

    return mu8_return_value;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void recovery_ice_tray(void)
{
    /*..hui [18-3-22���� 9:39:58] �ⱸ���� ������ ������ �ƿ���Ʈ���̰� ������ ���� �߻��Ҽ�����..*/
    /*..hui [18-3-22���� 9:40:16] ���̽�Ʈ���̰� ������ 10�ʿ� �ѹ��� �ٽ� �÷��ش�..*/
    if(gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_MAKING)
    {
        /*..hui [18-3-22���� 10:00:09] Ʈ���� ��õ���� �߿��� ���۾���..*/
        if(F_Safety_Routine != SET)
        {
            gu8_ice_tray_reovery_time++;
        }
        else
        {
            gu8_ice_tray_reovery_time = 0;
        }

        if(gu8_ice_tray_reovery_time >= 200)
        {
            gu8_ice_tray_reovery_time = 0;
            up_tray_motor();
        }
        else{}
    }
    else
    {
        gu8_ice_tray_reovery_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



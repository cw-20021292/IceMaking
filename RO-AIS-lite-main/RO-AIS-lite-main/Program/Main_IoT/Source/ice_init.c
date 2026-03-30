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
#include    "ice_init.h"


void ice_init_operation(void);
void normal_mode_ice_init_operation(void);
U8 ice_init_ice_heater_opr(void);


bit F_IceInit;


U16 gu16IniStepDelay;

U16 gu16_dummy_heating_delay_time;




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_init_operation(void)
{
    normal_mode_ice_init_operation();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void normal_mode_ice_init_operation(void)
{
    U8 mu8_return_value = 0;

    // 20120821 DUMMY 로시 기준 적용.
    switch(gu8InitStep)
    {
        case 0 :

              if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)                              // 탈빙위치 이동
              {
                  gu8InitStep = 1;
              }
              else{}

              if((gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
                  || (gu8IceTrayLEV == ICE_TRAY_POSITION_MOVING))      // 이동 중/제빙 위치 -> 탈빙위치
              {
                  down_tray_motor();
              }
              else{}     // 제빙 -> 3분 더미 제빙

              break;

        case 1 :

              if(F_TrayMotorCW != SET && F_TrayMotorCCW != SET
                 && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
              {
                  gu8InitStep = 2;
              }
              else{}

              break;

        case 2 :

              /*..hui [19-7-18오후 1:25:58] 셀렉트바 사양.. 삭제..*/
              #if 0
              if(gu16IniStepDelay > 0)
              {
                  gu16IniStepDelay--;
                  return;             // Inidelay 40sec
              }
              else{}
              #endif

              gu8InitStep = 3;

              break;

        case 3  :

              if(gu16CompOffDelay == 0)
              {
                  /*..hui [19-7-25오후 1:36:36] 냉매 전환밸브 얼음 방향 이동..*/
                  GasSwitchIce();
                  gu8InitStep = 4;
              }
              else{}

              break;

        case 4  :

             if(gu8_GasSwitch_Status == GAS_SWITCH_ICE)
             {
                 gu16IceMakeTime = DUMMY_ICE_MELT_TIME;        // 더미제빙 3분
                 gu8InitStep = 5;

                 #if  0
                 if( (F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
                     || Bit4_Hot_Water_COMP_Off_State == SET )
                 {
                     /*..hui [20-2-12오후 4:43:37] 온수 사용중이면 온수 사용 종료하고 2초 후 가동..*/

                 }
                 else
                 {
                     gu8InitStep = 5;
                 }
                 #endif
             }
             else{}

             break;

        case 5 :

             if(gu16IceMakeTime > 0)
             {
                 gu16IceMakeTime--;            // Dummy 2분 제빙 대기
             }
             else{}

             if(gu16IceMakeTime == 0)
             {
                 gu8InitStep = 6;
             }
             else{}

             break;

        case 6 :

            F_TrayMotorCCW = 1;        // 강제 탈빙

            gu16IceHeaterTime = calc_ice_heater_time();

            gu8InitStep = 7;

            break;

        case 7 :

            /*mu8_return_value = ice_init_ice_heater_opr();*/

            mu8_return_value = ice_heater_operation();

            if(mu8_return_value == SET)
            {
                gu8InitStep = 8;
                gu16_dummy_heating_delay_time = 0;
            }
            else{}

            break;

        case 8 :

            gu8InitStep = 9;

            /*..hui [19-9-20오후 1:50:46] 우선 대기.. 나중에 제빙 실험해보고 확정..*/
            #if 0
            if(gu16CompOffDelay == 0)
            {
                gu16_dummy_heating_delay_time++;

                if(gu16_dummy_heating_delay_time >= 1800)
                {
                    gu16_dummy_heating_delay_time = 0;
                    gu8InitStep = 9;
                }
                else{}
            }
            else
            {
                /*pCOMP = 0;*/
            }
            #endif

            break;

        case 9 :

            F_IceInit = 0;
            //F_IceMakeGo = 0;
            gu8InitStep = 0;
            gu8IceStep = STATE_0_STANDBY;

            break;


        default :

            gu8InitStep = 0;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 ice_init_ice_heater_opr(void)
{
    U8 mu8_return_value = 0;

    if(gu16IceHeaterTime > 0)
    {
        gu16IceHeaterTime--;
    }
    else{}

    // 20160509 SUS EVA 적용
    // 20160530 Sus EVA 추가 변경
    if(gu8_IceHeaterControl == 1)
    {
        if(gu16IceHeaterTime >= 300)
        {
            F_IceHeater = 1;
        }
        else{}

        if((gu16IceHeaterTime >= 100) && (gu16IceHeaterTime < 300))
        {
            F_IceHeater = 0;
        }
        else{}

        if(gu16IceHeaterTime < 100)
        {
            F_IceHeater = 1;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = 0;
            gu16IceHeaterTime = 0;
            /*gu8InitStep = 8;*/
            mu8_return_value = SET;
        }
        else{}
    }
    else if(gu8_IceHeaterControl >= 2)
    {
        if(gu16IceHeaterTime >= 400)
        {
            F_IceHeater = 1;
        }
        else{}

        if((gu16IceHeaterTime >= 200) && (gu16IceHeaterTime < 400))
        {
            F_IceHeater = 0;
        }
        else{}

        if(gu16IceHeaterTime < 200)
        {
            F_IceHeater = 1;
        }
        else{}

        if(gu16IceHeaterTime == 0)
        {
            F_IceHeater = 0;
            gu16IceHeaterTime = 0;
            /*gu8InitStep = 8;*/
            mu8_return_value = SET;
        }
    }
    else{}

    return mu8_return_value;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



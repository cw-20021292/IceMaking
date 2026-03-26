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


bit F_IceInit;


U16 gu16IniStepDelay;





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
    U8 mu8_return = 0;
    U8 mu8_comp_rps = 0;

    // 20120821 DUMMY ·Î½Ã ±âÁØ Àû¿ë.
    switch(gu8InitStep)
    {
        case 0 :

              if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)                              // Å»ºùÀ§Ä¡ ÀÌµ¿
              {
                  gu8InitStep = 1;
              }
              else{}

              if((gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
                  || (gu8IceTrayLEV == ICE_TRAY_POSITION_MOVING))      // ÀÌµ¿ Áß/Á¦ºù À§Ä¡ -> Å»ºùÀ§Ä¡
              {
                  down_tray_motor();
              }
              else{}     // Á¦ºù -> 3ºÐ ´õ¹Ì Á¦ºù

              break;

        case 1 :

              if(F_TrayMotorUP != SET && F_TrayMotorDOWN != SET
                 && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
              {
                  gu8InitStep = 2;
              }
              else{}

              break;

        case 2 :

              gu8InitStep = 3;

              break;

        case 3  :

              if(gu16CompOffDelay == 0)
              {
                  /*..hui [19-7-25¿ÀÈÄ 1:36:36] ³Ã¸Å ÀüÈ¯¹ëºê ¾óÀ½ ¹æÇâ ÀÌµ¿..*/
                  GasSwitchIce();
                  gu8InitStep = 4;
              }
              else{}

              break;

        case 4  :

             if(gu8_GasSwitch_Status == GAS_SWITCH_ICE)
             {
                 gu16IceMakeTime = DUMMY_ICE_MELT_TIME;
                 gu8InitStep = 5;

                 mu8_comp_rps = get_ice_mode_comp_rps();
                 set_comp_rps( mu8_comp_rps );
             }
             else{}

             break;

        case 5 :

             if(gu16IceMakeTime > 0)
             {
                 gu16IceMakeTime--;
             }
             else{}

             if(gu16IceMakeTime == 0)
             {
                 gu8InitStep = 6;
             }
             else{}

             break;

        case 6 :

            F_TrayMotorDOWN = 1;
            mu8_comp_rps = get_hotgas_mode_comp_rps();
            set_comp_rps( mu8_comp_rps );

            gu16IceHeaterTime = get_hotgas_time();

            GasSwitchHotGas();

            gu8InitStep = 7;

            break;

        case 7 :

            mu8_return = hot_gas_operation();

            if( mu8_return == SET )
            {
                gu8InitStep = 8;
            }
            else{}

            break;

        case 8 :

            gu8InitStep = 9;

            break;

        case 9 :

            F_IceInit = 0;
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



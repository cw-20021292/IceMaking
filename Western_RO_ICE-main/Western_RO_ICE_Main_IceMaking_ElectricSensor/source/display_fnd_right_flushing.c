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
#include    "display_fnd_right_flushing.h"


void fnd_right_flushing_state(void);

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_flushing_state(void)
{
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;


    /*..hui [23-8-18오후 3:14:08] 플러싱할때 오른쪽 OFF 후 퍼센트로만 표시하도록 변경됨..*/
    /*..hui [23-8-18오후 3:14:25] 탱크 플러싱 떄문에 시간을 정확하게 알 수 없기때문.....*/
    mu8_temporary_hundred = DISPLAY_OFF;
    mu8_temporary_ten = DISPLAY_OFF;
    mu8_temporary_one = DISPLAY_OFF;

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);

}











/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/





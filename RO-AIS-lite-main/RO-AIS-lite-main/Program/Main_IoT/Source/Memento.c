/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Memento.h"

void ErrorSaveStart( U8 mu8_err_code );
void ErrorSave(void);
void display_memento_mode( void );
void memento_err_display( U8 mu8_err_num );

/*..메멘토..*/
U8 u8Memento_Buff[] = {0,0,0,0,0,0};
bit F_ErrorSave;
U8  u8ErrorSaveCount;

U8  u8LEDOnTime;            //LED ON Time Memento
U8  u8LEDMementoBlinkCnt;
U8  u8MementoBufferCnt;
bit F_Memento;

U8  u8LEDMementoStep; /**********test*******************/

U8 u8Memento_Display_LED_Timer;
U8 u8Memento_Display_Cnt;

U8 gu8_error_occur_year[5];
U8 gu8_error_occur_month[5];
U8 gu8_error_occur_day[5];

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ErrorSaveStart( U8 mu8_err_code )
{
/**********..Error Code..*****************************************/
/**********..1: 급수에러(F_WaterSupplyError))..********************/
/**********..2: 누수에러(F_WaterLeakError))..**********************/
/**********..3: 변좌온도에러(F_SeatTempOverError))..**************/
/**********..4: 출수온도에러(F_OutTempOverError))..***************/
/**********..5: 출수Short/Open에러(F_WaterTempShortOpenError))..*/
/**********..6: 변좌Short/Open에러(F_SeatTempShortOpenError)..***/

    U8 mu8ErrorState = 0;

    if(u8Memento_Buff[0] == mu8_err_code || mu8_err_code == 0) /*..에러가 같으면 나간다..*/
    {
        return;
    }
    else{}

    u8Memento_Buff[4] = u8Memento_Buff[3];
    u8Memento_Buff[3] = u8Memento_Buff[2];
    u8Memento_Buff[2] = u8Memento_Buff[1];
    u8Memento_Buff[1] = u8Memento_Buff[0];
    u8Memento_Buff[0] = mu8_err_code;

    F_ErrorSave = SET;  /*..저장 시작..*/
    u8ErrorSaveCount = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ErrorSave(void)
{
    if(F_ErrorSave != SET)
    {
        return;
    }
    else{}

    gu8_eeprom_wbuf[0] = u8Memento_Buff[0];
    gu8_eeprom_wbuf[1] = u8Memento_Buff[1];
    gu8_eeprom_wbuf[2] = u8Memento_Buff[2];
    gu8_eeprom_wbuf[3] = u8Memento_Buff[3];
    gu8_eeprom_wbuf[4] = u8Memento_Buff[4];

    EepromPageWrite(MEMENTO_START_ADDR, gu8_eeprom_wbuf, MEMENTO_LENGTH);

    F_ErrorSave = CLEAR;
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_memento_mode( void )
{



}







void memento_err_display( U8 mu8_err_num )
{
    /*..hui [18-1-9오후 9:36:46] 메멘토 모드에서 시스템 정지하기 위해..*/
    //F_HardError = SET;
    gu8_Error_Code = mu8_err_num;

    //display_error_state();
}









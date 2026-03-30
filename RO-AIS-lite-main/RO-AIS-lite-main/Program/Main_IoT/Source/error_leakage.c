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
#include    "error_leakage.h"

void check_flow_error(void);
void check_error_leakage_sensor(void);
void check_error_blocked_trayin(void);


U16 gu16_LeakageCheckCount;
U16 gu16_LeakageCheckCount2;


U16 u16_tray_water_in_timer;
U16 u16_tray_flow_check_timer;

bit F_Tray_In_Error_Temporary;
U16 u16_tray_input_add_timer;

U8 gu8_tray_wrong_flow_retry_cnt;
U8 gu8_tray_normal_flow_retry_cnt;


typedef enum
{
    TEST_ADC_GENERAL,
    TEST_ADC_TRAY_IN,
    TEST_ADC_ICE_MAKE_COMPLPTE,
    TEST_ADC_MAX,
} TEST_ADC_T;

U16 gu16IceMakingAdc[TEST_ADC_MAX];

extern ICE_STEP gu8IceStep;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_flow_error(void)
{
    /*..hui [18-11-22���� 3:36:39] ���� ���� ����..*/
    check_error_leakage_sensor();
    /*..hui [18-11-22���� 3:36:46] �������� ���� ����..*/
    //check_error_leaked_water_flow();
    /*..hui [18-11-22���� 3:36:52] �ܼ� ����..*/
    //check_error_blocked_water_flow();

    check_error_blocked_trayin();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_leakage_sensor(void)
{
#if 0
    if( gu16IceMakingADVal >= LEAKAGE_DETECT_AD )
    {
        gu16_LeakageCheckCount2 = 0;

        if( gu16_LeakageCheckCount < LEAKAGE_ERROR_DETECT_TIME )
        {
            gu16_LeakageCheckCount++;
        }
        else
        {
            if(Bit3_Leakage_Sensor_Error != SET)
            {
                Bit3_Leakage_Sensor_Error = SET;
            }
            else{}
        }
    }
    else
    {
        gu16_LeakageCheckCount = 0;

        if( gu16_LeakageCheckCount2 < LEAKAGE_ERROR_CLEAR_TIME )
        {
            gu16_LeakageCheckCount2++;
        }
        else
        {
            Bit3_Leakage_Sensor_Error = CLEAR;
        }
    }
#endif

    
    // 시침(?)으로 얼음 만들어진 것을 확인하는 컨셉
    // 1. 평상시
    // 2. 입수 했을 때
    // 3. 제빙완료 됐을 때
    // 세 가지 케이스 ADC값 캡처

    // 1. 평상시
    if(gu8IceStep == STATE_12_CHECK_DRAIN_LEVEL)
    {
        gu16IceMakingAdc[TEST_ADC_GENERAL] = gu16IceMakingADVal;
    }
    // 2. 트레이 입수할 때
    else if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        gu16IceMakingAdc[TEST_ADC_TRAY_IN] = gu16IceMakingADVal;
    }
    // 3. 제빙완료 됐을 때
    else if(gu8IceStep == STATE_40_ICE_TRAY_MOVE_DOWN)
    {
        gu16IceMakingAdc[TEST_ADC_ICE_MAKE_COMPLPTE] = gu16IceMakingADVal;
    }
    else
    {
        // ?
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_blocked_trayin(void)
{
    U16 mu16_clear_time = 0;

    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY
       && F_Tray_In_Error_Temporary != SET)
    {
        /*if(pVALVE_ICE_TRAY_IN == SET && bit_tray_pump_output == SET)*/
        if( bit_tray_pump_output == SET )
        {
            /*..hui [20-11-30���� 3:33:32] 5Hz ���Ϸ� 10�� �̻� ���� �� ���� ���� FULL�� ����..*/
            if( gu8_Flow_1sec <= HOT_BLOCKED_FLOW_HZ )
            {
                u16_tray_flow_check_timer++;

                if(u16_tray_flow_check_timer >= BLOCKED_TRAIN_IN_CHECK_TIME)
                {
                    u16_tray_flow_check_timer = 0;
                    F_Tray_In_Error_Temporary = SET;
                }
                else{}
            }
            else
            {
                u16_tray_flow_check_timer = 0;
            }
        }
        else
        {
            if( F_WaterOut == SET )
            {
                /*..hui [20-6-22���� 10:21:02] �����Ҷ� ī��Ʈ �ʱ�ȭ�ϵ��� ����.. �ݺ����� �����϶� ���������� ����� ���̷����������..*/
                /*..hui [20-6-22���� 10:21:06] �̽������..*/
                u16_tray_flow_check_timer = 0;
            }
            else{}
        }
    }
    else
    {
        u16_tray_flow_check_timer = 0;
    }

    if( F_Tray_In_Error_Temporary == SET )
    {
        mu16_clear_time = BLOCKED_TRAY_ADD_TIME;

        /*..hui [20-11-30���� 4:05:29] Ʈ���� ��� �����ְ� ���� �����߿��� ī��Ʈ�ϴ°ɷ�..*/
        /*if(pVALVE_ICE_TRAY_IN == SET && bit_tray_pump_output == SET)*/
        if( bit_tray_pump_output == SET )
        {
            u16_tray_input_add_timer++;
        }
        else{}

        /*..hui [20-11-30���� 3:52:36] 1�е��� ���� FULL�� ���� �� ���� ����..*/
        if( u16_tray_input_add_timer >= mu16_clear_time )
        {
            F_Tray_In_Error_Temporary = CLEAR;
            u16_tray_input_add_timer = 0;

            /*..hui [20-11-30���� 3:57:17] �������� ���� �ȵǴ��� �����ð����� FULL�� ���� �� ���� ���ٰ� �Ǵ��ϰ� ����..*/
            /*..hui [20-11-30���� 3:57:42] ��뿬 �����..������ �׳� ������..*/
            /*..hui [20-11-30���� 3:57:46] ��� ���� �ȵɶ� FULL�� �����ϴ� ����� ���ܵδ°� ���� �� ����..*/
            gu16_Ice_Tray_Fill_Hz = 0;
        }
        else{}
    }
    else
    {
        u16_tray_input_add_timer = 0;
    }

    /*..hui [20-11-30���� 4:57:17] ���� FULL ������ �������� �������� ���ƿͼ� ����� ��� ���..*/
    /*..hui [20-11-30���� 4:57:30] Ʈ���� �Լ� state �����ϰ��� �ʱ�ȭ�ϵ���..*/
    if( gu8IceStep != STATE_20_WATER_IN_ICE_TRAY )
    {
        F_Tray_In_Error_Temporary = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



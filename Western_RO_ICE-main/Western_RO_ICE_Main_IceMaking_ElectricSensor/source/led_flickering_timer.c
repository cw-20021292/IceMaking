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
#include    "led_flickering_timer.h"


#if 0
U8 Ice_ongoing_extract_flick_timer(U8 interval);
U8 Ice_extract_flickering_timer(U8 flick_time, U8 interval);
U8 Ice_lock_led_flickering_timer(U8 flick_time, U8 interval);
U8 hot_water_lock_led_flickering_timer(U8 flick_time, U8 interval);
//U8 low_water_led_flickering_timer(U8 flick_time, U8 interval);
#endif


U8 gu8_ice_ext_flick_tmr;
U8 gu8_ice_lock_flick_tmr;
U8 gu8_hot_water_lock_flick_tmr;
U8 gu8_low_water_flick_tmr;
U8 gu8_all_lock_flick_tmr;


U8 gu8_ice_ext_ongoing_flick_tmr;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U8 Ice_ongoing_extract_flick_timer(U8 interval)
{
    U8 u8flick_state = 0;

    gu8_ice_ext_ongoing_flick_tmr++;

    if(gu8_ice_ext_ongoing_flick_tmr >= interval)
    {
        /*u16IceExtractionLED = 0;*/
        u8flick_state = CLEAR;

        if(gu8_ice_ext_ongoing_flick_tmr >= (interval * 2))
        {
            gu8_ice_ext_ongoing_flick_tmr = 0;
        }
        else{}
    }
    else
    {
        /*u16IceExtractionLED = 0x3FF;*/
        u8flick_state = SET;
        #if 0
        if( (gu8_ice_ext_flick_tmr % 5) == 0 )
        {
            u16IceExtractionLED ^= 0x3FF;
        }
        else{}
        #endif
    }

    return u8flick_state;
}











U8 Ice_extract_flickering_timer(U8 flick_time, U8 interval)
{
    U8 u8flick_state = 0;

    gu8_ice_ext_flick_tmr++;

    if(gu8_ice_ext_flick_tmr >= (flick_time - 1))
    {
        gu8_ice_ext_flick_tmr = 0;
        Bit1_Ice_Lock_Extract_LED_Flick = CLEAR;
        //u16IceExtractionLED = 0x3ff;
    }
    else
    {
        if( (gu8_ice_ext_flick_tmr % interval) == 0 )
        {
            /*u16IceExtractionLED ^= 0x3ff;*/
            u8flick_state = SET;
        }
        else{}
    }

    return u8flick_state;
}








U8 Ice_lock_led_flickering_timer(U8 flick_time, U8 interval)
{
    U8 u8flick_state = 0;

    gu8_ice_lock_flick_tmr++;

    if(gu8_ice_lock_flick_tmr >= (flick_time - 1))
    {
        gu8_ice_lock_flick_tmr = 0;
        Bit0_Ice_Lock_LED_Flick = CLEAR;

    }
    else
    {
        if( (gu8_ice_lock_flick_tmr % interval) == 0 )
        {
            /*Bit4_Ice_Lock_Led1_White ^= SET;
                      Bit5_Ice_Lock_Led2_White ^= SET;*/
            u8flick_state = SET;
        }
        else{}
    }

    return u8flick_state;
}



U8 hot_water_lock_led_flickering_timer(U8 flick_time, U8 interval)
{
    U8 u8flick_state = 0;

    gu8_hot_water_lock_flick_tmr++;

    if(gu8_hot_water_lock_flick_tmr >= (flick_time - 1))
    {
        gu8_hot_water_lock_flick_tmr = 0;
        Bit2_Hot_Water_Lock_LED_Flick = CLEAR;
        //u16IceExtractionLED = 0x3ff;
    }
    else
    {
        if( (gu8_hot_water_lock_flick_tmr % interval) == 0 )
        {
            /*Bit5_Hot_Water_Lock_Led1_White ^= SET;
                      Bit6_Hot_Water_Lock_Led2_White ^= SET;*/
            u8flick_state = SET;
        }
        else{}
    }

    return u8flick_state;
}


U8 all_lock_led_flickering_timer(U8 flick_time, U8 interval)
{
    U8 u8flick_state = 0;

    gu8_all_lock_flick_tmr++;

    if(gu8_all_lock_flick_tmr >= (flick_time - 1))
    {
        gu8_all_lock_flick_tmr = 0;
        Bit3_All_Lock_Water_Extract_LED_Flick = CLEAR;
        //u16IceExtractionLED = 0x3ff;
    }
    else
    {
        if( (gu8_all_lock_flick_tmr % interval) == 0 )
        {
            /*Bit5_Hot_Water_Lock_Led1_White ^= SET;
                      Bit6_Hot_Water_Lock_Led2_White ^= SET;*/
            u8flick_state = SET;
        }
        else{}
    }

    return u8flick_state;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/










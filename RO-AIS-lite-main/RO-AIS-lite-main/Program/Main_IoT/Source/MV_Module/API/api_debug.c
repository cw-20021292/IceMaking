
#include "api_debug.h"
#include    "Global_Variable.h"
int putchar(int c)
{
    Uart_Send_Data(UART_CHANNEL_3, (U8)c);

    if (c == '\n')
    {
        Uart_Send_Data(UART_CHANNEL_3, '\r');
    }

    return c;
}


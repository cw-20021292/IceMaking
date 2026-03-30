/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : 
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "Util.h"


U16 HexToAsc(U8 mu8RxdData);
U8 AscToHex(U8 mu8RxdData1, U8 mu8RxdData2);
U8 Nibble(U8 mu8RxdData);
U16 Rx_CRC_CCITT(U8 *puchMsg, U8 usDataLen);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : HexToAsc
// 개요       : Hex to Asc 변환 
//----------------------------------------------------------------------------
// 기능       : Hex 1 byte -> Asc 2 byte 로 변환
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U16 HexToAsc(U8 mu8RxdData)
{
    U8 mu8Temp_Data1;
    U16 mu16Temp_Data1;

    mu8Temp_Data1 = mu8RxdData >> 4;                           // 상위4비트
    mu8Temp_Data1 = mu8Temp_Data1 & 0x0f;
    mu8RxdData = mu8RxdData & 0x0f;                            // 하위4비트

    if(mu8Temp_Data1>=0x0a) mu8Temp_Data1 = mu8Temp_Data1 + 0x37;
    else mu8Temp_Data1 = mu8Temp_Data1 + 0x30;

    if(mu8RxdData>=0x0a) mu8RxdData = mu8RxdData + 0x37;
    else mu8RxdData = mu8RxdData + 0x30;

    mu16Temp_Data1 = 0;
    mu16Temp_Data1 = mu8Temp_Data1;
    mu16Temp_Data1 = mu16Temp_Data1<<8;
    mu16Temp_Data1 = mu16Temp_Data1 + mu8RxdData;

    return mu16Temp_Data1;
}


//""SUBR COMMENT""************************************************************
// ID         : AscToHex
// 개요       : ASC to Hex 변환 
//----------------------------------------------------------------------------
// 기능       : ASC 2 byte -> HEX 1 byte 로 변환
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U8 AscToHex(U8 mu8RxdData1, U8 mu8RxdData2)
{
    U8 mu8Temp_Data1, mu8Temp_Data2;

    mu8Temp_Data1 = Nibble(mu8RxdData1);
    mu8Temp_Data2 = Nibble(mu8RxdData2);

    mu8Temp_Data1 = mu8Temp_Data1<<4;
    mu8Temp_Data1 = mu8Temp_Data1 | mu8Temp_Data2; 

    return mu8Temp_Data1;
}

//""SUBR COMMENT""************************************************************
// ID         : Nibble
// 개요       : ASC to Hex 변환 
//----------------------------------------------------------------------------
// 기능       : ASC 1 byte -> HEX 1 nibble 로 변환
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U8 Nibble(U8 mu8RxdData)
{
    U8 mu8Temp_Data1, mu8Temp_Data2;

    mu8Temp_Data1 = mu8RxdData - 0x30;
    if(mu8RxdData<0x30) return mu8Temp_Data1;

    mu8Temp_Data2 = (U8)(mu8Temp_Data1 + 0xe9);
    if(mu8Temp_Data1>0x16) return mu8Temp_Data2;

    mu8Temp_Data1 = mu8Temp_Data2 + 0x06;

    if(mu8Temp_Data2 > 0xf9)
    {
        mu8Temp_Data2 = mu8Temp_Data1 + 0x0a;
        return mu8Temp_Data2;
    }

    mu8Temp_Data2= mu8Temp_Data1 + 0x07;
    if(mu8Temp_Data1>0xf8) return mu8Temp_Data2;
    else mu8Temp_Data1 = mu8Temp_Data2 + 0x0a;

    return mu8Temp_Data1;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 
***********************************************************************************************************************/
U16 Rx_CRC_CCITT(U8 *puchMsg, U8 usDataLen)
{
    U8 i = 0;
    unsigned short  wCRCin = 0x0000;
    unsigned short  wCPoly = 0x1021;
    U16 wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);

        for(i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }

    return (wCRCin);
}




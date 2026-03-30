// #include "include/_include.h"
#include "WIFI_Common.h"
#include "WIFI_DefUser.h"
#include "WIFI_SetCommon.h"
#include "WIFI_UserInterface.h"
#include "WIFI_MonitorFixRAM.h"
// #include "WIFI_UserCommon.c"

extern U8 A_NULL=0;


static const WifiFixRamList_T WifiRamList[] =
{
	{A_U8_A301_COLD_WATER_LEV_LOW,              (U8*)(&A_NULL),               				   OneByte,        Read_Only     },


};
#define SZ_RAM_ADR_LIST ( sizeof(WifiRamList) / sizeof(WifiFixRamList_T) )
/*--------------------------------------------------*/
/*	Parameter : write Ram Address (server -> wifi)  */
/*	return : U8* write value(start address) (wifi -> mcu)           */
/*--------------------------------------------------*/
U8 *SetRamData (U16 mu16address)
{
    static U16 mu16Data = 0U;
    U8 *buf;
    switch ( mu16address )
    {    
        buf = (U8*)mu16address;     // fix ram value

        // case A_FF_HOT_AddOperation : 
        //     mu16Data = *buf;
        // break;
        // case A_FF_COLD_AddOperation : 
        //     mu16Data = *buf;
        // break;
 
        default:
            mu16Data = 0U;
        break;
    }
    return (U8*)(&mu16Data);
}

void GetRamData (void)
{
    __near U8 *pFixRamAddress ;
    // U8 *TempPtrFix ;
    U8 *pTempPtr ;
    U8 *pTempPtrReturn ;
    U16 RamCheckAddress =0;
    U8 i=0;
    WifiWriteFun_T pWriteFunc;

    for ( i = 0 ; i < SZ_RAM_ADR_LIST; i++ )
    {
        pFixRamAddress = ((__near U8*)WifiRamList[i].AddressList);
        pTempPtr = WifiRamList[i].TargetVariable;
        RamCheckAddress = (U16)(GetUserSystemRamWriteStatus((U16)(WifiRamList[i].AddressList)));
        if (pTempPtr == &A_NULL) 
        {
            RamCheckAddress = CLEAR_ADR;
            SetUserSystemRamWriteStatus((U16)RamCheckAddress); // clear
        }
        else {
            if (RamCheckAddress != CLEAR_ADR) // write check
            {
                pWriteFunc =  WifiRamList[i].WriteFunc;
                if ( pWriteFunc != Read_Only ) // write check
                {
                    pTempPtrReturn = (U8*)pWriteFunc((U16)(RamCheckAddress));
                    *(pTempPtr) = *(pTempPtrReturn); // 1byte write

                    if (WifiRamList[i].VarSize == TwoByte ) // 2byte write
                    {
                        pTempPtr++;
                        RamCheckAddress++;
                        pTempPtrReturn = (U8*)RamCheckAddress;
                        *(pTempPtr) = *(pTempPtrReturn);
                    }
                    RamCheckAddress = CLEAR_ADR;
                    SetUserSystemRamWriteStatus((U16)RamCheckAddress); // clear
                    break;
                }
                else 
                {
                    RamCheckAddress = CLEAR_ADR;
                    SetUserSystemRamWriteStatus((U16)RamCheckAddress); // clear
                }
            }
            else  // read
            { //1byte read
                *pFixRamAddress = *(WifiRamList[i].TargetVariable);

                if (WifiRamList[i].VarSize == TwoByte ) 
                { //2byte variable
                    pTempPtr = WifiRamList[i].TargetVariable;
                    pFixRamAddress++;
                    pTempPtr++;
                    *pFixRamAddress = *pTempPtr;
                }
            }
        }

    }
}

/***** Type Define *****************************************************************/ 
// typedef unsigned char       U8;
// typedef signed char         I8;
// typedef unsigned int        U16; 
// typedef signed int          I16; 

/******** Define Func *********/
void GetRamData (void);
U8 *SetRamData (U16);

/******** typedef *********/
typedef U8 *(*WifiWriteFun_T)(U16); 
typedef struct 
{ 
    U16 AddressList;  
    U8 *TargetVariable;  
    U8 VarSize; 
    WifiWriteFun_T WriteFunc; 
} WifiFixRamList_T; 
 

/***** Directmap *****************************************************************/ 
 
// __directmap     U8     gu8_A301_COLD_WATER_LEV_LOW      = {0xFFC00};

/***** Define Address *****************************************************************/ 
 
#define     A_U8_A301_COLD_WATER_LEV_LOW        (0xFC00)







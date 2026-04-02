/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/

#ifndef _Macro_Driver_H
#define _Macro_Driver_H

/***********************************************************************************************************************/
#pragma sfr
#pragma DI
#pragma EI
#pragma NOP

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
CLEAR, SET
}NUM_B;

typedef enum
{
OFF, ON
}NUM_C;

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef bit             BIT;
typedef char            I8;
typedef unsigned char   U8;
typedef int             I16;
typedef unsigned int    U16;
typedef unsigned long   U32;
typedef signed char     S8;
typedef signed int      S16;
typedef signed long     S32;
typedef float           F32;
typedef double          D64;

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;
typedef unsigned short      MD_STATUS;
/***********************************************************************************************************************/
typedef struct
{
    unsigned int b0:1;
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;
}BYTE_FIELD;

typedef union
{
    unsigned char byte;
    BYTE_FIELD Bit;
}TYPE_BYTE;
/***********************************************************************************************************************/
typedef struct
{
    unsigned int b0:1;
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;

    unsigned int b8:1;
    unsigned int b9:1;
    unsigned int b10:1;
    unsigned int b11:1;
    unsigned int b12:1;
    unsigned int b13:1;
    unsigned int b14:1;
    unsigned int b15:1;
}WORD_FIELD;

typedef union
{
    unsigned int word;
    unsigned char byte[2];
    WORD_FIELD Bit;
}TYPE_WORD;
/***********************************************************************************************************************/
typedef struct
{
	unsigned int b0:1;
	unsigned int b1:1;
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;

	unsigned int b8:1;
	unsigned int b9:1;
	unsigned int b10:1;
	unsigned int b11:1;
	unsigned int b12:1;
	unsigned int b13:1;
	unsigned int b14:1;
	unsigned int b15:1;

	unsigned int b16:1;
	unsigned int b17:1;
	unsigned int b18:1;
	unsigned int b19:1;
	unsigned int b20:1;
	unsigned int b21:1;
	unsigned int b22:1;
	unsigned int b23:1;

	unsigned int b24:1;
	unsigned int b25:1;
	unsigned int b26:1;
	unsigned int b27:1;
	unsigned int b28:1;
	unsigned int b29:1;
	unsigned int b30:1;
	unsigned int b31:1;
}LONG_FIELD;

typedef union
{
	unsigned long dward;
	unsigned int word[2];
	unsigned char byte[4];
	LONG_FIELD Bit;
}TYPE_LONG;

typedef struct
{
    unsigned int b0_3:4;
    unsigned int b4_7:4;
}DIMMING_FIELD;

typedef union
{
    unsigned char byte;
    DIMMING_FIELD nibble;
}TYPE_DIMMING;


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/*..hui [22-8-17���� 10:49:14] ��õ���� �����˻��� �߰�..*/
/*#define Main_FW_Version_Main      0*/
/*#define Main_FW_Version_Sub       2*/
/*..sean [23-9-14 ���� 5:49:14] ���÷��� �׽�Ʈ ��� ����..*/
/*#define Main_FW_Version_Main      1*/
/*#define Main_FW_Version_Sub       2*/

#define Main_FW_Version_Main      1
/*#define Main_FW_Version_Sub       3*/
#define Main_FW_Version_Sub       2



/*..hui [19-11-6���� 9:21:06] 1�̸� wifi ��� ON, 0�̸� wifi ��� OFF..*/
//#define CONFIG_MMI                  1
//#define CONFIG_MMI                1


/*..hui [19-10-17���� 5:37:48] 1�̸� CHP, 0�̸� CP..*/

/*..hui [19-11-1���� 9:52:39] ���� PBA ���� ���·� �� ����..*/
//#define CONFIG_HOT                1   /*..CHP Model..*/
//#define CONFIG_HOT                0   /*..CP Model..*/

/*..hui [19-7-23���� 1:57:46] 0�̸� PC ���, 1�̸� �ڵ��˻� ���..*/
//#define CONFIG_MP                 1



#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef struct NNSG2dUserExDataBlock {
    u32 blkTypeID;
    u32 blkSize;
} NNSG2dUserExDataBlock;
typedef struct NNSG2dUserExCellAttr {
    u32 * pAttr;
} NNSG2dUserExCellAttr;
typedef struct NNSG2dUserExCellAttrBank {
    u16 numCells;
    u16 numAttribute;
    NNSG2dUserExCellAttr * pCellAttrArray;
} NNSG2dUserExCellAttrBank;
void func_02011ae8(NNSG2dUserExCellAttrBank * pCellAttrBank);

/* func_02011878 -- NitroSystem g2d_NMC_load.c: UnpackExtendedData_. */
void func_02011878 (void * pExData)
{

    {
        NNSG2dUserExDataBlock * pBlk = (NNSG2dUserExDataBlock *)pExData;
        NNSG2dUserExCellAttrBank * pCellAttrBank = (NNSG2dUserExCellAttrBank *)(pBlk + 1);

        func_02011ae8(pCellAttrBank);
    }
}

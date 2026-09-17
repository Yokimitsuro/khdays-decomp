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



typedef enum NNSG2dCharacterDataMappingType {
    NNS_G2D_CHARACTERMAPPING_1D_32,
    NNS_G2D_CHARACTERMAPPING_1D_64,
    NNS_G2D_CHARACTERMAPPING_1D_128,
    NNS_G2D_CHARACTERMAPPING_1D_256,
    NNS_G2D_CHARACTERMAPPING_2D,
    NNS_G2D_CHARACTERMAPPING_MAX
} NNSG2dCharacterDataMappingType;
typedef struct NNSG2dCellVramTransferData {
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;
typedef struct NNSG2dVramTransferData {
    u32 szByteMax;
    NNSG2dCellVramTransferData * pCellTransferDataArray;
} NNSG2dVramTransferData;
typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;
typedef struct NNSG2dCellBoundingRectS16 {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
} NNSG2dCellBoundingRectS16;
typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;
} NNSG2dCellData;
typedef struct NNSG2dCellDataWithBR {
    NNSG2dCellData cellData;
    NNSG2dCellBoundingRectS16 boundingRect;
} NNSG2dCellDataWithBR;
typedef struct NNSG2dCellDataBank {
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMappingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dCellDataBank;
inline BOOL NNSi_G2dCellBankHasBR (const NNSG2dCellDataBank * pCellBank)
{
    return (BOOL)(pCellBank->cellBankAttr & 0x1 );
}

/* func_02011858 -- NitroSystem g2d_NOB_load.c: GetPtrOamArrayHead_. */
void * func_02011858 (NNSG2dCellDataBank * pCellBank)
{

    if (NNSi_G2dCellBankHasBR(pCellBank)) {
        return (NNSG2dCellDataWithBR *)(pCellBank->pCellDataArrayHead) + pCellBank->numCells;
    } else {
        return pCellBank->pCellDataArrayHead + pCellBank->numCells;
    }
}

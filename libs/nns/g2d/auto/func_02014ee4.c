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



typedef s32 fx32;
typedef union {
        struct {
            fx32 _00, _01;
            fx32 _10, _11;
        };
        fx32 m[2][2];
        fx32 a[4];
    } MtxFx22;
typedef struct {
        union {
            u32 attr01;
            struct {
                u16 attr0;
                u16 attr1;
            };
            struct {
                u32 y : 8;
                u32 rsMode : 2;
                u32 objMode : 2;
                u32 mosaic : 1;
                u32 colorMode : 1;
                u32 shape : 2;
                u32 x : 9;
                u32 rsParam : 5;
                u32 size : 2;
            };
            struct {
                u32 _0 : 28;
                u32 flipH : 1;
                u32 flipV : 1;
                u32 _1 : 2;
            };
        };
        union {
            struct {
                u16 attr2;
                u16 _3;
            };
            u32 attr23;
            struct {
                u32 charNo : 10;
                u32 priority : 2;
                u32 cParam : 4;
                u32 _2 : 16;
            };
        };
    } GXOamAttr;
typedef enum NNSG2dOamExDrawOrder {
    NNSG2D_OAMEX_DRAWORDER_BACKWARD = 0x0,
    NNSG2D_OAMEX_DRAWORDER_FORWARD  = 0x1
} NNSG2dOamExDrawOrder;
typedef u16 (*NNSG2dGetOamCpacityFuncPtr)();
typedef BOOL (*NNSG2dEntryNewOamFuncPtr)(const GXOamAttr * pOam, u16 index);
typedef u16 (*NNSG2dEntryNewOamAffineFuncPtr)(const MtxFx22 * mtx, u16 index);
typedef struct NNSG2dOamExEntryFunctions {
    NNSG2dGetOamCpacityFuncPtr getOamCapacity;
    NNSG2dGetOamCpacityFuncPtr getAffineCapacity;
    NNSG2dEntryNewOamFuncPtr entryNewOam;
    NNSG2dEntryNewOamAffineFuncPtr entryNewAffine;
} NNSG2dOamExEntryFunctions;
typedef struct NNSG2dOamChunk {
    GXOamAttr oam;
    u16 affineProxyIdx;
    u16 pad16_;
    struct NNSG2dOamChunk * pNext;
} NNSG2dOamChunk;
typedef struct NNSG2dOamChunkList {
    u16 numChunks;
    u16 numLastFrameDrawn;
    u16 numDrawn;
    u16 bDrawn;
    NNSG2dOamChunk * pChunks;
    NNSG2dOamChunk * pAffinedChunks;
    NNSG2dOamChunk * pLastChunk;
    NNSG2dOamChunk * pLastAffinedChunk;
} NNSG2dOamChunkList;
typedef struct NNSG2dAffineParamProxy {
    MtxFx22 mtxAffine;
    u16 affineHWIndex;
    u16 pad16_;
} NNSG2dAffineParamProxy;
typedef struct NNSG2dOamManagerInstanceEx {
    NNSG2dOamChunkList * pOamOrderingTbl;
    u16 numPooledOam;
    u16 numUsedOam;
    NNSG2dOamChunk * pPoolOamChunks;
    u16 lengthOfOrderingTbl;
    u16 lengthAffineBuffer;
    u16 numAffineBufferUsed;
    u16 lastFrameAffineIdx;
    NNSG2dAffineParamProxy * pAffineBuffer;
    NNSG2dOamExEntryFunctions oamEntryFuncs;
    u16 lastRenderedOrderingTblIdx;
    u16 lastRenderedChunkIdx;
    NNSG2dOamExDrawOrder drawOrderType;
} NNSG2dOamManagerInstanceEx;

/* func_02014ee4 -- NitroSystem g2d_OAMEx.c: NNSG2d_SetOamManExDrawOrderType. */
void func_02014ee4 (NNSG2dOamManagerInstanceEx * pOam, NNSG2dOamExDrawOrder drawOrderType)
{
    pOam->drawOrderType = drawOrderType;
}

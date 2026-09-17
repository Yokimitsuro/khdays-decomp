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


#define NNS_GFD_NUM_TEX_VRAM_REGION 5

typedef void (*NNSGfdFrmTexVramDebugDumpCallBack)(int index, u32 startAddr, u32 endAddr, u32 blockMax, BOOL bActive, void * pUserContext);
typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL bActive;
    const BOOL bHalfSize;
    const u16 index;
    const u16 pad16_;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;
typedef struct NNSGfdFrmTexVramMnager {
    u16 numSlot;
} NNSGfdFrmTexVramMnager;
extern NNSGfdFrmTexVramMnager data_02047360;
extern NNSGfdFrmTexRegionState data_02042418[5 ];
static inline void ResetRegionNormal_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 ;
}
static inline void ResetRegionHalf_ (NNSGfdFrmTexRegionState * pRegion)
{
    pRegion->head = 0x0;
    pRegion->tail = 0x20000 / 2;
}

/* func_02010f08 -- NitroSystem gfd_FrameTexVramMan.c: NNS_GfdResetFrmTexVramState. */
void func_02010f08 (void)
{
    int i;
    u16 numSlot = data_02047360.numSlot;

    const numRegion = (numSlot > 1) ? numSlot + 1 : numSlot + 0;


    for (i = 0; i < NNS_GFD_NUM_TEX_VRAM_REGION; i++) {
        if ( i < numRegion ) {
            data_02042418[i].bActive = TRUE;
        } else {
            data_02042418[i].bActive = FALSE;
        }

        if ( data_02042418[i].bHalfSize ) {
            ResetRegionHalf_(&data_02042418[i]);
        } else {
            ResetRegionNormal_(&data_02042418[i]);
        }
    }
}

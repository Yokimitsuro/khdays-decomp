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



typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_MAX
} NNSG2dAnimationPlayMode;
typedef struct NNSG2dAnimFrameData {
    void * pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrameData;
typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrameData * pAnmFrameArray;
} NNSG2dAnimSequenceData;
typedef struct NNSG2dAnimBankData {
    u16 numSequences;
    u16 numTotalFrames;
    NNSG2dAnimSequenceData * pSequenceArrayHead;
    NNSG2dAnimFrameData * pFrameArrayHead;
    void * pAnimContents;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dAnimBankData;
inline u16 NNS_G2dGetNumAnimSequence (const NNSG2dAnimBankData * pAnimBank)
{
    return pAnimBank->numSequences;
}

/* func_02011840 -- NitroSystem g2d_NAN_load.c: NNS_G2dGetAnimSequenceByIdx. */
const NNSG2dAnimSequenceData * func_02011840 (const NNSG2dAnimBankData * pAnimBank, u16 idx)
{

    if (NNS_G2dGetNumAnimSequence(pAnimBank) > idx) {
        return &pAnimBank->pSequenceArrayHead[idx];
    } else {
        return NULL;
    }
}

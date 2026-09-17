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

#define NNS_G2D_UNPACK_OFFSET_PTR(ptr, baseOffs) (ptr) = (void *)((u32)(ptr) + (u32)baseOffs)

typedef struct NNSG2dUserExDataBlock {
    u32 blkTypeID;
    u32 blkSize;
} NNSG2dUserExDataBlock;
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
typedef struct NNSG2dUserExAnimFrameAttr {
    u32 * pAttr;
} NNSG2dUserExAnimFrameAttr;
typedef struct NNSG2dUserExAnimSequenceAttr {
    u16 numFrames;
    u16 pad16;
    u32 * pAttr;
    NNSG2dUserExAnimFrameAttr * pAnmFrmAttrArray;
} NNSG2dUserExAnimSequenceAttr;
typedef struct NNSG2dUserExAnimAttrBank {
    u16 numSequences;
    u16 numAttribute;
    NNSG2dUserExAnimSequenceAttr * pAnmSeqAttrArray;
} NNSG2dUserExAnimAttrBank;

/* func_020116f0 -- NitroSystem g2d_NAN_load.c: NNS_G2dUnpackNAN. */
void func_020116f0 (NNSG2dAnimBankData * pData)
{
    u16 i, j;


    pData->pSequenceArrayHead = NNS_G2D_UNPACK_OFFSET_PTR(pData->pSequenceArrayHead, pData);
    pData->pFrameArrayHead = NNS_G2D_UNPACK_OFFSET_PTR(pData->pFrameArrayHead, pData);
    pData->pAnimContents = NNS_G2D_UNPACK_OFFSET_PTR(pData->pAnimContents, pData);

    {
        NNSG2dAnimSequenceData * pSeq = pData->pSequenceArrayHead;
        NNSG2dAnimFrameData * pFrameBase = pData->pFrameArrayHead;
        void * pContentsBase = pData->pAnimContents;

        for (i = 0; i < pData->numSequences; i++) {
            pSeq[i].pAnmFrameArray = NNS_G2D_UNPACK_OFFSET_PTR(pSeq[i].pAnmFrameArray, pFrameBase);

            for (j = 0; j < pSeq[i].numFrames; j++) {
                pSeq[i].pAnmFrameArray[j].pContent =
                    NNS_G2D_UNPACK_OFFSET_PTR(pSeq[i].pAnmFrameArray[j].pContent, pContentsBase);
            }

        }
    }

    if (pData->pExtendedData != NULL) {
        pData->pExtendedData = NNS_G2D_UNPACK_OFFSET_PTR(pData->pExtendedData, pData);
        {
            u32 i = 0;
            u32 j = 0;

            NNSG2dUserExDataBlock * pExBlk = (NNSG2dUserExDataBlock *)pData->pExtendedData;
            NNSG2dUserExAnimAttrBank * pAnmExAttrBank = (NNSG2dUserExAnimAttrBank *)(pExBlk + 1);
            pAnmExAttrBank->pAnmSeqAttrArray = NNS_G2D_UNPACK_OFFSET_PTR(pAnmExAttrBank->pAnmSeqAttrArray, pAnmExAttrBank);

            for (i = 0; i < pAnmExAttrBank->numSequences; i++) {
                NNSG2dUserExAnimSequenceAttr * pSeqAttr = &pAnmExAttrBank->pAnmSeqAttrArray[i];

                pSeqAttr->pAttr = NNS_G2D_UNPACK_OFFSET_PTR(pSeqAttr->pAttr, pAnmExAttrBank);
                pSeqAttr->pAnmFrmAttrArray = NNS_G2D_UNPACK_OFFSET_PTR(pSeqAttr->pAnmFrmAttrArray, pAnmExAttrBank);
                for (j = 0; j < pSeqAttr->numFrames; j++) {
                    NNSG2dUserExAnimFrameAttr * pFrm = &pSeqAttr->pAnmFrmAttrArray[j];
                    pFrm->pAttr = NNS_G2D_UNPACK_OFFSET_PTR(pFrm->pAttr, pAnmExAttrBank);
                }
            }
        }
    }

}

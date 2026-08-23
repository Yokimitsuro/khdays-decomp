/*
 * Ov002_QueuePageCue - remember a cue and everything that goes with it.
 *
 * A fresh node carries the cue's own handle, the handle of the second cue when
 * there is one, the box on screen that answers for it and the callback the box
 * runs when touched. The cue's number also places it in one of two groups, or
 * in neither.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*Ov002CueProc)(int nHandle);

typedef struct {
    int hCue;
    int hAlt;
    short nGroup;
    u8 nX;
    u8 nY;
    u8 nWidth;
    u8 nHeight;
    char pad00e[2];
    Ov002CueProc pfn;
    char pad014[0xc];
} Ov002CueNode;

typedef struct {
    char pad000[8];
    char aList[0x10];
} Ov002CueCtx;

extern Ov002CueCtx *data_ov002_0207f99c;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern void NNS_FndAppendListObject(void *pList, void *pObject);

extern int func_ov002_02053558(int nCue);

void func_ov002_020657f4(u32 nCue, int nX, int nY, int nWidth, u8 nHeight,
                         u16 nAlt, Ov002CueProc pfn)
{
    Ov002CueCtx *ctx;
    Ov002CueNode *pNode;
    int hAlt;

    ctx = data_ov002_0207f99c;
    pNode = (Ov002CueNode *)NNSi_FndAllocFromDefaultExpHeap(0x20);
    pNode->hCue = func_ov002_02053558(nCue);

    if (nAlt == 0xffff) {
        hAlt = 0;
    } else {
        hAlt = func_ov002_02053558(nAlt);
    }
    pNode->hAlt = hAlt;
    pNode->nX = (u8)nX;
    pNode->nY = (u8)nY;
    pNode->nWidth = (u8)nWidth;
    pNode->nHeight = nHeight;
    pNode->pfn = pfn;

    if (nCue >= 0x474 && nCue <= 0x489) {
        pNode->nGroup = 0;
    } else if (nCue >= 0x48a && nCue <= 0x491) {
        pNode->nGroup = 1;
    } else {
        pNode->nGroup = -1;
    }

    NNS_FndAppendListObject(ctx->aList, pNode);
}

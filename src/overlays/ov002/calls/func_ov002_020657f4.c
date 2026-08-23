/*
 * Ov002_QueuePageCue - remember a cue and everything that goes with it.
 *
 * A fresh node carries the cue's own handle, the handle of the second cue when
 * there is one, the four bytes describing where it belongs and the value it
 * stands for. The cue's number also places it in one of two groups, or in
 * neither.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    int hCue;
    int hAlt;
    short nGroup;
    u8 nRow;
    u8 nColumn;
    u8 nKind;
    u8 nSlot;
    char pad00e[2];
    int nValue;
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

void func_ov002_020657f4(u32 nCue, int nRow, int nColumn, int nKind, u8 nSlot,
                         u16 nAlt, int nValue)
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
    pNode->nRow = (u8)nRow;
    pNode->nColumn = (u8)nColumn;
    pNode->nKind = (u8)nKind;
    pNode->nSlot = nSlot;
    pNode->nValue = nValue;

    if (nCue >= 0x474 && nCue <= 0x489) {
        pNode->nGroup = 0;
    } else if (nCue >= 0x48a && nCue <= 0x491) {
        pNode->nGroup = 1;
    } else {
        pNode->nGroup = -1;
    }

    NNS_FndAppendListObject(ctx->aList, pNode);
}

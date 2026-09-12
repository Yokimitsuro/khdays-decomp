/*
 * Fold one frame's worth of accumulated play data into the run record for
 * player nIdx and hand the individual events on to the scorers.
 *
 * The record lives in the 0x104-byte-per-player table at data_0204c678.  The
 * six running counters at +0x08 each take this frame's delta from the state
 * block, then every one of them is clamped: the four halfword counters at
 * 999, the long counter at 0x64000, and the fifth halfword at 255.  The
 * fourteen per-slot levels at +0x18 take their own rate (a 20.12 fixed-point
 * value) and are capped at 100.
 *
 * Three event lists on the state block are then walked.  The first pairs each
 * event with the two bytes the record keeps for it and passes the pair on to
 * func_02035794; the second scores each entry, halving the third word for one
 * particular kind and flooring the second word at 1 for the rest; the third
 * reports each entry's first two words as a position.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    void *pHead;
    void *pTail;
    u16 nObjects;
    u16 nOffset;
} NNSFndList;

typedef struct {
    u16 nField00;               /* 0x00 */
    u16 nField02;               /* 0x02 */
    u16 nField04;               /* 0x04 */
    u16 nField06;               /* 0x06 */
    u16 nField08;               /* 0x08 */
    u16 pad0a;
    int nField0c;               /* 0x0c */
} Counters;

typedef struct {
    u8 pad00[3];
    u8 nKind;                   /* 0x003 */
    u8 nField04;                /* 0x004 */
    u8 pad05;
    u16 nField06;               /* 0x006 */
    Counters counters;          /* 0x008 */
    u8 aLevels[14];             /* 0x018 */
    u8 pad26[0x74];
    u8 aPairs[0x6a];            /* 0x09a */
} Record;

typedef struct {
    u8 pad00[8];
    NNSFndList listA;           /* 0x08 */
    NNSFndList listB;           /* 0x14 */
    NNSFndList listC;           /* 0x20 */
    u8 pad2c[0x48];
    int nField74;               /* 0x74 */
    int nField78;               /* 0x78 */
    int nField7c;               /* 0x7c */
    int nField80;               /* 0x80 */
    int nField84;               /* 0x84 */
    int nField88;               /* 0x88 */
    int nField8c;               /* 0x8c */
    int nField90;               /* 0x90 */
    int aRates[14];             /* 0x94 */
} State;

typedef struct {
    int nKind;                  /* 0x00 */
    int nField04;               /* 0x04 */
    int nField08;               /* 0x08 */
    int pad0c;
    int nField10;               /* 0x10 */
    int nField14;               /* 0x14 */
} Event;

extern u8 data_0204c678[];
extern u8 data_0204c4f0[];
extern u8 data_0204c67c[];

extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void func_02035278(int nIdx);
extern void func_02035328(int nIdx, int nKind, int nArg);
extern void func_02035794(int nIdx, int nSlot, unsigned int nArg, u8 *pPair);
extern void func_020358c0(int nIdx, int nKind, int nValue);
extern void func_02035830(int nIdx, u16 *pPos);

void func_02035a58(int nIdx, State *pState)
{
    u8 *pTable;
    Counters *pCnt;
    Record *pRec;
    Event *pEvent;
    int nOffset;
    int i;
    int nValue;
    int nKind;
    u16 aPos[2];
    u8 aPair[2] = {0, 0};

    nOffset = nIdx * 0x104;
    pTable = data_0204c678;
    pRec = (Record *)(pTable + nOffset);
    pCnt = &pRec->counters;

    func_02035278(nIdx);

    data_0204c4f0[0] = 0;
    data_0204c4f0[3] = 0;
    data_0204c4f0[2] = 0;

    func_02035328(nIdx, ((Record *)((int)data_0204c678 + nOffset))->nKind, pState->nField78);

    data_0204c67c[nOffset] = (u8)pState->nField74;

    pRec->counters.nField00 = pRec->counters.nField00 + pState->nField80;
    pCnt->nField02 = pCnt->nField02 + pState->nField84;
    pCnt->nField04 = pCnt->nField04 + pState->nField88;
    pCnt->nField06 = pCnt->nField06 + pState->nField7c;
    pCnt->nField08 = pCnt->nField08 + pState->nField90;
    pCnt->nField0c = pCnt->nField0c + pState->nField8c;

    if (pRec->counters.nField00 > 999) {
        pCnt->nField00 = 999;
    }
    if (pCnt->nField02 > 999) {
        pCnt->nField02 = 999;
    }
    if (pCnt->nField04 > 999) {
        pCnt->nField04 = 999;
    }
    if (pCnt->nField06 > 999) {
        pCnt->nField06 = 999;
    }
    if (pCnt->nField0c > 0x64000) {
        pCnt->nField0c = 0x64000;
    }
    /* The cap on nField08 writes its result to nField0c: that is what the
       original does, not a transcription slip. */
    if (pCnt->nField08 > 0xff) {
        pCnt->nField0c = 0xff;
    }

    i = 0;
    do {
        pRec->aLevels[i] = pRec->aLevels[i] + (pState->aRates[i] >> 12);
        if (pRec->aLevels[i] > 100) {
            pRec->aLevels[i] = 100;
        }
        i++;
    } while (i < 14);

    pRec->nField06 = pCnt->nField06;

    pEvent = (Event *)NNS_FndGetNextListObject(&pState->listA, 0);
    while (pEvent != 0) {
        aPair[0] = (u8)(pEvent->nField14 + pRec->aPairs[pEvent->nKind * 2]);
        aPair[1] = (u8)(pEvent->nField14 + pRec->aPairs[pEvent->nKind * 2 + 1]);
        func_02035794(0, pEvent->nKind - 1, (u8)pEvent->nField10, aPair);
        pEvent = (Event *)NNS_FndGetNextListObject(&pState->listA, pEvent);
    }

    pEvent = (Event *)NNS_FndGetNextListObject(&pState->listB, 0);
    while (pEvent != 0) {
        nKind = pEvent->nKind;
        if (nKind == 0x5a) {
            func_020358c0(0, nKind, pEvent->nField08 / 2);
        } else {
            if (pEvent->nField04 < 0) {
                nValue = 1;
            } else {
                nValue = pEvent->nField04;
            }
            func_020358c0(0, *(int *)pEvent, nValue);
        }
        pEvent = (Event *)NNS_FndGetNextListObject(&pState->listB, pEvent);
    }

    pEvent = (Event *)NNS_FndGetNextListObject(&pState->listC, 0);
    while (pEvent != 0) {
        aPos[0] = (u16)pEvent->nKind;
        aPos[1] = (u16)pEvent->nField04;
        func_02035830(nIdx, aPos);
        pEvent = (Event *)NNS_FndGetNextListObject(&pState->listC, pEvent);
    }
}

/*
 * Ov002_CreatePanelSession - allocate the panel session and fill it in.
 *
 * The block comes off the root heap, is cleared, and becomes the overlay's one
 * live session. The caller's request names the entries: a bitmask of the
 * fifteen cells that exist, the keys of the entries themselves, and two words
 * copied across untouched. Cells the mask does not claim are stamped 0xff so
 * the drawing code skips them, and the cursor starts on the row that holds the
 * last claimed cell.
 *
 * The twenty-four entry slots are then walked once: every slot the request
 * reaches takes its key, looks the record up in the message database, records
 * whether that record's own field is empty, and joins the list. Slots past the
 * request keep a zero key but still join, so the list length is fixed.
 *
 * Returns the screen step the caller runs from here on.
 *
 * THUMB. The declaration order below is load-bearing: mwcc hands the counter
 * and the walker of each loop their registers by it, and this is the order that
 * gives the ROM's pairing. Each loop also assigns its counter before its
 * walker, which is what fixes the order the two initialisations come out in.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 *pKeys;                         /* +0x00 */
    u16 wCount;                         /* +0x04 */
    u16 pad0006;
    int nCellMask;                      /* +0x08 */
    int nField000c;                     /* +0x0c */
    int aWords[2];                      /* +0x10 */
} Ov002PanelSetup;

typedef struct {
    u8 pad0000[8];
    int nField0008;                     /* +0x008 */
    int nPrimaryValue;                  /* +0x00c */
    int nState;                         /* +0x010 */
    u8 pad0014[0x14];
    int aWords[2];                      /* +0x028 */
    u8 bColumns;                        /* +0x030 */
    u8 bCursorRow;                      /* +0x031 */
    u8 aCells[0x1e];                    /* +0x032 */
} Ov002PanelSession;

typedef int (*Ov002PanelStepFn)(void);

extern Ov002PanelSession *data_ov002_0207f620;
extern int data_ov002_0207eb10[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void NNS_FndInitList(void *pList, int nLinkOffset);
extern void NNS_FndAppendListObject(void *pList, void *pObject);
extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern long long func_02020400(int nNum, int nDen);
extern void func_02034150(int nSlot, int nFont);
extern void func_020342e8(int *pOut, int nSlot, unsigned int nKey, int nFont);
extern void func_02034258(int nSlot);
extern void func_020343cc(int *pRecord);

extern int func_ov002_020575d0(void);
extern void func_ov002_0205280c(void *pSet, const void *pTable);
extern void func_ov002_0205b5e4(void);
extern void func_ov002_0205a8c0(void);
extern void func_ov002_0205cc44(void);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_0205376c(int nEntry, int nValue);
extern void func_ov002_020536dc(int nEntry, int nValue);
extern void func_ov002_0205dc4c(int nValue);
extern void func_ov002_0205e178(int nValue);
extern int func_ov002_0205d18c(void);

Ov002PanelStepFn func_ov002_0205cf54(Ov002PanelSetup *pReq)
{
    int nOffset;
    int i;
    Ov002PanelSetup *pSrc;
    int nRecord;
    Ov002PanelSession *pCell;
    Ov002PanelSession *pWalk;
    int k;
    Ov002PanelSession *s;
    void *pNode;
    int nCount;

    nCount = 0;
    nRecord = 0;
    s = (Ov002PanelSession *)NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f620 = s;
    MI_CpuFill8(s, 0, 0x638);
    s->nPrimaryValue = (func_ov002_020575d0() == 0);
    s->nState = 0;

    pSrc = pReq;
    pWalk = s;
    i = 0;
    do {
        i++;
        pWalk->aWords[0] = pSrc->aWords[0];
        pSrc = (Ov002PanelSetup *)((char *)pSrc + 4);
        pWalk = (Ov002PanelSession *)((char *)pWalk + 4);
    } while (i < 2);

    k = 0;
    pCell = s;
    do {
        if (pReq->nCellMask & (1 << k)) {
            pCell->aCells[0] = (u8)k;
            pCell = (Ov002PanelSession *)((char *)pCell + 2);
            nCount++;
        }
        k++;
    } while (k < 0xf);

    *(int *)((char *)s + 0x4a8) = pReq->nCellMask;
    s->nField0008 = pReq->nField000c;
    s->bColumns = (u8)nCount;
    s->bCursorRow = (u8)func_02020400(nCount + 5, 6);

    if (nCount < 0xf) {
        pWalk = (Ov002PanelSession *)((char *)s + nCount * 2);
        do {
            pWalk->aCells[0] = 0xff;
            nCount++;
            pWalk = (Ov002PanelSession *)((char *)pWalk + 2);
        } while (nCount < 0xf);
    }

    NNS_FndInitList((char *)s + 0x480, 0xc);
    NNS_FndInitList((char *)s + 0x48c, 0xc);
    MI_CpuFill8((char *)s + 0x50, 0, 0x240);
    *(u16 *)((char *)s + 0x4ae) = pReq->wCount;
    func_02034150(0x15, 0xe);

    i = 0;
    nOffset = 0;
    pWalk = s;
    pNode = (char *)s + 0x50;
    do {
        if (i < pReq->wCount) {
            *(u16 *)((char *)pWalk + 0x4b8) = *(u16 *)((char *)pReq->pKeys + nOffset);
            func_020342e8(&nRecord, 0x15, *(u16 *)((char *)pWalk + 0x4b8), 0xe);
            *(int *)((char *)pWalk + 0x4bc) = (*(int *)(nRecord + 0x18) == 0);
            *(int *)((char *)s + 0x4b0) = *(int *)((char *)s + 0x4b0) | (1 << i);
            func_020343cc(&nRecord);
        } else {
            *(u16 *)((char *)pWalk + 0x4b8) = 0;
        }
        *(int *)((char *)s + 0x4b4) = *(int *)((char *)s + 0x4b0);
        NNS_FndAppendListObject((char *)s + 0x48c, pNode);
        nOffset += 2;
        pWalk = (Ov002PanelSession *)((char *)pWalk + 0xc);
        pNode = (char *)pNode + 0x18;
        i++;
    } while (i < 0x18);

    func_02034258(0x15);
    NNS_FndInitList((char *)s + 0x498, 0xc);

    i = 0;
    pWalk = s;
    do {
        *(int *)((char *)pWalk + 0x298) = 1;
        pWalk = (Ov002PanelSession *)((char *)pWalk + 0x18);
        i++;
    } while (i < 0x12);

    func_ov002_0205280c((char *)s + 0x5e8, data_ov002_0207eb10);
    func_ov002_0205b5e4();
    func_ov002_0205a8c0();
    func_ov002_0205cc44();

    i = func_ov002_020536bc(2);
    func_ov002_0205376c(i, 0);
    func_ov002_020536dc(i, 1);
    func_ov002_0205376c(func_ov002_020536bc(2), 0);

    if (func_ov002_020575d0() != 0) {
        func_ov002_0205dc4c(0);
        func_ov002_0205e178(0);
    }
    return func_ov002_0205d18c;
}

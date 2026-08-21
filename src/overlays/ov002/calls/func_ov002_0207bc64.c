typedef unsigned short u16;
typedef unsigned char u8;

/* The descriptor the caller fills in for one element class. */
typedef struct {
    const char *pName;              /* +0x00 */
    short nParam;                   /* +0x04 */
    signed char bLineCount;         /* +0x06 */
    const char *aLine[8];           /* +0x08 */
} Ov002LineClassDesc;

extern u8 data_0204c240;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);
extern void func_0202fcb8(const char *pNarrow, u16 *pWide);
extern int func_020200c8(const u16 *pWide);
extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern void func_02020104(u16 *pDst, const u16 *pSrc, int nLen);

extern void func_ov002_0207b020(void);
extern void func_ov002_0207b0c8(void);
extern void func_ov002_0207b21c(void);
extern void func_ov002_0207b340(void);
extern void func_ov002_0207b1c0(void);
extern void func_ov002_0207b230(void);
extern void func_ov002_0207b368(void);
extern void func_ov002_0207b40c(void);
extern void func_ov002_0207b414(void);
extern void func_ov002_0207b41c(void);
extern void func_ov002_0207b3d4(void);
extern void func_ov002_0207b424(void);

/* Create the table that owns one class of line element.
 *
 * Allocates the 0x8c byte table together with room for 0x1c4 byte elements,
 * blanks the name and copies the descriptor's one over it when there is one,
 * then widens each of the class's lines into its own allocation. Both the line
 * work and the start handler are skipped when the global gate is closed.
 *
 * The counter shares an object with the widening buffer, and the buffer's
 * address escapes into the widening call, so the counter lives in memory the
 * way the original's does. The two volatile reads pin it there and fix the
 * order the exit test reads its two operands in; both are codegen tools, not
 * hardware accesses.
 */
void *func_ov002_0207bc64(void *pCtx, const Ov002LineClassDesc *pDesc)
{
    struct {
        volatile int nIndex;
        u16 aWide[256];
    } f;
    char *pTable;
    int nLen;
    void (*pfnStart)(void);
    int nCount;
    char *pSlot;
    const Ov002LineClassDesc *pWalk;

    pTable = (char *)func_ov002_020769b0(0x8c, 0x1c4, pCtx);

    if (pDesc->pName == 0) {
        *(char *)(pTable + 0x58) = 0;
    } else {
        strncpy(pTable + 0x58, pDesc->pName, 0x10);
    }

    *(short *)(pTable + 0x68) = pDesc->nParam;
    *(signed char *)(pTable + 0x6a) = pDesc->bLineCount;

    if ((data_0204c240 & 4) == 0) {
        f.nIndex = 0;
        if (*(signed char *)(pTable + 0x6a) > 0) {
            pSlot = pTable;
            pWalk = pDesc;
            do {
                func_0202fcb8(pWalk->aLine[0], f.aWide);
                nLen = func_020200c8(f.aWide);
                *(u16 **)(pSlot + 0x6c) =
                    (u16 *)NNSi_FndAllocFromDefaultExpHeap((nLen + 1) * 2);
                func_02020104(*(u16 **)(pSlot + 0x6c), f.aWide, nLen);
                (*(u16 **)(pSlot + 0x6c))[nLen] = 0;
                f.nIndex++;
                pWalk = (const Ov002LineClassDesc *)((const char *)pWalk + 4);
                pSlot += 4;
                nCount = *(volatile signed char *)(pTable + 0x6a);
            } while (f.nIndex < nCount);
        }
    }

    *(u8 *)(pTable + 0x88) = 0;

    *(int *)(pTable + 0x00) = (int)func_ov002_0207b020;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov002_0207b0c8;
    *(int *)(pTable + 0x0c) = (int)func_ov002_0207b21c;
    *(int *)(pTable + 0x10) = (int)func_ov002_0207b340;
    *(int *)(pTable + 0x14) = (int)func_ov002_0207b1c0;
    *(int *)(pTable + 0x18) = (int)func_ov002_0207b230;
    *(int *)(pTable + 0x1c) = 0;

    pfnStart = 0;
    if ((data_0204c240 & 4) == 0) {
        pfnStart = func_ov002_0207b368;
    }
    *(int *)(pTable + 0x20) = (int)pfnStart;
    *(int *)(pTable + 0x24) = (int)func_ov002_0207b40c;
    *(int *)(pTable + 0x28) = (int)func_ov002_0207b414;
    *(int *)(pTable + 0x2c) = (int)func_ov002_0207b41c;

    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x48) = (int)func_ov002_0207b3d4;
    *(int *)(pTable + 0x3c) = (int)func_ov002_0207b424;
    *(u16 *)(pTable + 0x4c) = 9;

    return pTable;
}

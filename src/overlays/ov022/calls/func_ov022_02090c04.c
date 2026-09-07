/* ov022: build the slot manager.
 *
 * Takes a template table of fixed-size entries, gives the manager its own copy
 * on the heap, reserves room for the slots that will use them, and installs the
 * four handlers the rest of the subsystem calls through.
 *
 * Both counts come from the caller: one for the template entries, one for the
 * slots. The slot count is kept twice, as the total and as the number still
 * free, which start out the same.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ENTRY_SIZE 0x50
#define SLOT_SIZE 0x1c8

typedef void (*PfnHandler)(void);

struct Manager {
    u8 pad00[8];
    void *pOwner;                /* 0x08 */
    void *pSlots;                /* 0x0c */
    void *pEntries;              /* 0x10 */
    int nEntries;                /* 0x14 */
    u8 nSlots;                   /* 0x18 */
    u8 nFree;                    /* 0x19 */
    u8 pad1a[2];
    PfnHandler pfnA;             /* 0x1c */
    PfnHandler pfnB;             /* 0x20 */
    PfnHandler pfnC;             /* 0x24 */
    PfnHandler pfnD;             /* 0x28 */
};

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void func_ov022_02090cbc(void);
extern void func_ov022_02090e2c(void);
extern void func_ov022_02090ec4(void);
extern void func_ov022_02090f14(void);

void func_ov022_02090c04(struct Manager *pMgr, void *pOwner, const u8 *pSrc,
                         int nEntries, int nSlots)
{
    int i;
    int nOffset;

    pMgr->pOwner = pOwner;
    pMgr->nEntries = nEntries;
    pMgr->pEntries = NNSi_FndAllocFromDefaultExpHeap(nEntries * ENTRY_SIZE);
    i = 0;
    if (nEntries > 0) {
        nOffset = 0;
        do {
            MI_CpuCopy8(pSrc, (u8 *)pMgr->pEntries + nOffset, ENTRY_SIZE);
            i++;
            nOffset += ENTRY_SIZE;
            pSrc += ENTRY_SIZE;
        } while (i < nEntries);
    }
    pMgr->pSlots = NNSi_FndAllocFromDefaultExpHeap(nSlots * SLOT_SIZE);
    pMgr->nSlots = (u8)nSlots;
    pMgr->nFree = (u8)nSlots;
    pMgr->pfnA = func_ov022_02090cbc;
    pMgr->pfnB = func_ov022_02090e2c;
    pMgr->pfnC = func_ov022_02090ec4;
    pMgr->pfnD = func_ov022_02090f14;
}

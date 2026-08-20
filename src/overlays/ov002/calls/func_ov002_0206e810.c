/* Allocate the event context, blank every slot table and hand back the tick
 * routine the caller should install.
 *
 * Ghidra models this object as Ov002EventContext. Its tables are two identical
 * 0x120-byte banks at +0xc; the claim routine proves that shape by holding one
 * bank in a register. This function proved the header in front of them, which
 * was padding before: a version halfword at +0, four handles filled with 0xffff
 * at +2, a count at +0xa and the current index at +0xb. data_ov002_0207fa04 was
 * already typed Ov002EventContext*.
 *
 * All six tables are cleared by one loop walking them in step, so the codegen
 * view below stays flat: the nested shape does not reproduce the shared index.
 */

typedef struct {
    short nVersion;                     /* +0x000 */
    short aHandles[4];                  /* +0x002, filled with 0xffff */
    unsigned char nCount;               /* +0x00a */
    signed char nCurrent;               /* +0x00b */
    int aHandlers[0x20];                /* +0x00c  bank 0 */
    int aSlots[0x20];                   /* +0x08c */
    unsigned char aFlags[0x20];          /* +0x10c */
    int aHandlersAlt[0x20];             /* +0x12c  bank 1 */
    int aSlotsAlt[0x20];                   /* +0x1ac */
    unsigned char aFlagsAlt[0x20];         /* +0x22c */
} Ov002EventContext;                        /* 0x24c */

typedef int (*Ov002EventTickProc)(void);

extern Ov002EventContext *data_ov002_0207fa04;

extern Ov002EventContext *NNSi_FndGetCurrentRootHeap(void);
extern void MIi_CpuClear16(unsigned short nValue, void *pDest, int nSize);
extern int func_ov002_0206e888(void);

Ov002EventTickProc func_ov002_0206e810(void)
{
    Ov002EventContext *pContext;
    int i;

    pContext = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207fa04 = pContext;

    pContext->nVersion = 1;
    MIi_CpuClear16(0xffff, pContext->aHandles, 8);

    pContext->nCount = 0;
    pContext->nCurrent = -1;

    for (i = 0; i < 0x20; i++) {
        pContext->aHandlers[i] = 0;
        pContext->aSlots[i] = 0;
        pContext->aFlags[i] = 0;
        pContext->aHandlersAlt[i] = 0;
        pContext->aSlotsAlt[i] = 0;
        pContext->aFlagsAlt[i] = 0;
    }

    return func_ov002_0206e888;
}

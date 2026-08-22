/*
 * Ov002_AddPanelValue - add the panel's value-only entry to the pool.
 *
 * Kind 4 is the one the pool builder only latches a value for, so there is no
 * sampler and no second word: the descriptor is wiped, given a six-wide field
 * on target 0x11 in palette 9, and handed over.
 *
 * The running key at +0x1ad is read twice - as the entry's key and as its
 * colour - and only then bumped, the same way the counters do it.
 *
 * ARM.
 */

typedef unsigned char u8;

typedef struct {
    u8 bKey;                            /* +0x00 */
    u8 bWidth;                          /* +0x01 */
    u8 pad0002[2];
    int nKind;                          /* +0x04 */
    int nTarget;                        /* +0x08 */
    u8 bPalette;                        /* +0x0c */
    u8 bColour;                         /* +0x0d */
    u8 pad000e[2];
    int nValue;                         /* +0x10 */
    int nValueHi;                       /* +0x14 */
    int nOwner;                         /* +0x18 */
    u8 pad001c[4];
    long long (*pfnSample)(void);       /* +0x20 */
    int nExtra;                         /* +0x24 */
} Ov002EntryDesc;

typedef struct {
    u8 bKey;                            /* +0x00 */
} Ov002PoolEntry;

typedef struct {
    char pad0000[0x1ad];
    u8 nNextEntryKey;                   /* +0x1ad */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern Ov002PoolEntry *func_ov002_02059f3c(Ov002EntryDesc *pDesc);

u8 func_ov002_02056c44(int nValue)
{
    Ov002PanelContext *ctx;
    Ov002EntryDesc sDesc;

    ctx = data_ov002_0207f614;
    MI_CpuFill8(&sDesc, 0, 0x28);
    sDesc.bKey = ctx->nNextEntryKey;
    sDesc.nKind = 4;
    sDesc.bWidth = 6;
    sDesc.nTarget = 0x11;
    sDesc.bPalette = 9;
    sDesc.bColour = ctx->nNextEntryKey;
    sDesc.nValue = nValue;
    sDesc.nExtra = 0xb;
    ctx->nNextEntryKey = ctx->nNextEntryKey + 1;
    return func_ov002_02059f3c(&sDesc)->bKey;
}

/*
 * Ov002_AddPanelCounter - describe one panel counter and hand it to the pool.
 *
 * Everything about the entry is fixed except the value pair, the sampler and
 * which of the three kinds the caller asks for; a selector outside 0..2 leaves
 * the kind untouched, which is the ROM's own behaviour and means the
 * descriptor goes out with whatever the stack held.
 *
 * The running key at +0x1ad is used twice - as the entry's key and as its
 * colour - and only then bumped, so each counter gets its own.
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

extern Ov002PoolEntry *func_ov002_02059f3c(Ov002EntryDesc *pDesc);

u8 func_ov002_02056ba4(int nValue, int nValueHi, int nSelect,
                       long long (*pfnSample)(void))
{
    Ov002PanelContext *ctx;
    Ov002EntryDesc sDesc;

    ctx = data_ov002_0207f614;
    sDesc.bKey = ctx->nNextEntryKey;
    switch (nSelect) {
    case 0:
        sDesc.nKind = 3;
        break;
    case 1:
        sDesc.nKind = 1;
        break;
    case 2:
        sDesc.nKind = 2;
        break;
    }
    sDesc.bWidth = 8;
    sDesc.bPalette = 0xb;
    sDesc.nTarget = 9;
    sDesc.bColour = ctx->nNextEntryKey;
    sDesc.nValue = nValue;
    sDesc.pfnSample = pfnSample;
    sDesc.nExtra = 0xb;
    sDesc.nValueHi = nValueHi;
    ctx->nNextEntryKey = ctx->nNextEntryKey + 1;
    return func_ov002_02059f3c(&sDesc)->bKey;
}

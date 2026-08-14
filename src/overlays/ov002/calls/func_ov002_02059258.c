/* Restart the scene request queue for a new pair of ids. Drains whatever was
 * already queued exactly as the flush does, then raises the dirty bit, latches
 * the two ids at +0xec/+0xee, clears the two progress words and runs the two
 * setup passes. Bit 1 of +0x28 marks the scene as restarted.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[0x28];
    u8 bStateFlags;             /* +0x28 */
    u8 pad0029[0x13];
    int nQueued;                /* +0x3c */
    u8 pad0040[8];
    unsigned bDirty : 1;        /* +0x48 bit 0 */
    u8 pad004c[0xa0];
    u16 wIdLow;                 /* +0xec */
    u16 wIdHigh;                /* +0xee */
    u8 pad00f0[0x54];
    int nProgress144;           /* +0x144 */
    u8 pad0148[0x18];
    int nProgress160;           /* +0x160 */
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f618;

extern int func_ov002_02053558(int nId);
extern void func_ov002_02053534(int nEntry, int nFlag);
extern void func_ov002_02058440(void);
extern void func_ov002_02058568(void);

void func_ov002_02059258(u16 wIdHigh, u16 wIdLow) {
    Ov002SceneContext *ctx = data_ov002_0207f618;
    int i;
    int nPairs;

    nPairs = (ctx->nQueued + 1) / 2;
    for (i = 0; i < nPairs; i++) {
        func_ov002_02053534(func_ov002_02053558((u16)(i + 50000)), 1);
    }

    ctx->nQueued = 0;
    ctx->bDirty = 1;
    ctx->wIdLow = wIdLow;
    ctx->wIdHigh = wIdHigh;
    ctx->nProgress144 = 0;
    ctx->nProgress160 = 0;

    func_ov002_02058440();
    func_ov002_02058568();

    ctx->bStateFlags = ctx->bStateFlags | 2;
}

/* Flush the queued scene requests. Does nothing unless the dirty bit at +0x48 is
 * set; clearing it, replaying request 0x32 and then acknowledging one request per
 * queued pair, counting up from 50000. The queue length is reset to zero.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x3c];
    int nQueued;                /* +0x3c */
    u8 pad0040[8];
    unsigned bDirty : 1;        /* +0x48 bit 0 */
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f618;

extern int func_ov002_02053558(int nId);
extern void func_ov002_020535f0(int nEntry);
extern void func_ov002_02053534(int nEntry, int nFlag);

void func_ov002_0205932c(void) {
    Ov002SceneContext *ctx = data_ov002_0207f618;
    int nPairs;
    int i;

    if (ctx->bDirty) {
        ctx->bDirty = 0;
        func_ov002_020535f0(func_ov002_02053558(0x32));

        nPairs = (ctx->nQueued + 1) / 2;
        for (i = 0; i < nPairs; i++) {
            func_ov002_02053534(
                func_ov002_02053558((unsigned short)(i + 50000)), 1);
        }

        ctx->nQueued = 0;
    }
}

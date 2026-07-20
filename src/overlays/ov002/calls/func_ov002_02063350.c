/* Release surface 1 of the scene context, but only if it is in use, only if the
 * selected word is non-zero, and only if the context's +0x0c gate is clear.
 *
 * The offsets confirm Ov002SceneContext independently: +0x90 is aSurfaceUsed[1]
 * and +0xfc is aSurfaces[1] on the 0x3c TileSurface stride, both of which were
 * derived from the scene's constructor/teardown pair rather than from here.
 *
 * The struct is written FLAT rather than with the real aSurfaces[3][15] array:
 * only element 1 is touched, and the 2-D form makes mwcc emit index arithmetic
 * worth 20 bytes. That divergence from the Ghidra type is deliberate -- the
 * struct in a matched .c is a codegen tool, Ghidra holds the data model.
 */
typedef struct {
    char pad0000[0xc];
    int nField000c;          /* +0x00c */
    char pad0010[0x80];
    int nSurface1Used;       /* +0x090 */
    char pad0094[0x68];
    int aSurface1[1];        /* +0x0fc */
    char pad0100[0x74];
    int aWords0174[2];       /* +0x174 */
} Ov002SceneContext;

extern void func_02030094(int *surface, int value, int c);
extern void func_020300f8(int *surface);
extern char *data_ov002_0207f62c;

void func_ov002_02063350(int flag) {
    Ov002SceneContext *ctx = (Ov002SceneContext *)(&data_ov002_0207f62c)[1];
    int value;
    int i;

    if (ctx->nSurface1Used == 0) return;
    i = (flag == 0) ? 1 : 0;
    value = ctx->aWords0174[i];
    if (value == 0) return;
    func_02030094(ctx->aSurface1, value, 0);
    if (ctx->nField000c != 0) return;
    func_020300f8(ctx->aSurface1);
}

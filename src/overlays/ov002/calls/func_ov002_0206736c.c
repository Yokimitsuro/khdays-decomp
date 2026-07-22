/* Arm the scene for id `id` and mark it running. The arming call goes through
 * the installed hook at +0x1a8 when there is one, and to the default entry point
 * otherwise; both take the same pair of arguments, which is why the constant is
 * loaded once, above the branch. */
extern void func_ov002_020637d4(int mode, int mask);

typedef struct {
    char pad0000[2];
    short wId;                          /* +2 */
    char pad0004[0x24];
    int nState;                         /* +0x28 */
    char pad002c[0x17c];
    void (*pHook)(int mode, int mask);  /* +0x1a8 */
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f9fc;

void func_ov002_0206736c(short id) {
    Ov002SceneContext *ctx = data_ov002_0207f9fc;

    ctx->wId = id;

    if (ctx->pHook == 0) {
        func_ov002_020637d4(0, 0xffff0000);
    } else {
        ctx->pHook(0, 0xffff0000);
    }

    ctx->nState = 1;
}

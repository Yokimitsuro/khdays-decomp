/* Flush the pending draw, if there is one: hand the surface to the encoder, run
 * the flush tail, then clear the pending slot. */
extern void *func_ov002_020636ac(void);
extern void func_ov002_02063fb4(void *surface);
extern void func_ov002_02064264(void);

typedef struct {
    void *pSurface;     /* +0 */
    char pad0004[8];
    void *pPending;     /* +0xc */
} Ov002DrawContext;

void func_ov002_02064328(void) {
    Ov002DrawContext *ctx = (Ov002DrawContext *)func_ov002_020636ac();

    if (ctx->pPending == 0) {
        return;
    }

    func_ov002_02063fb4(ctx->pSurface);
    func_ov002_02064264();
    ctx->pPending = 0;
}

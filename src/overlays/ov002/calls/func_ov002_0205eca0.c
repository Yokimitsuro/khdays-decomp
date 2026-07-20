/* Tear the HUD context down to state 5 and hand the scene to
 * func_ov002_0205f14c.  Returns immediately if the context was never built.
 *
 * The two tiled surfaces are released with the same pair in the same order
 * (func_02030158 then func_020300f8), the second only when the count at +0x7e0
 * is positive -- so the second surface is conditional on there being rows to
 * draw, not on a separate allocated flag.
 *
 * Note the ROM builds ctx+0x734 twice by two different routes: once as
 * 0x7e0 - 0xac (reusing the constant it just loaded for the count) and once
 * from its own pool entry.  That is mwcc rematerialising, not two addresses. */
typedef struct {
    int nState;             /* +0x000 */
    char pad04[8];
    int aSub0c[1];          /* +0x00c */
    char pad10[0x694];
    int nHandle6a4;         /* +0x6a4 */
    char pad6a8[0x50];
    int aSurfaceA[1];       /* +0x6f8 */
    char pad6fc[0x38];
    int aSurfaceB[1];       /* +0x734 */
    char pad738[0xa8];
    int nCount7e0;          /* +0x7e0 */
} Ov002HudCtx;

extern void func_02030158(int *p);
extern void func_020300f8(int *p);
extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern void func_ov002_0205272c(int *p);
extern void func_ov002_0205eba4(int a);
extern void func_ov002_0205ec50(int a);
extern void func_02023a44(int handle, void (*callback)(void));
extern void func_ov002_0205f14c(void);

extern Ov002HudCtx *data_ov002_0207f624;

void func_ov002_0205eca0(void) {
    Ov002HudCtx *ctx = data_ov002_0207f624;

    if (ctx == 0) return;

    func_02030158(ctx->aSurfaceA);
    func_020300f8(ctx->aSurfaceA);
    func_ov002_02053b28(0xa, 0, 0, 0x20, 0x18);
    if (ctx->nCount7e0 > 0) {
        func_02030158(ctx->aSurfaceB);
        func_020300f8(ctx->aSurfaceB);
    }
    func_ov002_0205272c(ctx->aSub0c);
    func_ov002_0205eba4(-1);
    func_ov002_0205ec50(0);
    ctx->nState = 5;
    func_02023a44(ctx->nHandle6a4, func_ov002_0205f14c);
}

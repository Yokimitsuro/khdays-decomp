/* Sweep ctx->items[] (stride 0x30, count at +0x34); for each element whose
 * +0x24 bit 1 is set, notify func_ov002_020546e4(ctx, element). base/count are
 * reloaded each iteration because the callee may mutate *ctx. */
extern void func_ov002_020546e4(int ctx, int element);
struct Elem { unsigned char _pad[0x24]; unsigned char b0:1, b1:1; unsigned char _pad2[0xb]; };
struct Ctx { unsigned char _0[0x10]; struct Elem *items; unsigned char _1[0x20]; int count; };
void func_ov002_02054714(int ctx_) {
    struct Ctx *ctx = (struct Ctx *)ctx_;
    int i;
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].b1 == 1) {
            func_ov002_020546e4(ctx_, (int)&ctx->items[i]);
        }
    }
}

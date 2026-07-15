/* Sweep ctx->items[] (stride 0x10, count at +0x38); for each element whose +0xc
 * word is nonzero, notify func_ov006_0204d3dc(ctx, element). base/count reloaded
 * each iteration because the callee may mutate *ctx. */
extern void func_ov006_0204d3dc(int ctx, int element);
struct Elem2 { unsigned char _pad[0xc]; int field_c; };
struct Ctx2 { unsigned char _0[0x14]; struct Elem2 *items; unsigned char _1[0x20]; int count; };
void func_ov006_0204d408(int ctx_) {
    struct Ctx2 *ctx = (struct Ctx2 *)ctx_;
    int i;
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].field_c != 0) {
            func_ov006_0204d3dc(ctx_, (int)&ctx->items[i]);
        }
    }
}

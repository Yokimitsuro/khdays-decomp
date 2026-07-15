/* Notify param_2 hook, then sweep ctx->items[] (base@+0xc, count@+0x30, stride
 * 0x38): for each element whose +0x14 word is nonzero, call
 * func_ov026_02083304(ctx, element, arg). base/count reloaded per-iter (callees
 * may mutate *ctx). */
extern void func_ov026_020836ac(int ctx, int arg);
extern void func_ov026_02083304(int ctx, int element, int arg);
struct Elem3 { unsigned char _pad[0x14]; int field_14; unsigned char _pad2[0x20]; };
struct Ctx3 { unsigned char _0[0xc]; struct Elem3 *items; unsigned char _1[0x20]; int count; };
void func_ov026_02083330(int ctx_, int arg) {
    struct Ctx3 *ctx = (struct Ctx3 *)ctx_;
    int i;
    func_ov026_020836ac(ctx_, arg);
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].field_14 != 0) {
            func_ov026_02083304(ctx_, (int)&ctx->items[i], arg);
        }
    }
}

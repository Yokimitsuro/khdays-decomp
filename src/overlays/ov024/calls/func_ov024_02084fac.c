/* The null check really is duplicated in the original (movs r4,r0 + cmpne r4,#0);
 * a single test compiles 4 B short. Keep both halves. */
extern void func_ov024_02085140(int *ctx);
extern void WM_EndKeySharing_0x02085104(int *p);

void func_ov024_02084fac(int *ctx) {
    if (ctx != 0 && ctx != 0) {
        func_ov024_02085140(ctx);
        WM_EndKeySharing_0x02085104(ctx);
    }
}

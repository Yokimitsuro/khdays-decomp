extern void func_02024c94(int *dst, int res, int a, int b, int c);
extern void func_02025464(int res, int a);
extern int func_020255d4(int res, int a, int b);
extern int func_020119d4(int block, int *out);

/* Load a graphics resource block into *dst: when the context has a secondary
 * archive (+0x1dbc) prefer it, else fall back to the primary (+0x1db8). */
void func_ov003_0204d308(int *dst, int ctx, int a, int b, int c) {
    if (*(int *)(ctx + 0x1dbc) == 0) {
        func_02024c94(dst, *(int *)(ctx + 0x1db8), a, b, c);
        return;
    }
    func_02024c94(dst, *(int *)(ctx + 0x1db8), a, -1, c);
    func_02025464(*(int *)(ctx + 0x1dbc), 0);
    if (b < 0) {
        return;
    }
    {
        int block = func_020255d4(*(int *)(ctx + 0x1dbc), 1, b);
        if (block == 0) {
            return;
        }
        if (func_020119d4(block, dst + 1) == 0) {
            dst[1] = 0;
        }
    }
}

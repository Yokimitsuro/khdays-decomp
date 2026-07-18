/* Create a sub-object via func_0203c5c0 and populate it through the stack out-param.
 * Returns c5c0's result: that is what keeps r0 live across the out-param reload, so the
 * ROM's `ldr r1,[sp,#N]` needs no extra instruction. */

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov257_020d25fc(void);
extern void func_ov257_020d2530(void);

int func_ov257_020d24dc(int self, int a, int b) {
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0xc, func_ov257_020d2530, func_ov257_020d25fc, &out);
    out[0] = a;
    out[1] = b;
    return rc;
}

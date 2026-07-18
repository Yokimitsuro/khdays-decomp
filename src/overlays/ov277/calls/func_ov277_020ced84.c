/* Create a sub-object via func_0203c5c0 and populate it through the stack out-param.
 * Returns c5c0's result: that is what keeps r0 live across the out-param reload, so the
 * ROM's `ldr r1,[sp,#N]` needs no extra instruction. */

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov277_020cee9c(void);
extern void func_ov277_020cedd8(void);

int func_ov277_020ced84(int self, int arg) {
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0xc, func_ov277_020cedd8, func_ov277_020cee9c, &out);
    out[0] = self;
    out[1] = arg;
    return rc;
}

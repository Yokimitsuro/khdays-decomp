/* Create a sub-object via func_0203c5c0 and populate it through the stack out-param.
 * Returns c5c0's result: that is what keeps r0 live across the out-param reload, so the
 * ROM's `ldr r1,[sp,#N]` needs no extra instruction. */

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov279_020d3488(void);
extern void func_ov279_020d3444(void);

int func_ov279_020d33f0(int self, int arg) {
    int *out;

    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x10, func_ov279_020d3444, func_ov279_020d3488, &out);
    out[0] = self;
    out[3] = arg;
    return rc;
}

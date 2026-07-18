/* Create a sub-object via func_0203c5c0 and back-link it to the owner.
 * Returns c5c0's result: that is what keeps r0 live across the out-param
 * load, so the ROM's `ldr r1,[sp,#8]` needs no extra instruction. */
extern int func_0203c5c0(int a, int b, int c, void *cb1, void *cb2, int **out);
extern void func_ov202_020cebdc(void);
extern void func_ov202_020cec88(void);

int func_ov202_020ceb3c(int this_) {
    int *entry;
    int rc = func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x10, func_ov202_020cebdc, func_ov202_020cec88, &entry);
    *entry = this_;
    return rc;
}

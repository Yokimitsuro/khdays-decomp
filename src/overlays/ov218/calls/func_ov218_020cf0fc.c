/* Create a sub-object via func_0203c5c0 and back-link it to the owner.
 * Returns c5c0's result: that is what keeps r0 live across the out-param
 * load, so the ROM's `ldr r1,[sp,#8]` needs no extra instruction. */
extern int func_0203c5c0(int a, int b, int c, void *cb1, void *cb2, int **out);
extern void func_ov218_020cf1ac(void);
extern void func_ov218_020cf260(void);

int func_ov218_020cf0fc(int this_) {
    int *entry;
    int rc = func_0203c5c0(*(int *)(this_ + 0x3c), 0x64, 0x10, func_ov218_020cf1ac, func_ov218_020cf260, &entry);
    *entry = this_;
    return rc;
}

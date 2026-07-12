/* Spawn a child object via func_0203c5c0, seed its +0 from *(this)+0x3a8 and return it. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov253_020d1f7c(int);
int func_ov253_020d1dec(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0xc, (void *)&func_ov253_020d1f7c, 0, &obj);
    *(int *)obj = *(int *)(param_1 + 0x3a8);
    return obj;
}

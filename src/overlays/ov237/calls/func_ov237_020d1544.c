/* Spawn a child object via func_0203c5c0, store this object at the child's +0xc, seed +0 from
 * *(this)+0x3e4 and return the child. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov237_020d18b4(int);
int func_ov237_020d1544(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x20, (void *)&func_ov237_020d18b4, 0, &obj);
    *(int *)(obj + 0xc) = param_1;
    *(int *)obj = *(int *)(param_1 + 0x3e4);
    return obj;
}

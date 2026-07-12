/* Spawn a child object via func_0203c5c0, seed +4 from *(this)+0x388, link back to owner and
 * return the child. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov255_020d281c(int);
int func_ov255_020d26b8(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x14, (void *)&func_ov255_020d281c, 0, &obj);
    *(int *)(obj + 4) = *(int *)(param_1 + 0x388);
    *(int *)obj = param_1;
    return obj;
}

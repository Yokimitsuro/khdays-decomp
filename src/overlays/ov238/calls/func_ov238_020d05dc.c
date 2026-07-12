/* Spawn a child object via func_0203c5c0 (+0x388 copy), link back to owner, store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov238_020d0760(int);
void func_ov238_020d05dc(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x38, (void *)&func_ov238_020d0760, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x388);
    *(int *)(param_1 + 0x214) = obj;
}

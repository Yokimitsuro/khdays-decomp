/* Spawn a child object via func_0203c5c0, copy fields from *(child), store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov146_020cc838(int);
void func_ov146_020cc5ec(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x60, (void *)&func_ov146_020cc838, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 0x4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(obj + 0x8) = *(int *)(*(int *)obj + 0x3b8);
    *(int *)(param_1 + 0x214) = obj;
}

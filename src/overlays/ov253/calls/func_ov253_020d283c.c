/* Spawn a child object via func_0203c5c0, link back to owner, store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov253_020d2888(int);
void func_ov253_020d283c(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x24, (void *)&func_ov253_020d2888, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

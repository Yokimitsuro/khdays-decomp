/* Spawn a child object via func_0203c5c0, copy fields from *(child), store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov258_020d0018(int);
void func_ov258_020cffb0(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x20, (void *)&func_ov258_020d0018, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 0x4) = *(int *)(*(int *)obj + 0x384);
    *(signed char *)(obj + 0x1d) = -1;
    *(int *)(param_1 + 0x214) = obj;
}

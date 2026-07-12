/* Spawn a child object via func_0203c5c0, copy fields from *(child), store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov258_020cd50c(int);
void func_ov258_020ccfbc(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x5c, (void *)&func_ov258_020cd50c, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 0x4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(obj + 0x8) = *(int *)(*(int *)obj + 0x3ac);
    *(int *)(param_1 + 0x214) = obj;
}

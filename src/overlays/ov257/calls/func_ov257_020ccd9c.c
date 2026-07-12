/* Spawn a child object via func_0203c5c0, link back to owner, store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov257_020cd2bc(int);
void func_ov257_020ccd9c(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x8c, (void *)&func_ov257_020cd2bc, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

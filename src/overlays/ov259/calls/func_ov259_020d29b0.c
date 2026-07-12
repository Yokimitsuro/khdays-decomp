/* Spawn a child object via func_0203c5c0 (+0x9c copy), link back to owner, store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov259_020d2a0c(int);
void func_ov259_020d29b0(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x30, (void *)&func_ov259_020d2a0c, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x9c);
    *(int *)(param_1 + 0x214) = obj;
}

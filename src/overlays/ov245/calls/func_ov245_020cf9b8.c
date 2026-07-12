/* Spawn a child object via func_0203c5c0 (+0x384 copy), link back to owner, store at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov245_020cfb30(int);
void func_ov245_020cf9b8(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x40, (void *)&func_ov245_020cfb30, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(param_1 + 0x214) = obj;
}

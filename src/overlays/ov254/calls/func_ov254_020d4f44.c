/* Spawn a child object via func_0203c5c0 (callback 020d1b8c), link it back to this object, copy
 * *(child)+0x384 into its +4 field and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov254_020d4fa0(int);
void func_ov254_020d4f44(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x10, (void *)&func_ov254_020d4fa0, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(param_1 + 0x214) = obj;
}

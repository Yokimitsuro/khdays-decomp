/* Spawn a child object via func_0203c5c0 (callback 020d4854), link it back to this
 * object and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov254_020d2fe4(int);
void func_ov254_020d2f98(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x50, (void *)&func_ov254_020d2fe4, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

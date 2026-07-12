/* Spawn a child object via func_0203c5c0 (callback 020d2000), link it back to this
 * object and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov244_020d2000(int);
void func_ov244_020d1ab8(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x6c, (void *)&func_ov244_020d2000, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

/* Spawn a child object via func_0203c5c0 (callbacks ov213_020d1c24 and ov213_020d1c90), link it
 * back to this object and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, void *cb2, int *out);
extern void func_ov273_020d58d0(int);
extern void func_ov273_020d5864(int);
void func_ov273_020d56ec(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x54, (void *)&func_ov273_020d5864,
                  (void *)&func_ov273_020d58d0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

/* Spawn a child object via func_0203c5c0 (callbacks ov213_020d1c24 and ov213_020d1c90), link it
 * back to this object and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, void *cb2, int *out);
extern void func_ov213_020d1c90(int);
extern void func_ov213_020d1c24(int);
void func_ov213_020d1aac(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x54, (void *)&func_ov213_020d1c24,
                  (void *)&func_ov213_020d1c90, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

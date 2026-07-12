/* Spawn a child object via func_0203c5c0 (callback ov185_020d0064), link it back to this object
 * and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov187_020d5ac4(int);
void func_ov187_020d5854(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x98, (void *)&func_ov187_020d5ac4, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}

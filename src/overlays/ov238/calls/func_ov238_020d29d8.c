/* Spawn a child object via func_0203c5c0 (callback ov238_020d2a34), link it back to this object,
 * copy *(child)+0x384 into the child's +4 field and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov238_020d2a34(int);
void func_ov238_020d29d8(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x4c, (void *)&func_ov238_020d2a34, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(param_1 + 0x214) = obj;
}

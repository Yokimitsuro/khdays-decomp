/* Spawn a child object via func_0203c5c0 (callback ov231_020cd118), link it back to this object,
 * store it at +0x214 and initialise the child's +0x58 and +0x50 fields. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov232_020d0d58(int);
void func_ov232_020d05bc(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x5c, (void *)&func_ov232_020d0d58, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
    *(int *)(obj + 0x58) = 1;
    *(short *)(obj + 0x50) = 0x155;
}

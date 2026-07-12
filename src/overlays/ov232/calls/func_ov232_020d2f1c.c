/* Spawn a child object via func_0203c5c0 (callback ov231_020cf338), link it back to this object,
 * set the child's +0x24 field to 0x155 and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov232_020d2f78(int);
void func_ov232_020d2f1c(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x28, (void *)&func_ov232_020d2f78, 0, &obj);
    *(int *)obj = param_1;
    *(short *)(obj + 0x24) = 0x155;
    *(int *)(param_1 + 0x214) = obj;
}

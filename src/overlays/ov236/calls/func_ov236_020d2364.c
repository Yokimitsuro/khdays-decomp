/* Unless the +0x24 gate is busy, resolve a value from obj+0xa0 via 0202f384/020050b4 into
 * +0x2c/+0x30, clear bit0 of +0x3c0, latch sub-state 9 and dispatch. */
extern int func_0202f384(void *, int, void *);
extern int func_020050b4(int, int);
extern int func_0203c634(int, int, void *);
extern int data_02042258;
void func_ov236_020d2364(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 0x24)) != 0) return;
    int buf[3];
    func_0202f384(buf, *(int *)owner + 0xa0, &data_02042258);
    int result = func_020050b4(buf[0], buf[2]);
    *(int *)(owner + 0x2c) = result;
    *(int *)(owner + 0x30) = result;
    *(int *)(*(int *)owner + 0x3c0) &= ~1;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 9;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}

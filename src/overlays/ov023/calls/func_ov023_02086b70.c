/* func_ov023_02086b70 -- script VM command: wait until the record the operand names is idle.
 * An operand of -1 means "the record the last command touched", which is remembered at +0x488 of
 * the VM state. Records are 0x104 bytes apart starting at +0x30. Reports 1 (finished) as soon as
 * func_ov023_02086b34 says the record is idle; otherwise re-arms and reports 0. */
extern int func_02021980(int vm, void *op);
extern int func_ov023_02086b34(int p);
extern void func_020219b4(int vm, void *op);

int func_ov023_02086b70(int vm, void *op) {
    int idx = func_02021980(vm, op);
    if (idx == -1) {
        idx = *(int *)(*(int *)(vm + 0x128) + 0x488);
    }
    if (func_ov023_02086b34(*(int *)(vm + 0x128) + 0x30 + (idx + idx * 64) * 4) != 0) {
        return 1;
    }
    func_020219b4(vm, op);
    return 0;
}

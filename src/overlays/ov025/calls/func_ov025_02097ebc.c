extern int func_ov025_020a41f0();
extern void func_ov025_020a4970();

void func_ov025_02097ebc(int arg0, int arg1, int arg2, int arg3) {
    if (func_ov025_020a41f0(0x14, 0, 0, arg3) == 0) return;
    func_ov025_020a4970();
    *(int *)(arg0 + 4) = 0;
}

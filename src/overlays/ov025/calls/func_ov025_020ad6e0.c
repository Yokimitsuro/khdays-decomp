extern void func_ov025_020ac2a0();
extern void func_02033b78();
extern void func_ov025_02084830();

void func_ov025_020ad6e0(int arg0) {
    if (*(int *)(arg0 + 0x180) != 0) {
        *(int *)(arg0 + 0x184) = 0;
        func_ov025_020ac2a0(arg0, 0);
        func_02033b78(0, 3);
        return;
    }
    func_ov025_02084830(1);
    func_02033b78(0, 3);
}

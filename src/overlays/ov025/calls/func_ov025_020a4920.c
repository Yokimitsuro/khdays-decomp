extern int func_ov025_02084b14();
extern int func_020300f8();
extern int data_ov025_020b575c;

void func_ov025_020a4920(int arg0) {
    int x = func_ov025_02084b14(arg0);
    if (data_ov025_020b575c == 0) {
        return;
    }
    func_020300f8(x + 0x118);
}

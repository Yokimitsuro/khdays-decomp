extern void func_ov025_02094390();
extern int func_ov025_020922fc();
extern void func_ov025_02092da0();
extern void func_ov025_02092f34();
extern void func_020300f8();

void func_ov025_02094414(int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3) {
    func_ov025_02094390(arg0, arg1, arg2, arg3);
    int r = func_ov025_020922fc(arg0, arg1, arg2, arg3);
    if (r != 0) {
        func_ov025_02092da0(arg0, r);
        func_ov025_02092f34(arg0, r);
    }
    func_020300f8(arg0 + 0xac);
}

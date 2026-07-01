extern int func_0200c2c8();
extern int func_0200c340();
extern int func_0200c3d4();
extern int func_0200c694();
extern int func_0200ca50();
extern int func_0200ca68();

void func_ov001_0204cb6c(void) {
    int buf[2];

    func_0200c2c8();
    if (func_0200c340(buf) != 0) {
        func_0200c3d4(buf);
    }
    func_0200c694(9, 0x14);
    func_0200ca50(8);
    func_0200ca68(8);
}

extern void func_ov103_020bb180();
extern void func_ov103_020bb390();
extern void func_ov103_020bb56c();

struct b1 { unsigned char b : 1; };

void func_ov103_020bb034(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov103_020bb180(this_, arg1);
    func_ov103_020bb390(this_, arg1);
    func_ov103_020bb56c(this_, arg1);
}

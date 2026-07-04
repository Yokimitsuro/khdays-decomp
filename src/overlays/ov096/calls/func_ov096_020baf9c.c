extern void func_ov096_020bb0f8();
extern void func_ov096_020bb240();
extern void func_ov096_020bb560();

struct b1 { unsigned char b : 1; };

void func_ov096_020baf9c(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov096_020bb0f8(this_, arg1 + 8);
    func_ov096_020bb240(this_, arg1);
    func_ov096_020bb560(this_, arg1);
}

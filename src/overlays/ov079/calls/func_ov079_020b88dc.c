extern void func_ov079_020b8a38();
extern void func_ov079_020b8b80();
extern void func_ov079_020b8ea0();

struct b1 { unsigned char b : 1; };

void func_ov079_020b88dc(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov079_020b8a38(this_, arg1 + 8);
    func_ov079_020b8b80(this_, arg1);
    func_ov079_020b8ea0(this_, arg1);
}

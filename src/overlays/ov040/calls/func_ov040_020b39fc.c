extern void func_ov040_020b3b58();
extern void func_ov040_020b3ca0();
extern void func_ov040_020b3fc0();

struct b1 { unsigned char b : 1; };

void func_ov040_020b39fc(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov040_020b3b58(this_, arg1 + 8);
    func_ov040_020b3ca0(this_, arg1);
    func_ov040_020b3fc0(this_, arg1);
}

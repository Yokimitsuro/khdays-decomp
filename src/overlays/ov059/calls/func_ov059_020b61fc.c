extern void func_ov059_020b6358();
extern void func_ov059_020b64a0();
extern void func_ov059_020b67c0();

struct b1 { unsigned char b : 1; };

void func_ov059_020b61fc(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov059_020b6358(this_, arg1 + 8);
    func_ov059_020b64a0(this_, arg1);
    func_ov059_020b67c0(this_, arg1);
}

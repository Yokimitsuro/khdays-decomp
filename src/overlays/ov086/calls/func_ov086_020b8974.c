extern void func_ov086_020b8ac0();
extern void func_ov086_020b8cd0();
extern void func_ov086_020b8eac();

struct b1 { unsigned char b : 1; };

void func_ov086_020b8974(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov086_020b8ac0(this_, arg1);
    func_ov086_020b8cd0(this_, arg1);
    func_ov086_020b8eac(this_, arg1);
}

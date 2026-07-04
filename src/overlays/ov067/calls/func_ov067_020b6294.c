extern void func_ov067_020b63e0();
extern void func_ov067_020b65f0();
extern void func_ov067_020b67cc();

struct b1 { unsigned char b : 1; };

void func_ov067_020b6294(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov067_020b63e0(this_, arg1);
    func_ov067_020b65f0(this_, arg1);
    func_ov067_020b67cc(this_, arg1);
}

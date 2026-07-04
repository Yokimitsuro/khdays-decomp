extern void func_ov048_020b3be0();
extern void func_ov048_020b3df0();
extern void func_ov048_020b3fcc();

struct b1 { unsigned char b : 1; };

void func_ov048_020b3a94(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov048_020b3be0(this_, arg1);
    func_ov048_020b3df0(this_, arg1);
    func_ov048_020b3fcc(this_, arg1);
}

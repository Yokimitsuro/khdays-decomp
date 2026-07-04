extern void func_0202aa9c();
extern void func_ov076_020b957c();

struct b1 { unsigned char b : 1; };

void func_ov076_020b943c(int this_, int arg1) {
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    if (*(int *)arg1 == 2) {
        func_0202aa9c(arg1 + 4);
    }
    func_ov076_020b957c(this_, arg1);
}

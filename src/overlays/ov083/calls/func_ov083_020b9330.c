extern void func_0202aa9c();

struct b1 { unsigned char b : 1; };

void func_ov083_020b9330(int this_, int arg1) {
    signed char s = *(signed char *)arg1;
    if (s != 2 && s != 3 && s != 4) return;
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_0202aa9c(arg1 + 4);
}

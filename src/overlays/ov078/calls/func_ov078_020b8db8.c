extern void func_ov078_020b8ebc();

struct b1 { unsigned char b : 1; };

void func_ov078_020b8db8(int this_, int arg1) {
    int i;
    char *p;
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov078_020b8ebc(this_, (int)p);
    }
}

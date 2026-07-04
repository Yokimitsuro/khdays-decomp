extern void func_ov095_020bb57c();

struct b1 { unsigned char b : 1; };

void func_ov095_020bb478(int this_, int arg1) {
    int i;
    char *p;
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov095_020bb57c(this_, (int)p);
    }
}

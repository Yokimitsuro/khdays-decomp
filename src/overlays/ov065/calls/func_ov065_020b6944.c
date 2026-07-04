extern void func_ov065_020b6ae8();
extern void func_ov065_020b6ce8();

struct b1 { unsigned char b : 1; };

void func_ov065_020b6944(int this_, int arg1) {
    int i;
    char *p;
    if (((struct b1 *)(this_ + 0x694))->b == 0) return;
    func_ov065_020b6ae8(this_, arg1);
    p = (char *)(arg1 + 0x128);
    for (i = 0; i < 6; i++) {
        func_ov065_020b6ce8((int)p);
        p += 0x120;
    }
}

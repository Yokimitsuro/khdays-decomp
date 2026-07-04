extern void func_ov107_020c5c54();

struct w4 { int a, b, c, d; };

void func_ov151_020cc954(int this_, int arg1, struct w4 *src) {
    unsigned short *p;
    unsigned int h;
    func_ov107_020c5c54(this_, arg1);
    *(struct w4 *)(this_ + 0x394) = *src;
    p = (unsigned short *)(this_ + 0x60);
    h = *p;
    *p = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
}

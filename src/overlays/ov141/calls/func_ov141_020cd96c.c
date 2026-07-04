extern void func_ov107_020c5c54();

struct w3 { int a, b, c; };

void func_ov141_020cd96c(int this_, int arg1, struct w3 *src) {
    unsigned short *p;
    unsigned int h;
    func_ov107_020c5c54(this_, arg1);
    *(struct w3 *)(this_ + 0x38c) = *src;
    p = (unsigned short *)(this_ + 0x60);
    h = *p;
    *p = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
}

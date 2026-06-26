struct S {
    char pad0[8];
    unsigned short h;
    char pad1[0x19];
    unsigned char b;
};

int func_ov008_02056024(struct S *p, unsigned int n) {
    if (p->b != 0) {
        return 0;
    }
    return p->h < n;
}

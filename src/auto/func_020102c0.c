struct S {
    int a;
    int b;
};

void func_020102c0(struct S *out, unsigned int p) {
    unsigned short h = *(unsigned short *)(p + 2);
    out->a = p - (unsigned short)((h >> 8) & 0x7f);
    out->b = *(int *)(p + 4) + (p + 0x10);
}

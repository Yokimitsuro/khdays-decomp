extern int func_ov107_020c9ec8();
extern int func_ov107_020c6980();

struct V {
    int a;
    int b;
    int c;
};

struct S {
    char pad0[0x60];
    unsigned short n60 : 8;
    unsigned short n60b : 8;
    char pad1[0xb0 - 0x62];
    struct V vb0;
    char pad3[0x3f0 - 0xbc];
    struct V v3f0;
    char pad4[0x490 - 0x3fc];
    void *p490;
    struct V v494;
    int n4a0;
};

void func_ov229_020d1f5c(struct S *r4, int r5) {
    func_ov107_020c9ec8(r4->p490);
    func_ov107_020c6980(r4, r5);
    if (r4->n60 & 0x80) {
        r4->v494 = r4->vb0;
        *(int *)((char *)r4 + 0x498) += 0x2000;
    } else {
        r4->v494 = r4->v3f0;
    }
    r4->n4a0 = 0x2000;
}

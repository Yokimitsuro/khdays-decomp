struct E {
    char pad0[0x24];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
    char pad25[0xb];
};

struct S {
    char pad0[0x10];
    struct E *p;            /* 0x10 */
    char pad14[0x20];
    int count;              /* 0x34 */
};

struct E *func_ov009_02051e04(struct S *a) {
    int i;
    for (i = 0; i < a->count; i++) {
        if (!a->p[i].b1) break;
    }
    return &a->p[i];
}

extern int func_0202a440();
extern int func_0203c7e8();
extern int func_ov107_020c9eac();
extern int func_ov107_020c68ec();

struct E {
    void *p;
    void *q;
};

struct S {
    char pad[0x384];
    void *p384;
    char pad2[0x390 - 0x388];
    int n390;
    char pad3[0x3a8 - 0x394];
    void *p3a8;
    char pad4[0x490 - 0x3ac];
    void *p490;
    char pad5[0x4a8 - 0x494];
    struct E e4a8[10];
};

int func_ov249_020d00e4(struct S *r5) {
    int i;
    func_0202a440(&r5->p384);
    r5->n390 = 0;
    func_0203c7e8(r5->p3a8);
    func_ov107_020c9eac(r5->p490);
    for (i = 0; i < 10; i++) {
        if (r5->e4a8[i].p) {
            func_0203c7e8(r5->e4a8[i].p);
        }
    }
    return func_ov107_020c68ec(r5);
}

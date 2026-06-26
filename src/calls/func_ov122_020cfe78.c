extern int func_0203c7e8();
extern int func_ov107_020c9eac();
extern int func_0203d194();
extern int func_ov107_020c68ec();

struct E {
    void *p;
    void *q;
};

struct S {
    char pad[0x384];
    void *p384;
    char pad2[0x3a0 - 0x388];
    void *p3a0;
    struct E *p3a4;
};

int func_ov122_020cfe78(struct S *r5) {
    int i;
    func_0203c7e8(r5->p384);
    func_ov107_020c9eac(r5->p3a0);
    for (i = 0; i < 3; i++) {
        func_0203c7e8(r5->p3a4[i].p);
    }
    func_0203d194(r5->p3a4);
    return func_ov107_020c68ec(r5);
}

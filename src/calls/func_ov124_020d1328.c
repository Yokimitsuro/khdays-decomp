extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();

struct Elem {
    void *ptr;
    int other;
};

struct S {
    char pad[0x384];
    void *m384;
    char pad2[0x390 - 0x388];
    struct Elem *m390;
};

int func_ov124_020d1328(struct S *r5) {
    int i;
    func_0203c7e8(r5->m384);
    for (i = 0; i < 2; i++) {
        func_0203c7e8(r5->m390[i].ptr);
    }
    func_0203d194(r5->m390);
    return func_ov107_020c68ec(r5);
}

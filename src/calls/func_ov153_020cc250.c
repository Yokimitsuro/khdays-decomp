extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();

struct Elem {
    void *ptr;
    void *other;
};

struct S {
    char pad[0x384];
    void *p384;
    char pad2[0x394 - 0x388];
    struct Elem *p394;
};

int func_ov153_020cc250(struct S *r5) {
    int i;
    func_0203c7e8(r5->p384);
    for (i = 0; i < 2; i++) {
        func_0203c7e8(r5->p394[i].ptr);
    }
    func_0203d194(r5->p394);
    return func_ov107_020c68ec(r5);
}

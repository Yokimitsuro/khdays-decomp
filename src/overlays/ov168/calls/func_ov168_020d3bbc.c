extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();

struct Elem {
    int a;
    int b;
};

struct S {
    char pad[0x384];
    int field_384;
    char pad2[0x39c - 0x384 - 4];
    struct Elem *field_39c;
};

void func_ov168_020d3bbc(struct S *s) {
    int i;
    func_0203c7e8(s->field_384);
    for (i = 0; i < 3; i++) {
        func_0203c7e8(s->field_39c[i].a);
    }
    func_0203d194(s->field_39c);
    func_ov107_020c68ec(s);
}

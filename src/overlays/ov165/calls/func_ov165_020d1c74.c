extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();
extern int func_ov107_020c9eac();

struct Entry {
    void *ptr;
    int pad;
};

struct Obj {
    char pad0[0x384];
    void *field_384;
    char pad1[0x3c4 - 0x384 - 4];
    struct Entry *field_3c4;
    void *field_3c8;
};

int func_ov165_020d1c74(struct Obj *self) {
    int i;
    func_0203c7e8(self->field_384);
    func_ov107_020c9eac(self->field_3c8);
    for (i = 0; i < 5; i++) {
        func_0203c7e8(self->field_3c4[i].ptr);
    }
    func_0203d194(self->field_3c4);
    return func_ov107_020c68ec(self);
}

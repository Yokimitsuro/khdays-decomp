struct Entry {
    unsigned short id;
    short pad;
    int field4;
    int field8;
    int fieldC;
};

struct Obj {
    char pad0[0x14];
    struct Entry *entries;
    char pad18[0x38 - 0x18];
    int count;
};

struct Entry *func_ov005_0204cbdc(struct Obj *obj, int id) {
    int i;
    for (i = 0; i < obj->count; i++) {
        if (obj->entries[i].fieldC != 0) {
            if (id == obj->entries[i].id) {
                break;
            }
        }
    }
    return &obj->entries[i];
}

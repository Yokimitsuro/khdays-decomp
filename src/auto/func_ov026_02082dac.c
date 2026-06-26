struct Element {
    int unk0;
    int unk4;
    int unk8;
    int field_c;
};

struct Obj {
    char pad[0x14];
    struct Element *elems;
    char pad2[0x38 - 0x14 - 4];
    int count;
};

struct Element *func_ov026_02082dac(struct Obj *obj) {
    int i;
    for (i = 0; i < obj->count; i++) {
        if (obj->elems[i].field_c == 0) {
            break;
        }
    }
    return &obj->elems[i];
}

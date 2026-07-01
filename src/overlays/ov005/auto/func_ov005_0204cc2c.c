struct Elem {
    char pad[0x14];
    int active;
    char pad2[0x38 - 0x18];
};

struct Obj {
    char pad[0xc];
    struct Elem *arr;
    char pad2[0x30 - 0x10];
    int count;
};

struct Elem *func_ov005_0204cc2c(struct Obj *o) {
    int i = 0;
    struct Elem *p;
    if (o->count > 0) {
        p = o->arr;
        do {
            if (p->active == 0) break;
            i++;
            p++;
        } while (i < o->count);
    }
    return o->arr + i;
}

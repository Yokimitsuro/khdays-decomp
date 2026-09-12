typedef struct Obj {
    char _0[0x110];
    int flags;               // 0x110
    char _114[0x12c - 0x114];
    int field_12c;           // 0x12c
    char _130[0x14c - 0x130];
    void *field_14c;         // 0x14c: back-pointer to owning handle
    int field_150;           // 0x150
    char _154[0x174 - 0x154];
} Obj;

typedef struct Outer {
    Obj *ptr;
} Outer;

extern void func_0201cbd0(Outer *p);
extern void func_0201d0e0(Obj *p);

extern Obj data_0204b62c[];

void *func_0201cd60(Outer *handle, int idx, int value) {
    Obj *obj;

    if (handle->ptr != 0)
        func_0201cbd0(handle);

    obj = &data_0204b62c[idx];
    if (obj->field_12c == 0)
        return 0;

    if ((obj->flags << 31) >> 31) {
        if (value < obj->field_150)
            return 0;
        func_0201d0e0(obj);
    }
    obj->field_150 = value;
    obj->flags = (obj->flags & ~1) | 1;
    obj->field_14c = handle;
    handle->ptr = obj;
    return obj;
}

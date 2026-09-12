typedef unsigned int u32;

typedef struct Obj {
    char pad0[0x94];
    void *field_94;
    char pad1[0x9c - 0x94 - 4];
    void *field_9c;
    void *field_a0;
    char pad2[0xb0 - 0xa4];
    void *field_b0;
} Obj;

extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_0203d194(void *p);
extern void func_ov107_020c2c44(Obj *self);

void func_ov107_020c9730(Obj *self)
{
    if (self->field_b0) {
        NNSi_FndDestroyDoubleList(self->field_b0);
        func_0203d194(self->field_b0);
        self->field_b0 = 0;
    }
    if (self->field_94) {
        func_0203d194(self->field_94);
    }
    if (self->field_9c) {
        func_0203d194(self->field_9c);
    }
    if (self->field_a0) {
        func_0203d194(self->field_a0);
    }
    func_ov107_020c2c44(self);
}

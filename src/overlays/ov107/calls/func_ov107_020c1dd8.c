typedef struct {
    void *ptr;
    int val;
} Ov107Slot;

typedef struct Ov107Object {
    unsigned char pad_000[0xb0];
    unsigned short field_b0;
    unsigned char pad_b2[2];
    Ov107Slot slots[8];
} Ov107Object;

extern void func_0203d194(void *p);

void func_ov107_020c1dd8(Ov107Object *obj)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (obj->slots[i].ptr != 0) {
            func_0203d194(obj->slots[i].ptr);
            obj->slots[i].ptr = 0;
        }
        obj->slots[i].val = 0;
    }
    obj->field_b0 = 0;
}

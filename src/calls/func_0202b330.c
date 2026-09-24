/* Places a model object: the position is `pos`, or when none is given the object's own +0xa8 point
 * (or, for a bone-driven object (flag 0x20), the point of its +0x110 transform). Unless frozen
 * (flag 0x10) the +0x110 transform takes the position and is attached to the owner's scene; a free
 * object keeps the position in +0xa8. The object is marked placed (flag 8) and remembers `owner`. */
typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    int field_00;
    char pad_04[0xa4];
    VecFx32 pos_a8;
    char pad_b4[0x5c];
    char sub_110[0x48];
} Obj;

extern VecFx32 *func_0202b160(void *xf);
extern void func_020293fc(void *xf, VecFx32 *pos);
extern void func_0202922c(int scene, void *xf);

void func_0202b330(int owner, Obj *obj, VecFx32 *pos)
{
    if (pos == 0) {
        if (!(obj->field_00 & 0x20)) {
            pos = &obj->pos_a8;
        } else {
            pos = func_0202b160(obj->sub_110);
        }
    }
    if (!(obj->field_00 & 0x10)) {
        func_020293fc(obj->sub_110, pos);
        func_0202922c(**(int **)(owner + 4), obj->sub_110);
    }
    if (!(obj->field_00 & 0x20)) {
        obj->pos_a8 = *pos;
    }
    obj->field_00 |= 8;
    *(int *)((char *)obj + 0x10c) = owner;
}

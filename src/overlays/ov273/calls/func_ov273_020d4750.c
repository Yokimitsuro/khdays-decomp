/* Chase step: slerps the working quaternion towards the facing one by half of thirty
 * times the frame delta, writes the result into the actor's transform, hands the
 * accumulated velocity to the actor's motion slot and clears it. */
extern int func_0202f55c();
extern int func_0203c9d0();

extern int data_02041dc8;

typedef struct { int a, b, c; } Vec3;

typedef struct {
    char pad0[0xf0];
    Vec3 vf0;
} Node;

typedef struct {
    char pad0[0x2c];
    int f2c;
} Field0;

typedef struct {
    Node *n0;
    char pad4[0x8];
    Vec3 v0c;
    char pad18[0x28];
    char f40[0x10];
    char f50[0x10];
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

void func_ov273_020d4750(Obj *obj)
{
    Field0 *field0 = obj->field0;
    Inner *inner = obj->inner;

    func_0202f55c(inner->f50, (field0->f2c * 30) / 2, inner->f50, inner->f40);
    func_0203c9d0((char *)inner->n0 + 0xa0, inner->f50);

    inner->n0->vf0 = inner->v0c;
    inner->v0c = *(Vec3 *)&data_02041dc8;
}

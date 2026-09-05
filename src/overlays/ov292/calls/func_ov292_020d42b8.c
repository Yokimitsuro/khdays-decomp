/* Third chase step: slerps the working quaternion towards the facing one by
 * three times the frame delta, writes the result into the actor's transform,
 * hands the accumulated velocity to the actor's motion slot and clears it.
 * Same routine as the matched ov178 step without its two trailing counters. */
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
    char pad4[0xc];
    Vec3 v10;
    char pad1c[0x1c];
    char f38[0x10];
    char f48[0x10];
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

void func_ov292_020d42b8(Obj *obj)
{
    Field0 *field0 = obj->field0;
    Inner *inner = obj->inner;

    func_0202f55c(inner->f38, (field0->f2c * 30) / 10, inner->f38, inner->f48);
    func_0203c9d0((char *)inner->n0 + 0xa0, inner->f38);

    inner->n0->vf0 = inner->v10;
    inner->v10 = *(Vec3 *)&data_02041dc8;
}

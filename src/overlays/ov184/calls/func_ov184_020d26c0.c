extern int func_0203d040();
extern int func_0202f188();
extern int func_0202ed60();
extern int func_0202ef54();
extern int func_0203c9d0();

typedef struct { int a, b, c; } Vec3;

extern Vec3 data_02041dc8;
extern Vec3 data_02042264;

typedef struct {
    char pad0[0xa0];
    char fa0;
    char pada1[0xf0 - 0xa1];
    char f0f0;
    char padf1[0x124 - 0xf1];
    char f124;
} Node;

typedef struct {
    char pad2c[0x2c];
    int f2c;
} Field0;

typedef struct {
    Node *n0;
    char pad4[0x14 - 4];
    int f14;
    int f18;
    char pad1c[0x20 - 0x1c];
    int f20;
    char pad24[0x54 - 0x24];
    Vec3 v54;
    char pad60[0x74 - 0x60];
    int f74;
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

void func_ov184_020d26c0(Obj *obj)
{
    Inner *inner = obj->inner;
    int v;
    char localA[0x10];
    char localB[0x10];

    inner->f14 = func_0203d040(inner->f14, inner->f18, inner->f20, 0);

    func_0202f188(localB, &data_02042264, inner->f14);
    func_0202ed60(localA, &data_02042264, &inner->n0->f124);
    func_0202ef54(localA, localA, localB);
    func_0203c9d0(&inner->n0->fa0, localA);

    v = inner->f74;
    if (v > 0) {
        inner->f74 = v - obj->field0->f2c;
    }

    *(Vec3 *)&inner->n0->f0f0 = inner->v54;
    inner->v54 = data_02041dc8;
}

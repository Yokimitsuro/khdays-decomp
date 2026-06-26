extern int func_0203d040();
extern int func_0202f188();
extern int func_0202ed60();
extern int func_0202ef54();
extern int func_0203c9d0();

typedef struct { int a, b, c; } Vec3;

extern Vec3 data_02042264;
extern Vec3 data_02041dc8;

typedef struct {
    char *n0;
    char pad4[4];
    int f8;
    int fc;
    int f10;
    int f14;
    Vec3 v18;
} Inner;

typedef struct {
    char pad0[4];
    Inner *inner;
} Obj;

void func_ov151_020cdd08(Obj *obj)
{
    Inner *inner = obj->inner;
    char localB[0x10];
    char localA[0x10];

    inner->f8 = func_0203d040(inner->f8, inner->fc, inner->f10, &inner->f14);

    func_0202f188(localB, &data_02042264, inner->f8);
    func_0202ed60(localA, &data_02042264, inner->n0 + 0x124);
    func_0202ef54(localA, localA, localB);
    func_0203c9d0(inner->n0 + 0xa0, localA);

    *(Vec3 *)(inner->n0 + 0xf0) = inner->v18;
    inner->v18 = data_02041dc8;
}

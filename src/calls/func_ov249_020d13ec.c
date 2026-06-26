extern int func_0203d040();
extern int func_0202f188();
extern int func_0203c9d0();
extern int func_01ff8b90();
extern int func_01ffa724();
extern int func_01ff8d18();
extern int func_0202f384();
extern int func_01fff8e8();
extern int func_01ffd144();

typedef struct { int a, b, c; } Vec3;

extern Vec3 data_02042264;
extern Vec3 data_02041dc8;

typedef struct {
    char pad0[0x2c];
    int f2c;
} Field0;

typedef struct {
    Field0 *field0;
    void *f4;
    char pad8[0x74];
    int f7c;
} Node;

typedef struct {
    Node *n0;
    char pad4[8];
    Vec3 *fc;
    Vec3 v10;
    char pad1c[0xc];
    Vec3 v28;
    char pad34[0xc];
    int f40;
    int f44;
    char pad48[0xc];
    int f54;
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

typedef struct {
    char pad0[8];
    int f8;
    void *fc;
} Result;

void func_ov249_020d13ec(Obj *obj)
{
    Inner *inner = obj->inner;
    int local28[4];
    Vec3 local1c;
    char local10[0xc];
    int box[4];
    void *node4;
    Result *res;

    local1c = inner->v10;

    inner->f40 = func_0203d040(inner->f40, inner->f44,
                               obj->field0->f2c * 0xbe / 100, 0);
    func_0202f188(local28, &data_02042264, inner->f40);
    func_0203c9d0((char *)inner->n0 + 0xa0, local28);
    func_01ff8b90(&local1c, &inner->v28, &local1c);
    func_01ffa724(0xb00, &inner->v28, &inner->v28);

    if (func_01ff8d18(&inner->v28, local10) < 0x80) {
        inner->v28 = data_02041dc8;
    }

    node4 = inner->n0->f4;
    box[1] = 0;
    box[2] = 0x1800;
    box[3] = 0x1000;
    func_0202f384(&box[1], (char *)inner->n0 + 0xa0, &box[1]);
    func_01ff8b90(&box[1], inner->fc, &box[1]);
    box[0] = 0;
    res = (Result *)func_01fff8e8(*(int *)((char *)node4 + 0x7c), &box[1], &local1c, 0x1800);
    if (res != 0 && res->f8 == 0) {
        func_01ffd144(res->fc, &local1c, &local1c);
    }

    *(Vec3 *)((char *)inner->n0 + 0xf0) = local1c;
    inner->v10 = data_02041dc8;

    inner->f54 = inner->f54 - obj->field0->f2c;
    if (inner->f54 <= 0) {
        inner->f54 = 0;
    }
}

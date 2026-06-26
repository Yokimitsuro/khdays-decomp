extern int func_0202f55c();
extern int func_0203c9d0();

extern int data_02041dc8;

typedef struct { int a, b, c; } Vec3;

typedef struct {
    char pad0[0xf0];
    Vec3 vf0;
    char padfc[0x40];
    int f13c;
} Node;

typedef struct {
    char pad0[0x2c];
    int f2c;
} Field0;

typedef struct {
    Node *n0;
    char pad4[0x1c];
    Vec3 v20;
    char pad2c[0x18];
    int f44;
    char pad48[0x10];
    int f58;
    char pad5c[8];
    char f64[0x10];
    char f74[4];
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

void func_ov176_020d0a8c(Obj *obj)
{
    Field0 *field0 = obj->field0;
    Inner *inner = obj->inner;
    int v;

    func_0202f55c(inner->f64, (field0->f2c * 30) / 10, inner->f64, inner->f74);
    func_0203c9d0((char *)inner->n0 + 0xa0, inner->f64);

    inner->n0->vf0 = inner->v20;
    inner->v20 = *(Vec3 *)&data_02041dc8;

    inner->f44 = inner->n0->f13c;

    v = inner->f58 - obj->field0->f2c;
    inner->f58 = v;
    if (v <= 0) {
        inner->f58 = 0;
    }
}

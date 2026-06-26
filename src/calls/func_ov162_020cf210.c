extern int func_0203d040();
extern int func_0202f188();
extern int func_0202ed60();
extern int func_0202ef54();
extern int func_0203c9d0();
extern int INITi_CpuClear32_0x01ff86fc();

typedef struct { int a, b, c; } Vec3;

extern Vec3 data_02042264;

typedef struct {
    char pad0[0x60];
    unsigned short f60;
    char pad62[0x118];
    unsigned char f17a;
} Node;

typedef struct {
    char pad0[0x2c];
    int f2c;
} Field0;

typedef struct {
    Node *n0;
    char pad4[8];
    int fc;
    int f10;
    int f14;
    Vec3 v18;
    char pad24[0x10];
    int f34;
} Inner;

typedef struct {
    Field0 *field0;
    Inner *inner;
} Obj;

void func_ov162_020cf210(Obj *obj)
{
    Inner *inner = obj->inner;
    int v;
    char localB[0x10];
    char localA[0x10];

    inner->fc = func_0203d040(inner->fc, inner->f10, inner->f14, 0);

    if (!((unsigned)(inner->n0->f60 << 24) >> 24 & 0x40) && ((unsigned)(inner->n0->f17a << 31) >> 31)) {
        func_0202f188(localB, &data_02042264, inner->fc);
        func_0202ed60(localA, &data_02042264, (char *)inner->n0 + 0x124);
        func_0202ef54(localA, localA, localB);
        func_0203c9d0((char *)inner->n0 + 0xa0, localA);
    }

    v = inner->f34;
    if (v > 0) {
        inner->f34 = v - obj->field0->f2c;
    }

    *(Vec3 *)((char *)inner->n0 + 0xf0) = inner->v18;
    INITi_CpuClear32_0x01ff86fc(0, &inner->v18, 0xc);
}

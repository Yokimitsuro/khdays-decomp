typedef int fx32;
typedef struct { fx32 x, y, z; } VecFx32;

static inline fx32 FX_Mul(fx32 a, fx32 b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

typedef struct {
    VecFx32 offset;
    fx32 scale_x;
    fx32 scale_y;
    fx32 scale_z;
    unsigned char flags : 1;
} XformObj;

typedef struct {
    unsigned char sel : 4;
    unsigned char rest : 4;
} Sel;

extern void func_0203cc64(VecFx32 *out, XformObj *obj, VecFx32 *in);
extern void func_02039824(int *dst, int *src);
extern void func_0202f384(VecFx32 *in_vec, XformObj *unused, VecFx32 *out_vec);
extern void func_01ffa724(int factor, VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void func_02039874(int *dst, VecFx32 *src);
extern void func_02039958(int *dst, VecFx32 *src);

void func_ov107_020c3368(unsigned char *self)
{
    VecFx32 *work = (VecFx32 *)(self + 4);

    switch (((Sel *)self)->sel) {
    case 0:
        func_0203cc64((VecFx32 *)(self + 0x68), (XformObj *)(self + 0x10), (VecFx32 *)(self + 0x58));
        *(fx32 *)(self + 0x74) = FX_Mul(*(fx32 *)(self + 0x64), *(fx32 *)(self + 0x2c));
        *work = *(VecFx32 *)(self + 0x68);
        func_02039824((int *)(self + 0x3c), (int *)(self + 0x68));
        return;
    case 1: {
        fx32 half;

        func_0203cc64((VecFx32 *)(self + 0x78), (XformObj *)(self + 0x10), (VecFx32 *)(self + 0x58));
        func_0202f384((VecFx32 *)(self + 0x84), (XformObj *)(self + 0x10), (VecFx32 *)(self + 0x64));
        *(fx32 *)(self + 0x90) = FX_Mul(*(fx32 *)(self + 0x70), *(fx32 *)(self + 0x2c));
        *(fx32 *)(self + 0x94) = FX_Mul(*(fx32 *)(self + 0x74), *(fx32 *)(self + 0x2c));
        half = *(fx32 *)(self + 0x90) / 2;
        func_01ffa724(half, (VecFx32 *)(self + 0x84), work);
        VEC_Add((VecFx32 *)(self + 0x78), work, work);
        func_02039874((int *)(self + 0x3c), (VecFx32 *)(self + 0x78));
        return;
    }
    case 2: {
        int i;
        VecFx32 *dstv;
        VecFx32 *srcv;

        func_0203cc64((VecFx32 *)(self + 0x94), (XformObj *)(self + 0x10), (VecFx32 *)(self + 0x58));
        i = 0;
        dstv = (VecFx32 *)(self + 0x64);
        srcv = (VecFx32 *)(self + 0xa0);
        for (; i < 3; i++) {
            func_0202f384(srcv, (XformObj *)(self + 0x10), dstv);
            ((fx32 *)(self + 0xc4))[i] = FX_Mul(((fx32 *)(self + 0x88))[i], *(fx32 *)(self + 0x2c));
            dstv++;
            srcv++;
        }
        *work = *(VecFx32 *)(self + 0x94);
        func_02039958((int *)(self + 0x3c), (VecFx32 *)(self + 0x94));
        return;
    }
    default:
        return;
    }
}

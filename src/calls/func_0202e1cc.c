typedef signed long fx32;
typedef signed long long fx64;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(int *a, int *b, int *out);
extern VecFx32 data_020420e8;

/* self: an actor-local vector workspace. field_24 is a scratch VecFx32 built
 * either from a fixed "straight down" direction or copied from src's own
 * field_04 triple; field_30 is src's field_4c triple; field_3c is the
 * matrix-rotated straight-down vector; field_48 is an anchor vector set by
 * the caller and only read here. */
typedef struct Self {
    char pad_00[0x24];
    fx32 field_24;
    fx32 field_28;
    fx32 field_2c;
    fx32 field_30;
    fx32 field_34;
    fx32 field_38;
    VecFx32 field_3c;
    VecFx32 field_48;
} Self;

/* src: field_04 doubles as a sentinel-compared scalar (0x7ffff000 means "no
 * direction") and, together with field_08/field_0c, as a VecFx32 triple.
 * mtx is the object's rotation matrix; field_4c is a VecFx32 offset. */
typedef struct Src {
    fx32 field_00;
    fx32 field_04;
    fx32 field_08;
    fx32 field_0c;
    fx32 pad_10[6];
    MtxFx33 mtx;
    fx32 field_4c;
    fx32 field_50;
    fx32 field_54;
} Src;

void func_0202e1cc(Self *self, Src *src)
{
    VecFx32 vec = data_020420e8;
    int a = src->field_4c;
    int c = src->field_54;
    int b = src->field_50;
    int kind;

    self->field_30 = a;
    self->field_34 = b;
    self->field_38 = c;

    kind = src->field_04;
    if (kind == 0x7ffff000) {
        self->field_24 = 0;
        self->field_28 = -0x1000;
        self->field_2c = 0;
        MTX_MultVec33(&vec, &src->mtx, &self->field_3c);
        MTX_MultVec33((VecFx32 *)&self->field_24, &src->mtx, (VecFx32 *)&self->field_24);
        VEC_Add((int *)&self->field_24, (int *)&self->field_30, (int *)&self->field_24);
    } else {
        int c2 = src->field_0c;
        int b2 = src->field_08;
        self->field_24 = kind;
        self->field_28 = b2;
        self->field_2c = c2;
        MTX_MultVec33(&vec, &src->mtx, &self->field_3c);
    }

    VEC_Add((int *)&self->field_24, (int *)&self->field_48, (int *)&self->field_24);
    VEC_Add((int *)&self->field_30, (int *)&self->field_48, (int *)&self->field_30);
}

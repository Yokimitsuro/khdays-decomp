typedef int fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

extern void VEC_Subtract(int *a, int *b, int *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

typedef struct {
    char pad[0x7c];
    VecFx32 f7c;
    VecFx32 f88;
} Self;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

int func_ov107_020c9568(Self *self, VecFx32 *other)
{
    VecFx32 diff;
    fx32 mag;
    fx32 dot;

    VEC_Subtract((int *)other, (int *)&self->f88, (int *)&diff);
    mag = VEC_Mag(&diff);
    dot = VEC_DotProduct(&diff, &self->f7c);
    return dot < FX_Mul(mag, 0x800);
}

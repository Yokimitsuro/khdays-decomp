typedef int fx32;
typedef struct { fx32 x, y, z; } Vec;

extern void VEC_Subtract(const Vec *a, const Vec *b, Vec *dst);
extern fx32 VEC_DotProduct(const Vec *a, const Vec *b);
extern fx32 FX_Sqrt(fx32 x);
extern void func_01ffa724(fx32 a, const Vec *b, void *c);

#define FX_MUL(a, b) ((fx32)(((long long)(a) * (long long)(b) + 0x800) >> 12))

int func_01ffe3c8(const Vec *a, const Vec *b, const Vec *c, fx32 d, void *e)
{
    Vec diff;
    fx32 dot;
    fx32 disc;

    VEC_Subtract(a, c, &diff);
    dot = VEC_DotProduct(&diff, b);
    disc = FX_MUL(d, d) + (FX_MUL(dot, dot) - VEC_DotProduct(&diff, &diff));
    if (disc < 0) return 0;
    func_01ffa724(FX_Sqrt(disc) - dot, b, e);
    return 1;
}

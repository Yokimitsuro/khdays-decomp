typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Quat {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quat;

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

extern void VEC_Add(int *a, int *b, int *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int FX_Sqrt(int x);
extern long long func_01ff8a50(int x);

/*
 * Shortest-arc quaternion from `fwd` to `dir`: half = normalize(fwd + dir),
 * out->w = dot(fwd, half), out->xyz = cross(fwd, half). When fwd and dir are
 * (near) opposite, half collapses and the dot is zero; in that degenerate
 * case builds a 180-degree quaternion around whichever axis perpendicular to
 * fwd is best conditioned (the one using the two largest-magnitude components).
 */
void func_0202ed60(Quat *out, VecFx32 *fwd, VecFx32 *dir)
{
    VecFx32 half;
    fx32 w;

    VEC_Add((int *)fwd, (int *)dir, (int *)&half);
    func_01ff8d18(&half, &half);

    w = VEC_DotProduct(fwd, &half);
    out->w = w;

    if (w != 0) {
        VecFx32 axis;

        VEC_CrossProduct(fwd, &half, &axis);
        out->x = axis.x;
        out->y = axis.y;
        out->z = axis.z;
        return;
    }

    {
        fx32 absY = fwd->y < 0 ? -fwd->y : fwd->y;
        fx32 absX = fwd->x < 0 ? -fwd->x : fwd->x;

        if (absX >= absY) {
            long long recip = func_01ff8a50(FX_Sqrt(FX_Mul(fwd->x, fwd->x) + FX_Mul(fwd->y, fwd->y)));

            out->x = -(fx32)((recip * fwd->z + 0x80000000LL) >> 32);
            out->y = 0;
            out->z = (fx32)((recip * fwd->x + 0x80000000LL) >> 32);
        } else {
            long long recip = func_01ff8a50(FX_Sqrt(FX_Mul(fwd->y, fwd->y) + FX_Mul(fwd->z, fwd->z)));

            out->x = 0;
            out->y = (fx32)((recip * fwd->z + 0x80000000LL) >> 32);
            out->z = -(fx32)((recip * fwd->y + 0x80000000LL) >> 32);
        }
    }
}

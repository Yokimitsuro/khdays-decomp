/* func_020372cc -- squared distance from a point to a disc, MAIN. The point's offset from the disc
 * centre is split into its height along the normal (+0x24) and the radial part in the disc plane. A
 * filled disc (+0x34 non-zero) is at height^2 away when the radial part lies within the radius (+0x30);
 * otherwise -- and always for a bare ring -- the nearest point is on the rim: the radial direction is
 * scaled to the radius (FX_Sqrt, the fx64c divider, FX_Mul32x64c) and the squared distance to that
 * rim point is returned. A point on the ring's axis is radius^2 + height^2 away. */
typedef int fx32;
typedef long long s64;
typedef s64 fx64;
typedef s64 fx64c;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct Disc {
    VecFx32 centre;                     /* +0x00 */
    char pad0c[0x24 - 0x0c];
    VecFx32 normal;                     /* +0x24 */
    fx32 radius;                        /* +0x30 */
    int filled;                         /* +0x34 */
} Disc;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *pDest);
extern fx32 FX_Sqrt(fx32 x);
extern fx64c func_01ff8a14(fx32 numer, fx32 denom);     /* FX_DivFx64c */

static inline fx32 FX_Mul(fx32 v1, fx32 v2)
{
    return (fx32)(((fx64)v1 * v2 + 0x800LL) >> 12);
}

static inline fx32 FX_Mul32x64c(fx32 v32, fx64c v64c)
{
    fx64 tmp = v64c * v32 + 0x80000000LL;

    return (fx32)(tmp >> 32);
}

#define VEC_MAG_SQ(v) ((fx32)(((fx64)(v).x * (v).x + (fx64)(v).y * (v).y + (fx64)(v).z * (v).z + 0x800) >> 12))

fx32 func_020372cc(const VecFx32 *p, const Disc *disc)
{
    VecFx32 d;
    VecFx32 r;
    VecFx32 c;
    VecFx32 e;
    VecFx32 diffA;
    VecFx32 diffB;
    fx32 h;
    fx32 rr;
    fx64c k;

    VEC_Subtract(p, &disc->centre, &d);
    h = VEC_DotProduct(&d, &disc->normal);
    VEC_MultAdd(-h, &disc->normal, &d, &r);
    rr = VEC_MAG_SQ(r);
    if (disc->filled) {
        if (rr <= FX_Mul(disc->radius, disc->radius)) {
            VEC_Add(&disc->centre, &r, &c);
            return FX_Mul(h, h);
        }
        k = func_01ff8a14(disc->radius, FX_Sqrt(rr));
        r.x = FX_Mul32x64c(r.x, k);
        r.y = FX_Mul32x64c(r.y, k);
        r.z = FX_Mul32x64c(r.z, k);
        VEC_Add(&disc->centre, &r, &c);
        VEC_Subtract(p, &c, &diffA);
        return VEC_MAG_SQ(diffA);
    }
    if (rr >= 2) {
        k = func_01ff8a14(disc->radius, FX_Sqrt(rr));
        e.x = FX_Mul32x64c(r.x, k);
        e.y = FX_Mul32x64c(r.y, k);
        e.z = FX_Mul32x64c(r.z, k);
        VEC_Add(&disc->centre, &e, &c);
        VEC_Subtract(p, &c, &diffB);
        return VEC_MAG_SQ(diffB);
    }
    return FX_Mul(disc->radius, disc->radius) + FX_Mul(h, h);
}

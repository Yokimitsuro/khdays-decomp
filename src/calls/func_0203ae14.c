/* func_0203ae14 -- squared distance from a point to a triangle, MAIN. Eberly's (Magic Software)
 * point-triangle distance in fixed point: the triangle is tri[0] + s*(tri[1]-tri[0]) + t*(tri[2]-tri[0])
 * and the closest point's s and t are returned as 32.32 fixed point (fx64c) through pS / pT when
 * those are not null. The seven regions of the (s, t) plane are handled as in the original; the
 * result is the absolute value of the squared distance. Region 3 (s < 0 <= t) computes its distance
 * with the unnormalised t instead of the clamped one, as in the ROM. The determinant's absolute
 * value is a ternary: the if form spills it after the 64-bit sign-extended pairs instead of first. */
typedef int fx32;
typedef long long fx64;
typedef long long fx64c;

typedef struct { fx32 x, y, z; } VecFx32;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx64c func_01ff8a14(fx32 numer, fx32 denom);     /* FX_DivFx64c */

#define FX64C_ONE ((fx64c)1 << 32)

static inline fx32 FX_Mul32x64c(fx32 v32, fx64c v64c)
{
    fx64c tmp = v64c * v32 + 0x80000000LL;

    return (fx32)(tmp >> 32);
}

static inline fx32 VEC_SquaredLength(const VecFx32 *v)
{
    return (fx32)(((fx64)v->x * v->x + (fx64)v->y * v->y + (fx64)v->z * v->z + 0x800) >> 12);
}

fx32 func_0203ae14(const VecFx32 *p, const VecFx32 **tri, fx64c *pS, fx64c *pT)
{
    VecFx32 diff;
    VecFx32 edge0;
    VecFx32 edge1;
    fx32 a00;
    fx32 a01;
    fx32 a11;
    fx32 b0;
    fx32 b1;
    fx32 c;
    fx32 det;
    fx32 fS;
    fx32 fT;
    fx32 sqr;
    fx64c s;
    fx64c t;

    VEC_Subtract(tri[0], p, &diff);
    VEC_Subtract(tri[1], tri[0], &edge0);
    VEC_Subtract(tri[2], tri[0], &edge1);
    a00 = VEC_SquaredLength(&edge0);
    a01 = VEC_DotProduct(&edge0, &edge1);
    a11 = VEC_SquaredLength(&edge1);
    b0 = VEC_DotProduct(&diff, &edge0);
    b1 = VEC_DotProduct(&diff, &edge1);
    c = VEC_SquaredLength(&diff);
    det = (fx32)(((fx64)a00 * a11 - (fx64)a01 * a01 + 0x800) >> 12);
    det = det < 0 ? -det : det;
    fS = (fx32)(((fx64)a01 * b1 - (fx64)a11 * b0 + 0x800) >> 12);
    fT = (fx32)(((fx64)a01 * b0 - (fx64)a00 * b1 + 0x800) >> 12);

    if (fS + fT <= det) {
        if (fS < 0) {
            if (fT < 0) {
                /* region 4 */
                if (b0 < 0) {
                    t = 0;
                    if (-b0 >= a00) {
                        s = FX64C_ONE;
                        sqr = a00 + 2 * b0 + c;
                    } else {
                        s = -func_01ff8a14(b0, a00);
                        sqr = FX_Mul32x64c(b0, s) + c;
                    }
                } else {
                    s = 0;
                    if (b1 >= 0) {
                        t = 0;
                        sqr = c;
                    } else if (-b1 >= a11) {
                        t = FX64C_ONE;
                        sqr = a11 + 2 * b1 + c;
                    } else {
                        t = -func_01ff8a14(b1, a11);
                        sqr = FX_Mul32x64c(b1, t) + c;
                    }
                }
            } else {
                /* region 3 */
                s = 0;
                if (b1 >= 0) {
                    t = 0;
                    sqr = c;
                } else if (-b1 >= a11) {
                    t = FX64C_ONE;
                    sqr = a11 + 2 * b1 + c;
                } else {
                    t = -func_01ff8a14(b1, a11);
                    sqr = FX_Mul32x64c(b1, fT) + c;
                }
            }
        } else if (fT < 0) {
            /* region 5 */
            t = 0;
            if (b0 >= 0) {
                s = 0;
                sqr = c;
            } else if (-b0 >= a00) {
                s = FX64C_ONE;
                sqr = a00 + 2 * b0 + c;
            } else {
                s = -func_01ff8a14(b0, a00);
                sqr = FX_Mul32x64c(b0, s) + c;
            }
        } else {
            /* region 0 */
            s = func_01ff8a14(fS, det);
            t = func_01ff8a14(fT, det);
            sqr = FX_Mul32x64c(FX_Mul32x64c(a00, s) + FX_Mul32x64c(a01, t) + 2 * b0, s) +
                  FX_Mul32x64c(FX_Mul32x64c(a01, s) + FX_Mul32x64c(a11, t) + 2 * b1, t) + c;
        }
    } else {
        fx32 tmp0;
        fx32 tmp1;
        fx32 numer;
        fx32 denom;

        if (fS < 0) {
            /* region 2 */
            tmp0 = a01 + b0;
            tmp1 = a11 + b1;
            if (tmp1 > tmp0) {
                numer = tmp1 - tmp0;
                denom = a00 - 2 * a01 + a11;
                if (numer >= denom) {
                    s = FX64C_ONE;
                    t = 0;
                    sqr = a00 + 2 * b0 + c;
                } else {
                    s = func_01ff8a14(numer, denom);
                    t = FX64C_ONE - s;
                    sqr = FX_Mul32x64c(FX_Mul32x64c(a00, s) + FX_Mul32x64c(a01, t) + 2 * b0, s) +
                          FX_Mul32x64c(FX_Mul32x64c(a01, s) + FX_Mul32x64c(a11, t) + 2 * b1, t) + c;
                }
            } else {
                s = 0;
                if (tmp1 <= 0) {
                    t = FX64C_ONE;
                    sqr = a11 + 2 * b1 + c;
                } else if (b1 >= 0) {
                    t = 0;
                    sqr = c;
                } else {
                    t = -func_01ff8a14(b1, a11);
                    sqr = FX_Mul32x64c(b1, t) + c;
                }
            }
        } else if (fT < 0) {
            /* region 6 */
            tmp0 = a01 + b1;
            tmp1 = a00 + b0;
            if (tmp1 > tmp0) {
                numer = tmp1 - tmp0;
                denom = a00 - 2 * a01 + a11;
                if (numer >= denom) {
                    t = FX64C_ONE;
                    s = 0;
                    sqr = a11 + 2 * b1 + c;
                } else {
                    t = func_01ff8a14(numer, denom);
                    s = FX64C_ONE - t;
                    sqr = FX_Mul32x64c(FX_Mul32x64c(a00, s) + FX_Mul32x64c(a01, t) + 2 * b0, s) +
                          FX_Mul32x64c(FX_Mul32x64c(a01, s) + FX_Mul32x64c(a11, t) + 2 * b1, t) + c;
                }
            } else {
                t = 0;
                if (tmp1 <= 0) {
                    s = FX64C_ONE;
                    sqr = a00 + 2 * b0 + c;
                } else if (b0 >= 0) {
                    s = 0;
                    sqr = c;
                } else {
                    s = -func_01ff8a14(b0, a00);
                    sqr = FX_Mul32x64c(b0, s) + c;
                }
            }
        } else {
            /* region 1 */
            numer = a11 + b1 - a01 - b0;
            if (numer <= 0) {
                s = 0;
                t = FX64C_ONE;
                sqr = a11 + 2 * b1 + c;
            } else {
                denom = a00 - 2 * a01 + a11;
                if (numer >= denom) {
                    s = FX64C_ONE;
                    t = 0;
                    sqr = a00 + 2 * b0 + c;
                } else {
                    s = func_01ff8a14(numer, denom);
                    t = FX64C_ONE - s;
                    sqr = FX_Mul32x64c(FX_Mul32x64c(a00, s) + FX_Mul32x64c(a01, t) + 2 * b0, s) +
                          FX_Mul32x64c(FX_Mul32x64c(a01, s) + FX_Mul32x64c(a11, t) + 2 * b1, t) + c;
                }
            }
        }
    }

    if (pS != 0) {
        *pS = s;
    }
    if (pT != 0) {
        *pT = t;
    }
    if (sqr < 0) {
        sqr = -sqr;
    }
    return sqr;
}

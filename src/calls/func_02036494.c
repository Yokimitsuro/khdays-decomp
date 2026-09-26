/* func_02036494 -- squared distance between two segments, MAIN. Eberly's (Magic Software) segment-
 * segment distance in fixed point. A segment is an origin, a unit direction and a length; the
 * closest points' parameters s (on seg0) and t (on seg1) are returned in 32.32 fixed point (fx64c)
 * through pS / pT when those are not null. The determinant and the unnormalised s and t are 32.32
 * values (the products shifted up by 8); below a determinant of 0x30000 the segments count as
 * parallel. The nine regions and the parallel cases follow the original; two spots differ from it
 * as in the ROM: region 2's last case adds 2 * (b0 + c) and the acute parallel case multiplies
 * (a11 + 2 * b1) by t twice. The result is the absolute value of the squared distance.
 * Codegen: as in the original, fS holds the unnormalised s and then s itself (Eberly's fS *= fInvDet),
 * and the determinant's absolute value goes through the FX64_Abs inline. */
typedef int fx32;
typedef long long fx64;
typedef long long fx64c;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct Segment3 {
    VecFx32 origin;                     /* +0x00 */
    VecFx32 dir;                        /* +0x0c */
    fx32 length;                        /* +0x18 */
} Segment3;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa724(fx32 scale, const VecFx32 *v, VecFx32 *out);  /* scale a vector */
extern fx64c func_01ff8a14(fx32 numer, fx32 denom);                     /* FX_DivFx64c */
extern fx64 func_020201b8(fx64 numer, fx64 denom);                      /* 64-bit signed divide */

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

static inline fx64 FX64_Abs(fx64 x)
{
    if (x < 0) {
        x = -x;
    }
    return x;
}

fx32 func_02036494(const Segment3 *seg0, const Segment3 *seg1, fx64c *pS, fx64c *pT)
{
    VecFx32 d0;
    VecFx32 d1;
    VecFx32 diff;
    fx32 a00;
    fx32 a01;
    fx32 a11;
    fx32 b0;
    fx32 b1;
    fx32 c;
    fx32 tmp;
    fx32 sqr;
    fx64c det;
    fx64c fS;
    fx64c fT;
    fx64c t;

    func_01ffa724(seg0->length, &seg0->dir, &d0);
    func_01ffa724(seg1->length, &seg1->dir, &d1);
    VEC_Subtract(&seg0->origin, &seg1->origin, &diff);
    a00 = VEC_SquaredLength(&d0);
    a01 = -VEC_DotProduct(&d0, &d1);
    a11 = VEC_SquaredLength(&d1);
    b0 = VEC_DotProduct(&diff, &d0);
    c = VEC_SquaredLength(&diff);
    det = FX64_Abs(((fx64)a00 * a11 - (fx64)a01 * a01) << 8);

    if (det >= 0x30000) {
        /* the segments are not parallel */
        b1 = -VEC_DotProduct(&diff, &d1);
        fS = ((fx64)a01 * b1 - (fx64)a11 * b0) << 8;
        fT = ((fx64)a01 * b0 - (fx64)a00 * b1) << 8;

        if (fS >= 0) {
            if (fS <= det) {
                if (fT >= 0) {
                    if (fT <= det) {
                        /* region 0 (interior) */
                        fS = func_020201b8(fS << 16, det) << 16;
                        t = func_020201b8(fT << 16, det) << 16;
                        sqr = FX_Mul32x64c(FX_Mul32x64c(a00, fS) + FX_Mul32x64c(a01, t) + 2 * b0, fS) +
                              FX_Mul32x64c(FX_Mul32x64c(a01, fS) + FX_Mul32x64c(a11, t) + 2 * b1, t) + c;
                    } else {
                        /* region 3 (side) */
                        t = FX64C_ONE;
                        tmp = a01 + b0;
                        if (tmp >= 0) {
                            fS = 0;
                            sqr = a11 + 2 * b1 + c;
                        } else if (-tmp >= a00) {
                            fS = FX64C_ONE;
                            sqr = a00 + a11 + c + 2 * (b1 + tmp);
                        } else {
                            fS = -func_01ff8a14(tmp, a00);
                            sqr = FX_Mul32x64c(tmp, fS) + a11 + 2 * b1 + c;
                        }
                    }
                } else {
                    /* region 7 (side) */
                    t = 0;
                    if (b0 >= 0) {
                        fS = 0;
                        sqr = c;
                    } else if (-b0 >= a00) {
                        fS = FX64C_ONE;
                        sqr = a00 + 2 * b0 + c;
                    } else {
                        fS = -func_01ff8a14(b0, a00);
                        sqr = FX_Mul32x64c(b0, fS) + c;
                    }
                }
            } else {
                if (fT >= 0) {
                    if (fT <= det) {
                        /* region 1 (side) */
                        fS = FX64C_ONE;
                        tmp = a01 + b1;
                        if (tmp >= 0) {
                            t = 0;
                            sqr = a00 + 2 * b0 + c;
                        } else if (-tmp >= a11) {
                            t = FX64C_ONE;
                            sqr = a00 + a11 + c + 2 * (b0 + tmp);
                        } else {
                            t = -func_01ff8a14(tmp, a11);
                            sqr = FX_Mul32x64c(tmp, t) + a00 + 2 * b0 + c;
                        }
                    } else {
                        /* region 2 (corner) */
                        tmp = a01 + b0;
                        if (-tmp <= a00) {
                            t = FX64C_ONE;
                            if (tmp >= 0) {
                                fS = 0;
                                sqr = a11 + 2 * b1 + c;
                            } else {
                                fS = -func_01ff8a14(tmp, a00);
                                sqr = FX_Mul32x64c(tmp, fS) + a11 + 2 * b1 + c;
                            }
                        } else {
                            fS = FX64C_ONE;
                            tmp = a01 + b1;
                            if (tmp >= 0) {
                                t = 0;
                                sqr = a00 + 2 * b0 + c;
                            } else if (-tmp >= a11) {
                                t = FX64C_ONE;
                                sqr = a00 + a11 + c + 2 * (b0 + tmp);
                            } else {
                                t = -func_01ff8a14(tmp, a11);
                                sqr = FX_Mul32x64c(tmp, t) + a00 + 2 * (b0 + c);
                            }
                        }
                    }
                } else {
                    /* region 8 (corner) */
                    if (-b0 < a00) {
                        t = 0;
                        if (b0 >= 0) {
                            fS = 0;
                            sqr = c;
                        } else {
                            fS = -func_01ff8a14(b0, a00);
                            sqr = FX_Mul32x64c(b0, fS) + c;
                        }
                    } else {
                        fS = FX64C_ONE;
                        tmp = a01 + b1;
                        if (tmp >= 0) {
                            t = 0;
                            sqr = a00 + 2 * b0 + c;
                        } else if (-tmp >= a11) {
                            t = FX64C_ONE;
                            sqr = a00 + a11 + c + 2 * (b0 + tmp);
                        } else {
                            t = -func_01ff8a14(tmp, a11);
                            sqr = FX_Mul32x64c(tmp, t) + 2 * b0 + c;
                        }
                    }
                }
            }
        } else {
            if (fT >= 0) {
                if (fT <= det) {
                    /* region 5 (side) */
                    fS = 0;
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
                } else {
                    /* region 4 (corner) */
                    tmp = a01 + b0;
                    if (tmp < 0) {
                        t = FX64C_ONE;
                        if (-tmp >= a00) {
                            fS = FX64C_ONE;
                            sqr = a00 + a11 + c + 2 * (b1 + tmp);
                        } else {
                            fS = -func_01ff8a14(tmp, a00);
                            sqr = FX_Mul32x64c(tmp, fS) + a11 + 2 * b1 + c;
                        }
                    } else {
                        fS = 0;
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
                }
            } else {
                /* region 6 (corner) */
                if (b0 < 0) {
                    t = 0;
                    if (-b0 >= a00) {
                        fS = FX64C_ONE;
                        sqr = a00 + 2 * b0 + c;
                    } else {
                        fS = -func_01ff8a14(b0, a00);
                        sqr = FX_Mul32x64c(b0, fS) + c;
                    }
                } else {
                    fS = 0;
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
            }
        }
    } else {
        /* the segments are parallel */
        if (a01 > 0) {
            /* the directions form an obtuse angle */
            if (b0 >= 0) {
                fS = 0;
                t = 0;
                sqr = c;
            } else if (-b0 <= a00) {
                fS = -func_01ff8a14(b0, a00);
                t = 0;
                sqr = FX_Mul32x64c(b0, fS) + c;
            } else {
                b1 = -VEC_DotProduct(&diff, &d1);
                fS = FX64C_ONE;
                tmp = a00 + b0;
                if (-tmp >= a01) {
                    t = FX64C_ONE;
                    sqr = a00 + a11 + c + 2 * (a01 + b0 + b1);
                } else {
                    t = -func_01ff8a14(tmp, a01);
                    sqr = a00 + 2 * b0 + c + FX_Mul32x64c(FX_Mul32x64c(a11, t) + 2 * (a01 + b1), t);
                }
            }
        } else {
            /* the directions form an acute angle */
            if (-b0 >= a00) {
                fS = FX64C_ONE;
                t = 0;
                sqr = a00 + 2 * b0 + c;
            } else if (b0 <= 0) {
                fS = -func_01ff8a14(b0, a00);
                t = 0;
                sqr = FX_Mul32x64c(b0, fS) + c;
            } else {
                b1 = -VEC_DotProduct(&diff, &d1);
                fS = 0;
                if (b0 >= -a01) {
                    t = FX64C_ONE;
                    sqr = a11 + 2 * b1 + c;
                } else {
                    t = -func_01ff8a14(b0, a01);
                    sqr = c + FX_Mul32x64c(FX_Mul32x64c(a11 + 2 * b1, t), t);
                }
            }
        }
    }

    if (pS != 0) {
        *pS = fS;
    }
    if (pT != 0) {
        *pT = t;
    }
    if (sqr < 0) {
        sqr = -sqr;
    }
    return sqr;
}

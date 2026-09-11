/* func_0202ea48 -- convert a Q12 fixed-point 3x3 rotation matrix to a quaternion
 * (Shepperd's method). dst is {w, x, y, z}; m is row-major m[row][col].
 * When the trace is positive, w comes straight from the trace's square root and
 * x/y/z come from the three off-diagonal antisymmetric differences. Otherwise the
 * largest diagonal entry picks which axis (i) gets the square root instead, with
 * j/k walked from data_020420f4 (the {1,2,0} cyclic-successor table), and w is
 * built from the remaining antisymmetric difference.
 * The reciprocal (0x800 / s) comes back as a 64-bit Q32 factor from
 * func_01ff8a14; each product is widened to 64 bits, rounded with 0x80000000,
 * and the high word taken -- the same idiom as func_ov127_020cc5b8. */
typedef signed int s32;
typedef signed long long s64;

extern s32 FX_Sqrt(s32 x);
extern s64 func_01ff8a14(s32 num, s32 denom);
extern unsigned char data_020420f4[3];

void func_0202ea48(s32 *dst, s32 m[3][3])
{
    s32 trace;
    s32 s;
    s64 inv;

    trace = m[0][0] + m[1][1] + m[2][2];

    if (trace > 0) {
        s = FX_Sqrt(trace + 0x1000);
        dst[0] = s >> 1;

        inv = func_01ff8a14(0x800, s);
        dst[1] = (s32)((inv * (s64)(m[1][2] - m[2][1]) + 0x80000000LL) >> 32);
        dst[2] = (s32)((inv * (s64)(m[2][0] - m[0][2]) + 0x80000000LL) >> 32);
        dst[3] = (s32)((inv * (s64)(m[0][1] - m[1][0]) + 0x80000000LL) >> 32);
    } else {
        s32 i, j, k;
        s32 *q[3];

        i = 0;
        if (m[1][1] > m[0][0]) {
            i = 1;
        }
        if (m[2][2] > m[i][i]) {
            i = 2;
        }
        j = data_020420f4[i];
        k = data_020420f4[j];

        s = FX_Sqrt(m[i][i] - m[j][j] - m[k][k] + 0x1000);

        q[0] = &dst[1];
        q[1] = &dst[2];
        q[2] = &dst[3];
        *q[i] = s >> 1;

        inv = func_01ff8a14(0x800, s);
        dst[0] = (s32)((inv * (s64)(m[j][k] - m[k][j]) + 0x80000000LL) >> 32);
        *q[j] = (s32)((inv * (s64)(m[i][j] + m[j][i]) + 0x80000000LL) >> 32);
        *q[k] = (s32)((inv * (s64)(m[i][k] + m[k][i]) + 0x80000000LL) >> 32);
    }
}

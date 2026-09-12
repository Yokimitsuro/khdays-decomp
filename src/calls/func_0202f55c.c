typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quat;

extern int func_0202f3b4(int *a, int *b);
extern int FX_Sqrt(int x);
extern int func_020050b4(int x, int z);
extern long long func_01ff8a50(int x);
extern void func_0202ea34(int *p, int a, int b, int c, int d);
extern void func_0202f110(unsigned int *out, int *v, int scalar);
extern void func_0202ef10(int *out, int *a, int *b);
extern short data_0203d210[];

/*
 * Quaternion slerp: out = slerp(a, b, t), t in Q12 (0x1000 = 1.0).
 *
 * cos = dot(a,b) (Q12). If cos < 0, negate a and cos (shortest path).
 * Near-identical (cos ~= +1): fall back to a plain lerp, weights (1-t, t).
 * Near-antipodal (cos ~= -1): no defined rotation axis, so build an
 * arbitrary orthogonal quaternion in place of b (w,-z,y,-x) and blend
 * with t*PI run through the sin table directly (no divide by sin(omega),
 * which would be ~0).
 * Otherwise: omega = atan2(sqrt(1-cos^2), cos); scale by
 * sin((1-t)*omega)/sin(omega) and sin(t*omega)/sin(omega), each looked up
 * from the Q12 sin table and divided via the hardware reciprocal.
 */
void func_0202f55c(Quat *out, int t, Quat *a, Quat *b)
{
    Quat qaS;
    Quat qbS;
    int dot;
    int sum;
    int diff;
    int scaleA;
    int scaleB;
    int omega;
    long long recip;
    int idxOmega;
    int idxA;
    int idxB;
    int sOmega;
    int sA;
    int sB;
    int angleA;
    int angleB;
    int angleC;
    int idxC;
    int sC;

    qaS = *a;
    qbS = *b;

    dot = func_0202f3b4((int *)&qaS, (int *)&qbS);
    if (dot < 0) {
        qaS.x = -qaS.x;
        qaS.y = -qaS.y;
        qaS.z = -qaS.z;
        qaS.w = -qaS.w;
        dot = -dot;
    }

    /*
     * The three cases below (near-antipodal, near-identical, general slerp)
     * are mutually exclusive and the compiler places the two special cases
     * out of line after the general path; the gotos below reproduce that
     * layout (plain if/else re-shuffles the branches and no longer matches).
     */
    sum = dot + 0x1000;
    if (sum <= 0xcc) {
        goto near_opposite;
    }
    diff = 0x1000 - dot;
    if (diff < 0xcc) {
        goto near_parallel;
    }

    if (dot <= -0x1000) {
        goto omega_pi;
    }
    if (dot >= 0x1000) {
        omega = 0;
    } else {
        int sinSq = (int)(((long long)diff * sum + 0x800) >> 0xc);
        int sinOmega = FX_Sqrt(sinSq);
        omega = func_020050b4(sinOmega, dot);
    }
    goto omega_done;

omega_pi:
    omega = 0x3244;

omega_done:
    idxOmega = (unsigned short)(((long long)omega * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    sOmega = data_0203d210[idxOmega * 2];
    recip = func_01ff8a50(sOmega);

    angleA = (int)(((long long)omega * (0x1000 - t) + 0x800) >> 0xc);
    idxA = (unsigned short)(((long long)angleA * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    sA = data_0203d210[idxA * 2];
    scaleA = (int)((recip * sA + 0x80000000LL) >> 32);

    angleB = (int)(((long long)omega * t + 0x800) >> 0xc);
    idxB = (unsigned short)(((long long)angleB * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    sB = data_0203d210[idxB * 2];
    scaleB = (int)((recip * sB + 0x80000000LL) >> 32);
    goto blend;

near_parallel:
    scaleA = 0x1000 - t;
    scaleB = t;
    goto blend;

near_opposite:
    func_0202ea34((int *)&qbS, qaS.w, -qaS.z, qaS.y, -qaS.x);

    angleC = (int)(((long long)t * 0x3244 + 0x800) >> 0xc);
    idxC = (unsigned short)(((long long)angleC * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    sC = data_0203d210[idxC * 2];
    scaleA = sC;
    scaleB = 0x1000 - sC;

blend:
    func_0202f110((unsigned int *)&qaS, (int *)&qaS, scaleA);
    func_0202f110((unsigned int *)&qbS, (int *)&qbS, scaleB);
    func_0202ef10((int *)out, (int *)&qaS, (int *)&qbS);
}

/* Finds the nearest target (queues action 2 when none), returns the horizontal gap minus both
 * radii, stores the heading (+0x58) and direction. */

extern int Ov107_FindNearestObject();
extern int VEC_Subtract();
extern int VEC_Normalize();
extern short FX_Atan2();

struct s3 {
    int a;
    int b;
    int c;
};

int Ov227_MeasureTargetGap(int *arg0, struct s3 *out) {
    int **r4;
    int *r3;
    int r6;
    struct s3 v;

    r4 = (int **)arg0[1];
    r3 = (int *)(*r4)[250];
    if (r3 == 0) {
        (*r4)[250] = Ov107_FindNearestObject(*r4, 0);
        r3 = (int *)(*r4)[250];
        if (r3 == 0) {
            *((char *)*r4 + 0x1c7) = 2;
            return -1;
        }
    }

    VEC_Subtract((int)r3 + 0x190, r4[2], &v);
    v.b = 0;
    r6 = VEC_Normalize(&v, &v, 0);
    r6 = r6 - (((int *)(*r4)[250])[32] + (*r4)[32]);
    if (r6 < 0) {
        r6 = 0;
    }
    ((int *)r4)[22] = FX_Atan2(v.a, v.c);
    if (out != 0) {
        *out = v;
    }
    return r6;
}

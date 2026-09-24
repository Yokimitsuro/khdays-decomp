/* Closest approach between a swept sphere (capsule: start +0, direction +0xc, length +0x18) and
 * `other`: the segment test (func_02039428) gives the parameter along the capsule; outside
 * [0, length] the end point (start or start + dir * length) is tested instead (func_02037188) and
 * the parameter clamped. The parameter and the three results the tests report are stored through
 * the optional out pointers; the test's own result is returned. */
typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    VecFx32 pos;        /* 0x00 */
    VecFx32 dir;        /* 0x0c */
    int length;         /* 0x18 */
    int radius;         /* 0x1c */
} Capsule;

typedef struct {
    VecFx32 start;
    VecFx32 delta;
} Segment;

extern void func_01ffa724(int scale, const VecFx32 *v, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int func_02039428(Segment *seg, void *other, int *t, int *a, int *b, int *c);
extern int func_02037188(VecFx32 *point, void *other, int *a, int *b, int *c);

int func_02039700(Capsule *cap, void *other, int *outT, int *outA, int *outB, int *outC)
{
    Segment seg;
    VecFx32 end;
    int t;
    int a;
    int b;
    int c;
    int result;

    seg.start = cap->pos;
    func_01ffa724(cap->length, &cap->dir, &seg.delta);
    result = func_02039428(&seg, other, &t, &a, &b, &c);
    if (t >= 0) {
        if (t <= cap->length) {
            if (outT) {
                *outT = t;
            }
        } else {
            func_01ffa724(cap->length, &cap->dir, &end);
            VEC_Add(&cap->pos, &end, &end);
            result = func_02037188(&end, other, &a, &b, &c);
            if (outT) {
                *outT = cap->length;
            }
        }
    } else {
        result = func_02037188(&cap->pos, other, &a, &b, &c);
        if (outT) {
            *outT = 0;
        }
    }
    if (outA) {
        *outA = a;
    }
    if (outB) {
        *outB = b;
    }
    if (outC) {
        *outC = c;
    }
    return result;
}

/* Fire the shockwave once the wind-up passes 0xf78: measure the delta from the emitter to the
 * target, then walk the four sub-emitters at +0x3a4 and hand the shot to the first one whose
 * hw60 low bit is clear. Either way, once the busy byte clears, the action byte goes to 2 and a
 * fresh hold time is rolled between the bounds at +0x224/+0x228.
 *
 * Matched byte-exact 2026-07-23, first compile. The loop counter is a `char`, which is what
 * produces the `lsl #0x18 ; asr #0x18` round-trip on every increment.
 *
 * One of three byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *a, void *b);
extern void func_ov192_020d3bf8(int obj, void *p, VecFx32 *v);
extern int func_02023eb4(int n);
extern void func_0203c634(void *node, int idx, void *cb);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov192_020d3190(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    VecFx32 v;
    char i;
    int lo;
    int d;

    state[0xb] = state[0xb] + *(int *)((int)owner + 0x2c);
    if (*(unsigned char *)((int)state + 0x38) == 0 && state[0xb] >= 0xf78) {
        *(unsigned char *)((int)state + 0x38) = 1;
        VEC_Subtract((void *)(state[6] + 0x74), (void *)(*(int *)(state[0] + 0x39c) + 0x14), &v);
        func_01ff8d18(&v, &v);
        i = 0;
        do {
            if ((((struct hw60 *)(((int *)*(int *)(state[0] + 0x3a4))[i] + 0x60))->lo & 1) == 0) {
                func_ov192_020d3bf8(((int *)*(int *)(state[0] + 0x3a4))[i],
                                    (void *)(*(int *)(state[0] + 0x39c) + 0x14), &v);
                break;
            }
            i = i + 1;
        } while (i < 4);
    }
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    *(char *)(state[0] + 0x1c7) = 2;
    lo = *(int *)(state[0] + 0x224);
    d = *(int *)(state[0] + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    state[0xd] = lo + func_02023eb4(d + 1);
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}

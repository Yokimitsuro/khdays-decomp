/* Begin the approach: with no target, roll a fresh hold time between the bounds at +0x224/+0x228
 * and drop to action 2. With one, play animation 0xc, latch the heading to it with FX_Atan2 into
 * both the current and the goal slots, convert the owner's per-frame delta into the per-second
 * budget at state[8], set 0x40 in the hw60 high byte, clear the travel accumulator and the byte
 * at state+0x50, and start event 0x131 on the sub-object.
 *
 * Matched byte-exact 2026-07-23, first compile. The `* 30 / 30` is genuine: the ROM multiplies
 * by 30 and then divides by 30 through the textbook signed magic (0x88888889, shift 4, with the
 * add correction), which is not a no-op on the negative side.
 *
 * One of four byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern int func_02023eb4(int n);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_ov184_020d3a20(void);

void func_ov184_020d38fc(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int lo;
    int d;
    int h;

    if (state[4] == 0) {
        lo = *(int *)(state[0] + 0x224);
        d = *(int *)(state[0] + 0x228) - lo;
        if (d < 0) {
            d = -d;
        }
        state[0x1d] = lo + func_02023eb4(d + 1);
        *(char *)(state[0] + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(state[0], 0xc, 0);
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], &v);
    h = func_020050b4(v.x, v.z);
    state[6] = h;
    state[5] = h;
    state[8] = *(int *)(node[0] + 0x2c) * 0x1e / 0x1e;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    state[7] = 0;
    *(unsigned char *)((int)state + 0x50) = 0;
    func_ov107_020c5af8(state[0], 0x131, 7, state[1]);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov184_020d3a20);
}

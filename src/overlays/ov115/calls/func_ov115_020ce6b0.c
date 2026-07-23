/* Steer the circling attack. While the lock flag at state[0x22] is clear the heading at
 * state[9] is nudged: with a live distance reading it moves by (0x2800 - dist) / 30, and with
 * the sentinel 0x7fffffff it just steps 0x200 towards the sub-object's own heading. The frame
 * is then rebuilt from the sub-object's transform, the delta to the target is measured, the
 * travel accumulator advances, and once the busy byte clears the action becomes 2.
 *
 * Matched byte-exact 2026-07-23. Two things beyond the arithmetic: `sub` has to be declared
 * BEFORE `state` to colour r4/r5 the way the ROM does, and the 0x24-byte matrix has to be
 * declared before the 3-word vector so the frame comes out as sp+0xc / sp+0. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { int m[9]; } MtxFx33;

extern void func_0203cd7c(void *out, void *a, int b, VecFx32 *c);
extern void func_0202ea48(void *dst, void *src);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *a, void *b);
extern void func_0203c634(void *node, int idx, void *cb);
extern VecFx32 data_02042264;

void func_ov115_020ce6b0(int *node) {
    int *sub;
    int *state = (int *)node[1];
    MtxFx33 m;
    VecFx32 d;

    sub = (int *)state[3];
    if (state[0x22] == 0) {
        if (state[0x11] != 0x7fffffff) {
            state[9] = state[9] + (0x2800 - state[0x11]) / 30;
        } else if (*(int *)((int)sub + 0x194) < state[9]) {
            state[9] = state[9] - 0x200;
        } else {
            state[9] = state[9] + 0x200;
        }
    }
    func_0203cd7c(&m, (void *)((int)sub + 0x74), state[2], &data_02042264);
    func_0202ea48(state + 0x1d, &m);
    VEC_Subtract((void *)((int)sub + 0x74), (void *)(*(int *)(state[0] + 0x390) + 0x14), &d);
    func_01ff8d18(&d, &d);
    state[0x12] = state[0x12] + *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(char *)(state[0] + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}

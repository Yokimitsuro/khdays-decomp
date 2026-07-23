/* Drive the dash: advance the travel accumulator by the owner's per-frame delta and, while it
 * is still within 0x7f8, re-issue the dash request with the number of steps scaled from how far
 * it has got (v * 0x3e66 / 0x7f8) plus the three canned direction vectors. Once the sub-object's
 * busy byte clears, switch to action 2 and drop the think callback.
 *
 * The request is ONE 0x38-byte struct built on the stack and passed by address; the three
 * globals are declared with the vector type so their copies come out as the ROM's ldm/stm pairs.
 * Matched byte-exact 2026-07-23, first compile. */
typedef struct { int x, y, z; } VecFx32;

typedef struct {
    VecFx32 aim;
    VecFx32 v0c;
    VecFx32 v18;
    VecFx32 v24;
    int nSteps;
    int bFlag;
} Ov214Params;

extern void func_ov214_020cce44(int *state, int kind, Ov214Params *p);
extern void func_0203c634(void *node, int idx, void *cb);
extern VecFx32 data_02042270;
extern VecFx32 data_02042258;
extern VecFx32 data_02042264;

void func_ov214_020cdcf0(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    Ov214Params p;

    state[0x14] = state[0x14] + *(int *)((int)owner + 0x2c);
    if (state[0x14] <= 0x7f8) {
        p.aim = *(VecFx32 *)(state + 0xe);
        p.nSteps = state[0x14] * 0x3e66 / 0x7f8;
        p.v0c = data_02042270;
        p.v18 = data_02042258;
        p.v24 = data_02042264;
        p.bFlag = 1;
        func_ov214_020cce44(state, 1, &p);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(char *)(state[0] + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}

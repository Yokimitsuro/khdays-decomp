/* Steer the sweep: ask the target tracker for the turn speed, rebuild the desired direction in
 * the object's own frame and scale it. Advance the travel accumulator by the owner's per-frame
 * delta and, the first time it passes 0x1000 (latched by bit 1 of the byte at state+0x51), fire
 * event 0x131 on the sub-object. Once the sub-object stops reporting busy, roll a fresh hold
 * time between the bounds at +0x224/+0x228 and drop to action 2.
 *
 * Matched byte-exact 2026-07-23, first compile. The latch is a bitfield struct, not `& 2`: the
 * bitfield read is the lsl #0x1e / lsrs #0x1f pair, and writing it back through the same struct
 * is what lets mwcc reuse the loaded byte for the `orr`.
 *
 * One of four byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020c9f48(int p, VecFx32 *out);
extern void func_0202f384(void *out, void *a, void *b);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern int func_02023eb4(int n);
extern void func_0203c634(void *node, int idx, void *cb);

struct Ov182Flags { unsigned char b0 : 1, b1 : 1; };

void func_ov182_020d0568(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int scale;
    struct Ov182Flags *fl;
    int lo;
    int d;

    scale = func_ov107_020c9f48(*(int *)(state[0] + 0x390), &v);
    func_0202f384((void *)(state + 0x15), (void *)(state[0] + 0xa0), &v);
    func_01ffa724(scale, (void *)(state + 0x15), (void *)(state + 0x15));
    state[0x1b] = state[0x1b] + *(int *)(node[0] + 0x2c);
    fl = (struct Ov182Flags *)((int)state + 0x51);
    if (fl->b1 == 0 && state[0x1b] >= 0x1000) {
        fl->b1 = 1;
        func_ov107_020c5af8(state[0], 0x131, 9, state[1]);
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    lo = *(int *)(state[0] + 0x224);
    d = *(int *)(state[0] + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    state[0x1d] = lo + func_02023eb4(d + 1);
    *(char *)(state[0] + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}

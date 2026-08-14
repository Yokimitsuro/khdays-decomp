/* Pick the approach heading for this enemy and arm the approach timer.
 *
 * Asks func_ov107_020cab14 for a target; with none it drops to sub-state 2 and
 * dispatches the empty slot. Otherwise it takes the flattened vector from the
 * state's position at +0x40 to the target's position at +0x74, normalises it, and
 * measures `gap` = that length minus both collision radii at +0x80. `gap` becomes a
 * Q12 ratio against the fixed 0xf000 reach:
 *
 *     t = clamp(FX_Inv(gap, 0xf000) * 2 - 0x1000, -0x1000, 0x1000)
 *
 * so t sweeps -1.0 .. +1.0 as the target goes from touching to a full reach away.
 * The scatter shrinks as t saturates: spread = 0x1000 - |t|, the roll is uniform in
 * [-spread, +spread], and FX_Mul against PI turns Q12 turns into Q12 radians. The
 * sign of t also picks which way the bearing is taken: t > 0 measures the reversed
 * vector and subtracts the offset, t <= 0 measures it forwards and adds. Both add PI
 * (0x3244), which mwcc splits into +0x244 / +0x3000 because it is not an encodable
 * ARM immediate.
 *
 * Same maths shape as func_ov137_020cc9e0 and its six twins, which return the unit
 * direction instead of storing a heading. Byte-identical twins here: ov141 020ccf24,
 * ov142 020d0b64, ov143 020d47a4, ov150 020d0b68.
 *
 * The `+ (v.y - v.y)` on the roll is the copy artifact from deferred-ties.md: the ROM
 * puts a bare `add r0, r0, #0` between the call and the subtract, and only a
 * zero-valued addend of that shape reproduces it. Declaring the RNG as returning
 * long long, casting its result, or folding the addend to a constant zero all drop
 * the instruction and land at 408 bytes. */
typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov107_020cab14(int owner, int mode);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int FX_Inv(int num, int den);
extern int func_02023eb4();
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov142_020d0d00(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov142_020d0b64(int *node)
{
    int *state = (int *)node[1];
    VecFx32 v;
    int target;
    int gap;
    int t;
    int spread;
    int off;
    int roll;

    target = func_ov107_020cab14(*state, 0);
    state[1] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }

    VEC_Subtract((const VecFx32 *)(target + 0x74),
                 (const VecFx32 *)state[0x10], &v);
    v.y = 0;
    gap = func_01ff8d18(&v, &v);
    gap = gap - *(int *)(state[1] + 0x80) - *(int *)(*state + 0x80);

    t = FX_Inv(gap, 0xf000) * 2 - 0x1000;
    if (t < -0x1000) {
        t = -0x1000;
    }
    if (t > 0x1000) {
        t = 0x1000;
    }

    spread = 0x1000 - (t < 0 ? -t : t);
    off = spread * 2;
    if (off < 0) {
        off = -off;
    }
    roll = func_02023eb4(off + 1) + (v.y - v.y);
    off = FX_Mul(roll - spread, 0x3244);

    if (t > 0) {
        state[3] = (func_020050b4(-v.x, -v.z) + 0x3244) - off;
    } else {
        state[3] = off + (func_020050b4(v.x, v.z) + 0x3244);
    }

    state[4] = *(int *)(*node + 0x2c) * 30 / 5;
    func_ov107_020c9264(*state, 1, 1);
    *(char *)((char *)state + 0x48) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov142_020d0d00);
}

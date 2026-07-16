/* func_ov138_020d0620 -- pick a randomised approach direction toward the target.
 *
 * Returns a unit XZ direction in *out. One of a 7-member shape family; the twins live in
 * ov137/ov158/ov159/ov160/ov246/ov247 and are byte-identical modulo relocs (matched here, fanned out with dedupprop).
 *
 * With no target (ctx[2] == 0) it hands back the constant direction data_02042258 and stops --
 * that is the only exit that does not roll dice.
 *
 * Otherwise it takes the flattened vector from ctx[0x14] to the target's position (target+0x74),
 * normalises it, and measures `gap` = that length minus both collision radii (+0x80 each), exactly
 * as the move choosers do. `gap` is then turned into a Q12 ratio against the owner's reach at
 * ctx[0]+0x2d8 (with 0xf000 substituted when that reach is under 1.0, i.e. unset):
 *
 *     t = clamp(FX_Inv(gap, reach) * 2 - 0x1000, -0x1000, 0x1000)
 *
 * so t sweeps -1.0 .. +1.0 as the target goes from touching to a full reach away. The randomness
 * is then scaled by how far t sits from saturation:
 *
 *     spread = 0x1000 - |t|                    -- widest at t == 0, zero at either extreme
 *     off    = rand(|spread * 2| + 1) - spread -- uniform in [-spread, +spread]
 *     off    = FX_Mul(off, PI)                 -- Q12 turns -> Q12 radians
 *
 * i.e. at mid-range the heading is scattered across the full +/-PI circle, and as the target
 * approaches either end of the band the scatter collapses onto the exact bearing. The sign of t
 * also flips which way the bearing is taken: t > 0 measures the REVERSED vector and subtracts the
 * offset, t <= 0 measures it forwards and adds. Both add PI (0x3244) to the atan2 result, which
 * mwcc splits into +0x244 / +0x3000 because it is not an encodable ARM immediate.
 *
 * The final Q12 radian is converted to a 16-bit angle index and looked up in the sin/cos table
 * (codegen-cracks.md): 0x28be60db9391 is 65536/(2*PI) in .32, the +0x800<<32 is rounding, and the
 * (unsigned short) cast is what emits the lsl#4 / lsr#16 pair. out = (sin, 0, cos).
 *
 * `func_02023eb4(n) - spread` is why the ROM emits `rsb ; add` instead of a plain `sub`: the RNG
 * returns long long, so mwcc materialises -spread and adds it. Same mechanism as the `+ (v - v)`
 * copy artifact (deferred-ties.md) -- here the addend is real, so no dummy is needed. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int FX_Inv(int num, int den);
extern int func_02023eb4();
extern int func_020050b4(int x, int z);
extern VecFx32 data_02042258;
extern const short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov138_020d0620(int *ctx, VecFx32 *out) {
    VecFx32 v;
    int gap;
    int reach;
    int t;
    int spread;
    int off;
    int rad;
    unsigned int idx;

    if (ctx[2] == 0) {
        *out = data_02042258;
        return;
    }

    VEC_Subtract((const VecFx32 *)(ctx[2] + 0x74), (const VecFx32 *)ctx[0x14], &v);
    v.y = 0;
    gap = func_01ff8d18(&v, &v);
    gap = gap - *(int *)(ctx[2] + 0x80) - *(int *)(ctx[0] + 0x80);
    reach = *(int *)(ctx[0] + 0x2d8);
    if (reach < 0x1000) {
        reach = 0xf000;
    }

    t = FX_Inv(gap, reach) * 2 - 0x1000;
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
    off = FX_Mul(func_02023eb4(off + 1) + (-spread), 0x3244);

    if (t > 0) {
        rad = (func_020050b4(-v.x, -v.z) + 0x3244) - off;
    } else {
        rad = off + (func_020050b4(v.x, v.z) + 0x3244);
    }

    idx = (unsigned short)(((long long)rad * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    out->x = data_0203d210[idx * 2];
    out->y = 0;
    out->z = data_0203d210[idx * 2 + 1];
}

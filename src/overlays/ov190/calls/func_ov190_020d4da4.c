/*
 * Aim at the current target, drive the approach, and dispatch on how far away it still is
 * (x4: ov188/189/190/281).
 *
 * Each tick: age the node (state[6] += the owner's frame delta) and re-acquire the target
 * (020cab14). No target -> state 2 and advance. Otherwise take the vector from the owner's
 * position (owner+0xb0) to the target's (target+0x190), FLATTEN it (y = 0), normalise it -- the
 * normalise returns the distance -- and store the heading (atan2 of x,z) in state[5]. The gap is
 * that distance minus both radii (target+0x80 and owner+0x80). Independently, the node's own
 * heading in state[4] is turned into a sin/cos pair and scaled by 0x480 into state+0x20: that is
 * the per-frame step it moves along.
 *
 * Then the dispatch, on the countdown at state[7]: while it is still running, keep going only if
 * the gap is under 0x800 or the node is younger than 0x2000 -- otherwise give up (state 2). Once
 * it expires, the gap picks the attack: over 0x4000 -> 9, 0x2000..0x4000 -> 7, under -> 6.
 *
 * ★ FOUND BY THE VEC_Set FINGERPRINT SWEEP (ldm + individual strs to [sp], no stm) -- the sin/cos
 * vector is `VEC_Set(&v, sin, 0, cos)`, not an assigned struct. This is the biggest member of the
 * 12 the sweep found, and it matched at the exact size on the FIRST compile.
 *
 * Everything else came from catalogued cracks, which is the point worth recording -- there was
 * nothing new to discover here, only things to look up:
 *  - the Q12 radians->sin/cos conversion is the catalogued one verbatim (0x28be60db9391 =
 *    65536/2pi in .32; the `(unsigned short)` cast is what emits lsl#4/lsr#16, and the following
 *    `>> 4` becomes an `asr` because u16 promotes to signed int). See codegen-cracks.md.
 *  - ★ GHIDRA'S NON-ENCODABLE CONSTANTS, twice: it prints `0x7ff <` and `0x1fff <`; the ROM has
 *    `cmp r4, #0x800` and `cmp r4, #0x2000`. Written Ghidra's way both would come out of a pool.
 *  - EVERY branch pair is written with the arm the obvious reading puts SECOND first: the
 *    countdown's `<= 0` arm leads (ROM `bgt` sends the still-running case out of line), and the
 *    `< 0x2000` arm leads over the `>= 0x2000` one (ROM `bge`).
 *  - DECLARATION ORDER lays out the frame: `d` (the aim vector, sp+0xc) must be declared BEFORE
 *    `v` (the step vector, sp+0). Declared the other way the two swap slots and every sp-relative
 *    access in the function is off -- it looks catastrophic and is one line.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern int func_ov107_020cab14(int a, int b);
extern void func_0203c634(void *obj, int idx, int v);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int s, void *v, void *d);
extern short data_0203d210[];

void func_ov190_020d4da4(int *self) {
    int *state = (int *)self[1];
    struct Vecx32 d;
    struct Vecx32 v;
    int len;
    int gap;
    int idx;

    state[6] += *(int *)(*self + 0x2c);
    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 8), 0);
        return;
    }
    VEC_Subtract((void *)(state[2] + 0x190), (void *)(*state + 0xb0), &d);
    d.y = 0;
    len = func_01ff8d18(&d, &d);
    state[5] = func_020050b4(d.x, d.z);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[4] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    gap = (len - *(int *)(state[2] + 0x80)) - *(int *)(*state + 0x80);
    VEC_Set(&v, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    func_01ffa724(0x480, &v, (void *)(state + 8));
    state[7] -= *(int *)(*self + 0x2c);
    if (state[7] <= 0) {
        state[7] = 0;
        if (gap > 0x4000) {
            *(char *)(*state + 0x1c7) = 9;
            func_0203c634(self, *(signed char *)(self + 8), 0);
            return;
        }
        if (gap < 0x2000) {
            *(char *)(*state + 0x1c7) = 6;
            func_0203c634(self, *(signed char *)(self + 8), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)(self + 8), 0);
        return;
    }
    if (gap >= 0x800 && state[6] < 0x2000) { return; }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)(self + 8), 0);
}

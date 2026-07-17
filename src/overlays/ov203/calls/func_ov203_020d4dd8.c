/*
 * Orbit the target, re-rolling the dwell timer and the next attack when it expires
 * (x2: ov202/ov203).
 *
 * Sibling of func_ov202_020cd2fc, and the difference is the whole behaviour. That one DOTS the
 * facing direction with the aim vector to accelerate as it lines up. This one takes the CROSS
 * PRODUCT of the facing direction with a vertical vector (0, height << 12, 0) -- giving a
 * direction PERPENDICULAR to where it is looking. It strafes around the target rather than
 * closing on it.
 *
 * Per tick: re-acquire (020cab14); none -> state 2 and advance. Aim vector owner->target,
 * flattened, normalised for the distance; heading (atan2) into state[3]; gap = distance minus both
 * radii together. The facing sin/cos crossed with the vertical gives the strafe direction, scaled
 * by state[0xe] into the step at state+0x14. While the dwell timer at state[0xc] is still running,
 * only bail if the gap has opened past 0x5000. When it expires: re-roll the timer from the owner's
 * [0x224, 0x228] range, then roll a d100 -- over 0x50 -> attack 7, otherwise attack 6.
 *
 * MATCHED. Everything was a lookup; the two worth their lines:
 *  - ★ THE RELOC NAME WAS THE FINDING. This compiled byte-identical while verify_idx still said
 *    DIFIERE -- reloc NAMES differed: what I had called `func_01ff8c34` is **VEC_CrossProduct**,
 *    and the index knew that all along. The skill says to read `orig = {...}` rather than invent
 *    names; here it also handed over the semantics for free. A "vector library call" became "it
 *    orbits", and the function got its name from it.
 *  - The RNG `add r0,r0,#0` copy is the catalogued crack, NOT a tie: `f(0x65) + (delta - delta)`.
 *    `+ 0` folds away; the subtraction of a live local does not. Without it this is 484 -- exactly
 *    one instruction short. (It reads like a typo. It is load-bearing; do not "clean it up".)
 *  - `gap < 0x5000` not Ghidra's `0x4fff <` (non-encodable, would hit the pool), and both branch
 *    pairs written with the arm the obvious reading puts second first.
 *  - Three stack vectors: declaration order `d, v, up` puts up at sp+0, v at sp+0xc, d at sp+0x18
 *    -- the LAST declared gets the lowest slot.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern int func_ov107_020cab14(int a, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern void VEC_CrossProduct(void *a, void *b, void *d);
extern void func_01ffa724(int s, void *v, void *d);
extern int func_02023eb4();
extern short data_0203d210[];

void func_ov203_020d4dd8(int self) {
    int *state = *(int **)(self + 4);
    struct Vecx32 d;
    struct Vecx32 v;
    struct Vecx32 up;
    int owner;
    int target;
    int len;
    int gap;
    int idx;
    int obj;
    int start;
    int delta;

    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x190), (void *)(*state + 0xb0), &d);
    d.y = 0;
    owner = state[0];
    target = state[1];
    len = func_01ff8d18(&d, &d);
    gap = len - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    state[3] = func_020050b4(d.x, d.z);
    VEC_Set(&up, 0, (int)*(signed char *)((int)state + 0x58) << 12, 0);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[2] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    VEC_Set(&v, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    VEC_CrossProduct(&v, &up, &v);
    func_01ffa724(state[0xe], &v, (void *)(state + 5));
    if (state[0xc] <= 0) {
        obj = *state;
        start = *(int *)(obj + 0x224);
        delta = *(int *)(obj + 0x228) - start;
        if (delta < 0) {
            delta = -delta;
        }
        state[0xc] = start + func_02023eb4(delta + 1);
        if (func_02023eb4(0x65) + (delta - delta) <= 0x50) {
            *(char *)(*state + 0x1c7) = 6;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (gap < 0x5000) { return; }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}

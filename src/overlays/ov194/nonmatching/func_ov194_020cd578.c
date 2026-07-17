/*
 * func_ov194_020cd578 -- UNFINISHED. 408/408 bytes, 102/102 instructions.
 * x5 family (worth 5). Semantically complete; the instruction SHAPE is exact.
 *
 * WHAT IT DOES: a CloseOnTarget variant. Re-acquire the target (020cab14); none -> state 2. Aim
 * vector target->owner, flattened, normalised; heading (atan2) into state[4]. Turn state[3] into a
 * sin/cos direction, DOT it with the aim, take |dot| and max(0,...) (the second clamp is a no-op
 * after the abs, but the ROM emits it -- `rsbmi` then `movlt r6,#0`). Fetch a speed factor
 * (020c9f48), scale the direction by FX_Mul(factor, dot) into state+0x18. Then: if the sub-node at
 * state[1]+0xad is idle, state[0x11] < 1 drops to state 2, else state 7.
 *
 * THE GAP: the Q12 radians->sin/cos 64-bit multiply-accumulate schedules its sign-correction
 * `mla` and the rounding `adds` in the opposite order, and the umull's input/output registers
 * rotate with it (state[3] -> r2 in the ROM, r3 in mine).
 *      ROM:   umull ip,r3,r2,r0 ; mla r3,r2,r1,r3 ; asr r2,r2,#0x1f ; mla r3,r2,r0,r3 ; adds r0,ip,#0
 *      mine:  umull r2,ip,r3,r0 ; mla ip,r3,r1,ip ; asr r1,r3,#0x1f ; adds r2,r2,#0 ; mla ip,r1,r0,ip
 *
 * ★ WHY THIS Q12 TIES WHEN ov188/ov202/ov215's DID NOT: those had no CALL between the DotProduct
 * and the scale. Here `sf = 020c9f48(...)` sits between the dot and FX_Mul, so `dot` must survive
 * the call in a callee-saved register (ROM `movs r6,r0`), and that downstream pressure changes how
 * mwcc colors and schedules the Q12 multiply UPSTREAM. The exact same Q12 C expression that
 * matched byte-for-byte in ov215 ties here purely because of what happens 20 instructions later.
 * So the Q12 conversion is NOT the problem to solve -- it is the register pressure from the
 * dot-across-call, and no reordering of the source changed it (heading extracted to a local:
 * identical).
 *
 * RULED OUT: extracting `state[3]` to a local before the Q12 (identical, diff pinned at 0x85).
 * Arities checked: 020c9f48(val, 0), FX_Mul inline, VEC_DotProduct(2). The FX_Mul is the SDK
 * inline `((s64)a*b+0x800)>>12`, matched elsewhere.
 *
 * NEXT STEP: the residue is the Q12 multiply-accumulate scheduling under a live-across-call value.
 * Belongs with the scheduler/register-choice class. Worth 5, and everything but the 6-instruction
 * Q12 block is byte-exact.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline int FX_Mul(int v1, int v2) {
    return (int)(((long long)v1 * v2 + 0x800LL) >> 12);
}

extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(void *a, void *b);
extern int func_ov107_020c9f48(int a, int out);
extern void func_01ffa724(int s, void *v, void *d);
extern short data_0203d210[];

void func_ov194_020cd578(int self) {
    int *state = *(int **)(self + 4);
    struct Vecx32 aim;
    struct Vecx32 dir;
    int target;
    int idx;
    int dot;
    int sf;

    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), &aim);
    aim.y = 0;
    func_01ff8d18(&aim, &aim);
    state[4] = func_020050b4(aim.x, aim.z);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[3] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    VEC_Set(&dir, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
    dot = VEC_DotProduct(&dir, &aim);
    if (dot < 0) {
        dot = -dot;
    }
    if (dot < 0) {
        dot = 0;
    }
    sf = func_ov107_020c9f48(*(int *)(*state + 0x3d0), 0);
    func_01ffa724(FX_Mul(sf, dot), &dir, (void *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        if (state[0x11] < 1) {
            *(char *)(*state + 0x1c7) = 2;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}

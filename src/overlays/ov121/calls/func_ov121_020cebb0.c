/*
 * Aim at the target, then pick a melee reaction by range and facing dot (x3).
 *
 * Re-acquire the target (020cab14); none -> return (no state change). Aim vector owner->target,
 * flatten, normalise; the gap is the distance minus both radii. Store the heading (atan2) in
 * state[5]. If the gap exceeds the owner's reach (*state+0x2d8), wait. Otherwise run the cooldown
 * at state[0x10]: when it expires, build the facing sin/cos direction from state[4] and pick a
 * reaction -- if the target is within 0x3000 AND the facing dot exceeds 0x800, attack (6 inside
 * 0xa00, else 7); otherwise back off (4).
 *
 * MATCHED. Several catalogued spellings, the load-bearing ones:
 *  - target and owner (*state) are read into locals AFTER the VEC_Subtract but BEFORE the
 *    normalise call, so they live across it in callee-saved registers (the ROM's `push` includes
 *    r7 for exactly this). VEC_Subtract itself uses the CALL RESULT directly (state[2] right after
 *    the store), so target is not kept from the call -- it is re-loaded once. Getting this wrong
 *    keeps the call result alive (an extra `movs`, +1) or re-reads per use (+several).
 *  - the inner range constant is `gap <= 0xa00`, not Ghidra's `< 0xa01`: 0xa01 is not an ARM
 *    immediate and goes to the pool (+1); 0xa00 encodes.
 *  - the reach test is `gap > reach`, matching the ROM's `cmp gap,reach` operand order.
 *  - the reaction branch is written `if (gap > 0x3000 || dot <= 0x800) backoff; else attack;` so
 *    the back-off (state 4) is the inline fall-through and the attack block is out of line, as the
 *    ROM lays it out. The `||` short-circuits the DotProduct exactly as the ROM's first `bgt`.
 *  - Ghidra's two "conditional pointers" (piVar8 = &uStack_18 / piVar8 + 6) are DEAD CODE gated
 *    out by the null-return and the counter branch; the buffers are always the stack slots.
 */
struct Vecx32 { int x, y, z; };

static inline void VEC_Set(struct Vecx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(void *a, void *b);
extern short data_0203d210[];

void func_ov121_020cebb0(int *self) {
    int *state = (int *)self[1];
    struct Vecx32 aim;
    struct Vecx32 dir;
    int gap;
    int tgt;
    int own;
    int idx;
    int c;

    state[6] = 0;
    state[2] = func_ov107_020cab14(*state, 0);
    if (state[2] == 0) {
        return;
    }
    VEC_Subtract((void *)(state[2] + 0x190), (void *)(*state + 0xb0), &aim);
    aim.y = 0;
    tgt = state[2];
    own = *state;
    gap = (func_01ff8d18(&aim, &aim) - *(int *)(tgt + 0x80)) - *(int *)(own + 0x80);
    state[5] = func_020050b4(aim.x, aim.z);
    if (gap > *(int *)(*state + 0x2d8)) {
        return;
    }
    c = state[0x10] - *(int *)(*self + 0x2c);
    state[0x10] = c;
    if (c <= 0) {
        idx = (int)(((unsigned)(((long long)(int)(unsigned)state[4] * 0x28be60db9391LL +
                     0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        VEC_Set(&dir, (int)data_0203d210[idx * 2], 0, (int)data_0203d210[idx * 2 + 1]);
        if (gap > 0x3000 || VEC_DotProduct(&dir, &aim) <= 0x800) {
            *(char *)(*state + 0x1c7) = 4;
        } else if (gap <= 0xa00) {
            *(char *)(*state + 0x1c7) = 6;
        } else {
            *(char *)(*state + 0x1c7) = 7;
        }
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
    }
}

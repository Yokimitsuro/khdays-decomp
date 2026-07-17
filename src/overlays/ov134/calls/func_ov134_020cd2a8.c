/*
 * Aim at the target, spin toward it, and pick idle vs attack by a stored flag bit (x3).
 *
 * Re-acquire the target (020cab14); none -> state 2 and advance. Aim vector owner->target,
 * flatten, normalise; heading (atan2) -> state[4]. Build the facing sin/cos from state[3], dot it
 * with the aim (result discarded, call kept), and scale that direction by the speed factor
 * (020c9f48 on *state+0x3a0) into the step at state+0x18. Finally, once the sub-node at
 * state[1]+0xad is idle: bit 0 of the flag byte at state+0x42 picks the outcome -- set -> attack
 * (state 7), clear -> idle (state 2).
 *
 * MATCHED, a CloseOnTarget cousin with a stack direction vector (so it matches, unlike the
 * heap-vector ov214). The two catalogued spellings that finished it:
 *  - ★ the flag test is a 1-BIT BITFIELD, not a mask. The ROM extracts bit 0 with
 *    `lsl r0,#0x1f ; lsrs r0,#0x1f` -- the classic `unsigned b:1` read -- where a plain
 *    `(byte & 1)` compiles to a single `tst` (one short). Model it as
 *    `struct { unsigned char b : 1; }` and read `->b`.
 *  - the branch is inverted from the obvious reading: `if (bit != 0) attack; else idle;` so the
 *    attack (state 7) is the inline arm and idle (state 2) is out of line, matching the ROM's
 *    `beq` to the idle block. (Also: `aim` before `dir` for the frame; Ghidra's `< 0xa01`-style
 *    non-encodable constants do not appear here.)
 */
struct Vecx32 { int x, y, z; };
struct Bit0 { unsigned char b : 1; };

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
extern int func_ov107_020c9f48(int a, int out);
extern void func_01ffa724(int s, void *v, void *d);
extern short data_0203d210[];

void func_ov134_020cd2a8(int self) {
    int *state = *(int **)(self + 4);
    struct Vecx32 aim;
    struct Vecx32 dir;
    int target;
    int idx;

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
    VEC_DotProduct(&dir, &aim);
    func_01ffa724(func_ov107_020c9f48(*(int *)(*state + 0x3a0), 0), &dir, (void *)(state + 6));
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        if (((struct Bit0 *)((int)state + 0x42))->b != 0) {
            *(char *)(*state + 0x1c7) = 7;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}

/*
 * func_ov143_020d4ea8 -- UNFINISHED. 196/196 bytes. TWIN of func_ov142_020d1268 (see that file
 * for the full analysis); x5 family (worth 5). Same aim-and-rate shape, same residue.
 *
 * The division `*(int *)(*self + 0x2c) * 0x1e / 5` is the SAME divide-by-5 tie as ov142: the ROM
 * emits `mul ; lsr(signbit) ; smull(overwrites x*30 in r3) ; add ...,asr#1`, computing the sign
 * bit BEFORE the smull because the smull reuses the input register; mwcc schedules the smull
 * first (into fresh registers, preserving x*30) and the sign bit after. It is the smull's
 * destination-register choice, fixed by mwcc's divide-by-constant generator, and no source form
 * moves it.
 *
 * Confirmed this pass that the manual expansion makes it WORSE: writing the divide as
 * `((unsigned)v>>31) + ((long long)0x66666667 * v >> 33)` makes mwcc treat 0x66666667 as a 64-bit
 * constant and emit a full umull+mla 32x64 multiply (204 B, +2 instructions) instead of the
 * single smull. So `/ 5` is the right form and the residue is purely the smull ordering. Base is
 * *self (the owner), divisor is 5 (magic 0x66666667, asr #1) -- read the magic, it is not ov195's
 * /3 or ov182's /20.
 *
 * Everything else (aim, flatten, normalise, atan2) is byte-exact -- the division is the only gap.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int func_020050b4(int x, int z);
extern int func_ov143_020d4f68;

void func_ov143_020d4ea8(int *self) {
    int *state = (int *)self[1];
    int target;
    int aim[3];

    target = func_ov107_020cab14(*state, 0);
    state[1] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[0xf], aim);
    aim[1] = 0;
    func_01ff8d18(aim, aim);
    state[3] = func_020050b4(aim[0], aim[2]);
    state[4] = *(int *)(*self + 0x2c) * 0x1e / 5;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov143_020d4f68);
}

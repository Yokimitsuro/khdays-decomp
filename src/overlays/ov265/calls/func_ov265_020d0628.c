/* func_ov265_020d0628 -- acquire a target and cache the range and bearing to it.
 * Asks func_ov107_020cab14 for a target; without one the owner is dropped into state 2
 * (+0x1c7) and the caller told nothing was found.
 * With one, the offset from the owner (+0xb0) to the target (+0x190) is cached at +0x3c, and
 * from it: the gap at +0x20 -- the raw separation less both bodies' radii (+0x80 each), floored
 * at zero so touching bodies read 0 -- and the bearing at +0x1c, from the x/z components only. */
extern int func_ov107_020cab14(int owner, int kind);
extern void VEC_Subtract(const int *a, const int *b, int *out);
extern int func_01ff8d18(const int *v, int *out);
extern int func_020050b4(int x, int z);

int func_ov265_020d0628(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    ctx[5] = func_ov107_020cab14(ctx[0], 0);
    if (ctx[5] == 0) {
        *(unsigned char *)(ctx[0] + 0x1c7) = 2;
        return 0;
    }

    VEC_Subtract((const int *)(ctx[5] + 0x190), (const int *)(ctx[0] + 0xb0), &ctx[0xf]);
    ctx[8] = func_01ff8d18(&ctx[0xf], &ctx[0xf]);
    ctx[8] = ctx[8] - (*(int *)(ctx[5] + 0x80) + *(int *)(ctx[0] + 0x80));
    if (ctx[8] < 0) {
        ctx[8] = 0;
    }
    ctx[7] = func_020050b4(ctx[0xf], ctx[0x11]);
    return 1;
}

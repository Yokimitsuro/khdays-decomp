/* Run each seat's per-frame hook. The hooks are an array of four at +0x22a0 and
 * the objects they act on are four 0x20-byte records at +0x22c0; a seat with no
 * hook is skipped.
 *
 * The hook's third argument is the context RE-READ from the global rather than
 * the pointer already in hand: a hook is free to swap the context out from
 * under the loop, so the ROM reloads it at each call.
 *
 * Written as plain indexed access even though the ROM runs two walking pointers
 * (+4 for the hook, +0x20 for the object) alongside the counter. Those walkers
 * are mwcc's own strength reduction; hand-writing them costs the match. */
typedef struct {
    char pad0000[0x22a0];
    void (*hooks[4])(void *object, int seat, void *ctx);   /* +0x22a0 */
    char pad22b0[0x10];
    char objects[4][0x20];                                 /* +0x22c0 */
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

void func_ov002_02072000(void) {
    Ov002LinkCtx *ctx = data_ov002_0207fa10;
    int seat;

    for (seat = 0; seat < 4; seat++) {
        if (ctx->hooks[seat] != 0) {
            ctx->hooks[seat](ctx->objects[seat], seat, data_ov002_0207fa10);
        }
    }
}

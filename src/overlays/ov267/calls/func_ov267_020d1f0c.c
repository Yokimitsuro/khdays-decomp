/* func_ov267_020d1f0c -- if a dodge or a counter is queued and the opening still holds, fire the
 * emitter. Always returns 1.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Every exit returns 1 -- including all three early-outs -- so the return value is not a report of
 * whether anything happened. Transcribed as the ROM has it.
 *
 * The gate is: a target at ctx[0x11], func_ov267_020d124c(ctx, 0) still true, and a queued move at
 * ctx[0]+0x1c7 of exactly 6 (dodge) or 0xb. Only then does func_ov107_020c0b90 fire channel 4.
 *
 * data_02041dc8 is passed BY VALUE, which is what produces the ROM's `sub r3, sp, #8 ; ldm ; stm ;
 * ldm r3, {r2,r3}` straddle -- a 12-byte 3rd argument goes half in r2/r3 and half in the outgoing
 * stack slot, with the 4th argument (1) landing at [sp, #4]. See codegen-cracks.md. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov267_020d124c(int *ctx, int a);
extern void func_ov107_020c0b90(int obj, int kind, VecFx32 v, int flag);
extern VecFx32 data_02041dc8;

int func_ov267_020d1f0c(int self) {
    int *ctx;
    int owner;
    int q;

    ctx = *(int **)(self + 4);
    if (ctx[0x11] != 0 && func_ov267_020d124c(ctx, 0) != 0) {
        owner = ctx[0];
        q = *(signed char *)(owner + 0x1c7);
        if (q == 6 || q == 0xb) {
            func_ov107_020c0b90(owner, 4, data_02041dc8, 1);
        }
    }
    return 1;
}

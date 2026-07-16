/* func_ov228_020d193c -- drive the timed effect, then end the move.
 *
 * The timer at +0x4c runs to 0x7f8 and stops there (it is stored once raw and again clamped --
 * that double store is what the ROM emits). Once it has already reached 0x7f8 the whole effect is
 * skipped and only the ending runs.
 *
 * The effect is described by a 0x38-byte parameter block built on the stack and handed to
 * func_ov228_020ceeb8: the object's own vector from ctx+0x34, three constant vectors, a scaled
 * progress value, and a 1.
 *
 * The progress is `clamp(timer, 0, 0x3b8) * 0x6000 / 0x3b8` -- 0x3b8 (952) is both the clamp
 * ceiling and the divisor (read off the 0x44d72045 / asr #8 magic), so this normalises the timer
 * onto 0..0x6000. Kept unfolded because the intermediate product overflows nothing but the
 * multiply-then-magic-divide is what the ROM does.
 *
 * data_02042258/64/70 sit 12 bytes apart, i.e. three consecutive VecFx32 constants -- note the
 * block takes them out of order (70, 58, 64). */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    VecFx32 origin;
    VecFx32 v1;
    VecFx32 v2;
    VecFx32 v3;
    int progress;
    int enable;
} EffectParams;

extern void func_ov228_020ceeb8(int *ctx, int a, int b, EffectParams *p);
extern void func_0203c634(int self, int action, void *cb);
extern VecFx32 data_02042258;
extern VecFx32 data_02042264;
extern VecFx32 data_02042270;

void func_ov228_020d193c(int self) {
    int *ctx;
    EffectParams p;
    int t;

    ctx = *(int **)(self + 4);
    if (ctx[0x13] < 0x7f8) {
        /* Through a local and stored twice: writing `ctx[0x13] += x; if (... > 0x7f8) ctx[0x13] =
         * 0x7f8;` collapses into one conditional store, where the ROM stores the raw value and
         * then the clamped one unconditionally. */
        t = ctx[0x13] + *(int *)(*(int *)self + 0x2c);
        ctx[0x13] = t;
        if (t > 0x7f8) {
            t = 0x7f8;
        }
        ctx[0x13] = t;

        p.origin = *(VecFx32 *)((char *)ctx + 0x34);

        t = ctx[0x13];
        if (t > 0x3b8) {
            t = 0x3b8;
        } else if (t < 0) {
            t = 0;
        }
        p.progress = t * 0x6000 / 0x3b8;

        p.v1 = data_02042270;
        p.v2 = data_02042258;
        p.v3 = data_02042264;
        p.enable = 1;
        func_ov228_020ceeb8(ctx, 2, 0, &p);
    }

    /* Reached from both paths -- the early-out at the top of the function lands here too, not on
     * the ending below. */
    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }

    *(unsigned char *)(ctx[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}

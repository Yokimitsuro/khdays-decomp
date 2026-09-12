typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

/* Same Tween/TweenFlags shape already established by the callers in the tree
 * (e.g. src/overlays/ov008/calls/func_ov008_0205c670.c, which declares this
 * exact function as `extern void func_0203602c(Tween *tween, s32 *value);`,
 * and src/overlays/ov005/calls/func_ov005_020564a4.c /
 * func_ov005_02053994.c with the identical field layout). */
typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;           /* easing curve id, see func_02035da8 */
    s32 duration;
    s32 from;
    s32 to;
    long long startTick; /* running: tick the tween started at.
                           * paused: the frozen elapsed tick count itself. */
    TweenFlags flags;
} Tween;

extern long long func_020031d4(void);                     /* 64-bit tick counter */
extern int func_02020368(u64 value, u32 divisor, int mode); /* runtime 64/32 divide */
extern s32 func_02035da8(s32 start, s32 end, u32 elapsed, u32 duration, u32 curve);

/* Sample a tween's current value. Does nothing if it hasn't been started.
 * Once finished, keeps reporting the end value. While paused, the elapsed
 * time is read straight from startTick instead of measured against "now". */
void func_0203602c(Tween *tween, s32 *value)
{
    u32 elapsed;

    if (!tween->flags.started) {
        return;
    }

    if (!tween->flags.finished) {
        u32 duration;

        if (!tween->flags.paused) {
            elapsed = func_02020368(
                (u64)(func_020031d4() - tween->startTick) << 6, 0x82ea, 0);
        } else {
            elapsed = func_02020368((u64)tween->startTick << 6, 0x82ea, 0);
        }
        duration = tween->duration;
        if (elapsed >= duration) {
            tween->flags.finished = 1;
            elapsed = duration;
        }
    } else {
        elapsed = tween->duration;
    }

    if (value != 0) {
        *value = func_02035da8(tween->from, tween->to, elapsed, tween->duration,
                                tween->mode);
    }
}

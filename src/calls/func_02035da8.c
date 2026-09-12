/* Fixed-point tween: interpolate from `start` to `end` at `elapsed`/`duration`
 * along one of four easing curves.
 *
 * curve 0: linear.                          start + diff * t
 * curve 1: ease-in quadratic.               start + diff * t^2
 * curve 2: ease-out quadratic.              end   - diff * (1-t)^2
 * curve 3: two mirrored quadratic halves    (a smoothstep), built from a Q12
 *          FX_Inv reciprocal instead of the hardware divider.
 *
 * Any other curve value falls off the end of the switch and returns `start`
 * unchanged -- the ROM implements that as a bare `pop` right after the range
 * check, not as a real default arm, so there is deliberately no trailing
 * return statement here.
 *
 * Curves 1 and 2 drive the 64/64 divider with `diff << 32` over `duration^2`,
 * then scale the quotient's high word by the squared weight.  Note the two
 * weights are spelled differently on purpose: `elapsed * elapsed` is a 32-bit
 * product (the caller's elapsed time always fits), while `(duration-elapsed)^2`
 * is a full 64-bit one.
 *
 * Only DIVCNT and DIV_RESULT are volatile; the numerator and denominator are
 * plain stores, matching the rest of the divider code in this tree (see
 * libs/nitro/fx/auto/func_01ffcfd0.c).  It is not cosmetic -- leaving them
 * volatile pins the weight multiply above the register writes instead of
 * letting it schedule in among them.
 */

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed long long s64;
typedef unsigned long long u64;

#define DIVCNT        (*(volatile u16 *)0x04000280)
#define DIV_NUMER     (*(s64 *)0x04000290)
#define DIV_DENOM     (*(u64 *)0x04000298)
#define DIV_RESULT32  (*(volatile s32 *)0x040002a0)
#define DIV_RESULT    (*(volatile s64 *)0x040002a0)

extern int FX_Inv(int x, int y);

static inline s32 FX_Mul(s32 a, s32 b)
{
    return (s32)(((s64)a * b + 0x800) >> 12);
}

s32 func_02035da8(s32 start, s32 end, u32 elapsed, u32 duration, u32 curve)
{
    s32 diff;
    u64 weight;
    s32 offsetFromMid;
    s32 halfDiff;
    s32 offsetSq;
    s32 eased;

    if (start == end) {
        return end;
    }
    if (elapsed >= duration) {
        return end;
    }

    diff = end - start;

    switch (curve) {
    case 0:
        DIVCNT = 1;
        DIV_NUMER = (s64)diff * elapsed;
        DIV_DENOM = (u64)duration;
        while (DIVCNT & 0x8000) {
        }
        return start + DIV_RESULT32;

    case 1:
        DIVCNT = 2;
        DIV_NUMER = (s64)diff << 32;
        DIV_DENOM = (u64)duration * duration;
        weight = elapsed * elapsed;
        while (DIVCNT & 0x8000) {
        }
        return start + (s32)((weight * (u64)DIV_RESULT) >> 32);

    case 2:
        DIVCNT = 2;
        DIV_NUMER = (s64)diff << 32;
        DIV_DENOM = (u64)duration * duration;
        weight = (u64)(duration - elapsed) * (duration - elapsed);
        while (DIVCNT & 0x8000) {
        }
        return end - (s32)((weight * (u64)DIV_RESULT) >> 32);

    case 3:
        /* +0x1000 at the start, 0 at the midpoint, -0x1000 at the end. */
        offsetFromMid = 0x1000 - (FX_Inv(elapsed, duration) << 1);

        if (elapsed < (duration >> 1)) {
            offsetSq = FX_Mul(offsetFromMid, offsetFromMid);
            halfDiff = diff / 2;
            eased = FX_Mul(halfDiff, 0x1000 - offsetSq);
            return eased + start;
        } else {
            offsetSq = FX_Mul(offsetFromMid, offsetFromMid);
            halfDiff = diff / 2;
            eased = FX_Mul(halfDiff, offsetSq);
            return start + halfDiff + eased;
        }
    }
}

/*
 * RandNextScaled - advance the global 64-bit LCG RNG and return a value scaled to [0, range).
 *
 * Advances the RNG state at data_0204c168 (seed = seed*mult + inc, low 64 bits, with seed at
 * +0xc, mult at +0x14, inc at +0x1c). Returns range==0 ? newHigh : (u64)newHigh*range >> 32,
 * i.e. the new high word scaled into [0, range). This is the game-wide random source; hundreds
 * of callers do e.g. RandNextScaled(100), RandNextScaled(12).
 *
 * Sibling of func_020307f4 (the session RNG). The LCG is written mult*seed for the ROM's
 * operand-load order; the result is held in a local and conditionally rescaled (kept in a
 * register, not reloaded) so the tail is umull/mov rather than a predicated reload.
 */

typedef struct {
    char pad0[0xc];
    long long seed;   /* 0x0c */
    long long mult;   /* 0x14 */
    long long inc;    /* 0x1c */
} RngState;

extern RngState data_0204c168;

unsigned int func_02023eb4(unsigned int range)
{
    RngState *s = &data_0204c168;
    unsigned int result;

    s->seed = s->mult * s->seed + s->inc;
    result = (unsigned int)(s->seed >> 32);
    if (range != 0)
        result = (unsigned int)((unsigned long long)result * range >> 32);
    return result;
}

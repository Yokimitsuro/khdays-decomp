/*
 * RandNext - advance the global 64-bit LCG RNG and return its top 12 bits.
 *
 * Advances the RNG state at data_0204c168 (seed = seed*mult + inc, low 64 bits, with seed at
 * +0xc, mult at +0x14, inc at +0x1c) -- same state and step as func_02023eb4's
 * RandNextScaled. Returns the top 12 bits of the new 64-bit seed (seed >> 52), unscaled.
 *
 * Written as (newSeedHi << 12) >> 32 rather than the equivalent seed >> 52: the compiler
 * folds a direct 64-bit shift by a constant >= 32 into one instruction, but widening the
 * already-narrowed high word back to 64 bits before shifting forces the generic
 * mov #0 / lsl #12 / orr ...,lsr #20 merge codegen that the ROM actually has.
 */

typedef struct {
    char pad0[0xc];
    unsigned long long seed;   /* 0x0c */
    unsigned long long mult;   /* 0x14 */
    unsigned long long inc;    /* 0x1c */
} RngState;

extern RngState data_0204c168;

int func_02023f08(void)
{
    RngState *s = &data_0204c168;
    unsigned int newSeedHi;

    s->seed = s->mult * s->seed + s->inc;
    newSeedHi = (unsigned int)(s->seed >> 32);
    return (int)(((unsigned long long)newSeedHi << 12) >> 32);
}

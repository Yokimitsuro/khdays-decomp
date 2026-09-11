/*
 * Session_RandNext - advance the session's 64-bit LCG RNG and return its top 12 bits.
 *
 * Advances the GameSession RNG state (seed = mult*seed + inc, low 64 bits) pointed to by the
 * global data_0204c228 -- same state and step as func_020307f4's Session_RandNextScaled and the
 * global-RNG sibling func_02023f08 (RandNext). Returns the top 12 bits of the new 64-bit seed
 * (seed >> 52), unscaled.
 *
 * Written as (newSeedHi << 12) >> 32 rather than the equivalent seed >> 52, matching
 * func_02023f08: the compiler folds a direct 64-bit shift by a constant >= 32 into one
 * instruction, but widening the already-narrowed high word back to 64 bits before shifting
 * forces the generic mov #0 / lsl #12 / orr ...,lsr #20 merge codegen the ROM has.
 */

typedef struct { char pad[8]; long long seed; long long mult; long long inc; } GameSession;
extern GameSession *data_0204c228;

int func_0203084c(void)
{
    GameSession *s = data_0204c228;
    unsigned int newSeedHi;

    s->seed = s->mult * s->seed + s->inc;
    newSeedHi = (unsigned int)(s->seed >> 32);
    return (int)(((unsigned long long)newSeedHi << 12) >> 32);
}

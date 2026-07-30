/*
 * Session_RandNextScaled - advance the session RNG and return a value scaled to [0, range).
 *
 * Advances the GameSession 64-bit LCG (seed = seed*mult + inc, low 64 bits), then:
 *   range == 0 -> returns the raw new high word (a full 32-bit random value);
 *   range != 0 -> returns (u64)newHigh * range >> 32, i.e. newHigh scaled into [0, range).
 * The session pointer is the global data_0204c228. Sibling of func_0203084c (Session_RandNext,
 * which returns the top 12 bits). Both branches reload the new high word from memory, so the
 * tail is predicated (ldreq / umullne).
 *
 * The LCG multiply is written mult*seed (not seed*mult): the conditional-return context makes
 * mwcc schedule the operand loads mult-first only for that order.
 */

typedef struct { char pad[8]; long long seed; long long mult; long long inc; } GameSession;
extern GameSession *data_0204c228;

unsigned func_020307f4(unsigned range)
{
    GameSession *s = data_0204c228;
    s->seed = s->mult * s->seed + s->inc;
    if (range == 0)
        return (unsigned)(s->seed >> 32);
    return (unsigned)((unsigned long long)(unsigned)(s->seed >> 32) * range >> 32);
}

/*
 * Steps the multiplayer session's give-up countdown and reports when it has
 * run out.
 *
 * The countdown only runs while a millisecond stamp has been latched. Once a
 * second has gone by since that stamp, one second comes off the counter and
 * the stamp moves forward; the clock itself is the hardware tick count scaled
 * to milliseconds the way the rest of the game does it, by shifting up six and
 * dividing by the ticks-per-millisecond constant.
 *
 * While seconds remain the answer is no. When they run out the counter is
 * pinned at zero and the answer is whether the session is otherwise idle.
 *
 * One thing here is load-bearing rather than style. Both negative answers are
 * one `return 0` at the end of the function rather than early returns, so the
 * two exits share a single tail the way the original does. Written as early
 * returns the compiler predicates each of them into its own `pop` and the
 * function comes out four bytes short.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SessionLink {
    char pad000[0x1c];
    int nLastMs;
    s16 nSecondsLeft;
} Ov002SessionLink;

typedef struct Ov002SessionScreen {
    char pad0000[0x8b64];
    int nFlags;
    char pad8b68[0x40];
    Ov002SessionLink link;
} Ov002SessionScreen;

extern Ov002SessionScreen *NNSi_FndGetCurrentRootHeap(void);
extern unsigned long long func_ov002_0206f604(void);
extern unsigned long long func_02020368(unsigned long long value,
                                        unsigned int divisor, int arg3);

int func_ov002_0206a804(void)
{
    Ov002SessionScreen *pSess;
    Ov002SessionLink *pLink;
    int nNow;

    pSess = NNSi_FndGetCurrentRootHeap();
    pLink = &pSess->link;
    if (pLink->nLastMs > 0) {
        nNow = (int)func_02020368(func_ov002_0206f604() << 6, 0x82ea, 0);
        if (nNow - pLink->nLastMs >= 1000) {
            pLink->nSecondsLeft = (s16)(pLink->nSecondsLeft - 1);
            pLink->nLastMs = nNow;
        }

        if (pLink->nSecondsLeft <= 0) {
            pLink->nSecondsLeft = 0;
            return pSess->nFlags == 0;
        }
    }
    return 0;
}

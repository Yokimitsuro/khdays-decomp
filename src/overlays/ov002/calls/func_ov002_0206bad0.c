typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov002PlayerRecord {
    u64 nFlags;                 /* 0x000 */
    char pad008[0x45c];
    u64 nState;                 /* 0x464 */
} Ov002PlayerRecord;

/* Number of players the session currently holds. */
extern int func_ov022_020882f8(void);
extern Ov002PlayerRecord *func_01fffde0(int nPlayer);
/* Non-zero while the player is busy with something else. */
extern int func_ov022_020886d0(int nPlayer);
/* Positive while the player has something to act on. */
extern int func_ov022_020882e0(int nPlayer);
extern void func_ov022_020888b8(int nPlayer, int nArg);

/* Raise or drop the shared marker on every player that can take it.
 *
 * Players that are out of play, busy, or with nothing to act on are skipped.
 * With the marker going up it is only given to a player whose state does not
 * already rule it out; with it going down it is simply taken away.  Turning
 * the whole thing off hands each player over to the session instead.
 */
void func_ov002_0206bad0(int bOn, int nArg)
{
    int i;
    Ov002PlayerRecord *pRec;

    for (i = 0; i < func_ov022_020882f8(); i++) {
        if (((u32)func_01fffde0(i)->nState & 0x10000000) == 0
            && func_ov022_020886d0(i) == 0
            && func_ov022_020882e0(i) > 0) {
            if (bOn != 0) {
                pRec = func_01fffde0(i);
                if (nArg != 0) {
                    if ((pRec->nState & 0x400000000ULL) == 0) {
                        pRec->nFlags |= 0x80000;
                    }
                } else {
                    pRec->nFlags &= ~0x80000ULL;
                }
            } else {
                func_ov022_020888b8(i, nArg);
            }
        }
    }
}

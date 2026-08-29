/*
 * Ov002_EditSessionClock - apply one of four edits to one of the session
 * clock's two millisecond fields.
 *
 * The root context carries a start stamp and a limit, and the first argument
 * picks between them.  Operation 0 stamps the field with the current time the
 * way the rest of the module reads the clock: the raw tick count shifted up six
 * and divided by the ticks-per-millisecond constant.  Operation 1 stores the
 * caller's value outright, operation 2 adds it, and operation 3 takes it away
 * but never lets the field fall below zero.
 *
 * Two things here are load-bearing rather than style.  The step onto the clock
 * pair is its own statement through a cast, which is what keeps the +0x8c94 in
 * the literal pool separate from the +0x6c/+0x70 field offset instead of the
 * two folding into one constant.  And that step sits before the branch, on the
 * same variable the root was read into, so the root, the pair and the chosen
 * field all live in one register the way the original does.
 *
 * Ghidra models these two fields inline on Ov002RootContext as nClockStart at
 * +0x8d00 and nClockLimit at +0x8d04; the window struct below only exists to
 * hold the offset split the codegen needs.
 *
 * THUMB.
 */

typedef struct Ov002SessionClock {
    char pad0000[0x6c];
    int nClockStart;                /* root +0x8d00 */
    int nClockLimit;                /* root +0x8d04 */
} Ov002SessionClock;

extern char *data_ov002_0207fa00;   /* the session root context */

extern unsigned long long func_ov002_0206f604(void);        /* raw tick count */
extern unsigned long long func_02020368(unsigned long long value,
                                        unsigned int divisor, int arg3);

void func_ov002_0206de58(int bLimit, int nOp, int nValue)
{
    Ov002SessionClock *pClock;
    int *pField;
    int nLeft;

    pClock = (Ov002SessionClock *)data_ov002_0207fa00;
    pClock = (Ov002SessionClock *)((char *)pClock + 0x8c94);
    if (bLimit == 0) {
        pField = &pClock->nClockStart;
    } else {
        pField = &pClock->nClockLimit;
    }

    switch (nOp) {
    case 0:
        *pField = (int)func_02020368(func_ov002_0206f604() << 6, 0x82ea, 0);
        break;
    case 1:
        *pField = nValue;
        break;
    case 2:
        *pField = *pField + nValue;
        break;
    case 3:
        nLeft = *pField - nValue;
        if (nLeft < 0) {
            nLeft = 0;
        }
        *pField = nLeft;
        break;
    }
}

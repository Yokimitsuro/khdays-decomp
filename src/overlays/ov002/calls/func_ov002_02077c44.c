typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

/* Three tier values, one byte each, laid out just before the spot descriptors
   and read from the top down.  They are 100 here, 10 at 0207e679 and 1 at
   0207e678: a plain decimal breakdown.  Only this one carries a symbol, since
   the lower two fall inside the object before it. */
extern u8 data_ov002_0207e67a;

extern void *func_ov002_020779dc(int nKind, u16 nTier, int nCtxIndex,
                                 const Ov002Vec3 *pPlace, int nMode);

/* Turns an amount into spawned objects, spending the dearest tier first: as
   long as the tier's value still fits it is taken off the amount, and the
   toggle means only every second one is actually spawned, so a drop is worth
   half of what the amount affords.  Whatever is left over falls through to the
   next tier down, and the three tiers run 2, 1, 0 -- hundreds, tens and ones.

   Everything goes out with mode 0, so each object gets a scattered velocity
   off the stage generator. */
void func_ov002_02077c44(int nKind, u8 nAmount, int nCtxIndex,
                         const Ov002Vec3 *pPlace)
{
    int nTier;
    u8 *pTierValue;
    u8 nValue;
    u8 bTakeThisOne;

    pTierValue = &data_ov002_0207e67a;
    nTier = 2;
    do {
        bTakeThisOne = 0;
        nValue = *pTierValue;
        if (nAmount >= nValue) {
            do {
                nAmount = (u8)(nAmount - nValue);
                bTakeThisOne = (u8)(bTakeThisOne ^ 1);
                if (bTakeThisOne != 0) {
                    func_ov002_020779dc(nKind, (u16)nTier, nCtxIndex, pPlace, 0);
                }
            } while (nAmount >= nValue);
        }
        pTierValue--;
        nTier--;
    } while (nTier >= 0);
}

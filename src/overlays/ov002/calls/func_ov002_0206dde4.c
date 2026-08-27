typedef unsigned long long u64;
typedef signed long long s64;

extern char *data_ov002_0207fa00;

extern u64 func_ov002_0206f604(void);   /* the raw tick count */

/* How much of the request clock is left, back in raw ticks, or zero once it has
   run out.  0x82ea is the number of ticks in a millisecond, so scaling by 64
   and dividing gives the 64ths of a millisecond that nClockStart and
   nClockLimit are kept in; what is left is scaled straight back.

   The subtraction is deliberately done at 64 bits even though only the low half
   survives the cast: that is what makes the compare against zero a separate
   instruction instead of being folded into the subtract. */
u64 func_ov002_0206dde4(void)
{
    char *pRoot;
    u64 nNow;
    int nLeft;

    pRoot = data_ov002_0207fa00;
    nNow = (func_ov002_0206f604() << 6) / 0x82ea;
    nLeft = (int)(*(int *)(pRoot + 0x8d04)
                  - (s64)(nNow - *(int *)(pRoot + 0x8d00)));
    if (nLeft < 0) {
        return 0;
    }
    return (u64)((s64)nLeft * 0x82ea) >> 6;
}

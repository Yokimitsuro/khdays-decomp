typedef unsigned short u16;

extern int func_ov002_02070fa0(int bSub, int nValue);
extern int func_ov002_02071148(u16 nA, u16 nB, short nC, u16 nD);
extern void func_ov002_0206ee38(int nFlags, int nX, int nY, int nStyle, int nText);

/* Queue a text item, choosing how its body is built from the kind. The
 * sub-screen form carries the 0x1000 flag; unknown kinds are dropped.
 *
 * Each case takes its own pointer local: sharing one across the switch makes
 * mwcc hoist the argument load above the flag test, where the original reloads
 * it per case. The readiness flag is written as a ternary rather than an
 * equality for the same reason - it schedules the pointer load first.
 */
void func_ov002_0206af20(int bMain, int nFlags, int nX, int nY,
                         int nStyle, int nKind, const void *pParam)
{
    if (bMain == 0) {
        nFlags |= 1 << 12;
    }

    switch (nKind) {
    case 0:
        {
            const int *pWord = (const int *)pParam;

            func_ov002_0206ee38(nFlags, nX, nY, nStyle,
                                func_ov002_02070fa0(bMain ? 0 : 1, *pWord));
        }
        break;

    case 1:
        {
            const char *pRec = (const char *)pParam;

            func_ov002_0206ee38(nFlags, nX, nY, nStyle,
                                func_ov002_02071148(*(const u16 *)pRec,
                                                    *(const u16 *)(pRec + 2),
                                                    *(const short *)(pRec + 4),
                                                    *(const u16 *)(pRec + 6)));
        }
        break;
    }
}

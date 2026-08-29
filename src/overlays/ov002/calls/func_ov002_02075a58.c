typedef unsigned char u8;

extern int func_02021980(void *pCtx, int nArgs);
extern int func_02021994(void *pCtx, int nArgs);
extern int func_ov002_0206d204(int nWho, int nKind, int nMode, int nCount,
                               int (*aPath)[3]);

/* Script VM command: send a roster slot along a path.
 *
 * Four leading operands say who moves, in what way, in what mode and how many
 * waypoints follow; each waypoint is then three fixed point operands.  Operand
 * slots are eight bytes each, so the cursor walks 0x20 past the header and
 * 0x18 past every waypoint.  Reports 1 when the walk was accepted.
 */
int func_ov002_02075a58(void *pCtx, int nArgs)
{
    int aPath[128][3];
    int nWho;
    int nKind;
    int nMode;
    int nCount;
    int nLast;
    int i;

    nWho = func_02021980(pCtx, nArgs);
    nKind = func_02021980(pCtx, nArgs + 8);
    nMode = func_02021980(pCtx, nArgs + 0x10);
    nLast = nArgs + 0x18;
    nArgs += 0x20;
    nCount = func_02021980(pCtx, nLast);

    for (i = 0; i < nCount; i++) {
        aPath[i][0] = func_02021994(pCtx, nArgs);
        aPath[i][1] = func_02021994(pCtx, nArgs + 8);
        nLast = nArgs + 0x10;
        nArgs += 0x18;
        aPath[i][2] = func_02021994(pCtx, nLast);
    }

    if (func_ov002_0206d204(nWho, (u8)nKind, nMode, nCount, aPath) == 0) {
        return 0;
    }
    return 1;
}

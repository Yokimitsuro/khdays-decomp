typedef unsigned short u16;

extern int func_02021980(void *pCtx, int nArgs);
/* Read and write the saved counter 0x20ad, slot 8. */
extern int func_020235d0(int nId, int nSlot);
extern void func_020235e8(int nId, int nSlot, u16 nValue);
/* Non-zero while the counter display is already up. */
extern int func_02023534(void);
extern void func_0202354c(int nOn);
extern void func_ov002_0206ac74(int nKind, int nValue, int nFlags);
extern int func_02020400(int nNum, int nDen);
extern void func_ov002_0206af88(int bWait, int nWhat, int nFlags, int *pOut);

/* Script VM command: award something and show it.
 *
 * Operand slots are eight bytes each: who, what, a kind and an amount.  Kinds
 * 5 and 6 are the running counter -- kind 6 first folds the thousands the save
 * already holds back into the amount -- so the counter is bumped, its display
 * brought up if it was not already, and the new thousands written back to the
 * save.  Any other kind is passed straight through.
 *
 * Always returns 1.
 */
int func_ov002_020747d0(void *pCtx, int nArgs)
{
    int nWho;
    int nWhat;
    int aOut[2];
    int nKind;
    int nAmount;

    nWho = func_02021980(pCtx, nArgs);
    nWhat = func_02021980(pCtx, nArgs + 8);
    nKind = func_02021980(pCtx, nArgs + 0x10);
    nArgs += 0x18;
    nAmount = func_02021980(pCtx, nArgs);

    if (nKind == 5 || nKind == 6) {
        aOut[0] = 0;
        if (nKind == 6) {
            nAmount += func_020235d0(0x20ad, 8) * 1000;
        }
        aOut[1] = nAmount;
        func_ov002_0206ac74(2, nAmount, 0);
        if (func_02023534() == 0) {
            func_0202354c(1);
        }
        func_020235e8(0x20ad, 8, (u16)func_02020400(nAmount, 1000));
    } else {
        aOut[0] = nKind;
        aOut[1] = nAmount;
    }

    func_ov002_0206af88(nWho == 0, nWhat, 0, aOut);
    return 1;
}

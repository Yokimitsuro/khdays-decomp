extern int func_02021980(int pOwner, int pSlot);
extern void func_ov002_0206af88(int bReady, int nFirst, int nKind, int *pRest);

/* Resolve the five slots of a request block and hand them to the builder:
 * the first slot only decides readiness, the second is passed on its own,
 * and the remaining three go through as an array. */
int func_ov002_0207512c(int pOwner, int pBlock)
{
    int nRest[3];
    int nGate;
    int nFirst;
    int nB;
    int nC;
    int nD;

    nGate = func_02021980(pOwner, pBlock);
    nFirst = func_02021980(pOwner, pBlock + 8);
    nB = func_02021980(pOwner, pBlock + 0x10);
    nC = func_02021980(pOwner, pBlock + 0x18);
    nD = func_02021980(pOwner, pBlock + 0x20);

    nRest[0] = nB;
    nRest[1] = nC;
    nRest[2] = nD;

    func_ov002_0206af88(nGate == 0, nFirst, 5, nRest);
    return 1;
}

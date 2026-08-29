extern int func_02021980(int pOwner, int pSlot);
extern void func_ov002_0206af88(int bReady, int nFirst, int nKind, int *pRest);

/* Resolve the six slots of a request block and hand them to the builder:
 * the first slot only decides readiness, the second is passed on its own,
 * and the remaining four go through as an array.  Same shape as the sibling
 * at 0207512c, one slot wider and with a different node kind. */
int func_ov002_02074878(int pOwner, int pBlock)
{
    int nRest[4];
    int nGate;
    int nFirst;
    int nB;
    int nC;
    int nD;
    int nE;

    nGate = func_02021980(pOwner, pBlock);
    nFirst = func_02021980(pOwner, pBlock + 8);
    nB = func_02021980(pOwner, pBlock + 0x10);
    nC = func_02021980(pOwner, pBlock + 0x18);
    nD = func_02021980(pOwner, pBlock + 0x20);
    nE = func_02021980(pOwner, pBlock + 0x28);

    nRest[0] = nB;
    nRest[1] = nC;
    nRest[2] = nD;
    nRest[3] = nE;

    func_ov002_0206af88(nGate == 0, nFirst, 1, nRest);
    return 1;
}

extern int func_02021980(int pOwner, int pSlot);
extern void func_ov002_02072a48(int bThird, int nSecond, int nFirst, int nThird,
                                int bFifth);

/* Resolve the five slots of a request block and apply them. The fourth and
 * fifth slots are only tested for presence; the other three pass their values
 * through. */
int func_ov002_020753fc(int pOwner, int pBlock)
{
    int nFirst;
    int nSecond;
    int nThird;
    int bFourth;
    int bFifth;

    nFirst = func_02021980(pOwner, pBlock);
    nSecond = func_02021980(pOwner, pBlock + 8);
    nThird = func_02021980(pOwner, pBlock + 0x10);
    bFourth = func_02021980(pOwner, pBlock + 0x18) != 0;
    bFifth = func_02021980(pOwner, pBlock + 0x20) != 0;

    func_ov002_02072a48(bFourth, nSecond, nFirst, nThird, bFifth);
    return 1;
}

typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

/* The 0x2c byte path-task record this command builds on the stack. */
typedef struct Ov002TaskArgsPath {
    int n00;                            /* +0x00 */
    int n04;                            /* +0x04 */
    int n08;                            /* +0x08 */
    Ov002Vec3 vPlace;                   /* +0x0c */
    int n18;                            /* +0x18 */
    int n1c;                            /* +0x1c */
    int n20;                            /* +0x20 */
    int nResolved;                      /* +0x24 */
    int n28;                            /* +0x28 */
} Ov002TaskArgsPath;

extern int func_02021980(int pCtx, unsigned short *pOperand);
extern int func_02021994(int pCtx, unsigned short *pOperand);
extern int func_02021948(int pCtx, unsigned short *pOperand);
extern void func_ov002_0206af88(int bGate, int nSlot, int nKind,
                                Ov002TaskArgsPath *pArgs);

/* Script command: submit a path task.
 *
 * The first four operands give a gate flag, the slot and two plain values.
 * The fifth operand's tag then chooses how the place is filled: tag zero
 * reads three fixed-point operands into it, anything else resolves that
 * operand into the record's resolved field and leaves the place at zero.
 * Four more plain values, three of them fixed-point, close the record, which
 * goes in with kind two. Always returns one.
 */
int func_ov002_020748e8(int pCtx, unsigned short *pArgs)
{
    Ov002Vec3 vPlace;
    Ov002TaskArgsPath args;
    int nSlot;
    int nA;
    int nB;
    int nGate;
    int nC;
    int n18;
    int n1c;
    int n20;
    int nResolved;
    int n28;

    nResolved = 0;
    nGate = func_02021980(pCtx, pArgs);
    nSlot = func_02021980(pCtx, pArgs + 4);
    nA = func_02021980(pCtx, pArgs + 8);
    nB = func_02021980(pCtx, pArgs + 0xc);

    if (*(short *)(pArgs + 0x10) == 0) {
        vPlace.x = func_02021994(pCtx, pArgs + 0x14);
        vPlace.y = func_02021994(pCtx, pArgs + 0x18);
        vPlace.z = func_02021994(pCtx, pArgs + 0x1c);
    } else {
        nResolved = func_02021948(pCtx, pArgs + 0x10);
        vPlace.x = 0;
        vPlace.y = 0;
        vPlace.z = 0;
    }

    nC = func_02021980(pCtx, pArgs + 0x20);
    n18 = func_02021994(pCtx, pArgs + 0x24);
    n1c = func_02021994(pCtx, pArgs + 0x28);
    n20 = func_02021994(pCtx, pArgs + 0x2c);
    n28 = func_02021980(pCtx, pArgs + 0x30);

    args.n00 = nA;
    args.n04 = nC;
    args.n08 = nB;
    args.vPlace = vPlace;
    args.n18 = n18;
    args.n1c = n1c;
    args.n20 = n20;
    args.nResolved = nResolved;
    args.n28 = n28;

    func_ov002_0206af88(nGate == 0, nSlot, 2, &args);
    return 1;
}

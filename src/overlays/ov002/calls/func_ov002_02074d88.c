typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

extern int func_02021980(int pCtx, unsigned short *pOperand);
extern int func_02021994(int pCtx, unsigned short *pOperand);
/* The setup creates the object slot, stamps the five values into the object it
 * makes, and starts its animation. The names below are what it does with each
 * argument, not guesses. */
extern void func_ov002_02073a10(int nEntry, int nKind, int nMask, int nMode,
                                Ov002Vec3 *pObjectPos, int nObjA, int nObjTag,
                                int nObjB, int nObjC, Ov002Vec3 *pAnimAt,
                                int nAnimMode, int nAnimParam);

/* Script command: create a slot object and start it.
 *
 * Sixteen operands feed the setup at 02073a10. The first four give the entry,
 * the kind, a mask and a mode; the fifth is a gate that goes in last as a
 * boolean. Three fixed-point operands build the position stamped into the new
 * object, four single values follow for its other fields, three more build the
 * place the animation starts from, and one closes with the animation mode.
 * Always returns one.
 */
int func_ov002_02074d88(int pCtx, unsigned short *pArgs)
{
    Ov002Vec3 vObjectPos;
    Ov002Vec3 vAnimAt;
    int nEntry;
    int nKind;
    int nMask;
    int nMode;
    int nGate;
    int nObjA;
    int nObjTag;
    int nObjB;
    int nObjC;
    int nAnimMode;

    nEntry = func_02021980(pCtx, pArgs);
    nKind = func_02021980(pCtx, pArgs + 4);
    nMask = func_02021980(pCtx, pArgs + 8);
    nMode = func_02021980(pCtx, pArgs + 0xc);
    nGate = func_02021980(pCtx, pArgs + 0x10);
    vObjectPos.x = func_02021994(pCtx, pArgs + 0x14);
    vObjectPos.y = func_02021994(pCtx, pArgs + 0x18);
    vObjectPos.z = func_02021994(pCtx, pArgs + 0x1c);
    nObjA = func_02021994(pCtx, pArgs + 0x20);
    nObjTag = func_02021980(pCtx, pArgs + 0x24);
    nObjB = func_02021994(pCtx, pArgs + 0x28);
    nObjC = func_02021994(pCtx, pArgs + 0x2c);
    vAnimAt.x = func_02021994(pCtx, pArgs + 0x30);
    vAnimAt.y = func_02021994(pCtx, pArgs + 0x34);
    vAnimAt.z = func_02021994(pCtx, pArgs + 0x38);
    nAnimMode = func_02021994(pCtx, pArgs + 0x3c);

    func_ov002_02073a10(nEntry, nKind, nMask, nMode, &vObjectPos, nObjA,
                        nObjTag, nObjB, nObjC, &vAnimAt, nAnimMode,
                        nGate != 0);
    return 1;
}

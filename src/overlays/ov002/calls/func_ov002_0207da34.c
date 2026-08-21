typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x, y, z;
} VecFx32;

/* One operand of a script command: a tag saying how the value is fetched and
 * the word that carries either the value itself or the reference to it. */
typedef struct {
    short kind;
    short pad;
    int   value;
} OperandSlot;

extern int func_02021980(void *pContext, OperandSlot *pOperand);
extern int func_02021994(void *pContext, OperandSlot *pOperand);
extern void *func_ov002_02076468(int nModule);
extern int func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_0207c3bc(void *pClass, u16 wA, u16 wB, u16 wC,
                                u8 bHigh, VecFx32 *pPos, short nHeading,
                                short nLast);

/* Script command: spawn a travel element.
 *
 * Nine operands - a module slot, two keys, a packed word, three fixed point
 * coordinates, a heading in degrees and a trailing key. The fourth operand's
 * word is read straight out of the descriptor instead of through an accessor,
 * and it supplies two of the spawn arguments: its low halfword and the byte
 * above it.
 *
 * That byte is narrowed twice on purpose. The original truncates to a halfword
 * and only then to a byte, so a single (u8) cast is two instructions short.
 *
 * The heading is degrees shifted into fixed point and divided by 360.
 *
 * Always returns 1.
 */
int func_ov002_0207da34(void *pContext, OperandSlot *pArgs)
{
    VecFx32 vPos;
    int nModule;
    int nA;
    int nB;
    int nPacked;
    int nDegrees;
    int nLast;
    void *pClass;
    int nHeading;

    nModule = func_02021980(pContext, &pArgs[0]);
    nA = func_02021980(pContext, &pArgs[1]);
    nB = func_02021980(pContext, &pArgs[2]);
    nPacked = pArgs[3].value;
    vPos.x = func_02021994(pContext, &pArgs[4]);
    vPos.y = func_02021994(pContext, &pArgs[5]);
    vPos.z = func_02021994(pContext, &pArgs[6]);
    nDegrees = func_02021980(pContext, &pArgs[7]);
    pArgs += 8;
    nLast = func_02021980(pContext, pArgs);

    pClass = func_ov002_02076468(nModule);
    nHeading = func_02020400(nDegrees << 0x10, 0x168);
    func_ov002_0207c3bc(pClass, (u16)nA, (u16)nB, (u16)nPacked,
                        (u8)(u16)((unsigned int)nPacked >> 0x10), &vPos,
                        (short)nHeading, (short)nLast);
    return 1;
}

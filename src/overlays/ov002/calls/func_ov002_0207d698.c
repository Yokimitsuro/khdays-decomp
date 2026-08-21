typedef unsigned short u16;

/* The id, the state field and the position share one addressed block whose
 * address the call already takes. That is a codegen device: it makes those
 * accesses conservative, so the compiler cannot sink the stacked argument
 * stores past them to fill later stalls.
 *
 * The two keys are deliberately OUTSIDE the block, and both have to be. The
 * original lifts nB's load to the very top of the argument setup and nA's by a
 * single slot, above the text store; a conservative load could do neither. The
 * declaration order of the two is not free either - nA must come first, or its
 * reload lands a slot late and the frame comes out wrong at 0x1a and 0x26. */
typedef struct {
    int nId;                        /* +0x00 */
    int nStateField;                /* +0x04 */
    int aPos[3];                    /* +0x08 */
} Ov002CmdFrame;

extern int func_02021980(void *pCtx, int nOperand);
extern int func_02021994(void *pCtx, int nOperand);
extern int func_02021948(void *pCtx, int nOperand);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int nId);
/* The narrow arguments are declared int here rather than u16 and u8: both are
 * already narrowed where the packed word is split, and a narrow parameter would
 * make the compiler narrow them a second time at the call. */
extern void func_ov002_0207bd88(int nOwner, u16 wA, u16 wB, int nStateField,
                                int nStateWidth, void *pPos, int nAngle,
                                int nText);

/* Script VM command: spawn a line element from the command's operands.
 *
 * Same family as the other spawn commands. The word baked into the command at
 * +0x1c splits into the state field and its width, the three fixed point
 * operands form the position, the raw angle is divided by 0x168, and the text
 * operand at +0x40 is optional - the short tag beside it says whether it is
 * there, and without it the element gets none.
 *
 * Always returns 1.
 */
int func_ov002_0207d698(void *pCtx, int nArgs)
{
    Ov002CmdFrame f;
    int nA;
    int nB;
    unsigned int nPacked;
    int nAngle;
    int nText;
    int nStateWidth;
    int nOwner;

    f.nId = func_02021980(pCtx, nArgs);
    nA = func_02021980(pCtx, nArgs + 0x08);
    nB = func_02021980(pCtx, nArgs + 0x10);

    nPacked = *(unsigned int *)((char *)nArgs + 0x1c);
    f.nStateField = (u16)nPacked;
    nStateWidth = (unsigned char)(u16)(nPacked >> 0x10);

    f.aPos[0] = func_02021994(pCtx, nArgs + 0x20);
    f.aPos[1] = func_02021994(pCtx, nArgs + 0x28);
    f.aPos[2] = func_02021994(pCtx, nArgs + 0x30);

    nAngle = (short)func_02020400(func_02021980(pCtx, nArgs + 0x38) << 0x10,
                                  0x168);

    if (*(short *)((char *)nArgs + 0x40) != 0) {
        nText = func_02021948(pCtx, nArgs + 0x40);
    } else {
        nText = 0;
    }

    nOwner = func_ov002_02076468(f.nId);

    func_ov002_0207bd88(nOwner, (u16)nA, (u16)nB, f.nStateField, nStateWidth,
                        &f.aPos[0], nAngle, nText);
    return 1;
}

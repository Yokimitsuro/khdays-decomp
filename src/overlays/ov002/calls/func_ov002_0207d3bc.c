typedef unsigned short u16;

extern int func_02021980(void *pCtx, int nOperand);
extern int func_02021994(void *pCtx, int nOperand);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int nId);
extern void func_ov002_0207a650(int nOwner, u16 wA, u16 wB, u16 wStateField,
                                int bStateWidth, void *pPos, int nAngle);

/* Script VM command: start a line element from the command's operands.
 *
 * Same family as the other spawn commands. The word baked into the command at
 * +0x1c is read before anything else here and splits into the state field and
 * its width, the three fixed point operands form the position, and the raw
 * angle is divided by 0x168 and kept signed.
 *
 * Always returns 1.
 */
int func_ov002_0207d3bc(void *pCtx, int nArgs)
{
    int aPos[3];
    unsigned int nPacked;
    int nId;
    int nA;
    int nB;
    int nAngle;
    int nOwner;

    nPacked = *(unsigned int *)((char *)nArgs + 0x1c);

    nId = func_02021980(pCtx, nArgs);
    nA = func_02021980(pCtx, nArgs + 0x08);
    nB = func_02021980(pCtx, nArgs + 0x10);

    aPos[0] = func_02021994(pCtx, nArgs + 0x20);
    aPos[1] = func_02021994(pCtx, nArgs + 0x28);
    aPos[2] = func_02021994(pCtx, nArgs + 0x30);

    nAngle = (short)func_02020400(func_02021980(pCtx, nArgs + 0x38) << 0x10,
                                  0x168);

    nOwner = func_ov002_02076468(nId);

    func_ov002_0207a650(nOwner, (u16)nA, (u16)nB, (u16)nPacked,
                        (unsigned char)(u16)(nPacked >> 0x10), &aPos[0],
                        nAngle);
    return 1;
}

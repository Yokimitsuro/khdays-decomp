typedef unsigned short u16;

extern int func_02021980(void *pCtx, int nOperand);
extern int func_02021994(void *pCtx, int nOperand);
extern int func_02020400(int a, int b);
extern int func_ov002_02076468(int nId);
extern void func_ov002_020796bc(int nOwner, u16 wA, u16 wB, u16 wLow,
                                int bHigh, void *pPos, short nAngle);

/* Script VM command: start a timed element from the command's operands.
 *
 * Same shape as the other spawn commands in this overlay: the plain integers
 * come out first, the word baked into the command at +0x1c splits into a
 * halfword and a byte, the three fixed point operands form the position, and
 * the raw angle is turned into a fixed point rotation by the 0x168 divisor.
 *
 * Always returns 1.
 */
int func_ov002_0207d0f0(void *pCtx, int nArgs)
{
    int aPos[3];
    int nId;
    int nA;
    int nB;
    unsigned int nPacked;
    int nRawAngle;
    u16 wAngle;
    int nOwner;

    nId = func_02021980(pCtx, nArgs);
    nA = func_02021980(pCtx, nArgs + 0x08);
    nB = func_02021980(pCtx, nArgs + 0x10);

    nPacked = *(unsigned int *)((char *)nArgs + 0x1c);

    aPos[0] = func_02021994(pCtx, nArgs + 0x20);
    aPos[1] = func_02021994(pCtx, nArgs + 0x28);
    aPos[2] = func_02021994(pCtx, nArgs + 0x30);

    nRawAngle = func_02021980(pCtx, nArgs + 0x38);
    wAngle = (u16)func_02020400(nRawAngle << 0x10, 0x168);

    nOwner = func_ov002_02076468(nId);

    func_ov002_020796bc(nOwner, (u16)nA, (u16)nB, (u16)nPacked,
                        (unsigned char)(u16)(nPacked >> 0x10), &aPos[0],
                        (short)wAngle);
    return 1;
}

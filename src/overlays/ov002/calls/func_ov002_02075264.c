typedef unsigned short u16;

extern int func_02021980(void *pCtx, int nArgs);
extern int func_02021994(void *pCtx, int nArgs);
extern int func_02020400(int a, int b);
extern void func_ov002_0206ba78(int *pPos, int nAngle);

/* Script VM command: aim the roster slots at a point, at a heading, or at both.
 *
 * Operand slots are eight bytes each and the leading halfword is the kind tag,
 * so a zero tag means the command left that operand out.  With the first three
 * present they read out as a fixed point position; with the fourth present the
 * raw degrees become a rotation through the same 0x168 divisor the other spawn
 * commands use.  A missing position passes no point at all, and a missing
 * heading passes -1.
 *
 * The cursor walks past all three position operands before the last one is
 * read, which is why the third read goes through its own address rather than
 * off the advanced cursor.  Advancing after the third read instead lets the
 * compiler pull the step out to the join, and the branch that skips the
 * position then loses its own step.
 *
 * Always returns 1.
 */
int func_ov002_02075264(void *pCtx, int nArgs)
{
    int aPos[3];
    int bNoPos;
    int nAngle;

    bNoPos = 0;
    if (*(short *)((char *)nArgs) == 0) {
        bNoPos = 1;
        nArgs += 0x18;
    } else {
        int nThird;

        aPos[0] = func_02021994(pCtx, nArgs);
        aPos[1] = func_02021994(pCtx, nArgs + 0x08);
        nThird = nArgs + 0x10;
        nArgs += 0x18;
        aPos[2] = func_02021994(pCtx, nThird);
    }

    if (*(short *)((char *)nArgs) == 0) {
        nAngle = -1;
    } else {
        nAngle = (u16)func_02020400(
            func_02021980(pCtx, nArgs) << 0x10, 0x168);
    }

    func_ov002_0206ba78(bNoPos ? 0 : &aPos[0], nAngle);
    return 1;
}

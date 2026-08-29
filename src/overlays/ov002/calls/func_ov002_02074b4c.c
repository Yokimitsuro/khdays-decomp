typedef unsigned short u16;

extern int func_02021980(void *pCtx, int nArgs);
extern int func_02021994(void *pCtx, int nArgs);
extern char *func_02021948(void *pCtx, int nArgs);
extern int func_02020400(int a, int b);
extern int func_ov002_0206b4bc(int nWho, int nWhat, int *pPos, int nAngle,
                               char *pName, int nFlags);
extern void func_ov002_0206ba78(int *pPos, int nAngle);

/* Script VM command: move one roster slot somewhere.
 *
 * Operand slots are eight bytes each and the leading halfword is the kind tag.
 * A zero third tag means the command carries the destination itself -- three
 * fixed point coordinates and a heading in degrees, turned into a rotation
 * through the same 0x168 divisor the other move commands use.  Otherwise the
 * operand names the destination instead.
 *
 * If the move is accepted the camera aim is cleared and the command reports 1;
 * a rejected move reports 0.
 *
 * The heading is only written on the branch that carries one, and the named
 * branch hands on whatever it happened to hold -- that is what the game does.
 */
int func_ov002_02074b4c(void *pCtx, int nArgs)
{
    int nWho;
    int nWhat;
    int aPos[3];
    char *pName;
    int nAngle;

    pName = 0;
    nWho = func_02021980(pCtx, nArgs);
    nWhat = func_02021980(pCtx, nArgs + 8);

    if (*(short *)((char *)nArgs + 0x10) == 0) {
        aPos[0] = func_02021994(pCtx, nArgs + 0x18);
        aPos[1] = func_02021994(pCtx, nArgs + 0x20);
        aPos[2] = func_02021994(pCtx, nArgs + 0x28);
        nArgs += 0x30;
        nAngle = (u16)func_02020400(func_02021980(pCtx, nArgs) << 0x10,
                                    0x168);
    } else {
        nArgs += 0x10;
        pName = func_02021948(pCtx, nArgs);
    }

    if (func_ov002_0206b4bc(nWho, nWhat, aPos, nAngle, pName, 0) != 0) {
        func_ov002_0206ba78(0, -1);
        return 1;
    }
    return 0;
}

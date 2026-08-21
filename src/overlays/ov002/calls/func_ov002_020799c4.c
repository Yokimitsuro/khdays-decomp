typedef unsigned short u16;

typedef struct {
    int nX;
    int nY;
    int nZ;
} Vec3;

extern int func_ov002_0206da70(void *pName);
extern void func_0202b930(char *pObj, int nRes, int a, int b);
extern void func_0202b450(char *pNode, Vec3 *pPos);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_ov002_020798a0(char *pElement);
extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202af2c(u16 *pNode);
extern void func_0202bedc(char *pObj, int bOn);
extern void func_0203355c(int nId);

/* Rebuild everything an element shows after its model has been rebound.
 *
 * The two cached vectors are read first because binding the model overwrites
 * the second one, which is put back straight after. The node is then moved to
 * the cached position, the first placement remembers the angle, the game-state
 * bit is re-read and the mode derived from it, the named bindings are
 * re-applied and the mode's track blended in. A mode with no track leaves the
 * object hidden. Finally the owner's own id is refreshed.
 */
void func_ov002_020799c4(char *pElement)
{
    char *pOwner;
    Vec3 vPos;
    Vec3 vSaved;
    u16 wAngle;
    unsigned int nState;
    signed char nTrack;

    pOwner = *(char **)(pElement + 8);
    vPos = *(Vec3 *)(pElement + 0xd0);
    vSaved = *(Vec3 *)(pElement + 0xdc);

    if (*(signed char *)(pOwner + 0x58) != 0) {
        func_0202b930(pElement + 0x1c, func_ov002_0206da70(pOwner + 0x58),
                      1, 4);
        *(Vec3 *)(pElement + 0xdc) = vSaved;
    }

    func_0202b450(pElement + 0x28, &vPos);

    wAngle = *(u16 *)(pElement + 0x18);
    if ((*(int *)(pElement + 0x28) & 0x20) == 0) {
        *(u16 *)(pElement + 0xa8) = wAngle;
        *(u16 *)(pElement + 0x2c) |= 0x20;
    }

    nState = ((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                           *(unsigned char *)(pElement + 0x16))
                             & 0xfffe) << 15) >> 16;
    /* One mutated index, not two constants: 0x1c2 is past the THUMB immediate
     * range so it lives in a register, and 0x1ce is reached by adding 0xc to
     * it. Naming 0x1ce any other way reloads a second pool word. */
    {
        int off = 0x1c2;

        pElement[off] = (char)(nState & 1);
        if (*(unsigned char *)(pElement + off) == 1) {
            off = off + 0xc;
            pElement[off] = 0;
        } else {
            off = off + 0xc;
            pElement[off] = 2;
        }
    }

    func_ov002_020798a0(pElement);

    if (*(signed char *)(pOwner + 0x58) != 0) {
        func_ov002_0207c618((short *)(pElement + 0x2c),
                            *(signed char *)(pElement + 0x1c3
                                + *(signed char *)(pElement + 0x1ce)), 0);
    }

    if (*(signed char *)(pOwner + 0x58) != 0) {
        nTrack = *(signed char *)(pElement + 0x1c3
                                  + *(signed char *)(pElement + 0x1ce));
        if (nTrack >= 0) {
            func_0202af2c((u16 *)(pElement + 0x2c));
            func_0202bedc(pElement + 0x1c,
                          (func_020235d0(*(u16 *)(pElement + 0x14),
                                         *(unsigned char *)(pElement + 0x16))
                           & 1) != 0);
        } else {
            func_0202bedc(pElement + 0x1c, 0);
        }
    }

    if (*(short *)(pOwner + 0x68) >= 0) {
        func_0203355c(*(short *)(pOwner + 0x68));
    }
}

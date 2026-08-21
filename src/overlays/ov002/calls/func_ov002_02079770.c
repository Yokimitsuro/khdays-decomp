typedef unsigned short u16;

extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202af2c(u16 *pNode);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_0202bedc(char *pObj, int bOn);
extern void func_02033d0c(int nA, int nB, char *pDst, int nFlag);

/* Put a timed element into its finishing phase.
 *
 * Stamps the phase, remembers which mode ended it and clears the elapsed
 * counter. When the owner allows it and the element is driving its table, the
 * track that mode selects is blended in from frame zero and the object follows
 * the game-state bit again - unless the mode has no track, in which case the
 * object is simply hidden.
 *
 * Finally, modes 3 and 1 each hand their own pair of owner ids to the fade.
 */
void func_ov002_02079770(char *pElement, unsigned char bMode)
{
    char *pOwner;
    signed char nTrack;
    int nState;
    short nA;
    short nB;

    pOwner = *(char **)(pElement + 8);

    *(unsigned char *)(pElement + 0x1c1) = 2;
    *(unsigned char *)(pElement + 0x1ce) = bMode;
    *(int *)(pElement + 0x1d0) = 0;

    if (*(signed char *)(pOwner + 0x58) != 0 &&
        (*(u16 *)(pElement + 0x12) & 4) != 0) {

        nTrack = *(signed char *)(pElement + 0x1c3
                                  + *(signed char *)(pElement + 0x1ce));
        if (nTrack != -1) {
            func_ov002_0207c618((short *)(pElement + 0x2c), nTrack, 0);
            func_0202af2c((u16 *)(pElement + 0x2c));
            nState = func_020235d0(*(u16 *)(pElement + 0x14),
                                   *(unsigned char *)(pElement + 0x16));
            func_0202bedc(pElement + 0x1c, (nState & 1) != 0);
        } else {
            func_0202bedc(pElement + 0x1c, 0);
        }
    }

    nA = *(short *)(pOwner + 0x68);
    if (nA >= 0) {
        if (*(signed char *)(pElement + 0x1ce) == 3) {
            nB = *(short *)(pOwner + 0x6a);
            if (nB >= 0) {
                func_02033d0c(nA, nB, pElement + 0xd0, 0);
            }
        } else if (*(signed char *)(pElement + 0x1ce) == 1) {
            nB = *(short *)(pOwner + 0x6c);
            if (nB >= 0) {
                func_02033d0c(nA, nB, pElement + 0xd0, 0);
            }
        }
    }
}

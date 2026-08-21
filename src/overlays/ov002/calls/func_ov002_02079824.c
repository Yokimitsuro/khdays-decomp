typedef unsigned short u16;

extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_0202bedc(char *pObj, int bOn);

/* Put a timed element back at the start of its cycle.
 *
 * Picks the mode from the state bit the element last saw - 0 when it was set,
 * 2 otherwise - and, when the owner allows it and the element is driving its
 * table, blends that mode's track in from frame zero and lets the object
 * follow the game-state bit again; a mode with no track just hides it.
 * Finally the elapsed counter and the phase are cleared.
 */
void func_ov002_02079824(char *pElement)
{
    char *pOwner;
    signed char nTrack;
    int nState;

    pOwner = *(char **)(pElement + 8);

    *(unsigned char *)(pElement + 0x1ce) =
        (*(unsigned char *)(pElement + 0x1c2) == 1) ? 0 : 2;

    if (*(signed char *)(pOwner + 0x58) != 0 &&
        (*(u16 *)(pElement + 0x12) & 4) != 0) {

        nTrack = *(signed char *)(pElement + 0x1c3
                                  + *(signed char *)(pElement + 0x1ce));
        if (nTrack != -1) {
            func_ov002_0207c618((short *)(pElement + 0x2c), nTrack, 0);
            nState = func_020235d0(*(u16 *)(pElement + 0x14),
                                   *(unsigned char *)(pElement + 0x16));
            func_0202bedc(pElement + 0x1c, (nState & 1) != 0);
        } else {
            func_0202bedc(pElement + 0x1c, 0);
        }
    }

    *(int *)(pElement + 0x1d0) = 0;
    *(unsigned char *)(pElement + 0x1c1) = 0;
}

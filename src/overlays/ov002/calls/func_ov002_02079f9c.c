typedef unsigned short u16;

typedef int (*Ov002ReserveProc)(char *pCtx, unsigned char bLane, int nKind,
                                u16 wSlot);

extern int func_020235d0(u16 nId, unsigned char nSlot);
extern char *func_01fffde0(unsigned char nIndex);
extern int func_ov002_0206d144(short nId);
extern char *func_ov002_0206d194(short nIndex);
extern void func_ov022_02088c10(unsigned char nIndex, int nSlot, int nLane);
extern void func_ov002_02079e68(char *pElement);

/* Hand this element's reserved slot over to a new source.
 *
 * Runs only while the element's game state bit is clear and it has reached
 * stage 3. It asks the owner's reserve proc whether the new source may take
 * the slot; a missing proc counts as a yes. On a refusal it tells the ov022
 * owner and leaves the element alone, otherwise it retires the widget, clears
 * the present bit and latches the new source.
 *
 * The three call arguments are read into locals before the null test on
 * purpose: the original evaluates them unconditionally, above the branch. The
 * order of those three assignments is what fixes the schedule - slot, lane,
 * then kind. */
void *func_ov002_02079f9c(char *pElement, unsigned char *pSource)
{
    unsigned int nState;
    char *pEntry;
    char *pKey;
    char *pCtx;
    Ov002ReserveProc pProc;
    unsigned char bLane;
    int nKind;
    u16 wSlot;
    int nResult;

    nState = ((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                   *(unsigned char *)(pElement + 0x16))
                             & 0xfffe) << 15) >> 16;

    if ((nState & 1) == 0 && *(unsigned char *)(pElement + 0x1b4) == 3) {
        pEntry = func_01fffde0(*pSource);
        pKey = func_ov002_0206d194(
            (short)func_ov002_0206d144(*(short *)(pElement + 0x1b6)));

        pCtx = *(char **)(pEntry + 0x4ec);
        pProc = *(Ov002ReserveProc *)(pCtx + 0x1c0);
        wSlot = *(u16 *)(pKey + 0x40);
        bLane = *(unsigned char *)(pElement + 0x1b9);
        nKind = *(short *)(pKey + 0x42) & 0xff;

        if (pProc == 0) {
            nResult = 1;
        } else {
            nResult = pProc(pCtx, bLane, nKind, wSlot);
        }

        if (nResult == 0) {
            func_ov022_02088c10(*pSource, *(short *)(pKey + 0x40),
                                *(signed char *)(pElement + 0x1b9));
            return 0;
        }

        func_ov002_02079e68(pElement);
        *(u16 *)(pElement + 0x12) &= ~8;
        *(unsigned char *)(pElement + 0x1b8) = *pSource;
    }

    return 0;
}

typedef unsigned short u16;

typedef void (*Ov002NotifyProc)(char *pBase, int nUnit, int nKind, int nId);

extern int func_ov002_0207687c(void);
extern int func_ov002_0207c700(char *pElement, u16 *pTable, int nDelta,
                               int nFlag, int nLimit, int *pCounter);
extern short func_02030788(void);
extern int func_ov002_0206b758(void);
extern int func_ov002_0206b864(void);
extern char *func_01fffde0(int nIndex);
extern int func_ov002_0206d144(short nKey);
extern char *func_ov002_0206d194(short nIndex);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_020235e8(u16 nId, unsigned char nSlot, int nValue);
extern void func_ov002_02076bd8(char *pElement, int nFlag);
extern void func_0202bc30(char *pNode);
extern void *func_ov002_0207cea4(char *pElement);

/* Drive an element that is being taken down.
 *
 * The entry table runs to its limit while the countdown climbs. Once the
 * element reaches the reporting state and the counter passes its threshold,
 * the local player tells the session which unit finished, and the element
 * moves on to the next state. When the table is finally done the game-state
 * field is reduced to its low bit plus two, the node's resources are released
 * and the element hands itself to the retired handler.
 */
void *func_ov002_0207a0f0(char *pElement)
{
    int nDelta;
    int bDone;
    char *pSession;
    char *pEntry;
    Ov002NotifyProc pfnNotify;
    u16 wId;
    short nKind;
    unsigned char bUnit;
    int nMasked;
    int nState;

    nDelta = func_ov002_0207687c();
    bDone = (func_ov002_0207c700(pElement, (u16 *)(pElement + 0x3c), nDelta, 0,
                                 0x1e000, (int *)(pElement + 0x1b0)) == 0);

    if (*(unsigned char *)(pElement + 0x1b4) == 5
        && *(int *)(pElement + 0x1b0) >= 0xc000) {

        if (func_02030788() == 0) {
            if (func_ov002_0206b758() != 0 && func_ov002_0206b864() != 0) {

                pSession = func_01fffde0(*(unsigned char *)(pElement + 0x1b8));
                pEntry = func_ov002_0206d194(
                    (short)func_ov002_0206d144(*(short *)(pElement + 0x1b6)));

                /* All four values are read before the callback pointer is
                 * tested, and in this order: the original schedules them into
                 * the load-use slots ahead of the branch. */
                wId = *(u16 *)(pEntry + 0x40);
                nKind = *(short *)(pEntry + 0x42);
                nMasked = nKind & 0xff;
                bUnit = *(unsigned char *)(pElement + 0x1b9);
                pfnNotify = *(Ov002NotifyProc *)(
                    *(char **)(pSession + 0x4ec) + 0x1bc);
                if (pfnNotify != 0) {
                    pfnNotify(*(char **)(pSession + 0x4ec), bUnit, nMasked,
                              wId);
                }
            } else {
                return 0;
            }
        }

        *(unsigned char *)(pElement + 0x1b4) = 6;
    }

    if (bDone) {
        nState = func_020235d0(*(u16 *)(pElement + 0x14),
                               *(unsigned char *)(pElement + 0x16));
        func_020235e8(*(u16 *)(pElement + 0x14),
                      *(unsigned char *)(pElement + 0x16),
                      (u16)((nState & ~0xfffe) | 2));
        func_ov002_02076bd8(pElement, 0);
        func_0202bc30(pElement + 0x2c);
        *(unsigned char *)(pElement + 0x1b4) = 7;
        return func_ov002_0207cea4;
    }

    return 0;
}

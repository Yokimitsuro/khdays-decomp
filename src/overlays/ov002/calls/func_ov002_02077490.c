extern int func_02030788(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int nState);
extern int func_ov002_02072754(int nSlot);
extern void func_02033b24(int nBank, int nSound);
extern void func_02033d0c(int nBank, int nSound, void *pPos, int nOwner);

/* Play the sound a slot action makes.
 *
 * The bank offset is the actor's own index times seven, so each actor has its
 * own run of seven action sounds and the action kind picks which of them:
 * kinds 0 and 1 share one, 2 and 3 have their own, and anything else falls to
 * a common one. Kind 0xf is not part of that run at all - it takes a fixed
 * sound and drops the per actor offset entirely.
 *
 * The local seat's own actor plays it flat, unless bit 16 of its flag word is
 * up. Anyone else's plays it positionally from +0x48c, and only when their
 * slot table byte matches the one the active state resolves to.
 *
 * The bank is written into nBank inside the guard rather than passed as a
 * literal, which is what keeps it out of the way of the flag word's register
 * and lets it fill the load's delay slot; the pragma is what stops that store
 * from being propagated back into the call.
 */
#pragma opt_dead_assignments off

void func_ov002_02077490(int pOwner, int nKind)
{
    char *pActor;
    int nBase;
    int nSound;
    int nSlot;
    int nOther;
    int nBank;

    pActor = *(char **)(pOwner + 0x18c);
    nBase = *(unsigned char *)(pActor + 9) * 7;

    switch (nKind) {
    case 0:
    case 1:
        nSound = 0xe;
        break;
    case 2:
        nSound = 0xb;
        break;
    case 3:
        nSound = 0xd;
        break;
    case 0xf:
        nSound = 0x3e;
        nBase = 0;
        break;
    default:
        nSound = 0xc;
        break;
    }

    if (*(unsigned char *)(pActor + 8) == func_02030788()
            && (nBank = 0, *(int *)pActor & 0x10000) == 0) {
        func_02033b24(nBank, nSound + nBase);
        return;
    }

    nSlot = func_ov002_02072754(*(short *)(pActor + 0x66));
    nOther = func_ov002_02072754(func_ov022_02088474(func_01fffe14()));
    if (nOther == nSlot) {
        func_02033d0c(0, nSound + nBase, pActor + 0x48c, 0);
    }
}

#pragma opt_dead_assignments on

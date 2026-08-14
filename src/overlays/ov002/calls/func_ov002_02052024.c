typedef unsigned short u16;

/* The actor's animation state block. The table array and its count were named
   by the teardown at 02051fc8; the mode byte and the changed flag are proved
   here. */
typedef struct Ov002AnimStateBlock {
    char nCurrentMode;      /* mode the actor is playing right now */
    char pad0001[3];
    int bModeChanged;       /* raised whenever the mode is replaced */
    char pad0008[0x44];
    char *pTables;          /* +0x4c, animation tables of stride 0x24 */
    int nTableCount;        /* +0x50 */
} Ov002AnimStateBlock;

extern int func_ov002_02052270(void *pActor, void *pAnimState, int nNewMode);

/* The blend argument of both bind calls is a short. The narrowing therefore
   belongs to the call and not to a cast in this file, which is what makes the
   blend code stay live in a callee-saved register. */
extern void func_0202accc(void *pAnim, u16 nTrack, void *pTable, short nBlend);
extern void func_0202ad74(void *pAnim, u16 nTrack, void *pTable, short nBlend,
                          int nFlags);
extern void func_01fff774(void *pAnim, u16 nTrack, int nFrame);

/* Put an actor into a new animation mode.

   Modes 0x1e through 0x2d bind from the shared table array the state block
   carries, indexed by the blend code; kind 2 and every other mode bind from
   the actor's own inline table and blend by the code itself. */
void func_ov002_02052024(char *pActor, char *pAnimState, int nNewMode,
                         int nKind, int nFlags) {
    int nBlendCode;
    int nTrack;

    if (pActor[1] == 0 || *pAnimState == nNewMode) {
        return;
    }
    nBlendCode = func_ov002_02052270(pActor, pAnimState, nNewMode);

    if (nNewMode >= 0x1e && nNewMode < 0x2e && nKind != 2) {
        int nOffset = nBlendCode * 0x24;

        for (nTrack = 1; nTrack <= 3; nTrack++) {
            func_0202accc(pActor + 4, (u16)nTrack,
                          ((Ov002AnimStateBlock *)pAnimState)->pTables + nOffset,
                          0);
        }
        func_0202ad74(pActor + 4, 0,
                      ((Ov002AnimStateBlock *)pAnimState)->pTables + nOffset, 0,
                      nFlags);
    } else {
        for (nTrack = 1; nTrack <= 3; nTrack++) {
            func_0202accc(pActor + 4, (u16)nTrack, pActor + 0x13c, nBlendCode);
        }
        func_0202ad74(pActor + 4, 0, pActor + 0x13c, nBlendCode, nFlags);

        if (nKind == 1 && nNewMode == 3) {
            int nFrame;

            /* Written as a switch on purpose: spelled as a chain of
               equalities mwcc notices 0x13 and 0x14 are adjacent and emits a
               range test instead of the compare chain. */
            switch (*pAnimState) {
            case 0xe:
            case 0x13:
            case 0x14:
                nFrame = 0;
                break;
            default:
                nFrame = 0xc000;
                break;
            }

            if ((*(u16 *)(pActor + 4) & 4) != 0) {
                func_01fff774(pActor + 4, 0, nFrame);
            } else {
                for (nTrack = 0; nTrack <= 3; nTrack++) {
                    func_01fff774(pActor + 4, (u16)nTrack, nFrame);
                }
            }
        }
    }

    *pAnimState = (char)nNewMode;
    *(int *)(pAnimState + 4) = 1;
}

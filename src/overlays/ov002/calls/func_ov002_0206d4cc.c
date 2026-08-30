/* Ov002_UpdatePendingCaptionSequence; THUMB, 464 bytes, 20 relocs.
 * Queue caption ids, normalize both displays, dim the main display while
 * caption mode runs, then restore brightness and session/input state.
 * Returns one while busy and zero when complete.
 *
 * Keep nEntry materialized before the actor flag test. Propagation otherwise
 * folds it into the callee argument and changes the ROM register liveness.
 * The display loop is bottom-tested, as in the ROM.
 */
typedef struct Ov002PendingCaptionState {
    unsigned char pad00[0x51];
    unsigned char bPhase;
    short anCaptionIds[8];
    unsigned char pad62[2];
    int nBrightnessFx;
    signed char nCaptionIndex;
    unsigned char pad69[3];
} Ov002PendingCaptionState;

typedef struct Ov002SessionActorFlags {
    unsigned char pad000[0x464];
    unsigned int dwStateFlags;
} Ov002SessionActorFlags;

extern unsigned char *data_ov002_0207fa00;
extern int func_ov002_020575f8(int nCaptionId);
extern int func_0201e428(void);
extern int func_0201e438(void);
extern int func_02023c40(void);
extern void func_0201e374(int nBrightness);
extern void func_0201e3cc(int nBrightness);
extern int func_ov002_02062f34(void);
extern void func_ov002_0206aae4(int bActive, unsigned int nParts);
extern Ov002SessionActorFlags *func_01fffde0(int nIndex);
extern int func_ov022_020886d0(int nIndex);
extern int func_ov022_020882e0(int nIndex);
extern void func_02020878(int bEnabled);

#pragma opt_propagation off
int func_ov002_0206d4cc(void)
{
    Ov002PendingCaptionState *pState =
        (Ov002PendingCaptionState *)(data_ov002_0207fa00 + 0x8c94);
    int bBusy = 1;
    int nScreen, nSettled, nBrightness;
    unsigned int nFlags;
    int nEntry;

    switch (pState->bPhase) {
    case 0:
        while (pState->anCaptionIds[pState->nCaptionIndex] >= 0) {
            if (!func_ov002_020575f8(pState->anCaptionIds[pState->nCaptionIndex]))
                return 1;
            pState->nCaptionIndex++;
        }
        pState->bPhase++;
        break;
    case 1:
        nSettled = 0;
        nScreen = 0;
        do {
            nBrightness = (nScreen == 0 ? func_0201e428() : func_0201e438()) << 12;
            if (nBrightness < 0) {
                nBrightness += func_02023c40() == 1 ? 0x1800 : 0x1000;
                if (nBrightness >= 0) {
                    nBrightness = 0;
                    nSettled++;
                }
            } else {
                nBrightness -= func_02023c40() == 1 ? 0x1800 : 0x1000;
                if (nBrightness <= 0) {
                    nBrightness = 0;
                    nSettled++;
                }
            }
            if (nScreen == 0)
                func_0201e374(nBrightness >> 12);
            else
                func_0201e3cc(nBrightness >> 12);
            nScreen++;
        } while (nScreen < 2);
        if (nSettled == 2) {
            pState->bPhase++;
            pState->nBrightnessFx = func_0201e428() << 12;
        }
        break;
    case 2:
        pState->nBrightnessFx -= func_02023c40() == 1 ? 0x1800 : 0x1000;
        if (pState->nBrightnessFx <= -0x8000) {
            pState->nBrightnessFx = -0x8000;
            pState->bPhase++;
        }
        func_0201e374(pState->nBrightnessFx >> 12);
        break;
    case 3:
        if (func_ov002_02062f34())
            pState->bPhase++;
        break;
    case 4:
        pState->nBrightnessFx = func_0201e428() << 12;
        pState->nBrightnessFx += func_02023c40() == 1 ? 0x1800 : 0x1000;
        if (pState->nBrightnessFx >= 0) {
            bBusy = 0;
            pState->nBrightnessFx = 0;
            pState->bPhase = 0xff;
            func_ov002_0206aae4(bBusy, 0xff);
        }
        func_0201e374(pState->nBrightnessFx >> 12);
        break;
    default:
        bBusy = 0;
    }
    if (!bBusy && (nFlags = func_01fffde0(0)->dwStateFlags,
                  nEntry = 0, (nFlags & 0x10000000) == 0)
        && !func_ov022_020886d0(nEntry) && func_ov022_020882e0(0) > 0)
        func_02020878(1);
    return bBusy;
}
#pragma opt_propagation on

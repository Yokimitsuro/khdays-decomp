#include "nitro/types.h"
#include "game/engine.h"

typedef s64 (*Ov002EntrySampleFn)(void);

typedef struct Ov002PauseSlot {
    int nObject;
    char pad004[0x68];
    int nClockStart;
    int nClockLimit;
    char pad074[4];
} Ov002PauseSlot;
typedef struct Ov002RootContext {
    char pad0000[0x8c94];
    Ov002PauseSlot pause;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void Ov002_CreateAndRestoreHud(void);
extern void Ov002_CreatePauseObjectOnce(void);
extern u8 Ov002_AddPanelCounter(u64, int, Ov002EntrySampleFn);
extern u8 Ov002_AddPanelValue(int);
extern s64 Ov002_GetStartTicks(void);
extern s64 Ov002_GetEndTicks(void);
extern s64 Ov002_GetTimeoutTicks(void);
extern s64 Ov002_GetTimeoutRemaining(void);
extern s64 Ov002_GetRemainingTicks(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);

/* Dispatches HUD creation, sampled time counters and value-only entries.
 * Commands 1/2 convert signed milliseconds to ticks before sampling; 6/7
 * capture a clock baseline and optionally replace the remaining-time limit.
 * The unsigned division helper is named explicitly to preserve its ROM alias. */
void Ov002_DispatchHudCounterCommand(int nCommand, int nValue, int nSampler)
{
    Ov002PauseSlot *pPause;
    u64 nTicks;

    pPause = &data_ov002_0207fa00->pause;
    switch (nCommand) {
    case 0:
        switch (nValue) {
        case 0:
            Ov002_CreateAndRestoreHud();
            break;
        case 1:
            Ov002_CreatePauseObjectOnce();
            break;
        }
        break;
    case 1:
        if (pPause->nObject != -1) {
            nTicks = (u64)((s64)nValue * 33514) >> 6;
            switch (nSampler) {
            case 0:
                Ov002_AddPanelCounter(nTicks, 1, Ov002_GetStartTicks);
                break;
            case 1:
                Ov002_AddPanelCounter(nTicks, 1, Ov002_GetEndTicks);
                break;
            case 2:
                Ov002_AddPanelCounter(nTicks, 1, Ov002_GetTimeoutTicks);
                break;
            }
        }
        break;
    case 2:
        if (pPause->nObject != -1) {
            nTicks = (u64)((s64)nValue * 33514) >> 6;
            switch (nSampler) {
            case 0:
                Ov002_AddPanelCounter(nTicks, 2, Ov002_GetStartTicks);
                break;
            case 1:
                Ov002_AddPanelCounter(nTicks, 2, Ov002_GetEndTicks);
                break;
            case 2:
                Ov002_AddPanelCounter(nTicks, 2, Ov002_GetTimeoutTicks);
                break;
            }
        }
        break;
    case 6:
        if (nValue == 0) {
            pPause->nClockStart = func_02020368((u64)Ov002_GetTimeoutTicks() << 6, 33514);
        }
        Ov002_AddPanelCounter(0, 0, Ov002_GetTimeoutRemaining);
        break;
    case 7:
        if (nValue == 0) {
            pPause->nClockStart = func_02020368((u64)Ov002_GetTimeoutTicks() << 6, 33514);
        }
        if (nSampler >= 0) {
            pPause->nClockLimit = nSampler;
        }
        Ov002_AddPanelCounter(0, 0, Ov002_GetRemainingTicks);
        break;
    case 5:
        GameState_SetField(0x20a9, 4, (u16)(Ov002_AddPanelValue((s16)nValue) + 1));
        break;
    }
}

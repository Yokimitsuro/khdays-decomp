/* Card / save-check polling state for the Load screen.
 *
 * Sub-state 0 waits out a delay measured against the 64-bit tick counter, then polls
 * the check; result 3 raises the busy/phase pair and parks in sub-state 3, any other
 * non-negative result starts the three-step scan. Sub-state 1 runs that scan one step
 * per frame and, when the third step reports 2, clears the current slot, recounts how
 * many slots hold data and refreshes the selection draw. Sub-state 2 waits for A or B
 * and returns the scene to state 2.
 *
 * CODEGEN NOTES:
 *
 *  1. The two 16-bit halves at +0x6a48 are BITFIELDS (`unsigned wBusy : 16;
 *     unsigned wPhase : 16;`), not two u16 members. mwcc emits the ROM's
 *     read/mask/or/write on the whole word for a bitfield store; two u16 members
 *     would give plain strh.
 *
 *  2. The 64-bit divide is called EXPLICITLY as func_02020368 rather than written as
 *     `(t << 6) / 0x82ea`. The division operator produces identical bytes, but mwcc
 *     emits the relocation against its runtime helper name `_ll_sdiv`, and the delink
 *     config knows that address as func_02020368 -- so the bytes match and
 *     verify_idx reports a reloc mismatch. Where a compiler runtime helper is
 *     involved, the call has to be spelled with the address symbol the config uses.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov000CardSlot {
    u8  pad_00[0x10];
    int nSlotKind;
    int nSlotState;
    u8  pad_18[8];
} Ov000CardSlot;

typedef struct Ov000CardContext {
    u8  pad_0000[0x4ad0];
    int nActiveState;
    u8  pad_4ad4[0x4adc - 0x4ad4];
    int nAdvance;
    int nCheckState;
    u8  pad_4ae4[0x4afb - 0x4ae4];
    u8  bStepDone;
    u8  pad_4afc[0x4b08 - 0x4afc];
    int nPageIndex;
    u8  pad_4b0c[0x4b10 - 0x4b0c];
    Ov000CardSlot aSlot[3];
    u8  pad_4b70[0x4d94 - 0x4b70];
    int nIdleTicks;
    u8  pad_4d98[0x6a48 - 0x4d98];
    unsigned wBusy : 16;
    unsigned wPhase : 16;
    int nSlotCount;
    int nRetry;
    u8  pad_6a54[0x6a58 - 0x6a54];
    u32 dwCheckDelay;
} Ov000CardContext;

extern Ov000CardContext *data_ov000_0205ac24;
extern u16 gPadPressed;

extern s64  OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int  Ov000_PollSaveCheck(void);
extern unsigned char  Ov000_UpdateLoadState(int step);
extern void Ov000_RefreshSelectionGroupDraw(void);
extern void Ov000_UpdateNumberDisplays(void);
extern void Ov000_UpdateMenuMarkers(int a, int b, int c);
extern void Ov000_PlaceCursorByMode(int mode, int page);

void Ov000_PollSaveCheckState(void)
{
    Ov000CardContext *ctx = data_ov000_0205ac24;
    int done = 0;
    int i;

    switch (ctx->nCheckState) {
    case 0:
        {
            int r;
            s64 t = OS_GetTick() << 6;
            if ((u64)func_02020368(t, 0x82ea)
                    < data_ov000_0205ac24->dwCheckDelay) {
                r = -1;
            } else {
                r = Ov000_PollSaveCheck();
            }
            if (r == 3) {
                data_ov000_0205ac24->wBusy = 1;
                data_ov000_0205ac24->wPhase = 1;
                data_ov000_0205ac24->nIdleTicks = 0;
                data_ov000_0205ac24->nCheckState = 3;
                return;
            }
            if (r >= 0) {
                data_ov000_0205ac24->nCheckState = 1;
                data_ov000_0205ac24->nAdvance = 0;
                data_ov000_0205ac24->nRetry = 0;
            }
        }
        break;
    case 1:
        if (Ov000_UpdateLoadState(ctx->nAdvance) == 2) {
            data_ov000_0205ac24->nAdvance++;
            data_ov000_0205ac24->bStepDone = 0;
            if (data_ov000_0205ac24->nAdvance >= 3) {
                Sleep_Unblock();
                data_ov000_0205ac24->nCheckState = 2;
                data_ov000_0205ac24->nIdleTicks = 0;
                data_ov000_0205ac24->aSlot[data_ov000_0205ac24->nPageIndex].nSlotKind = 0;
                data_ov000_0205ac24->aSlot[data_ov000_0205ac24->nPageIndex].nSlotState = 0;
                data_ov000_0205ac24->nSlotCount = 0;
                for (i = 0; i < 3; i++) {
                    if (data_ov000_0205ac24->aSlot[i].nSlotKind > 0) {
                        data_ov000_0205ac24->nSlotCount++;
                    }
                }
                Ov000_RefreshSelectionGroupDraw();
            }
        }
        break;
    case 2:
        switch (gPadPressed) {
        case 1:
            done = 1;
            PlaySound(0, 1);
            break;
        case 2:
            done = 1;
            PlaySound(0, 3);
            break;
        }
        break;
    }

    if (done == 0) {
        return;
    }
    Ov000_UpdateMenuMarkers(0, 0, 1);
    Ov000_RefreshSelectionGroupDraw();
    Ov000_UpdateNumberDisplays();
    Ov000_PlaceCursorByMode(1, data_ov000_0205ac24->nPageIndex);
    data_ov000_0205ac24->nIdleTicks = 0;
    data_ov000_0205ac24->nActiveState = 2;
}

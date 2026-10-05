/* Shows or hides the camp-menu status entries (four main, two secondary); when shown, draws the
 * counter and the play time (saved time plus the ticks since it was latched), otherwise runs the
 * closing callback of tag 2. */

#include "nitro/types.h"

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
} Ov009GameState;

extern Ov009GameState *volatile gGameState;
extern const int data_ov008_0208f4f0[4];
extern const int data_ov008_0208f4e8[2];

extern int Ov008_GetContext(void);
extern int Ov008_GetCtxBlock9500(void);
extern int Ov008_FindEntryById(int manager, int id);
extern void Ov008_SetEntrySlotsVisible(int manager, int entry, int visible);
extern void Ov008_DrawNumberDigits(int value);
extern long long OS_GetTick(void);
extern long long Ov008_GetLatchedTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern void Ov008_RenderTimeDigits(u32 value);
extern int Ov008_FindEntryByTag(int tracker, int tag);
extern void Ov008_TagTracker_InvokeCallback(int tracker, int entry);

void Ov008_SetMenuEntriesVisible(int visible, int secondaryVisible)
{
    int manager = Ov008_GetContext();
    int tracker = Ov008_GetCtxBlock9500();
    u8 i;

    for (i = 0; i < 4; i++) {
        int entry = Ov008_FindEntryById(
            manager, data_ov008_0208f4f0[i]);
        Ov008_SetEntrySlotsVisible(manager, entry, visible);
    }

    for (i = 0; i < 2; i++) {
        int entry = Ov008_FindEntryById(
            manager, data_ov008_0208f4e8[i]);
        Ov008_SetEntrySlotsVisible(manager, entry, secondaryVisible);
    }

    if (visible != 0) {
        long long elapsed;

        Ov008_DrawNumberDigits(gGameState->value8);
        elapsed = OS_GetTick() - Ov008_GetLatchedTick();
        Ov008_RenderTimeDigits(
            (u32)(gGameState->value0 +
                  func_02020368(elapsed << 6, 0x1ff6210)));
    } else {
        int entry = Ov008_FindEntryByTag(tracker, 2);
        Ov008_TagTracker_InvokeCallback(tracker, entry);
    }
}

/* Confirm prompt for the Load screen, and the path that actually loads a save.
 *
 * Left/right move a two-item cursor; A on item 0 cancels back to state 2, A on item 1
 * commits (state 6), B cancels. State 6 is where the save is read: for a real slot it
 * calls Ov000_MarkSceneReady with the page index, and for the extra entry it opens the
 * message container, pulls the file out of the archive through a packed handle built
 * from the header address, copies the 7340-byte blob straight into the global game
 * state, frees both buffers and raises flag 0x200b. That whole-struct assignment is
 * the game actually being loaded, so this function is the hand-off from the menu slice
 * to gameplay.
 *
 * CODEGEN NOTES:
 *
 *  1. The save blob must be a WORD-typed array. As `u8 aData[0x1cac]` the copy has
 *     alignment 1 and mwcc emits a byte loop (ldrb/strb, two bytes an iteration); as
 *     `u32 aData[0x1cac / 4]` it emits the ROM's `ldm/stm` block move of four words an
 *     iteration plus a three-word tail. Same bytes copied, completely different code,
 *     and the element type is the only thing that says so.
 *
 *  2. Both dispatches are switches whose case bodies mwcc lays out in SOURCE order
 *     while testing in case-value order, so the ROM's layout pins which case is
 *     written first: 0x20 before 0x10 here. Same rule as
 *     src/overlays/scenes/ov000_title/Ov000_HandleSaveSlotInput.c.
 *
 *  3. The A-button test is written `if (cursor != 0) { commit } else { cancel }`. The
 *     ROM puts the cancel body out of line, which is what the inverted test gives;
 *     written the natural way round the two blocks swap places.
 */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef struct Ov000GameSave {
    u32 aData[0x1cac / 4];
} Ov000GameSave;

typedef struct Ov000ConfirmContext {
    u8  pad_0000[0x4acc];
    u8  bExtraEntryActive;
    u8  bExtraEntryTaken;
    u8  pad_4ace[2];
    int nActiveState;
    int nExtraEntryPending;
    u8  pad_4ad8[0x4af8 - 0x4ad8];
    u16 wHeldKeys;
    u8  pad_4afa[0x4b08 - 0x4afa];
    int nPageIndex;
    u8  pad_4b0c[0x4b70 - 0x4b0c];
    int nCursorRow;
    u8  pad_4b74[0x4d94 - 0x4b74];
    int nIdleTicks;
} Ov000ConfirmContext;

extern Ov000ConfirmContext *data_ov000_0205ac24;
extern u16 gPadPressed;
extern u8  gOv000TtlTtlPath_3[];
extern Ov000GameSave *gGameState;

extern void  Ov000_PlaceCursorByMode(int mode, int row);
extern void  Ov000_UpdateMenuMarkers(int a, int b, int c);
extern void  Ov000_PushSubWidgetValue(int a);
extern void  Ov000_MarkSceneReady(int page);
extern u32  *Msg_OpenContainerAndReadHeader(u8 *name, int heap);
extern void *Archive_LoadFile(u32 handle, int heap);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);

void Ov000_HandleLoadConfirm(void)
{
    Ov000ConfirmContext *ctx = data_ov000_0205ac24;
    int next = 0;

    switch (ctx->wHeldKeys) {
    case 0x20:
        if (ctx->nCursorRow != 1) {
            ctx->nCursorRow = 1;
            Ov000_PlaceCursorByMode(0, data_ov000_0205ac24->nCursorRow);
            PlaySound(0, 0);
        }
        break;
    case 0x10:
        if (ctx->nCursorRow != 0) {
            ctx->nCursorRow = 0;
            Ov000_PlaceCursorByMode(0, data_ov000_0205ac24->nCursorRow);
            PlaySound(0, 0);
        }
        break;
    default:
        switch (gPadPressed) {
        case 1:
            if (ctx->nCursorRow != 0) {
                next = 6;
                if (ctx->nExtraEntryPending == 0 && ctx->bExtraEntryActive != 0) {
                    PlaySound(0, 1);
                }
            } else {
                next = 2;
                PlaySound(0, 3);
            }
            break;
        case 2:
            next = 2;
            PlaySound(0, 3);
            break;
        }
        break;
    }

    if (next == 0) {
        return;
    }

    switch (next) {
    case 6:
        if (data_ov000_0205ac24->nExtraEntryPending == 0
            && data_ov000_0205ac24->bExtraEntryActive != 0
            && data_ov000_0205ac24->bExtraEntryTaken == 0) {
            data_ov000_0205ac24->nExtraEntryPending = 1;
            next = 3;
            Ov000_PushSubWidgetValue(0);
            data_ov000_0205ac24->nCursorRow = 0;
            Ov000_PlaceCursorByMode(0, data_ov000_0205ac24->nCursorRow);
        }
        break;
    case 2:
        Ov000_UpdateMenuMarkers(0, 0, 1);
        data_ov000_0205ac24->nCursorRow = 0;
        Ov000_PlaceCursorByMode(1, data_ov000_0205ac24->nPageIndex);
        Ov000_PushSubWidgetValue(0);
        data_ov000_0205ac24->nExtraEntryPending = 0;
        break;
    }

    if (next == 6) {
        if (data_ov000_0205ac24->nPageIndex < 3) {
            Ov000_MarkSceneReady(data_ov000_0205ac24->nPageIndex);
        } else {
            u32 *hdr = Msg_OpenContainerAndReadHeader(gOv000TtlTtlPath_3, 0xe);
            void *buf = Archive_LoadFile(
                ARCHIVE_HANDLE(hdr, 3), 0xe);
            *gGameState = *(Ov000GameSave *)buf;
            if (buf != 0) {
                NNSi_FndFreeFromDefaultHeap(buf);
            }
            ZeroHalfThenFree(hdr);
            GameState_SetFlag(0x200b);
        }
    }

    data_ov000_0205ac24->nActiveState = next;
    if (next == 6) {
        return;
    }
    data_ov000_0205ac24->nIdleTicks = 0;
}

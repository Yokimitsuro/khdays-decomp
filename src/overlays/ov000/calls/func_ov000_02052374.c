/* Input handler for the Load screen's slot list: moves the highlight between save
 * slots, dispatches confirm/cancel, and picks the state the scene moves to next.
 *
 * Up/down (held key 0x40/0x80) step nPageIndex and wrap it against
 * bExtraEntryActive + 3, so the extra entry appears only when that flag is set.
 * A (0x1) and X (0x400) confirm: a slot whose nSlotKind is 0 is not selectable and
 * only beeps, kind 2 goes to state 5, anything else to state 3. B (0x2) stamps the
 * tick counter and goes to state 7 (the exit). States 3 and 5 both reset the cursor
 * row, refresh the markers and hide entry 0x10; state 7 re-stamps the tick and defers
 * to nNextState instead of switching immediately.
 *
 * CODEGEN NOTE -- all three dispatches are `switch`, not `if/else if` chains. mwcc
 * hoists a switch's comparisons to the top and places the bodies out of line, which is
 * what the ROM does; an if/else chain interleaves each test with its body and comes out
 * 8 bytes short with every branch target wrong.
 *
 * And the final switch must be WRITTEN with `case 7` first. mwcc emits the comparison
 * chain in case-value order but the bodies in SOURCE order, so the ROM's layout --
 * tests 3, 5, 7 and bodies ordered 7, 3, 5 -- pins the source order even though the
 * behaviour is identical either way. Writing 3, 5, 7 costs one instruction: the last
 * case stops being the fall-through and needs its own branch.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long u64;

typedef struct Ov000SaveSlot {
    u8  pad_00[0x10];
    int nSlotKind;
    int nSlotState;
    u8  pad_18[8];
} Ov000SaveSlot;

typedef struct Ov000MenuContext {
    u8  pad_0000[0x4acc];
    u8  bExtraEntryActive;
    u8  pad_4acd[1];
    u8  bSelectedPage;
    u8  pad_4acf[1];
    int nActiveState;
    u8  pad_4ad4[4];
    int nNextState;
    u8  pad_4adc[0x4ae4 - 0x4adc];
    u64 nTimestamp;
    u8  pad_4aec[0x4af8 - 0x4aec];
    u16 wHeldKeys;
    u8  pad_4afa[0x4b08 - 0x4afa];
    int nPageIndex;
    u8  pad_4b0c[0x4b10 - 0x4b0c];
    Ov000SaveSlot aSlot[3];
    u8  pad_4b70_pre[0];
    int nCursorRow;
    u8  pad_4b74[0x4d94 - 0x4b74];
    int nIdleTicks;
    u8  pad_4d98[0x6a48 - 0x4d98];
    int nBusy;
} Ov000MenuContext;

typedef struct Ov000MenuContextB {
    u8 pad_0000[0x4c];
    u8 aSelectionObject[1];
} Ov000MenuContextB;

extern Ov000MenuContext *data_ov000_0205ac24;
extern u16 data_0204c190;

extern void func_02033b78(int a, int id);
extern void func_ov000_02050514(int a);
extern u64  func_020031d4(void);
extern void func_ov000_020505e4(int mode, int page);
extern void func_ov000_0205042c(int a, int b, int c);
extern int  func_ov000_02055b48(u8 *obj, int id);
extern void func_ov000_02055cb4(u8 *obj, int entry, int visible);

void func_ov000_02052374(void)
{
    Ov000MenuContext *ctx = data_ov000_0205ac24;
    int next = 0;
    int moved = 0;

    if ((short)ctx->nBusy != 0) {
        return;
    }

    switch (ctx->wHeldKeys) {
    case 0x40:
        ctx->nPageIndex--;
        moved = 1;
        func_02033b78(0, 0);
        break;
    case 0x80:
        ctx->nPageIndex++;
        moved = 1;
        func_02033b78(0, 0);
        break;
    default:
        switch (data_0204c190) {
        case 1:
            {
                int pg = ctx->nPageIndex;
                if (pg < 3 && ctx->aSlot[pg].nSlotKind == 0) {
                    func_02033b78(0, 4);
                } else {
                    if (pg < 3 && ctx->aSlot[pg].nSlotKind == 2) {
                        next = 5;
                        func_ov000_02050514(1);
                    } else {
                        next = 3;
                    }
                    data_ov000_0205ac24->bSelectedPage =
                        (u8)data_ov000_0205ac24->nPageIndex;
                    func_02033b78(0, 1);
                }
            }
            break;
        case 2:
            data_ov000_0205ac24->nTimestamp = func_020031d4();
            next = 7;
            func_02033b78(0, 3);
            break;
        case 0x400:
            {
                int pg = ctx->nPageIndex;
                if (pg < 3 && ctx->aSlot[pg].nSlotKind != 0) {
                    ctx->bSelectedPage = (u8)pg;
                    next = 5;
                    func_02033b78(0, 1);
                } else {
                    func_02033b78(0, 4);
                }
            }
            break;
        }
        break;
    }

    if (data_ov000_0205ac24->nPageIndex >= data_ov000_0205ac24->bExtraEntryActive + 3) {
        data_ov000_0205ac24->nPageIndex = 0;
    }
    if (data_ov000_0205ac24->nPageIndex < 0) {
        data_ov000_0205ac24->nPageIndex = data_ov000_0205ac24->bExtraEntryActive + 2;
    }
    if (moved != 0) {
        func_ov000_020505e4(1, data_ov000_0205ac24->nPageIndex);
    }
    if (moved != 0) {
        data_ov000_0205ac24->nIdleTicks = 0;
    }

    if (next == 0) {
        return;
    }
    switch (next) {
    case 7:
        {
            Ov000MenuContext *c = data_ov000_0205ac24;
            c->nTimestamp = func_020031d4();
            c->nNextState = 7;
            next = 0;
        }
        break;
    case 3:
        data_ov000_0205ac24->nCursorRow = 0;
        func_ov000_020505e4(0, data_ov000_0205ac24->nCursorRow);
        func_ov000_0205042c(1, 1, 1);
        if (data_ov000_0205ac24->nPageIndex >= 3) {
            func_ov000_02050514(1);
        }
        {
            int entry = func_ov000_02055b48(
                ((Ov000MenuContextB *)data_ov000_0205ac24)->aSelectionObject, 0x10);
            func_ov000_02055cb4(
                ((Ov000MenuContextB *)data_ov000_0205ac24)->aSelectionObject, entry, 0);
        }
        break;
    case 5:
        data_ov000_0205ac24->nCursorRow = 0;
        func_ov000_020505e4(0, data_ov000_0205ac24->nCursorRow);
        func_ov000_0205042c(1, 1, 1);
        func_ov000_02050514(1);
        {
            int entry = func_ov000_02055b48(
                ((Ov000MenuContextB *)data_ov000_0205ac24)->aSelectionObject, 0x10);
            func_ov000_02055cb4(
                ((Ov000MenuContextB *)data_ov000_0205ac24)->aSelectionObject, entry, 0);
        }
        break;
    }

    data_ov000_0205ac24->nActiveState = next;
    if (next == 0) {
        return;
    }
    data_ov000_0205ac24->nIdleTicks = 0;
}

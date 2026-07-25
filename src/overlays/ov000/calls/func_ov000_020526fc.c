/* Confirm prompt for the Load screen, and the path that actually loads a save.
 *
 * Left/right move a two-item cursor; A on item 0 cancels back to state 2, A on item 1
 * commits (state 6), B cancels. State 6 is where the save is read: for a real slot it
 * calls func_ov000_0204f7ac with the page index, and for the extra entry it opens the
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
 *     src/overlays/ov000/calls/func_ov000_02052374.c.
 *
 *  3. The A-button test is written `if (cursor != 0) { commit } else { cancel }`. The
 *     ROM puts the cancel body out of line, which is what the inverted test gives;
 *     written the natural way round the two blocks swap places.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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
extern u16 data_0204c190;
extern u8  data_ov000_0205ab00[];
extern Ov000GameSave *data_0204be18;

extern void  func_02033b78(int a, int id);
extern void  func_ov000_020505e4(int mode, int row);
extern void  func_ov000_0205042c(int a, int b, int c);
extern void  func_ov000_02050514(int a);
extern void  func_ov000_0204f7ac(int page);
extern u32  *func_02024ee8(u8 *name, int heap);
extern void *func_0201ef9c(u32 handle, int heap);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);
extern void  func_02024fd4(u32 *hdr);
extern void  func_020235a8(int id);

void func_ov000_020526fc(void)
{
    Ov000ConfirmContext *ctx = data_ov000_0205ac24;
    int next = 0;

    switch (ctx->wHeldKeys) {
    case 0x20:
        if (ctx->nCursorRow != 1) {
            ctx->nCursorRow = 1;
            func_ov000_020505e4(0, data_ov000_0205ac24->nCursorRow);
            func_02033b78(0, 0);
        }
        break;
    case 0x10:
        if (ctx->nCursorRow != 0) {
            ctx->nCursorRow = 0;
            func_ov000_020505e4(0, data_ov000_0205ac24->nCursorRow);
            func_02033b78(0, 0);
        }
        break;
    default:
        switch (data_0204c190) {
        case 1:
            if (ctx->nCursorRow != 0) {
                next = 6;
                if (ctx->nExtraEntryPending == 0 && ctx->bExtraEntryActive != 0) {
                    func_02033b78(0, 1);
                }
            } else {
                next = 2;
                func_02033b78(0, 3);
            }
            break;
        case 2:
            next = 2;
            func_02033b78(0, 3);
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
            func_ov000_02050514(0);
            data_ov000_0205ac24->nCursorRow = 0;
            func_ov000_020505e4(0, data_ov000_0205ac24->nCursorRow);
        }
        break;
    case 2:
        func_ov000_0205042c(0, 0, 1);
        data_ov000_0205ac24->nCursorRow = 0;
        func_ov000_020505e4(1, data_ov000_0205ac24->nPageIndex);
        func_ov000_02050514(0);
        data_ov000_0205ac24->nExtraEntryPending = 0;
        break;
    }

    if (next == 6) {
        if (data_ov000_0205ac24->nPageIndex < 3) {
            func_ov000_0204f7ac(data_ov000_0205ac24->nPageIndex);
        } else {
            u32 *hdr = func_02024ee8(data_ov000_0205ab00, 0xe);
            void *buf = func_0201ef9c(
                ((((u32)hdr + 0x8000) & 0xfffffc) << 7) | 0x80000003, 0xe);
            *data_0204be18 = *(Ov000GameSave *)buf;
            if (buf != 0) {
                NNSi_FndFreeFromDefaultHeap(buf);
            }
            func_02024fd4(hdr);
            func_020235a8(0x200b);
        }
    }

    data_ov000_0205ac24->nActiveState = next;
    if (next == 6) {
        return;
    }
    data_ov000_0205ac24->nIdleTicks = 0;
}

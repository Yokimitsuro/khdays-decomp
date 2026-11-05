#pragma opt_dead_assignments off
/* Ov000_LayoutSelectionPages -- Scene 1: lay out the panel-selection page positions.
 * Applies the layout template (language switch: 1 = keep the default charset
 * handle, 2..5 = subfile 3 of the language container, 0 = OS_Terminate), binds
 * the entry table (0x24 entries), sets sub-engine blending (DB_BLDCNT, alpha
 * 8/8), releases entries 0xb/0xd, seeds the page-4 x offsets (-0x100000 ..
 * -0x200000 fixed point), then caches the 4x8 grid entry positions into
 * ctx->pairs[page][item] (y shifted -0x8000 on pages 0..2 when flag +0x4acc is
 * set), hides the decorations (ids 0x14/0x15/0x3c + two tables), refreshes the
 * draw list and nudges entry 0x10 right by +0x8000.
 * MATCH NOTES: the dead stores 'page = 0; entry = 0; item = 0;' under
 * #pragma opt_dead_assignments off emit no code but order the register
 * allocator's colouring (the later the store, the higher the callee-saved
 * register) -- same demotion-ladder crack as Ov000_MatchRecipeAndApply. vec must be
 * declared before pos. */

#include "nitro/types.h"
#include "game/archive.h"

typedef struct Ov000LayoutTemplate {
    u32 handle;
    u32 param1;
    u32 param2;
    u32 param3;
} Ov000LayoutTemplate;

typedef struct Ov000Pair {
    int x;
    int y;
} Ov000Pair;

typedef struct Ov000LoadContext {
    u8 pad_0000[0x4c];
    u8 selectionObject[0x4a80];
    u8 flag_4acc;
    u8 pad_4acd[0x4b74 - 0x4acd];
    Ov000Pair pairs[5][8];
} Ov000LoadContext;

extern const Ov000LayoutTemplate data_ov000_0205a6d0;
extern const char gOv000UiCmCmoPath[];
extern const char gOv000UiCmCmSavePath[];
extern const int data_ov000_0205a7ac[4][8];
extern const int data_ov000_0205a6bc[2];
extern const int data_ov000_0205a6f4[7];
extern Ov000LoadContext *data_ov000_0205ac24;

extern int   GetLanguage(void);
extern void *Msg_OpenContainerAndReadHeader(const void *data, int id);
extern void  OS_Terminate(void);
extern void  Ov000_InitFromDescAndMark(u8 *obj, Ov000LayoutTemplate *tmpl);
extern void  Ov000_LoadBlockProcessAndFree(u8 *obj, const char *data, int count);
extern void  ClampToRange0to16At0x4628(u8 *obj, int v);
extern void  G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern int   Ov000_FindEntryById(u8 *obj, int id);
extern void  Ov000_ReleaseTwoSlots(u8 *obj, int entry);
extern Ov000Pair *Ov000_GetEntryPosition(u8 *obj, int entry);
extern void  Ov000_ReleaseTwoSlotsEx_2(u8 *obj, int entry, int mode);
extern void  Ov000_SetEntrySlotsVisible(u8 *obj, int entry, int visible);
extern void  Ov000_RefreshSelectionGroupDraw(void);
extern Ov000Pair *Ov000_GetEntryBlock2c(u8 *obj, int entry);
extern void  Ov000_SetEntryPosition(u8 *obj, int entry, Ov000Pair *pos);


void Ov000_LayoutSelectionPages(void)
{
    Ov000LayoutTemplate tmpl = data_ov000_0205a6d0;
    Ov000Pair vec;
    Ov000Pair pos;
    void *container;
    Ov000LoadContext *ctx;
    int page;
    u32 item;
    int entry;

    page = 0;
    entry = 0;
    item = 0;
    switch (GetLanguage()) {
    case 1:
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        container = Msg_OpenContainerAndReadHeader(gOv000UiCmCmoPath, 14);
        tmpl.handle = ARCHIVE_HANDLE(container, 3);
        break;
    case 0:
    default:
        OS_Terminate();
        break;
    }

    ctx = data_ov000_0205ac24;
    Ov000_InitFromDescAndMark(ctx->selectionObject, &tmpl);
    Ov000_LoadBlockProcessAndFree(ctx->selectionObject, gOv000UiCmCmSavePath, 0x24);
    ClampToRange0to16At0x4628(ctx->selectionObject, 8);
    G2x_SetBlendAlpha_(0x04001050, 4, 0x10, 8, 8);

    entry = Ov000_FindEntryById(ctx->selectionObject, 0xb);
    Ov000_ReleaseTwoSlots(ctx->selectionObject, entry);
    entry = Ov000_FindEntryById(ctx->selectionObject, 0xd);
    Ov000_ReleaseTwoSlots(ctx->selectionObject, entry);

    data_ov000_0205ac24->pairs[4][0].x = -0x100000;
    data_ov000_0205ac24->pairs[4][1].x = -0x155000;
    data_ov000_0205ac24->pairs[4][2].x = -0x1aa000;
    data_ov000_0205ac24->pairs[4][3].x = -0x200000;

    for (page = 0; page < 4; page++) {
        for (item = 0; item < 8; item++) {
            int id = data_ov000_0205a7ac[page][item];
            if (id != 0) {
                entry = Ov000_FindEntryById(ctx->selectionObject, id);
                vec = *Ov000_GetEntryPosition(ctx->selectionObject, entry);
                if (data_ov000_0205ac24->flag_4acc != 0 && page < 3) {
                    vec.y -= 0x8000;
                }
                data_ov000_0205ac24->pairs[page][item].x = vec.x;
                data_ov000_0205ac24->pairs[page][item].y = vec.y;
                Ov000_ReleaseTwoSlots(ctx->selectionObject, entry);
            }
        }
    }

    entry = Ov000_FindEntryById(ctx->selectionObject, 0x14);
    Ov000_ReleaseTwoSlotsEx_2(ctx->selectionObject, entry, 2);
    entry = Ov000_FindEntryById(ctx->selectionObject, 0x15);
    Ov000_ReleaseTwoSlotsEx_2(ctx->selectionObject, entry, 2);

    for (item = 0; item < 2; item++) {
        entry = Ov000_FindEntryById(ctx->selectionObject, data_ov000_0205a6bc[item]);
        Ov000_SetEntrySlotsVisible(ctx->selectionObject, entry, 0);
    }
    for (item = 0; item < 7; item++) {
        entry = Ov000_FindEntryById(ctx->selectionObject, data_ov000_0205a6f4[item]);
        Ov000_SetEntrySlotsVisible(ctx->selectionObject, entry, 0);
    }

    entry = Ov000_FindEntryById(ctx->selectionObject, 0x3c);
    Ov000_ReleaseTwoSlotsEx_2(ctx->selectionObject, entry, 2);
    Ov000_SetEntrySlotsVisible(ctx->selectionObject, entry, 0);
    Ov000_RefreshSelectionGroupDraw();

    entry = Ov000_FindEntryById(ctx->selectionObject, 0x10);
    pos = *Ov000_GetEntryBlock2c(ctx->selectionObject, entry);
    pos.x += 0x8000;
    Ov000_SetEntryPosition(ctx->selectionObject, entry, &pos);
}

/* Ov000_DrawListScene -- Ov000_DrawListScene (324 B, 10 relocs).
 * Redraws the ov000 list scene: refreshes both render surfaces, draws the 10 visible rows
 * (text + glyph run) onto the row surface, then the header/special text and the selected row
 * onto the primary surface, and commits both. The trailing transferFlags |= 9 is stored twice
 * on purpose -- MWCCARM 3.0/139 emits the duplicate store and it is required for the match. */

#include "nitro/types.h"

typedef struct Ov000RenderSurface { u8 data[0x3c]; } Ov000RenderSurface;
typedef struct Ov000GlyphRun Ov000GlyphRun;
typedef struct Ov000RowRenderEntry {
    int textHandle;
    const Ov000GlyphRun *glyphRun;
    u8 pad_0008[0x10];
} Ov000RowRenderEntry;

typedef struct Ov000ListSceneContext {
    s16 firstRow;
    s16 selectedRow;
    u8 pad_0004[0x90];
    Ov000RenderSurface primarySurface;   /* +0x94 */
    Ov000RenderSurface rowSurface;       /* +0xd0 */
    u8 pad_010c[0x9560];
    u16 transferFlags;                   /* +0x966c */
    u8 pad_966e[2];
    Ov000RowRenderEntry rows[18];        /* +0x9670 */
    u8 pad_9820[0x38f4];
    int specialTextHandle;               /* +0xd114 */
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void Obj_InvokeInnerVtable4(Ov000RenderSurface *surface);
extern void EnqueueObjGfxCommand(Ov000RenderSurface *surface);
/* Defined taking the colour and flags as one by-value struct (DrawTextStyle), which makes it read
 * them back from the stack at each use; declared here as the two words this caller passes, which
 * is how the ROM's calls store them (building the struct here costs a copy the ROM does not
 * make). The two agree word for word on the DS. */
extern void Ov000_DrawTextWithShadow(Ov000RenderSurface *surface, int textHandle, int x, int y, int color, u32 flags);
extern void Ov000_DrawGlyphRunWithShadow(Ov000RenderSurface *surface, const Ov000GlyphRun *run, int x, int y, int depth);

void Ov000_DrawListScene(void) {
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    u16 i;
    int y;
    Ov000RowRenderEntry *entry = &context->rows[context->firstRow];

    Obj_InvokeInnerVtable4(&context->primarySurface);
    Obj_InvokeInnerVtable4(&context->rowSurface);

    for (i = 0; i < 10; i++) {
        y = 0x13 + (i << 4);
        Ov000_DrawTextWithShadow(&context->rowSurface, entry->textHandle, 0x18, y, 2, 0x209);
        Ov000_DrawGlyphRunWithShadow(&context->rowSurface, entry->glyphRun, 0xd0, y, 4);
        entry++;
    }

    Ov000_DrawTextWithShadow(&context->primarySurface, context->specialTextHandle, 0xfa, 2, 2, 0x821);

    entry = &context->rows[context->selectedRow];
    Ov000_DrawTextWithShadow(&context->primarySurface, entry->textHandle, 0x38, 0x3b, 2, 0x209);
    Ov000_DrawGlyphRunWithShadow(&context->primarySurface, entry->glyphRun, 0xd0, 0x90, 4);

    EnqueueObjGfxCommand(&context->primarySurface);
    EnqueueObjGfxCommand(&context->rowSurface);

    /* The repeated store is required for MWCCARM 3.0/139's exact scheduling. */
    {
        u16 transferFlags = context->transferFlags | 9;
        context->transferFlags = transferFlags;
        context->transferFlags = transferFlags;
    }
}

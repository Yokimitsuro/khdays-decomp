/* func_ov000_02059b14 -- Ov000_DrawListScene (324 B, 10 relocs).
 * Redraws the ov000 list scene: refreshes both render surfaces, draws the 10 visible rows
 * (text + glyph run) onto the row surface, then the header/special text and the selected row
 * onto the primary surface, and commits both. The trailing transferFlags |= 9 is stored twice
 * on purpose -- MWCCARM 3.0/139 emits the duplicate store and it is required for the match. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

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
extern void func_02030158(Ov000RenderSurface *surface);
extern void func_020300f8(Ov000RenderSurface *surface);
extern void func_ov000_02059968(Ov000RenderSurface *surface, int textHandle, int x, int y, int color, u32 flags);
extern void func_ov000_020599bc(Ov000RenderSurface *surface, const Ov000GlyphRun *run, int x, int y, int depth);

void func_ov000_02059b14(void) {
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    u16 i;
    int y;
    Ov000RowRenderEntry *entry = &context->rows[context->firstRow];

    func_02030158(&context->primarySurface);
    func_02030158(&context->rowSurface);

    for (i = 0; i < 10; i++) {
        y = 0x13 + (i << 4);
        func_ov000_02059968(&context->rowSurface, entry->textHandle, 0x18, y, 2, 0x209);
        func_ov000_020599bc(&context->rowSurface, entry->glyphRun, 0xd0, y, 4);
        entry++;
    }

    func_ov000_02059968(&context->primarySurface, context->specialTextHandle, 0xfa, 2, 2, 0x821);

    entry = &context->rows[context->selectedRow];
    func_ov000_02059968(&context->primarySurface, entry->textHandle, 0x38, 0x3b, 2, 0x209);
    func_ov000_020599bc(&context->primarySurface, entry->glyphRun, 0xd0, 0x90, 4);

    func_020300f8(&context->primarySurface);
    func_020300f8(&context->rowSurface);

    /* The repeated store is required for MWCCARM 3.0/139's exact scheduling. */
    {
        u16 transferFlags = context->transferFlags | 9;
        context->transferFlags = transferFlags;
        context->transferFlags = transferFlags;
    }
}

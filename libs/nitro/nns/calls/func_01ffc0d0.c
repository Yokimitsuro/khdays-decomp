typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct FrameTable {
    u8 unknown00;
    u8 frameCount01;
    u8 pad02[4];
    u16 entryTableOffset06;
} FrameTable;

typedef struct FrameData {
    u8 pad00[8];
    u32 payloadOffset08;
    u32 payloadSize0c;
} FrameData;

typedef struct RenderCommandState {
    u8 *stream00;
    u8 pad04[4];
    u32 flags08;
    u8 pad0c[0xdc - 0x0c];
    FrameTable *frameTableDc;
} RenderCommandState;

extern void func_01ff9d90(const void *source, u32 size);

static inline s32 *GetFrameEntry(FrameTable *table, u32 frame)
{
    u8 *entries;
    u16 stride;
    s32 *entry;

    if (table != 0 && frame < table->frameCount01) {
        entries = (u8 *)table + table->entryTableOffset06;
        stride = *(u16 *)entries;
        entry = (s32 *)(entries + 4 + stride * frame);
    } else {
        entry = 0;
    }
    return entry;
}

void func_01ffc0d0(RenderCommandState *state)
{
    FrameTable *table;
    FrameData *data;
    s32 *entry;
    u32 frame;

    if ((state->flags08 & 0x303) == 1) {
        frame = state->stream00[1];
        table = state->frameTableDc;
        if (table == 0) {
            goto no_data;
        }
        entry = GetFrameEntry(table, frame);
        if (entry != 0) {
            data = (FrameData *)((u8 *)table + *entry);
            goto have_data;
        }
no_data:
        data = 0;
have_data:
        func_01ff9d90((u8 *)data + data->payloadOffset08, data->payloadSize0c);
    }
    state->stream00 += 2;
}

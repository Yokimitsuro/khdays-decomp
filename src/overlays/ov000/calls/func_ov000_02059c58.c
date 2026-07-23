typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov000TransferSource {
    u8 pad_0000[0xc];
    u16 rowData[10 * 0x14];
} Ov000TransferSource;

typedef struct Ov000TransferCommand {
    u8 pad_0000[0x10];
    u32 size;
    const void *source;
} Ov000TransferCommand;

typedef struct Ov000PaletteCommand {
    u8 pad_0000[0xc];
    const void *source;
} Ov000PaletteCommand;

typedef struct Ov000TransferEntry {
    Ov000TransferSource *rowSource;
    Ov000TransferCommand *command;
    Ov000PaletteCommand *palette;
    u8 pad_000c[0xc];
} Ov000TransferEntry;

typedef struct Ov000RowSlot {
    u8 pad_0000[0xc];
    u8 data[0x28];
    u8 pad_0034[0xc];
} Ov000RowSlot;

typedef struct Ov000SceneContext {
    s16 firstRow;
    s16 selectedRow;
    u8 pad_0004[0x9668];
    u16 transferFlags;
    u8 pad_966e[0xe];
    Ov000TransferEntry transferEntries[18];
    u8 pad_982c[0x8e4];
    Ov000RowSlot rowSlots[19];
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void GFXi_EnqueueCommand(int type, int offset,
                                const void *source, u32 size);
extern void MIi_CpuCopyFast(const void *source, void *destination, u32 size);

void func_ov000_02059c58(void) {
    u8 *rowData;
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000RowSlot *rowSlots =
        (Ov000RowSlot *)((u32)context + 0xa110);
    u16 i;
    Ov000TransferEntry *entry =
        &context->transferEntries[context->selectedRow];

    rowData = (u8 *)rowSlots;
    GFXi_EnqueueCommand(0xf, 0, entry->palette->source, 0x1a0);
    GFXi_EnqueueCommand(6, 0, entry->command->source,
                        entry->command->size);

    for (i = 0; i < 10; i++) {
        MIi_CpuCopyFast(&entry->rowSource->rowData[i * 0x14],
                        rowData + 0xc + (i + 9) * sizeof(*rowSlots),
                        0x28);
    }

    context->transferFlags |= 2;
}

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov009SlotRecord {
    int status;
    u8 pad004[0x18];
} Ov009SlotRecord;

typedef struct Ov009SaveContext {
    int selectedSlot;
    u8 pad004[0x20];
    Ov009SlotRecord slots[10];
    u8 pad13c[0x20];
    u8 varRecords[0x48];
    u8 renderer[0xa0];
    int alternatePrompt;
} Ov009SaveContext;

extern void func_02030158(void *renderer, int mode, int arg2, int arg3);
extern u16 *func_ov009_02052788(void *records, int index);
extern void func_ov009_02053398(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text
);
extern void func_020262a0(u16 *dst, int count, const u16 *format, ...);
extern void func_ov009_02053308(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int shadow
);
extern void func_02030278(
    void *renderer,
    int x,
    int y,
    int style,
    const u16 *text,
    int option
);
extern void func_020300f8(void *renderer);

void func_ov009_020546f8(
    Ov009SaveContext *ctx,
    int mode,
    int arg2,
    int arg3
)
{
    u16 buffer[128];
    const u16 *text;

    func_02030158(ctx->renderer, mode, arg2, arg3);

    switch (mode) {
    case 0:
        text = func_ov009_02052788(ctx->varRecords, 1);
        func_ov009_02053398(ctx->renderer, 0x62, 0, 2, text);
        break;

    case 1:
        text = func_ov009_02052788(
            ctx->varRecords,
            ctx->slots[ctx->selectedSlot].status != 0 ? 2 : 3
        );
        func_020262a0(buffer, 128, text, ctx->selectedSlot + 1);
        func_ov009_02053308(ctx->renderer, 0x10, 0, 2, buffer, 0);
        text = func_ov009_02052788(ctx->varRecords, 5);
        func_ov009_02053308(ctx->renderer, 0x50, 0x12, 2, text, 2);
        text = func_ov009_02052788(ctx->varRecords, 6);
        func_ov009_02053308(ctx->renderer, 0xae, 0x12, 2, text, 2);
        break;

    case 2:
        text = func_ov009_02052788(ctx->varRecords, 11);
        func_02030278(ctx->renderer, 0x10, 0, 2, text, 0);
        break;

    case 3:
        text = func_ov009_02052788(ctx->varRecords, 7);
        func_02030278(ctx->renderer, 0x10, 0, 2, text, 0);
        break;

    case 4:
        text = func_ov009_02052788(
            ctx->varRecords,
            ctx->alternatePrompt != 0 ? 10 : 13
        );
        func_02030278(ctx->renderer, 0x10, 0, 4, text, 0);
        break;

    case 5:
        text = func_ov009_02052788(ctx->varRecords, 14);
        func_02030278(ctx->renderer, 0x10, 0, 2, text, 0);
        text = func_ov009_02052788(ctx->varRecords, 5);
        func_ov009_02053308(ctx->renderer, 0x50, 0x12, 2, text, 2);
        text = func_ov009_02052788(ctx->varRecords, 6);
        func_ov009_02053308(ctx->renderer, 0xae, 0x12, 2, text, 2);
        break;
    }

    func_020300f8(ctx->renderer);
}

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov009SaveChoiceVisual {
    int value;
    u8 pad04[0x04];
} Ov009SaveChoiceVisual;

typedef struct Ov009SaveContext {
    int variant;
    int nextVariant;
    int state;
    u8 pad00c[0x5c];
    int pending;
    u8 pad06c[0xd8];
    Ov009SaveChoiceVisual visuals[3];
    u8 pad15c[0xe4];
    int interactionLock;
} Ov009SaveContext;

extern void func_ov009_0204e440(void);
extern void func_ov009_02054070(int enabled, int mode);
extern void func_ov009_020546f8(Ov009SaveContext *ctx, int mode);
extern void func_ov009_0204e328(int a, int b);
extern void func_02033b78(int bank, int sound);

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

void func_ov009_02053af0(Ov009SaveContext *ctx)
{
    int i;

    func_ov009_0204e440();
    if (ctx->interactionLock != 0) {
        return;
    }

    switch (ctx->state) {
    case 0:
        func_ov009_02054070(0, 1);
        func_ov009_020546f8(ctx, 5);
        ctx->pending = 0;
        ctx->state = 6;
        {
            int previousVariant = ctx->variant;
            u32 displayMode;
            u32 clearedDisplay;

            ctx->variant = -1;
            ctx->nextVariant = previousVariant;
            displayMode = (REG_DISPCNT & 0x1f00) >> 8;
            clearedDisplay = REG_DISPCNT & 0xffffe0ff;
            REG_DISPCNT =
                clearedDisplay | (displayMode & ~4) << 8;
        }
        break;

    case 1:
        goto cleanup;

    case 2:
    case 3:
        break;

    case 4:
        func_ov009_0204e328(-1, -1);
        break;

    case 5:
        break;

    case 6:
        ctx->variant = ctx->nextVariant;
        {
            u32 displayMode = (REG_DISPCNT & 0x1f00) >> 8;
            u32 clearedDisplay = REG_DISPCNT & 0xffffe0ff;

            REG_DISPCNT =
                clearedDisplay | (displayMode | 4) << 8;
        }

cleanup:
        func_ov009_02054070(1, 0);
        func_ov009_020546f8(ctx, 0);
        for (i = 0; i < 3; i++) {
            ctx->visuals[i].value = 0;
        }
        ctx->state = 0;
        break;
    }

    func_02033b78(0, 3);
}

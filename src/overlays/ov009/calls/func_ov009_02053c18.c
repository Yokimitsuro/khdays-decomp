typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
    u8 pad00c[0x1ca0];
} Ov009GameState;

typedef struct Ov009SaveContext {
    int variant;
    int nextVariant;
    int state;
    int currentSlot;
    int phase;
    u8 pad014[0x148];
    u8 resource15c[0xc0];
    u8 tween21c[0x24];
    int interactionLock;
    int field244;
    u8 slotPhase;
    u8 pad249[0x03];
    Ov009GameState snapshot;
    int bestSlot;
    u32 bestPackedValue;
} Ov009SaveContext;

extern Ov009GameState *volatile data_0204be18;
extern const char data_ov009_02056378[];

extern void func_ov009_02052dec(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(int value, void *dst, unsigned int size);
extern void func_ov009_02052750(void *resource, const char *path);
extern int func_ov009_020536b8(Ov009SaveContext *ctx, int slot);
extern int func_020235d0(int field, int kind);
extern void func_ov009_02052f98(void);
extern void func_ov009_020530c4(Ov009SaveContext *ctx);
extern void func_ov009_02053404(Ov009SaveContext *ctx);
extern void func_ov009_02052b58(Ov009SaveContext *ctx, int mode, int variant);
extern void func_ov009_02054558(Ov009SaveContext *ctx);
extern void func_02035f84(void *tween);
extern void func_ov009_02052be0(int value);
extern void func_ov009_020546f8(Ov009SaveContext *ctx, int mode);
extern void func_ov009_02054070(int enabled, int mode);

int func_ov009_02053c18(Ov009SaveContext *ctx)
{
    int done = 0;

    switch (ctx->phase) {
    case 0:
        func_ov009_02052dec();
        MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
        MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
        func_ov009_02052750(ctx->resource15c, data_ov009_02056378);
        ctx->snapshot = *data_0204be18;
        ctx->slotPhase = 0;
        ctx->state = 0;
        ctx->phase++;
        break;

    case 1:
        if (func_ov009_020536b8(ctx, ctx->currentSlot) == 2) {
            u32 high = func_020235d0(0xc77, 0x10);
            u32 low = func_020235d0(0xc87, 0x10);
            u32 packed = low | high << 16;

            if (packed > ctx->bestPackedValue) {
                ctx->bestPackedValue = packed;
                ctx->bestSlot = ctx->currentSlot;
            }
            ctx->currentSlot++;
            ctx->slotPhase = 0;
            if (ctx->currentSlot >= 3) {
                ctx->phase++;
            }
        }
        break;

    case 2:
        *data_0204be18 = ctx->snapshot;
        func_ov009_02052f98();
        func_ov009_020530c4(ctx);
        func_ov009_02053404(ctx);
        ctx->variant = func_020235d0(0xc98, 2);
        func_ov009_02052b58(ctx, 0, ctx->variant);
        func_ov009_02054558(ctx);
        func_02035f84(ctx->tween21c);
        func_ov009_02052be0(data_0204be18->value8);
        ctx->phase++;
        break;

    case 3:
        if (ctx->interactionLock != 0) {
            func_ov009_020546f8(ctx, 4);
            func_ov009_02054070(0, 0);
            ctx->state = 5;
        }
        done = 1;
        break;
    }

    return done;
}

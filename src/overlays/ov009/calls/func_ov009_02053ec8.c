typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

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
    u8 pad014[0x22c];
    int interactionLock;
    int field244;
    u8 slotPhase;
    u8 pad249[0x03];
    Ov009GameState snapshot;
} Ov009SaveContext;

extern Ov009GameState *volatile data_0204be18;

extern void func_ov009_0204e440(void);
extern long long func_020031d4(void);
extern long long func_ov009_02055f48(void);
extern u64 func_02020368(long long value, unsigned int divisor, int unused);
extern void func_ov009_02052cf4(int value);
extern int func_ov009_0205289c(Ov009SaveContext *ctx);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_ov009_02055f34(void);
extern int func_ov009_020536b8(Ov009SaveContext *ctx, int slot);
extern void func_ov009_02054b58(Ov009SaveContext *ctx);
extern void func_ov009_02054558(Ov009SaveContext *ctx);
extern void func_ov009_02054070(int enabled, int mode);
extern void func_ov009_020546f8(Ov009SaveContext *ctx, int mode);
extern void func_02033b78(int bank, int sound);
extern void func_020208f0(void);
extern void func_ov009_0204e3b4(int value);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov009_02054180(Ov009SaveContext *ctx);
extern void func_ov009_020544b4(Ov009SaveContext *ctx);

void func_ov009_02053ec8(Ov009SaveContext *ctx)
{
    func_ov009_0204e440();

    switch (ctx->state) {
    case 0:
        {
            long long elapsed =
                func_020031d4() - func_ov009_02055f48();
            func_ov009_02052cf4(
                (u32)(data_0204be18->value0 +
                      func_02020368(elapsed << 6, 0x1ff6210, 0)));
        }
        break;

    case 1:
        break;

    case 2:
        {
            int result = func_ov009_0205289c(ctx);

            if (result == 0) {
                MI_CpuCopy8(data_0204be18, &ctx->snapshot,
                            sizeof(Ov009GameState));
                ctx->slotPhase = 0;
                ctx->state = 3;
                func_ov009_02055f34();
            } else if (result == 3) {
                ctx->interactionLock = 1;
                ctx->field244 = 1;
            }
        }
        break;

    case 3:
        if (func_ov009_020536b8(ctx, ctx->variant) == 2) {
            MI_CpuCopy8(&ctx->snapshot, data_0204be18,
                        sizeof(Ov009GameState));
            func_ov009_02054b58(ctx);
            func_ov009_02054558(ctx);
            func_ov009_02054070(0, 0);
            func_ov009_020546f8(ctx, 3);
            func_02033b78(0, 0x39);
            ctx->state = 4;
            func_020208f0();
            func_ov009_0204e3b4(1);
        }
        break;

    case 4:
        break;

    case 5:
        func_0201e374(0);
        func_0201e3cc(0);
        break;
    }

    if (ctx->interactionLock != 0) {
        func_ov009_020546f8(ctx, 4);
        func_ov009_02054070(0, 0);
        ctx->state = 5;
        func_ov009_0204e3b4(0);
    }
    func_ov009_02054180(ctx);
    func_ov009_020544b4(ctx);
}

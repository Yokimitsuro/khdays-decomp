typedef unsigned char u8;

typedef struct Ov009TweenFlags {
    unsigned int pad0 : 2;
    unsigned int active : 1;
    unsigned int rest : 29;
} Ov009TweenFlags;

typedef struct Ov009SaveContext {
    u8 pad000[0x21c];
    u8 tween21c[0x18];
    Ov009TweenFlags tweenFlags;
    int tweenDirection;
} Ov009SaveContext;

extern int func_ov009_0204e440(void);
extern void func_02035fb0(
    void *tween,
    int mode,
    int from,
    int to,
    int duration
);
extern void func_02035ffc(void *tween);
extern void func_0203602c(void *tween, int *value);
extern void func_020327e0(int manager, int value);

void func_ov009_02054654(Ov009SaveContext *ctx)
{
    int value = 0;
    int manager = func_ov009_0204e440();

    if (ctx->tweenFlags.active != 0) {
        int direction = ctx->tweenDirection;
        int from;
        int to;

        to = direction != 0 ? 0x2000 : 0x8000;
        from = direction != 0 ? 0x8000 : 0x2000;
        func_02035fb0(ctx->tween21c, 0, from, to, 500);
        func_02035ffc(ctx->tween21c);
        ctx->tweenDirection = ctx->tweenDirection == 0;
    } else {
        func_0203602c(ctx->tween21c, &value);
        func_020327e0(manager, value >> 12);
    }
}

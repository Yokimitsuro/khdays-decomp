/* func_ov025_0209b700 -- Ov008_TickTitleFade (164 B, 5 relocs).
 * Ticks the title-menu "fade" SRT tween (a 0x18-byte object at ctx+0x218). Fetches the active
 * widget once (func_ov025_02084a7c). When bit 2 of ctx->flags230 is set it (re)starts the tween --
 * toggling between 0x2000 and 0x8000 over 500 units depending on ctx->field234 -- steps it, and
 * flips field234. Otherwise it samples the current tween value and applies it (>>12, fixed->int)
 * to the widget via func_020327e0. */
typedef unsigned char  u8;

typedef struct Ov008FadeCtx {
    u8  pad_0000[0x218];
    u8  fade[0x18];            /* 0x218: SRT/tween object */
    unsigned f230_lo   : 2;    /* 0x230 */
    unsigned f230_bit2 : 1;
    unsigned f230_hi   : 29;
    int field234;             /* 0x234: toggle direction */
} Ov008FadeCtx;

typedef struct Obj Obj;

extern Obj *func_ov025_02084a7c(void);
extern void func_02035fb0(void *fade, int mode, int from, int to, int dur);
extern void func_02035ffc(void *fade);
extern void func_0203602c(void *fade, int *out);
extern void func_020327e0(Obj *o, int v);

void func_ov025_0209b700(Ov008FadeCtx *ctx)
{
    int  val = 0;
    Obj *w = func_ov025_02084a7c();

    if (ctx->f230_bit2) {
        func_02035fb0(&ctx->fade, 0,
                      ctx->field234 ? 0x8000 : 0x2000,
                      ctx->field234 ? 0x2000 : 0x8000, 0x1f4);
        func_02035ffc(&ctx->fade);
        ctx->field234 = (ctx->field234 == 0);
    } else {
        func_0203602c(&ctx->fade, &val);
        func_020327e0(w, val >> 12);
    }
}

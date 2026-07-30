/* func_ov008_0206aa6c -- Ov008_CancelMenuSelection (196 B, 10 relocs).
 * Twin of func_ov008_0206a9a8 (Ov008_ConfirmMenuSelection): the un-select action for the
 * highlighted item (ctx->sel). Same gating on data_ov008_0209059d/9e[sel*0x14] and the same held
 * base pointer p = &ctx->sel, but it INCREMENTS the item's count (restoring it) instead of
 * decrementing, and on the unavailable path it refreshes first (func_ov008_0206b1f4) then plays
 * the cue (func_02033b78(0,4)). See the confirm twin for the addressing-form notes. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

extern Ov008SelCtx *func_ov008_02050cd4(void);
extern int  func_ov008_02069bc8(int index);
extern void func_02033b78(int a, int b);
extern int  func_ov008_0206a76c(int a, int b, int c);
extern void func_ov008_0206b1f4(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern u8   data_ov008_0209059d[];
extern u8   data_ov008_0209059e[];

void func_ov008_0206aa6c(void)
{
    Ov008SelCtx *ctx = func_ov008_02050cd4();
    s16 *p = &ctx->sel;
    int r = func_ov008_02069bc8((u16)ctx->sel);
    int idx = ctx->sel * 0x14;

    if (data_ov008_0209059d[idx] != 0) {
        return;
    }
    if (data_ov008_0209059e[idx] == 0) {
        func_ov008_0206b1f4();
        func_02033b78(0, 4);
        return;
    }
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    (p + 1)[p[0]] += 1;
    *(p + p[0] + 1) = func_ov008_0206a76c(*(p + p[0] + 1), 0, r);
    func_02033b78(0, 0);
    func_ov008_0206b1f4();
}

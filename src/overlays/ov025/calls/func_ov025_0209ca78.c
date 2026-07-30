/* func_ov025_0209ca78 -- Ov008_ConfirmMenuSelection (196 B, 10 relocs).
 * Confirms the currently highlighted item (ctx->sel at 0x4c). Resolves the item via
 * func_ov025_0209bfa8(sel) and gates on two stride-0x14 tables indexed by sel: bail silently if
 * data_ov025_020b4f69[sel*0x14] is set (locked); if data_ov025_020b4f6a[sel*0x14] is clear
 * (unavailable) play cue (func_02033b78(0,4)) + refresh and return. Otherwise back up the whole
 * 0x34-byte selection block (0x4c->0x80), decrement the selected item's count and recompute it
 * through func_ov025_0209c83c, then func_02033b78(0,0) + func_ov025_0209d2c4() refresh.
 * NOTE: the counts run right after ctx->sel, and the original holds a single base pointer
 * p = &ctx->sel (r6) for the copy source AND the count accesses -- hence the pointer forms
 * (p+1)[p[0]] and *(p+p[0]+1) rather than ctx->counts[ctx->sel] (which would re-base on ctx). */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

extern Ov008SelCtx *func_ov025_02084afc(void);
extern int  func_ov025_0209bfa8(int index);
extern void func_02033b78(int a, int b);
extern int  func_ov025_0209c83c(int a, int b, int c);
extern void func_ov025_0209d2c4(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern u8   data_ov025_020b4f69[];
extern u8   data_ov025_020b4f6a[];

void func_ov025_0209ca78(void)
{
    Ov008SelCtx *ctx = func_ov025_02084afc();
    s16 *p = &ctx->sel;
    int r = func_ov025_0209bfa8((u16)ctx->sel);
    int idx = ctx->sel * 0x14;

    if (data_ov025_020b4f69[idx] != 0) {
        return;
    }
    if (data_ov025_020b4f6a[idx] == 0) {
        func_02033b78(0, 4);
        func_ov025_0209d2c4();
        return;
    }
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    (p + 1)[p[0]] -= 1;
    *(p + p[0] + 1) = func_ov025_0209c83c(*(p + p[0] + 1), 0, r);
    func_02033b78(0, 0);
    func_ov025_0209d2c4();
}

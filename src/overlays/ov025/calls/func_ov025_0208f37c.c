/* Ov025_DrawSavePage -- draw the selected save/equipment page (ov025 build of Ov008_DrawSavePage).
 * Builds the page view from the preset item grid, blits the panel, draws the
 * page labels and counters, then draws the selected title and optional warning.
 * `count` is reused for the alternate font handle after the count text is drawn;
 * this preserves the original MWCC register assignment in the portrait block.
 */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Tmpl3 { unsigned a, b, c; } Tmpl3;

typedef struct NNSFndList {
    u16   numObjects;
    u16   offset;
    void *head;
    void *tail;
} NNSFndList;

typedef struct IterSelf {
    unsigned f00;              /* 0x00 */
    unsigned f04;              /* 0x04 */
    u8  pad_0008[0x2c - 0x08];
    int f2c;                   /* 0x2c */
    u8  pad_0030[0x74 - 0x30];
    int f74;                   /* 0x74 */
    u8  pad_0078[0x100 - 0x78];
} IterSelf;                    /* 0x100 */

extern char     *data_0204be18;
extern unsigned  data_ov025_020b3c78[3];
extern char      data_ov025_020b4d90[];
extern char      data_ov025_020b4d9c[];
extern char      data_ov025_020b4da8[];
extern char      data_ov025_020b4dac[];
extern char      data_ov025_020b4db4[];

extern int   func_020303b4(int a);
extern void  NNS_FndInitList(NNSFndList *list, int off);
extern void  func_ov025_020871d4(IterSelf *self, int a);
extern void  func_ov025_020874dc(IterSelf *self, void *entries, NNSFndList *list, void *ids);
extern void  func_ov025_02087260(IterSelf *self, void *entries, NNSFndList *list);
extern int   func_ov025_020877e0(IterSelf *self);
extern void  func_ov025_0208772c(IterSelf *self, void *entries, NNSFndList *list);
extern void  MIi_CpuCopyFast(void *dst, void *src, unsigned n);
extern int  *func_ov025_02089894(int base, int idx);
extern void  func_02030278(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  func_020301c8(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  func_020262a0(void *buf, int cap, const char *fmt, ...);
extern int   func_02023588(int flagId);
extern int   func_02013814(int a, int b, int c);
extern int   func_ov025_02084c84(void);
extern int   func_ov025_02084cb4(void);
extern int   func_ov025_0208f198(int ctx, int page);
extern void  WM_EndKeySharing_0x02087254(IterSelf *self);
extern void  func_020300f8(int dctx);

void func_ov025_0208f37c(int ctx, int page)
{
    struct { unsigned tag[3]; NNSFndList list; } hdr;
    unsigned collect[120];
    IterSelf self;
    u16      text[128];
    void    *saved;
    int      f04, count, f00, flag;
    int     *rec;

    saved = *(void **)(func_020303b4(ctx + 0xe8) + 0x20);
    *(Tmpl3 *)hdr.tag = *(Tmpl3 *)data_ov025_020b3c78;
    NNS_FndInitList(&hdr.list, 0x28);
    func_ov025_020871d4(&self, ctx + 0x2090);
    func_ov025_020874dc(&self, collect, &hdr.list, data_0204be18 + 0xc10 + page * 0xf0);
    func_ov025_02087260(&self, collect, &hdr.list);
    f04 = self.f04;
    count = func_ov025_020877e0(&self);
    f00 = self.f00;
    func_ov025_0208772c(&self, collect, &hdr.list);
    MIi_CpuCopyFast(*(void **)(ctx + 0x2f4), saved, *(unsigned *)(ctx + 0x2ec));

    rec = func_ov025_02089894(ctx + 0x28c, hdr.tag[page]);
    func_02030278(ctx + 0xe8, 8, 4, 0xf3, (int)rec, 0);
    rec = func_ov025_02089894(ctx + 0x28c, 0x17);
    func_020301c8(ctx + 0xe8, 0xca, 4, 0xf3, 0x821, rec);
    rec = func_ov025_02089894(ctx + 0x28c, 0x18);
    func_020301c8(ctx + 0xe8, 0x9a, 0x12, 0xf3, 0x821, rec);
    rec = func_ov025_02089894(ctx + 0x28c, 0x19);
    func_020301c8(ctx + 0xe8, 0xde, 0x12, 0xf3, 0x821, rec);

    flag = func_02023588(page + 0x3c67);
    if (flag != 0) {
        int clamp = *(int *)(ctx + 0x1e74);
        if (clamp > 0x78) {
            func_020262a0(text, 0x80, data_ov025_020b4d90, f04, 0x78);
        } else {
            func_020262a0(text, 0x80, data_ov025_020b4d90, f04, clamp);
        }
    } else {
        func_020262a0(text, 0x80, data_ov025_020b4d9c, data_ov025_020b4da8, data_ov025_020b4da8);
    }
    func_020301c8(ctx + 0xe8, 0xf8, 4, 0xf1, 0x821, text);

    if (flag != 0) {
        func_020262a0(text, 0x80, data_ov025_020b4dac, count);
    } else {
        func_020262a0(text, 0x80, data_ov025_020b4db4, data_ov025_020b4da8);
    }
    func_020301c8(ctx + 0xe8, 0xb4, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        func_020262a0(text, 0x80, data_ov025_020b4dac, f00);
    } else {
        func_020262a0(text, 0x80, data_ov025_020b4db4, data_ov025_020b4da8);
    }
    func_020301c8(ctx + 0xe8, 0xf8, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        int a = func_ov025_02084c84();
        count = func_ov025_02084cb4();
        int hi;
        rec = *(int **)(self.f74 * 0x3e0 + *(int *)(ctx + 0x208c) + 0xc);
        hi = func_02013814(*(int *)(ctx + 0x108), *(int *)(ctx + 0x10c), rec) >= 0x56;
        if (hi) *(int *)(ctx + 0x108) = count;
        func_02030278(ctx + 0xe8, 8, 0x12, 0xf3, (int)rec, 0);
        if (hi) *(int *)(ctx + 0x108) = a;
    }

    if (func_ov025_0208f198(ctx, page) != 0) {
        rec = func_ov025_02089894(ctx + 0x28c, 0x1a);
        func_02030278(ctx + 0xe8, 0x2c, 4, 0xf1, (int)rec, 0);
    }
    WM_EndKeySharing_0x02087254(&self);
    func_020300f8(ctx + 0xe8);
}

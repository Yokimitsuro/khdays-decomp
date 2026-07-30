/* func_ov008_0205cde8 -- Ov008_DrawSavePage (936 B, 44 relocs).
 * Renders one save/equip page. Fetches the draw context (func_020303b4) and snapshots a blit
 * source; copies a 3-word tag template out of data_ov008_0208f118; then runs the Ov008IterFrame
 * list walker over the u16 cell grid at *data_0204be18 + 0xc10 + page*0xf0 (the same grid as
 * func_ov008_0205cc04) to build the view, capturing the walker's field 4 (before the count) and
 * field 0 (after). It blits the panel, draws the page label + three fixed captions, then formats
 * three text fields with the variadic sprintf func_020262a0 (branching on a game-state flag from
 * func_02023588) and draws each. When the flag is set it runs the character-portrait cursor logic
 * (temporarily swapping ctx[0x108] around a draw when func_02013814/Cursor_MaxOverRun returns
 * >= 0x56). Finally it asks func_ov008_0205cc04 whether the page is over capacity and, if so, draws
 * the warning caption, then finalizes the walker and enqueues the gfx command.
 *
 * The draw helpers take their buffer/record argument as a pointer (a6 is void *, not an int): that
 * makes mwcc re-materialize the frame-relative text address fresh before each draw instead of
 * caching it in a callee-saved register -- the (int)-cast form is 8 bytes short. */
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
extern unsigned  data_ov008_0208f118[3];
extern char      data_ov008_020903c4[];
extern char      data_ov008_020903d0[];
extern char      data_ov008_020903dc[];
extern char      data_ov008_020903e0[];
extern char      data_ov008_020903e8[];

extern int   func_020303b4(int a);
extern void  NNS_FndInitList(NNSFndList *list, int off);
extern void  func_ov008_020533e4(IterSelf *self, int a);
extern void  func_ov008_020536ec(IterSelf *self, void *entries, NNSFndList *list, void *ids);
extern void  func_ov008_02053470(IterSelf *self, void *entries, NNSFndList *list);
extern int   func_ov008_020539f0(IterSelf *self);
extern void  func_ov008_0205393c(IterSelf *self, void *entries, NNSFndList *list);
extern void  MIi_CpuCopyFast(void *dst, void *src, unsigned n);
extern int  *func_ov008_02055c84(int base, int idx);
extern void  func_02030278(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  func_020301c8(int dctx, int x, int y, int mode, int a5, void *a6);
extern void  func_020262a0(void *buf, int cap, const char *fmt, ...);
extern int   func_02023588(int flagId);
extern int   func_02013814(int a, int b, int c);
extern int   func_ov008_02050e74(void);
extern int   func_ov008_02050ea4(void);
extern int   func_ov008_0205cc04(int ctx, int page);
extern void  WM_EndKeySharing_0x02053464(IterSelf *self);
extern void  func_020300f8(int dctx);

void func_ov008_0205cde8(int ctx, int page)
{
    struct { unsigned tag[3]; NNSFndList list; } hdr;
    unsigned collect[120];
    IterSelf self;
    u16      text[128];
    void    *saved;
    int      f04, count, f00, flag;
    int     *rec;

    saved = *(void **)(func_020303b4(ctx + 0xe8) + 0x20);
    *(Tmpl3 *)hdr.tag = *(Tmpl3 *)data_ov008_0208f118;
    NNS_FndInitList(&hdr.list, 0x28);
    func_ov008_020533e4(&self, ctx + 0x2090);
    func_ov008_020536ec(&self, collect, &hdr.list, data_0204be18 + 0xc10 + page * 0xf0);
    func_ov008_02053470(&self, collect, &hdr.list);
    f04 = self.f04;
    count = func_ov008_020539f0(&self);
    f00 = self.f00;
    func_ov008_0205393c(&self, collect, &hdr.list);
    MIi_CpuCopyFast(*(void **)(ctx + 0x2f4), saved, *(unsigned *)(ctx + 0x2ec));

    rec = func_ov008_02055c84(ctx + 0x28c, hdr.tag[page]);
    func_02030278(ctx + 0xe8, 8, 4, 0xf3, (int)rec, 0);
    rec = func_ov008_02055c84(ctx + 0x28c, 0x17);
    func_020301c8(ctx + 0xe8, 0xca, 4, 0xf3, 0x821, rec);
    rec = func_ov008_02055c84(ctx + 0x28c, 0x18);
    func_020301c8(ctx + 0xe8, 0x9a, 0x12, 0xf3, 0x821, rec);
    rec = func_ov008_02055c84(ctx + 0x28c, 0x19);
    func_020301c8(ctx + 0xe8, 0xde, 0x12, 0xf3, 0x821, rec);

    flag = func_02023588(page + 0x3c67);
    if (flag != 0) {
        int clamp = *(int *)(ctx + 0x1e74);
        if (clamp > 0x78) {
            func_020262a0(text, 0x80, data_ov008_020903c4, f04, 0x78);
        } else {
            func_020262a0(text, 0x80, data_ov008_020903c4, f04, clamp);
        }
    } else {
        func_020262a0(text, 0x80, data_ov008_020903d0, data_ov008_020903dc, data_ov008_020903dc);
    }
    func_020301c8(ctx + 0xe8, 0xf8, 4, 0xf1, 0x821, text);

    if (flag != 0) {
        func_020262a0(text, 0x80, data_ov008_020903e0, count);
    } else {
        func_020262a0(text, 0x80, data_ov008_020903e8, data_ov008_020903dc);
    }
    func_020301c8(ctx + 0xe8, 0xb4, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        func_020262a0(text, 0x80, data_ov008_020903e0, f00);
    } else {
        func_020262a0(text, 0x80, data_ov008_020903e8, data_ov008_020903dc);
    }
    func_020301c8(ctx + 0xe8, 0xf8, 0x12, 0xf1, 0x821, text);

    if (flag != 0) {
        int a = func_ov008_02050e74();
        int b = func_ov008_02050ea4();
        int hi;
        if (self.f2c != 0) {
            rec = func_ov008_02055c84(ctx + 0x28c, 0x23);
        } else {
            rec = *(int **)(self.f74 * 0x3e0 + *(int *)(ctx + 0x208c) + 0xc);
        }
        hi = func_02013814(*(int *)(ctx + 0x108), *(int *)(ctx + 0x10c), rec) >= 0x56;
        if (hi) *(int *)(ctx + 0x108) = b;
        func_02030278(ctx + 0xe8, 8, 0x12, 0xf3, (int)rec, 0);
        if (hi) *(int *)(ctx + 0x108) = a;
    }

    if (func_ov008_0205cc04(ctx, page) != 0) {
        rec = func_ov008_02055c84(ctx + 0x28c, 0x1a);
        func_02030278(ctx + 0xe8, 0x2c, 4, 0xf1, (int)rec, 0);
    }
    WM_EndKeySharing_0x02053464(&self);
    func_020300f8(ctx + 0xe8);
}

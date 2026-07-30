/* func_ov026_0208a774 -- Ov008_RefreshPanelDisplay (212 B, 16 relocs).
 * Rebuilds the visible menu panel from the shared panel context (*data_ov026_02091368).
 * Brackets the work with func_ov026_02085070 / func_ov026_0208529c. When the enable word at
 * ctx+0xc5f8 is set, it re-applies the highlighted widget (id 0xa in the widget group at
 * ctx+0x2ab0) to the current value from func_ov105_020bd7c4 (masked to u16). It then appends a
 * fresh cell (func_ov026_02083530 tag 0x3e8 -> func_ov026_020835c4) to the list at ctx+0x5c,
 * closes the four render surfaces (ctx+0xc19c/0xc1d8/0xc214/0xc160), clears the scroll on the two
 * widget groups (ctx+0x7530 and ctx+0x2ab0), and tears down the two sub-panels (ctx+0x5c, ctx+0x10). */
typedef unsigned char u8;
typedef unsigned short u16;

extern char *data_ov026_02091368;
extern void  func_ov026_02085070(void);
extern void *func_ov026_0208427c(void *ctx, int id);
extern void  func_ov026_02084488(void *ctx, void *widget, int value);
extern int   func_ov105_020bd7c4(void);
extern int   func_ov026_02083530(void *list, int tag);
extern void  func_ov026_020835c4(void *list, int cell);
extern void  func_020300f8(void *surface);
extern void  func_ov026_02083ee4(void *arg0, int arg1);
extern void  func_ov026_0208320c(void *arg);
extern void  func_ov026_0208529c(void);

void func_ov026_0208a774(void)
{
    char *ctx = data_ov026_02091368;

    func_ov026_02085070();
    if (*(int *)(ctx + 0xc5f8) != 0) {
        void *widget = func_ov026_0208427c(ctx + 0x2ab0, 0xa);
        func_ov026_02084488(ctx + 0x2ab0, widget, (u16)func_ov105_020bd7c4());
    }
    func_ov026_020835c4(ctx + 0x5c, func_ov026_02083530(ctx + 0x5c, 0x3e8));
    func_020300f8(ctx + 0xc19c);
    func_020300f8(ctx + 0xc1d8);
    func_020300f8(ctx + 0xc214);
    func_020300f8(ctx + 0xc160);
    func_ov026_02083ee4(ctx + 0x7530, 0);
    func_ov026_02083ee4(ctx + 0x2ab0, 0);
    func_ov026_0208320c(ctx + 0x5c);
    func_ov026_0208320c(ctx + 0x10);
    func_ov026_0208529c();
}

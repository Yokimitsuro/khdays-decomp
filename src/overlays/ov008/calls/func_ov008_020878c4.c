/* func_ov008_020878c4 -- Ov008_RefreshPanelDisplay (212 B, 16 relocs).
 * Rebuilds the visible menu panel from the shared panel context (*data_ov008_02090fac).
 * Brackets the work with func_ov008_020821c0 / func_ov008_020823ec. When the enable word at
 * ctx+0xc5f8 is set, it re-applies the highlighted widget (id 0xa in the widget group at
 * ctx+0x2ab0) to the current value from func_ov105_020bd7c4 (masked to u16). It then appends a
 * fresh cell (func_ov008_02055808 tag 0x3e8 -> func_ov008_0205589c) to the list at ctx+0x5c,
 * closes the four render surfaces (ctx+0xc19c/0xc1d8/0xc214/0xc160), clears the scroll on the two
 * widget groups (ctx+0x7530 and ctx+0x2ab0), and tears down the two sub-panels (ctx+0x5c, ctx+0x10). */
typedef unsigned char u8;
typedef unsigned short u16;

extern char *data_ov008_02090fac;
extern void  func_ov008_020821c0(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054c80(void *ctx, void *widget, int value);
extern int   func_ov105_020bd7c4(void);
extern int   func_ov008_02055808(void *list, int tag);
extern void  func_ov008_0205589c(void *list, int cell);
extern void  func_020300f8(void *surface);
extern void  func_ov008_02054390(void *arg0, int arg1);
extern void  func_ov008_020554e4(void *arg);
extern void  func_ov008_020823ec(void);

void func_ov008_020878c4(void)
{
    char *ctx = data_ov008_02090fac;

    func_ov008_020821c0();
    if (*(int *)(ctx + 0xc5f8) != 0) {
        void *widget = func_ov008_02054788(ctx + 0x2ab0, 0xa);
        func_ov008_02054c80(ctx + 0x2ab0, widget, (u16)func_ov105_020bd7c4());
    }
    func_ov008_0205589c(ctx + 0x5c, func_ov008_02055808(ctx + 0x5c, 0x3e8));
    func_020300f8(ctx + 0xc19c);
    func_020300f8(ctx + 0xc1d8);
    func_020300f8(ctx + 0xc214);
    func_020300f8(ctx + 0xc160);
    func_ov008_02054390(ctx + 0x7530, 0);
    func_ov008_02054390(ctx + 0x2ab0, 0);
    func_ov008_020554e4(ctx + 0x5c);
    func_ov008_020554e4(ctx + 0x10);
    func_ov008_020823ec();
}

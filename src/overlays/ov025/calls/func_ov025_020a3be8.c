/* func_ov025_020a3be8 -- Ov008_TickMenuScrollInput (460 B, 26 relocs).
 * Menu list scroll/selection tick. When the input-latch bit 0x400 of data_0204c18c is set it reads
 * the pad (func_ov025_02084f58): the up bit (0x40) scrolls to entry list[sel-1], the down bit
 * (0x80) to list[sel+1], each via func_ov025_020a1fa0, playing a click when the scroll actually
 * moved and clearing the ctx+0x10 pending flag. When the latch is clear it settles the selection:
 * commits the pending change (func_ov025_020a13d8, direction from ctx+0x44) with a confirm sound,
 * hides the up/down arrows (0x29/0x51), swaps entry 5 in, re-runs the layer object, shows entry
 * 0x80 (and the optional ctx+0x54 entry), and clears the busy flag ctx+8. */
typedef unsigned short u16;

extern u16  data_0204c18c;

extern int  func_ov025_02084f58(void);
extern int  func_ov025_020a1fa0(int ctx, int bound, int b, int c);
extern void func_02033b78(int a, int b);
extern void func_ov025_0208488c(int a);
extern int  func_ov025_02084a8c(void);
extern void func_ov025_020a13d8(int ctx, int newSel, int param3);
extern int  func_ov025_0208843c(int root, int id);
extern void func_ov025_0208884c(int root, int entry, int vis);
extern void func_ov025_02088928(int root, int entry, int n);
extern void func_02030158(int surface);
extern void func_020300f8(int dctx);

void func_ov025_020a3be8(int param_1)
{
    int block, entry;

    if ((data_0204c18c & 0x400) != 0) {
        if (*(int *)(param_1 + 0x44) == 1)
            return;
        if (func_ov025_02084f58() & 0x40) {
            if (func_ov025_020a1fa0(param_1, *(int *)(param_1 + 0x50) - 1, 1, 0) != 0)
                func_02033b78(0, 0);
            *(int *)(param_1 + 0x10) = 0;
            return;
        }
        if (func_ov025_02084f58() & 0x80) {
            if (func_ov025_020a1fa0(param_1, *(int *)(param_1 + 0x50) + 1, 1, 0) != 0)
                func_02033b78(0, 0);
            *(int *)(param_1 + 0x10) = 0;
        }
        return;
    }

    func_ov025_0208488c(1);
    block = func_ov025_02084a8c();
    if (*(int *)(param_1 + 0x10) != 0) {
        if (*(int *)(param_1 + 0x44) == 1) {
            func_ov025_020a13d8(param_1, 0, 100);
            func_02033b78(0, 2);
        } else {
            func_ov025_020a13d8(param_1, 1, 100);
            func_02033b78(0, 2);
        }
    }
    entry = func_ov025_0208843c(block, 0x29);
    func_ov025_0208884c(block, entry, 0);
    entry = func_ov025_0208843c(block, 0x51);
    func_ov025_0208884c(block, entry, 0);
    entry = func_ov025_0208843c(block, 5);
    func_ov025_02088928(block, entry, 0);
    entry = func_ov025_0208843c(block, 5);
    func_ov025_0208884c(block, entry, 1);
    func_02030158(param_1 + 0x64);
    func_020300f8(param_1 + 0x64);
    entry = func_ov025_0208843c(block, 0x80);
    func_ov025_0208884c(block, entry, 1);
    if (*(int *)(param_1 + 0x54) != 0)
        func_ov025_0208884c(block, *(int *)(param_1 + 0x54), 1);
    *(int *)(param_1 + 8) = 0;
}

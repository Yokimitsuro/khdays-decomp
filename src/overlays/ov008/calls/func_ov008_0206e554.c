/* func_ov008_0206e554 -- Ov008_TickMenuScrollInput (460 B, 26 relocs).
 * Menu list scroll/selection tick. When the input-latch bit 0x400 of data_0204c18c is set it reads
 * the pad (func_ov008_02051148): the up bit (0x40) scrolls to entry list[sel-1], the down bit
 * (0x80) to list[sel+1], each via func_ov008_0206c90c, playing a click when the scroll actually
 * moved and clearing the ctx+0x10 pending flag. When the latch is clear it settles the selection:
 * commits the pending change (func_ov008_0206bca0, direction from ctx+0x44) with a confirm sound,
 * hides the up/down arrows (0x29/0x51), swaps entry 5 in, re-runs the layer object, shows entry
 * 0x80 (and the optional ctx+0x54 entry), and clears the busy flag ctx+8. */
typedef unsigned short u16;

extern u16  data_0204c18c;

extern int  func_ov008_02051148(void);
extern int  func_ov008_0206c90c(int ctx, int bound, int b, int c);
extern void func_02033b78(int a, int b);
extern void func_ov008_02050a64(int a);
extern int  func_ov008_02050c64(void);
extern void func_ov008_0206bca0(int ctx, int newSel, int param3);
extern int  func_ov008_02054788(int root, int id);
extern void func_ov008_02054ba4(int root, int entry, int vis);
extern void func_ov008_02054c80(int root, int entry, int n);
extern void func_02030158(int surface);
extern void func_020300f8(int dctx);

void func_ov008_0206e554(int param_1)
{
    int block, entry;

    if ((data_0204c18c & 0x400) != 0) {
        if (*(int *)(param_1 + 0x44) == 1)
            return;
        if (func_ov008_02051148() & 0x40) {
            if (func_ov008_0206c90c(param_1, *(int *)(param_1 + 0x50) - 1, 1, 0) != 0)
                func_02033b78(0, 0);
            *(int *)(param_1 + 0x10) = 0;
            return;
        }
        if (func_ov008_02051148() & 0x80) {
            if (func_ov008_0206c90c(param_1, *(int *)(param_1 + 0x50) + 1, 1, 0) != 0)
                func_02033b78(0, 0);
            *(int *)(param_1 + 0x10) = 0;
        }
        return;
    }

    func_ov008_02050a64(1);
    block = func_ov008_02050c64();
    if (*(int *)(param_1 + 0x10) != 0) {
        if (*(int *)(param_1 + 0x44) == 1) {
            func_ov008_0206bca0(param_1, 0, 100);
            func_02033b78(0, 2);
        } else {
            func_ov008_0206bca0(param_1, 1, 100);
            func_02033b78(0, 2);
        }
    }
    entry = func_ov008_02054788(block, 0x29);
    func_ov008_02054ba4(block, entry, 0);
    entry = func_ov008_02054788(block, 0x51);
    func_ov008_02054ba4(block, entry, 0);
    entry = func_ov008_02054788(block, 5);
    func_ov008_02054c80(block, entry, 0);
    entry = func_ov008_02054788(block, 5);
    func_ov008_02054ba4(block, entry, 1);
    func_02030158(param_1 + 0x64);
    func_020300f8(param_1 + 0x64);
    entry = func_ov008_02054788(block, 0x80);
    func_ov008_02054ba4(block, entry, 1);
    if (*(int *)(param_1 + 0x54) != 0)
        func_ov008_02054ba4(block, *(int *)(param_1 + 0x54), 1);
    *(int *)(param_1 + 8) = 0;
}

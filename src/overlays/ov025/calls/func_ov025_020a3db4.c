/*
 * Ov008_Menu_SetupStateEntry - configure the menu's toolbar/OAM entries on
 * entering a menu state.
 *
 * Fetches the menu context block (func_ov025_02084a64) and queries a small
 * status record via func_ov025_02089834; if its gate halfword is non-zero the
 * state is not ready and it bails. Otherwise it applies control value 1, then
 * on the OAM cell table (func_ov025_02084a8c) it hides entries 0x29 and 0x51,
 * fires the object's inner vtable slot 4 and enqueues its gfx command
 * (both on ctx+0x64), shows entry 0x80 and the optional slot at ctx+0x54,
 * releases and re-shows entry 5, and records the new state at ctx+0x14.
 *
 * NB: func_02030158/func_020300f8 are invoked with only r0 set (ctx+0x64);
 * Ghidra's extraout_r1/param_4 args at that call are decompiler artifacts.
 */

extern int func_ov025_02084a64(void);
extern void func_ov025_02089834(int block, void *out);
extern void func_ov025_0208488c(int value);
extern int func_ov025_02084a8c(void);
extern int func_ov025_0208843c(int table, int id);
extern void func_ov025_0208884c(int table, int entry, int visible);
extern void func_02030158(int obj);
extern void func_020300f8(int obj);
extern void func_ov025_02088928(int table, int entry, int a);

void func_ov025_020a3db4(int param_1, int param_2, int param_3, int param_4)
{
    int blk, tbl, entry;
    unsigned short st[3];

    blk = func_ov025_02084a64();
    func_ov025_02089834(blk, st);
    if (st[2] != 0) return;
    func_ov025_0208488c(1);
    tbl = func_ov025_02084a8c();
    entry = func_ov025_0208843c(tbl, 0x29);
    func_ov025_0208884c(tbl, entry, 0);
    entry = func_ov025_0208843c(tbl, 0x51);
    func_ov025_0208884c(tbl, entry, 0);
    func_02030158(param_1 + 0x64);
    func_020300f8(param_1 + 0x64);
    entry = func_ov025_0208843c(tbl, 0x80);
    func_ov025_0208884c(tbl, entry, 1);
    if (*(int *)(param_1 + 0x54) != 0) {
        func_ov025_0208884c(tbl, *(int *)(param_1 + 0x54), 1);
    }
    entry = func_ov025_0208843c(tbl, 5);
    func_ov025_02088928(tbl, entry, 0);
    entry = func_ov025_0208843c(tbl, 5);
    func_ov025_0208884c(tbl, entry, 1);
    *(int *)(param_1 + 0x14) = 0;
}

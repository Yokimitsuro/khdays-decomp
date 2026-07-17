/* NONMATCHING: semantics correct; ties on CSE of the global base &data_02090f04 -- the ROM
 * rematerialises it from the literal pool in each store branch (3 callee-saved regs), mwcc
 * caches it in r4 (4 callee-saved), yielding 144B vs 152B. CSE-recompute tie class. */
/* func_ov008_02050970 -- set the ov008 menu's active/target slot and start the cursor move.
 * Records the target slot at screen-ctx +0x95c4. If no slot was active yet (cur == -1) it just
 * snaps (func_ov008_0204ee28(1)) and flags dirty (+0x95f8). Otherwise it animates: mode 4, a
 * cursor tween (func_ov008_0204eff0(-0x10, dur), dur defaulting to 100 when negative) and
 * func_ov008_0204f1ac(0); if the target differs from the current slot it flags dirty. */
extern int  OS_IsThreadAvailable_0x02051aa0(void);
extern void func_ov008_0204ee28(int a);
extern void func_ov008_0204eff0(int a, unsigned int dur);
extern void func_ov008_0204f1ac(int a);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

void func_ov008_02050970(int param_1, unsigned int param_2) {
    int cur = OS_IsThreadAvailable_0x02051aa0();
    *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95c4) = param_1;
    if (cur == -1) {
        func_ov008_0204ee28(1);
        *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95f8) = 1;
        return;
    }
    if ((int)param_2 < 0) {
        param_2 = 100;
    }
    func_ov008_0204ee28(4);
    func_ov008_0204eff0(-0x10, param_2);
    func_ov008_0204f1ac(0);
    if (cur == param_1) {
        return;
    }
    *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95f8) = 1;
}

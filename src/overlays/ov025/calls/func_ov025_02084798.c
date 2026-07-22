/* Set the menu's target slot and start the cursor move. Records the target at +0x95c4 of the
 * shared screen context. With no slot active yet (cur == -1) it just snaps and flags dirty;
 * otherwise it animates -- mode 4, a cursor tween over `dur` frames (defaulting to 100 when
 * negative) -- and flags dirty only if the target is not where the cursor already is.
 *
 * Parked as a CSE tie: the original reloads the context pointer from the literal pool in each
 * store branch while mwcc cached it in a callee-saved register, eight bytes short. The fix is
 * the spelling of the global read. `*(int *)((int)data + 4)` is one expression that mwcc is
 * free to reuse; `data[1]` is an array subscript and comes out as a fresh pool load every time,
 * which is what the original has. Same lever as func_ov008_0204ffe4. */
extern int  OS_IsThreadAvailable_0x02085850(void);
extern void func_ov025_02082c50(int mode);
extern void func_ov025_02082e18(int from, unsigned int dur);
extern void func_ov025_02082fd4(int a);
extern int  data_ov025_020b5744[];   /* [1] -> shared screen context */

void func_ov025_02084798(int slot, unsigned int dur) {
    int cur = OS_IsThreadAvailable_0x02085850();
    *(int *)((char *)data_ov025_020b5744[1] + 0x95c4) = slot;
    if (cur == -1) {
        func_ov025_02082c50(1);
        *(int *)((char *)data_ov025_020b5744[1] + 0x95f8) = 1;
        return;
    }
    if ((int)dur < 0) {
        dur = 100;
    }
    func_ov025_02082c50(4);
    func_ov025_02082e18(-0x10, dur);
    func_ov025_02082fd4(0);
    if (cur == slot) {
        return;
    }
    *(int *)((char *)data_ov025_020b5744[1] + 0x95f8) = 1;
}

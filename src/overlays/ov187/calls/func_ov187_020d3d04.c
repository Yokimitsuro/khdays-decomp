/*
 * func_ov187_020d3d04 -- x3 (ov185/186/187). If a pending request is queued and its mode is not one
 * of the "keep" modes, cancel it. If *(self+0x400) != 0, read the mode byte *(s8)(self+0x1c6): when
 * it is not 2, 4 or 5, run 020cb100(*(self+0x400)) and clear the slot. Always tick 020c7ca4(self).
 * (The 2nd incoming arg is unused -- the original reuses that register as the mode scratch.)
 */
extern void func_ov107_020cb100(int req);
extern void func_ov107_020c7ca4(int self);

void func_ov187_020d3d04(int self, int arg) {
    int req = *(int *)(self + 0x400);

    if (req != 0) {
        signed char mode = *(signed char *)(self + 0x1c6);
        if (mode != 2 && mode != 4 && mode != 5) {
            func_ov107_020cb100(req);
            *(int *)(self + 0x400) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}

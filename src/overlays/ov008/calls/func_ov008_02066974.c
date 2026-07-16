/* func_ov008_02066974 -- confirm the current grid selection on pen-up.
 * Only when the pen is released (touch[2]==0) and the grid is idle (obj+0x30==0), a selection
 * exists (obj+0x4c) and nothing is animating (obj+8): applies obj+0x70 and fires UI event 2. */
extern void func_ov008_02055dcc(unsigned short *touch);
extern void func_ov008_02063150(int obj, int key);
extern void func_02033b78(int a, int b);

void func_ov008_02066974(int param_1) {
    unsigned short touch[4];
    func_ov008_02055dcc(touch);
    if (touch[2] != 0 || *(int *)(param_1 + 0x30) != 0) {
        return;
    }
    if (*(int *)(param_1 + 0x4c) == 0) {
        return;
    }
    if (*(int *)(param_1 + 8) != 0) {
        return;
    }
    func_ov008_02063150(param_1, *(int *)(param_1 + 0x70));
    func_02033b78(0, 2);
}

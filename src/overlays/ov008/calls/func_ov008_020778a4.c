/* func_ov008_020778a4 -- drag the mission-info panel with the stylus.
 * Reads the touch state (func_ov008_02055dcc); if the pen is down, scrolls to
 * (touchY - height/2 - 0x3f) clamped to [0, 0x60 - height] (func_ov008_02074878).
 * On pen-up it clears the drag anchor (obj+0x158). */
extern void func_ov008_02055dcc(unsigned short *touch);
extern void func_ov008_02074878(int obj, int pos);

void func_ov008_020778a4(int param_1) {
    unsigned short touch[4];
    func_ov008_02055dcc(touch);
    if (touch[2] != 0) {
        int pos = ((int)touch[1] - *(int *)(param_1 + 0x164) / 2) - 0x3f;
        int lim;
        if (pos < 0) {
            pos = 0;
        }
        lim = 0x60 - *(int *)(param_1 + 0x164);
        if (pos > lim) {
            pos = lim;
        }
        func_ov008_02074878(param_1, pos);
        return;
    }
    *(int *)(param_1 + 0x158) = 0;
}

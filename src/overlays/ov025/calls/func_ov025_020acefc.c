/* func_ov025_020acefc -- drag the mission-info panel with the stylus.
 * Reads the touch state (func_ov025_020899dc); if the pen is down, scrolls to
 * (touchY - height/2 - 0x3f) clamped to [0, 0x60 - height] (func_ov025_020a9ed0).
 * On pen-up it clears the drag anchor (obj+0x158). */
extern void func_ov025_020899dc(unsigned short *touch);
extern void func_ov025_020a9ed0(int obj, int pos);

void func_ov025_020acefc(int param_1) {
    unsigned short touch[4];
    func_ov025_020899dc(touch);
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
        func_ov025_020a9ed0(param_1, pos);
        return;
    }
    *(int *)(param_1 + 0x158) = 0;
}

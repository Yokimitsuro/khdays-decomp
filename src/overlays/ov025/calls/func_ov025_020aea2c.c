/* func_ov025_020aea2c -- per-frame update of the ov025 list view: run the two live sub-updates
 * (obj+0xc / obj+0x10), then, only when a relayout is pending (obj+0x2c4), refresh the arrows,
 * rows, offset and scrollbar, latch the new offset (0x2cc = 0x2c8) and clear the flag. */
extern void func_ov025_020ae634(int obj);
extern void func_ov025_020ae6c0(int obj);
extern void func_ov025_020adcbc(int obj);
extern void func_ov025_020add28(int obj);
extern void func_ov025_020ade14(int obj);
extern void func_ov025_020ade68(int obj);

void func_ov025_020aea2c(int param_1) {
    if (*(int *)(param_1 + 0xc) != 0) {
        func_ov025_020ae634(param_1);
    }
    if (*(int *)(param_1 + 0x10) != 0) {
        func_ov025_020ae6c0(param_1);
    }
    if (*(int *)(param_1 + 0x2c4) == 0) {
        return;
    }
    func_ov025_020adcbc(param_1);
    func_ov025_020add28(param_1);
    func_ov025_020ade14(param_1);
    func_ov025_020ade68(param_1);
    *(int *)(param_1 + 0x2cc) = *(int *)(param_1 + 0x2c8);
    *(int *)(param_1 + 0x2c4) = 0;
}

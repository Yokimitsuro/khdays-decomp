/* func_ov009_02054cac -- set a mission list row's enabled/value state, ov008.
 * Finds the row widget (func_ov009_020518fc) for tag param_1; a non-negative param_2 enables it
 * (func_ov009_02051a68(...,1)) and pushes the value (func_ov009_02051b08), a negative param_2
 * disables it (func_ov009_02051a68(...,0)). */
extern int  func_ov009_0204e440(void);
extern int  func_ov009_020518fc(int list, int tag);
extern void func_ov009_02051a68(int list, int row, int enabled);
extern void func_ov009_02051b08(int list, int row, int value);

void func_ov009_02054cac(int tag, unsigned int value) {
    int list = func_ov009_0204e440();
    int row = func_ov009_020518fc(list, tag);
    if ((int)value >= 0) {
        func_ov009_02051a68(list, row, 1);
        func_ov009_02051b08(list, row, value & 0xffff);
    } else {
        func_ov009_02051a68(list, row, 0);
    }
}

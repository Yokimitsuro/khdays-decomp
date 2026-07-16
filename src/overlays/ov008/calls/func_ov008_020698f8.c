/* func_ov008_020698f8 -- set a mission list row's enabled/value state, ov008.
 * Finds the row widget (func_ov008_02054788) for tag param_1; a non-negative param_2 enables it
 * (func_ov008_02054ba4(...,1)) and pushes the value (func_ov008_02054c80), a negative param_2
 * disables it (func_ov008_02054ba4(...,0)). */
extern int  func_ov008_02050c54(void);
extern int  func_ov008_02054788(int list, int tag);
extern void func_ov008_02054ba4(int list, int row, int enabled);
extern void func_ov008_02054c80(int list, int row, int value);

void func_ov008_020698f8(int tag, unsigned int value) {
    int list = func_ov008_02050c54();
    int row = func_ov008_02054788(list, tag);
    if ((int)value >= 0) {
        func_ov008_02054ba4(list, row, 1);
        func_ov008_02054c80(list, row, value & 0xffff);
    } else {
        func_ov008_02054ba4(list, row, 0);
    }
}

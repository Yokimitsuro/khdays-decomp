/* func_ov008_02063184 -- move the grid selection to key param_2 (ignored while the grid is busy,
 * obj+0x30). Only acts if the key resolves (func_ov008_0205e83c) and differs from the current
 * selection (obj+0x70): applies it and fires UI event 2. */
extern int  func_ov008_0205e83c(int obj, unsigned int key);
extern void func_ov008_02063018(int obj, unsigned int key);
extern void func_02033b78(int a, int b);

void func_ov008_02063184(int param_1, unsigned int param_2) {
    if (*(int *)(param_1 + 0x30) != 0) {
        return;
    }
    if (func_ov008_0205e83c(param_1, param_2) != 0 &&
        param_2 != *(unsigned int *)(param_1 + 0x70)) {
        func_ov008_02063018(param_1, param_2);
        func_02033b78(0, 2);
    }
}

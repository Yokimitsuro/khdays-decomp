/* func_ov008_02078088 -- ov008 mission menu "back". If a selection is pending (obj+0x180), clear
 * its armed flag (obj+0x184), collapse the info panel (func_ov008_02076c48) and fire UI event 3.
 * Otherwise step back one page (func_ov008_02050a08(1)) and fire UI event 3. */
extern void func_ov008_02076c48(int obj, int arg);
extern void func_02033b78(int a, int b);
extern void func_ov008_02050a08(int step);

void func_ov008_02078088(int param_1) {
    if (*(int *)(param_1 + 0x180) != 0) {
        *(int *)(param_1 + 0x184) = 0;
        func_ov008_02076c48(param_1, 0);
        func_02033b78(0, 3);
        return;
    }
    func_ov008_02050a08(1);
    func_02033b78(0, 3);
}

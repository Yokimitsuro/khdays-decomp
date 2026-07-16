/* func_ov008_0207403c -- close the active menu popup, ov008.
 * On the active record: if it is modal-but-unconfirmed (rec+0x40 set, rec+0x44 clear) or has
 * no popup open (rec+0x4f8 == 0), does nothing. Otherwise dismisses the popup (func_ov008_02071d40
 * when rec+0x4fc set), releases it (func_ov008_02071ac8) and commits the input latch. */
extern int  func_ov008_02050cec(void);
extern void func_ov008_02071d40(int rec, int a);
extern void func_ov008_02071ac8(int rec, int a);
extern void func_02033b78(int a, int b);

void func_ov008_0207403c(void) {
    int rec = func_ov008_02050cec();
    if (*(int *)(rec + 0x40) != 0 && *(int *)(rec + 0x44) == 0) {
        return;
    }
    if (*(int *)(rec + 0x4f8) == 0) {
        return;
    }
    if (*(int *)(rec + 0x4fc) != 0) {
        func_ov008_02071d40(rec, 0);
    }
    func_ov008_02071ac8(rec, 0);
    func_02033b78(0, 3);
}

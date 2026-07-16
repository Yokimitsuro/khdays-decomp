/* func_ov008_0207825c -- close the active mission-info popup, ov008.
 * If the record is modal-but-unconfirmed (rec+0x150 set, rec+0x154 clear) or has no popup open
 * (rec+0x180 == 0), does nothing. Otherwise dismisses (func_ov008_02076e80 when rec+0x184 set),
 * releases (func_ov008_02076c48) and commits the input latch. */
extern int  func_ov008_02050cec(void);
extern void func_ov008_02076e80(int rec, int a);
extern void func_ov008_02076c48(int rec, int a);
extern void func_02033b78(int a, int b);

void func_ov008_0207825c(void) {
    int rec = func_ov008_02050cec();
    if (*(int *)(rec + 0x150) != 0 && *(int *)(rec + 0x154) == 0) {
        return;
    }
    if (*(int *)(rec + 0x180) == 0) {
        return;
    }
    if (*(int *)(rec + 0x184) != 0) {
        func_ov008_02076e80(rec, 0);
    }
    func_ov008_02076c48(rec, 0);
    func_02033b78(0, 3);
}

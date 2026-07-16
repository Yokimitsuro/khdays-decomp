/* func_ov025_020ad8b4 -- close the active mission-info popup, ov008.
 * If the record is modal-but-unconfirmed (rec+0x150 set, rec+0x154 clear) or has no popup open
 * (rec+0x180 == 0), does nothing. Otherwise dismisses (func_ov025_020ac4d8 when rec+0x184 set),
 * releases (func_ov025_020ac2a0) and commits the input latch. */
extern int  func_ov025_02084b14(void);
extern void func_ov025_020ac4d8(int rec, int a);
extern void func_ov025_020ac2a0(int rec, int a);
extern void func_02033b78(int a, int b);

void func_ov025_020ad8b4(void) {
    int rec = func_ov025_02084b14();
    if (*(int *)(rec + 0x150) != 0 && *(int *)(rec + 0x154) == 0) {
        return;
    }
    if (*(int *)(rec + 0x180) == 0) {
        return;
    }
    if (*(int *)(rec + 0x184) != 0) {
        func_ov025_020ac4d8(rec, 0);
    }
    func_ov025_020ac2a0(rec, 0);
    func_02033b78(0, 3);
}

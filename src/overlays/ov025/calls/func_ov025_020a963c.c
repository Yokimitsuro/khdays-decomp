/* func_ov025_020a963c -- close the active menu popup, ov008.
 * On the active record: if it is modal-but-unconfirmed (rec+0x40 set, rec+0x44 clear) or has
 * no popup open (rec+0x4f8 == 0), does nothing. Otherwise dismisses the popup (func_ov025_020a7264
 * when rec+0x4fc set), releases it (func_ov025_020a6fec) and commits the input latch. */
extern int  func_ov025_02084b14(void);
extern void func_ov025_020a7264(int rec, int a);
extern void func_ov025_020a6fec(int rec, int a);
extern void func_02033b78(int a, int b);

void func_ov025_020a963c(void) {
    int rec = func_ov025_02084b14();
    if (*(int *)(rec + 0x40) != 0 && *(int *)(rec + 0x44) == 0) {
        return;
    }
    if (*(int *)(rec + 0x4f8) == 0) {
        return;
    }
    if (*(int *)(rec + 0x4fc) != 0) {
        func_ov025_020a7264(rec, 0);
    }
    func_ov025_020a6fec(rec, 0);
    func_02033b78(0, 3);
}

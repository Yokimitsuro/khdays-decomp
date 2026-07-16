/* NONMATCHING: register-allocation tie — the ROM puts prev in r5 and next in r6, mwcc swaps them
 * (identical instruction sequence otherwise). Neither `int next = 0;` nor `int next = prev;`
 * reproduces the ROM's assignment; the two values are symmetric. */
/* func_ov025_020adcbc -- enable/disable the prev (tag 0x3f) and next (tag 0x3e) page arrows from
 * the current page (obj+0x2dc) and page count (obj+0x2e4). */
extern int  func_ov025_02084a8c(void);
extern int  func_ov025_0208843c(int table, int tag);
extern void func_ov025_0208884c(int table, int row, int enabled);

void func_ov025_020adcbc(int param_1) {
    int prev = 0;
    int next = prev;
    if (*(int *)(param_1 + 0x2e4) > 0) {
        prev = (*(int *)(param_1 + 0x2dc) > 0);
        if (*(int *)(param_1 + 0x2dc) < *(int *)(param_1 + 0x2e4)) {
            next = 1;
        }
    }
    {
        int table = func_ov025_02084a8c();
        func_ov025_0208884c(table, func_ov025_0208843c(table, 0x3f), prev);
        func_ov025_0208884c(table, func_ov025_0208843c(table, 0x3e), next);
    }
}

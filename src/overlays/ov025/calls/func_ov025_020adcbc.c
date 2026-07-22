/* func_ov025_020adcbc -- refresh the two scroll arrows of the ov025 list.
 * With a non-empty list (+0x2e4 > 0), the up arrow lights when the offset (+0x2dc) is past the
 * start and the down arrow when it has not reached the end; an empty list clears both. The two
 * widgets are items 0x3f and 0x3e of the table func_ov025_02084a8c hands back.
 *
 * Parked at a callee-saved swap between the two flags. The lever is not declaration order (six
 * orders and both copy directions all fail): it is that `prev = (x > 0);` is a BOOLEAN
 * MATERIALISATION and `if (x > 0) prev = 1;` is a predicated store. Both come out as `movgt`, but
 * only the second leaves the two flags in the order the ROM colours them -- the boolean form makes
 * mwcc treat that flag as a computed value and colour it after the other one. Writing both arms
 * the same way, as two plain `if`s over a shared zero, matches.
 */
extern int  func_ov025_02084a8c(void);
extern int  func_ov025_0208843c(int table, int tag);
extern void func_ov025_0208884c(int table, int row, int enabled);

void func_ov025_020adcbc(int param_1) {
    int prev;
    int next;
    prev = 0;
    next = prev;
    if (*(int *)(param_1 + 0x2e4) > 0) {
        if (*(int *)(param_1 + 0x2dc) > 0) {
            prev = 1;
        }
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

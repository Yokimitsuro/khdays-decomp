/* func_ov025_0208eb14 -- read the current player's slot config out of the default table, ov008.
 * Copies the 20-word default config template (data_ov025_020b3e88) onto the stack, then for the
 * current player's save accessor (func_020315c0) returns, via the optional out-params, the
 * template entry selected by the accessor's index (accessor+4) and that raw index. */
struct T20 { int w[20]; };
extern int func_02030788(void);
extern int func_020315c0(int player);
extern struct T20 data_ov025_020b3e88;

void func_ov025_0208eb14(int *outValue, int *outIndex) {
    struct T20 tbl = data_ov025_020b3e88;
    int slot = func_020315c0(func_02030788());
    if (slot != 0) {
        if (outValue != 0) {
            *outValue = tbl.w[*(int *)(slot + 4)];
        }
        if (outIndex != 0) {
            *outIndex = *(int *)(slot + 4);
        }
    }
}

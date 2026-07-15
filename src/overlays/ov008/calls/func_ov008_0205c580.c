/* func_ov008_0205c580 -- read the current player's slot config out of the default table, ov008.
 * Copies the 20-word default config template (data_ov008_0208f328) onto the stack, then for the
 * current player's save accessor (func_020315c0) returns, via the optional out-params, the
 * template entry selected by the accessor's index (accessor+4) and that raw index. */
struct T20 { int w[20]; };
extern int func_02030788(void);
extern int func_020315c0(int player);
extern struct T20 data_ov008_0208f328;

void func_ov008_0205c580(int *outValue, int *outIndex) {
    struct T20 tbl = data_ov008_0208f328;
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

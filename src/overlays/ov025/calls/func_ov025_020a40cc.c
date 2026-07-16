/* func_ov025_020a40cc -- per-frame update of the ov025 panel's live sub-widgets
 * (obj[0], obj[2], obj[5] gate their updates). Same shape as func_ov008_0206ea38. */
extern void func_ov025_020a3894(int *obj);
extern void func_ov025_020a3be8(int obj);
extern void func_ov025_020a3db4(int obj);

void func_ov025_020a40cc(int *param_1) {
    if (*param_1 != 0) {
        func_ov025_020a3894(param_1);
    }
    if (param_1[2] != 0) {
        func_ov025_020a3be8((int)param_1);
    }
    if (param_1[5] == 0) {
        return;
    }
    func_ov025_020a3db4((int)param_1);
}

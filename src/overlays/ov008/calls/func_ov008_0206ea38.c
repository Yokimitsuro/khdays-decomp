/* func_ov008_0206ea38 -- per-frame update of the ov008 panel: base tick (func_ov008_0206b5f4),
 * then each live sub-widget in turn (obj[0], obj[2], obj[5] gate their updates). */
extern void func_ov008_0206b5f4(void);
extern void func_ov008_0206e200(int *obj);
extern void func_ov008_0206e554(int obj);
extern void func_ov008_0206e720(int obj);

void func_ov008_0206ea38(int *param_1) {
    func_ov008_0206b5f4();
    if (*param_1 != 0) {
        func_ov008_0206e200(param_1);
    }
    if (param_1[2] != 0) {
        func_ov008_0206e554((int)param_1);
    }
    if (param_1[5] == 0) {
        return;
    }
    func_ov008_0206e720((int)param_1);
}

/* Notify func_02030788, then map a 0..4 slot index to its record pointer
 * (global + 0x2e + index*6); return 0 for a missing global or out-of-range index. */
extern int func_02030788(int arg);
extern int data_ov008_02090f00;

int func_ov008_0204ecd8(int param_1) {
    int g;
    func_02030788(param_1);
    g = *(int *)&data_ov008_02090f00;
    if (g == 0) return 0;
    if (param_1 < 0) return 0;
    if (param_1 > 4) return 0;
    return param_1 * 6 + (g + 0x2e);
}

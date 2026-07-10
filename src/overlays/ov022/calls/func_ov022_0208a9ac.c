extern int func_02023c40(void);

int func_ov022_0208a9ac(int param_1, int param_2, int param_3) {
    int factor = param_3 / 3 * 3;
    int iVar3 = func_02023c40() == 1 ? param_2 * 3 / 2 : param_2;
    factor = factor >> 0xc;
    if (0 < param_1 - factor * iVar3) {
        return param_1 - factor * (func_02023c40() == 1 ? param_2 * 3 / 2 : param_2);
    }
    return 0;
}

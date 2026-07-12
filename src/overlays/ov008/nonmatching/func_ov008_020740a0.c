/* PROVEN TIE - byte-identical twin of func_ov008_0206f864 (same stack-slot/register
 * frame tie). Kept here so the ov008 blob stays byte-exact. */
extern int func_02013768(int a, int b, int key, int *cont);

int func_ov008_020740a0(int param_1, int param_2) {
    int cont = 0;
    int best = 0;
    int i;
    if (param_1 == 0) return 0;
    if (param_2 == 0) return 0;
    for (i = 0; i < 5; i++) {
        int r = func_02013768(*(int *)(param_1 + 0x20), *(int *)(param_1 + 0x24), param_2, &cont);
        if (r > best) best = r;
        if (cont == 0) break;
    }
    return best;
}

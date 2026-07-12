/*
 * Return the largest unsigned value representable in param_1 decimal digits:
 * 10^param_1 - 1 (e.g. 3 -> 999). Returns -1 for a negative digit count.
 */
int func_ov002_0206189c(int param_1) {
    int value = 1;
    int i;

    if (param_1 < 0) {
        return -1;
    }
    for (i = 0; i < param_1; i++) {
        value = value * 10;
    }
    return value - 1;
}

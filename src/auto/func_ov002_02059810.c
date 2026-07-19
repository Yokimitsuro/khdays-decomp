/* Number of decimal digits in |n| (at least 1). */
int func_ov002_02059810(int n) {
    int digits = 0;
    if (n < 0) {
        n = -n;
    }
    do {
        n = n / 10;
        digits++;
    } while (n > 0);
    return digits;
}

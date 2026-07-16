/* func_ov008_02069a64 -- return decimal digit `pos` of `value`, counted from the most significant.
 * func_ov008_02069a34 gives the digit count; a negative value, or a position past the end, reports
 * -1. Walks down from the top digit dividing the place value by ten each step, and reports the
 * digit once the walk reaches `pos`.
 * The digit is clamped to 0..9 defensively -- func_02020400's result is trusted only that far. */
extern int func_ov008_02069a34(int value);
extern int func_02020400(int value, int place);

int func_ov008_02069a64(int pos, int value) {
    int n;
    int i;
    int k;
    int place;
    int d;

    n = func_ov008_02069a34(value);
    place = 1;
    if (value < 0 || pos >= n) {
        return -1;
    }

    i = n - 1;
    for (k = 1; k < n; k++) {
        place = place * 10;
    }

    while (place > 0) {
        d = func_02020400(value, place) % 10;
        if (d < 0) {
            d = 0;
        } else if (d > 9) {
            d = 9;
        }
        if (i == pos) {
            return d;
        }
        place = place / 10;
        i--;
    }
    return -1;
}

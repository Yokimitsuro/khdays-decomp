/* Fades every row of the owner's table down in proportion to how far the timer has left to run;
 * once the timer passes 0x1800 the rows are simply cleared. */
void func_ov267_020d560c(int *self) {
    int *s = (int *)self[1];
    int t = s[2];
    int i;
    if (t == 0) {
        return;
    }
    if (t > 0x1800) {
        return;
    }
    s[2] = t + *(int *)(*self + 0x2c);
    for (i = 0; i < *(int *)(*s + 0x8c); i++) {
        int *row = (int *)(*(int *)(*s + 0x90) + i * 0x38);
        int v = s[2];
        int scaled;
        if (v > 0x1800) {
            scaled = 0;
        } else {
            scaled = row[1] * (0x1800 - v) / 0x1800;
        }
        row[1] = scaled;
    }
}

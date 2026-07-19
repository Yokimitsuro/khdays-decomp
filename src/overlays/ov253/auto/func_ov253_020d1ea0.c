/* Advances every live row of the owner's table: phase 0 eases the width up towards 0x1000 and
 * hands over at 0xf00, phase 1 counts the hold timer down by the caller's step, phase 2 eases
 * the width back to nothing. */
void func_ov253_020d1ea0(int *self, int unused, int *ctx) {
    int i;
    for (i = 0; i < self[0x23]; i++) {
        char *row = (char *)self[0x24] + i * 0x38;
        int t = *(int *)row;
        if (t > 0) {
            switch (*(int *)(row + 0x18)) {
            case 0: {
                int v = t + (0x1000 - t) / 10;
                *(int *)row = v;
                if (v >= 0xf00) {
                    *(int *)(row + 0x18) = 1;
                }
                break;
            }
            case 1: {
                int v = *(int *)(row + 0x1c) - **(int **)((char *)ctx + 8);
                *(int *)(row + 0x1c) = v;
                if (v <= 0) {
                    *(int *)(row + 0x18) = 2;
                }
                break;
            }
            case 2: {
                int v = t + (0 - t) / 10;
                *(int *)row = v;
                if (v < 0x100) {
                    *(int *)row = 0;
                }
                break;
            }
            }
        }
    }
}

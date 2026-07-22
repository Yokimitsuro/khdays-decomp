extern int func_02032634();

void func_ov008_02054cc4(char *a, int *b)
{
    int i = 0;
    int *previous = *(int **)(a + 0x4a70);

    for (; i < 2; i++) {
        if (previous != 0) {
            if (previous[i + 5] != -1 && previous[i + 13] != -1) {
                func_02032634(a, previous[i + 5], previous[i + 13]);
            }
        }

        if (b != 0) {
            if (b[i + 5] != -1 && b[i + 15] != -1) {
                func_02032634(a, b[i + 5], b[i + 15]);
            }
        }

        *(int **)(a + 0x4a70) = b;
    }
}

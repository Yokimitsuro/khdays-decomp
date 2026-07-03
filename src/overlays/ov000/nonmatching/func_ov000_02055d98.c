extern int func_02032634();

void func_ov000_02055d98(char *a, int *b)
{
    int i = 0;
    int *r5 = *(int **)(a + 0x4a70);

    for (; i < 2; i++) {
        if (r5 != 0) {
            if (r5[i + 5] != -1 && r5[i + 13] != -1)
                func_02032634(a);
        }
        if (b != 0) {
            if (b[i + 5] != -1 && b[i + 15] != -1)
                func_02032634(a);
        }
        *(int **)(a + 0x4a70) = b;
    }
}

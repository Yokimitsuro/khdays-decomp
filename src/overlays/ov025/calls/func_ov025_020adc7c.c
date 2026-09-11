extern void func_ov025_020ada88(int arg0, int arg1, int arg2);

void func_ov025_020adc7c(int arg0) {
    int total = *(int *)(arg0 + 0x2d0);
    int chunk = total / 16;
    int i;

    for (i = 0; i < 11; i++) {
        func_ov025_020ada88(arg0, i, i + chunk);
    }

    *(int *)(arg0 + 0x14) = 1;
}

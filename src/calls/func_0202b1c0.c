extern void func_0202a7dc(int);

void func_0202b1c0(int *param_1) {
    if ((*param_1 & 0x20) == 0) {
        func_0202a7dc((int)param_1 + 4);
    }
    *param_1 |= 0x20;
}

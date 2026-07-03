extern void func_ov050_020b688c(int a);

void func_ov050_020b61d4(int param_1, int param_2) {
    int i;
    func_ov050_020b688c(param_1);
    i = 0;
    do {
        i++;
        *(int *)(param_2 + 0x10) = 0;
        param_2 += 0x118;
    } while (i < 2);
}

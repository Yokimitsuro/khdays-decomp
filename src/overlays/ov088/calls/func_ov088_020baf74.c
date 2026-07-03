extern void func_ov088_020bb62c(int a);

void func_ov088_020baf74(int param_1, int param_2) {
    int i;
    func_ov088_020bb62c(param_1);
    i = 0;
    do {
        i++;
        *(int *)(param_2 + 0x10) = 0;
        param_2 += 0x118;
    } while (i < 2);
}

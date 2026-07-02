extern void func_01fff774(unsigned short *p, int a, int b);
void func_0203be9c(int param_1, int param_2, int param_3) {
    if (*(short *)(*(int *)(param_1 + 0x8c) + param_2 * 2) == 0) return;
    func_01fff774(*(unsigned short **)(param_1 + 0x88), param_2, param_3);
}

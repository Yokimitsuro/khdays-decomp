extern int func_02021980(int a, void *b);

int func_02022290(int param_1, int param_2) {
    *(int *)(param_1 + 0x12c) = 1;
    *(int *)(param_1 + 0x130) = func_02021980(param_1, (void *)param_2);
    *(int *)(param_1 + 0x134) = func_02021980(param_1, (void *)(param_2 + 8));
    return 3;
}

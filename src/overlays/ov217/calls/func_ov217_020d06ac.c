extern void func_0203c5c0();
extern void func_ov217_020d0de8(void);

void func_ov217_020d06ac(int param_1) {
    int *local_10;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x7c, func_ov217_020d0de8, 0, &local_10);
    *local_10 = param_1;
    local_10[1] = *(int *)(*local_10 + 0x384);
    *(int **)(param_1 + 0x214) = local_10;
}

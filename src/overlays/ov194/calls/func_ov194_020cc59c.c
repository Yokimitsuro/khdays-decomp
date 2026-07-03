extern void func_0203c5c0();
extern void func_ov194_020cc884(void);

void func_ov194_020cc59c(int param_1) {
    int *local_10;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x58, func_ov194_020cc884, 0, &local_10);
    *local_10 = param_1;
    local_10[1] = *(int *)(*local_10 + 0x384);
    *(int **)(param_1 + 0x214) = local_10;
}

extern void func_0203c5c0();
extern void func_ov175_020ccb74(void);
void func_ov175_020cc75c(int param_1, int param_2, int param_3, int param_4) {
    int *local_10;
    int uStack_c = param_4;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 100, 0x8c, func_ov175_020ccb74, 0, &local_10);
    *local_10 = param_1;
    local_10[1] = *(int *)(*local_10 + 0x384);
    *(int **)(param_1 + 0x214) = local_10;
}

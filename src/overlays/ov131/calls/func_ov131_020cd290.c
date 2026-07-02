extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov131_020cd2f0(void);
void func_ov131_020cd290(int *param_1) {
    int v = *(int *)(*param_1 + 0x2c) * 0x1e;
    int *state = (int *)param_1[1];
    state[5] = v / 30;
    func_ov107_020c9264(*state, 8, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 8), func_ov131_020cd2f0);
}

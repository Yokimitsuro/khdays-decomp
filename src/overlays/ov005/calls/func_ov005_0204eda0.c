/* Advance 02030788, then map the current 020315c0 slot to a priority table, storing its index. */
extern void func_02030788(int a);
extern int func_020315c0(void);
extern int data_ov005_0205b2e4;
int func_ov005_0204eda0(int param_1) {
    int r = 0xa;
    func_02030788(param_1);
    int x = func_020315c0();
    if (x != 0) r = (&data_ov005_0205b2e4)[*(int *)(x + 4)];
    if (param_1 != 0) *(int *)param_1 = *(int *)(x + 4);
    return r;
}

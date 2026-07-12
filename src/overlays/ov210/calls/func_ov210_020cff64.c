/* Bind param_2 to the sub-object at *(*(param_1)+0x3d4), then run the ov107 attach. */
extern void func_ov107_020c2b20(int a, int b);
extern void func_ov107_020c7b70(int a, int b);
void func_ov210_020cff64(int param_1, int param_2) {
    func_ov107_020c2b20(param_2, *(int *)*(int *)(param_1 + 0x3d4));
    func_ov107_020c7b70(param_1, param_2);
}

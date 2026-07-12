/* Bind param_2 to the sub-object at *(*(param_1)+0x3d4), then run the ov107 attach. */
extern void func_ov107_020c2b38(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
void func_ov282_020cff98(int param_1, int param_2) {
    func_ov107_020c2b38(param_2, *(int *)*(int *)(param_1 + 0x3d4));
    func_ov107_020c7c1c(param_1, param_2);
}

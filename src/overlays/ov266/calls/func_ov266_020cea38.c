/* Finalize the list at (param_1)+0x388 with param_2, re-init it, then run the ov107 attach. */
extern void func_0203c7ac(int a, int b);
extern void func_0203c86c(int a, int b);
extern void func_ov107_020c6980(int a, int b);
void func_ov266_020cea38(int param_1, int param_2) {
    func_0203c7ac(*(int *)(param_1 + 0x388), param_2);
    func_0203c86c(*(int *)(param_1 + 0x388), 1);
    func_ov107_020c6980(param_1, param_2);
}

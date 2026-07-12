/* Bind param_2 to the sub-object at (param_1)+0x3b0, then run the ov107 attach for the pair. */
extern void func_ov107_020c2b20(int a, int b);
extern void func_ov107_020c7b70(int a, int b);
void func_ov209_020d23bc(int param_1, int param_2) {
    func_ov107_020c2b20(param_2, *(int *)(param_1 + 0x3b0));
    func_ov107_020c7b70(param_1, param_2);
}

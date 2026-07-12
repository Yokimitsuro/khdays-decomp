/* Bind param_2 to the sub-object at (param_1)+0x3b8, then run the ov107 attach for the pair. */
extern void func_ov107_020c9ec8(int a, int b);
extern void func_ov107_020c6980(int a, int b);
void func_ov282_020cff48(int param_1, int param_2) {
    func_ov107_020c9ec8(*(int *)(param_1 + 0x3b8), param_2);
    func_ov107_020c6980(param_1, param_2);
}

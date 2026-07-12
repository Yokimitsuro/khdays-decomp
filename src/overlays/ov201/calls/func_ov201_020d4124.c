/* Destroy the three sub-instances at (param_1)+4/+8/+0xc. */
extern void func_0203c7e8(int a);
void func_ov201_020d4124(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 4));
    func_0203c7e8(*(int *)(param_1 + 8));
    func_0203c7e8(*(int *)(param_1 + 0xc));
}

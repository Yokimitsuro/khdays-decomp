/* Teardown: release *(+0x3a8) target, free the +0x3a8 table, release +0x388/+0x38c, finalise. */
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov213_020d0758(int param_1) {
    func_0203c7e8(*(int *)*(int *)(param_1 + 0x3a8));
    func_0203d194(*(int *)(param_1 + 0x3a8));
    func_0203c7e8(*(int *)(param_1 + 0x388));
    func_0203c7e8(*(int *)(param_1 + 0x38c));
    func_ov107_020c68ec(param_1);
}

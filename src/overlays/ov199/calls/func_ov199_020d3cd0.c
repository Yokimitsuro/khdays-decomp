/* Teardown: release +0x384/+0x388/+0x3f0, finalise. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov199_020d3cd0(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x388));
    func_0203c7e8(*(int *)(param_1 + 0x3f0));
    func_ov107_020c68ec(param_1);
}

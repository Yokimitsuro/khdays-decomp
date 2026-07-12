/* Teardown: release +0x384/+0x3a4, finalise. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov238_020d2810(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x3a4));
    func_ov107_020c68ec(param_1);
}

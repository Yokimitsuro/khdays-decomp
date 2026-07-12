/* Teardown: release +0x384 (c7e8) and +0x390 (ov107), finalise. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_ov107_020c68ec(int a);
void func_ov256_020d12c0(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c9eac(*(int *)(param_1 + 0x390));
    func_ov107_020c68ec(param_1);
}

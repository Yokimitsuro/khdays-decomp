/* Teardown: release +0x384/+0x398/+0x394, finalise. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov223_020d4030(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x398));
    func_0203c7e8(*(int *)(param_1 + 0x394));
    func_ov107_020c68ec(param_1);
}

/* Teardown: run 0202a440 on &(+0x388), release +0x384, finalise. */
extern void func_0202a440(int a);
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov146_020ce514(int param_1) {
    func_0202a440(param_1 + 0x388);
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c68ec(param_1);
}

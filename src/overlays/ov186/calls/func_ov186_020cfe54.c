/* Tear down the actor: release the list at +0x390, destroy the render instance at +0x384,
 * then release the actor itself. */
extern void func_0203d194(int a);
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov186_020cfe54(int param_1) {
    func_0203d194(*(int *)(param_1 + 0x390));
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c68ec(param_1);
}

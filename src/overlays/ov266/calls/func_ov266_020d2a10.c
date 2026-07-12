/* Tear down the actor: destroy the render instance (+0x384) and the list instance (+0x394),
 * then release the actor itself. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov266_020d2a10(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x394));
    func_ov107_020c68ec(param_1);
}

/* Tear down the actor: destroy the render instance at +0x384 and the list instance at
 * +0x394 if present, then release the actor itself. */
extern void func_0203c7e8(int a);
extern void func_ov107_020c68ec(int a);
void func_ov224_020d4240(int param_1) {
    if (*(int *)(param_1 + 0x384) != 0) func_0203c7e8(*(int *)(param_1 + 0x384));
    if (*(int *)(param_1 + 0x394) != 0) func_0203c7e8(*(int *)(param_1 + 0x394));
    func_ov107_020c68ec(param_1);
}

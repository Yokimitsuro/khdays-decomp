/* Tear down the actor: destroy the render (+0x384) and list (+0x3a8) instances, free the 4
 * slot handles at +0x3a4, release the 3 sub-actors at +0x390, then release the handle table
 * and the actor itself. */
extern void func_0203c7e8(int a);
extern void func_ov201_020d4124(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
struct row8_020ce0d0 { int p; int q; };
void func_ov201_020d1d10(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x3a8));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(((struct row8_020ce0d0 *)*(int *)(param_1 + 0x3a4))[i].p);
    }
    for (i = 0; i < 3; i++) {
        func_ov201_020d4124(((int *)param_1)[i + 0xe4]);
    }
    func_0203d194(*(int *)(param_1 + 0x3a4));
    func_ov107_020c68ec(param_1);
}

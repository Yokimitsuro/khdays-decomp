/* Rebuild the +0x388 work list for the actor at *(+0x384): reset it, seed an entry
 * from the sub-object at *(owner+0x88), run the local setup + ov107 query (index+1),
 * append the result, then re-init and finalize the owner list. */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern int func_ov223_020cfd80(int a);
extern int func_ov107_020c9440(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
void func_ov223_020d0628(int param_1, int param_2, int param_3) {
    int owner = *(int *)(*(int *)(param_1 + 0x384) + 0x88);
    func_0202a440(param_1 + 0x388);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_ov223_020cfd80(param_1);
    func_0202a388(param_1 + 0x388, owner, func_ov107_020c9440(param_1, param_2 + 1), 0xc);
    func_0203b9ac(*(int *)(param_1 + 0x384), param_1 + 0x388);
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, 0, param_3);
    func_0203c7ac(*(int *)(param_1 + 0x384), 0);
}

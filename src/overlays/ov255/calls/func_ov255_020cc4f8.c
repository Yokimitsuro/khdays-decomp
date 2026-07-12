/* Object teardown: release/free sub-resources and run the finaliser. */
struct row8 { int p; int pad; };
extern void func_0202a440(int a);
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
extern void func_ov107_020c9eac(int a);
void func_ov255_020cc4f8(int param_1) {
    int i;
    func_0202a440(*(int *)(param_1 + 0x388));
    func_0203d194(*(int *)(param_1 + 0x388));
    func_0202a440(*(int *)(param_1 + 0x390));
    func_0203d194(*(int *)(param_1 + 0x390));
    func_ov107_020c9eac(*(int *)(param_1 + 0x3a4));
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x38c));
    for (i = 0; i < 12; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3ec))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3ec));
    func_0203d194(*(int *)(param_1 + 0x3f0));
    func_ov107_020c68ec(param_1);
}

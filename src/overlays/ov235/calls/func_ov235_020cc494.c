/* Object teardown: release/free sub-resources and run the finaliser. */
struct row8 { int p; int pad; };
extern void func_0202a440(int a);
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
extern void func_ov107_020c9eac(int a);
void func_ov235_020cc494(int param_1) {
    int i;
    func_0202a440(*(int *)(param_1 + 0x388));
    func_0203d194(*(int *)(param_1 + 0x388));
    func_0202a440(*(int *)(param_1 + 0x390));
    func_0203d194(*(int *)(param_1 + 0x390));
    func_0202a440(*(int *)(param_1 + 0x398));
    func_0203d194(*(int *)(param_1 + 0x398));
    func_ov107_020c9eac(*(int *)(param_1 + 0x3a8));
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x38c));
    func_0203c7e8(*(int *)(param_1 + 0x394));
    for (i = 0; i < 11; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3bc))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3bc));
    func_ov107_020c68ec(param_1);
}

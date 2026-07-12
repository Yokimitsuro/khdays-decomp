/* Teardown with an extra ov107 release. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov160_020cc24c(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c9eac(*(int *)(param_1 + 0x3a0));
    for (i = 0; i < 9; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x390))[i].p);
    func_0203d194(*(int *)(param_1 + 0x390));
    func_ov107_020c68ec(param_1);
}

/* Teardown: release +0x388, extra ov107 release, the 8 stride-8 table entries at +0x390, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov137_020cc248(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x388));
    func_ov107_020c9eac(*(int *)(param_1 + 0x39c));
    for (i = 0; i < 8; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x390))[i].p);
    func_0203d194(*(int *)(param_1 + 0x390));
    func_ov107_020c68ec(param_1);
}

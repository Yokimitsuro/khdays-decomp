/* Teardown: release +0x388, release the 3 stride-8 entries in the +0x3a4 table, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov277_020cd64c(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x388));
    for (i = 0; i < 3; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3a4))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3a4));
    func_ov107_020c68ec(param_1);
}

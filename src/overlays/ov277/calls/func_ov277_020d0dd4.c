/* Tear down: release +0x388, release the 3 stride-8 entries in the +0x38c table, free it and
 * run the ov107 finaliser. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov277_020d0dd4(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x388));
    for (i = 0; i < 3; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x38c))[i].p);
    func_0203d194(*(int *)(param_1 + 0x38c));
    func_ov107_020c68ec(param_1);
}

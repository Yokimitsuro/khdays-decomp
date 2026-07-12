/* Teardown: free +0x3e4 table, release +0x384/+0x3a0, release the 2 stride-8 table entries at
 * +0x3e8, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov253_020d2388(int param_1) {
    int i;
    func_0203d194(*(int *)(param_1 + 0x3e4));
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_0203c7e8(*(int *)(param_1 + 0x3a0));
    for (i = 0; i < 2; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3e8))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3e8));
    func_ov107_020c68ec(param_1);
}

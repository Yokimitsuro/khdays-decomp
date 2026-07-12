/* Tear down: release the 2 stride-8 entries in the +0x394 table, free it, release +0x388 and
 * run the ov107 finaliser. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov213_020d1824(int param_1) {
    int i;
    for (i = 0; i < 2; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x394))[i].p);
    func_0203d194(*(int *)(param_1 + 0x394));
    func_0203c7e8(*(int *)(param_1 + 0x388));
    func_ov107_020c68ec(param_1);
}

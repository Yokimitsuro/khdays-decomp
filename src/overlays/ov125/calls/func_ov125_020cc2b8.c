/* Tear down this object: release the +0x384 resource, release each of the 9 stride-8 entries in
 * the +0x39c table, free the table and run the ov107 finaliser. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov125_020cc2b8(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    for (i = 0; i < 9; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x39c))[i].p);
    func_0203d194(*(int *)(param_1 + 0x39c));
    func_ov107_020c68ec(param_1);
}

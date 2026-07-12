/* Teardown: run 0202a440 on &(+0x3a8), release +0x384, ov107-release +0x3a0,
 * release the 5 stride-8 table entries at +0x3a4, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0202a440(int a);
extern void func_0203c7e8(int a);
extern void func_ov107_020c9eac(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov245_020d57ec(int param_1) {
    int i;
    func_0202a440(param_1 + 0x3a8);
    func_0203c7e8(*(int *)(param_1 + 0x384));
    func_ov107_020c9eac(*(int *)(param_1 + 0x3a0));
    for (i = 0; i < 5; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3a4))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3a4));
    func_ov107_020c68ec(param_1);
}

/* Teardown: release +0x384, the 2 stride-8 table entries at +0x398, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov253_020d3c38(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x384));
    for (i = 0; i < 2; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x398))[i].p);
    func_0203d194(*(int *)(param_1 + 0x398));
    func_ov107_020c68ec(param_1);
}

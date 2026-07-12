/* Teardown: release +0x38c/+0x3b8, the 5 stride-8 table entries at +0x3b0, free it, finalise. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov253_020ce820(int param_1) {
    int i;
    func_0203c7e8(*(int *)(param_1 + 0x38c));
    func_0203c7e8(*(int *)(param_1 + 0x3b8));
    for (i = 0; i < 5; i++)
        func_0203c7e8(((struct row8 *)*(int *)(param_1 + 0x3b0))[i].p);
    func_0203d194(*(int *)(param_1 + 0x3b0));
    func_ov107_020c68ec(param_1);
}

/* Tear down: release the +0x394/+0x388/+0x38c resources and run the ov107 finaliser. */
struct row8 { int p; int pad; };
extern void func_0203c7e8(int a);
extern void func_0203d194(int a);
extern void func_ov107_020c68ec(int a);
void func_ov273_020d6144(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x394));
    func_0203c7e8(*(int *)(param_1 + 0x388));
    func_0203c7e8(*(int *)(param_1 + 0x38c));
    func_ov107_020c68ec(param_1);
}

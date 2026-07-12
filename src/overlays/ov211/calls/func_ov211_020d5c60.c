/* Release the sub-resource at +0x190, then tear down the object. */
extern void func_0203c7e8(int arg);
extern void func_ov107_020c3d84(int arg);
void func_ov211_020d5c60(int param_1) {
    func_0203c7e8(*(int *)(param_1 + 0x190));
    func_ov107_020c3d84(param_1);
}
